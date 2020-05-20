///////////////////////////////////////////////////////////////////////
//
//  Loader.cpp - Copyright 1999, Tim Ewald / DevelopMentor
//  

// Loader.cpp : Implementation of CLoader
#include "stdafx.h"
#include "MethodTimeHook.h"
#include "Loader.h"

#include <time.h>

extern long g_nCount;
extern long g_nTime;

extern HANDLE g_hMutex;

/////////////////////////////////////////////////////////////////////////////
// CLoader


STDMETHODIMP CLoader::GetAverageMethodTime(long *pnAvg)
{
    static time_t tStart = time(&tStart);

    time_t tEnd;
    if (tStart == time(&tEnd))
    {
        *pnAvg = 0;
        return S_OK;
    }

    DWORD dw = WaitForSingleObject(g_hMutex, INFINITE);

    // Average task-seconds per call
    //if (!g_nCount) g_nCount++;
    //*pnAvg = ((float)g_nTime / g_nCount) * 100;

    // Average task-seconds per interval
    *pnAvg = (((float) g_nTime) / (tEnd - tStart)) * 1000;
    g_nTime = 0;

    ReleaseMutex(g_hMutex);

    tStart = tEnd;

	return S_OK;
}
