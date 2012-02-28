// AudioClipView.cpp : Implementation of CAudioClipView
#include "stdafx.h"
#include "LXMedia.h"
#include "LXMedia2.h"

#include "AudioClipView.h"

#include "EMediaClipDocument.h"

void DrawWaveForm(
	HDC hDC,

	LPWAVEFORMATEX wavefmt,
	LPSTR waveData,
	LONGLONG totalSamples,
	LONGLONG totalXPels,

	int startx, int endx,

	RECT& rect)
{
	ATLASSERT(hDC);
	ATLASSERT(wavefmt);
	ATLASSERT(waveData);

	int nChannels = wavefmt->nChannels;

	int yoffset = rect.top;
	int height = rect.bottom - rect.top;
	int height2 = height/2;
	int y2 = height2/nChannels;

	for (unsigned int chan = 0; chan < nChannels; chan++)
	{
		int y = yoffset+height2*(chan+1);

	//	dc.MoveTo(m_waveRect.left, y);
	//	dc.LineTo(m_waveRect.right+1, y);
	}

	HPEN	pen[2];
	pen[0] = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_ACTIVECAPTION));
	pen[1] = CreatePen(PS_SOLID, 1, RGB(240, 40, 40));
	HPEN	pOldPen = (HPEN)GetCurrentObject(hDC, OBJ_PEN);

	LONGLONG numSamples = totalSamples;
