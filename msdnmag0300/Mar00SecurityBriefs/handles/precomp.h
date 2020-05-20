#define _WIN32_WINNT 0x400
#define STRICT
#define UNICODE
#include <windows.h>
#include <windowsx.h>
#include <aclapi.h>
#include <crtdbg.h>

#ifndef WINSTA_ALL_ACCESS
#define WINSTA_ALL_ACCESS 0x000F037F
#endif

#ifndef DESKTOP_ALL_ACCESS
#define DESKTOP_ALL_ACCESS 0x000F01FF
#endif
