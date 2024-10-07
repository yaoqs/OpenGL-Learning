// Matrix33.cpp: implementation of the CMatrix33 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyCollision1.h"
#include "Matrix33.h"
#include "vector.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatrix33::CMatrix33()
{
	_Mx[0][0]=1.0; _Mx[0][1]=0.0; _Mx[0][2]=0.0;
	_Mx[1][0]=0.0; _Mx[1][1]=1.0; _Mx[1][2]=0.0;
	_Mx[2][0]=0.0; _Mx[2][1]=0.0; _Mx[2][2]=1.0;
}

CMatrix33::~CMatrix33()
{

}

CMatrix33::CMatrix33(double mx00, double mx01, double mx02,
		 double mx10, double mx11, double mx12,
		 double mx20, double mx21, double mx22) 
{
	_Mx[0][0]=mx00; _Mx[0][1]=mx01; _Mx[0][2]=mx02;
	_Mx[1][0]=mx10; _Mx[1][1]=mx11; _Mx[1][2]=mx12;
	_Mx[2][0]=mx20; _Mx[2][1]=mx21; _Mx[2][2]=mx22;
}

CMatrix33::CMatrix33(double Phi, double Theta, double Psi) 
{
	double c1=cos(Phi), s1=sin(Phi), c2=cos(Theta), s2=sin(Theta), c3=cos(Psi), s3=sin(Psi);
	_Mx[0][0]=c2*c3;
	_Mx[0][1]=-c2*s3;
	_Mx[0][2]=s2;
	_Mx[1][0]=s1*s2*c3+c1*s3;
	_Mx[1][1]=-s1*s2*s3+c1*c3;
	_Mx[1][2]=-s1*c2;
	_Mx[2][0]=-c1*s2*c3+s1*s3;
	_Mx[2][1]=c1*s2*s3+s1*c3;
	_Mx[2][2]=c1*c2;
}

CMatrix33 &CMatrix33::add(const CMatrix33 &m1, const CMatrix33 &m2, CMatrix33 &result) 
{
	result._Mx[0][0] = m1._Mx[0][0] + m2._Mx[0][0];
	result._Mx[0][1] = m1._Mx[0][1] + m2._Mx[0][1];
	result._Mx[0][2] = m1._Mx[0][2] + m2._Mx[0][2];
	result._Mx[1][0] = m1._Mx[1][0] + m2._Mx[1][0];
	result._Mx[1][1] = m1._Mx[1][1] + m2._Mx[1][1];
	result._Mx[1][2] = m1._Mx[1][2] + m2._Mx[1][2];
	result._Mx[2][0] = m1._Mx[2][0] + m2._Mx[2][0];
	result._Mx[2][1] = m1._Mx[2][1] + m2._Mx[2][1];
	result._Mx[2][2] = m1._Mx[2][2] + m2._Mx[2][2];
	return result;
}

CMatrix33 &CMatrix33::subtract(const CMatrix33 &m1, const CMatrix33 &m2, CMatrix33 &result) 
{
	result._Mx[0][0] = m1._Mx[0][0] - m2._Mx[0][0];
	result._Mx[0][1] = m1._Mx[0][1] - m2._Mx[0][1];
	result._Mx[0][2] = m1._Mx[0][2] - m2._Mx[0][2];
	result._Mx[1][0] = m1._Mx[1][0] - m2._Mx[1][0];
	result._Mx[1][1] = m1._Mx[1][1] - m2._Mx[1][1];
	result._Mx[1][2] = m1._Mx[1][2] - m2._Mx[1][2];
	result._Mx[2][0] = m1._Mx[2][0] - m2._Mx[2][0];
	result._Mx[2][1] = m1._Mx[2][1] - m2._Mx[2][1];
	result._Mx[2][2] = m1._Mx[2][2] - m2._Mx[2][2];
	return result;
}

CMatrix33 &CMatrix33::multiply(const CMatrix33 &m1, const CMatrix33 &m2, CMatrix33 &result) 
{
	result._Mx[0][0] = m1._Mx[0][0]*m2._Mx[0][0] + m1._Mx[0][1]*m2._Mx[1][0] + m1._Mx[0][2]*m2._Mx[2][0];
	result._Mx[1][0] = m1._Mx[1][0]*m2._Mx[0][0] + m1._Mx[1][1]*m2._Mx[1][0] + m1._Mx[1][2]*m2._Mx[2][0];
	result._Mx[2][0] = m1._Mx[2][0]*m2._Mx[0][0] + m1._Mx[2][1]*m2._Mx[1][0] + m1._Mx[2][2]*m2._Mx[2][0];
	result._Mx[0][1] = m1._Mx[0][0]*m2._Mx[0][1] + m1._Mx[0][1]*m2._Mx[1][1] + m1._Mx[0][2]*m2._Mx[2][1];
	result._Mx[1][1] = m1._Mx[1][0]*m2._Mx[0][1] + m1._Mx[1][1]*m2._Mx[1][1] + m1._Mx[1][2]*m2._Mx[2][1];
	result._Mx[2][1] = m1._Mx[2][0]*m2._Mx[0][1] + m1._Mx[2][1]*m2._Mx[1][1] + m1._Mx[2][2]*m2._Mx[2][1];
	result._Mx[0][2] = m1._Mx[0][0]*m2._Mx[0][2] + m1._Mx[0][1]*m2._Mx[1][2] + m1._Mx[0][2]*m2._Mx[2][2];
	result._Mx[1][2] = m1._Mx[1][0]*m2._Mx[0][2] + m1._Mx[1][1]*m2._Mx[1][2] + m1._Mx[1][2]*m2._Mx[2][2];
	result._Mx[2][2] = m1._Mx[2][0]*m2._Mx[0][2] + m1._Mx[2][1]*m2._Mx[1][2] + m1._Mx[2][2]*m2._Mx[2][2];
	return result;
}

