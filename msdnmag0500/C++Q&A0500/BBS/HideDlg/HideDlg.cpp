////////////////////////////////////////////////////////////////
// MSDN -- May 2000
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably NT too.
//
#include "stdafx.h"
#include "resource.h"
#include "TraceWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CMainFrame : public CFrameWnd {
protected:
	CString m_sClassName;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	CMainFrame() { }
	~CMainFrame() { }
};

class CMyDlg : public CDialog {
public:
	CMyDlg(CWnd* pParent = NULL);	// standard constructor
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};

class CMyApp : public CWinApp {
public:
	CMyApp();
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};


//////////////////
// pre-create window: set WS_EX_TOOLWINDOW style
//
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (CFrameWnd::PreCreateWindow(cs)) {
		cs.dwExStyle |= WS_EX_TOOLWINDOW;
		return TRUE;
	}
	return FALSE;
}

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CMyApp::CMyApp()
{
}

CMyApp theApp;

//////////////////
// InitInstance: create dialog as child of invisible main frame
//
BOOL CMyApp::InitInstance()
{
	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPED, NULL, NULL);
	CMyDlg dlg(pFrame);
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK) {
	} else if (nResponse == IDCANCEL) {
	}
	return FALSE;
}

class CAboutDlg : public CDialog {
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_HIDEDLG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

//	ModifyStyleEx(WS_EX_APPWINDOW,0);

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL) {
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	} else {
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//
void CMyDlg::OnPaint() 
{
	if (IsIconic()) {
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	} else {
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
// the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
