# Microsoft Developer Studio Generated NMAKE File, Based on MethodTimeHook.dsp
!IF "$(CFG)" == ""
CFG=MethodTimeHook - Win32 Debug
!MESSAGE No configuration specified. Defaulting to MethodTimeHook - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MethodTimeHook - Win32 Debug" && "$(CFG)" != "MethodTimeHook - Win32 Unicode Debug" && "$(CFG)" != "MethodTimeHook - Win32 Release MinSize" && "$(CFG)" != "MethodTimeHook - Win32 Release MinDependency" && "$(CFG)" != "MethodTimeHook - Win32 Unicode Release MinSize" && "$(CFG)" != "MethodTimeHook - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MethodTimeHook.mak" CFG="MethodTimeHook - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MethodTimeHook - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MethodTimeHook - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MethodTimeHook - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MethodTimeHook - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MethodTimeHook - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MethodTimeHook - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "MethodTimeHook - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MethodTimeHook.dll" ".\MethodTimeHook.tlb" ".\MethodTimeHook.h" ".\MethodTimeHook_i.c" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Hook.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\MethodTimeHook.obj"
	-@erase "$(INTDIR)\MethodTimeHook.pch"
	-@erase "$(INTDIR)\MethodTimeHook.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\MethodTimeHook.dll"
	-@erase "$(OUTDIR)\MethodTimeHook.exp"
	-@erase "$(OUTDIR)\MethodTimeHook.ilk"
	-@erase "$(OUTDIR)\MethodTimeHook.lib"
	-@erase "$(OUTDIR)\MethodTimeHook.pdb"
	-@erase ".\MethodTimeHook.h"
	-@erase ".\MethodTimeHook.tlb"
	-@erase ".\MethodTimeHook_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\MethodTimeHook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MethodTimeHook.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MethodTimeHook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\MethodTimeHook.pdb" /debug /machine:I386 /def:".\MethodTimeHook.def" /out:"$(OUTDIR)\MethodTimeHook.dll" /implib:"$(OUTDIR)\MethodTimeHook.lib" /pdbtype:sept 
DEF_FILE= \
	".\MethodTimeHook.def"
LINK32_OBJS= \
	"$(INTDIR)\Hook.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\MethodTimeHook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MethodTimeHook.res"

"$(OUTDIR)\MethodTimeHook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\MethodTimeHook.dll
InputPath=.\Debug\MethodTimeHook.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "MethodTimeHook - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\MethodTimeHook.dll" ".\MethodTimeHook.tlb" ".\MethodTimeHook.h" ".\MethodTimeHook_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Hook.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\MethodTimeHook.obj"
	-@erase "$(INTDIR)\MethodTimeHook.pch"
	-@erase "$(INTDIR)\MethodTimeHook.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\MethodTimeHook.dll"
	-@erase "$(OUTDIR)\MethodTimeHook.exp"
	-@erase "$(OUTDIR)\MethodTimeHook.ilk"
	-@erase "$(OUTDIR)\MethodTimeHook.lib"
	-@erase "$(OUTDIR)\MethodTimeHook.pdb"
	-@erase ".\MethodTimeHook.h"
	-@erase ".\MethodTimeHook.tlb"
	-@erase ".\MethodTimeHook_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\MethodTimeHook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MethodTimeHook.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MethodTimeHook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\MethodTimeHook.pdb" /debug /machine:I386 /def:".\MethodTimeHook.def" /out:"$(OUTDIR)\MethodTimeHook.dll" /implib:"$(OUTDIR)\MethodTimeHook.lib" /pdbtype:sept 
DEF_FILE= \
	".\MethodTimeHook.def"
LINK32_OBJS= \
	"$(INTDIR)\Hook.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\MethodTimeHook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MethodTimeHook.res"

"$(OUTDIR)\MethodTimeHook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\MethodTimeHook.dll
InputPath=.\DebugU\MethodTimeHook.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "MethodTimeHook - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\MethodTimeHook.dll" ".\MethodTimeHook.tlb" ".\MethodTimeHook.h" ".\MethodTimeHook_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Hook.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\MethodTimeHook.obj"
	-@erase "$(INTDIR)\MethodTimeHook.pch"
	-@erase "$(INTDIR)\MethodTimeHook.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MethodTimeHook.dll"
	-@erase "$(OUTDIR)\MethodTimeHook.exp"
	-@erase "$(OUTDIR)\MethodTimeHook.lib"
	-@erase ".\MethodTimeHook.h"
	-@erase ".\MethodTimeHook.tlb"
	-@erase ".\MethodTimeHook_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\MethodTimeHook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MethodTimeHook.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MethodTimeHook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\MethodTimeHook.pdb" /machine:I386 /def:".\MethodTimeHook.def" /out:"$(OUTDIR)\MethodTimeHook.dll" /implib:"$(OUTDIR)\MethodTimeHook.lib" 
DEF_FILE= \
	".\MethodTimeHook.def"
LINK32_OBJS= \
	"$(INTDIR)\Hook.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\MethodTimeHook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MethodTimeHook.res"

"$(OUTDIR)\MethodTimeHook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\MethodTimeHook.dll
InputPath=.\ReleaseMinSize\MethodTimeHook.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "MethodTimeHook - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\MethodTimeHook.dll" ".\MethodTimeHook.tlb" ".\MethodTimeHook.h" ".\MethodTimeHook_i.c"


