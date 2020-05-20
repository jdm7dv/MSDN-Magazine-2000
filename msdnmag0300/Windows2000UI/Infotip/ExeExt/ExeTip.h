// ExeTip.h : Declaration of the CExeTip

#ifndef __EXETIP_H_
#define __EXETIP_H_

#include "resource.h"       // main symbols
#include "comdef.h"				   // GUIDs	
#include "IPersistFileImpl.h"      // IPersistFile
#include "IQueryInfoImpl.h"        // IQueryInfo

/////////////////////////////////////////////////////////////////////////////
// CExeTip
class ATL_NO_VTABLE CExeTip : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExeTip, &CLSID_ExeTip>,
	public IQueryInfoImpl,
	public IPersistFileImpl,
	public IDispatchImpl<IExeTip, &IID_IExeTip, &LIBID_EXEEXTLib>
{
public:
	CExeTip()
	{
		HRESULT hr;
		hr = SHGetMalloc(&m_pAlloc);
		if (FAILED(hr))
			m_pAlloc = NULL;
	}
	~CExeTip()
	{
		m_pAlloc->Release();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EXETIP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CExeTip)
	COM_INTERFACE_ENTRY(IExeTip)
	COM_INTERFACE_ENTRY(IQueryInfo)
	COM_INTERFACE_ENTRY(IPersistFile)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IQueryInfo
public:
	STDMETHOD(GetInfoTip)(DWORD, LPWSTR*);

private:
	STDMETHOD(GetDllInfo)(LPTSTR);
	BOOL CanLoad(void);

private:
	LPMALLOC m_pAlloc;
};

#endif //__EXETIP_H_
