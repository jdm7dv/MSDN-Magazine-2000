#include <windows.h>
#include <shellapi.h>

#define EXE_NONE		0x0000
#define EXE_WIN32		0x0001
#define EXE_WIN32C		0x0002
#define EXE_WIN16		0x0003
#define EXE_DOS			0x0004

#define PE_SIGN			0x4550	
#define NE_SIGN			0x454E
#define MZ_SIGN			0x5A4D




INT APIENTRY GetExeBinaryFormat( LPCSTR szExeName, LPSTR szExeType )
{
	SHFILEINFO sfi;
	DWORD dwRC;

	ZeroMemory( &sfi, sizeof(SHFILEINFO) );
	dwRC = SHGetFileInfo( szExeName, 0, &sfi, sizeof(SHFILEINFO),
			SHGFI_EXETYPE );
	
	// not an executable
	if( dwRC==0 )  {
		if( szExeType )
			lstrcpy( szExeType, "<Not an EXE file>" );
		return EXE_NONE;
	}

	// Win32: Win or console
	if( LOWORD(dwRC)==PE_SIGN ) {
		if( HIWORD(dwRC) ) {
			if( szExeType )
				lstrcpy( szExeType, "32-bit" );
			return EXE_WIN32;
		}
		else {
			if( szExeType )
				lstrcpy( szExeType, "32-bit Console" );
			return EXE_WIN32C;
		}
	}
	else {
		if( LOWORD(dwRC)==NE_SIGN ) {
			if( szExeType )
				lstrcpy( szExeType, "16-bit" );
			return EXE_WIN16;
		}
		else 
		if( LOWORD(dwRC)==MZ_SIGN ) {
			if( szExeType )
				lstrcpy( szExeType, "MS-DOS" );
			return EXE_DOS;
		}
	}

	if( szExeType )
		lstrcpy( szExeType, "<Not an EXE file>" );
	return EXE_NONE;
} 
