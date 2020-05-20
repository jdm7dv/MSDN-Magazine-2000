///////////////////////////////////////////////////////////////////////
//
//  RoundRobin.cpp - Copyright 1999, Tim Ewald / DevelopMentor
//  

// RoundRobin.cpp : Implementation of CRoundRobin
#include "stdafx.h"
#include "LoadBalancingAlgorithms.h"
#include "RoundRobin.h"

/////////////////////////////////////////////////////////////////////////////
// CRoundRobin

CRoundRobin::CRoundRobin() : m_nCurrent(0), m_nCount(0), m_rgwsz(0)
{
}

CRoundRobin::~CRoundRobin()
{
    if (m_rgwsz)
    {
        for (long i = 0; i < m_nCount; i++)
            delete [] m_rgwsz[i];
        delete [] m_rgwsz;
    }
}

STDMETHODIMP CRoundRobin::CreateInstance(REFCLSID rclsid, REFIID riid, void **ppv)
{
    if (!m_rgwsz) return E_UNEXPECTED;

    long n;
    this->Lock();

    n = m_nCurrent;
    m_nCurrent++;
    if (m_nCurrent == m_nCount) m_nCurrent = 0;
    
    this->Unlock();

    COSERVERINFO csi = { 0 };
    csi.pwszName = m_rgwsz[n];

    MULTI_QI mqi = { &riid, 0, 0 };
    
    HRESULT hr = CoCreateInstanceEx(rclsid, 0, CLSCTX_REMOTE_SERVER, &csi, 1, &mqi);
    if (FAILED(hr)) return hr;

    *ppv = mqi.pItf; // pass on ownership, no need to AddRef and Release
    
    return hr;
}

STDMETHODIMP CRoundRobin::SetHosts(long nCount, LPOLESTR *prgwszHosts)
{
	int i;

    m_rgwsz = new LPOLESTR[nCount];
    if (!m_rgwsz) return E_OUTOFMEMORY;

    for (long i = 0; i < nCount; i++)
    {
        m_rgwsz[i] = new OLECHAR[wcslen(prgwszHosts[i]) + 1];
        if (!m_rgwsz[i]) break;
        wcscpy(m_rgwsz[i], prgwszHosts[i]);
    }

    if (i != nCount)
    {
        for (; i >= 0; i--)
            delete [] m_rgwsz[i];
        delete [] m_rgwsz;
        return E_OUTOFMEMORY;
    }

    m_nCount = nCount;

    return S_OK;
}