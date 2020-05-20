#include "precomp.h"
#include "Win32Objects.h"
#include <stdlib.h>
#include <crtdbg.h>

namespace
{
    // this helper always uses a NULL DACL
    struct SecurityAttributes : SECURITY_ATTRIBUTES
    {
        SecurityAttributes( bool bInherit )
        {
            static SECURITY_DESCRIPTOR sdWithNullDacl = { SECURITY_DESCRIPTOR_REVISION, 0,
                                                          SE_DACL_PRESENT, 0, 0, 0, 0 };
            nLength              = sizeof SECURITY_ATTRIBUTES;
            lpSecurityDescriptor = &sdWithNullDacl;
            bInheritHandle       = bInherit ? TRUE : FALSE;
        }
    };
}

const wchar_t* Win32Object::MapPermissionName( DWORD nPermission )
{
    switch ( nPermission )
    {
        case DELETE:                    return L"DELETE";
        case READ_CONTROL:              return L"READ_CONTROL";
        case WRITE_DAC:                 return L"WRITE_DAC";
        case WRITE_OWNER:               return L"WRITE_OWNER";
        case SYNCHRONIZE:               return L"SYNCHRONIZE";

        case ACCESS_SYSTEM_SECURITY:    return L"ACCESS_SYSTEM_SECURITY";
        case MAXIMUM_ALLOWED:           return L"MAXIMUM_ALLOWED";

        case GENERIC_ALL:               return L"GENERIC_ALL";
        case GENERIC_EXECUTE:           return L"GENERIC_EXECUTE";
        case GENERIC_WRITE:             return L"GENERIC_WRITE";
        case GENERIC_READ:              return L"GENERIC_READ";
    }
    _ASSERT( FALSE );
    return 0;
}

void Win32Object::MapPermissionNames( DWORD grfAccess, wchar_t* pszResult,
                                        const wchar_t* pszDelim )
{
    wchar_t* psz = pszResult;
    *psz = L'\0';
    DWORD i = 0x80000000;
    bool bMappedAtLeastOne = false;
    while ( i )
    {
        if ( i & grfAccess )
        {
            if ( bMappedAtLeastOne )
            {
                lstrcpy( psz, pszDelim );
                psz += lstrlen( psz );
            }
            lstrcpy( psz, MapPermissionName( i ) );
            psz += lstrlen( psz );
            bMappedAtLeastOne = true;
        }
        i >>= 1;
    }
}

struct KernelObject : Win32Object
{
    KernelObject( DWORD grfMax,
                  bool bCanBeNamed,
                  const wchar_t* pszObjTypeName )
      : Win32Object( grfMax,
                     SE_KERNEL_OBJECT,
                     bCanBeNamed,
                     true,
                     pszObjTypeName )
    {}
    bool UseObject( HANDLE h )
    {
        return ( WAIT_FAILED == WaitForSingleObject( h, 0 ) ) ? false : true;
    }

};

struct Section : KernelObject
{
    Section()
      : KernelObject( 0xF0007,
                      true,
                      L"Section" )
    {}

    HANDLE CreateObject( bool bInherit, const wchar_t* pszSuggestedName = 0, wchar_t* pszActualName = 0 )
    {
        if ( pszSuggestedName && pszActualName )
            lstrcpy( pszActualName, pszSuggestedName );
        SecurityAttributes sa( bInherit );
        return CreateFileMapping( reinterpret_cast<HANDLE*>(0xFFFFFFFF), &sa,
                                  PAGE_READWRITE, 0, 1024, pszSuggestedName );
    }
    HANDLE OpenObject( const wchar_t* psz, DWORD grfAccess )
    {
        return OpenFileMapping( grfAccess, FALSE, psz );
    }
    const wchar_t* MapPermissionName( DWORD nPermission )
    {
        switch ( nPermission )
        {
            case FILE_MAP_COPY:         return L"FILE_MAP_COPY";
            case FILE_MAP_WRITE:        return L"FILE_MAP_WRITE";
            case FILE_MAP_READ:         return L"FILE_MAP_READ";
        }
        return Win32Object::MapPermissionName( nPermission );
    }
};

