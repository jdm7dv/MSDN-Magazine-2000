#pragma once

#include <string>
#include <iostream>
using namespace std;

class Tester
{
public:
	Tester( int nItemToTest,
			bool bCrossProcess,
			int nHandleXMIT,
			bool bCrossWindowStation,
			const wchar_t* pszAuthority,
			const wchar_t* pszPrincipal,
			const wchar_t* pszPassword )
	  : m_nItemToTest( nItemToTest ),
		m_bCrossProcess( bCrossProcess ),
		m_nHandleXMIT( nHandleXMIT ),
		m_bCrossWindowStation( bCrossWindowStation ),
		m_bUseAlternateCredentials( 0 != pszAuthority ),
		m_sAuthority(),
		m_sPrincipal(),
		m_sPassword()
	{
		if ( m_bUseAlternateCredentials )
		{
			m_sAuthority = pszAuthority;
			m_sPrincipal = pszPrincipal;
			m_sPassword  = pszPassword;
		}
	}

	void PerformTest( ostream& os );

private:
	int		m_nItemToTest;
	bool	m_bCrossProcess;
	int		m_nHandleXMIT;
	bool	m_bCrossWindowStation; 
	bool	m_bUseAlternateCredentials;
	wstring m_sAuthority;
	wstring m_sPrincipal;
	wstring m_sPassword;
};
