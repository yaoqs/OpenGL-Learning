#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <regstr.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#pragma hdrstop
#include "resource.h"
#include "tsaver.h"
#include <math.h>

#pragma warning(disable: 4800)
#pragma warning(disable: 4305)
#pragma warning(disable: 4244)
#define MAXTYPE 5
#define MAXCN 2000
#define TIMEPART 200
#define MAXPART 2048
#define FLOORX 9
#define FLOORZ 9

HINSTANCE hInstance=NULL;
HWND hScrWindow=NULL;
TSaverSettings *ss=NULL;
typedef struct
{
	float xc;
	float yc;
	float zc;
	float an;
	int type;
	int cn;
	float ant;
} VAR;
VAR var;

typedef struct
{
	int active;
	int rimb;
	float x;
	float y;
	float z;
	float dx;
	float dy;
	float dz;
} PART;
PART part[MAXPART];

typedef struct
{
	double x;
	double y;
	double z;
} Vector;
Vector Puf[4];
Vector flr[FLOORX][FLOORZ];
GLuint	texture[4];

// 求矢量长度
double VectorLength( Vector v )
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//  矢量规范化
Vector VectorNormalize( Vector v )
{
	Vector vresult;
	double l = VectorLength( v );

	vresult.x = v.x/l;
	vresult.y = v.y/l;
	vresult.z = v.z/l;

	return vresult;
}

//  -------------------------------------------------------------------
Vector VectorMultiply( Vector v1, Vector v2 )
{
	Vector vresult;

	vresult.x = v1.y * v2.z - v1.z * v2.y;
	vresult.y = v1.z * v2.x - v1.x * v2.z;
	vresult.z = v1.x * v2.y - v1.y * v2.x;

	return vresult;
}

//-------------------------------------------------------------------
Vector VectorScalarMultiply( Vector v, double s )
{
	Vector vresult;

	vresult.x = v.x * s;
	vresult.y = v.y * s;
	vresult.z = v.z * s;

	return vresult;
}

//-------------------------------------------------------------------
Vector VectorDiff( Vector v1, Vector v2 )
{
	Vector vresult;

	vresult.x = v1.x - v2.x;
	vresult.y = v1.y - v2.y;
	vresult.z = v1.z - v2.z;

	return vresult;
}

