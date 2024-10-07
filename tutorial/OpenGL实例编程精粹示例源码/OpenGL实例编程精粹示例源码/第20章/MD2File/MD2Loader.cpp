//========================================================
/**
*  @file      MD2Loader.cpp
*
*  ��Ŀ������ MD2�ļ�����
*  �ļ�����:  MD2�ļ�������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-12-06	
*  �޸����ڣ� 2006-12-13
*
*/     
//========================================================

#include "MD2Loader.h"

/** ���캯�� */
CMD2Loader::CMD2Loader()
{
	/** Ϊ�ļ�ͷ�����ڴ� */
	memset(&m_Header, 0, sizeof(tMd2Header));

	/** ��ʱ��ָ��Ϊ�� */
	m_pSkins=NULL;
	m_pTexCoords=NULL;
	m_pTriangles=NULL;
	m_pFrames=NULL;

	/** ��ʱ���������� */
	for(int i=0; i<MAX_TEXTURES; i++)
		m_textures[i]=0;

}

/** �������� */
CMD2Loader::~CMD2Loader()
{
	/** ������Ŀ���� */
	m_3DModel.numOfObjects = 0;
	m_3DModel.numOfMaterials = 0;
	m_3DModel.numOfAnimations = 0;
	
	/** ��������� */
	m_3DModel.pObject.clear();
	m_3DModel.pMaterials.clear();
	m_3DModel.pAnimations.clear();
	
	/** ɾ������ */
	glDeleteTextures(MAX_TEXTURES, m_textures);
}

/** �ͷ��ڴ� */
void CMD2Loader::CleanUp()
{
	/** �ر�ָ�� */
	fclose(m_FilePointer);						

	/** �ͷ��ڴ� */
	if(m_pSkins)	 delete [] m_pSkins;		
	if(m_pTexCoords) delete m_pTexCoords;		
	if(m_pTriangles) delete m_pTriangles;		
	if(m_pFrames)	 delete m_pFrames;	

}

/** ��ʼ�� */
void CMD2Loader::Init(char *strFileName, char *strTexture)
{
   
	/** ����MD2�ļ� */
	ImportMD2(&m_3DModel,strFileName,strTexture);
   
	for(int i =0; i<m_3DModel.numOfMaterials;i++)
	{ 
		if(strlen(m_3DModel.pMaterials[i].strFile)>0)                 /**< �ж��Ƿ���һ���ļ��� */
		   LoadTexture(m_3DModel.pMaterials[i].strFile,m_textures, i);/**< ʹ�������ļ�������װ��λͼ */		 
	   
		/** ���ò��ʵ�����ID */
		m_3DModel.pMaterials[i].texureId = i;                     
	} 
}