//	ULONG samplesPerPixel = (double)numSamples / totalXPels + 0.5;
//	ULONG pixelsPerSample = (double)totalXPels / numSamples + 0.5;
	ULONG samplesPerPixel = MulDiv(numSamples, 16, totalXPels);
	ULONG pixelsPerSample = MulDiv(totalXPels, 16, numSamples);

	if (wavefmt->wBitsPerSample == 8)
	{
		for (unsigned int chan = 0; chan < nChannels; chan++)
		{
			SelectObject(hDC, pen[chan]);

			//DWORD nsample = totalXPels/numSamples + (startx*samplesPerPixel);

			int y = yoffset+y2+(height2*chan);

			if (samplesPerPixel > 16)
			{
				for (unsigned int x = startx; x < endx; x++)
				{
					DWORD nsample = MulDiv(x, numSamples, totalXPels);

					LPBYTE pb = ((LPBYTE)(waveData)) + nsample * nChannels;

					int wmin, wmax;

					wmin = wmax = 128;
					pb += chan;

					DWORD count = samplesPerPixel;
					if (nsample+(count>>4) > numSamples-1)
						count -= ((nsample+(count>>4))-(numSamples-1))<<4;

					/*
					DWORD count = samplesPerPixel/16;
					if (nsample+(count) > numSamples-1)
						count -= ((nsample+(count))-(numSamples-1));
						*/

					//ATLASSERT(nsample+count < numSamples);

					for (ULONG i = 0; i < count; i += 16)
					{
						if (*pb < wmin) wmin = *pb;
						if (*pb > wmax) wmax = *pb;
						pb += nChannels;
					}

					LONG	hy, ly;

					hy = ((wmax-128)*(height/nChannels))>>8;
					ly = ((wmin-128)*(height/nChannels))>>8;

					MoveToEx(hDC, rect.left + x, y-hy, NULL);
					LineTo(hDC, rect.left + x, y-ly+1);

				//	nsample += samplesPerPixel;
				}
			}
			else
			{

				ATLASSERT(pixelsPerSample > 0);
				for (unsigned int x = (startx<<4); x < (endx<<4); x += pixelsPerSample)
				{
					DWORD nsample = MulDiv(x>>4, numSamples, totalXPels);

					if (nsample > numSamples-1) nsample = numSamples-1;	// TODO remove

					ATLASSERT(nsample >= 0 && nsample < numSamples);

					LPBYTE pb = ((LPBYTE)(waveData)) + nsample * nChannels;
					pb += chan;

					/*
					DWORD count = samplesPerPixel;
					if (nsample+count > numSamples-1)
						count -= (nsample+count)-(numSamples-1);
						*/

					int value = *pb;

					long y2 = ((value-128)*(height/nChannels))>>8;

					//int y = yoffset+y2+(height2*chan);

					if (x == (startx<<4))
						MoveToEx(hDC,	rect.left + (x)>>4, y-y2, NULL);
					else
						LineTo(hDC,	rect.left + (x)>>4, y-y2);

					LineTo(hDC,	rect.left + ((x+pixelsPerSample)>>4),	y-y2);

				//	nsample += samplesPerPixel;
				}
			}
		}
	}
	else if (wavefmt->wBitsPerSample == 16)
	{
		for (unsigned int chan = 0; chan < nChannels; chan++)
		{
			SelectObject(hDC, pen[chan]);

			//LONGLONG nsample = totalXPels/numSamples + (startx*samplesPerPixel);

			for (unsigned int x = startx; x < endx; x++)
			{
				DWORD nsample = MulDiv(x, numSamples, totalXPels);

				SHORT* pw = ((SHORT*)(waveData)) + nsample * nChannels;

				int wmin, wmax;

				wmin = wmax = 0;
				pw += chan;

				DWORD count = samplesPerPixel;
				if (nsample+count > numSamples-1)
					count -= (nsample+count)-(numSamples-1);

				//ATLASSERT(nsample+samplesPerPixel-1 < numSamples);

				for (DWORD i = 0; i < count; i += 1)
				{
					if (*pw < wmin) wmin = *pw;
					if (*pw > wmax) wmax = *pw;
					pw += nChannels;
				}

				LONG	hy, ly;

				hy = ((wmax)*(height/nChannels))>>16;
				ly = ((wmin)*(height/nChannels))>>16;

				int y = yoffset+y2+(height2*chan);

				MoveToEx(hDC, rect.left + x, y-hy, NULL);
				LineTo(hDC, rect.left + x, y-ly+1);

		//		nsample += samplesPerPixel;
			}
		}

	/*
		for (int x = startx; x < endx; x++)
		{
			SHORT*	pw = ((SHORT*)(waveData)) + (DWORD)j * nChannels;
			
			for (int chan = 0; chan < nChannels; chan++)
			{
				int	wmin, wmax;
				
				wmin = wmax = 0;
				pw += chan;
				
				for (WORD i = 0; i < (WORD)inc; i += 1)
				{
					if (*pw < wmin) wmin = *pw;
					if (*pw > wmax) wmax = *pw;
					pw += nChannels;
				}
				
				LONG	hy, ly;
				
				hy = ((wmax)*(height/nChannels))>>16;
				ly = ((wmin)*(height/nChannels))>>16;
				
				int	y = yoffset+y2+(height2*chan);
				
				SelectObject(hDC, pen[chan]);
				
				MoveToEx(hDC, rect.left + x, y-hy, NULL);
				LineTo(hDC, rect.left + x, y-ly+1);
			}
			
			j += inc;
		}
		*/
	}
	else
		ATLASSERT(0);
	
	SelectObject(hDC, pOldPen);
	
	DeleteObject(pen[0]);
	DeleteObject(pen[1]);
}

/////////////////////////////////////////////////////////////////////////////
// CAudioClipView

LRESULT CAudioClipView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axhorz.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
	m_axhorz.AttachControl(m_horz, &p);

	IDispEventImpl<1, CAudioClipView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);
	//IDispEventImpl<2, CAudioClipView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	return 0;
}

LRESULT CAudioClipView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CAudioClipView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
	//IDispEventImpl<2, CAudioClipView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	return 0;
}

