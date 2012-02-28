namespace System
{

class LFCEXT FloatObject : public Object
{
public:

	String ToString() override;

	virtual Type* GetPrimitiveType() const override
	{
		return typeid(float);
	}

	inline float GetValue() const throw()
	{
		return m_value;
	}

	inline operator float () const throw()
	{
		return GetValue();
	}

	static inline FloatObject* get_NegativeInfinity()
	{
		return &s_NegativeInfinity;
	}

	static inline FloatObject* get_PositiveInfinity()
	{
		return &s_PositiveInfinity;
	}

	static inline FloatObject* get_NaN()
	{
		return &s_NaN;
	}

	static inline FloatObject* get_Zero()
	{
		return &s_Zero;
	}

	static inline FloatObject* get_NegativeZero()
	{
		return &s_NegativeZero;
	}

	static inline FloatObject* get_One()
	{
		return &s_One;
	}

	static FloatObject* GetObject(float value);

	static constexpr float get_MinValue() { return FLT_MIN; }
#ifndef __LERSTAD__
	static constexpr float get_MaxValue() { return FLT_MAX; }
	static constexpr float get_Epsilon() { return FLT_EPSILON; }
#endif
//	static constexpr float get_NegativeInfinity() { return float_NegativeInfinity.value; }
//	static constexpr float get_PositiveInfinity() { return float_PositiveInfinity.value; }
	static constexpr float get_NAN() { return float_NaN.value; }

private:

	inline CTOR FloatObject(float value) : m_value(value)
	{
	}

	static FloatObject s_Epsilon;
	static FloatObject s_Zero;
	static FloatObject s_NegativeZero;
	static FloatObject s_One;
	static FloatObject s_NegativeInfinity;
	static FloatObject s_PositiveInfinity;
	static FloatObject s_NaN;

	float m_value;
};

}	// System
