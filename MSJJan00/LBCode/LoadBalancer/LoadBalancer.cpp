///////////////////////////////////////////////////////////////////////
//
//  LoadBalancer.cpp - Copyright 1999, Tim Ewald / DevelopMentor
//  


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f LoadBalancerps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "LoadBalancer.h"
#include "LoadBalancer_i.c"

#include "LoadBalancedCategory.h"

#include "ClassObjectShim.h"

#include <stdio.h>
#include "Admin.h"

CServiceModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Admin, CAdmin)
END_OBJECT_MAP()


LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
    while (p1 != NULL && *p1 != NULL)
    {
        LPCTSTR p = p2;
        while (p != NULL && *p != NULL)
        {
            if (*p1 == *p)
                return CharNext(p1);
            p = CharNext(p);
        }
        p1 = CharNext(p1);
    }
    return NULL;
}

// Although some of these functions are big they are declared inline since they are only used once

inline HRESULT CServiceModule::RegisterServer(BOOL bRegTypeLib, BOOL bService)
{
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
        return hr;

    // Remove any previous service since it may point to
    // the incorrect file
    Uninstall();

    // Add service entries
    UpdateRegistryFromResource(IDR_LoadBalancer, TRUE);

    // Adjust the AppID for Local Server or Service
    CRegKey keyAppID;
    LONG lRes = keyAppID.Open(HKEY_CLASSES_ROOT, _T("AppID"), KEY_WRITE);
    if (lRes != ERROR_SUCCESS)
        return lRes;

    CRegKey key;
    lRes = key.Open(keyAppID, _T("{5E7F74A4-E165-11D2-B72C-00A0CC212296}"), KEY_WRITE);
    if (lRes != ERROR_SUCCESS)
        return lRes;
    key.DeleteValue(_T("LocalService"));
    
    if (bService)
    {
        key.SetValue(_T("LoadBalancer"), _T("LocalService"));
        key.SetValue(_T("-Service"), _T("ServiceParameters"));
        // Create service
        Install();
    }

    // Add object entries
    hr = CComModule::RegisterServer(bRegTypeLib);

    CoUninitialize();
    return hr;
}

inline HRESULT CServiceModule::UnregisterServer()
{
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
        return hr;

    // Remove service entries
    UpdateRegistryFromResource(IDR_LoadBalancer, FALSE);
    // Remove service
    Uninstall();
    // Remove object entries
    CComModule::UnregisterServer(TRUE);
    CoUninitialize();
    return S_OK;
}

inline void CServiceModule::Init(_ATL_OBJMAP_ENTRY* p, HINSTANCE h, UINT nServiceNameID, const GUID* plibid)
{
    CComModule::Init(p, h, plibid);

	m_hStopping = CreateEvent(0, TRUE, FALSE, 0);

    m_bService = TRUE;

    LoadString(h, nServiceNameID, m_szServiceName, sizeof(m_szServiceName) / sizeof(TCHAR));

    // set up the initial service status 
    m_hServiceStatus = NULL;
    m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    m_status.dwCurrentState = SERVICE_STOPPED;
    m_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    m_status.dwWin32ExitCode = 0;
    m_status.dwServiceSpecificExitCode = 0;
    m_status.dwCheckPoint = 0;
    m_status.dwWaitHint = 0;
}

inline void CServiceModule::Term(void)
{
	if (m_hStopping) CloseHandle(m_hStopping);
}

BOOL CServiceModule::IsStopping(DWORD dwMilliseconds)
{
	return WaitForSingleObject(m_hStopping, dwMilliseconds) == WAIT_OBJECT_0;
}

LONG CServiceModule::Lock()
{
    if (!m_bService)
        return CoAddRefServerProcess();
    else
        return 2;
}

LONG CServiceModule::Unlock()
{
    if (!m_bService)
    {
    	LONG l = CoReleaseServerProcess();
	    if (l == 0)
            SetEvent(m_hStopping);
        return l;
    }
    else
        return 1;
}

