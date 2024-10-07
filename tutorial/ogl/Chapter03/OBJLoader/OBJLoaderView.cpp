// OBJLoaderView.cpp : implementation of the COBJLoaderView class
//

#include "stdafx.h"
#include "OBJLoader.h"

#include "OBJLoaderDoc.h"
#include "OBJLoaderView.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FRONT_PLANE 2.0
ModelContext *model;

int drawSetting = POLYGONS;

//��Դ�ĸ��ֲ���ֵ
GLfloat light1[4] = {1.0f, 1.0f, 0.9f, 1.0f};
GLfloat pos1[4] = { 5.0f,  7.0f, 1.0f, 0.0f};
GLfloat ambient[3] = {0.2f, 0.2f, 0.2f};
GLfloat diffuse[4] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat specular[3] = {1.0f, 1.0f, 1.0f};

/////////////////////////////////////////////////////////////////////////////
// COBJLoaderView

IMPLEMENT_DYNCREATE(COBJLoaderView, CView)

BEGIN_MESSAGE_MAP(COBJLoaderView, CView)
	//{{AFX_MSG_MAP(COBJLoaderView)
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
// COBJLoaderView construction/destruction

COBJLoaderView::COBJLoaderView()
{
	// TODO: add construction code here
}

COBJLoaderView::~COBJLoaderView()
{
}

BOOL COBJLoaderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
////////////////////////////////////////////////////////////////
//���ô�������
	cs.style |=WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
////////////////////////////////////////////////////////////////
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COBJLoaderView drawing

void COBJLoaderView::OnDraw(CDC* pDC)
{
	COBJLoaderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	RenderScene();	//��Ⱦ����
//////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////
// COBJLoaderView printing

BOOL COBJLoaderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COBJLoaderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COBJLoaderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COBJLoaderView diagnostics

#ifdef _DEBUG
void COBJLoaderView::AssertValid() const
{
	CView::AssertValid();
}

void COBJLoaderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COBJLoaderDoc* COBJLoaderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COBJLoaderDoc)));
	return (COBJLoaderDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COBJLoaderView message handlers

int COBJLoaderView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
//////////////////////////////////////////////////////////////////
//��ʼ��OpenGL�����ö�ʱ��
	m_pDC = new CClientDC(this);
	SetTimer(1, 20, NULL);
	InitializeOpenGL(m_pDC);
//////////////////////////////////////////////////////////////////
	Init();
	return 0;
}

void COBJLoaderView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//ɾ����ɫ�����Ⱦ�����ġ���ʱ��
	::wglMakeCurrent(0,0);
	::wglDeleteContext( m_hRC);
	if (m_hPalette)
	    DeleteObject(m_hPalette);
	if ( m_pDC )
	{
		delete m_pDC;
	}
	KillTimer(1);		
/////////////////////////////////////////////////////////////////
	delete model;
}

void COBJLoaderView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	
}

void COBJLoaderView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/////////////////////////////////////////////////////////////////
//��Ӷ�ʱ����Ӧ�����ͳ������º���
	Invalidate(FALSE);	
/////////////////////////////////////////////////////////////////
	
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  �����߼���ɫ��
//////////////////////////////////////////////////////////////////////
void COBJLoaderView::SetLogicalPalette(void)
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
//						��ʼ��openGL����
//////////////////////////////////////////////////////////
BOOL COBJLoaderView::InitializeOpenGL(CDC* pDC)
{
	m_pDC = pDC;
	SetupPixelFormat();
	//���ɻ���������
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//�õ�ǰ����������
	::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	return TRUE;
}

//////////////////////////////////////////////////////////
//						�������ظ�ʽ
//////////////////////////////////////////////////////////
BOOL COBJLoaderView::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С 
	    1,                                // �汾�� 
	    PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ 
	    PFD_SUPPORT_OPENGL |              // ֧�� OpenGL 
	    PFD_DOUBLEBUFFER,                 // ˫����ģʽ 
	    PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ 
	    24,                               // 24 λ��ɫ��� 
	    0, 0, 0, 0, 0, 0,                 // ������ɫλ 
	    0,                                // û�з�͸���Ȼ��� 
	    0,                                // ������λλ 
	    0,                                // ���ۼӻ��� 
	    0, 0, 0, 0,                       // �����ۼ�λ 
	    32,                               // 32 λ��Ȼ���     
	    0,                                // ��ģ�建�� 
	    0,                                // �޸������� 
	    PFD_MAIN_PLANE,                   // ���� 
	    0,                                // ���� 
	    0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ 
	}; 	
	int pixelformat;
	pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);//ѡ�����ظ�ʽ
	::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);	//�������ظ�ʽ
	if(pfd.dwFlags & PFD_NEED_PALETTE)
		SetLogicalPalette();	//�����߼���ɫ��
	return TRUE;
}



