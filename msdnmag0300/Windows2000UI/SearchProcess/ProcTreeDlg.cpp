// ProcTreeDlg.cpp : Implementation of CProcTreeDlg
#include "stdafx.h"
#include "ProcTreeDlg.h"
#include "EnumProc.h"

/////////////////////////////////////////////////////////////////////////////
// CProcTreeDlg

CProcTreeDlg::CProcTreeDlg()
{
}

CProcTreeDlg::~CProcTreeDlg()
{
}

LRESULT CProcTreeDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// set the icons
	HICON hIconLg = (HICON) LoadImage( _Module.m_hInst, 
		MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 32, 32, 0 );
	HICON hIconSm = (HICON) LoadImage( _Module.m_hInst, 
		MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 16, 16, 0 );

	SendMessage( WM_SETICON, TRUE, (LPARAM) hIconLg );
	SendMessage( WM_SETICON, FALSE, (LPARAM) hIconSm );

	// current time
	DoRefresh();

	// operating system
	OSVERSIONINFO osv;
    DWORD dwPlatformId;
    osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osv);
    dwPlatformId = osv.dwPlatformId;
	TCHAR szBuf[100];
    if(dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
		wsprintf(szBuf, _T("Windows %d.%d"), osv.dwMajorVersion, osv.dwMinorVersion);
	else
		wsprintf(szBuf, _T("Windows NT %d.%d"), osv.dwMajorVersion, osv.dwMinorVersion);

	TCHAR szTitle[200];
	GetWindowText(szTitle, 200);
	wsprintf(szTitle, _T("%s - %s"), szTitle, szBuf);
	SetWindowText(szTitle);
	return 1;  
}


LRESULT CProcTreeDlg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT CProcTreeDlg::OnRefresh(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DoRefresh();
	return 0;
}


VOID CProcTreeDlg::DoRefresh(VOID)
{
	// updates time
	CHAR szTime[50], szMsg[100];
	GetTimeFormat( LOCALE_SYSTEM_DEFAULT, 0, NULL, 
			 NULL, szTime, 50 );
	wsprintf( szMsg, "Snapshot taken at %s", szTime );
	SetDlgItemText( IDC_SNAPSHOT, szMsg );

	// updates the treeview
	HWND hwndTree = (HWND) GetDlgItem(IDC_TREEVIEW);
	UINT nCount = EnumProcessToTreeView( hwndTree );
	wsprintf( szMsg, "%d processes running.", nCount );
	SetDlgItemText( IDC_RUNNING, szMsg );

}

