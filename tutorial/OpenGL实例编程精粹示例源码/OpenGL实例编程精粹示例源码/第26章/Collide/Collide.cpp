//=========================================================================
/**
*  @file      Collide.cpp
*
*  ��Ŀ������ ��ײ���
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-20
*
*  ����������������������¼����麯��
*																								
*	virtual bool Init();														
*		ִ�����еĳ�ʼ������������ɹ���������true							
*																			
*	virtual void Uninit();													
*		ִ�����е�ж�ع���										
*																			
*	virtual void Update(DWORD milliseconds);										
*		ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ
*																			
*	virtual void Draw();															
*		ִ�����еĻ��Ʋ���
*/
//=========================================================================
#include "stdafx.h"
#include "Collide.h"						    


///��ʼ�����������
Vector3 dir(0,0,-10);                     /**< ���� */
Vector3 pos(0,-50,1000);                  /**< λ�� */
float camera_rotation = 0;                /**< ��ת�ٶ� */

///��ʼ���������
Vector3 veloc(0.5,-0.1,0.5);              /**< �ٶ� */
Vector3 accel(0,-0.05,0);                 /**< �������ٶ� */

Vector3 ArrayVel[10];                     /**< �����������ٶ� */
Vector3 ArrayPos[10];                     /**< ����������λ�� */
Vector3 OldPos[10];                       /**< ������һ�����λ�� */

int NrOfBalls;                            /**< ������ĸ��� */
double Time = 0.6;                        /**< ����ģ���ʱ�侫�� */


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Test * test = new Test(class_name);
	return reinterpret_cast<GLApplication *>(test);
}

/** ���캯�� */
Test::Test(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
  m_Fps = 0;

}

/** ��ʼ������ */
void Test::InitVars()
{
	
	///����ƽ�� 
	pl1._Position = Vector3(0,-300,0);
	pl1._Normal = Vector3(0,1,0);
	pl2._Position = Vector3(300,0,0);
	pl2._Normal = Vector3(-1,0,0);
	pl3._Position = Vector3(-300,0,0);
	pl3._Normal = Vector3(1,0,0);
	pl4._Position = Vector3(0,0,300);
	pl4._Normal = Vector3(0,0,-1);
	pl5._Position = Vector3(0,0,-300);
	pl5._Normal = Vector3(0,0,1);


	///����Բ����
	cyl1._Position = Vector3(0,0,0);
	cyl1._Axis = Vector3(0,1,0);
	cyl1._Radius = 60 + 20;
	cyl2._Position = Vector3(200,-300,0);
	cyl2._Axis = Vector3(0,0,1);
	cyl2._Radius = 60 + 20;
	cyl3._Position = Vector3(-200,0,0);
	cyl3._Axis = Vector3(0,1,1);
    cyl3._Axis.unit();
	cyl3._Radius = 30 + 20;
	
	///������μ�����
	cylinder_obj = gluNewQuadric();
	gluQuadricTexture(cylinder_obj, GL_TRUE);

    ///������ĳ�ʼ����,����ʼ����ը����
	NrOfBalls = 10;
	ArrayVel[0] = veloc;
	ArrayPos[0] = Vector3(199,180,10);
	ExplosionArray[0]._Alpha = 0;
	ExplosionArray[0]._Scale = 1;
	ArrayVel[1] = veloc;
	ArrayPos[1] = Vector3(0,150,100);
	ExplosionArray[1]._Alpha = 0;
	ExplosionArray[1]._Scale = 1;
	ArrayVel[2] = veloc;
	ArrayPos[2] = Vector3(-100,180,-100);
	ExplosionArray[2]._Alpha = 0;
	ExplosionArray[2]._Scale = 1;
	for (int i = 3; i < 10; i++)
	{
         ArrayVel[i] = veloc;
	     ArrayPos[i] = Vector3(-500 + i*75, 300, -500 + i*50);
		 ExplosionArray[i]._Alpha = 0;
	     ExplosionArray[i]._Scale = 1;
	}
	for (int i = 10; i < 20; i++)
	{
         ExplosionArray[i]._Alpha = 0;
	     ExplosionArray[i]._Scale = 1;
	}
}

