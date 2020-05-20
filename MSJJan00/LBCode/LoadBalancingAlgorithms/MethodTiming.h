///////////////////////////////////////////////////////////////////////
//
//  MethodTiming.h - Copyright 1999, Tim Ewald / DevelopMentor
//  

// MethodTiming.h : Declaration of the CMethodTiming

#ifndef __METHODTIMING_H_
#define __METHODTIMING_H_

#include "resource.h"       // main symbols

#include <process.h>

void _cdecl MethodTimeMonitor(void *pv);

interface ILoader;

/////////////////////////////////////////////////////////////////////////////
// CMethodTiming
class ATL_NO_VTABLE CMethodTiming : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMethodTiming, &CLSID_MethodTiming>,
	public ILoadBalancingAlgorithm,
    public IHosts
{
    typedef struct HostTimeInfo
    {
        long nAvgMethodTime;
        ILoader *pl;
        OLECHAR *wsz;
    } HostTimeInfo;

    long m_nCount;
    HostTimeInfo *m_rghti;
    HostTimeInfo *m_phti;
    HANDLE m_hThread;
    HANDLE m_hStopping;

    friend void MethodTimeMonitor(void*);

public:
    CMethodTiming();
    virtual ~CMethodTiming();

DECLARE_REGISTRY_RESOURCEID(IDR_METHODTIMING)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMethodTiming)
	COM_INTERFACE_ENTRY(ILoadBalancingAlgorithm)
	COM_INTERFACE_ENTRY(IHosts)
END_COM_MAP()

// IMethodTiming
public:
    STDMETHODIMP CreateInstance(REFCLSID rclsid, REFIID riid, void **ppv);
    STDMETHODIMP SetHosts(long nCount, LPOLESTR *prgwszHosts);
};

#endif //__METHODTIMING_H_
