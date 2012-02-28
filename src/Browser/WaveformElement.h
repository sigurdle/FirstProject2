#ifndef WaveformElement_h
#define WaveformElement_h

namespace System
{

struct WaveFormat
{
	uint16        wFormatTag;         /* format type */
	uint16        nChannels;          /* number of channels (i.e. mono, stereo...) */
	uint32       nSamplesPerSec;     /* sample rate */
	uint32       nAvgBytesPerSec;    /* for buffer estimation */
	uint16        nBlockAlign;        /* block size of data */
	uint16        wBitsPerSample;     /* number of bits per sample of mono data */
	uint16        cbSize;             /* the count in bytes of the size of */
	/* extra information (after cbSize) */
};

// TODO, improve this
class Wave : public Object
{
public:
	MSWindows::WAVEFORMATEX* m_wfx;
//	WaveFormat* m_wfx;
	uint8* m_data;
	ULONG m_nsamples;
};

class WaveformElement : public UI::FrameworkElement
#if 0//WIN32
,public MSWindows::WindowImpl//<WaveformControl>
#endif
{
public:
	CTOR WaveformElement();

	void Stop();

#if WIN32
	virtual bool ProcessWindowMessage(MSWindows::Hwnd hWnd, UINT uMsg, MSWindows::WPARAM wParam, MSWindows::LPARAM lParam, MSWindows::LRESULT& lResult);
#endif

	void OnTimer();

	LONGLONG GetMarkStart() const
	{
		return m_markStart;
	}

	LONGLONG GetMarkEnd() const
	{
		return m_markEnd;
	}

	void SetMarkStart(LONGLONG mark)
	{
		m_markStart = mark;
	}

	void SetMarkEnd(LONGLONG mark)
	{
		m_markEnd = mark;
	}

	virtual LDraw::SizeD MeasureOverride(LDraw::SizeD availSize);
	//virtual LDraw::SizeD ArrangeOverride(LDraw::SizeD finalSize);
	virtual void OnRender(UI::Graphics* pGraphics);

	virtual void OnMouseDown(UI::MouseButtonEventArgs* args);
	virtual void OnMouseUp(UI::MouseButtonEventArgs* args);
	virtual void OnMouseMove(UI::MouseEventArgs* args);

	void DrawWaveSelection(UI::Graphics* pGraphics);

	LDraw::Commands* m_commands;

	Wave* m_wave;

	LONGLONG m_startSample;
	LONGLONG m_markStart;
	LONGLONG m_markEnd;

	int m_display;

	int m_dragging;

	LONGLONG m_cur;
	ULONG m_nloop;
	UINT m_nTimerID;
	double m_freq;

	CriticalSection m_lock;

	//LDraw::GraphicsPathF path;

	MediaShow::WaveOutput* wo;

	double m_scale;
	bool m_bStop;
};

}

#endif // WaveformElement_h
