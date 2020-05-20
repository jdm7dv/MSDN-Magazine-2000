
ProcFindps.dll: dlldata.obj ProcFind_p.obj ProcFind_i.obj
	link /dll /out:ProcFindps.dll /def:ProcFindps.def /entry:DllMain dlldata.obj ProcFind_p.obj ProcFind_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del ProcFindps.dll
	@del ProcFindps.lib
	@del ProcFindps.exp
	@del dlldata.obj
	@del ProcFind_p.obj
	@del ProcFind_i.obj
