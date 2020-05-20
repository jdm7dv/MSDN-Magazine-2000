///////////////////////////////////////////////////////////////////////
//
//  CPULoad.cpp - Copyright 1999, Tim Ewald / DevelopMentor
//  

// CPULoad.cpp : Implementation of CCPULoad
#include "stdafx.h"
#include "LoadBalancingAlgorithms.h"
#include "CPULoad.h"

#include <pdh.h>
#include <limits.h>

/////////////////////////////////////////////////////////////////////////////
// CCPULoad

CCPULoad::CCPULoad() : m_hStopping(0), m_hThread(0), m_phli(0), m_rghli(0), m_nCount(0), m_hQuery(0)
{
}

CCPULoad::~CCPULoad()
{
    SetEvent(m_hStopping);        
    WaitForSingleObject(m_hThread, INFINITE);
    //MessageBox(0, "Thread stopped", "MethodTiming", MB_SETFOREGROUND | MB_SERVICE_NOTIFICATION);
    CloseHandle(m_hStopping);
    //CloseHandle(m_hThread);

    if (m_hQuery) PdhCloseQuery(m_hQuery);

    if (m_rghli)
    {
        for (long i = 0; i < m_nCount; i++)
            delete [] m_rghli[i].wsz;
        delete [] m_rghli;
    }
}


STDMETHODIMP CCPULoad::CreateInstance(REFCLSID rclsid, REFIID riid, void **ppv)
{
    COSERVERINFO csi = {0};

    csi.pwszName = m_phli->wsz;

    MULTI_QI mqi = { &riid, 0, 0 };

    HRESULT hr = CoCreateInstanceEx(rclsid, 0, CLSCTX_REMOTE_SERVER, &csi, 1, &mqi);
    if (FAILED(hr)) return hr;

    *ppv = mqi.pItf; // pass on ownership, no need to AddRef and Release
    
    return hr;
}

STDMETHODIMP CCPULoad::SetHosts(long nCount, LPOLESTR *prgwszHosts)
{
	int i;

    PDH_STATUS pdhStat;
    pdhStat = PdhOpenQuery (0, 0, &m_hQuery); 
    if (pdhStat != ERROR_SUCCESS) return E_FAIL;
    
    m_rghli = new HostLoadInfo[nCount];
    if (!m_rghli)
    {
        PdhCloseQuery(m_hQuery);
        return E_OUTOFMEMORY;
    }

    memset(m_rghli, 0, sizeof(CCPULoad::HostLoadInfo) * nCount);

    for (long i = 0; i < nCount; i++)
    {   
        m_rghli[i].wsz = new OLECHAR[wcslen(prgwszHosts[i]) + 1];
        if (!m_rghli[i].wsz) break;
        wcscpy(m_rghli[i].wsz, prgwszHosts[i]);

        OLECHAR wszCounter[1024];
        wcscpy(wszCounter, OLESTR("\\\\"));
        wcscat(wszCounter, m_rghli[i].wsz);
        //wcscat(wszCounter, OLESTR("\\Processor(0)\\% Processor Time"));
        wcscat(wszCounter, OLESTR("\\System\\% Total Processor Time"));
        pdhStat = PdhAddCounterW(m_hQuery, wszCounter, 0, &m_rghli[i].hCnt);
        if (pdhStat != ERROR_SUCCESS) break;
    }

    if (i != nCount)
    {
        for (; i >= 0; i--)
            if(m_rghli[i].wsz) delete [] m_rghli[i].wsz;
        delete [] m_rghli;
        PdhCloseQuery(m_hQuery);
        return E_OUTOFMEMORY;
    }

    pdhStat = PdhCollectQueryData(m_hQuery);

    m_nCount = nCount;

    m_hStopping = CreateEvent(0, TRUE, FALSE, 0);
    m_hThread = (HANDLE) _beginthread(&CPULoadMonitor, 0, (void*)this);

    return S_OK;
}

void _cdecl CPULoadMonitor(void *pv)
{
    CCPULoad *pcl = reinterpret_cast<CCPULoad*>(pv);
    CCPULoad::HostLoadInfo *prghli = pcl->m_rghli;

    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hr)) return;

    //MessageBox(0, "About to loop", "MethodTiming Thread", MB_SETFOREGROUND | MB_SERVICE_NOTIFICATION);

    while (WaitForSingleObject(pcl->m_hStopping, 500) == WAIT_TIMEOUT)
    {
        long nLowestIndex = 0;
        long nLowestValue = LONG_MAX;

        pcl->Lock();

        PDH_STATUS pdhStat = PdhCollectQueryData(pcl->m_hQuery);
        PDH_FMT_COUNTERVALUE fmtValue;
        for (long i = 0; i < pcl->m_nCount; i++)
        {
            pdhStat = PdhGetFormattedCounterValue(prghli[i].hCnt, PDH_FMT_LONG, 0, &fmtValue);

            prghli[i].nCPULoad = fmtValue.longValue;

            if (prghli[i].nCPULoad < nLowestValue)
            {
                nLowestValue = prghli[i].nCPULoad;
                nLowestIndex = i;
            }
#ifdef _DEBUG
            char sz[56];
            wsprintf(sz, "%S, %d\n", prghli[i].wsz, prghli[i].nCPULoad);
            OutputDebugString(sz);
#endif
        }

        pcl->m_phli = &prghli[nLowestIndex];
        
        pcl->Unlock();
    }

    //MessageBox(0, "Done looping", "MethodTiming Thread", MB_SETFOREGROUND | MB_SERVICE_NOTIFICATION);

    CoUninitialize();
}
