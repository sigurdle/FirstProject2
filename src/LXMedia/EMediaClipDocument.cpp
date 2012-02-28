// EMediaClipDocument.cpp : Implementation of CEMediaClipDocument
#include "stdafx.h"
#include "LXMedia.h"
#include "LXMedia2.h"

#include "EMediaClipDocument.h"

#include "MediaClipView.h"
#include "AudioClipView.h"

//#include "LXFrameworkApp.h"
//#include "LXFrameworkFrame.h"
//extern CLXFrameworkApp* gApp;

#pragma comment(lib, "winmm.lib")

////////////////////////////////////////////////////////////////////////
// CMediaStreamsDlg

LRESULT CMediaStreamsDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	int y = 0;

	for (int i = 0; i < m_pDocument->m_streams.GetSize(); i++)
	{
		CMediaStream* pStream = m_pDocument->m_streams[i];

		LStreamType streamType;
		pStream->m_stream->GetStreamType(&streamType);

		if (streamType == LStreamType_Video)
		{
			dc.TextOut(0, y, "Video");
		}
		else if (streamType == LStreamType_Audio)
		{
			dc.TextOut(0, y, "Audio");
		}

		/*
		CComQIPtr<ILStreamInfo> streamInfo = pStream->m_stream;
		if (streamInfo)
		{
			long bitrate;
			streamInfo->GetBitRate(&bitrate);

			CComBSTR codec;
			streamInfo->GetCodec(&codec);

			TCHAR buf[512];
			sprintf(buf, "codec: %S, bitrate: %g Kbps", (BSTR)codec, bitrate/1024.0);

			dc.TextOut(0, y, buf);
		}
		else
		{
			dc.TextOut(0, y, "Stream");
		}
		*/

		y += 24;
	}

	return 0;
}

LRESULT CMediaStreamsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CMediaStreamsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CMediaStreamsDlg::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CComQIPtr<ILXAddin> addin = m_pDocument->m_app;

	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	CComQIPtr<IEFrame> eframe = lxframe;
