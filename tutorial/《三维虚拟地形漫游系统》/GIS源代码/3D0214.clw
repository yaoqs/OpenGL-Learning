; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMy3D0214View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "3D0214.h"
LastPage=0

ClassCount=17
Class1=CMy3D0214App
Class2=CMy3D0214Doc
Class3=CMy3D0214View
Class4=CMainFrame

ResourceCount=15
Resource1=IDR_TOOLBAR1
Resource2=IDD_DIG_BASEHEIGHT
Class5=CAboutDlg
Resource3=IDD_DLG_SLOPE
Resource4=IDD_MY3D0214_FORM
Class6=CTocDlg
Class7=CSplash
Resource5=IDD_DLG_CREATE_TIN
Class8=CDlgCreateRasterIDW
Resource6=IDD_TOCDLG
Class9=CDlgCreateTINfromFeature
Resource7=IDD_DLG_PROFILE_GRAPH
Class10=CDlgSetScene
Resource8=IDD_DLG_CLASSBREAKRENDERER
Class11=CDlgBaseHeight
Resource9=IDD_DLG_CREATE_CONTOUR
Class12=CDlgClassBreakRenderer
Resource10=IDD_DLG_CREATE_RASTER_IDW
Class13=CDlgSlope
Resource11=IDD_DLG_VIEWSHED
Class14=CDlgViewshed
Resource12=IDD_DLD_SET_SCENE
Class15=CDlgProfileGraph
Resource13=IDD_ABOUTBOX
Class16=CDlgCreateContour
Resource14=IDR_MAINFRAME
Class17=CDlgInfoQuery
Resource15=IDD_DLG_INFO_QUERY

[CLS:CMy3D0214App]
Type=0
HeaderFile=3D0214.h
ImplementationFile=3D0214.cpp
Filter=N

[CLS:CMy3D0214Doc]
Type=0
HeaderFile=3D0214Doc.h
ImplementationFile=3D0214Doc.cpp
Filter=N

[CLS:CMy3D0214View]
Type=0
HeaderFile=3D0214View.h
ImplementationFile=3D0214View.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=IDC_SCENECONTROL1


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_SELECTFEATRUES




[CLS:CAboutDlg]
Type=0
HeaderFile=3D0214.cpp
ImplementationFile=3D0214.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_EXPORT_MAP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_ADD_DEM_TO_SCENE
Command18=ID_CREATE_RASTER_IDW
Command19=ID_CREATEDEM_TIN
Command20=ID_SET_SCENE
Command21=ID_SET_BASEHEIGHT
Command22=ID_CLASSBREAKRENDERER
Command23=ID_INFORMATION_QUERY
Command24=ID_CREATE_SLOP
Command25=ID_VIEWSHED
Command26=ID_LINEOFSIGHTPROFILE
Command27=ID_CREATE_CONTOUR
Command28=ID_APP_ABOUT
CommandCount=28

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_MY3D0214_FORM]
Type=1
Class=CMy3D0214View
ControlCount=1
Control1=IDC_SCENECONTROL1,{DD4B8602-61F1-4528-82DF-8B5ACC862F84},1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_ADDLAYER
Command10=ID_SELECTFEATRUES
CommandCount=10

[TB:IDR_TOOLBAR1]
Type=1
Class=?
Command1=ID_PLACEHOLD
Command2=ID_1
CommandCount=2

[DLG:IDD_TOCDLG]
Type=1
Class=CTocDlg
ControlCount=1
Control1=IDC_TOCCONTROL1,{A0F9A9A2-4A3F-4888-826F-CA2BFA23CF17},1342242816

[CLS:CTocDlg]
Type=0
HeaderFile=TocDlg.h
ImplementationFile=TocDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_TOCCONTROL1

[CLS:CSplash]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd
Filter=W
LastObject=CSplash
VirtualFilter=WC

[DLG:IDD_DLG_CREATE_RASTER_IDW]
Type=1
Class=CDlgCreateRasterIDW
ControlCount=21
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC_Set1,static,1342308352
Control9=IDC_STATIC_Set2,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_IDW_POINT_INPUT,edit,1350633600
Control13=IDC_EDIT_IDW_WIGHT,edit,1350631552
Control14=IDC_EDIT_IDW_RADIUSSETTINGS_1,edit,1350631552
Control15=IDC_EDIT_IDW_RADIUSSETTINGS_2,edit,1350631552
Control16=IDC_EDIT_IDW_INPUT_CELL_SIZE,edit,1350631552
Control17=IDC_EDIT_IDW_OUTPUT_RASTER,edit,1350631552
Control18=IDC_BUTTON_IDW_ADDPOINTLAYER,button,1342242816
Control19=IDC_COMBO_IDW_ZVALUE_FIELD,combobox,1344340226
Control20=IDC_COMBO_IDW_SEARCH_RADIUS_TYPE,combobox,1344340226
Control21=IDC_BUTTON_SELSAVERASTERPATH,button,1342242816

[CLS:CDlgCreateRasterIDW]
Type=0
HeaderFile=DlgCreateRasterIDW.h
ImplementationFile=DlgCreateRasterIDW.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgCreateRasterIDW

[DLG:IDD_DLG_CREATE_TIN]
Type=1
Class=CDlgCreateTINfromFeature
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_TIN_INPUTS,edit,1350633600
Control8=IDC_EDIT_TIN_OUTPUT,edit,1350631552
Control9=IDC_COMBO_TIN_HEIGHT_FIELD,combobox,1344340227
Control10=IDC_COMBO_TIN_TRIANGU,combobox,1344339971
Control11=IDC_STATIC,button,1342177287
Control12=IDC_BUTTON_TIN_INPUTS,button,1342242816
Control13=IDC_BUTTON_SAVEFILEPATH,button,1342242816

