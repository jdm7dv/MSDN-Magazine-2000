// BmpTip.h : Declaration of the CBmpTip

#ifndef __BMPTIP_H_
#define __BMPTIP_H_

#include "resource.h"              // main symbols
#include "comdef.h"				   // GUIDs	
#include "IPersistFileImpl.h"      // IPersistFile
#include "IQueryInfoImpl.h"        // IQueryInfo

/////////////////////////////////////////////////////////////////////////////
// CBmpTip
class ATL_NO_VTABLE CBmpTip : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBmpTip, &CLSID_BmpTip>,
	public IQueryInfoImpl,
	public IPersistFileImpl,
	public IDispatchImpl<IBmpTip, &IID_IBmpTip, &LIBID_BMPEXTLib>
{
public:
	CBmpTip()
	{
		HRESULT hr;
		hr = SHGetMalloc(&m_pAlloc);
		if (FAILED(hr))
			m_pAlloc = NULL;
	}
	~CBmpTip()
	{
		m_pAlloc->Release();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BMPTIP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBmpTip)
	COM_INTERFACE_ENTRY(IBmpTip)
	COM_INTERFACE_ENTRY(IQueryInfo)
	COM_INTERFACE_ENTRY(IPersistFile)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IQueryInfo
public:
	STDMETHOD(GetInfoTip)(DWORD, LPWSTR*);

private:
	STDMETHOD(GetBitmapInfo)(CComBSTR*);

private:
	LPMALLOC m_pAlloc;
};

#endif //__BMPTIP_H_
