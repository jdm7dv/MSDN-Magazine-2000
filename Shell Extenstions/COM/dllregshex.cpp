#include "dllreg_xhdr.h"
#include <olectl.h>
#include "dllregshex.h"
#include "dllreg_util.h"
#include "resource.h"

#ifndef __CLSID_NTSrv_Defined__
#define __CLSID_NTSrv_Defined__
DEFINE_GUID(CLSID_DLLRegisterer, 0x25d84cb0, 0x7345, 0x11d3, 0xa4, 0xa1, 0x0, 0x80, 0xc8, 0xec, 0xfe, 0xd4);
#endif

UINT      g_cRefThisDll = 0;    
HINSTANCE g_hmodThisDll = NULL;	

HBITMAP hBmp_Install	= 0;
HBITMAP hBmp_Uninstall  = 0;
HBITMAP hBmp_About		= 0;
HMENU	hSubMenu		= 0;

typedef struct
{
   HKEY  hRootKey;
   LPTSTR lpszSubKey;
   LPTSTR lpszValueName;
   LPTSTR lpszData;
} REGSTRUCT, *LPREGSTRUCT;

STDAPI DllRegisterServer(void);
STDAPI DllUnregisterServer(void);

VOID   _LoadResources();
VOID   _UnloadResources();

STDAPI 
DllRegisterServer(void)
{
	HINSTANCE hInst = g_hmodThisDll;

	int      i;
	HKEY     hKey;
	LRESULT  lResult;
	DWORD    dwDisp;
	TCHAR    szSubKey[MAX_PATH];
	TCHAR    szCLSID[MAX_PATH];
	TCHAR    szModule[MAX_PATH];
	LPWSTR   pwszShellExt;

	StringFromIID(CLSID_DLLRegisterer, &pwszShellExt);

	if (pwszShellExt) 
	{
		WideCharToLocal(szCLSID, pwszShellExt, ARRAYSIZE(szCLSID));

		LPMALLOC pMalloc;
		CoGetMalloc(1, &pMalloc);
		if(pMalloc)
		{
			pMalloc->Free(pwszShellExt);
			pMalloc->Release();
		}
	}															   

	GetModuleFileName(hInst, szModule, ARRAYSIZE(szModule));

	//	CLSID registry entries
	REGSTRUCT ShExClsidEntries[] = 
	{
		HKEY_CLASSES_ROOT,	TEXT("CLSID\\%s"),					NULL,                   TEXT(DLLREGUNREGNAME),
		HKEY_CLASSES_ROOT,	TEXT("CLSID\\%s\\InProcServer32"),	NULL,                   TEXT("%s"),
		HKEY_CLASSES_ROOT,	TEXT("CLSID\\%s\\InProcServer32"),	TEXT("ThreadingModel"), TEXT("Apartment"),
		NULL,                NULL,								NULL,                   NULL
	};

	for(i = 0; ShExClsidEntries[i].hRootKey; i++) 
    {
		wsprintf(szSubKey, ShExClsidEntries[i].lpszSubKey, szCLSID);
		lResult = RegCreateKeyEx(ShExClsidEntries[i].hRootKey, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
			KEY_WRITE, NULL, &hKey, &dwDisp);

		if(NOERROR == lResult) 
		{
			TCHAR szData[MAX_PATH];
			wsprintf(szData, ShExClsidEntries[i].lpszData, szModule);
			lResult = RegSetValueEx(hKey, ShExClsidEntries[i].lpszValueName, 0, REG_SZ, 
				(LPBYTE)szData, lstrlen(szData) + 1);
			RegCloseKey(hKey);
		} 
		else
			return SELFREG_E_CLASS;
   }                                

	//	Other necessary registry entries.
	REGSTRUCT OtherShExEntries[] = 
	{
			HKEY_LOCAL_MACHINE,	TEXT("software\\classes\\clsid\\"DLLREGUNREGNAME)			  , NULL,		TEXT("%s"),
			HKEY_CLASSES_ROOT,	TEXT("dllfile\\shellex\\ContextMenuHandlers\\"DLLREGUNREGNAME), NULL,		TEXT("%s"),
			NULL,				NULL,								NULL,                   NULL
	};

	for (i = 0; OtherShExEntries[i].hRootKey; i++) 
    {
		wsprintf(szSubKey, OtherShExEntries[i].lpszSubKey, szCLSID);
		lResult = RegCreateKeyEx(OtherShExEntries[i].hRootKey, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
			KEY_WRITE, NULL, &hKey, &dwDisp);

		if(NOERROR == lResult) 
		{
			TCHAR szData[MAX_PATH];
			wsprintf(szData, OtherShExEntries[i].lpszData, szCLSID);
			lResult = RegSetValueEx(hKey, OtherShExEntries[i].lpszValueName, 0, REG_SZ,
				(LPBYTE)szData, lstrlen(szData) + 1);
			RegCloseKey(hKey);
		} 
		else
			return SELFREG_E_CLASS;
	}

	//	See if 'ocxfile' extension exists; if no, create and populate with appropriate data.
	lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT,	".ocx", 0L, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE,
		NULL, &hKey, &dwDisp);
	if(NOERROR == lResult) 
	{
		//	to correct: they key can already exists!

		TCHAR szData[MAX_PATH];
		
		//	Associate with 'ocxfile'
		wsprintf(szData, TEXT("ocxfile"));
		lResult = RegSetValueEx(hKey, "", 0, REG_SZ, (LPBYTE)szData, lstrlen(szData) + 1);

		wsprintf(szData, TEXT("ActiveX Control"));
		lResult = RegSetValueEx(hKey, "Content Type", 0, REG_SZ, (LPBYTE)szData, lstrlen(szData) + 1);

		RegCloseKey(hKey);
	} 
	else
		return SELFREG_E_CLASS;

	REGSTRUCT OCXShExEntries[] = 
	{
			HKEY_CLASSES_ROOT,	TEXT("ocxfile\\shellex\\ContextMenuHandlers\\"DLLREGUNREGNAME), NULL,		TEXT("%s"),
			NULL,				NULL,								NULL,                   NULL
	};

	for (i = 0; OCXShExEntries[i].hRootKey; i++) 
    {
		wsprintf(szSubKey, OCXShExEntries[i].lpszSubKey, szCLSID);
		lResult = RegCreateKeyEx(OCXShExEntries[i].hRootKey, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
			KEY_WRITE, NULL, &hKey, &dwDisp);

		if(NOERROR == lResult) 
		{
			TCHAR szData[MAX_PATH];
			wsprintf(szData, OCXShExEntries[i].lpszData, szCLSID);

			lResult = RegSetValueEx(hKey, OCXShExEntries[i].lpszValueName, 0, REG_SZ,
				(LPBYTE)szData, lstrlen(szData) + 1);

			RegCloseKey(hKey);
		} 
		else
			return SELFREG_E_CLASS;
	}

	//	Default Icon
	lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT, "ocxfile\\DefaultIcon", 0L, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE,
		NULL, &hKey, &dwDisp);
	if(lResult == NO_ERROR)
	{
		TCHAR szData[MAX_PATH];

		wsprintf(szData, "%s,%ld", szModule, 0);
		lResult = RegSetValueEx(hKey, "", 0, REG_SZ, (LPBYTE)szData, lstrlen(szData) + 1);
		if(lResult != NO_ERROR)
			return SELFREG_E_CLASS;

		RegCloseKey(hKey);
	}

	//	Register extension as 'Approved' under WindowsNT.
	OSVERSIONINFO  osvi;
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	GetVersionEx(&osvi);
	if (VER_PLATFORM_WIN32_NT == osvi.dwPlatformId)  
	{
		lstrcpy( szSubKey, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"));
		lResult = RegCreateKeyEx(  HKEY_LOCAL_MACHINE, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE,
			NULL, &hKey, &dwDisp);
		if(NOERROR == lResult) 
		{
			TCHAR szData[MAX_PATH];
			lstrcpy(szData, DLLREGUNREGNAME);
			lResult = RegSetValueEx(hKey, szCLSID, 0, REG_SZ, (LPBYTE)szData, lstrlen(szData) + 1);
			RegCloseKey(hKey);
		} 
		else
			return SELFREG_E_CLASS;
	}

	return S_OK;
}

