// Process.cpp : Implementation of CProcess
#include "stdafx.h"
#include "ProcFind.h"
#include "Process.h"

/////////////////////////////////////////////////////////////////////////////
// CProcess

// QueryContextMenu
HRESULT CProcess::QueryContextMenu( HMENU hmenu, UINT indexMenu,
		UINT idCmdFirst, UINT idCmdLast, UINT uFlags )
{
	return S_OK;
}


 

// InvokeCommand
HRESULT CProcess::InvokeCommand( LPCMINVOKECOMMANDINFO lpcmi )
{
	m_Dlg.DoModal();
	return S_OK;
}




// GetCommandString
HRESULT CProcess::GetCommandString( UINT idCmd, UINT uFlags, 
		UINT *pwReserved, LPSTR pszText, UINT cchMax )
{
	return S_OK;
}



// Initialize
HRESULT CProcess::Initialize( LPCITEMIDLIST pidlFolder,
		LPDATAOBJECT lpdobj, HKEY hKeyProgID )
{
	return S_OK;
};