/** ����MD2�ļ� */
bool CMD2Loader::ImportMD2(t3DModel *pModel, char *strFileName, char *strTexture)
{
	char strMessage[255] = {0};

	/** ���ļ� */
	m_FilePointer = fopen(strFileName, "rb");

	/** ����ļ�ָ�� */
	if(!m_FilePointer) 
	{
		
		sprintf(strMessage, "���ļ�: %s����!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}
	
	/** ��ȡ�ļ�ͷ */
	fread(&m_Header, 1, sizeof(tMd2Header), m_FilePointer);

	/** ���汾�� */
	if(m_Header.version != 8)
	{
		
		sprintf(strMessage, "Invalid file format (Version not 8): %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}

	/** ��ȡMD2�ļ����� */
	ReadMD2Data();
	
	/** ��MD2����ת��Ϊģ�ͽṹ */
	ConvertDataStructures(pModel);

	/** ������������ļ� */
	if(strTexture)
	{
		/** ������Ϣ�ṹ�� */
		tMaterialInfo texture;

		/** �����ļ��� */
		strcpy(texture.strFile, strTexture);

		/** ����ID��Ϊ0 */
		texture.texureId = 0;

		texture.uTile = texture.uTile = 1;

		/** ģ�Ͳ�����Ϊ1 */
		pModel->numOfMaterials = 1;

		/** ��Ӳ�����Ϣ */
		pModel->pMaterials.push_back(texture);
	}

	/** �ͷ��ڴ� */
	CleanUp();
	
	return true;     /**< �ɹ����� */
}

/** ��ȡ���� */
void CMD2Loader::ReadMD2Data()
{
	/** Ϊ֡���������㹻���ڴ� */
	unsigned char buffer[MD2_MAX_FRAMESIZE];

	/** �����ڴ� */
	m_pSkins     = new tMd2Skin [m_Header.numSkins];
	m_pTexCoords = new tMd2TexCoord [m_Header.numTexCoords];
	m_pTriangles = new tMd2Face [m_Header.numTriangles];
	m_pFrames    = new tMd2Frame [m_Header.numFrames];

	/** ָ���Ƶ���������λ��,����ȡ���� */
	fseek(m_FilePointer, m_Header.offsetSkins, SEEK_SET);
	fread(m_pSkins, sizeof(tMd2Skin), m_Header.numSkins, m_FilePointer);
		
	/** ָ���Ƶ���������λ��,����ȡ�������� */
	fseek(m_FilePointer, m_Header.offsetTexCoords, SEEK_SET);
	fread(m_pTexCoords, sizeof(tMd2TexCoord), m_Header.numTexCoords, m_FilePointer);

	/** ָ���Ƶ���������λ��,����ȡ����Ϣ */
	fseek(m_FilePointer, m_Header.offsetTriangles, SEEK_SET);
	fread(m_pTriangles, sizeof(tMd2Face), m_Header.numTriangles, m_FilePointer);
			
	/** ָ���Ƶ���������λ�� */
	fseek(m_FilePointer, m_Header.offsetFrames, SEEK_SET);

	/** ��ÿ֡��ѹ�������� */
	for (int i=0; i < m_Header.numFrames; i++)
	{
		
		tMd2AliasFrame *pFrame = (tMd2AliasFrame *) buffer;

		/** ���䶥���ڴ� */
		m_pFrames[i].pVertices = new tMd2Triangle [m_Header.numVertices];

		/** ��ȡ��һ֡ */
		fread(pFrame, 1, m_Header.frameSize, m_FilePointer);

		/** ���涯������ */
		strcpy(m_pFrames[i].strName, pFrame->name);
			
		tMd2Triangle *pVertices = m_pFrames[i].pVertices;

		/** �����ж���ͨ�����ź�ƫ�ƽ��н�ѹ,���������� */
		for (int j=0; j < m_Header.numVertices; j++)
		{
			pVertices[j].vertex[0] = pFrame->aliasVertices[j].vertex[0] * pFrame->scale[0] + pFrame->translate[0];
			pVertices[j].vertex[2] = -1 * (pFrame->aliasVertices[j].vertex[1] * pFrame->scale[1] + pFrame->translate[1]);
			pVertices[j].vertex[1] = pFrame->aliasVertices[j].vertex[2] * pFrame->scale[2] + pFrame->translate[2];
		}
	}
}

/** װ������ */
void CMD2Loader::LoadTexture(char* filename, GLuint textureArray[], GLuint textureID)
{

	if(!filename)
		return;
	
	/** ����λͼ */
	if(!m_BMPTexture.LoadBitmap(filename))
	{
		MessageBox(NULL,"����λͼʧ��!","����",MB_OK);
		exit(0);
	}
	glGenTextures(1,&m_textures[textureID]);
	
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, m_textures[textureID]);
	
	/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	
	/** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_BMPTexture.imageWidth, m_BMPTexture.imageHeight, GL_RGB, 
		              GL_UNSIGNED_BYTE, m_BMPTexture.image);
		
}

/** ��������ȡ֡��Ϣ */
void CMD2Loader::ParseAnimations(t3DModel *pModel)
{
	tAnimationInfo animation;
	string strLastName = "";

	/** ѭ������ */
	for(int i = 0; i < pModel->numOfObjects; i++)
	{
		/** ����֡�� */
		string strName  = m_pFrames[i].strName;
		int frameNum = 0;
		
		/** ������֡���� */
		for(unsigned int j = 0; j < strName.length(); j++)
		{
			/** ����������ֶ�������������ַ�֮һ */
			if( isdigit(strName[j]) && j >= strName.length() - 2)
			{
				/** ���ַ�ת��Ϊ���� */
				frameNum = atoi(&strName[j]);

				/** �������*/
				strName.erase(j, strName.length() - j);
				break;
			}
		}

		/** �����֡���ֺ�ǰһ֡��ͬ���߸�֡Ϊ����֡ */
		if(strName != strLastName || i == pModel->numOfObjects - 1)
		{
			/** ����Ƿ�Ϊ��ʼ֡ */
			if(strLastName != "")
			{
				/** ����֡���� */
				strcpy(animation.strName, strLastName.c_str());

				/** ���ö�������֡���Ϊi */
				animation.endFrame = i;

				/** ����֡��ӵ������б��� */
				pModel->pAnimations.push_back(animation);
				memset(&animation, 0, sizeof(tAnimationInfo));

				/** ��������һ */
				pModel->numOfAnimations++;
			}

			/** ���ÿ�ʼ֡ */
			animation.startFrame = frameNum - 1 + i;
		}

		/** ����֡������ */
		strLastName = strName;
	}
}

/** ����֡���ݱ�����ģ�ͽṹ�� */
void CMD2Loader::ConvertDataStructures(t3DModel *pModel)
{
	int j = 0, i = 0;

	/** �����ڴ� */
	memset(pModel, 0, sizeof(t3DModel));
	
	/** ���ö�����ĿΪ�ؼ�֡��Ŀ */
	pModel->numOfObjects = m_Header.numFrames;

	/** ����������Ϣ */
	ParseAnimations(pModel);

	/** ����֡����������ӵ�ģ�Ͷ��������� */
	for (i=0; i < pModel->numOfObjects; i++)
	{
		/** �����һ֡���� */
		t3DObject currentFrame = {0};

		/** ָ������ �����������ĸ��� */
		currentFrame.numOfVerts   = m_Header.numVertices;
		currentFrame.numTexVertex = m_Header.numTexCoords;
		currentFrame.numOfFaces   = m_Header.numTriangles;

		/** �����ڴ� */
		currentFrame.pVerts    = new Vector3 [currentFrame.numOfVerts];

		/** ѭ���������ж��� */
		for (j=0; j < currentFrame.numOfVerts; j++)
		{
			currentFrame.pVerts[j].x = m_pFrames[i].pVertices[j].vertex[0];
			currentFrame.pVerts[j].y = m_pFrames[i].pVertices[j].vertex[1];
			currentFrame.pVerts[j].z = m_pFrames[i].pVertices[j].vertex[2];
		}

		/** �ͷ��ڴ� */
		delete m_pFrames[i].pVertices;
	
	    /** ����Ƿ񳬹���һ֡ */
		if(i > 0)
		{
			/** ����֡��ӵ�ģ�Ͷ����� */
			pModel->pObject.push_back(currentFrame);
			continue;	
		}

		/** �����ڴ� */
		currentFrame.pTexVerts = new Vector2 [currentFrame.numTexVertex];
		currentFrame.pFaces    = new tFace [currentFrame.numOfFaces];

		/** ������������ */
		for(j=0; j < currentFrame.numTexVertex; j++)
		{
			currentFrame.pTexVerts[j].x = m_pTexCoords[j].u / float(m_Header.skinWidth);
			currentFrame.pTexVerts[j].y = 1 - m_pTexCoords[j].v / float(m_Header.skinHeight);
		}

		/** ������������Ϣ */
		for(j=0; j < currentFrame.numOfFaces; j++)
		{
			/** Ϊ�涥������������ֵ */
			currentFrame.pFaces[j].vertIndex[0] = m_pTriangles[j].vertexIndices[0];
			currentFrame.pFaces[j].vertIndex[1] = m_pTriangles[j].vertexIndices[1];
			currentFrame.pFaces[j].vertIndex[2] = m_pTriangles[j].vertexIndices[2];

			/** Ϊ�涥����������������ֵ */
			currentFrame.pFaces[j].coordIndex[0] = m_pTriangles[j].textureIndices[0];
			currentFrame.pFaces[j].coordIndex[1] = m_pTriangles[j].textureIndices[1];
			currentFrame.pFaces[j].coordIndex[2] = m_pTriangles[j].textureIndices[2];
		}

		/** ����֡��ӵ�ģ���� */
		pModel->pObject.push_back(currentFrame);
	}
}

/** ����ʱ��t,��������֮֡����в�ֵ */
float CMD2Loader::ReturnCurrentTime(t3DModel *pModel, int nextFrame)
{
	static float elapsedTime   = 0.0f;
	static float lastTime	  = 0.0f;

	/** ��ȡ��ǰʱ�� */
	float time = (float)GetTickCount();

	/** ��������ʱ�� */
	elapsedTime = time - lastTime;

	/** ��������ʱ�����t */
	float t = elapsedTime / (1000.0f / kAnimationSpeed);
	
	/** ���elapsedTime���� 1s/kAnimationSpeed */
	if (elapsedTime >= (1000.0f / kAnimationSpeed) )
	{
		/** ������һ֡ */
		pModel->currentFrame = nextFrame;

		/** ����ʱ��ֵ */
		lastTime = time;
	}

	/** ����t */
	return t;
}

/** ͨ���ؼ�֡��ֵʵ��ģ�ͻ��ƺͶ��� */
void CMD2Loader::AnimateMD2Model()
{
	
	if(m_3DModel.pObject.size() <= 0) return;

	/** ��ȡ��ǰ������Ϣ */
	tAnimationInfo *pAnim = &(m_3DModel.pAnimations[m_3DModel.currentAnim]);

	/** ������һ֡ */
	int nextFrame = (m_3DModel.currentFrame + 1) % pAnim->endFrame;

	/** �����һ֡Ϊ0,����Ϊ��ʼ֡ */
	if(nextFrame == 0) 
		nextFrame =  pAnim->startFrame;

	/** ��ȡ��ǰ֡��Ϣ */
	t3DObject *pFrame =		 &m_3DModel.pObject[m_3DModel.currentFrame];

	/** ��ȡ��һ֡��Ϣ */
	t3DObject *pNextFrame =  &m_3DModel.pObject[nextFrame];

	/** ��ȡ��һ֡��Ϣ */
	t3DObject *pFirstFrame = &m_3DModel.pObject[0];

	/** ����t,����֡��ֵ */
	float t = ReturnCurrentTime(&m_3DModel, nextFrame);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textures[pFrame->materialID]);
	
	/** ��ʼ���� */
	glBegin(GL_TRIANGLES);

		/** ���������� */
		for(int j = 0; j < pFrame->numOfFaces; j++)
		{
			/** ����������ж��� */
			for(int whichVertex = 0; whichVertex < 3; whichVertex++)
			{
				/** ��ø����ж������������ */
				int vertIndex = pFirstFrame->pFaces[j].vertIndex[whichVertex];
				int texIndex  = pFirstFrame->pFaces[j].coordIndex[whichVertex];
						
				/** ����Ƿ�������� */
				if(pFirstFrame->pTexVerts) 
				{
					/** ָ���������� */
					glTexCoord2f(pFirstFrame->pTexVerts[ texIndex ].x, 
								 pFirstFrame->pTexVerts[ texIndex ].y);
				}

								
				/** ���濪ʼ����֡��ֵ */
				Vector3 vPoint1 = pFrame->pVerts[ vertIndex ];
				Vector3 vPoint2 = pNextFrame->pVerts[ vertIndex ];

				/** ���ù�ʽ: p(t) = p0 + t(p1 - p0),�õ���ֵ�� */
				glVertex3f(vPoint1.x + t * (vPoint2.x - vPoint1.x), 
						   vPoint1.y + t * (vPoint2.y - vPoint1.y), 
						   vPoint1.z + t * (vPoint2.z - vPoint1.z));
			}
		}
    /** ��Ⱦ���� */
	glEnd();	
}


