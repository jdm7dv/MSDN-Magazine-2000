//
// CLSID: 25D84CB0-7345-11d3-A4A1-0080C8ECFED4
//
      
#ifndef __NTSrv_ShellExtension_Defined__
#define __NTSrv_ShellExtension_Defined__

	#pragma data_seg(".text")
	#include <objbase.h>
	#define INITGUID
	#include <initguid.h>
	#include <shlobj.h>
	#include <shlguid.h>
	#pragma data_seg()

	//
	//	Operations.
	//
	#define REGDLL_INSTALL		0
	#define REGDLL_UNINSTALL	1

	//
	//	Factory
	//
	class CDllRegSxClassFactory : public IClassFactory
	{
		protected:
			ULONG	m_cRef;

		public:
			CDllRegSxClassFactory();
			~CDllRegSxClassFactory();

		public:
			STDMETHODIMP			QueryInterface(REFIID, LPVOID FAR *);
			STDMETHODIMP_(ULONG)	AddRef();
			STDMETHODIMP_(ULONG)	Release();

			STDMETHODIMP			CreateInstance(LPUNKNOWN, REFIID, LPVOID FAR *);
			STDMETHODIMP			LockServer(BOOL);
	};

	typedef CDllRegSxClassFactory *LPCSHELLEXTCLASSFACTORY;

	//
	//	Shell extension. Must implement IContextMenu (2, 3) and IShellExtInit.
	//
	class CShellExt : 
		public 
			IContextMenu, 
			IShellExtInit
	{
		protected:
			ULONG					m_cRef;

			LPDATAOBJECT			m_pDataObj;

			UINT					m_xFileCount;				//	count of selected files
			LPTSTR					*m_ppszFileUserClickedOn;	//	[MAX_PATH]

		protected:
			STDMETHODIMP			DoInstall(HWND hParent, LPCSTR pszWorkingDir, LPCSTR pszCmd, LPCSTR pszParam, int iShowCmd);
			STDMETHODIMP			DoUninstall(HWND hParent, LPCSTR pszWorkingDir, LPCSTR pszCmd, LPCSTR pszParam, int iShowCmd);

			STDMETHODIMP			DoAbout(HWND hParent, LPCSTR pszWorkingDir, LPCSTR pszCmd, LPCSTR pszParam, int iShowCmd);

		public:
			STDMETHODIMP			_GetFullFileName(/*LPSTR lpszName*/);
			STDMETHODIMP			_DoRegisterJob(HWND hParent, LPCSTR pszWorkingDir, LPCSTR pszCmd, LPCSTR pszParam, 
										int iShowCmd, const int cintOpCode = REGDLL_INSTALL);

			void					DeleteFileData();

		public:
			CShellExt();
			~CShellExt();

			//	IUnknown
			STDMETHODIMP			QueryInterface(REFIID riid, LPVOID FAR *ppv);
			STDMETHODIMP_(ULONG)	AddRef();
			STDMETHODIMP_(ULONG)	Release();

			//	IContextMenu
			STDMETHODIMP			QueryContextMenu(HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
			STDMETHODIMP			InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi);
			STDMETHODIMP			GetCommandString(UINT idCmd, UINT uFlags, UINT FAR *reserved, LPWSTR pszName, UINT cchMax);

			//	IShellExtInit
			STDMETHODIMP		    Initialize(LPCITEMIDLIST pIDFolder, LPDATAOBJECT pDataObj, HKEY hKeyID);
		};

	typedef CShellExt *LPCSHELLEXT;

#endif 
