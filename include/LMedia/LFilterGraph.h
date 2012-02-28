#ifndef __LFILTERGRAPH_H_
#define __LFILTERGRAPH_H_

//#include "resource.h"       // main symbols

//#include "../LFC/MSWindows.h"
//#include "../LFC/EventTargetImpl.h"
#include "LCollection.h"

namespace System
{
namespace MediaShow
{

class CLStreams;
class CDispLCollection;
class CDispLRegFilter;

class RegFilters
{
public:
	CTOR RegFilters();

	vector<CDispLRegFilter*> m_RegFilters;
};

class LMEDIAEXT FilterGraph : 
	public Object,//System::EventTargetImpl,
	public IGraphBuilder,
	public IMediaSeeking
{
public:
	CTOR FilterGraph();
	~FilterGraph();

#if WIN32
	class Wnd : public MSWindows::WindowImpl//<FilterGraph>
	{
	public:
		FilterGraph* m_graph;
	};

	Wnd* m_wnd;
#endif

	LONGLONG m_tStart;

	CDispLCollection* m_Filters;

	IReferenceClock* m_clock;

//	ErrorCode AddFilter(ILBaseFilter *pFilter, DispILFilter* *pVal);

	ErrorCode RenderGraph();
	ErrorCode RenderAllOutputs(IBaseFilter* pFilter);

	HANDLE GetEventHandle() const;

public:

#if AMIGA
	MsgPort* m_pMsgPort;
#endif

	long OnRun();

	void Notify(IBaseFilter* pFilter, long nEvent);

	long WaitForCompletion(long msTimeout);

	virtual void AddFilter(IBaseFilter *pFilter);
	virtual void RemoveFilter(IBaseFilter *pFilter);
	virtual ErrorCode ConnectDirect(IPin *ppinOut, IPin *ppinIn, MediaType* pMediaType);
	ErrorCode get_frameRate(double *pVal) const;
	ErrorCode set_frameRate(double newVal);
	virtual void LoadURL(System::StringW* url);
//	virtual ErrorCode AddSourceFilterForMoniker(IMoniker *pMoniker, IBindCtx *pCtx, LPCWSTR lpcwstrFilterName, ILBaseFilter* *ppFilter);
//	STDMETHOD(QueryFilterInterface)(REFIID riid, IUnknown* *pVal);
	System::Object* QueryFilterInterface(const Type_Info& riid);

// IMediaControl
	virtual void Run();
	virtual void Stop();
	virtual void Pause();
	virtual FILTER_STATE GetState();

// IGraphBuilder
	ErrorCode Connect(IPin *ppinOut, IPin *ppinIn);
	ErrorCode Render(IPin *ppinOut);

// IMediaSeeking
	ErrorCode GetDuration(TimeUnit unit, LONGLONG* pVal);
	ErrorCode GetCurrentPosition(TimeUnit unit, LONGLONG* pVal);
	ErrorCode Seek(TimeUnit unit, LONGLONG t);

protected:

	HANDLE m_hThread;
	DWORD m_threadId;

	HANDLE m_hEvent;

	FILTER_STATE m_state;
};

}	// MediaShow
}

#endif //__LFILTERGRAPH_H_