STDAPI 
DllUnregisterServer(void)
{
	int      i;
	LRESULT  lResult;
	TCHAR    szSubKey[MAX_PATH];
	TCHAR    szCLSID[MAX_PATH];
	LPWSTR   pwszShellExt;

	StringFromIID(CLSID_DLLRegisterer, &pwszShellExt);
	
	if (pwszShellExt) 
	{
		WideCharToLocal(szCLSID, pwszShellExt, ARRAYSIZE(szCLSID));

		LPMALLOC pMalloc;						  
		CoGetMalloc(1, &pMalloc);

		if(pMalloc)
		{
			pMalloc->Free(pwszShellExt);
			pMalloc->Release();
		}
	}															   
					    
	REGSTRUCT ShExClsidEntries[] = 
	{
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s\\InProcServer32"), NULL, NULL,
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s"), NULL, NULL,
		NULL, NULL, NULL, NULL
	};

	for(i = 0; ShExClsidEntries[i].hRootKey; i++) 
	{
		wsprintf(szSubKey, ShExClsidEntries[i].lpszSubKey, szCLSID);
		lResult = RegDeleteKey(ShExClsidEntries[i].hRootKey, szSubKey);
																			 
		if(lResult != NOERROR) 
			return SELFREG_E_CLASS;
	}

	REGSTRUCT OtherShExEntries[] = 
	{
			HKEY_CLASSES_ROOT,	TEXT("dllfile\\shellex\\ContextMenuHandlers\\"DLLREGUNREGNAME), NULL,		NULL,
			NULL,				NULL,								NULL,                   NULL
	};

	for(i = 0; OtherShExEntries[i].hRootKey; i++) 
	{
		wsprintf(szSubKey, OtherShExEntries[i].lpszSubKey, szCLSID);
		lResult = RegDeleteKey(OtherShExEntries[i].hRootKey, szSubKey);
		if(lResult != NOERROR) 
			return SELFREG_E_CLASS;
	}

	lResult = RegDeleteKey(HKEY_CLASSES_ROOT, ".ocx");
	if(lResult != NOERROR) 
		return SELFREG_E_CLASS;

	//	Default Icon
	lResult = RegDeleteKey(HKEY_CLASSES_ROOT, "ocxfile\\DefaultIcon");
	if(lResult != NOERROR) 
		return SELFREG_E_CLASS;

	TCHAR szKeyName[_MAX_PATH + 1];
	wsprintf(szKeyName, "ocxfile\\shellex\\ContextMenuHandlers\\%s", DLLREGUNREGNAME);
	lResult = RegDeleteKey(HKEY_CLASSES_ROOT, szKeyName);
	if(lResult != NOERROR) 
		return SELFREG_E_CLASS;

	lResult = RegDeleteKey(HKEY_CLASSES_ROOT, "ocxfile\\shellex\\ContextMenuHandlers");
	if(lResult != NOERROR) 
		return SELFREG_E_CLASS;
	lResult = RegDeleteKey(HKEY_CLASSES_ROOT, "ocxfile\\shellex");
	if(lResult != NOERROR) 
		return SELFREG_E_CLASS;
	lResult = RegDeleteKey(HKEY_CLASSES_ROOT, "ocxfile");
	if(lResult != NOERROR) 
		return SELFREG_E_CLASS;
	
	OSVERSIONINFO  osvi;
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	GetVersionEx(&osvi);

	if (VER_PLATFORM_WIN32_NT == osvi.dwPlatformId)  
	{
		lstrcpy( szSubKey, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved\\"DLLREGUNREGNAME));
		lResult = RegDeleteKey(HKEY_LOCAL_MACHINE, szSubKey);
	}

	return S_OK;
}

extern "C" 
int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	_UNUSED_PARAMETER(lpReserved);

    if (dwReason == DLL_PROCESS_ATTACH)
	{
        g_hmodThisDll = hInstance;
		_LoadResources();
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_UnloadResources();

    return 1;
}

VOID
_LoadResources(VOID)
{
	hBmp_Install	= LoadBitmap(g_hmodThisDll, MAKEINTRESOURCE(IDB_INSTALL));
	hBmp_Uninstall  = LoadBitmap(g_hmodThisDll, MAKEINTRESOURCE(IDB_UNINSTALL));
	hBmp_About		= LoadBitmap(g_hmodThisDll, MAKEINTRESOURCE(IDB_ABOUT));
}

VOID
_UnloadResources(VOID)
{
	DeleteObject(hBmp_Install);
	DeleteObject(hBmp_Uninstall);
	DeleteObject(hBmp_About);

	DestroyMenu(hSubMenu);
}

STDAPI 
DllCanUnloadNow(void)
{
    return (g_cRefThisDll == 0 ? S_OK : S_FALSE);
}

STDAPI 
DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppvOut)
{
    *ppvOut = NULL;

    if (IsEqualIID(rclsid, CLSID_DLLRegisterer))
    {
        CDllRegSxClassFactory *pcf = new CDllRegSxClassFactory;
        return pcf->QueryInterface(riid, ppvOut);
    }
	
    return CLASS_E_CLASSNOTAVAILABLE;
}

