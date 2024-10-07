#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#define IDM_APPLICATION_EXIT    (101)
#define IDM_APPLICATION_TEXTURE (102)
#define IDM_APPLICATION_BANK    (103)
#define MAZE_HEIGHT (16)
#define MAZE_WIDTH  (16)
#define STARTING_POINT_X (1.5f);
#define STARTING_POINT_Y (1.5f);
#define STARTING_HEADING (90.0f);

HWND  hWND;
HDC   hDC;
HGLRC hGLRC;
float player_x = STARTING_POINT_X ;
float player_y = STARTING_POINT_Y ;
float player_h = STARTING_HEADING ;  // player's heading
float player_s = 0.0f;  // forward speed of the player
float player_m = 1.0f;  // speed multiplier of the player
float player_t = 0.0f;  // player's turning (change in heading)
float player_b = 0.0f;  // viewpoint bank (roll)
int   walllist=0;
int       mazelist=0;

void  spinmaze(HDC hDC);
void  entermaze(HDC hDC);
void  navmaze(HDC hDC);
void  (*idlefunc)(HDC hDC)=NULL;

// unfortunately due to the way the polygon walls are generated there
// are restrictions on what the wall/maze data can look like.  See below.
char *mazedata[MAZE_HEIGHT] = {
        "HHHHHHHHHHHHHHHH",
        "H       H      H",
        "H H HHH H H    H",
        "H HH  H HH H H H",
        "H     H      H H",
        "HHHHHHHHHH HHH H",
        "H           H  H",
        "H HHHHH HHH HHHH",
        "H H   H   H    H",
        "H   HHHHHHH    H",
        "H H   H   H  H H",
        "H HHHHH HHHH H H",
        "H     H      H H",
        "HH HH HHHH HHH H",
        "H   H H    H   H",
        "HHHHHHHHHHHHH HH",
};

int wall(int x,int y) {
        // true if the region at x,y is solid space that
        // should be surrounded by other solid space or polygon walls
        return (x>=0 && y>=0 && x<MAZE_WIDTH && y<MAZE_HEIGHT && ' ' != mazedata[y][x]);
}

int onopen(int x,int y){
        //  returns whether node x,y is on the depth-first search open list
        assert(wall(x,y));
        return(mazedata[y][x]=='H');
}
void closeit(int x,int y) {
        //  puts node x,y on the closed list
        assert(wall(x,y));
        assert(onopen(x,y));
        mazedata[y][x]= 'X';
}
int neighbor(int x,int y,int w,int *nx,int *ny){
        // if x,y has a neighbor in direction w then returns true
        switch(w) {
        case 0:
                *nx = x-1; *ny=y;   break;
        case 1:
                *nx = x;   *ny=y+1; break;
        case 2:
                *nx = x+1; *ny=y;   break;
        case 3:
                *nx = x;   *ny=y-1; break;
        default:
                assert(0);
        }
        return wall(*nx,*ny);
}
int diagnal(int x,int y,int w,int *nx,int *ny){
        switch(w) {
        case 0:
                *nx = x-1; *ny=y-1; break;
        case 1:
                *nx = x-1; *ny=y+1; break;
        case 2:
                *nx = x+1; *ny=y+1; break;
        case 3:
                *nx = x+1; *ny=y-1; break;
        default:
                assert(0);
        }
        return wall(*nx,*ny);
}
static float texcoordX=0.0f;
int dw(int x,int y,int p) {
        // the recursive draw wall routine that extends the quad strip
	int w=p;  // w is the current wall direction being considered
 	closeit(x,y);
    do{
		int x2,y2;
		if(neighbor(x,y,w,&x2,&y2)) {
			if(onopen(x2,y2)) {
				dw(x2,y2,(w+3)%4);
			}
            else {
				assert((w+1)%4 ==p); // or a loop or cluster exists
                return 1;
			}
		}
        else {
		    float fx;
		    float fy;
			if(diagnal(x,y,w,&x2,&y2) && onopen(x2,y2)) {
				dw(x2,y2,(w+2)%4);
			}
			texcoordX=(texcoordX<0.5)?1.0f:0.0f;
			fx = (float)x+((w==1||w==2)?1.0f:0.0f);
            fy = (float)y+((w==0||w==1)?1.0f:0.0f);
            glTexCoord2f(texcoordX,0.0f);  // useful iff using textures
            glVertex3f(fx,fy,0.0f);
            glTexCoord2f(texcoordX,1.0f);
            glVertex3f(fx,fy,1.0f);
		}
		w++;w%=4;
	}while (w!=p);
    return 1;
}

int drawwalls() {
	int dl;
    glNewList(dl=glGenLists(1),GL_COMPILE);
    glBegin(GL_QUAD_STRIP);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    dw(0,0,0);
    glEnd();
    glEndList();
    return dl;
}

