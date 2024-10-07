#include <windows.h> 
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <math.h> 

#define		DEG_TO_RAD	(3.1415927 / 180.0)
#define		BOXWIDTH	100.0

GLfloat		azimuth = 0.0; 
GLfloat		inclin = 0.0;

/* Windows globals, defines, and prototypes */ 
CHAR szAppName[]="View"; 
HWND  ghWnd; 											   
HDC   ghDC; 
HGLRC ghRC; 

GLUquadricObj *qobj;
 
#define WIDTH	600
#define HEIGHT	600

BOOL bSetupPixelFormat(HDC); 
 
GLvoid resize(GLsizei, GLsizei); 
GLvoid initializeGL(GLsizei, GLsizei); 
GLvoid drawScene(GLvoid); 
void initLighting(void);
void setTransform(void);
void DrawFrame(HWND hWnd); 

GLint ell;
GLfloat dist=0.0;

GLvoid initializeGL(GLsizei width, GLsizei height) 
{
	initLighting();

	glEnable(GL_NORMALIZE);
    glClearColor(0.0, 0.0, 0.0, 0.0);	
}

BOOL bSetupPixelFormat(HDC hdc) 
{ 
    PIXELFORMATDESCRIPTOR *ppfd; 
    int pixelformat; 
 
	PIXELFORMATDESCRIPTOR pfd = { 
        sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd 
        1,                     // version number 
        PFD_DRAW_TO_WINDOW |   // support window 
        PFD_SUPPORT_OPENGL,    // support OpenGL 
        //PFD_DOUBLEBUFFER,    // double buffered 
        PFD_TYPE_RGBA,         // RGBA type 
        24,                    // 24-bit color depth 
        0, 0, 0, 0, 0, 0,      // color bits ignored 
        0,                     // no alpha buffer 
        0,                     // shift bit ignored 
        0,                     // no accumulation buffer 
        0, 0, 0, 0,            // accum bits ignored 
        32,                    // 32-bit z-buffer	 
        0,                     // no stencil buffer 
        0,                     // no auxiliary buffer 
        PFD_MAIN_PLANE,        // main layer 
        0,                     // reserved 
        0, 0, 0                // layer masks ignored 
    }; 

	pfd.cColorBits = GetDeviceCaps(ghDC,BITSPIXEL);
 
	ppfd = &pfd;

    pixelformat = ChoosePixelFormat(hdc, ppfd); 
 
    if ( (pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0 ) 
    { 
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK); 
        return FALSE; 
    } 
    if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE) 
    { 
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK); 
        return FALSE; 
    } 
    return TRUE; 
} 
 
/* OpenGL code */ 
GLvoid resize( GLsizei width, GLsizei height ) 
{ 

    glViewport( 0, 0, width, height ); 

	setTransform();
    drawScene();
}     
 
static void  spherToRect (double azim, double inc, double disteye,
			  double  *px, double  *py, double  *pz)
{
    double theta, phi, rho;             /* spherical coordinates */

    theta = azim - 90.0;                /* theta starts at +x axis */
    phi = 90.0 - inc;                   /* phi runs from 0 to 180 */
    rho = disteye;

    *px = rho * sin(phi*DEG_TO_RAD) * cos(theta*DEG_TO_RAD);
    *py = rho * sin(phi*DEG_TO_RAD) * sin(theta*DEG_TO_RAD);
    *pz = rho * cos(phi*DEG_TO_RAD);
}                                       /* end of spherToRect */

void  setTransform( void )
{
    GLfloat  eyedistance = 300.0;                 
    GLfloat  twist = 0.0;
    GLdouble fovy = 40.0;
    GLdouble aspect = 1.0;
    GLdouble znear, zfar;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    znear = eyedistance - (BOXWIDTH * 1.5);
    zfar = eyedistance + (BOXWIDTH * 1.5);
    gluPerspective(fovy, aspect, znear, zfar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  

    glTranslatef(0.0, 0.0, -eyedistance+dist);
    glRotated(-twist, 0.0, 0.0, 1.0);	
    glRotated(-(90.0 - inclin), 1.0, 0.0, 0.0);
    glRotated(-azimuth, 0.0, 0.0, 1.0);
}

/*----------------------------------------------------------------------*/
static void  initLighting( void )
{
    GLfloat	   light_position[] = { 0.0, 0.0, 0.0, 0.0 };
    GLfloat	   light_diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat	   light_specular[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat	   lmodel_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
    GLfloat	   mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat	   mat_shininess[] = { 50.0 };
    double	   litx, lity, litz;
    static float   litazim = 0.0;
    static float   litinclin = 0.0;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    spherToRect((double)litazim, (double)litinclin, 1.0,
                  &litx, &lity, &litz);

 /* correct position for coordinate system where z axis faces viewer,
    x axis points right, y axis points up */
    light_position[1] = (GLfloat)litx;
    light_position[2] = (GLfloat)litz;
    light_position[3] = (GLfloat)-lity;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);  /* OFF for now */
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_LIGHT0);
    qobj = gluNewQuadric();
    gluQuadricNormals(qobj,GLU_SMOOTH);
	ell = glGenLists(1);
	glNewList(ell,GL_COMPILE);
	  gluSphere(qobj,1.0,20,20);
 	glEndList();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}	/* end of initLighting */

static void DrawEllipsoid(void)
{
  float r = 20.0;
  glColor3f(1.0,1.0,0.0);
  glScalef(1.0,1.25,1.5);
  gluSphere(qobj,r,20,20);
  glScalef(1.0,1.0,1.0);
}

/*----------------------------------------------------------------------*/
 GLvoid drawScene(GLvoid) 
{
	static int theta = 0;
	static int alpha = 0;
	GLfloat x,y,z;
	/* set clear color to black */
	if(!theta%360)
	  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	theta = (theta + 10)%360;
	glPushMatrix();
	x = 100.0f*(GLfloat)cos(theta*DEG_TO_RAD) + 50.0f;
	z = 100.0f*(GLfloat)sin(theta*DEG_TO_RAD) + 50.0f;
	y = 100.0f;
	glTranslatef(x,y,z);
	glColor3f(rand()%255/255.0f,rand()%255/255.0f,rand()%255/255.0f);
	glScalef(20.0f,20.0f,20.0f);
	glCallList(ell);
	glPopMatrix();	
	glPushMatrix();
    glTranslatef(-x,y,-z);
	glColor3f(rand()%255/255.0f,rand()%255/255.0f,rand()%255/255.0f);
	glScalef(20.0f,20.0f,20.0f);
	glCallList(ell);
	glPopMatrix();
	glPushMatrix();
    glTranslatef(-50.0f,0.0f,0.0f);
	glColor3f(rand()%255/255.0f,rand()%255/255.0f,rand()%255/255.0f);
	
	glRotatef((GLfloat)theta,1.0f,0.0f,0.0f);
	glScalef(25.0f,25.0f,25.0f);
	glPopMatrix();
	glFlush();

	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
}

void DrawFrame(HWND hWnd)
{
	HDC hDC = GetDC(hWnd); // Get the DC for the window
    RECT rect;
    // If we didn't get a DC for the window then bail
    if (!hDC)
        return;
	// Get our drawing surface extents
    GetClientRect(hWnd, &rect);
    {
		setTransform();
		drawScene();
    }
    ReleaseDC(hWnd, hDC);
}     