BOOL CServiceModule::IsInstalled()
{
    BOOL bResult = FALSE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hSCM != NULL)
    {
        SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_QUERY_CONFIG);
        if (hService != NULL)
        {
            bResult = TRUE;
            ::CloseServiceHandle(hService);
        }
        ::CloseServiceHandle(hSCM);
    }
    return bResult;
}

inline BOOL CServiceModule::Install()
{
    if (IsInstalled())
        return TRUE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
    {
        MessageBox(NULL, _T("Couldn't open service manager"), m_szServiceName, MB_OK);
        return FALSE;
    }

    // Get the executable file path
    TCHAR szFilePath[_MAX_PATH];
    ::GetModuleFileName(NULL, szFilePath, _MAX_PATH);

    SC_HANDLE hService = ::CreateService(
        hSCM, m_szServiceName, m_szServiceName,
        SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
        SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
        szFilePath, NULL, NULL, _T("RPCSS\0"), NULL, NULL);

    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        MessageBox(NULL, _T("Couldn't create service"), m_szServiceName, MB_OK);
        return FALSE;
    }

    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);
    return TRUE;
}

inline BOOL CServiceModule::Uninstall()
{
    if (!IsInstalled())
        return TRUE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hSCM == NULL)
    {
        MessageBox(NULL, _T("Couldn't open service manager"), m_szServiceName, MB_OK);
        return FALSE;
    }

    SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);

    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        MessageBox(NULL, _T("Couldn't open service"), m_szServiceName, MB_OK);
        return FALSE;
    }
    SERVICE_STATUS status;
    ::ControlService(hService, SERVICE_CONTROL_STOP, &status);

    BOOL bDelete = ::DeleteService(hService);
    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);

    if (bDelete)
        return TRUE;

    MessageBox(NULL, _T("Service could not be deleted"), m_szServiceName, MB_OK);
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////
// Logging functions
void CServiceModule::LogEvent(LPCTSTR pFormat, ...)
{
    TCHAR    chMsg[256];
    HANDLE  hEventSource;
    LPTSTR  lpszStrings[1];
    va_list pArg;

    va_start(pArg, pFormat);
    _vstprintf(chMsg, pFormat, pArg);
    va_end(pArg);

    lpszStrings[0] = chMsg;

    if (m_bService)
    {
        /* Get a handle to use with ReportEvent(). */
        hEventSource = RegisterEventSource(NULL, m_szServiceName);
        if (hEventSource != NULL)
        {
            /* Write to event log. */
            ReportEvent(hEventSource, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, (LPCTSTR*) &lpszStrings[0], NULL);
            DeregisterEventSource(hEventSource);
        }
    }
    else
    {
        // As we are not running as a service, just write the error to the console.
        _putts(chMsg);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Service startup and registration
inline void CServiceModule::Start()
{
    SERVICE_TABLE_ENTRY st[] =
    {
        { m_szServiceName, _ServiceMain },
        { NULL, NULL }
    };
    if (m_bService && !::StartServiceCtrlDispatcher(st))
    {
        m_bService = FALSE;
    }
    if (m_bService == FALSE)
        Run();
}

inline void CServiceModule::ServiceMain(DWORD /* dwArgc */, LPTSTR* /* lpszArgv */)
{
    // Register the control request handler
    m_status.dwCurrentState = SERVICE_START_PENDING;
    m_hServiceStatus = RegisterServiceCtrlHandler(m_szServiceName, _Handler);
    if (m_hServiceStatus == NULL)
    {
        LogEvent(_T("Handler not installed"));
        return;
    }
    SetServiceStatus(SERVICE_START_PENDING);

    m_status.dwWin32ExitCode = S_OK;
    m_status.dwCheckPoint = 0;
    m_status.dwWaitHint = 0;

    // When the Run function returns, the service has stopped.
    Run();

    SetServiceStatus(SERVICE_STOPPED);
    LogEvent(_T("Service stopped"));
}

inline void CServiceModule::Handler(DWORD dwOpcode)
{
    switch (dwOpcode)
    {
    case SERVICE_CONTROL_STOP:
    case SERVICE_CONTROL_SHUTDOWN:
        SetServiceStatus(SERVICE_STOP_PENDING);
        CoSuspendClassObjects();
		SetEvent(m_hStopping);
        break;
    case SERVICE_CONTROL_PAUSE:
        break;
    case SERVICE_CONTROL_CONTINUE:
        break;
    case SERVICE_CONTROL_INTERROGATE:
        break;
    default:
        LogEvent(_T("Bad service request"));
    }
}

void WINAPI CServiceModule::_ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
    _Module.ServiceMain(dwArgc, lpszArgv);
}
void WINAPI CServiceModule::_Handler(DWORD dwOpcode)
{
    _Module.Handler(dwOpcode); 
}

void CServiceModule::SetServiceStatus(DWORD dwState)
{
    m_status.dwCurrentState = dwState;
    ::SetServiceStatus(m_hServiceStatus, &m_status);
}

HRESULT CServiceModule::RegisterClassObjects(void)
{
	HRESULT hr = CComModule::RegisterClassObjects(CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER, REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED);

    CComPtr<ICatInformation> pci;
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 0, CLSCTX_ALL, IID_ICatInformation, (void**)&pci);
    if (FAILED(hr)) return hr;

    CComPtr<IEnumCLSID> pec;
    hr = pci->EnumClassesOfCategories(1, const_cast<struct _GUID *>(&CATID_LoadBalancedClasses), 0, 0, &pec);
    if (FAILED(hr)) return hr;

    CLSID clsid;
    DWORD dwReg;
    while (S_OK == (hr = pec->Next(1, &clsid, 0)))
    {
        hr = CoRegisterClassObject(clsid, static_cast<IClassFactory*>(new ClassObjectShim(clsid)),
                                   CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER, REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED,
                                   &dwReg);
        if (FAILED(hr)) return hr;
        m_vdwReg.push_back(dwReg);
    }
	
	return CoResumeClassObjects();
}

