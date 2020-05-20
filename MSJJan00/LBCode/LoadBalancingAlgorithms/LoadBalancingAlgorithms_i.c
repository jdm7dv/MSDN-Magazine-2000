

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_LOADBALANCINGALGORITHMSLib,0x3C406C51,0xE3B1,0x11D2,0x81,0x17,0x00,0xE0,0x98,0x01,0xFD,0xBE);


MIDL_DEFINE_GUID(CLSID, CLSID_Random,0x3C406C5E,0xE3B1,0x11D2,0x81,0x17,0x00,0xE0,0x98,0x01,0xFD,0xBE);


MIDL_DEFINE_GUID(CLSID, CLSID_RoundRobin,0x86AADFB2,0xE612,0x11D2,0xB7,0x2D,0x00,0xA0,0xCC,0x21,0x22,0x96);


MIDL_DEFINE_GUID(CLSID, CLSID_MethodTiming,0x86AADFB9,0xE612,0x11D2,0xB7,0x2D,0x00,0xA0,0xCC,0x21,0x22,0x96);


MIDL_DEFINE_GUID(CLSID, CLSID_CPULoad,0xDD135284,0xE924,0x11D2,0xB7,0x2F,0x00,0xA0,0xCC,0x21,0x22,0x96);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



