namespace System
{

class LFCEXT BoolObject : public Object
{
public:

	virtual Type* GetPrimitiveType() const override
	{
		return typeid(bool);
	}

	virtual String ToString() override;

	inline bool GetValue() const throw()
	{
		ptrdiff_t diff = (this - &s_values[0]);
		__analysis_assume(diff == 0 || diff == 1);
	// __assume doesn't seem to optimize
		return diff&1;
	}

	inline operator bool () const throw()
	{
		ptrdiff_t diff = (this - &s_values[0]);
		__analysis_assume(diff == 0 || diff == 1);
	// __assume doesn't seem to optimize
		return diff&1;
	}

	static inline BoolObject* GetObject(bool value)
	{
		return &s_values[value];
	}

	static inline BoolObject* get_False()
	{
		return &s_values[0];
	}

	static inline BoolObject* get_True()
	{
		return &s_values[1];
	}

private:

	CTOR BoolObject()
	{
	}

	CTOR BoolObject(const BoolObject&);
	BoolObject& operator=(const BoolObject&);

	static BoolObject s_values[2];
};

}	// System
