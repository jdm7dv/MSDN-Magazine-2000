// CallNotifyObject.h : Declaration of the CCallNotifyObject

#ifndef __CALLNOTIFYOBJECT_H_
#define __CALLNOTIFYOBJECT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCallNotifyObject

class ATL_NO_VTABLE CCallNotifyObject : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCallNotifyObject, &CLSID_CallNotifyObject>,
	public ICallObjectInit,
	public ISynchronize
{
public:
	CCallNotifyObject()
	{
		m_hWnd = NULL;
		m_nMessageID = 0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CALLNOTIFYOBJECT)
DECLARE_PROTECT_FINAL_CONSTRUCT()
DECLARE_GET_CONTROLLING_UNKNOWN ()

BEGIN_COM_MAP(CCallNotifyObject)
	COM_INTERFACE_ENTRY(ICallObjectInit)
	COM_INTERFACE_ENTRY(ISynchronize)
	COM_INTERFACE_ENTRY_AGGREGATE_BLIND (m_spUnkInner.p)
END_COM_MAP()

// ICallObjectInit
public:
	STDMETHOD(Initialize)(/*[in]*/ unsigned int hWnd,
		/*[in]*/ unsigned int nMessageID, /*[in]*/ ICallFactory* pCallFactory,
		/*[in]*/ REFIID riid1, /*[in]*/ REFIID riid2, /*[out]*/ void** ppvObj);

// ISynchronize
public:
	STDMETHOD(Wait)(ULONG dwFlags, ULONG dwMilliseconds);
	STDMETHOD(Signal)();
	STDMETHOD(Reset)();

protected:
	HWND m_hWnd;
	unsigned int m_nMessageID;
	CComPtr<ISynchronize> m_spSyncInner;

public:
	CComPtr<IUnknown> m_spUnkInner;
};

#endif //__CALLNOTIFYOBJECT_H_