struct Mutex : KernelObject
{
    Mutex()
      : KernelObject( 0x1F0001,
                      true,
                      L"Mutex" )
    {}
    HANDLE CreateObject( bool bInherit, const wchar_t* pszSuggestedName = 0, wchar_t* pszActualName = 0 )
    {
        if ( pszSuggestedName && pszActualName )
            lstrcpy( pszActualName, pszSuggestedName );
        SecurityAttributes sa( bInherit );
        return CreateMutex( &sa, FALSE, pszSuggestedName );
    }
    HANDLE OpenObject( const wchar_t* psz, DWORD grfAccess )
    {
        return OpenMutex( grfAccess, FALSE, psz );
    }
    const wchar_t* MapPermissionName( DWORD nPermission )
    {
        switch ( nPermission )
        {
            case MUTEX_MODIFY_STATE:    return L"MUTEX_MODIFY_STATE";
        }
        return Win32Object::MapPermissionName( nPermission );
    }
};

struct Semaphore : KernelObject
{
    Semaphore()
      : KernelObject( 0x1F0002,
                      true,
                      L"Semaphore" )
    {}

    HANDLE CreateObject( bool bInherit, const wchar_t* pszSuggestedName = 0, wchar_t* pszActualName = 0 )
    {
        if ( pszSuggestedName && pszActualName )
            lstrcpy( pszActualName, pszSuggestedName );
        SecurityAttributes sa( bInherit );
        return CreateSemaphore( &sa, 0, 10, pszSuggestedName );
    }
    HANDLE OpenObject( const wchar_t* psz, DWORD grfAccess )
    {
        return OpenSemaphore( grfAccess, FALSE, psz );
    }
    const wchar_t* MapPermissionName( DWORD nPermission )
    {
        switch ( nPermission )
        {
            case SEMAPHORE_MODIFY_STATE:    return L"SEMAPHORE_MODIFY_STATE";
        }
        return Win32Object::MapPermissionName( nPermission );
    }
};

struct Event : KernelObject
{
    Event()
      : KernelObject( 0x1F0002,
                      true,
                      L"Event" )
    {}

    HANDLE CreateObject( bool bInherit, const wchar_t* pszSuggestedName = 0, wchar_t* pszActualName = 0 )
    {
        if ( pszSuggestedName && pszActualName )
            lstrcpy( pszActualName, pszSuggestedName );
        SecurityAttributes sa( bInherit );
        return CreateEvent( &sa, TRUE, FALSE, pszSuggestedName );
    }
    HANDLE OpenObject( const wchar_t* psz, DWORD grfAccess )
    {
        return OpenEvent( grfAccess, FALSE, psz );
    }
    const wchar_t* MapPermissionName( DWORD nPermission )
    {
        switch ( nPermission )
        {
            case EVENT_MODIFY_STATE:    return L"EVENT_MODIFY_STATE";
        }
        return Win32Object::MapPermissionName( nPermission );
    }
};

struct WaitableTimer : KernelObject
{
    WaitableTimer()
      : KernelObject( 0x1F0003,
                      true,
                      L"WaitableTimer" )
    {}

    HANDLE CreateObject( bool bInherit, const wchar_t* pszSuggestedName = 0, wchar_t* pszActualName = 0 )
    {
        if ( pszSuggestedName && pszActualName )
            lstrcpy( pszActualName, pszSuggestedName );
        SecurityAttributes sa( bInherit );
        return CreateWaitableTimer( &sa, TRUE, pszSuggestedName );
    }
    HANDLE OpenObject( const wchar_t* psz, DWORD grfAccess )
    {
        return OpenWaitableTimer( grfAccess, FALSE, psz );
    }
    const wchar_t* MapPermissionName( DWORD nPermission )
    {
        switch ( nPermission )
        {
            case TIMER_MODIFY_STATE:    return L"TIMER_MODIFY_STATE";
            case TIMER_QUERY_STATE:     return L"TIMER_QUERY_STATE";
        }
        return Win32Object::MapPermissionName( nPermission );
    }
};

struct Token : KernelObject
{
    Token()
      : KernelObject( 0xF00FF,
                      false,
                      L"Token" )
    {}

