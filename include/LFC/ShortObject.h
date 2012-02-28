namespace System
{

class LFCEXT ShortObject : public ValueType
{
public:

	String ToString() override;

	virtual Type* GetPrimitiveType() const override
	{
		return typeid(short);
	}

	inline short GetValue() const throw()
	{
		return m_value;
	}

	inline operator short () const throw()
	{
		return m_value;
	}

	static ShortObject* GetObject(short value);

	static const short MinValue = _I16_MIN;
	static const short MaxValue = _I16_MAX;

private:

	inline CTOR ShortObject(short value) : m_value(value)
	{
	}

	short m_value;

	static ShortObject s_values[];	// -1 .. 256
};

}	// System
