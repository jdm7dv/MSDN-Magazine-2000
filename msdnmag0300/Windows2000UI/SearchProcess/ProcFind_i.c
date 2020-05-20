/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Sep 01 20:22:43 1998
 */
/* Compiler settings for ProcFind.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
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

const IID IID_IProcess = {0x977DA8D0,0x41D5,0x11D2,{0xBC,0x00,0xAC,0x68,0x05,0xC1,0x0E,0x27}};


const IID LIBID_PROCFINDLib = {0x977DA8C3,0x41D5,0x11D2,{0xBC,0x00,0xAC,0x68,0x05,0xC1,0x0E,0x27}};


const CLSID CLSID_Process = {0x977DA8D2,0x41D5,0x11D2,{0xBC,0x00,0xAC,0x68,0x05,0xC1,0x0E,0x27}};


#ifdef __cplusplus
}
#endif

