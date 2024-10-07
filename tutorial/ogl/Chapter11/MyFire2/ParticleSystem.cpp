// ParticleSystem.cpp: implementation of the CParticleSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyFire2.h"
#include "ParticleSystem.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParticleSystem::CParticleSystem()
{
	m_fEmissionResidue = 0.0f;
	m_bIsSuppressed = FALSE;
	fVarx = 0.8f;
}

CParticleSystem::~CParticleSystem()
{

}

bool CParticleSystem::IsColliding()
{
	return m_bIsColliding;
}

//////////////////////////////////////////////////
//粒子系统更新函数
CParticleSystem::Update(float fTime)
{
	// fTime是绝对时间，必须计算相对时间间隔
	float fTimeDelta = fTime - m_fTimeLastUpdate;
	m_fTimeLastUpdate = fTime;
	if (m_bIsMoving)
	{
		static float fThetaHoriz = 0.0f;
		static float fThetaVert = 180.0f;
		fThetaHoriz += 25.0f * fTimeDelta;
		fThetaVert += 35.0f * fTimeDelta*fVarx;
		if ( fThetaHoriz > 359.0f ) 
		{
			fThetaHoriz = 0.0f;
		}
		if ( fThetaVert > 359.0f ) 
		{
			fVarx = RANDOM_NUM*1.0f+1.0f;
			fThetaVert = 0.0f;
		}
		m_vLocation.x = 20.0f * (float)cos( fThetaHoriz * 0.01745f );//*0.75f;
		m_vLocation.y =  7.0f * (float)sin( fThetaVert * 0.01745f );//*0.75f;
		m_vLocation.z = 20.0f * (float)sin( fThetaHoriz * 0.01745f )*(float)sin( fThetaVert * 0.01745f );//*0.75f;
	}
	else
	{
		m_vLocation.x = 0.0f;
		m_vLocation.y = 0.0f;
		m_vLocation.z = 0.0f;
	}
	m_uParticlesAlive = 0;
	// 更新所有的粒子
	for ( int i=0; i<MAX_PARTICLES; i++)
	{
		if (m_rParticles[i].m_fAge >= 0.0f )
			if ( m_rParticles[i].Update( fTimeDelta )) 
				m_uParticlesAlive++;
	}
	float fParticlesNeeded = m_uParticlesPerSec * fTimeDelta + m_fEmissionResidue;
	unsigned int uParticlesCreated = (unsigned int)fParticlesNeeded;
	if ( !m_bIsSuppressed )	
	{
		m_fEmissionResidue = fParticlesNeeded - uParticlesCreated;
	}	
	else	
	{		
		m_fEmissionResidue = 0.0f;		
		uParticlesCreated = 0;	
	}
	if ( uParticlesCreated > 0 )
	{
		// 循环所有粒子
		for ( i=0; i<MAX_PARTICLES; i++ )
		{
			if ( !uParticlesCreated )
				break;
			// 判断粒子生命
			if ( m_rParticles[i].m_fAge < 0.0f ) 
			{
				// 定义新粒子的生命
				m_rParticles[i].m_fAge = 0.0f;
				m_rParticles[i].m_fLifetime = m_fLifeTime+RANDOM_NUM * m_fLifeVar;
				Clamp( m_rParticles[i].m_fLifetime, MIN_LIFETIME, MAX_LIFETIME ); 

				m_rParticles[i].m_fAlpha = m_fAlphaStart + RANDOM_NUM * m_fAlphaVar;
				Clamp( m_rParticles[i].m_fAlpha, MIN_ALPHA, MAX_ALPHA );
				m_rParticles[i].m_fAlphaDelta = (m_fAlphaEnd - m_rParticles[i].m_fAlpha) / m_rParticles[i].m_fLifetime;
				// 粒子的颜色
				m_rParticles[i].m_vColor.r = m_vColorStart.r+ RANDOM_NUM * m_vColorVar.r;
				m_rParticles[i].m_vColor.g = m_vColorStart.g + RANDOM_NUM * m_vColorVar.g;
				m_rParticles[i].m_vColor.b = m_vColorStart.b + RANDOM_NUM * m_vColorVar.b;

				Clamp( m_rParticles[i].m_vColor.r, 0.0f, 1.0f );
				Clamp( m_rParticles[i].m_vColor.g, 0.0f, 1.0f );
				Clamp( m_rParticles[i].m_vColor.b, 0.0f, 1.0f );

				m_rParticles[i].m_vColorDelta.r = ((m_vColorEnd.r+ RANDOM_NUM * m_vColorVar.r) - m_rParticles[i].m_vColor.r) / m_rParticles[i].m_fLifetime;
				m_rParticles[i].m_vColorDelta.g = ((m_vColorEnd.g+ RANDOM_NUM * m_vColorVar.g) - m_rParticles[i].m_vColor.g) / m_rParticles[i].m_fLifetime;
				m_rParticles[i].m_vColorDelta.b = ((m_vColorEnd.b+ RANDOM_NUM * m_vColorVar.b) - m_rParticles[i].m_vColor.b) / m_rParticles[i].m_fLifetime;
				
				m_rParticles[i].m_fSize = m_fSizeStart + RANDOM_NUM * m_fSizeVar;
				Clamp( m_rParticles[i].m_fSize, MIN_SIZE, MAX_SIZE );
				m_rParticles[i].m_fSizeDelta = (m_fSizeEnd - m_rParticles[i].m_fSize) / m_rParticles[i].m_fLifetime;
				
				// 定义重力
					m_rParticles[i].m_vParticleGravity.x = 	m_vGravityStart.x * GRAVITY + RANDOM_NUM * m_fGravityVar*GRAVITY;
					Clamp( m_rParticles[i].m_vParticleGravity.x, MIN_GRAVITY*GRAVITY, MAX_GRAVITY*GRAVITY );

					m_rParticles[i].m_vGravityDelta.x = 
									( m_vGravityEnd.x*GRAVITY - m_rParticles[i].m_vParticleGravity.x ) / m_rParticles[i].m_fLifetime;

					m_rParticles[i].m_vParticleGravity.y = 	m_vGravityStart.y * GRAVITY + RANDOM_NUM * m_fGravityVar*GRAVITY;
					Clamp( m_rParticles[i].m_vParticleGravity.y, MIN_GRAVITY*GRAVITY, MAX_GRAVITY*GRAVITY );

					m_rParticles[i].m_vGravityDelta.y = 
									( m_vGravityEnd.y*GRAVITY - m_rParticles[i].m_vParticleGravity.y ) / m_rParticles[i].m_fLifetime;

					m_rParticles[i].m_vParticleGravity.z = 	m_vGravityStart.z * GRAVITY + RANDOM_NUM * m_fGravityVar*GRAVITY;
					Clamp( m_rParticles[i].m_vParticleGravity.z, MIN_GRAVITY*GRAVITY, MAX_GRAVITY*GRAVITY );

					m_rParticles[i].m_vGravityDelta.z = 
									( m_vGravityEnd.z*GRAVITY - m_rParticles[i].m_vParticleGravity.z ) / m_rParticles[i].m_fLifetime;

				// 计算粒子的速度 
				m_vTempVelocity.x = (m_vLocation.x - m_vPrevLocation.x)/fTimeDelta;
				m_vTempVelocity.y = (m_vLocation.y - m_vPrevLocation.y)/fTimeDelta;
				m_vTempVelocity.z = (m_vLocation.z - m_vPrevLocation.z)/fTimeDelta;
				// 从当前位置和前一个位置发射粒子
				m_rParticles[i].m_vLocation.x = m_vPrevLocation.x;
				m_rParticles[i].m_vLocation.y = m_vPrevLocation.y;
				m_rParticles[i].m_vLocation.z = m_vPrevLocation.z;
				// 更新前一位置
				m_rParticles[i].m_vPrevLocation.x = m_rParticles[i].m_vLocation.x;
				m_rParticles[i].m_vPrevLocation.y = m_rParticles[i].m_vLocation.y;
				m_rParticles[i].m_vPrevLocation.z = m_rParticles[i].m_vLocation.z;
				// 定义发射器的方向
				float RandomYaw = RANDOM_NUM * 3.14159f * 2.0f;
				float RandomPitch = RANDOM_NUM * m_fTheta * 3.14159f ;/// 180.0f ;
				// 利用球面坐标定义速度矢量
				m_rParticles[i].m_vVelocity.y = static_cast<float>(cos( RandomPitch ));
				m_rParticles[i].m_vVelocity.x = static_cast<float>(sin(RandomPitch) * cos(RandomYaw));
				m_rParticles[i].m_vVelocity.z = static_cast<float>(sin(RandomPitch) * sin(RandomYaw));
				m_rParticles[i].m_vVelocity.x *= m_fSpeed ;
				m_rParticles[i].m_vVelocity.y *= m_fSpeed ;
				m_rParticles[i].m_vVelocity.z *= m_fSpeed ;
			    // 设置粒子的双亲
				m_rParticles[i].SetParent(this);
				// 减少所需粒子数
				uParticlesCreated--;
			}
		}
	}
	// 将当前位置设置为前一位置
	m_vPrevLocation = m_vLocation;	

}

