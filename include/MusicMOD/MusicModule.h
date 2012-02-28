#ifndef MusicModule_h
#define MusicModule_h

namespace System
{

//using namespace System;
//using namespace System::IO;

//#pragma comment(lib, "../LMedia/ReleaseMinSize/LMedia.lib")

class IWaveformData
{
public:
};

class PatternView;
class ScopeView;

class SongPosition
{
public:
	LONGLONG samples;
	uint8 songpos;
	uint8 divpos;
};

//HRESULT ReadWAVE(ISequentialByteStream* stream, Riff::CChunk& parent, Wave* *ppWave);

class HorizontalZoomer : public UI::Decorator
{
public:
	CTOR HorizontalZoomer()
	{
	//	m_pContent = NULL;
		m_bViewAll = false;
		m_factor = 1;
	}

	virtual void OnRender(UI::Graphics* pGraphics)
	{
	//	LDraw::Matrix oldTransform = pGraphics->GetTransform();
	//	pGraphics->ScaleTransform(m_factor, 1);

	//	m_pContent->m_bRenderValid = false;	// TODO

		get_Child()->Render(pGraphics);
	//	pGraphics->SetTransform(oldTransform);
	}

	virtual LDraw::SizeD MeasureOverride(LDraw::SizeD availSize)
	{
		get_Child()->Measure(availSize);

		if (m_bViewAll)
		{
			return LDraw::SizeD(availSize.Width, get_Child()->get_DesiredSize().Height);
		}
		else
		{
			return LDraw::SizeD(get_Child()->get_DesiredSize().Width*m_factor, get_Child()->get_DesiredSize().Height);
		}
	}

	virtual LDraw::SizeD ArrangeOverride(LDraw::SizeD finalSize)
	{
		if (m_bViewAll)
		{
			m_factor = finalSize.Width / get_Child()->get_DesiredSize().Width;

		}

		//ASSERT(0);
#if 0
		m_pContent->SetLayoutTransform(LDraw::Matrix3f::GetScale(m_factor, 1));
#endif
	//	m_pContent->m_transformMatrix = gmMatrix3::scale(m_factor, 1);

		dynamic_cast<WaveformElement*>(get_Child())->m_scale = m_factor;	// TODO

		//finalSize.Width /= m_factor;
		get_Child()->Arrange(LDraw::RectD(LDraw::PointD(0, 0), finalSize / m_factor));

		return finalSize;
	}

	/*
	void set_Content(UI::UIElement* pContent)
	{
		m_pContent = pContent;
		AddRChild(pContent);

	//	m_pContent->m_transformMatrix = gmMatrix3::scale(m_factor, 1);
	}
	*/

//protected:

//	UI::UIElement* m_pContent;

	bool m_bViewAll;

	double m_factor;
};

class WaveformView : public UI::Control, public IViewOf
{
public:

	CTOR WaveformView();
	CTOR WaveformView(Wave* wave);

	/*
	static const type_info& GetType()
	{
		return typeid(Wave);
	}
	*/

	virtual System::Object* get_Viewable()
	{
		return m_pFile;
	}

	virtual void set_Viewable(System::Object* pViewable)
	{
		SetFile(static_cast<FileObject*>(pViewable));
	}

	void SetFile(FileObject* pFile);

	class InsertUndo : 
		public IUndoUnit
	{
	public:
		CTOR InsertUndo()
		{
		//	m_kind = 0;

			m_bRedo = false;
			m_pEdit = NULL;
			//m_startCharPos = -1;
			m_len = 0;
			m_text = NULL;
		}

		~InsertUndo()
		{
			if (m_text)
			{
				delete m_text;
				m_text = NULL;
			}
		}

		virtual void Do(IUndoManager  *pUndoManager);

		virtual System::StringW* GetDescription();
		/*
		virtual long GetUnitType(CLSID *pClsid)
		{
			return 0;
		}
		*/
		virtual void OnNextAdd()
		{
			return;
		}

//		long	m_kind;
		WaveformView* m_pEdit;
		LONGLONG m_startCharPos;
		LONGLONG m_len;
		bool m_bRedo;
		uint8* m_text;
//		LONGLONG m_nsamples;
	};

