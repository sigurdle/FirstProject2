#ifndef x3d_Viewport_h
#define x3d_Viewport_h

namespace System
{
namespace x3d
{

class X3DEXT Viewport : 
	public X3DViewportNode,
	public X3DBoundedImplImpl,
	public RenderImplImpl
{
public:
	CTOR Viewport();

	virtual BoundingBox CalculateBoundingBox(gm::matrix4f& transform) override;

	X3DMFIELD(MFFloat, clipBoundary, ClipBoundary)

	X3DNODE(Viewport, X3DViewportNode)

protected:

	virtual void Draw(X3DDrawContext* pDC) override;

//	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode);

};

}	// x3d
}	// System

#endif // x3d_Viewport_h
