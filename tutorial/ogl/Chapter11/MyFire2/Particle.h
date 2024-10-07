// Particle.h: interface for the CParticle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTICLE_H__6EB60624_CB94_485C_8F64_CCD3E2455B16__INCLUDED_)
#define AFX_PARTICLE_H__6EB60624_CB94_485C_8F64_CCD3E2455B16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 地面基准
#define FLOOR -7.0f
// 颜色的red green blue分量
struct COLORVECTOR{
	float r,g,b;
};
// 位置的3D坐标
struct POINTVECTOR{
	float x,y,z;
};

class CParticle  
{
public:

	friend class CParticleSystem;
	bool Update( float fTimeDelta );
	CParticle();
	virtual ~CParticle();
// 设置粒子系统为粒子的双亲
	void SetParent(CParticleSystem* Parent){ m_pParent = Parent;}
// 粒子的成员变量
	float m_fAlpha;
	float m_fAge;
	float m_fLifetime;
	float m_fAlphaDelta;
	float m_fSizeDelta;
	float m_fSize;
	COLORVECTOR m_vColor;
	COLORVECTOR m_vColorDelta;
	POINTVECTOR m_vLocation;
	POINTVECTOR m_vPrevLocation;
	POINTVECTOR m_vVelocity;
	POINTVECTOR m_vParticleGravity;
	POINTVECTOR m_vGravityDelta;
private:
	// 粒子所属的粒子系统
	CParticleSystem* m_pParent;

};

#endif // !defined(AFX_PARTICLE_H__6EB60624_CB94_485C_8F64_CCD3E2455B16__INCLUDED_)