LRESULT CAudioClipView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	long scrollposX; m_horz->get_pos(&scrollposX);

	CRect videoRect = m_waveRect;
	videoRect.top = 0;
	videoRect.bottom = 20;

	int state;
	
	state = dc.SaveDC();
	if (dc.IntersectClipRect(videoRect) > NULLREGION)
	{
		dc.FillSolidRect(&videoRect, RGB(196, 196, 196));

		dc.OffsetViewportOrg(-scrollposX, 0);

		//CComPtr<ILMediaLoader> loader;
		//m_pDocument->m_movie->GetLoader(&loader);

#if 0
		CComQIPtr<ILVideo> video;
		m_pDocument->m_movie->GetVideo(&video);

		if (video)
		{
			double videoDuration;
			
			CComQIPtr<ILMediaSeeking> seeking = video;
			if (seeking)
				seeking->GetDuration(&videoDuration);
			else
				videoDuration = 0;

			int m_videoXPels = m_totalXPels * videoDuration / m_pDocument->m_duration;

			dc.FillSolidRect(0, 0, m_videoXPels, 20, RGB(255, 0, 0));
		}
#endif
	}
	dc.RestoreDC(state);

	state = dc.SaveDC();
	if (dc.IntersectClipRect(m_waveRect) > NULLREGION)
	{
		dc.FillSolidRect(&m_waveRect, RGB(255, 255, 255));

		dc.OffsetViewportOrg(-scrollposX, 0);

		/*
		CRect clip;
		dc.GetClipBox(&clip);

		if (clip.right > m_waveXPels)
			clip.right = m_waveXPels;
			*/

		DrawWaveForm(dc.m_hDC,
			m_pStream->m_wavFormat, m_pStream->m_wavBuffer, m_pStream->m_nSamples,
			m_waveXPels, 0/*clip.left*/, m_waveXPels/*clip.right*/, m_waveRect);

		DrawWaveSelection(dc.m_hDC);

		if (m_bPlayMarker)
		{
			double inc = (double)m_pStream->m_pDocument->m_duration/m_totalXPels;
			int x = m_pStream->m_pDocument->m_currentTime / inc;

			dc.PatBlt(x, m_waveRect.top, 1, m_waveRect.Height(), DSTINVERT);
		}
	}
	dc.RestoreDC(state);

	return 0;
}

LRESULT CAudioClipView::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return TRUE;
}

void CAudioClipView::DrawWaveSelection(HDC hDC)
{
	CDCHandle dc(hDC);

	long scrollposX; m_horz->get_pos(&scrollposX);

	double inc = (double)m_pStream->m_pDocument->m_duration/m_totalXPels;

	int startX = GetMarkStart() / inc;
	int endX = GetMarkEnd() / inc;

	startX -= scrollposX;
	endX -= scrollposX;

	if (startX < m_waveRect.left) startX = m_waveRect.left;
	if (endX > m_waveRect.right) endX = m_waveRect.right;

	startX += scrollposX;
	endX += scrollposX;

	if (endX >= startX)
	{
		dc.PatBlt(startX, m_waveRect.top, endX-startX+1, m_waveRect.Height(), DSTINVERT);
	}
}

LRESULT CAudioClipView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	long scrollposX; m_horz->get_pos(&scrollposX);

	CPoint pt = point;
	pt.x += scrollposX;

	if (!m_dragging)
	{
		m_dragging = 1;
		SetCapture();
		
	//	double inc = (double)pDoc->GetAbsTotalFrames()/WaveXPels();
		double inc = (double)m_pStream->m_pDocument->m_duration/m_totalXPels;

		double position = pt.x*inc;
		
		int startx = GetMarkStart()/inc;
		int endx = GetMarkEnd()/inc;
		
		if (abs(pt.x-startx) < 4)	// Drag start marker
		{
			m_startSample = GetMarkEnd();
		}
		else if (abs(pt.x-endx) < 4)	// Drag end marker
		{
			m_startSample = GetMarkStart();
		}
		else	// Set new selection
		{
			m_startSample = position;
		}

		OnMouseMove(nFlags, point);
	}

	return 0;
}

LRESULT CAudioClipView::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposX; m_horz->get_pos(&scrollposX);

	CClientDC dc(m_hWnd);
	dc.OffsetViewportOrg(-scrollposX, 0);

	DrawWaveSelection(dc.m_hDC);
	
	// Select All
	SetMarkStart(0);

	double audioDuration = (double)m_pStream->m_nSamples / m_pStream->m_wavFormat->nSamplesPerSec;

	SetMarkEnd(audioDuration);//m_pVideo->GetSamples()-1;

	DrawWaveSelection(dc.m_hDC);
	
	return 0;
}

LRESULT CAudioClipView::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		m_dragging = 0;
		ReleaseCapture();
	}
	return 0;
}

