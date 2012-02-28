#ifndef x3d_Cylinder_h
#define x3d_Cylinder_h

namespace System
{
namespace x3d
{

class X3DEXT Cylinder :
	public X3DGeometryNode,
	public RenderImplImpl,
	public IGeometryRender
{
public:
	CTOR Cylinder();

	X3DSFIELD(SFFloat, radius, Radius)
	X3DSFIELD(SFFloat, height, Height)
	X3DSFIELD(SFBool, top, Top)
	X3DSFIELD(SFBool, bottom, Bottom)
	X3DSFIELD(SFBool, side, Side)

	X3DNODE(Cylinder, X3DGeometryNode)

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode);

protected:

//	virtual void CreateActor(NxScene* gScene, D3DXMATRIX modelView) override;

	Gui::Media3D::CylinderShape m_shape;

//	ID3D10Buffer* m_d3d10_VertexBuffer;
//	uint m_nvertices;
//	ID3D10Buffer* m_d3d10_IndexBuffer;

/*
	SFBool  [] bottom TRUE
	SFFloat [] height 2    (0,8)
	SFFloat [] radius 1    (0,8)
	SFBool  [] side   TRUE
	SFBool  [] top    TRUE
*/
	/*
	SFFloat* m_radius;
	SFFloat* m_height;
	SFBool* m_top;
	SFBool* m_bottom;
	SFBool* m_side;
	*/
};

}	// x3d
}	// System

#endif // x3d_Cylinder_h
