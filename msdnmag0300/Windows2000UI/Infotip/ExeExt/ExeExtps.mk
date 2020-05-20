
ExeExtps.dll: dlldata.obj ExeExt_p.obj ExeExt_i.obj
	link /dll /out:ExeExtps.dll /def:ExeExtps.def /entry:DllMain dlldata.obj ExeExt_p.obj ExeExt_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ExeExtps.dll
	@del ExeExtps.lib
	@del ExeExtps.exp
	@del dlldata.obj
	@del ExeExt_p.obj
	@del ExeExt_i.obj
