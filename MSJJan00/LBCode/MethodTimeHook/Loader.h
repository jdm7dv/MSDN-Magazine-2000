///////////////////////////////////////////////////////////////////////
//
//  Loader.h - Copyright 1999, Tim Ewald / DevelopMentor
//  

// Loader.h : Declaration of the CLoader

#ifndef __LOADER_H_
#define __LOADER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLoader
class ATL_NO_VTABLE CLoader : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CLoader, &CLSID_Loader>,
	public ILoader
{
public:
	CLoader()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOADER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoader)
	COM_INTERFACE_ENTRY(ILoader)
END_COM_MAP()

// ILoader
public:
	STDMETHOD(GetAverageMethodTime)(/*[out, retval]*/ long *pnAvg);
};

#endif //__LOADER_H_
