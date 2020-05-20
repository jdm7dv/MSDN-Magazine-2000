// IEmptyVolumeCache2Impl.h
//
//////////////////////////////////////////////////////////////////////
#include <AtlCom.h>
#include <emptyvc.h>


class ATL_NO_VTABLE IEmptyVolumeCache2Impl : public IEmptyVolumeCache2 
{

public:
	// IUnknown
	//
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) = 0;
	_ATL_DEBUG_ADDREF_RELEASE_IMPL(IEmptyVolumeCache2Impl)


	// IEmptyVolumeCache 
	//

	// IEmptyVolumeCache::Initialize
	STDMETHOD(Initialize)(HKEY hkRegKey,
						  LPCWSTR pcwszVolume, 
		                  LPWSTR *ppwszDisplayName, 
		                  LPWSTR *ppwszDescription, 
		                  DWORD *pdwFlags)
	{
		MessageBox(0, _T("Initialize"), _T("DCHDemo"), 0);
		return S_OK;
	}

	// IEmptyVolumeCache::Deactivate (ERROR IN THE DOC!!!)
	STDMETHOD(Deactivate)(DWORD *pdwFlags)
	{ 
		MessageBox(0, _T("Deactivate"), _T("DCHDemo"), 0);
		return S_OK; 
	}

	// IEmptyVolumeCache::GetSpaceUsed
	STDMETHOD(GetSpaceUsed)(DWORDLONG *pdwSpaceUsed, 
							IEmptyVolumeCacheCallBack *picb)
	{ 
		MessageBox(0, _T("GetSpaceUsed"), _T("DCHDemo"), 0);
		return S_OK;  
	}

	// IEmptyVolumeCache::Purge
	STDMETHOD(Purge)(DWORDLONG dwSpaceToFree, 
					 IEmptyVolumeCacheCallBack *picb)
	{ 
		MessageBox(0, _T("Purge"), _T("DCHDemo"), 0);
		return S_OK; 
	}

	// IEmptyVolumeCache::ShowProperties
	STDMETHOD(ShowProperties)(HWND hwnd)
	{ 
		MessageBox(0, _T("ShowProperties"), _T("DCHDemo"), 0);
		return S_OK; 
	}


	// IEmptyVolumeCache2 
	//


	// IEmptyVolumeCache2::InitializeEx
	STDMETHOD(InitializeEx)(HKEY hkRegKey,
						  LPCWSTR pcwszVolume, 
					      LPCWSTR pcwszKeyName, 
		                  LPWSTR *ppwszDisplayName, 
		                  LPWSTR *ppwszDescription, 
						  LPWSTR *ppwszBtnText, 
		                  DWORD *pdwFlags)
	{
		MessageBox(0, _T("InitializeEx"), _T("DCHDemo"), 0);
		return S_OK;
	}
};