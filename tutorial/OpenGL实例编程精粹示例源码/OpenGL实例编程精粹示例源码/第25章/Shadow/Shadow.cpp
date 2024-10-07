//=========================================================================
/**
*  @file      Shadow.cpp
*
*  ��Ŀ������ ƽ����Ӱ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-02
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
#include "Shadow.h"						    


/** ����һЩ���� */
float lightPos[4] = {0.0f, 0.0f, 13.0f, 1.0f};  /**< ��Դλ�� */
float direction = -0.06f;                       /**< X�����ƶ����� */

/** ������Щ��������3�����λ�� */
float objPos1;
float objPos2;
float objPos3;

float obj1 = -0.01f;
float obj2 = -0.02f;
float obj3 = -0.03f;


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

/** ��ʼ��OpenGL */
bool Test::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.2f, 0.2f, 0.2f, 0.5f);						
	glClearDepth(1.0f);											
	glEnable(GL_DEPTH_TEST);
	ResizeDraw(true);	                             /**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */

	/** ���ù�Դ���� */
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	

	/** ��ʼ������ */
	if(!m_Font.InitFont())
		MessageBox(NULL,"��ʼ������ʧ��!","����",MB_OK);
 
	float size = 6.0f;	      /**< ����ǽ�ı߳� */
	Wall wall;                /**< ����ṹ�� */
	
	///��������
	wall.vVerts.clear();									/**< ��ն������� */
	wall.vNormal = Vector3(1, 0, 0);						/**< ���÷����� */
	wall.vVerts.push_back(Vector3(-size, size, size));		/**< ���涨�嶥�� */
	wall.vVerts.push_back(Vector3(-size, -size, size));	
	wall.vVerts.push_back(Vector3(-size, -size, 0));		
	wall.vVerts.push_back(Vector3(-size, size, 0));		
	wall.vColor = Vector3(1, 0, 0);						    /**< ָ����ɫ */
	walls.push_back(wall);								    /**< ��Ӹ��浽������ */

	///��������
	wall.vVerts.clear();									/**< ��ն������� */
	wall.vNormal = Vector3(-1, 0, 0);						/**< ���÷����� */
	wall.vVerts.push_back(Vector3(size, size, 0));			/**< ���涨�嶥�� */
	wall.vVerts.push_back(Vector3(size, -size, 0));		
	wall.vVerts.push_back(Vector3(size, -size, size));		
	wall.vVerts.push_back(Vector3(size, size, size));		
	wall.vColor = Vector3(0, 0, 1);						    /**< ָ����ɫ */
	walls.push_back(wall);								    /**< ��Ӹ��浽������ */
	
	
	///��������
	wall.vVerts.clear();									/**< ��ն������� */
	wall.vNormal = Vector3(0, 1, 0);						/**< ���÷����� */
	wall.vVerts.push_back(Vector3(size, -size, size));		/**< ���涨�嶥�� */
	wall.vVerts.push_back(Vector3(size, -size, 0));		
	wall.vVerts.push_back(Vector3(-size, -size, 0));		
	wall.vVerts.push_back(Vector3(-size, -size, size));	
	wall.vColor = Vector3(0, 1, 0);						    /**< ָ����ɫ */
	walls.push_back(wall);								    /**< ��Ӹ��浽������ */

	///��������
	wall.vVerts.clear();									/**< ��ն������� */
	wall.vNormal = Vector3(0, -1, 0);						/**< ���÷����� */
	wall.vVerts.push_back(Vector3(size, size, size));		/**< ���涨�嶥�� */
	wall.vVerts.push_back(Vector3(size, size, 0));		
	wall.vVerts.push_back(Vector3(-size,size, 0));		
	wall.vVerts.push_back(Vector3(-size,size, size));	
	wall.vColor = Vector3(0, 1, 1);						    /**< ָ����ɫ */
	walls.push_back(wall);								    /**< ��Ӹ��浽������ */
	
	///��������
	wall.vVerts.clear();									/**< ��ն������� */
	wall.vNormal = Vector3(0, 0, 1);						/**< ���÷����� */
	wall.vVerts.push_back(Vector3(-size, size, 0));		    /**< ���涨�嶥�� */
	wall.vVerts.push_back(Vector3(-size, -size, 0));		
	wall.vVerts.push_back(Vector3(size, -size, 0));		
	wall.vVerts.push_back(Vector3(size, size, 0));			
	wall.vColor = Vector3(1, 0, 1);						    /**< ָ����ɫ */
	walls.push_back(wall);	                                /**< ��Ӹ��浽������ */
	

	return true;                                            /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Test::Uninit()									
{
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

/** ����ǽ�� */
void Test::RenderWall(const Wall& wall)
{
	glPushMatrix();
	    /** ��ʼ���� */
		glBegin(GL_QUADS);
			
			/** ָ������ */
			glNormal3f(wall.vNormal.x, wall.vNormal.y, wall.vNormal.z);

			/** ָ����ɫ */
			glColor4f(wall.vColor.x, wall.vColor.y, wall.vColor.z, 1.0);

			/** ָ������ */			 
			for(int i = 0; i < (int)wall.vVerts.size(); i++)
			{
				glVertex3f(wall.vVerts[i].x, wall.vVerts[i].y, wall.vVerts[i].z);
			}

		/** ���ƽ��� */
		glEnd();

	glPopMatrix();

}

/** �������� */
void Test::RenderObjects()
{
	/** ����һ�����ζ���ָ�� */
    GLUquadricObj *pObj = gluNewQuadric();			
	gluQuadricDrawStyle(pObj, GLU_FILL);
	

	/** ��������1 */
	glColor4f(0.0f, 1.0f, 0.0f, 1.0);    /**< ָ����ɫ */

	glPushMatrix();
		glTranslatef(-3.0f, objPos1, 4.0f);
		gluSphere(pObj, 0.5f, 75, 75);
	glPopMatrix();
	

	/** ��������2 */
	glColor4f(1.0f, 1.0f, 0.1f, 1.0);   /**< ָ����ɫ */

	glPushMatrix();
		glTranslatef(3, objPos2, 4);
		gluSphere(pObj, 0.5f, 75, 75);
	glPopMatrix();

	
	/** ��������3 */
	glColor4f(0.0f, 0.0f, 1.0f, 1.0);   /**< ָ����ɫ */
	glPushMatrix();
		glTranslatef(0, objPos3, 4);
		gluSphere(pObj, 0.5f, 75, 75);
	glPopMatrix();

	/** �����Ƕ�����λ�ý����޶� */
	///����1
	if(objPos1 < -4.5f)
	{
		obj1 = obj1 * -1;
		objPos1 = -4.5f; 
	}
	if(objPos1 > 4.5f)
	{
		obj1 = obj1 * -1;
		objPos1 = 4.5f; 
	}
	
	///����2
	if(objPos2 < -4.5f)
	{
		obj2 = obj2 * -1;
		objPos2 = -4.5f; 
	}
	if(objPos2 > 4.5f)
	{
		obj2 = obj2 * -1;
		objPos2 = 4.5f; 
	}	

	///����3
	if(objPos3 < -4.5f)
	{
		obj3 = obj3 * -1;
		objPos3 = -4.5f; 
	}
	if(objPos3 > 4.5f)
	{
		obj3 = obj3 * -1;
		objPos3 = 4.5f; 
	}	
	
	/** ����λ�� */
	objPos1 += obj1;
	objPos2 += obj2;
	objPos3 += obj3;

	/** �ָ���ɫ */
	glColor4f(1.0f, 1.0f, 1.0f, 1.0);

	/** ɾ�����ζ��� */
	gluDeleteQuadric(pObj);

}

/** ���ƹ�Դ */
void Test::RenderLight()
{
	/** �رչ��� */
	glDisable(GL_LIGHTING);

	glPushMatrix();
		GLUquadricObj *pObj = gluNewQuadric();				/**< �������ζ��� */
		gluQuadricDrawStyle(pObj, GLU_FILL);				

		///�ڹ�Դλ�ô�����һ����ɫС��
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
		glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
		gluSphere(pObj, 0.03f, 25, 25);
		
		gluDeleteQuadric(pObj);								/**< ɾ�����ζ��� */
	glPopMatrix();

	/** �������� */
	glEnable(GL_LIGHTING);

	/** �Թ�Դλ���ƶ�λ�úͷ�����и��� */
	if(lightPos[0] < -8.0f)
	{
		direction = direction * -1;
		lightPos[0] = -8.0f; 
	}
	if(lightPos[0] > 8.0f)
	{
		direction = direction * -1;
		lightPos[0] = 8.0f; 
	}	

	/** ���¹�Դλ�� */
	lightPos[0] += direction;
	glLightfv( GL_LIGHT0, GL_POSITION, lightPos );
}

/** ����Ͷ����� */
void Test::CreateShadowMatrix(float m[16], Vector3 point, Vector3 normal, float lp[4])
{
	/** ���㶥�㵽ƽ��ľ��� */
	float d = - ((normal.x * point.x) + (normal.y * point.y) + (normal.z * point.z));
	
	/** �����Դ�����ͷ������ĵ�� */
	float dot = normal.x*lp[0]  + normal.y*lp[1] + normal.z*lp[2] + d*lp[3];

	/** ���þ���Ԫ��ֵ */
	m[0]  = dot - lp[0]*normal.x;  m[1]  =	   -lp[1]*normal.x;	 m[2]  =      -lp[2]*normal.x;  m[3]  =	    -lp[3]*normal.x;
	m[4]  =		 -lp[0]*normal.y;  m[5]  = dot -lp[1]*normal.y;  m[6]  =	  -lp[2]*normal.y;  m[7]  =	    -lp[3]*normal.y;
	m[8]  =		 -lp[0]*normal.z;  m[9]  =	   -lp[1]*normal.z;	 m[10] = dot  - lp[2]*normal.z; m[11] =	    -lp[3]*normal.z;
	m[12] =		 -lp[0]*d;	       m[13] =	   -lp[1]*d;		 m[14] =	  -lp[2]*d;	        m[15] = dot -lp[3]*d;

}

/** ��Ⱦǽ�����Ӱ */
void  Test::Render()
{
	glClear(GL_STENCIL_BUFFER_BIT);							/**< ���ģ�滺�� */
	glEnable(GL_STENCIL_TEST);								/**< ��ʼģ����� */

	/** ѭ������ÿ��ǽ�� */
	for(int i = 0; i < (int)walls.size(); i++)
	{
		glStencilFunc(GL_ALWAYS, 1, 1);						/**< ����ÿ������ģ��ֵΪ1 */
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);			

		/** ���Ƶ�ǰǽ�� */
		glDisable(GL_LIGHT0);							
		RenderWall(walls[i]);								
		glEnable(GL_LIGHT0);                          

		glDisable(GL_DEPTH_TEST);							/**< �ر���Ȳ��� */
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);/**< ��ֹ��ɫ����д */
		glStencilFunc(GL_EQUAL, 1, 1);                      /**< ����ģ��ֵΪ1������ */
		glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);             /**< ģ��ֵ��1 */

		/** ��ʼͶ����Ӱ */
		glPushMatrix();

			/** ����Ͷ����� */
			float m[16] = {0};								
			CreateShadowMatrix(m, walls[i].vVerts[0], walls[i].vNormal, lightPos);
			glMultMatrixf(m);

			/** ��������,�õ���Ӱ */
			glPushMatrix();
			    RenderObjects();
			glPopMatrix();

		glPopMatrix();

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);	/**< �ָ���ɫ����д */

		RenderWall(walls[i]);								/**< ���Ƴ���Ӱ��Ĳ��� */
		glEnable(GL_DEPTH_TEST);							/**< ��ʼ��Ȳ��� */
	}

	/** �ر�ģ����� */
	glDisable(GL_STENCIL_TEST);  				

}
/** ���ƺ��� */
void Test::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();
    glTranslatef(0.0f,0.0f,-18.0f);
	
	/** �������� */
	RenderObjects();
	
	/** ��Ⱦǽ�����Ӱ */
	Render();

	/** ���ƹ�Դ */
	RenderLight();

	/** �����Ļ��Ϣ */ 
	PrintText();
		
	glFlush();	                 /**< ǿ��ִ�����е�OpenGL���� */
}
