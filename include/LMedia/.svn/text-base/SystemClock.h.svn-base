#ifndef __SYSTEMCLOCK_H_
#define __SYSTEMCLOCK_H_

namespace System
{
namespace MediaShow
{

class SystemClock : 
	public IReferenceClock
{
public:
	CTOR SystemClock();
	~SystemClock();

// IReferenceClock
	ErrorCode GetTime(LONGLONG *pVal);
	ErrorCode AdviseTime(LONGLONG rtBaseTime, LONGLONG rtStreamTime, HANDLE hEvent, ULONG_PTR *pdwAdviseCookie);

protected:

#if WIN32
	LONGLONG m_freq;
#endif
};

}	// MediaShow
}

#endif //__SYSTEMCLOCK_H_
