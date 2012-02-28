#ifndef x3d_X3DComposedGeometryNode_h
#define x3d_X3DComposedGeometryNode_h

namespace System
{
namespace x3d
{

class X3DEXT X3DComposedGeometryNode : public X3DGeometryNode
{
public:
	~X3DComposedGeometryNode();

	bool getCCW()
	{
		return m_ccw->getValue();
	}

	SFBool* getCCWField()
	{
		return m_ccw;
	}

	bool getNormalPerVertex()
	{
		return m_normalPerVertex->getValue();
	}

	SFBool* getNormalPerVertexField()
	{
		return m_normalPerVertex;
	}

	bool getColorPerVertex()
	{
		return m_colorPerVertex->getValue();
	}

	SFBool* getColorPerVertexField()
	{
		return m_colorPerVertex;
	}

	bool getSolid()
	{
		return m_solid->getValue();
	}

	void setSolid(bool solid)
	{
		m_solid->setValue(solid);
	}

	SFBool* getSolidField()
	{
		return m_solid;
	}

	MFNode* getAttribField()
	{
		return m_attrib;
	}

	static NodeType* GetNodeType();

	static X3DFieldDefinition* get_colorFieldDef();
	static X3DFieldDefinition* get_coordFieldDef();
	static X3DFieldDefinition* get_normalFieldDef();
	static X3DFieldDefinition* get_texCoordFieldDef();
	static X3DFieldDefinition* get_attribFieldDef();
	static TypedX3DFieldDefinition<SFBool>* get_ccwFieldDef();
	static TypedX3DFieldDefinition<SFBool>* get_solidFieldDef();
	static TypedX3DFieldDefinition<SFBool>* get_colorPerVertexFieldDef();

protected:

	CTOR X3DComposedGeometryNode(NodeType* nodeType);

/*
	MFNode [in,out] attrib          []   [X3DVertexAttributeNode]
	SFNode [in,out] color           NULL [X3DColorNode]
	SFNode [in,out] coord           NULL [X3DCoordinateNode]
	SFNode [in,out] fogCoord        []   [FogCoordinate]
	SFNode [in,out] metadata        NULL [X3DMetadataObject]
	SFNode [in,out] normal          NULL [X3DNormalNode]
	SFNode [in,out] texCoord        NULL [X3DTextureCoordinateNode]
	SFBool []       ccw             TRUE
	SFBool []       colorPerVertex  TRUE
	SFBool []       normalPerVertex TRUE
	SFBool []       solid           TRUE
*/

	TypedSFNode<X3DColorNode*>* m_color;
	TypedSFNode<X3DCoordinateNode*>* m_coord;
	TypedSFNode<X3DNormalNode*>* m_normal;
	TypedSFNode<X3DTextureCoordinateNode*>* m_texCoord;
	MFNode* m_attrib;
	SFBool* m_normalPerVertex;
	SFBool* m_colorPerVertex;
	SFBool* m_ccw;
	SFBool* m_solid;
};

}	// x3d
}

#endif // x3d_X3DComposedGeometryNode_h
