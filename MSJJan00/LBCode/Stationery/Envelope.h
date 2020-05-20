///////////////////////////////////////////////////////////////////////
//
//  Envelope.h - Copyright 1999, Tim Ewald / DevelopMentor
//  

// Envelope.h : Declaration of the CEnvelope

#ifndef __ENVELOPE_H_
#define __ENVELOPE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEnvelope
class ATL_NO_VTABLE CEnvelope : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CEnvelope, &CLSID_Envelope>,
	public IEnvelope,
	public IMarshal
{
	CComQIPtr<IMarshal> m_pMshl;

public:

	CEnvelope() {}
	virtual ~CEnvelope() {}


DECLARE_REGISTRY_RESOURCEID(IDR_ENVELOPE)
DECLARE_NOT_AGGREGATABLE(CEnvelope)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEnvelope)
	COM_INTERFACE_ENTRY(IEnvelope)
	COM_INTERFACE_ENTRY(IMarshal)
END_COM_MAP()

public:
// IEnvelope
	STDMETHODIMP put_Letter(
		/* [in] */ IUnknown *pUnk);

// IMarshal
	STDMETHODIMP GetUnmarshalClass( 
        /* [in] */ REFIID riid,
        /* [unique][in] */ void __RPC_FAR *pv,
        /* [in] */ DWORD dwDestContext,
        /* [unique][in] */ void __RPC_FAR *pvDestContext,
        /* [in] */ DWORD mshlflags,
        /* [out] */ CLSID __RPC_FAR *pCid);
    
    STDMETHODIMP GetMarshalSizeMax( 
        /* [in] */ REFIID riid,
        /* [unique][in] */ void __RPC_FAR *pv,
        /* [in] */ DWORD dwDestContext,
        /* [unique][in] */ void __RPC_FAR *pvDestContext,
        /* [in] */ DWORD mshlflags,
        /* [out] */ DWORD __RPC_FAR *pSize);
    
    STDMETHODIMP MarshalInterface( 
        /* [unique][in] */ IStream __RPC_FAR *pStm,
        /* [in] */ REFIID riid,
        /* [unique][in] */ void __RPC_FAR *pv,
        /* [in] */ DWORD dwDestContext,
        /* [unique][in] */ void __RPC_FAR *pvDestContext,
        /* [in] */ DWORD mshlflags);
    
    STDMETHODIMP UnmarshalInterface( 
        /* [unique][in] */ IStream __RPC_FAR *pStm,
        /* [in] */ REFIID riid,
        /* [out] */ void __RPC_FAR *__RPC_FAR *ppv);
    
    STDMETHODIMP ReleaseMarshalData( 
        /* [unique][in] */ IStream __RPC_FAR *pStm);
    
    STDMETHODIMP DisconnectObject( 
        /* [in] */ DWORD dwReserved);
};

#endif //__ENVELOPE_H_
