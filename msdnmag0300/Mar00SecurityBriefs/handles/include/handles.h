
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.02.0235 */
/* at Thu Jul 08 02:03:21 1999
 */
/* Compiler settings for handles.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
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

#ifndef __handles_h__
#define __handles_h__

/* Forward Declarations */ 

#ifndef __IHandleTestSite_FWD_DEFINED__
#define __IHandleTestSite_FWD_DEFINED__
typedef interface IHandleTestSite IHandleTestSite;
#endif 	/* __IHandleTestSite_FWD_DEFINED__ */


#ifndef __IHandleTest_FWD_DEFINED__
#define __IHandleTest_FWD_DEFINED__
typedef interface IHandleTest IHandleTest;
#endif 	/* __IHandleTest_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_handles_0000 */
/* [local] */ 



const DWORD HTO_DETAILEDOUTPUT    = 0x80000000;


extern RPC_IF_HANDLE __MIDL_itf_handles_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_handles_0000_v0_0_s_ifspec;

#ifndef __IHandleTestSite_INTERFACE_DEFINED__
#define __IHandleTestSite_INTERFACE_DEFINED__

/* interface IHandleTestSite */
/* [object][uuid] */ 


EXTERN_C const IID IID_IHandleTestSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("30E99A21-2A78-11d3-B561-00105A0FDD58")
    IHandleTestSite : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetEmptyDacl( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetNULLDacl( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHandleTestSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHandleTestSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHandleTestSite __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHandleTestSite __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEmptyDacl )( 
            IHandleTestSite __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNULLDacl )( 
            IHandleTestSite __RPC_FAR * This);
        
        END_INTERFACE
    } IHandleTestSiteVtbl;

    interface IHandleTestSite
    {
        CONST_VTBL struct IHandleTestSiteVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHandleTestSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHandleTestSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHandleTestSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHandleTestSite_SetEmptyDacl(This)	\
    (This)->lpVtbl -> SetEmptyDacl(This)

#define IHandleTestSite_SetNULLDacl(This)	\
    (This)->lpVtbl -> SetNULLDacl(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHandleTestSite_SetEmptyDacl_Proxy( 
    IHandleTestSite __RPC_FAR * This);


void __RPC_STUB IHandleTestSite_SetEmptyDacl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHandleTestSite_SetNULLDacl_Proxy( 
    IHandleTestSite __RPC_FAR * This);


void __RPC_STUB IHandleTestSite_SetNULLDacl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHandleTestSite_INTERFACE_DEFINED__ */


#ifndef __IHandleTest_INTERFACE_DEFINED__
#define __IHandleTest_INTERFACE_DEFINED__

/* interface IHandleTest */
/* [object][uuid] */ 


EXTERN_C const IID IID_IHandleTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("30E99A20-2A78-11d3-B561-00105A0FDD58")
    IHandleTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetHandle( 
            /* [in] */ long handle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetName( 
            /* [string][in] */ const OLECHAR __RPC_FAR *psz) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RunTest( 
            /* [in] */ IHandleTestSite __RPC_FAR *pSite,
            /* [in] */ long nObjectType,
            /* [in] */ DWORD grfOptions,
            /* [in] */ ISequentialStream __RPC_FAR *pstm) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHandleTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHandleTest __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHandleTest __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHandleTest __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetHandle )( 
            IHandleTest __RPC_FAR * This,
            /* [in] */ long handle);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            IHandleTest __RPC_FAR * This,
            /* [string][in] */ const OLECHAR __RPC_FAR *psz);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RunTest )( 
            IHandleTest __RPC_FAR * This,
            /* [in] */ IHandleTestSite __RPC_FAR *pSite,
            /* [in] */ long nObjectType,
            /* [in] */ DWORD grfOptions,
            /* [in] */ ISequentialStream __RPC_FAR *pstm);
        
        END_INTERFACE
    } IHandleTestVtbl;

    interface IHandleTest
    {
        CONST_VTBL struct IHandleTestVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHandleTest_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHandleTest_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHandleTest_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHandleTest_SetHandle(This,handle)	\
    (This)->lpVtbl -> SetHandle(This,handle)

#define IHandleTest_SetName(This,psz)	\
    (This)->lpVtbl -> SetName(This,psz)

#define IHandleTest_RunTest(This,pSite,nObjectType,grfOptions,pstm)	\
    (This)->lpVtbl -> RunTest(This,pSite,nObjectType,grfOptions,pstm)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHandleTest_SetHandle_Proxy( 
    IHandleTest __RPC_FAR * This,
    /* [in] */ long handle);


void __RPC_STUB IHandleTest_SetHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHandleTest_SetName_Proxy( 
    IHandleTest __RPC_FAR * This,
    /* [string][in] */ const OLECHAR __RPC_FAR *psz);


void __RPC_STUB IHandleTest_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHandleTest_RunTest_Proxy( 
    IHandleTest __RPC_FAR * This,
    /* [in] */ IHandleTestSite __RPC_FAR *pSite,
    /* [in] */ long nObjectType,
    /* [in] */ DWORD grfOptions,
    /* [in] */ ISequentialStream __RPC_FAR *pstm);


void __RPC_STUB IHandleTest_RunTest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHandleTest_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


