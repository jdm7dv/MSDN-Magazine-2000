// Property.cpp : Implementation of CProperty
#include "stdafx.h"
#include "FolderExt.h"
#include "Property.h"
#include "SHHelper.h"
#include <ShlWAPI.h>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "shhelper.lib")
#pragma comment(lib, "msimg32.lib")

// Externals
extern DWORD g_dwWinPlatform;

// Constants
#define BUFSIZE		(MAX_PATH + 20)
#define DRIVEICONS	"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\DriveIcons\\"

// Helper functions
static void InitializeDialog(HWND, LPTSTR);
static void ShowIcon(HWND, LPTSTR, UINT);
static void SetCustomization(HWND);
static void RemoveCustomization(void);

// A few plain old global variables... 
static TCHAR g_szFolder[MAX_PATH];
static TCHAR g_szDesktopIni[MAX_PATH];
static TCHAR g_szIconFile[MAX_PATH];
static DWORD g_nIconIndex;
static HICON g_hIcon=NULL;
static UINT g_idCmdFirst;
static HMENU g_hMenu;


/////////////////////////////////////////////////////////////////////////////
// CProperty


/////////////////////////////////////////////////////////////////////////////
// Methods of IContextMenu


// QueryContextMenu
HRESULT CProperty::QueryContextMenu(HMENU hmenu, UINT indexMenu,
		UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
	g_idCmdFirst = idCmdFirst;
	UINT idCmd = idCmdFirst;
	
	// Creates the popup menu
	HMENU hmnuPopup = CreatePopupMenu();
	InsertMenu(hmnuPopup, 0, MF_STRING|MF_BYPOSITION|MF_OWNERDRAW,
			idCmd++, _T(""));
	InsertMenu(hmnuPopup, 1, MF_STRING|MF_BYPOSITION|MF_OWNERDRAW,
			idCmd++, _T(""));
	
	
	// Add it to the context menu 
	InsertMenu(hmenu, indexMenu++, MF_POPUP|MF_BYPOSITION,
			(UINT)hmnuPopup, _T("Advanced Features"));
 
	return MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_NULL, 
		idCmd-idCmdFirst);
}

 
// InvokeCommand
HRESULT CProperty::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
	if (HIWORD(lpcmi->lpVerb) == 0)
	{
		UINT idCmd = LOWORD(lpcmi->lpVerb);
		switch(idCmd)
		{
			case 0:		// New folder
				lstrcpy(m_Dlg.m_szParentFolder, m_szFile);
				m_Dlg.DoModal();
				break;

			case 1:		// MS-DOS prompt
			   TCHAR szCommand[MAX_PATH] = _T("");
			   STARTUPINFO si;
			   PROCESS_INFORMATION pi;

			   // Determine the command prompt
			   GetEnvironmentVariable(_T("ComSpec"), szCommand, MAX_PATH);
			   if (!*szCommand)
			   {
					lstrcpy(szCommand, 
						(g_dwWinPlatform==VER_PLATFORM_WIN32_WINDOWS
						?_T("command.com")
						:_T("cmd.exe")));
			   }

			   // Create the process
			   ZeroMemory(&si, sizeof(si));
			   si.cb = sizeof(si);
			   CreateProcess( NULL,
							  szCommand,
							  NULL,
							  NULL,
							  FALSE,
							  NORMAL_PRIORITY_CLASS,
							  NULL,
							  m_szFile,
							  &si,
							  &pi);
				break;
		}
	}
	return S_OK;
}



// GetCommandString
HRESULT CProperty::GetCommandString(UINT idCmd, UINT uFlags, 
		UINT *pwReserved, LPSTR pszText, UINT cchMax)
{
	return S_OK;
}



/////////////////////////////////////////////////////////////////////////////
// Methods of IContextMenu2

HRESULT CProperty::HandleMenuMsg(UINT uMsg,WPARAM wParam, LPARAM lParam)
{
	return HandleMenuMsg2(uMsg, wParam, lParam, NULL);
}





