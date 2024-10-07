//========================================================
/**
*  @file      MD2Loader.h
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
#ifndef __MD2LOADER_H__
#define __MD2LOADER_H__


#include "vector.h"
#include "BMPLoader.h"
#include <string>
#include <vector>                    /** ������������ */
using namespace std;    

/** ���涨��һЩ���ֵ */
#define MD2_MAX_TRIANGLES		4096
#define MD2_MAX_VERTICES		2048
#define MD2_MAX_TEXCOORDS		2048
#define MD2_MAX_FRAMES			512
#define MD2_MAX_SKINS			32
#define MD2_MAX_FRAMESIZE		(MD2_MAX_VERTICES * 4 + 128)

/** MD2�ļ�ͷ */
struct tMd2Header
{ 
   int magic;					/**< �ļ���־ */
   int version;					/**< �ļ��汾�� */
   int skinWidth;				/**< ������ */
   int skinHeight;				/**< ����߶� */
   int frameSize;				/**< ÿһ֡���ֽ��� */
   int numSkins;				/**< ������Ŀ */
   int numVertices;				/**< ������Ŀ(ÿһ֡��) */
   int numTexCoords;			/**< ����������Ŀ */
   int numTriangles;			/**< ��������Ŀ */
   int numGlCommands;			/**< gl������Ŀ */
   int numFrames;				/**< ��֡�� */
   int offsetSkins;				/**< �����ƫ��λ�� */
   int offsetTexCoords;			/**< ���������ƫ��λ�� */
   int offsetTriangles;			/**< ������������ƫ��λ�� */
   int offsetFrames;			/**< ��һ֡��ƫ��λ�� */
   int offsetGlCommands;		/**< OPenGL�����ƫ��λ�� */
   int offsetEnd;				/**< �ļ���βƫ��λ�� */
};

/** ����ṹ */
struct tMd2AliasTriangle
{
   BYTE vertex[3];
   BYTE lightNormalIndex;
};

/** �����νṹ */  
struct tMd2Triangle
{
   float vertex[3];
   float normal[3];
};

/** ��ṹ */
struct tMd2Face
{
   short vertexIndices[3];
   short textureIndices[3];
};

/** ��������ṹ */
struct tMd2TexCoord
{
   short u, v;
};

/** ֡�ṹ */
struct tMd2AliasFrame
{
   float scale[3];
   float translate[3];
   char name[16];
   tMd2AliasTriangle aliasVertices[1];
};

/** �ؼ�֡�ṹ */
struct tMd2Frame
{
   char strName[16];
   tMd2Triangle *pVertices;
};


/** ����Ϣ */
struct tFace
{
	int vertIndex[3];			/**< �������� */
	int coordIndex[3];			/**< ������������ */
};

/** ������Ϣ�ṹ�� */
struct tMaterialInfo
{	
	char  strName[255];			   /**< �������� */
	char  strFile[255];			   /**< �����ļ����� */
	BYTE  color[3];				   /**< �����RGB��ɫ */
	int   texureId;				   /**< ����ID */
	float uTile;				   /**< u �ظ� */
	float vTile;				   /**< v �ظ� */
	float uOffset;			       /**< u ����ƫ�� */
	float vOffset;				   /**< v ����ƫ�� */
} ;

/** ������Ϣ�ṹ�� */
struct tAnimationInfo
{
	char strName[255];			/**< ֡������ */
	int startFrame;				/**< ��ʼ֡ */
	int endFrame;				/**< ����֡ */
};

/** ������Ϣ�ṹ�� */
struct t3DObject	
{	
	int  numOfVerts;		      /**< ģ���ж������Ŀ */
	int  numOfFaces;			  /**< ģ���������Ŀ */
	int  numTexVertex;			  /**< ģ���������������Ŀ */
	int  materialID;			  /**< ����ID */
	bool bHasTexture;			  /**< �Ƿ��������ӳ�� */
	char strName[255];			  /**< ��������� */
	Vector3  *pVerts;			  /**< ����Ķ��� */
	Vector3  *pNormals;		      /**< ����ķ����� */
	Vector2  *pTexVerts;		  /**< ����UV���� */
	tFace    *pFaces;		      /**< ���������Ϣ */
};

/** ģ����Ϣ�ṹ�� */
struct t3DModel	
{	int numOfObjects;			        /**< ģ���ж������Ŀ */
	int numOfMaterials;			        /**< ģ���в��ʵ���Ŀ */
	int numOfAnimations;                /**< ģ���ж�������Ŀ */
	int currentAnim;                    /**< ֡���� */
	int currentFrame;                   /**< ��ǰ֡ */
	vector<tAnimationInfo> pAnimations; /**< ֡��Ϣ���� */
	vector<tMaterialInfo> pMaterials;	/**< ����������Ϣ */
	vector<t3DObject> pObject;	        /**< ģ���ж���������Ϣ */
};

/** �������� */
typedef char tMd2Skin[64];

/** ����һ֡�����ٶ� */
#define kAnimationSpeed			5.0f

/** ���������Ŀ */
#define MAX_TEXTURES 100

/** MD2�ļ������� */
class CMD2Loader
{

public:
	/** ���캯�� */
	CMD2Loader();	

	~CMD2Loader();

    /** ����3Dģ�ͽṹ */
	t3DModel& GetModel() { return m_3DModel; }

	/** ��ʼ�� */
	void  Init(char* strFileName, char *strTexture);

	/** ����ģ�Ͷ��� */
	void AnimateMD2Model();
    
	/** ģ�ͽṹ */
	t3DModel                m_3DModel;                  
	
private:
	
	/** ����MD2�ļ� */
	bool ImportMD2(t3DModel *pModel, char *strFileName, char *strTexture);
	
	/** ��ȡMD2�ļ����� */
	void ReadMD2Data();

	/**  ���ļ��д������� */
	void LoadTexture(char* filename, GLuint textureArray[], GLuint textureID);

	/** ���涯����Ϣ */
	void ParseAnimations(t3DModel *pModel);

	/** ��MD2�ļ��ṹת��Ϊģ�ͽṹ */
	void ConvertDataStructures(t3DModel *pModel);

	/** �ͷ��ڴ� */
	void CleanUp();

	/** ���ص�ǰʱ�� */
	float ReturnCurrentTime(t3DModel *pModel, int nextFrame);

	FILE *m_FilePointer;                                 /**< �ļ�ָ�� */
	tMd2Header				m_Header;			         /**< �ļ�ͷ */
	tMd2Skin				*m_pSkins;			         /**< ��������ָ�� */
	tMd2TexCoord			*m_pTexCoords;		         /**< ��������ָ�� */
	tMd2Face				*m_pTriangles;		         /**< ��������ָ�� */
	tMd2Frame				*m_pFrames;			         /**< �ؼ�֡ */
	CBMPLoader              m_BMPTexture;                /**< ����λͼ */
	GLuint                  m_textures[MAX_TEXTURES];    /**< �������� */
	
};

#endif