#ifndef __H_VEC3__
#define __H_VEC3__

#include <math.h>

typedef struct _vec3 
{
	public:
		float x,y,z;
		
		_vec3() {}
		_vec3(const float fx,const float fy,const float fz) { x=fx; y=fy; z=fz; }
		_vec3(const float f[3]) { x=f[0]; y=f[1]; z=f[2]; }
		_vec3(const float f) { x=f;	y=f; z=f; }
		
		_vec3 operator+(const _vec3& v) { return _vec3(x+v.x,y+v.y,z+v.z); }
		_vec3 operator-(const _vec3& v) { return _vec3(x-v.x,y-v.y,z-v.z); }
		_vec3 operator*(const _vec3& v) { return _vec3(x*v.x,y*v.y,z*v.z); }
		_vec3 operator/(const _vec3& v) { return _vec3(x/v.x,y/v.y,z/v.z); }
		_vec3 operator*(const float f) { return _vec3(x*f,y*f,z*f);	}
		_vec3 operator/(const float f) { return _vec3(x/f,y/f,z/f); }
		_vec3 operator-(void) { return _vec3(-x,-y,-z); }
		
		_vec3& operator+=(const _vec3& v) {	*this = *this + v; return *this; }
		_vec3& operator-=(const _vec3& v) {	*this = *this - v; return *this; }
		_vec3& operator*=(const _vec3& v) {	*this = *this * v; return *this; }
		_vec3& operator/=(const _vec3& v) {	*this = *this / v; return *this; }
		_vec3& operator*=(const float f) { *this = *this * f; return *this; }
		_vec3& operator/=(const float f) { *this = *this / f; return *this; }
		
		inline float SqrLength(void) { return (x*x + y*y + z*z); }
		inline float Length(void) {	return (float)sqrt(SqrLength()); }		
		inline float DotProduct(_vec3& v) {	return ( x*v.x + y*v.y + z*v.z ); }
		inline void CrossProduct(const _vec3& a,const _vec3& b);
		inline void Normalize(void);
} vec3;

inline void _vec3::Normalize(void)
{
	float len = Length();
	if (!len) return;
	len=1.0f/len;
	
	x*=len;
	y*=len;
	z*=len;
}

inline void _vec3::CrossProduct(const _vec3& a,const _vec3& b)
{
	x = ( a.y * b.z ) - ( a.z * b.y );
	y = ( a.z * b.x ) - ( a.x * b.z );
	z = ( a.x * b.y ) - ( a.y * b.x );
}


inline float DotProduct(vec3& v1,vec3& v2)
{
	return ( v1.x*v2.x  +  v1.y*v2.y  +  v1.z*v2.z );
}

#endif