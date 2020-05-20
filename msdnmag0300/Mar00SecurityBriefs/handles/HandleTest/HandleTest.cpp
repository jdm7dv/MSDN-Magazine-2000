#include "precomp.h"
#include "..\include\handles.h"
#include "..\include\Win32Objects.h"

const SID_MAX_SIZE_IN_BYTES = sizeof(SID) + (SID_MAX_SUB_AUTHORITIES - ANYSIZE_ARRAY) * sizeof(DWORD);

void _log( ISequentialStream* pss, const wchar_t* psz )
{
	wchar_t sz[1024];
	lstrcat( lstrcpy( sz, psz ), L"\r\n" );
	pss->Write( sz, lstrlen( sz ) * sizeof *sz, 0 );
}

void _logf( ISequentialStream* pss, const wchar_t* pszFormat, ... )
{
	va_list marker; va_start( marker, pszFormat );
	wchar_t sz[1024];
	vswprintf( sz, pszFormat, marker );
   	lstrcat( sz, L"\r\n" );
	pss->Write( sz, lstrlen( sz ) * sizeof *sz, 0 );
}

void _logError( ISequentialStream* pss, const wchar_t* pszOperation, DWORD dwErr = GetLastError() )
{
	wchar_t szErr[256];
	if ( !FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, 0, dwErr, 0, szErr, sizeof szErr / sizeof *szErr, 0 ) )
		lstrcpy( szErr, L"<no description>" );
	wchar_t sz[1024];
	wsprintf( sz, L"%s failed (0x%08X: %s)\r\n", pszOperation, dwErr, szErr );
	pss->Write( sz, lstrlen( sz ) * sizeof *sz, 0 );
}

DWORD _lowestNBits( DWORD grf, int nBits )
{
	DWORD result = 0;
	for ( int i = 0; i <= 32 && nBits; ++i )
	{
		const DWORD mask = (1 << i);
		if ( mask & grf )
		{
			result |= mask;
			--nBits;
		}
	}
	return result;
}

DWORD _tryDupHandle( ISequentialStream* pss, HANDLE hObj, DWORD grf )
{
	DWORD result = 0;
	for ( int i = 0; i <= 32; ++i )
	{
		const DWORD mask = (1 << i);
		if ( mask & grf )
		{
			HANDLE hDup = 0;
			if ( DuplicateHandle( GetCurrentProcess(), hObj,
								  GetCurrentProcess(), &hDup,
								  mask, FALSE, 0 ) )
			{
				result |= mask;
				CloseHandle( hDup );
			}
		}
	}
	return result;
}

DWORD _testDupHandle( ISequentialStream* pss, Win32Object& obj, HANDLE hObj, DWORD grfAccess, DWORD grfOptions )
{
	// try duplicating the handle for all possible permissions,
	// one by one
	const DWORD grfResult = _tryDupHandle( pss, hObj, grfAccess );
	if ( HTO_DETAILEDOUTPUT & grfOptions )
	{
		if ( grfResult == grfAccess )
			_log( pss, L"DupHandle succeeded for each possible access permission" );
		else
		{
			wchar_t szAccess[1024];
			obj.MapPermissionNames( grfResult, szAccess );
			_logf( pss, L"Duphandle succeeded for: %s", szAccess );
			obj.MapPermissionNames( grfResult ^ grfAccess, szAccess );
			_logf( pss, L"DupHandle failed for: %s", szAccess );
		}
	}
	return grfResult;
}

