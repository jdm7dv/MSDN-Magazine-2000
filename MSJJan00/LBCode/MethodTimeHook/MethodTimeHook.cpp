///////////////////////////////////////////////////////////////////////
//
//  MethodTimeHook.cpp - Copyright 1999, Tim Ewald / DevelopMentor
//  

// MethodTimeHook.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f MethodTimeHookps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "MethodTimeHook.h"

#include "MethodTimeHook_i.c"
#include "Loader.h"

#include "Hook.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Loader, CLoader)
END_OBJECT_MAP()

DWORD g_dwTLSIndex;
HANDLE g_hheap;
HINSTANCE g_hInstance;

static const char *szMutexName = "MethodTime";
HANDLE g_hMutex = 0;

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    static Hook s_theHook;
    switch(dwReason)
    {
        case DLL_PROCESS_ATTACH :
        {
            _Module.Init(ObjectMap, hInstance, &LIBID_METHODTIMEHOOKLib);

    // create mutex
            g_hMutex = CreateMutex(0, FALSE, szMutexName);
            if (!g_hMutex)
            {
                MessageBox(0, "Couldn't create mutex", "MethodTimeHook::DllMain", MB_SETFOREGROUND);
                return FALSE;
            }

    // acquire a TLS slot
            if ((g_dwTLSIndex = TlsAlloc()) == 0xFFFFFFFF)
            {
                MessageBox(0, "Couldn't allocate TLS slot", "MethodTimeHook::DllMain", MB_SETFOREGROUND);
                return FALSE;
            }
    // register the process-wide channel hook
            HRESULT hr = CoRegisterChannelHook(EXTENTID_MethodTime, &s_theHook);
            if (FAILED(hr))
            {
                MessageBox(0, "Couldn't register channel hook", "MethodTimeHook::DllMain", MB_SETFOREGROUND);
                return FALSE;
            }
    // initialize various globals including getting the current IP address
            g_hInstance = hInstance;
            g_hheap = HeapCreate(0, 1, 0);
    
            break;
        }
        case DLL_THREAD_DETACH :
        {
    // clean up any thread/call context acquired for this thread
            void *pv = TlsGetValue(g_dwTLSIndex);
            if (pv)
            {
                HeapFree(g_hheap, 0, pv);
            }

            break;
        }
        case DLL_PROCESS_DETACH :
        {
    // release TLS slot and deallocate all memory
            if (g_dwTLSIndex != 0xFFFFFFFF)
                TlsFree(g_dwTLSIndex);
            HeapDestroy(g_hheap);

            CloseHandle(g_hMutex);

            _Module.Term();

            break;
        }
    }
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return S_FALSE; // (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    HRESULT hr = _Module.UpdateRegistryFromResource(IDR_METHODTIMEHOOK, TRUE);
    if (FAILED(hr)) return hr;
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    HRESULT hr = _Module.UpdateRegistryFromResource(IDR_METHODTIMEHOOK, FALSE);
    if (FAILED(hr)) return hr;
    return _Module.UnregisterServer(TRUE);
}


