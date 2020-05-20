///////////////////////////////////////////////////////////////////////
//
//  Random.cpp - Copyright 1999, Tim Ewald / DevelopMentor
//  

// Random.cpp : Implementation of CRandom
#include "stdafx.h"
#include "LoadBalancingAlgorithms.h"
#include "Random.h"

#include "time.h"

/////////////////////////////////////////////////////////////////////////////
// CRandom

CRandom::CRandom() : m_nCount(0), m_rgwsz(0)
{
    srand((unsigned)time(0));
}

CRandom::~CRandom()
{
    if (m_rgwsz)
    {
        for (long i = 0; i < m_nCount; i++)
            delete [] m_rgwsz[i];
        delete [] m_rgwsz;
    }
}

STDMETHODIMP CRandom::CreateInstance(REFCLSID rclsid, REFIID riid, void **ppv)
{
    if (!m_rgwsz) return E_UNEXPECTED;

    COSERVERINFO csi = {0};

    csi.pwszName = m_rgwsz[(long)(((float)rand()/RAND_MAX) * m_nCount)]; 

    MULTI_QI mqi = { &riid, 0, 0 };
    
    HRESULT hr = CoCreateInstanceEx(rclsid, 0, CLSCTX_REMOTE_SERVER, &csi, 1, &mqi);
    if (FAILED(hr)) return hr;

    *ppv = mqi.pItf; // pass on ownership, no need to AddRef and Release
    
    return hr;
}

STDMETHODIMP CRandom::SetHosts(long nCount, LPOLESTR *prgwszHosts)
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
