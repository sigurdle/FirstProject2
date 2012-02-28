#include "stdafx.h"
#include "UIMedia.h"
#include "MediaElement.h"

#include <windows.h>
#include <d3d9.h>

namespace System
{

namespace MSWindows
{

	extern "C"
	{
WINBASEAPI
BOOL
WINAPI
ResetEvent(
   HANDLE hEvent
    );
}

}	// extern "C"


namespace UI
{
extern UIEXT IDirect3DDevice9* g_d3dDevice9;	// The one and only

extern UIEXT signal1<Object*> g_presented;

extern UIEXT HANDLE g_PresentEvent;
//extern UIEXT HANDLE g_PresentedEvent;

//extern UIEXT LDraw::DrawImageRectCommand* g_pDrawCommand;

ErrorCode CVideoSample::LockBits(MediaShow::LSampleData* pVal)
{
#if 1
	D3DLOCKED_RECT lockedRect;
	m_pBitmap->m_texture.u.d3d->LockRect(0, &lockedRect, NULL, 0);

	pVal->width = m_pBitmap->GetWidth();
	pVal->height = m_pBitmap->GetHeight();
//	pVal->bitcount = 24;//m_pBitmap->GetBitCount();//Data.PFormat.GetBitCount();
	pVal->bitcount = m_pBitmap->GetPixelFormat().GetBitCount();//GetBitCount();//Data.PFormat.GetBitCount();
	pVal->rowbytes = lockedRect.Pitch;
	pVal->idata = (uint8*)lockedRect.pBits;
	return Success;

#else
	m_pBitmap->LockBits(NULL, LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite, &m_bitmapData);

	pVal->width = m_bitmapData.Width;
	pVal->height = m_bitmapData.Height;
	pVal->bitcount = m_bitmapData.PFormat.GetBitCount();
	pVal->rowbytes = m_bitmapData.Stride;
	pVal->idata = m_bitmapData.Scan0;
	return Success;
#endif
}

ErrorCode CVideoSample::UnlockBits()
{
#if 1
	m_pBitmap->m_texture.u.d3d->UnlockRect(0);
#else
	m_pBitmap->UnlockBits(&m_bitmapData);
#endif
	return Success;
}

ErrorCode CVideoFilter::CInputPin::CMemAllocator::GetBuffer(ULONG /*dwBytes*/, MediaShow::IMediaSample* *pVal)
{
	m_pInputPin->m_pLock.Lock();

	for (int i = 0; i < 8; i++)
	{
		CVideoSample* pSample = m_samples[i];
		if (pSample == NULL)
		{
			pSample = new CVideoSample;

			MediaShow::MediaType* mt;
			m_pInputPin->ConnectionMediaType(&mt);

			MediaShow::VideoInfoHeader* vih = (MediaShow::VideoInfoHeader*)mt->GetFormat();//((LMedia::LVIDEOINFOHEADER2*)mt.pbFormat);

//	CLMediaType mt;
//	m_pInputPin->m_e->GetMediaType(&mt);

			LDraw::Bitmap* pBitmap;
			if (vih->vih->bmiHeader.biBitCount == 24)
			{
				pBitmap = new LDraw::Bitmap(vih->vih->bmiHeader.biWidth, vih->vih->bmiHeader.biHeight, LDraw::PixelFormat_t::RGB_24);
			//	pBitmap->m_texture
			}
			else if (vih->vih->bmiHeader.biBitCount == 32)
			{
				pBitmap = new LDraw::Bitmap(vih->vih->bmiHeader.biWidth, vih->vih->bmiHeader.biHeight, LDraw::PixelFormat_t::RGBAP_32);
			}
			else if (vih->vih->bmiHeader.biBitCount == 8)
			{
				pBitmap = new LDraw::Bitmap(vih->vih->bmiHeader.biWidth, vih->vih->bmiHeader.biHeight, LDraw::PixelFormat_t::GRAY_8/*INDEXED_8*/);
			}
			else
				ASSERT(0);

			HRESULT hr = g_d3dDevice9->CreateTexture(pBitmap->GetWidth(), pBitmap->GetHeight(), 1, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, &pBitmap->m_texture.u.d3d, NULL);
			ASSERT(SUCCEEDED(hr));

			pSample->m_pBitmap = pBitmap;

			m_samples[i] = pSample;
		}

		if (pSample->m_dwRef == 0)
		{
			*pVal = pSample;
			(*pVal)->AddRef();
			break;
		}
	}

	m_pInputPin->m_pLock.Unlock();

	return Success;
}

ErrorCode CVideoFilter::CInputPin::CMemAllocator::ReleaseBuffer(MediaShow::IMediaSample* pBuffer)
{
	ASSERT(0);
	return Success;
}

CVideoFilter::CInputPin::CInputPin() : BasePinImpl(MediaShow::PINDIR_INPUT)
{
//	m_pSample = NULL;

	m_pAllocator = new CMemAllocator;
	m_pAllocator->m_pInputPin = this;

//	m_hEvent = NULL;
	m_hEvent = MSWindows::CreateEventW(NULL, false, false, NULL);
//	m_pLock.Init();
//	m_sampleLock.Init();

	m_samples.cont.reserve(2);
}

ErrorCode CVideoFilter::CInputPin::Receive(MediaShow::IMediaSample* pSample)
{
//	m_pLock.Lock();

	/*
	if (GetFilter()->GetState() == LState_Paused)
	{
#if WIN32
		WaitForSingleObject(m_hEvent, INFINITE);
#else
#endif
	}
	*/

	// Hack
	if (g_PresentEvent == NULL)
	{
		g_PresentEvent = MSWindows::CreateEventW(NULL, false, false, NULL);
	}

	LONGLONG timeStart;
	LONGLONG timeEnd;
	pSample->GetTime(&timeStart, &timeEnd);

	if (timeStart != 0 || timeEnd != 0)
	{

		if (true)
		{
	// Wait until it's time to display the sample
		// Estimate 2 milliseconds latency to blit to screen
	//	m_pFilter->m_clock->AdviseTime(m_pFilter->m_tStart/*baseTime*/, (timeStart + 20000)/*streamTime*/, m_hEvent, NULL);
	//	MSWindows::WaitForSingleObject(m_hEvent, INFINITE);
	//	MSWindows::CloseHandle(hEvent);
		}
	}
//	MSWindows::ResetEvent(GetFilter()->m_pControl->m_hCEvent);

	CVideoSample* pVideoSample = static_cast<CVideoSample*>(pSample);
#if 0
	{
//		m_sampleLock.Lock();

		if (m_pSample)
		{
			m_pSample->Release();
		}

		m_pSample = static_cast<CVideoSample*>(pSample);
		m_pSample->AddRef();

//		m_sampleLock.Unlock();
	}
#endif

//	m_pFilter->m_pMoviePlayer->m_cwnd.PostMessage(WM_USER+100, 0, 0);
//	m_pFilter->m_pControl->Invalidate();

// Composite into back buffer

//	g_pDrawCommand = GetFilter()->m_pControl->m_pDrawCommand;

	ASSERT(GetFilter()->m_pControl->m_pDrawCommand);
	if (GetFilter()->m_pControl->m_pDrawCommand)
	{
		GetFilter()->m_pControl->m_pDrawCommand->m_bitmap = pVideoSample->m_pBitmap;

		int width = pVideoSample->m_pBitmap->GetWidth();//vih->GetWidth();//pBitmap->GetWidth();
		int height = pVideoSample->m_pBitmap->GetHeight();//vih->GetHeight();//pBitmap->GetHeight();

		GetFilter()->m_pControl->m_pDrawCommand->m_srcWidth = width;
		GetFilter()->m_pControl->m_pDrawCommand->m_srcHeight = height;

		GetFilter()->m_pControl->GetOwnerWindow()->m_pSite->InvalidateRegion(GetFilter()->m_pControl->m_visibleRegion);
	}
	/*
	else
	{
		GetFilter()->m_pControl->InvalidateRender();
	}
	*/

//	MessageBeep(-1);

#if 0
	{
		Event* evt = new Event;
		evt->InitEvent(WSTR("propertychanged"), false, false);
		GetFilter()->m_pControl->dispatchEvent(evt);
		delete evt;
	}
#endif

//	m_pLock.Unlock();

#if WIN32
	if (timeStart != 0 || timeEnd != 0)
	{

		if (true)
		{
	// Wait until it's time to display the sample
		// Estimate 1 millisecond latency to blit to screen
	//	m_pFilter->m_clock->AdviseTime(m_pFilter->m_tStart/*baseTime*/, (timeStart - 10000)/*streamTime*/, m_hEvent, NULL);
	//	MSWindows::WaitForSingleObject(m_hEvent, INFINITE);
	//	MSWindows::CloseHandle(hEvent);
		}

		LONGLONG currentMediaTime;
		m_pFilter->m_clock->GetTime(&currentMediaTime);

		double delay = (double)(timeEnd - currentMediaTime) / TIME_SCALE;

//		PresentIn(delay);

		SetEvent(g_PresentEvent);
		MSWindows::WaitForSingleObject(GetFilter()->m_pControl->m_hCEvent, INFINITE);
		++GetFilter()->m_framesDrawn;

		uint64 myScale = 100000;
		GetFilter()->m_avgFrameRate = (GetFilter()->m_framesDrawn * myScale) / (timeEnd / (TIME_SCALE / myScale));
	}
#else
	// TODO
	m_pFilter->m_clock->AdviseTime(m_pFilter->m_tStart/*baseTime*/, (timeStart - 4*1000)/*streamTime*/, NULL/*hEvent*/, NULL);
#endif

	return Success_True;	// Keep sending samples
}

//PropertyReference* Video::CurrentTimeProperty = ::RegisterProperty(typeid(Video), "CurrentTime");

MediaElement::MediaElement()
{
	m_Source = NULL;
#if 0
	m_threadId = GetCurrentThreadId();	// The thread that this object is created on
#endif

	m_hCEvent = MSWindows::CreateEventW(NULL, false, false, NULL);

	g_presented.connect(bind1st_of_2(mem_fun(&MediaElement::OnPresent), this));

//	m_playing = FALSE;


//	hr = m_sceneRenderer.CoCreateInstance(CLSID_OGLSceneRenderer);
//	if (FAILED(hr)) return hr;

#if 0

	CComPtr<IBindCtx> ctx;
	hr = CreateBindCtx(0/*reserved*/, &ctx);
	if (SUCCEEDED(hr))
	{
		CComPtr<IMoniker> imkName;
		//hr = CreateURLMoniker(NULL, L"C:/RedSphereBlueBox.wrl", &imkName);
		hr = CreateURLMoniker(NULL, L"C:/Files/MPEG4/kangaroo.mp4", &imkName);

		if (SUCCEEDED(hr))
		{
			hr = m_filterGraph.CoCreateInstance(CLSID_LFilterGraph);
			if (SUCCEEDED(hr))
			{
				hr = m_filterGraph->AddSourceFilterForMoniker(imkName, ctx, L"", NULL);

				if (SUCCEEDED(hr))
				{
					CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
					LONGLONG duration;
					seeking->GetDuration(&duration);
					double m_duration = duration / 100000.0;

					if (m_duration > 0)
					{
					//	m_slider.Enable(TRUE);
					//	m_slider.SetMaxPos(m_duration);
					}
					else
					{
					//	m_slider.Enable(FALSE);
					}

				// find the renderer filter
					CComPtr<ILBasicVideo> basicVideo;
					m_filterGraph->QueryFilterInterface(IID_ILBasicVideo, (IUnknown**)&basicVideo);
					if (basicVideo)
					{
						//m_basicVideo = basicVideo;
					}
				}
			}
		}
	}
#endif
}

StringW* MediaElement::get_Source() const
{
	return m_Source;
}

void MediaElement::Run()
{
	m_filterGraph->Run();
}

void MediaElement::Stop()
{
	m_filterGraph->Stop();
}

void MediaElement::Pause()
{
	m_filterGraph->Pause();
}

MEDIACONTROL_STATE MediaElement::GetState()
{
	MediaShow::FILTER_STATE state = m_filterGraph->GetState();

	return (MEDIACONTROL_STATE)state;
}

void MediaElement::set_Source(StringW* newVal)
{
	m_filterGraph = new MediaShow::FilterGraph;

	m_pFilter = new CVideoFilter;
	m_pFilter->m_pControl = this;
//	pFilter->m_pBitmap = this;
	m_filterGraph->AddFilter(m_pFilter);

//	pFilterGraph->LoadURL(L"C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\Sample Pictures\\Sunset.pcx");
	m_filterGraph->LoadURL(newVal);

#if 0
	ErrorCode hr;

	if (m_filterGraph)
	{
		// TODO Stop
		m_filterGraph.Release();
	}

	m_Source = newVal;

	CComPtr<IBindCtx> ctx;
	hr = CreateBindCtx(0/*reserved*/, &ctx);
	if (SUCCEEDED(hr))
	{
		CComPtr<IMoniker> imkName;
		//hr = CreateURLMoniker(NULL, L"C:/RedSphereBlueBox.wrl", &imkName);
		hr = CreateURLMoniker(NULL, m_Source, &imkName);

		if (SUCCEEDED(hr))
		{
			hr = m_filterGraph.CoCreateInstance(CLSID_LFilterGraph);
			if (SUCCEEDED(hr))
			{
				hr = m_filterGraph->AddSourceFilterForMoniker(imkName, ctx, L"", NULL);

				if (SUCCEEDED(hr))
				{
					CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
					LONGLONG duration;
					seeking->GetDuration(&duration);
					double m_duration = duration / 100000.0;

					if (m_duration > 0)
					{
					//	m_slider.Enable(TRUE);
					//	m_slider.SetMaxPos(m_duration);
					}
					else
					{
					//	m_slider.Enable(FALSE);
					}

				// find the renderer filter
					CComPtr<ILBasicVideo> basicVideo;
					m_filterGraph->QueryFilterInterface(IID_ILBasicVideo, (IUnknown**)&basicVideo);
					if (basicVideo)
					{
						//m_basicVideo = basicVideo;
					}
				}
			}
		}
	}

#if 0
	ErrorCode hr;
	CComPtr<IVRMLLoader> loader;
	hr = loader.CoCreateInstance(CLSID_VRMLLoader);
	if (loader)
	{
		m_Source = newVal;

		CComPtr<ILX3DScene> scene;

		if (m_Source.Length())
		{
			loader->Load(m_Source, &scene);
		}

		m_sceneRenderer->SetScene(scene);

		return Success;
	}
#endif
#endif
}

void MediaElement::OnPresent(Object*)
{
	SetEvent(m_hCEvent);
}

double MediaElement::get_CurrentTime()
{
	MediaShow::IMediaSeeking* seeking = static_cast<MediaShow::IMediaSeeking*>(get_FilterGraph());
	LONGLONG pos;
	seeking->GetCurrentPosition(MediaShow::TimeFormat_ref, &pos);
	double fpos = pos / (double)TIME_SCALE;

	return fpos;
}

void MediaElement::set_CurrentTime(double pos)
{
	MediaShow::IMediaSeeking* seeking = static_cast<MediaShow::IMediaSeeking*>(get_FilterGraph());
	seeking->Seek(MediaShow::TimeFormat_ref, pos * TIME_SCALE);
}

// virtual
void MediaElement::OnRender(Graphics* pGraphics)
{
	/*
	m_pFilter->m_pInput->m_sampleLock.Lock();

	if (m_pFilter && m_pFilter->m_pInput->m_pSample)
	{
		LDraw::Bitmap* pBitmap = m_pFilter->m_pInput->m_pSample->m_pBitmap;
*/
	//	MediaShow::MediaType* mt;
	//	m_pInputPin->ConnectionMediaType(&mt);
	//	m_pFilter->m_pInput->ConnectionMediaType(&mt);

	//	MediaShow::VideoInfoHeader* vih = dynamic_cast<MediaShow::VideoInfoHeader*>(mt->GetFormat());

	//	int width = pBitmap->GetWidth();
	//	int height = pBitmap->GetHeight();

	//	int width = vih->GetWidth();//pBitmap->GetWidth();
	//	int height = vih->GetHeight();//pBitmap->GetHeight();

		LDraw::GraphicsMetafile* pG = dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p);
		ASSERT(pG);

