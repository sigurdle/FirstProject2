#ifndef x3d_Sound2D_h
#define x3d_Sound2D_h

namespace System
{
namespace x3d
{

class X3DEXT Sound2D :	// MPEG4 BIFS
	public X3DSoundNode,
	public RenderImplImpl	// Audio rendering
{
public:
	CTOR Sound2D();

	void init()
	{
// Assume that lpDsbSecondary is a valid IDirectSoundBuffer8
// that has been created with DSBCAPS_CTRL3D.
/*
		LPDIRECTSOUND3DBUFFER8 lpDs3dBuffer;
 
		ErrorCode hr = lpDsbSecondary->QueryInterface(IID_IDirectSound3DBuffer8, 
                                            (LPVOID *)&lpDs3dBuffer); 
*/
	}

	virtual void Draw(X3DDrawContext* pDC)
	{
#if 0
		if (m_source->m_value)
		{
			// Add us the audioclips list of sounds
			for (int i = 0; i < static_cast<CLAudioClip*>(m_source->m_value)->m_sounds.GetSize(); i++)
			{
				if (static_cast<CLAudioClip*>(m_source->m_value)->m_sounds[i] == this)
					break;
			}

			if (i == static_cast<CLAudioClip*>(m_source->m_value)->m_sounds.GetSize())
			{
				static_cast<CLAudioClip*>(m_source->m_value)->m_sounds.Add(this);
			}
		}
#endif
	}

	SFVec2f* m_location;
	SFFloat* m_intensity;
	SFBool* m_spatialize;

//	CComPtr<IDirectSound8> m_ds8;
#if 0
	<IDirectSoundBuffer8, &IID_IDirectSoundBuffer8> m_dsBuffer8;
#endif

	static NodeType* GetNodeType();

private:

	static NodeType* nodeType;
};

}	// x3d
}

#endif // x3d_Sound2D_h
