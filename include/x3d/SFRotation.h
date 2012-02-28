#ifndef x3d_SFRotation_h
#define x3d_SFRotation_h

namespace System
{
namespace x3d
{

class X3DEXT SFRotation : public X3DField
{
public:
	CTOR SFRotation(X3DNode* ownerNode);
	CTOR SFRotation(X3DNode* ownerNode, Rotation value);
	CTOR SFRotation(TypedX3DFieldDefinition<SFRotation>* fieldDef, X3DNode* ownerNode);

	virtual FieldType getFieldType() const override
	{
		return fieldtype;
	}

	Rotation getValue() const;
	void getValue(/*[in, out]*/ float value[4]) const;

	void setValue(float const value[4]);
	void setValue(Rotation value);

	virtual void CopyFrom(X3DField* pFrom);

	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream) override;

	static const FieldType fieldtype = FieldType_SFRotation;
	typedef Rotation value_t;

public:

	Rotation m_value;
};

}	// x3d
}

#endif // x3d_SFRotation_h