//////////////////////////////////////////////////////////
//						������������Ⱦ
//////////////////////////////////////////////////////////
BOOL COBJLoaderView::RenderScene() 
{

	GLdouble rotAxis[3] = { 1.0, 0.0, 0.0 };
	GLdouble rotAngle = -90.0;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //�Ӷ���õ�λ�ù۲�ͼ��
    gluLookAt(0.0, 0.1, 300.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, -1.0);

    setView();
	glDrawBuffer(GL_BACK);
	GLbitfield clearBits = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
    glClear(clearBits);

    model->pointerMotion = 0;			

	register int i, j;
    register int nextIndex;	
    register int currColor;
    GLfloat lightpos[3];               

	GLfloat black4f[] = { 0.0f, 0.0f, 0.0f, 0.0f };


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glScaled(model->scaleObj, model->scaleObj, model->scaleObj);
    if (model->needToUpdateViewMat) 
	{

		glPushMatrix();
		glLoadIdentity();

	//	glRotated(model->rotX * 0.2, 0.0, 0.0, -1.0);
		glMultMatrixd(model->rotMat);
		glGetDoublev(GL_MODELVIEW_MATRIX, model->rotMat);
		glPopMatrix();
		model->needToUpdateViewMat = 0;
    }
    glMultMatrixd(model->rotMat);

	lightpos[0] = (pos1[0] * model->rotMat[0]) + (pos1[2] * model->rotMat[1]);
    lightpos[1] = pos1[1];
    lightpos[2] = (pos1[0] * model->rotMat[4]) + (pos1[2] * model->rotMat[5]);

 //   glRotated(rotAngle, rotAxis[0], rotAxis[1], rotAxis[2]);

	static GLdouble rat=0.0;
	rat++;
	rat=(int)rat%360;

//	glRotated(rat, 0.0, 1.0, 0.0);

//	glRotated(-180, 1.0, 0.0, 0.0);
//	glRotated(-40, 0.0, 0.0, 1.0);

    //���ƶ���
    i = 0;
    j = 0;
    nextIndex = model->colorList[j].index;
	if(	m_objloaded )
	{
		if (drawSetting < LINE_INDEPENDENT) 
		{
			if (model->haveNormals)
			{
				do 
				{
					if (i == nextIndex)
					{
						setColor(&model->colorList[j].ra, &model->colorList[j].rd,
							&model->colorList[j].rs, model->colorList[j].spec, 0);
						j++;
						nextIndex = model->colorList[j].index;
					}
					if (drawSetting <= LINE_POLYGON)
						glBegin(GL_POLYGON);
					else
						glBegin(GL_LINE_LOOP);
					glNormal3fv(&model->vertexList[i].nx);
					glVertex3fv(&model->vertexList[i++].x);
					while (model->vertexList[i].draw) 
					{
						glNormal3fv(&model->vertexList[i].nx);
						glVertex3fv(&model->vertexList[i++].x);
					}
					glEnd();
				} while (i < model->vertexCount);
			} 
			else do
			{
				if (i == nextIndex) 
				{
					setColor(&model->colorList[j].ra, &model->colorList[j].rd,
						&model->colorList[j].rs, model->colorList[j].spec, 0);
					j++;
					nextIndex = model->colorList[j].index;
				}
				if (drawSetting <= LINE_POLYGON)
					glBegin(GL_POLYGON);
				else
					glBegin(GL_LINE_LOOP);
				glVertex3fv(&model->vertexList[i++].x);
				while (model->vertexList[i].draw) 
				{
					glVertex3fv(&model->vertexList[i++].x);
				}
				glEnd();
			}
			while (i < model->vertexCount);
		}
		else
		{
			currColor = -1;
			if (drawSetting == LINE_INDEPENDENT) 
			{
				glBegin(GL_LINES);	
				do
				{
					if (model->lineList[i].colorIndex != currColor) 
					{
						currColor = model->lineList[i].colorIndex;
						setColor(&model->colorList[currColor].ra,
							&model->colorList[currColor].rd,
							&model->colorList[currColor].rs,
							model->colorList[currColor].spec, 0);
					}
					glVertex3fv(&model->lineList[i++].x);
					glVertex3fv(&model->lineList[i++].x);
				}
				while (i < model->lineCount);
				glEnd();
			}
			if (drawSetting == LINE_STRIPS)
			do
			{
				glBegin(GL_LINE_STRIP);
				if (model->lineStripList[i].colorIndex != currColor) 
				{
					currColor = model->lineStripList[i].colorIndex;
					setColor(&model->colorList[currColor].ra,
						&model->colorList[currColor].rd,
						&model->colorList[currColor].rs,
						model->colorList[currColor].spec, 0);
				}
				glVertex3fv(&model->lineStripList[i++].x);
				while (model->lineStripList[i].draw) 
				{
					glVertex3fv(&model->lineStripList[i++].x);
				}
				glEnd();
			}
			while (i < model->lineStripCount);
		} 
	}
	::SwapBuffers(m_pDC->GetSafeHdc());		//����������
	return TRUE;
}

