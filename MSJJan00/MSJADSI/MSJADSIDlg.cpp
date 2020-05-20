/////////////////////////////////////////////////////////////////////////
// MSJ ADSI MFC Dialog Project
//
// Shows ADSI examples based upon the article enclosed.
//
// ©1999, Shawn Wildermuth
/////////////////////////////////////////////////////////////////////////
// MSJADSIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MSJADSI.h"
#include "MSJADSIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSJADSIDlg dialog

CMSJADSIDlg::CMSJADSIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMSJADSIDlg::IDD, pParent), m_pContainer(NULL)
{
	//{{AFX_DATA_INIT(CMSJADSIDlg)
	m_csSearchCriteria = _T("(&(objectClass=mSJ-DRArticle)(cn=Intel Chips))");
	m_csADServer = _T("twain.local");
	m_csPassword = _T("nopassword");
	m_csUsername = _T("Directory Manager");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMSJADSIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMSJADSIDlg)
	DDX_Control(pDX, IDC_STATUS, m_lbStatus);
	DDX_Text(pDX, IDC_EDIT_ADSEARCH, m_csSearchCriteria);
	DDX_Text(pDX, IDC_EDIT_ADSERVER, m_csADServer);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_USER, m_csUsername);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMSJADSIDlg, CDialog)
	//{{AFX_MSG_MAP(CMSJADSIDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_CREATEOBJECTS, OnBtnCreateobjects)
	ON_BN_CLICKED(ID_BTN_SEARCH, OnBtnSearch)
	ON_BN_CLICKED(ID_BTN_SHOWOBJECTS, OnBtnShowobjects)
	ON_BN_CLICKED(ID_BTN_OPENCONTAINER, OnBtnOpencontainer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSJADSIDlg message handlers

BOOL CMSJADSIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMSJADSIDlg::OnPaint() 
{
	if (IsIconic())
	{
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
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMSJADSIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMSJADSIDlg::AddToLog(CString csLog)
{
	m_lbStatus.AddString(csLog);
	m_lbStatus.ScrollWindow(0, 100);
	m_lbStatus.Invalidate();
	m_lbStatus.UpdateWindow();
}

/////////////////////////////////////////////////////////////////////////
// Example of how to create an authenticated 
// connection to an LDAP Server
/////////////////////////////////////////////////////////////////////////
void CMSJADSIDlg::OnBtnOpencontainer() 
{
	UpdateData();
	
	// Check for username password
	if (m_csUsername.IsEmpty() || m_csPassword.IsEmpty()) 
	{
		AddToLog("No Username and password for authentication");
		return;
	}

	// Open the Connection with Authentication
	CString csTemp = "LDAP://";
	csTemp += m_csADServer;
	HRESULT hr = ADsOpenObject(	csTemp.AllocSysString(), 
								m_csUsername.AllocSysString(), 
								m_csPassword.AllocSysString(), 
								0,	
								IID_IADsContainer, 
								(void**) &m_pContainer);


	// Validate the server connection
	if (FAILED(hr)) 
	{
		csTemp.Format("Failed to open connection with Server, Code: 0x%x", hr);
		AddToLog(csTemp);
	}
	else
	{
		// Add to Log
		AddToLog("Opened LDAP Server Connection");
	}
}

/////////////////////////////////////////////////////////////////////////
// Example of how to create objects within the Active Directory 
/////////////////////////////////////////////////////////////////////////
void CMSJADSIDlg::OnBtnCreateobjects() 
{
	// Validate Connection
	if (!m_pContainer) 
	{
		AddToLog("Container not open, Please Open Container First");
		return;
	}

	// Get a IDirectoryObject 
	IDirectoryObject* pDirObject = NULL;
	HRESULT hr; 
	hr = m_pContainer->QueryInterface(	IID_IDirectoryObject, 
										(void**) &pDirObject );
 
	// Create Objects
	if (SUCCEEDED(AddDocRepo(pDirObject))) 
	{
		AddToLog("Added All Objects Successfully");
	}
	
	
	// Release the IDirectoryObject
	pDirObject->Release();	

}

HRESULT CMSJADSIDlg::AddDocRepo(IDirectoryObject *pDirObject)
{
	HRESULT hr;
	ADSVALUE   classValue;
	LPDISPATCH pDisp = NULL;
	CString csTemp;
	
	// Setup the DocRepo Object (Root Object of our Hierarchy)
	ADS_ATTR_INFO  attrInfo[] = 
	{  
	   { L"objectClass", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &classValue, 1 }
	};
	DWORD dwAttrs = sizeof(attrInfo)/sizeof(ADS_ATTR_INFO); 
 
	// Set the Attribute Values
	classValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	classValue.CaseIgnoreString = L"container";
 
	// Create the Object
   hr = pDirObject->CreateDSObject( L"CN=DocRepo",  
									attrInfo, 
									dwAttrs, 
									&pDisp );
	if (SUCCEEDED(hr)) 
	{
		AddToLog("Added DocRepo Object");
		IDirectoryObject* pDocObj = NULL;
		hr = pDisp->QueryInterface(IID_IDirectoryObject, (void**) &pDocObj);
		pDisp->Release();
		if (SUCCEEDED(hr)) hr = AddPublishers(pDocObj);
		pDocObj->Release();
	}
	else
	{
		csTemp.Format("Failed to Add DocRepo Object, Code: 0x%x",hr);
		AddToLog(csTemp);
	}

	return hr;
}

HRESULT CMSJADSIDlg::AddPublishers(IDirectoryObject* pDirObject)
{
	HRESULT hr;
	ADSVALUE   classValue;
	ADSVALUE   descriptionValue;
	LPDISPATCH pDisp = NULL;
	CString csTemp;
	
	// Setup the Publisher 
	ADS_ATTR_INFO  attrInfo[] = 
	{  
	   { L"objectClass", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &classValue, 1 },
	   { L"description", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &descriptionValue, 1 }
	};
	DWORD dwAttrs = sizeof(attrInfo)/sizeof(ADS_ATTR_INFO); 
 
	// Set the Attribute Values
	classValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	classValue.CaseIgnoreString = L"mSJ-DRPublisher";
	descriptionValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	descriptionValue.CaseIgnoreString = L"TwainPress Ltd.";
 
 
	// Create the Twain Press Object
	hr = pDirObject->CreateDSObject(	L"OU=TwainPress",  
										attrInfo, 
										dwAttrs, 
										&pDisp );
	if (SUCCEEDED(hr)) 
	{
		AddToLog("Added TwainPress Publisher Object");
		IDirectoryObject* pPublisher = NULL;
		hr = pDisp->QueryInterface(IID_IDirectoryObject, (void**) &pPublisher);
		pDisp->Release();
		if (SUCCEEDED(hr)) hr = AddPublications(pPublisher);
		pPublisher->Release();
	}
	else
	{
		csTemp.Format("Failed to Add Publishers Object, Code: 0x%x",hr);
		AddToLog(csTemp);
	}

	return hr;

}

HRESULT CMSJADSIDlg::AddPublications(IDirectoryObject *pDirObject)
{
	HRESULT hr;
	ADSVALUE   classValue;
	ADSVALUE   descriptionValue;
	ADSVALUE   pubIntValue;
	ADSVALUE   isPeriodValue;
	LPDISPATCH pDisp = NULL;
	CString csTemp;
	
	// Setup the Publisher 
	ADS_ATTR_INFO  attrInfo[] = 
	{  
	   { L"objectClass", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &classValue, 1},
	   { L"description", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &descriptionValue, 1},
	   { L"mSJ-DRPublishedInterval", ADS_ATTR_UPDATE, 
						ADSTYPE_INTEGER, &pubIntValue, 1 },
	   { L"mSJ-DRIsPeriodical", ADS_ATTR_UPDATE, 
						ADSTYPE_BOOLEAN, &isPeriodValue, 1 }
	};
	DWORD dwAttrs = sizeof(attrInfo)/sizeof(ADS_ATTR_INFO); 
 
	// Set the Attribute Values
	classValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	classValue.CaseIgnoreString = L"mSJ-DRPublication";
	descriptionValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	descriptionValue.CaseIgnoreString = L"Better Chips and Cards";
	pubIntValue.dwType = ADSTYPE_INTEGER;
	pubIntValue.Integer = 4;
	isPeriodValue.dwType = ADSTYPE_BOOLEAN;
	isPeriodValue.Boolean = TRUE;
 
 
	// Create the Publication Object
	hr = pDirObject->CreateDSObject(	L"cn=Better Chips and Cards",  
										attrInfo, 
										dwAttrs, 
										&pDisp );
	if (SUCCEEDED(hr)) 
	{
		AddToLog("Added Better Chips and Cards Object");
		IDirectoryObject* pPublication = NULL;
		hr = pDisp->QueryInterface( IID_IDirectoryObject, 
                                    (void**) &pPublication);
		pDisp->Release();
		if (SUCCEEDED(hr)) hr = AddVolumes(pPublication);
		pPublication->Release();
	}
	else
	{
		csTemp.Format("Failed to Add Publication Object, Code: 0x%x",hr);
		AddToLog(csTemp);
	}

	return hr;
}

HRESULT CMSJADSIDlg::AddVolumes(IDirectoryObject* pDirObject)
{
	HRESULT hr;
	ADSVALUE   classValue;
	ADSVALUE   descriptionValue;
	LPDISPATCH pDisp = NULL;
	CString csTemp;
	
	// Setup the Publisher 
	ADS_ATTR_INFO  attrInfo[] = 
	{  
	   { L"objectClass", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &classValue, 1 },
	   { L"description", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &descriptionValue, 1}
	};
	DWORD dwAttrs = sizeof(attrInfo)/sizeof(ADS_ATTR_INFO); 
 
	// Set the Attribute Values
	classValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	classValue.CaseIgnoreString = L"mSJ-DRVolume";
	descriptionValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	descriptionValue.CaseIgnoreString = L"Volume 1";
 
 
	// Create the Volume Object
	hr = pDirObject->CreateDSObject(	L"cn=Vol.1",  
										attrInfo, 
										dwAttrs, 
										&pDisp );
	if (SUCCEEDED(hr)) 
	{
		AddToLog("Added Volume 1 Object");
		IDirectoryObject* pVolume = NULL;
		hr = pDisp->QueryInterface( IID_IDirectoryObject, 
                                    (void**) &pVolume);
		pDisp->Release();
		if (SUCCEEDED(hr)) hr = AddIssues(pVolume);
		pVolume->Release();
	}
	else
	{
		csTemp.Format("Failed to Add Volume Object, Code: 0x%x",hr);
		AddToLog(csTemp);
	}

	return hr;
}

HRESULT CMSJADSIDlg::AddIssues(IDirectoryObject* pDirObject)
{
	HRESULT hr;
	ADSVALUE   classValue;
	ADSVALUE   descriptionValue;
	LPDISPATCH pDisp = NULL;
	CString csTemp;
	
	// Setup the Publisher 
	ADS_ATTR_INFO  attrInfo[] = 
	{  
	   { L"objectClass", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &classValue, 1},
	   { L"description", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &descriptionValue, 1}
	};
	DWORD dwAttrs = sizeof(attrInfo)/sizeof(ADS_ATTR_INFO); 
 
	// Set the Attribute Values
	classValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	classValue.CaseIgnoreString = L"mSJ-DRIssue";
	descriptionValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	descriptionValue.CaseIgnoreString = L"Issue 4";
 
 
	// Create the Issue Object
	hr = pDirObject->CreateDSObject(	L"cn=Issue 4",  
										attrInfo, 
										dwAttrs, 
										&pDisp );
	if (SUCCEEDED(hr)) 
	{
		AddToLog("Added Issue 4 Object");
		IDirectoryObject* pIssue = NULL;
		hr = pDisp->QueryInterface(IID_IDirectoryObject, (void**) &pIssue);
		pDisp->Release();
		if (SUCCEEDED(hr)) hr = AddArticles(pIssue);
		pIssue->Release();
	}
	else
	{
		csTemp.Format("Failed to Add Issue Object, Code: 0x%x",hr);
		AddToLog(csTemp);
	}

	return hr;
}

HRESULT CMSJADSIDlg::AddArticles(IDirectoryObject* pDirObject)
{
	HRESULT hr;
	ADSVALUE   classValue;
	ADSVALUE   descriptionValue;
	ADSVALUE   abstractURLValue;
	ADSVALUE   URLValue;
	ADSVALUE   StartPageValue;
	ADSVALUE   EndPageValue;
	ADSVALUE   AuthorsValue;
	LPDISPATCH pDisp = NULL;
	CString csTemp;
	
	// Setup the Publisher 
	ADS_ATTR_INFO  attrInfo[] = 
	{  
	   { L"objectClass", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &classValue, 1 },
	   { L"description", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &descriptionValue, 1},
	   { L"mSJ-DRAbstractURL", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &abstractURLValue, 1},
	   { L"url", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &URLValue, 1 },
	   { L"mSJ-DRStartPageNumber", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &StartPageValue, 1 },
	   { L"mSJ-DREndPageNumber", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &EndPageValue, 1 },
	   { L"mSJ-DRAuthors", ADS_ATTR_UPDATE, 
						ADSTYPE_CASE_IGNORE_STRING, &AuthorsValue, 1 }
	};
	DWORD dwAttrs = sizeof(attrInfo)/sizeof(ADS_ATTR_INFO); 
 
	// Set the Attribute Values
	classValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	classValue.CaseIgnoreString = L"mSJ-DRArticle";
	descriptionValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	descriptionValue.CaseIgnoreString = L"Voodoo 3 Graphics Chips";
	abstractURLValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	abstractURLValue.CaseIgnoreString = 
                        L"http://twain.com/abstracts/voodoo.html";
	URLValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	URLValue.CaseIgnoreString = L"http://twain.com/voodoo.html";
	StartPageValue.dwType = ADSTYPE_INTEGER;
	StartPageValue.Integer = 15;
	EndPageValue.dwType = ADSTYPE_INTEGER;
	EndPageValue.Integer = 25;
	AuthorsValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	AuthorsValue.CaseIgnoreString = L"John P. Normal";
 
	// Create the First Article Object
	hr = pDirObject->CreateDSObject(	L"cn=Voodoo 3 Chips",  
										attrInfo, 
										dwAttrs, 
										&pDisp );
	if (SUCCEEDED(hr)) 
	{
		AddToLog("Added First Article Object");
		pDisp->Release();
	}
	else
	{
		csTemp.Format(  "Failed to Add First Article Object, Code: 0x%x",
                        hr);
		AddToLog(csTemp);
	}

	// Create the Second Article Object
	classValue.CaseIgnoreString = L"mSJ-DRArticle";
	descriptionValue.CaseIgnoreString = L"Intel's Motherboard Chips";
	abstractURLValue.CaseIgnoreString = 
                            L"http://twain.com/abstracts/intel.html";
	URLValue.CaseIgnoreString = L"http://twain.com/intel.html";
	StartPageValue.Integer = 30;
	EndPageValue.Integer = 35;
	AuthorsValue.CaseIgnoreString = L"Sam R. Phillips";
	hr = pDirObject->CreateDSObject(	L"cn=Intel Chips",  
										attrInfo, 
										dwAttrs, 
										&pDisp );
	if (SUCCEEDED(hr)) 
	{
		AddToLog("Added Second Article Object");
		pDisp->Release();
	}
	else
	{
		csTemp.Format(  "Failed to Add Second Article Object, Code: 0x%x", 
                        hr);
		AddToLog(csTemp);
	}

	// Create the Third Article Object
	classValue.CaseIgnoreString = L"mSJ-DRArticle";
	descriptionValue.CaseIgnoreString = L"Lay's Baked Ruffles";
	abstractURLValue.CaseIgnoreString = 
                    L"http://twain.com/abstracts/potato.html";
	URLValue.CaseIgnoreString = L"http://twain.com/potato.html";
	StartPageValue.Integer = 42;
	EndPageValue.Integer = 60;
	AuthorsValue.CaseIgnoreString = L"Couch A. Potato-Chip";
	hr = pDirObject->CreateDSObject(	L"cn=Lays Baked Ruffles",  
										attrInfo, 
										dwAttrs, 
										&pDisp );
	if (SUCCEEDED(hr)) 
	{
		AddToLog("Added Third Article Object");
		pDisp->Release();
	}
	else
	{
		csTemp.Format("Failed to Add Third Article Object, Code: 0x%x",hr);
		AddToLog(csTemp);
	}

	return hr;
}

/////////////////////////////////////////////////////////////////////////
// Example of how to iterate through the objects created in the above
// example of creating new objects
/////////////////////////////////////////////////////////////////////////
void CMSJADSIDlg::OnBtnShowobjects() 
{
	HRESULT hr;
    IADsContainer* pContainer = NULL;
    IADs* pAD = NULL;
    IDispatch* pDisp = NULL;
    
    // Validate Connection
	if (!m_pContainer) 
	{
		AddToLog("Container not open, Please Open Container First");
		return;
	}

    // Get the Root Container
    hr = m_pContainer->GetObject(   L"container", 
                                    L"CN=DocRepo",
                                    &pDisp);
    if (FAILED(hr))
    {
        AddToLog("Failed to Get the Container Object, please restart!");
        return;
    }
    hr = pDisp->QueryInterface( IID_IADsContainer, (void**) &pContainer );
    hr = pDisp->QueryInterface (IID_IADs, (void**) &pAD);
    pDisp->Release(); 

    // Show the Hierarchy Below the the Container (Recursive Function)
    BSTR bstrName;
    _variant_t varDesc;
    pAD->get_Name(&bstrName);
    pAD->Get(L"description", &varDesc);
    if (varDesc.vt == VT_BSTR)
    {
        AddToLog(CString(bstrName) + " : " + varDesc.bstrVal );
    } 
    else
    {
        AddToLog(CString(bstrName));
    }
    SysFreeString(bstrName);
    pAD->Release();
    ShowHierarchy(pContainer);
     
}

// Recursive Function to Dump all Objects to the Log
void CMSJADSIDlg::ShowHierarchy(IADsContainer *pContainer)
{
    static short    nIndent = 0;
    IEnumVARIANT*   pEnum;
    LPUNKNOWN       pUnk;
    IDispatch*      pDisp;
    ULONG           lFetch;
    IADs*           pAD;
    IADsContainer*  pNewContainer;
    BSTR            bstrName, bstrSchema;
    _variant_t      var, varDesc;

    // Start Indenting
    nIndent += 2;

    // Create Indention
    CString csIndent;
    for (int x = 0; x < nIndent; x++) csIndent += " ";
    
    // Get the Enumeration Interface
    pContainer->get__NewEnum(&pUnk);
    pUnk->QueryInterface(IID_IEnumVARIANT, (void**) &pEnum);
    pUnk->Release();
    // Now Enumerate 
    HRESULT hr = pEnum->Next(1, &var, &lFetch);
    while(hr == S_OK)
    {
        if (lFetch == 1)
        {
            pDisp = V_DISPATCH(&var);
            pDisp->QueryInterface(IID_IADs, (void**)&pAD); 
            pAD->get_Name(&bstrName);
            pAD->Get(L"description", &varDesc);
            if (varDesc.vt == VT_BSTR)
            {
                AddToLog(csIndent + bstrName + " : " + varDesc.bstrVal );
            } 
            else
            {
                AddToLog(CString(bstrName));
            }
            SysFreeString(bstrName);
            // Recurse if Necessary
            pAD->get_Schema(&bstrSchema);
            IADsClass* pCls;
            ADsGetObject(bstrSchema, IID_IADsClass, (void**)&pCls);
            SysFreeString(bstrSchema);
            VARIANT_BOOL isContainer;
            pCls->get_Container(&isContainer);
            if(isContainer) 
            {
                pAD->QueryInterface(IID_IADsContainer, (void**) &pNewContainer);
                ShowHierarchy(pNewContainer);                   
                pNewContainer->Release();
            }
            pCls->Release();            
            // Release the Object
            pAD->Release();
        }
        hr = pEnum->Next(1, &var, &lFetch);
    };
    pEnum->Release();


    // Reduce the index if possible
    nIndent -= 2;
    return;
}

/////////////////////////////////////////////////////////////////////////
// Example of how to search for objects in the Active Directory
/////////////////////////////////////////////////////////////////////////
void CMSJADSIDlg::OnBtnSearch() 
{
    UpdateData();
    
    HRESULT hr;
    IDirectorySearch* pSearch = NULL;
    ADS_SEARCH_HANDLE hSearch;
    long nFound = 0;
    ADS_SEARCH_COLUMN col;
    
    // Validate Connection
	if (!m_pContainer) 
	{
		AddToLog("Container not open, Please Open Container First");
		return;
	}

    // Get IDirectorySearch Object
    hr = m_pContainer->QueryInterface(IID_IDirectorySearch, 
                                        (void**) &pSearch);
    if (FAILED(hr)) 
    {
        AddToLog("Failed to Get Search Interface!");
        return;
    }

    // Set Search Defaults, to search the entire subtree
    ADS_SEARCHPREF_INFO prefInfo[1];
    prefInfo[0].dwSearchPref = ADS_SEARCHPREF_SEARCH_SCOPE;
    prefInfo[0].vValue.dwType = ADSTYPE_INTEGER;
    prefInfo[0].vValue.Integer = ADS_SCOPE_SUBTREE;
    hr = pSearch->SetSearchPreference( prefInfo, 1);
        
    // Execute Search
    LPWSTR pszAttr[] = { L"Name", L"description" };
    DWORD dwCount = sizeof(pszAttr)/sizeof(LPWSTR);
    hr = pSearch->ExecuteSearch(
                        m_csSearchCriteria.AllocSysString(),
                        pszAttr,
                        dwCount,
                        &hSearch
                                );

    // Display Contents
    if (SUCCEEDED(hr))
    {
        while( SUCCEEDED(hr = pSearch->GetNextRow(hSearch)) &&
                hr != S_ADS_NOMORE_ROWS   )
        {
            CString csLogItem;
            // Get Name
            if ( SUCCEEDED(pSearch->GetColumn(  hSearch, 
                                                pszAttr[0], 
                                                &col ) ) )
            {
               csLogItem = CString("Found: ") + 
                                    col.pADsValues->CaseIgnoreString;
               pSearch->FreeColumn( &col );
            }
            // Get Description
            if ( SUCCEEDED(pSearch->GetColumn(  hSearch, 
                                                pszAttr[1], 
                                                &col ) ) )
            {
               csLogItem += CString(" : ") +
                                col.pADsValues->CaseIgnoreString;
               pSearch->FreeColumn( &col );
            }
            AddToLog(csLogItem);
            nFound++;
        }
        pSearch->CloseSearchHandle(hSearch);
    }
    
    CString csTemp;
    csTemp.Format("Found %d Items...", nFound);
    AddToLog(csTemp);
}