    HANDLE CreateObject( bool bInherit, const wchar_t* = 0, wchar_t* = 0 )
    {
        HANDLE hObj = 0;
        if ( !LogonUser( L"Alice", L".", L"alice", LOGON32_LOGON_INTERACTIVE, 0, &hObj ) )
            hObj = 0;

        if ( hObj )
        {
            BOOL bOk = SetHandleInformation( hObj, HANDLE_FLAG_INHERIT,
                                              bInherit ? HANDLE_FLAG_INHERIT : 0 );
            _ASSERT( bOk );
            SECURITY_DESCRIPTOR sd;
            InitializeSecurityDescriptor( &sd, SECURITY_DESCRIPTOR_REVISION );
            SetSecurityDescriptorDacl( &sd, TRUE, 0, FALSE );
            bOk = SetKernelObjectSecurity( hObj, DACL_SECURITY_INFORMATION, &sd );
            _ASSERT( bOk );
        }
        return hObj;
    }
    const wchar_t* MapPermissionName( DWORD nPermission )
    {
        switch ( nPermission )
        {
            case TOKEN_ASSIGN_PRIMARY:      return L"TOKEN_ASSIGN_PRIMARY";
            case TOKEN_DUPLICATE:           return L"TOKEN_DUPLICATE";
            case TOKEN_IMPERSONATE:         return L"TOKEN_IMPERSONATE";
            case TOKEN_QUERY:               return L"TOKEN_QUERY";
            case TOKEN_QUERY_SOURCE:        return L"TOKEN_QUERY_SOURCE";
            case TOKEN_ADJUST_PRIVILEGES:   return L"TOKEN_ADJUST_PRIVILEGES";
            case TOKEN_ADJUST_GROUPS:       return L"TOKEN_ADJUST_GROUPS";
            case TOKEN_ADJUST_DEFAULT:      return L"TOKEN_ADJUST_DEFAULT";

            // undoc'd, and not included in grfMax
            case TOKEN_ADJUST_SESSIONID:    return L"TOKEN_ADJUST_SESSIONID";
        }
        return Win32Object::MapPermissionName( nPermission );
    }
};

struct Process : KernelObject
{
    Process()
      : KernelObject( 0x1F07FF,
                      true,
                      L"Process" )
    {}

    HANDLE CreateObject( bool bInherit, const wchar_t*, wchar_t* pszActualName = 0 )
    {
        SecurityAttributes saProcess( bInherit );
        SecurityAttributes saThread( false );
        STARTUPINFO si = { sizeof si };
        PROCESS_INFORMATION pi;
        wchar_t szCmd[80];
        wsprintf( szCmd, L"nullprocess" );
        BOOL bOk = CreateProcess( 0, szCmd, &saProcess, &saThread, TRUE, 0, 0, 0, &si, &pi );
        Sleep(0); // kludgy approach to fixing race condition
        if ( bOk )
        {
            if ( pszActualName )
                wsprintf( pszActualName, L"%d", pi.dwProcessId );
            CloseHandle( pi.hThread );
        }
        return bOk ? pi.hProcess : 0;
    }
    HANDLE OpenObject( const wchar_t* psz, DWORD grfAccess )
    {
        return OpenProcess( grfAccess, FALSE, _wtoi( psz ) );
    }
    void CloseObject( HANDLE h, const wchar_t* )
    {
        HANDLE hEvent = OpenEvent( EVENT_MODIFY_STATE, FALSE, L"NullProcessSynchronizer" );
        if ( hEvent )
        {
            SetEvent( hEvent );
            CloseHandle( hEvent );
        }
    }

    const wchar_t* MapPermissionName( DWORD nPermission )
    {
        switch ( nPermission )
        {
            case PROCESS_TERMINATE:         return L"PROCESS_TERMINATE";
            case PROCESS_CREATE_THREAD:     return L"PROCESS_CREATE_THREAD";
            case PROCESS_SET_SESSIONID:     return L"PROCESS_SET_SESSIONID";
            case PROCESS_VM_OPERATION:      return L"PROCESS_VM_OPERATION";
            case PROCESS_VM_READ:           return L"PROCESS_VM_READ";
            case PROCESS_VM_WRITE:          return L"PROCESS_VM_WRITE";
            case PROCESS_DUP_HANDLE:        return L"PROCESS_DUP_HANDLE";
            case PROCESS_CREATE_PROCESS:    return L"PROCESS_CREATE_PROCESS";
            case PROCESS_SET_QUOTA:         return L"PROCESS_SET_QUOTA";
            case PROCESS_SET_INFORMATION:   return L"PROCESS_SET_INFORMATION";
            case PROCESS_QUERY_INFORMATION: return L"PROCESS_QUERY_INFORMATION";
        }
        return Win32Object::MapPermissionName( nPermission );
    }
};

struct Thread : KernelObject
{
    Thread()
      : KernelObject( 0x1F00FB,
                      true,
                      L"Thread" )
    {}

