namespace System
{

class LFCEXT Namespace : public NamespaceType
{
public:
	CTOR Namespace();

	virtual Type_type get_Kind() const override
	{
		return type_namespace;
	}

	virtual uint get_sizeof(uint sizeofptr = 0) const override
	{
		return ~0;
	}

	virtual Class_Type GetSerializableType() const override;

	virtual String ToString() override;

	virtual void Load(TypeArchive& ar) override;
	virtual void Store(TypeArchive& ar) const override;

	void Load2(TypeArchive& ar);

	virtual Type* Clone() const
	{
		ASSERT(0);
		return NULL;
	}

	friend inline TypeArchive& operator >> (TypeArchive& ar, Namespace* & object)
	{
		TypeSerializable* p;
		ar >> p;
		if (p)
		{
			object = dynamic_cast<Namespace*>(p);
			if (object == NULL)
			{
				raise(IO::IOException("Archive - not namespace"));
			}
		}
		else
			object = NULL;

		return ar;
	}

	static Namespace* CreateFromArchive(TypeArchive& ar, uint32 id);
	static Namespace* CreateFromArchive(TypeArchive& ar, TypeLib* typelib, StringIn qname, uint32 id);
};

}	// System
