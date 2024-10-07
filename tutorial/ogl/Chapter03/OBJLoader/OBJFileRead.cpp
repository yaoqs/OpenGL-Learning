// OBJFileRead.cpp: implementation of the COBJFileRead class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OBJLoader.h"
#include "OBJFileRead.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COBJFileRead::COBJFileRead()
{

}

COBJFileRead::~COBJFileRead()
{

}

void COBJFileRead::readLineData(char *FileName)
{
    FILE *dataFile;
    char inputLine[256];
    GLfloat x, y, z;			
    GLfloat r, g, b;
    int count;

    dataFile = fileOpen(FileName, "r");
    if (dataFile == NULL)
	exit(1);

    model->haveNormals = 0;
    model->vertexCount = 0;
    model->colorCount = 0;
    model->colorList[0].index = -1;	

    //读入线数据直到文件结尾
    while ((fgets(inputLine, 250, dataFile) != NULL) && (inputLine[0] != 'e')) {

	if (inputLine[0] == 'm') {
	    count = sscanf(inputLine, "m %f %f %f", &x, &y, &z);
	    model->vertexList[model->vertexCount].draw = 0;
	}

	if (inputLine[0] == 'd') {
	    count = sscanf(inputLine, "d %f %f %f", &x, &y, &z);
	    model->vertexList[model->vertexCount].draw = 1;
	}

	if (inputLine[0] == 'c') {
	    count = sscanf(inputLine, "c %f %f %f", &r, &g, &b);
	    model->colorList[model->colorCount].index = model->vertexCount;
	    model->colorList[model->colorCount].rd = r;
	    model->colorList[model->colorCount].gd = g;
	    model->colorList[model->colorCount].bd = b;
            model->colorList[model->colorCount].ad = 1.0;

	    if (model->colorCount + 1 < COLOR_MAX) {
		model->colorCount++;
	    }
	    else {
		//颜色数量太多,显示错误提示
		fprintf (stderr, "Error, number of colors exceeds limit (%d)\n",
		    COLOR_MAX);
	    }
	    continue;
	}

	if (count != 3)
	    continue;

	model->vertexList[model->vertexCount].x = x;
	model->vertexList[model->vertexCount].y = y;
	model->vertexList[model->vertexCount].z = z;

	if (model->vertexCount + 1 < VERTEX_MAX) {
	    model->vertexCount++;
	}
	else {
	    //顶点数量太多，显示错误提示
	    fprintf (stderr, "Error, number of vertices exceeds limit (%d)\n",
		VERTEX_MAX);
	    exit (-1);
	}
    }

    
    model->vertexList[model->vertexCount].draw = 0;

    fclose(dataFile);
} /* End of readLineData */

