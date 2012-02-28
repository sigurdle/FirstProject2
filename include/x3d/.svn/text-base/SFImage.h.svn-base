#ifndef x3d_SFImage_h
#define x3d_SFImage_h

namespace System
{
namespace x3d
{

class X3DEXT SFImage :
	public X3DField
{
public:

	static const FieldType fieldtype = FieldType_SFImage;
	static const bool isSingleValue = true;
	typedef String value_t;

	CTOR SFImage(X3DNode* ownerNode);
	CTOR SFImage(TypedX3DFieldDefinition<SFImage>* fieldDef, X3DNode* ownerNode);

	String getValue() const
	{
		return "";//m_data;
	}

	void setValue(String data);

	virtual FieldType getFieldType() const override
	{
		return fieldtype;
	}

	virtual void CopyFrom(X3DField* pFrom) override;
	virtual IO::TextWriter& WriteValueToStream(IO::TextWriter& stream) override;

	ubyte* m_data;
	int m_width;
	int m_height;
	int m_components;
};

}	// x3d
}

#endif // x3d_SFImage_h
