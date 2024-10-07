//========================================================
/**
*  @file      Vector.h
*
*  ��Ŀ������ ��ײ���
*  �ļ�����:  ������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     BrightXu
*  �����ʼ�:  huoxini@hotmail.com
*  �������ڣ� 2006-12-06	
*  �޸����ڣ� 2006-12-19
*
*/     
//========================================================

#ifndef __VECTOR_H__
#define __VECTOR_H__

#define ZERO 1.0e-8
#define M_PI 3.1415926535
#include <math.h>

class TRay;

/** ������ */
class Vector3
{
public:
	enum Status { INVALID, DEFAULT, UNIT };
    double   x,y,z;
    Status  status;

public:
	/** ���캯�� */
	Vector3():x(0.0), y(0.0), z(0.0), status(INVALID) {}
	Vector3(double xx, double yy, double zz):x(xx),y(yy),z(zz),status(DEFAULT) {}
	Vector3(double xx, double yy, double zz,Status s):x(xx),y(yy),z(zz),status(s) {}

	/** �������캯�� */
	Vector3(const Vector3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		status = vec.status;
	}

	/** ���س�Ա���� */
	int isUnit() const    { return status==UNIT; }
	int isDefault() const { return status==DEFAULT; }
	int isValid() const   { return status!=INVALID; }
    
	/** �����������ߵ��е� */
	Vector3(const TRay &line1, const TRay &line2);

	/** ���ص�λ���� */
	Vector3 &unit();
	static Vector3 &unit(const Vector3 &v, Vector3 &result) { result = v; return result.unit(); }
	static Vector3 unit(const Vector3 &v) { return Vector3(v).unit(); }

	Vector3 &Default();
	static Vector3 Default(const Vector3 &v, Vector3 &result) { result = v; return result.Default(); }
	static Vector3 Default(const Vector3 &v) { return Vector3(v).Default(); }

	/// ����������ģ
	double mag() const { return (isValid() ? (isUnit() ? 1.0 : sqrt( x*x + y*y + z*z )) : 0.0); }
	double magSqr() const { return (isValid() ? (isUnit() ? 1.0 : x*x + y*y + z*z) : 0.0); }

	/// �������������ĵ��
	double dot(const Vector3 &v) const { return ((isValid() && v.isValid()) ? (x*v.x + y*v.y + z*v.z) : 0.0); }
	static double dot(const Vector3 &v1, const Vector3 &v2) { return v1.dot(v2); }

	/// �������������ľ���
	double dist(const Vector3 &v) const { return (*this-v).mag(); }
	double distSqr(const Vector3 &v) const { return (*this-v).magSqr(); }

	/// ������ʾ����������
	static Vector3 &add(const Vector3 &v1, const Vector3 &v2, Vector3 &result);
	static Vector3 &subtract(const Vector3 &v1, const Vector3 &v2, Vector3 &result);
	static Vector3 &cross(const Vector3 &v1, const Vector3 &v2, Vector3 &result);
	static Vector3 &invert(const Vector3 &v1, Vector3 &result);
	static Vector3 &multiply(const Vector3 &v1, const double &scale, Vector3 &result);

	/// ��������
	Vector3 operator-() const { return invert(*this, Vector3()); }
	Vector3 &operator+=(const Vector3 &v) { return add(*this, v, *this); }
	Vector3 &operator-=(const Vector3 &v) { return subtract(*this, v, *this); }
	Vector3 &operator*=(const Vector3 &v) { Vector3 tv(*this); return cross(tv, v, *this); }
	Vector3 &operator*=(const double &scale) { return multiply(*this, scale, *this); }
	Vector3 operator+(const Vector3 &v) const { Vector3 tv; return add(*this, v, tv); }
	Vector3 operator-(const Vector3 &v) const { Vector3 tv; return subtract(*this, v, tv); }
	Vector3 operator*(const Vector3 &v) const { Vector3 tv; return cross(*this, v, tv); }
	Vector3 operator*(const double &scale) const { Vector3 tv; return multiply(*this, scale, tv); }

};

#endif //__VECTOR_H__