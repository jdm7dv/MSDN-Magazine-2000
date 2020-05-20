/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Dec 01 09:58:48 1999
 */
/* Compiler settings for D:\Articles\Microsoft Systems Journal\Win2K UI Goodies\SOURCE\BmpColumnHandler\BmpCol\BmpCol.idl:
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

const IID IID_IBmpColInfo = {0xD1A87B75,0xBB28,0x42F8,{0x9B,0xC0,0xC5,0x5B,0x82,0x74,0x74,0xCD}};


const IID LIBID_BMPCOLLib = {0x43031770,0xD60B,0x41BF,{0xBA,0x70,0x6B,0x92,0xA8,0x7D,0x28,0xFC}};


const CLSID CLSID_BmpColInfo = {0x9A4BA3D8,0x6805,0x498F,{0x95,0x61,0x26,0x85,0xA1,0xE3,0x04,0x84}};


#ifdef __cplusplus
}
#endif

