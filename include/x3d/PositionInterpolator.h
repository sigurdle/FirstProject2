#ifndef x3d_PositionInterpolator_h
#define x3d_PositionInterpolator_h

namespace System
{
namespace x3d
{

class X3DEXT PositionInterpolator : public X3DInterpolatorNode
{
public:
	CTOR PositionInterpolator();

	X3DMFIELD(MFVec3f, keyValue, KeyValue)
	X3DSFIELD(SFVec3f, value_changed, valueChanged)

	virtual void OnFieldChanged(X3DField* pField) override;

	X3DNODE(PositionInterpolator, X3DInterpolatorNode)
};

}	// x3d
}

#endif // x3d_PositionInterpolator_h
