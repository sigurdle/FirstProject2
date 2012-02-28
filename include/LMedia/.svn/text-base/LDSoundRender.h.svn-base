#ifndef __LDSOUNDRENDER_H_
#define __LDSOUNDRENDER_H_

#include "LMediaImpl.h"
#include "WaveOutput.h"

namespace System
{
namespace MediaShow
{

class CLDSoundRender : 
	public BaseFilterImpl,
	public IMediaSeeking,
	public IReferenceClock,
	public IDirectSound
{
public:
	class CInputPin : 
		public BasePinImpl,
		public IMemInputPin
	{
	public:
		class CMemAllocator : 
			public IMemAllocator
		{
		public:
			class CAudioSample : 
				public MediaSampleImpl<IMediaSample>
			{
			public:
				CTOR CAudioSample()
				{
				//	m_mediaType = NULL;
					m_pointer = NULL;

					m_dwRef = 0;
				}

				~CAudioSample()
				{
					if (m_pointer)
					{
						delete[] m_pointer;
						m_pointer = NULL;
					}
				}

				uint8* m_pointer;
				ULONG m_dwBytes;
				ULONG m_ActualDataLength;

				ULONG m_dwRef;

				ULONG AddRef()
				{
					m_dwRef++;
					return m_dwRef;
				}

				ULONG Release()
				{
					ASSERT(m_dwRef > 0);
					m_dwRef--;
					if (m_dwRef == 0)
					{
						delete this;
						return 0;
					}

					return m_dwRef;
				}

				virtual ErrorCode LockBits(LSampleData* pVal)
				{
					pVal->idata = m_pointer;

					/*
					ULONG nSamples;
					m_mediaType->GetSamples(&nSamples);

					ErrorCode hr = m_pInput->m_dsBuffer8->Lock(m_pInput->m_dwOffset, nSamples*m_pInput->m_wf.nBlockAlign, (void**)&buffer1, &dwbuffer1, (void**)&buffer2, &dwbuffer2, 0);
					ASSERT(SUCCEEDED(hr));

					*pVal = (LPBYTE)buffer1;
					*/

					return 0;
				}

				ErrorCode UnlockBits()
				{
					/*
					m_pInput->m_dsBuffer8->Unlock(buffer1, dwbuffer1, buffer2, dwbuffer2);
					*/
					return 0;
				}

				virtual ErrorCode GetMediaType(MediaType *ppmt)
				{
					ASSERT(0);
					return 0;
					//*pVal = m_mediaType;
					//(*pVal)->AddRef();
				}

				virtual ULONG GetActualDataLength()
				{
					return m_ActualDataLength;
				}
				virtual ErrorCode SetActualDataLength(ULONG length)
				{
					// TODO
					if (length > m_dwBytes)
					{
						ASSERT(0);
						return MEDIA_E_BUFFER_OVERFLOW;
					}

					m_ActualDataLength = length;

					return 0;
				}

			public:

				CInputPin* m_pInput;
				//ILAudioMediaType* m_mediaType;
				/*
				ULONG dwbuffer1;
				LPBYTE buffer1;

				ULONG dwbuffer2;
				LPBYTE buffer2;
				*/
			};

			CTOR CMemAllocator()
			{
				m_pInput = NULL;
			}

			virtual ErrorCode GetBuffer(ULONG dwBytes, IMediaSample* *pVal)
			{
				CAudioSample* pSample = new CAudioSample;
				pSample->AddRef();
			//	CComObject<CAudioSample>::CreateInstance(&pSample);
			//	pSample->AddRef();

				pSample->m_pInput = m_pInput;
				//pSample->m_mediaType = m_pInput->m_mediaType;

				pSample->m_pointer = new uint8[dwBytes];
				pSample->m_dwBytes = dwBytes;
				pSample->m_ActualDataLength = dwBytes;

				//m_

				*pVal = pSample;

				return 0;
			}

			virtual ErrorCode ReleaseBuffer(IMediaSample* pBuffer)
			{
				if (static_cast<CAudioSample*>(pBuffer)->m_pointer)
				{
					delete[] static_cast<CAudioSample*>(pBuffer)->m_pointer;
					static_cast<CAudioSample*>(pBuffer)->m_pointer = NULL;
				}
				return 0;
			}

		public:
			CInputPin* m_pInput;
		};

		CTOR CInputPin() : BasePinImpl(PINDIR_INPUT)
		{
			m_pFilter = NULL;

			m_pAllocator = new CMemAllocator;
			m_pAllocator->m_pInput = this;

			m_wo = new WaveOutput;
			m_wo->Init();
		}

		~CInputPin()
		{
			if (m_pAllocator)
			{
				delete m_pAllocator;
				m_pAllocator = NULL;
			}
		}

		inline CLDSoundRender* GetFilter() const
		{
			return (CLDSoundRender*)m_pFilter;
		}

		virtual ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Audio)
				return Error;

			if (mt->GetSubType() != GUID_NULL)	// TODO
				return Error;

			const WaveFormat* pwfx = (const WaveFormat*)mt->GetFormat();
			if (pwfx->wf->wFormatTag != WAVE_FORMAT_PCM)
				return Error;

			return 0;
		}

