/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Dec 10 13:02:12 1999
 */
/* Compiler settings for D:\Articles\Microsoft Systems Journal\Win2K UI Goodies\SOURCE\FolderExt\FolderExt.idl:
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

const IID IID_IProperty = {0x7AB61C14,0xF59F,0x4A67,{0xA6,0x9F,0x46,0x78,0xFF,0x6B,0x3A,0x20}};


const IID LIBID_FOLDEREXTLib = {0xDABDF9F8,0x044D,0x47F9,{0x83,0x28,0xFA,0x2F,0x14,0xD7,0xD1,0x67}};


const CLSID CLSID_Property = {0x1F8F343A,0x1DE0,0x4B26,{0x97,0xC9,0x18,0xA3,0x9F,0xFC,0x98,0x80}};


#ifdef __cplusplus
}
#endif