void _mainTest( IHandleTestSite* pSite, ISequentialStream* pss,
				Win32Object& obj, HANDLE hObj, DWORD grfOriginalAccess,
				DWORD grfTestAccess, DWORD grfOptions, bool bIsOwner )
{
	wchar_t szAccess[1024];

	// NULL DACL at this point - should be granted all permissions
	DWORD grfResult = _testDupHandle( pss, obj, hObj, grfTestAccess, grfOptions );
	if ( grfResult != grfTestAccess )
	{
		obj.MapPermissionNames( grfResult ^ grfTestAccess, szAccess );
		_logf( pss, L"ERROR: Even with NULL DACL, failed to dup handle for: %s", szAccess );
	}

	if ( HTO_DETAILEDOUTPUT & grfOptions )
		_log( pss, L"Denying everyone all access by setting an empty DACL..." );
	HRESULT hr = pSite->SetEmptyDacl();
	if ( SUCCEEDED( hr ) )
	{
		if ( HTO_DETAILEDOUTPUT & grfOptions )
			_log( pss, L"  succeeded." );
		grfResult = _testDupHandle( pss, obj, hObj, grfTestAccess, grfOptions );
		
		// we expect to only be able to get the original access permissions
		// associated with the incoming handle (as DACL checks aren't performed for those)
		DWORD grfExpectedResults = grfOriginalAccess;
		if ( bIsOwner )
		{
			// owners have implicit permissions
			grfExpectedResults |= READ_CONTROL | WRITE_DAC;
		}
		if ( grfResult != grfExpectedResults )
		{
			_log( pss, L"Interesting emtpy DACL results:" );
			obj.MapPermissionNames( grfOriginalAccess, szAccess );
			_logf( pss, L"  Original handle open for: %s", szAccess );
			obj.MapPermissionNames( grfExpectedResults, szAccess );
			_logf( pss, L"  Expected success for: %s", szAccess );
			obj.MapPermissionNames( grfResult, szAccess );
			_logf( pss, L"  Dup succeeded for: %s", szAccess );
			obj.MapPermissionNames( grfResult ^ grfTestAccess, szAccess );
			_logf( pss, L"  Dup failed for: %s", szAccess );
		}
	}
	else _logError( pss, L"SetEmptyDacl", hr );

	if ( HTO_DETAILEDOUTPUT & grfOptions )
		_log( pss, L"Restoring NULL DACL..." );

	hr = pSite->SetNULLDacl();
	if ( SUCCEEDED( hr ) )
	{
		if ( HTO_DETAILEDOUTPUT & grfOptions )
			_log( pss, L"  succeeded." );
		grfResult = _testDupHandle( pss, obj, hObj, grfTestAccess, grfOptions );

		// once again, all dups should succeed because we've got a NULL DACL
		if ( grfResult != grfTestAccess )
		{
			obj.MapPermissionNames( grfResult ^ grfTestAccess, szAccess );
			_logf( pss, L"ERROR: Even with NULL DACL, failed to dup handle for: %s", szAccess );
		}
	}
	else _logError( pss, L"SetNULLDacl", hr );
}

bool _isOwner( ISequentialStream* pss, HANDLE h, SE_OBJECT_TYPE objType )
{
	bool bIsOwner = false;
	void* psidOwner = 0;
	void* psd = 0;
	DWORD err = GetSecurityInfo( h, objType, OWNER_SECURITY_INFORMATION, &psidOwner, 0, 0, 0, &psd );
	if ( !err )
	{
		HANDLE htok;
		if ( OpenProcessToken( GetCurrentProcess(), TOKEN_QUERY, &htok ) )
		{
			BYTE buf[sizeof(TOKEN_USER) + SID_MAX_SIZE_IN_BYTES];
			DWORD cb = sizeof buf;
			if ( GetTokenInformation( htok, TokenUser, buf, cb, &cb ) )
			{
				if ( EqualSid( reinterpret_cast<TOKEN_USER*>(buf)->User.Sid, psidOwner ) )
					bIsOwner = true;
				else
				{
					GetTokenInformation( htok, TokenGroups, 0, 0, &cb );
					if ( ERROR_INSUFFICIENT_BUFFER == GetLastError() )
					{
						TOKEN_GROUPS* ptg = reinterpret_cast<TOKEN_GROUPS*>( HeapAlloc( GetProcessHeap(), 0, cb ) );
						if ( ptg )
						{
							if ( GetTokenInformation( htok, TokenGroups, ptg, cb, &cb ) )
							{
								SID_AND_ATTRIBUTES* const end = ptg->Groups + ptg->GroupCount;
								for ( SID_AND_ATTRIBUTES* it = ptg->Groups; end != it; ++it )
								{
									if ( it->Attributes & SE_GROUP_OWNER )
									{
										if ( EqualSid( it->Sid, psidOwner ) )
										{
											bIsOwner = true;
											break;
										}
									}
								}
							}
							else _logError( pss, L"GetTokenInformation" );
							HeapFree( GetProcessHeap(), 0, ptg );
						}
						else _logError( pss, L"HeapAlloc", ERROR_OUTOFMEMORY );
					}
					else _logError( pss, L"GetTokenInformation" );
				}
			}
			else _logError( pss, L"GetTokenInformation" );

			CloseHandle( htok );
		}
		else _logError( pss, L"OpenProcessToken" );
		LocalFree( psd );
	}
	else _logError( pss, L"GetSecurityInfo", err );

	return bIsOwner;
}	

