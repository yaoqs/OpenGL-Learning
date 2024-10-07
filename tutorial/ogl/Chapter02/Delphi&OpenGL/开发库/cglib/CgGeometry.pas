unit CgGeometry;

{ CgLib: Basic geometry routines.
  Version 1.00
  (c) 1998-2000 Tom Nuydens. Use at your own risk. See cglib.txt for details. }

interface

uses
  CgTypes;

procedure cgSetPrecision(eps: Single);
function cgPrecision: Single;
function cgOrigin: TCGVector;
function cgXAxis: TCGVector;
function cgYAxis: TCGVector;
function cgZAxis: TCGVector;
function cgVectorComp(v1, v2: TCGVector): Boolean;
procedure cgTranslate(var v: TCGVector; t: TCGVector);
function cgVecAdd(v1, v2: TCGVector): TCGVector;
function cgVecSub(v1, v2: TCGVector): TCGVector;
function cgVecScalarMult(v: TCGVector; s: Single): TCGVector;
procedure cgMirror(var v: TCGVector; mx, my, mz: Boolean);
procedure cgScale(var v: TCGVector; sx, sy, sz: Single);
function cgVectorLength(v: TCGVector): Single;
function cgVectorDistance(v1, v2: TCGVector): Single;
procedure cgNormalize(var v: TCGVector);
procedure cgRotateX(var v: TCGVector; a: Single);
procedure cgRotateY(var v: TCGVector; a: Single);
procedure cgRotateZ(var v: TCGVector; a: Single);
function cgDotProduct(v1, v2: TCGVector): Single;
function cgCrossProduct(v1, v2: TCGVector): TCGVector;
function cgGetNormal(v1, v2, v3: TCGVector): TCGVector;
function cgVecMult(v1, v2: TCGVector): TCGMatrix;
function cgIdentity: TCGMatrix;
function cgNullMatrix: TCGMatrix;
procedure cgApplyMatrix(var v: TCGVector; m: TCGMatrix);
procedure cgMatrixAdd(var m1: TCGMatrix; m2: TCGMatrix);
procedure cgMatrixSub(var m1: TCGMatrix; m2: TCGMatrix);
procedure cgMatrixMult(var m1: TCGMatrix; m2: TCGMatrix);
procedure cgMScalarMult(var m: TCGMatrix; s: Single);
function cgMRotateX(angle: Single): TCGMatrix;
function cgMRotateY(angle: Single): TCGMatrix;
function cgMRotateZ(angle: Single): TCGMatrix;
function cgMScale(sx, sy, sz: Single): TCGMatrix;
function cgPlaneFromPoints(p1, p2, p3: TCGVector): TCGPlane;

implementation

uses
  CgUtils;

type
  TAVector = array [0..3] of Single;

var
  CG_EPS: Single = 0.0001;

procedure cgSetPrecision(eps: Single);
begin

  { Set precision for vector comparisons. Doesn't really affect floating point
    precision, of course... The default of 0.0001 should be adequate in most
    cases, but you never know. }
  CG_EPS := eps;

end;

function cgPrecision: Single;
begin

  { Return the current vector comparison precision. }
  Result := CG_EPS;

end;

function cgOrigin: TCGVector;
const
  r: TCGVector = (x: 0; y: 0; z: 0; w: 1);
begin

  { Return the origin. }
  Result := r;

end;

function cgXAxis: TCGVector;
const
  r: TCGVector = (x: 1; y: 0; z: 0; w: 1);
begin

  { Return a unit vector along the X axis. }
  Result := r;

end;

function cgYAxis: TCGVector;
const
  r: TCGVector = (x: 0; y: 1; z: 0; w: 1);
begin

  { Return a unit vector along the Y axis. }
  Result := r;

end;

function cgZAxis: TCGVector;
const
  r: TCGVector = (x: 0; y: 0; z: 1; w: 1);
begin

  { Return a unit vector along the Z axis. }
  Result := r;

end;

function cgVectorComp(v1, v2: TCGVector): Boolean;
begin

  { Determine if two vectors are equal. }
  Result := (Abs(v1.x - v2.x) < CG_EPS) and (Abs(v1.y - v2.y) < CG_EPS) and
            (Abs(v1.z - v2.z) < CG_EPS);

end;

procedure cgTranslate(var v: TCGVector; t: TCGVector);
begin

  { Translate vector v over vector t. }
  with v do
  begin
    x := x + t.x;
    y := y + t.y;
    z := z + t.z;
  end;

