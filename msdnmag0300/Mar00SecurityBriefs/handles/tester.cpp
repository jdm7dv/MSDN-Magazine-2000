#include "precomp.h"
#include "tester.h"
#include "include/Win32Objects.h"
#include "include/handles.h"
#include "include/handles_i.c"
#include "include/SurrogateInfo.h"
#include "AdjustWinstaDacl.h"

typedef HRESULT (__stdcall *CREATEOBJECTFCN)( REFIID, void** );
const wchar_t* const TESTOBJNAME = L"SecurityHandleTestObject";

struct StreamOnEdit : ISequentialStream
{
    StreamOnEdit( HWND hwnd )
      : m_cRefs( 0 ),
        m_hwnd( hwnd )
    {}
    STDMETHODIMP QueryInterface( REFIID iid, void** ppv )
    {
        if ( IID_ISequentialStream == iid || IID_IUnknown == iid )
            *ppv = static_cast<ISequentialStream*>( this );
        else return (*ppv = 0), E_NOINTERFACE;
        reinterpret_cast<IUnknown*>(*ppv)->AddRef();
        return S_OK;
    }
    STDMETHODIMP_(ULONG) AddRef()
    {
        return ++m_cRefs;
    }
    STDMETHODIMP_(ULONG) Release()
    {
        if ( 0 == m_cRefs )
        {
            delete this;
            return 0;
        }
        return m_cRefs;
    }
    STDMETHODIMP Read(
            void *pv,
            ULONG cb,
            ULONG *pcbRead)
    {
        return E_NOTIMPL;
    }
    STDMETHODIMP Write(
            void const *pv,
            ULONG cb,
            ULONG *pcbWritten)
    {
        const int cchOld = GetWindowTextLength( m_hwnd );
        const int cchNew = cchOld + cb / 2;

        wchar_t* psz = new wchar_t[cchNew+1];
        if ( !psz )
            return E_OUTOFMEMORY;

        GetWindowText( m_hwnd, psz, cchNew );
        CopyMemory( psz + cchOld,
                    pv, cb );
        psz[cchNew] = L'\0';
        Edit_SetText( m_hwnd, psz );
        Edit_SetSel( m_hwnd, cchNew, cchNew );
        Edit_ScrollCaret( m_hwnd );
        UpdateWindow( m_hwnd );
        delete [] psz;

        if ( pcbWritten )
            *pcbWritten = cb;

        return S_OK;
    }

    long m_cRefs;
    HWND m_hwnd;
};

struct HandleTestSite : IHandleTestSite
{
    HandleTestSite( HANDLE h, SE_OBJECT_TYPE objType )
      : m_cRefs( 0 ),
        m_h( h ),
        m_objType( objType )
    {}
    STDMETHODIMP QueryInterface( REFIID iid, void** ppv )
    {
        if ( IID_IHandleTestSite == iid || IID_IUnknown == iid )
            *ppv = static_cast<IHandleTestSite*>( this );
        else return (*ppv = 0), E_NOINTERFACE;
        reinterpret_cast<IUnknown*>(*ppv)->AddRef();
        return S_OK;
    }
    STDMETHODIMP_(ULONG) AddRef()
    {
        return ++m_cRefs;
    }
    STDMETHODIMP_(ULONG) Release()
    {
        if ( 0 == m_cRefs )
        {
            delete this;
            return 0;
        }
        return m_cRefs;
    }

    STDMETHODIMP SetEmptyDacl()
    {
        ACL emptyAcl;
        if ( !InitializeAcl( &emptyAcl, sizeof emptyAcl, ACL_REVISION ) )
            return HRESULT_FROM_WIN32( GetLastError() );
        const DWORD dwErr = SetSecurityInfo( m_h, m_objType,
                                             DACL_SECURITY_INFORMATION,
                                             0, 0, &emptyAcl, 0 );
        return dwErr ? HRESULT_FROM_WIN32( dwErr ) : S_OK;
    }
    STDMETHODIMP SetNULLDacl()
    {
        const DWORD dwErr = SetSecurityInfo( m_h, m_objType,
                                             DACL_SECURITY_INFORMATION,
                                             0, 0, 0, 0 );
        return dwErr ? HRESULT_FROM_WIN32( dwErr ) : S_OK;
    }
    long            m_cRefs;
    HANDLE          m_h;
    SE_OBJECT_TYPE  m_objType;
};

