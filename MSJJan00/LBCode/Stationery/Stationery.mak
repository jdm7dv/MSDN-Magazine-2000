# Microsoft Developer Studio Generated NMAKE File, Based on Stationery.dsp
!IF "$(CFG)" == ""
CFG=Stationery - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Stationery - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Stationery - Win32 Debug" && "$(CFG)" != "Stationery - Win32 Unicode Debug" && "$(CFG)" != "Stationery - Win32 Release MinSize" && "$(CFG)" != "Stationery - Win32 Release MinDependency" && "$(CFG)" != "Stationery - Win32 Unicode Release MinSize" && "$(CFG)" != "Stationery - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Stationery.mak" CFG="Stationery - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Stationery - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Stationery - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Stationery - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Stationery - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Stationery - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Stationery - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "Stationery - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Stationery.dll" ".\Stationery.tlb" ".\Stationery.h" ".\Stationery_i.c" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Envelope.obj"
	-@erase "$(INTDIR)\Stationery.obj"
	-@erase "$(INTDIR)\Stationery.pch"
	-@erase "$(INTDIR)\Stationery.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Stationery.dll"
	-@erase "$(OUTDIR)\Stationery.exp"
	-@erase "$(OUTDIR)\Stationery.ilk"
	-@erase "$(OUTDIR)\Stationery.lib"
	-@erase "$(OUTDIR)\Stationery.pdb"
	-@erase ".\Stationery.h"
	-@erase ".\Stationery.tlb"
	-@erase ".\Stationery_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\Stationery.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Stationery.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Stationery.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Stationery.pdb" /debug /machine:I386 /def:".\Stationery.def" /out:"$(OUTDIR)\Stationery.dll" /implib:"$(OUTDIR)\Stationery.lib" /pdbtype:sept 
DEF_FILE= \
	".\Stationery.def"
LINK32_OBJS= \
	"$(INTDIR)\Envelope.obj" \
	"$(INTDIR)\Stationery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Stationery.res"

"$(OUTDIR)\Stationery.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\Stationery.dll
InputPath=.\Debug\Stationery.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Stationery - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\Stationery.dll" ".\Stationery.tlb" ".\Stationery.h" ".\Stationery_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Envelope.obj"
	-@erase "$(INTDIR)\Stationery.obj"
	-@erase "$(INTDIR)\Stationery.pch"
	-@erase "$(INTDIR)\Stationery.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Stationery.dll"
	-@erase "$(OUTDIR)\Stationery.exp"
	-@erase "$(OUTDIR)\Stationery.ilk"
	-@erase "$(OUTDIR)\Stationery.lib"
	-@erase "$(OUTDIR)\Stationery.pdb"
	-@erase ".\Stationery.h"
	-@erase ".\Stationery.tlb"
	-@erase ".\Stationery_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Stationery.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Stationery.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Stationery.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Stationery.pdb" /debug /machine:I386 /def:".\Stationery.def" /out:"$(OUTDIR)\Stationery.dll" /implib:"$(OUTDIR)\Stationery.lib" /pdbtype:sept 
DEF_FILE= \
	".\Stationery.def"
LINK32_OBJS= \
	"$(INTDIR)\Envelope.obj" \
	"$(INTDIR)\Stationery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Stationery.res"

"$(OUTDIR)\Stationery.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\Stationery.dll
InputPath=.\DebugU\Stationery.dll
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
	

!ELSEIF  "$(CFG)" == "Stationery - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\Stationery.dll" ".\Stationery.tlb" ".\Stationery.h" ".\Stationery_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Envelope.obj"
	-@erase "$(INTDIR)\Stationery.obj"
	-@erase "$(INTDIR)\Stationery.pch"
	-@erase "$(INTDIR)\Stationery.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Stationery.dll"
	-@erase "$(OUTDIR)\Stationery.exp"
	-@erase "$(OUTDIR)\Stationery.lib"
	-@erase ".\Stationery.h"
	-@erase ".\Stationery.tlb"
	-@erase ".\Stationery_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\Stationery.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Stationery.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Stationery.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Stationery.pdb" /machine:I386 /def:".\Stationery.def" /out:"$(OUTDIR)\Stationery.dll" /implib:"$(OUTDIR)\Stationery.lib" 
DEF_FILE= \
	".\Stationery.def"
LINK32_OBJS= \
	"$(INTDIR)\Envelope.obj" \
	"$(INTDIR)\Stationery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Stationery.res"

"$(OUTDIR)\Stationery.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\Stationery.dll
InputPath=.\ReleaseMinSize\Stationery.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Stationery - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\Stationery.dll" ".\Stationery.tlb" ".\Stationery.h" ".\Stationery_i.c"


