# Microsoft Developer Studio Generated NMAKE File, Based on LoadBalancingAlgorithms.dsp
!IF "$(CFG)" == ""
CFG=LoadBalancingAlgorithms - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LoadBalancingAlgorithms - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LoadBalancingAlgorithms - Win32 Debug" && "$(CFG)" != "LoadBalancingAlgorithms - Win32 Unicode Debug" && "$(CFG)" != "LoadBalancingAlgorithms - Win32 Release MinSize" && "$(CFG)" != "LoadBalancingAlgorithms - Win32 Release MinDependency" && "$(CFG)" != "LoadBalancingAlgorithms - Win32 Unicode Release MinSize" && "$(CFG)" != "LoadBalancingAlgorithms - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LoadBalancingAlgorithms.mak" CFG="LoadBalancingAlgorithms - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LoadBalancingAlgorithms - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LoadBalancingAlgorithms - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LoadBalancingAlgorithms - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LoadBalancingAlgorithms - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LoadBalancingAlgorithms - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LoadBalancingAlgorithms - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "LoadBalancingAlgorithms - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\LoadBalancingAlgorithms.dll" ".\LoadBalancingAlgorithms.tlb" ".\LoadBalancingAlgorithms.h" ".\LoadBalancingAlgorithms_i.c" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CPULoad.obj"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.obj"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.pch"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.res"
	-@erase "$(INTDIR)\MethodTiming.obj"
	-@erase "$(INTDIR)\Random.obj"
	-@erase "$(INTDIR)\RoundRobin.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.dll"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.exp"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.ilk"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.lib"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.pdb"
	-@erase ".\LoadBalancingAlgorithms.h"
	-@erase ".\LoadBalancingAlgorithms.tlb"
	-@erase ".\LoadBalancingAlgorithms_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\LoadBalancingAlgorithms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LoadBalancingAlgorithms.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LoadBalancingAlgorithms.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=pdh.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\LoadBalancingAlgorithms.pdb" /debug /machine:I386 /def:".\LoadBalancingAlgorithms.def" /out:"$(OUTDIR)\LoadBalancingAlgorithms.dll" /implib:"$(OUTDIR)\LoadBalancingAlgorithms.lib" /pdbtype:sept 
DEF_FILE= \
	".\LoadBalancingAlgorithms.def"
LINK32_OBJS= \
	"$(INTDIR)\CPULoad.obj" \
	"$(INTDIR)\LoadBalancingAlgorithms.obj" \
	"$(INTDIR)\MethodTiming.obj" \
	"$(INTDIR)\Random.obj" \
	"$(INTDIR)\RoundRobin.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LoadBalancingAlgorithms.res"

"$(OUTDIR)\LoadBalancingAlgorithms.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\LoadBalancingAlgorithms.dll
InputPath=.\Debug\LoadBalancingAlgorithms.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "LoadBalancingAlgorithms - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\LoadBalancingAlgorithms.dll" ".\LoadBalancingAlgorithms.tlb" ".\LoadBalancingAlgorithms.h" ".\LoadBalancingAlgorithms_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CPULoad.obj"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.obj"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.pch"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.res"
	-@erase "$(INTDIR)\MethodTiming.obj"
	-@erase "$(INTDIR)\Random.obj"
	-@erase "$(INTDIR)\RoundRobin.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.dll"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.exp"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.ilk"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.lib"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.pdb"
	-@erase ".\LoadBalancingAlgorithms.h"
	-@erase ".\LoadBalancingAlgorithms.tlb"
	-@erase ".\LoadBalancingAlgorithms_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\LoadBalancingAlgorithms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LoadBalancingAlgorithms.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LoadBalancingAlgorithms.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib pdh.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\LoadBalancingAlgorithms.pdb" /debug /machine:I386 /def:".\LoadBalancingAlgorithms.def" /out:"$(OUTDIR)\LoadBalancingAlgorithms.dll" /implib:"$(OUTDIR)\LoadBalancingAlgorithms.lib" /pdbtype:sept 
DEF_FILE= \
	".\LoadBalancingAlgorithms.def"
LINK32_OBJS= \
	"$(INTDIR)\CPULoad.obj" \
	"$(INTDIR)\LoadBalancingAlgorithms.obj" \
	"$(INTDIR)\MethodTiming.obj" \
	"$(INTDIR)\Random.obj" \
	"$(INTDIR)\RoundRobin.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LoadBalancingAlgorithms.res"

"$(OUTDIR)\LoadBalancingAlgorithms.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\LoadBalancingAlgorithms.dll
InputPath=.\DebugU\LoadBalancingAlgorithms.dll
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
	