    static HANDLE _createEvent()
    {
        return CreateEvent( 0, FALSE, FALSE, L"TestThreadSynchronizer" );
    }

    static DWORD WINAPI ThreadProc( void* )
    {
        WaitForSingleObject( _createEvent(), INFINITE );
        return 0;
    }

    HANDLE CreateObject( bool bInherit, const wchar_t*, wchar_t* pszActualName = 0 )
    {
        SecurityAttributes sa( bInherit );
        DWORD tid = 0;
        HANDLE hObj = CreateThread( &sa, 0, ThreadProc, 0, 0, &tid );
        Sleep(0); // kludgy approach to fixing race condition
        if ( pszActualName )
            wsprintf( pszActualName, L"%d", tid );
        return hObj;
    }

    HANDLE OpenObject( const wchar_t* psz, DWORD grfAccess )
    {
        // OpenThread is only supported in W2K
        HANDLE hObj = 0;
        HMODULE hdll = LoadLibrary( L"kernel32.dll" );
        if ( hdll )
        {
            typedef HANDLE (WINAPI* OPENTHREADFCN)( DWORD, BOOL, DWORD );
            OPENTHREADFCN openThread = reinterpret_cast<OPENTHREADFCN>(GetProcAddress( hdll, "OpenThread" ));
            if ( openThread )
                hObj = openThread( grfAccess, FALSE, _wtoi( psz ) );
            FreeLibrary( hdll );
        }
        return hObj;
    }

    void CloseObject( HANDLE h, const wchar_t* )
    {
        HANDLE hEvent = _createEvent();
        if ( hEvent )
        {
            SetEvent( hEvent );
            CloseHandle( hEvent );
        }
    }

    const wchar_t* MapPermissionName( DWORD nPermission )
    {
        switch ( nPermission )
        {
            case THREAD_TERMINATE:              return L"THREAD_TERMINATE";
            case THREAD_SUSPEND_RESUME:         return L"THREAD_SUSPEND_RESUME";
            case THREAD_GET_CONTEXT:            return L"THREAD_GET_CONTEXT";
            case THREAD_SET_CONTEXT:            return L"THREAD_SET_CONTEXT";
            case THREAD_SET_INFORMATION:        return L"THREAD_SET_INFORMATION";
            case THREAD_QUERY_INFORMATION:      return L"THREAD_QUERY_INFORMATION";
            case THREAD_SET_THREAD_TOKEN:       return L"THREAD_SET_THREAD_TOKEN";
            
            // undoc'd, and not included in grfMax
            case THREAD_IMPERSONATE:            return L"THREAD_IMPERSONATE";
            case THREAD_DIRECT_IMPERSONATION:   return L"THREAD_DIRECT_IMPERSONATION";
        }
        return Win32Object::MapPermissionName( nPermission );
    }
};

struct FileSystemObject : Win32Object
{
    FileSystemObject(DWORD grfAccess, const wchar_t* pszObjTypeName)
      : Win32Object( grfAccess,
                     SE_FILE_OBJECT,
                     true,
                     false,
                     pszObjTypeName )
    {}

protected:
    void _getTempFileName(wchar_t* psz)
    {
        wchar_t szTempPath[MAX_PATH];
        DWORD nResult = GetTempPath(sizeof szTempPath / sizeof *szTempPath, szTempPath);
        _ASSERT(nResult);
        nResult = GetTempFileName(szTempPath, L"sht", 0, psz);
        _ASSERT(nResult);
    }
    HANDLE OpenObject( const wchar_t* psz, DWORD grfAccess )
    {
        HANDLE h = CreateFile(psz, grfAccess,
                                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                0, OPEN_EXISTING, 0, 0);
        return (INVALID_HANDLE_VALUE == h) ? 0 : h;
    }
    const wchar_t* MapPermissionName( DWORD nPermission )
    {
        switch ( nPermission )
        {
            case FILE_READ_DATA:            return L"FILE_READ_DATA";
            case FILE_WRITE_DATA:           return L"FILE_WRITE_DATA";
            case FILE_APPEND_DATA:          return L"FILE_APPEND_DATA";
            case FILE_READ_EA:              return L"FILE_READ_EA";
            case FILE_WRITE_EA:             return L"FILE_WRITE_EA";
            case FILE_EXECUTE:              return L"FILE_EXECUTE";
            case FILE_READ_ATTRIBUTES:      return L"FILE_READ_ATTRIBUTES";
            case FILE_WRITE_ATTRIBUTES:     return L"FILE_WRITE_ATTRIBUTES";
        }
        return Win32Object::MapPermissionName( nPermission );
    }
};