void Luce(double x, double y, double z,double dimensione,float r,float g,float b,float iox,float ioy,float ioz,int Tex)
{
	Vector Position;
	Vector MyPosition;
	Position.x = x;
	Position.y = y;
	Position.z = z;

	MyPosition.x=iox;
	MyPosition.y=ioy;
	MyPosition.z=ioz;
	Vector sight = VectorDiff(MyPosition, Position);

	Vector cz;
	cz.x = 0;
	cz.y = 0;
	cz.z = 1;

	Vector cross1 = VectorMultiply( sight, cz );
	Vector cross2 = VectorMultiply( sight, cross1 );

	cross1 = VectorNormalize(cross1);
	cross2 = VectorNormalize(cross2);

	cross1 = VectorScalarMultiply(cross1, dimensione);
	cross2 = VectorScalarMultiply(cross2, dimensione);

	glColor3f(r,g,b);
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc( (1,1,1,1), (1,1,1,1));
	glDepthMask (GL_FALSE);

	glBindTexture( GL_TEXTURE_2D, texture[Tex] );
	glBegin(GL_QUADS);
		glTexCoord2d( 0.0, 0.0 );
		glVertex3d( Position.x + cross1.x, Position.y + cross1.y, Position.z + cross1.z);
		glTexCoord2d( 1.0, 0.0 );
		glVertex3d( Position.x - cross2.x, Position.y - cross2.y, Position.z - cross2.z);
		glTexCoord2d( 1.0, 1.0 );
		glVertex3d( Position.x - cross1.x, Position.y - cross1.y, Position.z - cross1.z);
		glTexCoord2d( 0.0, 1.0 );
		glVertex3d( Position.x + cross2.x, Position.y + cross2.y, Position.z + cross2.z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable (GL_BLEND);
	glDepthMask (GL_TRUE);
}


int GetFromRes(int image,int number)
{
	HBITMAP h;
	

	if (GetModuleHandle(0))
		h = (HBITMAP)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(image),IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	else
		h = (HBITMAP)LoadImage(0, MAKEINTRESOURCE(image), IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (h) 
	{
		DIBSECTION ds;
		GetObject(h, sizeof(ds), &ds);
		int sz=(ds.dsBmih.biWidth<ds.dsBmih.biHeight)?ds.dsBmih.biWidth:ds.dsBmih.biHeight;
		double d=log(sz)/log(2);
		int txbits = (int)floor(d+0.01);
		int txsize = 1 << txbits;
		DeleteObject(h);
		if (GetModuleHandle(0))
			h = (HBITMAP)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(image),IMAGE_BITMAP, txsize, txsize, LR_CREATEDIBSECTION);
		else
			h = (HBITMAP)LoadImage(0, MAKEINTRESOURCE(image), IMAGE_BITMAP,txsize, txsize, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(h, sizeof(ds), &ds);

		BITMAPINFOHEADER a = {
			sizeof(BITMAPINFOHEADER),
			txsize,
			-txsize,
			1,
			24,
			BI_RGB,
			3*txsize*txsize,  /* 3 BGR, 4 BGRA */
			0,
			0,
			0,
			0
			};
	
		HDC dc;

		dc=GetDC(NULL);

		unsigned char *texturebis = new unsigned char[a.biSizeImage];
		GetDIBits(dc, h, 0, txsize, texturebis, (BITMAPINFO *)&a,DIB_RGB_COLORS);
		
		glGenTextures(1, &texture[number]);  
		glBindTexture(GL_TEXTURE_2D, texture[number]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, txsize, txsize, GL_RGB, GL_UNSIGNED_BYTE, texturebis);
		DeleteObject(h);
		ReleaseDC(NULL,dc);
		return true;
	}
	else
	   return false;
}

void initGL(int width, int height)
{
	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	

	gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,1.0f,100.0f);

	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
}

void DrawFlr(void)
{
	int x,z;
	float da,db,dc,dd;

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	for(z=0;z<FLOORZ-1;z++)
	{
		for(x=0;x<FLOORX-1;x++)
		{
			da=sqrt( flr[x][z].x*flr[x][z].x+flr[x][z].z*flr[x][z].z );
			db=sqrt( flr[x+1][z].x*flr[x+1][z].x+flr[x+1][z].z*flr[x+1][z].z );
			dc=sqrt( flr[x+1][z+1].x*flr[x+1][z+1].x+flr[x+1][z+1].z*flr[x+1][z+1].z );
			dd=sqrt( flr[x][z+1].x*flr[x][z+1].x+flr[x][z+1].z*flr[x][z+1].z );

			da=1-da/8;
			db=1-db/8;
			dc=1-dc/8;
			dd=1-dd/8;

			glBegin(GL_QUADS);
				glColor3f(da,da,da);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(flr[x][z].x,flr[x][z].y,flr[x][z].z);
				glColor3f(db,db,db);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(flr[x+1][z].x,flr[x+1][z].y,flr[x+1][z].z);
				glColor3f(dc,dc,dc);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(flr[x+1][z+1].x,flr[x+1][z+1].y,flr[x+1][z+1].z);
				glColor3f(dd,dd,dd);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(flr[x][z+1].x,flr[x][z+1].y,flr[x][z+1].z);
			glEnd();
		}
	}
	glColor3f(1,1,1);
}

void InitRimb(float x,float y,float z)
{
	float dan=(float)360/8,an=0;
	float dx,dy,dz;
	int t,j;

	for(j=0;j<8;j++)
	{
		for(t=0;t<MAXPART;t++)
		{
			if( part[t].active<0 && part[t].rimb==false)
			{
				dx=(float)(rand()%100-rand()%100)/8000;
				dy=(float)(rand()%100-rand()%100)/2000;
				dz=(float)(rand()%100-rand()%100)/4000;
				an+=dan;
				part[t].x=x;
				part[t].y=0.2;
				part[t].z=z;
				part[t].dx=dx;
				part[t].dy=dy;
				part[t].dz=dz;
				part[t].rimb=true;
				part[t].active=TIMEPART;
				goto fuori;
			}
		}
	fuori:
	;
	}
}

void InitPart(void)
{
	int t,k;
	float dx,dy,dz,kf;

	for(t=0;t<MAXPART;t++)
	{
		if( part[t].active<0 && part[t].rimb==false)
		{
			k=rand()%4;

			switch(var.type)
			{
			case 0:
				part[t].active=TIMEPART;
				part[t].rimb=false;
				part[t].x=Puf[k].x;
				part[t].y=Puf[k].y;
				part[t].z=Puf[k].z;
				switch(k)
				{
				case 0:
					dx=(float)(rand()%100-rand()%100)/8000;
					dy=(float)(rand()%100)/2000;
					dz=(float)(rand()%100)/4000;
					break;
				case 1:
					dx=(float)(-rand()%100)/4000;
					dy=(float)(rand()%100)/2000;
					dz=(float)(rand()%100-rand()%100)/8000;
					break;
				case 2:
					dx=(float)(rand()%100-rand()%100)/8000;
					dy=(float)(rand()%100)/2000;
					dz=(float)(-rand()%100)/4000;
					break;
				case 3:
					dx=(float)(rand()%100)/4000;
					dy=(float)(rand()%100)/2000;
					dz=(float)(rand()%100-rand()%100)/8000;
					break;
				}
				break;
			case 1:
				part[t].active=TIMEPART;
				part[t].rimb=false;
				part[t].x=0;
				part[t].y=4.3;
				part[t].z=0;
				dx=(float)(rand()%100-rand()%100)/4000;
				dy=(float)(rand()%100)/3000;
				dz=(float)(rand()%100-rand()%100)/4000;
				break;
			case 2:
				part[t].active=TIMEPART;
				part[t].rimb=false;
				part[t].x=0;
				part[t].y=4.2;
				part[t].z=0;
				dx=(float)(rand()%100-rand()%100)/4000;
				dy=0;
				dz=(float)(rand()%100-rand()%100)/4000;
				break;
			case 3:
				part[t].active=TIMEPART;
				part[t].rimb=false;
				part[t].x=0;
				part[t].y=4.2;
				part[t].z=0;
				dx=cos(var.ant*3.141/180)/50;
				dy=0;
				dz=sin(var.ant*3.141/180)/50;
				var.ant++;
				if(var.ant>=360)
					var.ant-=360;
				break;
			case 4:
				part[t].active=TIMEPART;
				part[t].rimb=false;
				part[t].x=0;
				part[t].y=4.2;
				part[t].z=0;
				if((int)var.ant%2==0)
					kf=0;
				else
					kf=180;
				dx=cos((var.ant+kf)*3.141/180)/50;
				dy=0;
				dz=sin((var.ant+kf)*3.141/180)/50;
				var.ant++;
				if(var.ant>=360)
					var.ant-=360;
				break;
			}
			part[t].dx=dx;
			part[t].dy=dy;
			part[t].dz=dz;
			return;
		}
	}
}

void MovePart(int n)
{
	part[n].x+=part[n].dx;
	part[n].y+=part[n].dy;
	part[n].z+=part[n].dz;

	switch(var.type)
	{
	case 0:
		if(part[n].y<0.2)
		{
			part[n].active=-1;
			InitRimb(part[n].x,part[n].y,part[n].z);
			return;
		}
		break;
	case 1:
		if(part[n].y<0.2)
		{
			part[n].active=-1;
			InitRimb(part[n].x,part[n].y,part[n].z);
			return;
		}
		if(part[n].y<4.2 && part[n].x>-1 && part[n].x<1 && part[n].z>-1 && part[n].z<1)
		{
			part[n].dy=-part[n].dy;
			part[n].y+=part[n].dy;
		}
		break;
	case 2:
		if(part[n].y<0.2)
		{
			part[n].active=-1;
			InitRimb(part[n].x,part[n].y,part[n].z);
			return;
		}
		if(part[n].y<4.2 && part[n].x>-1 && part[n].x<1 && part[n].z>-1 && part[n].z<1)
		{
			part[n].dy=-part[n].dy;
			part[n].y+=part[n].dy;
		}
		break;
	case 3:
		if(part[n].y<0.2)
		{
			part[n].active=-1;
			InitRimb(part[n].x,part[n].y,part[n].z);
			return;
		}
		if(part[n].y<4.2 && part[n].x>-1 && part[n].x<1 && part[n].z>-1 && part[n].z<1)
		{
			part[n].dy=-part[n].dy;
			part[n].y+=part[n].dy;
		}
		break;
	case 4:
		if(part[n].y<0.2)
		{
			part[n].active=-1;
			InitRimb(part[n].x,part[n].y,part[n].z);
			return;
		}
		if(part[n].y<4.2 && part[n].x>-1 && part[n].x<1 && part[n].z>-1 && part[n].z<1)
		{
			part[n].dy=-part[n].dy;
			part[n].y+=part[n].dy;
		}
		break;
	}

	part[n].dy-=0.0005;

	part[n].active--;
}

void MoveRimb(int n)
{
	part[n].x+=part[n].dx;
	part[n].y+=part[n].dy;
	part[n].z+=part[n].dz;

	if(part[n].y<0.1)
	{
		part[n].dy=-part[n].dy;
		part[n].y+=part[n].dy;
	}

	part[n].dy-=0.0005;

	part[n].active--;
}

void DrawPart(void)
{
	int t;
	float col;

	for(t=0;t<MAXPART;t++)
	{
		if(part[t].rimb==false)
		{
			// 正常粒子
			if(part[t].active>=0)
			{
				col=1; 
	
				Luce(part[t].x,part[t].y,part[t].z,0.2,col,col,0,var.xc,var.yc,var.zc,2);

				MovePart(t);
			}
		}
		else
		{
			// 粒子爆炸
			if(part[t].active>=0)
			{
				col=(float)part[t].active/TIMEPART;
	
				Luce(part[t].x,part[t].y,part[t].z,0.1,col,col/3,0,var.xc,var.yc,var.zc,2);

				MoveRimb(t);
			}
			else
				part[t].rimb=false;
		}
	}
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	var.xc=8*cos(var.an*3.141/180);
	var.yc=8;
	var.zc=8*sin(var.an*3.141/180);
	var.an+=0.1;
	gluLookAt(var.xc,var.yc,var.zc,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);

	glPushMatrix();
	glTranslatef(0,0,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f,0.0f,0.0f);				// 左上
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f,4.0f,0.0f);				// 右上
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f,4.0f,0.0f);					// 右下
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f,0.0f,0.0f);					// 左下
	glEnd();
	glPushMatrix();
	glTranslatef(1,0,-1);
	glRotatef(90,0,1,0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f,0.0f,0.0f);				// 左上
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f,4.0f,0.0f);				// 右上
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f,4.0f,0.0f);					// 右下
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f,0.0f,0.0f);					// 左下
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1,0,-1);
	glRotatef(90,0,1,0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f,0.0f,0.0f);				// 左上
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f,4.0f,0.0f);				// 右上
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f,4.0f,0.0f);					// 右下
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f,0.0f,0.0f);					// 左下
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0,-2);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f,0.0f,0.0f);				// 左上
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f,4.0f,0.0f);				// 右上
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f,4.0f,0.0f);					// 右下
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f,0.0f,0.0f);					// 左下
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f,4.0f,0.0f);				// 左上
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f,4.0f,-2.0f);				// 右上
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f,4.0f,-2.0f);				// 右下
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f,4.0f,0.0f);					// 左下
	glEnd();
	glPopMatrix();

	DrawFlr();
	glDisable(GL_TEXTURE_2D);

	if(rand()%2==0)
		InitPart();
	DrawPart();
	
	glColor3f(1,1,1);

    glFlush();

	var.cn--;
	if(var.cn==0)
	{
		var.cn=MAXCN;
		var.type=(var.type+1)%MAXTYPE;
	}
}

