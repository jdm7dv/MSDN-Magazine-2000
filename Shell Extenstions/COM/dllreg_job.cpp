#include "dllreg_xhdr.h"
#include "dllregshex.h"
#include "dllreg_util.h"
#include "resource.h"

#include <stdio.h>

extern HINSTANCE g_hmodThisDll;	
#pragma warning(disable:4127)
STDMETHODIMP 
CShellExt::_GetFullFileName()
{
	HRESULT hr = S_FALSE;

	//
	//	IEnumFORMATETC. Needed for format enumeration.
	//
	IEnumFORMATETC *pefEtc = 0;
	hr = m_pDataObj->EnumFormatEtc(DATADIR_GET, &pefEtc);
	if(SUCCEEDED(hr))
	{
		hr = pefEtc->Reset();	//	Reset enumeration.

		if(SUCCEEDED(hr))
		{
			//
			//	FORMATETC. Needed for get data about object.
			//
			FORMATETC fEtc;
			ULONG ulFetched = 0L;

			while(TRUE)
			{
				hr = pefEtc->Next(1, &fEtc, &ulFetched);
				if(FAILED(hr) || (ulFetched <= 0))
					break;

				//
				//	'Arm' format and 'launch' to obtain STGMEDIUM...
				//
				fEtc.cfFormat	= CF_HDROP;
				fEtc.dwAspect	= DVASPECT_CONTENT;
				fEtc.lindex		= -1;
				fEtc.ptd		= NULL;
				fEtc.tymed		= TYMED_HGLOBAL;

				//
				//	IDataObject : GetData. Returned as TYMED_HGLOBAL.
				//
				STGMEDIUM stgM;
				hr = m_pDataObj->GetData(&fEtc, &stgM);
				if(SUCCEEDED(hr))
				{
					if(stgM.tymed == TYMED_HGLOBAL)
					{
//						m_ppszFileUserClickedOn[0] = '\0';

						UINT nFileCount = DragQueryFile((HDROP)stgM.hGlobal, (UINT)INVALID_HANDLE_VALUE, NULL, 0);
						if(nFileCount >= 1)
						{
							if(m_ppszFileUserClickedOn)
							{
								DeleteFileData();
							}

							m_ppszFileUserClickedOn = new LPTSTR[nFileCount];

							for(register UINT x = 0; x < nFileCount; x++)
							{
								m_ppszFileUserClickedOn[x] = new TCHAR[_MAX_PATH + 1];

								//	one file only; eliminate this and improve code to allow multiple-DLL file (un)registering
								DragQueryFile((HDROP)stgM.hGlobal, x, m_ppszFileUserClickedOn[x], _MAX_PATH + 1);
							}

							m_xFileCount = nFileCount;
						}
					}
				}
			}
		}
	}

	if(pefEtc)
		pefEtc->Release();
	return hr;
}

STDMETHODIMP			
CShellExt::_DoRegisterJob(HWND hParent, LPCSTR pszWorkingDir, LPCSTR pszCmd, LPCSTR pszParam, int iShowCmd, 
	const int cintOpCode)
{
	_UNUSED_PARAMETER(iShowCmd);
	_UNUSED_PARAMETER(pszParam);
	_UNUSED_PARAMETER(pszCmd);

	HRESULT hr = S_FALSE;

	hr = _GetFullFileName();
	if(SUCCEEDED(hr))
	{
		bool fNotYetAgree = false;

		for(register UINT x = 0; x < m_xFileCount; x++)
		{
			char lpszFmtText[512], lpszAsk[1024], lpszRelName[2 * (_MAX_PATH + 1)];

			//	relative filename; pointer arithmetic ("C:\\TEMP\\file.dll" - "C:\\TEMP\\" = "file.dll"
			strcpy(lpszRelName, m_ppszFileUserClickedOn[x] + ((strlen(pszWorkingDir) + 1) * sizeof(char)));

			//	format string for user confirmation and ...
			//	compose message
			if(m_xFileCount == 1) // single file
			{
				LoadString(g_hmodThisDll, IDS_Q_INSTALL, lpszFmtText, 512);
				sprintf(lpszAsk, lpszFmtText, lpszRelName);
			}
			else
			{
				LoadString(g_hmodThisDll, IDS_QMI_INSTALL, lpszFmtText, 512);
				sprintf(lpszAsk, lpszFmtText);
			}

			if(fNotYetAgree || MessageBox(0, lpszAsk, 0, MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				fNotYetAgree = true;

				char pszCmdLine[_MAX_PATH + 1];	//	command line for regsvr32.exe
				switch(cintOpCode)
				{
					case REGDLL_INSTALL:
						sprintf(pszCmdLine, "regsvr32.exe \"%s\"", m_ppszFileUserClickedOn[x]);
						break;
					case REGDLL_UNINSTALL:
						sprintf(pszCmdLine, "regsvr32.exe /u \"%s\"", m_ppszFileUserClickedOn[x]);
						break;
					default:
						break;
				}

				STARTUPINFO si;
				PROCESS_INFORMATION pi;

				ZeroMemory(&si, sizeof(si));
				si.cb = sizeof(STARTUPINFO);
				si.dwFlags = STARTF_USESHOWWINDOW;
				si.wShowWindow = SW_SHOW;
				ZeroMemory(&pi, sizeof(pi));

				if(CreateProcess(0, pszCmdLine, 0, 0, FALSE, CREATE_DEFAULT_ERROR_MODE | NORMAL_PRIORITY_CLASS, 0, 0, &si, &pi))
				{
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
				}
				else
					MessageBox(0, "Unable to run regsvr32.exe process.", DLLREGUNREGNAME, MB_OK);
			}
			else
				MessageBox(hParent, "User abort!", DLLREGUNREGNAME, MB_OK);
		}
	}

	return NOERROR;
}

STDMETHODIMP 
CShellExt::DoInstall(HWND hParent, LPCSTR pszWorkingDir, LPCSTR pszCmd, LPCSTR pszParam, int iShowCmd)
{
	return _DoRegisterJob(hParent, pszWorkingDir, pszCmd, pszParam, iShowCmd, REGDLL_INSTALL);
}

STDMETHODIMP 
CShellExt::DoUninstall(HWND hParent, LPCSTR pszWorkingDir, LPCSTR pszCmd, LPCSTR pszParam, int iShowCmd)
{
	return _DoRegisterJob(hParent, pszWorkingDir, pszCmd, pszParam, iShowCmd, REGDLL_UNINSTALL);
}

STDMETHODIMP 
CShellExt::DoAbout(HWND hParent, LPCSTR pszWorkingDir, LPCSTR pszCmd, LPCSTR pszParam, int iShowCmd)
{
	_UNUSED_PARAMETER(iShowCmd);
	_UNUSED_PARAMETER(pszParam);
	_UNUSED_PARAMETER(pszCmd);
	_UNUSED_PARAMETER(pszWorkingDir);

	char szAboutText[1024];

	LoadString(g_hmodThisDll, IDS_ABOUT, szAboutText, 1024);
	MessageBox(hParent, szAboutText, DLLREGUNREGNAME, MB_OK | MB_ICONINFORMATION);
	return NOERROR;
}
