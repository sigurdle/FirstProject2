#ifndef x3d_SFBool_h
#define x3d_SFBool_h

namespace System
{
namespace x3d
{

class X3DEXT SFBool : public X3DField
{
public:
	CTOR SFBool(X3DNode* ownerNode, bool value = false);
	CTOR SFBool(TypedX3DFieldDefinition<SFBool>* fieldDef, X3DNode* ownerNode);
	CTOR SFBool(TypedX3DFieldDefinition<SFBool>* fieldDef, X3DNode* ownerNode, bool value);

	virtual FieldType getFieldType() const override
	{
		return fieldtype;
	}

	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream) override;

	virtual void CopyFrom(X3DField* pFrom) override;

	bool getValue() const
	{
		return m_value;
	}
	void setValue(bool value);

	static const FieldType fieldtype = FieldType_SFBool;
	typedef bool value_t;

//private:
public:

	bool m_value;
};

}	// x3d
}	// System

#endif // x3d_SFBool_h
