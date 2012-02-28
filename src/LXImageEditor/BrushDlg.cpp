// BrushDlg.cpp : Implementation of CBrushDlg
#include "stdafx.h"
#include "LXImageEditor.h"
#include "Image2.h"

#include "BrushDlg.h"

//#include "WebEditorApp.h"	// TODO remove
//#include "WebEditorFrame.h"	// TODO remove
//extern CWebEditorApp* gApp;	// TODO remove
#include "ImageLayerBitmap.h"	// TODO remove
#include "ImageApp.h"

/////////////////////////////////////////////////////////////////////////////
// CBrushDlg

int CBrushDlg::FinalConstruct()
{
	m_vert.CoCreateInstance(CLSID_UIScrollBar);
	m_vert->put_direction(1);

	return 0;
}

void CBrushDlg::FinalRelease()
{
}

LRESULT CBrushDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

	IDispEventImpl<1, CBrushDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	return 0;
}

LRESULT CBrushDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CBrushDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	return 0;
}

LRESULT CBrushDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	if (dc.IntersectClipRect(&m_areaRect) > NULLREGION)
	{
		long scrollposY; m_vert->get_pos(&scrollposY);

		dc.SetViewportOrg(m_areaRect.left, m_areaRect.top-scrollposY);

		int y = 0;

#if 0
		for (int i = 0; i < g_pImageApp->m_brushes.GetSize(); i++)
		{
			CImageBrush* pBrush = g_pImageApp->m_brushes[i];

			CRect itemrect(0, y, m_areaRect.Width(), y+32);

			dc.Rectangle(&itemrect);

			Gdiplus::Graphics graphics(dc);

			{
				{
					Gdiplus::Bitmap* pBitmap = pBrush->m_pBrushTip->GetBitmap();

					Gdiplus::Bitmap* m_pBrushBitmap = new Gdiplus::Bitmap(pBrush->m_brushSize, pBrush->m_brushSize, PixelFormat32bppARGB);

					{
						Gdiplus::Graphics graphics(m_pBrushBitmap);
						graphics.DrawImage(
							pBitmap,
							Gdiplus::RectF(0, 0, pBrush->m_brushSize, pBrush->m_brushSize),
							(float)0, (float)0, (float)pBitmap->GetWidth(), (float)pBitmap->GetHeight(),
							Gdiplus::UnitPixel);
					}

					graphics.DrawImage(m_pBrushBitmap,
						Gdiplus::Rect(0, y, pBrush->m_brushSize, pBrush->m_brushSize),
						(float)0, (float)0, (float)m_pBrushBitmap->GetWidth(), (float)m_pBrushBitmap->GetHeight(),
						Gdiplus::UnitPixel);

					delete m_pBrushBitmap;
				}

				{
					Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(180, 32, PixelFormat32bppARGB);
					if (pBitmap)
					{
						{
							Gdiplus::Graphics graphics(pBitmap);
							graphics.Clear(Gdiplus::Color(0, 0, 0, 0));	// white transparent
						}

						CStrokeObject* pStroke = new CStrokeObject;
						if (pStroke)
						{
							pStroke->m_pBrushTip = pBrush->m_pBrushTip;
							pStroke->m_pMethod = pBrush->m_pMethod;
							pStroke->m_brushSize = pBrush->m_brushSize;
							pStroke->m_color[0] = 0;
							pStroke->m_color[1] = 0;
							pStroke->m_color[2] = 0;

							for (int i = 20; i < 180-20; i += 6)
							{
								pStroke->m_points.Add(PointD(i, 16));
							}

							pStroke->m_clipRect = CRect(0, 0, 180-1, 32-1);

							pStroke->BeginBrushStroke(1, 1);

							pStroke->Render(pBitmap, 1, 1);

							pStroke->EndBrushStroke();

							delete pStroke;
						}

						graphics.DrawImage(pBitmap,
							Gdiplus::Rect(32, y, 180, 32),
							(float)0, (float)0, (float)180, (float)32,
							Gdiplus::UnitPixel);
					}
				}
			}

			y += 32;
		}
#endif
	}

	return 0;
}

LRESULT CBrushDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposY; m_vert->get_pos(&scrollposY);

	point.y += scrollposY;

	int index = point.y / 32;

#if 0
	if (index >= 0 && index < g_pImageApp->m_brushes.GetSize())
	{
		CImageBrush* pBrush = g_pImageApp->m_brushes[index];

		g_pImageApp->m_pActiveBrushTip = pBrush->m_pBrushTip;
		g_pImageApp->m_brushSize = pBrush->m_brushSize;
		g_pImageApp->m_pActivePaintMethod = pBrush->m_pMethod;
	}
#endif

	return 0;
}

LRESULT CBrushDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_areaRect = client;
	m_areaRect.right -= 16;

	m_axvert.MoveWindow(m_areaRect.right, m_areaRect.top, 16, m_areaRect.Height());

#if 0
	m_vert->SetInfo(0, g_pImageApp->m_brushes.GetSize()*32, m_areaRect.Height());
#endif

	return 0;
}

void __stdcall CBrushDlg::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);
	m_vert->put_pos(pos);

	ScrollWindow(0, oldPos-pos, &m_areaRect, &m_areaRect);
}

/*
LRESULT CBrushDlg::OnBrushSize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int value = GetDlgItemInt(wID);

	gApp->m_brushSize = value;

	return 0;
}
*/

// IUIEventHandler
STDMETHODIMP CBrushDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	return S_OK;
}

STDMETHODIMP CBrushDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	return S_OK;
}