		virtual ErrorCode CompleteConnect(IPin* pConnector)
		{
			ErrorCode hr = BasePinImpl::CompleteConnect(pConnector);
			if (hr < 0) return hr;
#if 0
			CComQIPtr<ILAudioMediaType> audioType = pMediaType;
			m_mediaType = audioType;
#endif

		//	ErrorCode hr; 
			
			// Set up wave format structure. 
			//memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT)); 
			//pcmwf = *(PCMWAVEFORMAT*)&m_wavfmt;
			/*
			m_wf.wFormatTag = WAVE_FORMAT_PCM; 
			m_wf.nChannels = 2;
			m_wf.nSamplesPerSec = 22050;
			m_wf.nBlockAlign = 2; 
			m_wf.nAvgBytesPerSec = m_wf.nSamplesPerSec * m_wf.nBlockAlign; 
			m_wf.wBitsPerSample = 8; 
			m_wf.cbSize = 0;
			*/
			//if (m_pmt.->format != FORMAT_WaveFormatEx)
						//	m_pmt = NULL;

			//m_wf = ;

			return m_wo->SetFormat(((const WaveFormat*)m_mt->GetFormat())->wf);
		}

		virtual IMemAllocator* GetAllocator()
		{
			return m_pAllocator;
		}

		virtual ErrorCode_Bool Receive(IMediaSample *sample);

		virtual ErrorCode EndOfStream();

		virtual ErrorCode Run(LONGLONG tStart)
		{
			m_wo->Run();
			return 0;
		}

		virtual ErrorCode Pause()
		{
			m_wo->Pause();
			return 0;
		}

	public:
		friend class CLDSoundRender;

		CriticalSection m_pLock;

		CMemAllocator* m_pAllocator;

		WaveOutput* m_wo;

		LONGLONG m_lastTimeStart;
		LONGLONG m_lastTimeEnd;
	};

	//ULONG m_dwCurrentPlayCursor;

	CLDSoundRender();

	CInputPin* m_pInput;

	struct AdviseData
	{
		CLDSoundRender* pClock;
		LONGLONG rt;
		HANDLE hEvent;
		HANDLE hTimer;
	};

	AdviseData* m_pNewAdvise;
//	ULONG m_dwTimerThreadId;
//	HANDLE m_hTimerThread;

//	static void CALLBACK EventProc(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)

#if 0
	static void CALLBACK timerCompletionRoutine(
	  LPVOID lpArgToCompletionRoutine,
	  ULONG dwTimerLowValue,
	  ULONG dwTimerHighValue
	)
	{
#if 0
		LONGLONG timerValue = ((LONGLONG)dwTimerLowValue | (LONGLONG)dwTimerHighValue<<32);

		// This is called on the same thread that set the timer
		AdviseData* adv = (AdviseData*)lpArgToCompletionRoutine;
//		PostThreadMessage(p->pClock->m_dwTimerThreadId, WM_USER+1, (WPARAM)p, 0);

		CLDSoundRender* p = adv->pClock;

#if 0
		LONGLONG curtime;
		p->GetTime(&curtime);
	//	TRACE("%d\n", (ULONG)curtime);

		LONGLONG attime = adv->rt;

	//	p->m_timers.erase(p->m_advise.begin()+n);
	//	CloseHandle(adv-

		LONGLONG uDelay = (attime - curtime);
	//	if (uDelay <= 0)	// Time has passed, signal the event
#endif
		{
			//p->m_advise.erase(p->m_advise.begin()+n);

			if (adv->hTimer)
			{
			//	CancelWaitableTimer(adv->hTimer);
			//	CloseHandle(adv->hTimer);
				adv->hTimer = NULL;
			}

			SetEvent(adv->hEvent);
		}
#if 0
		else
		{
		//	HANDLE hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
			// Hasn't passed yet, set a timer for estimated time

			// to 100 ns (relative)
			LARGE_INTEGER li;
			li.QuadPart = -(uDelay*100);

			if (adv->hTimer == NULL)
				adv->hTimer = p->m_hTimers[p->m_nTimer & 0xF];// CreateWaitableTimer(NULL, FALSE, NULL);
			ASSERT(adv->hTimer);
			BOOL bSucc = SetWaitableTimer(adv->hTimer, &li, 0, timerCompletionRoutine, (LPVOID)adv, FALSE);
			ASSERT(bSucc);

		//	ULONG nTimerID = timeSetEvent(uDelay, 0, EventProc, (ULONG)adv, TIME_ONESHOT | TIME_CALLBACK_FUNCTION);
		//	WaitForSingleObject(hEvent2, INFINITE);
		//	CloseHandle(hEvent2);

			/*
			if (pdwAdviseCookie)
				*pdwAdviseCookie = nTimerID;
				*/
		}
#endif
#endif
	}
#endif

