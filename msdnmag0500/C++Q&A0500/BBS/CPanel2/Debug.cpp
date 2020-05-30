////////////////////////////////////////////////////////////////
// PixieLib(TM) Copyright 1997-1998 Paul DiLascia
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// General purpose debugging utilities.
//
#include "StdAfx.h"
#include "Debug.h"
#include "TraceWin.h"

#ifdef _DEBUG

#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

int CTraceFn::nIndent=-1;	    // current indent level

////////////////
// These two functions are copied from dumpout.cpp in the MFC source,
// with my modification to do indented output
//
void AFXAPI AfxDump(const CObject* pOb)
{
	afxDump << pOb;
}

void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...)
{
	if (afxDump.m_pFile == NULL)
		PxlTraceInit(); // initialize TraceWin tracing while I'm here

	// all AfxTrace output is controlled by afxTraceEnabled
	if (!afxTraceEnabled)
		return;

	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	TCHAR szBuffer[512];

	nBuf = _vstprintf(szBuffer, lpszFormat, args);
	ASSERT(nBuf < countof(szBuffer));

	// PD: Here are my added lines to do the indenting. Search
	// for newlines and insert prefix before each one. Yawn.
	//
	static BOOL bStartNewLine = TRUE;
	TCHAR* nextline;
	for (TCHAR* start = szBuffer; *start; start=nextline+1) {
		if (bStartNewLine) {
			if ((afxTraceFlags & traceMultiApp) && (AfxGetApp() != NULL))
				afxDump << AfxGetApp()->m_pszExeName << _T(": ");
			afxDump << CString(' ',CTraceFn::nIndent);
			bStartNewLine = FALSE;
		}
		nextline = _tcschr(start, '\n');
		if (nextline) {
			*nextline = 0; // terminate string at newline
			bStartNewLine = TRUE;
		}
		afxDump << start;
		if (!nextline)
			break;
		afxDump << _T("\n"); // the one I terminated
	}
		
	va_end(args);
}

#endif // DEBUG