struct File : FileSystemObject
{
    File()
      : FileSystemObject( 0x1F019F,
                     L"File" )
    {}

    HANDLE CreateObject( bool bInherit, const wchar_t* pszSuggestedName = 0, wchar_t* pszActualName = 0 )
    {
        wchar_t szTempFileName[MAX_PATH];
        _getTempFileName(szTempFileName);
        pszSuggestedName = szTempFileName;
        if ( pszActualName )
            lstrcpy( pszActualName, pszSuggestedName );
        SecurityAttributes sa( bInherit );
        HANDLE h = CreateFile(pszSuggestedName, m_grfMax,
                                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                &sa, OPEN_ALWAYS, 0, 0);
        return (INVALID_HANDLE_VALUE == h) ? 0 : h;
    }
    void CloseObject( HANDLE h, const wchar_t* psz )
    {
        CloseHandle(h);
        DeleteFile(psz);
    }
    bool UseObject( HANDLE h )
    {
        const char sz[] = "TEST";
        DWORD cb = sizeof sz;
        return 0 != WriteFile(h, sz, cb, &cb, 0);
    }
};

struct RegistryKey : Win32Object
{
    RegistryKey()
      : Win32Object( 0x0F003F, SE_REGISTRY_KEY, true, false, L"Registry Key" )
    {}

    HANDLE CreateObject( bool bInherit, const wchar_t* pszSuggestedName = 0, wchar_t* pszActualName = 0 )
    {
        wchar_t sz[256];
        wsprintf(sz, L"software\\%s", pszSuggestedName ? pszSuggestedName : L"SecurityHandleTest");
        if ( pszActualName )
            lstrcpy( pszActualName, sz );
        SecurityAttributes sa( bInherit );
        HKEY h;
        const DWORD err = RegCreateKeyEx(HKEY_LOCAL_MACHINE, sz,
            0, L"", 0, m_grfMax, &sa, &h, 0);
        return err ? 0 : h;
    }
    HANDLE OpenObject( const wchar_t* psz, DWORD grfAccess )
    {
        HKEY h;
        const DWORD err = RegOpenKeyEx(HKEY_LOCAL_MACHINE, psz, 0, grfAccess, &h);
        return err ? 0 : h;
    }
    bool UseObject( HANDLE h )
    {
        DWORD cb;
        DWORD err = RegQueryValueEx( reinterpret_cast<HKEY>(h), 0, 0, 0, 0, &cb );
        if (err)
            SetLastError(err);
        return 0 == err;
    }
    const wchar_t* MapPermissionName( DWORD nPermission )
    {
        switch ( nPermission )
        {
            case KEY_QUERY_VALUE:        return L"KEY_QUERY_VALUE";
            case KEY_SET_VALUE:          return L"KEY_SET_VALUE";
            case KEY_CREATE_SUB_KEY:     return L"KEY_CREATE_SUB_KEY";
            case KEY_ENUMERATE_SUB_KEYS: return L"KEY_ENUMERATE_SUB_KEYS";
            case KEY_NOTIFY:             return L"KEY_NOTIFY";
            case KEY_CREATE_LINK:        return L"KEY_CREATE_LINK";
        }
        return Win32Object::MapPermissionName( nPermission );
    }
    void CloseObject( HANDLE h, const wchar_t* psz )
    {
        RegCloseKey( reinterpret_cast<HKEY>(h) );
        RegDeleteKey( HKEY_LOCAL_MACHINE, psz );
    }
};

struct WindowStation : Win32Object
{
    WindowStation()
      : Win32Object( 0x0F037F, SE_WINDOW_OBJECT, true, true, L"Window Station" )
    {}

