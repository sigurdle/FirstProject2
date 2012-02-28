namespace System
{

class LFCEXT PointerType : public Type
{
public:
	CTOR PointerType();
	CTOR PointerType(Type* pPointerTo);

	virtual Type_type get_Kind() const throw() override
	{
		return type_pointer;
	}

	Type* get_Type() const throw()
	{
		return m_pPointerTo;
	}

	virtual uint get_sizeof(uint sizeofptr = 0) const override;

	virtual String ToString() override;
	virtual IO::TextWriter& Write(IO::TextWriter& stream) const override;
	virtual Type* Clone() const;
	bool Equals(const PointerType& other) const;

	/*
	StringStream Write() const
	{
		StringStream stream;
		return Write(stream);
	}
	*/

	virtual Class_Type GetSerializableType() const override;
	virtual void Load(TypeArchive& stream) override;
	virtual void Store(TypeArchive& stream) const override;

	virtual bool IsConst() const override;
	virtual bool IsVolatile() const override;

	Type* m_pPointerTo;

	static unsigned int default_sizeofptr;
};

}	// System
