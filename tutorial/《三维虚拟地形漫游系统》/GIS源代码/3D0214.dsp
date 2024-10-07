# Microsoft Developer Studio Project File - Name="3D0214" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=3D0214 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "3D0214.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "3D0214.mak" CFG="3D0214 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "3D0214 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "3D0214 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "3D0214 - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "3D0214 - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "3D0214 - Win32 Release"
# Name "3D0214 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\3D0214.cpp
# End Source File
# Begin Source File

SOURCE=.\3D0214.rc
# End Source File
# Begin Source File

SOURCE=.\3D0214Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\3D0214View.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ColorListBox.CPP
# End Source File
# Begin Source File

SOURCE=.\src\ColorPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\src\CoolTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBaseHeight.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgClassBreakRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCreateContour.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCreateRasterIDW.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCreateTINfromFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfoQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProfileGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetScene.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSlope.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewshed.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\src\scbarg.cpp
# End Source File
# Begin Source File

SOURCE=.\scenecontroldefault.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\toccontroldefault.cpp
# End Source File
# Begin Source File

SOURCE=.\TocDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\toolbarcontroldefault.cpp
# End Source File
# Begin Source File

SOURCE=.\WZDBTMAP.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\3D0214.h
# End Source File
# Begin Source File

SOURCE=.\3D0214Doc.h
# End Source File
# Begin Source File

SOURCE=.\3D0214View.h
# End Source File
# Begin Source File

SOURCE=.\src\ColorListBox.H
# End Source File
# Begin Source File

SOURCE=.\src\ColorPicker.h
# End Source File
# Begin Source File

SOURCE=.\src\CoolTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgBaseHeight.h
# End Source File
# Begin Source File

SOURCE=.\DlgClassBreakRenderer.h
# End Source File
# Begin Source File

SOURCE=.\DlgCreateContour.h
# End Source File
# Begin Source File

SOURCE=.\DlgCreateRasterIDW.h
# End Source File
# Begin Source File

SOURCE=.\DlgCreateTINfromFeature.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfoQuery.h
# End Source File
# Begin Source File

SOURCE=.\DlgProfileGraph.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetScene.h
# End Source File
# Begin Source File

SOURCE=.\DlgSlope.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewshed.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\src\scbarg.h
# End Source File
# Begin Source File

SOURCE=.\scenecontroldefault.h
# End Source File
# Begin Source File

SOURCE=.\src\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\toccontroldefault.h
# End Source File
# Begin Source File

SOURCE=.\TocDlg.h
# End Source File
# Begin Source File

SOURCE=.\toolbarcontroldefault.h
# End Source File
# Begin Source File

SOURCE=.\WZDBTMAP.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\3D0214.ico
# End Source File
# Begin Source File

SOURCE=.\res\3D0214.rc2
# End Source File
# Begin Source File

SOURCE=.\res\3D0214Doc.ico
# End Source File
# Begin Source File

SOURCE=.\ArcScene.bmp
# End Source File
# Begin Source File

SOURCE=.\QiDong.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section 3D0214 : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section 3D0214 : {D959783F-B033-4A0C-966B-DB90FE45BEE5}
# 	2:5:Class:CToolbarControlDefault
# 	2:10:HeaderFile:toolbarcontroldefault.h
# 	2:8:ImplFile:toolbarcontroldefault.cpp
# End Section
# Section 3D0214 : {B7D4358E-3CBC-11D6-AA09-00104BB6FC1C}
# 	2:21:DefaultSinkHeaderFile:toolbarcontroldefault.h
# 	2:16:DefaultSinkClass:CToolbarControlDefault
# End Section
# Section 3D0214 : {A0F9A9A2-4A3F-4888-826F-CA2BFA23CF17}
# 	2:21:DefaultSinkHeaderFile:toccontroldefault.h
# 	2:16:DefaultSinkClass:CTOCControlDefault
# End Section
# Section 3D0214 : {DD4B8602-61F1-4528-82DF-8B5ACC862F84}
# 	2:21:DefaultSinkHeaderFile:scenecontroldefault.h
# 	2:16:DefaultSinkClass:CSceneControlDefault
# End Section
# Section 3D0214 : {6F7C3AFD-EE18-4633-8611-A2AA3CFB869B}
# 	2:5:Class:CSceneControlDefault
# 	2:10:HeaderFile:scenecontroldefault.h
# 	2:8:ImplFile:scenecontroldefault.cpp
# End Section
# Section 3D0214 : {DAA3AECE-0C15-42BA-A34D-0DFE38C68586}
# 	2:5:Class:CTOCControlDefault
# 	2:10:HeaderFile:toccontroldefault.h
# 	2:8:ImplFile:toccontroldefault.cpp
# End Section
