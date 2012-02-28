// matrix3f.h - 3x3 element matrix class
//
// libgm++: Graphics Math Library
// Ferdi Scheepers and Stephen F May
// 15 June 1994

#ifndef gmMatrix3f_H
#define gmMatrix3f_H

#ifndef MathExt
#define MathExt DECLSPEC_DLLIMPORT
#endif

//#include <stdio.h>
//#include <stdlib.h>
//#include <ASSERT.h>
#include "../gm/gmUtils.h"

namespace System
{
namespace gm
{

enum MatrixOrder
{
	MatrixOrderPrepend = 0,
	MatrixOrderAppend = 1
};

template<class T> class vector2;
typedef vector2<float> vector2f;
typedef vector2<double> vector2d;

	//class gmVector2f;
//	class gmVector2d;

//template<class T> class gmVector2t;
//typedef gmVector2t<float> gmVector2f;

//template<class T> class gmVector3t;
//typedef gmVector3t<float> vector3f;

//class vector3f;

class MathExt matrix3f
{
public:
  CTOR matrix3f();
  CTOR matrix3f(const matrix3f&);
  CTOR matrix3f(float, float, float, float, float, float, float, float, float);

  // array access

  float* operator [](int);
  const float* operator [](int) const;

  // assignment
  
  matrix3f& assign(float, float, float, float, float, float, float, float, float);
  matrix3f& operator =(const matrix3f&);

  // operators

  matrix3f& operator +=(const matrix3f&);
  matrix3f& operator -=(const matrix3f&);
  matrix3f& operator *=(const matrix3f&);
  matrix3f& operator *=(float);
  matrix3f& operator /=(float);
 
  matrix3f operator +(const matrix3f&) const;
  matrix3f operator -(const matrix3f&) const;
  matrix3f operator -() const;
  matrix3f operator *(const matrix3f&) const;
  matrix3f operator *(float) const;
  matrix3f operator /(float) const;

  /*
	inline bool IsIdentity() const
	{
		if (m_[0][0] != 1.0) return false;
		if (m_[1][0] != 0.0) return false;
		if (m_[2][0] != 0.0) return false;

		if (m_[1][0] != 0.0) return false;
		if (m_[1][1] != 1.0) return false;
		if (m_[1][2] != 0.0) return false;

		if (m_[2][0] != 0.0) return false;
		if (m_[2][1] != 0.0) return false;
		if (m_[2][2] != 1.0) return false;

		return true;
	};
	*/

friend MathExt matrix3f operator *(float, const matrix3f&);

  bool operator ==(const matrix3f&) const;
  bool operator !=(const matrix3f&) const;

  vector3f operator *(const vector3f&) const;

friend MathExt vector3f operator *(const vector3f&, const matrix3f&);

  // operations

  matrix3f getInverse() const;
  matrix3f getTransposed() const;
  matrix3f adjoint() const;
  
  float determinant() const;
  bool isSingular() const;

	vector2f transform(const vector2f&) const;
	vector2d transform(const vector2d&) const;
 
	vector3f transform(const vector3f& v) const
	{
	  return vector3f(
		 v[0] * m_[0][0] + v[1] * m_[1][0] + v[2] * m_[2][0]/* + m_[3][0]*/,
		 v[0] * m_[0][1] + v[1] * m_[1][1] + v[2] * m_[2][1]/* + m_[3][1]*/,
		 v[0] * m_[0][2] + v[1] * m_[1][2] + v[2] * m_[2][2]/* + m_[3][2]*/);
	}

  void copyTo(float [3][3]) const;

  // transformation matrices

  static matrix3f getIdentity();
  static matrix3f getRotate(float);
  static matrix3f getScale(float, float);
  static matrix3f getTranslate(float, float);
  static matrix3f getSkewX(float x);
  static matrix3f getSkewY(float y);

  static matrix3f tilde(const vector3f& v)
  {
	  float rx = v[0];
	  float ry = v[1];
	  float rz = v[2];

	  return matrix3f(
		  0, - rz, ry, 
		  rz,  0, - rx,
		  -ry, rx, 0 );
  }

  /*
  template<class T> static matrix3f tilde(const gmVector3t<T>& v)
  {
	  float rx = v[0];
	  float ry = v[1];
	  float rz = v[2];

	  return matrix3f(
		  0, - rz, ry, 
		  rz,  0, - rx,
		  -ry, rx, 0 );
  }

	template matrix3f matrix3f::tilde(const gmVector3t<float>& v);
//	template matrix3f matrix3f::tilde(const gmVector3t<float>& v);
*/

public:

