#pragma once

#include <string>
using namespace std;

interface IHandleTest;
struct Win32Object;
struct SurrogateInfo;

class Tester
{
public:
	enum HandleXMIT // inproc items ordered first
	{
		hxAll,
		hxDirect,
		hxByName,
		hxByDupHandle,
		hxByInheritance,
		hxByDupdInheritance
	};

	Tester( int nObjectType,
			bool bCrossProcess,
			HandleXMIT handleXMIT,
			bool bCrossWinsta,
            bool bAuditing,
			DWORD grfOptions,
			const wchar_t* pszAuthority,
			const wchar_t* pszPrincipal,
			const wchar_t* pszPassword )
	  : m_nObjectType( nObjectType ),
		m_bCrossProcess( bCrossProcess ),
		m_handleXMIT( handleXMIT ),
		m_bCrossWinsta( bCrossWinsta ),
		m_grfOptions( grfOptions ),
		m_bUseAlternateCredentials( 0 != pszAuthority ),
		m_sAuthority(),
		m_sPrincipal(),
		m_sPassword(),
        m_bAuditing(bAuditing)
	{
		if ( m_bUseAlternateCredentials )
		{
			m_sAuthority = pszAuthority;
			m_sPrincipal = pszPrincipal;
			m_sPassword  = pszPassword;
		}
	}
	bool _verifyUserHasRequiredAuthorization();
	bool _isAdministrator( HANDLE htok );
	bool _verifyPrivs( HANDLE htok, const wchar_t** rgpsz, int cElems );
    bool _enablePriv( const wchar_t* pszPriv, TOKEN_PRIVILEGES& tpOld );
    void _restorePriv( const TOKEN_PRIVILEGES& tpOld );

	void _initiateTest( HWND hwndOutput );
	void _initiateTest( ISequentialStream* pss, HandleXMIT hx );
	void _initiateTest( ISequentialStream* pss, HandleXMIT hx, int nObjectType );
	void _testInproc( ISequentialStream* pss, HandleXMIT hx, int nObjectType );
	void _testOOP( ISequentialStream* pss, HandleXMIT hx, int nObjectType );

    void _setupSACL(HANDLE hObj, Win32Object* pObj);
	const wchar_t* _getHandleXMITName( HandleXMIT );
	IHandleTest* _unmarshalInterface( SurrogateInfo& si );

	void _logTestParameters( Win32Object* pObj, HandleXMIT hx, ISequentialStream* pss );
	void _log( ISequentialStream* pss, const wchar_t* psz );
	void _logf( ISequentialStream* pss, const wchar_t* psz, ... );
	void _logError( ISequentialStream* pss, const wchar_t* pszFcn, DWORD dwErr = GetLastError() );

private:
	int			m_nObjectType;
	bool		m_bCrossProcess;
	HandleXMIT	m_handleXMIT;
	bool		m_bCrossWinsta;
    bool        m_bAuditing;
	DWORD		m_grfOptions;
	bool		m_bUseAlternateCredentials;
	wstring		m_sAuthority;
	wstring		m_sPrincipal;
	wstring		m_sPassword;
};
