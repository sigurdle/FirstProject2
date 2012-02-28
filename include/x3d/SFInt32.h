#ifndef x3d_SFInt32_h
#define x3d_SFInt32_h

namespace System
{
namespace x3d
{

class X3DEXT SFInt32 : public X3DField
{
public:
	CTOR SFInt32(X3DFieldDefinition* fieldDef, X3DNode* ownerNode, int32 value = 0);

	virtual FieldType getFieldType() const
	{
		return FieldType_SFInt32;
	}

	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream);

	virtual void CopyFrom(X3DField* pFrom)
	{
		m_value = static_cast<SFInt32*>(pFrom)->m_value;
	}

	int32 getValue() const
	{
		return m_value;
	}

	void setValue(int32 newVal);

	static const FieldType fieldtype = FieldType_SFInt32;
	typedef int32 value_t;

public:

	int32 m_value;
};

}	// x3d
}

#endif // x3d_SFInt32_h
