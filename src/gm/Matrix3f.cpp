// matrix3f.cc - 3x3 element matrix class
//
// libgm++: Graphics Math Library
// Ferdi Scheepers and Stephen F May
// 15 June 1994

//#include "stdafx.h"

#include "StdAfx.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
*/

#define DrawExt DECLSPEC_DLLEXPORT

#include "../LFC/LFC.h"

/*
#include "Matrix3f.h"

#include "vector2.h"
#include "Vector3.h"
*/

namespace System
{
namespace gm
{

// private function: RCD
// - dot product of row i of matrix A and row j of matrix B

inline float RCD(const matrix3f& A, const matrix3f& B, int i, int j)
{
  return A[i][0] * B[0][j] + A[i][1] * B[1][j] + A[i][2] * B[2][j];
}

// private function: MINOR
// - MINOR of M[r][c]; r in {0,1,2}-{r0,r1}; c in {0,1,2}-{c0,c1}

inline float MINOR(const matrix3f& M, int r0, int r1, int c0, int c1)
{
  return M[r0][c0] * M[r1][c1] - M[r1][c0] * M[r0][c1];
}

// CONSTRUCTORS

matrix3f::matrix3f()
{
  assign(0,0,0, 0,0,0, 0,0,0);
}

matrix3f::matrix3f(const matrix3f& M)
{
  assign(M[0][0], M[0][1], M[0][2],
         M[1][0], M[1][1], M[1][2],
         M[2][0], M[2][1], M[2][2]);
}

matrix3f::matrix3f(float a00, float a01, float a02,
		     float a10, float a11, float a12,
		     float a20, float a21, float a22)
{
  assign(a00, a01, a02,
         a10, a11, a12,
         a20, a21, a22);
}

// ASSIGNMENT

matrix3f& matrix3f::assign(float a00, float a01, float a02,
		             float a10, float a11, float a12,
		             float a20, float a21, float a22)
{
  m_[0][0] = a00; m_[0][1] = a01; m_[0][2] = a02;
  m_[1][0] = a10; m_[1][1] = a11; m_[1][2] = a12;
  m_[2][0] = a20; m_[2][1] = a21; m_[2][2] = a22;
  return *this;
}

matrix3f& matrix3f::operator =(const matrix3f& M)
{
  assign(M[0][0], M[0][1], M[0][2],
	 M[1][0], M[1][1], M[1][2],
         M[2][0], M[2][1], M[2][2]);
  return *this;
}

// OPERATORS

matrix3f& matrix3f::operator +=(const matrix3f& M)
{
  m_[0][0] += M[0][0]; m_[0][1] += M[0][1]; m_[0][2] += M[0][2];
  m_[1][0] += M[1][0]; m_[1][1] += M[1][1]; m_[1][2] += M[1][2];
  m_[2][0] += M[2][0]; m_[2][1] += M[2][1]; m_[2][2] += M[2][2];
  return *this;
}

matrix3f& matrix3f::operator -=(const matrix3f& M)
{
  m_[0][0] -= M[0][0]; m_[0][1] -= M[0][1]; m_[0][2] -= M[0][2];
  m_[1][0] -= M[1][0]; m_[1][1] -= M[1][1]; m_[1][2] -= M[1][2];
  m_[2][0] -= M[2][0]; m_[2][1] -= M[2][1]; m_[2][2] -= M[2][2];
  return *this;
}

matrix3f& matrix3f::operator *=(const matrix3f& M)
{
#if AMIGA
	assign(1, 0, 0,
			0, 1, 0,
			m_[2][0] + M[2][0], m_[2][1] + M[2][1], 1);

#else
  assign(RCD(*this, M, 0, 0), RCD(*this, M, 0, 1), RCD(*this, M, 0, 2),
	 RCD(*this, M, 1, 0), RCD(*this, M, 1, 1), RCD(*this, M, 1, 2),
	 RCD(*this, M, 2, 0), RCD(*this, M, 2, 1), RCD(*this, M, 2, 2));
#endif
  return *this;
}

matrix3f& matrix3f::operator *=(float d)
{
  m_[0][0] *= d; m_[0][1] *= d; m_[0][2] *= d;
  m_[1][0] *= d; m_[1][1] *= d; m_[1][2] *= d;
  m_[2][0] *= d; m_[2][1] *= d; m_[2][2] *= d;
  return *this;
}

matrix3f& matrix3f::operator /=(float d)
{
  float di = 1 / d;
  m_[0][0] *= di; m_[0][1] *= di; m_[0][2] *= di;
  m_[1][0] *= di; m_[1][1] *= di; m_[1][2] *= di;
  m_[2][0] *= di; m_[2][1] *= di; m_[2][2] *= di;
  return *this;
}

matrix3f matrix3f::operator +(const matrix3f& M) const
{
  return matrix3f(m_[0][0] + M[0][0], m_[0][1] + M[0][1], m_[0][2] + M[0][2],
		   m_[1][0] + M[1][0], m_[1][1] + M[1][1], m_[1][2] + M[1][2],
		   m_[2][0] + M[2][0], m_[2][1] + M[2][1], m_[2][2] + M[2][2]);
}

matrix3f matrix3f::operator -(const matrix3f& M) const
{
  return matrix3f(m_[0][0] - M[0][0], m_[0][1] - M[0][1], m_[0][2] - M[0][2],
		   m_[1][0] - M[1][0], m_[1][1] - M[1][1], m_[1][2] - M[1][2],
		   m_[2][0] - M[2][0], m_[2][1] - M[2][1], m_[2][2] - M[2][2]);
}

matrix3f matrix3f::operator -() const
{
  return matrix3f(-m_[0][0], -m_[0][1], -m_[0][2],
		   -m_[1][0], -m_[1][1], -m_[1][2],
                   -m_[2][0], -m_[2][1], -m_[2][2]);
}

matrix3f matrix3f::operator *(const matrix3f& M) const
{
#if AMIGA

	return matrix3f(1, 0, 0,
							0, 1, 0,
							m_[2][0] + M[2][0], m_[2][1] + M[2][1], 1);
							

#else
  return
    matrix3f(RCD(*this, M, 0, 0), RCD(*this, M, 0, 1), RCD(*this, M, 0, 2),
              RCD(*this, M, 1, 0), RCD(*this, M, 1, 1), RCD(*this, M, 1, 2),
              RCD(*this, M, 2, 0), RCD(*this, M, 2, 1), RCD(*this, M, 2, 2));
#endif
}

matrix3f matrix3f::operator *(float d) const
{
  return matrix3f(m_[0][0] * d, m_[0][1] * d, m_[0][2] * d,
		   m_[1][0] * d, m_[1][1] * d, m_[1][2] * d,
                   m_[2][0] * d, m_[2][1] * d, m_[2][2] * d);
}

matrix3f matrix3f::operator /(float d) const
{
  ASSERT(!gmIsZero(d));
  float di = 1 / d;
  return matrix3f(m_[0][0] * di, m_[0][1] * di, m_[0][2] * di,
		   m_[1][0] * di, m_[1][1] * di, m_[1][2] * di,
                   m_[2][0] * di, m_[2][1] * di, m_[2][2] * di);
}

DrawExt matrix3f operator *(float d, const matrix3f& M)
{
  return matrix3f(M[0][0] * d, M[0][1] * d, M[0][2] * d,
		   M[1][0] * d, M[1][1] * d, M[1][2] * d,
                   M[2][0] * d, M[2][1] * d, M[2][2] * d);
}

bool matrix3f::operator ==(const matrix3f& M) const
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

bool matrix3f::operator !=(const matrix3f& M) const
{
  return (!(*this == M));
}

vector3f matrix3f::operator *(const vector3f& v) const
{
  return vector3f(m_[0][0] * v[0] + m_[0][1] * v[1] + m_[0][2] * v[2],
                   m_[1][0] * v[0] + m_[1][1] * v[1] + m_[1][2] * v[2],
                   m_[2][0] * v[0] + m_[2][1] * v[1] + m_[2][2] * v[2]);
}

vector3f operator *(const vector3f& v, const matrix3f& M)
{
  return vector3f(v[0] * M[0][0] + v[1] * M[1][0] + v[2] * M[2][0],
                   v[0] * M[0][1] + v[1] * M[1][1] + v[2] * M[2][1],
                   v[0] * M[0][2] * v[1] * M[1][2] + v[2] * M[2][2]);
}

// OPERATIONS

matrix3f matrix3f::getTransposed() const
{
  return matrix3f(m_[0][0], m_[1][0], m_[2][0],
		   m_[0][1], m_[1][1], m_[2][1],
                   m_[0][2], m_[1][2], m_[2][2]);
}

matrix3f matrix3f::getInverse() const
{
#if AMIGA
	return matrix3f(1, 0, 0,
							0, 1, 0,
							-m_[2][0], -m_[2][1], 1);
#else

  ASSERT(!isSingular());
  return adjoint() * gmInv(determinant());
#endif
}

matrix3f matrix3f::adjoint() const
{
  matrix3f A;
  
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

float matrix3f::determinant() const
{
  return m_[0][0] * MINOR(*this, 1, 2, 1, 2) -
         m_[0][1] * MINOR(*this, 1, 2, 0, 2) +
	 m_[0][2] * MINOR(*this, 1, 2, 0, 1);
}

bool matrix3f::isSingular() const
{
  return gmIsZero(determinant());
}

/*
transform_point(float out[2], float[2*3], cosnt float in[2])
{
}
*/

vector2f matrix3f::transform(const vector2f& v) const
{
#if AMIGA
	return vector2f(v[0] + m_[2][0], v[1] + m_[2][1]);
#else
  return vector2f(v[0] * m_[0][0] + v[1] * m_[1][0] + m_[2][0],
                   v[0] * m_[0][1] + v[1] * m_[1][1] + m_[2][1]);
#endif
}

vector2d matrix3f::transform(const vector2d& v) const
{
#if AMIGA
	return vector2d(v[0] + m_[2][0], v[1] + m_[2][1]);
#else
  return vector2d(v[0] * m_[0][0] + v[1] * m_[1][0] + m_[2][0],
                   v[0] * m_[0][1] + v[1] * m_[1][1] + m_[2][1]);
#endif
}

/*
DblPOINT matrix3f::transform(const DblPOINT& v) const
{
	DblPOINT r;

	r.x = v.x * m_[0][0] + v.y * m_[1][0] + m_[2][0];
	r.y = v.x * m_[0][1] + v.y * m_[1][1] + m_[2][1];

	return r;
}
*/

// TRANSFORMATION MATRICES

matrix3f matrix3f::getIdentity()
{
  return matrix3f(1, 0, 0,
                   0, 1, 0,
                   0, 0, 1);
}

matrix3f matrix3f::getRotate(float angle)
{
  float sine = sin(gmRadians(angle));
  float cosine = cos(gmRadians(angle));
  
  return matrix3f( cosine, sine,   0,
                   -sine,   cosine, 0,
                    0,      0,      1);
}

matrix3f matrix3f::getScale(float x, float y)
{
  return matrix3f(x, 0, 0,
		   0, y, 0,
		   0, 0, 1);
}

matrix3f matrix3f::getTranslate(float x, float y)
{
  return matrix3f(1, 0, 0,
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

matrix3f matrix3f::getSkewX(float x)
{
  return

	matrix3f(
	1, tan(gmRadians(x)), 0,
	0, 1, 0,
	0, 0, 1);
}

matrix3f matrix3f::getSkewY(float y)
{
  return

	matrix3f(
	1, 0, 0,
	tan(gmRadians(y)), 1, 0,
	0, 0, 1);
}

Matrix3f::Matrix3f()
{
}

Matrix3f::Matrix3f(float m11, float m12, float m21, float m22, float dx, float dy) :
	m_matrix(m11, m12, 0, m21, m22, 0, dx, dy, 1)
{
}

Matrix3f::Matrix3f(float m11, float m12, float m13, float m21, float m22, float m23, float dx, float dy, float dz) :
	m_matrix(m11, m12, m13, m21, m22, m23, dx, dy, dz)
{
}

Matrix3f::Matrix3f(const matrix3f& mat) : m_matrix(mat)
{
}

double Matrix3f::Determinant() const
{
	return m_matrix.determinant();
}

bool Matrix3f::Equals(const Matrix3f & other) const
{
	return m_matrix == other.m_matrix;
}

//static __live_object_ptr2<__release<Matrix3f> > IdentityMatrix(new Matrix3f(matrix3f::getIdentity()));
static __release<Matrix3f> IdentityMatrix(new Matrix3f(matrix3f::getIdentity()));

__release<Matrix3f> Matrix3f::GetInverse() const
{
	return new Matrix3f(m_matrix.getInverse());
}

#if 0
///////////////////////////////////////
// Matrix

Matrix3f::Matrix3f()
{
	m_p = NULL;
}

Matrix3f::Matrix3f(Matrix3f *p)
{
	m_p = p;
	if (m_p) m_p->AddRef();
}

Matrix3f::Matrix3f(const Matrix3f & other)
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

Matrix3f::Matrix3f(float m11, float m12, float m21, float m22, float dx, float dy)
{
	m_p = new Matrix3f(m11, m12, m21, m22, dx, dy);
	m_p->AddRef();
}

Matrix3f::Matrix3f(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
{
	m_p = new Matrix3f(m11, m12, m13, m21, m22, m23, m31, m32, m33);
	m_p->AddRef();
}

Matrix3f::~Matrix3f()
{
	if (m_p)
	{
		m_p->Release();
	}
}
#endif

void Matrix3f::Get(float m[3][2]) const
{
	/*
	ASSERT(m_p);
	if (m_p == NULL) THROW(-1);
	*/

	m[0][0] = m_matrix[0][0];
	m[1][0] = m_matrix[1][0];
	m[0][1] = m_matrix[0][1];
	m[1][1] = m_matrix[1][1];
	m[2][0] = m_matrix[2][0];
	m[2][1] = m_matrix[2][1];
//	ASSERT(m_p->m_matrix[2][0] == 0);
//	ASSERT(m_p->m_matrix[2][1] == 0);
//	ASSERT(m_p->m_matrix[2][2] == 1);
}

void Matrix3f::Get(float m[9]) const
{
	std::memcpy(m, &m_matrix, 9*4);
}

PointF Matrix3f::Transform(PointI point) const
{
	/*
	ASSERT(m_p);
	if (m_p == NULL) THROW(-1);
	*/
	return m_matrix.transform(PointF(point.X, point.Y));
}

PointF Matrix3f::Transform(PointF point) const
{
	/*
	ASSERT(m_p);
	if (m_p == NULL) THROW(-1);
	*/
	return m_matrix.transform(*(const vector2f*)&point);
}

vector3f Matrix3f::Transform(const vector3f& v) const
{
	/*
	ASSERT(m_p);
	if (m_p == NULL) THROW(-1);
	*/
	return m_matrix.transform(v);
}

vector3f Matrix3f::operator * (const vector3f& v) const
{
	return m_matrix * v;
}

DrawExt vector3f operator * (const vector3f& v, const Matrix3f& m)
{
	return v * m.m_matrix;
}

PointD Matrix3f::Transform(const PointD& point) const
{
	ASSERT(this);
	/*
	ASSERT(m_p);
	if (m_p == NULL) THROW(-1);
	*/
	return m_matrix.transform(vector2d(point.X, point.Y));
}

#if 0
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

#endif

void Matrix3f::TransformPoints(PointF* dst, const PointF* src, int count) const
{
	const float* m = (const float*)&m_matrix;

	while (count--)
	{
		float x = src->X * m[0] + src->Y * m[3] + m[6];
		float y = src->X * m[1] + src->Y * m[4] + m[7];
		dst->X = x;
		dst->Y = y;

		dst++;
		src++;
	}

#if 0
	matrix3f& m = m_p->m_matrix;

	float mt[6];
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
		transform_2points((float*)dst, mt, (const float*)src);

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

#if 0

Matrix3f Matrix3f::GetMultiplied(const Matrix3f& other) const
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
	return new Matrix3f(other.m_p->m_matrix * m_p->m_matrix);
}
#endif

// static
__release<Matrix3f> Matrix3f::GetIdentity()
{
	return (Matrix3f*)IdentityMatrix.m_p;
}

// static
__release<Matrix3f> Matrix3f::GetTranslate(float dx, float dy)
{
	return new Matrix3f(matrix3f::getTranslate(dx, dy));
}

// static
__release<Matrix3f> Matrix3f::GetScale(float sx, float sy)
{
	return new Matrix3f(matrix3f::getScale(sx, sy));
}

// static
__release<Matrix3f> Matrix3f::GetRotate(float angle)
{
	return new Matrix3f(matrix3f::getRotate(angle));
}

// static
__release<Matrix3f> Matrix3f::GetSkewX(float angle)
{
	return new Matrix3f(matrix3f::getSkewX(angle));
}

// static
__release<Matrix3f> Matrix3f::GetSkewY(float angle)
{
	return new Matrix3f(matrix3f::getSkewY(angle));
}

#if 0
__release<Matrix3f> Matrix3f::GetInverse() const
{
	/*
	if (m_p == NULL)
		return Matrix3f();
		*/

	return new Matrix3f(m_matrix.getInverse());
}
#endif

void Matrix3f::Multiply(const Matrix3f* other, MatrixOrder order)
{
	ASSERT(this);
	ASSERT(&other);

	VERIFY(m_refcount <= 1);

	if (order == MatrixOrderPrepend)
		m_matrix = other->m_matrix * m_matrix;
	else
		m_matrix = m_matrix * other->m_matrix;
}

void Matrix3f::Multiply(const Matrix3f* other, MatrixOrder order, Matrix3f** pVal)
{
	ASSERT(this);
	ASSERT(&other);

	if (m_refcount > 1)
	{
		if (order == MatrixOrderPrepend)
			*pVal = new Matrix3f(other->m_matrix * m_matrix);
		else
			*pVal = new Matrix3f(m_matrix = m_matrix * other->m_matrix);

		(*pVal)->AddRef();
	}
	else
	{
		if (order == MatrixOrderPrepend)
			m_matrix = other->m_matrix * m_matrix;
		else
			m_matrix = m_matrix * other->m_matrix;
	}
}

void Matrix3f::Translate(float dx, float dy, MatrixOrder order)
{
	VERIFY(m_refcount <= 1);
	ASSERT(this);

	if (order == MatrixOrderPrepend)
		m_matrix = matrix3f::getTranslate(dx, dy) * m_matrix;
	else
		m_matrix = m_matrix * matrix3f::getTranslate(dx, dy);
}

void Matrix3f::Translate(float dx, float dy, MatrixOrder order, Matrix3f** pVal)
{
	ASSERT(this);

	if (m_refcount > 1)
	{
		if (order == MatrixOrderPrepend)
			*pVal = new Matrix3f(matrix3f::getTranslate(dx, dy) * m_matrix);
		else
			*pVal = new Matrix3f(m_matrix * matrix3f::getTranslate(dx, dy));

		(*pVal)->AddRef();
	}
	else
	{
		if (order == MatrixOrderPrepend)
			m_matrix = matrix3f::getTranslate(dx, dy) * m_matrix;
		else
			m_matrix = m_matrix * matrix3f::getTranslate(dx, dy);
	}
}

void Matrix3f::Scale(float sx, float sy, MatrixOrder order)
{
	/*
	if (m_p == NULL)
	{
		m_p = new Matrix3f;
		m_p->AddRef();
		m_p->m_matrix = matrix3f::getScale(sx, sy);
		return;
	}

	if (m_p->m_refcount > 1)
	{
		m_p->Release();
		m_p = new Matrix3f(m_p->m_matrix);
		m_p->AddRef();
	}
	*/

	VERIFY(m_refcount <= 1);
	ASSERT(this);

	if (order == MatrixOrderPrepend)
		m_matrix = matrix3f::getScale(sx, sy) * m_matrix;
	else
		m_matrix = m_matrix * matrix3f::getScale(sx, sy);
}

void Matrix3f::Rotate(float angle, MatrixOrder order)
{
	/*
	if (m_p == NULL)
	{
		m_p = new Matrix3f;
		m_p->AddRef();
		m_p->m_matrix = matrix3f::getRotate(angle);
		return;
	}

	if (m_p->m_refcount > 1)
	{
		m_p->Release();
		m_p = new Matrix3f(m_p->m_matrix);
		m_p->AddRef();
	}
*/

	VERIFY(m_refcount <= 1);
	ASSERT(this);

	if (order == MatrixOrderPrepend)
		m_matrix = matrix3f::getRotate(angle) * m_matrix;
	else
		m_matrix = m_matrix * matrix3f::getRotate(angle);
}

#if 0

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

void Matrix3f::Invert()
{
	if (m_p == NULL)
	{
		return;// *this;
	}

	if (m_p->m_refcount > 1)
	{
		Matrix3f* p = m_p;
		m_p = new Matrix3f(p->m_matrix.getInverse());
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

Matrix3f & Matrix3f::operator = (const Matrix3f & other)
{
	Matrix3f * old = m_p;

	m_p = other.m_p;

	if (m_p) m_p->AddRef();
	if (old) old->Release();

	return *this;
}
#endif


Matrix3f & Matrix3f::operator *= (const Matrix3f & other)
{
	/*
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
		m_p = new Matrix3f(*m_p);
		m_p->AddRef();
	}
	*/
	m_matrix *= other.m_matrix;

	return *this;
}

/*
Matrix& Matrix::operator = (const matrix3f& other)
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

__release<Matrix3f> Matrix3f::operator * (const Matrix3f & other) const
{
	return new Matrix3f(m_matrix * other.m_matrix);
}

#if 0

bool Matrix3f::ReferenceEquals(const Matrix3f & other) const
{
	return m_p == other.m_p;
}

bool Matrix3f::Equals(const Matrix3f & other) const
{
	if (m_p == other.m_p) return true;
	if (m_p == NULL) return false;
	if (other.m_p == NULL) return false;
	return m_p->Equals(*other.m_p);
}

bool Matrix3f::IsIdentity() const
{
	return Equals(IdentityMatrix);
}

bool Matrix3f::IsInvertible() const
{
	if (m_p == NULL) return false;
	return !m_p->m_matrix.isSingular();
}

/*
const float* Matrix::operator [] (int row) const
{
	VERIFY(m_p);
	VERIFY(row >= 0 && row < 3);
	return m_p->m_matrix[row];
}
*/

#endif

}	// LDraw
}
