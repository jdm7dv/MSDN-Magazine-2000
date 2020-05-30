

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "CallObjectServer.h"

#define TYPE_FORMAT_STRING_SIZE   55                                
#define PROC_FORMAT_STRING_SIZE   67                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _CallObjectServer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } CallObjectServer_MIDL_TYPE_FORMAT_STRING;

typedef struct _CallObjectServer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } CallObjectServer_MIDL_PROC_FORMAT_STRING;

typedef struct _CallObjectServer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } CallObjectServer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const CallObjectServer_MIDL_TYPE_FORMAT_STRING CallObjectServer__MIDL_TypeFormatString;
extern const CallObjectServer_MIDL_PROC_FORMAT_STRING CallObjectServer__MIDL_ProcFormatString;
extern const CallObjectServer_MIDL_EXPR_FORMAT_STRING CallObjectServer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ICallObjectInit_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ICallObjectInit_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif
#if !(TARGET_IS_NT60_OR_LATER)
#error You need Windows Vista or later to run this stub because it uses these features:
#error   forced complex structure or array, compiled for Windows Vista.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const CallObjectServer_MIDL_PROC_FORMAT_STRING CallObjectServer__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Initialize */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 10 */	NdrFcShort( 0x98 ),	/* 152 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x7,		/* 7 */
/* 16 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 18 */	NdrFcShort( 0x1 ),	/* 1 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hWnd */

/* 24 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nMessageID */

/* 30 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pCallFactory */

/* 36 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 38 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 40 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Parameter riid1 */

/* 42 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 44 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 46 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */

	/* Parameter riid2 */

/* 48 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 50 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 52 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */

	/* Parameter ppvObj */

/* 54 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 56 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 58 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Return value */

/* 60 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 62 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 64 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const CallObjectServer_MIDL_TYPE_FORMAT_STRING CallObjectServer__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/*  4 */	NdrFcLong( 0x1c733a30 ),	/* 477313584 */
/*  8 */	NdrFcShort( 0x2a1c ),	/* 10780 */
/* 10 */	NdrFcShort( 0x11ce ),	/* 4558 */
/* 12 */	0xad,		/* 173 */
			0xe5,		/* 229 */
/* 14 */	0x0,		/* 0 */
			0xaa,		/* 170 */
/* 16 */	0x0,		/* 0 */
			0x44,		/* 68 */
/* 18 */	0x77,		/* 119 */
			0x3d,		/* 61 */
/* 20 */	
			0x11, 0x0,	/* FC_RP */
/* 22 */	NdrFcShort( 0x8 ),	/* Offset= 8 (30) */
/* 24 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 26 */	NdrFcShort( 0x8 ),	/* 8 */
/* 28 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 30 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 32 */	NdrFcShort( 0x10 ),	/* 16 */
/* 34 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 36 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 38 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (24) */
			0x5b,		/* FC_END */
/* 42 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 44 */	NdrFcShort( 0x2 ),	/* Offset= 2 (46) */
/* 46 */	
			0x2f,		/* FC_IP */
			0x5c,		/* FC_PAD */
/* 48 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 50 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 52 */	NdrFcShort( 0x5 ),	/* Corr flags:  early, iid_is, */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ICallObjectInit, ver. 0.0,
   GUID={0xD38F681D,0x307F,0x4559,{0x96,0xC8,0xFF,0x8B,0x75,0x97,0x12,0xA9}} */

#pragma code_seg(".orpc")
static const unsigned short ICallObjectInit_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ICallObjectInit_ProxyInfo =
    {
    &Object_StubDesc,
    CallObjectServer__MIDL_ProcFormatString.Format,
    &ICallObjectInit_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ICallObjectInit_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    CallObjectServer__MIDL_ProcFormatString.Format,
    &ICallObjectInit_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _ICallObjectInitProxyVtbl = 
{
    &ICallObjectInit_ProxyInfo,
    &IID_ICallObjectInit,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ICallObjectInit::Initialize */
};

const CInterfaceStubVtbl _ICallObjectInitStubVtbl =
{
    &IID_ICallObjectInit,
    &ICallObjectInit_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    CallObjectServer__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x60001, /* Ndr library version */
    0,
    0x800025b, /* MIDL Version 8.0.603 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _CallObjectServer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ICallObjectInitProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _CallObjectServer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ICallObjectInitStubVtbl,
    0
};

PCInterfaceName const _CallObjectServer_InterfaceNamesList[] = 
{
    "ICallObjectInit",
    0
};


#define _CallObjectServer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _CallObjectServer, pIID, n)

int __stdcall _CallObjectServer_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_CallObjectServer_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo CallObjectServer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _CallObjectServer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _CallObjectServer_StubVtblList,
    (const PCInterfaceName * ) & _CallObjectServer_InterfaceNamesList,
    0, /* no delegation */
    & _CallObjectServer_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_) */