void flrInit(void)
{
	int xi,zi;
	double x,z;

	for(zi=0;zi<FLOORZ;zi++)
	{
		z=((double)zi-(double)FLOORZ/2)*2;
		for(xi=0;xi<FLOORX;xi++)
		{
			x=((double)xi-(double)FLOORX/2)*2;
			flr[xi][zi].x=x;
			flr[xi][zi].y=0.05;
			flr[xi][zi].z=z;
		}
	}
}

void Init(void)
{
	int t;

	var.cn=MAXCN;
	var.type=0;	// 粒子初始化类型
	var.ant=0;
	var.xc=-5;
	var.yc=8;
	var.zc=10;
	var.an=0;
	
	Puf[0].x=0;
	Puf[0].y=2;
	Puf[0].z=1;
	Puf[1].x=-1;
	Puf[1].y=2;
	Puf[1].z=0;
	Puf[2].x=0;
	Puf[2].y=2;
	Puf[2].z=-1;
	Puf[3].x=1;
	Puf[3].y=2;
	Puf[3].z=0;

	flrInit();

	for(t=0;t<MAXPART;t++)
		part[t].active=-1;
}

BOOL VerifyPassword(HWND hwnd)
{
	OSVERSIONINFO osv;
	osv.dwOSVersionInfoSize = sizeof(osv);
	
	GetVersionEx(&osv);

	if( osv.dwPlatformId==VER_PLATFORM_WIN32_NT )
		return true;

	HINSTANCE hpwdcpl = ::LoadLibrary("PASSWORD.CPL");
	if( hpwdcpl==NULL )
		return true;

	typedef BOOL (WINAPI *VERIFYSCREENSAVEPWD)(HWND hwnd);
	VERIFYSCREENSAVEPWD VerifyScreenSavePwd;
	VerifyScreenSavePwd = (VERIFYSCREENSAVEPWD)GetProcAddress(hpwdcpl,"VerifyScreenSavePwd");

	if( VerifyScreenSavePwd==NULL )
	{
		FreeLibrary(hpwdcpl);
		return true;
	}
	
	BOOL bres = VerifyScreenSavePwd(hwnd);
	FreeLibrary(hpwdcpl);
	return bres;
}

