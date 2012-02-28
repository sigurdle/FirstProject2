// matrix4x4f.cc - 4x4 element matrix class
//
// libgm++: Graphics Math Library
// Ferdi Scheepers and Stephen F May
// 15 June 1994

#include "StdAfx.h"

//#define LFCEXT DECLSPEC_DLLEXPORT

#include "LFC/LFC.h"

//#include "Draw2.h"
//#include "gl.h"
//#include "matrix4x4f.h"
//#include "gmMat4.h"

/*
#include "Vector3.h"
#include "Vector4.h"
*/

#include <malloc.h>

namespace System
{
namespace gm
{

#define A(row,col)  a[(col<<2)+row]
#define B(row,col)  b[(col<<2)+row]
#define P(row,col)  product[(col<<2)+row]

/**
 * Perform a full 4x4 matrix multiplication.
 *
 * \param a matrix.
 * \param b matrix.
 * \param product will receive the product of \p a and \p b.
 *
 * \warning Is assumed that \p product != \p b. \p product == \p a is allowed.
 *
 * \note KW: 4*16 = 64 multiplications
 * 
 * \author This \c matmul was contributed by Thomas Malik
 */
LFCEXT void matmul4( float *product, const float *a, const float *b )
{
   int i;
   for (i = 0; i < 4; i++) {
      const float ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
      P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
      P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
      P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
      P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
   }
}

#undef A
#undef B
#undef P

void LFCEXT FrustumMatrix(float m[16], double left, double right, double bottom, double top, double zNear, double zFar)
{
	float tx = - (right + left) / (right - left);
	float ty = - (top + bottom) / (top - bottom);
	float tz = - (zFar + zNear) / (zFar - zNear);

#define M(row,col)	m[col*4+row]

	M(0,0) = 2*zNear / (right-left); M(0,1) = 0;								M(0,2) =	tx;	M(0,3) =	0;
	M(1,0) = 0;								M(1,1) = 2*zNear / (top-bottom); M(1,2) = ty;	M(1,3) =	0;
	M(2,0) = 0;								M(2,1) =	0;								M(2,2) = tz;	M(2,3) =	-(2*zFar*zNear) / (zFar - zNear);
	M(3,0) = 0;								M(3,1) = 0;								M(3,2) = -1;	M(3,3) =	0;

#undef M
}

void LFCEXT FrustumMatrix(double m[16], double left, double right, double bottom, double top, double zNear, double zFar)
{
	double tx = - (right + left) / (right - left);
	double ty = - (top + bottom) / (top - bottom);
	double tz = - (zFar + zNear) / (zFar - zNear);

#define M(row,col)	m[col*4+row]

	M(0,0) = 2*zNear / (right-left); M(0,1) = 0;								M(0,2) =	tx;	M(0,3) =	0;
	M(1,0) = 0;								M(1,1) = 2*zNear / (top-bottom); M(1,2) = ty;	M(1,3) =	0;
	M(2,0) = 0;								M(2,1) =	0;								M(2,2) = tz;	M(2,3) =	-(2*zFar*zNear) / (zFar - zNear);
	M(3,0) = 0;								M(3,1) = 0;								M(3,2) = -1;	M(3,3) =	0;

#undef M

	/*
	m[0] = 2 / (right-left); m[1] = 0; m[2] =						tx;	m[3] =				0;
	m[4] = 0;		m[5] = 			2 / (top-bottom); m[6] = ty;	m[7] = 					0;
	m[8] = 0;		m[9] =				0;		m[10] = 				tz;		m[11] =				-(2*zFar*zNear) / (zFar - zNear);
	m[12] = 0;	m[13] = 					0;	m[14] = 					-1;	m[15] = 					0;
	*/
}

// private function: RCD
// - dot product of row i of matrix A and col j of matrix B

/*
inline float RCD(const matrix4x4f& A, const matrix4x4f& B, int i, int j)
{
  return A[0][i] * B[j][0] +
			A[1][i] * B[j][1] +
			A[2][i] * B[j][2] +
			A[3][i] * B[j][3];
}
*/

inline float RCD(const matrix4x4f& A, const matrix4x4f& B, int i, int j)
{
	return A[i][0] * B[0][j] + A[i][1] * B[1][j] + A[i][2] * B[2][j] + A[i][3] * B[3][j];
}

/*
inline float RCD(const matrix4x4f& A, const matrix4x4f& B, int i, int j)
{
  return A[i][0] * B[0][j] + A[i][1] * B[1][j] + A[i][2] * B[2][j] + A[i][3] * B[3][j];
}
*/

// private function: MINOR
// - MINOR of M[r][c]; r in {0,1,2,3}-{r0,r1,r2}; c in {0,1,2,3}-{c0,c1,c2}

inline float MINOR(const matrix4x4f& M,
                    int r0, int r1, int r2, int c0, int c1, int c2)
{
  return
	 M[r0][c0] * (M[r1][c1] * M[r2][c2] - M[r2][c1] * M[r1][c2]) -
	 M[r0][c1] * (M[r1][c0] * M[r2][c2] - M[r2][c0] * M[r1][c2]) +
	 M[r0][c2] * (M[r1][c0] * M[r2][c1] - M[r2][c0] * M[r1][c1]);
}

/*
inline float MINOR_transposed(const matrix4x4f& M,
                    int r0, int r1, int r2, int c0, int c1, int c2)
{
  return 
	M[c0][r0] * (M[c1][r1] * M[c2][r2] - M[c1][r2] * M[c2][r1]) -
	M[c1][r0] * (M[c0][r1] * M[c2][r2] - M[c0][r2] * M[c2][r1]) +
	M[c2][r0] * (M[c0][r1] * M[c1][r2] - M[c0][r2] * M[c1][r1]);
}
*/

// CONSTRUCTORS

matrix4x4f::matrix4x4f(const float* m)
{
	assign(	m[0], m[1], m[2], m[3],
				m[4], m[5], m[6], m[7],
				m[8], m[9], m[10], m[11],
				m[12], m[13], m[14], m[15]);
}

matrix4x4f::matrix4x4f(
	float a00, float a01, float a02, float a03,
	float a10, float a11, float a12, float a13,
	float a20, float a21, float a22, float a23,
	float a30, float a31, float a32, float a33)
{
	m_[0][0] = a00; m_[0][1] = a01; m_[0][2] = a02; m_[0][3] = a03;
	m_[1][0] = a10; m_[1][1] = a11; m_[1][2] = a12; m_[1][3] = a13;
	m_[2][0] = a20; m_[2][1] = a21; m_[2][2] = a22; m_[2][3] = a23;
	m_[3][0] = a30; m_[3][1] = a31; m_[3][2] = a32; m_[3][3] = a33;
/*
	assign(	a00, a01, a02, a03,
				a10, a11, a12, a13,
				a20, a21, a22, a23,
				a30, a31, a32, a33);
				*/
}

matrix4x4f::matrix4x4f(const matrix3f& transform)
{
	if (true)
	{
		m_[0][0] = transform[0][0];
		m_[0][1] = transform[0][1];
		m_[0][2] = transform[0][2];
		m_[0][3] = 0;

		m_[1][0] = transform[1][0];
		m_[1][1] = transform[1][1];
		m_[1][2] = transform[1][2];
		m_[1][3] = 0;

		m_[2][0] = transform[2][0];
		m_[2][1] = transform[2][1];
		m_[2][2] = transform[2][2];
		m_[2][3] = 0;

		m_[3][0] = 0;
		m_[3][1] = 0;
		m_[3][2] = 0;
		m_[3][3] = 1;
	}
	else
	{
		m_[0][0] = transform[0][0];
		m_[0][1] = transform[0][1];
		m_[0][2] = 0;//transform[0][2];
		m_[0][3] = 0;

		m_[1][0] = transform[1][0];
		m_[1][1] = transform[1][1];
		m_[1][2] = 0;//transform[1][2];
		m_[1][3] = 0;

		m_[2][0] = 0;
		m_[2][1] = 0;
		m_[2][2] = 1;
		m_[2][3] = 0;

		m_[3][0] = transform[2][0];
		m_[3][1] = transform[2][1];
		m_[3][2] = 0;//transform[2][2];
		m_[3][3] = 1;
	}
}

// ASSIGNMENT

matrix4x4f& matrix4x4f::assign(
	float a00, float a01, float a02, float a03,
	float a10, float a11, float a12, float a13,
	float a20, float a21, float a22, float a23,
	float a30, float a31, float a32, float a33)
{
	m_[0][0] = a00; m_[0][1] = a01; m_[0][2] = a02; m_[0][3] = a03;
	m_[1][0] = a10; m_[1][1] = a11; m_[1][2] = a12; m_[1][3] = a13;
	m_[2][0] = a20; m_[2][1] = a21; m_[2][2] = a22; m_[2][3] = a23;
	m_[3][0] = a30; m_[3][1] = a31; m_[3][2] = a32; m_[3][3] = a33;

	return *this;
}

/*
matrix4x4f& matrix4x4f::operator =(const matrix4x4f& M)
{
  assign(M[0][0], M[0][1], M[0][2], M[0][3],
	 M[1][0], M[1][1], M[1][2], M[1][3],
	 M[2][0], M[2][1], M[2][2], M[2][3],
	 M[3][0], M[3][1], M[3][2], M[3][3]);
  return *this;
}
*/

////////////////////////////////////////////////////////////////////////////
// OPERATORS

matrix4x4f& matrix4x4f::operator +=(const matrix4x4f& M)
{
  m_[0][0] += M[0][0]; m_[0][1] += M[0][1];
  m_[0][2] += M[0][2]; m_[0][3] += M[0][3];
  
  m_[1][0] += M[1][0]; m_[1][1] += M[1][1];
  m_[1][2] += M[1][2]; m_[1][3] += M[1][3];
  
  m_[2][0] += M[2][0]; m_[2][1] += M[2][1];
  m_[2][2] += M[2][2]; m_[2][3] += M[2][3];
  
  m_[3][0] += M[3][0]; m_[3][1] += M[3][1];
  m_[3][2] += M[3][2]; m_[3][3] += M[3][3];
  return *this;
}

matrix4x4f& matrix4x4f::operator -=(const matrix4x4f& M)
{
  m_[0][0] -= M[0][0]; m_[0][1] -= M[0][1];
  m_[0][2] -= M[0][2]; m_[0][3] -= M[0][3];
  
  m_[1][0] -= M[1][0]; m_[1][1] -= M[1][1];
  m_[1][2] -= M[1][2]; m_[1][3] -= M[1][3];
  
  m_[2][0] -= M[2][0]; m_[2][1] -= M[2][1];
  m_[2][2] -= M[2][2]; m_[2][3] -= M[2][3];
  
  m_[3][0] -= M[3][0]; m_[3][1] -= M[3][1];
  m_[3][2] -= M[3][2]; m_[3][3] -= M[3][3];
  return *this;
}

void matmul4( float *product, const float *a, const float *b );

/*
static void __gluMultMatricesf(const float a[16], const float b[16],
				float r[16])
{
    int i, j;

    for (i = 0; i < 4; i++) {
	for (j = 0; j < 4; j++) {
	    r[i*4+j] = 
		a[i*4+0]*b[0*4+j] +
		a[i*4+1]*b[1*4+j] +
		a[i*4+2]*b[2*4+j] +
		a[i*4+3]*b[3*4+j];
	}
    }
}
*/

matrix4x4f& matrix4x4f::operator *=(const matrix4x4f& M)
{
	/*
  assign(RCD(*this, M, 0, 0), RCD(*this, M, 0, 1), 
	 RCD(*this, M, 0, 2), RCD(*this, M, 0, 3),
	 RCD(*this, M, 1, 0), RCD(*this, M, 1, 1),
	 RCD(*this, M, 1, 2), RCD(*this, M, 1, 3),
	 RCD(*this, M, 2, 0), RCD(*this, M, 2, 1),
	 RCD(*this, M, 2, 2), RCD(*this, M, 2, 3),
	 RCD(*this, M, 3, 0), RCD(*this, M, 3, 1),
	 RCD(*this, M, 3, 2), RCD(*this, M, 3, 3));
*/
#if 1
	/*
	float a[16];
	memcpy(a, m_, 4*16);
	__gluMultMatricesf(a, (const float*)M.m_, (float*)m_);
	*/
	matmul4((float*)m_, (const float*)m_, (const float*)M.m_);

	/*
  assign(RCD(*this, M, 0, 0), RCD(*this, M, 0, 1), 
	 RCD(*this, M, 0, 2), RCD(*this, M, 0, 3),
	 RCD(*this, M, 1, 0), RCD(*this, M, 1, 1),
	 RCD(*this, M, 1, 2), RCD(*this, M, 1, 3),
	 RCD(*this, M, 2, 0), RCD(*this, M, 2, 1),
	 RCD(*this, M, 2, 2), RCD(*this, M, 2, 3),
	 RCD(*this, M, 3, 0), RCD(*this, M, 3, 1),
	 RCD(*this, M, 3, 2), RCD(*this, M, 3, 3));
  *this = getTransposed();
  */
#endif
  return *this;
}

matrix4x4f& matrix4x4f::operator *=(float d)
{
  m_[0][0] *= d; m_[0][1] *= d; m_[0][2] *= d; m_[0][3] *= d;
  m_[1][0] *= d; m_[1][1] *= d; m_[1][2] *= d; m_[1][3] *= d;
  m_[2][0] *= d; m_[2][1] *= d; m_[2][2] *= d; m_[2][3] *= d;
  m_[3][0] *= d; m_[3][1] *= d; m_[3][2] *= d; m_[3][3] *= d;
  return *this;
}

matrix4x4f& matrix4x4f::operator /=(float d)
{
  float di = 1 / d;
  m_[0][0] *= di; m_[0][1] *= di; m_[0][2] *= di; m_[0][3] *= di;
  m_[1][0] *= di; m_[1][1] *= di; m_[1][2] *= di; m_[1][3] *= di;
  m_[2][0] *= di; m_[2][1] *= di; m_[2][2] *= di; m_[2][3] *= di;
  m_[3][0] *= di; m_[3][1] *= di; m_[3][2] *= di; m_[3][3] *= di;
  return *this;
}

matrix4x4f matrix4x4f::operator +(const matrix4x4f& M) const
{
  return matrix4x4f(m_[0][0] + M[0][0], m_[0][1] + M[0][1],
		   m_[0][2] + M[0][2], m_[0][3] + M[0][3],
		   m_[1][0] + M[1][0], m_[1][1] + M[1][1],
		   m_[1][2] + M[1][2], m_[1][3] + M[1][3],
		   m_[2][0] + M[2][0], m_[2][1] + M[2][1],
		   m_[2][2] + M[2][2], m_[2][3] + M[2][3],
		   m_[3][0] + M[3][0], m_[3][1] + M[3][1],
		   m_[3][2] + M[3][2], m_[3][3] + M[3][3]);
}

matrix4x4f matrix4x4f::operator -(const matrix4x4f& M) const
{
  return matrix4x4f(m_[0][0] - M[0][0], m_[0][1] - M[0][1],
		   m_[0][2] - M[0][2], m_[0][3] - M[0][3],
		   m_[1][0] - M[1][0], m_[1][1] - M[1][1],
		   m_[1][2] - M[1][2], m_[1][3] - M[1][3],
		   m_[2][0] - M[2][0], m_[2][1] - M[2][1],
		   m_[2][2] - M[2][2], m_[2][3] - M[2][3],
		   m_[3][0] - M[3][0], m_[3][1] - M[3][1],
		   m_[3][2] - M[3][2], m_[3][3] - M[3][3]);
}

matrix4x4f matrix4x4f::operator -() const
{
  return matrix4x4f(-m_[0][0], -m_[0][1], -m_[0][2], -m_[0][3],
		   -m_[1][0], -m_[1][1], -m_[1][2], -m_[1][3],
		   -m_[2][0], -m_[2][1], -m_[2][2], -m_[2][3],
		   -m_[3][0], -m_[3][1], -m_[3][2], -m_[3][3]);
}

/*
matrix4x4f matrix4x4f::operator *(const matrix4x4f& M) const
{
  return matrix4x4f(
			RCD(*this, M, 0, 0), RCD(*this, M, 0, 1), RCD(*this, M, 0, 2), RCD(*this, M, 0, 3),
		   RCD(*this, M, 1, 0), RCD(*this, M, 1, 1), RCD(*this, M, 1, 2), RCD(*this, M, 1, 3),
		   RCD(*this, M, 2, 0), RCD(*this, M, 2, 1), RCD(*this, M, 2, 2), RCD(*this, M, 2, 3),
		   RCD(*this, M, 3, 0), RCD(*this, M, 3, 1), RCD(*this, M, 3, 2), RCD(*this, M, 3, 3));
}
*/

matrix4x4f matrix4x4f::operator *(const matrix4x4f& M) const
{
	/*
  return matrix4x4f(RCD(*this, M, 0, 0), RCD(*this, M, 0, 1), 
		   RCD(*this, M, 0, 2), RCD(*this, M, 0, 3),
		   RCD(*this, M, 1, 0), RCD(*this, M, 1, 1),
		   RCD(*this, M, 1, 2), RCD(*this, M, 1, 3),
		   RCD(*this, M, 2, 0), RCD(*this, M, 2, 1),
		   RCD(*this, M, 2, 2), RCD(*this, M, 2, 3),
		   RCD(*this, M, 3, 0), RCD(*this, M, 3, 1),
		   RCD(*this, M, 3, 2), RCD(*this, M, 3, 3));
*/

#if 1
	matrix4x4f r;
//	__gluMultMatricesf((const float*)m_, (const float*)M.m_, (float*)r.m_);
	matmul4((float*)r.m_, (const float*)m_, (const float*)M.m_);

	return r;
#endif
	/*
  return matrix4x4f(
			RCD(*this, M, 0, 0), RCD(*this, M, 0, 1), RCD(*this, M, 0, 2), RCD(*this, M, 0, 3),
		   RCD(*this, M, 1, 0), RCD(*this, M, 1, 1), RCD(*this, M, 1, 2), RCD(*this, M, 1, 3),
		   RCD(*this, M, 2, 0), RCD(*this, M, 2, 1), RCD(*this, M, 2, 2), RCD(*this, M, 2, 3),
		   RCD(*this, M, 3, 0), RCD(*this, M, 3, 1), RCD(*this, M, 3, 2), RCD(*this, M, 3, 3)).getTransposed();
			*/
}

matrix4x4f matrix4x4f::operator *(float d) const
{
  return matrix4x4f(m_[0][0] * d, m_[0][1] * d, m_[0][2] * d, m_[0][3] * d,
		   m_[1][0] * d, m_[1][1] * d, m_[1][2] * d, m_[1][3] * d,
		   m_[2][0] * d, m_[2][1] * d, m_[2][2] * d, m_[2][3] * d,
		   m_[3][0] * d, m_[3][1] * d, m_[3][2] * d, m_[3][3] * d);
}

matrix4x4f matrix4x4f::operator /(float d) const
{
  ASSERT(!gmIsZero(d));
  float di = 1 / d;
  return matrix4x4f(m_[0][0] * di, m_[0][1] * di, m_[0][2] * di, m_[0][3] * di,
		   m_[1][0] * di, m_[1][1] * di, m_[1][2] * di, m_[1][3] * di,
		   m_[2][0] * di, m_[2][1] * di, m_[2][2] * di, m_[2][3] * di,
		   m_[3][0] * di, m_[3][1] * di, m_[3][2] * di, m_[3][3] * di);
}

matrix4x4f operator *(float d, const matrix4x4f& M)
{
  return matrix4x4f(M[0][0] * d, M[0][1] * d, M[0][2] * d, M[0][3] * d,
		   M[1][0] * d, M[1][1] * d, M[1][2] * d, M[1][3] * d,
		   M[2][0] * d, M[2][1] * d, M[2][2] * d, M[2][3] * d,
		   M[3][0] * d, M[3][1] * d, M[3][2] * d, M[3][3] * d);
}

bool matrix4x4f::operator ==(const matrix4x4f& M) const
{
  return (gmFuzEQ(m_[0][0], M[0][0]) && gmFuzEQ(m_[0][1], M[0][1]) &&
	  gmFuzEQ(m_[0][2], M[0][2]) && gmFuzEQ(m_[0][3], M[0][3]) &&
	 
	  gmFuzEQ(m_[1][0], M[1][0]) && gmFuzEQ(m_[1][1], M[1][1]) &&
	  gmFuzEQ(m_[1][2], M[1][2]) && gmFuzEQ(m_[1][3], M[1][3]) &&

 	  gmFuzEQ(m_[2][0], M[2][0]) && gmFuzEQ(m_[2][1], M[2][1]) &&
	  gmFuzEQ(m_[2][2], M[2][2]) && gmFuzEQ(m_[2][3], M[2][3]) &&

	  gmFuzEQ(m_[3][0], M[3][0]) && gmFuzEQ(m_[3][1], M[3][1]) &&
	  gmFuzEQ(m_[3][2], M[3][2]) && gmFuzEQ(m_[3][3], M[3][3]));
}

bool matrix4x4f::operator !=(const matrix4x4f& M) const
{
  return (!(*this == M));
}

//#define gm_FLT_EPSILON 1.192092896e–07F

//#define gm_FLT_EPSILON 1.192092896e-07F
#define gm_FLT_EPSILON 0.1

inline bool gmFuzEQ2(float f, float g)
{
  return (f <= g) ? (f >= g - gm_FLT_EPSILON) : (f <= g + gm_FLT_EPSILON);
}

bool matrix4x4f::FuzzyEquals(const matrix4x4f& M) const
{
	if (!gmFuzEQ2(m_[0][0], M[0][0])) return false;
	if (!gmFuzEQ2(m_[0][1], M[0][1])) return false;
	if (!gmFuzEQ2(m_[0][2], M[0][2])) return false;
	if (!gmFuzEQ2(m_[0][3], M[0][3])) return false;

	if (!gmFuzEQ2(m_[1][0], M[1][0])) return false;
	if (!gmFuzEQ2(m_[1][1], M[1][1])) return false;
	if (!gmFuzEQ2(m_[1][2], M[1][2])) return false;
	if (!gmFuzEQ2(m_[1][3], M[1][3])) return false;

	if (!gmFuzEQ2(m_[2][0], M[2][0])) return false;
	if (!gmFuzEQ2(m_[2][1], M[2][1])) return false;
	if (!gmFuzEQ2(m_[2][2], M[2][2])) return false;
	if (!gmFuzEQ2(m_[2][3], M[2][3])) return false;

	if (!gmFuzEQ2(m_[3][0], M[3][0])) return false;
	if (!gmFuzEQ2(m_[3][1], M[3][1])) return false;
	if (!gmFuzEQ2(m_[3][2], M[3][2])) return false;
	if (!gmFuzEQ2(m_[3][3], M[3][3])) return false;

	return false;

  return (gmFuzEQ2(m_[0][0], M[0][0]) && gmFuzEQ2(m_[0][1], M[0][1]) &&
	  gmFuzEQ2(m_[0][2], M[0][2]) && gmFuzEQ2(m_[0][3], M[0][3]) &&
	 
	  gmFuzEQ2(m_[1][0], M[1][0]) && gmFuzEQ2(m_[1][1], M[1][1]) &&
	  gmFuzEQ2(m_[1][2], M[1][2]) && gmFuzEQ2(m_[1][3], M[1][3]) &&

 	  gmFuzEQ2(m_[2][0], M[2][0]) && gmFuzEQ2(m_[2][1], M[2][1]) &&
	  gmFuzEQ2(m_[2][2], M[2][2]) && gmFuzEQ2(m_[2][3], M[2][3]) &&

	  gmFuzEQ2(m_[3][0], M[3][0]) && gmFuzEQ2(m_[3][1], M[3][1]) &&
	  gmFuzEQ2(m_[3][2], M[3][2]) && gmFuzEQ2(m_[3][3], M[3][3]));
}

vector4f matrix4x4f::operator *(const vector4f& v) const
{
  return vector4f(
    m_[0][0] * v[0] + m_[1][0] * v[1] + m_[2][0] * v[2] + m_[3][0] * v[3],
    m_[0][1] * v[0] + m_[1][1] * v[1] + m_[2][1] * v[2] + m_[3][1] * v[3],
    m_[0][2] * v[0] + m_[1][2] * v[1] + m_[2][2] * v[2] + m_[3][2] * v[3],
    m_[0][3] * v[0] + m_[1][3] * v[1] + m_[2][3] * v[2] + m_[3][3] * v[3]);
}

#if 0//WIN32

void transform_point_unaligned_sse3(float outvec[4], const float invec[4], const float m[16])
{
	__asm
	{
		push		ebx
		push		ecx

		MOV		eax,[invec]
		MOV		ebx,[outvec]
		MOV		ecx,[m]
		MOVUPS	xmm1,[eax]

		MOVUPS	xmm5,[ecx]
		MULPS		xmm5,xmm1

		MOVUPS	xmm4,[ecx+16]
		MULPS		xmm4,xmm1

		MOVUPS	xmm3,[ecx+32]
		MULPS		xmm3,xmm1

		MOVUPS	xmm2,[ecx+48]
		MULPS		xmm2,xmm1

		HADDPS	(MOD_11(5,4))
		HADDPS	(MOD_11(3,2))

		HADDPS	(MOD_11(5,3))

		MOVUPS	[ebx],xmm5

		pop		ecx
		pop		ebx
	}
}

void transform_point_aligned_matrix_sse3(float outvec[4], const float invec[4], const float m[16])
{
	__asm
	{
		push		ebx
		push		ecx

		MOV		eax,[invec]
		MOV		ebx,[outvec]
		MOV		ecx,[m]
		MOVUPS	xmm1,[eax]

		MOVAPS	xmm5,[ecx]
		MULPS		xmm5,xmm1

		MOVAPS	xmm4,[ecx+16]
		MULPS		xmm4,xmm1

		MOVAPS	xmm3,[ecx+32]
		MULPS		xmm3,xmm1

		MOVAPS	xmm2,[ecx+48]
		MULPS		xmm2,xmm1

		HADDPS	(MOD_11(5,4))
		HADDPS	(MOD_11(3,2))

		HADDPS	(MOD_11(5,3))

		MOVUPS	[ebx],xmm5

		pop		ecx
		pop		ebx
	}
}

#endif

LFCEXT void transform_point_unoptimized(float outvec[4], const float invec[4], const float m[16])
{
#define M(row,col)  m[col*4+row]

	float invec2[4];
	invec2[0] = invec[0];
	invec2[1] = invec[1];
	invec2[2] = invec[2];
	invec2[3] = invec[3];

   outvec[0] = M(0,0) * invec2[0] + M(0,1) * invec2[1] + M(0,2) * invec2[2] + M(0,3) * invec2[3];
   outvec[1] = M(1,0) * invec2[0] + M(1,1) * invec2[1] + M(1,2) * invec2[2] + M(1,3) * invec2[3];
   outvec[2] = M(2,0) * invec2[0] + M(2,1) * invec2[1] + M(2,2) * invec2[2] + M(2,3) * invec2[3];
   outvec[3] = M(3,0) * invec2[0] + M(3,1) * invec2[1] + M(3,2) * invec2[2] + M(3,3) * invec2[3];
#undef M
}

#if WIN32
LFCEXT transform_point_t transform_point_unaligned = transform_point_unoptimized;
//LFCEXT transform_point_t transform_point_unaligned = transform_point_unaligned_sse3;

#endif

#if 0//WIN32
__declspec(naked)
#endif

LFCEXT vector4f operator * (const vector4f& v, const matrix4x4f& M)
{
  return vector4f(
    v[0] * M[0][0] + v[1] * M[1][0] + v[2] * M[2][0] + v[3] * M[3][0],
    v[0] * M[0][1] + v[1] * M[1][1] + v[2] * M[2][1] + v[3] * M[3][1],
    v[0] * M[0][2] + v[1] * M[1][2] + v[2] * M[2][2] + v[3] * M[3][2],
    v[0] * M[0][3] + v[1] * M[1][3] + v[2] * M[2][3] + v[3] * M[3][3]);

#if 0
#if WIN32

	/*
	vector4f out;
	transform_point_unaligned(out, v, M);
	return out;
	*/

	__asm
	{
		jmp [transform_point_unaligned]
	}
#else
	// TODO
	ASSERT(0);
#endif
#endif
}

// OPERATIONS

matrix4x4f matrix4x4f::getTranspose() const
{
  return matrix4x4f(m_[0][0], m_[1][0], m_[2][0], m_[3][0],
		   m_[0][1], m_[1][1], m_[2][1], m_[3][1],
		   m_[0][2], m_[1][2], m_[2][2], m_[3][2],
		   m_[0][3], m_[1][3], m_[2][3], m_[3][3]);
}

matrix4x4f matrix4x4f::getInverse() const
{
	ASSERT(!isSingular());

	const matrix4x4f& t = *this;
//	matrix4x4f t = getTransposed();

	float determinant = t.getDeterminant();
	if (gmIsZero(determinant))
		THROW(-1);

	return (t.getAdjoint() * gmInv(determinant));
//	return (t.getAdjoint() * gmInv(determinant)).getTransposed();
}

matrix4x4f matrix4x4f::getAdjoint() const
{
  matrix4x4f A;
  
  A[0][0] =  MINOR(*this, 1, 2, 3, 1, 2, 3);
  A[0][1] = -MINOR(*this, 0, 2, 3, 1, 2, 3);
  A[0][2] =  MINOR(*this, 0, 1, 3, 1, 2, 3);
  A[0][3] = -MINOR(*this, 0, 1, 2, 1, 2, 3);
  A[1][0] = -MINOR(*this, 1, 2, 3, 0, 2, 3);
  A[1][1] =  MINOR(*this, 0, 2, 3, 0, 2, 3);
  A[1][2] = -MINOR(*this, 0, 1, 3, 0, 2, 3);
  A[1][3] =  MINOR(*this, 0, 1, 2, 0, 2, 3);
  A[2][0] =  MINOR(*this, 1, 2, 3, 0, 1, 3);
  A[2][1] = -MINOR(*this, 0, 2, 3, 0, 1, 3);
  A[2][2] =  MINOR(*this, 0, 1, 3, 0, 1, 3);
  A[2][3] = -MINOR(*this, 0, 1, 2, 0, 1, 3);
  A[3][0] = -MINOR(*this, 1, 2, 3, 0, 1, 2);
  A[3][1] =  MINOR(*this, 0, 2, 3, 0, 1, 2);
  A[3][2] = -MINOR(*this, 0, 1, 3, 0, 1, 2);
  A[3][3] =  MINOR(*this, 0, 1, 2, 0, 1, 2);

  return A;

	/*
  matrix4x4f A;
  
  const matrix4x4f& _this = *this;
  //_this = _this.transpose();

  A[0][0] =  MINOR_transposed(_this, 1, 2, 3, 1, 2, 3);
  A[1][0] = -MINOR_transposed(_this, 0, 2, 3, 1, 2, 3);
  A[2][0] =  MINOR_transposed(_this, 0, 1, 3, 1, 2, 3);
  A[3][0] = -MINOR_transposed(_this, 0, 1, 2, 1, 2, 3);
  A[0][1] = -MINOR_transposed(_this, 1, 2, 3, 0, 2, 3);
  A[1][1] =  MINOR_transposed(_this, 0, 2, 3, 0, 2, 3);
  A[2][1] = -MINOR_transposed(_this, 0, 1, 3, 0, 2, 3);
  A[3][1] =  MINOR_transposed(_this, 0, 1, 2, 0, 2, 3);
  A[0][2] =  MINOR_transposed(_this, 1, 2, 3, 0, 1, 3);
  A[1][2] = -MINOR_transposed(_this, 0, 2, 3, 0, 1, 3);
  A[2][2] =  MINOR_transposed(_this, 0, 1, 3, 0, 1, 3);
  A[3][2] = -MINOR_transposed(_this, 0, 1, 2, 0, 1, 3);
  A[0][3] = -MINOR_transposed(_this, 1, 2, 3, 0, 1, 2);
  A[1][3] =  MINOR_transposed(_this, 0, 2, 3, 0, 1, 2);
  A[2][3] = -MINOR_transposed(_this, 0, 1, 3, 0, 1, 2);
  A[3][3] =  MINOR_transposed(_this, 0, 1, 2, 0, 1, 2);

  return A;
  */
}

/*
float matrix4x4f::determinant() const
{
  return m_[0][0] * MINOR(*this, 1, 2, 3, 1, 2, 3) -
	 m_[0][1] * MINOR(*this, 1, 2, 3, 0, 2, 3) +
	 m_[0][2] * MINOR(*this, 1, 2, 3, 0, 1, 3) -
	 m_[0][3] * MINOR(*this, 1, 2, 3, 0, 1, 2);
}
*/

float matrix4x4f::getDeterminant() const
{
  return m_[0][0] * MINOR(*this, 1, 2, 3, 1, 2, 3) -
	 m_[0][1] * MINOR(*this, 1, 2, 3, 0, 2, 3) +
	 m_[0][2] * MINOR(*this, 1, 2, 3, 0, 1, 3) -
	 m_[0][3] * MINOR(*this, 1, 2, 3, 0, 1, 2);

	/*
	const matrix4x4f& _this = *this;

	return (
		_this.m_[0][0] * MINOR_transposed(_this, 1, 2, 3, 1, 2, 3) -
		_this.m_[1][0] * MINOR_transposed(_this, 1, 2, 3, 0, 2, 3) +
		_this.m_[2][0] * MINOR_transposed(_this, 1, 2, 3, 0, 1, 3) -
		_this.m_[3][0] * MINOR_transposed(_this, 1, 2, 3, 0, 1, 2));
		*/
}

bool matrix4x4f::isSingular() const
{
  return gmIsZero(getDeterminant());
}

/*
gmVector3t<float> matrix4x4f::transform(const gmVector3t<float>& v) const
{
  return gmVector3t<float>(
    v[0] * m_[0][0] + v[1] * m_[1][0] + v[2] * m_[2][0] + m_[3][0],
    v[0] * m_[0][1] + v[1] * m_[1][1] + v[2] * m_[2][1] + m_[3][1],
    v[0] * m_[0][2] + v[1] * m_[1][2] + v[2] * m_[2][2] + m_[3][2]);
}
*/

vector3f matrix4x4f::transform(const vector3f& v) const
{
  return vector3f(
    v[0] * m_[0][0] + v[1] * m_[1][0] + v[2] * m_[2][0] + m_[3][0],
    v[0] * m_[0][1] + v[1] * m_[1][1] + v[2] * m_[2][1] + m_[3][1],
    v[0] * m_[0][2] + v[1] * m_[1][2] + v[2] * m_[2][2] + m_[3][2]);

	/*
  return vector3f(
    v[0] * m_[0][0] + v[1] * m_[0][1] + v[2] * m_[0][2] + m_[0][3],
    v[0] * m_[1][0] + v[1] * m_[1][1] + v[2] * m_[1][2] + m_[1][3],
    v[0] * m_[2][0] + v[1] * m_[2][1] + v[2] * m_[2][2] + m_[2][3]);
	 */
}

#if 0
vector4f matrix4x4f::transform(const vector4f& v) const
{
  return vector4f(
    v[0] * m_[0][0] + v[1] * m_[1][0] + v[2] * m_[2][0] + m_[3][0],
    v[0] * m_[0][1] + v[1] * m_[1][1] + v[2] * m_[2][1] + m_[3][1],
    v[0] * m_[0][2] + v[1] * m_[1][2] + v[2] * m_[2][2] + m_[3][2],
	 v[0] * m_[0][3] + v[1] * m_[1][3] + v[2] * m_[2][3] + m_[3][3]);

	/*
  return vector4f(
    v[0] * m_[0][0] + v[1] * m_[0][1] + v[2] * m_[0][2] + v[3] * m_[0][3],
    v[0] * m_[1][0] + v[1] * m_[1][1] + v[2] * m_[1][2] + v[3] * m_[1][3],
    v[0] * m_[2][0] + v[1] * m_[2][1] + v[2] * m_[2][2] + v[3] * m_[2][3],
	 v[0] * m_[3][0] + v[1] * m_[3][1] + v[2] * m_[3][2] + v[3] * m_[3][3]);
	 */
}
#endif

////////////////////////////////////////////////////////////////////////////
// TRANSFORMATION MATRICES

matrix4x4f matrix4x4f::getIdentity()
{
	return matrix4x4f(
			1, 0, 0, 0,
		   0, 1, 0, 0,
		   0, 0, 1, 0,
		   0, 0, 0, 1);
}

matrix4x4f matrix4x4f::getRotate(float angle, const vector3f& axis)
{
	matrix4x4f m_;
	float length = axis.length();
	float a = axis[0] / length;
	float b = axis[1] / length;
	float c = axis[2] / length;
	float aa = a * a;
	float bb = b * b;
	float cc = c * c;
	float sine = sin(gmRadians(angle));
	float cosine = cos(gmRadians(angle));
	float omcos = 1 - cosine;
	
	m_[0][0] = aa + (1 - aa) * cosine;
	m_[1][1] = bb + (1 - bb) * cosine;
	m_[2][2] = cc + (1 - cc) * cosine;
	m_[0][1] = a * b * omcos + c * sine;
	m_[0][2] = a * c * omcos - b * sine;
	m_[1][0] = a * b * omcos - c * sine;
	m_[1][2] = b * c * omcos + a * sine;
	m_[2][0] = a * c * omcos + b * sine;
	m_[2][1] = b * c * omcos - a * sine;
//	m_[0][3] = m_[3][1] = m_[3][2] = m_[0][3] = m_[1][3] = m_[2][3] = 0;
	m_[0][3] = m_[1][3] = m_[2][3] = m_[3][0] = m_[3][1] = m_[3][2] = 0;
	m_[3][3] = 1;

	/*
	m_[0][0] = aa + (1 - aa) * cosine;
	m_[1][1] = bb + (1 - bb) * cosine;
	m_[2][2] = cc + (1 - cc) * cosine;
	m_[1][0] = a * b * omcos + c * sine;
	m_[2][0] = a * c * omcos - b * sine;
	m_[0][1] = a * b * omcos - c * sine;
	m_[2][1] = b * c * omcos + a * sine;
	m_[0][2] = a * c * omcos + b * sine;
	m_[1][2] = b * c * omcos - a * sine;
	m_[3][0] = m_[3][1] = m_[3][2] = m_[0][3] = m_[1][3] = m_[2][3] = 0;
	m_[3][3] = 1;
*/

  return m_;
}

matrix4x4f matrix4x4f::getRotate(float angle, float x, float y, float z)
{
	return getRotate(angle, vector3f(x, y, z));
}

matrix4x4f matrix4x4f::getScale(float x, float y, float z)
{
  return matrix4x4f(
			x, 0, 0, 0,
		   0, y, 0, 0,
		   0, 0, z, 0,
		   0, 0, 0, 1);

  /*
  return matrix4x4f(x, 0, 0, 0,
		   0, y, 0, 0,
		   0, 0, z, 0,
		   0, 0, 0, 1).transpose();
			*/
}

matrix4x4f matrix4x4f::getScale(const vector3f& xyz)
{
  return getScale(xyz[0], xyz[1], xyz[2]);
}

matrix4x4f matrix4x4f::getTranslate(float x, float y, float z)
{
  return matrix4x4f(
			1, 0, 0, 0,
		   0, 1, 0, 0,
		   0, 0, 1, 0,
		   x, y, z, 1);

  /*
  return matrix4x4f(
			1, 0, 0, x,
		   0, 1, 0, y,
		   0, 0, 1, z,
		   0, 0, 0, 1);
			*/
}

matrix4x4f matrix4x4f::getTranslate(const vector3f& xyz)
{
  return getTranslate(xyz[0], xyz[1], xyz[2]);
}

// static
matrix4x4f matrix4x4f::getPerspective(double fovy, double aspect, double zNear, double zFar)
{
   double xmin, xmax, ymin, ymax;

   ymax = zNear * tan( fovy * M_PI / 360.0 );
   ymin = -ymax;

   xmin = ymin * aspect;
   xmax = ymax * aspect;

	matrix4x4f m;
   FrustumMatrix((float*)m, xmin, xmax, ymin, ymax, zNear, zFar );
	return m;
}

// static
matrix4x4f matrix4x4f::getOrtho(double left, double right, double bottom, double top, double zNear, double zFar)
{
	double tx = - (right + left) / (right - left);
	double ty = - (top + bottom) / (top - bottom);
	double tz = - (zFar + zNear) / (zFar - zNear);

	matrix4x4f m;

#define M(row, col)	m[col][row]

	M(0,0) = 2 / (right-left);		M(0,1) = 0;						M(0,2) = 0;							M(0,3) = tx;
	M(1,0) = 0;							M(1,1) = 2 / (top-bottom); M(1,2) = 0;							M(1,3) = ty;
	M(2,0) = 0;							M(2,1) = 0;						M(2,2) = -2 / (zFar - zNear); M(2,3) = tz;
	M(3,0) = 0;							M(3,1) = 0;						M(3,2) = 0;							M(3,3) = 1;

#undef M

	return m;
}

// static
matrix4x4f matrix4x4f::getOrtho2D(double left, double right, double bottom, double top)
{
	return getOrtho(left, right, bottom, top, -1, 1);
}

////////////////////////////////////////////////////////////////////////////
// CUBIC BASIS MATRICES

matrix4x4f matrix4x4f::bezierBasis()
{
  return matrix4x4f(-1,  3, -3,  1,
	 	    3, -6,  3,  0,
		   -3,  3,  0,  0,
		    1,  0,  0,  0);
}

matrix4x4f matrix4x4f::bsplineBasis()
{  
  return matrix4x4f(-1,  3, -3,  1,
		    3, -6,  3,  0,
		   -3,  0,  3,  0,
		    1,  4,  1,  0) / 6;
}

matrix4x4f matrix4x4f::catmullromBasis()
{
  return matrix4x4f(-1,  3, -3,  1,
		    2, -5,  4, -1,
		   -1,  0,  1,  0,
		    0,  2,  0,  0) / 2;
}

matrix4x4f matrix4x4f::hermiteBasis()
{
  return matrix4x4f( 2,  1, -2,  1,
		   -3, -2,  3, -1,
		    0,  1,  0,  0,
		    1,  0,  0,  0);
}

matrix4x4f matrix4x4f::tensedBSplineBasis(float tension)
{
  matrix4x4f m;
  double sixth = 1.0 / 6.0;

  m[0][0] = sixth * (-tension);
  m[0][1] = sixth * (12.0 - 9.0 * tension);
  m[0][2] = sixth * (9.0 * tension - 12.0);
  m[0][3] = sixth * tension;

  m[1][0] = sixth * 3.0 * tension;
  m[1][1] = sixth * (12.0 * tension - 18.0);
  m[1][2] = sixth * (18.0 - 15.0 * tension);
  m[1][3] = 0.0;

  m[2][0] = sixth * -3.0 * tension;
  m[2][1] = 0.0;
  m[2][2] = sixth * 3.0 * tension;
  m[2][3] = 0.0;

  m[3][0] = sixth * tension;
  m[3][1] = sixth * (6.0 - 2.0 * tension);
  m[3][2] = sixth * tension;
  m[3][3] = 0.0;

  return m;
}

matrix4x4f matrix4x4f::cardinalBasis(float tension)
{
  matrix4x4f m;
  
  m[0][0] = -tension;
  m[0][1] = 2.0 - tension;
  m[0][2] = tension - 2.0;
  m[0][3] = tension;

  m[1][0] = 2.0 * tension;
  m[1][1] = tension - 3.0;
  m[1][2] = 3 - 2.0 * tension;
  m[1][3] = -tension;

  m[2][0] = -tension;
  m[2][1] = 0.0;
  m[2][2] = tension;
  m[2][3] = 0.0;

  m[3][0] = 0.0;
  m[3][1] = 1.0;
  m[3][2] = 0.0;
  m[3][3] = 0.0;
  
  return m;
}

matrix4x4f matrix4x4f::tauBasis(float bias, float tension)
{
  matrix4x4f m;
  
  m[0][0] = tension * (bias - 1.0);
  m[0][1] = 2.0 - tension * bias;
  m[0][2] = tension * (1.0 - bias) - 2.0;
  m[0][3] = tension * bias;

  m[1][0] = tension * 2.0 * (1.0 - bias);
  m[1][1] = tension * (3.0 * bias - 1.0) - 3.0;
  m[1][2] = 3.0 - tension;
  m[1][3] = -tension * bias;

  m[2][0] = tension * (bias - 1.0);
  m[2][1] = tension * (1.0 - 2.0 * bias);
  m[2][2] = tension * bias;
  m[2][3] = 0.0;

  m[3][0] = 0.0;
  m[3][1] = 1.0;
  m[3][2] = 0.0;
  m[3][3] = 0.0;
  
  return m;
}

matrix4x4f matrix4x4f::betaSplineBasis(float bias, float tension)
{
  matrix4x4f m;
  float bias2, bias3, d;

  bias2 = bias * bias;
  bias3 = bias * bias2;
  d = 1.0 / (tension + 2.0 * bias3 + 4.0 * bias2 + 4.0 * bias + 2.0);

  m[0][0] = -d * 2.0 * bias3;
  m[0][1] = d * 2.0 * (tension + bias3 + bias2 + bias);
  m[0][2] = -d * 2.0 * (tension + bias2 + bias + 1.0);
  m[0][3] = d * 2.0;

  m[1][0] = d * 6.0 * bias3;
  m[1][1] = -d * 3.0 * (tension + 2.0 * bias3 + 2.0 * bias2);
  m[1][2] = d * 3.0 * (tension + 2 * bias2);
  m[1][3] = 0.0;
  
  m[2][0] = -d * 6.0 * bias3;
  m[2][1] = d * 6.0 * (bias3 - bias);
  m[2][2] = d * 6.0 * bias;
  m[2][3] = 0.0;

  m[3][0] = d * 2.0 * bias3;
  m[3][1] = d * (tension + 4 * (bias2 + bias));
  m[3][2] = d * 2.0;
  m[3][3] = 0.0;

  return m;
}

/////////////////////////////////////////////
// Matrix4

Matrix4::Matrix4()// : m_matrix(matrix4x4f::getIdentity())
{
}

Matrix4::Matrix4(const matrix4x4f& m) : m_matrix(m)
{
}

Matrix4::Matrix4(const float* m) : m_matrix(m)
{
}

#if WIN32

#undef new

void* Matrix4::operator new (size_t size)
{
	return _aligned_malloc(size, 16);
}

void* Matrix4::operator new (size_t size, const char* filename, int line)
{
	return _aligned_malloc(size, 16);
}

void Matrix4::operator delete (void* p)
{
	_aligned_free(p);
}

//#define new DEBUG_NEW

#endif

bool Matrix4::Equals(const Matrix4& other) const
{
	return m_matrix == other.m_matrix;
}

//static __live_object_ptr2<__release<Matrix4> > IdentityMatrix4(new Matrix4(matrix4x4f::getIdentity()));
static __release<Matrix4> IdentityMatrix4(new Matrix4(matrix4x4f::getIdentity()));

#if 0
////////////////////////////////////////////////
// Matrix4


Matrix4::Matrix4()
{
	m_p = NULL;
}

Matrix4::Matrix4(const Matrix4 &src)
{
	m_p = src.m_p;
	if (m_p) m_p->AddRef();
}

Matrix4::Matrix4(Matrix4* p)
{
	m_p = p;
	if (m_p) m_p->AddRef();
}

Matrix4::Matrix4(const float* m)
{
	m_p = new Matrix4(m);
	m_p->AddRef();
}
#endif

Matrix4::Matrix4(float a00, float a01, float a02, float a03,
		     float a10, float a11, float a12, float a13,
		     float a20, float a21, float a22, float a23,
			  float a30, float a31, float a32, float a33) : m_matrix(a00, a01, a02, a03, a10, a11, a12, a13, a20, a21, a22, a23, a30, a31, a32, a33)
{
}

#if 0
Matrix4::~Matrix4()
{
	if (m_p) m_p->Release();
}
#endif

void Matrix4::Get(float m[16]) const
{
	std::memcpy(m, m_matrix, 16*4);
}

#if 0
Matrix4& Matrix4::operator = (const Matrix4 &src)
{
	Matrix4* old = m_p;
	m_p = src.m_p;
	if (m_p) m_p->AddRef();
	if (old) old->Release();
	return *this;
}
#endif

Matrix4* Matrix4::operator * (const Matrix4& src) const
{
	ASSERT(this);
	ASSERT(&src);
	//if (this == NULL) return &src;
	//if (&src == NULL) return this;

	return new Matrix4(m_matrix * src.m_matrix);
}

vector4f Matrix4::operator * (const vector4f &v) const
{
	//if (m_p == NULL) return v;

	return m_matrix * v;
}

LFCEXT vector4f operator * (const vector4f& v, const Matrix4& M)
{
	return v * M.m_matrix;
}

#if 0

Matrix4& Matrix4::operator *= (const Matrix4 &src)
{
	if (m_p->m_refcount > 1)
	{
		Matrix4* p = m_p;
		m_p = new Matrix4(p->m_matrix * src.m_p->m_matrix);
		m_p->AddRef();
		p->Release();
	}
	else
	{
		m_p->m_matrix *= src.m_p->m_matrix;
	}
	return *this;
}

bool Matrix4::IsInvertible() const
{
	return !m_p->m_matrix.isSingular();
}

void Matrix4::Invert()
{
	if (m_p->m_refcount > 1)
	{
		Matrix4* p = m_p;
		m_p = new Matrix4(p->m_matrix.getInverse());
		m_p->AddRef();
		p->Release();
	}
	else
	{
		m_p->m_matrix = m_p->m_matrix.getInverse();
	}
}
#endif

__release<Matrix4> Matrix4::GetInverse() const
{
	/*
	if (m_p == NULL)
		return Matrix4();
		*/

	return new Matrix4(m_matrix.getInverse());
}

// static
__release<Matrix4> Matrix4::GetIdentity()
{
	return (Matrix4*)IdentityMatrix4.m_p;
}

// static
__release<Matrix4> Matrix4::GetTranslate(float x, float y, float z)
{
	return new Matrix4(matrix4x4f::getTranslate(x, y, z));
}

// static
__release<Matrix4> Matrix4::GetScale(float x, float y, float z)
{
	return new Matrix4(matrix4x4f::getScale(x, y, z));
}

// static
__release<Matrix4> Matrix4::GetRotate(float angle, float x, float y, float z)
{
	return new Matrix4(matrix4x4f::getRotate(angle, vector3f(x, y, z)));
}

// static
__release<Matrix4> Matrix4::GetOrtho(double left, double right, double bottom, double top, double zNear, double zFar)
{
	return new Matrix4(matrix4x4f::getOrtho(left, right, bottom, top, zNear, zFar));
	/*
	double tx = - (right + left) / (right - left);
	double ty = - (top + bottom) / (top - bottom);
	double tz = - (zFar + zNear) / (zFar - zNear);

	matrix4x4f mat(2 / (right-left), 0,						0,						tx,
						0,						2 / (top-bottom), 0,							ty,
						0,						0,						-2 / (zFar - zNear), tz,
						0,						0,						0,							1);

	return new Matrix4(mat);
	*/
}

// static
__release<Matrix4> Matrix4::GetOrtho2D(double left, double right, double bottom, double top)
{
	return GetOrtho(left, right, bottom, top, -1, 1);
}

// static
__release<Matrix4> Matrix4::GetFrustum(double left, double right, double bottom, double top, double zNear, double zFar)
{
	Matrix4* pMatrix = new Matrix4;
	FrustumMatrix(pMatrix->m_matrix, left, right, bottom, top, zNear, zFar);

	return pMatrix;
}

#if 0
bool Matrix4::ReferenceEquals(const Matrix4& other) const
{
	return m_p == other.m_p;
}

bool Matrix4::Equals(const Matrix4& other) const
{
	if (m_p == other.m_p) return true;
	if (m_p == NULL) return false;
	if (other.m_p == NULL) return false;
	return m_p->Equals(*other.m_p);
}

#endif

vector3f Matrix4::Transform(const vector3f &v) const
{
	return m_matrix.transform(v);
}

/*
vector4f Matrix4::Transform(const vector4f &v) const
{
	return m_matrix.transform(v);
}
*/

}	// LDraw
}
