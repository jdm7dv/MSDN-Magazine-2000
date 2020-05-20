// BmpTip.cpp : Implementation of CBmpTip
#include "stdafx.h"
#include "BmpExt.h"
#include "BmpTip.h"

/////////////////////////////////////////////////////////////////////////////
// CBmpTip

HRESULT CBmpTip::GetInfoTip(DWORD dwFlags, LPWSTR* ppwszTip)
{
	USES_CONVERSION;

	// dwFlags is currently unused.

	// At this point the shell is requiring the tip
	// for a certain BMP file whose name is now 
	// stored in the m_szFile member of the 
	// IPersistFileImpl class. 

	// Opens the BMP file and returns size and colors
	CComBSTR bstrInfo;
	GetBitmapInfo((CComBSTR *)&bstrInfo);
    
	*ppwszTip = (WCHAR*) m_pAlloc->Alloc( 
		(bstrInfo.Length() +1) * sizeof(WCHAR));
	if (*ppwszTip)
		wcscpy(*ppwszTip, (WCHAR*)(BSTR)bstrInfo);
	
	return S_OK;
}




/////////////////////////////////////////////////////////////////////////////
// Private Members

HRESULT CBmpTip::GetBitmapInfo(CComBSTR *p)
{
	p->Empty();

	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

	// Reads the file header
	HANDLE hFile = CreateFile(m_szFile, GENERIC_READ, FILE_SHARE_READ, NULL, 
		OPEN_EXISTING, 0, NULL);
	if (hFile == NULL)
	{
		p->LoadString(IDS_TEXT_UNABLETOREAD);
		return S_OK;
	}	
	DWORD dwRead=0;
	ReadFile(hFile, (LPBITMAPFILEHEADER)&bf, sizeof(BITMAPFILEHEADER), 
		&dwRead, NULL);
	ReadFile(hFile, (LPBITMAPINFOHEADER)&bi, sizeof(BITMAPINFOHEADER), 
		&dwRead, NULL);
	CloseHandle(hFile);	

	// Format the string 
	TCHAR szTemp[100];
	wsprintf(szTemp, 
			_T("%d x %d pixel (%d bit)"),
			bi.biWidth, bi.biHeight, bi.biBitCount);  

	p->Append(szTemp); 
	return S_OK;
}

