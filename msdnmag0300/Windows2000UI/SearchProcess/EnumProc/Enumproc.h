#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <shellapi.h>
#include <tlhelp32.h>   // Win95 only
//#include <psapi.h>      // WinNT only

typedef BOOL (CALLBACK *LPENUMPROC)( LPPROCSTRUCT, LPARAM );

typedef struct tagPROCSTRUCT {
	CHAR szExeName[MAX_PATH];
	DWORD processID;
	CHAR szExeType[20];

} PROCSTRUCT, FAR *LPPROCSTRUCT;

#ifdef __cplusplus
extern "C" {
#endif

BOOL APIENTRY EnumProcess( 
	LPENUMPROC lpfunc,
	LPARAM lParam
);


UINT APIENTRY EnumProcessToTreeView( 
	HWND hwndTree
);


INT APIENTRY GetExeBinaryFormat( 
	LPCSTR szExeName, 
	LPSTR szExeType 
);

#ifdef __cplusplus
}
#endif

/*  End of file: EnumProc.h  */
