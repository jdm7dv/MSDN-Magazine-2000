///////////////////////////////////////////////////////////////////////
//
//  Envelope.cpp - Copyright 1999, Tim Ewald / DevelopMentor
//  

// Envelope.cpp : Implementation of CEnvelope
#include "stdafx.h"
#include "Stationery.h"
#include "Envelope.h"

/////////////////////////////////////////////////////////////////////////////
// CEnvelope

STDMETHODIMP CEnvelope::put_Letter(
		/* [in] */ IUnknown *pUnk)
{
	m_pMshl = pUnk;
	return S_OK;
}

STDMETHODIMP CEnvelope::GetUnmarshalClass( 
    /* [in] */ REFIID riid,
    /* [unique][in] */ void __RPC_FAR *pv,
    /* [in] */ DWORD dwDestContext,
    /* [unique][in] */ void __RPC_FAR *pvDestContext,
    /* [in] */ DWORD mshlflags,
    /* [out] */ CLSID __RPC_FAR *pCid)
{
	*pCid = CLSID_Envelope;
	return S_OK;
}

STDMETHODIMP CEnvelope::GetMarshalSizeMax( 
    /* [in] */ REFIID riid,
    /* [unique][in] */ void __RPC_FAR *pv,
    /* [in] */ DWORD dwDestContext,
    /* [unique][in] */ void __RPC_FAR *pvDestContext,
    /* [in] */ DWORD mshlflags,
    /* [out] */ DWORD __RPC_FAR *pSize)
{
	return m_pMshl->GetMarshalSizeMax(riid, pv, dwDestContext, pvDestContext, mshlflags, pSize);
}

STDMETHODIMP CEnvelope::MarshalInterface( 
    /* [unique][in] */ IStream __RPC_FAR *pStm,
    /* [in] */ REFIID riid,
    /* [unique][in] */ void __RPC_FAR *pv,
    /* [in] */ DWORD dwDestContext,
    /* [unique][in] */ void __RPC_FAR *pvDestContext,
    /* [in] */ DWORD mshlflags)
{
	return m_pMshl->MarshalInterface(pStm, riid, pv, dwDestContext, pvDestContext, mshlflags);
}

STDMETHODIMP CEnvelope::UnmarshalInterface( 
    /* [unique][in] */ IStream __RPC_FAR *pStm,
    /* [in] */ REFIID riid,
    /* [out] */ void __RPC_FAR *__RPC_FAR *ppv)
{
	return CoUnmarshalInterface(pStm, riid, ppv);
}

STDMETHODIMP CEnvelope::ReleaseMarshalData( 
    /* [unique][in] */ IStream __RPC_FAR *pStm)
{
	return CoReleaseMarshalData(pStm);
}

STDMETHODIMP CEnvelope::DisconnectObject( 
    /* [in] */ DWORD dwReserved)
{
	return S_OK;
}