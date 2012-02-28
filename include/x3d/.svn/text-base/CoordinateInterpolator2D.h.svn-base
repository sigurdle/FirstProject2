#ifndef x3d_CoordinateInterpolator2D_h
#define x3d_CoordinateInterpolator2D_h

namespace System
{
namespace x3d
{

class X3DEXT CoordinateInterpolator2D : 
	public X3DInterpolatorNode
{
public:
	CTOR CoordinateInterpolator2D();

	virtual void OnFieldChanged(X3DField* pField) override;

	X3DMFIELD(MFVec2f, keyValue, KeyValue)
	X3DMFIELD(MFVec2f, value_changed, ValueChanged)

	X3DNODE(CoordinateInterpolator2D, X3DInterpolatorNode)
};

}	// x3d
}	// System

#endif // x3d_CoordinateInterpolator2D_h
