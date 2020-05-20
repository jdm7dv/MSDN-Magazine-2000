
FolderExtps.dll: dlldata.obj FolderExt_p.obj FolderExt_i.obj
	link /dll /out:FolderExtps.dll /def:FolderExtps.def /entry:DllMain dlldata.obj FolderExt_p.obj FolderExt_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del FolderExtps.dll
	@del FolderExtps.lib
	@del FolderExtps.exp
	@del dlldata.obj
	@del FolderExt_p.obj
	@del FolderExt_i.obj
