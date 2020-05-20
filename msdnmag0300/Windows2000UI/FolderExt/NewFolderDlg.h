// NewFolderDlg.h : Declaration of the CNewFolderDlg

#ifndef __NEWFOLDERDLG_H_
#define __NEWFOLDERDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include <ImageHLP.h>

#pragma comment(lib, "imageHLP.lib")


/////////////////////////////////////////////////////////////////////////////
// CNewFolderDlg
class CNewFolderDlg : 
	public CAxDialogImpl<CNewFolderDlg>
{
public:
	CNewFolderDlg()
	{
	}

	~CNewFolderDlg()
	{
	}

	enum { IDD = IDD_NEWFOLDERDLG };
	TCHAR m_szParentFolder[MAX_PATH];

BEGIN_MSG_MAP(CNewFolderDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (!lstrlen(m_szParentFolder))
		{
			MessageBox(_T("Not a file system folder"),
				_T("Warning!"), MB_OK|MB_ICONEXCLAMATION);
			return 0;
		}

		SetDlgItemText(IDC_CURFOLDER, m_szParentFolder);
		SetDlgItemText(IDC_NEWFOLDER, _T("New Folder"));
		PathAddBackslash(m_szParentFolder);
		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		TCHAR szNewFolder[MAX_PATH];
		TCHAR szBuf[MAX_PATH];
		GetDlgItemText(IDC_NEWFOLDER, szNewFolder, MAX_PATH);
		wsprintf(szBuf, _T("%s%s"), m_szParentFolder, szNewFolder);
		
		// Make sure there's a final backslash...
		PathAddBackslash(szBuf);
		MakeSureDirectoryPathExists((LPCSTR)szBuf);

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__NEWFOLDERDLG_H_
