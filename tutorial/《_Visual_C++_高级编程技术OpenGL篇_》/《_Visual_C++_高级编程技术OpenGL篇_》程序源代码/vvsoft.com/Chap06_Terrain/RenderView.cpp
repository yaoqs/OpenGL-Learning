// RenderView.cpp
#include "stdafx.h"
#include "Tool.h"
#include <math.h> 

#include "ToolDoc.h"
#include "RenderView.h"
#include "glm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WIDTH 32 // 纹理文件的宽度
// 地形网格格点数，用来控制地形矩阵的下标
#define MAP 512

// This is the holding space for the landscape.
GLfloat y[MAP+1][MAP+1];
char object[MAP+1][MAP+1];

typedef struct color {
  GLfloat r, g, b;
} color;

// 地形网格点颜色
color c[MAP+1][MAP+1];

static GLubyte texImg[WIDTH][WIDTH][4];
static GLuint texName;

unsigned short int comp = 32; // Scale modifier.

unsigned short int temp, texture_mapping = FALSE,
                   land_fogging = TRUE, flat_shading = TRUE;

// 初始视点位置和视角
static GLfloat patriot_posx = 0, patriot_posy = 0, patriot_posz = 0;
static GLfloat lookx=0, looky=0, lookz=20;
static GLfloat speed = 0;

// The following code for mouse routines was contributed.
// These are used for the motion function.
#define FORWARD 1
#define UP 2
#define TURNLEFT 3
#define STRAFELEFT 4
#define LOOKUP 5

#define PI 3.14159f
#define H 0.4f
#define DT 2
#define VN 20
#define CN 16
#define TAILL 4
#define LIST  6
#define ADDL 0.3f
#define ADDH 0.1f
#define MISSLE 2

// Mouse position and button.
int oldmx = 0, oldmy = 0, mb;
int srnd;
float L = 10.0f,tmp[CN][2],red_green[6][CN],tail[6][CN];
float vetxm[LIST][VN+1][CN][7];
double ttt;

float vertex[213][3], normals[286][3];
int faces[187][2][41];

int loop1, counter = 0, flag=0;


// CRenderView
IMPLEMENT_DYNCREATE(CRenderView, CView)

BEGIN_MESSAGE_MAP(CRenderView, CView)
//{{AFX_MSG_MAP(CRenderView)
ON_WM_DESTROY()
ON_WM_SIZE()
ON_WM_PAINT()
ON_WM_TIMER()
ON_WM_CREATE()
//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()


// CRenderView construction/destruction
CRenderView::CRenderView()
{
  // OpenGL
  m_hGLContext = NULL;
  m_GLPixelIndex = 0;
}

CRenderView::~CRenderView()
{
	glmDelete(plane);
	glmDelete(patriot);
}

void CRenderView::InitGeometry(void)
{
  GLfloat fogColor[4] = {0.75, 0.75, 1.0, 1.0};
  patriot = glmReadOBJ("patriot.obj");
  plane = glmReadOBJ("plane.obj");
  glmUnitize(plane);
  glmScale(plane, 8.0f);
  patriot_posx = 3000.0;
  patriot_posy = 256.0;
  patriot_posz = 8500.0;

  lookx = 15.0;
  looky = -8.0; 
  lookz = -18.00;

//  loop=-5.0;
  Shoot = FALSE;
  speed = 0;

  srand(224);
  GenScean();
  GenFire();
  MakeFireList();
  srand((unsigned)time(NULL));
  MakeTexture();
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(1, &texName);
  glBindTexture(GL_TEXTURE_2D, texName);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, WIDTH, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImg);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, fogColor);
  glFogf(GL_FOG_DENSITY, 0.8f);
  glFogf(GL_FOG_START, 400.0f);
  glFogf(GL_FOG_END, 500.0f);  
  glEnable(GL_TEXTURE_2D);
  glClearColor(0.75f, 0.75f, 1.0f, 1.0f);
}

BOOL CRenderView::PreCreateWindow(CREATESTRUCT& cs)
{
  return CView::PreCreateWindow(cs);
}

// CRenderView drawing
void CRenderView::OnDraw(CDC* pDC)
{
}

BOOL CRenderView::OnPreparePrinting(CPrintInfo* pInfo)
{
  return DoPreparePrinting(pInfo);
}

void CRenderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CRenderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

// CRenderView diagnostics
#ifdef _DEBUG
void CRenderView::AssertValid() const
{
  CView::AssertValid();
}

void CRenderView::Dump(CDumpContext& dc) const
{
  CView::Dump(dc);
}

CToolDoc* CRenderView::GetDocument() // non-debug version is inline
{
  if (m_pDocument){
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
    return (CToolDoc*)m_pDocument;
  }
  else return NULL;
}
#endif //_DEBUG

// Create OpenGL rendering context 
int CRenderView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CView::OnCreate(lpCreateStruct) == -1)
    return -1;
  
  HWND hWnd = GetSafeHwnd();
  HDC hDC = ::GetDC(hWnd);

  if(SetWindowPixelFormat(hDC)==FALSE)
    return 0;
  
  if(CreateViewGLContext(hDC)==FALSE)
    return 0;
  
  // Default mode
  glPolygonMode(GL_FRONT,GL_FILL);
  glPolygonMode(GL_BACK,GL_FILL);
  glShadeModel(GL_FLAT);
  
  InitGeometry();
  SetTimer(1,50,NULL);
  return 0;
}

BOOL CRenderView::SetWindowPixelFormat(HDC hDC)
{
  PIXELFORMATDESCRIPTOR pixelDesc;
  
  pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pixelDesc.nVersion = 1;
  
  pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
    PFD_DOUBLEBUFFER | PFD_STEREO_DONTCARE;
  
  pixelDesc.iPixelType = PFD_TYPE_RGBA;
  pixelDesc.cColorBits = 32;
  pixelDesc.cRedBits = 8;
  pixelDesc.cRedShift = 16;
  pixelDesc.cGreenBits = 8;
  pixelDesc.cGreenShift = 8;
  pixelDesc.cBlueBits = 8;
  pixelDesc.cBlueShift = 0;
  pixelDesc.cAlphaBits = 0;
  pixelDesc.cAlphaShift = 0;
  pixelDesc.cAccumBits = 64;
  pixelDesc.cAccumRedBits = 16;
  pixelDesc.cAccumGreenBits = 16;
  pixelDesc.cAccumBlueBits = 16;
  pixelDesc.cAccumAlphaBits = 0;
  pixelDesc.cDepthBits = 32;
  pixelDesc.cStencilBits = 8;
  pixelDesc.cAuxBuffers = 0;
  pixelDesc.iLayerType = PFD_MAIN_PLANE;
  pixelDesc.bReserved = 0;
  pixelDesc.dwLayerMask = 0;
  pixelDesc.dwVisibleMask = 0;
  pixelDesc.dwDamageMask = 0;
  
  m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);
  if(m_GLPixelIndex == 0) // Choose default
  {
    m_GLPixelIndex = 1;
    if(DescribePixelFormat(hDC,m_GLPixelIndex,
      sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
      return FALSE;
  }
  
  if(!SetPixelFormat(hDC,m_GLPixelIndex,&pixelDesc))
    return FALSE;
  
  return TRUE;
}

// Create an OpenGL rendering context
BOOL CRenderView::CreateViewGLContext(HDC hDC)
{
  m_hGLContext = wglCreateContext(hDC);
  
  if(m_hGLContext==NULL)
    return FALSE;
  
  if(wglMakeCurrent(hDC,m_hGLContext)==FALSE)
    return FALSE;
  
  return TRUE;
}

// Cleanup every OpenGL rendering context
void CRenderView::OnDestroy() 
{
  if(wglGetCurrentContext() != NULL)
    wglMakeCurrent(NULL,NULL);
  
  if(m_hGLContext != NULL)
  {
    wglDeleteContext(m_hGLContext);
    m_hGLContext = NULL;
  }
  CView::OnDestroy();
}

void CRenderView::OnSize(UINT nType, int cx, int cy) 
{
  CView::OnSize(nType, cx, cy);
  
  // Set OpenGL perspective, viewport and mode
  CSize size(cx,cy);
  double aspect;
  aspect = (cy == 0) ? (double)size.cx : (double)size.cx/(double)size.cy;

  glViewport(0, 0, (GLsizei) cx, (GLsizei) cy);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat) cx/(GLfloat) cy, 1.0f, 5000.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void CRenderView::OnPaint() 
{
  // Device context for painting  
  CPaintDC dc(this); 
  
  // Useful in singledoc templates
  HWND hWnd = GetSafeHwnd();
  HDC hDC = ::GetDC(hWnd);
  wglMakeCurrent(hDC,m_hGLContext);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.75f, 0.75f, 1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  CheckHeight();
  gluLookAt(patriot_posx, patriot_posy, patriot_posz,patriot_posx+lookx, patriot_posy+looky, patriot_posz+lookz, 0.0f,1.0f,0.0f);
  RenderTerrain();
  TrackObj();
  glFlush();
  SwapBuffers(hDC);
}

void CRenderView::RenderTerrain()
{
  int x, z, position_x, position_z;
  GLfloat x1, x2, z1, z2;

  glPushMatrix();  
  position_x = (int)patriot_posx/comp;
  position_z = (int)patriot_posz/comp;
  for(x=position_x-16; x<position_x+17; x++){
    for(z=position_z-16; z<position_z+17; z++) {
      if(x>0 && x<MAP && z>0 && z<MAP) {
        x1 = (float)x*comp;
        x2 = (float)x*comp + comp;
        z1 = (float)z*comp;
        z2 = (float)z*comp + comp;
		// 绘制地形时必须关闭光照，因为这里没有定义法向量
		glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        glColor3f(c[x][z].r, c[x][z].g, c[x][z].b);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x1, y[x][z], z1);
        glColor3f(c[x+1][z].r, c[x+1][z].g, c[x+1][z].b);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x2, y[x+1][z], z1);
        glColor3f(c[x][z+1].r, c[x][z+1].g, c[x][z+1].b);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x1, y[x][z+1], z2);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(c[x+1][z+1].r, c[x+1][z+1].g, c[x+1][z+1].b);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x2, y[x+1][z+1], z2);
        glColor3f(c[x][z+1].r, c[x][z+1].g, c[x][z+1].b);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x1, y[x][z+1], z2);
        glColor3f(c[x+1][z].r, c[x+1][z].g, c[x+1][z].b);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x2, y[x+1][z], z1);
		glEnd();
        if(object[x][z]=='t')
          DrawTree(x, z);
      }
    }  
  }
  glPopMatrix();
}

