#ifndef x3d_MFVec3f_h
#define x3d_MFVec3f_h

namespace System
{
namespace x3d
{

class X3DEXT MFVec3f : public X3DArrayField
{
public:

	static const FieldType fieldtype = FieldType_MFVec3f;
	typedef vector<Vec3f> value_t;

	CTOR MFVec3f(X3DNode* ownerNode) : X3DArrayField(ownerNode)
	{
	}

	CTOR MFVec3f(TypedX3DFieldDefinition<MFVec3f>* fieldDef, X3DNode* ownerNode);

	virtual FieldType getFieldType() const
	{
		return fieldtype;
	}

	Vec3f get1Value(size_t index) const;
	void append1Value(Vec3f value);

	size_t get_size() const	// X3DArrayField
	{
		return m_items.GetSize();
	}

	virtual void CopyFrom(X3DField* pFrom) override;
	virtual IO::TextWriter& WriteValuesToStream(IO::TextWriter& stream) override;

public:

	vector<Vec3f> m_items;
};

}	// x3d
}	// System

#endif // x3d_MFVec3f_h
