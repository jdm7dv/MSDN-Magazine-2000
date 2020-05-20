///////////////////////////////////////////////////////////////////////
//
//  TestClient.cpp - Copyright 1999, Tim Ewald / DevelopMentor
//  

// TestClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "atlbase.h"
#include "atlimpl.cpp"

#include "..\\TestServer\\TestServer.h"
#include "..\\TestServer\\TestServer_i.c"

#include <stdio.h>

int main(int argc, char* argv[])
{
    int nIterations = 1;

    if (argc == 2)
        nIterations = atoi(argv[1]);

    HRESULT hr;
    hr = CoInitialize(0);
    if (FAILED(hr)) return hr;

    for (; nIterations > 0; nIterations--)
    {
        CComPtr<ITest> pt;
        hr = CoCreateInstance(CLSID_Test, 0, CLSCTX_LOCAL_SERVER, IID_ITest, (void**)&pt);
        if (FAILED(hr)) return hr;

        for (int i = 0; i < 3; i++)
        {
            CComBSTR b;
            hr = pt->GetHostName(&b);
            printf("%S\n", b.m_str);
        }
    }

    CoUninitialize();
	return 0;
}
