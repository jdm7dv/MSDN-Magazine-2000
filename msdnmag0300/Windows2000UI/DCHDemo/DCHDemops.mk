
DCHDemops.dll: dlldata.obj DCHDemo_p.obj DCHDemo_i.obj
	link /dll /out:DCHDemops.dll /def:DCHDemops.def /entry:DllMain dlldata.obj DCHDemo_p.obj DCHDemo_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del DCHDemops.dll
	@del DCHDemops.lib
	@del DCHDemops.exp
	@del dlldata.obj
	@del DCHDemo_p.obj
	@del DCHDemo_i.obj
