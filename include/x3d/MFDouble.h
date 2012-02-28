namespace System
{
namespace x3d
{

class X3DEXT MFDouble : public X3DArrayField
{
public:

	static const FieldType fieldtype = FieldType_MFDouble;
	static const bool isSingleValue = false;
	typedef int32 value_t;

	CTOR MFDouble(X3DNode* ownerNode) : X3DArrayField(ownerNode)
	{
	}

	CTOR MFDouble(TypedX3DFieldDefinition<MFDouble>* fieldDef, X3DNode* ownerNode);

	virtual FieldType getFieldType() const override
	{
		return fieldtype;
	}

	double get1Value(size_t index) const;
	void set1Value(size_t index, double value);
	void append1Value(double value);

	size_t get_size() const override	// X3DArrayField
	{
		return m_items.size();
	}

	virtual void CopyFrom(X3DField* pFrom);

protected:

	vector<double> m_items;
};

}	// x3d
}