void COBJFileRead::readObjData(char *FileName)
{
    FILE *dataFile;				//读入的文件
    int count;					//输入数量的计数器
    char inputLine[512];	
    int ilLen;					//线的长度
    GLfloat x, y, z;			//顶点坐标
    int facetVertex[100];		//面的顶点序列
    int facetNormal[100];		//面的法向量
    int fvCount;				//在面中的顶点数
    int linePos, lp;			//输入线的位置
    int i, j, k, m;			
    char materialName[128];		//材质文件
    MaterialColor *materials;	//材质描述的指针
    MaterialColor *matPtr;		
    int foundMatch;				
    int v0,v1;					

   
    glFrontFace(GL_CCW);

    dataFile = fileOpen(FileName, "r");
    if (dataFile == NULL) 
	{
		perror(FileName);
		exit(1);
    }
    materials = NULL;
    model->facetCount = 0;
    model->haveNormals = 0;
    model->ovCount = 1;			//顶点数从1开始
    model->onCount = 1;
    model->vertexCount = 0;
    model->edgeCount = 0;
    model->lineCount = 0;
    model->lineStripCount = 0;
    model->colorCount = 0;
    model->colorList[0].index = -1;
    model->boundBoxLeft = 0;
    model->boundBoxRight = 0.0;
    model->boundBoxBottom = 0.0;
    model->boundBoxTop = 0.0;
    model->boundBoxNear = 0.0;
    model->boundBoxFar = 0.0;

    for(;;) 
	{
		if (fgets(inputLine, 500, dataFile) == NULL)
			break;			//文件结尾

		//获得线的长度
		ilLen = strlen(inputLine);
		while ((ilLen > 0) && ((inputLine[ilLen - 1] == ' ') ||
			(inputLine[ilLen - 1] == '\n')))
			ilLen--;

		if (inputLine[0] == 'v') 
		{
			//读入一个顶点，并将其保存到点的数组中
			if (inputLine[1] == ' ') 
			{
				//一个顶点
				count = sscanf(inputLine, "v %f %f %f", &x, &y, &z);
				if (count != 3)
					continue;
				model->objVertexList[model->ovCount].facetsNum = 0;
				model->objVertexList[model->ovCount].edgesNum = 0;
				model->objVertexList[model->ovCount].x = x;
				model->objVertexList[model->ovCount].y = y;
				model->objVertexList[model->ovCount++].z = z;

				//更新边界盒
				if (x < model->boundBoxLeft)
					model->boundBoxLeft = x;
				if (x > model->boundBoxRight)
					model->boundBoxRight = x;
				if (y < model->boundBoxBottom)
					model->boundBoxBottom = y;
				if (y > model->boundBoxTop)
					model->boundBoxTop = y;
				if (z < model->boundBoxNear)
					model->boundBoxNear = z;
				if (z > model->boundBoxFar)
					model->boundBoxFar = z;
			}
			else if (inputLine[1] == 'n') 
			{
				//法向量
				count = sscanf(inputLine, "vn %f %f %f", &x, &y, &z);
				if (count != 3)
					continue;
				model->objVertexList[model->onCount].nx = x;
				model->objVertexList[model->onCount].ny = y;
				model->objVertexList[model->onCount++].nz = z;
				model->haveNormals = 1;
			}
		}
		else if (inputLine[0] == 'f') 
		{
			//读入一个面，获得顶点的坐标
			fvCount = 0;
			linePos = 2;
			while (linePos < ilLen) 
			{
				//获得下一个数
				sscanf(&inputLine[linePos], "%d%n", &facetVertex[fvCount], &lp);
				if (inputLine[linePos + lp] == '/') 
				{
					linePos += lp + 2;
					sscanf(&inputLine[linePos], "%d%n", &facetNormal[fvCount], 
						&lp);
				}
				fvCount++;
				linePos += lp + 1;
			}
			if (fvCount < 3)
				continue;		//不是多边形
			facetVertex[fvCount] = facetVertex[0];	

			//转换顶点数为XYZ
			for (i = 0; i < fvCount; i++) 
			{
				if (facetVertex[i] < facetVertex[i+1]) 
				{
					v0 = facetVertex[i];
					v1 = facetVertex[i+1];
				}
				else 
				{
					v0 = facetVertex[i+1];
					v1 = facetVertex[i];
				}
				foundMatch = 0;
				for (j = 0; j < model->objVertexList[v0].facetsNum; j++) 
				{
					for (k = 0; k < model->objVertexList[v1].facetsNum; k++) 
					{
						if (model->objVertexList[v0].facets[j] ==
							model->objVertexList[v1].facets[k]) 
						{
							if (model->objVertexList[v0].facets[j] != 
								model->facetCount) 
							{
			    				foundMatch = 1;
			    				break;
							}
						}
					}
					if (foundMatch)
						break;
				}

				if (foundMatch == 0) 
				{
					model->objVertexList[v0].edges[ 
						model->objVertexList[v0].edgesNum++] = model->edgeCount;
					model->objVertexList[v1].edges[
						model->objVertexList[v1].edgesNum++] = model->edgeCount;

					model->edgeList[model->edgeCount][0] = v0;
					model->edgeList[model->edgeCount][1] = v1;
					model->edgeCount++;
				}
				//添加该面到顶点记录中
				model->objVertexList[v0].facets[
					model->objVertexList[v0].facetsNum++] = model->facetCount;
				model->objVertexList[v1].facets[
					model->objVertexList[v1].facetsNum++] = model->facetCount;

				j = i;

				//将顶点作为三角形或多边形读入
				if (model->triangleFlag) 
				{
					if (j > 0) 
					{
						if ((i & 1) == 1)
							j = (i + 1) >> 1;
						else
							j = fvCount - (i >> 1);
					}
				}
				model->vertexList[model->vertexCount].draw = i;
				model->vertexList[model->vertexCount].x = 
					model->objVertexList[facetVertex[j]].x;
				model->vertexList[model->vertexCount].y = 
					model->objVertexList[facetVertex[j]].y;
				model->vertexList[model->vertexCount].z = 
					model->objVertexList[facetVertex[j]].z;
				if (model->haveNormals) 
				{
					model->vertexList[model->vertexCount].nx = 
					model->objVertexList[facetNormal[j]].nx;
					model->vertexList[model->vertexCount].ny = 
					model->objVertexList[facetNormal[j]].ny;
					model->vertexList[model->vertexCount].nz = 
					model->objVertexList[facetNormal[j]].nz;
				}	
				model->objVertexList[facetVertex[j]].vertexIndex = 
					model->vertexCount;
				model->vertexCount++;
			}
			model->facetCount++;
		}
		else if (inputLine[0] == 'l') 
		{
			//线
		}
		else if (inputLine[0] == 'p') 
		{
			//点
		}
		else if (inputLine[0] == 's') 
		{
	    
		}
		else if (inputLine[0] == 'u') 
		{
			if (strncmp("usemtl", inputLine, 6) != 0)
				continue;		
			if (materials == NULL)
				materials = readMaterials(FileName);

			sscanf(&inputLine[7], "%s", materialName);
			matPtr = materials;
			while ((strcmp(materialName, matPtr->name) != 0) &&
				(matPtr->name[0] != 0))
				matPtr++;
			if (matPtr->name[0] == 0)
				fprintf(stderr, "Can't find %s\n", materialName);
	  
			model->colorList[model->colorCount].index = model->vertexCount;
			model->colorList[model->colorCount].ra = matPtr->ra;
			model->colorList[model->colorCount].ga = matPtr->ga;
			model->colorList[model->colorCount].ba = matPtr->ba;
			model->colorList[model->colorCount].rd = matPtr->rd;
			model->colorList[model->colorCount].gd = matPtr->gd;
			model->colorList[model->colorCount].bd = matPtr->bd;
			model->colorList[model->colorCount].ad = matPtr->ad;
			model->colorList[model->colorCount].rs = matPtr->rs;
			model->colorList[model->colorCount].gs = matPtr->gs;
			model->colorList[model->colorCount].bs = matPtr->bs;
			model->colorList[model->colorCount].spec = matPtr->spec;
			model->colorCount++;
		}
    }

    model->vertexList[model->vertexCount].draw = 0;

    model->colorList[model->colorCount].index = model->vertexCount + 1;

     model->lineCount = 0;
    for (i = 0; i < model->edgeCount; i++) 
	{
		//寻找该边界的颜色
		model->lineList[model->lineCount].colorIndex = 0;
		for (j = 0; j <= model->colorCount; j++) 
		{
			if (model->objVertexList[model->edgeList[i][0]].vertexIndex <
				model->colorList[j].index) 
			{
				model->lineList[model->lineCount].colorIndex = j-1;
				break;
			}
		}

		model->lineList[model->lineCount].draw = 0;
		model->lineList[model->lineCount].x = 
			model->objVertexList[model->edgeList[i][0]].x;
		model->lineList[model->lineCount].y = 
			model->objVertexList[model->edgeList[i][0]].y;
		model->lineList[model->lineCount].z = 
			model->objVertexList[model->edgeList[i][0]].z;
		model->lineCount++;

		model->lineList[model->lineCount].draw = 1;
		model->lineList[model->lineCount].x = 
			model->objVertexList[model->edgeList[i][1]].x;
		model->lineList[model->lineCount].y = 
			model->objVertexList[model->edgeList[i][1]].y;
		model->lineList[model->lineCount].z = 
			model->objVertexList[model->edgeList[i][1]].z;
		model->lineCount++;
    }
    model->lineList[model->lineCount].draw = 0;

    int edgeBase;			
    model->lineStripCount = 0;
    edgeBase = 0;
    do 
	{
		while (model->edgeList[edgeBase][0] == -1)
			edgeBase++;
		if (edgeBase >= model->edgeCount)
			break;			/* Exit here */

		i = edgeBase;

		v0 = model->edgeList[i][0];
		v1 = model->edgeList[i][1];

		//寻找该边界的颜色
		model->lineStripList[model->lineStripCount].colorIndex = 0;
		for (j = 0; j <= model->colorCount; j++) 
		{
			if (model->objVertexList[v0].vertexIndex <=
				model->colorList[j].index) 
			{
				model->lineStripList[model->lineStripCount].colorIndex= j-1;
				break;
			}
		}

		model->lineStripList[model->lineStripCount].draw = 0;
		model->lineStripList[model->lineStripCount].x = 
			model->objVertexList[v0].x;
		model->lineStripList[model->lineStripCount].y = 
			model->objVertexList[v0].y;
		model->lineStripList[model->lineStripCount].z = 
			model->objVertexList[v0].z;
        model->lineStripCount++;

		model->lineStripList[model->lineStripCount].draw = 1;
		model->lineStripList[model->lineStripCount].x =
            model->objVertexList[v1].x;
		model->lineStripList[model->lineStripCount].y = 
			model->objVertexList[v1].y;
		model->lineStripList[model->lineStripCount].z = 
			model->objVertexList[v1].z;
		model->lineStripCount++;

		for (j=0; j<model->objVertexList[v0].edgesNum; j++) 
		{
			if (model->objVertexList[v0].edges[j] == edgeBase) 
			{
	    		model->objVertexList[v0].edges[j] = -1;
				break;
			}
		}
		for (j=0; j<model->objVertexList[v1].edgesNum; j++) 
		{
			if (model->objVertexList[v1].edges[j] == edgeBase) 
			{
	    		model->objVertexList[v1].edges[j] = -1;
				break;
			}
		}

		model->edgeList[i][0] = -1;			

		do 
		{
			foundMatch = 0;
			for (j=0; j<model->objVertexList[v1].edgesNum; j++) 
			{
				//寻找没有使用的边界
				if (model->objVertexList[v1].edges[j] != -1) 
				{ 
					if (model->edgeList[model->objVertexList[v1].edges[j]][0] 
						!= -1) 
					{
						foundMatch = 1;
						k = model->objVertexList[v1].edges[j];
						model->objVertexList[v1].edges[j] = -1;
						if (model->edgeList[k][0] == v1) 
						{
							//查找该边界的颜色
							model->lineStripList[
								model->lineStripCount].colorIndex = 0;
							for (m = 0; m <= model->colorCount; m++) 
							{
								if (model->objVertexList[
									model->edgeList[k][1]].vertexIndex <=
									model->colorList[m].index) 
								{
									model->lineStripList[
										model->lineStripCount].colorIndex= m-1;
									break;
								}
							}

  		 					model->lineStripList[model->lineStripCount].draw = 1;
							model->lineStripList[model->lineStripCount].x = 
								model->objVertexList[model->edgeList[k][1]].x;
							model->lineStripList[model->lineStripCount].y = 
								model->objVertexList[model->edgeList[k][1]].y;
							model->lineStripList[model->lineStripCount].z = 
								model->objVertexList[model->edgeList[k][1]].z;
							model->lineStripCount++;
							v1 = model->edgeList[k][1];
						}
						else 
						{
							//查找该边界的颜色
							model->lineStripList[
								model->lineStripCount].colorIndex = 0;
							for (m = 0; m <= model->colorCount; m++) 
							{
								if (model->objVertexList[
									model->edgeList[k][0]].vertexIndex <=
									model->colorList[m].index) 
								{
									model->lineStripList[
										model->lineStripCount].colorIndex= m-1;
									break;
								}
							}

		  					model->lineStripList[model->lineStripCount].draw = 1;
							model->lineStripList[model->lineStripCount].x = 
								model->objVertexList[model->edgeList[k][0]].x;
							model->lineStripList[model->lineStripCount].y = 
								model->objVertexList[model->edgeList[k][0]].y;
							model->lineStripList[model->lineStripCount].z = 
								model->objVertexList[model->edgeList[k][0]].z;
							model->lineStripCount++;
		  					v1 = model->edgeList[k][0];
						}
						model->edgeList[k][0] = -1; 
						break;
					}
				} 
            }  
		} while (foundMatch != 0);
    } while (edgeBase < model->edgeCount);
    model->lineStripList[model->lineStripCount].draw = 0;
    fclose(dataFile);
    free(materials);
} /* End of readObjData */


