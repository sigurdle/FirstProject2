#ifndef x3d_MFRotation_h
#define x3d_MFRotation_h

namespace System
{
namespace x3d
{

class X3DEXT MFRotation : public X3DArrayField
{
public:
	CTOR MFRotation(X3DNode* ownerNode);

	virtual FieldType getFieldType() const
	{
		return FieldType_MFRotation;
	}

	AxisAngle get1Value(size_t index);
	void set1Value(size_t index, const AxisAngle& value);

	void append1Value(const float value[4]);
	void append1Value(const AxisAngle& value);

	virtual void CopyFrom(X3DField* pFrom);

// X3DArrayField
	size_t get_size() const;

public:

	vector<AxisAngle> m_items;
};

}	// x3d
}	// System

#endif // x3d_MFRotation_h
