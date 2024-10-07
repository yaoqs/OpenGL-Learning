//========================================================
/**
*  @file      Camera.h
*
*  ��Ŀ������ TGA�ļ�����
*  �ļ�����:  �������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-12-06	
*  �޸����ڣ� 2006-12-07
*
*/     
//========================================================

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "stdafx.h"
#include "Vector.h"                 /**< ����������ͷ�ļ� */
#include "GLFrame.h"

/** ������� */
class Camera
{
public:
	/** ���캯������������ */
	Camera();
	~Camera();
	
	/** ��������״̬���� */
	Vector3 getPosition()   {	return m_Position;		}
	Vector3 getView()	    {	return m_View;			}
	Vector3 getUpVector()   {	return m_UpVector;		}
	float   getSpeed()      {   return m_Speed;         }

	/** �����ٶ� */
	void    setSpeed(float speed)
	{ 
		m_Speed  = speed;
	}
     
	/** �����������λ��, �۲����������� */
	void setCamera(float positionX, float positionY, float positionZ,
			 	   float viewX,     float viewY,     float viewZ,
				   float upVectorX, float upVectorY, float upVectorZ);

	/** ��ת��������� */
	void rotateView(float angle, float X, float Y, float Z);

	/** �����������������۲췽�� */
	void setViewByMouse(); 
	
    /** ����������ƶ� */
	void yawCamera(float speed);

	/** ǰ���ƶ������ */
	void moveCamera(float speed);
	
	/** ��������� */
	void setLook();

	/** ���߽� */
	void checkBound();

private:
	/** ��������� */
	Vector3        m_Position;      /**< λ�� */
	Vector3        m_View;          /**< ���� */
	Vector3        m_UpVector;      /**< �������� */
	float          m_Speed;         /**< �ٶ� */

};

#endif //__CAMERA_H__