void CAudioClipView::OnMouseMove(UINT nFlags, CPoint point)
{
	long scrollposX; m_horz->get_pos(&scrollposX);

	CPoint pt = point;
	pt.x += scrollposX;

	if (m_dragging)
	{
		CClientDC dc(m_hWnd);

		dc.OffsetViewportOrg(-scrollposX, 0);

		DrawWaveSelection(dc.m_hDC);

		double inc = (double)m_pStream->m_pDocument->m_duration/m_totalXPels;

		double position = pt.x*inc;

		if (position > m_startSample)
		{
			SetMarkStart(m_startSample);
			SetMarkEnd(position);
		}
		else
		{
			SetMarkStart(position);
			SetMarkEnd(m_startSample);
		}

		if (GetMarkStart() < 0) SetMarkStart(0);
//		if (pDoc->m_markEnd > pDoc->GetComp()->m_pVideo->GetSamples()-1)
//			pDoc->m_markEnd = pDoc->GetComp()->m_pVideo->GetSamples()-1;
		if (GetMarkEnd() > m_pStream->m_pDocument->m_duration)
			SetMarkEnd(m_pStream->m_pDocument->m_duration);

		DrawWaveSelection(dc.m_hDC);

		m_pStream->m_pDocument->Seek(position);
	}
}

LRESULT CAudioClipView::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnMouseMove(wParam, point);

	return 0;
}

LRESULT CAudioClipView::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = (HWND) wParam;       // handle to window with cursor 
	int nHittest = LOWORD(lParam);  // hit-test code 
	int wMouseMsg = HIWORD(lParam); // mouse-message identifier 

	if (nHittest == HTCLIENT)
	{
		HCURSOR	hCursor = NULL;

		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		if (m_waveRect.PtInRect(point))
		{
			long scrollposX; m_horz->get_pos(&scrollposX);

			CPoint pt;
			pt.x = point.x + scrollposX;
			pt.y = point.y;

			double inc = (double)m_pStream->m_pDocument->m_duration/m_totalXPels;

			double position = point.x*inc;
			
			int startx = GetMarkStart()/inc;
			int endx = GetMarkEnd()/inc;

			if (abs(pt.x-startx) < 4)
			{
				hCursor = LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_MARKSTART));
			}
			else if (abs(pt.x-endx) < 4)
			{
				hCursor = LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_MARKEND));
			}
			else
			{
				hCursor = LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_MARK));
			}
		}

		if (hCursor)
		{
			SetCursor(hCursor);
			return TRUE;
		}
	}
	
	return FALSE;
}

LRESULT CAudioClipView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	/*
	m_bottomRect = CRect(0, client.bottom-32, client.right, client.bottom);
	m_sliderRect = m_bottomRect;
	m_sliderRect.left += 8;
	m_sliderRect.right -= 8;
	*/

	m_waveRect.left = 0;
	m_waveRect.top = 20;
	m_waveRect.right = client.right;
	m_waveRect.bottom = client.bottom-16;

	m_axhorz.MoveWindow(0, m_waveRect.bottom, m_waveRect.Width(), 16);

	OnSize();

	return 0;
}

void CAudioClipView::OnSize() 
{
	CRect client;
	GetClientRect(&client);

	double audioDuration = (double)m_pStream->m_nSamples / m_pStream->m_wavFormat->nSamplesPerSec;

	if (m_bViewAll)
	{
		m_totalXPels = client.right;// * m_duration / audioDuration;
	}

	if (m_totalXPels < client.right) m_totalXPels = client.right;

	m_waveXPels = m_totalXPels * audioDuration / m_pStream->m_pDocument->m_duration;

	m_horz->SetInfo(0, m_totalXPels, m_waveRect.Width());
}

void __stdcall CAudioClipView::OnHorzScroll(long code, long pos)
{
	long oldPos; m_horz->get_pos(&oldPos);

	CRect	rect = m_waveRect;
	rect.top = 0;
	
	m_horz->put_pos(pos);

	ScrollWindow(oldPos-pos, 0, &rect, &rect);
}

void CAudioClipView::OnStartPlay()
{
	ATLASSERT(m_bPlayMarker == false);
}

