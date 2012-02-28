#ifndef x3d_SFVec4f_h
#define x3d_SFVec4f_h

namespace System
{
namespace x3d
{

class X3DEXT SFVec4f : public X3DField
{
public:
	CTOR SFVec4f(X3DNode* owner);
	CTOR SFVec4f(TypedX3DFieldDefinition<SFVec4f>* def, X3DNode* owner);
	CTOR SFVec4f(TypedX3DFieldDefinition<SFVec4f>* def, X3DNode* owner, Vec4f value);

	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream) override;

	virtual FieldType getFieldType() const override
	{
		return FieldType_SFVec4f;
	}

	virtual void CopyFrom(X3DField* pFrom) override
	{
		m_value = static_cast<SFVec4f*>(pFrom)->getValue();
		/*
		if (m_fieldName == WSTR("scale"))
		{
			if (m_value[0] == 0 && m_value[1] == 0 && m_value[2] == 0)
			{
				MessageBeep(-1);
			}
		}
		*/
	}

	Vec4f getValue() const
	{
		return m_value;
	}

	void setValue(Vec4f value);
	void setValue(float x, float y, float z, float w);

	static const FieldType fieldtype = FieldType_SFVec4f;
	static const bool isSingleValue = true;

	typedef Vec4f value_t;

private:

	Vec4f m_value;
};


}	// x3d
}	// System

#endif // x3d_SFVec4f_h
