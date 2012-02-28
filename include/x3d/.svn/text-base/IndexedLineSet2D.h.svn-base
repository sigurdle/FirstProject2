#ifndef x3d_IndexedLineSet2D_h
#define x3d_IndexedLineSet2D_h

namespace System
{
namespace x3d
{

class IndexedLineSet2D :
	public X3DGeometryNode,
	public IGeometryRender
{
public:
	CTOR IndexedLineSet2D();
	~IndexedLineSet2D();

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode);

	Coordinate2D* getCoord() const
	{
		return m_coord->getValue();
	}

	SFNode* getCoordField() const
	{
		return m_coord;
	}

	MFInt32* getCoordIndexField() const
	{
		return m_coordIndex;
	}

	bool getColorPerVertex() const
	{
		return m_colorPerVertex->getValue();
	}

	SFBool* getColorPerVertexField() const
	{
		return m_colorPerVertex;
	}

	static NodeType* GetNodeType();

private:

	TypedSFNode<Coordinate2D*>* m_coord;
	MFInt32* m_coordIndex;
	SFBool* m_colorPerVertex;

	static NodeType* nodeType;
};

}	// x3d
}

#endif // x3d_IndexedLineSet2D_h
