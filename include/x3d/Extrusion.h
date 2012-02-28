#ifndef x3d_Extrusion_h
#define x3d_Extrusion_h

namespace System
{
namespace x3d
{

class X3DEXT Extrusion : 
	public X3DGeometryNode,
	public RenderImplImpl,
	public IGeometryRender
{
public:
	CTOR Extrusion();

	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode);

	static NodeType s_nodeType;

protected:

	MFVec2f* m_crossSection;
	MFVec3f* m_spine;
	MFVec2f* m_scale;
};

}	// x3d
}

#endif // x3d_Extrusion_h
