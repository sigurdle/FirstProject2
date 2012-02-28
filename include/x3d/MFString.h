#ifndef x3d_MFString_h
#define x3d_MFString_h

namespace System
{
namespace x3d
{

class X3DEXT MFString : public X3DArrayField
{
public:

	static const FieldType fieldtype = FieldType_MFString;
	typedef vector<String> value_t;

	CTOR MFString(X3DNode* ownerNode);
	CTOR MFString(TypedX3DFieldDefinition<MFString>* fieldDef, X3DNode* ownerNode);

	CTOR MFString(X3DFieldDefinition* def, X3DNode* ownerNode, StringIn item0);
	CTOR MFString(X3DFieldDefinition* def, X3DNode* ownerNode, StringIn item0, StringIn item1);

	virtual FieldType getFieldType() const override
	{
		return fieldtype;
	}

	void append1Value(StringIn value);

// X3DArrayField
	size_t get_size() const throw()
	{
		return m_items.size();
	}

	void clear();

	String get1Value(size_t index) throw(ArgumentOutOfRangeException);

	virtual IO::TextWriter& WriteValuesToStream(IO::TextWriter& stream) override;

	virtual void CopyFrom(X3DField* pFrom);

protected:

	vector<String> m_items;
};

}	// x3d
}

#endif // x3d_MFString_h
