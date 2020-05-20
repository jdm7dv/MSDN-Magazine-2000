// BmpColInfo.cpp : Implementation of CBmpColInfo
#include "stdafx.h"
#include "BmpCol.h"
#include "BmpColInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CBmpColInfo


HRESULT CBmpColInfo::GetColumnInfo(DWORD dwIndex, SHCOLUMNINFO *psci)
{ 
	// Since this extension might provide more columns, the
	// index is used to enumerate them. The shell calls 
	// repeatedly this method with progressive indexes, until
	// you return S_FALSE. Return S_FALSE only when you've
	// finished with all your columns. dwIndex is a 0-based 
	// index. Notice that without this checking you enter
	// an infinite loop!
	if (dwIndex >= BMPCH_NUMOFCOLS)
		return S_FALSE;

	// Now fills out the SHCOLUMNINFO structure to let the 
	// shell know about general-purpose features of the column

	// Identifies the column with a FMTID/PID pair. You'd
	// define one of these pairs for each column you're
	// adding here.
	psci->scid.fmtid = *_Module.pguidVer;	// use object's CLSID
	psci->scid.pid = 1;
	//psci->scid.fmtid = FMTID_SummaryInformation;
	//psci->scid.pid = 2;	//title

	// Sets type, alignment and default width
	psci->vt = VT_LPSTR;				// data is LPSTR
	psci->fmt = LVCFMT_LEFT;			// left alignment
	psci->cChars = BMPCH_DEFWIDTH;		// default width in chars
	
	// Other flags
	psci->csFlags = SHCOLSTATE_TYPE_STR;
		
	// Caption and description
	wcsncpy(psci->wszTitle,  
			L"Dimensions",  
			MAX_COLUMN_NAME_LEN);
	wcsncpy(psci->wszDescription, 
			L"Provides dimensions and colors for BMPs", 
			MAX_COLUMN_DESC_LEN);

	return S_OK; 
}

// IColumnProvider::GetItemData
HRESULT CBmpColInfo::GetItemData(LPCSHCOLUMNID pscid, LPCSHCOLUMNDATA pscd, VARIANT *pvarData)
{ 
	USES_CONVERSION;
	// The shell calls this method for each file displayed
	// in the folder where this column has been selected. 
	// The SHCOLUMNID structure identifies univocally the
	// column just in case you're handling more than one.

	// In this case, I'm managing just one column so I'll
	// ignore the SHCOLUMNID param.

	// Information about the specific file is contained in the 
	// SHCOLUMNDATA structure. I'm interested only in .BMP.
	if (wcsicmp(pscd->pwszExt, L".bmp"))
		return S_FALSE;
	//if (wcsicmp(pscd->pwszExt, L".htm"))
	//	return S_FALSE;

	// Reads dimensions and palette size from the BMP file
	TCHAR szBuf[BMPCH_MAXSIZE];
	ZeroMemory(szBuf, BMPCH_MAXSIZE);
	GetBitmapInfo(pscd->wszFile, szBuf);
	//GetTitleFromHTML(pscd->wszFile, szBuf);

	// The return value (a string in this case) must be 
	// packed as a Variant.
	CComVariant cv(szBuf);
	cv.Detach(pvarData); 

	return S_OK; 
}

HRESULT CBmpColInfo::GetBitmapInfo(LPCWSTR wszFile, LPTSTR p)
{
	USES_CONVERSION;

	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	HFILE h;

	// Opens the file and reads the header
	h = _lopen((LPCSTR)OLE2T((LPOLESTR)wszFile), OF_READ);
	if (h==HFILE_ERROR)
		return S_OK;

	_lread(h, (LPBITMAPFILEHEADER)&bf, sizeof(BITMAPFILEHEADER));
	_lread(h, (LPBITMAPINFOHEADER)&bi, sizeof(BITMAPINFOHEADER));
	_lclose(h);

	// Formats the string 
	wsprintf(p, _T("%d x %d x %d"),
			 bi.biWidth, bi.biHeight, bi.biBitCount);  

	return S_OK;
}

HRESULT CBmpColInfo::GetTitleFromHTML(LPCWSTR wszFile, LPTSTR p)
{
	HFILE h;

	// Opens the file
	CHAR szFile[MAX_PATH];
	wcstombs(szFile, wszFile, MAX_PATH);
	h = _lopen(szFile, OF_READ);
	if (h==HFILE_ERROR)
		return S_OK;

	DWORD dwFileSize, dwBytesRead;
	dwFileSize = _llseek(h, 0, FILE_END);
	_llseek(h, 0, FILE_BEGIN);
	LPTSTR pszHTML = new TCHAR[dwFileSize+1];
	dwBytesRead = _lread(h, (LPVOID) pszHTML, dwFileSize);
	_lclose(h);

	LPTSTR psz1=NULL, psz2=NULL;
	psz1 = StrStrI(pszHTML, (LPCTSTR)_T("<title>"));
	if (psz1 == NULL)
	{
		delete [] pszHTML;
		return S_OK;
	}

	psz1 += _tcslen(_T("<title>"));

	psz2 = StrStrI(pszHTML, (LPCTSTR)_T("</title>"));
	if (psz2 == NULL)
	{
		delete [] pszHTML;
		return S_OK;
	}

	// Completes the string 
	_tcsncpy(p, psz1, psz2-psz1);
	delete [] pszHTML;
	return S_OK;
}

