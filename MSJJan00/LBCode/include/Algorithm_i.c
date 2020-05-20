/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Mar 30 15:24:49 1999
 */
/* Compiler settings for C:\users\tim\com\com+\NewLB\LoadBalancing\include\Algorithm.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


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

const IID IID_ILoadBalancingAlgorithm = {0x741F3750,0xE3B1,0x11d2,{0x81,0x17,0x00,0xE0,0x98,0x01,0xFD,0xBE}};


const IID IID_IHosts = {0x6345D6A0,0xE6DC,0x11d2,{0xB7,0x2D,0x00,0xA0,0xCC,0x21,0x22,0x96}};


#ifdef __cplusplus
}
#endif

