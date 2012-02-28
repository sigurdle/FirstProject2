#include "stdafx.h"
#include "DShowPlayer.h"

#include "VMR9Allocator.h"

#pragma comment(lib, "LFC")
#pragma comment(lib, "Graphics")

//#pragma comment(lib, "Strmbase")
#pragma comment(lib, "strmiids")

#pragma comment(lib, "d3d9")

namespace System
{
namespace DShow
{

#define WM_GRAPHNOTIFY  WM_APP + 1

#define ONE_SECOND 10000000

HRESULT VideoPlayer::SetAllocatorPresenter(IBaseFilter *filter)
{
	if (filter == nullptr)
	{
		return E_FAIL;
	}

	HWindow* w = new HWindow();
	w->CreateHidden();
	m_hWnd = w->get_Hwnd();
	if (m_hWnd == nullptr) return E_FAIL;

	HRESULT hr;

	ComPtr<IVMRSurfaceAllocatorNotify9> lpIVMRSurfAllocNotify;
	FAIL_RET(filter->QueryInterface(IID_IVMRSurfaceAllocatorNotify9, reinterpret_cast<void**>(&lpIVMRSurfAllocNotify)));

	// create our surface allocator
	VMR9Allocator* a = new VMR9Allocator(m_hWnd);
	a->m_scene = m_presenter;
	m_allocator.Attach(a);
	if (FAILED(hr))
	{
		m_allocator = nullptr;
		return hr;
	}

	m_eventEx->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0);

	// let the allocator and the notify know about each other
	FAIL_RET(lpIVMRSurfAllocNotify->AdviseSurfaceAllocator(m_userId, m_allocator));
	FAIL_RET(m_allocator->AdviseNotify(lpIVMRSurfAllocNotify) );

	return hr;
}

VideoPlayer::VideoPlayer(IVideoPresenter* presenter) :  m_presenter(presenter)
{
	m_userId = 0xACDCACDC;
	m_rotRegister = 0;
}

VideoPlayer::~VideoPlayer()
{
	if (m_rotRegister) RemoveFromROT();
}

void VideoPlayer::Load(StringIn path)
{
    // Clear DirectShow interfaces (COM smart pointers)
   // CloseGraph(window);

	ThrowHr(m_graph.CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER));
	ThrowHr(m_graph->QueryInterface(IID_IMediaEventEx, (void**)&m_eventEx));

	ThrowHr(m_filter.CoCreateInstance(CLSID_VideoMixingRenderer9, nullptr, CLSCTX_INPROC_SERVER));

	ComPtr<IVMRFilterConfig9> filterConfig;
	ThrowHr(m_filter->QueryInterface(IID_IVMRFilterConfig9, reinterpret_cast<void**>(&filterConfig)));

	ThrowHr(filterConfig->SetRenderingMode(VMR9Mode_Renderless));
	ThrowHr(filterConfig->SetNumberOfStreams(1));
	ThrowHr(SetAllocatorPresenter(m_filter));
	ThrowHr(m_graph->AddFilter(m_filter, L"Video Mixing Renderer 9"));
	ThrowHr(m_graph->QueryInterface(IID_IMediaControl, reinterpret_cast<void**>(&m_mediaControl)));

	ThrowHr(m_graph->RenderFile(path.c_strw(), nullptr));

	ThrowHr(m_graph->QueryInterface(IID_IMediaSeeking, (void**)&m_seek));

	m_graph->QueryInterface(IID_IBasicAudio, (void**)&m_basicAudio);
	m_graph->QueryInterface(IID_IAMOpenProgress, (void**)&m_openProgress);
	m_graph->QueryInterface(IID_IVideoFrameStep, (void**)&m_videoFrameStep);
}

void VideoPlayer::Play()
{
	ThrowHr(m_mediaControl->Run());
}

void VideoPlayer::Stop()
{
	ThrowHr(m_mediaControl->Stop());
}

void VideoPlayer::Pause()
{
	ThrowHr(m_mediaControl->Pause());
}