CDllRegSxClassFactory::CDllRegSxClassFactory()
{
    m_cRef = 0L;
    g_cRefThisDll++;	
}
																
CDllRegSxClassFactory::~CDllRegSxClassFactory()				
{
    g_cRefThisDll--;
}

STDMETHODIMP 
CDllRegSxClassFactory::QueryInterface(REFIID riid, LPVOID FAR *ppv)
{
    *ppv = NULL;

    if(IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IClassFactory))
    {
        *ppv = (LPCLASSFACTORY)this;
        AddRef();

        return NOERROR;
    }

    return E_NOINTERFACE;
}	

STDMETHODIMP_(ULONG) 
CDllRegSxClassFactory::AddRef()
{
    return ++m_cRef;
}

STDMETHODIMP_(ULONG) 
CDllRegSxClassFactory::Release()
{
    if (--m_cRef)
        return m_cRef;

    delete this;
    return 0L;
}

STDMETHODIMP 
CDllRegSxClassFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, LPVOID *ppvObj)
{
    *ppvObj = NULL;

    if (pUnkOuter)
    	return CLASS_E_NOAGGREGATION;

    LPCSHELLEXT pShellExt = new CShellExt();
    if (NULL == pShellExt)
    	return E_OUTOFMEMORY;

    return pShellExt->QueryInterface(riid, ppvObj);
}

