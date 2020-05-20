/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Mar 30 15:24:49 1999
 */
/* Compiler settings for C:\users\tim\com\com+\NewLB\LoadBalancing\include\Algorithm.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Algorithm_h__
#define __Algorithm_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILoadBalancingAlgorithm_FWD_DEFINED__
#define __ILoadBalancingAlgorithm_FWD_DEFINED__
typedef interface ILoadBalancingAlgorithm ILoadBalancingAlgorithm;
#endif 	/* __ILoadBalancingAlgorithm_FWD_DEFINED__ */


#ifndef __IHosts_FWD_DEFINED__
#define __IHosts_FWD_DEFINED__
typedef interface IHosts IHosts;
#endif 	/* __IHosts_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ILoadBalancingAlgorithm_INTERFACE_DEFINED__
#define __ILoadBalancingAlgorithm_INTERFACE_DEFINED__

/* interface ILoadBalancingAlgorithm */
/* [object][uuid] */ 


EXTERN_C const IID IID_ILoadBalancingAlgorithm;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("741F3750-E3B1-11d2-8117-00E09801FDBE")
    ILoadBalancingAlgorithm : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateInstance( 
            /* [in] */ REFCLSID rclsid,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILoadBalancingAlgorithmVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILoadBalancingAlgorithm __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILoadBalancingAlgorithm __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILoadBalancingAlgorithm __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateInstance )( 
            ILoadBalancingAlgorithm __RPC_FAR * This,
            /* [in] */ REFCLSID rclsid,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppv);
        
        END_INTERFACE
    } ILoadBalancingAlgorithmVtbl;

    interface ILoadBalancingAlgorithm
    {
        CONST_VTBL struct ILoadBalancingAlgorithmVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadBalancingAlgorithm_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILoadBalancingAlgorithm_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILoadBalancingAlgorithm_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILoadBalancingAlgorithm_CreateInstance(This,rclsid,riid,ppv)	\
    (This)->lpVtbl -> CreateInstance(This,rclsid,riid,ppv)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ILoadBalancingAlgorithm_CreateInstance_Proxy( 
    ILoadBalancingAlgorithm __RPC_FAR * This,
    /* [in] */ REFCLSID rclsid,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppv);


void __RPC_STUB ILoadBalancingAlgorithm_CreateInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILoadBalancingAlgorithm_INTERFACE_DEFINED__ */


#ifndef __IHosts_INTERFACE_DEFINED__
#define __IHosts_INTERFACE_DEFINED__

/* interface IHosts */
/* [object][uuid] */ 


EXTERN_C const IID IID_IHosts;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6345D6A0-E6DC-11d2-B72D-00A0CC212296")
    IHosts : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetHosts( 
            /* [in] */ long nCount,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgwszHosts) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHostsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHosts __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHosts __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHosts __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetHosts )( 
            IHosts __RPC_FAR * This,
            /* [in] */ long nCount,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgwszHosts);
        
        END_INTERFACE
    } IHostsVtbl;

    interface IHosts
    {
        CONST_VTBL struct IHostsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHosts_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHosts_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHosts_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHosts_SetHosts(This,nCount,rgwszHosts)	\
    (This)->lpVtbl -> SetHosts(This,nCount,rgwszHosts)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHosts_SetHosts_Proxy( 
    IHosts __RPC_FAR * This,
    /* [in] */ long nCount,
    /* [size_is][in] */ LPOLESTR __RPC_FAR *rgwszHosts);


void __RPC_STUB IHosts_SetHosts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHosts_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
