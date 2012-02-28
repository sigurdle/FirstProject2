#ifndef __ODDECODER_H_
#define __ODDECODER_H_

namespace System
{
namespace MediaShow
{

class ODDecoder : 
	public IODDecoder,
	public BaseFilterImpl	// ILMediaFilter
{
public:
	CTOR ODDecoder()
	{
		m_threadId = 0;
		m_hThread = NULL;
	}

#if 0
	int FinalConstruct()
	{
		HRESULT hr;

	#if 0
		/*
		CComObject<CInputPin>::CreateInstance(&m_pInputPin);
		m_pInputPin->m_pFilter = this;
		AddPin(m_pInputPin);
		*/
		CComObject<CVideoSequence>::CreateInstance(&m_pVideo);
		m_pVideo->m_pFilter = this;
		AddPin(m_pVideo);
	#endif

		return 0;
	}
#endif

	DWORD m_threadId;
	HANDLE m_hThread;

	Stream m_stream;
	Mpeg4::Track* m_pTrack;

// IODDecoder
public:
	ErrorCode Run(LONGLONG tStart);
};

}	// Media
}

#endif //__ODDECODER_H_