    HANDLE CreateObject( bool bInherit, const wchar_t* pszSuggestedName = 0, wchar_t* pszActualName = 0 )
    {
        wchar_t sz[256];
        if ( pszSuggestedName )
             lstrcpy( sz, pszSuggestedName );
        else lstrcpy( sz, L"SecHandleTestWinsta" );
        if ( pszActualName )
            lstrcpy( pszActualName, sz );

        SecurityAttributes sa( bInherit );
        return CreateWindowStation( sz, 0, m_grfMax, &sa );
    }
    HANDLE OpenObject( const wchar_t* psz, DWORD grfAccess )
    {
        wchar_t sz[256];
        lstrcpy( sz, psz );
        return OpenWindowStation( sz, FALSE, grfAccess );
    }
    bool UseObject( HANDLE h )
    {
        HWINSTA hwsOrg = GetProcessWindowStation();
        if ( !SetProcessWindowStation( reinterpret_cast<HWINSTA>(h) ) )
            return false;

        bool bOk = false;
        if ( OpenClipboard( 0 ) )
        {
            bOk = true;
            CloseClipboard();
        }
        SetProcessWindowStation( hwsOrg );
        return bOk;
    }
    const wchar_t* MapPermissionName( DWORD nPermission )
    {
        switch ( nPermission )
        {
            case WINSTA_ENUMDESKTOPS:       return L"WINSTA_ENUMDESKTOPS";
            case WINSTA_READATTRIBUTES:     return L"WINSTA_READATTRIBUTES";
            case WINSTA_ACCESSCLIPBOARD:    return L"WINSTA_ACCESSCLIPBOARD";
            case WINSTA_CREATEDESKTOP:      return L"WINSTA_CREATEDESKTOP";
            case WINSTA_WRITEATTRIBUTES:    return L"WINSTA_WRITEATTRIBUTES";
            case WINSTA_ACCESSGLOBALATOMS:  return L"WINSTA_ACCESSGLOBALATOMS";
            case WINSTA_EXITWINDOWS:        return L"WINSTA_EXITWINDOWS";
            case WINSTA_ENUMERATE:          return L"WINSTA_ENUMERATE";
            case WINSTA_READSCREEN:         return L"WINSTA_READSCREEN";
        }
        return Win32Object::MapPermissionName( nPermission );
    }
    void CloseObject( HANDLE h, const wchar_t* )
    {
        CloseWindowStation( reinterpret_cast<HWINSTA>(h) );
    }
};

Win32Object* Win32Object::Create( ObjectTypes ot )
{
    switch ( ot )
    {
        case otProcess:         return new Process;
        case otThread:          return new Thread;
        case otMutex:           return new Mutex;
        case otSemaphore:       return new Semaphore;
        case otEvent:           return new Event;
        case otSection:         return new Section;
        case otTimer:           return new WaitableTimer;
        case otToken:           return new Token;
        case otFile:            return new File;
        case otRegistryKey:     return new RegistryKey;
        case otWinSta:          return new WindowStation;
    }
    return 0;
}




/*
struct Dir : FileSystemObject
{
    Dir()
      : FileSystemObject( 0x1F01FF,
                     L"Directory" )
    {}

    HANDLE CreateObject( bool bInherit, const wchar_t* pszSuggestedName = 0, wchar_t* pszActualName = 0 )
    {
        wchar_t szTempFileName[MAX_PATH];
        _getTempFileName(szTempFileName);
        DeleteFile(szTempFileName); // GetTempFileName creates a file, but we want a dir
        pszSuggestedName = szTempFileName;
        if ( pszActualName )
            lstrcpy( pszActualName, pszSuggestedName );
        SecurityAttributes sa( bInherit );
        if (!CreateDirectory(pszSuggestedName, &sa))
            return 0;
        // explicitly set a NULL DACL
        SetNamedSecurityInfo(szTempFileName, SE_FILE_OBJECT,
            DACL_SECURITY_INFORMATION, 0, 0, 0, 0);
        HANDLE h = CreateFile(pszSuggestedName, FILE_LIST_DIRECTORY, 0, 0, OPEN_EXISTING, 0, 0);
        return (INVALID_HANDLE_VALUE == h) ? 0 : h;
    }
    const wchar_t* MapPermissionName( DWORD nPermission )
    {
        switch ( nPermission )
        {
            case FILE_LIST_DIRECTORY:       return L"FILE_LIST_DIRECTORY";
            case FILE_ADD_FILE:             return L"FILE_ADD_FILE";
            case FILE_ADD_SUBDIRECTORY:     return L"FILE_ADD_SUBDIRECTORY";
            case FILE_TRAVERSE:             return L"FILE_TRAVERSE";
            case FILE_DELETE_CHILD:         return L"FILE_DELETE_CHILD";
        }
        return FileSystemObject::MapPermissionName( nPermission );
    }
};

*/