/** �������� */
bool Test::LoadTexture()
{
	glEnable(GL_TEXTURE_2D);                                      /**< ��������ӳ�� */
	char* file[] = {"data/marble.bmp","data/spark.bmp","data/boden.bmp","data/wand.bmp"};
	
	/** ѭ������λͼ���� */
	for(int i = 0; i < 4; i++)
	{
		if(!m_texture[i].LoadBitmap(file[i]))                    /**< ����λͼ�ļ� */
		{
			MessageBox(NULL,"װ��λͼ�ļ�ʧ�ܣ�","����",MB_OK);  /**< �������ʧ���򵯳��Ի��� */
			return false;
		}
		glGenTextures(1, &m_texture[i].ID);                      /**< ����һ������������� */
		 
		glBindTexture(GL_TEXTURE_2D, m_texture[i].ID);            /**< ����������� */
		
		/** �����˲� */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		
		/** �������� */
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture[i].imageWidth,
						m_texture[i].imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
						m_texture[i].image);
	}
	return true;
}

/** ��ʼ��OpenGL */
bool Test::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0,0,0,0);
  	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  

	 ///���ù�Դ����
	GLfloat spec[] = { 1.0, 1.0 ,1.0 ,1.0 };      
	GLfloat posl[] = { 0, 400, 0, 1 };               
	GLfloat amb[]  = { 0.2f, 0.2f, 0.2f ,1.0f };   
	GLfloat amb2[] = { 0.3f, 0.3f, 0.3f ,1.0f };  
	float df=100.0;

	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);		
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);						
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

	/** ���ò������� */
	glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
	glMaterialfv(GL_FRONT,GL_SHININESS,&df);

	/** ���ù�Դ */
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_POSITION,posl);
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb2);
	glEnable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
   
	/** ������� */
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
   	
	/** ��������ӳ�䣬���������� */
	glEnable(GL_TEXTURE_2D);
    LoadTexture();

	/** ���������ഹֱ��ƽ��ģ�ⱬըЧ�� */
    glNewList( dlist = glGenLists(1), GL_COMPILE);  /**< ������ʾ�б� */
    glBegin(GL_QUADS);
	glRotatef(-45,0,1,0);
	glNormal3f(0,0,1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-50,-40,0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(50,-40,0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(50,40,0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-50,40,0);
    glNormal3f(0,0,-1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-50,40,0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(50,40,0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(50,-40,0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-50,-40,0);

	glNormal3f(1,0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,-40,50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0,-40,-50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0,40,-50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0,40,50);
    glNormal3f(-1,0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0,40,50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0,40,-50);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0,-40,-50);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0,-40,50);
	glEnd();
    glEndList();                                   /**< ������ʾ�б��� */

	/** ��ʼ������ */
	InitVars();    

	/** ��ʼ������ */
	if(!m_Font.InitFont())
		MessageBox(NULL,"��ʼ������ʧ��!","����",MB_OK);

	ResizeDraw(true);

	return true;                                            /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Test::Uninit()									
{
	for(int i=0; i < 4; i++) 
	{
		m_texture[i].FreeImage();               /**< �ͷ�����ͼ��ռ�õ��ڴ� */
	    glDeleteTextures(1, &m_texture[i].ID);  /**< ɾ��������� */
	}
	
	/** �ͷŶ��ζ��� */
	if(cylinder_obj != NULL)
		gluDeleteQuadric(cylinder_obj);
}

/** ������º��� */
void Test::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}

    
}

/** ����֡�� */
void Test::CaculateFrameRate()
{
	static float framesPerSecond    = 0.0f;	     /**< ������ʾ֡�� */	
    static float lastTime			= 0.0f;	     /**< ��¼�ϴ�ʱ�� */						
    float currentTime = GetTickCount() * 0.001f; /**< ��õ�ǰʱ�� */	 			

	++framesPerSecond;                           /**< ��ʾ֡������1 */
    /** ���ʱ������1.0�� */
	if( currentTime - lastTime > 1.0f )          
    {
		
	    lastTime = currentTime;                   /**< ���浱ǰʱ�� */
		m_Fps = framesPerSecond;                  /**< ��ǰ֡������m_Fps */
        framesPerSecond = 0;                      /**< ��֡������ */                    
    }
}

