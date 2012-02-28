#ifndef x3d_SFTime_h
#define x3d_SFTime_h

namespace System
{
namespace x3d
{

class X3DEXT SFTime : public X3DField
{
public:

	static const FieldType fieldtype = FieldType_SFTime;
	typedef double value_t;

	CTOR SFTime(X3DNode* ownerNode, double value = 0);
	CTOR SFTime(TypedX3DFieldDefinition<SFTime>* fieldDef, X3DNode* ownerNode);

	virtual FieldType getFieldType() const override
	{
		return fieldtype;
	}

	double getValue() const
	{
		return m_value;
	}
	void setValue(double newVal);

	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream);

	virtual void CopyFrom(X3DField* pFrom);

public:

	double m_value;
};

}	// x3d
}

#endif // x3d_SFTime_h
