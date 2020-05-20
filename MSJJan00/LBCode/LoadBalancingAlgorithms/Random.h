///////////////////////////////////////////////////////////////////////
//
//  Random.h - Copyright 1999, Tim Ewald / DevelopMentor
//  

// Random.h : Declaration of the CRandom

#ifndef __RANDOM_H_
#define __RANDOM_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRandom
class ATL_NO_VTABLE CRandom : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CRandom, &CLSID_Random>,
	public ILoadBalancingAlgorithm,
    public IHosts
{
    long m_nCount;
    LPOLESTR *m_rgwsz;
public:
	CRandom();
    virtual ~CRandom();

DECLARE_REGISTRY_RESOURCEID(IDR_RANDOM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRandom)
	COM_INTERFACE_ENTRY(ILoadBalancingAlgorithm)
	COM_INTERFACE_ENTRY(IHosts)
END_COM_MAP()

// IRandom
public:
    STDMETHODIMP CreateInstance(REFCLSID rclsid, REFIID riid, void **ppv);
    STDMETHODIMP SetHosts(long nCount, LPOLESTR *prgwszHosts);
};

#endif //__RANDOM_H_
