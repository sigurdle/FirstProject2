namespace System
{
namespace Gui
{

class GUIEXT WaveformData : public Object// TODO, public IViewable
{
public:
	CTOR WaveformData();

	uint64 get_SampleCount();
	uint32 get_SampleCount32();
	uint64 get_SampleCount64();

	TimeDuration get_Duration();

	const WAVEFORMATEX& get_Format() const throw()
	{
		return m_wfx;
	}

	static WaveformData* FromFile(StringIn filename);

protected:

	WAVEFORMATEX m_wfx;

public:	// TODO protected

	byte* m_audioData;
	uint64 m_audioBytes;
	uint64 m_nsamples;

	list<WaveformVisual*> m_views;
	list<WaveformData*>::iterator m_playing;

	static List<WaveformData*> m_playingList;
};

GUIEXT WaveformVisual* Show(WaveformData* waveformdata);
GUIEXT Object* Play(WaveformData* waveformdata);

}	// Gui
}	// System
