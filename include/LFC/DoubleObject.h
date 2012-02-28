namespace System
{

class LFCEXT DoubleObject : public ValueType
{
public:

	String ToString() override;

	virtual Type* GetPrimitiveType() const override
	{
		return typeid(double);
	}

	inline double GetValue() const throw()
	{
		return m_value;
	}

	inline operator double () const throw()
	{
		return m_value;
	}

	static inline DoubleObject* get_NegativeInfinity()
	{
		return &s_NegativeInfinity;
	}

	static inline DoubleObject* get_PositiveInfinity()
	{
		return &s_PositiveInfinity;
	}

	static inline DoubleObject* get_NaN()
	{
		return &s_NaN;
	}

	static inline DoubleObject* get_Zero()
	{
		return &s_Zero;
	}

	static inline DoubleObject* get_NegativeZero()
	{
		return &s_NegativeZero;
	}

	static inline DoubleObject* get_One()
	{
		return &s_One;
	}

	static DoubleObject* GetObject(double value);

	static constexpr double get_MinValue() { return DBL_MIN; }
#ifndef __LERSTAD__
	static constexpr double get_MaxValue() { return DBL_MAX; }
	static constexpr double get_Epsilon() { return DBL_EPSILON; }
#endif
//	static constexpr double get_NegativeInfinity() { return double_NegativeInfinity.value; }
//	static constexpr double get_PositiveInfinity() { return double_PositiveInfinity.value; }
	static constexpr double get_NAN() { return double_NaN.value; }

private:

	inline CTOR DoubleObject(double value) : m_value(value)
	{
	}

	static DoubleObject s_Zero;
	static DoubleObject s_NegativeZero;
	static DoubleObject s_One;
	static DoubleObject s_NegativeInfinity;
	static DoubleObject s_PositiveInfinity;
	static DoubleObject s_NaN;
	static DoubleObject s_Epsilon;
	static DoubleObject s_MinValue;
	static DoubleObject s_MaxValue;

	double m_value;
};

}	// System
