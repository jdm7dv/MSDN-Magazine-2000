// adapted from cmdasuser
#include "precomp.h"

ACL* _getUserObjectDacl( HANDLE h, DWORD cbExtra )
{
	// At least one person complained about GetSecurityInfo failing with
	// E_INVALIDARG, so I changed the code to use the older API
	// and this seemed to fix the problem.
	// But the GetSecurityInfo version was soooo much cleaner :-)
	DWORD cb = 0;
	SECURITY_INFORMATION si = DACL_SECURITY_INFORMATION;
	GetUserObjectSecurity( h, &si, 0, cb, &cb );
	_ASSERT( ERROR_INSUFFICIENT_BUFFER == GetLastError() );

	void* psd = HeapAlloc( GetProcessHeap(), 0, cb );
	_ASSERT( psd );

	si = DACL_SECURITY_INFORMATION;
	BOOL bOk = GetUserObjectSecurity( h, &si, psd, cb, &cb );
	_ASSERT( bOk );

	BOOL bPresent, bDefaulted;
	ACL* pdaclOld;
	bOk = GetSecurityDescriptorDacl( psd, &bPresent, &pdaclOld, &bDefaulted );
	_ASSERT( bOk );

	// get the size of the existing DACL
	ACL_SIZE_INFORMATION info;
	bOk = GetAclInformation( pdaclOld, &info, sizeof info, AclSizeInformation );
	_ASSERT( bOk );

	// allocate enough memory for the existing DACL
	// plus whatever extra space the caller requires
	cb = info.AclBytesInUse + cbExtra;
	ACL* pdaclNew = reinterpret_cast<ACL*>( HeapAlloc( GetProcessHeap(), 0, cb ) );
	_ASSERT( pdaclNew );

	bOk = InitializeAcl( pdaclNew, cb, ACL_REVISION );
	_ASSERT( bOk );
	
	// copy over all the old aces to the new DACL
	for ( DWORD i = 0; i < info.AceCount; ++i )
	{
		ACE_HEADER* pace = 0;
		bOk = GetAce( pdaclOld, i, reinterpret_cast<void**>(&pace) );
		_ASSERT( bOk );

		bOk = AddAce( pdaclNew, ACL_REVISION, MAXDWORD, pace, pace->AceSize );
		_ASSERT( bOk );
	}
	HeapFree( GetProcessHeap(), 0, psd );
	return pdaclNew;
}

DWORD _calcAceSizeFromSid( void* psid )
{
	return sizeof( ACCESS_ALLOWED_ACE ) - sizeof( DWORD ) + GetLengthSid( psid );
}

#if _WIN32_WINNT < 0x500
// this is such a simple function, it's bizarre that we had to wait 'till W2K to get it
BOOL AddAccessAllowedAceEx( PACL pAcl, DWORD dwAceRevision, DWORD AceFlags, DWORD AccessMask, PSID pSid )
{
	if ( !AddAccessAllowedAce( pAcl, dwAceRevision, AccessMask, pSid ) )
		return FALSE;
	ACL_SIZE_INFORMATION info;
	if ( !GetAclInformation( pAcl, &info, sizeof info, AclSizeInformation ) )
		return FALSE;
	ACE_HEADER* pace = 0;
	if ( !GetAce( pAcl, info.AceCount - 1, reinterpret_cast<void**>(&pace) ) )
		return FALSE;
	pace->AceFlags = static_cast<BYTE>(AceFlags);
	return TRUE;
}
#endif

void _deleteMatchingAces( ACL* pdacl, void* psid )
{
	ACL_SIZE_INFORMATION info;
	BOOL bOk = GetAclInformation( pdacl, &info, sizeof info, AclSizeInformation );
	_ASSERT( bOk );

	// it's a bit easier to delete aces while iterating backwards
	// so that the iterator doesn't get honked up
	DWORD i = info.AceCount;
	while ( i-- )
	{
		ACCESS_ALLOWED_ACE* pAce = 0;
		bOk = GetAce( pdacl, i, reinterpret_cast<void**>(&pAce) );
		_ASSERT( bOk );
		if ( EqualSid( psid, &pAce->SidStart ) )
			DeleteAce( pdacl, i );
	}
}