CLEAN :
	-@erase "$(INTDIR)\Envelope.obj"
	-@erase "$(INTDIR)\Stationery.obj"
	-@erase "$(INTDIR)\Stationery.pch"
	-@erase "$(INTDIR)\Stationery.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Stationery.dll"
	-@erase "$(OUTDIR)\Stationery.exp"
	-@erase "$(OUTDIR)\Stationery.lib"
	-@erase ".\Stationery.h"
	-@erase ".\Stationery.tlb"
	-@erase ".\Stationery_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\Stationery.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Stationery.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Stationery.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Stationery.pdb" /machine:I386 /def:".\Stationery.def" /out:"$(OUTDIR)\Stationery.dll" /implib:"$(OUTDIR)\Stationery.lib" 
DEF_FILE= \
	".\Stationery.def"
LINK32_OBJS= \
	"$(INTDIR)\Envelope.obj" \
	"$(INTDIR)\Stationery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Stationery.res"

"$(OUTDIR)\Stationery.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Stationery - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\Stationery.dll" ".\Stationery.tlb" ".\Stationery.h" ".\Stationery_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Envelope.obj"
	-@erase "$(INTDIR)\Stationery.obj"
	-@erase "$(INTDIR)\Stationery.pch"
	-@erase "$(INTDIR)\Stationery.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Stationery.dll"
	-@erase "$(OUTDIR)\Stationery.exp"
	-@erase "$(OUTDIR)\Stationery.lib"
	-@erase ".\Stationery.h"
	-@erase ".\Stationery.tlb"
	-@erase ".\Stationery_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Stationery.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Stationery.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Stationery.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Stationery.pdb" /machine:I386 /def:".\Stationery.def" /out:"$(OUTDIR)\Stationery.dll" /implib:"$(OUTDIR)\Stationery.lib" 
DEF_FILE= \
	".\Stationery.def"
LINK32_OBJS= \
	"$(INTDIR)\Envelope.obj" \
	"$(INTDIR)\Stationery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Stationery.res"

"$(OUTDIR)\Stationery.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\Stationery.dll
InputPath=.\ReleaseUMinSize\Stationery.dll
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
	

!ELSEIF  "$(CFG)" == "Stationery - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\Stationery.dll" ".\Stationery.tlb" ".\Stationery.h" ".\Stationery_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Envelope.obj"
	-@erase "$(INTDIR)\Stationery.obj"
	-@erase "$(INTDIR)\Stationery.pch"
	-@erase "$(INTDIR)\Stationery.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Stationery.dll"
	-@erase "$(OUTDIR)\Stationery.exp"
	-@erase "$(OUTDIR)\Stationery.lib"
	-@erase ".\Stationery.h"
	-@erase ".\Stationery.tlb"
	-@erase ".\Stationery_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Stationery.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Stationery.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Stationery.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Stationery.pdb" /machine:I386 /def:".\Stationery.def" /out:"$(OUTDIR)\Stationery.dll" /implib:"$(OUTDIR)\Stationery.lib" 
DEF_FILE= \
	".\Stationery.def"
LINK32_OBJS= \
	"$(INTDIR)\Envelope.obj" \
	"$(INTDIR)\Stationery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Stationery.res"

"$(OUTDIR)\Stationery.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\Stationery.dll
InputPath=.\ReleaseUMinDependency\Stationery.dll
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
!IF EXISTS("Stationery.dep")
!INCLUDE "Stationery.dep"
!ELSE 
!MESSAGE Warning: cannot find "Stationery.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Stationery - Win32 Debug" || "$(CFG)" == "Stationery - Win32 Unicode Debug" || "$(CFG)" == "Stationery - Win32 Release MinSize" || "$(CFG)" == "Stationery - Win32 Release MinDependency" || "$(CFG)" == "Stationery - Win32 Unicode Release MinSize" || "$(CFG)" == "Stationery - Win32 Unicode Release MinDependency"
SOURCE=.\Envelope.cpp

"$(INTDIR)\Envelope.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Stationery.pch"


SOURCE=.\Stationery.cpp

"$(INTDIR)\Stationery.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Stationery.pch"


SOURCE=.\Stationery.idl
MTL_SWITCHES=/tlb ".\Stationery.tlb" /h "Stationery.h" /iid "Stationery_i.c" /Oicf 

".\Stationery.tlb"	".\Stationery.h"	".\Stationery_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\Stationery.rc

"$(INTDIR)\Stationery.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Stationery - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\Stationery.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Stationery.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Stationery - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Stationery.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Stationery.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Stationery - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\Stationery.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Stationery.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Stationery - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\Stationery.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Stationery.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Stationery - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Stationery.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Stationery.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Stationery - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Stationery.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Stationery.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