int drawtop() {
        // draws the top and the bottom of the maze
        // which is useful for overhead views
        // The display list created here is only used for the intro
        // spinning bit.  No optimizations such as using quad strips
        // or combining adjacent polygons are done here.
	int x,y,dl;
    glNewList(dl=glGenLists(1),GL_COMPILE);
    glPushAttrib(GL_TEXTURE_BIT | GL_LIGHTING_BIT);
    glBegin(GL_QUADS);
    for(y=0;y<MAZE_HEIGHT;y++) {
     for(x=0;x<MAZE_WIDTH;x++) {
      if(wall(x,y)) {
        glVertex3f(x+0.0f ,y+0.0f ,1.0f );
        glVertex3f(x+1.0f ,y+0.0f ,1.0f );
        glVertex3f(x+1.0f ,y+1.0f ,1.0f );
        glVertex3f(x+0.0f ,y+1.0f ,1.0f );
          }
         }
        }
    glEnd();
        glPopAttrib();
    glEndList();
    return(dl);
}

void spinmaze(HDC hDC) {
    // spin the maze around on 2 axis
    static float spin=720.0f;
    spin-=5.0f;  // change this line to be time dependant!
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-20.0f);
    glRotatef(spin, 0.0f, 1.0f, 1.0f);
    glTranslatef(-MAZE_WIDTH/2.0f,-MAZE_HEIGHT/2.0f,0.0f);
    glCallList(walllist);
    glCallList(mazelist);
    glPopMatrix();
    SwapBuffers(hDC);
    if(spin <=0.0f) {
		spin = 720.0f;
        idlefunc = entermaze;
        player_x = STARTING_POINT_X ;
        player_y = STARTING_POINT_Y ;
        player_h = STARTING_HEADING ;
	}
}

void entermaze(HDC hDC) {
	static float p=0.0f;
	p+=0.02f; // hmmm, should be time dependant
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glRotatef(-90.0f*p,1.0f,0.0f,0.0f);
    glRotatef(player_h*p,0.0f,0.0f,1.0f);
    glTranslatef(-(player_x*p + MAZE_WIDTH /2.0f*(1-p)),
                 -(player_y*p + MAZE_HEIGHT/2.0f*(1-p)),
                 -(0.5f*p + 20.0f*(1-p)));
    glCallList(walllist);
    glCallList(mazelist);
    glPopMatrix();
    SwapBuffers(hDC);
    if(p>=1.0f) {
		p=0.0f;
        idlefunc = navmaze;
	}
}


int forward(float px,float py,float bf) {
        int x = ((int)player_x);
        int y = ((int)player_y);
    int h=0;            // number of walls hit
    if((px> x+1.0f - bf) && wall(x+1,y)) {
        px = (float)(x)+1.0f-bf;
        h++;
    }
    if(py> y+1.0f-bf && wall(x,y+1))  {
        py = (float)(y)+1.0f-bf;
        h++;
    }
    if(px< x+bf && wall(x-1,y)) {
        px = (float)(x)+bf;
        h++;
    }
    if(py< y+bf && wall(x,y-1)) {
        py = (float)(y)+bf;
        h++;
    }
        player_x=px;
        player_y=py;
        return h;
}

        // navigate through the maze and render it from the
        // players point of view.
        // Ideally updates to heading and position should be time dependant
void navmaze(HDC hDC)
{
    forward(player_x+player_m*player_s*(float)sin(player_h*3.14/180),
            player_y+player_m*player_s*(float)cos(player_h*3.14/180),0.2f);
    player_h+=player_t;
    player_b = 3*player_b/4 + player_t/4;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glRotatef(-90.0f,1.0f,0.0f,0.0f);
    glRotatef(player_h,0.0f,0.0f,1.0f);
    glTranslatef(-player_x,-player_y,-0.5f);
    glCallList(walllist); // no need to draw the top since we're in the maze now
    glPopMatrix();
    SwapBuffers(hDC);
    if(player_x>MAZE_WIDTH || player_y>MAZE_HEIGHT) {
        // start over
        idlefunc = spinmaze;
    }
}

void readtexture(){
    unsigned char *image;
    int rc;
    // the bitmap must be a 24 bit bmp file thats 128x128
    // I think i mixed up red and blue componants - oh well :-)
    FILE *fp;
    fp = fopen("maze.bmp","rb");
    if(!fp) return;
    fseek(fp,54,SEEK_SET);
    image = (unsigned char *)malloc(128*128*3);
    assert(image);
    rc=fread(image,sizeof(unsigned char),128*128*3,fp);
    assert(rc == 128*128*3);
    glTexImage2D(GL_TEXTURE_2D,0,3,128,128,0,GL_RGB,
                 GL_UNSIGNED_BYTE, image);
    // let texture wrap-around
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // use point sampleing (fastest)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable (GL_TEXTURE_2D);
    fclose(fp);
}

