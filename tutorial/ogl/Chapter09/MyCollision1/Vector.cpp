// Vector.cpp: implementation of the CVector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyCollision1.h"
#include "Vector.h"
#include "tray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CVector::~CVector()
{

}

CVector::CVector(const CTray &ray1, const CTray &ray2) 
{
	CVector point1, point2;
	if (ray1.adjacentPoints(ray2, point1, point2))
		*this = (point1 + point2)*0.5;
	else
		*this = CVector();
}
// 单位矢量
CVector &CVector::unit() 
{
	if (isDefault()) 
	{
		double rep = mag();
		if (rep < EPSILON) 
		{
			_x = 0.0;
			_y = 0.0;
			_z = 0.0;
		} 
		else 
		{
			double temp = 1.0 / rep;
			_x *= temp;
			_y *= temp;
			_z *= temp;
		}
		_Status = UNIT;
	}
	return *this;
}
// 缺省矢量
CVector &CVector::Default() 
{
	if (isUnit())
		_Status = DEFAULT;
	return *this;
}

CVector &CVector::invert(const CVector &v1, CVector &result) 
{
	if (v1.isValid()) 
	{
		result._x = -v1._x;
		result._y = -v1._y;
		result._z = -v1._z;
		result._Status = v1._Status;
	} else
		result = CVector();
	return result;
}

CVector &CVector::add(const CVector &v1, const CVector &v2, CVector &result) 
{
	if (v1.isValid() && v2.isValid()) 
	{
		result._x = v1._x + v2._x;
		result._y = v1._y + v2._y;
		result._z = v1._z + v2._z;
		result._Status = DEFAULT;
	} 
	else
		result = CVector();
	return result;
}

CVector &CVector::subtract(const CVector &v1, const CVector &v2, CVector &result) 
{
	if (v1.isValid() && v2.isValid()) 
	{
		result._x = v1._x - v2._x;
		result._y = v1._y - v2._y;
		result._z = v1._z - v2._z;
		result._Status = DEFAULT;
	} 
	else
		result = CVector();
	return result;
}

CVector &CVector::cross(const CVector &v1, const CVector &v2, CVector &result) 
{
	if (v1.isValid() && v2.isValid()) 
	{
		result._x = v1._y * v2._z - v1._z * v2._y;
		result._y = v1._z * v2._x - v1._x * v2._z;
		result._z = v1._x * v2._y - v1._y * v2._x;
		result._Status = DEFAULT;
	} 
	else
		result = CVector();
	return result;
}

CVector &CVector::multiply(const CVector &v1, const double &scale, CVector &result) 
{
	if (v1.isValid()) 
	{
		result._x = v1._x * scale;
		result._y = v1._y * scale;
		result._z = v1._z * scale;
		result._Status = DEFAULT;
	} 
	else
		result = CVector();
	return result;
}
// 输入输出
ostream &CVector::write(ostream &out) const 
{
	if (isValid())
		if (isUnit())
			return out<<"<"<<X()<<","<<Y()<<","<<Z()<<">";
		else
			return out<<"["<<X()<<","<<Y()<<","<<Z()<<"]";
	return out<<"Invalid";
}

istream &CVector::read(istream &in) 
{
	char buf[20],ch, ch2;
	in >> ch2;
	if (ch2 != 'I') 
	{
		double x,y,z;
		in >> x >> ch >> y >> ch >> z;
		*this=CVector(x,y,z);
		if (ch2 == '<')
			unit();
	} 
	else 
	{
		*this=CVector();
		in.get(buf,20,'d');
	}
	return in >> ch;
}
