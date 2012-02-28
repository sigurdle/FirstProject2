// NavigatorDlg.cpp : Implementation of CNavigatorDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "NavigatorDlg.h"

#include "PDDocumentView.h"

/*
#include "PageDesignerApp.h"
#include "PageDesignerFrame.h"

extern CPageDesignerApp* gApp;
*/

/////////////////////////////////////////////////////////////////////////////
// CNavigatorDlg

int CNavigatorDlg::FinalConstruct()
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->FindMenu(IDR_NAVIGATOR, &m_menu);

	return 0;
}

LRESULT CNavigatorDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIManager> uiManager = gApp->m_frame;
//	IDispEventImpl<1, CNavigatorDlg, &DIID__IUIManagerEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(uiManager);

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	return 0;
}

LRESULT CNavigatorDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

//	CComQIPtr<IUIManager> uiManager = gApp->m_frame;
//	IDispEventImpl<1, CNavigatorDlg, &DIID__IUIManagerEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(uiManager);

	return 0;
}

LRESULT CNavigatorDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);

	CRect client;
	GetClientRect(&client);

	if (m_view)
	{
		CComPtr<IPDDocument> document = m_view->m_document;

		if (m_view->m_activeSpread)
		{
			Gdiplus::Graphics graphics(hDC);

			double pageWidth;
			double pageHeight;
			document->get_pageWidth(&pageWidth);
			document->get_pageHeight(&pageHeight);

			int fullwidth = (pageWidth*m_maxpages)+200;
			int fullheight = (pageHeight)+100;

			CRect rect;
			rect.left = 3 + (client.Width()-6-m_size.cx)/2;
			rect.top = 3 + (client.Height()-6-m_size.cy)/2;
			rect.right = rect.left + m_size.cx;
			rect.bottom = rect.top + m_size.cy;

			CRect brect = rect;

			FillSolidRect(hDC, &rect, RGB(255, 255, 255));

			brect.InflateRect(1, 1);
			Draw3DRect(hDC, &brect, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DLIGHT));

			brect.InflateRect(1, 1);
			Draw3DRect(hDC, &brect, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));

			{
				int x = (100 + ((m_maxspine-m_spine)*pageWidth));// * m_magnify;
				int y = (100);// * m_magnify;

				CComQIPtr<IPDRenderer> renderer;
				renderer.CoCreateInstance(CLSID_PDRenderer);

				Gdiplus::GraphicsState state = graphics.Save();

				graphics.TranslateTransform(rect.left+x*m_magnify, rect.top+y*m_magnify);

					renderer->put_targetHDC((HDC)&graphics);
					renderer->put_magnify(m_magnify);

					renderer->RenderSpread(m_view->m_activeSpread, -(x), 0, 0, 0);

					graphics.Restore(state);
			//graphics.TranslateTransform(-(rect.left+x), -(rect.top+y));
			}

		// Draw visible viewRect
			{
				int x = 100*m_magnify;
				int y = 100*m_magnify;
				graphics.TranslateTransform(rect.left+x, rect.top+y);

				CRect viewBox;
				m_view->getViewBox(&viewBox);

				CRect viewRect = viewBox;
				viewRect.left *= m_magnify;
				viewRect.top *= m_magnify;
				viewRect.right *= m_magnify;
				viewRect.bottom *= m_magnify;

				viewRect.InflateRect(1, 1);

				Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0), 2);

				graphics.DrawRectangle(&pen, viewRect.left, viewRect.top, viewRect.Width(), viewRect.Height());
			}

		//	RestoreDC(hDC, state);
		}
	}

	EndPaint(&ps);
	return 0;
}

LRESULT CNavigatorDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL);

	return 0;
}

