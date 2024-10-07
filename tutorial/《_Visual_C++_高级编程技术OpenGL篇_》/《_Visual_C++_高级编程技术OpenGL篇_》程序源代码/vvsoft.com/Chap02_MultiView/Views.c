#include <windows.h> 
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glut.lib")
#pragma comment(lib,"GLAUX.LIB")



/* Windows globals, defines, and prototypes */ 
CHAR szAppName[]="Views"; 
HWND  ghWnd; 
HDC   ghDC; 
HGLRC ghRC; 


GLUquadricObj *qobj;
 
#define WIDTH	400
#define HEIGHT	400


static GLint sphere,cyl,mol;

// light
static GLfloat light1_pos[] = {20.0,10.0,40.0,1.0};

GLfloat cyl_amb_dif[] = {0.0,1.0,0.0,1.0};
GLfloat cyl_spec[] = {1.0,1.0,1.0,1.0};
GLfloat sph_amb_dif[] = {0.8,0.2,0.5,1.0};
GLfloat sph_spec[] = {1.0,1.0,1.0,1.0};

static int Width, Height;

LONG WINAPI MainWndProc (HWND, UINT, WPARAM, LPARAM); 
BOOL bSetupPixelFormat(HDC); 
 
GLvoid resize(GLsizei, GLsizei); 
GLvoid initializeGL(GLsizei, GLsizei); 
GLvoid drawScene(HWND hWnd); 
 