//	m_spViewGroupSite->GetFrame(&eframe);

	CComQIPtr<IUIMDIFrame> mdiframe = eframe;

	int index = point.y/24;

	if (index >= 0 && index < m_pDocument->m_streams.GetSize())
	{
		CMediaStream* pStream = m_pDocument->m_streams[index];
		
		LStreamType streamType;
		pStream->m_stream->GetStreamType(&streamType);

		if (streamType == LStreamType_Video)
		{
/*
			CComQIPtr<ILVideo> video = pStream->m_stream;
			if (video)
			{
				if (pStream->m_pSample == NULL)
				{
					long width;
					long height;
					video->GetWidth(&width);
					video->GetHeight(&height);

#if 0
					CComObject<CVideoSample>::CreateInstance(&pStream->m_pSample);
					pStream->m_pSample->AddRef();

					pStream->m_pSample->m_pBitmap = new Gdiplus::Bitmap(width, height, PixelFormat24bppRGB);

					video->SetSample(pStream->m_pSample);
#endif
				}
			}
*/

			if (pStream->m_view)
			{
				// TODO pStream->m_view->Activate()
			}
			else
			{
				CComObject<CMediaClipView>* pClipView;
				CComObject<CMediaClipView>::CreateInstance(&pClipView);
				if (pClipView)
				{
					pStream->m_view = pClipView;

					//eframe->CreateViewGroupSite(pClipView, &pClipView->m_spViewGroupSite);

					pClipView->m_pStream = pStream;

					//gApp->m_frame->FindMenu(_Module.GetResourceInstance(), IDR_MEDIACLIPVIEW, &pClipView->m_menu);
					//pClipView->m_spViewGroupSite->AddPage(pClipView, NULL);

					CComPtr<IUIMDIChild> childFrame;
					mdiframe->CreateChildFrame(pClipView, &childFrame);

				//	m_pDocument->m_pVideoClipView = pClipView;
				}
			}
		}
		else if (streamType == LStreamType_Audio)
		{
#if 0
			CComQIPtr<ILAudio> audio = pStream->m_stream;
			if (audio)
			{
				if (pStream->m_nSamples == 0)
				{
					audio->GetSamples(&pStream->m_nSamples);

					if (pStream->m_nSamples > 0)
					{
						pStream->m_wavFormat = (LPWAVEFORMATEX)GlobalAlloc(0, sizeof(WAVEFORMATEX));
						audio->GetFormat(pStream->m_wavFormat);

						pStream->m_wavBuffer = (LPSTR)GlobalAlloc(0, (DWORD)(pStream->m_nSamples*pStream->m_wavFormat->nBlockAlign));
						if (pStream->m_wavBuffer)
						{
							LPSTR buffer = pStream->m_wavBuffer;

							int i = 0;
							ULONG chunksamples;
							while (audio->GetChunkSize(i, &chunksamples) == S_OK)
							{
								audio->ReadChunk(i, buffer, chunksamples);

								buffer += chunksamples*pStream->m_wavFormat->nBlockAlign;

								i++;
							}
						}
					}
				}

				if (pStream->m_view)
				{
					// TODO pStream->m_view->Activate()
				}
				else
				{
					CComObject<CAudioClipView>* pClipView;
					CComObject<CAudioClipView>::CreateInstance(&pClipView);
					if (pClipView)
					{
						pStream->m_view = pClipView;

					//	eframe->CreateViewGroupSite(pClipView, &pClipView->m_spViewGroupSite);

						pClipView->m_pStream = pStream;

					//	gApp->m_frame->FindMenu(_Module.GetResourceInstance(), IDR_AUDIOCLIPVIEW, &pClipView->m_menu);
					//	pClipView->m_spViewGroupSite->AddPage(pClipView, NULL);

						CComPtr<IUIMDIChild> childFrame;
						mdiframe->CreateChildFrame(pClipView, &childFrame);

					//	m_pDocument->m_pAudioClipView = pClipView;
					}
				}
			}
#endif
		}
	}

	return 0;
}

// ICommandTarget
STDMETHODIMP CMediaStreamsDlg::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	CComQIPtr<ICommandTarget> target;

// Try document
	target = m_pDocument;
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

	return S_OK;
}

BEGIN_CMD_MAP(CMediaStreamsDlg)
//	CMD_HANDLER(ID_EDIT_PLAY, OnPlay)
END_CMD_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEMediaClipDocument

void CEMediaClipDocument::UpdateAllVideoViews()
{
	for (int i = 0; i < m_streams.GetSize(); i++)
	{
		CMediaStream* pStream = m_streams[i];

		if (pStream->m_pSample)	// Video
		{
			if (pStream->m_view)
			{
				HWND hwnd;
				pStream->m_view->get_hwnd(&hwnd);

				InvalidateRect(hwnd, NULL, TRUE);
			}
		}
	}
}

HRESULT CEMediaClipDocument::Seek(double seekTo)
{
	HRESULT hr;

	m_currentTime = seekTo;

// Seek
	{
		CComQIPtr<ILMediaSeeking> mediaSeeking = m_filterGraph;
		ATLASSERT(mediaSeeking);

		hr = mediaSeeking->Seek(m_currentTime);
	}

	UpdateAllVideoViews();

	return S_OK;
}

HRESULT CEMediaClipDocument::SetMediaElement(ILDOMElement* element)
{
	ATLASSERT(m_filterGraph == NULL);

	m_mediaElement = element;

	ATLASSERT(m_mediaElement != NULL);

	CComBSTR src;

	CComQIPtr<ILSMILMediaElement> mediaElement = m_mediaElement;
	if (mediaElement)
	{
		mediaElement->get_src(&src);
	}
	else
	{
		m_mediaElement->getAttributeNS(L"http://www.w3.org/1999/xlink", L"href", &src);
	}

	HRESULT hr = LoadFile(src);

	Seek(0);

	return hr;
}