STDMETHODIMP 
CDllRegSxClassFactory::LockServer(BOOL fLock)
{
	_UNUSED_PARAMETER(fLock);

    return NOERROR;
}

CShellExt::CShellExt()
	: 
		m_xFileCount(0),
		m_ppszFileUserClickedOn(0)
{
    m_cRef = 0L;
    m_pDataObj = NULL;

    g_cRefThisDll++;
}

CShellExt::~CShellExt()
{
    if (m_pDataObj)
        m_pDataObj->Release();

	DeleteFileData();

    g_cRefThisDll--;
}

void
CShellExt::DeleteFileData()
{
	if(m_xFileCount > 0)
	{
		for(register UINT x = 0; x < m_xFileCount; x++)
		{
			delete[] m_ppszFileUserClickedOn[x];
		}
		delete m_ppszFileUserClickedOn;
	}
}

STDMETHODIMP 
CShellExt::QueryInterface(REFIID riid, LPVOID FAR *ppv)
{
    *ppv = NULL;
    if (IsEqualIID(riid, IID_IShellExtInit) || IsEqualIID(riid, IID_IUnknown))
    	*ppv = (LPSHELLEXTINIT)this;
    else if (IsEqualIID(riid, IID_IContextMenu))
        *ppv = (LPCONTEXTMENU)this;

    if(*ppv)
    {
        AddRef();
        return NOERROR;
    }

	return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) 
CShellExt::AddRef()
{
    return ++m_cRef;
}

STDMETHODIMP_(ULONG) 
CShellExt::Release()
{
    if(--m_cRef)
        return m_cRef;

    delete this;
    return 0L;
}

STDMETHODIMP 
CShellExt::Initialize(LPCITEMIDLIST pIDFolder, LPDATAOBJECT pDataObj, HKEY hRegKey)
{
	_UNUSED_PARAMETER(hRegKey);
	_UNUSED_PARAMETER(pIDFolder);

	if (m_pDataObj)
    	m_pDataObj->Release();
    if (pDataObj)
    {
    	m_pDataObj = pDataObj;
    	pDataObj->AddRef();
    }
    return NOERROR;
}
