// LandTex.cpp: implementation of the CLandTex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyLOD.h"
#include "LandTex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLandTex::CLandTex()
{
	int x, y;

	for(x=0; x<4; x++) {
		for(y=0; y<4; y++) {
			m_Bmpload.destroy_bmp(tex[x][y]);
		}
	}
}

CLandTex::~CLandTex()
{

}

void CLandTex::NEW_BITMAP(unsigned int *tn, int *hf) 
{
	int x, z;
	int i;
	int tx, tz;
	int hf1[M_SIZE*M_SIZE];

	i = 0;

	for(x=0; x<4; x++) 
	{
		for(z=0; z<4; z++) 
		{
			if(!tex[x][z]) 
			{
				tex[x][z] = m_Bmpload.new_bitmap(256, 256);
				if(!tex[x][z]) 
				{
					return;
				}
			}

			texture_name[x][z] = tn[i];

			for(tx=0; tx<M_SIZE; tx++) 
			{
				for(tz=0; tz<M_SIZE; tz++) 
				{
					hf1[IX(tx, tz)] = hf[IX(x*64 + tx/4, z*64 + tz/4)];
				}		
			} 

			m_Bmpload.texture_terrain(tex[x][z], hf1);

			glBindTexture(GL_TEXTURE_2D, texture_name[x][z]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB5, tex[x][z]->w, tex[x][z]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex[x][z]->data);

			i++;
		}
	}
}