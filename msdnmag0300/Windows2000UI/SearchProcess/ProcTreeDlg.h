// ProcTreeDlg.h : Declaration of the CProcTreeDlg

#ifndef __PROCTREEDLG_H_
#define __PROCTREEDLG_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CProcTreeDlg
class CProcTreeDlg : 
	public CDialogImpl<CProcTreeDlg>
{
public:
	CProcTreeDlg();
	~CProcTreeDlg();

	enum { IDD = IDD_PROCTREEDLG };

BEGIN_MSG_MAP(CProcTreeDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnRefresh)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnRefresh(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

private:
	VOID DoRefresh(VOID);
};

#endif //__PROCTREEDLG_H_
