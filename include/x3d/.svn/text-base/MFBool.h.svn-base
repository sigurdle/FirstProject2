#ifndef x3d_MFBool_h
#define x3d_MFBool_h

namespace System
{
namespace x3d
{

class X3DEXT MFBool : public X3DArrayField
{
public:

	static const FieldType fieldtype = FieldType_MFBool;
	static const bool isSingleValue = false;
	typedef vector<bool> value_t;

	CTOR MFBool(X3DNode* ownerNode) : X3DArrayField(ownerNode)
	{
	}

	virtual FieldType getFieldType() const override
	{
		return fieldtype;
	}

	virtual void CopyFrom(X3DField* pFrom)
	{
		ASSERT(m_items.GetSize() == 0);

		for (size_t i = 0; i < static_cast<MFBool*>(pFrom)->m_items.GetSize(); i++)
		{
			bool v = static_cast<MFBool*>(pFrom)->m_items[i];
			m_items.Add(v);
		}
	}

	bool get1Value(size_t index)
	{
		if (index < m_items.GetSize())
		{
			return m_items[index];
		}
		else
		{
			THROW(-1);
		}
	}
	void append1Value(bool value)
	{
		m_items.Add(value);
	}
// X3DArrayField
	size_t get_size() const
	{
		return m_items.GetSize();
	}

public:

	vector<bool> m_items;
};

}	// x3d
}

#endif // x3d_MFBool_h
