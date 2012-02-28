#include "stdafx.h"
#include "LMediaImpl.h"
#include "WaveOutput.h"

#if AMIGA
#include "../amiga_header.h"
#endif

extern "C"
{

#if AMIGA
#include <devices/ahi.h>
//#include <proto/ahi.h>
#endif

}

#if WIN32
//#include "../include/windows_header.h"

#if 0
#pragma comment(lib, "Dxguid.lib")

#define DIRECTSOUND_VERSION 0x0800  /* Version 8.0 */
#include <mmsystem.h>
#include <mmreg.h>
#include <dsound.h>

#pragma comment(lib, "dsound.lib")

#endif

#pragma comment(lib, "winmm.lib")

//#include <mmsystem.h>

#endif

namespace System
{
namespace MediaShow
{

#if AMIGA
LONGLONG GetCurrentSysTime();
#endif

WaveOutput::WaveOutput()
{
	m_dwOffset = 0;
	m_bRunning = false;
	m_nLoops = 0;

	m_bReady = false;

#if WIN32

	m_whdr = (wavehdr_tag*)HeapAlloc(GetProcessHeap(), 0, sizeof(wavehdr_tag)* 200 );

	m_ds8 = NULL;
	m_dsBuffer8 = NULL;

	m_hPauseEvent = CreateEventA(NULL, false, false, NULL);
	m_hRunEvent = CreateEventA(NULL, false, false, NULL);

#elif AMIGA

	m_AHImp = NULL;
	m_AHIio = NULL;

#endif
}

WaveOutput::~WaveOutput()
{
#if WIN32

	if (m_hwo)
	{
		MSWindows::waveOutClose(m_hwo);
	}

	HeapFree(GetProcessHeap(), 0, m_whdr);

#endif
}

ErrorCode WaveOutput::Init()
{
#if 0
#if WIN32
	ErrorCode hr;
	hr = DirectSoundCreate8(NULL, &m_ds8, NULL);
	ASSERT(SUCCEEDED(hr));

//	RECT rc = {0,0,0,0};
	Create(NULL, LDraw::Rect(), NULL, WS_POPUP);
	SetWindow(m_hWnd);
	return hr;

#elif AMIGA

  /* Send commands to the device here...
{
{
      if(! CheckIO((struct IORequest *) AHIio))
      {
        AbortIO((struct IORequest *) AHIio);
      }

      WaitIO((struct IORequest *) AHIio);

      CloseDevice((struct IORequest *) AHIio);
      AHIDevice = -1;
    }
    DeleteIORequest((struct IORequest *) AHIio);
    AHIio = NULL;
  }
  DeleteMsgPort(AHImp);
  AHImp = NULL;
  */
	return S_OK;
#endif

//	GetSystemTimeAsFileTime((FILETIME*)&m_lastSysTime);
//	m_lastSysTime = GetTickCount()*1000;
#endif
	return 0;
}

ErrorCode WaveOutput::SetWindow(HWND hWnd)
{
	ASSERT(0);
	return 0;
#if 0
#if WIN32
	ErrorCode hr = m_ds8->SetCooperativeLevel(hWnd, /*DSSCL_PRIORITY*/DSSCL_NORMAL);
	ASSERT(SUCCEEDED(hr));
	return hr;
#else
	return 0;
#endif
#endif
}

#if WIN32

#if 0
DWORD WINAPI PP(void* lpParameter)
{
	WaveOutput* p = (WaveOutput*)lpParameter;

	p->Main();

	return 0;
}
#endif


void CALLBACK MyWaveOutProc(
  HWAVEOUT hwo,      
  UINT uMsg,
  DWORD dwInstance,  
  DWORD dwParam1,    
  DWORD dwParam2     
)
{
	WaveOutput* wo = (WaveOutput*)dwInstance;

	wo->WaveCallback(uMsg);
}

void WaveOutput::WaveCallback(UINT uMsg)
{
	if (uMsg == WOM_DONE)
	{
#if 1
		waveOutWrite(m_hwo, &m_whdr[m_nbuffer], sizeof(WAVEHDR));
		m_nbuffer++;
		if (m_nbuffer == m_nbuffers)
		{
			m_nbuffer = 0;
		}
#endif

		SetEvent(m_hEvent[0]);
	}
}

bool WaveOutput::ProcessWindowMessage(MSWindows::Hwnd hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult/*, DWORD dwMsgMapID*/ )
{
	if (uMsg == MM_WOM_DONE)
	{
		waveOutWrite(m_hwo, &m_whdr[m_nbuffer], sizeof(WAVEHDR));
		m_nbuffer++;
		if (m_nbuffer == m_nbuffers)
		{
			m_nbuffer = 0;
		}

		SetEvent(m_hEvent[0]);

		return true;
	}
	return false;
}

#endif	// WIN32

ErrorCode WaveOutput::SetFormat(const WAVEFORMATEX* wf)
{
	ErrorCode hr;

	m_wf = new WAVEFORMATEX;
	*m_wf = *wf;
	//	if (m_wf->wFormatTag == WAVE_FORMAT_PCM)
		//m_wf.nAvgBytesPerSec = m_wf.nSamplesPerSec * m_wf.nBlockAlign;

	m_nbuffers = 100;
//	m_nbuffers = 200;

	ASSERT(m_nbuffers <= 200);

//	ULONG nBufferSamples = m_wf->nSamplesPerSec * 2;	// We buffer 2 seconds
//	ULONG nBufferSamples = m_wf->nSamplesPerSec * 4;	// We buffer 1 seconds
	ULONG nBufferSamples = 200;//256*96;	// Test

	m_nbuffers = 2;
	nBufferSamples = m_wf->nSamplesPerSec * 2;

	m_dwBufferBytes = nBufferSamples*m_wf->nBlockAlign;	// Bytes used by one buffer

#if WIN32
	if (true)
	{
		m_hwo = NULL;

		m_hEvent[0] = CreateEventW(NULL, false, false, NULL);

		/*
		ASSERT(m_hWnd == NULL);
		Create(NULL, LDraw::Rect(), NULL, WS_POPUP);
		ASSERT(m_hWnd);
		*/

	//	MMRESULT result = waveOutOpen(&m_hwo, WAVE_MAPPER, m_wf, (DWORD)m_hWnd/*MyWaveOutProc*/, (DWORD)this, CALLBACK_WINDOW/*CALLBACK_FUNCTION*/);
		MMRESULT result = waveOutOpen(&m_hwo, WAVE_MAPPER, m_wf, (DWORD_PTR)MyWaveOutProc, (DWORD_PTR)this, CALLBACK_FUNCTION);
		ASSERT(result == 0);

		m_buffer = (uint8*)HeapAlloc(GetProcessHeap(), 0, m_dwBufferBytes*m_nbuffers);

		for (size_t i = 0; i < m_nbuffers; ++i)
		{
			m_whdr[i].lpData = (LPSTR)(m_buffer + m_dwBufferBytes*i);
			m_whdr[i].dwBufferLength = m_dwBufferBytes;
			m_whdr[i].dwFlags = 0;
			m_whdr[i].dwLoops = 0;
			m_whdr[i].lpNext = NULL;	// reserved
			m_whdr[i].reserved = 0;	// reserved

			result = waveOutPrepareHeader(m_hwo, &m_whdr[i], sizeof(WAVEHDR));
			ASSERT(result == 0);
			if (result != 0)
			{
				char msg[MAXERRORLENGTH];

				waveOutGetErrorTextA(result, msg, 1204);

				MessageBoxA(NULL, "waveOutPrepareHeader Error", msg, MB_OK);
				return Error_Failed;
			}
		}

		m_nbuffer = 0;
	}
	else
	//m_lock.Lock();
//	if (m_dsBuffer8 == NULL)
	{
#if 0
	// Set up DSBUFFERDESC structure. 
		DSBUFFERDESC dsbdesc;

		memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); 
		dsbdesc.dwSize = sizeof(DSBUFFERDESC);
		dsbdesc.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY; 
		dsbdesc.dwFlags |= DSBCAPS_GLOBALFOCUS;

		dsbdesc.dwBufferBytes = m_dwBufferBytes*2;	// We double-buffer
		dsbdesc.lpwfxFormat = m_wf;

		// Create buffer. 
		
		IDirectSoundBuffer* dsBuffer;
		hr = m_ds8->CreateSoundBuffer(&dsbdesc, &dsBuffer, NULL); 
		if (FAILED(hr))
		{
			ASSERT(0);
			return hr;
		}

		dsBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&m_dsBuffer8);
		if (m_dsBuffer8 == NULL)
		{
			ASSERT(0);
			return Error_NoInterface;
		}

