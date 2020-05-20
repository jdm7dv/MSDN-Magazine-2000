///////////////////////////////////////////////////////////////////////
//
//  ClassObjectShim.h - Copyright 1999, Tim Ewald / DevelopMentor
//  

#include "stdafx.h"

#include "..\\Stationery\\Stationery.h"
#include "..\\Stationery\\Stationery_i.c"

#include "..\\LoadBalancingAlgorithms\\LoadBalancingAlgorithms.h"
#include "..\\LoadBalancingAlgorithms\\LoadBalancingAlgorithms_i.c"
#include "..\\include\\algorithm_i.c"

extern CServiceModule _Module;

class ClassObjectShim : public IClassFactory
{
    CLSID m_clsid;
public:
    ClassObjectShim(CLSID clsid) : m_clsid(clsid) {}
    virtual ~ClassObjectShim() {}

    STDMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        *ppv = 0;
        if (riid == IID_IClassFactory || riid == IID_IUnknown)
            reinterpret_cast<IUnknown*>((*ppv = static_cast<IClassFactory*>(this)))->AddRef();
        return *ppv ? S_OK : E_NOINTERFACE;
    }

    STDMETHODIMP_(ULONG) AddRef()
    {
        return 2;
    }

    STDMETHODIMP_(ULONG) Release()
    {
        return 1;
    }

    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
    {
        _Module.Lock();
        
        *ppv = 0;

		if (_Module.IsStopping()) return CO_E_SERVER_STOPPING;

        CComQIPtr<ILoadBalancingAlgorithm> plba(_Module.m_pUnkAlgorithm);
        HRESULT hr = plba->CreateInstance(m_clsid, riid, ppv);
        if (SUCCEEDED(hr))
        {
			CComPtr<IEnvelope> pe;
			hr = CoCreateInstance(CLSID_Envelope, 0, CLSCTX_INPROC_SERVER, IID_IEnvelope, (void**)&pe);
            if (SUCCEEDED(hr))
            {
        		hr = pe->put_Letter(reinterpret_cast<IUnknown*>(*ppv));
                (reinterpret_cast<IUnknown*>(*ppv))->Release();
			    *ppv = pe.Detach(); // transfer ownership of envelope reference
            }
        }

        _Module.Unlock();
        return hr;
    }

    STDMETHODIMP LockServer(BOOL bFlag)
    {
        if (bFlag)
            _Module.Lock();
        else
            _Module.Unlock();
        return S_OK;
    }
};
