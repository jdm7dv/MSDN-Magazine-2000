#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x400
#define UNICODE
#include <windows.h>
#pragma comment( lib, "kernel32.lib" )
#pragma comment( lib, "advapi32.lib" )

int WINAPI WinMain( HINSTANCE, HINSTANCE, char*, int )
{
	SECURITY_DESCRIPTOR sd;
	InitializeSecurityDescriptor( &sd, SECURITY_DESCRIPTOR_REVISION );
	SetSecurityDescriptorDacl( &sd, TRUE, 0, FALSE );
	SECURITY_ATTRIBUTES sa = { sizeof sa, &sd, FALSE };
	WaitForSingleObject( CreateEvent( &sa, FALSE, FALSE, L"NullProcessSynchronizer" ), INFINITE );
	return 0;
}