FILE * COBJFileRead::fileOpen(const char *filename,
    const char *mode) 
{
    FILE *retVal;
	retVal = fopen(filename, mode);
        if (retVal != NULL)    return retVal;
	return NULL;
}


MaterialColor * COBJFileRead::readMaterials(char *FileName)
{
    FILE *mtlFile;				//需要读入的材质文件
    char inputLine[256];		//输入线
    MaterialColor *matPtr;		//分配空间
    int i;						//数组索引
    int count;					//读入的数量
    GLfloat r, g, b;			//读入的颜色
    GLfloat spec;				//读入的高光值

	char MaterialName[256];
	strcpy(MaterialName,FileName);
    int index=strlen(FileName);
	strncpy(MaterialName+(index-3),"mtl",3);

    mtlFile = fileOpen(MaterialName, "r");
    if (mtlFile == NULL) {
	fprintf(stderr, "Error, could not open 'materials.mtl', exiting.\n");
	exit(1);
    }

    matPtr = (MaterialColor *)malloc(100 * sizeof(MaterialColor));

    i = -1;
    for(;;) {
	if (fgets(inputLine, 250, mtlFile) == NULL)
	    break;			//文件结尾

	if (strncmp("newmtl", inputLine, 6) == 0) {
	    i++;
	    sscanf(&inputLine[7], "%s", matPtr[i].name);
	}
	else if (strncmp("Ka", inputLine, 2) == 0) {
	    count = sscanf(inputLine, "Ka %f %f %f", &r, &g, &b);
	    if (count != 3)
		continue;
	    matPtr[i].ra = r;
	    matPtr[i].ga = g;
	    matPtr[i].ba = b;
	}
	else if (strncmp("Kd", inputLine, 2) == 0) {
	    count = sscanf(inputLine, "Kd %f %f %f", &r, &g, &b);
	    if (count != 3)
		continue;
	    matPtr[i].rd = r;
	    matPtr[i].gd = g;
	    matPtr[i].bd = b;
	    matPtr[i].ad = 1.0;
	}
	else if (strncmp("Ks", inputLine, 2) == 0) {
	    count = sscanf(inputLine, "Ks %f %f %f", &r, &g, &b);
	    if (count != 3)
		continue;
	    matPtr[i].rs = r;
	    matPtr[i].gs = g;
	    matPtr[i].bs = b;
	}
	else if (strncmp("Ns", inputLine, 2) == 0) {
	    count = sscanf(inputLine, "Ns %f", &spec);
	    if (count != 1)
		continue;
	    matPtr[i].spec = spec;
	}
    }
    i++;

    matPtr[i].name[0] = 0;		
    matPtr[i].ra = 0.0f;
    matPtr[i].ga = 0.1f;
    matPtr[i].ba = 0.0f;
    matPtr[i].rd = 0.2f;
    matPtr[i].gd = 1.0f;
    matPtr[i].bd = 0.0f;
    matPtr[i].ad = 1.0f;
    matPtr[i].rs = 1.0f;
    matPtr[i].gs = 0.8f;
    matPtr[i].bs = 0.0f;
    matPtr[i].spec = 25.0f;

    return matPtr;
} /* End of readMaterials */




