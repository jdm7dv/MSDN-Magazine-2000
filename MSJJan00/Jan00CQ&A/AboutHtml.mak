# Microsoft Developer Studio Generated NMAKE File, Based on AboutHtml.dsp
!IF "$(CFG)" == ""
CFG=AboutHtml - Win32 Release
!MESSAGE No configuration specified. Defaulting to AboutHtml - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "AboutHtml - Win32 Release" && "$(CFG)" != "AboutHtml - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AboutHtml.mak" CFG="AboutHtml - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AboutHtml - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AboutHtml - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "AboutHtml - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\AboutHtml.exe"


CLEAN :
	-@erase "$(INTDIR)\AboutHtml.obj"
	-@erase "$(INTDIR)\AboutHtml.pch"
	-@erase "$(INTDIR)\AboutHtml.res"
	-@erase "$(INTDIR)\HtmlCtrl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\AboutHtml.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\AboutHtml.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AboutHtml.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AboutHtml.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\AboutHtml.pdb" /machine:I386 /out:"$(OUTDIR)\AboutHtml.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutHtml.obj" \
	"$(INTDIR)\HtmlCtrl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AboutHtml.res"

"$(OUTDIR)\AboutHtml.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AboutHtml - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\AboutHtml.exe"


CLEAN :
	-@erase "$(INTDIR)\AboutHtml.obj"
	-@erase "$(INTDIR)\AboutHtml.pch"
	-@erase "$(INTDIR)\AboutHtml.res"
	-@erase "$(INTDIR)\HtmlCtrl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\AboutHtml.exe"
	-@erase "$(OUTDIR)\AboutHtml.ilk"
	-@erase "$(OUTDIR)\AboutHtml.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\AboutHtml.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\AboutHtml.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AboutHtml.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\AboutHtml.pdb" /debug /machine:I386 /out:"$(OUTDIR)\AboutHtml.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutHtml.obj" \
	"$(INTDIR)\HtmlCtrl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\AboutHtml.res"

"$(OUTDIR)\AboutHtml.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("AboutHtml.dep")
!INCLUDE "AboutHtml.dep"
!ELSE 
!MESSAGE Warning: cannot find "AboutHtml.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "AboutHtml - Win32 Release" || "$(CFG)" == "AboutHtml - Win32 Debug"
SOURCE=.\AboutHtml.cpp

"$(INTDIR)\AboutHtml.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AboutHtml.pch"


SOURCE=.\AboutHtml.rc

"$(INTDIR)\AboutHtml.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\HtmlCtrl.cpp

"$(INTDIR)\HtmlCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\AboutHtml.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "AboutHtml - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\AboutHtml.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AboutHtml.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "AboutHtml - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\AboutHtml.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\AboutHtml.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

