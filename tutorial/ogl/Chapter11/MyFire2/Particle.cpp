// Particle.cpp: implementation of the CParticle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyFire2.h"
#include "Particle.h"
#include "ParticleSystem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParticle::CParticle()
{
		m_vLocation.x = 0.0f;
		m_vLocation.y = 0.0f;
		m_vLocation.z = 0.0f;

		m_vPrevLocation.x = 0.0f;
		m_vPrevLocation.y = 0.0f;
		m_vPrevLocation.z = 0.0f;

		m_vParticleGravity.x      = 1.0f;
		m_vGravityDelta.x = 1.0f;
		m_vParticleGravity.y      = 1.0f;
		m_vGravityDelta.y = 1.0f;
		m_vParticleGravity.z      = 1.0f;
		m_vGravityDelta.z = 1.0f;

		m_vVelocity.x = 0.0f;
		m_vVelocity.y = 0.0f;
		m_vVelocity.z = 0.0f;

		m_vColor.r = 0.3f;
		m_vColor.g = 0.3f;
		m_vColor.b = 0.3f;

		m_vColorDelta.r = 0.0f;
		m_vColorDelta.g = 0.0f;
		m_vColorDelta.b = 0.0f;

		m_fAge      = -1.0f;
		m_fLifetime = -1.0f;

		m_fAlpha      = 0.0f;
		m_fAlphaDelta = 0.0f;

		m_fSizeDelta  = 1.0f;
		m_fSize			  = 1.0f;

}

CParticle::~CParticle()
{

}


bool CParticle::Update( float fTimeDelta )
{
	if ( m_fAge + fTimeDelta >= m_fLifetime ) 
	{
		m_fAge = -1.0f;
		return FALSE;
	}
	else
	{
		// ���ӵ�����
		m_fAge += fTimeDelta;
    	// �������ӵ�λ��
		m_vPrevLocation.x = m_vLocation.x;
		m_vPrevLocation.y = m_vLocation.y;
		m_vPrevLocation.z = m_vLocation.z;
		// ���ӵ�ǰ��λ��
		m_vLocation.x += m_vVelocity.x * fTimeDelta;
		m_vLocation.y += m_vVelocity.y * fTimeDelta;
		m_vLocation.z += m_vVelocity.z * fTimeDelta;

		if ( m_pParent->IsColliding() ) // ��ײ����
		{
			if ( m_vLocation.y < FLOOR ) 
			{
				if ( m_vVelocity.y > -5.0f )  // -5.0f <= velocity.y <= 0.0f
				{
					m_vLocation.y = FLOOR;
					m_vVelocity.y = 0.0f;
				}
				else
				{
					m_vLocation.y = m_vPrevLocation.y; 
					m_vVelocity.y = -m_vVelocity.y*m_pParent->m_fBoing;
				}
			}

		}
		m_vVelocity.x += (9.8f * m_vParticleGravity.x * fTimeDelta );
		m_vVelocity.y += (9.8f *  m_vParticleGravity.y * fTimeDelta );
		m_vVelocity.z += (9.8f *  m_vParticleGravity.z * fTimeDelta );
		// �������ӵ�ǰ��Alphaֵ
		m_fAlpha += m_fAlphaDelta * fTimeDelta;
		// �������ӵ�ǰ����ɫ
		m_vColor.r += m_vColorDelta.r * fTimeDelta;
		m_vColor.g += m_vColorDelta.g * fTimeDelta;
		m_vColor.b += m_vColorDelta.b * fTimeDelta;
		// ���ӵĴ�С
		m_fSize += m_fSizeDelta * fTimeDelta;
		// �������ӵ��������ٶ� 
		m_vParticleGravity.x += m_vGravityDelta.x * fTimeDelta;
		m_vParticleGravity.y += m_vGravityDelta.y * fTimeDelta;
		m_vParticleGravity.z += m_vGravityDelta.z * fTimeDelta;
	}

	return TRUE;
}
