// ASELoaderView.cpp : implementation of the CASELoaderView class
//

#include "stdafx.h"
#include "ASELoader.h"

#include "ASELoaderDoc.h"
#include "ASELoaderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CASELoaderView

IMPLEMENT_DYNCREATE(CASELoaderView, CView)

BEGIN_MESSAGE_MAP(CASELoaderView, CView)
	//{{AFX_MSG_MAP(CASELoaderView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CASELoaderView construction/destruction
UINT m_Texture[MAX_TEXTURES]={5} ;						// This holds the texture info, referenced by an ID

CASELoaderView::CASELoaderView()
{
	// TODO: add construction code here
	m_ViewMode	  =  GL_TRIANGLES;					// We want the default drawing mode to be normal
	m_bLighting     = true;							// Turn lighting on initially
	m_RotateX		  = 0.0f;							// This is the current value at which the model is rotated
	m_RotationSpeed = 0.8f;							// This is the speed that our model rotates.  (-speed rotates left)
//	for(int i=0;i<=MAX_TEXTURES;i++)
//	{
//		m_Texture[i]=0;
//	}


}

CASELoaderView::~CASELoaderView()
{
}

BOOL CASELoaderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CASELoaderView drawing

void CASELoaderView::OnDraw(CDC* pDC)
{
	CASELoaderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	RenderScene();
}

/////////////////////////////////////////////////////////////////////////////
// CASELoaderView printing

BOOL CASELoaderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CASELoaderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CASELoaderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CASELoaderView diagnostics

#ifdef _DEBUG
void CASELoaderView::AssertValid() const
{
	CView::AssertValid();
}

void CASELoaderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CASELoaderDoc* CASELoaderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CASELoaderDoc)));
	return (CASELoaderDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CASELoaderView message handlers

int CASELoaderView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_pDC = new CClientDC(this);
	SetTimer(1, 20, NULL);
	InitializeOpenGL(m_pDC);	
	Init();
	return 0;
}

void CASELoaderView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	::wglMakeCurrent(0,0);
	::wglDeleteContext( m_hRC);
	if (m_hPalette)
	    DeleteObject(m_hPalette);
	if ( m_pDC )
	{
		delete m_pDC;
	}

	for(int i = 0; i < m_3DModel.numOfObjects; i++)
	{
		// Free the faces, normals, vertices, and texture coordinates.
		delete [] m_3DModel.pObject[i].pFaces;
		delete [] m_3DModel.pObject[i].pNormals;
		delete [] m_3DModel.pObject[i].pVerts;
		delete [] m_3DModel.pObject[i].pTexVerts;
	}

	KillTimer(1);		
}

void CASELoaderView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
		if (cy==0)										// Prevent A Divide By Zero error
	{
		cy=1;										// Make the Height Equal One
	}

	glViewport(0,0,cx,cy);						// Make our viewport the whole window
														// We could make the view smaller inside
														// Our window if we wanted too.
														// The glViewport takes (x, y, width, height)
														// This basically means, what our our drawing boundries

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

														// Calculate The Aspect Ratio Of The Window
														// The parameters are:
														// (view angle, aspect ration of the width to the height, 
														//  The closest distance to the camera before it clips, 
				  // FOV		// Ratio				//  The farthest distance before it stops drawing)
	gluPerspective(45.0f,(float)cx/(float)cy,0.1f,150.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();				

}

void CASELoaderView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate(FALSE);	
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  SetLogicalPalette
//////////////////////////////////////////////////////////////////////
void CASELoaderView::SetLogicalPalette(void)
{
    struct
    {
        WORD Version;
        WORD NumberOfEntries;
        PALETTEENTRY aEntries[256];
    } logicalPalette = { 0x300, 256 };

	BYTE reds[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE greens[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE blues[] = {0, 85, 170, 255};

    for (int colorNum=0; colorNum<256; ++colorNum)
    {
        logicalPalette.aEntries[colorNum].peRed =
            reds[colorNum & 0x07];
        logicalPalette.aEntries[colorNum].peGreen =
            greens[(colorNum >> 0x03) & 0x07];
        logicalPalette.aEntries[colorNum].peBlue =
            blues[(colorNum >> 0x06) & 0x03];
        logicalPalette.aEntries[colorNum].peFlags = 0;
    }

    m_hPalette = CreatePalette ((LOGPALETTE*)&logicalPalette);
}


//////////////////////////////////////////////////////////
//							InitializeopenGL
//////////////////////////////////////////////////////////
BOOL CASELoaderView::InitializeOpenGL(CDC* pDC)
{
	m_pDC = pDC;
	SetupPixelFormat();
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	return TRUE;
}

//////////////////////////////////////////////////////////
//							SetupPixelFormat
//////////////////////////////////////////////////////////
BOOL CASELoaderView::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),//Size of yhis pfd
		1,							//versjonsnummer
		PFD_DRAW_TO_WINDOW |		//support window
			PFD_SUPPORT_OPENGL |	//support openGL
			PFD_DOUBLEBUFFER,		//double buffered
		PFD_TYPE_RGBA,				//RGBA typed
		24,							//24bit color depth
		0,0,0,0,0,0,				//colorbits ignored
		0,							//no alpha buffer
		0,							//shift bit ignored
		0,							//no accumulation buffer
		0,0,0,0,					//accum bits ignored
		16,							//16-bit z-buffer
		0,							//no stencil buffer
		0,							//no auxiliary buffer
		PFD_MAIN_PLANE,				//main layer
		0,							//reserved
		0,0,0,						//layer masks ignored
	};
	
	int pixelformat;
	pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);
	if(pfd.dwFlags & PFD_NEED_PALETTE)
		SetLogicalPalette();
	return TRUE;
}



