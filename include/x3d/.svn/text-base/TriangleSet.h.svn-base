#ifndef x3d_TriangleSet_h
#define x3d_TriangleSet_h

namespace System
{
namespace x3d
{

class X3DEXT TriangleSet :
	public X3DComposedGeometryNode,
	public IGeometryRender,
	public RenderImplImpl
{
public:
	CTOR TriangleSet();
	~TriangleSet();

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode);

	static NodeType* GetNodeType();
	static NodeType* nodeType;

protected:

	Graphics::VertexDeclaration m_vertexDeclaration;

	Graphics::VertexBuffer m_vertexBuffer0;	// position
	Graphics::VertexBuffer m_vertexBuffer1;	// normal
	Graphics::VertexBuffer m_vertexBuffer2;	// color
	vector<Graphics::VertexBuffer> m_attribBuffer;	// attrib
	unsigned int m_nvertices;

	vector<gm::vector3f> m_normals;

	SFNode* m_color;
	SFNode* m_coord;

};

}	// x3d
}	// System

#endif // x3d_TriangleSet_h
