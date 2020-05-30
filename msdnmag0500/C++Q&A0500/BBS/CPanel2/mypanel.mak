# Microsoft Developer Studio Generated NMAKE File, Based on mypanel.dsp
!IF "$(CFG)" == ""
CFG=MYPANEL - Win32 Release
!MESSAGE No configuration specified. Defaulting to MYPANEL - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "MYPANEL - Win32 Release" && "$(CFG)" != "MYPANEL - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mypanel.mak" CFG="MYPANEL - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MYPANEL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MYPANEL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MYPANEL - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\mypanel.dll"


CLEAN :
	-@erase "$(INTDIR)\cpanel.obj"
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\mypanel.obj"
	-@erase "$(INTDIR)\mypanel.pch"
	-@erase "$(INTDIR)\mypanel.res"
	-@erase "$(INTDIR)\StatLink.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\mypanel.dll"
	-@erase "$(OUTDIR)\mypanel.exp"
	-@erase "$(OUTDIR)\mypanel.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\mypanel.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\mypanel.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mypanel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\mypanel.pdb" /machine:I386 /def:".\mypanel.def" /out:"$(OUTDIR)\mypanel.dll" /implib:"$(OUTDIR)\mypanel.lib" 
DEF_FILE= \
	".\mypanel.def"
LINK32_OBJS= \
	"$(INTDIR)\cpanel.obj" \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\mypanel.obj" \
	"$(INTDIR)\StatLink.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\mypanel.res"

"$(OUTDIR)\mypanel.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MYPANEL - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\mypanel.dll"


CLEAN :
	-@erase "$(INTDIR)\cpanel.obj"
	-@erase "$(INTDIR)\Debug.obj"
	-@erase "$(INTDIR)\mypanel.obj"
	-@erase "$(INTDIR)\mypanel.pch"
	-@erase "$(INTDIR)\mypanel.res"
	-@erase "$(INTDIR)\StatLink.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\mypanel.dll"
	-@erase "$(OUTDIR)\mypanel.exp"
	-@erase "$(OUTDIR)\mypanel.ilk"
	-@erase "$(OUTDIR)\mypanel.lib"
	-@erase "$(OUTDIR)\mypanel.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\mypanel.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\mypanel.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mypanel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\mypanel.pdb" /debug /machine:I386 /def:".\mypanel.def" /out:"$(OUTDIR)\mypanel.dll" /implib:"$(OUTDIR)\mypanel.lib" 
DEF_FILE= \
	".\mypanel.def"
LINK32_OBJS= \
	"$(INTDIR)\cpanel.obj" \
	"$(INTDIR)\Debug.obj" \
	"$(INTDIR)\mypanel.obj" \
	"$(INTDIR)\StatLink.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\mypanel.res"

"$(OUTDIR)\mypanel.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("mypanel.dep")
!INCLUDE "mypanel.dep"
!ELSE 
!MESSAGE Warning: cannot find "mypanel.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MYPANEL - Win32 Release" || "$(CFG)" == "MYPANEL - Win32 Debug"
SOURCE=.\cpanel.cpp

"$(INTDIR)\cpanel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mypanel.pch"


SOURCE=.\Debug.cpp

"$(INTDIR)\Debug.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mypanel.pch"


SOURCE=.\mypanel.cpp

"$(INTDIR)\mypanel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mypanel.pch"


SOURCE=.\mypanel.rc

"$(INTDIR)\mypanel.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StatLink.cpp

"$(INTDIR)\StatLink.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\mypanel.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "MYPANEL - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\mypanel.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\mypanel.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MYPANEL - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\mypanel.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\mypanel.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

