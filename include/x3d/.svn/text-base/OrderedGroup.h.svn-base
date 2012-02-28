#ifndef x3d_OrderedGroup_h
#define x3d_OrderedGroup_h

namespace System
{
namespace x3d
{

// Part of MPEG-4
class X3DEXT OrderedGroup :	// MPEG-4
	public X3DGroupingNode, //	public X3DBoundedObject,
	public RenderImplImpl
{
public:
	CTOR OrderedGroup();

	virtual void Draw(X3DDrawContext* pDC) override;

	X3DMFIELD(MFFloat, order, Order)

	X3DNODE(OrderedGroup, X3DGroupingNode)
};

}	// x3d
}	// System

#endif // x3d_OrderedGroup_h