	class TrimUndo : 
		public IUndoUnit
	{
	public:
		CTOR TrimUndo()
		{
			//m_kind = 0;

			m_bRedo = false;
			m_pEdit = NULL;
			//m_startCharPos = -1;
			//m_len = 0;
			//m_text = NULL;
		}

		~TrimUndo()
		{
			/*
			if (m_text)
			{
				delete m_text;
				m_text = NULL;
			}
			*/
		}

		virtual void Do(IUndoManager* pUndoManager);

		virtual System::StringW* GetDescription();
		/*
		virtual long GetUnitType(CLSID *pClsid)
		{
			return 0;
		}
		*/
		virtual void OnNextAdd()
		{
			return;
		}

		//long	m_kind;
		WaveformView* m_pEdit;
		LONGLONG m_leftSamples;
		LONGLONG m_rightSamples;
		bool m_bRedo;
		//uint8* m_text;
	};

	class MuteUndo : 
		public IUndoUnit
	{
	public:
		CTOR MuteUndo()
		{
			//m_kind = 0;

			m_bRedo = false;
			m_pEdit = NULL;
			//m_startCharPos = -1;
			//m_len = 0;
			//m_text = NULL;
		}

		~MuteUndo()
		{
			/*
			if (m_text)
			{
				delete m_text;
				m_text = NULL;
			}
			*/
		}

		virtual void Do(IUndoManager* pUndoManager);

		virtual System::StringW* GetDescription();
		/*
		virtual long GetUnitType(CLSID *pClsid)
		{
			return 0;
		}
		*/
		virtual void OnNextAdd()
		{
			return;
		}

		WaveformView* m_pEdit;
		LONGLONG m_startCharPos;
		LONGLONG m_len;
		uint8* m_text;
		bool m_bRedo;
	};

	class InsertSilenceUndo : 
		public IUndoUnit
	{
	public:
		CTOR InsertSilenceUndo()
		{
			//m_kind = 0;

			m_bRedo = false;
			m_pEdit = NULL;
			//m_startCharPos = -1;
			//m_len = 0;
			//m_text = NULL;
		}

		~InsertSilenceUndo()
		{
			/*
			if (m_text)
			{
				delete m_text;
				m_text = NULL;
			}
			*/
		}

		virtual void Do(IUndoManager* pUndoManager);

		virtual System::StringW* GetDescription();
		/*
		virtual long GetUnitType(CLSID *pClsid)
		{
			return 0;
		}
		*/
		virtual void OnNextAdd()
		{
			return;
		}

		WaveformView* m_pEdit;
		LONGLONG m_startCharPos;
		LONGLONG m_len;
		bool m_bRedo;
	};

	class ReverseUndo : 
		public IUndoUnit
	{
	public:
		CTOR ReverseUndo()
		{
			m_bRedo = false;
			m_pEdit = NULL;
		}

		~ReverseUndo()
		{
		}

		virtual void Do(IUndoManager* pUndoManager);

		virtual System::StringW* GetDescription();
		/*
		virtual long GetUnitType(CLSID *pClsid)
		{
			return 0;
		}
		*/
		virtual void OnNextAdd()
		{
			return;
		}

		WaveformView* m_pEdit;
		LONGLONG m_startCharPos;
		LONGLONG m_len;
		bool m_bRedo;
	};

//	virtual void handleEvent(System::Event* evt);

	FileObject* m_pFile;
	HorizontalZoomer* m_zoomer;
	WaveformElement* m_ctl;
	UI::ScrollViewer* m_pScroller;
	UI::ChildWindowContainer* m_pCanvas;

	UI::UndoManager* m_undoManager;
};

class InstrumentSample
{
public:
	CTOR InstrumentSample()
	{
		name[0] = 0;
		sampleLength = 0;
		finetune = 0;
		relativenote = 0;
		data = NULL;
		volume = 64;
	}

