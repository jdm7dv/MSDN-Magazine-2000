// ExeTip.cpp : Implementation of CExeTip
#include "stdafx.h"
#include "ExeExt.h"
#include "ExeTip.h"

#include "DepList.h"
#pragma comment(lib, "deplist.lib")
#include <ShlWApi.h>
#pragma comment(lib, "ShlWApi.lib")





/////////////////////////////////////////////////////////////////////////////
// CExeTip

HRESULT CExeTip::GetInfoTip(DWORD dwFlags, LPWSTR* ppwszTip)
{
	USES_CONVERSION;

	// dwFlags is currently unused.

	if (!CanLoad()) {
		*ppwszTip = NULL;
		return S_FALSE;
	}


	// Opens the EXE file and returns referenced DLLs
	TCHAR szInfo[1024];
	GetDllInfo(szInfo);	
	*ppwszTip = (WCHAR*) m_pAlloc->Alloc(lstrlen(szInfo)*sizeof(WCHAR));
	if (*ppwszTip)
		wcscpy(*ppwszTip, (WCHAR*)T2OLE(szInfo));

	return S_OK;
}




/////////////////////////////////////////////////////////////////////////////
// Private Members

HRESULT CExeTip::GetDllInfo(LPTSTR szInfo)
{
	// Get the DLL info
	int nBytes = GetImportTableSize(m_szFile);
	LPTSTR szDLLs = new TCHAR[nBytes+1];
	int iNumOfLibs = GetImportTable(m_szFile, szDLLs);
	if (iNumOfLibs ==0) 
	{
		lstrcpy(szInfo, _T("No DLLs needed."));
		return S_OK;
	}



    // Builds the HTML string
	int i=0;
	lstrcpy(szInfo, _T("Needs:\n"));
	LPTSTR p = (LPTSTR) szDLLs;
	while (i < iNumOfLibs)
	{
		lstrcat(szInfo, _T("\t"));
		lstrcat(szInfo, p);
		if (i+1 < iNumOfLibs)
			lstrcat(szInfo, _T("\n"));
		p += lstrlen(p)+1;
		i++;
	}
	
	return S_OK;
}



BOOL CExeTip::CanLoad()
{
	DWORD dwType = REG_DWORD;
	DWORD dwSize=sizeof(DWORD), dwVal=0;

	DWORD dwRC = SHGetValue(HKEY_CURRENT_USER,
				_T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced"),
				_T("ExeTip"),
				&dwType,
				(LPVOID) &dwVal,
				&dwSize); 
	return dwVal;
}
