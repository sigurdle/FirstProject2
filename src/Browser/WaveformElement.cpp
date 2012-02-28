#include "stdafx.h"
#include "Browser.h"
#include "WaveformElement.h"

#include <algorithm>

namespace System
{

using namespace UI;

WaveformElement::WaveformElement()
{
	m_wave = NULL;
//	m_nsamples = 0;
	m_markStart = 0;
	m_markEnd = 0;

	m_startSample = 0;

	m_dragging = 0;

	m_display = 2;

#if 0//WIN32
//	RECT rc;
//	SetRectEmpty(&rc);
	Create(NULL, LDraw::RectI(), NULL, WS_POPUP);
#endif

	m_cur = 0;

	m_freq = 1;
}

#if WIN32
bool WaveformElement::ProcessWindowMessage(MSWindows::Hwnd hWnd, UINT uMsg, MSWindows::WPARAM wParam, MSWindows::LPARAM lParam, MSWindows::LRESULT& lResult)
{
	if (uMsg == WM_TIMER)
	{
		OnTimer();
		return true;
	}
	return false;
}
#endif

#if 0
void WaveformElement::handleEvent(Event* evt)
{
	if (evt->get_eventPhase() != CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"mousedown")
		{
		//	LMedia::WaveOutput* wo = new LMedia::WaveOutput;



			evt->stopPropagation();
			OnLButtonDown(dynamic_cast<MouseEvent*>(evt));
		}
		else if (*evt->get_type() == L"mouseup")
		{
			evt->stopPropagation();
			OnLButtonUp(dynamic_cast<MouseEvent*>(evt));
		}
		else if (*evt->get_type() == L"mousemove")
		{
			evt->stopPropagation();
			OnMouseMove(dynamic_cast<MouseEvent*>(evt));
		}
	}
}
#endif

void WaveformElement::OnTimer()
{
	m_cur = wo->GetCurrentPlayCursor();// / m_wave->m_wfx->nBlockAlign;

	m_lock.Lock();

	LONGLONG markStart = GetMarkStart();
	LONGLONG markEnd = GetMarkEnd();
	if (markEnd <= markStart) markEnd = m_wave->m_nsamples;

	LONGLONG nSamples = markEnd - markStart;

	m_cur %= nSamples;

	//m_cur -= m_nloop * m_nsamples;

	m_lock.Unlock();

	m_cur += markStart;

	/*
	DWORD dwCurrentPlayCursor;
	//DWORD dwCurrentWriteCursor;
	HRESULT hr = wo->GetDDSoundBuffer()->GetCurrentPosition(&dwCurrentPlayCursor, NULL);
	*/

	Invalidate();
}

LDraw::SizeD WaveformElement::MeasureOverride(LDraw::SizeD availSize)
{
	return LDraw::SizeD(m_wave->m_nsamples, 100/*availSize.Height*/);
}

/*
void WaveformElement::OnArrange(LDraw::SizeD finalSize)
{
//	path = LDraw::GraphicsPathF();

//	return LDraw::SizeD(m_nsamples, availSize.Height);
}
*/

void WaveformElement::OnRender(UI::Graphics* pGraphics)
{
	LDraw::SizeD actualSize = get_ActualSize();

	pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(255, 255, 255)), 0, 0, actualSize.Width, actualSize.Height);
//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(110, 210, 60)), 0, 0, actualSize.Width, actualSize.Height);

//	pGraphics->SetSmoothingMode(LDraw::SmoothingModeHighQuality);
	//long scrollposX; m_horz->get_pos(&scrollposX);

	DrawWaveSelection(pGraphics);

//	DrawWaveForm(pGraphics, m_wfx, m_data, m_nsamples

	//LDraw::Pen pen(LDraw::Color(0, 200, 0), 2);
	LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color(0, 0, 0));
//	LDraw::SolidBrush brush(LDraw::Color(170, 170, 170));
	LDraw::SolidBrush* shadowbrush = new LDraw::SolidBrush(LDraw::Color(0, 0/*200*/, 0));

	pGraphics->PushTransform();

	/*
	LDraw::PointD scale =
		oldTransform.Transform(LDraw::PointD(1,0)) -
		oldTransform.Transform(LDraw::PointD(0,0));
		*/

//	pGraphics->ScaleTransform(1/16.0, 1/16.0);