void ChangePassword(HWND hwnd)
{
	HINSTANCE hmpr = ::LoadLibrary("MPR.DLL");
	if( hmpr==NULL )
		return;
	
	typedef VOID (WINAPI *PWDCHANGEPASSWORD) (LPCSTR lpcRegkeyname,HWND hwnd,UINT uiReserved1,UINT uiReserved2);
	PWDCHANGEPASSWORD PwdChangePassword=(PWDCHANGEPASSWORD)::GetProcAddress(hmpr,"PwdChangePasswordA");
	if( PwdChangePassword==NULL )
	{
		FreeLibrary(hmpr);
		return;
	}
	
	PwdChangePassword("SCRSAVE",hwnd,0,0); FreeLibrary(hmpr);
}

  
LRESULT CALLBACK SaverWindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
    static PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_CREATE:
		{
			ss->hwnd=hwnd;
			GetCursorPos(&(ss->InitCursorPos));
			ss->InitTime=GetTickCount();
		} break;
    case WM_ACTIVATE:
	case WM_ACTIVATEAPP:
	case WM_NCACTIVATE:
		{
			if( ScrMode==smSaver && !ss->IsDialogActive && LOWORD(wParam)==WA_INACTIVE )
				ss->CloseSaverWindow();
		} break;
	case WM_SETCURSOR:
		{
			if( ScrMode==smSaver && !ss->IsDialogActive )
				SetCursor(NULL);
			else
				SetCursor(LoadCursor(NULL,IDC_ARROW));
		} break;
    case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_KEYDOWN:
		{
			if( ScrMode==smSaver && !ss->IsDialogActive )
				ss->CloseSaverWindow();
		} break;
	case WM_MOUSEMOVE:
		{
			if( ScrMode==smSaver && !ss->IsDialogActive )
			{
				POINT pt;
				GetCursorPos(&pt);
				int dx = pt.x-ss->InitCursorPos.x;
				if( dx<0 )
					dx = -dx;
				int dy = pt.y-ss->InitCursorPos.y;
				if( dy<0 )
					dy = -dy;
				if( dx>(int)ss->MouseThreshold || dy>(int)ss->MouseThreshold )
					ss->CloseSaverWindow();
			}
		} break;
	case (WM_SYSCOMMAND):
		{
			if( ScrMode==smSaver )
			{
				if( wParam==SC_SCREENSAVE )
					return false;
				if( wParam==SC_CLOSE )
					return false;
			}
		} break;
	case (WM_CLOSE):
		{
			if( ScrMode==smSaver && ss->ReallyClose && !ss->IsDialogActive )
			{
				BOOL CanClose = true;
				if( GetTickCount()-ss->InitTime > 1000*ss->PasswordDelay )
				{
					ss->StartDialog();
					CanClose = VerifyPassword(hwnd);
					ss->EndDialog();
				}
				if( CanClose )
					DestroyWindow(hwnd);
			}
			if( ScrMode==smSaver )
				return false; 
		} break;
	case (WM_DESTROY):
		{
			if( ss->idTimer!=0 )
				KillTimer(hwnd,ss->idTimer);
			ss->idTimer=0;
			PostQuitMessage(0);
		} break;
  }
  return DefWindowProc(hwnd,msg,wParam,lParam);
}

