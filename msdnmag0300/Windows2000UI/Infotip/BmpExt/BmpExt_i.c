/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Nov 29 23:53:36 1999
 */
/* Compiler settings for D:\My Conferences\Windows European Summit 99\Speeches\Details\Shell Extensions\Source\IQueryInfo\BmpExt\BmpExt.idl:
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

const IID IID_IBmpTip = {0x7BEA1DD0,0x1EB9,0x11D3,{0xB1,0x7C,0x00,0xC0,0xDF,0xE3,0x97,0x36}};


const IID LIBID_BMPEXTLib = {0x7BEA1DC4,0x1EB9,0x11D3,{0xB1,0x7C,0x00,0xC0,0xDF,0xE3,0x97,0x36}};


const CLSID CLSID_BmpTip = {0x7BEA1DD1,0x1EB9,0x11D3,{0xB1,0x7C,0x00,0xC0,0xDF,0xE3,0x97,0x36}};


#ifdef __cplusplus
}
#endif

