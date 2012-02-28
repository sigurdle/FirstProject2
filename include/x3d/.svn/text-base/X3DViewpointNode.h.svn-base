#ifndef x3d_X3DViewpointNode_h
#define x3d_X3DViewpointNode_h

namespace System
{
namespace x3d
{

class X3DEXT X3DViewpointNode : public X3DBindableNode,
	public ICamera,
	public IPositionable3f,
	public RenderImplImpl
{
protected:

	CTOR X3DViewpointNode(NodeType* nodeType);

	virtual void OnFieldChanged(X3DField* pField) override;

public:

	X3DSFIELD(SFString, description, Description)
	X3DSFIELD(SFVec3f, position, Position)
	X3DSFIELD(SFRotation, orientation, Orientation)
	X3DSFIELD(SFVec3f, centerOfRotation, CenterOfRotation)
	X3DSFIELD(SFBool, jump, Jump)

	X3DNODE_ABSTRACT(X3DViewpointNode, X3DBindableNode)

	virtual Vec3f getPosition3f() override	// IPositionable3f
	{
		return getPosition();
	}

	virtual void setPosition3f(Vec3f position) override	// IPositionable3f
	{
		return setPosition(position);
	}

	virtual void DrawOverlay(X3DDrawContext* pDC) override;
	virtual int HitTest(const D3DXMATRIX& projection, const D3DXMATRIX& view, const D3DXMATRIX& model, const D3D10_VIEWPORT& vp, int type, Vec2f mousepos, Vec3f pos, IHitTest* hitTest) override;

	virtual D3DXMATRIX GetViewMatrix() override;
	virtual D3DXMATRIX GetViewMatrixI() override;
};

}	// x3d
}

#endif // x3d_X3DViewpointNode_h