void CNavigatorDlg::OnSize()
{
	CRect client;
	GetClientRect(&client);

	client.right -= 6;
	client.bottom -= 6;

	m_size.cx = 0;
	m_size.cy = 0;

	if (m_view)
	{
		CComPtr<IPDDocument> document = m_view->m_document;

		m_maxpages = 0;
		m_maxspine = 0;
		{
			CComPtr<IObjectMap> spreads;
			document->get_spreads(&spreads);

			long nspreads;
			spreads->get_length(&nspreads);

			for (long nspread = 0; nspread < nspreads; nspread++)
			{
				CComPtr<IPDSpread> spread;
				spreads->item(nspread, (IUnknown**)&spread);

				CComPtr<IObjectMap> pages;
				spread->get_pages(&pages);

				long npages;
				pages->get_length(&npages);
				m_maxpages = max(m_maxpages, npages);

				long spine;
				spread->get_spine(&spine);
				m_maxspine = max(m_maxspine, spine);
			}
		}

		if (m_view->m_activeSpread)
		{
			m_view->m_activeSpread->get_spine(&m_spine);

			double pageWidth;
			double pageHeight;
			document->get_pageWidth(&pageWidth);
			document->get_pageHeight(&pageHeight);

			int fullwidth = (pageWidth*m_maxpages)+200;
			int fullheight = (pageHeight)+200;

			m_size.cx = client.Width();
			m_size.cy = (m_size.cx*fullheight)/fullwidth;

			if (m_size.cy > client.Height())
			{
				m_size.cy = client.Height();
				m_size.cx = (m_size.cy*fullwidth)/fullheight;
			}

			m_magnify = (double)m_size.cx/fullwidth;
		}
	}
}

LRESULT CNavigatorDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect client;
	GetClientRect(&client);

	if (!m_dragging)
	{
		if (m_view)
		{
			CComPtr<IPDDocument> document = m_view->m_document;
			double pageWidth;
			double pageHeight;
			document->get_pageWidth(&pageWidth);
			document->get_pageHeight(&pageHeight);

		//	int left = (100 + ((m_maxspine-m_spine)*pageWidth))*m_magnify + 3 + (client.Width()-6-m_size.cx)/2;
			int left = (100)*m_magnify + 3 + (client.Width()-6-m_size.cx)/2;
			int top = 100*m_magnify + 3 + (client.Height()-6-m_size.cy)/2;

			//int left = (100 + ((m_maxspine-spine)*pageWidth))*m_magnify + 3 + (client.Width()-6-m_size.cx)/2;
			//int top = 50*m_magnify + 3 + (client.Height()-6-m_size.cy)/2;

			POINT cpt;
			cpt.x = point.x-left;
			cpt.y = point.y-top;

			CRect viewBox;
			m_view->getViewBox(&viewBox);

			CRect viewRect = viewBox;

			viewRect.left *= m_magnify;
			viewRect.top *= m_magnify;
			viewRect.right *= m_magnify;
			viewRect.bottom *= m_magnify;

			if (PtInRect(&viewRect, cpt))
			{
				m_offset.x = (cpt.x/m_magnify) - viewBox.left;
				m_offset.y = (cpt.y/m_magnify) - viewBox.top;
			}
			else
			{
				m_offset.x = viewBox.Width()/2;
				m_offset.y = viewBox.Height()/2;

				double currentScale = m_view->m_magnify;

				int cx = ((cpt.x/m_magnify) - m_offset.x) * currentScale;
				int cy = ((cpt.y/m_magnify) - m_offset.y) * currentScale;

				m_view->setScrollPosXY(cx, cy);
				Invalidate();	// TODO remove
			}

			SetCursor(LoadCursor(_Module.m_hInst, MAKEINTRESOURCE(IDC_HAND2)));

			m_dragging = TRUE;
			SetCapture();
		}
	}

	return 0;
}

LRESULT CNavigatorDlg::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = FALSE;
	}

	return 0;
}

