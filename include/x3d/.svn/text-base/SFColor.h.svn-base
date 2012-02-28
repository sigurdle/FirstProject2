#ifndef x3d_SFColor_h
#define x3d_SFColor_h

namespace System
{
namespace x3d
{

class X3DEXT SFColor : public X3DField
{
public:
	CTOR SFColor(X3DNode* ownerNode);
	CTOR SFColor(TypedX3DFieldDefinition<SFColor>* fieldDef, X3DNode* ownerNode);
	CTOR SFColor(TypedX3DFieldDefinition<SFColor>* fieldDef, X3DNode* ownerNode, Vec3f value);

	virtual FieldType getFieldType() const override
	{
		return FieldType_SFColor;
	}

	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream);

	virtual void CopyFrom(X3DField* pFrom);

	Vec3f getValue() const throw()
	{
		return m_value;
	}

	void getValue(/*[in, out]*/ float value[3]) const
	{
		value[0] = m_value[0];
		value[1] = m_value[1];
		value[2] = m_value[2];
	}

	void setValue(/*[in]*/ const float value[3]);
	void setValue(Vec3f value);

	static const FieldType fieldtype = FieldType_SFColor;
	static const bool isSingleValue = true;
	typedef Vec3f value_t;

public:

	Vec3f m_value;
};

}	// x3d
}	// System

#endif // x3d_SFColor_h
