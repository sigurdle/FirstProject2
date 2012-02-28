#ifndef x3d_Rectangle2D_h
#define x3d_Rectangle2D_h

namespace System
{
namespace x3d
{

class X3DEXT Rectangle2D :
	public X3DGeometryNode, // X3DNode,
	public IGeometryRender
{
public:
	CTOR Rectangle2D();

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* textureNode);

	X3DSFIELD(SFVec2f, size, Size)

	X3DNODE(Rectangle2D, X3DGeometryNode)

private:

	Gui::Media3D::Rectangle2DShape m_shape;
};

}	// x3d
}

#endif // x3d_Rectangle2D_h