//	double scalex = fabs(scale.X);
//	int scalex = (int)(sqrt(scale.X*scale.X + scale.Y*scale.Y)*(1<<24));
	double scalex = m_scale;

	LONGLONG samplesPerPixel = (1<<16/* / 16*/)/scalex;

	pGraphics->ScaleTransform(1/scalex/* / 16*/, 1);

	if (false)
	{
		LDraw::RectF bounds;
		pGraphics->GetClipBounds(&bounds);
	}

//	if (bounds.X < 0) bounds.X = 0;
//	if (bounds.Y < 0) bounds.Y = 0;

//	pGraphics->ScaleTransform(4, 1);

//	TRACE("%f\n", bounds.X);

//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(0, 0, 0)), bounds.X-2, 20, bounds.Width, 8);

	if (m_commands == NULL)
	{
		int npixels = ((LONGLONG)m_wave->m_nsamples<<16) / samplesPerPixel;

	#if 0
		int pixelLeft = bounds.X;
		int pixelRight = ceil(bounds.GetRight());
	#endif

		int pixelLeft = 0;
		int pixelRight = npixels;

		if (pixelLeft < 0) pixelLeft = 0;
		if (pixelRight > npixels) pixelRight = npixels;

		if (pixelRight <= pixelLeft)
			return;

		LONGLONG left = (pixelLeft) * samplesPerPixel;
		LONGLONG right = (pixelRight) * samplesPerPixel;

	//	path.AddMove(left, actualSize.Height/2);

		LDraw::GraphicsPathF* path = new LDraw::GraphicsPathF();

		//if (path.IsNull())
		{
			if (m_wave->m_wfx->wBitsPerSample == 8)
			{
				char* minbuffer = new char[pixelRight-pixelLeft];
				char* maxbuffer = new char[pixelRight-pixelLeft];
				char* buffer = minbuffer;

				LONGLONG i;

				for (i = left; i < right; i += samplesPerPixel)
				{
					uint8* p = m_wave->m_data + (i>>16);

					int n = (i-left) / (samplesPerPixel);

					minbuffer[n] = 0;
					maxbuffer[n] = 0;

				//	buffer[n] = *p;

					for (int j = 0; j < (samplesPerPixel>>16); j++)
					{
						minbuffer[n] = std::min(minbuffer[n], (char)(*p/* - 128*/));
						maxbuffer[n] = std::max(maxbuffer[n], (char)(*p/* - 128*/));
					//	buffer[n] = (buffer[n] + *p) / 2;
						p++;
					}
				}

				if (m_display == 0)
				{
					i = pixelLeft;
					if (abs(minbuffer[i-pixelLeft]) > abs(maxbuffer[i-pixelLeft]))
						path->AddMove(i, actualSize.Height/2 + minbuffer[i-pixelLeft]*actualSize.Height / 256);
					else
						path->AddMove(i, actualSize.Height/2 + maxbuffer[i-pixelLeft]*actualSize.Height / 256);

					i++;
					for (; i < pixelRight; i++)
					{
						if (abs(minbuffer[i-pixelLeft]) > abs(maxbuffer[i-pixelLeft]))
							path->AddLine(i, actualSize.Height/2 + minbuffer[i-pixelLeft]*actualSize.Height / 256);
						else
							path->AddLine(i, actualSize.Height/2 + maxbuffer[i-pixelLeft]*actualSize.Height / 256);
					}
				}
				else if (m_display == 1)
				{
					{
						i = pixelLeft;
						path->AddMove(i, actualSize.Height/2);
						for (; i < pixelRight; i++)
						{
							path->AddLine(i, actualSize.Height/2 + maxbuffer[i-pixelLeft]*actualSize.Height / 256);
							path->AddLine(i+1/*/16.0*/, actualSize.Height/2 + maxbuffer[i-pixelLeft]*actualSize.Height / 256);
						}
						path->AddLine(i, actualSize.Height/2);
						path->AddLine(pixelLeft, actualSize.Height/2);
					}

				//	path.AddRectangle(0, 0, 200, 20);

					{
						i = pixelLeft;
						path->AddMove(i, actualSize.Height/2);
						for (; i < pixelRight; i++)
						{
							path->AddLine(i, actualSize.Height/2 + minbuffer[i-pixelLeft]*actualSize.Height / 256);
							path->AddLine(i+1, actualSize.Height/2 + minbuffer[i-pixelLeft]*actualSize.Height / 256);
						}
						path->AddLine(i, actualSize.Height/2);
						path->AddLine(pixelLeft, actualSize.Height/2);
					}
				}
				else
				{
					{
						i = pixelLeft;
						path->AddMove(i, actualSize.Height/2);
						for (; i < pixelRight; i++)
						{
							path->AddLine(i, actualSize.Height/2 + maxbuffer[i-pixelLeft]*actualSize.Height / 256);
							path->AddLine(i+1/*/16.0*/, actualSize.Height/2 + maxbuffer[i-pixelLeft]*actualSize.Height / 256);
						}
						path->AddLine(i, actualSize.Height/2);
						path->AddLine(pixelLeft, actualSize.Height/2);
					}

					{
						i = pixelLeft;
						path->AddMove(i, actualSize.Height/2);
						for (; i < pixelRight; i++)
						{
							path->AddLine(i, actualSize.Height/2 + minbuffer[i-pixelLeft]*actualSize.Height / 256);
							path->AddLine(i+1, actualSize.Height/2 + minbuffer[i-pixelLeft]*actualSize.Height / 256);
						}
						path->AddLine(i, actualSize.Height/2);
						path->AddLine(pixelLeft, actualSize.Height/2);
					}
				}

				/*
				{
					i = pixelLeft;
					path.AddMove(i, actualSize.Height/2);
					for (; i < pixelRight; i++)
					{
						path.AddLine(i, actualSize.Height/2 + minbuffer[i-pixelLeft]*actualSize.Height / 256);
					}
					path.AddLine(i, actualSize.Height/2);
					path.AddLine(left, actualSize.Height/2);
					pGraphics->FillPath(&brush, &path);
				}
				*/
				/*
				{
					i = right;
					path.AddMove(i, actualSize.Height/2);
					i--;
					for (; i > left; i--)
					{
						path.AddLine(i, actualSize.Height/2 + minbuffer[i-left]*actualSize.Height / 256);
					}
					path.AddLine(i, actualSize.Height/2);
					path.AddLine(right, actualSize.Height/2);

					pGraphics->FillPath(&brush, &path);
				}
				*/

				delete minbuffer;
				delete maxbuffer;
			}
			else if (m_wave->m_wfx->wBitsPerSample == 16)
			{
				short* minbuffer = new short[pixelRight-pixelLeft];
				short* maxbuffer = new short[pixelRight-pixelLeft];

				int i;

				short* p = ((short*)m_wave->m_data);// + (i>>12);

				for (i = left; i < right; i += samplesPerPixel)
				{
					//uint8* p = ((uint8*)m_data) + (i>>12)*2;

					LONGLONG s = i>>12;

					int n = (i-left) / (samplesPerPixel);

					minbuffer[n] = 0;
					maxbuffer[n] = 0;
					for (int j = 0; j < samplesPerPixel>>12; j++)
					{
						ASSERT(n >= 0 && n < pixelRight-pixelLeft);

						ASSERT(s >= 0 && s < m_wave->m_nsamples);

						minbuffer[n] = std::min(minbuffer[n], p[s]);
						maxbuffer[n] = std::max(maxbuffer[n], p[s]);
						s++;
					}

					/*
					//miny
					path.AddLine(i, actualSize.Height/2 + (char)(*p - 128)*actualSize.Height / 256);
					p++;
					*/
				}

				{
					i = pixelLeft;
					path->AddMove(i, actualSize.Height/2);
					for (; i < pixelRight; i++)
					{
						path->AddLine(i, actualSize.Height/2 + maxbuffer[i-pixelLeft]*actualSize.Height / 65536);
						path->AddLine(i+1, actualSize.Height/2 + maxbuffer[i-pixelLeft]*actualSize.Height / 65536);
					}
					path->AddLine(i, actualSize.Height/2);
					path->AddLine(left, actualSize.Height/2);
					pGraphics->FillPath(brush, path);
				}

				{
					i = pixelLeft;
					path->AddMove(i, actualSize.Height/2);
					for (; i < pixelRight; i++)
					{
						path->AddLine(i, actualSize.Height/2 + minbuffer[i-pixelLeft]*actualSize.Height / 65536);
						path->AddLine(i+1, actualSize.Height/2 + minbuffer[i-pixelLeft]*actualSize.Height / 65536);
					}
					path->AddLine(i, actualSize.Height/2);
					path->AddLine(left, actualSize.Height/2);
					pGraphics->FillPath(brush, path);
				}

				/*
				{
					i = pixelLeft;
					path.AddMove(i, actualSize.Height/2);
					for (; i < pixelRight; i++)
					{
						path.AddLine(i, actualSize.Height/2 + minbuffer[i-pixelLeft]*actualSize.Height / 256);
					}
					path.AddLine(i, actualSize.Height/2);
					path.AddLine(left, actualSize.Height/2);
					pGraphics->FillPath(&brush, &path);
				}
				*/
				/*
				{
					i = right;
					path.AddMove(i, actualSize.Height/2);
					i--;
					for (; i > left; i--)
					{
						path.AddLine(i, actualSize.Height/2 + minbuffer[i-left]*actualSize.Height / 256);
					}
					path.AddLine(i, actualSize.Height/2);
					path.AddLine(right, actualSize.Height/2);

					pGraphics->FillPath(&brush, &path);
				}
				*/

				delete minbuffer;
				delete maxbuffer;
			}
		}

		if (m_display == 0)
		{
		//	__release<LDraw::Pen> pen = new LDraw::Pen(brush);
			LDraw::Pen* pen = new LDraw::Pen(brush);
			pen->SetLineJoin(LDraw::LineJoinBevel);
			pGraphics->DrawPath(pen, path);
		}
		else if (m_display == 1)
		{
			if (false)
			{
				pGraphics->TranslateTransform(1, 1);
				pGraphics->FillPath(shadowbrush, path);
				pGraphics->TranslateTransform(-1, -1);
			}
			pGraphics->FillPath(brush, path);
		}
		else
		{
			LDraw::GraphicsMetafile* pMeta = dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p);

			m_commands = new LDraw::Commands;

			// TODO push
			LDraw::Commands* pOld = pMeta->m_pCommands;
			pMeta->m_pCommands = m_commands;

			LDraw::Pen* pen = new LDraw::Pen(brush);
			pGraphics->DrawPath(pen, path);

			pMeta->m_pCommands = pOld;
		}
	}

	pGraphics->RenderCommands(m_commands);

	pGraphics->PopTransform();

	{
		pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(0,0,0)), m_cur, 0, 1/scalex, actualSize.Height);
	}

