///////////////////////////////////////////////////////////////////////
//
//  StdAfx.h - Copyright 1999, Tim Ewald / DevelopMentor
//  

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__5E7F74A6_E165_11D2_B72C_00A0CC212296__INCLUDED_)
#define AFX_STDAFX_H__5E7F74A6_E165_11D2_B72C_00A0CC212296__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
//#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module

#include <vector>

using namespace std;

class CServiceModule : public CComModule
{
public:

	HRESULT RegisterServer(BOOL bRegTypeLib, BOOL bService);
	HRESULT UnregisterServer();
    void Start();
	void ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    void Handler(DWORD dwOpcode);
    void Run();
    BOOL IsInstalled();
    BOOL Install();
    BOOL Uninstall();
	void LogEvent(LPCTSTR pszFormat, ...);
    void SetServiceStatus(DWORD dwState);
    void SetupAsLocalServer();

	void Init(_ATL_OBJMAP_ENTRY* p, HINSTANCE h, UINT nServiceNameID, const GUID* plibid = NULL);
	void Term();
	LONG Lock();
	LONG Unlock();
    BOOL IsStopping(DWORD dwMilliseconds = 0);
	HRESULT RegisterClassObjects(void);
	HRESULT RevokeClassObjects(void);
    HRESULT LoadAlgorithm(void);
    HRESULT LoadHosts(void);

//Implementation
private:
	static void WINAPI _ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    static void WINAPI _Handler(DWORD dwOpcode);

// data members
public:
    TCHAR m_szServiceName[256];
    SERVICE_STATUS_HANDLE m_hServiceStatus;
    SERVICE_STATUS m_status;
	DWORD dwThreadID;
	BOOL m_bService;

    HANDLE m_hStopping;
    vector<DWORD> m_vdwReg;
    CComPtr<IUnknown> m_pUnkAlgorithm;
};

extern CServiceModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5E7F74A6_E165_11D2_B72C_00A0CC212296__INCLUDED)
