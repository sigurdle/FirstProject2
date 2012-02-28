#ifndef x3d_ScalarInterpolator_h
#define x3d_ScalarInterpolator_h

namespace System
{
namespace x3d
{

class X3DEXT ScalarInterpolator : 
	public X3DInterpolatorNode
{
public:
	CTOR ScalarInterpolator();

	X3DMFIELD(MFFloat, keyValue, KeyValue)
	X3DSFIELD(SFFloat, value_changed, ValueChanged)

	X3DNODE(ScalarInterpolator, X3DInterpolatorNode)

	virtual void OnFieldChanged(X3DField* pField) override;
};

}	// x3d
}	// System

#endif // x3d_ScalarInterpolator_h