void CRenderView::GenScean(void)
{
  int x, z;
  int r = 256; // 随机数最大值
  float gradient, shadow = 0.5, max = 0;
  FILE *fp;

   if((fp=fopen("airport.asc.","rb"))==NULL) return;
		float XCorner, YCorner;
		int OridtmDX, OridtmDY;
		float CellSize;
        fread(&XCorner,sizeof(float),1,fp);
		fread(&YCorner,sizeof(float),1,fp);
		fread(&OridtmDX,sizeof(int),1,fp);
		fread(&OridtmDY,sizeof(int),1,fp);
		fread(&CellSize,sizeof(float),1,fp);
   
        fread(y,sizeof(float),MAP*MAP,fp);
	    for (x = 0; x < MAP; x++ )
	 	    for ( z = 0; z < MAP; z++)
			    y[x][z] /=2.0;
        fclose(fp);
		// 在地形中随机生成一些树木
		for(x=0; x<MAP; x++){
			for(z=0; z<MAP; z++) {
				if(rand()%13==0 && y[x][z]>0)
					object[x][z] = 't';
				else
					object[x][z] = 'n';
			}
		}
 
		for(x=0; x<=MAP; x++){
			for(z=0; z<=MAP; z++) {
				gradient = ((GLfloat) (y[x][z]-y[x+1][z])) / 100.0f;
				if(y[x][z]>64) {
					if((y[x][z]-y[x][z+1])<8 && (y[x][z]-y[x][z+1])>-8 && (y[x][z]-y[x+1][z])<8 && (y[x][z]-y[x+1][z])>-8) {
					c[x][z].g = gradient + 0.75f;
					c[x][z].r = c[x][z].g;
					c[x][z].b = c[x][z].g;
				}
				else {
					c[x][z].r = gradient + 0.75f;
					c[x][z].g = c[x][z].r*0.8f;
					c[x][z].b = c[x][z].r*0.5f;
				}
			}  else
			if(y[x][z]>0){
				c[x][z].g = gradient + 0.75f;
				c[x][z].r = c[x][z].g * 0.6f;
				c[x][z].b = 0.0f;
			}
            else {
				c[x][z].r = gradient + 1.0f;
				c[x][z].g = c[x][z].r * 0.75f;
				c[x][z].b = c[x][z].r * 0.5f;
			}
		}
	}
}

