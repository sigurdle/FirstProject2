#ifndef x3d_SFFloat_h
#define x3d_SFFloat_h

namespace System
{
namespace x3d
{

class X3DEXT SFFloat : public X3DField
{
public:
	CTOR SFFloat(X3DNode* ownerNode, float value = 0.0f);
	CTOR SFFloat(TypedX3DFieldDefinition<SFFloat>* fieldDef, X3DNode* ownerNode);
	CTOR SFFloat(TypedX3DFieldDefinition<SFFloat>* fieldDef, X3DNode* ownerNode, float value);

	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream);

	virtual FieldType getFieldType() const override
	{
		return FieldType_SFFloat;
	}

	virtual void CopyFrom(X3DField* pFrom)
	{
		m_value = static_cast<SFFloat*>(pFrom)->m_value;
	}

	float getValue() const throw()
	{
		return m_value;
	}
	void setValue(float newVal);

	static const FieldType fieldtype = FieldType_SFFloat;
	typedef float value_t;

public:

	float m_value;
};

}	// x3d
}	// System

#endif // x3d_SFFloat_h
