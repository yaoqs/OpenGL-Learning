// BMPLoad.cpp: implementation of the CBMPLoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyLOD.h"
#include "BMPLoad.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBMPLoad::CBMPLoad()
{

}

CBMPLoad::~CBMPLoad()
{

}


TEXTURE *CBMPLoad::load_bitmap(char* filename) 
{

	TEXTURE *bmp;
	PAL colour;
	int x, y, i;
	WIN3XHEAD h1;
	WIN3XINFOHEAD h2;
	FILE *fp = fopen(filename, "rb");

	if(fp) 
	{

		bmp = new TEXTURE;
		if(!bmp) 
		{
			MessageBox(NULL,"Unable to allocate texture map.","Error",MB_OK);
		}

		fread(&h1.ImageFileType, sizeof(h1.ImageFileType), 1, fp);
		fread(&h1.FileSize, sizeof(h1.FileSize), 1, fp);
		fread(&h1.Reserved1, sizeof(h1.Reserved1), 1, fp);
		fread(&h1.Reserved2, sizeof(h1.Reserved2), 1, fp);
		fread(&h1.ImageDataOffset, sizeof(h1.ImageDataOffset), 1, fp);

		fread(&h2.HeaderSize, sizeof(h2.HeaderSize), 1, fp);
		fread(&h2.ImageWidth, sizeof(h2.ImageWidth), 1, fp);
		fread(&h2.ImageHeight, sizeof(h2.ImageHeight), 1, fp);
		fread(&h2.NumberOfImagePlanes, sizeof(h2.NumberOfImagePlanes), 1, fp);
		fread(&h2.BitsPerPixel, sizeof(h2.BitsPerPixel), 1, fp);
		fread(&h2.CompressionMethod, sizeof(h2.CompressionMethod), 1, fp);
		fread(&h2.SizeOfBitmap, sizeof(h2.SizeOfBitmap), 1, fp);
		fread(&h2.HorzResolution, sizeof(h2.HorzResolution), 1, fp);
		fread(&h2.VertResolution, sizeof(h2.VertResolution), 1, fp);
		fread(&h2.NumColorsUsed, sizeof(h2.NumColorsUsed), 1, fp);
		fread(&h2.NumSignificantColors, sizeof(h2.NumSignificantColors), 1, fp);

		bmp -> w = h2.ImageWidth;
		bmp -> h = h2.ImageHeight;
		bmp -> data = new unsigned char[((bmp -> w)*(bmp -> h))*3];

		
		if(!bmp) 
		{
			MessageBox(NULL,"Unable to allocate texture map data.","Error",MB_OK);
		}

		i = 0;

		for(x=0; x<bmp->w; x++) {
			for(y=0; y<bmp->h; y++) {
				fread(&colour, sizeof(colour), 1, fp);
            bmp -> data[i+0] = (unsigned char) ((int)colour.b); 
				bmp -> data[i+1] = (unsigned char) ((int)colour.g);
            bmp -> data[i+2] = (unsigned char) ((int)colour.r); 
				i += 3;
      		}
		}

		fclose(fp);

		if(!bmp || !bmp->data) 
		{
			return NULL;
		}
		else 
		{
			return bmp;
		}

   }
   else {

	   return NULL;

   }
}

void CBMPLoad::GET_COLOR(TEXTURE *tex, int x, int y, BYTE *r, BYTE *g, BYTE *b) 
{
	if((x < tex->w) && (y < tex->h)) 
	{
		*r = tex->data[(x + (y*tex->w))*3 + 0];
		*g = tex->data[(x + (y*tex->w))*3 + 1];
		*b = tex->data[(x + (y*tex->w))*3 + 2];
	}
}

void CBMPLoad::SET_COLOR(TEXTURE *tex, int x, int y, BYTE r, BYTE g, BYTE b) 
{
	if((x < tex->w) && (y < tex->h)) 
	{
		tex->data[(x + (y*tex->w))*3 + 0] = r;
		tex->data[(x + (y*tex->w))*3 + 1] = g;
		tex->data[(x + (y*tex->w))*3 + 2] = b;
	}
}

TEXTURE *CBMPLoad::new_bitmap(int x, int y) 
{
	TEXTURE *bmp;
	
	bmp = new TEXTURE;
	if(!bmp) 
	{
		MessageBox(NULL,"Unable to allocate texture map.","Error",MB_OK);
	}
	
	bmp -> w = x;
	bmp -> h = y;
	bmp -> data = new unsigned char[((bmp -> w)*(bmp -> h))*3];
	
	if(!bmp || !bmp->data) {
		return NULL;
	}
	else {
		return bmp;
	}
}

