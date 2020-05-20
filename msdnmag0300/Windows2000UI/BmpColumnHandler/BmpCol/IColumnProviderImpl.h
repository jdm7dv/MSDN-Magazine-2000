// IColumnProviderImpl.h
//
//////////////////////////////////////////////////////////////////////
#include <AtlCom.h>
#include <ShlObj.h>



class ATL_NO_VTABLE IColumnProviderImpl : public IColumnProvider 
{
protected:
	TCHAR m_szFolder[MAX_PATH];

public:
	// IUnknown
	//
	STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject) = 0;
	_ATL_DEBUG_ADDREF_RELEASE_IMPL(IColumnProviderImpl)


	// IColumnProvider 
	//

	// IColumnProvider::Initialize
	STDMETHOD(Initialize)(LPCSHCOLUMNINIT psci)
	{
		USES_CONVERSION;
		_tcscpy(m_szFolder, OLE2T((WCHAR*)psci->wszFolder)); 
		return S_OK;
	}

	// IColumnProvider::GetColumnInfo
	STDMETHOD(GetColumnInfo)(DWORD dwIndex, SHCOLUMNINFO *psci)
	{ 
		return S_FALSE; 
	}

	// IColumnProvider::GetItemData
	STDMETHOD(GetItemData)(LPCSHCOLUMNID pscid, LPCSHCOLUMNDATA pscd, VARIANT *pvarData)
	{ 
		return S_FALSE; 
	}
};


