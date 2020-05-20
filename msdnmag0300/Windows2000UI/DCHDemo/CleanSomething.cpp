// CleanSomething.cpp : Implementation of CCleanSomething
#include "stdafx.h"
#include "DCHDemo.h"
#include "CleanSomething.h"

/////////////////////////////////////////////////////////////////////////////
// CCleanSomething

HRESULT CCleanSomething::InitializeEx(HKEY hkRegKey,
		LPCWSTR pcwszVolume, LPCWSTR pcwszKeyName, 
	    LPWSTR *ppwszDisplayName, LPWSTR *ppwszDescription, 
	    LPWSTR *ppwszBtnText, DWORD *pdwFlags)
{
	USES_CONVERSION;
	
	// DEBUG: Display the volume name
	MessageBoxW(0, pcwszVolume, _T("DCHDemo"), 0);

	// Prepare the UI
	*ppwszDisplayName = (LPWSTR)CoTaskMemAlloc(100);
	*ppwszDescription = (LPWSTR)CoTaskMemAlloc(100);
	*ppwszBtnText = (LPWSTR)CoTaskMemAlloc(100);
	lstrcpyW(*ppwszDisplayName, T2OLE(_T("DCHDemo")));
	lstrcpyW(*ppwszDescription, T2OLE(_T("Clean Something")));
	lstrcpyW(*ppwszBtnText, T2OLE(_T("Click Me!")));
	*pdwFlags |= EVCF_HASSETTINGS;
	return S_OK;
}


HRESULT CCleanSomething::GetSpaceUsed(DWORDLONG *pdwSpaceUsed, 
		IEmptyVolumeCacheCallBack *picb)
{
	*pdwSpaceUsed = 1024000;
	return S_OK;
}
 
