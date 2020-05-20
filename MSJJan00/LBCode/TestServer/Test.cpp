///////////////////////////////////////////////////////////////////////
//
//  Test.cpp - Copyright 1999, Tim Ewald / DevelopMentor
//  

// Test.cpp : Implementation of CTest
#include "stdafx.h"
#include "TestServer.h"
#include "Test.h"

#include <time.h>

/////////////////////////////////////////////////////////////////////////////
// CTest
const int dummy = (srand((unsigned)time(0)), 0);

STDMETHODIMP CTest::GetHostName(BSTR *pbstrHostName)
{
	// TODO: Add your implementation code here
    long ms = 0;
    float f = ((float)rand()/RAND_MAX);
    if (f < 0.5)
        ms = 5000;
    else if (f < 0.8)
        ms = 7500;
    else
        ms = 10000;
    Sleep(ms);
    
    *pbstrHostName = 0;
    DWORD dw = MAX_COMPUTERNAME_LENGTH + 1; 
    TCHAR buf[MAX_COMPUTERNAME_LENGTH + 1];
    if (GetComputerName(buf, &dw))
    {
        *pbstrHostName = CComBSTR(buf).Copy();
    }
    return *pbstrHostName ? S_OK : E_FAIL;
}