void CBMPLoad::destroy_bmp(TEXTURE *bmp)
{
	if (bmp) {
		if (bmp->data) {
			delete[] bmp->data;
		}

		delete[] bmp; 
	}
}


int CBMPLoad::limit255(int a) 
{
	if(a < 0) {
		return 0;
	}
	else if(a > 255) {
		return 255;
	}
	else {
		return a;
	}
}

float CBMPLoad::texture_factor(int h1, int h2) 
{
	float t;
	t = (64 - abs(h1 - h2)) / 64.0f;

	if(t < 0.0f) t = 0.0f;
	else if(t > 1.0f) t = 1.0f;

	return t;
}

int CBMPLoad::IX_MAP(int x, int z) 
{
	if(x < 0) {
		x = 0;
	}
	else if(x > 255) {
		x = 255;
	}

	if(z < 0) {
		z = 0;
	}
	else if(z > 255) {
		z = 255;
	}

	return IX(x, z);
}

void CBMPLoad::texture_terrain(TEXTURE *t, int *hf) 
{
	int x, z;
	int h1;
	int bsize, csize;
	float f0;
	float f1;
	float f2;
	float f3;
	float f4;

	BYTE r[5], g[5], b[5];
	BYTE new_r, new_g, new_b;
	TEXTURE *tex[4];

	bsize = 4;
	csize = 2;

	while(csize > 0) {

		for(x=0; x<M_SIZE-0; x+=bsize) {
			for(z=0; z<M_SIZE-0; z+=bsize) {
				hf[IX_MAP(x+csize, z+csize)] = f4(hf[IX_MAP(x, z)], hf[IX_MAP(x+bsize, z)], hf[IX_MAP(x+bsize, z+bsize)], hf[IX_MAP(x, z+bsize)]);
			}
		}
		
		for(x=0; x<M_SIZE-0; x+=bsize) {
			for(z=0; z<M_SIZE-0; z+=bsize) {
				hf[IX_MAP(x+csize, z)] = f4(hf[IX_MAP(x, z)],
					hf[IX_MAP(x+bsize, z)],
					hf[IX_MAP(x+csize, z+csize)],
					hf[IX_MAP(x+csize, z-csize)]);
			}
		}
		
		for(x=0; x<M_SIZE-0; x+=bsize) {
			for(z=0; z<M_SIZE-0; z+=bsize) {
				hf[IX_MAP(x, z+csize)] = f4(hf[IX_MAP(x, z)],
					hf[IX_MAP(x, z+bsize)],
					hf[IX_MAP(x-csize, z+csize)],
					hf[IX_MAP(x+csize, z+csize)]);
			}
		} 
		
		bsize /= 2;
		csize /= 2;
	}

	tex[0] = load_bitmap("TEX0.BMP");
	tex[1] = load_bitmap("TEX1.BMP");
	tex[2] = load_bitmap("TEX2.BMP");
	tex[3] = load_bitmap("TEX3.BMP");

	for(x=0; x<M_SIZE; x++) {
		for(z=0; z<M_SIZE; z++) {
			h1 = limit255(hf[IX(x, z)]);
			
			f4 = texture_factor(256, h1);
			f3 = texture_factor(192, h1);
			f2 = texture_factor(128, h1);
			f1 = texture_factor(64, h1);
			f0 = texture_factor(0, h1);
			
			GET_COLOR(tex[0], x, z, &r[0], &g[0], &b[0]);			
			GET_COLOR(tex[1], x, z, &r[1], &g[1], &b[1]);
			GET_COLOR(tex[2], x, z, &r[2], &g[2], &b[2]);			
			GET_COLOR(tex[3], x, z, &r[3], &g[3], &b[3]);
			
			new_r = limit255((r[0] * f0) + (r[1] * f1) + (r[2] * f2) + (r[3] * f3) + (r[3] * f4)); // + (r[1] * f3) + (r[1] * f4));
			new_g = limit255((g[0] * f0) + (g[1] * f1) + (g[2] * f2) + (g[3] * f3) + (g[3] * f4)); // + (g[1] * f3) + (g[1] * f4));
			new_b = limit255((b[0] * f0) + (b[1] * f1) + (b[2] * f2) + (b[3] * f3) + (b[3] * f4)); // + (b[1] * f3) + (b[1] * f4));
			
			SET_COLOR(t, x, z, new_r, new_g, new_b); 
		}
	}

	destroy_bmp(tex[0]);
	destroy_bmp(tex[1]);
	destroy_bmp(tex[2]);
	destroy_bmp(tex[3]);
}

