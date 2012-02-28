#ifndef x3d_SFDouble_h
#define x3d_SFDouble_h

namespace System
{
namespace x3d
{

class X3DEXT SFDouble : public X3DField
{
public:
	CTOR SFDouble(X3DNode* ownerNode);
	CTOR SFDouble(X3DNode* ownerNode, double value);

	virtual FieldType getFieldType() const override
	{
		return FieldType_SFDouble;
	}

	double getValue() const throw()
	{
		return m_value;
	}
	void setValue(double newVal);

	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream) override;

	virtual void CopyFrom(X3DField* pFrom);

	static const FieldType fieldtype = FieldType_SFDouble;
	typedef double value_t;

public:

	double m_value;
};

}	// x3d
}	// System

#endif // x3d_SFDouble_h
