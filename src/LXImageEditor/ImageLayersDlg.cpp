// ImageLayersDlg.cpp : Implementation of CImageLayersDlg
#include "stdafx.h"
#include "LXImageEditor.h"
#include "Image2.h"

#include "ImageLayersDlg.h"

/*
#include "WebEditorApp.h"	// TODO remove
#include "WebEditorFrame.h"	// TODO remove
extern CWebEditorApp* gApp;	// TODO remove
*/

#include "ImageLayerBitmap.h"	// TODO remove

#include "ImageView.h"	// TODO remove

/////////////////////////////////////////////////////////////////////////////
// CImageLayersDlg

LRESULT CImageLayersDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
	uiActiveManager->AddEventHandler(this);

	return 0;
}

LRESULT CImageLayersDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
	uiActiveManager->RemoveEventHandler(this);

	return 0;
}

LRESULT CImageLayersDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect client;
	GetClientRect(&client);

	int m_itemHeight = 24;

	if (m_view)
	{
		CComPtr<IImageDocument> document;
		m_view->GetDocument(&document);

		int index = point.y / 24;

		CComPtr<IImageLayerGroup> layerGroup;
		document->GetImageLayerGroup(&layerGroup);

		long nsublayers;
		layerGroup->GetSubLayersCount(&nsublayers);

		if (index >= 0 && index < nsublayers)
		{
			CComPtr<IImageLayerUnknown> layer;
			layerGroup->GetSubLayer(index, &layer);

			//static_cast<CImageView*>(m_view.p)->m_pActiveLayer = layer;

			int y = index*m_itemHeight;

			CRect itemrect(0, y, client.right, y+m_itemHeight);

			CRect trect = itemrect;

			Gdiplus::Bitmap* pBitmap = static_cast<CImageLayerBitmap*>(layer.p)->m_pBitmap;
			if (pBitmap)
			{
				trect.left += 24;

				if (point.x < trect.left)
				{
					static_cast<CImageView*>(m_view.p)->m_pActiveBitmap = pBitmap;
					static_cast<CImageView*>(m_view.p)->m_pActiveGroup = static_cast<CImageLayerBitmap*>(layer.p)->m_group;
					return 0;
				}
			}

			Gdiplus::Bitmap* pBitmapMask = static_cast<CImageLayerBitmap*>(layer.p)->m_pBitmapMask;
			if (pBitmapMask)
			{
				trect.left += 24;

				if (point.x < trect.left)
				{
					static_cast<CImageView*>(m_view.p)->m_pActiveBitmap = pBitmapMask;
					static_cast<CImageView*>(m_view.p)->m_pActiveGroup = static_cast<CImageLayerBitmap*>(layer.p)->m_groupMask;
					return 0;
				}
			}
		}
	}

	return 0;
}

LRESULT CImageLayersDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	CRect client;
	GetClientRect(&client);

	int m_itemHeight = 24;

	if (m_view)
	{
		CComPtr<IImageDocument> document;
		m_view->GetDocument(&document);

		dc.SetBkMode(TRANSPARENT);

		CComPtr<IImageLayerGroup> layerGroup;
		document->GetImageLayerGroup(&layerGroup);

		long nsublayers;
		layerGroup->GetSubLayersCount(&nsublayers);

		int y = 0;

		for (int i = 0; i < nsublayers; i++)
		{
			CComPtr<IImageLayerUnknown> layer;
			layerGroup->GetSubLayer(i, &layer);

			CComBSTR name;
			layer->GetName(&name);

			CRect itemrect(0, y, client.right, y+m_itemHeight);

			CRect trect = itemrect;

			Gdiplus::Bitmap* pBitmap = static_cast<CImageLayerBitmap*>(layer.p)->m_pBitmap;
			if (pBitmap)
			{
				Gdiplus::Graphics graphics(dc.m_hDC);

				graphics.DrawImage(pBitmap,
					Gdiplus::Rect(trect.left, itemrect.top, 24, 24),
					0, 0, pBitmap->GetWidth(), pBitmap->GetHeight(),
					Gdiplus::UnitPixel);

				trect.left += 24;
			}

			Gdiplus::Bitmap* pBitmapMask = static_cast<CImageLayerBitmap*>(layer.p)->m_pBitmapMask;
			if (pBitmapMask)
			{
				Gdiplus::Graphics graphics(dc.m_hDC);

				graphics.DrawImage(pBitmapMask,
					Gdiplus::Rect(trect.left, itemrect.top, 24, 24),
					0, 0, pBitmapMask->GetWidth(), pBitmapMask->GetHeight(),
					Gdiplus::UnitPixel);

				trect.left += 24;
			}

			dc.DrawText(_bstr_t(name), name.Length(), &trect, DT_SINGLELINE | DT_VCENTER);

			y += m_itemHeight;
		}
	}

	return 0;
}

// IUIEventHandler
STDMETHODIMP CImageLayersDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IImageView> view = object;
	if (view)
	{
		m_view = view;

		Invalidate();

		*cookie = 1;
	}
	return S_OK;
}

STDMETHODIMP CImageLayersDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	m_view = NULL;

	return S_OK;
}