void _runTest( IHandleTestSite* pSite, long nObjectType, const wchar_t* pszObj,
	HANDLE hObjOriginal, DWORD grfOptions, ISequentialStream* pss )
{
	Win32Object* pObj = Win32Object::Create( Win32Object::ObjectTypes( nObjectType ) );
	if ( !pObj )
	{
		_logError( pss, L"Win32Object::Create" );
		return;
	}

	const DWORD grfMax			 = pObj->GetMaxAccessMask();
	const DWORD grfMed			 = _lowestNBits( grfMax, 2 );
	const DWORD grfMin			 = _lowestNBits( grfMax, 1 );
	const SE_OBJECT_TYPE objType = pObj->GetObjectType();

	wchar_t szAccess[1024];

	if ( pszObj )
	{
		if ( HTO_DETAILEDOUTPUT & grfOptions )
			_log( pss, L"Opening named object for max access" );
		hObjOriginal = pObj->OpenObject( pszObj, grfMax );
		if ( !hObjOriginal )
			_logError( pss, L"OpenNamedObject" );
	}
	if ( hObjOriginal )
	{
		const bool bIsOwner = _isOwner( pss, hObjOriginal, pObj->GetObjectType() );

        // to test the SACL, try using the object
	    if ( HTO_DETAILEDOUTPUT & grfOptions )
		    _log( pss, L"Trying to use the object..." );
        bool bUsedOk = pObj->UseObject( hObjOriginal );
	    if ( HTO_DETAILEDOUTPUT & grfOptions )
        {
            if ( bUsedOk )
                 _log( pss, L"  succeeded." );
            else _logError( pss, L"UseObject" );
        }

		_mainTest( pSite, pss, *pObj, hObjOriginal, grfMax, grfMax, grfOptions, bIsOwner );

        if ( pObj->CanExpandHandlePermissions() ) {
            const DWORD grfForDup = grfMed;
		    pObj->MapPermissionNames( grfForDup, szAccess );

		    if ( HTO_DETAILEDOUTPUT & grfOptions )
			    _logf( pss, L"*** Duping original handle for %s, and running the same tests with this duplicate handle", szAccess );

		    HANDLE hDup = 0;
		    if ( DuplicateHandle( GetCurrentProcess(), hObjOriginal,
							    GetCurrentProcess(), &hDup,
							    grfForDup, FALSE, 0 ) )
		    {
			    _mainTest( pSite, pss, *pObj, hDup, grfForDup, grfMax, grfOptions, bIsOwner );
			    CloseHandle( hDup );
		    }
		    else _logError( pss, L"DuplicateHandle" );
        }
        else if ( HTO_DETAILEDOUTPUT & grfOptions )
            _logf( pss, L"%s objects do not support expansion of permissions via DuplicateHandle, so I'll skip that test", pObj->GetObjectTypeName() );

		pObj->CloseObject( hObjOriginal, pszObj );
	}
	delete pObj;
}
