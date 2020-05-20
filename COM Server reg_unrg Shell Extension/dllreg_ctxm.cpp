#include "dllreg_xhdr.h"
#include "dllregshex.h"
#include "dllreg_util.h"
#include "resource.h"

extern UINT			g_cRefThisDll;
extern HINSTANCE	g_hmodThisDll;

extern HBITMAP		hBmp_Install;
extern HBITMAP		hBmp_Uninstall;
extern HBITMAP		hBmp_About;
extern HMENU		hSubMenu;

//	IContextMenu
STDMETHODIMP 
CShellExt::QueryContextMenu(HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
	_UNUSED_PARAMETER(idCmdLast);

    UINT idCmd = idCmdFirst;

	char *szMenuText_Popup		= "Re&gister/Unregister...";
    char *szMenuText_Install	= "&Register";
	char *szMenuText_Uninstall	= "&Unregister";
	char *szMenuText_About		= "&About...";

	BOOL bAppendItems = TRUE;

	if((uFlags & 0x000F) == CMF_NORMAL)
		bAppendItems = TRUE;
	else if (uFlags & CMF_VERBSONLY)
		bAppendItems = TRUE;
	else if (uFlags & CMF_EXPLORE)
		bAppendItems = TRUE;
	else
		bAppendItems = FALSE;

    if(bAppendItems)
    {
        InsertMenu(hMenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);  
		indexMenu++;

		HMENU hSubMenu = CreateMenu();
		if(hSubMenu)
		{
			InsertMenu(hSubMenu, 0, MF_STRING	 | MF_BYPOSITION, idCmd++, szMenuText_Install);
			SetMenuItemBitmaps(hSubMenu, 0, MF_BYPOSITION, hBmp_Install, hBmp_Install);

			InsertMenu(hSubMenu, 1, MF_STRING	 | MF_BYPOSITION, idCmd++, szMenuText_Uninstall);
			SetMenuItemBitmaps(hSubMenu, 1, MF_BYPOSITION, hBmp_Uninstall, hBmp_Uninstall);

			InsertMenu(hSubMenu, 2, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);

			InsertMenu(hSubMenu, 3, MF_STRING	 | MF_BYPOSITION, idCmd++, szMenuText_About);
			SetMenuItemBitmaps(hSubMenu, 3, MF_BYPOSITION, hBmp_About, hBmp_About);
		}
		
		InsertMenu(hMenu, indexMenu, MF_STRING | MF_POPUP | MF_BYPOSITION, (UINT_PTR)hSubMenu, szMenuText_Popup);
		indexMenu++;

        InsertMenu(hMenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL);
		indexMenu++;

        return ResultFromShort(idCmd - idCmdFirst);
   }

   return NOERROR;
}

STDMETHODIMP 
CShellExt::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
	HRESULT hr = E_INVALIDARG;
	if (!HIWORD(lpcmi->lpVerb))
    {
        UINT idCmd = LOWORD(lpcmi->lpVerb);
        switch (idCmd)
        {
            case 0:
                hr = DoInstall(lpcmi->hwnd, lpcmi->lpDirectory, lpcmi->lpVerb, lpcmi->lpParameters, lpcmi->nShow);
                break;
            case 1:
                hr = DoUninstall(lpcmi->hwnd, lpcmi->lpDirectory, lpcmi->lpVerb, lpcmi->lpParameters, lpcmi->nShow);
                break;
            case 2:
                hr = DoAbout(lpcmi->hwnd, lpcmi->lpDirectory, lpcmi->lpVerb, lpcmi->lpParameters, lpcmi->nShow);
                break;
			default:
                break;
        }
    }
    return hr;
}

STDMETHODIMP 
CShellExt::GetCommandString(UINT idCmd, UINT uFlags, UINT FAR *reserved, LPSTR pszName, UINT cchMax)
{
	_UNUSED_PARAMETER(reserved);
	_UNUSED_PARAMETER(uFlags);

	*pszName = 0;

	cchMax   = 40;
	char psz[40];

    switch (idCmd)
    {
        case 0:
			LoadString(g_hmodThisDll, IDCMD_INSTALL, psz, cchMax);
            break;
        case 1:
			LoadString(g_hmodThisDll, IDCMD_UNINSTALL, psz, cchMax);
            break;
        case 2:
			LoadString(g_hmodThisDll, IDCMD_ABOUT, psz, cchMax);
            break;
		default:
			break;
    }

	wcscpy((unsigned short *)pszName, _WCSTR(psz));
    return NOERROR;
}