void COBJLoaderView::setColor(const GLfloat *ambient,
    const GLfloat *diffuse,
    const GLfloat *specular,
    GLfloat shininess,
    GLboolean stereo)
{
    GLfloat c;				
    GLfloat ca[4];

    if (!stereo) {
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	glColor4fv(diffuse);
    }
    else {
	c = 0.27 * ambient[0] + 0.59 * ambient[1] + 0.14 * ambient[2];
	ca[0] = ca[1] = ca[2] = c;
	glMaterialfv(GL_FRONT, GL_AMBIENT, ca);

	ca[0] = ca[1] = ca[2] = c;
	ca[3] = diffuse[3];
	c = 0.27 * diffuse[0] + 0.59 * diffuse[1] + 0.14 * diffuse[2];
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ca);

	glColor4f(c, c, c, diffuse[3]);

	ca[0] = ca[1] = ca[2] = c;
	c = 0.27 * specular[0] + 0.59 * specular[1] + 0.14 * specular[2];
	glMaterialfv(GL_FRONT, GL_SPECULAR, ca);

	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }

} /* End of setColor */

void COBJLoaderView::Init(GLvoid)
{
	
	m_objloaded = false;
	//����ģ�͵Ĵ洢�ռ�
    model = (ModelContext *)calloc(1, sizeof(ModelContext));

    if (model == NULL) 
	{
		MessageBox("Not enough memory count be allocated for model data","����",MB_OK);
		exit (-1);
    }
    //��ʼ��ģ������
    model->scaleObj = 5.0;		
    model->needToUpdateViewMat = 0;
    model->pointerMotion = 0;
    model->windowWidth = 640;
    model->windowHeight = 480;
    model->minimumScale = MINIMUM_SCALE;
    model->triangleFlag = 0;		

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetDoublev(GL_MODELVIEW_MATRIX, model->rotMat);	/* Initial rotation */

    glClearColor(0.2f, 0.4f, 0.7f, 1.0f);

    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_BLEND);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    setAlternateLights(1);



}


////////////////////////////////////////////////////////////////////////////////////
//���ú��ʵĹ�Դ
void COBJLoaderView::setAlternateLights(int lights)
{
    if (lights == 0) {
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	return;
    }
    else  {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_LIGHTING);

    glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light1);
	glLightfv(GL_LIGHT0, GL_POSITION, pos1);

	setColor(ambient, diffuse, specular, 50.0, 0);
	glPopMatrix();
    }
} 



////////////////////////////////////////////////////////////////////////////////////
//���ú��ʵ��ӵ�
void COBJLoaderView::setView(void)
{
    GLdouble distanceAdjust;		
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    distanceAdjust = FRONT_PLANE / EYE_BACK; 
    distanceAdjust /= PIXELS_PER_INCH / FRONT_PLANE;

    glFrustum(-model->windowWidth * distanceAdjust, model->windowWidth * distanceAdjust,
	-model->windowHeight * distanceAdjust, model->windowHeight * distanceAdjust,
	FRONT_PLANE, 1000.0);		
} 

BOOL COBJLoaderView::OpenFile(LPCTSTR lpszPathName)
{
	char* file = new char[strlen(lpszPathName)];
	strcpy(file, lpszPathName);	
	m_objRead->readObjData(file);

	m_objloaded = TRUE;
	return true;

}
