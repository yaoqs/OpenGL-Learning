// Vector.h: interface for the CVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR_H__A30C8298_00F2_11D6_95F2_93B9C68FDF74__INCLUDED_)
#define AFX_VECTOR_H__A30C8298_00F2_11D6_95F2_93B9C68FDF74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <iostream.h>
#include <math.h>
#include "mathex.h"

class CTray;

class CVector  
{
public:

	virtual ~CVector();
		public:
		enum TStatus { INVALID, DEFAULT, UNIT };
	private:
		double _x, _y, _z;
		TStatus _Status;
		// 构造函数
		CVector(double x, double y, double z, TStatus s) : _x(x), _y(y), _z(z), _Status(s) {}
		// Input and output
		ostream &write(ostream &out) const;
		istream &read(istream &in);
	public:
		// 构造函数
		CVector() : _x(0.0), _y(0.0), _z(0.0), _Status(INVALID) {}
		CVector(double x, double y, double z) : _x(x), _y(y), _z(z), _Status(DEFAULT) {}
		// 求中间矢量
		CVector(const CTray &line1, const CTray &line2);
		double X() const { return _x; }
		double Y() const { return _y; }
		double Z() const { return _z; }
		int isUnit() const { return _Status==UNIT; }
		int isDefault() const { return _Status==DEFAULT; }
		int isValid() const { return _Status!=INVALID; }
		// 改变矢量的状态
		CVector &unit();
		static CVector &unit(const CVector &v, CVector &result) { result = v; return result.unit(); }
		static CVector unit(const CVector &v) { return CVector(v).unit(); }
		CVector &Default();
		static CVector Default(const CVector &v, CVector &result) { result = v; return result.Default(); }
		static CVector Default(const CVector &v) { return CVector(v).Default(); }
		double mag() const { return (isValid() ? (isUnit() ? 1.0 : sqrt(sqr(X()) + sqr(Y()) + sqr(Z()))) : 0.0); }
		double magSqr() const { return (isValid() ? (isUnit() ? 1.0 : sqr(X()) + sqr(Y()) + sqr(Z())) : 0.0); }
		double dot(const CVector &v) const { return ((isValid() && v.isValid()) ? (X()*v.X() + Y()*v.Y() + Z()*v.Z()) : 0.0); }
		static double dot(const CVector &v1, const CVector &v2) { return v1.dot(v2); }
		// 求两矢量的距离
		double dist(const CVector &v) const { return (*this-v).mag(); }
		double distSqr(const CVector &v) const { return (*this-v).magSqr(); }
		// 矢量的各种算法
		static CVector &add(const CVector &v1, const CVector &v2, CVector &result);
		static CVector &subtract(const CVector &v1, const CVector &v2, CVector &result);
		static CVector &cross(const CVector &v1, const CVector &v2, CVector &result);
		static CVector &invert(const CVector &v1, CVector &result);
		static CVector &multiply(const CVector &v1, const double &scale, CVector &result);
		CVector operator-() const { return invert(*this, CVector()); }
		CVector &operator+=(const CVector &v) { return add(*this, v, *this); }
		CVector &operator-=(const CVector &v) { return subtract(*this, v, *this); }
		CVector &operator*=(const CVector &v) { CVector tv(*this); return cross(tv, v, *this); }
		CVector &operator*=(const double &scale) { return multiply(*this, scale, *this); }
		CVector operator+(const CVector &v) const { CVector tv; return add(*this, v, tv); }
		CVector operator-(const CVector &v) const { CVector tv; return subtract(*this, v, tv); }
		CVector operator*(const CVector &v) const { CVector tv; return cross(*this, v, tv); }
		CVector operator*(const double &scale) const { CVector tv; return multiply(*this, scale, tv); }
		friend ostream &operator<<(ostream &out, const CVector &o) { return o.write(out); }
		friend istream &operator>>(istream &in, CVector &o) { return o.read(in); }

};

#endif // !defined(AFX_VECTOR_H__A30C8298_00F2_11D6_95F2_93B9C68FDF74__INCLUDED_)
