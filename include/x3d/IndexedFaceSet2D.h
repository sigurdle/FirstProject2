#ifndef x3d_IndexedFaceSet2D_h
#define x3d_IndexedFaceSet2D_h

namespace System
{
namespace x3d
{

class X3DEXT IndexedFaceSet2D :
	public X3DGeometryNode,
	public IGeometryRender
{
public:
	CTOR IndexedFaceSet2D();
	~IndexedFaceSet2D();

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode);

	static NodeType s_nodeType;

public:
/*
	eventIn MFInt32 set_colorIndex
	eventIn MFInt32 set_coordIndex
	eventIn MFInt32 set_texCoordIndex
	exposedField SFNode color NULL
	exposedField SFNode coord NULL
	exposedField SFNode texCoord NULL
	field MFInt32 colorIndex []
	field SFBool colorPerVertex TRUE
	field SFBool convex TRUE
	field MFInt32 coordIndex []
	field MFInt32 texCoordIndex []
*/

	SFNode* m_coord;
	MFInt32* m_coordIndex;
	SFBool* m_convex;
};

}	// x3d
}

#endif // x3d_IndexedFaceSet2D_h