void DoSaver(HWND hparwnd, int nCmdShow)
{
	int k;
	
	WNDCLASS wc;
	wc.style=CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc	= SaverWindowProc;
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hInstance	= hInstance;
	wc.hIcon		= NULL;
	wc.hCursor		= NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName	= NULL;
	wc.lpszClassName	= "OpenGL";

	if( !RegisterClass(&wc) ) {
		MessageBox(NULL, "RegisterClass() failed:  "
			"Cannot register window class.", "Error", MB_OK);
		return;
	}

	int cx, cy;
	if( ScrMode==smPreview )
	{
		RECT rc;
		GetWindowRect(hparwnd,&rc);
		cx = rc.right - rc.left;
		cy = rc.bottom - rc.top;
		hScrWindow =
			CreateWindow("OpenGL", "SaverWindow", WS_CHILD|WS_VISIBLE,0, 0, cx, cy, hparwnd, NULL, hInstance, NULL);
	}
	else
	{
		cx = GetSystemMetrics(SM_CXSCREEN);
		cy = GetSystemMetrics(SM_CYSCREEN);
		DWORD exstyle, style;

		exstyle = WS_EX_TOPMOST;
		style = WS_POPUP|WS_VISIBLE;

		hScrWindow = CreateWindow   ("OpenGL", "SaverWindow", style,0, 0, cx, cy, NULL, NULL, hInstance, NULL);

	}

	if( hScrWindow==NULL )
		return;

	UINT oldval;

	if( ScrMode==smSaver )
		SystemParametersInfo(SPI_SCREENSAVERRUNNING,1,&oldval,0);

	HDC hDC = GetDC(hScrWindow);

	static	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
	    1,                                // 版本号 
	    PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
	    PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
	    PFD_DOUBLEBUFFER,                 // 双缓存模式 
	    PFD_TYPE_RGBA,                    // RGBA 颜色模式 
	    24,                               // 24 位颜色深度 
	    0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
	    0,                                // 没有非透明度缓存 
	    0,                                // 忽略移位位 
	    0,                                // 无累加缓存 
	    0, 0, 0, 0,                       // 忽略累加位 
	    32,                               // 32 位深度缓存     
	    0,                                // 无模板缓存 
	    0,                                // 无辅助缓存 
	    PFD_MAIN_PLANE,                   // 主层 
	    0,                                // 保留 
	    0, 0, 0                           // 忽略层,可见性和损毁掩模 
	}; 		
	int pf = ChoosePixelFormat(hDC, &pfd);
    if (pf == 0) 
	{
		MessageBox(NULL, "ChoosePixelFormat() failed:  "
			"Cannot find a suitable pixel format.", "Error", MB_OK); 
		return;
    } 
	
    if (SetPixelFormat(hDC, pf, &pfd) == FALSE) 
	{
		MessageBox(NULL, "SetPixelFormat() failed:  "
			"Cannot set format specified.", "Error", MB_OK);
		return;
    } 

    DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	HGLRC hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);
	
	initGL(cx, cy);
	Init();
	
	glShadeModel(GL_SMOOTH);							// 光滑阴影
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// 黑色背景
	glClearDepth(1.0f);									// 清除深度缓存
	glEnable(GL_DEPTH_TEST);							// 使用深度缓存测试
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	k=GetFromRes(IDB_BITMAP1,0);	// 前表面纹理
	if(k==false)
		return;
	k=GetFromRes(IDB_BITMAP2,1);	// 上表面纹理
	if(k==false)
		return;
	k=GetFromRes(IDB_BITMAP3,2);	// 粒子纹理
	if(k==false)
		return;
	k=GetFromRes(IDB_BITMAP4,3);	// 地面纹理
	if(k==false)
		return;

	ShowWindow(hScrWindow, nCmdShow);
	
	MSG msg;

	bool done = false;
	while(!done)		
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)				// 是否受到QUIT消息
				done=TRUE;							// 是
			else									// 没有
			{
				TranslateMessage(&msg);	
				DispatchMessage(&msg);	
			}
		}
		else										// 如果没有消息
		{
			display();
			SwapBuffers(hDC);						// 交换缓冲区
		}
	}

	wglMakeCurrent(NULL, NULL);
    ReleaseDC(hScrWindow, hDC);
    wglDeleteContext(hRC);

	if( ScrMode==smSaver )
		SystemParametersInfo(SPI_SCREENSAVERRUNNING,0,&oldval,0);
	return;
}

