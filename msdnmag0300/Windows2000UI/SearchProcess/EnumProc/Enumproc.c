#include "EnumProc.h"
#include "Resource.h"
#pragma comment( lib, "comctl32.lib" )

static FARPROC g_pfnCreateSnapshot=0;
static FARPROC g_pfnProcessFirst=0;
static FARPROC g_pfnProcessNext=0;
static FARPROC g_pfnEnumModule=0;
static FARPROC g_pfnModuleNameEx=0;
static FARPROC g_pfnEnumProcesses=0;
static HANDLE  g_hSupportLib=NULL;
static HINSTANCE g_hInstance;
static HIMAGELIST g_himl;

static DWORD _LoadFuncAddress( VOID );
static VOID  _UnloadFuncAddress( VOID );
static VOID  _GetProcessName( DWORD, LPSTR );
static VOID _DoRefresh( HWND );
static HTREEITEM _AddTreeItem( HWND, HTREEITEM, LPSTR, INT );


static BOOL CALLBACK EnumToTreeViewProc( LPPROCSTRUCT, LPARAM );
static BOOL CALLBACK ProcessDlgProc( HWND, UINT, WPARAM, LPARAM );




/*----------------------------------------------------------
//  DLL
----------------------------------------------------------*/
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, 
	LPVOID lpReserved )
{
	if( dwReason==DLL_PROCESS_ATTACH ) {
		g_hInstance = hInstance;
		InitCommonControls();
	}
	return TRUE;    
}



/*----------------------------------------------------------
//  Enumerates all the active processes...
----------------------------------------------------------*/
BOOL APIENTRY EnumProcess( LPENUMPROC lpFunc, LPARAM lParam )
{
    // local data
	DWORD dwPlatformId;

	if( lpFunc==NULL ) 
		return FALSE;


	// load the needed library and set the function pointers
	dwPlatformId = _LoadFuncAddress();
 

	// check the platform: Win95
    if( dwPlatformId==VER_PLATFORM_WIN32_WINDOWS )
    {
       HANDLE hSnapShot;
       PROCESSENTRY32 pe;
       BOOL bResult;

       hSnapShot = (HANDLE) g_pfnCreateSnapshot(
          TH32CS_SNAPPROCESS, 0 );
       if( hSnapShot==(HANDLE)-1 ) return FALSE;

       pe.dwSize = sizeof(PROCESSENTRY32);

       bResult = g_pfnProcessFirst( hSnapShot, &pe );
       while( bResult )
       {
		   PROCSTRUCT ps;
		   ZeroMemory( &ps, sizeof(PROCSTRUCT) );
	       lstrcpy( ps.szExeName, pe.szExeFile );
		   ps.processID = pe.th32ProcessID;
		   GetExeBinaryFormat( pe.szExeFile, ps.szExeType );

		   if( lpFunc( &ps, lParam ) )
               bResult = g_pfnProcessNext( hSnapShot, &pe );
		   else
			   break;
       }

       CloseHandle( hSnapShot );
    }
    else  // Windows NT
    if( dwPlatformId==VER_PLATFORM_WIN32_NT )
	{
       DWORD cbNeeded;
	   DWORD aProcessIDs[1024];

	   // get all the process IDs in an array
	   if( g_pfnEnumProcesses( aProcessIDs, sizeof(aProcessIDs), &cbNeeded) )
       {
           BOOL bExist;
		   INT i, j;
		   INT iNumOfProcesses = cbNeeded/sizeof(DWORD);

		   // scan the array
		   for( i=0; i<iNumOfProcesses; i++ )
		   {
              bExist = FALSE;

			  // verify if already exists...
              for( j=0; j<=i-1; j++ )
			  {
                if( aProcessIDs[i]==aProcessIDs[j] )
				{
                   bExist = TRUE;
				   break;
				}
			  }

			  if( !bExist )
			  {
			     PROCSTRUCT ps;
				 ZeroMemory( &ps, sizeof(PROCSTRUCT) );
				 _GetProcessName( aProcessIDs[i], ps.szExeName );
				 ps.processID = aProcessIDs[i];
				 lstrcpy( ps.szExeType, "32-bit" );
				 if( !lpFunc( &ps, lParam ) )
					 break;
			  }
		  }
	   }
    }

	// free the loaded library
    _UnloadFuncAddress();
	return TRUE;
}



