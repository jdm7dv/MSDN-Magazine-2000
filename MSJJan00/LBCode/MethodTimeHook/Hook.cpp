///////////////////////////////////////////////////////////////////////
//
//  Hook.cpp - Copyright 1999, Tim Ewald / DevelopMentor
//  

#include "stdafx.h"
#include "hook.h"
#include <initguid.h>

#include <assert.h>

#include <time.h>

#pragma data_seg("Shared")

long g_nCount = 0;
long g_nTime = 0;

#pragma data_seg()

#pragma comment(linker, "/section:Shared,rws")

extern HANDLE g_hMutex;

// information about a particular call site
struct CALLINFO
{
    long nCount;
    time_t tStart;
};

extern DWORD g_dwTLSIndex;
extern HANDLE g_hheap;
extern HINSTANCE g_hInstance;

STDMETHODIMP 
Hook::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown)
        *ppv = static_cast<IUnknown*>(this);
    else if (riid == IID_IUnknown)
        *ppv = static_cast<IChannelHook*>(this);
    else
        return (*ppv = 0), E_NOINTERFACE;
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
}

STDMETHODIMP_(ULONG) 
Hook::AddRef(void)
{
    return 2;
}

STDMETHODIMP_(ULONG) 
Hook::Release(void)
{
    return 1;
}


// called in client prior to making a call
STDMETHODIMP_(void) 
Hook::ClientGetSize(REFGUID uExtent, REFIID riid, ULONG *pDataSize)
{
    assert(uExtent == EXTENTID_MethodTime);
    void *pv = TlsGetValue(g_dwTLSIndex);
    *pDataSize = pv ? sizeof(CALLINFO) : sizeof(BYTE);
    return;
}

// called in client prior to making a call
STDMETHODIMP_(void) 
Hook::ClientFillBuffer(REFGUID uExtent, REFIID riid, ULONG *pDataSize, void *pDataBuffer)
{
    assert(uExtent == EXTENTID_MethodTime);
    void *pv = TlsGetValue(g_dwTLSIndex);
    if (!pv)
    {
        // original client, pass signal
        *pDataSize = sizeof(BYTE);
        *((DWORD*)pDataBuffer) = 7;
    }
    else
    {
        // send current CALLINFO
        *((CALLINFO*)pDataBuffer) = *((CALLINFO*)pv);
        *pDataSize = sizeof(CALLINFO);
        HeapFree(g_hheap, 0, pv);
        TlsSetValue(g_dwTLSIndex, 0);
    }
    return;
}

// called in client just after a call completes
STDMETHODIMP_(void) 
Hook::ClientNotify(REFGUID uExtent, REFIID riid, ULONG cbDataSize, void *pDataBuffer, DWORD lDataRep, HRESULT hrFault)
{
    assert(uExtent == EXTENTID_MethodTime);
    assert(lDataRep == NDR_LOCAL_DATA_REPRESENTATION);

    if (cbDataSize == sizeof(CALLINFO))
    {
        // rehydrate existing CALLINFO
        CALLINFO *pci = reinterpret_cast<CALLINFO*>(HeapAlloc(g_hheap, 0, sizeof(CALLINFO)));
        assert(pci);

        *pci = *((CALLINFO*)pDataBuffer);

        TlsSetValue(g_dwTLSIndex, pci);
    }
    return;
}

// called in server just prior to invoking a call
STDMETHODIMP_(void) 
Hook::ServerNotify(REFGUID uExtent, REFIID riid, ULONG cbDataSize, void *pDataBuffer, DWORD lDataRep)
{
    assert(uExtent == EXTENTID_MethodTime);
    assert(lDataRep == NDR_LOCAL_DATA_REPRESENTATION);

    CALLINFO *pci = reinterpret_cast<CALLINFO*>(HeapAlloc(g_hheap, 0, sizeof(CALLINFO)));
    assert(pci);

    memset(pci, 0, sizeof(CALLINFO));

    if (cbDataSize != sizeof(CALLINFO))
    {
        // make a new CALLINFO
        pci->nCount = 0;
        time(&pci->tStart);
    }
    else
    {
        // rehydrate existing CALLINFO
        *pci = *((CALLINFO*)pDataBuffer);
        pci->nCount++;
    }
    TlsSetValue(g_dwTLSIndex, pci);
    return;
}

// called in server just after invoking a call
STDMETHODIMP_(void) 
Hook::ServerGetSize(REFGUID uExtent, REFIID riid, HRESULT hrFault, ULONG *pDataSize)
{
    assert(uExtent == EXTENTID_MethodTime);
    CALLINFO *pci = reinterpret_cast<CALLINFO*>(TlsGetValue(g_dwTLSIndex));
    //assert(pci);
    if (pci)
    {
        if (pci->nCount == 0)
        {
            *pDataSize = sizeof(BYTE);
        }
        else
        {
            *pDataSize = sizeof(CALLINFO);
        }
    }
    else
    {
        *pDataSize = sizeof(BYTE);
    }
    return;
}

// called in server just after invoking a call
STDMETHODIMP_(void) 
Hook::ServerFillBuffer(REFGUID uExtent, REFIID riid, ULONG *pDataSize, void *pDataBuffer, HRESULT hrFault)
{
    assert(uExtent == EXTENTID_MethodTime);

    CALLINFO *pci = reinterpret_cast<CALLINFO*>(TlsGetValue(g_dwTLSIndex));
    //assert(pci);
    if (pci)
    {
        if (pci->nCount == 0)
        {
            // returning to original client, pass signal
            *pDataSize = sizeof(BYTE);
            *((DWORD*)pDataBuffer) = 77;

            time_t tEnd;
            time(&tEnd);

            DWORD dw = WaitForSingleObject(g_hMutex, INFINITE);
            
            g_nCount++;
            g_nTime += (tEnd - pci->tStart);

            char buf[1024];
            wsprintf(buf, "Interval: %d, Count: %d, Time: %d\n", tEnd - pci->tStart, g_nCount, g_nTime);
            OutputDebugString(buf);

            ReleaseMutex(g_hMutex);
        }
        else
        {
            // return current CALLINFO
            pci->nCount--;
            *pDataSize = sizeof(CALLINFO);
            *((CALLINFO*)pDataBuffer) = *pci;
        }

        HeapFree(g_hheap, 0, pci);
        TlsSetValue(g_dwTLSIndex, 0);
    }
    else
    {
        *pDataSize = sizeof(BYTE);
        *((DWORD*)pDataBuffer) = 777;
    }


    return;
}

