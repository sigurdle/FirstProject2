#ifndef x3d_TriangleStripSet_h
#define x3d_TriangleStripSet_h

namespace System
{
namespace x3d
{

class X3DEXT TriangleStripSet :
	public X3DComposedGeometryNode,
	public RenderImplImpl,
	public IGeometryRender
{
public:
	CTOR TriangleStripSet();
	~TriangleStripSet();

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode);

	static NodeType s_nodeType;

private:

	SFNode* m_coord;
	SFNode* m_normal;
	MFInt32* m_stripCount;

/*
	SFNode  [in,out] color           NULL [X3DColorNode]
	SFNode  [in,out] coord           NULL [X3DCoordinateNode]
	SFNode  [in,out] metadata        NULL [X3DMetadataObject]
	SFNode  [in,out] normal          NULL [X3DNormalNode]
	MFInt32 [in,out] stripCount      []   [3,8)
	SFNode  [in,out] texCoord        NULL [X3DTextureCoordinateNode]
	SFBool  []       ccw             TRUE
	SFBool  []       colorPerVertex  TRUE
	SFBool  []       normalPerVertex TRUE
	SFBool  []       solid           TRUE
*/
};

}	// x3d
}

#endif // x3d_TriangleStripSet_h
