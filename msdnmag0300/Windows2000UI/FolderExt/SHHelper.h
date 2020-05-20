////////////////////////////////////////////////////////////////
//
//   SHHelper.DLL
//   Shell Helper functions - Header
//   shhelper.h
//


#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <shlobj.h>


#ifdef __cplusplus
extern "C" {
#endif




// opens a dialog and browse for a icon
INT APIENTRY 
SHBrowseForIcon(
	LPCSTR szFileName,		// file name
	HICON FAR* lphIcon		// buffer for HICON
);




typedef struct _BFFSTRUCT { 
	BOOL fIsPathName;	
	LPVOID lpv;
} BFFSTRUCT, FAR* LPBFFSTRUCT;

// simplified version of SHBrowseForFolder
LPITEMIDLIST APIENTRY 
BrowseForFolders( 
	HWND hwndParent,	// parent window for the dialog
	LPVOID lpv,			// initial dir (PIDL or path)
	BOOL fIsPathName,	// specifies the above param
	LPSTR szDirName		// return buffer for path
);




typedef struct _SHORTCUTSTRUCT {
	LPSTR pszTarget;
	LPSTR pszDesc;
	WORD wHotKey;
	LPSTR pszIconPath;
	WORD wIconIndex;
} SHORTCUTSTRUCT, FAR* LPSHORTCUTSTRUCT;

// creates shortcuts
HRESULT APIENTRY 
SHCreateShortcut( 
	LPCSTR szLnkFile,		// LNK file to create
	LPSHORTCUTSTRUCT lpss	// shortcut info
);

// resolve shortcuts
HRESULT APIENTRY
SHResolveShortcut( 
	LPCSTR szLnkFile,		// LNK file to resolve
	LPSHORTCUTSTRUCT lpss	// shortcut info	
);




#ifdef __cplusplus
}
#endif