!ELSEIF  "$(CFG)" == "LoadBalancingAlgorithms - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\LoadBalancingAlgorithms.dll" ".\LoadBalancingAlgorithms.tlb" ".\LoadBalancingAlgorithms.h" ".\LoadBalancingAlgorithms_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CPULoad.obj"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.obj"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.pch"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.res"
	-@erase "$(INTDIR)\MethodTiming.obj"
	-@erase "$(INTDIR)\Random.obj"
	-@erase "$(INTDIR)\RoundRobin.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.dll"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.exp"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.lib"
	-@erase ".\LoadBalancingAlgorithms.h"
	-@erase ".\LoadBalancingAlgorithms.tlb"
	-@erase ".\LoadBalancingAlgorithms_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\LoadBalancingAlgorithms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LoadBalancingAlgorithms.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LoadBalancingAlgorithms.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib pdh.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\LoadBalancingAlgorithms.pdb" /machine:I386 /def:".\LoadBalancingAlgorithms.def" /out:"$(OUTDIR)\LoadBalancingAlgorithms.dll" /implib:"$(OUTDIR)\LoadBalancingAlgorithms.lib" 
DEF_FILE= \
	".\LoadBalancingAlgorithms.def"
LINK32_OBJS= \
	"$(INTDIR)\CPULoad.obj" \
	"$(INTDIR)\LoadBalancingAlgorithms.obj" \
	"$(INTDIR)\MethodTiming.obj" \
	"$(INTDIR)\Random.obj" \
	"$(INTDIR)\RoundRobin.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LoadBalancingAlgorithms.res"

"$(OUTDIR)\LoadBalancingAlgorithms.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\LoadBalancingAlgorithms.dll
InputPath=.\ReleaseMinSize\LoadBalancingAlgorithms.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "LoadBalancingAlgorithms - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\LoadBalancingAlgorithms.dll" ".\LoadBalancingAlgorithms.tlb" ".\LoadBalancingAlgorithms.h" ".\LoadBalancingAlgorithms_i.c"


CLEAN :
	-@erase "$(INTDIR)\CPULoad.obj"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.obj"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.pch"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.res"
	-@erase "$(INTDIR)\MethodTiming.obj"
	-@erase "$(INTDIR)\Random.obj"
	-@erase "$(INTDIR)\RoundRobin.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.dll"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.exp"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.lib"
	-@erase ".\LoadBalancingAlgorithms.h"
	-@erase ".\LoadBalancingAlgorithms.tlb"
	-@erase ".\LoadBalancingAlgorithms_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\LoadBalancingAlgorithms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LoadBalancingAlgorithms.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LoadBalancingAlgorithms.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib pdh.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\LoadBalancingAlgorithms.pdb" /machine:I386 /def:".\LoadBalancingAlgorithms.def" /out:"$(OUTDIR)\LoadBalancingAlgorithms.dll" /implib:"$(OUTDIR)\LoadBalancingAlgorithms.lib" 
DEF_FILE= \
	".\LoadBalancingAlgorithms.def"
LINK32_OBJS= \
	"$(INTDIR)\CPULoad.obj" \
	"$(INTDIR)\LoadBalancingAlgorithms.obj" \
	"$(INTDIR)\MethodTiming.obj" \
	"$(INTDIR)\Random.obj" \
	"$(INTDIR)\RoundRobin.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LoadBalancingAlgorithms.res"

"$(OUTDIR)\LoadBalancingAlgorithms.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LoadBalancingAlgorithms - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\LoadBalancingAlgorithms.dll" ".\LoadBalancingAlgorithms.tlb" ".\LoadBalancingAlgorithms.h" ".\LoadBalancingAlgorithms_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CPULoad.obj"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.obj"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.pch"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.res"
	-@erase "$(INTDIR)\MethodTiming.obj"
	-@erase "$(INTDIR)\Random.obj"
	-@erase "$(INTDIR)\RoundRobin.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.dll"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.exp"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.lib"
	-@erase ".\LoadBalancingAlgorithms.h"
	-@erase ".\LoadBalancingAlgorithms.tlb"
	-@erase ".\LoadBalancingAlgorithms_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\LoadBalancingAlgorithms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LoadBalancingAlgorithms.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LoadBalancingAlgorithms.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib pdh.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\LoadBalancingAlgorithms.pdb" /machine:I386 /def:".\LoadBalancingAlgorithms.def" /out:"$(OUTDIR)\LoadBalancingAlgorithms.dll" /implib:"$(OUTDIR)\LoadBalancingAlgorithms.lib" 
DEF_FILE= \
	".\LoadBalancingAlgorithms.def"
LINK32_OBJS= \
	"$(INTDIR)\CPULoad.obj" \
	"$(INTDIR)\LoadBalancingAlgorithms.obj" \
	"$(INTDIR)\MethodTiming.obj" \
	"$(INTDIR)\Random.obj" \
	"$(INTDIR)\RoundRobin.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LoadBalancingAlgorithms.res"