	//			CreateStreamOnHGlobal(NULL, TRUE, &m_pFilter->m_stream);

		IDirectSoundNotify8* notify8;
		m_dsBuffer8->QueryInterface(IID_IDirectSoundNotify, (void**)&notify8);
		if (notify8 == NULL)
		{
			ASSERT(0);
			return E_NOINTERFACE;
		}

		m_hEvent[0] = CreateEvent(NULL, false, false, NULL);
		if (m_hEvent[0] == NULL)
		{
			ASSERT(0);
			return E_FAIL;
		}

		m_hEvent[1] = CreateEvent(NULL, false, false, NULL);
		if (m_hEvent[1] == NULL)
		{
			ASSERT(0);
			return E_FAIL;
		}

		m_dwOffset = 0;

		DSBPOSITIONNOTIFY ps[2];
		ps[0].dwOffset = 0;
		ps[0].hEventNotify = m_hEvent[0];
		ps[1].dwOffset = m_dwBufferBytes;//nsamples*m_wf->nBlockAlign;//2*m_wf.nAvgBytesPerSec;
		ps[1].hEventNotify = m_hEvent[0]/*[1]*/;

		if (notify8->SetNotificationPositions(2, ps) != DS_OK)
		{
			ASSERT(0);
			return Error_Fail;
		}
		notify8->Release();
#endif
	}