#if (_WIN32_WINNT < 0x0500)
BOOL _checkTokenMembership( HANDLE htok, void* psid, BOOL* pbIsMember )
{
    if ( !pbIsMember )
    {
        SetLastError( ERROR_INVALID_PARAMETER );
        return FALSE;
    }

    if ( !IsValidSid( psid ) )
    {
        SetLastError( ERROR_INVALID_SID );
        return FALSE;
    }

    // this is an NT 4.0 compatible implementation
    DWORD cb;
    if ( GetTokenInformation( htok, TokenGroups, 0, 0, &cb ) )
        return FALSE;

    if ( ERROR_INSUFFICIENT_BUFFER != GetLastError() )
        return FALSE;

    HANDLE hheap = GetProcessHeap();
    if ( !hheap )
        return FALSE;

    TOKEN_GROUPS* ptg = reinterpret_cast<TOKEN_GROUPS*>( HeapAlloc( hheap, 0, cb ) );
    if ( !ptg )
    {
        SetLastError( ERROR_NOT_ENOUGH_MEMORY );
        return FALSE;
    }

    BOOL bOk = FALSE;
    if ( GetTokenInformation( htok, TokenGroups, ptg, cb, &cb ) )
    {
        *pbIsMember = FALSE;
        SID_AND_ATTRIBUTES* const end = ptg->Groups + ptg->GroupCount;
        for ( SID_AND_ATTRIBUTES* it = ptg->Groups; it != end; ++it )
        {
            if ( EqualSid( it->Sid, psid ) )
            {
                *pbIsMember = TRUE;
                break;
            }
        }
        bOk = TRUE;
    }
    
    HeapFree( hheap, 0, ptg );
    return bOk;
}
#else
#define _checkTokenMembership CheckTokenMembership
#endif

bool Tester::_isAdministrator( HANDLE htok )
{
    SID_IDENTIFIER_AUTHORITY ntauth = SECURITY_NT_AUTHORITY;
    void* psid = 0;
    BOOL bOk = AllocateAndInitializeSid( &ntauth, 2,
                                        SECURITY_BUILTIN_DOMAIN_RID,
                                        DOMAIN_ALIAS_RID_ADMINS,
                                        0, 0, 0, 0, 0, 0, &psid );
    _ASSERT( bOk );

    BOOL bIsMember = FALSE;
    const bool bIsAdmin = _checkTokenMembership( htok, psid, &bIsMember ) && bIsMember;

    FreeSid( psid );

    return bIsAdmin;
}

bool Tester::_verifyPrivs( HANDLE htok, const wchar_t** rgpsz, int cElems )
{
    DWORD cb = 0;
    BOOL bOk = GetTokenInformation( htok, TokenPrivileges, 0, 0, &cb );
    _ASSERT( !bOk && ERROR_INSUFFICIENT_BUFFER == GetLastError() );

    HANDLE hheap = GetProcessHeap();
    TOKEN_PRIVILEGES* ptp = reinterpret_cast<TOKEN_PRIVILEGES*>( HeapAlloc( hheap, 0, cb ) );
    _ASSERT( ptp );

    bOk = GetTokenInformation( htok, TokenPrivileges, ptp, cb, &cb );
    _ASSERT( bOk );
    bool bHasPrivs = true;
    const wchar_t** const end = rgpsz + cElems;
    for ( const wchar_t** it = rgpsz; it != end && bHasPrivs; ++it )
    {
        LUID luid;
        bOk = LookupPrivilegeValue( 0, *it, &luid );
        _ASSERT( bOk );

        const LUID_AND_ATTRIBUTES* const end = ptp->Privileges + ptp->PrivilegeCount;
        for ( const LUID_AND_ATTRIBUTES* it = ptp->Privileges; it != end; ++it )
        {
            if ( luid.HighPart == it->Luid.HighPart &&
                 luid.LowPart  == it->Luid.LowPart )
                break;
        }
        if ( end == it )
            bHasPrivs = false;
    }
    HeapFree( hheap, 0, ptp );
    return bHasPrivs;
}

