// MediaClipView.cpp : Implementation of CMediaClipView
#include "stdafx.h"
#include "LXMedia.h"
#include "LXMedia2.h"

#include "MediaClipView.h"

#include "EMediaClipDocument.h"

//#include "LXFrameworkApp.h"

#if 0
#include <qedit.h>

/*
//#include <Streams.h>
//#include <Mtype.h>

  If you prefer not to link to the base class library, you can use the
  following code directly:
*/

void /*My*/FreeMediaType(AM_MEDIA_TYPE& mt)
{
	if (mt.cbFormat != 0)
	{
		CoTaskMemFree((PVOID)mt.pbFormat);
		mt.cbFormat = 0;
		mt.pbFormat = NULL;
	}
	if (mt.pUnk != NULL)
	{
		// Unecessary because pUnk should not be used, but safest.
		mt.pUnk->Release();
		mt.pUnk = NULL;
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CMediaClipView

LRESULT CMediaClipView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CMediaClipView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);
	IDispEventImpl<2, CMediaClipView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	return 0;
}

LRESULT CMediaClipView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CMediaClipView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
	IDispEventImpl<2, CMediaClipView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	return 0;
}

LRESULT CMediaClipView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);
	{
		Gdiplus::Graphics graphics(dc.m_hDC);

		Gdiplus::Bitmap* pBitmap;
		GetBitmap(&pBitmap);

		if (pBitmap)
		{
			CRect client;
			GetClientRect(&client);

			graphics.DrawImage(pBitmap, m_videoRect,
				0, 0, pBitmap->GetWidth(), pBitmap->GetHeight(),
				Gdiplus::UnitPixel);
		}
	}

	dc.FillSolidRect(&m_bottomRect, GetSysColor(COLOR_BTNFACE));

	dc.FillSolidRect(&m_sliderRect, RGB(220, 220, 220));

	{
		/*
		CComQIPtr<IMediaSeeking> mediaSeeking = m_dsGraph;

		LONGLONG llpos;
		mediaSeeking->GetCurrentPosition(&llpos);

		double seconds = (double)llpos / 10000000; //seconds;
		*/

		double secondWidth = m_sliderRect.Width() / m_pStream->m_pDocument->m_duration;

		int x = m_sliderRect.left + (m_pStream->m_pDocument->m_currentTime * secondWidth);
		dc.MoveTo(x, m_sliderRect.top);
		dc.LineTo(x, m_sliderRect.bottom);

		double clipBegin = m_pStream->m_pDocument->GetClipBegin();
		double clipEnd = m_pStream->m_pDocument->GetClipEnd();

		x = m_sliderRect.left + (clipBegin * secondWidth);
		dc.DrawText("{", 1, CRect(x-5, m_sliderRect.top, x+5, m_sliderRect.bottom), DT_CENTER | DT_SINGLELINE);

		x = m_sliderRect.left + (clipEnd * secondWidth);
		dc.DrawText("}", 1, CRect(x-5, m_sliderRect.top, x+5, m_sliderRect.bottom), DT_CENTER | DT_SINGLELINE);
	}

	return 0;
}

LRESULT CMediaClipView::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return TRUE;
}

LRESULT CMediaClipView::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (!m_dragging)
	{
		double secondWidth = m_sliderRect.Width() / m_pStream->m_pDocument->m_duration;

		CPoint pt = point;
		pt.x -= m_sliderRect.left;

		double seekTo = pt.x / secondWidth;
		if (seekTo < 0) seekTo = 0;
		else if (seekTo > m_pStream->m_pDocument->m_duration) seekTo = m_pStream->m_pDocument->m_duration;	// ??

		double clipBegin = m_pStream->m_pDocument->GetClipBegin();
		double clipEnd = m_pStream->m_pDocument->GetClipEnd();

		if (abs(pt.x-(m_pStream->m_pDocument->m_currentTime*secondWidth)) < 4)
		{
			m_dragging = 1;
		}
		else if (abs(pt.x-(clipBegin*secondWidth)) < 4)
		{
			m_dragging = 2;
		}
		else if (abs(pt.x-(clipEnd*secondWidth)) < 4)
		{
			m_dragging = 3;
		}
		else
		{
			m_dragging = 1;
		}

		SetCapture();

		OnMouseMove(point, wParam);
	}

	return 0;
}

LRESULT CMediaClipView::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		m_dragging = 0;
		ReleaseCapture();
	}
	return 0;
}