/*----------------------------------------------------------
//  Enumerates all the active processes to a treeview...
----------------------------------------------------------*/
UINT APIENTRY EnumProcessToTreeView( HWND hwndTree )
{
	TreeView_DeleteAllItems( hwndTree );
	ImageList_Destroy( g_himl );

	// creates an imagelist
	g_himl = ImageList_LoadBitmap( g_hInstance,
		"IMAGELIST", 16, 1, CLR_NONE );
	ImageList_SetBkColor( g_himl, 0xFFFFFF );
	TreeView_SetImageList( hwndTree, g_himl, TVSIL_NORMAL );

	// enumerates processes
	EnumProcess( EnumToTreeViewProc, (LPARAM) hwndTree );
	return TreeView_GetCount( hwndTree )/3;  // only in this case!!!;
}




/*----------------------------------------------------------
//  Dialog that displays the tree of processes
----------------------------------------------------------*/
BOOL APIENTRY ProcessDlg( HWND hwndParent )
{
	return DialogBox( g_hInstance, MAKEINTRESOURCE(IDD_DLG),
		hwndParent, (DLGPROC) ProcessDlgProc );
}




/*----------------------------------------------------------
//  Callback used to fill in a treeview 
----------------------------------------------------------*/
BOOL CALLBACK EnumToTreeViewProc( LPPROCSTRUCT lpps, LPARAM lParam )
{
	CHAR s[20];
	SHFILEINFO sfi;
	HTREEITEM hNode;
	INT iImageId;
	HWND hwndTree = (HWND) lParam;
	

	// main module
	iImageId=0;
	ZeroMemory( &sfi, sizeof(SHFILEINFO) );
	if( SHGetFileInfo( lpps->szExeName, 0, &sfi, 
		sizeof(SHFILEINFO), SHGFI_ICON|SHGFI_SMALLICON ) )
	{
		iImageId = ImageList_AddIcon( g_himl, sfi.hIcon );
	}
	hNode = _AddTreeItem( hwndTree, NULL, lpps->szExeName, iImageId );
	


	// information
	wsprintf( s, "0x%08X", lpps->processID );
	_AddTreeItem( hwndTree, hNode, s, 1 );

	if( !lstrcmpi(lpps->szExeType, "<Not an EXE file>") )
		_AddTreeItem( hwndTree, hNode, lpps->szExeType, 2 );
	else
		_AddTreeItem( hwndTree, hNode, lpps->szExeType, 0 );
	return 1;
}



/*----------------------------------------------------------
//  Callback used to manage the dialog
----------------------------------------------------------*/
BOOL CALLBACK ProcessDlgProc( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_INITDIALOG:
			_DoRefresh( hDlg );
			break;

		case WM_COMMAND:
			switch( LOWORD(wParam) )
			{
				case IDCANCEL:
					EndDialog( hDlg, 0 );
					break;

				case IDOK:
					_DoRefresh( hDlg );
					break;
			}
			break;
	}

	return FALSE;
}





///////////////////////////////////////////
//
// Internal Functions
//
//