static void SetupDC(HDC hDC)
{
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),  /* size of this pfd */
        1,                              /* version num */
        PFD_DRAW_TO_WINDOW |            /* window types */
        PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,                  /* RGBA type */
        8,                              /* 8-bit color depth */
        0, 0, 0, 0, 0, 0,               /* color bits (ignored) */
        0,                              /* no alpha buffer */
        0,                              /* alpha bits (ignored) */
        0,                              /* no accumulation buffer */
        0, 0, 0, 0,                     /* accum bits (ignored) */
        16,                             /* 16-bit depth buffer */
        0,                              /* no stencil buffer */
        0,                              /* no auxiliary buffers */
        PFD_MAIN_PLANE,                 /* main layer */
        0,                              /* reserved */
        0, 0, 0,                        /* no layer, visible, damage */
                                        /* masks */
    };
    int SelectedPixelFormat;
    BOOL retVal;
    /* see if the pixel format exists */
    SelectedPixelFormat = ChoosePixelFormat(hDC, &pfd);
    if (SelectedPixelFormat == 0) {
        MessageBox(WindowFromDC(hDC),
                   "Failed to find acceptable pixel format.",
                   "OpenGL application error", MB_ICONERROR|MB_OK);
        exit(1);
    }
    /* use the pixel format */
    retVal = SetPixelFormat(hDC, SelectedPixelFormat, &pfd);
    if (retVal != TRUE) {
        MessageBox(WindowFromDC(hDC), "Failed to set pixel format.",
                   "OpenGL application error", MB_ICONERROR|MB_OK);
        exit(1);
    }
}

LRESULT APIENTRY WinProc(HWND hWND, UINT message, WPARAM wParam,
                         LPARAM lParam)
{

    switch (message) {
        case WM_CREATE:
            hDC = GetDC(hWND);
            SetupDC(hDC);
            hGLRC = wglCreateContext(hDC);
            wglMakeCurrent(hDC, hGLRC);
            glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
            readtexture();			
            glEnable(GL_CULL_FACE);
            glShadeModel(GL_FLAT);
            walllist = drawwalls();
            mazelist = drawtop();
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60.0, 1.0 , 0.1, 60.0);
            glMatrixMode(GL_MODELVIEW);
            glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
            glLoadIdentity ();
			glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
            idlefunc = spinmaze;
            return 0;
        case WM_DESTROY:
            if (hGLRC) {
                wglMakeCurrent(NULL, NULL);
                wglDeleteContext(hGLRC);
            }
            ReleaseDC(hWND, hDC);
            PostQuitMessage(0);
            return 0;
		case WM_SIZE:
			glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
			break;
		//  方向键按下，向指定方向前进
        case WM_KEYDOWN:
			switch (LOWORD((int)wParam)) {
				case VK_LEFT:
					player_t = -5.0f;
					break;
				case VK_RIGHT:
					player_t = 5.0f;
					break;
				case VK_UP:
					player_s = 0.05f;
					break;
				case VK_DOWN:
					player_s = -0.02f;
					break;
				case VK_SHIFT:
					player_m = 3.0f;
					break;
			}
            break;
		//  方向键松开，停止前进
		case WM_KEYUP:
			switch (LOWORD((int)wParam)) {
				case VK_LEFT:
					player_t = 0.0f;
					break;
				case VK_RIGHT:
					player_t = 0.0f;
					break;
				case VK_UP:
					player_s = 0.0f;
					break;
				case VK_DOWN:
					player_s = 0.0f;
					break;
				case VK_SHIFT:
					player_m = 1.0f;
					break;
			}
			break;
		default:
			break;
	}
	return DefWindowProc(hWND, message, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hCurrentInst, HINSTANCE hPreviousInst,
                     LPSTR lpszCmdLine, int nCmdShow)
{
    char *className = "OpenGL";
    char *winName = "Maze Example";
    WNDCLASS winClass;
    MSG msg;

    // 定义并登记窗口类
    winClass.style = CS_HREDRAW | CS_VREDRAW;
    winClass.lpfnWndProc = WinProc;
    winClass.cbClsExtra = 0;
    winClass.cbWndExtra = 0;
    winClass.hInstance = hCurrentInst;
    winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    winClass.hbrBackground = GetStockObject(WHITE_BRUSH);
    winClass.lpszMenuName = NULL;
    winClass.lpszClassName = className;
    RegisterClass(&winClass);
    // 创建窗口
    hWND = CreateWindow(className,
		winName,
		WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
		0, 0,
		300, 300,
        NULL,              /* Parent window's handle */
        NULL,              /* Menu handle */
        hCurrentInst,      /* Instance handle */
        NULL);             /* No additional data */
    ShowWindow(hWND, nCmdShow);

    UpdateWindow(hWND);
    // 事件处理
    while (1) {
        // oops, busy wait when no messages or idlefunc - ohwell
        if(idlefunc)idlefunc(hDC);
        if(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)){
			if (GetMessage(&msg, NULL, 0, 0) != TRUE) {
				return msg.wParam;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
    }
}
