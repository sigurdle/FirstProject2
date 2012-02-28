namespace System
{

// NOTE, the value of the object is deduced from the address of the object

class LFCEXT UByteObject : public Object
{
public:

	virtual Type* GetPrimitiveType() const override
	{
		return typeid(unsigned char);
	}

	virtual String ToString() override;

	inline ubyte GetValue() const throw()
	{
		__assume(this - &s_values[0] < 256);
		return ubyte(this - &s_values[0]);
	}

	inline operator ubyte () const throw()
	{
		__assume(this - &s_values[0] < 256);
		return ubyte(this - &s_values[0]);
	}

	static UByteObject* GetObject(ubyte value)
	{
		return &s_values[value];
	}

	static int GetValueFrom(Object* obj)
	{
		if (obj >= &s_values[0] && obj < &s_values[256])
		{
			return ubyte((UByteObject*)obj - &s_values[0]);
		}

		return -1;
	}

private:

	CTOR UByteObject()
	{
	}

	CTOR UByteObject(const UByteObject&);
	UByteObject& operator=(const UByteObject&);

	static UByteObject s_values[256];	// 0 .. 255
};

}	// System
