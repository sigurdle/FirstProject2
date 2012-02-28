#ifndef x3d_Layer_h
#define x3d_Layer_h

namespace System
{
namespace x3d
{

class X3DEXT Layer : public X3DLayerNode
{
public:
	CTOR Layer();

	X3DNODE(Layer, X3DLayerNode)

#ifndef __LERSTAD__
	X3DMFIELD(TypedMFNode<X3DChildNode*>, children, Children)
#else
	X3DMFIELD(MFNode, children, Children)
#endif

	virtual void Draw(X3DDrawContext* pDC) override;
	virtual void DrawGlobalLights(X3DDrawContext* pDC) override;
	virtual void DrawOverlay(X3DDrawContext* pDC) override;
	virtual int HitTest(const D3DXMATRIX& projection, const D3DXMATRIX& view, const D3DXMATRIX& model, const D3D10_VIEWPORT& vp, int type, Vec2f mousepos, Vec3f pos, IHitTest* hitTest) override;
};

}	// x3d
}	// System

#endif // x3d_Layer_h
