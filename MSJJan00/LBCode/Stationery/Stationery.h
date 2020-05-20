

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed May 20 07:18:27 2020
 */
/* Compiler settings for Stationery.idl:
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

#ifndef __Stationery_h__
#define __Stationery_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEnvelope_FWD_DEFINED__
#define __IEnvelope_FWD_DEFINED__
typedef interface IEnvelope IEnvelope;

#endif 	/* __IEnvelope_FWD_DEFINED__ */


#ifndef __Envelope_FWD_DEFINED__
#define __Envelope_FWD_DEFINED__

#ifdef __cplusplus
typedef class Envelope Envelope;
#else
typedef struct Envelope Envelope;
#endif /* __cplusplus */

#endif 	/* __Envelope_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IEnvelope_INTERFACE_DEFINED__
#define __IEnvelope_INTERFACE_DEFINED__

/* interface IEnvelope */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnvelope;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5E7F74C0-E165-11D2-B72C-00A0CC212296")
    IEnvelope : public IUnknown
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Letter( 
            /* [in] */ IUnknown *pUnk) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnvelopeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnvelope * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnvelope * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnvelope * This);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Letter )( 
            IEnvelope * This,
            /* [in] */ IUnknown *pUnk);
        
        END_INTERFACE
    } IEnvelopeVtbl;

    interface IEnvelope
    {
        CONST_VTBL struct IEnvelopeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnvelope_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnvelope_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnvelope_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnvelope_put_Letter(This,pUnk)	\
    ( (This)->lpVtbl -> put_Letter(This,pUnk) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnvelope_INTERFACE_DEFINED__ */



#ifndef __StationeryLib_LIBRARY_DEFINED__
#define __StationeryLib_LIBRARY_DEFINED__

/* library StationeryLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_StationeryLib;

EXTERN_C const CLSID CLSID_Envelope;

#ifdef __cplusplus

class DECLSPEC_UUID("5E7F74C1-E165-11D2-B72C-00A0CC212296")
Envelope;
#endif
#endif /* __StationeryLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