void CRenderView::MakeTexture(void) {
  int i, j;
  FILE *fp;
  unsigned char *image;
  int rc;

  fp = fopen("res\\texture.bmp","rb");
  if(!fp) return;
  fseek(fp,54,SEEK_SET);
  image = (unsigned char *)malloc(WIDTH*WIDTH*3);
  rc=fread(image,sizeof(unsigned char),WIDTH*WIDTH*3,fp);
  fclose(fp);
  for(i=0; i<WIDTH; i++) {
     for(j=0; j<WIDTH; j++) {
      texImg[i][j][0] = (GLubyte) *(image+i*WIDTH*3+j*3);
      texImg[i][j][1] = (GLubyte) *(image+i*WIDTH*3+j*3+1);
      texImg[i][j][2] = (GLubyte) *(image+i*WIDTH*3+j*3+2);
      texImg[i][j][3] = (GLubyte) 255;
     }
   }
}

void CRenderView::CheckHeight(void) {

  float x0, x1, lx, lz, x, z, midpoint;
  int fx, fz;

  x = (patriot_posx/(comp*1.0f));
  z = (patriot_posz/(comp*1.0f));
  fx = (int)(x);
  fz = (int)(z);
  lx = x - fx;
  lz = z - fz;
  x0 = y[fx][fz] + (y[fx][fz+1] - y[fx][fz])*lz;
  x1 = y[fx+1][fz] + (y[fx+1][fz+1] - y[fx+1][fz])*lz;
  midpoint = x0 + (x1 - x0)*lx;
  patriot_posy = midpoint + 50.0f;
}

void CRenderView::DrawTree(int x, int z)
{

  int x1, y1, z1;
    
    y1 = (int)y[x][z];
    x1 = (int)x * comp;
    z1 = (int)z * comp;

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_POLYGON);
  glColor3f(0.6f, 0.4f, 0.0f);
  glVertex3f((float)x1-1, (float)y1+5, (float)z1);
  glVertex3f((float)x1+1, (float)y1+5, (float)z1);
  glVertex3f((float)x1+1, (float)y1, (float)z1);
  glVertex3f((float)x1-1, (float)y1, (float)z1);
  glEnd();
  
  glBegin(GL_POLYGON);
  glVertex3f((float)x1, (float)y1+5, (float)z1-2);
  glVertex3f((float)x1, (float)y1+5, (float)z1+2);
  glVertex3f((float)x1, (float)y1, (float)z1+2);
  glVertex3f((float)x1, (float)y1, (float)z1-2);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.35f, 0.7f, 0.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f((float)x1-10, (float)y1+5, (float)z1);
  glTexCoord2f(0.5f, 1.0f);
  glVertex3f((float)x1, (float)y1+25, (float)z1);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f((float)x1+10, (float)y1+5, (float)z1);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0.4f, 0.8f, 0.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f((float)x1, (float)y1+5, (float)z1-10);
  glTexCoord2f(0.5f, 1.0f);
  glVertex3f((float)x1, (float)y1+25, (float)z1);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f((float)x1, (float)y1+5, (float)z1+10);
  glEnd();
}

// Function that moves the eye or turns the angle of sight.
// Updates scene if update != 0.
void CRenderView::MoveEye(int type, GLfloat amount, int update)
{
  GLfloat a;
  
  switch(type){
    case FORWARD:
      patriot_posx += lookx*amount*2;
      patriot_posz += lookz*amount*2;
      break;
    case TURNLEFT:
      lookx = lookx*(float)cos(amount) + lookz*(float)sin(amount);
      lookz = lookz*(float)cos(amount) - lookx*(float)sin(amount);
      // 因为浮点数计算存在误差，因此有时lookx^2 + lookz^2 != 1，以下进行校正
      a = 1.0f / (float)sqrt(lookx*lookx + lookz*lookz);
      lookx *= a;
      lookz *= a;
      break;
    case STRAFELEFT:
      patriot_posx += lookz * amount;
      patriot_posz -= lookx * amount;
      break;
    case UP:
      patriot_posy += amount;
      break;
    case LOOKUP:
      looky += amount;
      break;
  }
  CheckHeight();
  glPushMatrix();
  glPopMatrix();
  if (update){
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
	glBegin(GL_POLYGON);
	glVertex3f(patriot_posx+lookx, patriot_posy+looky, patriot_posz+lookz);
    glVertex3f(patriot_posx+lookx, patriot_posy+looky+10, patriot_posz+lookz);
	glVertex3f(patriot_posx+lookx, patriot_posy+looky-10, patriot_posz+lookz);
	glEnd();
  }
}

