namespace System
{

class LFCEXT Int64Object : public ValueType
{
public:

	typedef long long value_t;

	String ToString() override;

	virtual Type* GetPrimitiveType() const override
	{
		return typeid(long long);
	}

	inline long long GetValue() const throw()
	{
		return m_value;
	}

	inline operator long long () const throw()
	{
		return m_value;
	}

	static Int64Object* GetObject(long long value);

#ifndef __LERSTAD__
	static const long long MinValue = _I64_MIN;
	static const long long MaxValue = _I64_MAX;
#endif

private:

	inline CTOR Int64Object(long long value) : m_value(value)
	{
	}

	long long m_value;

	static Int64Object s_values[];	// -1 .. 256
	static Int64Object s_minValue;
	static Int64Object s_maxValue;
};

}	// System
