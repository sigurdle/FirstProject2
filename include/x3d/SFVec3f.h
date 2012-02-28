#ifndef x3d_SFVec3f_h
#define x3d_SFVec3f_h

namespace System
{
namespace x3d
{

class X3DEXT SFVec3f : public X3DField
{
public:
	CTOR SFVec3f(X3DNode* owner);
	CTOR SFVec3f(TypedX3DFieldDefinition<SFVec3f>* def, X3DNode* owner);
	CTOR SFVec3f(TypedX3DFieldDefinition<SFVec3f>* def, X3DNode* owner, Vec3f value);

	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream) override;

	virtual FieldType getFieldType() const override
	{
		return FieldType_SFVec3f;
	}

	virtual void CopyFrom(X3DField* pFrom) override
	{
		m_value = static_cast<SFVec3f*>(pFrom)->m_value;
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

	Vec3f getValue() const
	{
		return m_value;
	}

	void getValue(/*[in, out]*/ float value[3]) const
	{
		m_value.copyTo(value);
	}

	void setValue(Vec3f value);
	void setValue(float x, float y, float z);

	/*
	static inline FieldType fieldtype()
	{
		return FieldType_SFVec3f;
	}

	static inline bool isSingleValue()
	{
		return true;
	}
	*/
	static const FieldType fieldtype = FieldType_SFVec3f;
	static const bool isSingleValue = true;

	typedef Vec3f value_t;

public:

	Vec3f m_value;
};

class X3DEXT _SFNode : public Expressive::_Object
{
public:

	CTOR _SFNode(const Expressive::expression& exp) : Expressive::_Object(exp)
	{
	}
};

class X3DEXT _Vec3f : public _SFNode
{
public:

	CTOR _Vec3f(const Expressive::expression& exp) : _SFNode(exp)
	{
	}

	/*
	Expressive::typed_expression<float> getY() const
	{
		return new GetPropertyExpression(_this(), GetDispatch(typeid(Object).GetType()->GetClass())->GetProperty("GetType"));

		return getProperty();
	}
	*/
};

}	// x3d
}

#endif // x3d_SFVec3f_h