CLEAN :
	-@erase "$(INTDIR)\Hook.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\MethodTimeHook.obj"
	-@erase "$(INTDIR)\MethodTimeHook.pch"
	-@erase "$(INTDIR)\MethodTimeHook.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MethodTimeHook.dll"
	-@erase "$(OUTDIR)\MethodTimeHook.exp"
	-@erase "$(OUTDIR)\MethodTimeHook.lib"
	-@erase ".\MethodTimeHook.h"
	-@erase ".\MethodTimeHook.tlb"
	-@erase ".\MethodTimeHook_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\MethodTimeHook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MethodTimeHook.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MethodTimeHook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\MethodTimeHook.pdb" /machine:I386 /def:".\MethodTimeHook.def" /out:"$(OUTDIR)\MethodTimeHook.dll" /implib:"$(OUTDIR)\MethodTimeHook.lib" 
DEF_FILE= \
	".\MethodTimeHook.def"
LINK32_OBJS= \
	"$(INTDIR)\Hook.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\MethodTimeHook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MethodTimeHook.res"

"$(OUTDIR)\MethodTimeHook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MethodTimeHook - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\MethodTimeHook.dll" ".\MethodTimeHook.tlb" ".\MethodTimeHook.h" ".\MethodTimeHook_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Hook.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\MethodTimeHook.obj"
	-@erase "$(INTDIR)\MethodTimeHook.pch"
	-@erase "$(INTDIR)\MethodTimeHook.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MethodTimeHook.dll"
	-@erase "$(OUTDIR)\MethodTimeHook.exp"
	-@erase "$(OUTDIR)\MethodTimeHook.lib"
	-@erase ".\MethodTimeHook.h"
	-@erase ".\MethodTimeHook.tlb"
	-@erase ".\MethodTimeHook_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\MethodTimeHook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MethodTimeHook.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MethodTimeHook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\MethodTimeHook.pdb" /machine:I386 /def:".\MethodTimeHook.def" /out:"$(OUTDIR)\MethodTimeHook.dll" /implib:"$(OUTDIR)\MethodTimeHook.lib" 
DEF_FILE= \
	".\MethodTimeHook.def"
LINK32_OBJS= \
	"$(INTDIR)\Hook.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\MethodTimeHook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MethodTimeHook.res"

"$(OUTDIR)\MethodTimeHook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\MethodTimeHook.dll
InputPath=.\ReleaseUMinSize\MethodTimeHook.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "MethodTimeHook - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\MethodTimeHook.dll" ".\MethodTimeHook.tlb" ".\MethodTimeHook.h" ".\MethodTimeHook_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Hook.obj"
	-@erase "$(INTDIR)\Loader.obj"
	-@erase "$(INTDIR)\MethodTimeHook.obj"
	-@erase "$(INTDIR)\MethodTimeHook.pch"
	-@erase "$(INTDIR)\MethodTimeHook.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MethodTimeHook.dll"
	-@erase "$(OUTDIR)\MethodTimeHook.exp"
	-@erase "$(OUTDIR)\MethodTimeHook.lib"
	-@erase ".\MethodTimeHook.h"
	-@erase ".\MethodTimeHook.tlb"
	-@erase ".\MethodTimeHook_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\MethodTimeHook.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MethodTimeHook.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MethodTimeHook.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\MethodTimeHook.pdb" /machine:I386 /def:".\MethodTimeHook.def" /out:"$(OUTDIR)\MethodTimeHook.dll" /implib:"$(OUTDIR)\MethodTimeHook.lib" 
DEF_FILE= \
	".\MethodTimeHook.def"
LINK32_OBJS= \
	"$(INTDIR)\Hook.obj" \
	"$(INTDIR)\Loader.obj" \
	"$(INTDIR)\MethodTimeHook.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MethodTimeHook.res"

"$(OUTDIR)\MethodTimeHook.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\MethodTimeHook.dll
InputPath=.\ReleaseUMinDependency\MethodTimeHook.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
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

MTL_PROJ=

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MethodTimeHook.dep")
!INCLUDE "MethodTimeHook.dep"
!ELSE 
!MESSAGE Warning: cannot find "MethodTimeHook.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MethodTimeHook - Win32 Debug" || "$(CFG)" == "MethodTimeHook - Win32 Unicode Debug" || "$(CFG)" == "MethodTimeHook - Win32 Release MinSize" || "$(CFG)" == "MethodTimeHook - Win32 Release MinDependency" || "$(CFG)" == "MethodTimeHook - Win32 Unicode Release MinSize" || "$(CFG)" == "MethodTimeHook - Win32 Unicode Release MinDependency"
SOURCE=.\Hook.cpp

"$(INTDIR)\Hook.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MethodTimeHook.pch"


SOURCE=.\Loader.cpp

"$(INTDIR)\Loader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MethodTimeHook.pch"


SOURCE=.\MethodTimeHook.cpp

"$(INTDIR)\MethodTimeHook.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MethodTimeHook.pch"


SOURCE=.\MethodTimeHook.idl
MTL_SWITCHES=/tlb ".\MethodTimeHook.tlb" /h "MethodTimeHook.h" /iid "MethodTimeHook_i.c" /Oicf 

".\MethodTimeHook.tlb"	".\MethodTimeHook.h"	".\MethodTimeHook_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\MethodTimeHook.rc

"$(INTDIR)\MethodTimeHook.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "MethodTimeHook - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\MethodTimeHook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MethodTimeHook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MethodTimeHook - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MT /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\MethodTimeHook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MethodTimeHook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MethodTimeHook - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\MethodTimeHook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MethodTimeHook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MethodTimeHook - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\MethodTimeHook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MethodTimeHook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MethodTimeHook - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\MethodTimeHook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MethodTimeHook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MethodTimeHook - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\MethodTimeHook.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MethodTimeHook.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

