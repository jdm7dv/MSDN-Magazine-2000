

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed May 20 08:49:30 2020
 */
/* Compiler settings for FolderExt.idl:
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

#ifndef __FolderExt_h__
#define __FolderExt_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IProperty_FWD_DEFINED__
#define __IProperty_FWD_DEFINED__
typedef interface IProperty IProperty;

#endif 	/* __IProperty_FWD_DEFINED__ */


#ifndef __Property_FWD_DEFINED__
#define __Property_FWD_DEFINED__

#ifdef __cplusplus
typedef class Property Property;
#else
typedef struct Property Property;
#endif /* __cplusplus */

#endif 	/* __Property_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IProperty_INTERFACE_DEFINED__
#define __IProperty_INTERFACE_DEFINED__

/* interface IProperty */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7AB61C14-F59F-4A67-A69F-4678FF6B3A20")
    IProperty : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProperty * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProperty * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProperty * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IProperty * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IProperty * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IProperty * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IProperty * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IPropertyVtbl;

    interface IProperty
    {
        CONST_VTBL struct IPropertyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProperty_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProperty_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProperty_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProperty_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IProperty_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IProperty_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IProperty_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProperty_INTERFACE_DEFINED__ */



#ifndef __FOLDEREXTLib_LIBRARY_DEFINED__
#define __FOLDEREXTLib_LIBRARY_DEFINED__

/* library FOLDEREXTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_FOLDEREXTLib;

EXTERN_C const CLSID CLSID_Property;

#ifdef __cplusplus

class DECLSPEC_UUID("1F8F343A-1DE0-4B26-97C9-18A39FFC9880")
Property;
#endif
#endif /* __FOLDEREXTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


