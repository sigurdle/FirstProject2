#ifndef x3d_MFColor_h
#define x3d_MFColor_h

namespace System
{
namespace x3d
{

class X3DEXT MFColor : public X3DArrayField
{
public:

	static const FieldType fieldtype = FieldType_MFColor;
	static const bool isSingleValue = false;
	typedef vector<Vec3f> value_t;

	CTOR MFColor(X3DNode* ownerNode);
	CTOR MFColor(TypedX3DFieldDefinition<MFColor>* fieldDef, X3DNode* ownerNode);

	virtual FieldType getFieldType() const override
	{
		return fieldtype;
	}

	Vec3f get1Value(size_t index) const throw (ArgumentOutOfRangeException*);
	void set1Value(size_t index, Vec3f value) throw (ArgumentOutOfRangeException*);
	void append1Value(Vec3f value);

	size_t get_size() const override;	// X3DArrayField

	virtual void CopyFrom(X3DField* pFrom) override;
	virtual IO::TextWriter& WriteValuesToStream(IO::TextWriter& stream) override;

public:

	vector<Vec3f> m_items;
};

}	// x3d
}	// System

#endif // x3d_MFColor_h