CMatrix33 &CMatrix33::multiply(const CMatrix33 &m1, const double &scale, CMatrix33 &result) 
{
	result._Mx[0][0] = m1._Mx[0][0] * scale;
	result._Mx[0][1] = m1._Mx[0][1] * scale;
	result._Mx[0][2] = m1._Mx[0][2] * scale;
	result._Mx[1][0] = m1._Mx[1][0] * scale;
	result._Mx[1][1] = m1._Mx[1][1] * scale;
	result._Mx[1][2] = m1._Mx[1][2] * scale;
	result._Mx[2][0] = m1._Mx[2][0] * scale;
	result._Mx[2][1] = m1._Mx[2][1] * scale;
	result._Mx[2][2] = m1._Mx[2][2] * scale;
	return result;
}

CVector &CMatrix33::multiply(const CMatrix33 &m1, const CVector &v, CVector &result) 
{
	result = CVector(
   	m1._Mx[0][0]*v.X() + m1._Mx[0][1]*v.Y() + m1._Mx[0][2]*v.Z(),
		m1._Mx[1][0]*v.X() + m1._Mx[1][1]*v.Y() + m1._Mx[1][2]*v.Z(),
		m1._Mx[2][0]*v.X() + m1._Mx[2][1]*v.Y() + m1._Mx[2][2]*v.Z() );
	return result;
}

double CMatrix33::determinant() const 
{
	return _Mx[0][0]*(_Mx[1][1]*_Mx[2][2]-_Mx[1][2]*_Mx[2][1])
		- _Mx[0][1]*(_Mx[1][0]*_Mx[2][2]-_Mx[1][2]*_Mx[2][0])
		+ _Mx[0][2]*(_Mx[1][0]*_Mx[2][1]-_Mx[1][1]*_Mx[2][0]);
}

CMatrix33 &CMatrix33::transpose() 
{
	double t=_Mx[0][2]; _Mx[0][2]=_Mx[2][0]; _Mx[2][0]=t;
	t=_Mx[0][1]; _Mx[0][1]=_Mx[1][0]; _Mx[1][0]=t;
	t=_Mx[1][2]; _Mx[1][2]=_Mx[2][1]; _Mx[2][1]=t;
	return *this;
}

CMatrix33 &CMatrix33::inverse(const CMatrix33 &m1, CMatrix33 &result) 
{
	double det = m1.determinant();
	if (fabs(det) < EPSILON) 
	{
		result = CMatrix33();
		return result;
	} 
	else 
	{
		result._Mx[0][0] = m1._Mx[1][1]*m1._Mx[2][2] - m1._Mx[1][2]*m1._Mx[2][1];
		result._Mx[0][1] = m1._Mx[2][1]*m1._Mx[0][2] - m1._Mx[2][2]*m1._Mx[0][1];
		result._Mx[0][2] = m1._Mx[0][1]*m1._Mx[1][2] - m1._Mx[0][2]*m1._Mx[1][1];
		result._Mx[1][0] = m1._Mx[1][2]*m1._Mx[2][0] - m1._Mx[1][0]*m1._Mx[2][2];
		result._Mx[1][1] = m1._Mx[2][2]*m1._Mx[0][0] - m1._Mx[2][0]*m1._Mx[0][2];
		result._Mx[1][2] = m1._Mx[0][2]*m1._Mx[1][0] - m1._Mx[0][0]*m1._Mx[1][2];
		result._Mx[2][0] = m1._Mx[1][0]*m1._Mx[2][1] - m1._Mx[1][1]*m1._Mx[2][0];
		result._Mx[2][1] = m1._Mx[2][0]*m1._Mx[0][1] - m1._Mx[2][1]*m1._Mx[0][0];
		result._Mx[2][2] = m1._Mx[0][0]*m1._Mx[1][1] - m1._Mx[0][1]*m1._Mx[1][0];
		return multiply(result, 1.0/det, result);
	}
}

CVector CMatrix33::operator*(const CVector &v) const 
{
	CVector tv;
	return multiply(*this, v, tv);
}

ostream &CMatrix33::write(ostream &out) const 
{
	return out<<"("<<_Mx[0][0]<<","<<_Mx[0][1]<<","<<_Mx[0][2]<<")"<<endl
		<<"("<<_Mx[1][0]<<","<<_Mx[1][1]<<","<<_Mx[1][2]<<")"<<endl
		<<"("<<_Mx[2][0]<<","<<_Mx[2][1]<<","<<_Mx[2][2]<<")"<<endl;
}

istream &CMatrix33::read(istream &in) 
{
	char ch;
	return in>>ch>>_Mx[0][0]>>ch>>_Mx[0][1]>>ch>>_Mx[0][2]>>ch
		>>ch>>_Mx[1][0]>>ch>>_Mx[1][1]>>ch>>_Mx[1][2]>>ch
		>>ch>>_Mx[2][0]>>ch>>_Mx[2][1]>>ch>>_Mx[2][2]>>ch;
}
