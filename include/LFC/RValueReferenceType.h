namespace System
{

class LFCEXT RValueReferenceType : public Type
{
public:
	CTOR RValueReferenceType();
	CTOR RValueReferenceType(Type* pPointerTo);

	virtual Type_type get_Kind() const throw() override
	{
		return type_rvalue_reference;
	}

	Type* get_Type() const throw()
	{
		return m_pPointerTo; 
	}

	virtual Type* GetPointerTo() const override
	{
		return m_pPointerTo;
	}

	virtual uint get_sizeof(uint sizeofptr = 0) const override;

	virtual String ToString() override;
	virtual IO::TextWriter& Write(IO::TextWriter& stream) const override;
	virtual Type* Clone() const override;
	bool Equals(const ReferenceType& other) const;

	virtual Class_Type GetSerializableType() const override;
	virtual void Load(TypeArchive& stream) override;
	virtual void Store(TypeArchive& stream) const override;

	virtual bool IsConst() const override;
	virtual bool IsVolatile() const override;

	Type* m_pPointerTo;
};

}	// System