/** ���������Ϣ */
void  Test::PrintText()
{
	char string[128];                               /**< ���ڱ�������ַ��� */
	glPushAttrib(GL_CURRENT_BIT);                   /**< ����������ɫ������Ϣ */
	glColor3f(0.0f,1.0f,0.0f);                      /**< ����������ɫ */
	
	/** ���֡�� */
	CaculateFrameRate();                               /**< ����֡�� */
    sprintf(string,"FPS:%3.0f",m_Fps);                 /**< �ַ�����ֵ */
	m_Font.PrintText(string, -5.0f,3.0f);              /**< ����ַ��� */
	glPopAttrib();
		
}

/** ����Ƿ���ƽ����ײ */
int Test::TestIntersionPlane(const Plane& plane,const Vector3& position,const Vector3& direction, double& lamda, Vector3& pNormal)
{
	double dotProduct = direction.dot(plane._Normal);
	double l2;

    ///�ж��Ƿ�ƽ����ƽ��
    if ((dotProduct < ZERO) && (dotProduct > -ZERO)) 
		return 0;

    l2 = (plane._Normal.dot(plane._Position - position))/dotProduct;

	///�����������෴���򣬴�ʱ��������ײ
    if (l2 < -ZERO) 
		return 0;

    pNormal = plane._Normal;
	lamda = l2;
    return 1;
}

/** ����Ƿ���Բ������ײ */
int Test::TestIntersionCylinder(const Cylinder& cylinder,const Vector3& position,const Vector3& direction, double& lamda, Vector3& pNormal,Vector3& newposition)
{
	Vector3 RC;
	double d;
	double t,s;
	Vector3 n,D,O;
	double ln;
	double in,out;
	

	Vector3::subtract(position,cylinder._Position,RC);
	Vector3::cross(direction,cylinder._Axis,n);

    ln = n.mag();

	if ( (ln<ZERO)&&(ln>-ZERO) ) return 0;

	n.unit();

	d =  fabs( RC.dot(n) );

    if (d <= cylinder._Radius)
	{
		Vector3::cross(RC,cylinder._Axis,O);
		t =  - O.dot(n)/ln;
		Vector3::cross(n,cylinder._Axis,O);
		O.unit();
		s =  fabs( sqrt(cylinder._Radius*cylinder._Radius - d*d) / direction.dot(O) );

		in = t-s;
		out = t+s;

		if (in<-ZERO){
			if (out<-ZERO) return 0;
			else lamda = out;
		}
		else
        if (out<-ZERO) {
			      lamda = in;
		}
		else
		if (in<out) lamda = in;
		else lamda = out;

    	newposition = position+direction*lamda;
		Vector3 HB = newposition-cylinder._Position;
		pNormal = HB - cylinder._Axis*(HB.dot(cylinder._Axis));
		pNormal.unit();

		return 1;
	}
    
	return 0;
}

int Test::FindBallCol(Vector3& point, double& TimePoint, double Time2, int& BallNr1, int& BallNr2)
{
	Vector3 RelativeV;
	TRay rays;
	double MyTime = 0.0, Add = Time2/150.0, Timedummy = 10000, Timedummy2 = -1;
	Vector3 posi;
	
	///�ж�������Ƿ��ཻ
	for (int i = 0;i<NrOfBalls-1;i++)
	{
	 for (int j = i+1;j<NrOfBalls;j++)
	 {	
		    RelativeV = ArrayVel[i]-ArrayVel[j];
			rays = TRay(OldPos[i],Vector3::unit(RelativeV));
			MyTime = 0.0;

			if ( (rays.dist(OldPos[j])) > 40) continue; 

			while (MyTime<Time2)
			{
			   MyTime += Add;
			   posi = OldPos[i]+RelativeV*MyTime;
			   if (posi.dist(OldPos[j]) <= 40) {
										   point = posi;
										   if (Timedummy>(MyTime-Add)) Timedummy = MyTime-Add;
										   BallNr1 = i;
										   BallNr2 = j;
										   break;
										}
			
			}
	 }

	}

	if (Timedummy != 10000) { TimePoint = Timedummy;
	                        return 1;
	}

	return 0;
}