#if 0
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
#endif

#if 0
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
#endif
}

void WaveformElement::DrawWaveSelection(Graphics* pGraphics)
{
	LDraw::SizeD actualSize = get_ActualSize();

	LONGLONG startX = GetMarkStart();
	LONGLONG endX = GetMarkEnd();

	if (false)	// Should eventually not be necessary when LDraw implements clipping of floats before converting to ints
	{
		LDraw::RectF bounds;
		pGraphics->GetClipBounds(&bounds);

		if (startX < bounds.X) startX = bounds.X;
		if (endX > bounds.GetRight()) endX = bounds.GetRight();
	}

	if (endX >= startX)
	{

		LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color(128, 160, 190, 255));
		pGraphics->FillRectangle(brush, startX, 0, endX-startX, actualSize.Height);
	}
}

/*
class Thread
{
public:
};

Thread
*/

#if WIN32

HANDLE hWait;

MSWindows::DWORD WINAPI ThreadFunc(void* lpParameter)
{
	WaveformElement* p = (WaveformElement*)lpParameter;

	p->wo = new MediaShow::WaveOutput;
	p->wo->Init();
//	wo->SetWindow(NULL);
	p->wo->SetFormat(p->m_wave->m_wfx);

	//wo->Pause();
	p->wo->Run();

//	uint8* buffer = new uint8[p->m_nsamples*p->m_wfx->nBlockAlign];
//	memcpy(buffer, p->m_data, p->m_nsamples*p->m_wfx->nBlockAlign);

	p->m_nloop = 0;

	MSWindows::SetEvent(hWait);

	LONGLONG markStart = p->GetMarkStart();
	LONGLONG markEnd = p->GetMarkEnd();
	if (markEnd <= markStart) markEnd = p->m_wave->m_nsamples;

	LONGLONG nSamples = markEnd - markStart;

	p->m_bStop = false;

	while (!p->m_bStop)
	{
		p->wo->Receive(p->m_wave->m_data + markStart*p->m_wave->m_wfx->nBlockAlign, (nSamples)*p->m_wave->m_wfx->nBlockAlign);

		p->m_lock.Lock();
		p->m_nloop++;
		p->m_lock.Unlock();
	}

#if 0
	//p->wo->Stop();
	KillTimer(p->m_hWnd, p->m_nTimerID);
#endif

//	WaitForSingleObject(p->wo->m_hEvent[0], INFINITE);
//	WaitForSingleObject(p->wo->m_hEvent[0], INFINITE);

//	delete[] buffer;

	return 0;
}
#endif

