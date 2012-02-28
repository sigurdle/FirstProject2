// LXMoviePlayerCtl.cpp : Implementation of CLXMoviePlayerCtl

#include "stdafx.h"
#include "LXMoviePlayer.h"
#include "LXMoviePlayerCtl.h"

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CMoviePlayerFilter::CInputPin::Receive(ILMediaSample *pSample)
{
	EnterCriticalSection(&m_pLock);
	/*

	while (1)
	{
		EnterCriticalSection(&m_pFilter->m_pLock);
		if (m_pFilter->m_state == LState_Running)
			break;
		LeaveCriticalSection(&m_pFilter->m_pLock);
	}
	LeaveCriticalSection(&m_pFilter->m_pLock);

	*/

//	MessageBeep(-1);

	double timeStart;
	double timeEnd;
	pSample->GetTime(&timeStart, &timeEnd);

// Wait until it's time to display the sample
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_pFilter->m_clock->AdviseTime(m_pFilter->m_tStart/*baseTime*/, timeStart/*streamTime*/, hEvent, NULL);
	WaitForSingleObject(hEvent, INFINITE);

	CloseHandle(hEvent);

	m_pSample = static_cast<CVideoSample*>(pSample);

	m_pFilter->m_pMoviePlayer->m_cwnd.PostMessage(WM_USER+100, 0, 0);

	LeaveCriticalSection(&m_pLock);

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CLXMoviePlayerCtl

HRESULT CLXMoviePlayerCtl::OnDraw(ATL_DRAWINFO& di)
{
	CRect& rc = *(CRect*)di.prcBounds;
//	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	CDCHandle dc(di.hdcDraw);

	CPoint oldOrg;
	dc.OffsetViewportOrg(rc.left, rc.top, &oldOrg);

	CRect client(0, 0, rc.Width(), rc.Height());

	if (m_pFilter)	// Video render filter
	{
		CRect availrect(0, 0, client.Width(), client.Height()-16);

		if (m_pFilter->m_pInput->m_mediaType)
		{
			long fullwidth;
			long fullheight;
			m_pFilter->m_pInput->m_mediaType->GetWidth(&fullwidth);
			m_pFilter->m_pInput->m_mediaType->GetHeight(&fullheight);

			CSize size;

			size.cx = availrect.Width();
			size.cy = (size.cx*fullheight)/fullwidth;

			if (size.cy > availrect.Height())
			{
				size.cy = availrect.Height();
				size.cx = (size.cy*fullwidth)/fullheight;
			}

			m_videoRect.left = availrect.left + (availrect.Width()-size.cx)/2;
			m_videoRect.top = availrect.top + (availrect.Height()-size.cy)/2;
			m_videoRect.right = m_videoRect.left + size.cx;
			m_videoRect.bottom = m_videoRect.top + size.cy;
		}

		if (m_pFilter->m_pInput->m_pSample)
		{
			StretchDIBits(dc,
				m_videoRect.left, m_videoRect.top, m_videoRect.Width(), m_videoRect.Height(),
				0, 0,
				m_pFilter->m_pInput->m_pSample->m_lpBmi->biWidth, m_pFilter->m_pInput->m_pSample->m_lpBmi->biHeight,
				m_pFilter->m_pInput->m_pSample->m_bits, (BITMAPINFO*)m_pFilter->m_pInput->m_pSample->m_lpBmi,
				DIB_RGB_COLORS, SRCCOPY);
		}
	}

	{
		m_playRect.SetRect(client.left, client.bottom-16, client.left+16, client.bottom);
		CRect rect = m_playRect;
		dc.Draw3dRect(rect, RGB(20, 20, 30), RGB(200, 200, 210));
	}

//	m_sliderRect.SetRect(m_rcPos.left, m_rcPos.bottom-16, m_rcPos.right, m_rcPos.bottom);
	{
		m_sliderRect.SetRect(client.left+16, client.bottom-16, client.right, client.bottom);

		CRect rect = m_sliderRect;
		dc.Draw3dRect(rect, RGB(20, 20, 30), RGB(200, 200, 210));

		rect.InflateRect(-1,-1);
		dc.Draw3dRect(rect, RGB(30, 30, 40), RGB(180, 180, 190));

		rect.InflateRect(-1,-1);
		dc.FillSolidRect(rect, RGB(190, 190, 200));
	}

	{
		CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
		double currentPosition;
		seeking->GetCurrentPosition(&currentPosition);

		int width = m_sliderRect.Width()-4;
		int knobWidth = 16;

		double secondWidth = (width-knobWidth) / m_duration;

		int x = (currentPosition * secondWidth);

		m_knobRect.SetRect(m_sliderRect.left+2+x, m_sliderRect.top+2, m_sliderRect.left+2+x+knobWidth, m_sliderRect.bottom-2);

		CRect rect = m_knobRect;
		dc.Draw3dRect(rect, RGB(200, 200, 210), RGB(20,20,30));

		rect.InflateRect(-1,-1);
		dc.FillSolidRect(rect, RGB(210, 210, 210));
	}

	dc.SetViewportOrg(oldOrg.x, oldOrg.y, NULL);

	return S_OK;
}

LRESULT CLXMoviePlayerCtl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;

	if (m_dragging == 0)
	{
		if (m_playRect.PtInRect(point))
		{
			m_dragging = 1;
		}
		else if (m_sliderRect.PtInRect(point))
		{
			m_dragging = 2;
		}

		if (m_dragging)
		{
			m_spInPlaceSite->SetCapture(TRUE);
		}
	}
	return 0;
}

