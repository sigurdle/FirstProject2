#ifndef x3d_SFColorRGBA_h
#define x3d_SFColorRGBA_h

namespace System
{
namespace x3d
{

class X3DEXT SFColorRGBA : public X3DField
{
public:
	CTOR SFColorRGBA(X3DNode* ownerNode);
	CTOR SFColorRGBA(X3DNode* ownerNode, Vec4f value);
	CTOR SFColorRGBA(TypedX3DFieldDefinition<SFColorRGBA>* fieldDef, X3DNode* ownerNode);

	virtual FieldType getFieldType() const override
	{
		return fieldtype;
	}

	virtual void CopyFrom(X3DField* pFrom) override;
	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream) override;

	Vec4f getValue() const throw()
	{
		return m_value;
	}

	void getValue(float value[4]) const
	{
		value[0] = m_value[0];
		value[1] = m_value[1];
		value[2] = m_value[2];
		value[3] = m_value[3];
	}

	void setValue(Vec4f value);

	static const FieldType fieldtype = FieldType_SFColorRGBA;
	static const bool isSingleValue = true;
	typedef Vec4f value_t;

public:

	Vec4f m_value;
};

}	// x3d
}	// System

#endif // x3d_SFColorRGBA_h