HRESULT CServiceModule::RevokeClassObjects(void)
{
	HRESULT hr = CComModule::RevokeClassObjects();
	if (FAILED(hr)) return hr;
    for (vector<DWORD>::iterator i = m_vdwReg.begin(); i != m_vdwReg.end(); i++)
    {
        hr = CoRevokeClassObject(*i);
		if (FAILED(hr)) return hr;
    }
	return hr;
}

HRESULT CServiceModule::LoadAlgorithm(void)
{
    HRESULT hr;

    CRegKey keySettings;
    LONG lRes = keySettings.Open(HKEY_LOCAL_MACHINE, _T("Software\\DevelopMentor\\LoadBalancing\\RoutingServer"), KEY_READ);
    if (lRes != ERROR_SUCCESS)
        return lRes;

    TCHAR tsz[64];
    DWORD dw = sizeof(tsz);
    lRes = keySettings.QueryValue(tsz, _T("Default Algorithm"), &dw);
    if (lRes != ERROR_SUCCESS)
        return lRes;

    if (!dw) return E_FAIL;

#ifdef UNICODE
    OLECHAR *wsz = tsz;
#else
    OLECHAR wsz[64];
    mbstowcs(wsz, tsz, dw);
#endif
    CLSID clsid;
    hr = CLSIDFromProgID(wsz, &clsid);
    if (FAILED(hr))
    {
        hr = CLSIDFromString(wsz, &clsid);
    }
    if (FAILED(hr)) return hr;

    hr = CoCreateInstance(clsid, 0, CLSCTX_ALL, IID_IUnknown, (void**)&m_pUnkAlgorithm);
    
    return hr;
}