HRESULT CEMediaClipDocument::LoadFile(BSTR wszFileName)
{
	HRESULT hr;

	hr = m_filterGraph.CoCreateInstance(CLSID_LFilterGraph/*L"LMedia.LFilterGraph"*/);
	if (SUCCEEDED(hr))
	{
		hr = m_filterGraph->LoadURL(wszFileName);
		if (SUCCEEDED(hr))
		{
			//CComPtr<ILMediaLoader> loader;
			//m_movie->GetLoader(&loader);

			{
				CComPtr<DispILStreams> streams;
				m_filterGraph->get_Streams(&streams);

				long nstreams;
				streams->get_Count(&nstreams);

				for (int i = 0; i < nstreams; i++)
				{
					CComObject<CMediaStream>* pStream;
					CComObject<CMediaStream>::CreateInstance(&pStream);
					pStream->AddRef();

					pStream->m_pDocument = this;
					
					CComPtr<DispILMediaStream> stream;
					streams->Item(i, &stream);

					pStream->m_stream = stream;

					m_filterGraph->AddFilter(pStream);

					m_streams.Add(pStream);

					CComPtr<ILPin> pin;
					pStream->m_stream->GetPin(&pin);
					m_filterGraph->ConnectDirect(pin, pStream->m_pInputPin, NULL);
				}
			}

			CComQIPtr<ILMediaSeeking> mediaSeeking = m_filterGraph;
			mediaSeeking->GetDuration(&m_duration);
		}
	}

	return hr;
}

// IEDocument

//	STDMETHOD(GetDocumentsClass)(/*[out,retval]*/ IDocumentsClass* *pVal);
//	STDMETHOD(get_undoManager)(/*[out, retval]*/ IOleUndoManager* *pVal);
//	STDMETHOD(LoadDocumentByteArray)(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success);

STDMETHODIMP CEMediaClipDocument::Activate()
{
	return S_OK;
}
STDMETHODIMP CEMediaClipDocument::NewDocument()
{
	return S_OK;
}

STDMETHODIMP CEMediaClipDocument::CloseDocument()
{
	return S_OK;
}

STDMETHODIMP CEMediaClipDocument::ShowViews(IEFrame* eframe)
{
	CComQIPtr<IUIMDIFrame> mdiframe = eframe;

	CComObject<CMediaStreamsDlg>* pView;
	CComObject<CMediaStreamsDlg>::CreateInstance(&pView);
	if (pView)
	{
	//	eframe->CreateViewGroupSite(pView, &pView->m_spViewGroupSite);

		pView->m_pDocument = this;

		CComPtr<IUIMDIChild> childFrame;
		mdiframe->CreateChildFrame(pView, &childFrame);
		//gApp->m_frame->FindMenu(IDR_MEDIACLIPVIEW, &pClipView->m_menu);
		//pView->m_spViewGroupSite->AddView(pView);

		//m_pVideoClipView = pClipView;
	}

	//	child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);

	return S_OK;
}

// IPersistFile
STDMETHODIMP CEMediaClipDocument::Load(/* [in] */ LPCOLESTR pszFileName, /* [in] */ DWORD dwMode)
{
	HRESULT hr = LoadFile(W2BSTR(pszFileName));
	if (SUCCEEDED(hr))
	{
		Seek(0);
	}

	return hr;
}

/////////////////////////////////////////////////////
// Playback stuff
static void CALLBACK AudioCallback(
	HWAVEOUT hwo,
	UINT uMsg,
	DWORD dwInstance, 
	DWORD dwParam1,
	DWORD dwParam2)
{
	CEMediaClipDocument* pDocument = (CEMediaClipDocument*)dwInstance;
	ATLASSERT(pDocument);

	if (uMsg == WOM_DONE)
	{
//		::PostThreadMessage(g_idThread, WM_USER+1025, (WPARAM)pComp, dwParam1);

		timeKillEvent(pDocument->m_nTimerID);
		pDocument->m_bPlaying = FALSE;
	}
}

