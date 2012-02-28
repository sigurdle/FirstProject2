namespace System
{

class LFCEXT UIntObject : public ValueType
{
public:

	String ToString() override;

	virtual Type* GetPrimitiveType() const override
	{
		return typeid(unsigned int);
	}

	inline unsigned int GetValue() const throw()
	{
		return m_value;
	}

	inline operator unsigned int () const throw()
	{
		return m_value;
	}

	static UIntObject* GetObject(unsigned int value);

	static const unsigned int MinValue = 0;
	static const unsigned int MaxValue = UINT_MAX;

private:

	inline CTOR UIntObject(unsigned int value) : m_value(value)
	{
	}

	unsigned int m_value;

	static UIntObject s_values[];	// -1(0xffffffff) .. 256
};

typedef UIntObject UInt32;

}	// System
