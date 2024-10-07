//========================================================
/**
*  @file      Vector.cpp
*
*  ��Ŀ������ ��ײ���
*  �ļ�����:  ������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-12-06	
*  �޸����ڣ� 2006-12-20
*
*/     
//========================================================

#include "Vector.h"                       /**< ����ͷ�ļ� */
#include "Tray.h"

/** �����������ߵ��е� */
Vector3::Vector3(const TRay &ray1, const TRay &ray2) 
{

	Vector3 point1, point2;

	if (ray1.adjacentPoints(ray2, point1, point2))

		*this = (point1 + point2)*0.5;

	else

		*this = Vector3();

}

/** ��λ�� */
Vector3 &Vector3::unit() {

	if (isDefault()) {

		double rep = mag();

		if (rep < ZERO) {

			x = 0.0;

			y = 0.0;

			z = 0.0;

		} 
		else 
		{

			double temp = 1.0 / rep;

			x *= temp;

			y *= temp;

			z *= temp;

		}

		status = UNIT;

	}

	return *this;

}

Vector3 &Vector3::Default() {

	if (isUnit())

		status = DEFAULT;

	return *this;

}


/** �õ��෴���� */
Vector3 &Vector3::invert(const Vector3 &v1, Vector3 &result) {

	if (v1.isValid()) 
	{

		result.x = -v1.x;

		result.y = -v1.y;

		result.z = -v1.z;

		result.status = v1.status;

	} 
	else

		result = Vector3();

	return result;

}

/** ������� */
Vector3 &Vector3::add(const Vector3 &v1, const Vector3 &v2, Vector3 &result) 
{

	if (v1.isValid() && v2.isValid()) {

		result.x = v1.x + v2.x;

		result.y = v1.y + v2.y;

		result.z = v1.z + v2.z;

		result.status = DEFAULT;

	} 
	else

		result = Vector3();

	return result;

}


/** ������� */
Vector3 &Vector3::subtract(const Vector3 &v1, const Vector3 &v2, Vector3 &result) 
{

	if (v1.isValid() && v2.isValid()) 
	{

		result.x = v1.x - v2.x;

		result.y = v1.y - v2.y;

		result.z = v1.z - v2.z;

		result.status = DEFAULT;

	} 
	else

		result = Vector3();

	return result;

}


/** ������� */
Vector3 &Vector3::cross(const Vector3 &v1, const Vector3 &v2, Vector3 &result) 
{

	if (v1.isValid() && v2.isValid()) 
	{

		result.x = v1.y * v2.z - v1.z * v2.y;

		result.y = v1.z * v2.x - v1.x * v2.z;

		result.z = v1.x * v2.y - v1.y * v2.x;

		result.status = DEFAULT;

	} 
	else

		result = Vector3();

	return result;

}


/** �������� */
Vector3 &Vector3::multiply(const Vector3 &v1, const double &scale, Vector3 &result) {

	if (v1.isValid()) 
	{

		result.x = v1.x * scale;

		result.y = v1.y * scale;

		result.z = v1.z * scale;

		result.status = DEFAULT;

	} 
	else

		result = Vector3();

	return result;

}