void WaveformElement::OnMouseDown(MouseButtonEventArgs* args)
{
	LDraw::PointD point = args->GetPosition(this);//ScreenToClient(evt->get_ScreenX(), evt->get_ScreenY());

#if 0
	if (evt->m_nclicks > 0)
	{
		SetMarkStart(0);
		SetMarkEnd(m_wave->m_nsamples);
		Invalidate();
		return;
	}
#endif

#if 0
	if (point.Y < 20)
	{
#if WIN32
		hWait = MSWindows::CreateEventA(NULL, false, false, NULL);

		MSWindows::DWORD threadID;
		HANDLE hThread = MSWindows::CreateThread(NULL, 0, ThreadFunc, this, 0, &threadID);
	//	SetThreadPriority(hThread, THREAD_PRIORITY_ABOVE_NORMAL);
		MSWindows::WaitForSingleObject(hWait, INFINITE);
#if 0
		m_nTimerID = SetTimer(1, 20);
#endif
#endif
		return;
	}
#endif

	/*
	LMedia::WaveOutput* wo = new LMedia::WaveOutput;
	wo->Init();
//	wo->SetWindow(NULL);
	wo->SetFormat(m_wfx);

	wo->Receive(m_data, m_nsamples*m_wfx->nBlockAlign);

	return;
*/

	//LDraw::PointD point(ppoint.get_X(), ppoint->get_Y());

	/*
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	long scrollposX; m_horz->get_pos(&scrollposX);

	CPoint pt = point;
	pt.x += scrollposX;
	*/

	if (!m_dragging)
	{
		m_dragging = 1;
		CaptureMouse();
		
	//	double inc = (double)pDoc->GetAbsTotalFrames()/WaveXPels();
	//	double inc = (double)m_pStream->m_pDocument->m_duration/m_totalXPels;

		LONGLONG	position = (LONGLONG)point.X;//pt.x*inc;
		
		LONGLONG startx = GetMarkStart();///inc;
		LONGLONG endx = GetMarkEnd();///inc;
		
		if (fabs(point.X-startx) < 4)	// Drag start marker
		{
			m_startSample = GetMarkEnd();
		}
		else if (fabs(point.X-endx) < 4)	// Drag end marker
		{
			m_startSample = GetMarkStart();
		}
		else	// Set new selection
		{
			m_startSample = position;
		}

		OnMouseMove(args);
	}
}

