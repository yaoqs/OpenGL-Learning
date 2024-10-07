// CTray.h: interface for the CTray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTray_H__A30C8297_00F2_11D6_95F2_93B9C68FDF74__INCLUDED_)
#define AFX_CTray_H__A30C8297_00F2_11D6_95F2_93B9C68FDF74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream.h>
#include "mathex.h"
#include "vector.h"

class CTray  
{
private:
	CVector _P; // 直线上任意点
	CVector _V; // 直线的方向
	// 输入和输出
	ostream &write(ostream &out) const;
	istream &read(istream &in);

public:
	CTray();
	virtual ~CTray();
		// 两点的直线或点与一个方向
		CTray(const CVector &point1, const CVector &point2);
		// 两条直线的交点
		bool adjacentPoints(const CTray &ray, CVector &point1, CVector &point2) const;
		// 一元运算符
		static CTray &invert(const CTray &r, CTray &result) { result._P = r._P; CVector::invert(r._V, result._V); return result; }
		CTray operator-() const { return invert(*this, CTray()); }
		CVector P() const { return _P; }
		CVector V() const { return _V; }
		int isValid() const { return V().isUnit() && P().isValid(); }
		// 距离
		double dist(const CTray &ray) const;
		double dist(const CVector &point) const;
		// 输入输出
		friend ostream &operator<<(ostream &out, const CTray &o) { return o.write(out); }
		friend istream &operator>>(istream &in, CTray &o) { return o.read(in); }
};

#endif // !defined(AFX_CTray_H__A30C8297_00F2_11D6_95F2_93B9C68FDF74__INCLUDED_)
