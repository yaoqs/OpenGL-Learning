// CTray.cpp: implementation of the CCTray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyCollision1.h"
#include "Tray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTray::CTray()
{

}

CTray::~CTray()
{

}

CTray::CTray(const CVector &point1, const CVector &point2)

: _P(point1) 
{
	_V = (point2.isUnit() ? point2 : CVector::unit(point2-point1));
}

bool CTray::adjacentPoints(const CTray &ray, CVector &point1, CVector &point2) const 
{
	if (isValid() && ray.isValid())
	{
		double temp = CVector::dot(_V, ray._V);
		double temp2 = 1.0 - sqr(temp);
		CVector tv; 
		if (fabs(temp2)<EPSILON) 
		{
			double mu = CVector::dot(_V, _P-ray._P)/temp;
			point1 = _P;
			CVector::add(ray._P, CVector::multiply(ray._V, mu, tv), point2);
		} 
		else 
		{
			double a = CVector::dot(_V, CVector::subtract(ray._P, _P, tv));
			double b = CVector::dot(ray._V, CVector::subtract(_P, ray._P, tv));
			double mu = (b + temp*a)/temp2;
			double lambda = (a + temp*b)/temp2;
			CVector::add(_P, CVector::multiply(_V, lambda, tv), point1);
			CVector::add(ray._P, CVector::multiply(ray._V, mu, tv), point2);
		}
		return true;
	}
	return false;
}
// 求两条平行线之间的距离
double CTray::dist(const CTray &ray) const 
{
	CVector point1, point2;
	if (adjacentPoints(ray, point1, point2))
		return point1.dist(point2);
	else
		return 0.0;
}
// 求一条直线与一个点之间的距离
double CTray::dist(const CVector &point) const 
{
	if (isValid() && point.isValid()) 
	{
		CVector tv, point2;
		double lambda = CVector::dot(_V, point-_P);
		CVector::add(_P, CVector::multiply(_V, lambda, tv), point2);
		return point.dist(point2);
	}
	return 0.0;
}
// 输入输出
ostream &CTray::write(ostream &out) const 
{
	return isValid() ? out<<"(P="<<_P<<",V="<<_V<<")" : out<<"Invalid";
}

istream &CTray::read(istream &in) 
{
	char buf[20],ch;
	in >> ch;
	if (ch != 'I')
		in >>ch>>ch>>_P>>ch>>ch>>ch>>_V;
	else 
	{
		*this=CTray();
		in.get(buf,20,'d');
	}
	return in >> ch;
}
