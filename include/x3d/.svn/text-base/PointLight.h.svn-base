namespace System
{
namespace x3d
{

class X3DEXT PointLight : 
	public X3DLightNode,
	public RenderImplImpl,
	public IPositionable3f
{
public:
	CTOR PointLight();

	/*
	SFFloat [in,out] ambientIntensity 0     [0,1]
	SFVec3f [in,out] attenuation      1 0 0 [0,8)
	SFColor [in,out] color            1 1 1 [0,1]
	SFBool  [in,out] global           TRUE
	SFFloat [in,out] intensity        1     [0,1]
	SFVec3f [in,out] location         0 0 0 (-8,8)
	SFBool  [in,out] on               TRUE
	SFFloat [in,out] radius           100   [0,8)
  */

	X3DSFIELD(SFVec3f, location, Location)
	X3DSFIELD(SFVec3f, attenuation, Attenuation)
	X3DSFIELD(SFFloat, radius, Radius)

	X3DNODE(PointLight, X3DLightNode)

	virtual Vec3f getPosition3f() override	// IPositionable3f
	{
		return getLocation();
	}

	virtual void setPosition3f(Vec3f position) override	// IPositionable3f
	{
		return setLocation(position);
	}

	virtual void PreDraw(X3DDrawContext* pDC) override;
	virtual void DrawGlobalLights(X3DDrawContext* pDC) override;
	virtual void DrawOverlay(X3DDrawContext* pDC) override;
	virtual int HitTest(const D3DXMATRIX& projection, const D3DXMATRIX& view, const D3DXMATRIX& model, const D3D10_VIEWPORT& vp, int type, Vec2f mousepos, Vec3f pos, IHitTest* hitTest) override;

protected:

	void SetLight(X3DDrawContext* pDC);
};

}	// x3d
}	// System