"$(OUTDIR)\LoadBalancingAlgorithms.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\LoadBalancingAlgorithms.dll
InputPath=.\ReleaseUMinSize\LoadBalancingAlgorithms.dll
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
	

!ELSEIF  "$(CFG)" == "LoadBalancingAlgorithms - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\LoadBalancingAlgorithms.dll" ".\LoadBalancingAlgorithms.tlb" ".\LoadBalancingAlgorithms.h" ".\LoadBalancingAlgorithms_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\CPULoad.obj"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.obj"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.pch"
	-@erase "$(INTDIR)\LoadBalancingAlgorithms.res"
	-@erase "$(INTDIR)\MethodTiming.obj"
	-@erase "$(INTDIR)\Random.obj"
	-@erase "$(INTDIR)\RoundRobin.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.dll"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.exp"
	-@erase "$(OUTDIR)\LoadBalancingAlgorithms.lib"
	-@erase ".\LoadBalancingAlgorithms.h"
	-@erase ".\LoadBalancingAlgorithms.tlb"
	-@erase ".\LoadBalancingAlgorithms_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\LoadBalancingAlgorithms.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LoadBalancingAlgorithms.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LoadBalancingAlgorithms.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib pdh.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\LoadBalancingAlgorithms.pdb" /machine:I386 /def:".\LoadBalancingAlgorithms.def" /out:"$(OUTDIR)\LoadBalancingAlgorithms.dll" /implib:"$(OUTDIR)\LoadBalancingAlgorithms.lib" 
DEF_FILE= \
	".\LoadBalancingAlgorithms.def"
LINK32_OBJS= \
	"$(INTDIR)\CPULoad.obj" \
	"$(INTDIR)\LoadBalancingAlgorithms.obj" \
	"$(INTDIR)\MethodTiming.obj" \
	"$(INTDIR)\Random.obj" \
	"$(INTDIR)\RoundRobin.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\LoadBalancingAlgorithms.res"

"$(OUTDIR)\LoadBalancingAlgorithms.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\LoadBalancingAlgorithms.dll
InputPath=.\ReleaseUMinDependency\LoadBalancingAlgorithms.dll
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
!IF EXISTS("LoadBalancingAlgorithms.dep")
!INCLUDE "LoadBalancingAlgorithms.dep"
!ELSE 
!MESSAGE Warning: cannot find "LoadBalancingAlgorithms.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LoadBalancingAlgorithms - Win32 Debug" || "$(CFG)" == "LoadBalancingAlgorithms - Win32 Unicode Debug" || "$(CFG)" == "LoadBalancingAlgorithms - Win32 Release MinSize" || "$(CFG)" == "LoadBalancingAlgorithms - Win32 Release MinDependency" || "$(CFG)" == "LoadBalancingAlgorithms - Win32 Unicode Release MinSize" || "$(CFG)" == "LoadBalancingAlgorithms - Win32 Unicode Release MinDependency"
SOURCE=.\CPULoad.cpp

"$(INTDIR)\CPULoad.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LoadBalancingAlgorithms.pch"


SOURCE=.\LoadBalancingAlgorithms.cpp

"$(INTDIR)\LoadBalancingAlgorithms.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LoadBalancingAlgorithms.pch"


SOURCE=.\LoadBalancingAlgorithms.idl
MTL_SWITCHES=/I "..\include" /tlb ".\LoadBalancingAlgorithms.tlb" /h "LoadBalancingAlgorithms.h" /iid "LoadBalancingAlgorithms_i.c" /Oicf 

".\LoadBalancingAlgorithms.tlb"	".\LoadBalancingAlgorithms.h"	".\LoadBalancingAlgorithms_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\LoadBalancingAlgorithms.rc

"$(INTDIR)\LoadBalancingAlgorithms.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MethodTiming.cpp

"$(INTDIR)\MethodTiming.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LoadBalancingAlgorithms.pch"


SOURCE=.\Random.cpp

"$(INTDIR)\Random.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LoadBalancingAlgorithms.pch"


SOURCE=.\RoundRobin.cpp

"$(INTDIR)\RoundRobin.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LoadBalancingAlgorithms.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LoadBalancingAlgorithms - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\LoadBalancingAlgorithms.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LoadBalancingAlgorithms.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LoadBalancingAlgorithms - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\LoadBalancingAlgorithms.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LoadBalancingAlgorithms.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LoadBalancingAlgorithms - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\LoadBalancingAlgorithms.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LoadBalancingAlgorithms.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LoadBalancingAlgorithms - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\LoadBalancingAlgorithms.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LoadBalancingAlgorithms.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LoadBalancingAlgorithms - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\LoadBalancingAlgorithms.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LoadBalancingAlgorithms.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LoadBalancingAlgorithms - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\LoadBalancingAlgorithms.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LoadBalancingAlgorithms.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

