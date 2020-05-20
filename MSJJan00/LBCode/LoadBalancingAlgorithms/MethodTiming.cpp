///////////////////////////////////////////////////////////////////////
//
//  MethodTiming.cpp - Copyright 1999, Tim Ewald / DevelopMentor
//  

// MethodTiming.cpp : Implementation of CMethodTiming
#include "stdafx.h"
#include "LoadBalancingAlgorithms.h"
#include "MethodTiming.h"

#include "..\\MethodTimeHook\\MethodTimeHook.h"
#include "..\\MethodTimeHook\\MethodTimeHook_i.c"

#include <limits.h>

/////////////////////////////////////////////////////////////////////////////
// CMethodTiming
CMethodTiming::CMethodTiming() : m_hStopping(0), m_hThread(0), m_phti(0), m_rghti(0), m_nCount(0)
{
}

CMethodTiming::~CMethodTiming()
{
    SetEvent(m_hStopping);        
    WaitForSingleObject(m_hThread, INFINITE);
    //MessageBox(0, "Thread stopped", "MethodTiming", MB_SETFOREGROUND | MB_SERVICE_NOTIFICATION);
    CloseHandle(m_hStopping);
    //CloseHandle(m_hThread);

    if (m_rghti)
    {
        for (long i = 0; i < m_nCount; i++)
        {
            delete [] m_rghti[i].wsz;
            m_rghti[i].pl->Release();
        }
        delete [] m_rghti;
    }
}


STDMETHODIMP CMethodTiming::CreateInstance(REFCLSID rclsid, REFIID riid, void **ppv)
{
    COSERVERINFO csi = {0};

    csi.pwszName = m_phti->wsz;

    MULTI_QI mqi = { &riid, 0, 0 };

    HRESULT hr = CoCreateInstanceEx(rclsid, 0, CLSCTX_REMOTE_SERVER, &csi, 1, &mqi);
    if (FAILED(hr)) return hr;

    *ppv = mqi.pItf; // pass on ownership, no need to AddRef and Release
    
    return hr;
}

STDMETHODIMP CMethodTiming::SetHosts(long nCount, LPOLESTR *prgwszHosts)
{
	int i;
    m_rghti = new HostTimeInfo[nCount];
    if (!m_rghti) return E_OUTOFMEMORY;

    memset(m_rghti, 0, sizeof(CMethodTiming::HostTimeInfo) * nCount);

    for (long i = 0; i < nCount; i++)
    {   
        m_rghti[i].wsz = new OLECHAR[wcslen(prgwszHosts[i]) + 1];
        if (!m_rghti[i].wsz) break;
        wcscpy(m_rghti[i].wsz, prgwszHosts[i]);

        COSERVERINFO csi = { 0 };

        csi.pwszName = m_rghti[i].wsz;

        MULTI_QI mqi = { &IID_ILoader, 0, 0 };

        HRESULT hr = CoCreateInstanceEx(CLSID_Loader, 0, CLSCTX_REMOTE_SERVER, &csi, 1, &mqi);
        if (FAILED(hr)) break;

        (m_rghti[i].pl = reinterpret_cast<ILoader*>(mqi.pItf))->AddRef();
    }

    if (i != nCount)
    {
        for (; i >= 0; i--)
        {
            if(m_rghti[i].wsz) delete [] m_rghti[i].wsz;
            if(m_rghti[i].pl) m_rghti[i].pl->Release();
        }
        delete [] m_rghti;
        return E_OUTOFMEMORY;
    }

    m_nCount = nCount;

    m_hStopping = CreateEvent(0, TRUE, FALSE, 0);
    m_hThread = (HANDLE) _beginthread(&MethodTimeMonitor, 0, (void*)this);

    return S_OK;
}

void _cdecl MethodTimeMonitor(void *pv)
{
    CMethodTiming *pmt = reinterpret_cast<CMethodTiming*>(pv);
    CMethodTiming::HostTimeInfo *prghti = pmt->m_rghti;

    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hr)) return;

    //MessageBox(0, "About to loop", "MethodTiming Thread", MB_SETFOREGROUND | MB_SERVICE_NOTIFICATION);

    while (WaitForSingleObject(pmt->m_hStopping, 500) == WAIT_TIMEOUT)
    {
        long nLowestIndex = 0;
        long nLowestValue = LONG_MAX;

        pmt->Lock();

        for (long i = 0; i < pmt->m_nCount; i++)
        {
            //hr = prghti[i].pl->GetAverageMethodTime(&prghti[i].nAvgMethodTime);

            long nNewAvg;
            hr = prghti[i].pl->GetAverageMethodTime(&nNewAvg);

            long nDelta = nNewAvg - prghti[i].nAvgMethodTime;

            prghti[i].nAvgMethodTime += (nDelta/4);

#ifdef _DEBUG
            char buf[1024];
            wsprintf(buf, "%S, %d, %d\n", prghti[i].wsz, nNewAvg, prghti[i].nAvgMethodTime);
            OutputDebugString(buf);
#endif

            if (prghti[i].nAvgMethodTime < nLowestValue)
            {
                nLowestValue = prghti[i].nAvgMethodTime;
                nLowestIndex = i;
            }
        }

        pmt->m_phti = &prghti[nLowestIndex];
        
        pmt->Unlock();
    }

    //MessageBox(0, "Done looping", "MethodTiming Thread", MB_SETFOREGROUND | MB_SERVICE_NOTIFICATION);

    CoUninitialize();
}
