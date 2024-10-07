//=========================================================================
/**
*  @file      Test.cpp
*
*  ��Ŀ������ emboss��͹ӳ��
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-16
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
#include "Emboss.h"	

/** ���������� */
PFNGLACTIVETEXTUREARBPROC       glActiveTextureARB       = NULL;
PFNGLMULTITEXCOORD2FARBPROC     glMultiTexCoord2fARB     = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB = NULL;

/** ���弸����־���� */
bool  g_bEmbossBumpMap  = true;        /**< �Ƿ����ð�͹ӳ�� */
float g_fEmbossFactor   = 0.5f;        /**< ��������ƫ������ */

/** ���嶥�� */
Vertex g_quadVertices[NUM_VERTICES] = 
{
///    tu    tv     nx    ny     nz     x      y     z 
    { 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  -1.0f, -1.0f, 0.0f },
    { 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, -1.0f, 0.0f },
    { 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  -1.0f,  1.0f, 0.0f },
    { 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,   1.0f,  1.0f, 0.0f }
};

TexCoords g_fEmbossTexCoords[NUM_VERTICES];    /**< ����ƫ�ƺ���������� */
Vector3 g_vTangents[NUM_VERTICES];             /**< ���涥�������T���� */
Vector3 g_vBiNormals[NUM_VERTICES];            /**< ���涥�������B���� */


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
	sp = false;
		
}

/** ����Ƿ�֧����չ */
bool Test::isExtensionSupported(const char* string)
{
	char *extension;			/**< ָ����չ�ַ�����ָ�� */
	char *end;				    /**< ���һ���ַ�ָ�� */
	int idx;

	extension = (char*)glGetString(GL_EXTENSIONS);
	if (extension == NULL)
		return false;	
	
	/** �õ����һ���ַ� */
	end = extension + strlen(extension);	

	/** ѭ�������ַ���string */
	while (extension < end)
	{
		/** �ҵ��ո�ǰ��һ���ַ��� */
		idx = strcspn(extension, " ");
		
		/** ����Ƿ��ҵ��ַ���string */
		if ( (strlen(string) == idx) && (strncmp(string, extension, idx) == 0))
		{
			return true;
		}
		
		/** ��ǰ������string,������һ���ַ��� */
		extension += (idx + 1);
	}
	/** û���ҵ�,�򷵻�false */
	return false;   
}

/** ��ʼ�� */
bool Test::initMultiTexture()
{
	/** ����Ƿ�֧����չ */
	if (isExtensionSupported("GL_ARB_multitexture"))
	{
				
		/** ��ú���ָ���ַ */
		glActiveTextureARB       = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
		glMultiTexCoord2fARB     = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
		glClientActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");
		
		return true;
	}
	else 
		return false;
}


/** ��ʼ��OpenGL */
bool Test::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);	                             /**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
	
	/** �������� */
	glEnable(GL_TEXTURE_2D);

	/** ����Ƿ�֧�ֶ������� */
	if(!initMultiTexture())
	{
		MessageBox(NULL,"��֧�ֶ�������!","����",MB_OK);
	    exit(-1);
	}
	
	/** �������� */
	if(!m_texture.Load("woodfloor.tga"))
	{
		MessageBox(NULL,"��������ʧ��!","����",MB_OK);
		exit(-1);
	}
	
	/** ָ������ */
	float ambient_mat[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float diffuse_mat[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient_mat );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse_mat );

	/** ָ����Դ����ֵ */
    float ambient_light0[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
    float diffuse_light0[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	float position_light0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float linearAttenuation_light0[] = { 0.5f };
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambient_light0 );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse_light0 );
    glLightfv( GL_LIGHT0, GL_POSITION, position_light0 );
    glLightfv( GL_LIGHT0, GL_LINEAR_ATTENUATION, linearAttenuation_light0 );
    
	/** �������պ͹�Դ */
	glEnable(GL_LIGHTING);
	glEnable( GL_LIGHT0 );

	/** ���û�����ǿ�� */
	float ambient_lightModel[] = { 0.50f, 0.50f, 0.50f, 1.0f };
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient_lightModel );
    
    /** Ϊÿ��������������� */
	computeTangentsAndBinormals();

	return true;                        /**< �ɹ����� */
}

/** ����dt���������� */
Vector3 Test::computeTangentVector(Vertex pVtxA, Vertex pVtxB, Vertex pVtxC)
{

	Vector3 vAB = Vector3(pVtxB.x, pVtxB.y, pVtxB.z) - Vector3(pVtxA.x, pVtxA.y, pVtxA.z);
	Vector3 vAC = Vector3(pVtxC.x, pVtxC.y, pVtxC.z) - Vector3(pVtxA.x, pVtxA.y, pVtxA.z);
	Vector3 nA  = Vector3(pVtxA.nx, pVtxA.ny, pVtxA.nz);

    /** �����÷��������������� */
    Vector3 vProjAB = vAB - ( nA * vAB.dotProduct(nA));
    Vector3 vProjAC = vAC - ( nA * vAC.dotProduct(nA));

    /** ������������u����Ĳ�ֵ */
    float duAB = pVtxB.tu - pVtxA.tu;
    float duAC = pVtxC.tu - pVtxA.tu;

	/** ������������v����Ĳ�ֵ */
    float dvAB = pVtxB.tv - pVtxA.tv;
    float dvAC = pVtxC.tv - pVtxA.tv;

    if( (duAC * dvAB) > (duAB * dvAC) )
    {
        duAC = -duAC;
        duAB = -duAB;
    }
    
	/** ����������,����һ�� */
    Vector3 vTangent = (vProjAB * duAC) - (vProjAC * duAB);
    vTangent.normalize();
    return vTangent;
}