[CLS:CDlgCreateTINfromFeature]
Type=0
HeaderFile=DlgCreateTINfromFeature.h
ImplementationFile=DlgCreateTINfromFeature.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgCreateTINfromFeature

[DLG:IDD_DLD_SET_SCENE]
Type=1
Class=CDlgSetScene
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_EXAGGERATIONFACTOR,edit,1350631552
Control5=IDC_BUTTON_EXAGGERATIONFACTOR,button,1342242816

[CLS:CDlgSetScene]
Type=0
HeaderFile=DlgSetScene.h
ImplementationFile=DlgSetScene.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_DIG_BASEHEIGHT]
Type=1
Class=CDlgBaseHeight
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_COMBO_CURRENT_LAYER,combobox,1344339970
Control6=IDC_COMBO_LAYERS,combobox,1344339970

[CLS:CDlgBaseHeight]
Type=0
HeaderFile=DlgBaseHeight.h
ImplementationFile=DlgBaseHeight.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgBaseHeight

[DLG:IDD_DLG_CLASSBREAKRENDERER]
Type=1
Class=CDlgClassBreakRenderer
ControlCount=10
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO_CLASSES_NUM,combobox,1344340227
Control7=IDC_BUTTON_COLOR_RAMP,button,1342242816
Control8=IDC_LIST_COLOR_RANGE,listbox,1352728913
Control9=IDC_BUTTON_START_COLOR,button,1342242827
Control10=IDC_BUTTON_END_COLOR,button,1342242827

[CLS:CDlgClassBreakRenderer]
Type=0
HeaderFile=DlgClassBreakRenderer.h
ImplementationFile=DlgClassBreakRenderer.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST_COLOR_RANGE

[DLG:IDD_DLG_SLOPE]
Type=1
Class=CDlgSlope
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,button,1342177287
Control7=IDC_EDIT_INPUT_SURF_SLOPE,edit,1350633600
Control8=IDC_EDIT_OUTPUT_CELLSIZE_SLOPE,edit,1350631552
Control9=IDC_EDIT_OUTPUT_RASTER_SLOPE,edit,1350633600
Control10=IDC_BUTTON_INPUTSURF_SLOPE,button,1342242816
Control11=IDC_BUTTON_OUTPUTRASTER_SLOPE,button,1342242816
Control12=IDC_RADIO_DEGREE_SLOPE,button,1342308361
Control13=IDC_RADIO_PERCENT_SLOPE,button,1342308361

[CLS:CDlgSlope]
Type=0
HeaderFile=DlgSlope.h
ImplementationFile=DlgSlope.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_DLG_VIEWSHED]
Type=1
Class=CDlgViewshed
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_VIEWSHED_SURFACEINPUT,edit,1350633600
Control8=IDC_EDIT_VIEWSHED_OBSERVERPOINTS,edit,1350633600
Control9=IDC_EDIT_VIEWSHED_CELLSIZE,edit,1350631552
Control10=IDC_BUTTON_VIEWSHED_SURFACEINPUT,button,1342242816
Control11=IDC_EDIT_VIEWSHED_RASTEROUTPUT,edit,1350633600
Control12=IDC_BUTTON_VIEWSHED_OBSERVERPOINTS,button,1342242816
Control13=IDC_BUTTON_VIEWSHED_RASTEROUTPUT,button,1342242816

[CLS:CDlgViewshed]
Type=0
HeaderFile=DlgViewshed.h
ImplementationFile=DlgViewshed.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_DLG_PROFILE_GRAPH]
Type=1
Class=CDlgProfileGraph
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC_PROFILE_GRAPH,static,1342177287

[CLS:CDlgProfileGraph]
Type=0
HeaderFile=DlgProfileGraph.h
ImplementationFile=DlgProfileGraph.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgProfileGraph

[DLG:IDD_DLG_CREATE_CONTOUR]
Type=1
Class=CDlgCreateContour
ControlCount=25
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,button,1342177287
Control15=IDC_EDIT_CONTOUR_SURFACE_INPUT,edit,1350633600
Control16=IDC_EDIT_CONTOUR_CONTOURINTERVAL,edit,1350631552
Control17=IDC_EDIT_CONTOUR_BASECONTOUR,edit,1350631552
Control18=IDC_EDIT_CONTOUR_FEATURE_OUTPUT,edit,1350633600
Control19=IDC_EDIT_CONTOUR_ZMIN,edit,1342244993
Control20=IDC_EDIT_CONTOUR_ZMAX,edit,1342244993
Control21=IDC_EDIT_CONTOUR_MINCONTOUR,edit,1342244993
Control22=IDC_EDIT_CONTOUR_MAXCONTOUR,edit,1342244993
Control23=IDC_EDIT_CONTOUR_TOTALNUMCONTOUR,edit,1342244993
Control24=IDC_BUTTON_CONTOUR_FEATURE_OUTPUT,button,1342242816
Control25=IDC_BUTTON_CONTOUR_SURFACE_INPUT,button,1342242816

[CLS:CDlgCreateContour]
Type=0
HeaderFile=DlgCreateContour.h
ImplementationFile=DlgCreateContour.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_CONTOUR_CONTOURINTERVAL
VirtualFilter=dWC

[DLG:IDD_DLG_INFO_QUERY]
Type=1
Class=CDlgInfoQuery
ControlCount=6
Control1=IDC_EDIT_X,edit,1350631552
Control2=IDC_EDIT_Y,edit,1350631552
Control3=IDC_EDIT_Z,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CDlgInfoQuery]
Type=0
HeaderFile=DlgInfoQuery.h
ImplementationFile=DlgInfoQuery.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgInfoQuery
VirtualFilter=dWC