	/*
	m_hEvent[2] = CreateEvent(NULL, false, false, NULL);
	if (m_hEvent[2] == NULL)
	{
		ASSERT(0);
		return E_FAIL;
	}

	m_replyEvent = CreateEvent(NULL, false, false, NULL);
	if (m_replyEvent == NULL)
	{
		ASSERT(0);
		return E_FAIL;
	}
	*/

	m_replyEvent2 = CreateEventA(NULL, false, false, NULL);
	if (m_replyEvent2 == NULL)
	{
		ASSERT(0);
		return Error_Failed;
	}

#elif AMIGA

	m_buffer = new uint8[m_dwBufferBytes*2];

#endif

	/*
	DWORD threadID;
	CreateThread(NULL, 0, PP, (void*)this, 0, &threadID);
	*/
	return Success;
}

#if 0
void WaveOutput::Main()
{
	m_count = 0;
	while (1)
	{
		int n;
		while ((n = (WaitForMultipleObjects(2, m_hEvent, false, INFINITE) - WAIT_OBJECT_0)) == 2)
		{
#if 0
		//	m_lock.Lock();

			DWORD dwCurrentPlayCursor;
			DWORD dwCurrentWriteCursor;
			ErrorCode hr = GetDDSoundBuffer()->GetCurrentPosition(&dwCurrentPlayCursor, &dwCurrentWriteCursor);
			m_currentPlayCursor = m_nLoops + dwCurrentPlayCursor;
			if (dwCurrentPlayCursor < m_count)
			{
				m_currentPlayCursor += m_dwBufferBytes;
				MessageBeep(-1);
			}

			SetEvent(m_replyEvent);
#endif
		//	m_lock.Unlock();
		}

		m_lock.Lock();

		if (n == 0)
		{
			if (m_bReady)
			{
				m_nLoops += m_dwBufferBytes*2;
			}
		}

		if (n == 1)
		{
			m_count = m_dwBufferBytes;
		}
		else
			m_count = 0;

		m_n = n;
		m_lock.Unlock();

		{
			SetEvent(m_replyEvent2);
		}
	}
}
#endif

