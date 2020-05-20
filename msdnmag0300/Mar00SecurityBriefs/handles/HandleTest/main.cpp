#include "precomp.h"

#include "..\include\handles.h"
#include "..\include\handles_i.c"

HANDLE g_hModule;

extern void _runTest( IHandleTestSite* pSite, long nObjectType,
					  const wchar_t* pszObj, HANDLE hObj,
					  DWORD grfOptions, ISequentialStream* pstm );

struct HandleTest : public IHandleTest
{
	HandleTest()
	  : m_bUsingName( false ),
		m_handle( 0 ),
		m_sName()
	{}

	STDMETHODIMP QueryInterface( REFIID iid, void** ppv )
	{
		if ( IID_IUnknown == iid || IID_IHandleTest == iid )
			 *ppv = static_cast<IHandleTest*>(this);
		else return (*ppv = 0), E_NOINTERFACE;
		AddRef();
		return S_OK;
	}
	STDMETHODIMP_(ULONG) AddRef()  { return 42; }
	STDMETHODIMP_(ULONG) Release() { return 42; }

	STDMETHODIMP GetProcessId( DWORD* ppid );
	STDMETHODIMP SetHandle( long handle );
	STDMETHODIMP SetName( const OLECHAR* psz );
	STDMETHODIMP RunTest( IHandleTestSite* pSite, long nObjectType,
						  DWORD grfOptions, ISequentialStream* pstm );

	bool	m_bUsingName;
	HANDLE	m_handle;
	wstring	m_sName;
};

STDMETHODIMP HandleTest::GetProcessId( DWORD* ppid )
{
	*ppid = GetCurrentProcessId();
	return S_OK;
}

STDMETHODIMP HandleTest::SetHandle( long handle )
{
	m_handle = reinterpret_cast<HANDLE>( handle );
	m_bUsingName = false;
	return S_OK;
}

STDMETHODIMP HandleTest::SetName( const OLECHAR* psz )
{
	m_sName = psz;
	m_bUsingName = true;
	return S_OK;
}

STDMETHODIMP HandleTest::RunTest( IHandleTestSite* pSite, long nObjectType,
	DWORD grfOptions, ISequentialStream* pstm )
{
	const wchar_t* pszObj	= m_bUsingName ? m_sName.c_str() : 0;
	HANDLE hObj				= m_bUsingName ? 0 : m_handle;

	::_runTest( pSite, nObjectType, pszObj, hObj, grfOptions, pstm );
	return S_OK;
}

BOOL WINAPI DllMain( HANDLE hModule, DWORD dwReason, void* )
{
	if ( DLL_PROCESS_ATTACH == dwReason )
		g_hModule = hModule;
	return TRUE;
}

extern "C" STDAPI CreateObject( REFIID iid, void** ppv )
{
	static HandleTest s_test;
	return s_test.QueryInterface( iid, ppv );
}
