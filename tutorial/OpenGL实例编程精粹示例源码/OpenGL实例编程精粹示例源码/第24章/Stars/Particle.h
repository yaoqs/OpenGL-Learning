//======================================================================
/**
*  @file      Particle.h
*
*  ��Ŀ������ ����ϵͳ
*  �ļ�����:  ���Ӷ����� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-12-18	
*  �޸����ڣ� 2006-12-19
*	
*/																			
//======================================================================

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "stdafx.h"
#include "BMPLoader.h"


/** ���ӽṹ */
struct Particle
{
	float x,y,z;		    /**< ���ӵ�λ�� */
	unsigned int  r,g,b;	/**< ���ӵ���ɫ */
	float vx,vy,vz;         /**< ���ӵ��ٶ�(x,y,z����) */
	float ax,ay,az;         /**< ������x��y��z�ϵļ��ٶ� */
	float lifetime;	        /**< ��������ֵ */
	float size;		        /**< ���ӳߴ� */
	float dec;		        /**< ������ʧ���ٶ� */
};

/** ������ */
class CParticle
{
private:
	CBMPLoader  texture[2];         /**< ����λͼ */
	Particle*   data;				/**< ����ָ�� */
	int         numparticle;	    /**< ������Ŀ */
	

public:

	CParticle();          /**< ���캯�� */

	~CParticle();         /**< �������� */
	
	/** ������������ */
	int Create(long num);
	
	/** ���úͻ�ȡ��ɫ���� */
	int SetColor(GLint r,GLint g,GLint b);
	int SetColor(GLint index,GLint r,GLint g,GLint b);
	int GetColor(GLint index,GLint &r,GLint &g,GLint &b);
	
	/** ���úͻ�ȡ�ٶ����� */
	int SetVelocity(GLfloat vx,GLfloat vy,GLfloat vz);
	int SetVelocity(GLint index,GLfloat vx,GLfloat vy,GLfloat vz);
	int GetVelocity(GLint index,GLfloat &vx,GLfloat &vy,GLfloat &vz);
	
	/** ���úͻ�ȡλ������ */	
	int SetPosition(GLfloat x,GLfloat y,GLfloat z);
	int SetPosition(GLint index,GLfloat x,GLfloat y,GLfloat z);
	int GetPosition(GLint index,GLfloat &x,GLfloat &y,GLfloat &z);
	
	/** ���úͻ�ȡ���ٶ����� */
	int SetAcceleration(GLfloat ax,GLfloat ay,GLfloat az);
	int SetAcceleration(GLint index,GLfloat ax,GLfloat ay,GLfloat az);
	int GetAcceletation(GLint index,GLfloat &ax,GLfloat &ay,GLfloat &az);

	/** ���úͻ�ȡ�ߴ����� */
	int SetSize(GLfloat size);
	int SetSize(GLint index,GLfloat size);
	int GetSize(GLint index,GLfloat &size);

	/** ���úͻ�ȡ��ʧ�ٶ����� */
	int SetDec(GLfloat dec);
	int SetDec(GLint index,GLfloat dec);
	int GetDec(GLint index,GLfloat &dec);
	
	/** ���úͻ�ȡ����ֵ���� */
	int SetLifeTime(GLfloat lifetime);
	int SetLifeTime(GLint index,GLfloat lifetime);
	int GetLifeTime(GLint index,GLfloat &lifetime);

	/** ����ͻ�ȡ���� */
	bool LoadTextures();
	unsigned int GetTexture(int index);

	/** ��ȡ���������ַ */
	Particle *GetParticle()	{	return data;		}
	
	/** ������ӵ���Ŀ */
	int GetNumOfParticle()	{	return numparticle;	}

	/** ����������е����� */
	int GetAll(int index,								/**< ���� */
				GLint &r,GLint &g,GLint &b,				/**< ���ӵ���ɫ */
				GLfloat &x,GLfloat &y,GLfloat &z,		/**< λ�� */
				GLfloat &vx,GLfloat &vy,GLfloat &vz,	/**< �ٶ� */
				GLfloat &ax,GLfloat &ay,GLfloat &az,	/**< ���ٶ� */
				GLfloat &size,							/**< ��С */
				GLfloat &lifetime,						/**< ����ʱ�� */
				GLfloat &dec							/**< ��ʧ�ٶ� */
				);

	/** �������ӵ��������� */
	int SetAll(int index,							/**< ���� */
				GLint r,GLint g,GLint b,			/**< ���ӵ���ɫ */
				GLfloat x,GLfloat y,GLfloat z,		/**< λ�� */	
				GLfloat vx,GLfloat vy,GLfloat vz,	/**< �ٶ� */
				GLfloat ax,GLfloat ay,GLfloat az,	/**< ���ٶ� */
				GLfloat size,						/**< ��С */
				GLfloat lifetime,					/**< ����ʱ�� */
				GLfloat dec						    /**< ��ʧ�ٶ� */
				);


};


#endif