# Microsoft Developer Studio Project File - Name="SimpleIsapi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE x86em) Dynamic-Link Library" 0x7f02
# TARGTYPE "Win32 (WCE x86) Dynamic-Link Library" 0x8302
# TARGTYPE "Win32 (WCE MIPS) Dynamic-Link Library" 0x8202

CFG=SimpleIsapi - Win32 (WCE MIPS) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SimpleIsapi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SimpleIsapi.mak" CFG="SimpleIsapi - Win32 (WCE MIPS) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SimpleIsapi - Win32 (WCE MIPS) Release" (based on "Win32 (WCE MIPS) Dynamic-Link Library")
!MESSAGE "SimpleIsapi - Win32 (WCE MIPS) Debug" (based on "Win32 (WCE MIPS) Dynamic-Link Library")
!MESSAGE "SimpleIsapi - Win32 (WCE x86) Release" (based on "Win32 (WCE x86) Dynamic-Link Library")
!MESSAGE "SimpleIsapi - Win32 (WCE x86) Debug" (based on "Win32 (WCE x86) Dynamic-Link Library")
!MESSAGE "SimpleIsapi - Win32 (WCE x86em) Release" (based on "Win32 (WCE x86em) Dynamic-Link Library")
!MESSAGE "SimpleIsapi - Win32 (WCE x86em) Debug" (based on "Win32 (WCE x86em) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "H/PC Pro 2.11"
# PROP WCE_FormatVersion "6.0"

!IF  "$(CFG)" == "SimpleIsapi - Win32 (WCE MIPS) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WMIPSRel"
# PROP BASE Intermediate_Dir "WMIPSRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WMIPSRel"
# PROP Intermediate_Dir "WMIPSRel"
# PROP Target_Dir ""
CPP=clmips.exe
# ADD BASE CPP /nologo /M$(CECrt) /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "SIMPLEISAPI_EXPORTS" /YX /QMRWCE /c
# ADD CPP /nologo /M$(CECrt) /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "SIMPLEISAPI_EXPORTS" /YX /QMRWCE /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /dll /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /dll /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "SimpleIsapi - Win32 (WCE MIPS) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WMIPSDbg"
# PROP BASE Intermediate_Dir "WMIPSDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WMIPSDbg"
# PROP Intermediate_Dir "WMIPSDbg"
# PROP Target_Dir ""
CPP=clmips.exe
# ADD BASE CPP /nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "SIMPLEISAPI_EXPORTS" /YX /QMRWCE /c
# ADD CPP /nologo /M$(CECrtDebug) /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "SIMPLEISAPI_EXPORTS" /YX /QMRWCE /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 commctrl.lib coredll.lib /nologo /dll /debug /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 commctrl.lib coredll.lib /nologo /dll /debug /machine:MIPS /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "SimpleIsapi - Win32 (WCE x86) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCEX86Rel"
# PROP BASE Intermediate_Dir "WCEX86Rel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCEX86Rel"
# PROP Intermediate_Dir "WCEX86Rel"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /ML /W3 /O2 /D "x86" /D "_i386_" /D "_x86_" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "NDEBUG" /D "i_386_" /D "_MBCS" /D "_USRDLL" /D "SIMPLEISAPI_EXPORTS" /Gs8192 /GF /c
# ADD CPP /nologo /ML /W3 /O2 /D "x86" /D "_i386_" /D "_x86_" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "NDEBUG" /D "i_386_" /D "_MBCS" /D "_USRDLL" /D "SIMPLEISAPI_EXPORTS" /Gs8192 /GF /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "x86" /d "_i386_" /d "_x86_" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "NDEBUG"
# ADD RSC /l 0x409 /r /d "x86" /d "_i386_" /d "_x86_" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "NDEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib /nologo /base:"0x00010000" /dll /machine:IX86 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 $(CEx86Corelibc) $(CEx86Corelibc) commctrl.lib coredll.lib /nologo /base:"0x00010000" /dll /machine:IX86 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "SimpleIsapi - Win32 (WCE x86) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCEX86Dbg"
# PROP BASE Intermediate_Dir "WCEX86Dbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCEX86Dbg"
# PROP Intermediate_Dir "WCEX86Dbg"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MLd /W3 /Zi /Od /D "x86" /D "_i386_" /D "_x86_" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "DEBUG" /D "i_386_" /D "_MBCS" /D "_USRDLL" /D "SIMPLEISAPI_EXPORTS" /Gs8192 /GF /c
# ADD CPP /nologo /MLd /W3 /Zi /Od /D "x86" /D "_i386_" /D "_x86_" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "DEBUG" /D "i_386_" /D "_MBCS" /D "_USRDLL" /D "SIMPLEISAPI_EXPORTS" /Gs8192 /GF /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "x86" /d "_i386_" /d "_x86_" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "DEBUG"
# ADD RSC /l 0x409 /r /d "x86" /d "_i386_" /d "_x86_" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "DEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib /nologo /base:"0x00010000" /dll /debug /machine:IX86 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 $(CEx86Corelibc) $(CEx86Corelibc) commctrl.lib coredll.lib /nologo /base:"0x00010000" /dll /debug /machine:IX86 /nodefaultlib:"$(CENoDefaultLib)" /subsystem:$(CESubsystem) /STACK:65536,4096
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "SimpleIsapi - Win32 (WCE x86em) Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "x86emRel"
# PROP BASE Intermediate_Dir "x86emRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86emRel"
# PROP Intermediate_Dir "x86emRel"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /ML /W3 /O2 /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "NDEBUG" /D "x86" /D "i486" /D "_x86_" /D "_MBCS" /D "_USRDLL" /D "SIMPLEISAPI_EXPORTS" /YX /c
# ADD CPP /nologo /ML /W3 /O2 /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "NDEBUG" /D "x86" /D "i486" /D "_x86_" /D "_MBCS" /D "_USRDLL" /D "SIMPLEISAPI_EXPORTS" /YX /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "NDEBUG"
# ADD RSC /l 0x409 /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "NDEBUG"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib /nologo /stack:0x10000,0x1000 /dll /machine:I386 /nodefaultlib:"$(CENoDefaultLib)" /windowsce:emulation
# ADD LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib /nologo /stack:0x10000,0x1000 /dll /machine:I386 /nodefaultlib:"$(CENoDefaultLib)" /windowsce:emulation

!ELSEIF  "$(CFG)" == "SimpleIsapi - Win32 (WCE x86em) Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "x86emDbg"
# PROP BASE Intermediate_Dir "x86emDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86emDbg"
# PROP Intermediate_Dir "x86emDbg"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MLd /W3 /Gm /Zi /Od /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "_DEBUG" /D "x86" /D "i486" /D "_x86_" /D "_MBCS" /D "_USRDLL" /D "SIMPLEISAPI_EXPORTS" /YX /c
# ADD CPP /nologo /MLd /W3 /Gm /Zi /Od /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "_DEBUG" /D "x86" /D "i486" /D "_x86_" /D "_MBCS" /D "_USRDLL" /D "SIMPLEISAPI_EXPORTS" /YX /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "_DEBUG" /d "x86" /d "i486" /d "_x86_"
# ADD RSC /l 0x409 /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "_DEBUG" /d "x86" /d "i486" /d "_x86_"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib /nologo /stack:0x10000,0x1000 /dll /debug /machine:I386 /nodefaultlib:"$(CENoDefaultLib)" /windowsce:emulation
# ADD LINK32 $(CEx86Corelibc) commctrl.lib coredll.lib /nologo /stack:0x10000,0x1000 /dll /debug /machine:I386 /nodefaultlib:"$(CENoDefaultLib)" /windowsce:emulation

!ENDIF 

# Begin Target

# Name "SimpleIsapi - Win32 (WCE MIPS) Release"
# Name "SimpleIsapi - Win32 (WCE MIPS) Debug"
# Name "SimpleIsapi - Win32 (WCE x86) Release"
# Name "SimpleIsapi - Win32 (WCE x86) Debug"
# Name "SimpleIsapi - Win32 (WCE x86em) Release"
# Name "SimpleIsapi - Win32 (WCE x86em) Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\simpleisapi.c

!IF  "$(CFG)" == "SimpleIsapi - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "SimpleIsapi - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "SimpleIsapi - Win32 (WCE x86) Release"

!ELSEIF  "$(CFG)" == "SimpleIsapi - Win32 (WCE x86) Debug"

!ELSEIF  "$(CFG)" == "SimpleIsapi - Win32 (WCE x86em) Release"

!ELSEIF  "$(CFG)" == "SimpleIsapi - Win32 (WCE x86em) Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SimpleIsapi.def
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
