#include <windows.h>
#include <imagehlp.h>


// defines our callback interface
typedef BOOL (CALLBACK *LPIMPTABLEPROC)(LPCSTR, LPARAM);


// enumerates all the imported libraries
extern "C"
INT 
APIENTRY 
EnumExeImportTable( 
	LPCTSTR pszFileName, 
	LPIMPTABLEPROC pfnImpTableProc,
	LPARAM lParam 
);


// returns the bytes required to hold the names of the DLLs
extern "C"
INT 
APIENTRY 
GetImportTableSize( 
	LPCTSTR pszFileName
);


// fills the specified buffer with the name of the DLLs
extern "C"
INT 
APIENTRY 
GetImportTable( 
	LPCTSTR pszFileName, 
	LPTSTR pszBuf
);



/*  End of file: DEPlist.h  */