void CMediaClipView::OnMouseMove(CPoint point, UINT nFlags)
{
	if (m_dragging)
	{
		double secondWidth = m_sliderRect.Width() / m_pStream->m_pDocument->m_duration;

		double seekTo = (point.x-m_sliderRect.left) / secondWidth;
		if (seekTo < 0) seekTo = 0;
		else if (seekTo > m_pStream->m_pDocument->m_duration) seekTo = m_pStream->m_pDocument->m_duration;	// ??

		if (m_dragging == 1)
		{
			m_pStream->m_pDocument->Seek(seekTo);
		}
		else
		{
			WCHAR buf[64];
			swprintf(buf, L"%gs", seekTo);

			if (m_dragging == 2)
			{
				m_pStream->m_pDocument->m_mediaElement->setAttribute(L"clipBegin", buf);
			}
			else
			{
				m_pStream->m_pDocument->m_mediaElement->setAttribute(L"clipEnd", buf);
			}

			InvalidateRect(&m_bottomRect);
		}
	}
}

LRESULT CMediaClipView::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnMouseMove(point, wParam);

	return 0;
}

LRESULT CMediaClipView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	//if (m_pSrcBitmap)	// TODO
	{
		m_videoRect = Gdiplus::Rect(0, 0, client.right, client.bottom-32);
	}

	m_bottomRect = CRect(0, client.bottom-32, client.right, client.bottom);
	m_sliderRect = m_bottomRect;
	m_sliderRect.left += 8;
	m_sliderRect.right -= 8;

	return 0;
}

HRESULT CMediaClipView::GetBitmap(Gdiplus::Bitmap** pVal)
{
	HRESULT hr = S_OK;

	if (m_pStream->m_pSample)
		*pVal = m_pStream->m_pSample->m_pBitmap;
	else
		*pVal = NULL;

	return hr;
}

BEGIN_CMD_MAP(CMediaClipView)
	CMD_HANDLER(ID_EDIT_EDITFRAME, OnEditFrame)
END_CMD_MAP()

// ICommandTarget
STDMETHODIMP CMediaClipView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
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

#if 0
#include "Image2.h"
#include "ImageDocument.h"
#include "ImageLayerBitmap.h"
#include "ImageLayerGroup.h"
#endif

LRESULT CMediaClipView::OnEditFrame(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	CComObject<CImageDocument>* pImageDocument;
	CComObject<CImageDocument>::CreateInstance(&pImageDocument);
	pImageDocument->AddRef();

	{
		CComObject<CImageLayerBitmap>* pLayer;
		CComObject<CImageLayerBitmap>::CreateInstance(&pLayer);
		pLayer->AddRef();

		pLayer->m_pBitmap = m_pDocument->m_pSample->m_pBitmap;

		pLayer->m_pInitialBitmap = pLayer->m_pBitmap->Clone(Gdiplus::Rect(0, 0, pLayer->m_pBitmap->GetWidth(), pLayer->m_pBitmap->GetHeight()), PixelFormat32bppARGB);
		{
			Gdiplus::BitmapData bitmapData;
			pLayer->m_pBitmap->LockBits(
				&Gdiplus::Rect(0, 0, pLayer->m_pBitmap->GetWidth(), pLayer->m_pBitmap->GetHeight()),
				Gdiplus::ImageLockModeRead,
				PixelFormat32bppARGB, &bitmapData);

			GetAlphaBounds(&bitmapData, &pLayer->m_alphaBounds);

			pLayer->m_pBitmap->UnlockBits(&bitmapData);
		}

		pLayer->m_name = L"Layer 0";

		pLayer->m_width = pLayer->m_pBitmap->GetWidth();
		pLayer->m_height = pLayer->m_pBitmap->GetHeight();

		pImageDocument->m_width = pLayer->m_pBitmap->GetWidth();
		pImageDocument->m_height = pLayer->m_pBitmap->GetHeight();

		/*
		Gdiplus::BitmapData data;
		if (pBitmap->LockBits(
			&Gdiplus::Rect(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight()),
			Gdiplus::ImageLockModeRead,
			PixelFormat32bppPARGB, &data) != 0)
		{
			ATLASSERT(0);
			return -1;
		}

		pBitmap->UnlockBits(&data);
		*/

		pLayer->m_parentGroup = pImageDocument->m_imageLayerGroup;
		pImageDocument->m_imageLayerGroup->m_subLayers.Add(pLayer);
	}

	pImageDocument->ShowViews(NULL);
#endif

	return 0;
}
