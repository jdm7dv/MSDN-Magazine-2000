///////////////////////////////////////////////////////////////////////
//
//  Hook.h - Copyright 1999, Tim Ewald / DevelopMentor
//  

#ifndef _HOOK_H
#define _HOOK_H

#include <windows.h>

// {FCA953B0-E3D0-11d2-8117-00E09801FDBE}
DEFINE_GUID(EXTENTID_MethodTime, 
0xfca953b0, 0xe3d0, 0x11d2, 0x81, 0x17, 0x0, 0xe0, 0x98, 0x1, 0xfd, 0xbe);

class Hook : public IChannelHook
{
public:
	STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

    STDMETHODIMP_(void) ClientGetSize(REFGUID uExtent, REFIID riid, ULONG *pDataSize);
    STDMETHODIMP_(void) ClientFillBuffer(REFGUID uExtent, REFIID riid, ULONG *pDataSize, void *pDataBuffer);
    STDMETHODIMP_(void) ClientNotify(REFGUID uExtent, REFIID riid, ULONG cbDataSize, void *pDataBuffer, DWORD lDataRep, HRESULT hrFault);

    STDMETHODIMP_(void) ServerNotify(REFGUID uExtent, REFIID riid, ULONG cbDataSize, void *pDataBuffer, DWORD lDataRep);
    STDMETHODIMP_(void) ServerGetSize(REFGUID uExtent, REFIID riid, HRESULT hrFault, ULONG *pDataSize); 
    STDMETHODIMP_(void) ServerFillBuffer(REFGUID uExtent, REFIID riid, ULONG *pDataSize, void *pDataBuffer, HRESULT hrFault);
};

#endif
