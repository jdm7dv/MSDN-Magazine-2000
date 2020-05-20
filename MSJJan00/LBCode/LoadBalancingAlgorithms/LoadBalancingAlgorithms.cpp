///////////////////////////////////////////////////////////////////////
//
//  LoadBalancingAlgorithms.cpp - Copyright 1999, Tim Ewald / DevelopMentor
//  

// LoadBalancingAlgorithms.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f LoadBalancingAlgorithmsps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "LoadBalancingAlgorithms.h"
#include "LoadBalancingAlgorithms_i.c"

#include "Random.h"
#include "RoundRobin.h"
#include "MethodTiming.h"
#include "CPULoad.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Random, CRandom)
OBJECT_ENTRY(CLSID_RoundRobin, CRoundRobin)
OBJECT_ENTRY(CLSID_MethodTiming, CMethodTiming)
OBJECT_ENTRY(CLSID_CPULoad, CCPULoad)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_LOADBALANCINGALGORITHMSLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
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
    HRESULT hr = _Module.UpdateRegistryFromResource(IDR_LOADBALANCINGALGORITHMS, TRUE);
    if (FAILED(hr)) return hr;
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    HRESULT hr = _Module.UpdateRegistryFromResource(IDR_LOADBALANCINGALGORITHMS, FALSE);
    if (FAILED(hr)) return hr;
    return _Module.UnregisterServer(TRUE);
}


#include "RoundRobin.h"
#include "MethodTiming.h"
#include "CPULoad.h"
