#ifndef __WAVEOUTPUT_H_
#define __WAVEOUTPUT_H_

#ifndef LMEDIAEXT
#define LMEDIAEXT DECLSPEC_DLLIMPORT
#endif

/*
namespace System
{
namespace MSWindows
{
struct wavehdr_tag;
}
}
*/

#if WIN32

struct IDirectSound8;
struct IDirectSoundBuffer8;

//#include "../LFC/MSWindows.h"

#endif

/*
namespace System
{
namespace MSWindows
{

typedef struct HWAVEOUT__ * HWAVEOUT;
struct tWAVEFORMATEX;

}
}
*/

namespace System
{
namespace MediaShow
{

class LMEDIAEXT WaveOutput
#if WIN32
	: public MSWindows::WindowImpl //<WaveOutput>
#endif
{
public:

	CTOR WaveOutput();
	~WaveOutput();

	ErrorCode Init();
	ErrorCode SetWindow(HWND hWnd);

	ErrorCode SetFormat(const WAVEFORMATEX* wf);
	ErrorCode Receive(const uint8* idata, ULONG ActualDataLength);
	void Run();
	void Pause();

	void Stop();

#if WIN32
	IDirectSoundBuffer8* GetDDSoundBuffer()
	{
		return m_dsBuffer8;
	}
#endif

	bool m_bRunning;
	HANDLE m_hRunEvent;
	HANDLE m_hPauseEvent;

	//LONGLONG m_lastSysTime;
#if AMIGA
	LONGLONG m_lastTime;
#endif

	ULONG m_dwOffset;
	ULONG m_dwBufferBytes;
	tWAVEFORMATEX* m_wf;

	CriticalSection m_lock;

	ULONG GetCurrentPlayCursor();

	int m_n;
	ULONG m_count;

	ULONGLONG m_nLoops;

	void Main();

		HANDLE m_hEvent[2];

	void WaveCallback(UINT uMsg);

#if WIN32
	short* m_channeldata[32];

#ifdef __LERSTAD__
	void* m_hwo;
	void * m_whdr;
#else
	HWAVEOUT m_hwo;
	wavehdr_tag * m_whdr;
#endif
#endif

	uint8* m_buffer;

	unsigned int m_nbuffer;
	unsigned int m_nbuffers;
	bool m_bReady;

protected:


#if WIN32

	virtual bool ProcessWindowMessage(MSWindows::Hwnd hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult/*, ULONG dwMsgMapID*/ );

	IDirectSound8* m_ds8;
	IDirectSoundBuffer8* m_dsBuffer8;
	//HANDLE m_hEvent2;

	//HANDLE m_replyEvent;
	HANDLE m_replyEvent2;

//	ULONGLONG m_currentPlayCursor;

#elif AMIGA

	struct MsgPort    *m_AHImp;
	struct AHIRequest *m_AHIio;
	struct AHIRequest *m_AHIio2;

	struct AHIRequest *m_req;
	struct AHIRequest *m_req2;

#endif

};

}	// MediaShow
}

#endif // __WAVEOUTPUT_H_
