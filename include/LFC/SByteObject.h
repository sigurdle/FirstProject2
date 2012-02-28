namespace System
{

// NOTE, the value of the object is deduced from the address of the object

class LFCEXT SByteObject : public Object
{
public:

	typedef signed char value_t;

	virtual Type* GetPrimitiveType() const override
	{
		return typeid(signed char);
	}

	virtual String ToString() override;

	inline sbyte GetValue() const throw()
	{
		return sbyte(this - &s_values[0]);
	}

	inline operator sbyte () const throw()
	{
		return sbyte(this - &s_values[0]);
	}

	static SByteObject* GetObject(sbyte value)
	{
		return &s_values[(ubyte)value];
	}

	static int GetValueFrom(Object* obj)
	{
		if (obj >= &s_values[0] && obj < &s_values[256])
		{
			return (sbyte)((SByteObject*)obj - &s_values[0]);
		}

		return 0xffff;
	}

private:

	CTOR SByteObject()
	{
	}

	CTOR SByteObject(const SByteObject&);
	SByteObject& operator=(const SByteObject&);

	static SByteObject s_values[256];	// 0 .. 255
};

}	// System
