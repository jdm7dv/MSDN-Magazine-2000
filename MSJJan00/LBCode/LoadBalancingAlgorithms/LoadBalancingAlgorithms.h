

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed May 20 07:47:15 2020
 */
/* Compiler settings for LoadBalancingAlgorithms.idl:
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


#ifndef __LoadBalancingAlgorithms_h__
#define __LoadBalancingAlgorithms_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __Random_FWD_DEFINED__
#define __Random_FWD_DEFINED__

#ifdef __cplusplus
typedef class Random Random;
#else
typedef struct Random Random;
#endif /* __cplusplus */

#endif 	/* __Random_FWD_DEFINED__ */


#ifndef __RoundRobin_FWD_DEFINED__
#define __RoundRobin_FWD_DEFINED__

#ifdef __cplusplus
typedef class RoundRobin RoundRobin;
#else
typedef struct RoundRobin RoundRobin;
#endif /* __cplusplus */

#endif 	/* __RoundRobin_FWD_DEFINED__ */


#ifndef __MethodTiming_FWD_DEFINED__
#define __MethodTiming_FWD_DEFINED__

#ifdef __cplusplus
typedef class MethodTiming MethodTiming;
#else
typedef struct MethodTiming MethodTiming;
#endif /* __cplusplus */

#endif 	/* __MethodTiming_FWD_DEFINED__ */


#ifndef __CPULoad_FWD_DEFINED__
#define __CPULoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPULoad CPULoad;
#else
typedef struct CPULoad CPULoad;
#endif /* __cplusplus */

#endif 	/* __CPULoad_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "algorithm.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __LOADBALANCINGALGORITHMSLib_LIBRARY_DEFINED__
#define __LOADBALANCINGALGORITHMSLib_LIBRARY_DEFINED__

/* library LOADBALANCINGALGORITHMSLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LOADBALANCINGALGORITHMSLib;

EXTERN_C const CLSID CLSID_Random;

#ifdef __cplusplus

class DECLSPEC_UUID("3C406C5E-E3B1-11D2-8117-00E09801FDBE")
Random;
#endif

EXTERN_C const CLSID CLSID_RoundRobin;

#ifdef __cplusplus

class DECLSPEC_UUID("86AADFB2-E612-11D2-B72D-00A0CC212296")
RoundRobin;
#endif

EXTERN_C const CLSID CLSID_MethodTiming;

#ifdef __cplusplus

class DECLSPEC_UUID("86AADFB9-E612-11D2-B72D-00A0CC212296")
MethodTiming;
#endif

EXTERN_C const CLSID CLSID_CPULoad;

#ifdef __cplusplus

class DECLSPEC_UUID("DD135284-E924-11D2-B72F-00A0CC212296")
CPULoad;
#endif
#endif /* __LOADBALANCINGALGORITHMSLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


