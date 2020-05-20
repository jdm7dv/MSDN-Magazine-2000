
BmpExtps.dll: dlldata.obj BmpExt_p.obj BmpExt_i.obj
	link /dll /out:BmpExtps.dll /def:BmpExtps.def /entry:DllMain dlldata.obj BmpExt_p.obj BmpExt_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del BmpExtps.dll
	@del BmpExtps.lib
	@del BmpExtps.exp
	@del dlldata.obj
	@del BmpExt_p.obj
	@del BmpExt_i.obj
