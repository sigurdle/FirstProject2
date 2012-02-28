#ifndef x3d_MFInt32_h
#define x3d_MFInt32_h

namespace System
{
namespace x3d
{

class X3DEXT MFInt32 : public X3DArrayField
{
public:

	static const FieldType fieldtype = FieldType_MFInt32;
	static const bool isSingleValue = false;
	typedef int32 value_t;

	CTOR MFInt32(X3DNode* ownerNode);
	CTOR MFInt32(TypedX3DFieldDefinition<MFInt32>* fieldDef, X3DNode* ownerNode);

	virtual IO::TextWriter& WriteValuesToStream(IO::TextWriter& stream) override;

	virtual FieldType getFieldType() const override
	{
		return fieldtype;
	}

	virtual void CopyFrom(X3DField* pFrom);

	int32 get1Value(size_t index) const throw (ArgumentOutOfRangeException*);
	void append1Value(int32 value);

// X3DArrayField
	size_t get_size() const
	{
		return m_items.GetSize();
	}

public:

	vector<int32> m_items;
};

}	// x3d
}	// System

#endif // x3d_MFInt32_h