HRESULT CServiceModule::LoadHosts(void)
{
	int i;
    HRESULT hr = E_FAIL;

    CRegKey keySettings;
    LONG lRes = keySettings.Open(HKEY_LOCAL_MACHINE, _T("Software\\DevelopMentor\\LoadBalancing\\RoutingServer"), KEY_READ);
    if (lRes != ERROR_SUCCESS)
        return lRes;

    DWORD dwSubKeys, dwMaxValueLen;
    lRes = RegQueryInfoKey(keySettings,
                           0,
                           0,
                           0,
                           &dwSubKeys,
                           0,
                           0,
                           0,
                           &dwMaxValueLen,
                           0,
                           0,
                           0);

    if (!dwSubKeys) return E_FAIL;

    LPOLESTR *prgwsz = new LPOLESTR[dwSubKeys];
    if (!prgwsz) return E_OUTOFMEMORY;

    memset(prgwsz, 0, sizeof(prgwsz));

    for (long i = 0; i < dwSubKeys; i++)
    {
        DWORD dw = dwMaxValueLen;
        prgwsz[i] = new OLECHAR[dw];
        if (!prgwsz[i]) break;
        
        lRes = RegEnumKeyExW(keySettings,
                             i,
                             prgwsz[i],
                             &dw,
                             0,
                             0,
                             0,
                             0);
        if (lRes != ERROR_SUCCESS) break;
	}
	
    if (i == dwSubKeys)
    {
        CComQIPtr<IHosts> ph(_Module.m_pUnkAlgorithm);
        hr = ph->SetHosts(dwSubKeys, prgwsz);
        i--;
    }
   
    for (; i >= 0; i--)
        if (prgwsz[i]) delete [] prgwsz[i];
    delete [] prgwsz;
    
    return hr;
}

void CServiceModule::Run()
{
    _Module.dwThreadID = GetCurrentThreadId();

//  If you are running on NT 4.0 or higher you can use the following call
//  instead to make the EXE free threaded.
//  This means that calls come in on a random RPC thread
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    _ASSERTE(SUCCEEDED(hr));

    // This provides a NULL DACL which will allow access to everyone.
    CSecurityDescriptor sd;
    sd.InitializeFromThreadToken();
    hr = CoInitializeSecurity(sd, -1, NULL, NULL,
        RPC_C_AUTHN_LEVEL_PKT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
    _ASSERTE(SUCCEEDED(hr));

    hr = _Module.LoadAlgorithm();
    _ASSERTE(SUCCEEDED(hr));

    hr = _Module.LoadHosts();
    _ASSERTE(SUCCEEDED(hr));

	hr = _Module.RegisterClassObjects();
	_ASSERTE(SUCCEEDED(hr));

    LogEvent(_T("Service started"));
    if (m_bService)
	{
        SetServiceStatus(SERVICE_RUNNING);
	}

	WaitForSingleObject(m_hStopping, INFINITE);

    _Module.m_pUnkAlgorithm.Release();

	_Module.RevokeClassObjects();

    CoUninitialize();
}

/////////////////////////////////////////////////////////////////////////////
//
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, 
    HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int /*nShowCmd*/)
{
    lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
    _Module.Init(ObjectMap, hInstance, IDS_SERVICENAME, &LIBID_LOADBALANCERLib);
    _Module.m_bService = TRUE;

    TCHAR szTokens[] = _T("-/");

    LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
    while (lpszToken != NULL)
    {
        if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
            return _Module.UnregisterServer();

        // Register as Local Server
        if (lstrcmpi(lpszToken, _T("RegServer"))==0)
            return _Module.RegisterServer(TRUE, FALSE);
        
        // Register as Service
        if (lstrcmpi(lpszToken, _T("Service"))==0)
            return _Module.RegisterServer(TRUE, TRUE);
        
        lpszToken = FindOneOf(lpszToken, szTokens);
    }

    // Are we Service or Local Server
    CRegKey keyAppID;
    LONG lRes = keyAppID.Open(HKEY_CLASSES_ROOT, _T("AppID"), KEY_READ);
    if (lRes != ERROR_SUCCESS)
        return lRes;

    CRegKey key;
    lRes = key.Open(keyAppID, _T("{5E7F74A4-E165-11D2-B72C-00A0CC212296}"), KEY_READ);
    if (lRes != ERROR_SUCCESS)
        return lRes;

    TCHAR szValue[_MAX_PATH];
    DWORD dwLen = _MAX_PATH;
    lRes = key.QueryValue(szValue, _T("LocalService"), &dwLen);

    _Module.m_bService = FALSE;
    if (lRes == ERROR_SUCCESS)
        _Module.m_bService = TRUE;

    _Module.Start();

    // When we get here, the service has been stopped
    return _Module.m_status.dwWin32ExitCode;
}

