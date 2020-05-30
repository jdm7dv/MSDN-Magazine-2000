////////////////////////////////////////////////////////////////
// Microsoft Systems Journal -- November 1999
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably NT too.
//
#ifndef _CPANEL_H_
#define _CPANEL_H_

#include "Debug.h"

class CControlPanelApp;

//////////////////
// This class represents one applet within a control panel extension.
// Usually, there's only one. If your control panel extension implements
// more than one applet, then you should use one of these for each applet.
//
class CCPApplet : public CCmdTarget {
public:
	CCPApplet(UINT nIDRes, CRuntimeClass* pDialogClass, BOOL bDynamic=FALSE);
	virtual ~CCPApplet();

protected:
	CControlPanelApp* m_pApp;			// back ptr to owning app
	CRuntimeClass*	m_pDialogClass;	// dialog class
	BOOL				m_bDynamic;			// update icon every time CPL starts?
	UINT				m_nIDRes;			// resource ID for this applet

	friend class CControlPanelApp;	// OK for control panel to access me

	// To implement your applet, override these virtual functions.
	// The only really important one is OnLaunch. 
	//
	virtual LRESULT OnLaunch(CWnd* pWndCpl, LPCSTR lpCmdLine); 
	virtual LRESULT OnInquire(CPLINFO& info);			// CPL_INQUIRE
	virtual LRESULT OnNewInquire(NEWCPLINFO& info);	// CPL_NEWINQUIRE
	virtual LRESULT OnSelect();							// CPL_SELECT
	virtual LRESULT OnStop();								// CPL_STOP
	DECLARE_DYNAMIC(CCPApplet);
};

//////////////////
// To imlement a control panel application (DLL), derive your
// app class from this and override virtual functions if you need to.
//
class CControlPanelApp : public CWinApp {
	DECLARE_DYNAMIC(CControlPanelApp)
	static BOOL bTRACE;						 // show TRACE diagnostics

protected:
	CObList m_lsApplets;						 // list of applets

	CControlPanelApp();
	virtual ~CControlPanelApp();

	BOOL AddApplet(CCPApplet* pApplet);

	// OK for control panel callback to access me
	friend LRESULT APIENTRY CPlApplet(HWND, UINT, LPARAM, LPARAM);

	// Control panel message handlers.
	// Override these to implement your own control panel extension.
	//
	virtual LRESULT OnCplMsg(HWND hwnd, UINT msg, LPARAM lp1, LPARAM lp2);
	virtual BOOL	 OnInit();	// CPL_INIT
	virtual LRESULT OnExit();	// CPL_EXIT
};

#ifdef _DEBUG

#define CPTRACEFN				\
	CTraceFn __fooble;		\
	if (CControlPanelApp::bTRACE)	\
		TRACE						
#define CPTRACE				\
	if (CControlPanelApp::bTRACE)	\
		TRACE

#else // not _DEBUG

#define CPTRACEFN
#define CPTRACE

#endif // _DEBUG

#endif // _CPANEL_H_
