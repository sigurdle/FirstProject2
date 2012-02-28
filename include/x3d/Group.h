#ifndef x3d_Group_h
#define x3d_Group_h

namespace System
{
namespace x3d
{

class X3DEXT Group :
	public X3DGroupingNode, //	public X3DBoundedObject,

	public RenderImplImpl
{
public:
	CTOR Group();

	X3DNODE(Group, X3DGroupingNode)

	virtual void Draw(X3DDrawContext* pDC) override;
	virtual void DrawOverlay(X3DDrawContext* pDC) override;
	virtual void DrawGlobalLights(X3DDrawContext* pDC) override;

	virtual int HitTest(const D3DXMATRIX& projection, const D3DXMATRIX& view, const D3DXMATRIX& model, const D3D10_VIEWPORT& vp, int type, Vec2f mousepos, Vec3f pos, IHitTest* hitTest) override;
};

}	// x3d
}	// System

#endif // x3d_Group_h
