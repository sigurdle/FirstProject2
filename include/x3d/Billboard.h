#ifndef x3d_Billboard_h
#define x3d_Billboard_h

namespace System
{
namespace x3d
{

class X3DEXT Billboard : 
	public X3DGroupingNode, //	public X3DBoundedObject,
	public RenderImplImpl
{
public:
	CTOR Billboard();

	virtual void Draw(X3DDrawContext* pDC) override;

	X3DSFIELD(SFVec3f, axisOfRotation, AxisOfRotation)

	X3DNODE(Billboard, X3DGroupingNode)
};

}	// x3d
}	// System

#endif // x3d_Billboard_h