// Useful helper function for enabling a single privilege
bool Tester::_enablePriv( const wchar_t* pszPriv,
                          TOKEN_PRIVILEGES& tpOld )
{
    HANDLE htok;
    BOOL bOk = OpenProcessToken(GetCurrentProcess(),
        TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &htok);
    _ASSERT(bOk);

    TOKEN_PRIVILEGES tp;
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    bOk = LookupPrivilegeValue( 0, pszPriv, &tp.Privileges[0].Luid );
    _ASSERT(bOk);

    DWORD cbOld = sizeof tpOld;
    bOk = AdjustTokenPrivileges( htok, FALSE, &tp,
                                 cbOld, &tpOld, &cbOld );
    _ASSERT(bOk);

    CloseHandle(htok);

    // Note that AdjustTokenPrivileges may succeed, and yet
    // some privileges weren't actually adjusted.
    // You've got to check GetLastError() to be sure!
    return ( ERROR_NOT_ALL_ASSIGNED != GetLastError() );
}

// Corresponding restoration helper function
void Tester::_restorePriv( const TOKEN_PRIVILEGES& tpOld )
{
    HANDLE htok;
    BOOL bOk = OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES, &htok);
    _ASSERT(bOk);
    bOk = AdjustTokenPrivileges( htok, FALSE,
                                 const_cast<TOKEN_PRIVILEGES*>(&tpOld),
                                 0, 0, 0 );
    _ASSERT(bOk);
    CloseHandle(htok);
}

bool Tester::_verifyUserHasRequiredAuthorization()
{
    bool bOk = true;

    HANDLE htok;
    OpenProcessToken( GetCurrentProcess(), TOKEN_QUERY, &htok );

    if ( !_isAdministrator( htok ) )
    {
        MessageBox( 0, L"You need to be an administrator to run this program.",
                       L"Security Handle Test", MB_SETFOREGROUND | MB_ICONSTOP );
        bOk = false;
    }

    if ( bOk )
    {
        if ( m_bCrossProcess && m_bUseAlternateCredentials )
        {
            const wchar_t* rgpsz[] = { SE_TCB_NAME, SE_INCREASE_QUOTA_NAME, SE_ASSIGNPRIMARYTOKEN_NAME };
            if ( !_verifyPrivs( htok, rgpsz, sizeof rgpsz / sizeof *rgpsz ) )
            {
                MessageBox( 0, L"You need to grant yourself the following privileges before using alternate credentials:\n"
                               L"Act as part of the operating system\n"
                               L"Increase quotas\n"
                               L"Replace a process level token\n\n"
                               L"After granting yourself these privileges, log off and back on again,\n"
                               L"then come back and try running this program again.",
                               L"Security Handle Test", MB_SETFOREGROUND | MB_ICONSTOP );
                bOk = false;
            }
        }
        if ( m_bAuditing )
        {
            const wchar_t* rgpsz[] = { SE_SECURITY_NAME };
            if ( !_verifyPrivs( htok, rgpsz, sizeof rgpsz / sizeof *rgpsz ) )
            {
                MessageBox( 0, L"You need to grant yourself the following privilege before using the Auditing feature:\n"
                               L"Manage auditing and security log\n"
                               L"After granting yourself this privilege, log off and back on again,\n"
                               L"then come back and try running this program again.",
                               L"Security Handle Test", MB_SETFOREGROUND | MB_ICONSTOP );
                bOk = false;
            }
        }
    }
    CloseHandle( htok );
    return bOk;
}

void Tester::_initiateTest( HWND hwndOutput )
{
    if ( !_verifyUserHasRequiredAuthorization() )
        return;

    SetWindowText( hwndOutput, L"" );

    ISequentialStream* pss = new StreamOnEdit( hwndOutput );
    _ASSERT( pss );
    pss->AddRef();

    // determine mode of transmission
    if ( hxAll == m_handleXMIT )
    {
        const int first = m_bCrossProcess ? int( hxByName )            : int( hxDirect );
        const int last  = m_bCrossProcess ? int( hxByDupdInheritance ) : int( hxByDupHandle );
        for ( int i = first; i <= last; ++i )
            _initiateTest( pss, HandleXMIT( i ) );
    }
    else _initiateTest( pss, m_handleXMIT );

    pss->Release();
}

