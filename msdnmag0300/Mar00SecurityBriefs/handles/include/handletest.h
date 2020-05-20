// single export point from DLL
HRESULT __stdcall CreateObject( REFIID iid, void** ppv );
typedef HRESULT (__stdcall *CREATEOBJECTFCN)( REFIID, void** );
