////////////////////////////////////////////////////////////////
// Microsoft Systems Journal -- December 1999
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably NT too.
//
// ---
// AboutHtml shows how to implement an HTML About Dialog using a
// new class, CHtmlCtrl, that lets you use CHtmlView as a control in a dialog.

#include "StdAfx.h"
#include "resource.h"
#include "HtmlCtrl.h"
#include "TraceWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////
// Ordinary main frame--very boring.
//
class CMainFrame : public CFrameWnd {
public:
	CMainFrame(){ }
	virtual ~CMainFrame() { }
protected:
	CStatusBar	 m_wndStatusBar;
	CToolBar     m_wndToolBar;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	DECLARE_DYNCREATE(CMainFrame)
	DECLARE_MESSAGE_MAP()
};

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.cx = 250;
	cs.cy = 200;
	return TRUE;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this)) {
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	return 0;
}

void CMainFrame::OnPaint()
{
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(&rc);
	dc.DrawText(_T("Check out the About Box, Fred."),
		rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

class CMyApp : public CWinApp {
public:
	CMyApp();
	virtual BOOL InitInstance();
protected:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CMyApp::CMyApp()
{
}

CMyApp theApp;

BOOL CMyApp::InitInstance()
{
   // Create main frame window (don't use doc/view stuff)
   // 
   CMainFrame* pMainFrame = new CMainFrame;
   if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
      return FALSE;
   pMainFrame->ShowWindow(m_nCmdShow);
   pMainFrame->UpdateWindow();
   m_pMainWnd = pMainFrame;

	return TRUE;
}

//////////////////
// Specialized derivation to handle "button" click
//
class CMyHtmlCtrl : public CHtmlCtrl {
	virtual void OnAppCmd(LPCTSTR lpszWhere);
};

/////////////////
// Handle "app:ok" link by closing dialog
//
void CMyHtmlCtrl::OnAppCmd(LPCTSTR lpszWhere)
{
	if (_tcsicmp(lpszWhere,_T("ok"))==0) {
		GetParent()->SendMessage(WM_COMMAND,IDOK);
	}
}

//////////////////
// About dialog uses HTML control to display contents.
//
class CAboutDialog : public CDialog {
	DECLARE_DYNAMIC(CAboutDialog)
protected:
	CMyHtmlCtrl m_page;
	virtual BOOL OnInitDialog(); 
public:
	CAboutDialog() : CDialog(IDD_ABOUTBOX, NULL) { }
};

IMPLEMENT_DYNAMIC(CAboutDialog, CDialog)

BOOL CAboutDialog::OnInitDialog()
{
	VERIFY(CDialog::OnInitDialog());
	VERIFY(m_page.CreateFromStatic(IDC_HTMLVIEW, this));
	m_page.LoadFromResource(_T("about.htm"));
	return TRUE;
}

void CMyApp::OnAppAbout()
{
	static CAboutDialog dlg; // static to remember state of hyperlinks
	dlg.DoModal();				 // run it
}
