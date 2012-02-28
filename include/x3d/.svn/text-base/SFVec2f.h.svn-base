#ifndef x3d_SFVec2f_h
#define x3d_SFVec2f_h

namespace System
{
namespace x3d
{

class X3DEXT SFVec2f : public X3DField
{
public:
	CTOR SFVec2f(const SFVec2f& other);
	CTOR SFVec2f(X3DNode* ownerNode, Vec2f value = Vec2f());
	CTOR SFVec2f(X3DFieldDefinition* fieldDef, X3DNode* ownerNode, Vec2f value = Vec2f());

	virtual FieldType getFieldType() const override
	{
		return fieldtype;
	}

	Vec2f getValue() const
	{
		return m_value;
	}

	void setValue(Vec2f value)
	{
		m_value = value;
		m_ownerNode->OnFieldChanged(this);
	}

	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream) override;

	virtual void CopyFrom(X3DField* pFrom)
	{
		m_value = static_cast<SFVec2f*>(pFrom)->m_value;
	}

	static const FieldType fieldtype = FieldType_SFVec2f;
	typedef Vec2f value_t;

public:

	Vec2f m_value;
};

}	// x3d
}

#endif //  x3d_SFVec2f_h
