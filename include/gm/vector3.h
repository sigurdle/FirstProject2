// vector3<TYPE>.h - 3 element vector class
//
// libgm++: Graphics Math Library
// Ferdi Scheepers and Stephen F May
// 15 June 1994

#ifndef gm_Vector3f_h
#define gm_Vector3f_h

#include "../gm/gmUtils.h"

namespace System
{
namespace gm
{

template<class T> class vector2;

class matrix4x4f;
class Matrix4;

template<class TYPE> class vector3
{
public:

	CTOR vector3() : x(0), y(0), z(0)
	{
	}

	CTOR vector3(const vector3<TYPE>&);
	CTOR vector3(const vector2<TYPE>& v)
	{
		x = v.x;
		y = v.y;
		z = 0;
	}
	CTOR vector3(TYPE _x, TYPE _y, TYPE _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	
	inline operator TYPE* ()
	{
		return &x;
	}
	
	inline operator const TYPE* () const
	{
		return &x;
	}

	//
	/*
	operator D3DXVECTOR3 () const
	{
		return *(D3DXVECTOR3*)this;
	}
	*/

	// array access
	
	TYPE& operator [](int);
	const TYPE& operator [](int) const;
	
	// assignment
	
	vector3<TYPE>& assign(TYPE, TYPE, TYPE);
	vector3<TYPE>& operator =(const vector3<TYPE>&);
	
	// math operators
	
	vector3<TYPE>& operator +=(const vector3<TYPE>&);
	vector3<TYPE>& operator -=(const vector3<TYPE>&);

	inline vector3<TYPE>& operator *=(int c)
	{
		x = (TYPE)(x * c);
		y = (TYPE)(y * c);
		z = (TYPE)(z * c);
		return *this;
	}

	inline vector3<TYPE>& operator *=(float c)
	{
		x = (TYPE)(x * c);
		y = (TYPE)(y * c);
		z = (TYPE)(z * c);
		return *this;
	}

	inline vector3<TYPE>& operator *=(double c)
	{
		x = (TYPE)(x * c);
		y = (TYPE)(y * c);
		z = (TYPE)(z * c);
		return *this;
	}

	inline vector3<TYPE>& operator /=(int c)
	{
		ASSERT(!gmIsZero(c));
		x = (TYPE)(x / c);
		y = (TYPE)(y / c);
		z = (TYPE)(z / c);
		return *this;
	}

	inline vector3<TYPE>& operator /=(float c)
	{
		ASSERT(!gmIsZero(c));
		x = (TYPE)(x / c);
		y = (TYPE)(y / c);
		z = (TYPE)(z / c);
		return *this;
	}

	inline vector3<TYPE>& operator /=(double c)
	{
		ASSERT(!gmIsZero(c));
		x = (TYPE)(x / c);
		y = (TYPE)(y / c);
		z = (TYPE)(z / c);
		return *this;
	}

	vector3<TYPE> operator +(const vector3<TYPE>&) const;
	vector3<TYPE> operator -(const vector3<TYPE>&) const;
	//	vector3<TYPE> operator *(const vector3<TYPE>&) const;
	vector3<TYPE> operator -() const;

	inline vector3<TYPE> operator *(int c) const
	{
		return vector3<TYPE>((TYPE)(x * c), (TYPE)(y * c), (TYPE)(z * c));
	}

	inline vector3<TYPE> operator *(float c) const
	{
		return vector3<TYPE>((TYPE)(x * c), (TYPE)(y * c), (TYPE)(z * c));
	}

	inline vector3<TYPE> operator *(double c) const
	{
		return vector3<TYPE>((TYPE)(x * c), (TYPE)(y * c), (TYPE)(z * c));
	}

	inline vector3<TYPE> operator /(int c) const
	{
		ASSERT(!gmIsZero(c));
		return vector3<TYPE>((TYPE)(x / c), (TYPE)(y / c), (TYPE)(z / c));
	}
	
	inline vector3<TYPE> operator /(float c) const
	{
		ASSERT(!gmIsZero(c));
		return vector3<TYPE>((TYPE)(x / c), (TYPE)(y / c), (TYPE)(z / c));
	}
	
	inline vector3<TYPE> operator /(double c) const
	{
		ASSERT(!gmIsZero(c));
		return vector3<TYPE>((TYPE)(x / c), (TYPE)(y / c), (TYPE)(z / c));
	}
	
	//friend vector3<TYPE> operator *(TYPE, const vector3<TYPE>&);
	
	bool operator ==(const vector3<TYPE>&) const;
	bool operator !=(const vector3<TYPE>&) const;
	
	// operations
	
//	vector3<TYPE> Project(const matrix4x4f& proj, const double viewport[4]) const;
//	vector3<TYPE> UnProject(const matrix4x4f& proj, const double viewport[4]) const;
	
//	vector3<TYPE> Project(const matrix4x4f& model, const matrix4x4f& proj, const double viewport[4]) const;
//	vector3<TYPE> UnProject(const matrix4x4f& model, const matrix4x4f& proj, const double viewport[4]) const;
	
	vector3<TYPE>& clamp(TYPE, TYPE);
	double length() const;
	double lengthSquared() const;
	vector3<TYPE>& normalize();
	
	void copyTo(TYPE [3]) const;
	
	//   friend vector3<TYPE> cross(const vector3<TYPE>&, const vector3<TYPE>&);
	//	friend double distance(const vector3<TYPE>&, const vector3<TYPE>&);
	//	friend double distanceSquared(const vector3<TYPE>&, const vector3<TYPE>&);
	//template<> friend double dot(const vector3<TYPE>&, const vector3<TYPE>&);
	//template<class T2> friend vector3<TYPE> lerp(double, const vector3<TYPE>&, const vector3<TYPE>&);
	
	// swizzle

	/*
	inline TYPE x() const
	{
		return x;
	}

	inline TYPE y() const
	{
		return y;
	}

	inline TYPE z() const
	{
		return z;
	}
	*/

	inline vector2<TYPE> xy() const
	{
		return vector2<TYPE>(x, y);
	}

	inline vector3<TYPE> xyy() const
	{
		return vector3<TYPE>(x, y, y);
	}

	inline vector2<TYPE> yx() const
	{
		return vector2<TYPE>(y, x);
	}

	inline vector3<TYPE> yxx() const
	{
		return vector3<TYPE>(y, x, x);
	}

	inline vector3<TYPE> xyz() const
	{
		return vector3<TYPE>(x, y, z);
	}

	inline vector3<TYPE> zyx() const
	{
		return vector3<TYPE>(z, y, x);
	}

	inline vector3<TYPE> xzy() const
	{
		return vector3<TYPE>(x, z, y);
	}

	inline vector3<TYPE> yzx() const
	{
		return vector3<TYPE>(y, z, x);
	}

	inline vector3<TYPE> zxy() const
	{
		return vector3<TYPE>(z, x, y);
	}

	// output
#if 0
	friend ostream & operator << ( ostream &, const vector3<TYPE> & );
#endif
	
	/*
	union
	{
		TYPE m_v[3];
		struct
		{
		*/
			TYPE x;
			TYPE y;
			TYPE z;
			/*
		};
	};
	*/
};

// CONSTRUCTORS

template<class TYPE> inline vector3<TYPE>::vector3(const vector3<TYPE>& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

// ARRAY ACCESS

template<class TYPE> inline TYPE& vector3<TYPE>::operator [](int i)
{
	ASSERT(i == 0 || i == 1 || i == 2);
	return (&x)[i];
}

template<class TYPE> inline const TYPE& vector3<TYPE>::operator [](int i) const
{
	ASSERT(i == 0 || i == 1 || i == 2);
	return (&x)[i];
}

// ASSIGNMENT

template<class TYPE> inline vector3<TYPE>& vector3<TYPE>::assign(TYPE _x, TYPE _y, TYPE _z)
{
	x = _x;
	y = _y;
	z = _z;
	return *this;
}

template<class TYPE> inline vector3<TYPE>& vector3<TYPE>::operator = (const vector3<TYPE>& v)
{
	x = v[0];
	y = v[1];
	z = v[2];
	return *this;
}

// MATH OPERATORS

template<class TYPE> inline vector3<TYPE>& vector3<TYPE>::operator += (const vector3<TYPE>& v)
{
	x += v[0];
	y += v[1];
	z += v[2];
	return *this;
}

template<class TYPE> inline vector3<TYPE>& vector3<TYPE>::operator -= (const vector3<TYPE>& v)
{
	x -= v[0];
	y -= v[1];
	z -= v[2];
	return *this;
}

/*
inline vector3<TYPE> vector3<TYPE>::operator *(const vector3<TYPE>& v) const
{
  return vector3<TYPE>(m_v[0] * v[0], m_v[1] * v[1], m_v[2] * v[2]);
}
*/

template<class TYPE> inline vector3<TYPE> vector3<TYPE>::operator + (const vector3<TYPE>& v) const
{
	return vector3<TYPE>(x + v[0], y + v[1], z + v[2]);
}

template<class TYPE> inline vector3<TYPE> vector3<TYPE>::operator - (const vector3<TYPE>& v) const
{
	return vector3<TYPE>(x - v[0], y - v[1], z - v[2]);
}

template<class TYPE> inline vector3<TYPE> vector3<TYPE>::operator - () const
{
	return vector3<TYPE>(-x, -y, -z);
}

template<class TYPE> inline bool vector3<TYPE>::operator == (const vector3<TYPE>& v) const
{
	return
		(x == v[0]) && (y == v[1]) && (z == v[2]);

	//  return
	//  (gmFuzEQ(m_v[0], v[0]) && gmFuzEQ(m_v[1], v[1]) && gmFuzEQ(m_v[2], v[2]));
}

template<class TYPE> inline bool vector3<TYPE>::operator != (const vector3<TYPE>& v) const
{
	return !(*this == v);
}

// OPERATIONS

template<class TYPE> inline vector3<TYPE>& vector3<TYPE>::clamp(TYPE lo, TYPE hi)
{
	gmClamp(x, lo, hi); gmClamp(y, lo, hi); gmClamp(z, lo, hi);
	return *this;
}

template<class TYPE> inline double vector3<TYPE>::length() const
{
	return sqrt(gmSqr(x) + gmSqr(y) + gmSqr(z));
}

template<class TYPE> inline double vector3<TYPE>::lengthSquared() const
{
	return gmSqr(x) + gmSqr(y) + gmSqr(z);
}

template<class TYPE> inline vector3<TYPE>& vector3<TYPE>::normalize()
{
	TYPE len = (TYPE)length();
	//ASSERT(!gmIsZero(len));
	*this *= 1/len;
	return *this;
}

template<class TYPE> inline void vector3<TYPE>::copyTo(TYPE f[3]) const
{
	f[0] = x;
	f[1] = y;
	f[2] = z;
}

/*
inline void vector3<TYPE>::copyTo(double f[3]) const
{
f[0] = m_v[0]; f[1] = m_v[1]; f[2] = m_v[2];
}
*/

template<class TYPE> inline vector3<TYPE> cross(const vector3<TYPE>& v1, const vector3<TYPE>& v2)
{
	return vector3<TYPE>(v1[1] * v2[2] - v1[2] * v2[1],
		v1[2] * v2[0] - v1[0] * v2[2],
		v1[0] * v2[1] - v1[1] * v2[0]);
}

template<class TYPE> inline double distance(const vector3<TYPE>& v1, const vector3<TYPE>& v2)
{
	return
		sqrt(gmSqr(v1[0] - v2[0]) + gmSqr(v1[1] - v2[1]) + gmSqr(v1[2] - v2[2]));
}

template<class TYPE> inline double gmDistance(const vector3<TYPE>& v1, const vector3<TYPE>& v2)
{
	return
		sqrt(gmSqr(v1[0] - v2[0]) + gmSqr(v1[1] - v2[1]) + gmSqr(v1[2] - v2[2]));
}

template<class TYPE> inline double distanceSquared(const vector3<TYPE>& v1, const vector3<TYPE>& v2)
{
	return gmSqr(v1[0] - v2[0]) + gmSqr(v1[1] - v2[1]) + gmSqr(v1[2] - v2[2]);
}

template<class TYPE> inline double dot(const vector3<TYPE>& v1, const vector3<TYPE>& v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

template<class TYPE> inline vector3<TYPE> lerp(double f, const vector3<TYPE>& v1, const vector3<TYPE>& v2)
{
	return v1 + ((v2 - v1) * f);
}

template<class TYPE> inline vector3<TYPE> operator *(int c, const vector3<TYPE>& v)
{
	return vector3<TYPE>(TYPE(c * v[0]), TYPE(c * v[1]), TYPE(c * v[2]));
}

template<class TYPE> inline vector3<TYPE> operator *(float c, const vector3<TYPE>& v)
{
	return vector3<TYPE>(TYPE(c * v[0]), TYPE(c * v[1]), TYPE(c * v[2]));
}

template<class TYPE> inline vector3<TYPE> operator *(double c, const vector3<TYPE>& v)
{
	return vector3<TYPE>(TYPE(c * v[0]), TYPE(c * v[1]), TYPE(c * v[2]));
}

typedef vector3<int> vector3i;
typedef vector3<float> vector3f;
typedef vector3<double> vector3d;

typedef vector3<int> Vec3i;
typedef vector3<float> Vec3f;
typedef vector3<double> Vec3d;

typedef vector3<float> float3;

#ifndef __LERSTAD__
#ifndef LFC_EXPORTS
template class LFCEXT vector3<float>;
template class LFCEXT vector3<double>;
#endif
#endif

}

/*
namespace Math
{
	typedef LDraw::vector3<float> float3;
}
*/

LFCEXT gm::vector3f proj(gm::vector3f a, gm::vector3f u);

}

#endif // gm_Vector3f_h
