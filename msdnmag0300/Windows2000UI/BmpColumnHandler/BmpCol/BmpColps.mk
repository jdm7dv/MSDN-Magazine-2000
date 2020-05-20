
BmpColps.dll: dlldata.obj BmpCol_p.obj BmpCol_i.obj
	link /dll /out:BmpColps.dll /def:BmpColps.def /entry:DllMain dlldata.obj BmpCol_p.obj BmpCol_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del BmpColps.dll
	@del BmpColps.lib
	@del BmpColps.exp
	@del dlldata.obj
	@del BmpCol_p.obj
	@del BmpCol_i.obj
