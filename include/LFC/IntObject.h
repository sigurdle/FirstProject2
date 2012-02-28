namespace System
{

class LFCEXT IntObject : public ValueType
{
public:

	String ToString() override;

	virtual Type* GetPrimitiveType() const override
	{
		return typeid(int);
	}

	inline int GetValue() const throw()
	{
		return m_value;
	}

	inline operator int () const throw()
	{
		return m_value;
	}

	static IntObject* GetObject(int value);

	static const int MinValue = INT_MIN;
	static const int MaxValue = INT_MAX;

private:

	inline CTOR IntObject(int value) : m_value(value)
	{
	}

	int m_value;

	static IntObject s_values[];	// -1 .. 256
};

typedef IntObject IntObject32;

}	// System
