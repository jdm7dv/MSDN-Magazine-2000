# Microsoft Developer Studio Generated NMAKE File, Based on LoadBalancer.dsp
!IF "$(CFG)" == ""
CFG=LoadBalancer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LoadBalancer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LoadBalancer - Win32 Debug" && "$(CFG)" != "LoadBalancer - Win32 Unicode Debug" && "$(CFG)" != "LoadBalancer - Win32 Release MinSize" && "$(CFG)" != "LoadBalancer - Win32 Release MinDependency" && "$(CFG)" != "LoadBalancer - Win32 Unicode Release MinSize" && "$(CFG)" != "LoadBalancer - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LoadBalancer.mak" CFG="LoadBalancer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LoadBalancer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "LoadBalancer - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "LoadBalancer - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "LoadBalancer - Win32 Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE "LoadBalancer - Win32 Unicode Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "LoadBalancer - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LoadBalancer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\LoadBalancer.exe" ".\LoadBalancer.tlb" ".\LoadBalancer.h" ".\LoadBalancer_i.c" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Admin.obj"
	-@erase "$(INTDIR)\LoadBalancer.obj"
	-@erase "$(INTDIR)\LoadBalancer.pch"
	-@erase "$(INTDIR)\LoadBalancer.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LoadBalancer.exe"
	-@erase "$(OUTDIR)\LoadBalancer.ilk"
	-@erase "$(OUTDIR)\LoadBalancer.pdb"
	-@erase ".\LoadBalancer.h"
	-@erase ".\LoadBalancer.tlb"
	-@erase ".\LoadBalancer_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\LoadBalancer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LoadBalancer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LoadBalancer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\LoadBalancer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\LoadBalancer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Admin.obj" \
	"$(INTDIR)\LoadBalancer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LoadBalancer.res"

"$(OUTDIR)\LoadBalancer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\LoadBalancer.exe
InputPath=.\Debug\LoadBalancer.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "LoadBalancer - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\LoadBalancer.exe" ".\LoadBalancer.tlb" ".\LoadBalancer.h" ".\LoadBalancer_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Admin.obj"
	-@erase "$(INTDIR)\LoadBalancer.obj"
	-@erase "$(INTDIR)\LoadBalancer.pch"
	-@erase "$(INTDIR)\LoadBalancer.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LoadBalancer.exe"
	-@erase "$(OUTDIR)\LoadBalancer.ilk"
	-@erase "$(OUTDIR)\LoadBalancer.pdb"
	-@erase ".\LoadBalancer.h"
	-@erase ".\LoadBalancer.tlb"
	-@erase ".\LoadBalancer_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\LoadBalancer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LoadBalancer.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LoadBalancer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\LoadBalancer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\LoadBalancer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Admin.obj" \
	"$(INTDIR)\LoadBalancer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LoadBalancer.res"

"$(OUTDIR)\LoadBalancer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\LoadBalancer.exe
InputPath=.\DebugU\LoadBalancer.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "LoadBalancer - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\LoadBalancer.exe" ".\LoadBalancer.tlb" ".\LoadBalancer.h" ".\LoadBalancer_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Admin.obj"
	-@erase "$(INTDIR)\LoadBalancer.obj"
	-@erase "$(INTDIR)\LoadBalancer.pch"
	-@erase "$(INTDIR)\LoadBalancer.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LoadBalancer.exe"
	-@erase ".\LoadBalancer.h"
	-@erase ".\LoadBalancer.tlb"
	-@erase ".\LoadBalancer_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /Fp"$(INTDIR)\LoadBalancer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LoadBalancer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LoadBalancer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\LoadBalancer.pdb" /machine:I386 /out:"$(OUTDIR)\LoadBalancer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Admin.obj" \
	"$(INTDIR)\LoadBalancer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LoadBalancer.res"

"$(OUTDIR)\LoadBalancer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\LoadBalancer.exe
InputPath=.\ReleaseMinSize\LoadBalancer.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "LoadBalancer - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\LoadBalancer.exe" ".\LoadBalancer.tlb" ".\LoadBalancer.h" ".\LoadBalancer_i.c"


