////////////////////////////////////////////////////////////////
// MSDN -- May 2000
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably NT too.
//
// This file shows the modified cpanel.cpp with CCPApplet::OnLaunch
// that uses the parent window passed from the control panel when it
// sends CPL_DBLCLK
//
#include "StdAfx.h"
#include "CPanel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// To turn on TRACE diagnostics, set this = TRUE
BOOL CControlPanelApp::bTRACE = FALSE;

IMPLEMENT_DYNAMIC(CControlPanelApp, CWinApp)

CControlPanelApp::CControlPanelApp()
{
	CPTRACEFN(_T("CControlPanelApp::CControlPanelApp\n"));
}

CControlPanelApp::~CControlPanelApp()
{
	CPTRACEFN(_T("CControlPanelApp::~CControlPanelApp\n"));

	// delete all the applets
	while (!m_lsApplets.IsEmpty())
		delete STATIC_DOWNCAST(CCPApplet, m_lsApplets.RemoveHead());
}

//////////////////
// Add a new applet to the app. You should call this once for
// each applet your control panel extension supports.
//
BOOL CControlPanelApp::AddApplet(CCPApplet* pApplet)
{
	CPTRACEFN(_T("CControlPanelApp::AddApplet\n"));
	m_lsApplets.AddTail(pApplet);
	pApplet->m_pApp = this;
	return TRUE;
}

#define CPL_FIRST	CPL_INIT
#define CPL_LAST  CPL_STARTWPARMS

///////////////////////////////////////////////////////////////////////////
// CPlApplet: This is the Control Panel callback function that Windows will
// call, the function the control panel calls to do stuff.
// The control panel framework implements most of the functions for you.
// 
LRESULT APIENTRY CPlApplet(HWND hwnd, UINT msg, LPARAM lp1, LPARAM lp2)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#ifdef _DEBUG
	static LPCSTR MsgNames[] = { 
		NULL,
		_T("CPL_INIT"),		
		_T("CPL_GETCOUNT"),	
		_T("CPL_INQUIRE"),	
		_T("CPL_SELECT"),	
		_T("CPL_DBLCLK"),	
		_T("CPL_STOP"),			
		_T("CPL_EXIT"),		
		_T("CPL_NEWINQUIRE"),
		_T("CPL_STARTWPARMS") };
	CPTRACEFN(_T("CPlApplet(%s,%d,%p)\n"),
		CPL_FIRST<=msg && msg<= CPL_LAST ? MsgNames[msg] : _T("(Unknown)"), 
		lp1, lp2);
#endif

	CControlPanelApp* pApp = STATIC_DOWNCAST(CControlPanelApp, AfxGetApp());
	return pApp->OnCplMsg(hwnd, msg, lp1, lp2);
}

//////////////////
// Low-level message handler for all CPL_ messages.
// You can override this to do funky stuff, like overriding CWnd::WndProc.
//
LRESULT CControlPanelApp::OnCplMsg(HWND hwnd, UINT msg, LPARAM lp1, LPARAM lp2)
{
	// Dispatch on message
	if (msg==CPL_INIT)
		return OnInit();
	else if (msg==CPL_GETCOUNT)
		return m_lsApplets.GetCount();
	else if (msg==CPL_EXIT)
		return OnExit();
	else {
		// It must be one of the applet-specific messages. Get applet.
		//
		POSITION pos = m_lsApplets.FindIndex(lp1);
		ASSERT(pos);
		CCPApplet* pApplet = STATIC_DOWNCAST(CCPApplet, m_lsApplets.GetAt(pos));
		ASSERT_VALID(pApplet);

		// Dispatch to appropriate CCPApplet function.
		//
		switch (msg) {
		case CPL_NEWINQUIRE:
			return pApplet->OnNewInquire(* ((NEWCPLINFO*)lp2) );
		case CPL_INQUIRE:
			return pApplet->OnInquire(* ((CPLINFO*)lp2) );
		case CPL_STARTWPARMS:
			pApplet->OnLaunch(CWnd::FromHandle(hwnd), (LPCSTR)lp2);
			return TRUE; // handled
		case CPL_SELECT:
			return pApplet->OnSelect();
		case CPL_DBLCLK:
			return pApplet->OnLaunch(CWnd::FromHandle(hwnd), NULL);
		case CPL_STOP:
			return pApplet->OnStop();
		}
	}
	ASSERT(FALSE);		// shouldn't get here
	return 1;			// failed
}

//////////////////
// Default handler for CPL_INIT checks that there's at least one
// applet registered and that all applets are valid (_DEBUG only).
//
BOOL CControlPanelApp::OnInit()
{
	CPTRACEFN(_T("CControlPanelApp::OnInit\n"));
#ifdef _DEBUG
	POSITION pos = m_lsApplets.GetHeadPosition();
	if (!pos) {
		CPTRACE(_T("*** No applets registered! You forgot to call AddApplet!\n"));
	} else {
		while (pos) {
			CCPApplet* pApplet = STATIC_DOWNCAST(CCPApplet,
				m_lsApplets.GetNext(pos));
			ASSERT_VALID(pApplet);
		}
	}
#endif
	return !m_lsApplets.IsEmpty();
}

