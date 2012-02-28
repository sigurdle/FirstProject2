#ifndef x3d_Sound_h
#define x3d_Sound_h

namespace System
{
namespace x3d
{

class X3DEXT Sound :
	public X3DSoundNode,
	public RenderImplImpl,	// Audio rendering
	public IPositionable3f
{
public:
	CTOR Sound();
	~Sound();

	X3DSFIELD(SFVec3f, direction, Direction)
	X3DSFIELD(SFVec3f, location, Location)
	X3DSFIELD(SFFloat, intensity, Intensity)
	X3DSFIELD(SFFloat, minBack, MinBack)
	X3DSFIELD(SFFloat, maxBack, MaxBack)
	X3DSFIELD(SFFloat, minFront, MinFront)
	X3DSFIELD(SFFloat, maxFront, MaxFront)
	X3DSFIELD(SFBool, spatialize, Spatialize)

	X3DNODE(Sound, X3DSoundNode)

	void Play();

	virtual void Draw(X3DDrawContext* pDC) override;
	virtual void DoTime(double gt) override;
	virtual void OnFieldChanged(X3DField* field) override;

	virtual void DrawOverlay(X3DDrawContext* pDC) override;
	virtual int HitTest(const D3DXMATRIX& projection, const D3DXMATRIX& view, const D3DXMATRIX& model, const D3D10_VIEWPORT& vp, int type, Vec2f mousepos, Vec3f pos, IHitTest* hitTest) override;

	virtual Vec3f getPosition3f() override	// IPositionable3f
	{
		return getLocation();
	}

	virtual void setPosition3f(Vec3f position) override	// IPositionable3f
	{
		setLocation(position);
	}

	void mute()
	{
		setIntensity(0);
	}

protected:

	virtual void SoundSourceUrlChanged() override;

private:

	IXAudio2SubmixVoice* m_submixVoice;
	IUnknown* m_reverbEffect;

	bool m_bPlaying;

/*
	SFVec3f [in,out] direction  0 0 1 (-8,8)
	SFFloat [in,out] intensity  1     [0,1]
	SFVec3f [in,out] location   0 0 0 (-8,8)
	SFFloat [in,out] maxBack    10    [0,8)
	SFFloat [in,out] maxFront   10    [0,8)
	SFNode  [in,out] metadata   NULL  [X3DMetadataObject]
	SFFloat [in,out] minBack    1     [0,8)
	SFFloat [in,out] minFront   1     [0,8)
	SFFloat [in,out] priority   0     [0,1]
	SFNode  [in,out] source     NULL  [X3DSoundSourceNode]
	SFBool  []       spatialize TRUE
*/
};

}	// x3d
}

#endif // x3d_Sound_h