/////////////////////////////////////////////////////////////////////////////
// Methods of IContextMenu3

HRESULT CProperty::HandleMenuMsg2(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *plResult)
{
	switch(uMsg)
	{
		case WM_INITMENUPOPUP:
			g_hMenu = (HMENU) wParam;
			break;

	    case WM_DRAWITEM:
			DrawMenuItem((LPDRAWITEMSTRUCT) lParam);
			break;

		case WM_MEASUREITEM:
			MeasureItem((LPMEASUREITEMSTRUCT) lParam);
			break;
	}
	
	return S_OK;
}




/////////////////////////////////////////////////////////////////////////////
// Methods of IShellExtInit




// Initialize
HRESULT CProperty::Initialize(LPCITEMIDLIST pidlFolder,
	LPDATAOBJECT lpdobj, HKEY hKeyProgID)
{
   if (lpdobj == NULL)
        return E_INVALIDARG;

   // Initialize common controls
   InitCommonControls();

   // Get the data as CF_HDROP   
   STGMEDIUM medium;
   FORMATETC fe = {CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
   HRESULT hr = lpdobj->GetData(&fe, &medium);
   if (FAILED(hr))
        return E_INVALIDARG;

	// save the file name
    if (DragQueryFile((HDROP) medium.hGlobal, 0xFFFFFFFF, NULL, 0)==1) 
	{
		DragQueryFile((HDROP) medium.hGlobal, 0, m_szFile, sizeof(m_szFile));
		lstrcpy(g_szFolder, m_szFile);
        hr = NOERROR;
    }
    else
        hr = E_INVALIDARG;

	ReleaseStgMedium(&medium);
    return hr;
}



/////////////////////////////////////////////////////////////////////////////
// Methods of IShellPropSheetExt 


// AddPages
HRESULT CProperty::AddPages(LPFNADDPROPSHEETPAGE lpfnAddPage,
	LPARAM lParam)
{
	PROPSHEETPAGE psp;
	HPROPSHEETPAGE hPage;

	ZeroMemory(&psp, sizeof(PROPSHEETPAGE));
    psp.dwSize = sizeof(PROPSHEETPAGE);
    psp.dwFlags = PSP_USETITLE|PSP_DEFAULT;
    psp.hInstance = _Module.GetModuleInstance();
    psp.pszTemplate = MAKEINTRESOURCE(IDD_CUSTOMIZEFOLDER);
    psp.pszTitle = _T("Customize");
    psp.pfnDlgProc = (DLGPROC) PropPage_DlgProc;
    psp.lParam = (LPARAM) this;
    hPage = ::CreatePropertySheetPage(&psp);

    // add the page to the property sheet
    if (hPage != NULL)
        if (!lpfnAddPage(hPage, lParam))
		::DestroyPropertySheetPage(hPage);

    return NOERROR;
}


// STATIC: Dialog-procedure for the new page
BOOL CALLBACK CProperty::PropPage_DlgProc(HWND hwnd, UINT uiMsg, WPARAM wParam,
    LPARAM lParam)
{
    switch(uiMsg) 
	{
		case WM_INITDIALOG:
			PathSetDlgItemPath(hwnd, IDC_FOLDERNAME, (LPTSTR) g_szFolder); 
			InitializeDialog(hwnd, g_szFolder);
			return TRUE;   
			
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_REMOVE:
					RemoveCustomization();
					break;

				case IDC_CUSTOMIZE:
					SetCustomization(hwnd);
					break;

				case IDC_CHANGEICON:
					TCHAR szBuf[MAX_PATH];
					lstrcpy(szBuf, g_szIconFile);
					if (!lstrlen(szBuf))
					{
						GetSystemDirectory(szBuf, MAX_PATH);
						lstrcat(szBuf, _T("\\shell32.dll"));
					}
					g_nIconIndex = SHBrowseForIcon((LPCSTR)szBuf, &g_hIcon);
					if (g_nIconIndex != -1)
					{
						lstrcpy(g_szIconFile, szBuf);
						ShowIcon(hwnd, g_szIconFile, g_nIconIndex);
					}
					break;
			}
			break;

		case WM_DESTROY:
			DestroyIcon(g_hIcon);
			break;

    }
    return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// Helper Functions

void InitializeDialog(HWND hwnd, LPTSTR szFolder)
{
	lstrcpy(g_szDesktopIni, szFolder);
	PathAddBackslash(g_szDesktopIni);
	lstrcat(g_szDesktopIni, _T("desktop.ini"));

	// Read the description
	TCHAR szBuf[BUFSIZE];
	GetPrivateProfileString(_T(".ShellClassInfo"), _T("infotip"), _T(""), szBuf, MAX_PATH, g_szDesktopIni);
	SetDlgItemText(hwnd, IDC_TEXT, szBuf);

	// Read the icon information
	if (!PathIsRoot(g_szFolder))
	{
		GetPrivateProfileString(_T(".ShellClassInfo"), _T("iconfile"), _T(""), g_szIconFile, MAX_PATH, g_szDesktopIni);
		g_nIconIndex = GetPrivateProfileInt(_T(".ShellClassInfo"), _T("iconindex"), -1, g_szDesktopIni);
	}
	else
	{
		g_nIconIndex = -1;
		DWORD dwType;
		DWORD dwSize = BUFSIZE;
		TCHAR temp[BUFSIZE];
		wsprintf(temp, _T("%s%c\\DefaultIcon"), DRIVEICONS, g_szFolder[0]);
		DWORD rc = SHGetValue(HKEY_LOCAL_MACHINE, temp, _T(""), &dwType, (LPVOID) szBuf, &dwSize);
		if (rc == ERROR_SUCCESS)
		{
			lstrcpy(g_szIconFile, szBuf);
			g_nIconIndex = PathParseIconLocation(g_szIconFile);
		}
	}
	ShowIcon(hwnd, g_szIconFile, g_nIconIndex);	
}


void ShowIcon(HWND hwnd, LPTSTR szIconFile, UINT nIconIndex)
{	
	if (nIconIndex == -1) {
		SetDlgItemText(hwnd, IDC_ICONFILE, _T("")); 					
		return;
	}

	// Attach the path if only the file name is specified
	if (PathIsFileSpec(szIconFile)) {
		TCHAR buf[MAX_PATH];
		lstrcpy(buf, g_szFolder);
		PathAddBackslash(buf);
		lstrcat(buf, szIconFile);
		lstrcpy(szIconFile, buf);
	}

	g_hIcon = ExtractIcon(_Module.m_hInst, szIconFile, nIconIndex);
	SendDlgItemMessage(hwnd, IDC_FOLDERICON, STM_SETICON, (WPARAM)g_hIcon, 0);
	
	TCHAR szBuf[BUFSIZE];
	wsprintf(szBuf, _T("%s,%d"), szIconFile, nIconIndex);
	SetDlgItemText(hwnd, IDC_ICONFILE, (LPTSTR) szBuf); 					
}


void RemoveCustomization(void)
{
	// Remove the read-only attribute
	DWORD dwAttrib = GetFileAttributes(g_szFolder);
	dwAttrib &= ~FILE_ATTRIBUTE_READONLY;
	SetFileAttributes(g_szFolder, dwAttrib);
	
	if (!PathIsRoot(g_szFolder))
	{
		// Deletes info from Desktop.ini
		WritePrivateProfileString(_T(".ShellClassInfo"), _T("Infotip"), NULL, g_szDesktopIni);
		WritePrivateProfileString(_T(".ShellClassInfo"), _T("IconFile"), NULL, g_szDesktopIni);
		WritePrivateProfileString(_T(".ShellClassInfo"), _T("IconIndex"), NULL, g_szDesktopIni);
	}
	else
	{
		// Deletes info from Desktop.ini
		WritePrivateProfileString(_T(".ShellClassInfo"), _T("Infotip"), NULL, g_szDesktopIni);

		// Delete icon info from the registry
		TCHAR temp[BUFSIZE];
		wsprintf(temp, _T("%s%c"), DRIVEICONS, g_szFolder[0]);
		SHDeleteKey(HKEY_LOCAL_MACHINE, temp);
	}

	SHChangeNotify(SHCNE_ALLEVENTS, 0, NULL, NULL);
}


void SetCustomization(HWND hwnd)
{
	// Collect the data to be used
	BOOL bIconInfo = TRUE;
	TCHAR szText[MAX_PATH];
	TCHAR szIcon[BUFSIZE];
	GetDlgItemText(hwnd, IDC_TEXT, szText, MAX_PATH);
	GetDlgItemText(hwnd, IDC_ICONFILE, szIcon, BUFSIZE);
	if (lstrlen(szIcon))
	{
		lstrcpy(g_szIconFile, szIcon);
		g_nIconIndex = PathParseIconLocation(g_szIconFile);
	}
	else
		bIconInfo = FALSE;

	// Make the folder readonly
	DWORD dwAttrib = GetFileAttributes(g_szFolder);
	dwAttrib |= FILE_ATTRIBUTE_READONLY;
	SetFileAttributes(g_szFolder, dwAttrib);

	// Creates Desktop.ini (hidden)
	WritePrivateProfileString(_T(".ShellClassInfo"), _T("Infotip"), szText, g_szDesktopIni);
	SetFileAttributes(g_szDesktopIni, FILE_ATTRIBUTE_SYSTEM);

	if (!PathIsRoot(g_szFolder))
	{
		// Inserts icon info in the desktop.ini file
		if (bIconInfo)
		{
			WritePrivateProfileString(_T(".ShellClassInfo"), _T("IconFile"), g_szIconFile, g_szDesktopIni);
			TCHAR temp[10];
			wsprintf(temp, _T("%d"), g_nIconIndex);
			WritePrivateProfileString(_T(".ShellClassInfo"), _T("IconIndex"), temp, g_szDesktopIni);
		}
		else
		{
			// remove icon info (only text info set)
			WritePrivateProfileString(_T(".ShellClassInfo"), _T("IconFile"), NULL, g_szDesktopIni);
			WritePrivateProfileString(_T(".ShellClassInfo"), _T("IconIndex"), NULL, g_szDesktopIni);
		}
	}
	else
	{
		// Inserts icon info in the registry
		if (bIconInfo)
		{
			TCHAR temp[BUFSIZE];
			wsprintf(temp, _T("%s%c\\DefaultIcon"), DRIVEICONS, g_szFolder[0]);
			TCHAR szIconInfo[BUFSIZE];
			wsprintf(szIconInfo, _T("%s,%d"), g_szIconFile, g_nIconIndex);
			SHSetValue(HKEY_LOCAL_MACHINE, temp, _T(""), REG_SZ, (LPVOID) szIconInfo, lstrlen(szIconInfo));
		}
		else
		{
			// Delete icon info from the registry
			TCHAR temp[BUFSIZE];
			wsprintf(temp, _T("%s%c"), DRIVEICONS, g_szFolder[0]);
			SHDeleteKey(HKEY_LOCAL_MACHINE, temp);
		}
	}

	SHChangeNotify(SHCNE_ALLEVENTS, 0, NULL, NULL);
}



/////////////////////////////////////////////////////////////////////////////
// Private members


void CProperty::MeasureItem(LPMEASUREITEMSTRUCT lpmis) 
{ 
	lpmis->itemWidth = 150; 
	lpmis->itemHeight = 20; 
}


void CProperty::DrawMenuItem(LPDRAWITEMSTRUCT lpdis)
{
#define DEFBITMAPSIZE  16
#define BITMAPOFFSET  6
#define ITEMSIZE  40

	USES_CONVERSION;
	
	TCHAR szItem[ITEMSIZE];
	COLORREF crText, crBack;
	HBITMAP hbmItem;

	// if not called by a menu, exit
	if (lpdis->CtlType != ODT_MENU)
		return;

	// retrieve the data associated with the menu item
	lstrcpy(szItem, OLE2T(menuItems[lpdis->itemID-g_idCmdFirst]));	

	// manage how to draw
	if (lpdis->itemAction & (ODA_DRAWENTIRE|ODA_SELECT))
	{
		 int ix, iy; 
		 RECT rt, rtTemp;
		 SIZE size;

		 // select the appropriate text colors
		 if (lpdis->itemState & ODS_SELECTED)
		 {
             if (lpdis->itemState & ODS_GRAYED)
				crText = SetTextColor( lpdis->hDC, RGB(128,128,128) );
			 else
			 	crText = SetTextColor( lpdis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT) );
			 crBack = SetBkColor( lpdis->hDC, GetSysColor(COLOR_HIGHLIGHT) );
		 }

		 
		 // get bitmap bits and paint
		 CopyRect(&rtTemp, &(lpdis->rcItem));

		 hbmItem = (HBITMAP) LoadImage(_Module.m_hInst, 
			 MAKEINTRESOURCE(IDB_NEWFOLDER+(lpdis->itemID-g_idCmdFirst)), IMAGE_BITMAP, 0, 0, 0);
		 if (hbmItem)
		 {
			BITMAP bm;
			GetObject(hbmItem, sizeof(bm), &bm);
			
			ix = lpdis->rcItem.left+BITMAPOFFSET;
			int tempY = lpdis->rcItem.top + ((lpdis->rcItem.bottom-lpdis->rcItem.top)-bm.bmHeight)/2;
 			SetRect(&rt, ix, tempY, ix+DEFBITMAPSIZE, tempY+DEFBITMAPSIZE);
 
			ExtTextOut(lpdis->hDC, 0, 0, ETO_CLIPPED|ETO_OPAQUE, &rtTemp, NULL, 0, (LPINT)NULL);
			 
			COLORREF rgbTrans=RGB(0,255,255);
			rtTemp.left = rt.right;

			HDC hDCTemp = CreateCompatibleDC(lpdis->hDC);
			SelectObject(hDCTemp, hbmItem);
			TransparentBlt(lpdis->hDC, rt.left, rt.top, rt.right-rt.left, rt.bottom-rt.top,
				hDCTemp, 0, 0, bm.bmWidth, bm.bmHeight, rgbTrans);  
			DeleteDC(hDCTemp);
			DeleteObject(hbmItem);
		 }
		 ix = rt.right + GetSystemMetrics(SM_CXFRAME);

		 // draw text (one line centered vertically)
		 GetTextExtentPoint32(lpdis->hDC, szItem, lstrlen(szItem), &size);
		 iy = ((lpdis->rcItem.bottom-lpdis->rcItem.top)-size.cy)/2;
		 iy = lpdis->rcItem.top + (iy>=0 ?iy :0);
		 SetRect(&rt, ix+1, iy, lpdis->rcItem.right, lpdis->rcItem.bottom);
		 ExtTextOut(lpdis->hDC, ix, iy, ETO_CLIPPED|ETO_OPAQUE, &rtTemp, NULL, 0, (LPINT)NULL);
		 if (lpdis->itemState & ODS_GRAYED)
		 {			
			 SetBkMode(lpdis->hDC, TRANSPARENT);
 			 OffsetRect( &rt, 1, 1 );
			 SetTextColor( lpdis->hDC, RGB(255,255,255) );
			 DrawText( lpdis->hDC, szItem, lstrlen(szItem), &rt, DT_LEFT|DT_EXPANDTABS );
			 OffsetRect( &rt, -1, -1 );
			 SetTextColor( lpdis->hDC, RGB(128,128,128) );
			 DrawText( lpdis->hDC, szItem, lstrlen(szItem), &rt, DT_LEFT|DT_EXPANDTABS );			 
		 }
		 else
	 		 DrawText( lpdis->hDC, szItem, lstrlen(szItem), &rt, DT_LEFT|DT_EXPANDTABS );
	 }

	 return;
}
