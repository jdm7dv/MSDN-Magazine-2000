// CallNotifyObject.cpp : Implementation of CCallNotifyObject
#include "stdafx.h"
#include "CallObjectServer.h"
#include "CallNotifyObject.h"

/////////////////////////////////////////////////////////////////////////////
// CCallNotifyObject

STDMETHODIMP CCallNotifyObject::Initialize(unsigned int hWnd,
	unsigned int nMessageID, ICallFactory* pCallFactory, REFIID riid1,
	REFIID riid2, void **ppvObj)
{
	//
	// Store the window handle and message ID used for notifications.
	//
	m_hWnd = (HWND) hWnd;
	m_nMessageID = nMessageID;

	//
	// Create (and aggregate) a call object.
	//
	HRESULT hr = pCallFactory->CreateCall (riid1, GetControllingUnknown (),
		IID_IUnknown, &m_spUnkInner);

	if (FAILED (hr))
		return hr;

	//
	// Cache a pointer to the aggregated object's ISynchronize interface.
	//
	hr = m_spUnkInner->QueryInterface (IID_ISynchronize,
		(void**) &m_spSyncInner);

	if (FAILED (hr)) {
		m_spUnkInner.Release ();
		return hr;
	}

	//
	// Query the aggregated object for the interface requested by the caller.
	//
	hr = m_spUnkInner->QueryInterface (riid2, ppvObj);

	if (FAILED (hr)) {
		m_spSyncInner.Release ();
		m_spUnkInner.Release ();
	}
	return hr;
}

STDMETHODIMP CCallNotifyObject::Wait (ULONG dwFlags, ULONG dwMilliseconds)
{
	//
	// Forward the call to the aggregated call object.
	//
	ATLASSERT (m_spSyncInner.p != NULL);	
	return m_spSyncInner->Wait (dwFlags, dwMilliseconds);
}

STDMETHODIMP CCallNotifyObject::Signal ()
{
	//
	// Forward the call to the aggregated call object.
	//
	ATLASSERT (m_spSyncInner.p != NULL);	
	m_spSyncInner->Signal ();	

	//
	// Notify the caller that an asynchronous call has returned.
	//
	ATLASSERT (m_hWnd != NULL && m_nMessageID != 0);
	PostMessage (m_hWnd, m_nMessageID, 0, 0);
	return S_OK;
}

STDMETHODIMP CCallNotifyObject::Reset ()
{
	//
	// Forward the call to the aggregated call object.
	//
	ATLASSERT (m_spSyncInner.p != NULL);	
	return m_spSyncInner->Reset ();
}