ErrorCode WaveOutput::Receive(const uint8* idata, ULONG ActualDataLength)
{

#if AMIGA
	if (m_AHIio == NULL)
	{
		// This must be done in same task as we do WaitIO

		int8               AHIDevice  = -1;
		uint8              unit       = AHI_DEFAULT_UNIT;

		m_AHImp = CreateMsgPort();
		m_AHIio = (struct AHIRequest *)CreateIORequest(m_AHImp, sizeof(struct AHIRequest));

		if (m_wf->wBitsPerSample == 8)
		{
			if (m_wf->nChannels == 1)
			{
				m_AHIio->ahir_Type = AHIST_M8S;
			}
			else if (m_wf->nChannels == 2)
			{
				m_AHIio->ahir_Type = AHIST_S8S;
			}
			else
				ASSERT(0);
		}
		else if (m_wf->wBitsPerSample == 16)
		{
			if (m_wf->nChannels == 1)
			{
				m_AHIio->ahir_Type = AHIST_M16S;
			}
			else if (m_wf->nChannels == 2)
			{
				m_AHIio->ahir_Type = AHIST_S16S;
			}
			else
				ASSERT(0);
		}
		else
			ASSERT(0);

		m_AHIio->ahir_Version = 4;
		AHIDevice = OpenDevice(AHINAME, unit, (struct IORequest *) m_AHIio, NULL);

		// For double buffering
		m_AHIio2 = (struct AHIRequest *)execAllocMem(SysBase, sizeof(struct AHIRequest), MEMF_PUBLIC);
		memcpy(m_AHIio2, m_AHIio, sizeof(struct AHIRequest));

		m_req = m_AHIio;
		m_req2 = NULL;
	}
#endif

	ErrorCode hr;
#if 0
	m_lock.Lock();
#endif

	ULONG nbytesSoFar = 0;
	while (nbytesSoFar < ActualDataLength)
	{
		ULONG nbytes;


	// Try to fill the rest of the buffer (either the first or second buffer)
/*
		if (m_dwOffset < m_dwBufferBytes)	// first buffer
			nbytes = m_dwBufferBytes-m_dwOffset;
		else		// second buffer
			nbytes = m_dwBufferBytes*2-m_dwOffset;
*/
		ULONG upper = ((m_dwOffset+m_dwBufferBytes) / m_dwBufferBytes)*m_dwBufferBytes;
		nbytes = upper - m_dwOffset;

	// Limit it to what is available/left in sample
		if (nbytes > ActualDataLength - nbytesSoFar)
		{
			nbytes = ActualDataLength - nbytesSoFar;
		}

		// Probably doesn't matter, but we check here that we're copying an integral number of samples
		ASSERT(((nbytes / m_wf->nBlockAlign)*m_wf->nBlockAlign) == nbytes);

#if WIN32

//	#ifdef _DEBUG	// Remove this if you're single step debugging
//#if 0	// Remove this if you're single step debugging

#if 0
		DWORD dwCurrentPlayCursor;
		DWORD dwCurrentWriteCursor;
		hr = m_dsBuffer8->GetCurrentPosition(&dwCurrentPlayCursor, &dwCurrentWriteCursor);
		ASSERT(SUCCEEDED(hr));
#endif

		ULONG dwbuffer1;
		uint8* buffer1;

		ULONG dwbuffer2;
		uint8* buffer2;

#if 0
		if (m_dwOffset < dwCurrentWriteCursor)
		{
			ASSERT(m_dwOffset < dwCurrentPlayCursor);
		}
		else
		{
			ASSERT(m_dwOffset >= dwCurrentWriteCursor);
		}
#endif
//#endif

		if (true)
		{
			uint8* buffer1 = m_buffer + m_dwOffset;
			uint32 dwbuffer1 = nbytes;

			if (m_wf->wBitsPerSample == 8)	// signed -> unsigned
			{
				char* dst = (char*)buffer1;
				const char* src = (const char*)idata+nbytesSoFar;
				for (size_t i = 0; i < dwbuffer1; ++i)
				{
					*dst = *src + 128;
					dst++;
					src++;
				}
			}
			else
			{
				std::memcpy(buffer1, idata+nbytesSoFar, dwbuffer1);
			}
			nbytesSoFar += dwbuffer1;
		}
		else
		{
#if 0
			hr = m_dsBuffer8->Lock(m_dwOffset, nbytes, (void**)&buffer1, &dwbuffer1, (void**)&buffer2, &dwbuffer2, 0);
			if (SUCCEEDED(hr))
			{
				ASSERT(dwbuffer1 == nbytes);

				ASSERT(!IsBadWritePtr(buffer1, dwbuffer1));
				ASSERT(!IsBadReadPtr(idata+nbytesSoFar, dwbuffer1));

				ASSERT(nbytesSoFar+dwbuffer1 <= ActualDataLength);

				memcpy(buffer1, idata+nbytesSoFar, dwbuffer1);
				nbytesSoFar += dwbuffer1;

				ASSERT(buffer2 == NULL);
				/*
				if (buffer2)
				{
					CopyMemory(buffer2, pSample->m_pointer+nbytesSoFar, dwbuffer2);
					nbytesSoFar += dwbuffer2;
				}
				*/

				m_dsBuffer8->Unlock(buffer1, dwbuffer1, buffer2, dwbuffer2);
			}
			else
				ASSERT(0);
#endif
		}

#elif AMIGA

		//ASSERT(nbytesSoFar+dwbuffer1 <= ActualDataLength);

		uint8* buffer1 = m_buffer + m_dwOffset;
		uint32 dwbuffer1 = nbytes;

		memcpy(buffer1, idata+nbytesSoFar, dwbuffer1);
		nbytesSoFar += dwbuffer1;

#endif

		m_dwOffset += nbytes;

	//	ASSERT(m_dwOffset <= 2*m_dwBufferBytes);

		if (m_dwOffset == m_nbuffers*m_dwBufferBytes)
			m_dwOffset = 0;	// Wrap around to first buffer

		if ((m_dwOffset % m_dwBufferBytes) == 0)	// A buffer has been completely filled
		{
#if WIN32

			if (true)
			{
				if (!m_bReady)
				{
					m_bReady = true;
					MMRESULT result = waveOutWrite(m_hwo, &m_whdr[0], sizeof(WAVEHDR));
					ASSERT(result == 0);

					// This one isn't filled yet, but it'll probably be filled by the time buffer 0 is done (and this one starts automatically)
					result = waveOutWrite(m_hwo, &m_whdr[1], sizeof(WAVEHDR));
					ASSERT(result == 0);

					if (!m_bRunning)
					{
						SetEvent(m_hPauseEvent);
					}
				}
				else
				{
					WaitForSingleObject(m_hEvent[0], INFINITE);
				}
			}
			else
			{
#if 0
				DWORD status;
				m_dsBuffer8->GetStatus(&status);

				if (!(status & DSBSTATUS_PLAYING))
				{
					// If it's not yet playing, wait til we've filled half the
					// buffer before starting to play
					if (m_dwOffset == m_dwBufferBytes)
					{
						if (!m_bRunning)
						{
							SetEvent(m_hPauseEvent);
							m_lock.Unlock();
							WaitForSingleObject(m_hRunEvent, INFINITE);
					//	m_lock.Lock();
						}

						ErrorCode hr = m_dsBuffer8->Play(0, 0, DSBPLAY_LOOPING);
						ASSERT(SUCCEEDED(hr));

			//		m_lock.Unlock();
						WaitForSingleObject(m_hEvent[0], INFINITE);	// This should return immediately now
	#if 0
						WaitForSingleObject(m_replyEvent2, INFINITE);
	#endif

			//		m_lock.Lock();
					//	m_lastSysTime = GetTickCount() * 1000;
					}
					else
					{
						ASSERT(0);	// ??
						m_nLoops++;	// Completed playing a buffer
				//		m_lastSysTime = GetTickCount() * 1000;
					}
					//	GetSystemTimeAsFileTime((FILETIME*)&m_lastSysTime);
				}
				else
				{
				//	WaitForSingleObject(m_hEvent, INFINITE);
					m_lock.Lock();
					m_bReady = true;

					m_lock.Unlock();

	#if 0
					WaitForSingleObject(m_replyEvent2, INFINITE);
	#endif
					WaitForSingleObject(m_hEvent[0], INFINITE);
				//	int n;
				//	n = WaitForMultipleObjects(2, m_hEvent, false, INFINITE) - WAIT_OBJECT_0;
					{
	#if 0
					//	m_lock.Lock();

						DWORD dwCurrentPlayCursor;
						DWORD dwCurrentWriteCursor;
						ErrorCode hr = GetDDSoundBuffer()->GetCurrentPosition(&dwCurrentPlayCursor, &dwCurrentWriteCursor);
						m_currentPlayCursor = dwCurrentPlayCursor;
						SetEvent(m_replyEvent);
					//	m_lock.Unlock();
	#endif
					}

	#if 0
					m_lock.Lock();
	#endif

				//	if (m_dwOffset == m_dwBufferBytes)
				//	if (n == 0)
					if (m_dwOffset == m_dwBufferBytes)
					{
						/*
						DWORD dwCurrentPlayCursor;
						DWORD dwCurrentWriteCursor;
						ErrorCode hr = GetDDSoundBuffer()->GetCurrentPosition(&dwCurrentPlayCursor, &dwCurrentWriteCursor);

						ASSERT(dwCurrentWriteCursor < m_dwBufferBytes);
						*/

						m_lock.Lock();
					//	m_nLoops++;	// Completed playing two buffers

						m_nLoops += m_dwBufferBytes*2;
						m_lock.Unlock();
					}
				}
#endif
			}
#elif AMIGA

			m_req->ahir_Std.io_Command = CMD_WRITE;
			if (m_dwOffset == 0)
				m_req->ahir_Std.io_Data = m_buffer + m_dwBufferBytes;
			else
				m_req->ahir_Std.io_Data = m_buffer;

			m_req->ahir_Std.io_Length = m_dwBufferBytes;//ActualDataLength;
			m_req->ahir_Std.io_Offset = 0;

			m_req->ahir_Frequency = m_wf->nSamplesPerSec;
			m_req->ahir_Volume = 0x00010000;	// 1
			m_req->ahir_Position = 0x00008000;	// 0.5 Center
			m_req->ahir_Link = m_req2;
			SendIO((struct IORequest *)m_req);	// This will start playing when req2 is done or immediately if first time

			if (m_req2)
			{
				WaitIO((struct IORequest *)m_req2);
				m_nLoops++;	// Completed playing a buffer
				m_lastTime = GetCurrentSysTime();
			}
			else
				m_req2 = m_AHIio2;

			// swap
			AHIRequest * temp = m_req;
			m_req = m_req2;
			m_req2 = temp;

			/*
			m_req2 = m_req;
			m_req2->ahir_Link = m_req;
			m_req = m_req2;
			*/
#endif
		}
	}

#if 0
	m_lock.Unlock();
#endif
	return Success;
}

