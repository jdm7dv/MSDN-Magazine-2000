#ifndef __ExtensionHeader_Defined__
#define __ExtensionHeader_Defined__

	#ifndef STRICT
	#define STRICT
	#endif

	#define INC_OLE2        
	
	#include <windows.h>
	#include <windowsx.h>
	#include <shlobj.h>

	#define ResultFromShort(i)  ResultFromScode(MAKE_SCODE(SEVERITY_SUCCESS, 0, (USHORT)(i)))

#endif