// 绘制粒子系统
CParticleSystem::Draw(float x_Rot,float y_Rot)
{
int loop;

	for (loop = 0; loop < MAX_PARTICLES; loop++)
	{
		// 如果粒子处于生命期,则绘制
		if (m_rParticles[loop].m_fAge >= 0.0f)
		{
			glColor4f(m_rParticles[loop].m_vColor.r,m_rParticles[loop].m_vColor.g,
								m_rParticles[loop].m_vColor.b,m_rParticles[loop].m_fAlpha);

			glPushMatrix();
			glTranslatef(m_rParticles[loop].m_vLocation.x,
										m_rParticles[loop].m_vLocation.y,
											m_rParticles[loop].m_vLocation.z);
			
			glRotatef(y_Rot,0.0f,1.0f,0.0f);
			glRotatef(x_Rot,1.0f,0.0f,0.0f);

			glBegin(GL_TRIANGLE_STRIP);						
			  glTexCoord2f(1.0f, 1.0f); glVertex3f( m_rParticles[loop].m_fSize, m_rParticles[loop].m_fSize, 0.0f); // Top Right
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_rParticles[loop].m_fSize, m_rParticles[loop].m_fSize, 0.0f); // Top Left
				glTexCoord2f(1.0f, 0.0f); glVertex3f( m_rParticles[loop].m_fSize,-m_rParticles[loop].m_fSize, 0.0f); // Bottom Right
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_rParticles[loop].m_fSize,-m_rParticles[loop].m_fSize, 0.0f);// Bottom Left
			glEnd();									
			glPopMatrix();
		}
	}
	// 绘制地面
	if(	m_bIsColliding)
	{
		glPushAttrib(GL_TEXTURE_BIT);
		// 关闭纹理
		glDisable(GL_TEXTURE_2D);
		glLineWidth(1.0f);
		glColor4f(0.4f,0.6f,0.6f,0.9f);
		// 绘制一个小烛台
		glBegin(GL_LINES);
				glVertex3f( m_vLocation.x,m_vLocation.y-m_fSizeStart*0.5f,m_vLocation.z);
				glVertex3f( m_vLocation.x,m_vLocation.y-m_fSizeStart*3.0f,m_vLocation.z);
		glEnd();
		// 绘制地面
		glTranslatef(0.0f,FLOOR,0.0f);
		glColor4f(0.0f,0.3f,0.3f,0.7f);
		glBegin(GL_LINE_STRIP);
				glVertex3f(-20.0f,-0.0f,-20.0f);
				glVertex3f(-20.0f,-0.0f, 20.0f);
				glVertex3f( 20.0f,-0.0f, 20.0f);
				glVertex3f( 20.0f,-0.0f,-20.0f);
				glVertex3f(-20.0f,-0.0f,-20.0f);
		glEnd();
		glBegin(GL_LINE_STRIP);
				glVertex3f(-10.0f,-0.0f,-10.0f);
				glVertex3f(-10.0f,-0.0f, 10.0f);
				glVertex3f( 10.0f,-0.0f, 10.0f);
				glVertex3f( 10.0f,-0.0f,-10.0f);
				glVertex3f(-10.0f,-0.0f,-10.0f);
		glEnd();
		glPopAttrib();
	}
}