//////////////////////////////////////////////////////////
//							RenderScene
//////////////////////////////////////////////////////////
BOOL CASELoaderView::RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The matrix

//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////

	// Give OpenGL our position,	then view,		then up vector
	gluLookAt(		0, 1.5f, 18,		0, 0.5f, 0,			0, 1, 0);
	
	// We want the model to rotate around the axis so we give it a rotation
	// value, then increase/decrease it. You can rotate right of left with the arrow keys.

	glRotatef(m_RotateX, 0, 1.0f, 0);						// Rotate the object around the Y-Axis
	m_RotateX += m_RotationSpeed;							// Increase the speed of rotation

	// I am going to attempt to explain what is going on below up here as not to clutter the 
	// code below.  We have a model that has a certain amount of objects and textures.  We want 
	// to go through each object in the model, bind it's texture map to it, then render it.
	// To render the current object, we go through all of it's faces (Polygons).  
	// What is a face you ask?  A face is just (in this case) a triangle of the object.
	// For instance, a cube has 12 faces because each side has 2 triangles.
	// You might be thinking.  Well, if there are 12 faces in a cube, that makes
	// 36 vertices that we needed to read in for that object.  Not really true.  Because
	// a lot of the vertices are the same, since they share sides, they only need to save
	// 8 vertices, and ignore the duplicates.  Then, you have an array of all the
	// unique vertices in that object.  No 2 vertices will be the same.  This cuts down
	// on memory.  Then, another array is saved, which is the index numbers for each face,
	// which index in to that array of vertices.  That might sound silly, but it is better
	// than saving tons of duplicate vertices.  The same thing happens for UV coordinates.
	// You don't save duplicate UV coordinates, you just save the unique ones, then an array
	// that index's into them.  This might be confusing, but most 3D files use this format.
	// This loop below will stay the same for most file formats that you load, so all you need
	// to change is the loading code.  You don't need to change this loop (Except for animation).

	// Since we know how many objects our model has, go through each of them.
	for(int i = 0; i < m_3DModel.numOfObjects; i++)
	{
		// Make sure we have valid objects just in case. (size() is in the vector class)
		if(m_3DModel.pObject.size() <= 0) break;

		// Get the current object that we are displaying
		t3DObject *pObject = &m_3DModel.pObject[i];
			
		// Check to see if this object has a texture map, if so bind the texture to it.
		if(pObject->bHasTexture) {

			// Turn on texture mapping and turn off color
			glEnable(GL_TEXTURE_2D);

			// Reset the color to normal again
			glColor3ub(255, 255, 255);

			// Bind the texture map to the object by it's materialID
			glBindTexture(GL_TEXTURE_2D, m_Texture[pObject->materialID]);
		} else {

			// Turn off texture mapping and turn on color
			glDisable(GL_TEXTURE_2D);

			// Reset the color to normal again
			glColor3ub(255, 255, 255);
		}

		// This determines if we are in wireframe or normal mode
		glBegin(m_ViewMode);					// Begin drawing with our selected mode (triangles or lines)

			// Go through all of the faces (polygons) of the object and draw them
			for(int j = 0; j < pObject->numOfFaces; j++)
			{
				// Go through each corner of the triangle and draw it.
				for(int whichVertex = 0; whichVertex < 3; whichVertex++)
				{
					// Get the vertex index for each point of the face
					int vertIndex = pObject->pFaces[j].vertIndex[whichVertex];
			
					// Give OpenGL the normal for this vertex.
					glNormal3f(pObject->pNormals[ vertIndex ].x, pObject->pNormals[ vertIndex ].y, pObject->pNormals[ vertIndex ].z);
				
					// If the object has a texture associated with it, give it a texture coordinate.
					if(pObject->bHasTexture) {

						// Make sure there was a UVW map applied to the object or else it won't have tex coords.
						if(pObject->pTexVerts) {

							// Get the texture coordinate index
							int coordIndex = pObject->pFaces[j].coordIndex[whichVertex];

							// Assign the UV coordinates to the current vertex being rendered
							glTexCoord2f(pObject->pTexVerts[ coordIndex ].x, pObject->pTexVerts[ coordIndex ].y);
						}
					} else {

						// Make sure there is a valid material/color assigned to this object.
						// You should always at least assign a material color to an object, 
						// but just in case we want to check the size of the material list.
						// if the size is at least one, and the material ID != -1,
						// then we have a valid material.
						if(m_3DModel.pMaterials.size() && pObject->materialID >= 0) 
						{
							// Get and set the color that the object is, since it must not have a texture
							float *pColor = m_3DModel.pMaterials[pObject->materialID].fColor;

							// Assign the current color to this model
							glColor3f(pColor[0], pColor[1], pColor[2]);
						}
					}

					// Pass in the current vertex of the object (Corner of current face)
					glVertex3f(pObject->pVerts[ vertIndex ].x, pObject->pVerts[ vertIndex ].y, pObject->pVerts[ vertIndex ].z);
				}
			}

		glEnd();								// End the drawing
	}


	::SwapBuffers(m_pDC->GetSafeHdc());
	return TRUE;
}

