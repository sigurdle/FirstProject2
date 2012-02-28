#include "stdafx.h"
#include "LMediaImpl.h"
#include "LDSoundRender.h"

#if AMIGA
#include "../amiga_header.h"
#include <devices/timer.h>
#endif

namespace System
{
namespace MediaShow
{
#if AMIGA
LONGLONG GetCurrentSysTime();
#endif

ErrorCode_Bool CLDSoundRender::CInputPin::Receive(IMediaSample *sample)
{
	CriticalSectionLock lock(m_pLock);

	ErrorCode hr;

	LSampleData sampledata;
	hr = sample->LockBits(&sampledata);
	if (hr >= 0)
	{
		ULONG ActualDataLength = sample->GetActualDataLength();

		sample->GetTime(&m_lastTimeStart, &m_lastTimeEnd);

		hr = m_wo->Receive(sampledata.idata, ActualDataLength);

		sample->UnlockBits();
	}

	return hr;
	/*
	DWORD nbytesSoFar = 0;
	while (nbytesSoFar < pSample->m_ActualDataLength)
	{
		DWORD nbytes = m_dwBufferBytes;

		if (nbytes > pSample->m_ActualDataLength)
		{
			nbytes = pSample->m_ActualDataLength;
		}

		DWORD dwbuffer1;
		LPBYTE buffer1;

		DWORD dwbuffer2;
		LPBYTE buffer2;

		ErrorCode hr = m_dsBuffer8->Lock(m_dwOffset, nbytes, (void**)&buffer1, &dwbuffer1, (void**)&buffer2, &dwbuffer2, 0);
		if (SUCCEEDED(hr))
		{
			CopyMemory(buffer1, pSample->m_pointer+nbytesSoFar, dwbuffer1);
			nbytesSoFar += dwbuffer1;

			if (buffer2)
			{
				CopyMemory(buffer2, pSample->m_pointer+nbytesSoFar, dwbuffer2);
				nbytesSoFar += dwbuffer2;
			}

			m_dsBuffer8->Unlock(buffer1, dwbuffer1, buffer2, dwbuffer2);
		}

		DWORD status;
		m_dsBuffer8->GetStatus(&status);

		if (!(status & DSBSTATUS_PLAYING))
		{
			ErrorCode hr = m_dsBuffer8->Play(0, 0, DSBPLAY_LOOPING);
			ASSERT(SUCCEEDED(hr));
		}

		//if (dwBytesSoFar > m_dwBufferBytes)
		WaitForSingleObject(m_hEvent, INFINITE);

		m_dwOffset += nbytes;//pSample->m_dwBytes;

		while (m_dwOffset >= 2*m_dwBufferBytes)
			m_dwOffset -= 2*m_dwBufferBytes;
	}
	*/
}

ErrorCode CLDSoundRender::CInputPin::EndOfStream()
{
#if WIN32
// Wait until the last sample has ended
	HANDLE hEvent = CreateEventA(NULL, false, false, NULL);
	GetFilter()->m_clock->AdviseTime(m_pFilter->m_tStart/*baseTime*/, m_lastTimeEnd/*streamTime*/, hEvent, NULL);
	WaitForSingleObject(hEvent, INFINITE);
#elif AMIGA
	GetFilter()->m_clock->AdviseTime(m_pFilter->m_tStart/*baseTime*/, m_lastTimeEnd/*streamTime*/, NULL/*hEvent*/, NULL);
#endif
	m_wo->Pause();

	return Success;
}

CLDSoundRender::CLDSoundRender()
{
#if 0
#if WIN32
	CoInitialize(NULL);
#endif
#endif

	m_pInput = NULL;

//	m_oldtime = 0;

//		m_dwCurrentPlayCursor = 0;

	ErrorCode hr;

	m_pInput = new CInputPin;
	m_pInput->m_pFilter = this;
	m_pInput->m_id = WSTR("Audio Input");
	AddPin(m_pInput);

#if WIN32
	m_hWakeupEvent = CreateEventA(NULL, false, false, NULL);
	m_hGotWakeupEvent = CreateEventA(NULL, false, false, NULL);
#endif

//	m_hTimerThread = CreateThread(NULL, 0, TimerThread, (LPVOID)this, 0, &m_dwTimerThreadId);
	//SetThreadPriority(m_hTimerThread, THREAD_PRIORITY_BELOW_NORMAL/*THREAD_PRIORITY_HIGHEST*/);

#if 0
	m_cwnd.Create(NULL, CRect(0,0,0,0), NULL, WS_POPUP);
	ASSERT(m_cwnd.m_hWnd);
	if (m_cwnd.m_hWnd == NULL)
		return E_FAIL;
#endif

#if 0
	hr = m_pInput->m_ds8->SetCooperativeLevel(m_cwnd.m_hWnd, DSSCL_PRIORITY/*DSSCL_NORMAL*/);
	ASSERT(SUCCEEDED(hr));
#endif

#if AMIGA
	//m_timereq = NULL;
#endif
}

ErrorCode CLDSoundRender::GetTime(LONGLONG *pVal)
{

#if WIN32

	LONGLONG nPlayedSamples = m_pInput->m_wo->GetCurrentPlayCursor();

	LONGLONG t = nPlayedSamples * TIME_SCALE / m_pInput->m_wo->m_wf->nSamplesPerSec;

	ASSERT(t >= 0);

	*pVal = t;

#elif AMIGA

	int nloops = m_pInput->m_wo->m_nLoops;

	LONGLONG nPlayedSamples = (((LONGLONG)nloops * m_pInput->m_wo->m_dwBufferBytes) / m_pInput->m_wo->m_wf->nBlockAlign);
	LONGLONG t = nPlayedSamples * LTIME_SCALE / m_pInput->m_wo->m_wf->nSamplesPerSec;// + currentPlayCursor;
	t += GetCurrentSysTime() - m_pInput->m_wo->m_lastTime;

	*pVal = t;

#else
#error Unknown OS
#endif

	return Success;
}

CLDSoundRender::AdviseData advdata;

ErrorCode CLDSoundRender::AdviseTime(LONGLONG rtBaseTime, LONGLONG rtStreamTime, HANDLE hEvent, ULONG_PTR *pdwAdviseCookie)
{
	CriticalSectionLock lock(m_clockcrit);

	LONGLONG curtime;
	GetTime(&curtime);

#if WIN32
	// TODO
	AdviseData* data = &advdata;//new AdviseData;
	data->pClock = this;
	data->rt = rtBaseTime + rtStreamTime;
	data->hEvent = hEvent;
	data->hTimer = NULL;

	if (pdwAdviseCookie)
		*pdwAdviseCookie = (ULONG_PTR)data;

	LONGLONG attime = data->rt;

#if 0
	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = 

#else

	long delay = (long)((attime - curtime) / (TIME_SCALE / 1000));
	if (delay <= 0)
	{
		SetEvent(hEvent);
	}
	else
	{
		MMRESULT mmresult = timeSetEvent(delay, 0, (LPTIMECALLBACK)hEvent, 0, TIME_ONESHOT | TIME_CALLBACK_EVENT_SET);
		if (mmresult == NULL)	// Error
		{
			SetEvent(hEvent);
		}
	//	HANDLE hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	//	SetWaitableTimer(hTimer, 
	}
#endif

//	PostThreadMessage(m_dwTimerThreadId, WM_USER+1, (WPARAM)data, 0);
	//m_advise.insert(m_advise.begin(), data);
	/*
	m_pNewAdvise = data;
	SetEvent(m_hWakeupEvent);
	WaitForSingleObject(m_hGotWakeupEvent, INFINITE);
	*/
#elif AMIGA

	LONGLONG attime = rtBaseTime + rtStreamTime;

	LONGLONG uDelay = (attime - curtime);
	if (uDelay <= 0)
	{
	}
	else
	{
		MsgPort* mp = CreateMsgPort();
		timerequest* timereq = (timerequest*)CreateIORequest(mp, sizeof(timerequest));
		OpenDevice("timer.device", UNIT_MICROHZ, (struct IORequest *)timereq, NULL);

		timereq->tr_node.io_Command = TR_ADDREQUEST;
		timereq->tr_time.tv_secs = uDelay / 1000000;
		timereq->tr_time.tv_micro = uDelay % 1000000;
		DoIO((struct IORequest *)timereq);

		CloseDevice((struct IORequest *)timereq);
		DeleteIORequest((struct IORequest *)timereq);
		DeleteMsgPort(mp);
	}

#endif

	return Success;
}

ErrorCode CLDSoundRender::Seek(TimeUnit unit, LONGLONG t)
{
	IMediaSeeking* peerSeeking = dynamic_cast<IMediaSeeking*>(m_pInput->m_connectedTo);
	if (peerSeeking == NULL)
		return Error_NoInterface;

	return peerSeeking->Seek(unit, t);
}

ErrorCode CLDSoundRender::GetCurrentPosition(TimeUnit unit, LONGLONG *pVal)
{
	/*
	CComQIPtr<ILMediaSeeking> peerSeeking = m_pInputPin->m_connectedTo;
	if (peerSeeking == NULL)
		return E_NOINTERFACE;

	return peerSeeking->Seek(seconds);
	*/
	return Success;
}

ErrorCode CLDSoundRender::GetDuration(TimeUnit unit, LONGLONG *pVal)
{
	IMediaSeeking* peerSeeking = dynamic_cast<IMediaSeeking*>(m_pInput->m_connectedTo);
	if (peerSeeking == NULL)
		return Error_NoInterface;

	return peerSeeking->GetDuration(unit, pVal);
}

}	// MediaShow
}