void CRenderView::DrawPatriot(void)
{
	GLfloat no_mat[] = { 0.05f, 0.05f, 0.05f, 1.0f };
	GLfloat mat_ambient[] = { 0.35f, 0.35f, 0.45f, 1.0f };
	GLfloat mat_diffuse[] = { 0.6f, 0.6f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat no_shininess[] = { 0.0f };
	GLfloat low_shininess[] = { 100.0f };
	GLfloat high_shininess[] = { 10.0f };
	GLfloat mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
    GLfloat ambient[4] = { 0.2f, 0.2f, 0.3f, 1.0f };
    GLfloat diffuse[4] = { 0.8f, 0.8f, 1.0f, 1.0f };
    GLfloat specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat position[4] = { 10.0f,10.0f,10.0f, 1.0f };
   
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR,specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);

	glMaterialfv(GL_FRONT, GL_AMBIENT,  mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION,  no_mat);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glmDraw(patriot, GLM_SMOOTH|GLM_MATERIAL);
	glDisable(GL_LIGHTING);
}

void CRenderView::DrawPlane(void)
{
	GLfloat no_mat[] = { 0.05f, 0.05f, 0.05f, 1.0f };
	GLfloat mat_ambient[] = { 0.35f, 0.35f, 0.45f, 1.0f };
	GLfloat mat_diffuse[] = { 0.6f, 0.6f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat low_shininess[] = { 100.0f };
	GLfloat mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
    GLfloat ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat position[4] = { 0.0f,0.0f,10.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR,specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT, GL_AMBIENT,  mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION,  no_mat);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glmDraw(plane, GLM_SMOOTH);
	glDisable(GL_LIGHTING);
}

void CRenderView::TrackObj(void)
{
    float ta=-90.0f, thita=ta*PI/180.0f, distance=20.0f;
    static GLuint FireList = 0;
	CPaintDC dc(this); 
	
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);
	wglMakeCurrent(hDC,m_hGLContext);

    glPushMatrix();
	glLoadIdentity();
	gluLookAt(patriot_posx, patriot_posy, patriot_posz,patriot_posx+lookx, patriot_posy+looky, patriot_posz+lookz, 0.0f,1.0f,0.0f);
    glTranslatef(patriot_posx+lookx, patriot_posy+looky, patriot_posz+lookz);
	if (Shoot){
		glRotatef(-90,1,0,0);
		glRotatef(-30,0,1,0);
		glTranslatef(0, 5, 0);
		DrawPatriot();
		glCallList(FireList+1);
		FireList = (FireList+1) % LIST;
	}	else {
		glRotatef(-90,1,0,0);
		glRotatef(-30,0,0,1);
		DrawPlane();
	}
	if (L>12 || L<10) flag=1-flag;
	if (flag) L-=0.1f; else L+=0.1f;
	counter++;
	patriot_posx=patriot_posx-(float)cos(thita)*14.0f;
	patriot_posz=patriot_posz+(float)sin(thita)*14.0f;
	CheckHeight();
	glDisable(GL_BLEND);
    glPopMatrix();
}

