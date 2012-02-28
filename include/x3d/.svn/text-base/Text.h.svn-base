#ifndef x3d_Text_h
#define x3d_Text_h

namespace System
{
namespace x3d
{

class X3DEXT Text :
	public X3DGeometryNode,
	public IGeometryRender
{
public:
	CTOR Text();
	~Text();

	//virtual void SetNodeType(NodeType* pNodeType);

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode);

	static NodeType s_nodeType;

public:

	SFNode* m_fontStyle;
	MFString* m_string;

/*
	SFNode   [in,out] fontStyle NULL  [X3FontSyleNode]
	MFFloat  [in,out] length    []    [0,8)
	SFFloat  [in,out] maxExtent 0.0   [0,8)
	SFNode   [in,out] metadata  NULL  [X3DMetadataObject]
	MFString [in,out] string    []
	SFBool   []       solid     FALSE
*/
};

}	// x3d
}

#endif // x3d_Text_h