VideoState VideoPlayer::get_State()
{
	OAFilterState fs;
	ThrowHr hr = m_mediaControl->GetState(INFINITE, &fs);
	switch (fs)
	{
	case State_Stopped: return VideoState_Stopped;
	case State_Paused: return VideoState_Paused;
	default:/*case State_Running:*/ return VideoState_Playing;
	}
}

uint VideoPlayer::get_Width()
{
	return m_width;
}

uint VideoPlayer::get_Height()
{
	return m_height;
}

bool VideoPlayer::get_CanSeekAbsolute()
{
	DWORD caps = AM_SEEKING_CanSeekAbsolute;
	return m_seek->CheckCapabilities(&caps) == S_OK;
}

bool VideoPlayer::get_CanSeekForwards()
{
	DWORD caps = AM_SEEKING_CanSeekForwards;
	return m_seek->CheckCapabilities(&caps) == S_OK;
}

bool VideoPlayer::get_CanSeekBackwards()
{
	DWORD caps = AM_SEEKING_CanSeekBackwards;
	return m_seek->CheckCapabilities(&caps) == S_OK;
}

bool VideoPlayer::get_CanPlayBackwards()
{
	DWORD caps = AM_SEEKING_CanPlayBackwards;
	return m_seek->CheckCapabilities(&caps) == S_OK;
}

bool VideoPlayer::get_CanGetFrameCount()
{
	if (m_seek->IsFormatSupported(&TIME_FORMAT_FRAME) != S_OK) return false;

	DWORD caps = AM_SEEKING_CanGetDuration;
	return m_seek->CheckCapabilities(&caps) == S_OK;
}

uint VideoPlayer::get_FrameCount()
{
	if (FAILED(m_seek->SetTimeFormat(&TIME_FORMAT_FRAME))) raise(Exception("Cannot get framecount"));

	LONGLONG duration;
	ThrowHr(m_seek->GetDuration(&duration));

	return (uint)duration;
}

bool VideoPlayer::get_CanGetDuration()
{
	DWORD caps = AM_SEEKING_CanGetDuration;
	return m_seek->CheckCapabilities(&caps) == S_OK;
}

double VideoPlayer::get_Duration()
{
	if (FAILED(m_seek->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME))) raise(Exception("Cannot get duration"));

	LONGLONG duration;
	ThrowHr(m_seek->GetDuration(&duration));

	return (double)duration / ONE_SECOND;
}

bool VideoPlayer::get_CanGetCurrentTime()
{
	DWORD caps = AM_SEEKING_CanGetCurrentPos;
	return m_seek->CheckCapabilities(&caps) == S_OK;
}

double VideoPlayer::get_CurrentTime()
{
	if (FAILED(m_seek->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME))) raise(Exception(S("Cannot get current time")));

	LONGLONG current;
	ThrowHr(m_seek->GetCurrentPosition(&current));

	return (double)current / ONE_SECOND;
}

void VideoPlayer::set_CurrentTime(double currentTime)
{
	if (FAILED(m_seek->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME))) raise(Exception(S("Cannot set current time")));

	LONGLONG lCurrentTime = (LONGLONG)(currentTime * ONE_SECOND);

	ThrowHr(m_seek->SetPositions(&lCurrentTime, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning));

	if (get_State() == VideoState_Paused)
	{
		// To update video frame
		m_mediaControl->StopWhenReady();
	}
}

bool VideoPlayer::get_CanGetCurrentFrane()
{
	if (FAILED(m_seek->SetTimeFormat(&TIME_FORMAT_FRAME))) return false;
	DWORD caps = AM_SEEKING_CanGetCurrentPos;
	return m_seek->CheckCapabilities(&caps) == S_OK;
}

uint VideoPlayer::get_CurrentFrame()
{
	if (FAILED(m_seek->SetTimeFormat(&TIME_FORMAT_FRAME))) raise(Exception(S("Cannot get current frame")));

	LONGLONG current;
	ThrowHr(m_seek->GetCurrentPosition(&current));

	return (uint)current;
}