/*----------------------------------------------------
// _LoadFuncAddress: initializes some function ptrs
-----------------------------------------------------*/
DWORD _LoadFuncAddress( VOID )
{
    OSVERSIONINFO osv;
    DWORD dwPlatformId;

    osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx( &osv );
    dwPlatformId = osv.dwPlatformId;
    if( dwPlatformId==VER_PLATFORM_WIN32_WINDOWS )
    {
      g_hSupportLib = LoadLibrary( "kernel32.dll" );
      g_pfnCreateSnapshot = GetProcAddress( g_hSupportLib,
        "CreateToolhelp32Snapshot" );
      g_pfnProcessFirst = GetProcAddress( g_hSupportLib,
        "Process32First" );
      g_pfnProcessNext = GetProcAddress( g_hSupportLib,
        "Process32Next" );
    }
    else
    if( dwPlatformId==VER_PLATFORM_WIN32_NT )
    {
      g_hSupportLib = LoadLibrary( "psapi.dll" );
      g_pfnEnumProcesses = GetProcAddress( g_hSupportLib, 
        "EnumProcesses" );
      g_pfnEnumModule = GetProcAddress( g_hSupportLib, 
        "EnumProcessModules" );
      g_pfnModuleNameEx = GetProcAddress( g_hSupportLib,
        "GetModuleFileNameExA" );
    }

	return dwPlatformId;
}


/*----------------------------------------------------
//  _UnloadFuncAddress: free the loaded library
-----------------------------------------------------*/
VOID _UnloadFuncAddress( VOID )
{
    if( g_hSupportLib )
    {
       FreeLibrary( g_hSupportLib );
       g_hSupportLib = NULL;
    }
}


/*----------------------------------------------------
//  _GetProcessName: return the name of the process
-----------------------------------------------------*/
VOID _GetProcessName( DWORD dwProcessID, LPSTR pszName )
{
   HANDLE hProcess;
   HMODULE hModule;
   DWORD cb;

   hProcess = OpenProcess( PROCESS_QUERY_INFORMATION|
        PROCESS_VM_READ, FALSE, dwProcessID );
       
   if( g_pfnEnumModule(hProcess, &hModule, sizeof(HMODULE), &cb) )
       g_pfnModuleNameEx( hProcess, hModule, pszName, MAX_PATH );

   if( !lstrlen(pszName) )
   {
	   lstrcpy( pszName, "<Unknown name>" );
   }
   CloseHandle( hProcess );
}


/*----------------------------------------------------
//  _AddTreeItem: add an item to a treeview
-----------------------------------------------------*/
HTREEITEM _AddTreeItem( HWND hwndTree, HTREEITEM hNode, 
	LPSTR szText, INT iImageId )
{
	HTREEITEM hItem;
	TV_ITEM tvI;
	TV_INSERTSTRUCT tvIns;

	tvI.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvI.pszText = szText;
	tvI.cchTextMax = lstrlen(szText);
	tvI.iImage = iImageId;
	tvI.iSelectedImage = iImageId;

	ZeroMemory( &tvIns, sizeof(TV_INSERTSTRUCT) );
	tvIns.item = tvI;
	tvIns.hParent = hNode;
	
	// insert the item into the tree
	hItem = TreeView_InsertItem( hwndTree, &tvIns );
	return hItem;
}
   

/*----------------------------------------------------
//  _DoRefresh: updates the process list
-----------------------------------------------------*/
VOID _DoRefresh( HWND hDlg )
{
	CHAR szTime[50], szMsg[100];
	HWND hwndTree;
	UINT nCount;

	GetTimeFormat( LOCALE_SYSTEM_DEFAULT, 0, NULL, 
			 NULL, szTime, 50 );
	wsprintf( szMsg, "Snapshot taken at %s", szTime );
	SetDlgItemText( hDlg, IDC_SNAPSHOT, szMsg );

	// updates the treeview
	hwndTree = (HWND) GetDlgItem(hDlg, IDC_TREE);
	nCount = EnumProcessToTreeView( hwndTree );
	wsprintf( szMsg, "%d processes running.", nCount );
	SetDlgItemText( hDlg, IDC_NUMPROC, szMsg );
}


/*  End of module: EnumProc.c  */
