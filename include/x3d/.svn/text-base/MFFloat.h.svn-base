namespace System
{
namespace x3d
{

class X3DEXT MFFloat : public X3DArrayField
{
public:

	static const FieldType fieldtype = FieldType_MFFloat;
	static const bool isSingleValue = false;
	typedef vector<float> value_t;

	CTOR MFFloat(X3DNode* ownerNode) : X3DArrayField(ownerNode)
	{
	}

	CTOR MFFloat(TypedX3DFieldDefinition<MFFloat>* fieldDef, X3DNode* ownerNode) : X3DArrayField(fieldDef, ownerNode),
		m_items(fieldDef->getDefaultValue())
	{
	}

	CTOR MFFloat(X3DNode* ownerNode, float item0) : X3DArrayField(ownerNode)
	{
		m_items.push_back(item0);
	}

	CTOR MFFloat(X3DNode* ownerNode, float item0, float item1) : X3DArrayField(ownerNode)
	{
		m_items.push_back(item0);
		m_items.push_back(item1);
	}

	CTOR MFFloat(X3DNode* ownerNode, float item0, float item1, float item2) : X3DArrayField(ownerNode)
	{
		m_items.push_back(item0);
		m_items.push_back(item1);
		m_items.push_back(item2);
	}

	CTOR MFFloat(X3DNode* ownerNode, float item0, float item1, float item2, float item3) : X3DArrayField(ownerNode)
	{
		m_items.push_back(item0);
		m_items.push_back(item1);
		m_items.push_back(item2);
		m_items.push_back(item3);
	}

	CTOR MFFloat(X3DNode* ownerNode, float item0, float item1, float item2, float item3, float item4) : X3DArrayField(ownerNode)
	{
		m_items.push_back(item0);
		m_items.push_back(item1);
		m_items.push_back(item2);
		m_items.push_back(item3);
		m_items.push_back(item4);
	}

	CTOR MFFloat(X3DFieldDefinition* fieldDef, X3DNode* ownerNode, float item0, float item1, float item2, float item3) : X3DArrayField(fieldDef, ownerNode)
	{
		m_items.push_back(item0);
		m_items.push_back(item1);
		m_items.push_back(item2);
		m_items.push_back(item3);
	}

	IO::TextWriter& WriteValuesToStream(IO::TextWriter& stream) override;

	virtual FieldType getFieldType() const override
	{
		return fieldtype;
	}

	virtual void CopyFrom(X3DField* pFrom);

	float get1Value(size_t index) const throw(ArgumentOutOfRangeException);
	void set1Value(size_t index, float newVal);
	void append1Value(float value);

	vector<float> getValue() const
	{
		return m_items;
	}

	void setValue(const vector<float>& items)
	{
		m_items = items;
	}

// X3DArrayField
	size_t get_size() const override
	{
		return m_items.size();
	}

public:

	vector<float> m_items;
};

class X3DEXT SFMatrix4f : public X3DArrayField
{
public:

	virtual FieldType getFieldType() const override
	{
		return FieldType_SFMatrix4f;
	}

	gm::matrix4f getValue() const
	{
		return m_value;
	}

	void setValue(const gm::matrix4f& value)
	{
		m_value = value;
		getOwnerNode()->OnFieldChanged(this);
	}

	static const FieldType fieldtype = FieldType_SFMatrix4f;
	static const bool isSingleValue = true;

private:

	gm::matrix4f m_value;
};

class X3DEXT MFMatrix4f : public X3DArrayField
{
public:

	virtual FieldType getFieldType() const override
	{
		return FieldType_MFMatrix4f;
	}

	gm::matrix4f get1Value(unsigned int index) const;

	void set1Value(unsigned int index, const gm::matrix4f& value);

	void append1Value(const gm::matrix4f& value);

// X3DArrayField
	size_t get_size() const
	{
		return m_items.GetSize();
	}

	static const FieldType fieldtype = FieldType_MFMatrix4f;
	static const bool isSingleValue = false;

private:

	vector<gm::matrix4f> m_items;
};

class X3DEXT MFMatrix3f : public X3DArrayField
{
public:

	virtual FieldType getFieldType() const override
	{
		return FieldType_MFMatrix3f;
	}

	gm::matrix3f get1Value(unsigned int index) const;

	void set1Value(unsigned int index, const gm::matrix3f& value);

	void append1Value(const gm::matrix3f& value);

// X3DArrayField
	size_t get_size() const override
	{
		return m_items.GetSize();
	}

	static const FieldType fieldtype = FieldType_MFMatrix3f;
	static const bool isSingleValue = false;

private:

	vector<gm::matrix3f> m_items;
};

}	// x3d
}	// System
