#ifndef x3d_AudioClip_h
#define x3d_AudioClip_h

namespace System
{
namespace x3d
{

class X3DEXT AudioClip :
	public X3DSoundSourceNode,
	public X3DUrlObject
{
public:
	CTOR AudioClip();

	X3DNODE(AudioClip, X3DSoundSourceNode)

	X3DMFIELD_OVERRIDE(MFString, url, Url)
	X3DSFIELD(SFFloat, pitch, Pitch)
	X3DSFIELD(SFFloat, duration_changed, DurationChanged)

	void setUrl(StringIn url);

	virtual void AddSoundNode(X3DSoundNode* pSound) override;
	virtual void RemoveSoundNode(X3DSoundNode* pSound) override;

	virtual void OnFieldChanged(X3DField* field) override;

	virtual void DoTime(double gt)
	{
	}

	Gui::WaveformData* GetWave()
	{
		return m_wave;
	}

protected:

	bool LoadFile();
	bool LoadFile(StringIn url);

	/*
	SFString [in,out] description      ""
	SFBool   [in,out] loop             FALSE
	SFNode   [in,out] metadata         NULL  [X3DMetadataObject]
	SFTime   [in,out] pauseTime        0     (-8,8)
	SFFloat  [in,out] pitch            1.0   (0,8)
	SFTime   [in,out] resumeTime       0     (-8,8)
	SFTime   [in,out] startTime        0     (-8,8)
	SFTime   [in,out] stopTime         0     (-8,8)
	MFString [in,out] url              []    [urn]
	SFTime   [out]    duration_changed
	SFTime   [out]    elapsedTime
	SFBool   [out]    isActive
	SFBool   [out]    isPaused
  */

	/*
	MFString* m_url;
	SFTime* m_duration_changed;
	SFFloat* m_pitch;
	*/

	vector<X3DSoundNode*> m_sounds;

	bool m_triedLoad;

public:

	/*
	WAVEFORMATEX m_wfx;
	byte* m_audioData;
	ULONG m_audioBytes;
	*/
	Gui::WaveformData* m_wave;

};

}	// x3d
}	// System

#endif // x3d_AudioClip_h
