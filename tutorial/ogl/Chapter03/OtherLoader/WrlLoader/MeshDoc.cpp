// MeshDoc.cpp : implementation of the CMeshDoc class
//

#include "stdafx.h"
#include "Mesh.h"

#include "MeshDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeshDoc

IMPLEMENT_DYNCREATE(CMeshDoc, CDocument)

BEGIN_MESSAGE_MAP(CMeshDoc, CDocument)
	//{{AFX_MSG_MAP(CMeshDoc)
	ON_COMMAND(ID_GL_ADD_WIREFRAME, OnGlAddWireframe)
	ON_UPDATE_COMMAND_UI(ID_GL_ADD_WIREFRAME, OnUpdateGlAddWireframe)
	ON_COMMAND(ID_GL_SMOOTH, OnGlSmooth)
	ON_UPDATE_COMMAND_UI(ID_GL_SMOOTH, OnUpdateGlSmooth)
	ON_COMMAND(ID_MESH_LOOP, OnMeshLoop)
	ON_UPDATE_COMMAND_UI(ID_MESH_LOOP, OnUpdateMeshLoop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeshDoc construction/destruction

CMeshDoc::CMeshDoc()
{
	m_AddWireframe = 0;
	m_Smooth = 1;
	m_PolygonOffset = -1.0f;
	m_Lighting = 1;
}

CMeshDoc::~CMeshDoc()
{
}

BOOL CMeshDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMeshDoc serialization

void CMeshDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMeshDoc diagnostics

#ifdef _DEBUG
void CMeshDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMeshDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMeshDoc commands

BOOL CMeshDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	// Extension-based checking
	CString file = lpszPathName;

	// Extension
	CString extension = lpszPathName;
	extension = extension.Right(4);
	extension.MakeLower();

	// Path "c:\path\file.wrl" -> c:\path
	CString path = lpszPathName;
	path = path.Left(path.ReverseFind('\\'));

	// CDocument
	SetCurrentDirectory(path);

	TRACE("\nOpening document\n");
	TRACE("File      : %s\n",lpszPathName);
	TRACE("Path      : %s\n",path);
	TRACE("Extension : %s\n",extension);

	// Start reading VRML file
	if(extension == ".wrl")
	{
		TRACE("wrl type\n");
		// Parser VRML 2.0
		CParserVrml parser;
		if(parser.Run((char *)lpszPathName,&m_SceneGraph))
		{
			m_SceneGraph.BuildAdjacency();
			m_SceneGraph.CalculateNormalPerFace();
			m_SceneGraph.CalculateNormalPerVertex();
			return TRUE;
		}
	}

	return TRUE;
}


//////////////////////////////////////////////
//////////////////////////////////////////////
// RENDERING
//////////////////////////////////////////////
//////////////////////////////////////////////

//***********************************************
// RenderScene
//***********************************************
void CMeshDoc::RenderScene()
{
	static BOOL busy = FALSE;

	if(busy)
		return;

	busy = TRUE;

	// Main drawing
	m_SceneGraph.glDraw();

	// Add wireframe (no light, and line mode)
	if(m_AddWireframe)
	{
		// Set state
		::glDisable(GL_LIGHTING);
		::glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		::glEnable(GL_POLYGON_OFFSET_LINE);
		::glPolygonOffset(m_PolygonOffset,-1.0f);

		// Draw again...
		m_SceneGraph.glDraw(TYPE_MESH3D);

		// Restore light and mode
		::glDisable(GL_POLYGON_OFFSET_LINE);
		::glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		::glEnable(GL_LIGHTING);
	}

	::glFlush();
	busy = FALSE;

}


//***********************************************
// Add wireframe
//***********************************************
void CMeshDoc::OnGlAddWireframe() 
{
	m_AddWireframe = !m_AddWireframe;
	UpdateAllViews(NULL);
}

void CMeshDoc::OnUpdateGlAddWireframe(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_AddWireframe);
}

//***********************************************
// Smooth shading
//***********************************************
void CMeshDoc::OnGlSmooth() 
{
	m_Smooth = !m_Smooth;
	if(m_Smooth)
	{
		m_SceneGraph.SetNormalBinding(NORMAL_PER_VERTEX);
		::glShadeModel(GL_SMOOTH);
	}
	else
	{
		m_SceneGraph.SetNormalBinding(NORMAL_PER_FACE);
		::glShadeModel(GL_FLAT);
	}
	UpdateAllViews(NULL);
}

void CMeshDoc::OnUpdateGlSmooth(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Smooth);
}

//***********************************************
// Smooth subdivision
//***********************************************
void CMeshDoc::OnMeshLoop() 
{
	BeginWaitCursor();
	int NbObject = m_SceneGraph.NbObject();
	for(int i=0;i<NbObject;i++)
	{
		CObject3d *pObject3d = m_SceneGraph[i];
	  if(pObject3d->GetType() == TYPE_MESH3D)
		{
			CMesh3d *pMesh  = (CMesh3d *)pObject3d;
			pMesh->SubdivisionLoop();
		}
	}
	UpdateAllViews(NULL);
	EndWaitCursor();
}
void CMeshDoc::OnUpdateMeshLoop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_SceneGraph.NbObject() > 0);
}



BOOL CMeshDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// Extension
	CString extension = lpszPathName;
	extension = extension.Right(4);
	extension.MakeLower();

	// Path "c:\path\file.wrl" -> c:\path
	CString path = lpszPathName;
	path = path.Left(path.ReverseFind('\\'));

	TRACE("\nSaving document\n");
	TRACE("File      : %s\n",lpszPathName);
	TRACE("Path      : %s\n",path);
	TRACE("Extension : %s\n",extension);

	// Start reading VRML file
	if(extension == ".wrl")
	{
		TRACE("wrl type\n");
		m_SceneGraph.SaveFile((char *)lpszPathName);
	}

	return TRUE;
}
