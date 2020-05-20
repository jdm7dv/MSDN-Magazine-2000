
LoadBalancingAlgorithmsps.dll: dlldata.obj LoadBalancingAlgorithms_p.obj LoadBalancingAlgorithms_i.obj
	link /dll /out:LoadBalancingAlgorithmsps.dll /def:LoadBalancingAlgorithmsps.def /entry:DllMain dlldata.obj LoadBalancingAlgorithms_p.obj LoadBalancingAlgorithms_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del LoadBalancingAlgorithmsps.dll
	@del LoadBalancingAlgorithmsps.lib
	@del LoadBalancingAlgorithmsps.exp
	@del dlldata.obj
	@del LoadBalancingAlgorithms_p.obj
	@del LoadBalancingAlgorithms_i.obj
