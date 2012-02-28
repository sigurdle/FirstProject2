#include "stdafx.h"
#include "LMediaImpl.h"
#include "SystemClock.h"

#if WIN32
#pragma comment(lib, "winmm.lib")
#endif

#if AMIGA
#include "../amiga_header.h"
#include <devices/timer.h>
#endif

namespace System
{
namespace MediaShow
{

#if AMIGA

LONGLONG GetCurrentSysTime()
{
	LONGLONG t;

	MsgPort* mp = CreateMsgPort();
	timerequest* timereq = (timerequest*)CreateIORequest(mp, sizeof(timerequest));
	OpenDevice("timer.device", UNIT_MICROHZ, (struct IORequest *)timereq, NULL);

	timereq->tr_node.io_Command = TR_GETSYSTIME;
	DoIO((struct IORequest *)timereq);
	t = (LONGLONG)timereq->tr_time.tv_secs*1000000 + timereq->tr_time.tv_micro;

	CloseDevice((struct IORequest *)timereq);
	DeleteIORequest((struct IORequest *)timereq);
	DeleteMsgPort(mp);

	return t;
}

#endif

SystemClock::SystemClock()
{
#if WIN32
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_freq);
#endif
}

SystemClock::~SystemClock()
{
}

ErrorCode SystemClock::GetTime(LONGLONG *pVal)
{
#if WIN32

//	*pVal = GetTickCount() * LTIME_SCALE / 1000;

	LONGLONG counter;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter);

	double scale = (double)TIME_SCALE / m_freq;

	*pVal = counter * scale;//LTIME_SCALE / m_freq;

#elif AMIGA

	*pVal = GetCurrentSysTime();

#endif

	return Success;
}

ErrorCode SystemClock::AdviseTime(LONGLONG rtBaseTime, LONGLONG rtStreamTime, HANDLE hEvent, ULONG_PTR *pdwAdviseCookie)
{
	LONGLONG curtime;
	GetTime(&curtime);

	LONGLONG attime = rtBaseTime + rtStreamTime;

#if WIN32

	long delay = (long)((attime - curtime) / (TIME_SCALE / 1000));	// to milliseconds
	if (delay <= 0)	// Time has already passed, just signal the event immediately
	{
		SetEvent(hEvent);
	}
	else
	{
		ULONG nTimerID = timeSetEvent(delay, 0, (LPTIMECALLBACK)hEvent/*VideoPlayTimeProc*/, (ULONG_PTR)this, TIME_ONESHOT | TIME_CALLBACK_EVENT_SET);

		if (pdwAdviseCookie)
			*pdwAdviseCookie = nTimerID;
	}

#elif AMIGA

	LONGLONG delay = (attime - curtime);
	delay -= 100;	// Since setting up a wait request also takes some time

	if (delay <= 0)	// Time has already passed
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

}	// MediaShow
}