/*
DWORD WINAPI ThreadStartProc(
  LPVOID lpParameter   // thread data
)
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
	}

	return 0;
}
*/

LRESULT CLXMoviePlayerCtl::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		m_spInPlaceSite->SetCapture(FALSE);

		if (m_dragging == 1)	// Play
		{
			m_filterGraph->Run();
			/*
			DWORD m_threadId;
			HANDLE m_hThread = CreateThread(NULL, 0L, ThreadStartProc, (LPVOID)NULL, 0, &m_threadId);
*/
		}

		m_dragging = 0;
	}

	return 0;
}

LRESULT CLXMoviePlayerCtl::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_dragging)
	{
#if 0
		if (m_dragging == 2)
		{
			int width = m_sliderRect.Width()-4;
			int knobWidth = 16;

			double secondWidth = (width-knobWidth) / m_duration;

			double position = (point.x-m_sliderRect.left)/secondWidth;

			CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
			seeking->Seek(position);

			m_spInPlaceSite->InvalidateRect(NULL, TRUE);
		}
#endif
	}
	return 0;
}

STDMETHODIMP CLXMoviePlayerCtl::get_src(BSTR *pVal)
{
	return m_src.CopyTo(pVal);
}

STDMETHODIMP CLXMoviePlayerCtl::put_src(BSTR newVal)
{
	m_src = newVal;

	CComQIPtr<IServiceProvider> sp = m_spClientSite;
	if (sp)
	{
		CComPtr<IBindHost> bindHost;
		if (SUCCEEDED(sp->QueryService(SID_SBindHost, &bindHost)))
		{
			CComPtr<IMoniker> imkName;

			CComPtr<IBindCtx> ctx;
			CreateBindCtx(0/*reserved*/, &ctx);

			if (SUCCEEDED(bindHost->CreateMoniker(m_src, NULL, &imkName, 0)))
			{
				m_filterGraph.CoCreateInstance(CLSID_LFilterGraph);
				m_filterGraph->AddSourceFilterForMoniker(imkName, ctx, L"", NULL);

				CComPtr<DispILStreams> streams;
				m_filterGraph->get_Streams(&streams);

				CComPtr<ILMediaStream> stream;
				streams->Item(0, (DispILMediaStream**)&stream);
				if (stream)
				{
					// Connect our video renderer filter
					CComObject<CMoviePlayerFilter>::CreateInstance(&m_pFilter);
					m_pFilter->AddRef();
					m_pFilter->m_pMoviePlayer = this;
					m_filterGraph->AddFilter(m_pFilter);

					CComPtr<ILPin> pin;
					stream->GetPin(&pin);
					m_filterGraph->ConnectDirect(pin, m_pFilter->m_pInput, NULL);

				}

				CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
				seeking->GetDuration(&m_duration);
			}
		}
	}

	return S_OK;
}
