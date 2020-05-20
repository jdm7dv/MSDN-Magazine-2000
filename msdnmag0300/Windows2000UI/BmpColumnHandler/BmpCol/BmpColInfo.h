// BmpColInfo.h : Declaration of the CBmpColInfo

#ifndef __BMPCOLINFO_H_
#define __BMPCOLINFO_H_
#undef ATL_MIN_CRT

#include "resource.h"					// main symbols
#include <shlguid.h>					// GUID of IColumnProvider
#include "IColumnProviderImpl.h"        // IColumnProvider base impl


/////////////////////////////////////////////////////////////////////////////
// Constants
const UINT BMPCH_DEFWIDTH = 16;		// column default width in chars 
const UINT BMPCH_MAXSIZE = 80;		// max text size 
const DWORD BMPCH_NUMOFCOLS = 1;	// number of columns handled here


/////////////////////////////////////////////////////////////////////////////
// CBmpColInfo
class ATL_NO_VTABLE CBmpColInfo : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBmpColInfo, &CLSID_BmpColInfo>,
	public IColumnProviderImpl,
	public IDispatchImpl<IBmpColInfo, &IID_IBmpColInfo, &LIBID_BMPCOLLib>
{
public:
	CBmpColInfo()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BMPCOLINFO)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBmpColInfo)
	COM_INTERFACE_ENTRY(IBmpColInfo)
	COM_INTERFACE_ENTRY_IID(IID_IColumnProvider, CBmpColInfo)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IColumnProvider

public:
	STDMETHOD(GetColumnInfo)(DWORD, SHCOLUMNINFO *);
	STDMETHOD(GetItemData)(LPCSHCOLUMNID, LPCSHCOLUMNDATA, VARIANT *);

private:
	STDMETHOD(GetBitmapInfo)(LPCWSTR, LPTSTR);
	STDMETHOD(GetTitleFromHTML)(LPCWSTR, LPTSTR);
};

#endif //__BMPCOLINFO_H_
