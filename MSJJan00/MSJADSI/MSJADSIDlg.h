/////////////////////////////////////////////////////////////////////////
// MSJ ADSI MFC Dialog Project
//
// Shows ADSI examples based upon the article enclosed.
//
// ©1999, Shawn Wildermuth
/////////////////////////////////////////////////////////////////////////
// MSJADSIDlg.h : header file
//

#if !defined(AFX_MSJADSIDLG_H__9DDA89E4_9EC8_4587_8789_0BCE0CF53F9C__INCLUDED_)
#define AFX_MSJADSIDLG_H__9DDA89E4_9EC8_4587_8789_0BCE0CF53F9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <activeds.h>	// ADSI 2.5 SDK
#include <comdef.h>		// _com_ptr_t, et al

/////////////////////////////////////////////////////////////////////////////
// CMSJADSIDlg dialog

class CMSJADSIDlg : public CDialog
{
// Construction
public:
	CMSJADSIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMSJADSIDlg)
	enum { IDD = IDD_MSJADSI_DIALOG };
	CListBox	m_lbStatus;
	CString	m_csSearchCriteria;
	CString	m_csADServer;
	CString	m_csPassword;
	CString	m_csUsername;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSJADSIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ShowHierarchy(IADsContainer* pContainer);
	void AddToLog(CString csLog);
	
	HRESULT AddDocRepo(IDirectoryObject* pDirObject);
	HRESULT AddPublishers(IDirectoryObject* pDirObject);
	HRESULT AddPublications(IDirectoryObject* pDirObject);
	HRESULT AddVolumes(IDirectoryObject* pDirObject);
	HRESULT AddIssues(IDirectoryObject* pDirObject);
	HRESULT AddArticles(IDirectoryObject* pDirObject);

	
	HICON m_hIcon;
	IADsContainer*	m_pContainer;

	// Generated message map functions
	//{{AFX_MSG(CMSJADSIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnCreateobjects();
	afx_msg void OnBtnSearch();
	afx_msg void OnBtnShowobjects();
	afx_msg void OnBtnOpencontainer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSJADSIDLG_H__9DDA89E4_9EC8_4587_8789_0BCE0CF53F9C__INCLUDED_)
