///////////////////////////////////////////////////////////////////////
//
//  Admin.h - Copyright 1999, Tim Ewald / DevelopMentor
//  

// Admin.h : Declaration of the CAdmin

#ifndef __ADMIN_H_
#define __ADMIN_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAdmin
class ATL_NO_VTABLE CAdmin : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CAdmin, &CLSID_Admin>,
	public IAdmin
{
public:
	CAdmin()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ADMIN)
DECLARE_NOT_AGGREGATABLE(CAdmin)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAdmin)
	COM_INTERFACE_ENTRY(IAdmin)
END_COM_MAP()

// IAdmin
public:
};

#endif //__ADMIN_H_