void MakeSphere(void);
void MakeCylinder(void);
void MakeMol(void);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{ 
    MSG        msg; 
    WNDCLASS   wndclass; 
 
    /* Register the frame class */ 
    wndclass.style         = 0; 
    wndclass.lpfnWndProc   = (WNDPROC)MainWndProc; 
    wndclass.cbClsExtra    = 0; 
    wndclass.cbWndExtra    = 0; 
    wndclass.hInstance     = hInstance; 
    wndclass.hIcon         = LoadIcon (hInstance, szAppName); 
    wndclass.hCursor       = LoadCursor (NULL,IDC_ARROW); 
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); 
    wndclass.lpszMenuName  = szAppName; 
    wndclass.lpszClassName = szAppName; 
 
    if (!RegisterClass (&wndclass) ) 
        return FALSE; 
 
    /* Create the frame */ 
    ghWnd = CreateWindow (szAppName, 
             "Multiple Views", 
         WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
             CW_USEDEFAULT, 
             CW_USEDEFAULT, 
             WIDTH, 
             HEIGHT, 
             NULL, 
             NULL, 
             hInstance, 
             NULL); 
 
    /* make sure window was created */ 
    if (!ghWnd) 
        return FALSE; 
 
    /* show and update main window */ 
    ShowWindow (ghWnd, nCmdShow); 
 
    UpdateWindow (ghWnd); 
 
    while(GetMessage(&msg,NULL,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
} 
 
/* main window procedure */ 
LONG WINAPI MainWndProc ( 
    HWND    hWnd, 
    UINT    uMsg, 
    WPARAM  wParam, 
    LPARAM  lParam) 
{ 
    LONG    lRet = 1; 
    PAINTSTRUCT    ps; 
    RECT rect; 
	//static BOOL Right = TRUE;
 
    switch (uMsg) { 
 
    case WM_CREATE: 
        ghDC = GetDC(hWnd); 

        if (!bSetupPixelFormat(ghDC)) 
            PostQuitMessage (0); 
 
        ghRC = wglCreateContext(ghDC); 
        wglMakeCurrent(ghDC, ghRC); 
        GetClientRect(hWnd, &rect); 
        initializeGL(rect.right, rect.bottom); 
        break; 

	case WM_SIZE: 
        GetClientRect(hWnd, &rect); 
        resize(rect.right, rect.bottom); 
		InvalidateRect(hWnd,NULL,TRUE);


        break; 

 
    case WM_PAINT: 
        BeginPaint(hWnd, &ps); 

		drawScene(hWnd);

        EndPaint(hWnd, &ps); 
        break; 

    case WM_DESTROY: 

        if (ghRC) 
            wglDeleteContext(ghRC); 
        if (ghDC) 
            ReleaseDC(hWnd, ghDC); 
 
        PostQuitMessage (0); 
        break; 
       
    default: 
        lRet = DefWindowProc (hWnd, uMsg, wParam, lParam); 
        break; 
    } 
 
    return lRet; 
}



BOOL bSetupPixelFormat(HDC hdc) 
{ 
    PIXELFORMATDESCRIPTOR *ppfd; 
    int pixelformat; 
 
	PIXELFORMATDESCRIPTOR pfd = { 
    sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd 
    1,                     // version number 
    PFD_DRAW_TO_WINDOW |   // support window 
    PFD_SUPPORT_OPENGL |   // support OpenGL 
    PFD_DOUBLEBUFFER,      // double buffered 
    PFD_TYPE_RGBA,         // RGBA type 
    24,                    // 24-bit color depth 
    0, 0, 0, 0, 0, 0,      // color bits ignored 
    0,                     // no alpha buffer 
    0,                     // shift bit ignored 
    0,                     // no accumulation buffer 
    0, 0, 0, 0,            // accum bits ignored 
    32,                    // 32-bit z-buffer	 
    32,                     //  stencil buffer 
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

GLfloat aspect;  

GLvoid resize( GLsizei width, GLsizei height ) 
{ 
    
 
	Width = width;
	Height = height;
 
    
}     

GLvoid initializeGL(GLsizei width, GLsizei height) 
{
	FILE* fp;
	int i,j;
	GLfloat tmp;

	srand(1234);
	
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj,GLU_FILL);
	gluQuadricNormals(qobj,GLU_SMOOTH);

	glClearColor(1.0,1.0,1.0,0.0);
	
	glShadeModel(GL_SMOOTH);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_POSITION,light1_pos);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	

	MakeSphere();
	MakeCylinder();
	MakeMol();
}
 
GLvoid drawScene(hWnd) 
{ 
	// View 1

	glEnable(GL_SCISSOR_TEST);
	//glPushAttrib(GL_SCISSOR_BIT);
	glScissor(0,0,Width/2,Height);
	glClearColor(0.55,0.7,0.7,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);
	//glPopAttrib();

	//aspect = Width/(2.0*Height);
	aspect = Width/(Height);

	glMatrixMode( GL_PROJECTION ); 
    glLoadIdentity(); 
    gluPerspective( 60.0, aspect, 5.0, 70.0); 
	//glOrtho(-30.0,30.0,-30.0,30.0,-5.0,50.0);
    glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();
	
	glViewport(0,0,Width/2,Height);

	glPushMatrix();

	gluLookAt(25.0,25.0,50.0,25.0,25.0,20.0,0.0,1.0,0.0);

	glLightfv(GL_LIGHT0,GL_POSITION,light1_pos);

	glTranslatef(25.0,25.0,10.0);
	glCallList(mol);		

	glPopMatrix();

	// View 2

	glEnable(GL_SCISSOR_TEST);
	//glPushAttrib(GL_SCISSOR_BIT);
	glScissor(Width/2 + 1,Height/2 +1,Width/2,Height/2);
	glClearColor(0.77,0.7,0.7,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPopAttrib();
	glDisable(GL_SCISSOR_TEST);

	aspect = Width/(Height);

	glMatrixMode( GL_PROJECTION ); 
    glLoadIdentity(); 
    gluPerspective( 60.0, aspect, 5.0, 70.0); 
	//glOrtho(-30.0,30.0,-30.0,30.0,-5.0,50.0);
    glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();
	
	glViewport(Width/2 + 1,Height/2 +1,Width/2,Height/2);

	glPushMatrix();

	gluLookAt(25.0,50.0,50.0,25.0,25.0,20.0,0.0,1.0,0.0);

	glLightfv(GL_LIGHT0,GL_POSITION,light1_pos);

	glTranslatef(25.0,25.0,10.0);
	glCallList(mol);		

	glPopMatrix();

	// View 3

	glEnable(GL_SCISSOR_TEST);
	//glPushAttrib(GL_SCISSOR_BIT);
	glScissor(Width/2 +1,0,Width/2,Height/2);
	glClearColor(0.0,0.6,0.7,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPopAttrib();
	glDisable(GL_SCISSOR_TEST);

	aspect = Width/(Height);

	glMatrixMode( GL_PROJECTION ); 
    glLoadIdentity(); 
    gluPerspective( 60.0, aspect, 5.0, 70.0); 
	//glOrtho(-30.0,30.0,-30.0,30.0,-5.0,50.0);
    glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();
	
	glViewport(Width/2 +1,0,Width/2,Height/2);

	glPushMatrix();

	gluLookAt(0.0,25.0,50.0,25.0,25.0,20.0,0.0,1.0,0.0);

	glLightfv(GL_LIGHT0,GL_POSITION,light1_pos);

	glTranslatef(25.0,25.0,10.0);
	glCallList(mol);		

	glPopMatrix();


	SwapBuffers(ghDC);
} 


void MakeSphere(void)
{
	sphere = glGenLists(1);
	glNewList(sphere,GL_COMPILE);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,sph_amb_dif);
		glMaterialfv(GL_FRONT,GL_SPECULAR,sph_spec);
		glMaterialf(GL_FRONT,GL_SHININESS,100.0);
		
		gluSphere(qobj,2.5,20,20);
		
	glEndList();
}

void MakeCylinder(void)
{
	cyl = glGenLists(1);
	glNewList(cyl,GL_COMPILE);
		glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,cyl_amb_dif);
		glMaterialfv(GL_FRONT,GL_SPECULAR,cyl_spec);
		glMaterialf(GL_FRONT,GL_SHININESS,100.0);
		
		gluCylinder(qobj,0.5,0.5,10.0,20,20);
	glEndList();
}

void MakeMol(void)
{
	int i;
	mol = glGenLists(1);
	glNewList(mol,GL_COMPILE);

		glCallList(sphere);
		glCallList(cyl);

		glPushMatrix();
		glRotatef(270.0,1.0,0.0,0.0);
		for(i=0;i<3;i++)
		{
			glPushMatrix();
				glRotatef(120.0*i,0.0,1.0,0.0);
				glCallList(cyl);
				glTranslatef(0.0,0.0,10.0);
				glCallList(sphere);			
			glPopMatrix();

		}
		glPopMatrix();
		glTranslatef(0.0,0.0,10.0);
		glPushMatrix();

		glRotatef(270.0,1.0,0.0,0.0);
		for(i=0;i<3;i++)
		{
			glPushMatrix();
				glRotatef(60.0+120.0*i,0.0,1.0,0.0);
				glCallList(cyl);
				glTranslatef(0.0,0.0,10.0);
				glCallList(sphere);			
			glPopMatrix();

		}
		glPopMatrix();

	glEndList();
}
