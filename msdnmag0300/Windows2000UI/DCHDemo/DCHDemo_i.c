/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Dec 10 10:27:15 1999
 */
/* Compiler settings for D:\Articles\Microsoft Systems Journal\Win2K UI Goodies\SOURCE\DCHDemo\DCHDemo.idl:
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

const IID IID_ICleanSomething = {0xE9243790,0xC1C3,0x41B6,{0x9F,0x02,0x98,0x38,0x0E,0xF5,0x95,0xED}};


const IID LIBID_DCHDEMOLib = {0xC2DAFB18,0xC704,0x4233,{0x85,0xF6,0xE8,0x33,0xF6,0x5F,0x34,0x7C}};


const CLSID CLSID_CleanSomething = {0xE61151A9,0xE694,0x40FF,{0xA3,0x50,0xBA,0xD5,0x4C,0x39,0x67,0x2E}};


#ifdef __cplusplus
}
#endif

