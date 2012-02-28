namespace System
{

class LFCEXT UInt64Object : public ValueType
{
public:

	typedef unsigned long long value_t;

	String ToString() override;

	virtual Type* GetPrimitiveType() const override
	{
		return typeid(unsigned long long);
	}

	inline unsigned long long GetValue() const throw()
	{
		return m_value;
	}

	inline operator unsigned long long () const throw()
	{
		return m_value;
	}

	static UInt64Object* GetObject(unsigned long long value);

	static const unsigned long long MinValue = 0;
#ifndef __LERSTAD__
	static const unsigned long long MaxValue = _UI64_MAX;
#endif

private:

	inline CTOR UInt64Object(unsigned long long value) : m_value(value)
	{
	}

	unsigned long long m_value;

	static UInt64Object s_values[];	// 0 .. 256
	static UInt64Object s_maxValue; 
};

}	// System