	~InstrumentSample()
	{
		delete[] data;
	}

	uint8* data;
	uint32 sampleLength;
	uint32 repeatPoint;
	uint32 repeatLength;
	uint8 volume;
	int8 finetune;
	int8 relativenote;
	uint8 bitsPerSample;
	char name[27];
};

class Instrument
{
public:
	CTOR Instrument()
	{
		name[0] = 0;
		std::memset(noteSample, 0, 120*sizeof(InstrumentSample*));
	}

	~Instrument()
	{
	}

	vector<InstrumentSample*> samples;
	InstrumentSample* noteSample[10*12];	// sample numbers for all notes (C-0 -> B-9)
	char name[27];
};

struct Note
{
	CTOR Note()
	{
		note = 0;
		effect = 0;
		effectparms = 0;
		volume = 0;
		instrument = 0;
	}

	uint16 period;
	uint8 instrument;
	uint8 reserved;
	uint8 note;
	uint8 volume;
	uint8 effect;
	uint8 effectparms;
};

struct Pattern
{
	unsigned int rows;
	Note** notes;
};

class MidiSynth
{
public:
};

class MusicModule : public Object
{
public:
	CTOR MusicModule();

	vector<Instrument*> m_instruments;
	vector<Pattern*> m_patterns;

	unsigned int m_songlength;
	unsigned int m_restartPosition;
	unsigned int m_nchannels;
	unsigned int m_defaultTempo;
	unsigned int m_defaultBPM;
	uint8 m_patternOrder[256];
	char m_name[21];

	bool m_channelEnabled[32];

	bool m_linearFreq;

	uint8 m_patternTempo[128];	// 669 format
	uint8 m_patternBreak[128];	// 669 format

};

class MusicModuleReader : public Object
{
public:
	CTOR MusicModuleReader();
	CTOR MusicModuleReader(StringA* filename);
	CTOR MusicModuleReader(StringW* filename);
	CTOR MusicModuleReader(IO::ISequentialByteStream* stream);

	void Load(StringA* filename);
	void Load(StringW* filename);
	void Load(IO::ISequentialByteStream* stream);

	int ReadXM(IO::ISequentialByteStream* stream);
	int ReadImpulseTracker(IO::ISequentialByteStream* stream);
	int ReadMOD(IO::ISequentialByteStream* stream);
	int ReadMIDI(IO::ISequentialByteStream* stream);
	int Read669(IO::ISequentialByteStream* stream);

	uint8 GETBYTE(IO::ISequentialByteStream* stream);

	MusicModule* m_pModule;

	int nstacked;
	uint8 stackedbyte;
};

class DataSample : public System::Object
{
public:
	CTOR DataSample();
	~DataSample();

	unsigned int AddRef();
	unsigned int Release();

public:

	uint8* copy[64];
	unsigned int length;

protected:

	unsigned int m_refcount;
};

//static const type_info& viewOfType;

class MusicModuleView : public UI::Control//, public IViewOf
{
public:
	CTOR MusicModuleView();

//	FileObject* m_pFile;
	UI::ChildWindowContainer* m_pCanvas;

//	static const type_info& viewOfType;

	MusicModule* m_pMusicModule;
	UI::ScrollViewer* m_pScroller;

	/*
	virtual Object* get_Viewable()
	{
		return m_pFile;
	}

	virtual void put_Viewable(Object* pViewable)
	{
		SetFile(static_cast<FileObject*>(pViewable));
	}
	*/

	void SetModule(MusicModule* pMusicModule);

	double m_divisionsPerMinute;

	MediaShow::WaveOutput* wo;
	ULONG m_masterSamplesPerSec;

	//	LONGLONG m_freq;
	//	LONGLONG startCounter;

	short* m__channeldata[64];

	void Func();

	void Func3();

	static MSWindows::DWORD WINAPI ThreadFunc(void* lpParameter);

	static MSWindows::DWORD WINAPI ThreadFunc1(void* lpParameter);

