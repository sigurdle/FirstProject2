#ifndef x3d_Rectangle_h
#define x3d_Rectangle_h

namespace System
{
namespace x3d
{

class X3DEXT Rectangle : 
	public X3DGeometryNode,
	public IGeometryRender
{
public:
	CTOR Rectangle();

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* textureNode) override;

	X3DSFIELD(SFVec2f, size, Size)

	X3DNODE(Rectangle, X3DGeometryNode)

protected:

	void Rectf(X3DDrawContext* pDC, float x1, float y1, float x2, float y2);
};

}	// x3d
}	// System

#endif // x3d_Rectangle_h