/** ����ÿ���������߿ռ��ڵ�T��B���� */
void Test::computeTangentsAndBinormals( void )
{	
    
	/** ���ı��η�Ϊ���������� */
    const int nNumIndices = 6;
	int indices[nNumIndices] = { 0,1,2,  2,3,1 };   /**< �����ζ������� */

    /** Ϊÿ����ĸ�������������� */
    for( int i = 0; i < nNumIndices; i += 3 )
    {
		int a = indices[i+0];
        int b = indices[i+1];
        int c = indices[i+2];

        /** ������˶�������������� */
		g_vTangents[a] += computeTangentVector( g_quadVertices[a], g_quadVertices[b], g_quadVertices[c] );
	    g_vTangents[b] += computeTangentVector( g_quadVertices[b], g_quadVertices[a], g_quadVertices[c] );
	    g_vTangents[c] += computeTangentVector( g_quadVertices[c], g_quadVertices[a], g_quadVertices[b] );
	}

    /** ��һ��T����,������B���� */
    for(int i = 0; i < NUM_VERTICES; ++i )
    {
		g_vTangents[i].normalize();
		
		Vector3 normal(g_quadVertices[i].nx, g_quadVertices[i].ny, g_quadVertices[i].nz);

		g_vBiNormals[i] = normal.crossProduct(  g_vTangents[i] );
    }
}

/** ƫ���������� */
void Test::shiftTextureCoordinates( void )
{
	/** �õ�ģ���ӵ���������� */
	CMatrix4x4 modelView;
    CMatrix4x4 inverseModelView;
    glGetFloatv( GL_MODELVIEW_MATRIX, &modelView.m[0] );
	inverseModelView = CMatrix4x4::invertMatrix( &modelView );

    /** �õ���Դλ�� */
    float fLightsPosition[4];
	glGetLightfv( GL_LIGHT0, GL_POSITION, fLightsPosition );
    Vector3 vLightsPosition( fLightsPosition[0], 
                              fLightsPosition[1], 
                              fLightsPosition[2] );
	
	/** ����Դλ��ת�����пռ����� */
    inverseModelView.transformPoint( &vLightsPosition );

	/** Ϊÿ�����������������ƫ���� */
    for( int i = 0; i < NUM_VERTICES; ++i )
    {
       
        Vector3 vLightToVertex;
        
		///����ӹ�Դ�����������
        vLightToVertex = vLightsPosition - Vector3( g_quadVertices[i].x, 
			                             g_quadVertices[i].y, g_quadVertices[i].z );
        ///��һ��
        vLightToVertex.normalize();
        
		///ͬ�������������
		Vector3 normal(g_quadVertices[i].nx, g_quadVertices[i].ny, g_quadVertices[i].nz);
       
		float r = normal.dotProduct( vLightToVertex );
        
        if( r < 0.0f )
        {

            /** ��Դλ��ƽ����·�ʱ������ƫ�� */
            g_fEmbossTexCoords[i].tu2 = g_quadVertices[i].tu;
            g_fEmbossTexCoords[i].tv2 = g_quadVertices[i].tv;
        }
        else
        {
			/** ���пռ����Ŷ��������� */
            Vector3 vEmbossShift;
            
			vEmbossShift.x = vLightToVertex.dotProduct( g_vTangents[i] );
            vEmbossShift.y = vLightToVertex.dotProduct( g_vBiNormals[i] );
			
			vEmbossShift.normalize();  /**< ��һ�� */
            
			g_fEmbossTexCoords[i].tu2 = g_quadVertices[i].tu + (vEmbossShift.x / 128) * g_fEmbossFactor;
            g_fEmbossTexCoords[i].tv2 = g_quadVertices[i].tv + (vEmbossShift.y / 128) * g_fEmbossFactor;
        }
    }
}