static bool audioClock = true;

void CALLBACK VideoPlayTimeProc(
  UINT uID,     
  UINT uMsg,  
  DWORD dwUser,
  DWORD dw1,
  DWORD dw2
)
{
	CEMediaClipDocument* pDoc = (CEMediaClipDocument*)dwUser;

	if (!audioClock)
	{
		pDoc->m_currentTime += 1 / pDoc->m_frameRate;
	}

	pDoc->m_cwnd.PostMessage(WM_USER+100, 0, 0);
}

LRESULT CEMediaClipDocument::OnWOMDone(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_nTimerID)
	{
		timeKillEvent(m_nTimerID);
		m_nTimerID = 0;
	}

	if (m_hWaveOut)
	{
		waveOutUnprepareHeader(m_hWaveOut, &m_wavHdr, sizeof(WAVEHDR));
		waveOutClose(m_hWaveOut);
	}

#if 0
	if (m_pAudioClipView)
	{
		m_pAudioClipView->OnStopPlay();
	}
#endif

	m_bPlaying = FALSE;

	return 0;
}

LRESULT CEMediaClipDocument::OnSeekVideo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (audioClock)
	{
		ATLASSERT(0);
#if 0
		MMTIME mmt;
		mmt.wType = TIME_SAMPLES;
		waveOutGetPosition(m_hWaveOut, &mmt, sizeof(mmt));

		if (mmt.wType == TIME_SAMPLES)
			m_currentTime = (double)mmt.u.sample/m_wavFormat->nSamplesPerSec;
		else
			ATLASSERT(0);
#endif
	}

	CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
	seeking->Seek(m_currentTime);

	/*
	if (m_pVideoClipView)
	{
		m_pVideoClipView->InvalidateRect(NULL);
	}
	*/
	UpdateAllVideoViews();//InvalidateRect(NULL);

#if 0
	if (m_pAudioClipView)
	{
		m_pAudioClipView->OnPlaying();
	}
#endif

	return 0;
}

BEGIN_CMD_MAP(CEMediaClipDocument)
	CMD_HANDLER(ID_EDIT_PLAY, OnPlay)
END_CMD_MAP()

LRESULT CEMediaClipDocument::OnPlay(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	Seek(0);

	m_bPlaying = TRUE;

	MMRESULT	mmresult;

	LONG uDelay = (LONG)(1000/m_frameRate);

#if 0	// Had this
	if (m_pAudioClipView)
	{
		m_pAudioClipView->OnStartPlay();
	}
#endif

#if 0	// Had this
	if (m_nSamples)
	{
		mmresult = waveOutOpen(&m_hWaveOut, WAVE_MAPPER, m_wavFormat, (DWORD)m_cwnd.m_hWnd/*AudioCallback*/, (DWORD)this, CALLBACK_WINDOW/*CALLBACK_FUNCTION*/);
		if (mmresult == 0)
		{
			memset(&m_wavHdr, 0, sizeof(WAVEHDR));
			m_wavHdr.dwBufferLength = (DWORD)(m_nSamples*m_wavFormat->nBlockAlign);
			m_wavHdr.lpData = m_wavBuffer;
			m_wavHdr.dwFlags = 0;

			mmresult = waveOutPrepareHeader(m_hWaveOut, &m_wavHdr, sizeof(WAVEHDR));
			if (mmresult == 0)
			{
				mmresult = waveOutWrite(m_hWaveOut, &m_wavHdr, sizeof(WAVEHDR));
			}
		}
	}
#endif

	m_nTimerID = timeSetEvent(uDelay, 0, VideoPlayTimeProc, (DWORD)this, TIME_PERIODIC);

	return 0;
}
