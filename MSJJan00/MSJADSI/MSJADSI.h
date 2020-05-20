/////////////////////////////////////////////////////////////////////////
// MSJ ADSI MFC Dialog Project
//
// Shows ADSI examples based upon the article enclosed.
//
// ©1999, Shawn Wildermuth
/////////////////////////////////////////////////////////////////////////
// MSJADSI.h : main header file for the MSJADSI application
//

#if !defined(AFX_MSJADSI_H__DA970199_EF49_4DD0_8F03_30AA49091FAC__INCLUDED_)
#define AFX_MSJADSI_H__DA970199_EF49_4DD0_8F03_30AA49091FAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMSJADSIApp:
// See MSJADSI.cpp for the implementation of this class
//

class CMSJADSIApp : public CWinApp
{
public:
	CMSJADSIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSJADSIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMSJADSIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSJADSI_H__DA970199_EF49_4DD0_8F03_30AA49091FAC__INCLUDED_)
