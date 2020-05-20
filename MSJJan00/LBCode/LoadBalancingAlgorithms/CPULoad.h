///////////////////////////////////////////////////////////////////////
//
//  CPULoad.h - Copyright 1999, Tim Ewald / DevelopMentor
//  

// CPULoad.h : Declaration of the CCPULoad

#ifndef __CPULOAD_H_
#define __CPULOAD_H_

#include "resource.h"       // main symbols

#include <process.h>

void _cdecl CPULoadMonitor(void *pv);

#include <pdh.h>

/////////////////////////////////////////////////////////////////////////////
// CCPULoad
class ATL_NO_VTABLE CCPULoad : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCPULoad, &CLSID_CPULoad>,
	public ILoadBalancingAlgorithm,
    public IHosts
{
    typedef struct HostLoadInfo
    {
        long nCPULoad;
        HCOUNTER hCnt;
        OLECHAR *wsz;
    } HostLoadInfo;

    HQUERY m_hQuery;

    long m_nCount;
    HostLoadInfo *m_rghli;
    HostLoadInfo *m_phli;
    HANDLE m_hThread;
    HANDLE m_hStopping;

    friend void CPULoadMonitor(void*);

public:
    CCPULoad();
    virtual ~CCPULoad();

DECLARE_REGISTRY_RESOURCEID(IDR_CPULOAD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCPULoad)
	COM_INTERFACE_ENTRY(ILoadBalancingAlgorithm)
	COM_INTERFACE_ENTRY(IHosts)
END_COM_MAP()

// ICPULoad
public:
    STDMETHODIMP CreateInstance(REFCLSID rclsid, REFIID riid, void **ppv);
    STDMETHODIMP SetHosts(long nCount, LPOLESTR *prgwszHosts);
};

#endif //__CPULOAD_H_