CLEAN :
	-@erase "$(INTDIR)\Admin.obj"
	-@erase "$(INTDIR)\LoadBalancer.obj"
	-@erase "$(INTDIR)\LoadBalancer.pch"
	-@erase "$(INTDIR)\LoadBalancer.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LoadBalancer.exe"
	-@erase ".\LoadBalancer.h"
	-@erase ".\LoadBalancer.tlb"
	-@erase ".\LoadBalancer_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\LoadBalancer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LoadBalancer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LoadBalancer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\LoadBalancer.pdb" /machine:I386 /out:"$(OUTDIR)\LoadBalancer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Admin.obj" \
	"$(INTDIR)\LoadBalancer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LoadBalancer.res"

"$(OUTDIR)\LoadBalancer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LoadBalancer - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\LoadBalancer.exe" ".\LoadBalancer.tlb" ".\LoadBalancer.h" ".\LoadBalancer_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Admin.obj"
	-@erase "$(INTDIR)\LoadBalancer.obj"
	-@erase "$(INTDIR)\LoadBalancer.pch"
	-@erase "$(INTDIR)\LoadBalancer.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LoadBalancer.exe"
	-@erase ".\LoadBalancer.h"
	-@erase ".\LoadBalancer.tlb"
	-@erase ".\LoadBalancer_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\LoadBalancer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LoadBalancer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LoadBalancer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\LoadBalancer.pdb" /machine:I386 /out:"$(OUTDIR)\LoadBalancer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Admin.obj" \
	"$(INTDIR)\LoadBalancer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LoadBalancer.res"

"$(OUTDIR)\LoadBalancer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\LoadBalancer.exe
InputPath=.\ReleaseUMinSize\LoadBalancer.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "LoadBalancer - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\LoadBalancer.exe" ".\LoadBalancer.tlb" ".\LoadBalancer.h" ".\LoadBalancer_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Admin.obj"
	-@erase "$(INTDIR)\LoadBalancer.obj"
	-@erase "$(INTDIR)\LoadBalancer.pch"
	-@erase "$(INTDIR)\LoadBalancer.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LoadBalancer.exe"
	-@erase ".\LoadBalancer.h"
	-@erase ".\LoadBalancer.tlb"
	-@erase ".\LoadBalancer_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\LoadBalancer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LoadBalancer.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LoadBalancer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\LoadBalancer.pdb" /machine:I386 /out:"$(OUTDIR)\LoadBalancer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Admin.obj" \
	"$(INTDIR)\LoadBalancer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LoadBalancer.res"

"$(OUTDIR)\LoadBalancer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\LoadBalancer.exe
InputPath=.\ReleaseUMinDependency\LoadBalancer.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
<< 
	

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LoadBalancer.dep")
!INCLUDE "LoadBalancer.dep"
!ELSE 
!MESSAGE Warning: cannot find "LoadBalancer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LoadBalancer - Win32 Debug" || "$(CFG)" == "LoadBalancer - Win32 Unicode Debug" || "$(CFG)" == "LoadBalancer - Win32 Release MinSize" || "$(CFG)" == "LoadBalancer - Win32 Release MinDependency" || "$(CFG)" == "LoadBalancer - Win32 Unicode Release MinSize" || "$(CFG)" == "LoadBalancer - Win32 Unicode Release MinDependency"
SOURCE=.\Admin.cpp

"$(INTDIR)\Admin.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LoadBalancer.pch"


SOURCE=.\LoadBalancer.cpp

"$(INTDIR)\LoadBalancer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LoadBalancer.pch"


SOURCE=.\LoadBalancer.idl
MTL_SWITCHES=/tlb ".\LoadBalancer.tlb" /h "LoadBalancer.h" /iid "LoadBalancer_i.c" /Oicf 

".\LoadBalancer.tlb"	".\LoadBalancer.h"	".\LoadBalancer_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\LoadBalancer.rc

"$(INTDIR)\LoadBalancer.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LoadBalancer - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\LoadBalancer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LoadBalancer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LoadBalancer - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Fp"$(INTDIR)\LoadBalancer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LoadBalancer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LoadBalancer - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /Fp"$(INTDIR)\LoadBalancer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LoadBalancer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LoadBalancer - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\LoadBalancer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LoadBalancer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LoadBalancer - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\LoadBalancer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LoadBalancer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LoadBalancer - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\LoadBalancer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LoadBalancer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

