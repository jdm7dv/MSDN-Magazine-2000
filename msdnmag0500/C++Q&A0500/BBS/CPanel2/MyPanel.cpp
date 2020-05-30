////////////////////////////////////////////////////////////////
// Microsoft Systems Journal -- November 1999
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably NT too.
//
// ---
// MyPanel shows how to implement a control panel extension in MFC
// using the control panel mini-framework (CControlPanelApp and CCPApplet).
// The framework is implemented in cpanel.cpp and cpanel.h.
//
// This file implements two applets: one dialog and one property sheet.
// 
#include "StdAfx.h"
#include "CPanel.h"
#include "resource.h"
#include "StatLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////
// My control panel app
//
class CMyControlPanelApp : public CControlPanelApp {
public:
	virtual BOOL OnInit();
	DECLARE_DYNAMIC(CMyControlPanelApp)
} theApp;

// this widget turns on tracing before all static constructors are called
struct CInitTracing {
	CInitTracing() { 	CControlPanelApp::bTRACE=TRUE; }
} foo;

////////////////////////////////////////////////////////////////
// Dialog ("Market Meltdown")
//
class CMyDialog : public CDialog {
protected:
	CStaticLink	m_wndLink1;
	CStaticLink	m_wndLink2;
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy() { delete this; }
public:
	CMyDialog() : CDialog(IDR_MYAPPLET1) { }
	DECLARE_DYNCREATE(CMyDialog);
};
IMPLEMENT_DYNCREATE(CMyDialog, CDialog);

BOOL CMyDialog::OnInitDialog()
{
	// subclass static controls. URL is static text or 3rd arg
	m_wndLink1.SubclassDlgItem(IDC_MSJURL, this);
	m_wndLink2.SubclassDlgItem(IDC_PDURL,  this);
	return CDialog::OnInitDialog();
}

////////////////////////////////////////////////////////////////
// Property sheet ("intergalactic settings")
//

class CMyPropPage : public CPropertyPage {
protected:
	CStaticLink	m_wndLink1;
	CStaticLink	m_wndLink2;
	virtual BOOL OnInitDialog();
	DECLARE_DYNAMIC(CMyPropPage);
};
IMPLEMENT_DYNAMIC(CMyPropPage, CPropertyPage);

//////////////////
// Initialize: subclass web links if on this page.
//
BOOL CMyPropPage::OnInitDialog()
{
	if (GetDlgItem(IDC_MSJURL)) {
		m_wndLink1.SubclassDlgItem(IDC_MSJURL, this);
		m_wndLink2.SubclassDlgItem(IDC_PDURL,  this);
	}
	return CPropertyPage::OnInitDialog();
}

//////////////////
// Custom prop sheet has 5 pages.
//
class CMyPropSheet : public CPropertySheet {
public:
	CMyPropSheet();
protected:
	enum {NPAGES=5};
	CMyPropPage m_mypages[NPAGES];
	virtual void PostNcDestroy() { delete this; }
	DECLARE_DYNCREATE(CMyPropSheet);
};
IMPLEMENT_DYNCREATE(CMyPropSheet, CPropertySheet);

//////////////////
// Construct: set icon and add all the pages.
//
CMyPropSheet::CMyPropSheet() : CPropertySheet(IDS_MYPROPSHEETCAPTION)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW | PSH_USEHICON;
	m_psh.hIcon = AfxGetApp()->LoadIcon(IDR_MYAPPLET3);
	for (int i=0; i<NPAGES; i++) {
		m_mypages[i].Construct(IDD_PAGE1+i);
		AddPage(&m_mypages[i]);
	}
}

////////////////////////////////////////////////////////////////
// application object

IMPLEMENT_DYNAMIC(CMyControlPanelApp, CControlPanelApp)

//////////////////
// Control panel initialization similar to InitInstance. The only thing
// required is that you add at least one CCPApplet.
//
BOOL CMyControlPanelApp::OnInit()
{
	CPTRACEFN(_T("CMyControlPanelApp::OnInit\n"));

	// NOTE: I use third arg (bDynamic) = TRUE for testing, so control panel
	// uses CPL_NEWINQUIRE instead of CPL_INQUIRE. For production code, you
	// should change to FALSE (default)
	//
	AddApplet(new CCPApplet(IDR_MYAPPLET1, RUNTIME_CLASS(CMyDialog), TRUE));
	AddApplet(new CCPApplet(IDR_MYAPPLET3, RUNTIME_CLASS(CMyPropSheet),TRUE));
	return CControlPanelApp::OnInit();
}

