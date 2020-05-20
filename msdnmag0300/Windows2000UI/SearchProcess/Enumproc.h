#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tlhelp32.h>   // Win95 only
//#include <psapi.h>      // WinNT only

typedef struct tagPROCSTRUCT {
	CHAR szExeName[MAX_PATH];
	DWORD processID;
	CHAR szExeType[20];

} PROCSTRUCT, FAR *LPPROCSTRUCT;

typedef BOOL (CALLBACK *LPENUMPROC)( LPPROCSTRUCT, LPARAM );

#ifdef __cplusplus
extern "C" {
#endif

BOOL APIENTRY EnumProcess( 
	LPENUMPROC lpfunc,
	LPARAM lParam
);


BOOL APIENTRY EnumProcessToTreeView( 
	HWND hwndTree
);


INT APIENTRY GetExeBinaryFormat( 
	LPCSTR szExeName, 
	LPSTR szExeType 
);


BOOL APIENTRY ProcessDlg( 
	HWND hwnd
);

#ifdef __cplusplus
}
#endif

/*  End of file: EnumProc.h  */