void VideoPlayer::set_CurrentFrame(uint currentFrame)
{
	if (FAILED(m_seek->SetTimeFormat(&TIME_FORMAT_FRAME))) raise(Exception(S("Cannot set current frame")));

	LONGLONG lCurrentFrame = currentFrame;
	ThrowHr(m_seek->SetPositions(&lCurrentFrame, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning));

	if (get_State() == VideoState_Paused)
	{
		// To update video frame
		m_mediaControl->StopWhenReady();
	}
}

float VideoPlayer::get_Rate()
{
	double rate;
	ThrowHr(m_seek->GetRate(&rate));
	return (float)rate;
}

void VideoPlayer::set_Rate(float rate)
{
	/*
	if (rate == 0)
	{
		Pause();
	}
	else
		*/
	{
		ThrowHr(m_seek->SetRate(rate));
	}
}

bool VideoPlayer::get_HasAudio()
{
	// TODO
	return false;
}

float VideoPlayer::get_Balance()
{
	long balance;
	m_basicAudio->get_Balance(&balance);
	return (float)balance / 10000;
}

void VideoPlayer::set_Balance(float balance)
{
	ThrowHr(m_basicAudio->put_Balance(long(balance * 10000)));
}

float VideoPlayer::get_Volume()
{
	long volume;
	m_basicAudio->get_Volume(&volume);
	return 1 - (-volume / 1000.0f);
}

void VideoPlayer::set_Volume(float decibel)
{
	if (decibel < 0) decibel = 0;
	else if (decibel > 1) decibel = 1;

/*
Specifies the volume, as a number from –10,000 to 0, inclusive. Full volume is 0, and –10,000 is silence.
Multiply the desired decibel level by 100. For example, –10,000 = –100 dB.
*/

	ThrowHr(m_basicAudio->put_Volume(long((1-decibel) * -1000)));
}

String VideoPlayer::GetMetadataAsString()
{
	ComPtr<IPersistMediaPropertyBag> pPersist;
	m_graph->QueryInterface(IID_IPersistMediaPropertyBag, (void**)&pPersist);
	if (pPersist == nullptr)
	{
		return nullptr;
	}

	ComPtr<IMediaPropertyBag> pBag;
	pBag.CoCreateInstance(CLSID_MediaPropertyBag, nullptr, CLSCTX_INPROC);

	ThrowHr(pPersist->Save(pBag, FALSE/*unused*/, FALSE/*unused*/));

	ComVariant name;
	ComVariant value;

	IO::StringWriter str;

	for (ULONG i = 0; pBag->EnumProperty(i, &name, &value) == S_OK; ++i)
	{
		str << name;
		str << "=";
		str << value;
		str << endl;
	}

	return str;
}

void VideoPlayer::CloseGraph()
{
	RemoveFromROT();

	if (m_eventEx)
	{
		m_eventEx->SetNotifyWindow(0/*LONG_PTR*/, WM_GRAPHNOTIFY, 0);
		m_eventEx.Release();
	}

	m_mediaControl.Release();
	m_allocator.Release();
	m_seek.Release();
	m_basicAudio.Release();
	m_extendedSeek.Release();
	m_openProgress.Release();
	m_videoFrameStep.Release();
	m_qualProp.Release();

	m_filter.Release();
	m_graph.Release();
}

void VideoPlayer::HandleGraphEvent()
{
	// Disregard if we don't have an IMediaEventEx pointer.
	if (m_eventEx == nullptr)
	{
		return;
	}
	// Get all the events
	long evCode;
	LONG_PTR param1, param2;
	//HRESULT hr;
	while (SUCCEEDED(m_eventEx->GetEvent(&evCode, &param1, &param2, 0)))
	{
		m_eventEx->FreeEventParams(evCode, param1, param2);
		switch (evCode)
		{
		case EC_COMPLETE:
			{
				ev_OnComplete(this);
			}
			break;

			/*
			case EC_LOADSTATUS:
			{
			int statusCode = param1;

			AM_LOADSTATUS_CLOSED The source filter has closed the file. 
AM_LOADSTATUS_CONNECTING The source filter is connecting to the server. 
AM_LOADSTATUS_LOADINGDESCR Not used. 
AM_LOADSTATUS_LOADINGMCAST Not used 
AM_LOADSTATUS_LOCATING The source filter is locating requested data. 
AM_LOADSTATUS_OPEN The source filter has opened the file. 
AM_LOADSTATUS_OPENING The source filter is opening the file. 

			}
			break;

		case EC_OLE_EVENT:
		{
		BSTR type = param1;
		BSTR text = param2;
		}
		break;

			*/
        case EC_USERABORT: // Fall through.
        case EC_ERRORABORT:
			{
				HRESULT errhr = param1;
			  //  CleanUp();
			   // PostQuitMessage(0);
			}
            break;

		case EC_OPENING_FILE:
			{
				BOOL opening = param1;
				ev_OnOpeningFile(this);
			}
			break;

		case EC_BUFFERING_DATA:
			{
				BOOL buffering = param1;
				ev_OnBufferingData(this, !!buffering);
			}
			break;

		case EC_PAUSED:
			break;
        }
    } 
}

