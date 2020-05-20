/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Dec 10 10:27:15 1999
 */
/* Compiler settings for D:\Articles\Microsoft Systems Journal\Win2K UI Goodies\SOURCE\DCHDemo\DCHDemo.idl:
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

#ifndef __DCHDemo_h__
#define __DCHDemo_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICleanSomething_FWD_DEFINED__
#define __ICleanSomething_FWD_DEFINED__
typedef interface ICleanSomething ICleanSomething;
#endif 	/* __ICleanSomething_FWD_DEFINED__ */


#ifndef __CleanSomething_FWD_DEFINED__
#define __CleanSomething_FWD_DEFINED__

#ifdef __cplusplus
typedef class CleanSomething CleanSomething;
#else
typedef struct CleanSomething CleanSomething;
#endif /* __cplusplus */

#endif 	/* __CleanSomething_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ICleanSomething_INTERFACE_DEFINED__
#define __ICleanSomething_INTERFACE_DEFINED__

/* interface ICleanSomething */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICleanSomething;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E9243790-C1C3-41B6-9F02-98380EF595ED")
    ICleanSomething : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ICleanSomethingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICleanSomething __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICleanSomething __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICleanSomething __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICleanSomething __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICleanSomething __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICleanSomething __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICleanSomething __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ICleanSomethingVtbl;

    interface ICleanSomething
    {
        CONST_VTBL struct ICleanSomethingVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICleanSomething_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICleanSomething_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICleanSomething_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICleanSomething_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICleanSomething_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICleanSomething_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICleanSomething_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICleanSomething_INTERFACE_DEFINED__ */



#ifndef __DCHDEMOLib_LIBRARY_DEFINED__
#define __DCHDEMOLib_LIBRARY_DEFINED__

/* library DCHDEMOLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DCHDEMOLib;

EXTERN_C const CLSID CLSID_CleanSomething;

#ifdef __cplusplus

class DECLSPEC_UUID("E61151A9-E694-40FF-A350-BAD54C39672E")
CleanSomething;
#endif
#endif /* __DCHDEMOLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
