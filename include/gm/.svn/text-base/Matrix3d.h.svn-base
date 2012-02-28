// matrix3d.h - 3x3 element matrix class
//
// libgm++: Graphics Math Library
// Ferdi Scheepers and Stephen F May
// 15 June 1994

#ifndef gmMatrix3d_H
#define gmMatrix3d_H

/*
#ifndef LFCEXT
#define LFCEXT DECLSPEC_DLLIMPORT
#endif
*/

//#include <stdio.h>
//#include <stdlib.h>
//#include <ASSERT.h>
#include "../gm/gmUtils.h"

namespace System
{
namespace gm
{

//template<class T> class gmVector2t;
//typedef gmVector2t<float> gmVector2f;
//typedef gmVector2t<double> gmVector2d;

template<class T> class vector2;
typedef vector2<double> vector2d;

template<class T> class vector3;
typedef vector3<double> vector3d;

class LFCEXT matrix3d
{
public:
	CTOR matrix3d();
	CTOR matrix3d(const matrix3d&);
	CTOR matrix3d(double, double, double,
		double, double, double,
		double, double, double);
	
	// array access
	
	double* operator [](int);
	const double* operator [](int) const;
	
	// assignment
	
	matrix3d& assign(double, double, double,
		    double, double, double,
			 double, double, double);
	matrix3d& operator =(const matrix3d&);
	
	// operators
	
	matrix3d& operator +=(const matrix3d&);
	matrix3d& operator -=(const matrix3d&);
	matrix3d& operator *=(const matrix3d&);
	matrix3d& operator *=(double);
	matrix3d& operator /=(double);
	
	matrix3d operator +(const matrix3d&) const;
	matrix3d operator -(const matrix3d&) const;
	matrix3d operator -() const;
	matrix3d operator *(const matrix3d&) const;
	matrix3d operator *(double) const;
	matrix3d operator /(double) const;

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
	}
	
	friend LFCEXT matrix3d operator *(double, const matrix3d&);
	
	bool operator ==(const matrix3d&) const;
	inline bool operator !=(const matrix3d& M) const
	{
		return !(*this == M);
	}
	
	vector3d operator *(const vector3d&) const;
	
	friend LFCEXT vector3d operator *(const vector3d&, const matrix3d&);
	
	// operations
	
	matrix3d getInverse() const;
	matrix3d getTransposed() const;
	matrix3d getAdjoint() const;
	
	double determinant() const;
	bool isSingular() const;

	vector2d transform(const vector2d&) const;
//	gmVector2d transform(const gmVector2f&) const;
//	DblPOINT matrix3d::transform(const DblPOINT& v) const;
 
#if 0
	gmVector3t<float> matrix3d::transform(const gmVector3t<float>& v) const
	{
	  return gmVector3t<float>(
		 v[0] * m_[0][0] + v[1] * m_[1][0] + v[2] * m_[2][0]/* + m_[3][0]*/,
		 v[0] * m_[0][1] + v[1] * m_[1][1] + v[2] * m_[2][1]/* + m_[3][1]*/,
		 v[0] * m_[0][2] + v[1] * m_[1][2] + v[2] * m_[2][2]/* + m_[3][2]*/);
	}
#endif

	vector3d transform(const vector3d& v) const;

  void copyTo(float [3][3]) const;
  void copyTo(double [3][3]) const;

  // transformation matrices

  static matrix3d getIdentity();
  static matrix3d getRotate(double);
  static matrix3d getScale(double, double);
  static matrix3d getTranslate(double, double);
  static matrix3d getSkewX(double x);
  static matrix3d getSkewY(double y);

  /*
  static matrix3d tilde(const gmVector3t<float>& v)
  {
	  double rx = v[0];
	  double ry = v[1];
	  double rz = v[2];

	  return matrix3d(
		  0, - rz, ry, 
		  rz,  0, - rx,
		  -ry, rx, 0 );
  }
  */

  static matrix3d getTilde(const vector3d& v);

