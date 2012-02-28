#ifndef x3d_OrientationInterpolator_h
#define x3d_OrientationInterpolator_h

namespace System
{
namespace x3d
{

class X3DEXT OrientationInterpolator : 
	public X3DInterpolatorNode
{
public:
	CTOR OrientationInterpolator();

	virtual MFRotation* get_keyValueField()
	{
		return m_keyValue;
	}

	virtual SFRotation* get_valueChangedField()
	{
		return m_valueChanged;
	}

	virtual void OnFieldChanged(X3DField* pField) override;

	X3DNODE(OrientationInterpolator, X3DInterpolatorNode)

protected:

	MFRotation* m_keyValue;
	SFRotation* m_valueChanged;
};

}	// x3d
}

#endif // x3d_OrientationInterpolator_h
