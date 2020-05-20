// Property.h : Declaration of the CProperty

#ifndef __PROPERTY_H_
#define __PROPERTY_H_

#include "resource.h"					// main symbols
#include "comdef.h"	
#include "IShellExtInitImpl.h"			// IShellExtInit
#include "IShellPropSheetExtImpl.h"		// IShellPropSheetExt
#include "IContextMenuImpl.h"			// IContextMenu
#include "NewFolderDlg.h"				// Dialog box


/////////////////////////////////////////////////////////////////////////////
// CProperty
class ATL_NO_VTABLE CProperty : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProperty, &CLSID_Property>,
	public IShellExtInitImpl,
	public IShellPropSheetExtImpl,
	public IContextMenuImpl,
	public IDispatchImpl<IProperty, &IID_IProperty, &LIBID_FOLDEREXTLib>
{
public:

	CNewFolderDlg m_Dlg;				// dialog box
	CSimpleArray<CComBSTR> menuItems;
	CProperty() 
	{
		CComBSTR  bstrNewFolder = L"New Folder";
		CComBSTR  bstrMsDos = L"MS-DOS Prompt from here";
		menuItems.Add(bstrNewFolder);
		menuItems.Add(bstrMsDos);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PROPERTY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProperty)
	COM_INTERFACE_ENTRY(IProperty)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IShellPropSheetExt)
	COM_INTERFACE_ENTRY(IContextMenu)
	COM_INTERFACE_ENTRY(IContextMenu2)
	COM_INTERFACE_ENTRY(IContextMenu3)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

public: 
	STDMETHOD(Initialize) (LPCITEMIDLIST, LPDATAOBJECT, HKEY);
	STDMETHOD(AddPages) (LPFNADDPROPSHEETPAGE, LPARAM);

// IContextMenu
	STDMETHOD(GetCommandString)(UINT, UINT, UINT*, LPSTR, UINT);
	STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO);
	STDMETHOD(QueryContextMenu)(HMENU, UINT, UINT , UINT, UINT);

// IContextMenu2
	STDMETHOD(HandleMenuMsg)(UINT, WPARAM, LPARAM);

// IContextMenu3
	STDMETHOD(HandleMenuMsg2)(UINT, WPARAM, LPARAM, LRESULT *);

// Static members
static	BOOL CALLBACK PropPage_DlgProc(HWND, UINT, WPARAM, LPARAM);

// Private members
	void MeasureItem(LPMEASUREITEMSTRUCT);
	void DrawMenuItem(LPDRAWITEMSTRUCT);
};

#endif //__PROPERTY_H_
