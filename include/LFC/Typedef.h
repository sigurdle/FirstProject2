namespace System
{

class LFCEXT Typedef : public NamedType
{
public:
	CTOR Typedef();
	CTOR Typedef(StringIn name, Type* pType);

	virtual Type_type get_Kind() const throw() override
	{
		return type_typedef;
	}

	Type* get_Type() const
	{
		return m_pType;
	}

	virtual ClassType* AsClass() override;
	virtual Type* GetStripped() override;
	virtual Type* GetPointerTo() const override;
	virtual bool IsOfType(Type* pType) const override;

	virtual FunctionType* AsFunction() override
	{
		if (m_pType == nullptr) return nullptr;
		return m_pType->AsFunction();
	}

	virtual uint get_sizeof(uint sizeofptr = 0) const override;

	virtual String ToString() override;
	virtual IO::TextWriter& Write(IO::TextWriter& stream) const override;
	virtual Type* Clone() const override;

	virtual bool IsConst() const override;
	virtual bool IsVolatile() const override;

	virtual Class_Type GetSerializableType() const override;
	virtual void Load(TypeArchive& ar) override;
	virtual void Store(TypeArchive& ar) const override;

	static Typedef* CreateFromArchive(TypeArchive& ar, uint32 id);

public:

	Type* m_pType;
};

}	// System
