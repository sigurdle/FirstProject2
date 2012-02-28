#ifndef x3d_SpotLight_h
#define x3d_SpotLight_h

namespace System
{
namespace x3d
{

class X3DEXT SpotLight : 
	public X3DLightNode,
	public RenderImplImpl,
	public IPositionable3f
{
public:
	CTOR SpotLight();

	X3DSFIELD(SFFloat, radius, Radius)
	X3DSFIELD(SFFloat, beamWidth, BeamWidth)
	X3DSFIELD(SFFloat, cutOffAngle, CutOffAngle)
	X3DSFIELD(SFVec3f, location, Location)
	X3DSFIELD(SFVec3f, direction, Direction)

	X3DNODE(SpotLight, X3DLightNode)

	virtual Vec3f getPosition3f() override	// IPositionable3f
	{
		return getLocation();
	}

	virtual void setPosition3f(Vec3f position) override	// IPositionable3f
	{
		return setLocation(position);
	}

	virtual void PreDraw(X3DDrawContext* pDC) override;

	/*
	SFFloat [in,out] ambientIntensity 0        [0,1]
	SFVec3f [in,out] attenuation      1 0 0    [0,8)
	SFFloat [in,out] beamWidth        p/2      (0,p/2]
	SFColor [in,out] color            1 1 1    [0,1]
	SFFloat [in,out] cutOffAngle      p/4      (0,p/2]
	SFVec3f [in,out] direction        0 0 -1   (-8,8)
	SFFloat [in,out] intensity        1        [0,1]
	SFVec3f [in,out] location         0 0 0    (-8,8)
	SFBool  [in,out] on               TRUE
	SFFloat [in,out] radius           100      [0,8)
	*/
};

}	// x3d
}

#endif // x3d_SpotLight_h