	vector<AdviseData*> m_advise;

	HANDLE m_hWakeupEvent;
	HANDLE m_hGotWakeupEvent;
	HANDLE m_hTimers[16];
	int m_nTimer;

	CriticalSection m_clockcrit;

#if AMIGA
//	struct timerequest* m_timereq;
#endif

#if 0
	static ULONG WINAPI TimerThread(LPVOID lpData)
	{
		CLDSoundRender* p = (CLDSoundRender*)lpData;

		for (int i = 0; i < 16; i++)
		{
			p->m_hTimers[i] = CreateWaitableTimer(NULL, FALSE, NULL);
		}

		while (1)
		{
		//	MSG msg;
		//	if (!GetMessage(&msg, NULL, 0, 0))
		//		return 0;

			HANDLE handles[256];

			int i;
			handles[0] = p->m_hWakeupEvent;

			/*
			for (i = 0; i < p->m_advise.size(); i++)
			{
				handles[i+1] = p->m_advise[i]->hTimer;
			}
			*/

			ULONG n = WaitForSingleObjectEx(handles[0], INFINITE, TRUE);
			//ULONG n = WaitForMultipleObjects(i+1, handles, FALSE, INFINITE);
			ASSERT(n != WAIT_FAILED);
			n -= WAIT_OBJECT_0;

			if (n == 0)
			{
				//p->m_advise.insert(p->m_advise.begin(), p->m_pNewAdvise);

				AdviseData* adv;
				adv = p->m_pNewAdvise;

				SetEvent(p->m_hGotWakeupEvent);

				LONGLONG curtime;
				p->GetTime(&curtime);
			//	TRACE("%d\n", (ULONG)curtime);

				LONGLONG attime = adv->rt;

			//	p->m_timers.erase(p->m_advise.begin()+n);
			//	CloseHandle(adv-

				LONGLONG uDelay = (attime - curtime);
				if (uDelay <= /*0*/10)	// Time has passed, signal the event
				{
				//	p->m_advise.erase(p->m_advise.begin()+n);

					if (adv->hTimer)
					{
					//	CancelWaitableTimer(adv->hTimer);
					//	CloseHandle(adv->hTimer);
						adv->hTimer = NULL;
					}

					SetEvent(adv->hEvent);
				}
				else
				{
				//	HANDLE hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
					// Hasn't passed yet, set a timer for estimated time

					// to 100 ns (relative)
					LARGE_INTEGER li;
					li.QuadPart = -(uDelay*100);

					if (adv->hTimer == NULL)
						adv->hTimer = p->m_hTimers[p->m_nTimer & 0xF];// CreateWaitableTimer(NULL, FALSE, NULL);
					ASSERT(adv->hTimer);
					BOOL bSucc = SetWaitableTimer(adv->hTimer, &li, 0, timerCompletionRoutine, (LPVOID)adv, FALSE);
					ASSERT(bSucc);

				//	ULONG nTimerID = timeSetEvent(uDelay, 0, EventProc, (ULONG)adv, TIME_ONESHOT | TIME_CALLBACK_FUNCTION);
				//	WaitForSingleObject(hEvent2, INFINITE);
				//	CloseHandle(hEvent2);

					/*
					if (pdwAdviseCookie)
						*pdwAdviseCookie = nTimerID;
						*/
				}
			}
		}

		return 0;
	}
#endif

//	CUPtrList m_advise;

// IMediaSeeking
	ErrorCode Seek(TimeUnit unit, LONGLONG t);
	ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG *pVal);
	ErrorCode GetDuration(TimeUnit unit, LONGLONG *pVal);

// ILDirectSound
	ErrorCode SetWindow(HWND hWnd)
	{
		return m_pInput->m_wo->SetWindow(hWnd);
	}

// IReferenceClock
	ErrorCode GetTime(LONGLONG *pVal);
	ErrorCode AdviseTime(LONGLONG rtBaseTime, LONGLONG rtStreamTime, HANDLE hEvent, ULONG_PTR *pdwAdviseCookie);
};

}	// MediaShow
}

#endif //__LDSOUNDRENDER_H_
