#pragma once

struct SurrogateInfo
{
	BYTE	objref[4096];
	DWORD	cbObjref;
	HANDLE	hBeginTest; // event
};