/*
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
*/

void WaveformElement::OnMouseUp(MouseButtonEventArgs* args)
{
	if (m_dragging)
	{
		m_dragging = 0;
		ReleaseMouseCapture();
	}
}

void WaveformElement::OnMouseMove(MouseEventArgs* args)
{
	LDraw::PointD point = args->GetPosition(this);//ScreenToClient(evt->get_ScreenX(), evt->get_ScreenY());
	//LDraw::PointD point(ppoint->get_X(), ppoint->get_Y());

//	long scrollposX; m_horz->get_pos(&scrollposX);

//	CPoint pt = point;
//	pt.x += scrollposX;

	if (m_dragging)
	{
#if 0
		CClientDC dc(m_hWnd);

		dc.OffsetViewportOrg(-scrollposX, 0);

		DrawWaveSelection(dc.m_hDC);
#endif

	//	double inc = (double)m_pStream->m_pDocument->m_duration/m_totalXPels;

		LONGLONG position = point.X;//*inc;

		LONGLONG markStart;
		LONGLONG markEnd;

		if (position > m_startSample)
		{
			markStart = m_startSample;
			markEnd = position;
		}
		else
		{
			markStart = position;
			markEnd = m_startSample;
		}

		if (markStart < 0) markStart = 0;
//		if (pDoc->m_markEnd > pDoc->GetComp()->m_pVideo->GetSamples()-1)
//			pDoc->m_markEnd = pDoc->GetComp()->m_pVideo->GetSamples()-1;
		if (markEnd > m_wave->m_nsamples) markEnd = m_wave->m_nsamples;

		SetMarkStart(markStart);
		SetMarkEnd(markEnd);
#if 0
		DrawWaveSelection(dc.m_hDC);

		m_pStream->m_pDocument->Seek(position);
#endif
		Invalidate();
	}
}

void WaveformElement::Stop()
{
	m_bStop = true;
	wo->Stop();
	delete wo;
	wo = NULL;
}

}
