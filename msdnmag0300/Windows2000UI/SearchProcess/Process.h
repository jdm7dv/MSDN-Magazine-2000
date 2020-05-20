// Process.h : Declaration of the CProcess

#ifndef __PROCESS_H_
#define __PROCESS_H_

#include "resource.h"			     // main symbols
#include "IShellExtInitImpl.h"       // IShellExtInit
#include "IContextMenuImpl.h"        // IContextMenu
#include "ProcTreeDlg.h"             // IContextMenu
#include <comdef.h>


/////////////////////////////////////////////////////////////////////////////
// CProcess
class ATL_NO_VTABLE CProcess : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProcess, &CLSID_Process>,
	public IShellExtInitImpl,
	public IContextMenuImpl,
	public IDispatchImpl<IProcess, &IID_IProcess, &LIBID_PROCFINDLib>
{
public:
	CProcTreeDlg m_Dlg;

	CProcess() 	{}

	STDMETHOD(GetCommandString)( UINT, UINT, UINT*, LPSTR, UINT );
	STDMETHOD(InvokeCommand)( LPCMINVOKECOMMANDINFO );
	STDMETHOD(QueryContextMenu)( HMENU, UINT, UINT , UINT, UINT );
	STDMETHOD(Initialize)( LPCITEMIDLIST, LPDATAOBJECT, HKEY );


DECLARE_REGISTRY_RESOURCEID(IDR_PROCESS)

BEGIN_COM_MAP(CProcess)
	COM_INTERFACE_ENTRY(IProcess)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IContextMenu)
END_COM_MAP()

// IProcess
public:
};

#endif //__PROCESS_H_
