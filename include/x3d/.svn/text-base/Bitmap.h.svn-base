namespace System
{
namespace x3d
{

class X3DEXT Bitmap :
	public X3DGeometryNode,
	public IGeometryRender
{
public:
	CTOR Bitmap();

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* textureNode);

	static NodeType s_nodeType;

private:

/*
	SFVec2f [] size -1,-1
*/

	SFVec2f* m_scale;
};

}	// x3d
}
