namespace System
{
namespace x3d
{

class X3DEXT IndexedLineSet :
	public X3DGeometryNode,
	public IGeometryRender
{
public:
	CTOR IndexedLineSet();
	~IndexedLineSet();

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode) override;

	static NodeType* GetNodeType();
	static X3DFieldDefinition* get_coordFieldDef();
	static X3DFieldDefinition* get_coordIndexFieldDef();
	static X3DFieldDefinition* get_colorIndexFieldDef();
	static X3DFieldDefinition* get_colorPerVertexFieldDef();
	static X3DFieldDefinition* get_colorFieldDef();

private:

	SFNode* m_coord;
	MFInt32* m_coordIndex;
	MFInt32* m_colorIndex;
	SFBool* m_colorPerVertex;
	TypedSFNode<X3DColorNode*>* m_color;

	static NodeType* nodeType;

/*
	MFInt32 [in]     set_colorIndex
	MFInt32 [in]     set_coordIndex	// This must be a typo, should it be get??
	SFNode  [in,out] color          NULL [X3DColorNode]
	SFNode  [in,out] coord          NULL [X3DCoordinateNode]
	SFNode  [in,out] metadata       NULL [X3DMetadataObject]
	MFInt32 []       colorIndex     []   [0,8) or -1
	SFBool  []       colorPerVertex TRUE
	MFInt32 []       coordIndex     []   [0,8) or -1
*/

	struct polyline
	{
		int index;
		int count;

		CTOR polyline()
		{
		}

		CTOR polyline(int _index, int _count)
		{
			index = _index;
			count = _count;
		}
	};
};

}	// x3d
}
