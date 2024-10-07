#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "body.h"

void vecPrint (vector v)
{
  printf ("[%f %f %f]\n", v[0], v[1], v[2]);
}

void vecCopy (vector dest, vector src)
{
  dest[0] = src[0];
  dest[1] = src[1];
  dest[2] = src[2];
}

float vecLength (vector u)
{
  return sqrt (u[0] * u[0] + u[1] * u[1] + u[2] * u[2]);
}

float vecLengthSq (vector u)
{
  return (u[0] * u[0] + u[1] * u[1] + u[2] * u[2]);
}

float vecDist (vector   u,
	 vector   v)
{
  return sqrt ((v[0] - u[0]) * (v[0] - u[0]) +
	       (v[1] - u[1]) * (v[1] - u[1]) +
	       (v[2] - u[2]) * (v[2] - u[2]));
}

float vecDistSq (vector   u,
	   vector   v)
{
  return ((v[0] - u[0]) * (v[0] - u[0]) +
	  (v[1] - u[1]) * (v[1] - u[1]) +
	  (v[2] - u[2]) * (v[2] - u[2]));
}

void vecSub (vector     dest, 
	vector     u,
	vector     v)
{
  vector    res;

  res[0] = u[0] - v[0];
  res[1] = u[1] - v[1];
  res[2] = u[2] - v[2];

  vecCopy (dest, res);
}

void vecAdd (vector     dest, 
	vector     u,
	vector     v)
{
  vector     res;

  res[0] = u[0] + v[0];
  res[1] = u[1] + v[1];
  res[2] = u[2] + v[2];

  vecCopy (dest, res);
}

void vecMult (vector     dest, 
	 float      c,
	 vector     u)
{
  vector    res;

  res[0] = u[0] * c;
  res[1] = u[1] * c;
  res[2] = u[2] * c;

  vecCopy (dest, res);
}

float vecDot (vector    u,
	vector    v)
{
  return (u[0] * v[0] + u[1] * v[1] + u[2] * v[2]);
}

float vecAngle (vector   u,
	  vector   v)
{
  return acos (vecDot (u, v) / (vecLength (u) * vecLength (v)));
}

void vecCross (vector    dest,
	  vector    u,
	  vector    v)
{
  vector res;

  res[0] = u[1] * v[2] - u[2] * v[1];
  res[1] = u[2] * v[0] - u[0] * v[2];
  res[2] = u[0] * v[1] - u[1] * v[0];

  vecCopy (dest, res);
}

void vecNormalize (vector dest, vector v)
{
  float   length;

  length = vecLength (v);
  
  if (length != 0)
    {
      vecMult (dest, 1 / length, v);
    }
}

float vecDistPointToPlane (vector    r,
		     plane     p)
{
  return (p[0] * r[0] + p[1] * r[1] + p[2] * r[2] + p[3]);
}

void vecPlaneFromPointAndNormal (plane    dest,
			    vector   p,
			    vector   N)
{
  dest[0] = N[0];
  dest[1] = N[1];
  dest[2] = N[2];
  dest[3] = -((N[0] * p[0]) + (N[1] * p[1]) + (N[2] * p[2]));
}

void vecSpherical (vector dest, float theta, float phi)
{
  dest[0] = (float)sin (theta) * (float)cos (phi);
  dest[1] = (float)sin (theta) * (float)sin (phi);
  dest[2] = (float)cos (theta);
}

void vecRotateX (vector     dest,
	    vector     src,
	    float      angle)
{
  float    s;
  float    c;
  vector   result;

  s = (float)sin (angle * VEC_DEG_TO_RAD);
  c = (float)cos (angle * VEC_DEG_TO_RAD);

  result[0] = src[0];
  result[1] = src[1] * c + src[2] * s;
  result[2] = -src[1] * s + src[2] * c;

  vecCopy (dest, result);
}

void vecRotateY (vector      dest,
	    vector      src,
	    float       angle)
{
  float    s;
  float    c;
  vector   result;

  s = (float)sin (angle * VEC_DEG_TO_RAD);
  c = (float)cos (angle * VEC_DEG_TO_RAD);

  result[0] = src[0] * c - src[2] * s;
  result[1] = src[1];
  result[2] = src[0] * s + src[2] * c;

  vecCopy (dest, result);
}

void vecRotateZ (vector     dest,
	    vector     src,
	    float      angle)
{
  float   s;
  float   c;
  vector  result;

  s = (float)sin (angle * VEC_DEG_TO_RAD);
  c = (float)cos (angle * VEC_DEG_TO_RAD);

  result[0] = src[0] * c + src[1] * s;
  result[1] = -src[0] * s + src[1] * c;
  result[2] = src[2];
  
  vecCopy (dest, result);
}

void vecRotate (vector dest, vector p, vector axis, float angle)
{
  float   c;
  float   s;
  float   t;
  float   x, y, z;
  float   x2, y2, z2;
  float   R[3][3];
  vector  result;

  c = (float)cos (angle);
  s = (float)sin (angle);
  t = 1 - c;
  x = axis[0];
  y = axis[1];
  z = axis[2];
  x2 = x * x;
  y2 = y * y;
  z2 = z * z;

  R[0][0] = (t * x2) + c;
  R[1][0] = (t * x * y) - (s * z);
  R[2][0] = (t * x * z) + (s * y);
  
  R[0][1] = (t * x * y) + (s * z);
  R[1][1] = (t * y2) + c;
  R[2][1] = (t * y * z) - (s * x);

  R[0][2] = (t * x * z) - (s * y);
  R[1][2] = (t * y * z) + (s * x);
  R[2][2] = (t * z2) + c;

  result[0] = (p[0] * R[0][0]) + (p[1] * R[1][0]) + (p[2] * R[2][0]);
  result[1] = (p[0] * R[0][1]) + (p[1] * R[1][1]) + (p[2] * R[2][1]);
  result[2] = (p[0] * R[0][2]) + (p[1] * R[1][2]) + (p[2] * R[2][2]);
  
  vecCopy (dest, result);
}

void vecMatch (float *angle, vector axis, vector u, vector v)
{
  vecCross (axis, u, v);
  vecNormalize (axis, axis);
  *angle = acos (vecDot (u, v));
}

void vecSetValue(vector dest, float x, float y, float z)
{
  vector  result;

  result[X] = x;
  result[Y] = y;
  result[Z] = z;

  vecCopy(dest, result);
}

void vecTranslate(vector dest, float x, float y, float z)
{
  vector  result;
  result[X] = dest[X] + x;
  result[Y] = dest[Y] + y;
  result[Z] = dest[Z] + z;

  vecCopy(dest, result);
}