namespace
{

HRESULT _AddToRot(IUnknown *pUnkGraph, DWORD *pdwRegister) 
{
	ComPtr<IRunningObjectTable> pROT;
    if (FAILED(GetRunningObjectTable(0, &pROT))) 
    {
        return E_FAIL;
    }
    
    const size_t STRING_LENGTH = 256;

    WCHAR wsz[STRING_LENGTH];
 
	StringCchPrintfW(
		wsz, STRING_LENGTH, 
		L"FilterGraph %08x pid %08x", 
		(DWORD_PTR)pUnkGraph, 
		GetCurrentProcessId()
		);

	ComPtr<IMoniker> pMoniker;
	HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
	if (SUCCEEDED(hr)) 
	{
		hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph, pMoniker, pdwRegister);
	}
    
    return hr;
}

void _RemoveFromRot(DWORD pdwRegister)
{
    ComPtr<IRunningObjectTable> pROT;
    if (SUCCEEDED(GetRunningObjectTable(0, &pROT)))
	{
        pROT->Revoke(pdwRegister);
    }
}
}

void VideoPlayer::AddToROT()
{
	ThrowHr(_AddToRot(m_graph, &m_rotRegister));
}

void VideoPlayer::RemoveFromROT()
{
	if (m_rotRegister)
	{
		_RemoveFromRot(m_rotRegister);
		m_rotRegister = 0;
	}
}

DShowPlayerExt HRESULT EnumFilters(IFilterGraph* pGraph) 
{
	ComPtr<IEnumFilters> pEnum;
	ULONG cFetched;

	HRESULT hr = pGraph->EnumFilters(&pEnum);
	if (FAILED(hr)) return hr;

	Std::get_Out() << "Filter Name" << endl;

	ComPtr<IBaseFilter> pFilter;
	while (pEnum->Next(1, &pFilter, &cFetched) == S_OK)
	{
		FILTER_INFO FilterInfo;
		hr = pFilter->QueryFilterInfo(&FilterInfo);
		if (FAILED(hr))
		{
		//	MessageBox(NULL, TEXT("Could not get the filter info"),
			//	TEXT("Error"), MB_OK | MB_ICONERROR);
			continue;  // Maybe the next one will work.
		}

#ifdef UNICODE
		Std::get_Out() << FilterInfo.achName << endl;
#else
		char szName[MAX_FILTER_NAME];
		int cch = WideCharToMultiByte(CP_ACP, 0, FilterInfo.achName,
			MAX_FILTER_NAME, szName, MAX_FILTER_NAME, 0, 0);
		if (cch > 0)
			MessageBox(NULL, szName, TEXT("Filter Name"), MB_OK);
#endif

		// The FILTER_INFO structure holds a pointer to the Filter Graph
		// Manager, with a reference count that must be released.
		if (FilterInfo.pGraph != nullptr)
		{
			FilterInfo.pGraph->Release();
		}
		pFilter.Release();
	}

	return S_OK;
}

}	// DShow

template class DECLSPEC_DLLEXPORT ComPtr<IFilterGraph>;
template class DECLSPEC_DLLEXPORT ComPtr<IGraphBuilder>;

}	// System
