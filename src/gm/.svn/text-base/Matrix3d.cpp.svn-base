// matrix3d.cc - 3x3 element matrix class
//
// libgm++: Graphics Math Library
// Ferdi Scheepers and Stephen F May
// 15 June 1994

#include "StdAfx.h"

#define DrawExt DECLSPEC_DLLEXPORT

#include "../LFC/LFC.h"

namespace System
{
namespace gm
{

// private function: RCD
// - dot product of row i of matrix A and row j of matrix B

inline double RCD(const matrix3d& A, const matrix3d& B, int i, int j)
{
  return A[i][0] * B[0][j] + A[i][1] * B[1][j] + A[i][2] * B[2][j];
}

// private function: MINOR
// - MINOR of M[r][c]; r in {0,1,2}-{r0,r1}; c in {0,1,2}-{c0,c1}

inline double MINOR(const matrix3d& M, int r0, int r1, int c0, int c1)
{
  return M[r0][c0] * M[r1][c1] - M[r1][c0] * M[r0][c1];
}

// CONSTRUCTORS

matrix3d::matrix3d()
{
  assign(0,0,0, 0,0,0, 0,0,0);
}

matrix3d::matrix3d(const matrix3d& M)
{
  assign(M[0][0], M[0][1], M[0][2],
         M[1][0], M[1][1], M[1][2],
         M[2][0], M[2][1], M[2][2]);
}

matrix3d::matrix3d(double a00, double a01, double a02,
		     double a10, double a11, double a12,
		     double a20, double a21, double a22)
{
  assign(a00, a01, a02,
         a10, a11, a12,
         a20, a21, a22);
}

// ASSIGNMENT

matrix3d& matrix3d::assign(double a00, double a01, double a02,
		             double a10, double a11, double a12,
		             double a20, double a21, double a22)
{
  m_[0][0] = a00; m_[0][1] = a01; m_[0][2] = a02;
  m_[1][0] = a10; m_[1][1] = a11; m_[1][2] = a12;
  m_[2][0] = a20; m_[2][1] = a21; m_[2][2] = a22;
  return *this;
}

matrix3d& matrix3d::operator =(const matrix3d& M)
{
  assign(M[0][0], M[0][1], M[0][2],
	 M[1][0], M[1][1], M[1][2],
         M[2][0], M[2][1], M[2][2]);
  return *this;
}

// OPERATORS

matrix3d& matrix3d::operator +=(const matrix3d& M)
{
  m_[0][0] += M[0][0]; m_[0][1] += M[0][1]; m_[0][2] += M[0][2];
  m_[1][0] += M[1][0]; m_[1][1] += M[1][1]; m_[1][2] += M[1][2];
  m_[2][0] += M[2][0]; m_[2][1] += M[2][1]; m_[2][2] += M[2][2];
  return *this;
}

matrix3d& matrix3d::operator -=(const matrix3d& M)
{
  m_[0][0] -= M[0][0]; m_[0][1] -= M[0][1]; m_[0][2] -= M[0][2];
  m_[1][0] -= M[1][0]; m_[1][1] -= M[1][1]; m_[1][2] -= M[1][2];
  m_[2][0] -= M[2][0]; m_[2][1] -= M[2][1]; m_[2][2] -= M[2][2];
  return *this;
}

matrix3d& matrix3d::operator *=(const matrix3d& M)
{
  assign(RCD(*this, M, 0, 0), RCD(*this, M, 0, 1), RCD(*this, M, 0, 2),
	 RCD(*this, M, 1, 0), RCD(*this, M, 1, 1), RCD(*this, M, 1, 2),
	 RCD(*this, M, 2, 0), RCD(*this, M, 2, 1), RCD(*this, M, 2, 2));
  return *this;
}

matrix3d& matrix3d::operator *=(double d)
{
  m_[0][0] *= d; m_[0][1] *= d; m_[0][2] *= d;
  m_[1][0] *= d; m_[1][1] *= d; m_[1][2] *= d;
  m_[2][0] *= d; m_[2][1] *= d; m_[2][2] *= d;
  return *this;
}

matrix3d& matrix3d::operator /=(double d)
{
  double di = 1 / d;
  m_[0][0] *= di; m_[0][1] *= di; m_[0][2] *= di;
  m_[1][0] *= di; m_[1][1] *= di; m_[1][2] *= di;
  m_[2][0] *= di; m_[2][1] *= di; m_[2][2] *= di;
  return *this;
}

matrix3d matrix3d::operator +(const matrix3d& M) const
{
  return matrix3d(m_[0][0] + M[0][0], m_[0][1] + M[0][1], m_[0][2] + M[0][2],
		   m_[1][0] + M[1][0], m_[1][1] + M[1][1], m_[1][2] + M[1][2],
		   m_[2][0] + M[2][0], m_[2][1] + M[2][1], m_[2][2] + M[2][2]);
}

matrix3d matrix3d::operator -(const matrix3d& M) const
{
  return matrix3d(m_[0][0] - M[0][0], m_[0][1] - M[0][1], m_[0][2] - M[0][2],
		   m_[1][0] - M[1][0], m_[1][1] - M[1][1], m_[1][2] - M[1][2],
		   m_[2][0] - M[2][0], m_[2][1] - M[2][1], m_[2][2] - M[2][2]);
}

matrix3d matrix3d::operator -() const
{
  return matrix3d(-m_[0][0], -m_[0][1], -m_[0][2],
		   -m_[1][0], -m_[1][1], -m_[1][2],
                   -m_[2][0], -m_[2][1], -m_[2][2]);
}

matrix3d matrix3d::operator *(const matrix3d& M) const
{
  return
    matrix3d(RCD(*this, M, 0, 0), RCD(*this, M, 0, 1), RCD(*this, M, 0, 2),
              RCD(*this, M, 1, 0), RCD(*this, M, 1, 1), RCD(*this, M, 1, 2),
              RCD(*this, M, 2, 0), RCD(*this, M, 2, 1), RCD(*this, M, 2, 2));
}

matrix3d matrix3d::operator *(double d) const
{
  return matrix3d(m_[0][0] * d, m_[0][1] * d, m_[0][2] * d,
		   m_[1][0] * d, m_[1][1] * d, m_[1][2] * d,
                   m_[2][0] * d, m_[2][1] * d, m_[2][2] * d);
}

matrix3d matrix3d::operator /(double d) const
{
  ASSERT(!gmIsZero(d));
  double di = 1 / d;
  return matrix3d(m_[0][0] * di, m_[0][1] * di, m_[0][2] * di,
		   m_[1][0] * di, m_[1][1] * di, m_[1][2] * di,
                   m_[2][0] * di, m_[2][1] * di, m_[2][2] * di);
}

DrawExt matrix3d operator *(double d, const matrix3d& M)
{
  return matrix3d(M[0][0] * d, M[0][1] * d, M[0][2] * d,
		   M[1][0] * d, M[1][1] * d, M[1][2] * d,
                   M[2][0] * d, M[2][1] * d, M[2][2] * d);
}

bool matrix3d::operator ==(const matrix3d& M) const
{
  return(gmFuzEQ(m_[0][0], M[0][0]) &&
         gmFuzEQ(m_[0][1], M[0][1]) &&
	 gmFuzEQ(m_[0][2], M[0][2]) &&
	 
	 gmFuzEQ(m_[1][0], M[1][0]) &&
         gmFuzEQ(m_[1][1], M[1][1]) &&
	 gmFuzEQ(m_[1][2], M[1][2]) &&

	 gmFuzEQ(m_[2][0], M[2][0]) &&
         gmFuzEQ(m_[2][1], M[2][1]) &&
	 gmFuzEQ(m_[2][2], M[2][2]));
}

vector3d matrix3d::operator *(const vector3d& v) const
{
  return vector3d(m_[0][0] * v[0] + m_[0][1] * v[1] + m_[0][2] * v[2],
                   m_[1][0] * v[0] + m_[1][1] * v[1] + m_[1][2] * v[2],
                   m_[2][0] * v[0] + m_[2][1] * v[1] + m_[2][2] * v[2]);
}

vector3d operator *(const vector3d& v, const matrix3d& M)
{
  return vector3d(v[0] * M[0][0] + v[1] * M[1][0] + v[2] * M[2][0],
                   v[0] * M[0][1] + v[1] * M[1][1] + v[2] * M[2][1],
                   v[0] * M[0][2] * v[1] * M[1][2] + v[2] * M[2][2]);
}

// OPERATIONS

matrix3d matrix3d::getTransposed() const
{
  return matrix3d(m_[0][0], m_[1][0], m_[2][0],
		   m_[0][1], m_[1][1], m_[2][1],
                   m_[0][2], m_[1][2], m_[2][2]);
}

matrix3d matrix3d::getInverse() const
{
  ASSERT(!isSingular());
  return getAdjoint() * gmInv(determinant());
}

matrix3d matrix3d::getAdjoint() const
{
  matrix3d A;
  
  A[0][0] =  MINOR(*this, 1, 2, 1, 2);
  A[0][1] = -MINOR(*this, 0, 2, 1, 2);
  A[0][2] =  MINOR(*this, 0, 1, 1, 2);
  A[1][0] = -MINOR(*this, 1, 2, 0, 2);
  A[1][1] =  MINOR(*this, 0, 2, 0, 2);
  A[1][2] = -MINOR(*this, 0, 1, 0, 2);
  A[2][0] =  MINOR(*this, 1, 2, 0, 1);
  A[2][1] = -MINOR(*this, 0, 2, 0, 1);
  A[2][2] =  MINOR(*this, 0, 1, 0, 1);

  return A;
}

double matrix3d::determinant() const
{
  return m_[0][0] * MINOR(*this, 1, 2, 1, 2) -
         m_[0][1] * MINOR(*this, 1, 2, 0, 2) +
	 m_[0][2] * MINOR(*this, 1, 2, 0, 1);
}

bool matrix3d::isSingular() const
{
  return gmIsZero(determinant());
}

/*
vector2d matrix3d::transform(const gmVector2f& v) const
{
  return vector2d(v[0] * m_[0][0] + v[1] * m_[1][0] + m_[2][0],
                   v[0] * m_[0][1] + v[1] * m_[1][1] + m_[2][1]);
}
*/

vector2d matrix3d::transform(const vector2d& v) const
{
  return vector2d(v[0] * m_[0][0] + v[1] * m_[1][0] + m_[2][0],
                   v[0] * m_[0][1] + v[1] * m_[1][1] + m_[2][1]);
}

vector3d matrix3d::transform(const vector3d& v) const
{
  return vector3d(
	 v[0] * m_[0][0] + v[1] * m_[1][0] + v[2] * m_[2][0]/* + m_[3][0]*/,
	 v[0] * m_[0][1] + v[1] * m_[1][1] + v[2] * m_[2][1]/* + m_[3][1]*/,
	 v[0] * m_[0][2] + v[1] * m_[1][2] + v[2] * m_[2][2]/* + m_[3][2]*/);
}

/*
DblPOINT matrix3d::transform(const DblPOINT& v) const
{
	DblPOINT r;

	r.x = v.x * m_[0][0] + v.y * m_[1][0] + m_[2][0];
	r.y = v.x * m_[0][1] + v.y * m_[1][1] + m_[2][1];

	return r;
}
*/

// TRANSFORMATION MATRICES

// static
matrix3d matrix3d::getIdentity()
{
  return matrix3d(1, 0, 0,
                   0, 1, 0,
                   0, 0, 1);
}

// static
matrix3d matrix3d::getRotate(double angle)
{
  double sine = sin(gmRadians(angle));
  double cosine = cos(gmRadians(angle));
  
  return matrix3d( cosine, sine,   0,
                   -sine,   cosine, 0,
                    0,      0,      1);
}

// static
matrix3d matrix3d::getScale(double x, double y)
{
  return matrix3d(x, 0, 0,
		   0, y, 0,
		   0, 0, 1);
}

// static
matrix3d matrix3d::getTranslate(double x, double y)
{
  return matrix3d(1, 0, 0,
		   0, 1, 0,
		   x, y, 1);
}

/*

SkewX

1	tan(a)	0
0	1			0
0	0			1

SkewY

1			0	0
tan(a)	1	0
0			0	1


*/

// static
matrix3d matrix3d::getSkewX(double x)
{
  return

	matrix3d(
	1, tan(gmRadians(x)), 0,
	0, 1, 0,
	0, 0, 1);
}

// static
matrix3d matrix3d::getSkewY(double y)
{
  return

	matrix3d(
	1, 0, 0,
	tan(gmRadians(y)), 1, 0,
	0, 0, 1);
}

// static
matrix3d matrix3d::getTilde(const vector3d& v)
{
  double rx = v[0];
  double ry = v[1];
  double rz = v[2];

  return matrix3d(
	  0, - rz, ry, 
	  rz,  0, - rx,
	  -ry, rx, 0 );
}

Matrix3d::Matrix3d()
{
}

Matrix3d::Matrix3d(double m11, double m12, double m21, double m22, double dx, double dy) :
	m_matrix(m11, m12, 0, m21, m22, 0, dx, dy, 1)
{
}

Matrix3d::Matrix3d(double m11, double m12, double m13, double m21, double m22, double m23, double dx, double dy, double dz) :
	m_matrix(m11, m12, m13, m21, m22, m23, dx, dy, dz)
{
}

Matrix3d::Matrix3d(const matrix3d& mat) : m_matrix(mat)
{
}

double Matrix3d::Determinant() const
{
	return m_matrix.determinant();
}

bool Matrix3d::Equals(const Matrix3d& other) const
{
	return m_matrix == other.m_matrix;
}

static __release<Matrix3d> IdentityMatrix = new Matrix3d(matrix3d::getIdentity());

#if 0

///////////////////////////////////////
// Matrix3d

Matrix3d::Matrix3d()
{
	m_p = NULL;
}

Matrix3d::Matrix3d(Matrix3d *p)
{
	m_p = p;
	if (m_p) m_p->AddRef();
}

Matrix3d::Matrix3d(const Matrix3d& other)
{
	m_p = other.m_p;
	if (m_p)
	{
		m_p->AddRef();
	}
}

/*
Matrix::Matrix(const gmMatrix3& other)
{
	m_p = new _Matrix(other);
	m_p->AddRef();
}
*/

Matrix3d::Matrix3d(double m11, double m12, double m21, double m22, double dx, double dy)
{
	m_p = new Matrix3d(m11, m12, m21, m22, dx, dy);
	m_p->AddRef();
}

Matrix3d::Matrix3d(double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33)
{
	m_p = new Matrix3d(m11, m12, m13, m21, m22, m23, m31, m32, m33);
	m_p->AddRef();
}

Matrix3d::Matrix3d(const matrix3d & m)
{
	m_p = new Matrix3d(m);
	m_p->AddRef();
}

Matrix3d::~Matrix3d()
{
	if (m_p)
	{
		m_p->Release();
	}
}

void Matrix3d::Get(double m[3][2]) const
{
	ASSERT(m_p);
	if (m_p == NULL) THROW(-1);

	m[0][0] = m_p->m_matrix[0][0];
	m[1][0] = m_p->m_matrix[1][0];
	m[0][1] = m_p->m_matrix[0][1];
	m[1][1] = m_p->m_matrix[1][1];
	m[2][0] = m_p->m_matrix[2][0];
	m[2][1] = m_p->m_matrix[2][1];
//	ASSERT(m_p->m_matrix[2][0] == 0);
//	ASSERT(m_p->m_matrix[2][1] == 0);
//	ASSERT(m_p->m_matrix[2][2] == 1);
}

void Matrix3d::Get(double m[9]) const
{
	memcpy(m, &m_p->m_matrix, 9*4);
}
#endif

PointD Matrix3d::Transform(const PointD & point) const
{
	/*
	ASSERT(m_p);
	if (m_p == NULL) THROW(-1);
	*/
	return m_matrix.transform(*(const vector2d*)&point);
}

#if 0
vector3d Matrix3d::Transform(const vector3d & v) const
{
	/*
	ASSERT(m_p);
	if (m_p == NULL) THROW(-1);
	*/
	return m_matrix.transform(v);
}
#endif

#if 0

vector3d Matrix3d::operator * (const vector3d& v) const
{
	return m_p->m_matrix * v;
}

DrawExt vector3d operator * (const vector3d& v, const Matrix3d& m)
{
	return v * m.m_p->m_matrix;
}

/*
PointD Matrix::Transform(const PointD& point) const
{
	ASSERT(m_p);
	if (m_p == NULL) THROW(-1);
	return m_p->m_matrix.transform(vector2d(point.X, point.Y));
}
*/

/*
void transform_2points(float *outvec, float m[3*2], const float *invec)
{
	__asm
	{
		push		ecx

		MOV		eax,[invec]
		MOV		ebx,[outvec]
		MOV		ecx,[m]
		MOVUPS	xmm7,[eax]
		MOVUPS	xmm6,[ecx]

		MOVSLDUP	(MOD_11(1,7))	//	x0,x0,x1,x1
		MOVUPS	[ebx],xmm1

		MOVSHDUP	(MOD_11(2,7))	// y0,y0,y1,y1
		MOVUPS	[ebx],xmm2

		MULPS		xmm1,xmm6	// (x0*m0),(x0*m1),(x1*m2),(x1*m3)
		MOVUPS	[ebx],xmm1

		MULPS		xmm2,xmm6	// (y0*m0),(y0*m1),(y1*m2),(y1*m3)
		MOVUPS	[ebx],xmm2

		HADDPS	(MOD_11(1,2))
		//ADDPS		xmm1,[ecx+4]

		MOVUPS	[ebx],xmm1	// x0,y0,x1,y1

		MOVUPS	[ebx],xmm1	// x0,y0,x1,y1

		pop	ecx
	}
}
*/

void Matrix3d::TransformPoints(PointD* dst, const PointD* src, int count) const
{
	const double* m = (const double*)&m_p->m_matrix;

	while (count--)
	{
		double x = src->X * m[0] + src->Y * m[3] + m[6];
		double y = src->X * m[1] + src->Y * m[4] + m[7];
		dst->X = x;
		dst->Y = y;

		dst++;
		src++;
	}

#if 0
	gmMatrix3f& m = m_p->m_matrix;

	double mt[6];
	mt[0] = m[0][0];
	mt[1] = m[1][0];
	mt[2] = m[0][1];
	mt[3] = m[1][1];
	mt[4] = m[0][2];
	mt[5] = m[1][2];

	int n = count;
	while (n >= 2)
	{
	//	dst[0] = m.transform(src[0]);
	//	dst[1] = m.transform(src[1]);
		transform_2points((double*)dst, mt, (const double*)src);

		dst += 2;
		src += 2;
		n -= 2;
	}

	if (n)
	{
		dst[0] = m.transform(src[0]);
	}
#endif
}

Matrix3d Matrix3d::GetMultiplied(const Matrix3d& other) const
{
	if (other.m_p == NULL)
		return *this;

	if (m_p == NULL)
	{
		return other;
	//	m_p = other.m_p;
	//	m_p->AddRef();
	//	return *this;
	}

	/*
	if (m_p->m_refcount > 1)
	{
		m_p->Release();
		m_p = new _Matrix(m_p->m_matrix);
		m_p->AddRef();
	}
	m_p->m_matrix = other.m_p->m_matrix * m_p->m_matrix;

  return *this;
	*/
	return new Matrix3d(other.m_p->m_matrix * m_p->m_matrix);
}

double Matrix3d::Determinant() const
{
	VERIFY(m_p);
	return m_p->m_matrix.determinant();
}
#endif

// static
__release<Matrix3d> Matrix3d::GetIdentity()
{
	return IdentityMatrix;
}

// static
__release<Matrix3d> Matrix3d::GetTranslate(double dx, double dy)
{
	return new Matrix3d(matrix3d::getTranslate(dx, dy));
}

// static
__release<Matrix3d> Matrix3d::GetScale(double sx, double sy)
{
	return new Matrix3d(matrix3d::getScale(sx, sy));
}

// static
__release<Matrix3d> Matrix3d::GetRotate(double angle)
{
	return new Matrix3d(matrix3d::getRotate(angle));
}

// static
__release<Matrix3d> Matrix3d::GetSkewX(double angle)
{
	return new Matrix3d(matrix3d::getSkewX(angle));
}

// static
__release<Matrix3d> Matrix3d::GetSkewY(double angle)
{
	return new Matrix3d(matrix3d::getSkewY(angle));
}

__release<Matrix3d> Matrix3d::GetInverse()
{
	return new Matrix3d(m_matrix.getInverse());
}

__release<Matrix3d> Matrix3d::operator * (const Matrix3d & other) const
{
	return new Matrix3d(m_matrix * other.m_matrix);
}

#if 0

void Matrix3d::Multiply(const Matrix3d& other, MatrixOrder order)
{
	if (other.m_p == NULL)
		return;

	if (m_p == NULL)
	{
		m_p = other.m_p;
		m_p->AddRef();
		return;
	}

	if (m_p->m_refcount > 1)
	{
		m_p->Release();
		m_p = new Matrix3d(m_p->m_matrix);
		m_p->AddRef();
	}

	if (order == MatrixOrderPrepend)
		m_p->m_matrix = other.m_p->m_matrix * m_p->m_matrix;
	else
		m_p->m_matrix = m_p->m_matrix * other.m_p->m_matrix;
}

void Matrix3d::Translate(double dx, double dy, MatrixOrder order)
{
	if (m_p == NULL)
	{
		m_p = new Matrix3d;
		m_p->AddRef();
		m_p->m_matrix = matrix3d::getTranslate(dx, dy);
		return;// *this;
	}

	if (m_p->m_refcount > 1)
	{
		m_p->Release();
		m_p = new Matrix3d(m_p->m_matrix);
		m_p->AddRef();
	}

	if (order == MatrixOrderPrepend)
		m_p->m_matrix = matrix3d::getTranslate(dx, dy) * m_p->m_matrix;
	else
		m_p->m_matrix = m_p->m_matrix * matrix3d::getTranslate(dx, dy);
}

void Matrix3d::Scale(double sx, double sy, MatrixOrder order)
{
	if (m_p == NULL)
	{
		m_p = new Matrix3d;
		m_p->AddRef();
		m_p->m_matrix = matrix3d::getScale(sx, sy);
		return;
	}

	if (m_p->m_refcount > 1)
	{
		m_p->Release();
		m_p = new Matrix3d(m_p->m_matrix);
		m_p->AddRef();
	}

	if (order == MatrixOrderPrepend)
		m_p->m_matrix = matrix3d::getScale(sx, sy) * m_p->m_matrix;
	else
		m_p->m_matrix = m_p->m_matrix * matrix3d::getScale(sx, sy);
}

void Matrix3d::Rotate(double angle, MatrixOrder order)
{
	if (m_p == NULL)
	{
		m_p = new Matrix3d;
		m_p->AddRef();
		m_p->m_matrix = matrix3d::getRotate(angle);
		return;
	}

	if (m_p->m_refcount > 1)
	{
		m_p->Release();
		m_p = new Matrix3d(m_p->m_matrix);
		m_p->AddRef();
	}

	if (order == MatrixOrderPrepend)
		m_p->m_matrix = matrix3d::getRotate(angle) * m_p->m_matrix;
	else
		m_p->m_matrix = m_p->m_matrix * matrix3d::getRotate(angle);
}

/*
Matrix& Matrix::Identity()
{
	if (m_p == NULL)
	{
		m_p = new _Matrix;
		m_p->AddRef();
		m_p->m_matrix = gmMatrix3::identity();
		return *this;
	}

	if (m_p->m_refcount > 1)
	{
		m_p->Release();
		m_p = new _Matrix;
		m_p->AddRef();
	}
	m_p->m_matrix = gmMatrix3::identity();

	return *this;
}
*/

void Matrix3d::Invert()
{
	if (m_p == NULL)
	{
		return;// *this;
	}

	if (m_p->m_refcount > 1)
	{
		Matrix3d* p = m_p;
		m_p = new Matrix3d(p->m_matrix.getInverse());
		m_p->AddRef();
		p->Release();
	}
	else
	{
		m_p->m_matrix = m_p->m_matrix.getInverse();
	}

	/*
	Matrix mat;
	mat.m_p = new _Matrix;
	mat.m_p->AddRef();

	mat.m_p->m_matrix = m_p->m_matrix.inverse();

	return mat;
	*/
}

Matrix3d& Matrix3d::operator = (const Matrix3d& other)
{
	Matrix3d* old = m_p;

	m_p = other.m_p;

	if (m_p) m_p->AddRef();
	if (old) old->Release();

	return *this;
}

Matrix3d& Matrix3d::operator *= (const Matrix3d& other)
{
	if (m_p == NULL)
	{
		m_p = other.m_p;
		if (m_p) m_p->AddRef();
		return *this;
	}
	else if (other.m_p == NULL)
	{
		return *this;
	}

	if (m_p->m_refcount > 1)
	{
		m_p->Release();
		m_p = new Matrix3d(*m_p);
		m_p->AddRef();
	}
	m_p->m_matrix *= other.m_p->m_matrix;

	return *this;
}

/*
Matrix& Matrix::operator = (const gmMatrix3f& other)
{
	if (m_p == NULL)
	{
		m_p = new _Matrix;
		m_p->AddRef();
		m_p->m_matrix = other;
		return *this;
	}

	if (m_p->m_refcount > 1)
	{
		m_p->Release();
		m_p = new _Matrix;
		m_p->AddRef();
	}
	m_p->m_matrix = other;

	return *this;
}
*/

Matrix3d Matrix3d::operator * (const Matrix3d& other) const
{
	Matrix3d mat;
	mat.m_p = new Matrix3d;
	mat.m_p->AddRef();
	mat.m_p->m_matrix = m_p->m_matrix * other.m_p->m_matrix;

	/*
	Matrix3d* old = m_p;

	m_p = other.m_p;

	if (m_p) m_p->AddRef();
	if (old) old->Release();
	*/

	return mat;
}

bool Matrix3d::ReferenceEquals(const Matrix3d& other) const
{
	return m_p == other.m_p;
}

bool Matrix3d::Equals(const Matrix3d& other) const
{
	if (m_p == other.m_p) return true;
	if (m_p == NULL) return false;
	if (other.m_p == NULL) return false;
	return m_p->Equals(*other.m_p);
}

bool Matrix3d::IsIdentity() const
{
	return Equals(IdentityMatrix);
}

bool Matrix3d::IsInvertible() const
{
	if (m_p == NULL) return false;
	return !m_p->m_matrix.isSingular();
}

/*
const double* Matrix::operator [] (int row) const
{
	VERIFY(m_p);
	VERIFY(row >= 0 && row < 3);
	return m_p->m_matrix[row];
}
*/

#endif

}	// gm
}	// System
