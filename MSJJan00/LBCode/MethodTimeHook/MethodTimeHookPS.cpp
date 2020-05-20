///////////////////////////////////////////////////////////////////////
//
//  MethodTimeHookPS.cpp - Copyright 1999, Tim Ewald / DevelopMentor
//  

#include <windows.h>
#include <initguid.h>

DEFINE_GUID(CLSID_Loader, 
0x233108A3, 0xE3CD, 0x11D2, 0x81, 0x17, 0x0, 0xe0, 0x98, 0x1, 0xfd, 0xbe);

extern "C" BOOL WINAPI OldDllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    static IUnknown *pUnk = 0;
    switch(dwReason)
    {
        case DLL_PROCESS_ATTACH :
        {
            HRESULT hr = CoCreateInstance(CLSID_Loader, 0, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pUnk);
            if (SUCCEEDED(hr)) pUnk->Release();
            break;
        }
        case DLL_PROCESS_DETACH :
        {
            break;
        }
    }
    return OldDllMain(hInstance, dwReason, lpReserved); //TRUE;    // ok
}