	static MSWindows::DWORD WINAPI ThreadFunc2(void* lpParameter);

	static MSWindows::DWORD WINAPI ThreadFunc3(void* lpParameter);

	virtual void OnMouseDown(UI::MouseButtonEventArgs* args);
//	virtual void handleEvent(System::Event* evt);

	HANDLE m_hEvent1;
	HANDLE m_hEventPop1;

	HANDLE m_hEvent2;
	HANDLE m_hEventPop2;
	//HANDLE m_hReplyEvent2;

	HANDLE m_hEvent3;
	HANDLE m_hEventPop3;
	//HANDLE m_hReplyEvent3;

	ULONG m_sampleCounter;

	CriticalSection m_mixlock;

	CriticalSection m_lock2;
	CriticalSection m_lock3;

	PatternView* m_pPatternView;
	ScopeView* m_pScopeView;
};

class PatternView : public UI::FrameworkElement
{
public:

	CTOR PatternView()// : font(OLESTR("Courier New"), 12)
	{
	//	m_lock.Init();

		m_currentSongPos = 0;
		m_currentDivision = 0;

//			m_sofar = 0;
//			m_sampleSoFar = 0;

	}

	LDraw::Font* GetFont()
	{
		return UI::Control::GetFont(this);
	}

	virtual LDraw::SizeD MeasureOverride(LDraw::SizeD availSize)
	{
		return LDraw::SizeD(120*4, 64*GetFont()->GetSize());
	}

	void ReceiveSongPos(SongPosition& songpos);

	virtual void OnRender(UI::Graphics* pGraphics);

//		virtual void handleEvent(System::Event* evt);

	void Func1();

	MusicModuleView* m_p;
	//LDraw::Font font;

//	CriticalSection m_lock;

	int m_currentSongPos;
	int m_currentDivision;

	queue<SongPosition> m_songpos;
};

class InstrumentsView : public UI::FrameworkElement
{
public:

	CTOR InstrumentsView()// : font(OLESTR("Courier New"), 14)
	{
	}

	LDraw::Font* GetFont()
	{
		return UI::Control::GetFont(this);
	}

	virtual LDraw::SizeD MeasureOverride(LDraw::SizeD availSize)
	{
		return LDraw::SizeD(300, GetFont()->GetSize() * m_p->m_pMusicModule->m_instruments.size());
	}

	virtual void OnRender(UI::Graphics* pGraphics);

	virtual void OnMouseDown(UI::MouseButtonEventArgs* args);

//		virtual void handleEvent(System::Event* evt);

	MusicModuleView* m_p;
};

class ScopeView : public UI::FrameworkElement
{
public:
	CTOR ScopeView();

	void MixChannels(ULONG samplesToProcess, int nchannels, short* m_channelData[], short* clippedData);

	/*
	void Receive(int nchannel, uint8* data, ULONG datalength)
	{
		m_channelData[nchannel] = (short*)data;
	}
	*/

	void ReceiveMaster(DataSample* sample/*ULONG datalength*/);

protected:

	virtual LDraw::SizeD MeasureOverride(LDraw::SizeD availSize);
	virtual void OnRender(UI::Graphics* pGraphics);

//		virtual void handleEvent(System::Event* evt);

public:

	void Func2();

	/*
	std::queue<uint8*> m_channelCopy[64];
	std::queue<ULONG> m_channelLength;

	std::queue<uint8*> m_masterCopy[64];
	std::queue<ULONG> m_masterLength;
	*/

	MusicModuleView* m_p;
	CriticalSection m_lock;

	ULONG m_scopeSamples;

	int16* m_channelBuffer[64];

	double m_scopeSeconds;
	int m_sofar;
	ULONGLONG m_sampleSoFar;

	int16* m_channelData[64];

	int32* m_masterData;

	queue<DataSample*> m_channelQueue;
	queue<DataSample*> m_masterQueue;

	int16* m_buffer;

	int m_pixelWidth;
};

}

#endif // MusicModule_h
