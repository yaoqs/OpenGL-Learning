// Matrix33.h: interface for the CMatrix33 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX33_H__A30C8296_00F2_11D6_95F2_93B9C68FDF74__INCLUDED_)
#define AFX_MATRIX33_H__A30C8296_00F2_11D6_95F2_93B9C68FDF74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream.h>
#include "mathex.h"

class CVector;
class CMatrix33  
{
private:
		double _Mx[3][3];
		// 输入输出
		ostream &write(ostream &out) const;
		istream &read(istream &in);
public:
		CMatrix33();
		virtual ~CMatrix33();
		CMatrix33(double Phi, double Theta, double Psi);
		CMatrix33(double mx00, double mx01, double mx02, double mx10, double mx11, double mx12, double mx20, double mx21, double mx22);
		double operator()(int Row, int Column) const { return _Mx[Row][Column]; }
		double &operator()(int Row, int Column) { return _Mx[Row][Column]; }
		// 算术方法
		static CMatrix33 &add(const CMatrix33 &m1, const CMatrix33 &m2, CMatrix33 &result);
		static CMatrix33 &subtract(const CMatrix33 &m1, const CMatrix33 &m2, CMatrix33 &result);
		static CMatrix33 &multiply(const CMatrix33 &m1, const CMatrix33 &m2, CMatrix33 &result);
		static CMatrix33 &multiply(const CMatrix33 &m1, const double &scale, CMatrix33 &result);
		static CVector &multiply(const CMatrix33 &m1, const CVector &v, CVector &result);
		// 矩阵算法
		CMatrix33 &operator+=(const CMatrix33 &m) { return add(*this, m, *this); }
		CMatrix33 &operator-=(const CMatrix33 &m) { return subtract(*this, m, *this); }
		CMatrix33 &operator*=(const CMatrix33 &m) { CMatrix33 tm(*this); return multiply(tm, m, *this); }
		CMatrix33 &operator*=(const double &scale) { return multiply(*this, scale, *this); }
		CMatrix33 operator+(const CMatrix33 &m) const { CMatrix33 tm; return add(*this, m, tm); }
		CMatrix33 operator-(const CMatrix33 &m) const { CMatrix33 tm; return subtract(*this, m, tm); }
		CMatrix33 operator*(const CMatrix33 &m) const { CMatrix33 tm; return multiply(*this, m, tm); }
		CMatrix33 operator*(const double &scale) const { CMatrix33 tm; return multiply(*this, scale, tm); }
		CVector operator*(const CVector &v) const;
		// 求行列式
		double determinant() const;
		static double determinant(const CMatrix33 &m) { return m.determinant(); }
		// 求转置矩阵
		CMatrix33 &transpose();
		static CMatrix33 &transpose(const CMatrix33 &m, CMatrix33 &result) { result = m; return result.transpose(); }
		static CMatrix33 transpose(const CMatrix33 &m) { return CMatrix33(m).transpose(); }
		static CMatrix33 &CMatrix33::inverse(const CMatrix33 &m1, CMatrix33 &result);
		static CMatrix33 CMatrix33::inverse(const CMatrix33 &m1) { CMatrix33 tm; return inverse(m1, tm); }
		CMatrix33 inverse() const { CMatrix33 tm; return inverse(*this, tm); }
		// 输入输出
		friend ostream &operator<<(ostream &out, const CMatrix33 &o) { return o.write(out); }
		friend istream &operator>>(istream &in, CMatrix33 &o) { return o.read(in); }
};

#endif // !defined(AFX_MATRIX33_H__A30C8296_00F2_11D6_95F2_93B9C68FDF74__INCLUDED_)