//////////////////
// Default handler for CPL_EXIT: do nothing. 
// Override if you need to perform cleanup.
//
LRESULT CControlPanelApp::OnExit()
{
	CPTRACEFN(_T("CControlPanelApp::OnExit\n"));
	return 0; // success
}

////////////////////////////////////////////////////////////////
// CCPApplet
//
IMPLEMENT_DYNAMIC(CCPApplet, CCmdTarget)

CCPApplet::CCPApplet(UINT nIDRes, CRuntimeClass* pDialogClass, BOOL bDynamic)
{
	CPTRACEFN(_T("CCPApplet::CCPApplet\n"));

	ASSERT(pDialogClass == NULL ||
		pDialogClass->IsDerivedFrom(RUNTIME_CLASS(CDialog)) ||
		pDialogClass->IsDerivedFrom(RUNTIME_CLASS(CPropertySheet)));
	m_pDialogClass = pDialogClass;
	m_nIDRes   = nIDRes;
	m_bDynamic = bDynamic;
}

CCPApplet::~CCPApplet()
{
	CPTRACEFN(_T("CCPApplet::~CCPApplet\n"));
}

//////////////////
// Default implementation for CPL_NEWINQUIRE:
// Load up the info struct from resource string.
// Use the CCPApplet itself as the lData item.
//
LRESULT CCPApplet::OnNewInquire(NEWCPLINFO& info) 
{
	CPTRACEFN(_T("CControlPanelApp::OnNewInquire\n"));

	// Fill in the data
	//
	info.dwSize = sizeof(NEWCPLINFO);
	info.dwFlags = 0;
	info.dwHelpContext = 0;
	info.lData = (LONG)this;
	info.hIcon = m_pApp->LoadIcon(m_nIDRes);

	// Load resource string.
	// Format is "Icon Name\nLong Description\nFILENAME.HLP".
	// Use AfxExtractSubString to parse the substrings.
	//
	CString sResource, sName, sDescription, sHelpFile;
	if (sResource.LoadString(m_nIDRes)) {
		AfxExtractSubString(sName,			 sResource, 0);
		AfxExtractSubString(sDescription, sResource, 1);
		AfxExtractSubString(sHelpFile,	 sResource, 2);
	}
	strcpy(info.szName,		sName);
	strcpy(info.szInfo,		sDescription);
	strcpy(info.szHelpFile, sHelpFile);

	return 0; // success
}

//////////////////
// Default implementation for CPL_INQUIRE:
// Load up the info struct from resource string.
// Use the CCPApplet itself as the lData item.
//
LRESULT CCPApplet::OnInquire(CPLINFO& info) 
{
	CPTRACEFN(_T("CControlPanelApp::OnInquire\n"));
#ifdef _WIN32
	if (m_bDynamic)
		return 1; // (failed)

	info.idIcon = m_nIDRes;
	info.idName = m_nIDRes;
	info.idInfo = m_nIDRes;
	info.lData = (LONG)this;
	return 0; // success
#else
	return 1; // fail
#endif
}

//////////////////
// Default hander for CPL_SELECT: do nothing
//
LRESULT CCPApplet::OnSelect() 
{
	CPTRACEFN(_T("CControlPanelApp::OnSelect\n"));
	return 0; // success
}

//////////////////
// Hack to make m_pParentWnd public so I can set it.
//
class CHackPropertySheet : public CPropertySheet {
public:
	void SetParentWnd(CWnd* pw) { m_pParentWnd = pw; }
};

inline void SetParentWindow(CPropertySheet* ps, CWnd* pw)
{
	((CHackPropertySheet*)ps)->SetParentWnd(pw);
}

class CHackDialog : public CDialog {
public:
	void SetParentWnd(CWnd* pw) { m_pParentWnd = pw; }
};

inline void SetParentWindow(CDialog* pd, CWnd* pw)
{
	((CHackDialog*)pd)->SetParentWnd(pw);
}

//////////////////
// User double-clicked an icon: launch the applet.
//
LRESULT CCPApplet::OnLaunch(CWnd* pWndCpl, LPCSTR lpCmdLine)
{
	TRACE(_T("CCPApplet::OnLaunch, parent=0x%04x\n"),pWndCpl->GetSafeHwnd());
	CWnd* pw = (CWnd*)m_pDialogClass->CreateObject();
	if (pw) {
		if (pw->IsKindOf(RUNTIME_CLASS(CPropertySheet))) {
			CPropertySheet* ps = (CPropertySheet*)pw;
			SetParentWindow(ps, pWndCpl);	 // use control panel window as parent
			ps->SetActivePage(lpCmdLine ? atoi(lpCmdLine) : 0);
			ps->DoModal();
		} else if (pw->IsKindOf(RUNTIME_CLASS(CDialog))) {
			CDialog* pd = (CDialog*)pw;
			SetParentWindow(pd, pWndCpl);	 // use control panel window as parent
			pd->DoModal();
		}
	}
	return pw==NULL;
}

//////////////////
// Default hander for CPL_STOP: do nothing
//
LRESULT CCPApplet::OnStop() 
{
	CPTRACEFN(_T("CControlPanelApp::OnStop\n"));
	return 0; // success
}