		LDraw::SizeD actualSize = get_ActualSize();

		if (m_pDrawCommand == NULL)
		{
			pGraphics->DrawImage(NULL, LDraw::RectD(0, 0, actualSize.Width, actualSize.Height), 0, 0, 0/*width*/, 0/*height*/);
			m_pDrawCommand = dynamic_cast<LDraw::DrawImageRectCommand*>(pG->m_pCommands->GetTail());
			ASSERT(m_pDrawCommand);
		}

		/*
		for (int x = 0; x < width; x += 16)
		{
			pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(0, 255, 0, 0)), x, 0, 1, height);
		}

		for (int y = 0; y < height; y += 16)
		{
			pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(0, 255, 0, 0)), 0, y, width, 1);
		}
		*/
	//}
	//m_pFilter->m_pInput->m_sampleLock.Unlock();
}

// virtual
LDraw::SizeD MediaElement::MeasureOverride(LDraw::SizeD availSize)
{
	if (m_pDrawCommand)
	{
		return LDraw::SizeD(m_pDrawCommand->m_bitmap->GetWidth(), m_pDrawCommand->m_bitmap->GetHeight());
	}

	/*
	if (m_pFilter && m_pFilter->m_pInput->m_pSample)
	{
		return LDraw::SizeD(m_pFilter && m_pFilter->m_pInput->m_pSample->m_pBitmap->GetWidth(), m_pFilter && m_pFilter->m_pInput->m_pSample->m_pBitmap->GetHeight());
	}
	*/
	else
		return LDraw::SizeD(0, 0);

#if 0
	if (m_Width)
	{
		LXUIUnitType UnitType;
		double Value;
		m_Width->get_UnitType(&UnitType);
		m_Width->get_Value(&Value);
		if (UnitType == UnitPercentage)
		{
			m_computedWidth = Value * viewBox.Width;
		}
		else
		{
			m_computedWidth = Value;
		}
	}
	else
	{
		m_computedWidth = 0;
	}

	if (m_Height)
	{
		LXUIUnitType UnitType;
		double Value;
		m_Height->get_UnitType(&UnitType);
		m_Height->get_Value(&Value);
		if (UnitType == UnitPercentage)
		{
			m_computedHeight = Value * viewBox.Height;
		}
		else
		{
			m_computedHeight = Value;
		}
	}
	else
	{
		m_computedHeight = 0;
	}

	m_expandedBBox.X = 0;//minx;
	m_expandedBBox.Y = 0;//miny;
	m_expandedBBox.Width = m_computedWidth;
	m_expandedBBox.Height = m_computedHeight;
#endif
}

LDraw::SizeD MediaElement::ArrangeOverride(LDraw::SizeD finalSize)
{
	m_pDrawCommand = NULL;
	return finalSize;
}

}	// UI
}