end;

function cgVecAdd(v1, v2: TCGVector): TCGVector;
begin

  // Add two vectors.
  with Result do
  begin
    x := v1.x + v2.x;
    y := v1.y + v2.y;
    z := v1.z + v2.z;
  end;

end;

function cgVecSub(v1, v2: TCGVector): TCGVector;
begin

  // Add two vectors.
  with Result do
  begin
    x := v1.x - v2.x;
    y := v1.y - v2.y;
    z := v1.z - v2.z;
  end;

end;

function cgVecScalarMult(v: TCGVector; s: Single): TCGVector;
begin

  with Result do
  begin
    x := v.x * s;
    y := v.y * s;
    z := v.z * s;
  end;

end;

procedure cgMirror(var v: TCGVector; mx, my, mz: Boolean);
begin

  { Mirror v around any axis. }
  with v do
  begin
    if mx then x := -x;
    if my then y := -y;
    if mz then z := -z;
  end;

end;

procedure cgScale(var v: TCGVector; sx, sy, sz: Single);
begin

  { Scale v with the given scale factors for each axis. }
  with v do
  begin
    x := x * sx;
    y := y * sy;
    z := z * sz;
  end;

end;

function cgVectorLength(v: TCGVector): Single;
begin

  { Calculate v's length (distance to the origin), using Pythagoras in 3D. }
  Result := sqrt(v.x*v.x + v.y*v.y + v.z*v.z);

end;

function cgVectorDistance(v1, v2: TCGVector): Single;
begin

  { Calculate the distance between two points. }
  cgMirror(v1, TRUE, TRUE, TRUE);
  cgTranslate(v2, v1);
  Result := cgVectorLength(v2);

end;

procedure cgNormalize(var v: TCGVector);
var
  l: Single;
begin

  { Normalize a vector by dividing its components by its length. }
  l := cgVectorLength(v);
  if l <> 0 then
  begin
    with v do
    begin
      x := x / l;
      y := y / l;
      z := z / l;
    end;
  end;

end;

procedure cgRotateX(var v: TCGVector; a: Single);
var
  temp: TCGVector;
begin

  { Rotate v over a radians around the X-axis. }
  with temp do
  begin
    x := v.x;
    y := (v.y * cos(a)) + (v.z * -sin(a));
    z := (v.y * sin(a)) + (v.z * cos(a));
    w := 1;
  end;
  v := temp;

end;

procedure cgRotateY(var v: TCGVector; a: Single);
var
  temp: TCGVector;
begin

  { Rotate v over a radians around the Y-axis. }
  with temp do
  begin
    x := (v.x * cos(a)) + (v.z * sin(a));
    y := v.y;
    z := (v.x * -sin(a)) + (v.z * cos(a));
    w := 1;
  end;
  v := temp;

end;

procedure cgRotateZ(var v: TCGVector; a: Single);
var
  temp: TCGVector;
begin

  { Rotate v over a radians around the Z-axis. }
  with temp do
  begin
    x := (v.x * cos(a)) + (v.y * -sin(a));
    y := (v.x * sin(a)) + (v.y * cos(a));
    z := v.z;
    w := 1;
  end;
  v := temp;

end;

function cgDotProduct(v1, v2: TCGVector): Single;
begin

  // Return the dot product v1 . v2
  Result := v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

end;

function cgCrossProduct(v1, v2: TCGVector): TCGVector;
begin

  // Return the cross product v1 x v2.
  Result := cgVector(v1.y * v2.z - v2.y * v1.z,
                     v2.x * v1.z - v1.x * v2.z,
                     v1.x * v2.y - v2.x * v1.y);

end;

function cgGetNormal(v1, v2, v3: TCGVector): TCGVector;
begin

  // Return the normal vector to the plane defined by v1, v2 and v3.
  cgMirror(v2, TRUE, TRUE, TRUE);
  cgTranslate(v1, v2);
  cgTranslate(v3, v2);
  Result := cgCrossProduct(v1, v3);
  cgNormalize(Result);

end;

function cgVecMult(v1, v2: TCGVector): TCGMatrix;
var
  i, j: Integer;
begin

  // Multiply a row and a column vector, resulting in a 4x4 matrix.
  for i := 0 to 3 do
  begin
    for j := 0 to 3 do
    begin
      Result[i,j] := TAVector(v1)[i] * TAVector(v2)[j];
    end;
  end;

end;

function cgIdentity: TCGMatrix;
const
  i: TCGMatrix = ((1, 0, 0, 0), (0, 1, 0, 0), (0, 0, 1, 0), (0, 0, 0, 1));
begin

  // Return the identity matrix.
  Result := i;

end;

function cgNullMatrix: TCGMatrix;
const
  n: TCGMatrix = ((0, 0, 0, 0), (0, 0, 0, 0), (0, 0, 0, 0), (0, 0, 0, 0));
begin

  // Return the null matrix.
  Result := n;

end;

procedure cgApplyMatrix(var v: TCGVector; m: TCGMatrix);
var
  t: TCGVector;
  r, c: Integer;
begin

  // Multiply v with the matrix m.
  for c := 0 to 3 do
  begin
    TAVector(t)[c] := 0;
    for r := 0 to 3 do
    begin
      TAVector(t)[c] := TAVector(t)[c] + TAVector(v)[r] * m[r,c];
    end;
  end;
  v := t;

end;

procedure cgMatrixAdd(var m1: TCGMatrix; m2: TCGMatrix);
var
  i, j: Integer;
begin

  // Add the second matrix to the first.
  for i := 0 to 3 do
  begin
    for j := 0 to 3 do
    begin
      m1[i,j] := m1[i,j] + m2[i,j];
    end;
  end;

end;

procedure cgMatrixSub(var m1: TCGMatrix; m2: TCGMatrix);
var
  i, j: Integer;
begin

  // Substract the second matrix from the first.
  for i := 0 to 3 do
  begin
    for j := 0 to 3 do
    begin
      m1[i,j] := m1[i,j] - m2[i,j];
    end;
  end;

end;

procedure cgMatrixMult(var m1: TCGMatrix; m2: TCGMatrix);
var
  r, c, i: Byte;
  t: TCGMatrix;
begin

  // Multiply two matrices.
  t := cgNullMatrix;
  for r := 0 to 3 do
  begin
    for c := 0 to 3 do
    begin
      for i := 0 to 3 do
      begin
        t[r,c] := t[r,c] + (m1[r,i] * m2[i,c]);
      end;
    end;
  end;
  m1 := t;

end;

procedure cgMScalarMult(var m: TCGMatrix; s: Single);
var
  i, j: Integer;
begin

  // Multiply a matrix with a scalar.
  for i := 0 to 3 do
  begin
    for j := 0 to 3 do
    begin
      m[i,j] := m[i,j] * s;
    end;
  end;

end;

function cgMRotateX(angle: Single): TCGMatrix;
begin

  // Return a rotation matrix for the X axis.
  Result := cgIdentity;
  Result[1,1] := cos(angle);
  Result[2,2] := Result[1,1];   // Don't calculate cosine twice.
  Result[1,2] := sin(angle);
  Result[2,1] := -Result[1,2];

end;

function cgMRotateY(angle: Single): TCGMatrix;
begin

  // Return a rotation matrix for the Y axis.
  Result := cgIdentity;
  Result[0,0] := cos(angle);
  Result[2,2] := Result[0,0];
  Result[0,2] := -sin(angle);
  Result[2,0] := -Result[0,2];

end;

function cgMRotateZ(angle: Single): TCGMatrix;
begin

  // Return a rotation matrix for the Z axis.
  Result := cgIdentity;
  Result[0,0] := cos(angle);
  Result[1,1] := Result[0,0];
  Result[0,1] := sin(angle);
  Result[1,0] := -Result[0,1];

end;

function cgMScale(sx, sy, sz: Single): TCGMatrix;
begin

  // Return a transformation matrix for scaling.
  Result := cgIdentity;
  Result[0,0] := sx;
  Result[1,1] := sy;
  Result[2,2] := sz;

end;

function cgPlaneFromPoints(p1, p2, p3: TCGVector): TCGPlane;
var
  n: TCGVector;
begin

  { Create a TCGPlane from 3 coplanar points. To do this, calculate the normal
    to the plane. The x, y and z components of the normal vector correspond to
    the A, B and C components of the plane. D can then be very easily calculated
    knowing that Ax + By + Cz + D = 0 for any point on the plane, such as p1. }
  n := cgGetNormal(p1, p2, p3);
  with Result do
  begin
    A := n.x;
    B := n.y;
    C := n.z;
    D := -(A * p1.x + B * p1.y + c * p1.z);
  end;

end;

end.