	float m_[3][3];
};

// ARRAY ACCESS

inline float* matrix3f::operator [](int i)
{
  ASSERT(i == 0 || i == 1 || i == 2 || i == 3);
  return &m_[i][0];
}

inline const float* matrix3f::operator [](int i) const
{
  ASSERT(i == 0 || i == 1 || i == 2 || i == 3);
  return &m_[i][0];
}

inline void matrix3f::copyTo(float f[3][3]) const
{
  f[0][0] = (float)m_[0][0]; f[0][1] = (float)m_[0][1]; f[0][2] = (float)m_[0][2];
  f[1][0] = (float)m_[1][0]; f[1][1] = (float)m_[1][1]; f[1][2] = (float)m_[1][2];
  f[2][0] = (float)m_[2][0]; f[2][1] = (float)m_[2][1]; f[2][2] = (float)m_[2][2];
}

class LFCEXT Matrix3f : public System::RefCountedObject
{
public:

	CTOR Matrix3f();
	CTOR Matrix3f(float m11, float m12, float m21, float m22, float dx, float dy);
	CTOR Matrix3f(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);
	CTOR Matrix3f(const matrix3f& mat);

	bool Equals(const Matrix3f& other) const;

	double Determinant() const;

//	Matrix3f* operator * (const Matrix3f* other) const;

	void Multiply(const Matrix3f* other, MatrixOrder order = MatrixOrderPrepend);
	void Multiply(const Matrix3f* other, MatrixOrder order, Matrix3f** pVal);
	void Translate(float dx, float dy, MatrixOrder order = MatrixOrderPrepend);
	void Translate(float dx, float dy, MatrixOrder order, Matrix3f** pVal);
	void Scale(float sx, float sy, MatrixOrder order = MatrixOrderPrepend);
	void Rotate(float angle, MatrixOrder order = MatrixOrderPrepend);
	void Invert();

	__release<Matrix3f> operator * (const Matrix3f& other) const;
	__release<Matrix3f> GetInverse() const;

	Matrix3f& operator *= (const Matrix3f& other);

	friend MathExt vector3f operator *(const vector3f &, const Matrix3f &);
	vector3f operator *(const vector3f &) const;

	PointF Transform(PointI point) const;
	PointF Transform(PointF point) const;
	PointD Transform(const PointD& point) const;
	vector3f Transform(const vector3f & vec) const;
	void TransformPoints(PointF* dst, const PointF* src, int count) const;

	void Get(float m[3][2]) const;
	void Get(float m[9]) const;

	static __release<Matrix3f> GetIdentity();
	static __release<Matrix3f> GetTranslate(float dx, float dy);
	static __release<Matrix3f> GetScale(float sx, float sy);
	static __release<Matrix3f> GetRotate(float angle);
	static __release<Matrix3f> GetSkewX(float angle);
	static __release<Matrix3f> GetSkewY(float angle);

	matrix3f m_matrix;
};

/*
class MathExt Matrix3f
{
public:
	Matrix3f();
	Matrix3f(float m11, float m12, float m21, float m22, float dx, float dy);
	Matrix3f(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);
	Matrix3f(const Matrix3f& other);
	Matrix3f(Matrix3f* p);
	~Matrix3f();

//	const float* operator [] (int row) const;

	void Get(float m[3][2]) const;
	void Get(float m[9]) const;

	void Multiply(const Matrix3f& other, MatrixOrder order = MatrixOrderPrepend);
	void Translate(float dx, float dy, MatrixOrder order = MatrixOrderPrepend);
	void Scale(float sx, float sy, MatrixOrder order = MatrixOrderPrepend);
	void Rotate(float angle, MatrixOrder order = MatrixOrderPrepend);
	void Invert();

	bool IsIdentity() const;
	bool IsInvertible() const;

	double Determinant() const;
	Matrix3f GetInverse() const;
	Matrix3f GetMultiplied(const Matrix3f & other) const;

	static Matrix3f GetIdentity();
	static Matrix3f GetTranslate(float dx, float dy);
	static Matrix3f GetScale(float sx, float sy);
	static Matrix3f GetRotate(float angle);
	static Matrix3f GetSkewX(float angle);
	static Matrix3f GetSkewY(float angle);

	PointF Transform(PointF point) const;
	vector3f Transform(const vector3f &vec) const;
	PointD Transform(const PointD& point) const;
	void TransformPoints(PointF* dst, const PointF* src, int count) const;

	Matrix3f operator * (const Matrix3f& other) const;
	Matrix3f& operator = (const Matrix3f& other);
	Matrix3f& operator *= (const Matrix3f& other);
//	Matrix& operator = (const matrix3f& other);

	friend MathExt vector3f operator *(const vector3f &, const Matrix3f &);
	vector3f operator *(const vector3f &) const;

	bool ReferenceEquals(const Matrix3f & other) const;
	bool Equals(const Matrix3f & other) const;

	inline bool operator == (const Matrix3f & other) const
	{
		return Equals(other);
	}

	inline bool operator != (const Matrix3f& other) const
	{
		return !Equals(other);
	}

	Matrix3f* m_p;
};
*/

//typedef Matrix3f Matrix;

}	// LDraw
}

#endif
