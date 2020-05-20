
HostHookTestSrvps.dll: dlldata.obj HostHookTestSrv_p.obj HostHookTestSrv_i.obj MethodTimeHookPS.obj
	link /dll /out:HostHookTestSrvps.dll /def:HostHookTestSrvps.def /entry:DllMain dlldata.obj HostHookTestSrv_p.obj HostHookTestSrv_i.obj MethodTimeHookPS.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib ole32.lib user32.lib

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL /DDllMain=OldDllMain $<

.cpp.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<


clean:
	@del HostHookTestSrvps.dll
	@del HostHookTestSrvps.lib
	@del HostHookTestSrvps.exp
	@del dlldata.obj
	@del HostHookTestSrv_p.obj
	@del HostHookTestSrv_i.obj
