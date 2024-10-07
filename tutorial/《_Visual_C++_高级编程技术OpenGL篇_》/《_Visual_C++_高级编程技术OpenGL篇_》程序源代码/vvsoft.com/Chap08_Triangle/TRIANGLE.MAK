# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Triangle - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Triangle - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Triangle - Win32 Release" && "$(CFG)" !=\
 "Triangle - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Triangle.mak" CFG="Triangle - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Triangle - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Triangle - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Triangle - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Triangle - Win32 Release"

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

ALL : "$(OUTDIR)\Triangle.exe" "$(OUTDIR)\Triangle.pch"

CLEAN : 
	-@erase ".\Release\Triangle.exe"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\TriangleView.obj"
	-@erase ".\Release\TriangleDoc.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\Triangle.obj"
	-@erase ".\Release\Triangle.res"
	-@erase ".\Release\Triangle.pch"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Triangle.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Triangle.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Triangle.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Triangle.pdb" /machine:I386\
 /out:"$(OUTDIR)/Triangle.exe" 
LINK32_OBJS= \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/TriangleView.obj" \
	"$(INTDIR)/TriangleDoc.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/Triangle.obj" \
	"$(INTDIR)/Triangle.res"

"$(OUTDIR)\Triangle.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Triangle - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Triangle"
# PROP BASE Intermediate_Dir "Triangle"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Triangle"
# PROP Intermediate_Dir "Triangle"
# PROP Target_Dir ""
OUTDIR=.\Triangle
INTDIR=.\Triangle

ALL : "$(OUTDIR)\Triangle.exe" "$(OUTDIR)\Triangle.pch"

CLEAN : 
	-@erase ".\Triangle\vc40.pdb"
	-@erase ".\Triangle\vc40.idb"
	-@erase ".\Triangle\Triangle.exe"
	-@erase ".\Triangle\Triangle.obj"
	-@erase ".\Triangle\MainFrm.obj"
	-@erase ".\Triangle\TriangleDoc.obj"
	-@erase ".\Triangle\StdAfx.obj"
	-@erase ".\Triangle\TriangleView.obj"
	-@erase ".\Triangle\Triangle.res"
	-@erase ".\Triangle\Triangle.ilk"
	-@erase ".\Triangle\Triangle.pdb"
	-@erase ".\Triangle\Triangle.pch"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Triangle.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Triangle/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Triangle.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Triangle.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Triangle.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Triangle.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Triangle.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/TriangleDoc.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/TriangleView.obj" \
	"$(INTDIR)/Triangle.res"

"$(OUTDIR)\Triangle.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Triangle - Win32 Release"
# Name "Triangle - Win32 Debug"

!IF  "$(CFG)" == "Triangle - Win32 Release"

!ELSEIF  "$(CFG)" == "Triangle - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Triangle - Win32 Release"

!ELSEIF  "$(CFG)" == "Triangle - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Triangle.cpp
DEP_CPP_TRIAN=\
	".\StdAfx.h"\
	".\Triangle.h"\
	".\MainFrm.h"\
	".\TriangleDoc.h"\
	".\TriangleView.h"\
	

"$(INTDIR)\Triangle.obj" : $(SOURCE) $(DEP_CPP_TRIAN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Triangle - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Triangle.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Triangle.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Triangle - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Triangle.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Triangle.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\Triangle.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TriangleDoc.cpp
DEP_CPP_TRIANG=\
	".\StdAfx.h"\
	".\Triangle.h"\
	".\TriangleDoc.h"\
	

"$(INTDIR)\TriangleDoc.obj" : $(SOURCE) $(DEP_CPP_TRIANG) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TriangleView.cpp
DEP_CPP_TRIANGL=\
	".\StdAfx.h"\
	".\Triangle.h"\
	".\TriangleDoc.h"\
	".\TriangleView.h"\
	

"$(INTDIR)\TriangleView.obj" : $(SOURCE) $(DEP_CPP_TRIANGL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Triangle.rc
DEP_RSC_TRIANGLE=\
	".\res\Triangle.ico"\
	".\res\TriangleDoc.ico"\
	".\res\Triangle.rc2"\
	

"$(INTDIR)\Triangle.res" : $(SOURCE) $(DEP_RSC_TRIANGLE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
