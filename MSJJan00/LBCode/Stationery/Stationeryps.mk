
Stationeryps.dll: dlldata.obj Stationery_p.obj Stationery_i.obj
	link /dll /out:Stationeryps.dll /def:Stationeryps.def /entry:DllMain dlldata.obj Stationery_p.obj Stationery_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Stationeryps.dll
	@del Stationeryps.lib
	@del Stationeryps.exp
	@del dlldata.obj
	@del Stationery_p.obj
	@del Stationery_i.obj