/** ��Ⱦ��͹ӳ�� */
void Test::renderQuadWithEmbossBumpMapping()
{
	/** ������� */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ZERO);/**< ָ��������� */
	
	/** ����Ԫ0 */
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture.ID);

	///ָ��������ģʽΪ��Ϻ�����ʽ��
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);

	//ָ��RGB������ʽ�ǳ˷�
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_MODULATE);
    
	///ָ������ɫ���������Ų�����������2��0f ����2����ͼ����ɫ
	glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 2.0f);

	///ָ��alpha�Ĳ�����ʽΪ�滻��ʽ
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_REPLACE);
	
	
	/** ����Ԫ1 */
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture.ID);
	
	///ָ��������ģʽΪ��Ϻ�����ʽ
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);

	///ָ��RGB������ʽΪ�滻
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);

	/** ָ��RGB���Ų��� */
	glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 1.0f);

	/** ��ǰ������Ľ����Ϊ���� */
	glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_PREVIOUS_EXT);


	/** ָ��alpha�����ķ��� */
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_ADD_SIGNED_EXT);	
	glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA_EXT, GL_ONE_MINUS_SRC_ALPHA);
	
	/** ָ��������һ����������alpha ����һ������ǰ��alpha */
	glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, GL_TEXTURE);
	glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_EXT, GL_PREVIOUS_EXT);

	/** ��ʼ��Ⱦ */
	glBegin( GL_TRIANGLE_STRIP );
    {
		for( int i = 0; i < NUM_VERTICES; ++i )
        {
			glNormal3f( g_quadVertices[i].nx, g_quadVertices[i].ny, g_quadVertices[i].nz );
			
            ///ָ������Ԫ0����������
			glMultiTexCoord2fARB( GL_TEXTURE0_ARB, g_quadVertices[i].tu, g_quadVertices[i].tv );

            ///ָ������Ԫ1����������
            glMultiTexCoord2fARB( GL_TEXTURE1_ARB, g_fEmbossTexCoords[i].tu2, g_fEmbossTexCoords[i].tv2 );
			
			///ָ����������
            glVertex3f( g_quadVertices[i].x, g_quadVertices[i].y, g_quadVertices[i].z );
		}
    }
	glEnd();

	
	///�ָ�״̬,�ر���������Ԫ
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_2D);

	///�رջ��
	glDisable( GL_BLEND );   
}

/** �û��Զ����ж�غ��� */
void Test::Uninit()									
{
	m_texture.FreeImage();
	glDeleteTextures(1,&m_texture.ID);
}

/** ������º��� */
void Test::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}

/** �û��Զ���ĸ��¹��� */
	
	
	/** �ո���л�����ģʽ */
	if(m_Keys.IsPressed(VK_SPACE) && !sp)
	{
		sp = true;
		g_bEmbossBumpMap = !g_bEmbossBumpMap;
	}

	if(!m_Keys.IsPressed(VK_SPACE))
		sp = false;
	
	/** ���¹�Դλ�� */
	static float fAngle = 0; 
	fAngle += 60 * (float)milliseconds*0.001;

	/** �Ƕȿ��� */
	while(fAngle > 360.0f) 
		fAngle -= 360.0f;
	while(fAngle < 0.0f)  
		fAngle += 360.0f;

    float x = sinf( DEGTORAD(fAngle) );
    float y = cosf( DEGTORAD(fAngle) );

    float position_light0[4];

    position_light0[0] = 2.0f * x;
    position_light0[1] = 2.0f * y;
    position_light0[2] = 0.0f;
    position_light0[3] = 1.0f;

	/** ָ����Դλ�� */
    glLightfv( GL_LIGHT0, GL_POSITION, position_light0 );
	    
}


/** ���ƺ��� */
void Test::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-4.0f);

	
	if( g_bEmbossBumpMap == true )
    {
        /** �Ŷ��������� */
        shiftTextureCoordinates();

        /** ��Ⱦ��͹ӳ�� */
	    renderQuadWithEmbossBumpMapping();
    }
    else
    {
        /** �����а�͹ӳ����Ⱦ */
		glDisable( GL_BLEND );

		/** ��������Ԫ0 */
		glActiveTextureARB( GL_TEXTURE0_ARB );
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, m_texture.ID );

		glBegin( GL_TRIANGLE_STRIP );
        {
		    for( int i = 0; i < 4; i++ )
            {
			    glNormal3f( g_quadVertices[i].nx, g_quadVertices[i].ny, g_quadVertices[i].nz );
                glTexCoord2f( g_quadVertices[i].tu, g_quadVertices[i].tv );
			    glVertex3f( g_quadVertices[i].x, g_quadVertices[i].y, g_quadVertices[i].z );
		    }
        }
	    glEnd();
    }
	glPopMatrix();        /**< ���ƽ��� */


	/** ����һ��С������Դ */
	glDisable( GL_LIGHTING );     /**< �رչ��� */
    glDisable(GL_TEXTURE_2D);     /**< �ر����� */
 	glColor3f( 1.0f, 1.0f, 1.0f );
   
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	/** �õ���Դλ�� */
	float fLightsPosition[4];
	glGetLightfv( GL_LIGHT0, GL_POSITION, fLightsPosition );
	glTranslatef( fLightsPosition[0], fLightsPosition[1], -5.0f );
	auxSolidSphere(0.1);
	glPopMatrix();

	/** ���ù��պ����� */
	glEnable( GL_LIGHTING );
	glEnable(GL_TEXTURE_2D);

	glFlush();	                 /**< ǿ��ִ�����е�OpenGL���� */
}
