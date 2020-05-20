// CleanSomething.h : Declaration of the CCleanSomething

#ifndef __CLEANSOMETHING_H_
#define __CLEANSOMETHING_H_

#include "resource.h"					// main symbols
#include "IEmptyVolumeCache2Impl.h"		// IEmptyVolumeCache2

/////////////////////////////////////////////////////////////////////////////
// CCleanSomething
class ATL_NO_VTABLE CCleanSomething : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCleanSomething, &CLSID_CleanSomething>,
	public IEmptyVolumeCache2Impl,
	public IDispatchImpl<ICleanSomething, &IID_ICleanSomething, &LIBID_DCHDEMOLib>
{
public:
	CCleanSomething()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CLEANSOMETHING)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCleanSomething)
	COM_INTERFACE_ENTRY(IEmptyVolumeCache)
	COM_INTERFACE_ENTRY(IEmptyVolumeCache2)
	COM_INTERFACE_ENTRY(ICleanSomething)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEmptyVolumeCache2
public:
	STDMETHOD(InitializeEx)(HKEY hkRegKey,
				  LPCWSTR pcwszVolume, 
			      LPCWSTR pcwszKeyName, 
	              LPWSTR *ppwszDisplayName, 
	              LPWSTR *ppwszDescription, 
				  LPWSTR *ppwszBtnText, 
		          DWORD *pdwFlags);

	STDMETHOD(GetSpaceUsed)(DWORDLONG *pdwSpaceUsed, 
		IEmptyVolumeCacheCallBack *picb);
 
};

#endif //__CLEANSOMETHING_H_