void Tester::_initiateTest( ISequentialStream* pss, HandleXMIT hx )
{
    if ( m_nObjectType )
        _initiateTest( pss, hx, m_nObjectType );
    else
    {
        // test all object types
        const int first = int( Win32Object::__otFirst );
        const int last  = int( Win32Object::__otLast );
        for ( int i = first; i <= last; ++i )
            _initiateTest( pss, hx, i );
    }
}

void Tester::_initiateTest( ISequentialStream* pss, HandleXMIT hx, int nObjectType )
{
    if ( m_bCrossProcess )
         _testOOP   ( pss, hx, nObjectType );
    else _testInproc( pss, hx, nObjectType );
}

void Tester::_testInproc( ISequentialStream* pss, HandleXMIT hx, int nObjectType )
{
    HMODULE hdll = LoadLibrary( L"HandleTest.dll" );
    if ( !hdll )
    {
        _logError( pss, L"LoadLibrary" );
        return;
    }
    CREATEOBJECTFCN CreateObject = reinterpret_cast<CREATEOBJECTFCN>( GetProcAddress( hdll, "CreateObject" ) );
    if ( !CreateObject )
    {
        _logError( pss, L"GetProcAddress" );
        FreeLibrary( hdll );
        return;
    }
    IHandleTest* pht = 0;
    HRESULT hr = CreateObject( IID_IHandleTest, (void**)&pht );
    if ( FAILED( hr ) )
    {
        _logError( pss, L"CreateObject", hr );
        FreeLibrary( hdll );
        return;
    }

    Win32Object* pObj = Win32Object::Create( Win32Object::ObjectTypes( nObjectType ) );
    if ( !pObj )
    {
        _logf( pss, L"%d object type not supported...", nObjectType );
        pht->Release();
        FreeLibrary( hdll );
        return;
    }

    _logTestParameters( pObj, hx, pss );

    if ( ( hxByName == hx ) && !pObj->CanBeNamed() )
    {
        _log( pss, L"INFO: this object type can't be transmitted by name (skipped test)" );
        delete pObj;
        pht->Release();
        FreeLibrary( hdll );
        return;
    }

    wchar_t szObjName[256];
    HANDLE hObj = pObj->CreateObject( false, TESTOBJNAME, szObjName );
    if ( hObj )
    {
        if (m_bAuditing)
            _setupSACL(hObj, pObj);

        IHandleTestSite* pTestSite = new HandleTestSite( hObj, pObj->GetObjectType() );
        _ASSERT( pTestSite );
        pTestSite->AddRef();

        switch ( hx )
        {
            case hxDirect:
                pht->SetHandle( long( hObj ) );
                hObj = 0;
                break;

            case hxByName:
                pht->SetName( szObjName );
                break;

            case hxByDupHandle:
            {
                HANDLE hDup = 0;
                if ( DuplicateHandle( GetCurrentProcess(), hObj,
                                      GetCurrentProcess(), &hDup,
                                      0,
                                      FALSE, DUPLICATE_SAME_ACCESS ) )
                {
                    pht->SetHandle( long( hDup ) );
                }
                else _logError( pss, L"DuplicateHandle" );
                break;
            }

            default:
                _ASSERT( FALSE );
                break;
        }

        pht->RunTest( pTestSite, nObjectType, m_grfOptions, pss );

        pTestSite->Release();

        if ( hObj )
        {
            pObj->CloseObject( hObj, szObjName );
            hObj = 0;
        }
    }
    else _logError( pss, L"object creation" );

    delete pObj;
    pht->Release();
    FreeLibrary( hdll );
}

