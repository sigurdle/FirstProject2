namespace System
{

class LFCEXT UShortObject : public ValueType
{
public:

	typedef short value_t;

	String ToString() override;

	virtual Type* GetPrimitiveType() const override
	{
		return typeid(unsigned short);
	}

	inline unsigned short GetValue() const throw()
	{
		return m_value;
	}

	inline operator unsigned short () const throw()
	{
		return m_value;
	}

	static UShortObject* GetObject(unsigned short value);

	static const unsigned short MinValue = 0;
	static const unsigned short MaxValue = _UI16_MAX;

private:

	inline CTOR UShortObject(unsigned short value) : m_value(value)
	{
	}

	unsigned short m_value;

	static UShortObject s_values[];	// -1 .. 256
};

}	// System
