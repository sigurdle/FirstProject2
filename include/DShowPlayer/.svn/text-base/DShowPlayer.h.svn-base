#ifndef DShowPlayer_h
#define DShowPlayer_h

#ifdef __LERSTAD__
#import "LFC/LFC.h"
#else
#include "LFC/LFC.h"
#endif

#ifdef __LERSTAD__
#import "Graphics/Graphics.h"
#else
#include "Graphics/Graphics.h"
#endif

#ifndef DShowPlayerExt
#define DShowPlayerExt DECLSPEC_DLLIMPORT
#endif

#define FAIL_RET(x) do { if (FAILED(hr = (x))) return hr; } while(0)

#ifdef __LERSTAD__

struct IDirect3DDevice9 : public IUnknown
{
};

struct IDirect3DTexture9 : public IUnknown
{
};

struct IBaseFilter : public IUnknown
{
};

struct IFilterGraph : public IUnknown
{
};

struct IGraphBuilder : public IFilterGraph
{
};

struct IMediaControl : public IUnknown
{
};

struct IBasicAudio : public IUnknown
{
};
struct IMediaEventEx : public IUnknown
{
};

struct IMediaSeeking : public IUnknown
{
};

struct IAMExtendedSeeking : public IUnknown
{
};

struct IAMOpenProgress : public IUnknown
{
};

struct IVideoFrameStep : public IUnknown
{
};

struct IVMRSurfaceAllocator9 : public IUnknown
{
};

struct IQualProp : public IUnknown
{
};

#endif

#ifndef __LERSTAD__
#include <DShow.h>
#include <qnetwork.h>
#include <d3d9.h>
#include <vmr9.h>
#endif

//#include "playback.h"

namespace System
{
namespace DShow
{

enum VideoState
{
	VideoState_Stopped,
	VideoState_Paused,
	VideoState_Playing,
};

/*
interface IVideoPerformance
{
	virtual int get_AvgFrameRate();
};
*/

interface IVideoPlayer
{
	virtual void Load(StringIn path) = 0;

	virtual void Play() = 0;
	virtual void Pause() = 0;
	virtual void Stop() = 0;
	virtual VideoState get_State() = 0;

	virtual uint get_Width() = 0;
	virtual uint get_Height() = 0;

	virtual bool get_CanSeekAbsolute() = 0;
	virtual bool get_CanSeekForwards() = 0;
	virtual bool get_CanSeekBackwards() = 0;
	virtual bool get_CanPlayBackwards() = 0;

	virtual float get_Rate() = 0;
	virtual void set_Rate(float rate) = 0;

	virtual bool get_CanGetDuration() = 0;
	virtual double get_Duration() = 0;

	virtual bool get_CanGetFrameCount() = 0;
	virtual uint get_FrameCount() = 0;

	virtual bool get_CanGetCurrentTime() = 0;
	virtual double get_CurrentTime() = 0;
	virtual void set_CurrentTime(double seconds) = 0;

	virtual bool get_CanGetCurrentFrane() = 0;
	virtual uint get_CurrentFrame() = 0;
	virtual void set_CurrentFrame(uint frame) = 0;

	virtual bool get_HasAudio() = 0;

	virtual String GetMetadataAsString() = 0;
};

interface IAudio
{
	virtual float get_Balance() = 0;
	virtual void set_Balance(float balance) = 0;

	virtual float get_Volume() = 0;
	virtual void set_Volume(float decibel) = 0;
};

interface IVideoPresenter
{
	virtual HRESULT Init(IDirect3DDevice9* d3ddev, uint width, uint height, ID3D10Texture2D* texture) = 0;
	virtual HRESULT DrawScene(IDirect3DDevice9* d3ddev, IDirect3DTexture9* texture) = 0;
//	virtual void SetSrcRect(float fTU, float fTV) = 0;
};

class DShowPlayerExt VideoPlayer : public Object, public IVideoPlayer, public IAudio
{
public:
	CTOR VideoPlayer(IVideoPresenter* presenter);
	virtual ~VideoPlayer();

	virtual void Load(StringIn path) override;

	virtual void Play() override;
	virtual void Stop() override;
	virtual void Pause() override;
	virtual VideoState get_State() override;

	virtual uint get_Width() override;
	virtual uint get_Height() override;

	virtual float get_Rate() override;
	virtual void set_Rate(float rate) override;

	virtual bool get_CanSeekAbsolute() override;
	virtual bool get_CanSeekForwards() override;
	virtual bool get_CanSeekBackwards() override;
	virtual bool get_CanPlayBackwards() override;

	virtual bool get_CanGetDuration() override;
	virtual double get_Duration() override;

	virtual bool get_CanGetFrameCount() override;
	virtual uint get_FrameCount() override;

	virtual bool get_CanGetCurrentTime() override;
	virtual double get_CurrentTime() override;
	virtual void set_CurrentTime(double seconds) override;

	virtual bool get_CanGetCurrentFrane() override;
	virtual uint get_CurrentFrame() override;
	virtual void set_CurrentFrame(uint frame) override;

	virtual bool get_HasAudio() override;

	virtual float get_Balance() override;
	virtual void set_Balance(float balance) override;
	virtual float get_Volume() override;
	virtual void set_Volume(float decibel) override;

	virtual String GetMetadataAsString() override;

	void AddToROT();
	void RemoveFromROT();

	ComPtr<IGraphBuilder> get_Graph()
	{
		return m_graph;
	}

	Event1<Object*>& get_OnComplete()
	{
		return ev_OnComplete;
	}

	Event1<Object*>& get_OnOpeningFile()
	{
		return ev_OnOpeningFile;
	}

	Event1<Object*>& get_OnClosingFile()
	{
		return ev_OnClosingFile;
	}

	Event2<Object*, bool>& get_OnBufferingData()
	{
		return ev_OnBufferingData;
	}

	Event1<Object*> ev_OnComplete;
	Event1<Object*> ev_OnOpeningFile;
	Event1<Object*> ev_OnClosingFile;
	Event2<Object*, bool> ev_OnBufferingData;

protected:

	virtual HRESULT SetAllocatorPresenter(IBaseFilter* filter);
	virtual void CloseGraph();
	virtual void HandleGraphEvent();

	IVideoPresenter* m_presenter;

	uint m_width;
	uint m_height;

	DWORD_PTR m_userId;
	HWND m_hWnd;

	DWORD m_rotRegister;

	ComPtr<IGraphBuilder> m_graph;
	ComPtr<IBaseFilter> m_filter;
	ComPtr<IMediaControl> m_mediaControl;
	ComPtr<IMediaEventEx> m_eventEx;
	ComPtr<IVMRSurfaceAllocator9> m_allocator;
	ComPtr<IMediaSeeking> m_seek;
	ComPtr<IBasicAudio> m_basicAudio;
	ComPtr<IAMExtendedSeeking> m_extendedSeek;
	ComPtr<IAMOpenProgress> m_openProgress;
	ComPtr<IVideoFrameStep> m_videoFrameStep;

	ComPtr<IQualProp> m_qualProp;
};

DShowPlayerExt HRESULT EnumFilters(IFilterGraph* pGraph);

}	// DShow
}	// System

#endif