void Tester::_testOOP( ISequentialStream* pss, HandleXMIT hx, int nObjectType )
{
    // create the object
    Win32Object* pObj = Win32Object::Create( Win32Object::ObjectTypes( nObjectType ) );
    if ( !pObj )
    {
        _logf( pss, L"%d object type not supported...", nObjectType );
        return;
    }

    _logTestParameters( pObj, hx, pss );

    if ( ( hxByName == hx ) && !pObj->CanBeNamed() )
    {
        _log( pss, L"INFO: this object type can't be transmitted by name (skipped test)" );
        delete pObj;
        return;
    }

    HANDLE htokSurrogate = 0;
    if ( m_bUseAlternateCredentials )
    {
        if ( !LogonUser(    const_cast<wchar_t*>( m_sPrincipal.c_str() ),
                            const_cast<wchar_t*>( m_sAuthority.c_str() ),
                            const_cast<wchar_t*>( m_sPassword.c_str() ),
                            LOGON32_LOGON_INTERACTIVE, 0,
                            &htokSurrogate ) )
        {
            if ( ERROR_LOGON_FAILURE == GetLastError() )
            {
                _logError( pss, L"ERROR: alternate credential logon failed - check user name and password" );
                delete pObj;
                return;
            }
            else _ASSERT( FALSE );
        }
    }

    wchar_t szObjName[256];
    HANDLE hObj = pObj->CreateObject( hxByInheritance == hx, TESTOBJNAME, szObjName );
    if ( !hObj )
    {
        _logError( pss, L"object creation" );
        delete pObj;
        if ( htokSurrogate )
            CloseHandle( htokSurrogate );
        return;
    }

    if (m_bAuditing)
        _setupSACL(hObj, pObj);

    // set up the surrogate process's world
    HWINSTA hws = 0;
    HDESK hd = 0;
    bool bNeedToCleanupWinstaDacl = false;

    // unless otherwise specified, run surrogate in winsta0
    STARTUPINFO si = { sizeof si };
    if ( m_bCrossWinsta )
    {
        // create a window station / desktop pair
        hws = CreateWindowStation( L"SHTWinsta", 0, WINSTA_ALL_ACCESS, 0 );
        HWINSTA hwsOld = GetProcessWindowStation();
        SetProcessWindowStation( hws );
        hd = CreateDesktop( L"Default", 0, 0, 0, DESKTOP_ALL_ACCESS, 0 );
        SetProcessWindowStation( hwsOld );
        _ASSERT( hws );
        _ASSERT( hd );

        // make sure both have a NULL DACL to make it easy to connect
        SetSecurityInfo( hws, SE_WINDOW_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, 0, 0 );
        SetSecurityInfo( hd, SE_WINDOW_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, 0, 0 );

        si.lpDesktop = L"SHTWinsta\\Default";
    }
    else if ( m_bUseAlternateCredentials )
    {
        // allow new logon session to use winsta0
        _grantSessionSIDAccessToWinstationAndDesktop( htokSurrogate, true );
        bNeedToCleanupWinstaDacl = true;
    }

    // create an inheritable section object
    SECURITY_ATTRIBUTES saInherit = { sizeof saInherit, 0, TRUE };
    HANDLE hSection = CreateFileMapping( reinterpret_cast<HANDLE>( 0xFFFFFFFF ),
        &saInherit, PAGE_READWRITE, 0, sizeof SurrogateInfo, 0 );
    _ASSERT( hSection );

    SurrogateInfo* psi = reinterpret_cast<SurrogateInfo*>(
        MapViewOfFile( hSection, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0 ) );
    _ASSERT( psi );

    // create an inheritable event for synchronizing the surrogate process
    psi->hBeginTest = CreateEvent( &saInherit, TRUE, FALSE, 0 );
    _ASSERT( psi->hBeginTest );

    BOOL bOk = FALSE;
    HANDLE hInheritableDuplicate = 0;
    if ( hxByDupdInheritance == hx )
    {
        // original handle isn't inheritable, so duplicate a new handle that IS inheritable
        bOk = DuplicateHandle( GetCurrentProcess(), hObj,
                               GetCurrentProcess(), &hInheritableDuplicate,
                               0, TRUE, DUPLICATE_SAME_ACCESS );
        _ASSERT( bOk );
    }

    // create surrogate process
    PROCESS_INFORMATION pi;
    wchar_t szCmd[256];
    wsprintf( szCmd, L"surrogate.exe %d", hSection );
    if ( m_bUseAlternateCredentials )
         bOk = CreateProcessAsUser( htokSurrogate, 0, szCmd, 0, 0, TRUE, 0, 0, 0, &si, &pi );
    else bOk = CreateProcess(                      0, szCmd, 0, 0, TRUE, 0, 0, 0, &si, &pi );

    if ( bOk )
    {
        // wait for surrogate to signal that it's marshaled a test object into the shared section
        DWORD dwWait = WaitForSingleObject( psi->hBeginTest, 10000 );
        _ASSERT( WAIT_OBJECT_0 == dwWait );

        // unmarshal the interface to set up a communication channel with the surrogate
        IHandleTest* pht = _unmarshalInterface( *psi );

        // set up the test
        HRESULT hr = S_OK;
        switch ( hx )
        {
            case hxByName:
                hr = pht->SetName( szObjName );
                _ASSERT( SUCCEEDED( hr ) );
                break;

            case hxByDupHandle:
            {
                HANDLE hDup = 0;
                if ( DuplicateHandle( GetCurrentProcess(), hObj,
                                      pi.hProcess, &hDup,
                                      0, FALSE, DUPLICATE_SAME_ACCESS ) )
                {
                    hr = pht->SetHandle( long( hDup ) );
                    _ASSERT( SUCCEEDED( hr ) );
                }
                else _logError( pss, L"DuplicateHandle" );
                break;
            }

            case hxByInheritance:
                // original handle is inheritable
                hr = pht->SetHandle( long( hObj ) );
                _ASSERT( SUCCEEDED( hr ) );
                break;

            case hxByDupdInheritance:
            {
                hr = pht->SetHandle( long( hInheritableDuplicate ) );
                _ASSERT( SUCCEEDED( hr ) );
                break;
            }

            default:
                _ASSERT( FALSE );
                break;
        }

        IHandleTestSite* pTestSite = new HandleTestSite( hObj, pObj->GetObjectType() );
        _ASSERT( pTestSite );
        pTestSite->AddRef();

        hr = pht->RunTest( pTestSite, nObjectType, m_grfOptions, pss );
        _ASSERT( SUCCEEDED( hr ) );

        // final release of test object will shut the surrogate down
        pht->Release();
        pTestSite->Release();

        // for simplicity, serialize everything so we don't end up
        // with multiple surrogate processes
        dwWait = WaitForSingleObject( pi.hProcess, 10000 );
        _ASSERT( WAIT_OBJECT_0 == dwWait );

        CloseHandle( pi.hThread );
        CloseHandle( pi.hProcess );
    }
    else _logError( pss, L"surrogate process creation" );

    if ( bNeedToCleanupWinstaDacl )
        _grantSessionSIDAccessToWinstationAndDesktop( htokSurrogate, false );

    if ( hws ) CloseWindowStation( hws );
    if ( hd  ) CloseDesktop( hd );

    UnmapViewOfFile( psi );
    if (hObj) {
        pObj->CloseObject( hObj, szObjName );
    }
    delete pObj;
    if ( hInheritableDuplicate )
        CloseHandle( hInheritableDuplicate );
    CloseHandle( hSection );
    if ( htokSurrogate )
        CloseHandle( htokSurrogate );
}