void CRenderView::GenFire()
{
	float r,dt,dy,t,y;
	int k, l, ff, i, j, list;

	for (list=0; list<LIST; list++){
		srnd=0;
		for (i=0;i<CN;i++){
			tmp[i][0]=(float)(cos(i*2.0f*PI/CN));
			tmp[i][1]=(float)(sin(i*2.0f*PI/CN));
		}
		for (j=0; j<6; j++)
			for (k=0; k<CN; k++){
				red_green[j][k]=2*rand()/32767.0f;
				tail[j][k]=TAILL*rand()/32767.0f+1;
			}

		ff=(srnd++)%6;
		dt=(float)(DT/L*PI);
		dy=(float)((L-DT)/VN);
		y=0;

		for(k=0;k<=VN;k++)
		{
			r=(float)(H*sin(y*PI/L+dt));
			for(l=0;l<CN;l++)
			{
				vetxm[list][k][l][0]=r*tmp[l][0];
				vetxm[list][k][l][1]=-y;
				vetxm[list][k][l][2]=r*tmp[l][1];
				vetxm[list][k][l][6]=1;
				if (y<=red_green[ff][l]){
					t=y/red_green[ff][l];
					vetxm[list][k][l][3]=vetxm[list][k][l][4]=t*t+0.1f;
					vetxm[list][k][l][4]=vetxm[list][k][l][3]-0.3f;
					vetxm[list][k][l][5]=vetxm[list][k][l][4]+0.4f;
				}   else {
					vetxm[list][k][l][3]=1.0f-y/(L-DT+ADDL);
					vetxm[list][k][l][4]=vetxm[list][k][l][3]-0.3f;
					vetxm[list][k][l][5]=0.08f;
				}
				t=L-DT-y;
				if(t<=tail[ff][l])
					vetxm[list][k][l][6]=0;
			}
			y+=dy;
		}
	}
}

void CRenderView::MakeFireList()
{
	int k, l,list;

	for (list = 0; list < LIST; list++){
		glNewList(list+1, GL_COMPILE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		for(k=0;k<VN;k++)
		{
			for(l=0;l<CN-1;l++)
			{
				glBegin(GL_POLYGON);
				glColor4f(vetxm[list][k][l][3],vetxm[list][k][l][4],vetxm[list][k][l][5],vetxm[list][k][l][6]);
				glVertex3f(vetxm[list][k][l][0],vetxm[list][k][l][1],vetxm[list][k][l][2]);
				glColor4f(vetxm[list][k+1][l][3],vetxm[list][k+1][l][4],vetxm[list][k+1][l][5],vetxm[list][k+1][l][6]);
				glVertex3f(vetxm[list][k+1][l][0],vetxm[list][k+1][l][1],vetxm[list][k+1][l][2]);
				glColor4f(vetxm[list][k+1][l+1][3],vetxm[list][k+1][l+1][4],vetxm[list][k+1][l+1][5],vetxm[list][k+1][l+1][6]);
				glVertex3f(vetxm[list][k+1][l+1][0],vetxm[list][k+1][l+1][1],vetxm[list][k+1][l+1][2]);
				glColor4f(vetxm[list][k][l+1][3],vetxm[list][k][l+1][4],vetxm[list][k][l+1][5],vetxm[list][k][l+1][6]);
				glVertex3f(vetxm[list][k][l+1][0],vetxm[list][k][l+1][1],vetxm[list][k][l+1][2]);
				glEnd();
				glFlush();
			}
			glBegin(GL_POLYGON);
			glColor4f(vetxm[list][k][l][3],vetxm[list][k][l][4],vetxm[list][k][l][5],vetxm[list][k][l][6]);
			glVertex3f(vetxm[list][k][l][0],vetxm[list][k][l][1],vetxm[list][k][l][2]);
			glColor4f(vetxm[list][k+1][l][3],vetxm[list][k+1][l][4],vetxm[list][k+1][l][5],vetxm[list][k+1][l][6]);
			glVertex3f(vetxm[list][k+1][l][0],vetxm[list][k+1][l][1],vetxm[list][k+1][l][2]);
			glColor4f(vetxm[list][k+1][0][3],vetxm[list][k+1][0][4],vetxm[list][k+1][0][5],vetxm[list][k+1][0][6]);
			glVertex3f(vetxm[list][k+1][0][0],vetxm[list][k+1][0][1],vetxm[list][k+1][0][2]);
			glColor4f(vetxm[list][k][0][3],vetxm[list][k][0][4],vetxm[list][k][0][5],vetxm[list][k][0][6]);
			glVertex3f(vetxm[list][k][0][0],vetxm[list][k][0][1],vetxm[list][k][0][2]);
			glEnd();
		}
		glFlush();
		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEndList();
	}
}

void CRenderView::OnTimer(UINT nIDEvent) 
{
	loop+=1.0f;
	Invalidate(FALSE);
}
