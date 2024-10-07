# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Tool - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Tool - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Tool - Win32 Release" && "$(CFG)" != "Tool - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tool.mak" CFG="Tool - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tool - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Tool - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Tool - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Tool - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Tool.exe"

CLEAN : 
	-@erase "$(INTDIR)\DlgAbout.obj"
	-@erase "$(INTDIR)\FormCommandView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RenderView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tool.obj"
	-@erase "$(INTDIR)\Tool.pch"
	-@erase "$(INTDIR)\Tool.res"
	-@erase "$(INTDIR)\ToolDoc.obj"
	-@erase "$(OUTDIR)\Tool.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Tool.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x804 /fo"$(INTDIR)/Tool.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tool.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Tool.pdb" /machine:I386\
 /out:"$(OUTDIR)/Tool.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DlgAbout.obj" \
	"$(INTDIR)\FormCommandView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RenderView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tool.obj" \
	"$(INTDIR)\Tool.res" \
	"$(INTDIR)\ToolDoc.obj"

"$(OUTDIR)\Tool.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Tool.exe"

CLEAN : 
	-@erase "$(INTDIR)\DlgAbout.obj"
	-@erase "$(INTDIR)\FormCommandView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RenderView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tool.obj"
	-@erase "$(INTDIR)\Tool.pch"
	-@erase "$(INTDIR)\Tool.res"
	-@erase "$(INTDIR)\ToolDoc.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Tool.exe"
	-@erase "$(OUTDIR)\Tool.ilk"
	-@erase "$(OUTDIR)\Tool.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Tool.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x804 /fo"$(INTDIR)/Tool.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tool.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Tool.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Tool.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DlgAbout.obj" \
	"$(INTDIR)\FormCommandView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RenderView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tool.obj" \
	"$(INTDIR)\Tool.res" \
	"$(INTDIR)\ToolDoc.obj"

"$(OUTDIR)\Tool.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Tool - Win32 Release"
# Name "Tool - Win32 Debug"

!IF  "$(CFG)" == "Tool - Win32 Release"

!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Tool.cpp
DEP_CPP_TOOL_=\
	".\DlgAbout.h"\
	".\MainFrm.h"\
	".\RenderView.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

"$(INTDIR)\Tool.obj" : $(SOURCE) $(DEP_CPP_TOOL_) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Tool - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Tool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Tool.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Tool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Tool.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\FormCommandView.h"\
	".\MainFrm.h"\
	".\RenderView.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ToolDoc.cpp
DEP_CPP_TOOLD=\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

"$(INTDIR)\ToolDoc.obj" : $(SOURCE) $(DEP_CPP_TOOLD) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\RenderView.cpp
DEP_CPP_RENDE=\
	".\RenderView.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

"$(INTDIR)\RenderView.obj" : $(SOURCE) $(DEP_CPP_RENDE) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tool.rc
DEP_RSC_TOOL_R=\
	".\res\cursor1.cur"\
	".\res\Tool.ico"\
	".\res\Tool.rc2"\
	".\res\Toolbar.bmp"\
	".\res\ToolDoc.ico"\
	

"$(INTDIR)\Tool.res" : $(SOURCE) $(DEP_RSC_TOOL_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgAbout.cpp
DEP_CPP_DLGAB=\
	".\DlgAbout.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DlgAbout.obj" : $(SOURCE) $(DEP_CPP_DLGAB) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\FormCommandView.cpp
DEP_CPP_FORMC=\
	".\FormCommandView.h"\
	".\MainFrm.h"\
	".\RenderView.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

"$(INTDIR)\FormCommandView.obj" : $(SOURCE) $(DEP_CPP_FORMC) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


# End Source File
# End Target
# End Project
################################################################################