void CASELoaderView::Init(GLvoid)
{
//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////
	glEnable(GL_TEXTURE_2D);							// Enable texture mapping
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

	// First we need to actually load the .ASE file.  We just pass in an address to
	// our t3DModel structure and the file name string we want to load ("Statue.Ase").

	m_LoadASE.ImportASE(&m_3DModel, "statue.ase");			// Load our .Ase file into our model structure

	// Depending on how many textures we found, load each one (Assuming .BMP)
	// If you want to load other files than bitmaps, you will need to adjust CreateTexture().
	// Below, we go through all of the materials and check if they have a texture map to load.
	// Otherwise, the material just holds the color information and we don't need to load a texture.

	// Go through all the materials
	for(int i = 0; i < m_3DModel.numOfMaterials; i++)
	{
		// Check to see if there is a file name to load in this material
		if(strlen(m_3DModel.pMaterials[i].strFile) > 0)
		{
			// Use the name of the texture file to load the bitmap, with a texture ID (i).
			// We pass in our global texture arrow, the name of the texture, and an ID to reference it.	
			CreateTexture(m_Texture, m_3DModel.pMaterials[i].strFile, i);			
		}

		// Set the texture ID for this material
		m_3DModel.pMaterials[i].texureId = i;
	}

	// Here, we turn on a lighting and enable lighting.  We don't need to
	// set anything else for lighting because we will just take the defaults.
	// We also want color, so we turn that on

	glEnable(GL_LIGHT0);							// Turn on a light with defaults set
	glEnable(GL_LIGHTING);							// Turn on lighting
	glEnable(GL_COLOR_MATERIAL);					// Allow color

//////////// *** NEW *** ////////// *** NEW *** ///////////// *** NEW *** ////////////////////


}


///////////////////////////////// CREATE TEXTURE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This creates a texture in OpenGL that we can texture map
/////
///////////////////////////////// CREATE TEXTURE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CASELoaderView::CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID)
{
	AUX_RGBImageRec *pBitmap = NULL;
	
	if(!strFileName)									// Return from the function if no file name was passed in
		return;

	pBitmap = auxDIBImageLoad(strFileName);				// Load the bitmap and store the data
	
	if(pBitmap == NULL)									// If we can't load the file, quit!
		exit(0);

	// Generate a texture with the associative texture ID stored in the array
	glGenTextures(1, &textureArray[textureID]);

	// This sets the alignment requirements for the start of each pixel row in memory.
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	// Bind the texture to the texture arrays index and init the texture
	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);

	// Build Mipmaps (builds different versions of the picture for distances - looks better)
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pBitmap->sizeX, pBitmap->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pBitmap->data);

	// Lastly, we need to tell OpenGL the quality of our texture map.  GL_LINEAR is the smoothest.
	// GL_NEAREST is faster than GL_LINEAR, but looks blochy and pixelated.  Good for slower computers though.
	// Read more about the MIN and MAG filters at the bottom of main.cpp
		
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	// Now we need to free the bitmap data that we loaded since openGL stored it as a texture

	if (pBitmap)										// If we loaded the bitmap
	{
		if (pBitmap->data)								// If there is texture data
		{
			free(pBitmap->data);						// Free the texture data, we don't need it anymore
		}

		free(pBitmap);									// Free the bitmap structure
	}
}
