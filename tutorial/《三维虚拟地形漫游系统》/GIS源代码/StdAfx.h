// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__CC915EC1_72DF_4725_81DD_9AFBC238C766__INCLUDED_)
#define AFX_STDAFX_H__CC915EC1_72DF_4725_81DD_9AFBC238C766__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers


#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "atlbase.h"
extern CComModule _Module;  // This is not a COM module but this global just ensures ATL can find the module resource instance
#include <atlcom.h>
//#include <atlwin.h>
//#include <atlhost.h>
#include "src\sizecbar.h" 
#include "src\scbarg.h"
#include "src\CoolTabCtrl.h"
#pragma warning(push)
#pragma warning(disable: 4192)
#pragma warning(disable: 4146)
/*
#import "d:/Program Files/ArcGis/com/esriSystem.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE", "VARTYPE")
#import "d:/Program Files/ArcGis/com/esriSystemUI.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("IProgressDialog")
#import "d:/Program Files/ArcGIS/com/esriFramework.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE")

#import "d:/Program Files/ArcGis/bin/ToolbarControl.ocx" raw_interfaces_only raw_native_types no_namespace named_guids
#import "d:/Program Files/ArcGis/bin/TOCControl.ocx" raw_interfaces_only raw_native_types no_namespace named_guids

#import "d:/Program Files/ArcGis/com/esriGeometry.olb" raw_interfaces_only raw_native_types no_namespace named_guids
#import "d:/Program Files/ArcGis/com/esriDisplay.olb" raw_interfaces_only raw_native_types no_namespace named_guids

#import "d:/Program Files/ArcGis/com/esriGeoDatabase.olb" raw_interfaces_only raw_native_types no_namespace named_guids
#import "d:/Program Files/ArcGis/com/esri3DAnalyst.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE", "VARTYPE")
#import "d:/Program Files/ArcGis/bin/SceneControl.ocx" raw_interfaces_only raw_native_types no_namespace named_guids
#import "d:/Program Files/ArcGis/com/esriOutput.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE", "VARTYPE")

#import "d:/Program Files/ArcGis/com/esriCatalogUI.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE", "VARTYPE", "IStatusBar")
#import "d:/Program Files/ArcGis/com/esriCatalog.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE", "VARTYPE", "IStatusBar")

#import "d:/Program Files/ArcGis/com/esri3DAnalystUI.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE", "VARTYPE", "IStatusBar")
#import "d:/Program Files/ArcGis/com/esriNetworkAnalysis.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE", "VARTYPE", "IStatusBar")
#import "d:/Program Files/ArcGis/com/esriGeoAnalyst.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE", "VARTYPE", "IStatusBar")

#import "d:/Program Files/ArcGIS/com/esriCarto.olb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 
#import "d:/Program Files/ArcGIS/com/esriCartoUI.olb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

#import "d:/Program Files/ArcGis/com/esriSpatialAnalyst.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE", "VARTYPE", "IStatusBar")
#import "d:/Program Files/ArcGis/com/esriSpatialAnalystUI.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE", "VARTYPE", "IStatusBar")

#import "d:/Program Files/ArcGIS/com/esriDataSourcesFile.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE")
#import "d:/Program Files/ArcGIS/com/esriDataSourcesGDB.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE")
#import "d:/Program Files/ArcGIS/com/esriDataSourcesRaster.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE")
#import "d:/Program Files/ArcGIS/com/esriDataSourcesRasterUI.olb" raw_interfaces_only raw_native_types no_namespace named_guids exclude("OLE_COLOR", "OLE_HANDLE")
*/

//#import "DATE\C0214.dll" no_namespace
#pragma warning(pop)
//{{AFX_INSERT_LOCATION}}                                                                                                                                                                   
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CC915EC1_72DF_4725_81DD_9AFBC238C766__INCLUDED_)
