
LoadBalancerps.dll: dlldata.obj LoadBalancer_p.obj LoadBalancer_i.obj
	link /dll /out:LoadBalancerps.dll /def:LoadBalancerps.def /entry:DllMain dlldata.obj LoadBalancer_p.obj LoadBalancer_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del LoadBalancerps.dll
	@del LoadBalancerps.lib
	@del LoadBalancerps.exp
	@del dlldata.obj
	@del LoadBalancer_p.obj
	@del LoadBalancer_i.obj
