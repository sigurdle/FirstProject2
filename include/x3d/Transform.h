#ifndef x3d_Transform_h
#define x3d_Transform_h

namespace System
{
namespace x3d
{

class X3DEXT Transform : 
	public X3DGroupingNode, // X3DBoundedObject,
	public X3DBoundedImplImpl,
	public RenderImplImpl,
	public IPositionable3f
{
public:
	CTOR Transform();

	X3DSFIELD(SFVec3f, center, Center)
	X3DSFIELD(SFVec3f, scale, Scale)
	X3DSFIELD(SFVec3f, translation, Translation)
	X3DSFIELD(SFRotation, rotation, Rotation)
	X3DSFIELD(SFRotation, scaleOrientation, ScaleOrientation)

	X3DNODE(Transform, X3DGroupingNode)

	virtual BoundingBox CalculateBoundingBox(gm::matrix4f& transform) override;

	virtual Vec3f getPosition3f() override	// IPositionable3f
	{
		return getTranslation();
	}

	virtual void setPosition3f(Vec3f position) override	// IPositionable3f
	{
		setTranslation(position);
	}

	virtual int Moveability() override
	{
		return 3;
	}

	virtual int Resizability() override
	{
		return 3;
	}

public:
/*
P' = T * C * R * SR * S * -SR * -C * P

center           C
rotation         R
scale            S
scaleOrientation SR
translation      T
*/

	virtual void Draw(X3DDrawContext* pDC) override;
	virtual void DrawOverlay(X3DDrawContext* pDC) override;
	virtual void DrawGlobalLights(X3DDrawContext* pDC) override;

//	virtual BoundingBox CalculateBoundingBox(LDraw::matrix4f& transform) override;

	virtual int HitTest(const D3DXMATRIX& projection, const D3DXMATRIX& view, const D3DXMATRIX& model, const D3D10_VIEWPORT& vp, int type, Vec2f mousepos, Vec3f pos, IHitTest* hitTest) override;

//	virtual void addActors(NxScene* nxScene, D3DXMATRIX modelView) override;

	D3DXMATRIX GetTransform() override;
};

}	// x3d
}

#endif // x3d_Transform_h
