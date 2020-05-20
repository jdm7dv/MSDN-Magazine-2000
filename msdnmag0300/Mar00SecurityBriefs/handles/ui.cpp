#include "precomp.h"
#include "tester.h"
#include "include/handles.h"
#include "resource.h"

inline bool _isChecked( HWND hwnd )
{
	return BST_CHECKED == Button_GetCheck( hwnd );
}

inline bool _isDlgItemChecked( HWND hwnd, int n )
{
	return _isChecked( GetDlgItem( hwnd, n ) );
}

bool _isRadioButton( HWND hwnd )
{
	wchar_t sz[20];
	if ( !GetClassName( hwnd, sz, sizeof sz / sizeof *sz ) )
		return false;

	if ( lstrcmpi( L"button", sz ) )
		return false;

	const DWORD grfStyle = GetWindowLong( hwnd, GWL_STYLE );

	return ( grfStyle & ( BS_RADIOBUTTON | BS_AUTORADIOBUTTON ) ) ? true : false;
}

int _getRadioButtonSetting( HWND hwnd, int nFirstRadio )
{
	int n = 0;
	for ( HWND hwndRadio = GetDlgItem( hwnd, nFirstRadio );
		  _isRadioButton( hwndRadio );
		  hwndRadio = GetWindow( hwndRadio, GW_HWNDNEXT ) )
	{
		if ( BST_CHECKED == Button_GetCheck( hwndRadio ) )
		{
			n = GetDlgCtrlID( hwndRadio ) - nFirstRadio;
			break;
		}
	}
	return n;
}

void _enableAlternateCredentials( HWND hwnd )
{
	const bool bEnable = _isDlgItemChecked( hwnd, IDC_CROSSPROCESS ) &&
						 _isDlgItemChecked( hwnd, IDC_ALTCRED );

	const int rgItems[] = { IDC_AUTHORITY, IDC_PRINCIPAL, IDC_PASSWORD };
	const int* const end = rgItems + sizeof rgItems / sizeof *rgItems;
	for ( const int* it = rgItems; end != it; ++it )
		EnableWindow( GetDlgItem( hwnd, *it ), bEnable ? TRUE : FALSE );
}	

void _enableCrossProcessItems( HWND hwnd )
{
	const bool bCrossProcess = _isDlgItemChecked( hwnd, IDC_CROSSPROCESS );

	_enableAlternateCredentials( hwnd );

	const int rgItems[] = { IDC_CROSSWINSTA, IDR_INHERITANCE, IDR_DUPDINHERITANCE, IDC_ALTCRED };
	const int* const end = rgItems + sizeof rgItems / sizeof *rgItems;
	for ( const int* it = rgItems; end != it; ++it )
		EnableWindow( GetDlgItem( hwnd, *it ), bCrossProcess ? TRUE : FALSE );
	EnableWindow( GetDlgItem( hwnd, IDR_DIRECT ), bCrossProcess ? FALSE : TRUE );

	if ( bCrossProcess )
	{
		if ( _isDlgItemChecked( hwnd, IDR_DIRECT ) )
			Button_SetCheck( GetDlgItem( hwnd, IDR_NAMEDOBJECT ), BST_CHECKED );
		Button_SetCheck( GetDlgItem( hwnd, IDR_DIRECT ), BST_UNCHECKED );
	}
	else
	{
		if ( _isDlgItemChecked( hwnd, IDR_INHERITANCE ) || _isDlgItemChecked( hwnd, IDR_DUPDINHERITANCE ) )
			Button_SetCheck( GetDlgItem( hwnd, IDR_DIRECT ), BST_CHECKED );
		Button_SetCheck( GetDlgItem( hwnd, IDR_INHERITANCE ), BST_UNCHECKED );
		Button_SetCheck( GetDlgItem( hwnd, IDR_DUPDINHERITANCE ), BST_UNCHECKED );
	}
}

BOOL CALLBACK _dlgProc( HWND hwnd, UINT msg, WPARAM wp, LPARAM lp )
{
	switch ( msg )
	{
		case WM_INITDIALOG:
		{
			SetDlgItemText( hwnd, IDC_AUTHORITY, L"wendoline" );
			SetDlgItemText( hwnd, IDC_PRINCIPAL, L"Alice" );
			SetDlgItemText( hwnd, IDC_PASSWORD,  L"alice" );
			Button_SetCheck( GetDlgItem( hwnd, 203 ), BST_CHECKED );
			Button_SetCheck( GetDlgItem( hwnd, IDR_DIRECT ), BST_CHECKED );
			return TRUE;
		}
		case WM_COMMAND:
		{
			HWND hwndCtrl = reinterpret_cast<HWND>(lp);
			switch ( LOWORD(wp) )
			{
				case IDC_CROSSPROCESS:
					_enableCrossProcessItems( hwnd );
					break;
				case IDC_ALTCRED:
					_enableCrossProcessItems( hwnd );
					break;
				case IDOK:
				{
					EnableWindow( GetDlgItem( hwnd, IDOK ), FALSE );

					const bool bCrossProcess	   = _isDlgItemChecked( hwnd, IDC_CROSSPROCESS );
					const bool bCrossWindowStation = _isDlgItemChecked( hwnd, IDC_CROSSWINSTA );
					const bool bAltCred			   = _isDlgItemChecked( hwnd, IDC_ALTCRED );
					const bool bAuditing		   = _isDlgItemChecked( hwnd, IDC_AUDITING );

					DWORD grfOptions = 0;
					if ( _isDlgItemChecked( hwnd, IDC_DETAILEDOUTPUT ) )
						grfOptions |= HTO_DETAILEDOUTPUT;

					const int nItemToTest = _getRadioButtonSetting( hwnd, 201 ) + 1;
					const int nHandleXMIT = _getRadioButtonSetting( hwnd, IDR_DIRECT ) + 1;

					wchar_t szAuthority[256]; GetDlgItemText( hwnd, IDC_AUTHORITY, szAuthority, sizeof szAuthority / sizeof *szAuthority );
					wchar_t szPrincipal[256]; GetDlgItemText( hwnd, IDC_PRINCIPAL, szPrincipal, sizeof szPrincipal / sizeof *szPrincipal );
					wchar_t szPassword[256];  GetDlgItemText( hwnd, IDC_PASSWORD,  szPassword,  sizeof szPassword  / sizeof *szPassword );
					
					Tester t(	nItemToTest,
								bCrossProcess,
								Tester::HandleXMIT( nHandleXMIT ),
								bCrossWindowStation,
                                bAuditing,
								grfOptions,
								bAltCred ? szAuthority : 0,
								bAltCred ? szPrincipal : 0,
								bAltCred ? szPassword  : 0 );
					
					t._initiateTest( GetDlgItem( hwnd, IDC_OUTPUT ) );

					EnableWindow( GetDlgItem( hwnd, IDOK ), TRUE );
					SetFocus( hwnd );
					break;
				}
				case IDCANCEL:
					EndDialog( hwnd, IDCANCEL );
					break;
			}
			return TRUE;
		}
	}
	return FALSE;
}

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, char*, int )
{
	CoInitialize( 0 ); // run in STA due to user interface
	CoInitializeSecurity( 0, -1, 0, 0, RPC_C_AUTHN_LEVEL_NONE,
							RPC_C_IMP_LEVEL_IDENTIFY, 0, 0, 0 );
	DialogBox( hInst, MAKEINTRESOURCE(100), 0, _dlgProc );
	CoUninitialize();
	return 0;	
}