/** ��Ҫ�Ĵ������ */
void Test::process()
{
	 double rt,rt2,rt4,lamda = 10000;
  Vector3 norm,uveloc;
  Vector3 normal,point,time;
  double RestTime,BallTime;
  Vector3 Pos2;
  int BallNr = 0,dummy = 0,BallColNr1,BallColNr2;
  Vector3 Nc;

  ///���û�����������ϣ���ת�����
 // if (!hook_toball1)
 // {
	  camera_rotation += 0.1f;
	  if (camera_rotation>360)
		  camera_rotation = 0;
 // }
 
	  RestTime = Time;
	  lamda = 1000;

	///�����������ٶ�
	for (int j = 0;j<NrOfBalls;j++)
	  ArrayVel[j] += accel*RestTime;

	///�����һ����ģ��ʱ����(������������㣬����������)
	while (RestTime>ZERO)
	{
	   lamda = 10000;   
	
	   ///����ÿ�����ҵ������������ײ��
   	   for (int i = 0;i<NrOfBalls;i++)
	   {
		      ///�����µ�λ�ú��ƶ��ľ���
			  OldPos[i] = ArrayPos[i];
			  Vector3::unit(ArrayVel[i],uveloc);
			  ArrayPos[i] = ArrayPos[i]+ArrayVel[i]*RestTime;
			  rt2 = OldPos[i].dist(ArrayPos[i]);

			  ///�����Ƿ��ǽ����ײ
			  if (TestIntersionPlane(pl1,OldPos[i],uveloc,rt,norm))
			  {  
				  ///������ײ��ʱ��
				  rt4 = rt*RestTime/rt2;

				  ///���С�ڵ�ǰ�������ײʱ�䣬�������
				  if (rt4 <= lamda)
				  { 
				    if (rt4 <= RestTime+ZERO)
						 if (! ((rt <= ZERO)&&(uveloc.dot(norm)>ZERO)) )
						  {
							normal = norm;
							point = OldPos[i]+uveloc*rt;
							lamda = rt4;
							BallNr = i;
						  }
				  }
			  }
			  
			  if (TestIntersionPlane(pl2,OldPos[i],uveloc,rt,norm))
			  {
				   rt4 = rt*RestTime/rt2;

				  if (rt4 <= lamda)
				  { 
				    if (rt4 <= RestTime+ZERO)
						if (! ((rt <= ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal = norm;
							point = OldPos[i]+uveloc*rt;
							lamda = rt4;
							BallNr = i;
							dummy = 1;
						 }
				  }
				 
			  }

			  if (TestIntersionPlane(pl3,OldPos[i],uveloc,rt,norm))
			  {
			      rt4 = rt*RestTime/rt2;

				  if (rt4 <= lamda)
				  { 
				    if (rt4 <= RestTime+ZERO)
						if (! ((rt <= ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal = norm;
							point = OldPos[i]+uveloc*rt;
							lamda = rt4;
							BallNr = i;
						 }
				  }
			  }

			  if (TestIntersionPlane(pl4,OldPos[i],uveloc,rt,norm))
			  {
				  rt4 = rt*RestTime/rt2;

				  if (rt4 <= lamda)
				  { 
				    if (rt4 <= RestTime+ZERO)
						if (! ((rt <= ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal = norm;
							point = OldPos[i]+uveloc*rt;
							lamda = rt4;
							BallNr = i;
						 }
				  }
			  }

			  if (TestIntersionPlane(pl5,OldPos[i],uveloc,rt,norm))
			  {
				  rt4 = rt*RestTime/rt2;

				  if (rt4 <= lamda)
				  { 
				    if (rt4 <= RestTime+ZERO)
						if (! ((rt <= ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal = norm;
							point = OldPos[i]+uveloc*rt;
							lamda = rt4;
							BallNr = i;
						 }
				  }
			  }

              ///�����Ƿ�������Բ������
			  if (TestIntersionCylinder(cyl1,OldPos[i],uveloc,rt,norm,Nc))
			  {
				  rt4 = rt*RestTime/rt2;

				  if (rt4 <= lamda)
				  { 
				    if (rt4 <= RestTime+ZERO)
						if (! ((rt <= ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal = norm;
							point = Nc;
							lamda = rt4;
							BallNr = i;
						 }
				  }
				 
			  }
			  if (TestIntersionCylinder(cyl2,OldPos[i],uveloc,rt,norm,Nc))
			  {
				  rt4 = rt*RestTime/rt2;

				  if (rt4 <= lamda)
				  { 
				    if (rt4 <= RestTime+ZERO)
						if (! ((rt <= ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal = norm;
							point = Nc;
							lamda = rt4;
							BallNr = i;
						 }
				  }
				 
			  }
			  if (TestIntersionCylinder(cyl3,OldPos[i],uveloc,rt,norm,Nc))
			  {
				  rt4 = rt*RestTime/rt2;

				  if (rt4 <= lamda)
				  { 
				    if (rt4 <= RestTime+ZERO)
						if (! ((rt <= ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal = norm;
							point = Nc;
							lamda = rt4;
							BallNr = i;
						 }
				  }
				 
			  }
	   }


	   ///����ÿ����֮�����ײ�������ײʱ��С�����������ײ�����滻����
	   if (FindBallCol(Pos2,BallTime,RestTime,BallColNr1,BallColNr2))
	   {
						      
				  if ( (lamda == 10000) || (lamda>BallTime) )
				  {
					  RestTime = RestTime-BallTime;

					  Vector3 pb1,pb2,xaxis,U1x,U1y,U2x,U2y,V1x,V1y,V2x,V2y;
					  double a,b;

					  pb1 = OldPos[BallColNr1]+ArrayVel[BallColNr1]*BallTime;
					  pb2 = OldPos[BallColNr2]+ArrayVel[BallColNr2]*BallTime;
					  xaxis = (pb2-pb1).unit();

					  a = xaxis.dot(ArrayVel[BallColNr1]);
					  U1x = xaxis*a;
					  U1y = ArrayVel[BallColNr1]-U1x;

					  xaxis = (pb1-pb2).unit();
					  b = xaxis.dot(ArrayVel[BallColNr2]);
      				  U2x = xaxis*b;
					  U2y = ArrayVel[BallColNr2]-U2x;

					  V1x = (U1x+U2x-(U1x-U2x))*0.5;
					  V2x = (U1x+U2x-(U2x-U1x))*0.5;
					  V1y = U1y;
					  V2y = U2y;

					  for (int j = 0;j<NrOfBalls;j++)
					  ArrayPos[j] = OldPos[j]+ArrayVel[j]*BallTime;

					  ArrayVel[BallColNr1] = V1x+V1y;
					  ArrayVel[BallColNr2] = V2x+V2y;

					  ///���±�ը����
                      for(int j = 0;j<20;j++)
					  {
						  if (ExplosionArray[j]._Alpha <= 0)
						  {
							  ExplosionArray[j]._Alpha = 1;
                              ExplosionArray[j]._Position = ArrayPos[BallColNr1];
							  ExplosionArray[j]._Scale = 1;
							  break;
						  }
					  }

					  continue;
				  }
		}
  
	    ///���Ĳ��ԣ��滻�´���ײ��ʱ�䣬�����±�ըЧ��������
		if (lamda!= 10000)
		{		 
			RestTime -= lamda;

			for (int j = 0;j<NrOfBalls;j++)
			ArrayPos[j] = OldPos[j]+ArrayVel[j]*lamda;

			rt2 = ArrayVel[BallNr].mag();
			ArrayVel[BallNr].unit();
			ArrayVel[BallNr] = Vector3::unit( (normal*(2*normal.dot(-ArrayVel[BallNr]))) + ArrayVel[BallNr] );
			ArrayVel[BallNr] = ArrayVel[BallNr]*rt2;
				
			for(int j = 0;j<20;j++)
			{
			  if (ExplosionArray[j]._Alpha <= 0)
			  {
				  ExplosionArray[j]._Alpha = 1;
                  ExplosionArray[j]._Position = point;
				  ExplosionArray[j]._Scale = 1;
				  break;
			  }
			}
		}
		else
			RestTime = 0;

	}
}

/** ���ƺ��� */
void Test::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);			
	glLoadIdentity();

	process();  /** ����ģ�� */

	int i;
	 	
	///�������������̶���
	gluLookAt(pos.x,pos.y,pos.z, pos.x+dir.x,pos.y+dir.y,pos.z+dir.z, 0,1.0,0.0);
	
	glRotatef(camera_rotation,0,1,0);

	///��Ⱦ��
	for (i = 0;i<NrOfBalls;i++)
	{
		switch(i)
		{
			case 1: glColor3f(1.0f,1.0f,1.0f);
					break;
			case 2: glColor3f(1.0f,1.0f,0.0f);
					break;
			case 3: glColor3f(0.0f,1.0f,1.0f);
					break;
			case 4: glColor3f(0.0f,1.0f,0.0f);
					break;
			case 5: glColor3f(0.0f,0.0f,1.0f);
					break;
			case 6: glColor3f(0.65f,0.2f,0.3f);
					break;
			case 7: glColor3f(1.0f,0.0f,1.0f);
					break;
			case 8: glColor3f(0.0f,0.7f,0.4f);
					break;
			default: glColor3f(1.0f,0,0);
		}
		glPushMatrix();
		glTranslated(ArrayPos[i].x,ArrayPos[i].y,ArrayPos[i].z);
		gluSphere(cylinder_obj,20,20,20);
		glPopMatrix();
	}
	
	/** ��������ӳ�� */
	glEnable(GL_TEXTURE_2D);
	///��Ⱦǽ��
	glBindTexture(GL_TEXTURE_2D, m_texture[3].ID); 
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(320,320,320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(320,-320,320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-320,-320,320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-320,320,320);
        
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-320,320,-320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-320,-320,-320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(320,-320,-320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(320,320,-320);
    
	glTexCoord2f(1.0f, 0.0f); glVertex3f(320,320,-320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(320,-320,-320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(320,-320,320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(320,320,320);
	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-320,320,320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-320,-320,320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-320,-320,-320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-320,320,-320);
	glEnd();

	///��Ⱦ����
	glBindTexture(GL_TEXTURE_2D, m_texture[2].ID); 
    glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-320,-320,320);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(320,-320,320);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(320,-320,-320);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-320,-320,-320);
	glEnd();

    ///��ȾԲ��
	glBindTexture(GL_TEXTURE_2D, m_texture[0].ID);   
	glColor3f(0.5,0.5,0.5);
    glPushMatrix();
	glRotatef(90, 1,0,0);
	glTranslatef(0,0,-500);
	gluCylinder(cylinder_obj, 60, 60, 1000, 20, 2);
	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(200,-300,-500);
	gluCylinder(cylinder_obj, 60, 60, 1000, 20, 2);
	glPopMatrix();

	glPushMatrix();
    glTranslatef(-200,0,0);
	glRotatef(135, 1,0,0);
	glTranslatef(0,0,-500);
	gluCylinder(cylinder_obj, 30, 30, 1000, 20, 2);
	glPopMatrix();
	
	///��Ⱦ��ı�ըЧ��
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, m_texture[1].ID);   
	for(i = 0; i < 20; i++)
	{
		if(ExplosionArray[i]._Alpha >= 0)
		{
		   glPushMatrix();
           ExplosionArray[i]._Alpha -= 0.01f;
		   ExplosionArray[i]._Scale += 0.03f;
		   glColor4f(1,1,0,ExplosionArray[i]._Alpha);	 
		   glScalef(ExplosionArray[i]._Scale,ExplosionArray[i]._Scale,ExplosionArray[i]._Scale);
           glTranslatef((float)ExplosionArray[i]._Position.x/ExplosionArray[i]._Scale, 
			            (float)ExplosionArray[i]._Position.y/ExplosionArray[i]._Scale, 
						(float)ExplosionArray[i]._Position.z/ExplosionArray[i]._Scale);
           glCallList(dlist);
	       glPopMatrix();
		}
	}

	/** �ָ�һЩ���� */
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
   
	/** �����Ļ��Ϣ */ 
	PrintText();
    
	/** ǿ��ִ�����е�OpenGL���� */
	glFlush();	                 
}
