#ifndef __NTServiceManager_Utils_Defined__
#define __NTServiceManager_Utils_Defined__

#include <malloc.h>

#define DLLREGUNREGNAME	TEXT("DLL Registerer")

#define _UNUSED_PARAMETER(p)	\
	{							\
		(p) = (p);				\
	}

extern CRITICAL_SECTION g_critSectionBreak;
template <class T> T GET_SAFE( T a ) {EnterCriticalSection(&g_critSectionBreak); T z = a; LeaveCriticalSection(&g_critSectionBreak); return z;}
template <class T> void SET_SAFE( T & a , T b) {EnterCriticalSection(&g_critSectionBreak); a = b; LeaveCriticalSection(&g_critSectionBreak);}

#define ARRAYSIZE(a)    (sizeof(a)/sizeof(a[0]))

extern int  LocalToWideChar(LPWSTR pWide, LPTSTR pLocal, DWORD dwChars);
extern int  WideCharToLocal(LPTSTR pLocal, LPWSTR pWide, DWORD dwChars);

#define _MBSTR(wstr) hf_wctomb((LPSTR)alloca(wcslen(wstr) + 1), (wstr),wcslen(wstr) + 1)
#define _WCSTR(str) hf_mbtowc((LPWSTR)alloca((strlen(str) + 1) * sizeof(WCHAR)),(str),strlen(str) + 1)

LPWSTR hf_mbtowc(LPWSTR lpw, LPCSTR lpa, int nChars);
LPSTR hf_wctomb(LPSTR lpa, LPCWSTR lpw, int nChars);

#endif