//=========================================================================
/**
*  @file      BoneAnimation.cpp
*
*  ��Ŀ������ ��������
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-29
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
#include "BoneAnimation.h"						    

/** ���Ƴ�����ת */
extern float xRotation ;
extern float yRotation ;

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

}


/** ��ʼ��OpenGL */
bool Test::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
   glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);		
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

   /** ������� */
   bones[0].SetBone(-1, 4.5f);
   bones[1].SetBone(0, 4.5f);

   /** ����ģ��ÿ���������� */
   modelPoints[0].SetVertex(CVector4(-1.0f, 0.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
                            0, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1);
   modelPoints[1].SetVertex(CVector4(1.0f, 0.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
                            0, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1);
   modelPoints[2].SetVertex(CVector4(1.0f, 3.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
                            0, 1, 0, 0, 0.50f, 0.50f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 2);
   modelPoints[3].SetVertex(CVector4(-1.0f, 3.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
                            0, 1, 0, 0, 0.50f, 0.50f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 2);

   modelPoints[4].SetVertex(CVector4(-1.0f, 3.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
                            0, 1, 0, 0, 0.50f, 0.50f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2);
   modelPoints[5].SetVertex(CVector4(1.0f, 3.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
                            0, 1, 0, 0, 0.50f, 0.50f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2);
   modelPoints[6].SetVertex(CVector4(1.0f, 6.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
                            0, 1, 0, 0, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2);
   modelPoints[7].SetVertex(CVector4(-1.0f, 6.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
                            0, 1, 0, 0, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2);

   modelPoints[8].SetVertex(CVector4(-1.0f, 6.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
                            0, 1, 0, 0, 0.35f, 0.65f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2);
   modelPoints[9].SetVertex(CVector4(1.0f, 6.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
                            0, 1, 0, 0, 0.35f, 0.65f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2);
   modelPoints[10].SetVertex(CVector4(1.0f, 9.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
                             1, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1);
   modelPoints[11].SetVertex(CVector4(-1.0f, 9.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
                             1, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 1.0, 0.0f, 0.0f, 1.0f, 1);

  
	ResizeDraw(true);

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

/** �������� */
void Test::UpdateBones()
{
	/** ���ڱ�����ת��ƽ�ƾ��� */ 
	CMatrix4x4 transpose, rotTemp1, rotTemp2, tempRelative;

   /** ѭ�����¹��� */
   for(int i = 0; i < MAX_BONES; i++)
      {
         ///����Ƿ��Ǹ�����
         if(bones[i].parent == -1)
            {
               /** ���ñ任���� */
               bones[i].relative.Translate(trans.x, trans.y, trans.z);
               bones[i].absolute = bones[i].relative;

               /** ��ֵ��Ϊ����ʾ���� */
               displayBones[i] = bones[i].relative;
            }
         else
            {
               bones[i].relative.Clear();
               
               /** �ƶ��ù������������� */
               bones[i].relative.Translate(0, bones[bones[i].parent].length * i, 0);

               /** ���������ת */
               rotTemp1.Rotate(xRotation, 0, 1, 0);
               rotTemp2.Rotate(yRotation, 0, 0, 1);

               /** ������Ա任���󣬲���ת */
               tempRelative = bones[i].relative;
               tempRelative.inverseTranslate();

               /** ����任��Ϊ����ʾ���� */
               displayBones[i] = bones[bones[i].parent].absolute * bones[i].relative *
                                 (rotTemp1 * rotTemp2);

               /** ������Ա任���� */
               bones[i].relative = bones[i].relative * (rotTemp1 * rotTemp2) * tempRelative;
               
               /** ������Ա任���� */
               bones[i].absolute = bones[bones[i].parent].absolute * bones[i].relative;
            }
      }
}

/** ���ƺ��� */
void Test::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );			
	glLoadIdentity();
	
	glTranslatef(0.0f, -4.0f, -15.0f);
	
	/** ���¹����б� */
	UpdateBones();
	
	CMatrix4x4 mat;

   /** ��Ⱦ�����еĶ��� */
   for(int j = 0; j < MAX_MESHES; j++)
   {
      glBegin(GL_QUADS);

      for(int i = 0; i < MAX_MESH_POINTS; i++)
         {
            ///��ö���ָ��
            CBoneVertex *thisVertex = &modelPoints[i + j * MAX_MESH_POINTS];

            ///����Ȩֵ���㶥��
            CVector4 pos = CVector4(0.0, 0.0, 0.0, 0.0);
            CVector4 normal = CVector4(0.0, 0.0, 0.0);

			
            for(int i2 = 0; i2 < thisVertex->numBones; i2++)
               {
                  
                  mat = bones[thisVertex->boneIndex[i2]].absolute;

                  ///��Ȩ�����Զ���λ�úͷ��ߵ�Ӱ��   
                  pos += (mat.VectorMatrixMultiply(thisVertex->pos) * thisVertex->weights[i2]);
                  normal += (mat.VectorMatrixMultiply3x3(thisVertex->normal) *
                             thisVertex->weights[i2]);
               }

            ///��Ⱦ�ö���
            glColor4f(thisVertex->r, thisVertex->g, thisVertex->b, thisVertex->a);
            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(pos.x, pos.y, pos.z);
         }

      glEnd();
   }

   //���ƹ���
   for(int i = 0; i < MAX_BONES; i++)
      {
         glPushMatrix();

            glMultMatrixf(displayBones[i].matrix);
      
            glColor3f(1.0f, 1.0f, 1.0f);

            glBegin(GL_LINES);

               ///�����߶�
               glVertex3f(-0.4f, 0.0f, -0.4f);
               glVertex3f(0.4f, 0.0f, -0.4f);
               glVertex3f(0.4f, 0.0f, -0.4f);
               glVertex3f(0.4f, 0.0f, 0.4f);
               glVertex3f(0.4f, 0.0f, 0.4f);
               glVertex3f(-0.4f, 0.0f, 0.4f);
               glVertex3f(-0.4f, 0.0f, 0.4f);
               glVertex3f(-0.4f, 0.0f, -0.4f);

               
               glVertex3f(-0.4f, 0.0f, -0.4f);
               glVertex3f(0.0f, bones[i].length, 0.0f);
               glVertex3f(0.4f, 0.0f, -0.4f);
               glVertex3f(0.0f, bones[i].length, 0.0f);
               glVertex3f(0.4f, 0.0f, 0.4f);
               glVertex3f(0.0f, bones[i].length, 0.0f);
               glVertex3f(-0.4f, 0.0f, 0.4f);
               glVertex3f(0.0f, bones[i].length, 0.0f);

            glEnd();

         glPopMatrix();
      }

	    
	/** ǿ��ִ�����е�OpenGL���� */
	glFlush();	                 
}
