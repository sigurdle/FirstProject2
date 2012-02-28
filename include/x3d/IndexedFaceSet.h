namespace System
{
namespace x3d
{

class X3DEXT IndexedFaceSet :
	public X3DComposedGeometryNode,
	public RenderImplImpl,
	public X3DBoundedImplImpl,
	public IGeometryRender
{
public:
	CTOR IndexedFaceSet();

	X3DNODE(IndexedFaceSet, X3DComposedGeometryNode)

	bool Within(const gm::vector3f& start, const gm::vector3f& end, gm::vector3f& plane_normal, gm::vector3f& pt, double& d2);

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode) override;
	virtual BoundingBox CalculateBoundingBox(gm::matrix4f& transform) override;

	Coordinate* getCoord();
	TextureCoordinate* getTexCoord();
	Normal* getNormal();

	MFInt32* getCoordIndexField()
	{
		return m_coordIndex;
	}

	MFInt32* getTexCoordIndexField()
	{
		return m_texCoordIndex;
	}

	int getCoordIndex1Value(uint index);
	uint getCoordIndexSize()
	{
		return m_coordIndex->get_size();
	}

	static TypedX3DFieldDefinition<SFBool>* get_convexFieldDef();
	static TypedX3DFieldDefinition<MFInt32>* get_coordIndexFieldDef();
	static TypedX3DFieldDefinition<MFInt32>* get_texCoordIndexFieldDef();
	static TypedX3DFieldDefinition<MFInt32>* get_normalIndexFieldDef();

private:

	SFBool* m_convex;
	MFInt32* m_coordIndex;
	MFInt32* m_normalIndex;
	MFInt32* m_colorIndex;
	MFInt32* m_texCoordIndex;
	SFFloat* m_creaseAngle;

#if 1
	vector<Vec3f> m_points;
	vector<Vec3f> m_normals;
//	std::vector<LDraw::vector3f> m_texcoords[16];

	vector<X3DTextureCoordinateNode*> m_texcoordNode;

	vector<uint32> m_indices;
	vector<uint32> m_normalIndices;
	vector<uint32> m_texcoordIndices;
#endif

	ID3D10Buffer* m_d3d10_VertexBuffer[2];

	Graphics::VertexDeclaration m_vertexDeclaration;

	Graphics::VertexBuffer m_vertexBuffer0;
	unsigned int m_vertexOffsetInBytes;

	unsigned int m_nvertices;
	bool m_bInited;
};

}	// x3d
}	// System