  /*
  template<class T> static matrix3d tilde(const gmVector3t<T>& v)
  {
	  double rx = v[0];
	  double ry = v[1];
	  double rz = v[2];

	  return matrix3d(
		  0, - rz, ry, 
		  rz,  0, - rx,
		  -ry, rx, 0 );
  }

	template matrix3d matrix3d::tilde(const gmVector3t<float>& v);
//	template matrix3d matrix3d::tilde(const gmVector3t<double>& v);
*/

public:
  double m_[3][3];
};

// ARRAY ACCESS

inline double* matrix3d::operator [](int i)
{
  ASSERT(i == 0 || i == 1 || i == 2 || i == 3);
  return &m_[i][0];
}

inline const double* matrix3d::operator [](int i) const
{
  ASSERT(i == 0 || i == 1 || i == 2 || i == 3);
  return &m_[i][0];
}

inline void matrix3d::copyTo(float f[3][3]) const
{
  f[0][0] = (float)m_[0][0]; f[0][1] = (float)m_[0][1]; f[0][2] = (float)m_[0][2];
  f[1][0] = (float)m_[1][0]; f[1][1] = (float)m_[1][1]; f[1][2] = (float)m_[1][2];
  f[2][0] = (float)m_[2][0]; f[2][1] = (float)m_[2][1]; f[2][2] = (float)m_[2][2];
}

inline void matrix3d::copyTo(double f[3][3]) const
{
  f[0][0] = m_[0][0]; f[0][1] = m_[0][1]; f[0][2] = m_[0][2];
  f[1][0] = m_[1][0]; f[1][1] = m_[1][1]; f[1][2] = m_[1][2];
  f[2][0] = m_[2][0]; f[2][1] = m_[2][1]; f[2][2] = m_[2][2];
}

class LFCEXT Matrix3d : public System::RefCountedObject
{
public:

	CTOR Matrix3d();
	CTOR Matrix3d(double m11, double m12, double m21, double m22, double dx, double dy);
	CTOR Matrix3d(double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33);
	CTOR Matrix3d(const matrix3d& mat);

	bool Equals(const Matrix3d& other) const;

	double Determinant() const;

	PointD Transform(const PointD& point) const;
//	vector3d Transform(const vector3d& vec) const;

	__release<Matrix3d> operator * (const Matrix3d& other) const;
	__release<Matrix3d> GetInverse();

	static __release<Matrix3d> GetIdentity();
	static __release<Matrix3d> GetTranslate(double dx, double dy);
	static __release<Matrix3d> GetScale(double sx, double sy);
	static __release<Matrix3d> GetRotate(double angle);
	static __release<Matrix3d> GetSkewX(double angle);
	static __release<Matrix3d> GetSkewY(double angle);

	matrix3d m_matrix;
};

#if 0
class LFCEXT Matrix3d
{
public:
	Matrix3d();
	Matrix3d(double m11, double m12, double m21, double m22, double dx, double dy);
	Matrix3d(double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33);
	Matrix3d(const matrix3d & m);
	Matrix3d(const Matrix3d& other);
	Matrix3d(_Matrix3d* p);
	~Matrix3d();

//	const double* operator [] (int row) const;

	void Get(double m[3][2]) const;
	void Get(double m[9]) const;

	void Multiply(const Matrix3d& other, MatrixOrder order = MatrixOrderPrepend);
	void Translate(double dx, double dy, MatrixOrder order = MatrixOrderPrepend);
	void Scale(double sx, double sy, MatrixOrder order = MatrixOrderPrepend);
	void Rotate(double angle, MatrixOrder order = MatrixOrderPrepend);
	void Invert();

	bool IsIdentity() const;
	bool IsInvertible() const;

	double Determinant() const;
	Matrix3d GetInverse() const;
	Matrix3d GetMultiplied(const Matrix3d& other) const;

	static Matrix3d GetIdentity();
	static Matrix3d GetTranslate(double dx, double dy);
	static Matrix3d GetScale(double sx, double sy);
	static Matrix3d GetRotate(double angle);
	static Matrix3d GetSkewX(double angle);
	static Matrix3d GetSkewY(double angle);

	PointD Transform(const PointD & point) const;
	vector3d Transform(const vector3d & vec) const;
	void TransformPoints(PointD* dst, const PointD* src, int count) const;

	Matrix3d operator * (const Matrix3d& other) const;
	Matrix3d& operator = (const Matrix3d& other);
	Matrix3d& operator *= (const Matrix3d& other);
//	Matrix& operator = (const gmMatrix3f& other);

	friend LFCEXT vector3d operator *(const vector3d&, const Matrix3d&);
	vector3d operator *(const vector3d&) const;

	bool ReferenceEquals(const Matrix3d& other) const;
	bool Equals(const Matrix3d& other) const;

	inline bool operator == (const Matrix3d& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const Matrix3d& other) const
	{
		return !Equals(other);
	}

	class _Matrix3d* m_p;

};
#endif

}	// LDraw
}

#endif