void WaveOutput::Stop()
{
	ASSERT(0);
#if 0
	ULONG nbytes;

#if WIN32
	if (m_hwo)
	{
		waveOutReset(m_hwo);
		WaitForSingleObject(m_hEvent[0], INFINITE);
	}
	else
	{
	// Fill rest of buffer with silence
	// Try to fill the rest of the buffer (either the first or second buffer)
		if (m_dwOffset < m_dwBufferBytes)	// first buffer
			nbytes = m_dwBufferBytes-m_dwOffset;
		else		// second buffer
			nbytes = m_dwBufferBytes*2-m_dwOffset;

		/*
	// Limit it to what is available/left in sample
		if (nbytes > ActualDataLength - nbytesSoFar)
		{
			nbytes = ActualDataLength - nbytesSoFar;
		}
		*/

		DWORD dwbuffer1;
		LPBYTE buffer1;

		DWORD dwbuffer2;
		LPBYTE buffer2;

		ErrorCode hr = m_dsBuffer8->Lock(m_dwOffset, nbytes, (void**)&buffer1, &dwbuffer1, (void**)&buffer2, &dwbuffer2, 0);
		if (SUCCEEDED(hr))
		{
			ASSERT(dwbuffer1 == nbytes);

		//	ASSERT(!IsBadWritePtr(buffer1, dwbuffer1));
		//	ASSERT(!IsBadReadPtr(idata+nbytesSoFar, dwbuffer1));

		//	ASSERT(nbytesSoFar+dwbuffer1 <= ActualDataLength);

			memset(buffer1, 128/*idata+nbytesSoFar*/, dwbuffer1);
		}

		m_dwOffset += nbytes;

		ASSERT(m_dwOffset <= 2*m_dwBufferBytes);

		if (m_dwOffset == 2*m_dwBufferBytes)
			m_dwOffset = 0;	// Wrap around to first buffer

		ASSERT(m_dwOffset == 0 || m_dwOffset == m_dwBufferBytes);

	//	if (m_dwOffset == 0 || m_dwOffset == m_dwBufferBytes)	// A buffer has been completely filled
		{
				WaitForSingleObject(m_hEvent[0], INFINITE);
		}

		m_dsBuffer8->Stop();
	}
#endif
#endif
}

