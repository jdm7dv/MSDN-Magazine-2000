////////////////////////////////////////////
//
//  EXE Helper functions
//  to enumerate the dependency list of a
//  Win32 executable.
//
//
#pragma comment( lib, "imagehlp.lib" )
#include "DEPlist.h"


/*----------------------------------------------------------------*/
//                 GLOBAL section 
/*----------------------------------------------------------------*/

// data
static LPTSTR *g_ppszBuf = NULL;
static INT g_iNumOfBytes = 0;
static INT g_iNumOfDLLs = 0;

// callback
static BOOL CALLBACK SizeOfDLLs( IMAGEHLP_STATUS_REASON,  
	LPTSTR, LPTSTR, ULONG, ULONG );
static BOOL CALLBACK GetDLLs( IMAGEHLP_STATUS_REASON,  
	LPTSTR, LPTSTR, ULONG, ULONG );





/*----------------------------------------------------------------*/
// Procedure...: GetImportTableSize()
// Description.: Returns the amount of bytes required
// INPUT.......: LPCTSTR
// OUTPUT......: INT
/*----------------------------------------------------------------*/
INT APIENTRY GetImportTableSize( LPCTSTR pszFileName )
{
	g_iNumOfBytes = 0;

	// bind to the executable
	BindImageEx( BIND_NO_BOUND_IMPORTS|BIND_NO_UPDATE,
		(LPTSTR) pszFileName, NULL, NULL, 
		(PIMAGEHLP_STATUS_ROUTINE) SizeOfDLLs );
	
	return g_iNumOfBytes;
}




/*----------------------------------------------------------------*/
// Procedure...: GetImportTable
// Description.: Returns a null-separated string with all DLLs
// INPUT.......: LPCTSTR, LPTSTR *
// OUTPUT......: INT
/*----------------------------------------------------------------*/
INT APIENTRY GetImportTable( LPCTSTR pszFileName, LPTSTR pszBuf )
{
	g_ppszBuf = (LPTSTR*) &pszBuf;
	g_iNumOfDLLs = 0;

	// bind to the executable
	BindImageEx( BIND_NO_BOUND_IMPORTS|BIND_NO_UPDATE,
		(LPTSTR) pszFileName, NULL, NULL, 
		(PIMAGEHLP_STATUS_ROUTINE) GetDLLs );
	
	return g_iNumOfDLLs;
}



/*----------------------------------------------------------------*/
// Procedure...: SizeOfDLLs()
// Description.: Callback for calculating the size of DLLs
// INPUT.......: IMAGEHLP_STATUS_REASON, LPTSTR, LPTSTR, ULONG, ULONG
// OUTPUT......: BOOL
/*----------------------------------------------------------------*/
BOOL CALLBACK SizeOfDLLs( IMAGEHLP_STATUS_REASON Reason,  
  LPTSTR ImageName, LPSTR DllName, ULONG Va, ULONG Parameter )
{
	if( Reason==BindImportModule || Reason==BindImportModuleFailed )
		g_iNumOfBytes += lstrlen( DllName )+1;
	return TRUE;
}



/*----------------------------------------------------------------*/
// Procedure...: GetDLLs()
// Description.: Callback for packaging a string
// INPUT.......: IMAGEHLP_STATUS_REASON, LPTSTR, LPTSTR, ULONG, ULONG
// OUTPUT......: BOOL
/*----------------------------------------------------------------*/
BOOL CALLBACK GetDLLs( IMAGEHLP_STATUS_REASON Reason,  
  LPTSTR ImageName, LPTSTR DllName, ULONG Va, ULONG Parameter )
{
	if( Reason==BindImportModule || Reason==BindImportModuleFailed )
	{
		lstrcpy( *g_ppszBuf, DllName );
		*g_ppszBuf += lstrlen(*g_ppszBuf) + 1;
		g_iNumOfDLLs ++;
	}
	
	return TRUE;
}



/*  End of file: DEPlist.c  */

