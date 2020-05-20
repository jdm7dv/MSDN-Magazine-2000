///////////////////////////////////////////////////////////////////////
//
//  RoundRobin.h - Copyright 1999, Tim Ewald / DevelopMentor
//  

// RoundRobin.h : Declaration of the CRoundRobin

#ifndef __ROUNDROBIN_H_
#define __ROUNDROBIN_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRoundRobin
class ATL_NO_VTABLE CRoundRobin : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CRoundRobin, &CLSID_RoundRobin>,
	public ILoadBalancingAlgorithm,
    public IHosts
{
    long m_nCurrent;
    long m_nCount;
    LPOLESTR *m_rgwsz;
public:
    CRoundRobin();
    virtual ~CRoundRobin();

DECLARE_REGISTRY_RESOURCEID(IDR_ROUNDROBIN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRoundRobin)
	COM_INTERFACE_ENTRY(ILoadBalancingAlgorithm)
    COM_INTERFACE_ENTRY(IHosts)
END_COM_MAP()

// IRoundRobin
public:
	STDMETHODIMP CreateInstance(REFCLSID rclsid, REFIID riid, void **ppv);
    STDMETHODIMP SetHosts(long nCount, LPOLESTR *prgwszHosts);
};

#endif //__ROUNDROBIN_H_