void _grantSessionSIDAccessToWinstationAndDesktop( HANDLE htok, bool bGrant )
{
	// get the list of groups from the token
	DWORD cbtgs = 0;
	GetTokenInformation( htok, TokenGroups, 0, 0, &cbtgs );
	_ASSERT( ERROR_INSUFFICIENT_BUFFER == GetLastError() );
	
	TOKEN_GROUPS* ptgs = reinterpret_cast<TOKEN_GROUPS*>(
		HeapAlloc( GetProcessHeap(), 0, cbtgs ) );
	_ASSERT( ptgs );
	BOOL bOk = GetTokenInformation( htok, TokenGroups, ptgs, cbtgs, &cbtgs );
	_ASSERT( bOk );

	// search for the the logon session SID
	const SID_AND_ATTRIBUTES* it = ptgs->Groups;
	const SID_AND_ATTRIBUTES* end = it + ptgs->GroupCount;
	while ( end != it )
	{
		if ( it->Attributes & SE_GROUP_LOGON_ID )
			break;
		++it;
	}
	_ASSERT( end != it );

	void* psidLogonSession = it->Sid;

	HWINSTA hws = GetProcessWindowStation();
	_ASSERT( hws );

	// adjust the DACL on WinSta0 to grant access to the the logon SID
	{
		ACL* pdacl = 0;
		if ( bGrant )
		{
			// get the existing DACL, with enough extra space for adding a couple more aces
			const DWORD cbExtra = 2 * _calcAceSizeFromSid( psidLogonSession );
			pdacl = _getUserObjectDacl( hws, cbExtra );

			// grant the logon session all access to winsta0
			bOk = AddAccessAllowedAce( pdacl, ACL_REVISION,
									   WINSTA_ALL_ACCESS | STANDARD_RIGHTS_REQUIRED,
									   psidLogonSession );
			_ASSERT( bOk );

			// grant the logon session all access to any new desktops created in winsta0
			// by adding an inherit-only ace
			bOk = AddAccessAllowedAceEx( pdacl, ACL_REVISION,
										SUB_CONTAINERS_AND_OBJECTS_INHERIT | INHERIT_ONLY,
										DESKTOP_ALL_ACCESS | STANDARD_RIGHTS_REQUIRED,
										psidLogonSession );
			_ASSERT( bOk );
		}
		else
		{
			pdacl = _getUserObjectDacl( hws, 0 );
			_deleteMatchingAces( pdacl, psidLogonSession );
		}

		// apply the changes to winsta0
		// unlike GetSecurityInfo, SetSecurityInfo has no troubles on SP3 :-)
		DWORD err = SetSecurityInfo( hws, SE_WINDOW_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, pdacl, 0 );
		_ASSERT( !err );

		HeapFree( GetProcessHeap(), 0, pdacl );
	}

	CloseWindowStation( hws );

	HDESK hd = GetThreadDesktop( GetCurrentThreadId() );
	_ASSERT( hd );

	// adjust the DACL on the desktop to grant access to the the logon SID
	{
		ACL* pdacl = 0;
		if ( bGrant )
		{
			// get the existing DACL, with enough extra space for adding a couple more aces
			const DWORD cbExtra = _calcAceSizeFromSid( psidLogonSession );
			pdacl = _getUserObjectDacl( hd, cbExtra );

			// grant the logon session all access to the default desktop
			bOk = AddAccessAllowedAce( pdacl, ACL_REVISION,
										DESKTOP_ALL_ACCESS | STANDARD_RIGHTS_REQUIRED,
										psidLogonSession );
			_ASSERT( bOk );

		}
		else
		{
			pdacl = _getUserObjectDacl( hd, 0 );
			_deleteMatchingAces( pdacl, psidLogonSession );
		}

		// apply the changes to the default desktop
		// unlike GetSecurityInfo, SetSecurityInfo has no troubles on SP3 :-)
		DWORD err = SetSecurityInfo( hd, SE_WINDOW_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, pdacl, 0 );
		_ASSERT( !err );

		HeapFree( GetProcessHeap(), 0, pdacl );
	}

	CloseDesktop( hd );
	HeapFree( GetProcessHeap(), 0, ptgs );
}
