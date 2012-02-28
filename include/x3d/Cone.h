#ifndef x3d_Cone_h
#define x3d_Cone_h

namespace System
{
namespace x3d
{

class X3DEXT Cone :
	public X3DGeometryNode,

	public RenderImplImpl,
	public IGeometryRender
{
public:
	CTOR Cone();

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode);

	X3DSFIELD(SFFloat, bottomRadius, BottomRadius)
	X3DSFIELD(SFFloat, height, Height)

	X3DNODE(Cone, X3DGeometryNode)

protected:

	Gui::Media3D::CylinderShape m_shape;
};

}	// x3d
}

#endif // x3d_Cone_h
