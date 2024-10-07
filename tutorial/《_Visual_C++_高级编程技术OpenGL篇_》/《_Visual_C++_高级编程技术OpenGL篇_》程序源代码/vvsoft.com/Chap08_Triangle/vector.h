#ifndef VECTOR_H
#define VECTOR_H

/* Conversion constants between degrees and radians */

#define VEC_DEG_TO_RAD 0.017453293
#define VEC_RAD_TO_DEG 57.29578

typedef float vector[3];

typedef float plane[4];

void  vecPrint (vector v);
void  vecCopy (vector dest, vector src);
float vecLength (vector u);
float vecLengthSq (vector u);
float vecDist (vector u, vector v);
float vecDistSq (vector u, vector v);
void  vecSub (vector dest, vector u, vector v);
void  vecAdd (vector dest, vector u, vector v);
void  vecMult (vector dest, float c, vector u);
float vecDot (vector u, vector v);
float vecAngle (vector u, vector v);
void  vecCross (vector dest, vector u, vector v);
void  vecNormalize (vector dest, vector v);
float vecDistPointToPlane (vector r, plane p);
void  vecPlaneFromPointAndNormal (plane dest, vector p, vector N);
void  vecSpherical (vector dest, float theta, float phi);
void  vecRotateX (vector dest, vector src, float angle);
void  vecRotateY (vector dest, vector src, float angle);
void  vecRotateZ (vector dest, vector src, float angle);
void  vecRotate (vector dest, vector p, vector axis, float angle);
void  vecMatch (float *angle, vector axis, vector u, vector v);
void vecSetValue(vector dest, float x, float y, float z);
void vecTranslate(vector dest, float x, float y, float z);
#endif /* VECTOR_H */