void Tester::_setupSACL(HANDLE hObj, Win32Object* pObj)
{
    // set up a SACL
    TOKEN_PRIVILEGES tpOld;
    if (_enablePriv(SE_SECURITY_NAME, tpOld))
    {
        HANDLE h;
        if (DuplicateHandle(GetCurrentProcess(), hObj,
                            GetCurrentProcess(), &h,
                            ACCESS_SYSTEM_SECURITY, FALSE, 0)) {

            DWORD mask = pObj->GetMaxAccessMask();
            SID world = {SID_REVISION, 1, SECURITY_WORLD_SID_AUTHORITY, SECURITY_WORLD_RID};
            EXPLICIT_ACCESS rgea[] = { {
                mask,
                SET_AUDIT_SUCCESS,
                NO_INHERITANCE,
                {
                    0, NO_MULTIPLE_TRUSTEE,
                    TRUSTEE_IS_SID,
                    TRUSTEE_IS_GROUP,
                    (TCHAR*)&world
                }
            }, {
                mask,
                SET_AUDIT_FAILURE,
                NO_INHERITANCE,
                {
                    0, NO_MULTIPLE_TRUSTEE,
                    TRUSTEE_IS_SID,
                    TRUSTEE_IS_GROUP,
                    (TCHAR*)&world
                }
            } };
            ACL* psacl = 0;
            DWORD err = SetEntriesInAcl(2, rgea, 0, &psacl);
            if (!err) {
                SetSecurityInfo(h, pObj->GetObjectType(), SACL_SECURITY_INFORMATION, 0, 0, 0, psacl);
                LocalFree(psacl);
            }
            CloseHandle(h);
        }
        _restorePriv(tpOld);
    }
}

