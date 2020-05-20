
MethodTimeHookps.dll: dlldata.obj MethodTimeHook_p.obj MethodTimeHook_i.obj
	link /dll /out:MethodTimeHookps.dll /def:MethodTimeHookps.def /entry:DllMain dlldata.obj MethodTimeHook_p.obj MethodTimeHook_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del MethodTimeHookps.dll
	@del MethodTimeHookps.lib
	@del MethodTimeHookps.exp
	@del dlldata.obj
	@del MethodTimeHook_p.obj
	@del MethodTimeHook_i.obj
