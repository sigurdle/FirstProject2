#ifndef x3d_Sphere_h
#define x3d_Sphere_h

namespace System
{
namespace x3d
{

class X3DEXT Sphere : 
	public X3DGeometryNode,	// X3DChildNode / X3DNode
	public X3DBoundedImplImpl,
	public RenderImplImpl,

	public IGeometryRender
{
public:
	CTOR Sphere();

	X3DSFIELD(SFFloat, radius, Radius)

	X3DNODE(Sphere, X3DGeometryNode)

	virtual void AddShapeDesc(physx::PxRigidActor* actor) override;
	virtual void Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode) override;
	virtual BoundingBox CalculateBoundingBox(gm::matrix4f& transform) override;

protected:

	Gui::Media3D::SphereShape m_shape;
};

}	// x3d
}	// System

#endif // x3d_Sphere_h
