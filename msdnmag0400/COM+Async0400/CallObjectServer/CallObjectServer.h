

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat May 30 09:43:48 2020
 */
/* Compiler settings for CallObjectServer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
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

#ifndef __CallObjectServer_h__
#define __CallObjectServer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICallObjectInit_FWD_DEFINED__
#define __ICallObjectInit_FWD_DEFINED__
typedef interface ICallObjectInit ICallObjectInit;

#endif 	/* __ICallObjectInit_FWD_DEFINED__ */


#ifndef __CallNotifyObject_FWD_DEFINED__
#define __CallNotifyObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CallNotifyObject CallNotifyObject;
#else
typedef struct CallNotifyObject CallNotifyObject;
#endif /* __cplusplus */

#endif 	/* __CallNotifyObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICallObjectInit_INTERFACE_DEFINED__
#define __ICallObjectInit_INTERFACE_DEFINED__

/* interface ICallObjectInit */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICallObjectInit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D38F681D-307F-4559-96C8-FF8B759712A9")
    ICallObjectInit : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ unsigned int hWnd,
            /* [in] */ unsigned int nMessageID,
            /* [in] */ ICallFactory *pCallFactory,
            /* [in] */ REFIID riid1,
            /* [in] */ REFIID riid2,
            /* [iid_is][out] */ void **ppvObj) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICallObjectInitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICallObjectInit * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICallObjectInit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICallObjectInit * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            ICallObjectInit * This,
            /* [in] */ unsigned int hWnd,
            /* [in] */ unsigned int nMessageID,
            /* [in] */ ICallFactory *pCallFactory,
            /* [in] */ REFIID riid1,
            /* [in] */ REFIID riid2,
            /* [iid_is][out] */ void **ppvObj);
        
        END_INTERFACE
    } ICallObjectInitVtbl;

    interface ICallObjectInit
    {
        CONST_VTBL struct ICallObjectInitVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICallObjectInit_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICallObjectInit_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICallObjectInit_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICallObjectInit_Initialize(This,hWnd,nMessageID,pCallFactory,riid1,riid2,ppvObj)	\
    ( (This)->lpVtbl -> Initialize(This,hWnd,nMessageID,pCallFactory,riid1,riid2,ppvObj) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICallObjectInit_INTERFACE_DEFINED__ */



#ifndef __CALLOBJECTSERVERLib_LIBRARY_DEFINED__
#define __CALLOBJECTSERVERLib_LIBRARY_DEFINED__

/* library CALLOBJECTSERVERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CALLOBJECTSERVERLib;

EXTERN_C const CLSID CLSID_CallNotifyObject;

#ifdef __cplusplus

class DECLSPEC_UUID("3DE3FDA5-A785-423C-84A5-45A12A15FCBD")
CallNotifyObject;
#endif
#endif /* __CALLOBJECTSERVERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


