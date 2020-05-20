

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed May 20 07:36:11 2020
 */
/* Compiler settings for LoadBalancer.idl:
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

#ifndef __LoadBalancer_h__
#define __LoadBalancer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAdmin_FWD_DEFINED__
#define __IAdmin_FWD_DEFINED__
typedef interface IAdmin IAdmin;

#endif 	/* __IAdmin_FWD_DEFINED__ */


#ifndef __Admin_FWD_DEFINED__
#define __Admin_FWD_DEFINED__

#ifdef __cplusplus
typedef class Admin Admin;
#else
typedef struct Admin Admin;
#endif /* __cplusplus */

#endif 	/* __Admin_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IAdmin_INTERFACE_DEFINED__
#define __IAdmin_INTERFACE_DEFINED__

/* interface IAdmin */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAdmin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5E7F74C5-E165-11D2-B72C-00A0CC212296")
    IAdmin : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IAdminVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAdmin * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAdmin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAdmin * This);
        
        END_INTERFACE
    } IAdminVtbl;

    interface IAdmin
    {
        CONST_VTBL struct IAdminVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAdmin_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAdmin_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAdmin_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAdmin_INTERFACE_DEFINED__ */



#ifndef __LOADBALANCERLib_LIBRARY_DEFINED__
#define __LOADBALANCERLib_LIBRARY_DEFINED__

/* library LOADBALANCERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LOADBALANCERLib;

EXTERN_C const CLSID CLSID_Admin;

#ifdef __cplusplus

class DECLSPEC_UUID("5E7F74C6-E165-11D2-B72C-00A0CC212296")
Admin;
#endif
#endif /* __LOADBALANCERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


