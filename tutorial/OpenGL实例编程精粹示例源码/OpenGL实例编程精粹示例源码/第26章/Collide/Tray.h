//========================================================
/**
*  @file      Tray.h
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

#ifndef __TRAY_H__
#define __TRAY_H__

#include "Vector.h"

/** ������ */
class TRay
{
	private:
		Vector3 _P;      /**< ���ߵĶ˵� */
		Vector3 _V;      /**< ���ߵķ��� */	
	public:
		/** ���캯�� */
		TRay() {}
		TRay(const Vector3 &point1, const Vector3 &point2);
		
		/** �������ֱ�ߵ�����ĵ㣬��������point1��point2�� */
		bool adjacentPoints(const TRay &ray, Vector3 &point1, Vector3 &point2) const;
		
		/** �������ߵķ���ԭ�㲻�� */
		static TRay &invert(const TRay &r, TRay &result) { result._P = r._P; result._V = -r._V; return result; }
		TRay operator-() const { return invert(*this, TRay()); }
		int isValid() const { return V().isUnit() && P().isValid(); }
		
		/** ���س�Ա���� */
		Vector3 P() const { return _P; }
		Vector3 V() const { return _V; }
		
		/** �������ߵľ��� */
		double dist(const TRay &ray) const;
		double dist(const Vector3 &point) const;
		
};

#endif

