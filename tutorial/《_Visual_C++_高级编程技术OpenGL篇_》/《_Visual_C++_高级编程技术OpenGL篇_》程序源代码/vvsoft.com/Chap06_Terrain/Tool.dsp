# Microsoft Developer Studio Project File - Name="Tool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Tool - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Tool.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tool.mak" CFG="Tool - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tool - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Tool - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Tool - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" "StdAfx.h" /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Tool - Win32 Release"
# Name "Tool - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DlgAbout.cpp
DEP_CPP_DLGAB=\
	".\DlgAbout.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Tool - Win32 Release"

!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FormCommandView.cpp
DEP_CPP_FORMC=\
	".\formcommandview.h"\
	".\glm.h"\
	".\MainFrm.h"\
	".\RenderView.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

!IF  "$(CFG)" == "Tool - Win32 Release"

!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\glm.cpp
DEP_CPP_GLM_C=\
	".\glm.h"\
	

!IF  "$(CFG)" == "Tool - Win32 Release"

!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\formcommandview.h"\
	".\glm.h"\
	".\MainFrm.h"\
	".\RenderView.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

!IF  "$(CFG)" == "Tool - Win32 Release"

!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RenderView.cpp
DEP_CPP_RENDE=\
	".\glm.h"\
	".\RenderView.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

!IF  "$(CFG)" == "Tool - Win32 Release"

!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Tool - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Tool.cpp
DEP_CPP_TOOL_=\
	".\DlgAbout.h"\
	".\glm.h"\
	".\MainFrm.h"\
	".\RenderView.h"\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

!IF  "$(CFG)" == "Tool - Win32 Release"

!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Tool.rc
# End Source File
# Begin Source File

SOURCE=.\ToolDoc.cpp
DEP_CPP_TOOLD=\
	".\StdAfx.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

!IF  "$(CFG)" == "Tool - Win32 Release"

!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DlgAbout.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\RenderView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Tool.h
# End Source File
# Begin Source File

SOURCE=.\ToolDoc.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\RES\texture.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tool.ico
# End Source File
# Begin Source File

SOURCE=.\res\Tool.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Tool.reg
# End Source File
# End Target
# End Project
