#ifndef x3d_CoordinateInterpolator_h
#define x3d_CoordinateInterpolator_h

namespace System
{
namespace x3d
{

class X3DEXT CoordinateInterpolator : 
	public X3DInterpolatorNode
{
public:
	CTOR CoordinateInterpolator();

	virtual void OnFieldChanged(X3DField* pField) override;

	static NodeType s_nodeType;

protected:

	MFVec3f* m_keyValue;
	MFVec3f* m_valueChanged;
};

}	// x3d
}

#endif // x3d_CoordinateInterpolator_h