const wchar_t* Tester::_getHandleXMITName( HandleXMIT hx )
{
    const wchar_t* psz = 0;
    switch ( hx )
    {
        case hxDirect:              psz = L"xmit directly";                     break;
        case hxByName:              psz = L"xmit by name";                      break;
        case hxByInheritance:       psz = L"xmit by inheritance";               break;
        case hxByDupdInheritance:   psz = L"xmit by inheriting a dup'd handle"; break;
        case hxByDupHandle:         psz = L"xmit via DuplicateHandle";          break;
        default:
            _ASSERT( FALSE );
            break;
    }
    return psz;
}

IHandleTest* Tester::_unmarshalInterface( SurrogateInfo& si )
{
    // copy the marshaled OBJREF out of the shared memory block,
    // and stick an IStream on top of it
    HANDLE hmem = GlobalAlloc( GMEM_FIXED, si.cbObjref );
    _ASSERT( hmem );
    CopyMemory( hmem, si.objref, si.cbObjref );
    IStream* pstm = 0;
    HRESULT hr = CreateStreamOnHGlobal( hmem, TRUE, &pstm );
    _ASSERT( SUCCEEDED( hr ) );

    // unmarshal the OBJREF to get a proxy (be sure you've registered
    // the proxy/stub DLL or this step will fail with E_NOINTERFACE)
    IHandleTest* pht = 0;
    hr = CoUnmarshalInterface( pstm, IID_IHandleTest, (void**)&pht );
    _ASSERT( SUCCEEDED( hr ) );
    pstm->Release();
    return pht;
}

void Tester::_logTestParameters( Win32Object* pObj, HandleXMIT hx, ISequentialStream* pss )
{
    if ( m_bCrossProcess )
    {
        wchar_t szWhom[256] = L"Self";
        if ( m_bUseAlternateCredentials )
            wsprintf( szWhom, L"%s\\%s", m_sAuthority.c_str(), m_sPrincipal.c_str() );

        _logf( pss, L"*** %s, CrossProcess (%s), %s as %s ***",
            pObj->GetObjectTypeName(),
            _getHandleXMITName( hx ),
            m_bCrossWinsta ? L"CrossWinsta," : L"",
            szWhom );
    }
    else
    {
        _logf( pss, L"*** %s, Inproc (%s) ***",
            pObj->GetObjectTypeName(),
            _getHandleXMITName( hx ) );
    }
}

void Tester::_log( ISequentialStream* pss, const wchar_t* psz )
{
    wchar_t sz[1024];
    lstrcat( lstrcpy( sz, psz ), L"\r\n" );
    pss->Write( sz, lstrlen( sz ) * sizeof *sz, 0 );
}

void Tester::_logf( ISequentialStream* pss, const wchar_t* pszFormat, ... )
{
    va_list marker; va_start( marker, pszFormat );
    wchar_t sz[1024];
    vswprintf( sz, pszFormat, marker );
    lstrcat( sz, L"\r\n" );
    pss->Write( sz, lstrlen( sz ) * sizeof *sz, 0 );
}

void Tester::_logError( ISequentialStream* pss, const wchar_t* pszFcn, DWORD dwErr )
{
    wchar_t szErr[256];
    if ( !FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, 0, dwErr, 0, szErr, sizeof szErr / sizeof *szErr, 0 ) )
        lstrcpy( szErr, L"<no description>" );
    wchar_t sz[1024];
    wsprintf( sz, L"%s failed (0x%08X: %s)\r\n", pszFcn, dwErr, szErr );
    pss->Write( sz, lstrlen( sz ) * sizeof *sz, 0 );
}
