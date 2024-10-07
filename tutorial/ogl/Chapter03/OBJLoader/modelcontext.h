//定义OBJ模型的结构和一些相关的数据类型
#ifndef MODEL_CONTEXT_HEADER
#define MODEL_CONTEXT_HEADER

#define VERTEX_MAX 66000
#define LINE_MAX 29000
#define LINE_STRIP_MAX 18000
#define EDGE_MAX 15000
#define OBJ_VERTEX_MAX 8500
#define COLOR_MAX 100

#define SCALE_SPEED 0.003
#define MINIMUM_SCALE 0.5

#define PIXELS_PER_INCH 100.0
#define EYE_BACK 36.0

typedef struct Vertex Vertex;
struct Vertex {
	int draw;                       
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat nx;
	GLfloat ny;
	GLfloat nz;

	int colorIndex;	
	int vertexIndex;		
					
	int facets[90];
	int facetsNum;

	int edges[60];
	int edgesNum;
};

typedef struct ColorStruct ColorStruct;
struct ColorStruct {
	int index;          	
	GLfloat ra, ga, ba;
	GLfloat rd, gd, bd, ad;
	GLfloat rs, gs, bs;
	GLfloat spec;
};
//材质定义
typedef struct MaterialColor MaterialColor;
struct MaterialColor {
    char name[100];
    GLfloat ra, ga, ba;			/* Ambient */
    GLfloat rd, gd, bd, ad;		/* Diffuse */
    GLfloat rs, gs, bs;			/* Specular */
    GLfloat spec;			/* Specular power (shininess) */
};

typedef struct ModelContext ModelContext;
struct ModelContext
{
    int facetCount;                     //面的数量
    int triangleFlag;			
    Vertex vertexList[VERTEX_MAX];		//模型中的顶点列表
    int vertexCount;
    Vertex lineList[LINE_MAX];			//线中的顶点数组
    int lineCount;						//顶点数量
    Vertex lineStripList[LINE_STRIP_MAX]; 
    int lineStripCount;			
    int edgeList[EDGE_MAX][2];
    int edgeCount;
    Vertex objVertexList[OBJ_VERTEX_MAX]; //OBJ文件中的顶点
    int ovCount;
    int onCount;
    ColorStruct colorList[COLOR_MAX];		//模型中的颜色列表
    int colorCount;
    //模型中的边界盒
    GLfloat boundBoxLeft, boundBoxBottom, boundBoxNear;
    GLfloat boundBoxRight, boundBoxTop, boundBoxFar;

    GLdouble rotX, rotY;
    GLdouble scaleObj;
    GLdouble rotMat[16];
    GLdouble windowWidth, windowHeight;
    GLdouble minimumScale;

    int haveNormals;
    int needToUpdateViewMat;
    int pointerMotion;			
};

#endif /* MODEL_CONTEXT_HEADER */