ULONG WaveOutput::GetCurrentPlayCursor()
{
//	DWORD status;
//	m_dsBuffer8->GetStatus(&status);

#if WIN32
	if (true)
	{
		MMTIME mmtime;
		mmtime.wType = TIME_SAMPLES;
		MMRESULT result = waveOutGetPosition(m_hwo, &mmtime, sizeof(MSWindows::MMTIME));
		ASSERT(result == 0);

		return mmtime.u.sample;
	}

#if 0
//	m_lock.Lock();
	bool bReady = m_bReady;
//	m_lock.Unlock();

	if (bReady/*status & DSBSTATUS_PLAYING*/)
	{

		DWORD dwCurrentPlayCursor;
		DWORD dwCurrentWriteCursor;
		ErrorCode hr = GetDDSoundBuffer()->GetCurrentPosition(&dwCurrentPlayCursor, &dwCurrentWriteCursor);
	//m_lock.Lock();
		ULONGLONG currentPlayCursor = m_nLoops + dwCurrentPlayCursor;
		/*
		if (dwCurrentPlayCursor < m_count)
		{
			currentPlayCursor += m_dwBufferBytes;
			MessageBeep(-1);
		}
		*/

		/*
		SetEvent(m_hEvent[2]);
		WaitForSingleObject(m_replyEvent, INFINITE);
		*/

	//	m_lock.Unlock();

		return currentPlayCursor;
	}
	else
	{
//		m_lock.Unlock();
		return 0;
	}
#endif
#endif
	return 0;
}

void WaveOutput::Run()
{
	m_bRunning = true;

//	ErrorCode hr = m_dsBuffer8->Play(0, 0, DSBPLAY_LOOPING);
//	ASSERT(SUCCEEDED(hr));
#if WIN32
	SetEvent(m_hRunEvent);
#endif
}

void WaveOutput::Pause()
{
	//ASSERT(0);
#if 0

	if (m_bRunning)
	{
		m_bRunning = false;
#if WIN32
		if (m_dsBuffer8)
		{
			ErrorCode hr = m_dsBuffer8->Stop();
			ASSERT(hr == DS_OK);
		}
#endif
	}
	else
	{
#if WIN32
		WaitForSingleObject(m_hPauseEvent, INFINITE);
#endif

#if AMIGA
	m_lastTime = GetCurrentSysTime();	// Not here ??
#endif
	}
#endif
}

}	// MediaShow
}
