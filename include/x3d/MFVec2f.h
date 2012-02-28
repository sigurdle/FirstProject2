#ifndef x3d_MFVec2f_h
#define x3d_MFVec2f_h

namespace System
{
namespace x3d
{

class X3DEXT MFVec2f : public X3DArrayField
{
public:
	CTOR MFVec2f(X3DNode* ownerNode) : X3DArrayField(ownerNode)
	{
	}

	virtual FieldType getFieldType() const
	{
		return fieldtype;
	}

	virtual IO::TextWriter& WriteValuesToStream(IO::TextWriter& stream) override;

	virtual void CopyFrom(X3DField* pFrom);

	Vec2f get1Value(size_t index) throw(ArgumentOutOfRangeException)
	{
		if (index >= m_items.size())
		{
			raise(ArgumentOutOfRangeException());
		}

		return m_items[index];
	}

	void append1Value(const float value[2]);

	// X3DArrayField
	size_t get_size() const
	{
		return m_items.size();
	}

	static const FieldType fieldtype = FieldType_MFVec2f;
	static const bool isSingleValue = false;
	typedef vector<Vec2f> value_t;

public:

	vector<Vec2f> m_items;
};

}	// x3d
}	// System

#endif // x3d_MFVec2f_h