BOOL CALLBACK ConfigDialogProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			CheckDlgButton(hwnd,IDC_FLASH,ss->Rotate);
			return true;
		}
    case WM_COMMAND:
		{
			int id=LOWORD(wParam);
			if( id==IDOK )
			{
				ss->Rotate = (IsDlgButtonChecked(hwnd,IDC_FLASH)==BST_CHECKED);
				ss->WriteConfigRegistry();
			}
			if( id==IDOK || id==IDCANCEL )
				EndDialog(hwnd,id);
		} break;
	}
	return false;
}

int WINAPI WinMain(HINSTANCE h, HINSTANCE,LPSTR,int nCmdShow)
{
	hInstance = h;
	char *c = GetCommandLine();
	if(*c == '\"' )
	{
		c++;
		while( *c!=0 && *c!='\"' )
			c++;
	}
	else
	{
		while( *c!=0 && *c!=' ' )
			c++;
	}
	
	if( *c!=0 )
		c++;
	
	while( *c==' ' )
		c++;

	HWND hwnd=NULL;
	if( *c==0 )
	{
		ScrMode = smConfig;
		hwnd=NULL;
	}
	else
	{
		if( *c=='-' || *c=='/' )
			c++;
		if( *c=='p' || *c=='P' || *c=='l' || *c=='L' )
		{
			c++;
			while( *c==' ' || *c==':' )
				c++;
			hwnd = (HWND)atoi(c);
			
			ScrMode = smPreview;
		}
		else if( *c=='s' || *c=='S' )
		{
			ScrMode=smSaver;
		}
		else if( *c=='c' || *c=='C' )
		{
			c++;
			while( *c==' ' || *c==':' )
				c++;
			if( *c==0 )
				hwnd = GetForegroundWindow();
			else
				hwnd = (HWND)atoi(c);
			ScrMode = smConfig;
		}
		else if( *c=='a' || *c=='A' )
		{
			c++;
			while( *c==' ' || *c==':' )
				c++;
			hwnd = (HWND)atoi(c);
			ScrMode = smPassword;
		}
	}
	// 生成一个新的屏幕保护环境
	ss = new TSaverSettings();
	ss->ReadGeneralRegistry();
	ss->ReadConfigRegistry();

	if( ScrMode==smPassword )
		ChangePassword(hwnd);
	if( ScrMode==smConfig )
		DialogBox(hInstance,MAKEINTRESOURCE(IDD_CONFIG_DIALOG),hwnd,ConfigDialogProc);
	if( ScrMode == smSaver || ScrMode==smPreview )
		DoSaver(hwnd, nCmdShow);
	delete ss;
	return 0;
}