LRESULT CNavigatorDlg::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect client;
	GetClientRect(&client);

	if (m_dragging)
	{
		ATLASSERT(m_view);

		CComPtr<IPDDocument> document = m_view->m_document;
		double pageWidth;
		double pageHeight;
		document->get_pageWidth(&pageWidth);
		document->get_pageHeight(&pageHeight);
		
//		int left = (100 + ((m_maxspine-m_spine)*pageWidth))*m_magnify + 3 + (client.Width()-6-m_size.cx)/2;
		int left = (100)*m_magnify + 3 + (client.Width()-6-m_size.cx)/2;
		int top = 100*m_magnify + 3 + (client.Height()-6-m_size.cy)/2;
		
		POINT cpt;
		cpt.x = point.x-left;
		cpt.y = point.y-top;
		
		double currentScale = m_view->m_magnify;
		
		int cx = ((cpt.x/m_magnify) - m_offset.x) * currentScale;
		int cy = ((cpt.y/m_magnify) - m_offset.y) * currentScale;
		
		m_view->setScrollPosXY(cx, cy);
		Invalidate();	// TODO remove
	}

	return 0;
}

LRESULT CNavigatorDlg::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = (HWND) wParam;       // handle to window with cursor 
	UINT nHittest = LOWORD(lParam);  // hit-test code 
	UINT wMouseMsg = HIWORD(lParam); // mouse-message identifier 
 
	if (nHittest == HTCLIENT)
	{
		CRect client;
		GetClientRect(&client);

		if (m_view)
		{
			CComPtr<IPDDocument> document = m_view->m_document;
			double pageWidth;
			double pageHeight;
			document->get_pageWidth(&pageWidth);
			document->get_pageHeight(&pageHeight);

	//		int left = (100 + ((m_maxspine-m_spine)*pageWidth))*m_magnify + 3 + (client.Width()-6-m_size.cx)/2;
			int left = (100)*m_magnify + 3 + (client.Width()-6-m_size.cx)/2;
			int top = 100*m_magnify + 3 + (client.Height()-6-m_size.cy)/2;

			POINT point;
			GetCursorPos(&point);
			ScreenToClient(&point);

			POINT cpt;
			cpt.x = point.x-left;
			cpt.y = point.y-top;

			CRect viewBox;
			m_view->getViewBox(&viewBox);

			CRect viewRect = viewBox;

			viewRect.left *= m_magnify;
			viewRect.top *= m_magnify;
			viewRect.right *= m_magnify;
			viewRect.bottom *= m_magnify;

			if (PtInRect(&viewRect, cpt))
			{
				SetCursor(LoadCursor(_Module.m_hInst, MAKEINTRESOURCE(IDC_HAND0)));
				return TRUE;
			}
			else
			{
				SetCursor(LoadCursor(_Module.m_hInst, MAKEINTRESOURCE(IDC_HAND1)));
				return TRUE;
			}
		}
	}

	return DefWindowProc(uMsg, wParam, lParam);//HANDLE_BASE<IUIDlg>(m_puiwnd, uMsg, wParam, lParam);
}

STDMETHODIMP CNavigatorDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IPDDocumentView> view = object;
	if (view)
	{
		m_view = static_cast<CComObject<CPDDocumentView>*>(view.p);
		m_view->AddRef();
		//IDispEventImpl<3, CLayersDlg, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventAdvise(m_view->m_document);
		OnSize();
		Invalidate();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CNavigatorDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ATLASSERT(cookie == 1);

	//IDispEventImpl<3, CLayersDlg, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventUnadvise(m_view->m_document);
	m_view->Release();
	m_view = NULL;

	Invalidate();
	OnSize();

	return S_OK;
}

BEGIN_CMD_MAP(CNavigatorDlg)
	CMD_HANDLER(ID_NAVIGATOR_VIEWALLSPREADS, OnNavigatorViewAllSpreads)
END_CMD_MAP()

LRESULT CNavigatorDlg::OnNavigatorViewAllSpreads(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}
