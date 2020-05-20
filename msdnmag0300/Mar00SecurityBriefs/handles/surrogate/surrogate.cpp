#include "precomp.h"
#include "..\include\surrogateInfo.h"
#include "..\include\Win32Objects.h"
#include "..\include\HandleTest.h"
#include "..\include\handles.h"
#include "..\include\handles_i.c"

HMODULE _loadDllAndCreateTest( IHandleTest** ppht )
{
	HMODULE hdll = LoadLibrary( L"HandleTest.dll" );
	_ASSERTE(( "LoadLibrary", hdll ));

	CREATEOBJECTFCN CreateObject = reinterpret_cast<CREATEOBJECTFCN>( GetProcAddress( hdll, "CreateObject" ) );
	_ASSERTE(( "GetProcAddress", CreateObject ));

	HRESULT hr = CreateObject( IID_IHandleTest, (void**)ppht );
	_ASSERTE(( "CreateObject", SUCCEEDED( hr ) ));

	return hdll;
}

void _sendTestObjectToCreator( SurrogateInfo* psi,
                               IHandleTest* pht )
{
    // given a previously mapped block of shared memory,
    // drop a marshaled OBJREF into it
    IStream* pstm = 0;
	HRESULT hr = CreateStreamOnHGlobal( 0, FALSE, &pstm );
	_ASSERTE(( "CreateStreamOnHGlobal", SUCCEEDED( hr ) ));

	hr = CoMarshalInterface( pstm, IID_IHandleTest, pht,
                             MSHCTX_LOCAL, 0, MSHLFLAGS_NORMAL );
	_ASSERTE(( "CoMarshalInterface", SUCCEEDED( hr ) ));
	pht->Release(); pht = 0;

    // see how many bytes were written by CoMarshalInterface
	__int64 zero = 0;
	__int64 cb;
	pstm->Seek( *reinterpret_cast<LARGE_INTEGER*>( &zero ),
                STREAM_SEEK_CUR,
                reinterpret_cast<ULARGE_INTEGER*>( &cb ) );

    // copy the OBJREF and its length
    // into the shared memory block
	psi->cbObjref = (DWORD) cb;
	HGLOBAL hmem = 0;
	GetHGlobalFromStream( pstm, &hmem );
	pstm->Release();

	CopyMemory( psi->objref, GlobalLock( hmem ), psi->cbObjref );
	GlobalUnlock( hmem );
	GlobalFree( hmem );
}

int _crtDbgReportHook( int reportType, char *message, int *returnValue )
{
	if ( _CRT_ASSERT == reportType )
	{
		switch ( MessageBoxA( 0, message, "Security Handle Test Surrogate",
			MB_SERVICE_NOTIFICATION | MB_ABORTRETRYIGNORE | MB_ICONSTOP ) )
		{
			case IDABORT:
				ExitProcess( 1 );
				break;
			case IDRETRY:
				*returnValue = 1; // start debugger
				break;
			case IDIGNORE:
				*returnValue = 0; // continue execution
				break;
		}
		return 1; // no further reporting necessary
	}
	return 0;
}

struct Surrogate : ISurrogate
{
	Surrogate()
	  : m_cRefs( 0 ),
		m_hEvent( CreateEvent( 0, TRUE, FALSE, 0 ) )
	{
		_ASSERT( m_hEvent );
	}
	void WaitUntilAllStubsDie()
	{
		_ASSERT( m_hEvent );
		WaitForSingleObject( m_hEvent, INFINITE );
		CloseHandle( m_hEvent );
		m_hEvent = 0;
	}
	STDMETHODIMP QueryInterface( REFIID iid, void** ppv )
	{
		if ( IID_ISurrogate == iid || IID_IUnknown == iid )
			*ppv = static_cast<ISurrogate*>( this );
		else return (*ppv = 0), E_NOINTERFACE;
		reinterpret_cast<IUnknown*>(*ppv)->AddRef();
		return S_OK;
	}
	STDMETHODIMP_(ULONG) AddRef()			{ return 42; }
	STDMETHODIMP_(ULONG) Release()			{ return 42; }
	STDMETHODIMP LoadDllServer( REFCLSID )	{ return E_NOTIMPL; }
	STDMETHODIMP FreeSurrogate()			{ SetEvent( m_hEvent ); return S_OK; }

	long	m_cRefs;
	HANDLE	m_hEvent;
};


int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, char*, int )
{
	// make ASSERT work properly in non-interactive windowstations
	_CrtSetReportHook( _crtDbgReportHook );

    CoInitializeEx(0,0);
	CoInitializeSecurity( 0, -1, 0, 0, RPC_C_AUTHN_LEVEL_NONE,
							RPC_C_IMP_LEVEL_IDENTIFY, 0, 0, 0 );
	Surrogate surrogate;
	HRESULT hr = CoRegisterSurrogate( &surrogate );
	_ASSERT( SUCCEEDED( hr ) );

    // inherited handle of shared section is passed on cmd line
	wchar_t szModuleFileName[MAX_PATH];
	long nSectionHandle = 0;
	swscanf( GetCommandLine(), L"%s %d", szModuleFileName, &nSectionHandle );
	HANDLE hSection = reinterpret_cast<HANDLE>( nSectionHandle );
	_ASSERT( hSection );

    // map the section into memory
	SurrogateInfo* psi = reinterpret_cast<SurrogateInfo*>(
		MapViewOfFile( hSection, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0 ) );
	_ASSERTE(( "Surrogate failed to open shared memory section", psi ));

	IHandleTest* pht = 0;
	HMODULE hdll = _loadDllAndCreateTest( &pht );

	_sendTestObjectToCreator( psi, pht );
	pht->Release();
	pht = 0;

	// tell parent we're ready to go
	SetEvent( psi->hBeginTest );

	// COM will tell us when no external clients exist
	surrogate.WaitUntilAllStubsDie();

	UnmapViewOfFile( psi );
	psi = 0;
	CloseHandle( hSection );

	CoUninitialize();
	return 0;
}
