// ParticleSystem.h: interface for the CParticleSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTICLESYSTEM_H__1C8B40FC_7CBA_487E_BD73_EDCA48A2969C__INCLUDED_)
#define AFX_PARTICLESYSTEM_H__1C8B40FC_7CBA_487E_BD73_EDCA48A2969C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Particle.h"
//定义最多的粒子数
#define MAX_PARTICLES 5000
// 定义随机数
#define RANDOM_NUM (static_cast<float>(rand())/static_cast<float>(RAND_MAX))

#define MIN_SPEED			0.0f	
#define MIN_LIFETIME    	0.1f	
#define MIN_SPREAD	    	0.01f	
#define MIN_EMISSION    	1.0f	
#define MIN_SIZE			0.1f	
#define MIN_GRAVITY	    	-0.5f	 
#define MIN_ALPHA			0.0f	 
#define MAX_SPEED			25.0f	
#define MAX_LIFETIME    	15.0f	
#define MAX_SPREAD	    	180.0f	
#define MAX_EMISSION        1000.0f	
#define MAX_SIZE			4.0f	
#define MAX_GRAVITY	    	0.5f	 
#define MAX_ALPHA			1.0f	 
#define GRAVITY				9.8f 
#define Clamp(x, min, max)  x = (x<min  ? min : x<max ? x : max);

class CParticleSystem  
{
public:
	CParticleSystem();
	virtual ~CParticleSystem();
	Draw(float,float);// 绘制粒子系统
	Update(float fTime);// 粒子系统的更新
	bool IsColliding();// 碰撞处理
	// 成员变量
	float m_fTimeLastUpdate;
	bool m_bIsColliding;
	bool m_bIsMoving;
	float m_fLifeTime;
	float m_fLifeVar;
	float m_fAlphaStart;
	float m_fAlphaEnd;
	float m_fAlphaVar;
	float m_fSizeStart;
	float m_fSizeEnd;
	float m_fSizeVar;
	float m_fSpeed;
	float m_fGravityVar;
	float m_fSpeedVar;
	float m_fTheta;
	float m_fBoing;
	bool m_bIsSuppressed;
	bool m_bIsFloor;
	POINTVECTOR m_vPrevLocation;
	POINTVECTOR m_vLocation;
	POINTVECTOR m_vGravityStart;
	POINTVECTOR m_vGravityEnd;
	COLORVECTOR m_vColorStart;
	COLORVECTOR m_vColorEnd;
	COLORVECTOR m_vColorVar;
	unsigned int m_uParticlesPerSec;
	unsigned int m_uParticlesAlive;

	CParticle m_rParticles[MAX_PARTICLES];
private:
	float fColorArray[4];
	float m_fEmissionResidue;
	float fVarHoriz;
	float fVarz;
	float fVarx;
	POINTVECTOR m_vTempVelocity;

};

#endif // !defined(AFX_PARTICLESYSTEM_H__1C8B40FC_7CBA_487E_BD73_EDCA48A2969C__INCLUDED_)
