#ifndef gm_Vector4f_h
#define gm_Vector4f_h

namespace System
{
namespace gm
{

template<class TYPE> class vector4
{
public:
	CTOR vector4();
	CTOR vector4(const vector4<TYPE>&);
	CTOR vector4(TYPE, TYPE, TYPE, TYPE);
	CTOR vector4(const vector3<TYPE>&, TYPE);
	
	// array access

	inline operator float* ()
	{
		return m_v;
	}

	inline operator const float* () const
	{
		return m_v;
	}
	
	TYPE& operator [](int);
	const TYPE operator [](int) const;
	
	//
/*
	operator D3DXVECTOR4 () const
	{
		return *(D3DXVECTOR4*)this;
	}
*/

	// assignment
	
	vector4<TYPE>& assign(TYPE, TYPE, TYPE, TYPE);
	vector4<TYPE>& operator = (const vector4<TYPE>&);
	
	// math operators
	
	vector4<TYPE>& operator += (const vector4<TYPE>&);
	vector4<TYPE>& operator -= (const vector4<TYPE>&);
	//  vector4<TYPE>& operator *=(TYPE);
	//  vector4<TYPE>& operator /=(TYPE);
	
	inline vector4<TYPE>& operator *= (int c)
	{
		m_v[0] *= c;
		m_v[1] *= c;
		m_v[2] *= c;
		m_v[3] *= c;
		return *this;
	}

	inline vector4<TYPE>& operator *= (float c)
	{
		m_v[0] *= c;
		m_v[1] *= c;
		m_v[2] *= c;
		m_v[3] *= c;
		return *this;
	}

	inline vector4<TYPE>& operator *= (double c)
	{
		m_v[0] *= c;
		m_v[1] *= c;
		m_v[2] *= c;
		m_v[3] *= c;
		return *this;
	}

	inline vector4<TYPE>& operator /= (int c)
	{
		ASSERT(!gmIsZero(c));
		
		m_v[0] /= c;
		m_v[1] /= c;
		m_v[2] /= c;
		m_v[3] /= c;
		return *this;
	}

	inline vector4<TYPE>& operator /= (float c)
	{
		ASSERT(!gmIsZero(c));
		float ic = 1.0f/c;
		
		m_v[0] *= ic;
		m_v[1] *= ic;
		m_v[2] *= ic;
		m_v[3] *= ic;
		return *this;
	}

	inline vector4<TYPE>& operator /= (double c)
	{
		ASSERT(!gmIsZero(c));
		double ic = 1.0/c;
		
		m_v[0] *= ic;
		m_v[1] *= ic;
		m_v[2] *= ic;
		m_v[3] *= ic;
		return *this;
	}

	vector4<TYPE> operator * (const vector4<TYPE>& other) const
	{
		// TODO SSE3 optimized
		return vector4<TYPE>(m_v[0] * other[0], m_v[1] * other[1], m_v[2] * other[2], m_v[3] * other[3]);
	}

	vector4<TYPE> operator + (const vector4<TYPE>&) const;
	vector4<TYPE> operator - (const vector4<TYPE>&) const;
	vector4<TYPE> operator - () const;
//  vector4<TYPE> operator *(TYPE) const;
//  vector4<TYPE> operator /(TYPE) const;

	inline vector4<TYPE> operator * (int c) const
	{
	  return vector4<TYPE>(
		  m_v[0] * c,
		  m_v[1] * c,
		  m_v[2] * c,
		  m_v[3] * c);
	}

	inline vector4<TYPE> operator * (float c) const
	{
	  return vector4<TYPE>(
		  m_v[0] * c,
		  m_v[1] * c,
		  m_v[2] * c,
		  m_v[3] * c);
	}

	inline vector4<TYPE> operator * (double c) const
	{
	  return vector4<TYPE>(
		  m_v[0] * c,
		  m_v[1] * c,
		  m_v[2] * c,
		  m_v[3] * c);
	}

	inline vector4<TYPE> operator / (int c) const
	{
	  ASSERT(!gmIsZero(c));

	  return vector4<TYPE>(
		  m_v[0] / c,
		  m_v[1] / c,
		  m_v[2] / c,
		  m_v[3] / c);
	}

	inline vector4<TYPE> operator / (float c) const
	{
	  ASSERT(!gmIsZero(c));

	  return vector4<TYPE>(
		  m_v[0] / c,
		  m_v[1] / c,
		  m_v[2] / c,
		  m_v[3] / c);
	}

	inline vector4<TYPE> operator / (double c) const
	{
	  ASSERT(!gmIsZero(c));

	  return vector4<TYPE>(
		  m_v[0] / c,
		  m_v[1] / c,
		  m_v[2] / c,
		  m_v[3] / c);
	}

	vector4<TYPE>& operator = (const vector3<TYPE>& v)
	{
		m_v[0] = v[0];
		m_v[1] = v[1];
		m_v[2] = v[2];
		m_v[3] = 1;
		return *this;
	}

//friend vector4<TYPE> operator *(TYPE, const vector4<TYPE>&);

	bool operator == (const vector4<TYPE>&) const;
	bool operator != (const vector4<TYPE>&) const;

  // operations

	vector4<TYPE>& clamp(TYPE, TYPE);
	TYPE length() const;
	TYPE lengthSquared() const;
	vector4<TYPE>& normalize();

	void copyTo(TYPE [4]) const;

	LFCEXT friend TYPE distance(const vector4<TYPE>&, const vector4<TYPE>&);
	LFCEXT friend TYPE distanceSquared(const vector4<TYPE>&, const vector4<TYPE>&);
//	LFCEXT friend TYPE dot(const vector4<TYPE>&, const vector4<TYPE>&);
	LFCEXT friend vector4<TYPE> lerp(TYPE, const vector4<TYPE>&, const vector4<TYPE>&);

	/*
	template<class TYPE2> friend TYPE2 distance(const vector4<TYPE2>&, const vector4<TYPE>&);
	template<class TYPE2> friend TYPE2 distanceSquared(const vector4<TYPE2>&, const vector4<TYPE>&);
	template<class TYPE2> friend TYPE2 dot(const vector4<TYPE2>&, const vector4<TYPE>&);
	template<class TYPE2> friend vector4<TYPE2> lerp(TYPE, const vector4<TYPE2>&, const vector4<TYPE>&);
*/
protected:

	TYPE m_v[4];
};

// CONSTRUCTORS

template<class TYPE> inline vector4<TYPE>::vector4()
{
	m_v[0] = m_v[1] = m_v[2] = m_v[3] = 0;
}

template<class TYPE> inline vector4<TYPE>::vector4(const vector4<TYPE>& v)
{
	m_v[0] = v.m_v[0]; m_v[1] = v.m_v[1]; m_v[2] = v.m_v[2]; m_v[3] = v.m_v[3];
}

template<class TYPE> inline vector4<TYPE>::vector4(const vector3<TYPE>& v, TYPE _3)
{
	m_v[0] = v[0]; m_v[1] = v[1]; m_v[2] = v[2]; m_v[3] = _3;
}

template<class TYPE> inline vector4<TYPE>::vector4(TYPE x, TYPE y, TYPE z, TYPE a)
{
	m_v[0] = x; m_v[1] = y; m_v[2] = z; m_v[3] = a;
}

// ARRAY ACCESS

template<class TYPE> inline TYPE& vector4<TYPE>::operator [] (int i) 
{
	ASSERT(i == 0 || i == 1 || i == 2 || i == 3);
	return m_v[i];
}

template<class TYPE> inline const TYPE vector4<TYPE>::operator [] (int i) const
{
	ASSERT(i == 0 || i == 1 || i == 2 || i == 3);
	return m_v[i];
}

// ASSIGNMENT

template<class TYPE> inline vector4<TYPE>& vector4<TYPE>::assign(TYPE x, TYPE y, TYPE z, TYPE a)
{
	m_v[0] = x; m_v[1] = y; m_v[2] = z; m_v[3] = a;
	return *this;
}

template<class TYPE> inline vector4<TYPE>& vector4<TYPE>::operator = (const vector4<TYPE>& v)
{
	m_v[0] = v[0]; m_v[1] = v[1]; m_v[2] = v[2]; m_v[3] = v[3];
	return *this;
}

// MATH OPERATORS

template<class TYPE> inline vector4<TYPE>& vector4<TYPE>::operator += (const vector4<TYPE>& v)
{
	m_v[0] += v[0];
	m_v[1] += v[1];
	m_v[2] += v[2];
	m_v[3] += v[3];
	return *this;
}

template<class TYPE> inline vector4<TYPE>& vector4<TYPE>::operator -= (const vector4<TYPE>& v)
{
	m_v[0] -= v[0];
	m_v[1] -= v[1];
	m_v[2] -= v[2];
	m_v[3] -= v[3];
	return *this;
}

template<class TYPE> inline vector4<TYPE> vector4<TYPE>::operator + (const vector4<TYPE>& v) const
{
	return vector4<TYPE>(m_v[0] + v[0], m_v[1] + v[1], m_v[2] + v[2], m_v[3] + v[3]);
}

template<class TYPE> inline vector4<TYPE> vector4<TYPE>::operator - (const vector4<TYPE>& v) const
{
	return vector4<TYPE>(m_v[0] - v[0], m_v[1] - v[1], m_v[2] - v[2], m_v[3] - v[3]);
}

template<class TYPE> inline vector4<TYPE> vector4<TYPE>::operator - () const
{
	return vector4<TYPE>(-m_v[0], -m_v[1], -m_v[2], -m_v[3]);
}

template<class TYPE> inline bool vector4<TYPE>::operator == (const vector4<TYPE>& v) const
{
	return ((m_v[0] == v[0]) && (m_v[1] == v[1]) &&
		(m_v[2] == v[2]) && (m_v[3] == v[3]));
	
	//  return (gmFuzEQ(m_v[0], v[0]) && gmFuzEQ(m_v[1], v[1]) &&
	//          gmFuzEQ(m_v[2], v[2]) && gmFuzEQ(m_v[3], v[3]));
}

template<class TYPE> inline bool vector4<TYPE>::operator != (const vector4<TYPE>& v) const
{
	return !(*this == v);
}

// OPERATIONS

/*
inline vector4<TYPE>& vector4<TYPE>::clamp(TYPE lo, TYPE hi)
{
gmClamp(m_v[0], lo, hi); gmClamp(m_v[1], lo, hi);
gmClamp(m_v[2], lo, hi); gmClamp(m_v[3], lo, hi);
return *this;
}
*/

template<class TYPE> inline TYPE vector4<TYPE>::length() const
{
	return sqrt(gmSqr(m_v[0]) + gmSqr(m_v[1]) + gmSqr(m_v[2]) + gmSqr(m_v[3]));
}

template<class TYPE> inline TYPE vector4<TYPE>::lengthSquared() const
{
	return gmSqr(m_v[0]) + gmSqr(m_v[1]) + gmSqr(m_v[2]) + gmSqr(m_v[3]);
}

template<class TYPE> inline vector4<TYPE>& vector4<TYPE>::normalize()
{
	TYPE len = length();
	ASSERT(!gmIsZero(len));
	*this *= 1/len;
	return *this;
}

template<class TYPE> inline void vector4<TYPE>::copyTo(TYPE f[4]) const
{
	f[0] = m_v[0];
	f[1] = m_v[1];
	f[2] = m_v[2];
	f[3] = m_v[3];
}

template<class TYPE> inline TYPE distance(const vector4<TYPE>& v1, const vector4<TYPE>& v2)
{
	return sqrt(gmSqr(v1[0] - v2[0]) + gmSqr(v1[1] - v2[1]) + gmSqr(v1[2] - v2[2]) + gmSqr(v1[3] - v2[3]));
}

template<class TYPE> inline TYPE distanceSquared(const vector4<TYPE>& v1, const vector4<TYPE>& v2)
{
	return gmSqr(v1[0] - v2[0]) + gmSqr(v1[1] - v2[1]) + gmSqr(v1[2] - v2[2]) + gmSqr(v1[3] - v2[3]);
}

template<class TYPE> inline TYPE dot(const vector4<TYPE>& v1, const vector4<TYPE>& v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
}

template<class TYPE> inline vector4<TYPE> lerp(TYPE f, const vector4<TYPE>& v1, const vector4<TYPE>& v2)
{
	return v1 + ((v2 - v1) * f);
}

template<class TYPE> inline vector4<TYPE> operator * (int c, const vector4<TYPE>& v)
{
	return vector4<TYPE>(c * v[0], c * v[1], c * v[2], c * v[3]);
}

template<class TYPE> inline vector4<TYPE> operator * (float c, const vector4<TYPE>& v)
{
	return vector4<TYPE>(c * v[0], c * v[1], c * v[2], c * v[3]);
}

template<class TYPE> inline vector4<TYPE> operator * (double c, const vector4<TYPE>& v)
{
	return vector4<TYPE>(c * v[0], c * v[1], c * v[2], c * v[3]);
}

typedef vector4<int> vector4i;
typedef vector4<float> vector4f;
typedef vector4<double> vector4d;

typedef vector4<int> Vec4i;
typedef vector4<float> Vec4f;
typedef vector4<double> Vec4d;


}	// gm
}

#endif // gm_Vector4_h