void CAudioClipView::OnPlaying()
{
	if (m_hWnd)
	{
		CClientDC dc(m_hWnd);

		long scrollposX; m_horz->get_pos(&scrollposX);
		double inc = (double)m_pStream->m_pDocument->m_duration/m_totalXPels;

		if (m_bPlayMarker)
		{
			int x = m_playMarker / inc;

			dc.PatBlt(x-scrollposX, m_waveRect.top, 1, m_waveRect.Height(), DSTINVERT);
			m_bPlayMarker = false;
		}

		m_playMarker = m_pStream->m_pDocument->m_currentTime;

		int x = m_playMarker / inc;

		dc.PatBlt(x-scrollposX, m_waveRect.top, 1, m_waveRect.Height(), DSTINVERT);
		m_bPlayMarker = true;
	}
}

void CAudioClipView::OnStopPlay()
{
	if (m_hWnd)
	{
		CClientDC dc(m_hWnd);

		long scrollposX; m_horz->get_pos(&scrollposX);
		double inc = (double)m_pStream->m_pDocument->m_duration/m_totalXPels;

		if (m_bPlayMarker)
		{
			int x = m_playMarker / inc;

			dc.PatBlt(x-scrollposX, m_waveRect.top, 1, m_waveRect.Height(), DSTINVERT);

			m_bPlayMarker = false;
		}
	}
}

BEGIN_CMD_MAP(CAudioClipView)
	CMD_HANDLER(ID_EDIT_MUTE, OnEditMute)
	CMD_HANDLER(ID_VIEW_ALL, OnViewAll)
	CMD_HANDLER(ID_VIEW_SELECTION, OnViewSelection)
	CMD_HANDLER(ID_VIEW_ZOOMIN, OnViewZoomIn)
	CMD_HANDLER(ID_VIEW_ZOOMOUT, OnViewZoomOut)
	CMD_HANDLER(ID_VIEW_ZOOM11, OnViewZoom11)
END_CMD_MAP()

// ICommandTarget
STDMETHODIMP CAudioClipView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	CComQIPtr<ICommandTarget> target;

// Try document
	target = m_pStream->m_pDocument;
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

	return S_OK;
}

LRESULT CAudioClipView::OnEditMute(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DWORD startSample = GetMarkStart() * m_pStream->m_wavFormat->nSamplesPerSec;
	DWORD endSample = GetMarkEnd() * m_pStream->m_wavFormat->nSamplesPerSec;

	DWORD nSamples = endSample-startSample+1;

	UINT nChannels = m_pStream->m_wavFormat->nChannels;
	DWORD len = nSamples * nChannels;

	if (m_pStream->m_wavFormat->wBitsPerSample == 8)
	{
		BYTE*	ptr = ((BYTE*)m_pStream->m_wavBuffer) + startSample*nChannels;

		for (int i = 0; i < len; i++)
		{
			ptr[i] = 128;
		}
	}
	else if (m_pStream->m_wavFormat->wBitsPerSample == 16)
	{
		SHORT* ptr = ((SHORT*)m_pStream->m_wavBuffer) + startSample*nChannels;

		for (int i = 0; i < len; i++)
		{
			ptr[i] = 0;
		}
	}
	else
		ATLASSERT(0);

	Invalidate();

	return 0;
}

LRESULT CAudioClipView::OnViewAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_bViewAll = TRUE;

	OnSize();
	Invalidate();

	return 0;
}

LRESULT CAudioClipView::OnViewSelection(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	double inc = (double)m_pStream->m_pDocument->m_duration/m_totalXPels;

	if (GetMarkEnd() > GetMarkStart())
	{
		double duration = GetMarkEnd() - GetMarkStart();

		m_bViewAll = FALSE;
		m_totalXPels = m_waveRect.Width() * m_pStream->m_pDocument->m_duration / duration;
		long scrollposX = GetMarkStart()/((double)m_pStream->m_pDocument->m_duration/m_totalXPels);

		OnSize();

		m_horz->put_pos(scrollposX);
	}

	Invalidate();

	return 0;
}

LRESULT CAudioClipView::OnViewZoomIn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_bViewAll = FALSE;
	m_totalXPels *= 2;

	OnSize();
	Invalidate();

	return 0;
}

LRESULT CAudioClipView::OnViewZoomOut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_bViewAll = FALSE;
	m_totalXPels /= 2;

	OnSize();
	Invalidate();

	return 0;
}

LRESULT CAudioClipView::OnViewZoom11(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_bViewAll = FALSE;
	m_totalXPels = m_pStream->m_nSamples;

	OnSize();
	Invalidate();

	return 0;
}
