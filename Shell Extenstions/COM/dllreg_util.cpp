#include "dllregshex.h"
#include "resource.h"
#include "dllreg_util.h"
#include "errno.h"
//#include <direct.h>
//#include <io.h>
#include <assert.h>
//#include <sys/types.h>
//#include <sys/stat.h>

CRITICAL_SECTION g_critSectionBreak;
extern HINSTANCE g_hmodThisDll;

int WideCharToLocal(LPTSTR pLocal, LPWSTR pWide, DWORD dwChars)
{
	*pLocal = 0;

	#ifdef UNICODE
	lstrcpyn(pLocal, pWide, dwChars);
	#else
	WideCharToMultiByte( CP_ACP, 
						 0, 
						 pWide, 
						 -1, 
						 pLocal, 
						 dwChars, 
						 NULL, 
						 NULL);
	#endif

	return lstrlen(pLocal);
}

////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////
int LocalToWideChar(LPWSTR pWide, LPTSTR pLocal, DWORD dwChars)
{
	*pWide = 0;

	#ifdef UNICODE
	lstrcpyn(pWide, pLocal, dwChars);
	#else
	MultiByteToWideChar( CP_ACP, 
						 0, 
						 pLocal, 
						 -1, 
						 pWide, 
						 dwChars); 
	#endif

	return lstrlenW(pWide);
}

LPWSTR hf_mbtowc(LPWSTR lpw, LPCSTR lpa, int nChars)
{
	assert(lpa != NULL);
	assert(lpw != NULL);
	
	lpw[0] = '\0';
	MultiByteToWideChar(CP_ACP, 0, lpa, -1, lpw, nChars);
	return lpw;
}

LPSTR hf_wctomb(LPSTR lpa, LPCWSTR lpw, int nChars)
{
	assert(lpw != NULL);
	assert(lpa != NULL);
	
	lpa[0] = '\0';
	WideCharToMultiByte(CP_ACP, 0, lpw, -1, lpa, nChars, NULL, NULL);
	return lpa;
}
