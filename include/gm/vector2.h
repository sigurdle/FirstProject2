// vector2.h - 2 element vector class
//
// libgm++: Graphics Math Library
// Ferdi Scheepers and Stephen F May
// 15 June 1994

#ifndef GMVECTOR2_H
#define GMVECTOR2_H


#include "gm/gmUtils.h"

namespace System
{
namespace gm
{

template<class TYPE> class vector2
{
public:
	CTOR vector2();
	CTOR vector2(const vector2<TYPE>&);
	CTOR vector2(TYPE _x, TYPE _y);
	
	// conversion
	operator TYPE* ()
	{
		return &x;
	}
	
	operator const TYPE* () const
	{
		return &x;
	}
	
	// array access
	
	TYPE& operator [](int);
	const TYPE& operator [](int) const;
	
	// assignment
	
	vector2<TYPE>& assign(TYPE, TYPE);
	vector2<TYPE>& operator =(const vector2<TYPE>&);
	
	// math operators
	
	vector2<TYPE>& operator +=(const vector2<TYPE>&);
	vector2<TYPE>& operator -=(const vector2<TYPE>&);
	template<class T> inline vector2<TYPE>& operator *= (T c)
	{
		x *= c; y *= c;
		return *this;
	}
	
	template<class T> inline vector2<TYPE>& operator /= (T c)
	{
		ASSERT(!gmIsZero(c));
		x /= c; y /= c;
		return *this;
	}
	
	vector2<TYPE> operator +(const vector2<TYPE>&) const;
	vector2<TYPE> operator -(const vector2<TYPE>&) const;
	vector2<TYPE> operator -() const;

	template<class T> inline vector2<TYPE> operator *(T c) const
	{
		return vector2<TYPE>(x * c, y * c);
	}
	template<class T> inline vector2<TYPE> operator / (T c) const
	{
		ASSERT(!gmIsZero(c));
		return vector2<TYPE>(x / c, y / c);
	}
	
	//friend gmVector2f operator *(float, const gmVector2f&);
	
	bool operator ==(const vector2<TYPE>&) const;
	bool operator !=(const vector2<TYPE>&) const;
	
	// operations
	
	vector2<TYPE>& clamp(TYPE, TYPE);
	TYPE length() const;
	TYPE lengthSquared() const;
	vector2<TYPE>& normalize();
	
	void copyTo(TYPE [2]) const;
	//void copyTo(float [2]) const;
	
	//friend float distance(const gmVector2f&, const gmVector2f&);
	//friend float distanceSquared(const gmVector2f&, const gmVector2f&);
	//friend float dot(const gmVector2f&, const gmVector2f&);
	//friend gmVector2f lerp(float, const gmVector2f&, const gmVector2f&);
	
	// swizzle

	inline vector2 xx() const
	{
		return vector2<TYPE>(x, x);
	}

	inline vector2 yy() const
	{
		return vector2<TYPE>(y, y);
	}

	inline vector2 yx() const
	{
		return vector2<TYPE>(y, x);
	}

	// output
	
#if 0
	friend ostream & operator << ( ostream &, const vector2 & );
#endif

	TYPE x, y;
};

// CONSTRUCTORS

template<class TYPE> inline vector2<TYPE>::vector2() : x(0), y(0)
{
}

template<class TYPE> inline vector2<TYPE>::vector2(const vector2<TYPE>& v) : x(v.x), y(v.y)
{
}

template<class TYPE> inline vector2<TYPE>::vector2(TYPE _x, TYPE _y) : x(_x), y(_y)
{
}

// ARRAY ACCESS

template<class TYPE> inline TYPE& vector2<TYPE>::operator [](int i)
{
  ASSERT(i == 0 || i == 1);
  return (&x)[i];
}

template<class TYPE> inline const TYPE& vector2<TYPE>::operator [](int i) const
{
  ASSERT(i == 0 || i == 1);
  return (&x)[i];
}

// ASSIGNMENT

template<class TYPE> inline vector2<TYPE>& vector2<TYPE>::assign(TYPE _x, TYPE _y)
{
	x = _x; y = _y;
	return *this;
}

template<class TYPE> inline vector2<TYPE>& vector2<TYPE>::operator =(const vector2<TYPE>& v)
{
	x = v.x; y = v.y;
	return *this;
}

// MATH OPERATORS

template<class TYPE> inline vector2<TYPE>& vector2<TYPE>::operator +=(const vector2<TYPE>& v)
{
	x += v.x; y += v.y;
	return *this;
}

template<class TYPE> inline vector2<TYPE>& vector2<TYPE>::operator -=(const vector2<TYPE>& v)
{
	x -= v.x; y -= v.y;
	return *this;
}

template<class TYPE> inline vector2<TYPE> vector2<TYPE>::operator +(const vector2<TYPE>& v) const
{
	return vector2<TYPE>(x + v.x, y + v.y);
}

template<class TYPE> inline vector2<TYPE> vector2<TYPE>::operator -(const vector2<TYPE>& v) const
{
	return vector2<TYPE>(x - v.x, y - v.y);
}

template<class TYPE> inline vector2<TYPE> vector2<TYPE>::operator -() const
{
	return vector2<TYPE>(-x, -y);
}

/*
template<class TYPE> inline gmVector2f gmVector2f::operator /(float c) const
{
  ASSERT(!gmIsZero(c));
  return gmVector2f(m_v[0] / c, m_v[1] / c);
}
*/

template<class TYPE, class T> inline vector2<TYPE> operator *(T c, const vector2<TYPE>& v)
{
	return vector2<TYPE>(c * v[0], c * v[1]);
}

template<class TYPE> inline bool vector2<TYPE>::operator ==(const vector2<TYPE>& v) const
{
	return (x == v.x) && (y == v.y);
}

template<class TYPE> inline bool vector2<TYPE>::operator !=(const vector2<TYPE>& v) const
{
	return !(*this == v);
}

// OPERATIONS

template<class TYPE> inline vector2<TYPE>& vector2<TYPE>::clamp(TYPE lo, TYPE hi)
{
	gmClamp(x, lo, hi); gmClamp(y, lo, hi);
	return *this;
}

template<class TYPE> inline TYPE vector2<TYPE>::length() const
{
	return TYPE(sqrt(gmSqr(x) + gmSqr(y)));
}

template<class TYPE> inline TYPE vector2<TYPE>::lengthSquared() const
{
	return TYPE(gmSqr(x) + gmSqr(y));
}

template<class TYPE> inline vector2<TYPE>& vector2<TYPE>::normalize()
{
	TYPE len = length();
	ASSERT(!gmIsZero(len));
	*this /= len;
	return *this;
}

template<class TYPE> inline void vector2<TYPE>::copyTo(TYPE f[2]) const
{
	f[0] = (TYPE)x; f[1] = (TYPE)y;
}

template<class TYPE> inline TYPE distance(const vector2<TYPE>& v1, const vector2<TYPE>& v2)
{
	return sqrt(gmSqr(v1[0] - v2[0]) + gmSqr(v1[1] - v2[1]));
}

template<class TYPE> inline TYPE distanceSquared(const vector2<TYPE>& v1, const vector2<TYPE>& v2)
{
	return gmSqr(v1[0] - v2[0]) + gmSqr(v1[1] - v2[1]);
}

template<class TYPE> inline TYPE dot(const vector2<TYPE>& v1, const vector2<TYPE>& v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1];
}

template<class TYPE> inline vector2<TYPE> lerp(TYPE f, const vector2<TYPE>& v1, const vector2<TYPE>& v2)
{
	return v1 + ((v2 - v1) * f);
}

//typedef gmVector2f<float> gmVector2f;
//typedef gmVector2f<float> gmVector2f;

// OUTPUT
#if 0
inline ostream & operator << ( ostream& os, const vector2& v)
{
	os << "< " << v[0] << " " << v[1] << " >";
	return os;
}
#endif

typedef vector2<int> vector2i;
typedef vector2<float> vector2f;
typedef vector2<double> vector2d;

typedef vector2<int> Vec2i;
typedef vector2<float> Vec2f;
typedef vector2<double> Vec2d;

#ifndef __LERSTAD__
#ifndef LFC_EXPORTS
template class LFCEXT vector2<float>;
template class LFCEXT vector2<double>;
#endif
#endif

}	// gm

LFCEXT float dot(gm::vector2f v1, gm::vector2f v2);
LFCEXT gm::vector2f proj(gm::vector2f v1, gm::vector2f v2);
}

#endif
