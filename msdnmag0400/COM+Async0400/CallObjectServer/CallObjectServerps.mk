
CallObjectServerps.dll: dlldata.obj CallObjectServer_p.obj CallObjectServer_i.obj
	link /dll /out:CallObjectServerps.dll /def:CallObjectServerps.def /entry:DllMain dlldata.obj CallObjectServer_p.obj CallObjectServer_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del CallObjectServerps.dll
	@del CallObjectServerps.lib
	@del CallObjectServerps.exp
	@del dlldata.obj
	@del CallObjectServer_p.obj
	@del CallObjectServer_i.obj
