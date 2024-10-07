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

#include "Tray.h"

///���캯��
TRay::TRay(const Vector3 &point1, const Vector3 &point2): _P(point1) 
{
	_V = (point2.isUnit() ? point2 : Vector3::unit(point2-point1));
}

/** �������ֱ�ߵ�����ĵ㣬��������point1��point2�� */
bool TRay::adjacentPoints(const TRay &ray, Vector3 &point1, Vector3 &point2) const 
{

	if (isValid() && ray.isValid())
	{
		double temp = Vector3::dot(_V, ray._V);
		double temp2 = 1.0 - temp*temp;
		Vector3 tv;

		/** ���ֱ���Ƿ�ƽ�� */
		if (fabs(temp2)<ZERO) 
		{
			double mu = Vector3::dot(_V, _P-ray._P)/temp;
			point1 = _P;
			Vector3::add(ray._P, Vector3::multiply(ray._V, mu, tv), point2);
		}
		/** �����ƽ����������ڵĵ� */
		else 
		{
			double a = Vector3::dot(_V, Vector3::subtract(ray._P, _P, tv));
			double b = Vector3::dot(ray._V, Vector3::subtract(_P, ray._P, tv));
			double mu = (b + temp*a)/temp2;
			double lambda = (a + temp*b)/temp2;
			Vector3::add(_P, Vector3::multiply(_V, lambda, tv), point1);
			Vector3::add(ray._P, Vector3::multiply(ray._V, mu, tv), point2);
		}
		return true;
	}
	return false;
}

/** �������ߵľ��� */
double TRay::dist(const TRay &ray) const 
{
	Vector3 point1, point2;
	if (adjacentPoints(ray, point1, point2))
		return point1.dist(point2);
	else
		return 0.0;
}

/** �������ߵľ��� */
double TRay::dist(const Vector3 &point) const 
{
	if (isValid() && point.isValid()) {
		Vector3 tv, point2;
		double lambda = Vector3::dot(_V, point-_P);
		Vector3::add(_P, Vector3::multiply(_V, lambda, tv), point2);
		return point.dist(point2);
	}
	return 0.0;
}
