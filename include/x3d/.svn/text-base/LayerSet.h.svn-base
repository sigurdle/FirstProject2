#ifndef x3d_LayerSet_h
#define x3d_LayerSet_h

namespace System
{
namespace x3d
{

class X3DEXT LayerSet : public X3DNode, public RenderImplImpl
{
public:

	CTOR LayerSet();

	X3DNODE(LayerSet, X3DNode)

	X3DSFIELD(SFInt32, activeLayer, ActiveLayer)
	X3DMFIELD(MFInt32, order, Order)
#ifndef __LERSTAD__
	X3DMFIELD(TypedMFNode<X3DLayerNode*>, layers, Layers)
#else
	X3DMFIELD(MFNode, layers, Layers)
#endif

	virtual void Draw(X3DDrawContext* pDC) override;
	virtual void DrawGlobalLights(X3DDrawContext* pDC) override;
	virtual void DrawOverlay(X3DDrawContext* pDC) override;
	virtual int HitTest(const D3DXMATRIX& projection, const D3DXMATRIX& view, const D3DXMATRIX& model, const D3D10_VIEWPORT& vp, int type, Vec2f mousepos, Vec3f pos, IHitTest* hitTest) override;
};

}
}

#endif // x3d_LayerSet_h
