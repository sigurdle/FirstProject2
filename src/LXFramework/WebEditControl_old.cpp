// WebEditControl.cpp : Implementation of CWebEditControl
#include "stdafx.h"
#include "WebEditor.h"
#include "WebEditor2.h"
#include "WebEditControl.h"

/////////////////////////////////////////////////////////////////////////////
// CWebEditControl

#include "ESvgDocument.h"
//#include "Element.h"

#include "WEUndoMoveObjects.h"

#include "WebEditorApp.h"
#include "WebEditorFrame.h"

extern CWebEditorApp* gApp;

CComQIPtr<ILSVGPathSegList> GetPathSegList(CElementImpl* pElement);
void PutPathSegList(CElementImpl* pElement, CComQIPtr<ILSVGPathSegList> seglist);
BOOL GetPointOnSegList(ILSVGPathSegList* seglist, double mousex, double mousey, double tolerance, long* segindex, double* pt);

/////////////////////////////////////////////////////////////////////////////
// CWebEditControl

CWebEditControl::CWebEditControl()
{
	m_bWindowOnly = TRUE;

	m_dragging = 0;

	m_bShowRulers = FALSE;

	m_offset.x = m_offset.y = 0;

	m_pActivePathElement = NULL;

//	m_horz = NULL;
//	m_vert = NULL;
//	m_sizeGrip = NULL;

	m_magnify = 1.0;

	m_pivotPt.x = 0;
	m_pivotPt.y = 0;

	m_effectRadius = 100;

/*
	m_lpBmi = NULL;
	m_hBitmap = NULL;
	m_bmBits = NULL;
*/
	m_cursorPos = 0;
	m_pTextElement = NULL;

	m_sourceText = NULL;
}

STDMETHODIMP CWebEditControl::get_ESvgDocument(IWebXMLDocument **pVal)
{
	*pVal = m_pDocument;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CWebEditControl::put_ESvgDocument(IWebXMLDocument *newVal)
{
	m_pDocument = newVal;
	return S_OK;
}

STDMETHODIMP CWebEditControl::DrawOver(HDC hDC, tagRECT rect)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	HDC clipdc = hDC;

	if (TRUE/*!m_pDocument->m_bPlaying*/)
	{
		POINT oldOrg;
		OffsetViewportOrgEx(clipdc, /*m_offset.x - scrollposX*/0, /*m_offset.y - scrollposY*/0, &oldOrg);

		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 200));
		HPEN hOldPen = (HPEN)SelectObject(clipdc, hPen);

		CElementImpl* pActiveElement = pDocument->GetActiveElement();

		if (pActiveElement)
		{

			CElementImpl* pTargetElement = NULL;
			if (pActiveElement) pTargetElement = pActiveElement->GetTargetElement();

			if (gApp->m_svgActiveTool == ID_SVGTOOL_SELECT ||
				gApp->m_svgActiveTool == TOOL_SKEW)
			{
				pTargetElement->DrawBBox(clipdc);
			}

			if (gApp->m_svgActiveTool == TOOL_ROTATE ||
				gApp->m_svgActiveTool == TOOL_SCALE ||
				gApp->m_svgActiveTool == TOOL_SKEW)
			{
				float x = m_pivotPt.x;
				float y = m_pivotPt.y;

				HBRUSH hOldBrush = (HBRUSH)SelectObject(clipdc, GetStockObject(NULL_BRUSH));
				Ellipse(clipdc, x-4, y-4, x+5, y+5);
				SelectObject(clipdc, hOldBrush);
			}

			if (gApp->m_svgActiveTool == TOOL_TWIRL)
			{
				float x = m_pivotPt.x;
				float y = m_pivotPt.y;

				HBRUSH hOldBrush = (HBRUSH)SelectObject(clipdc, GetStockObject(NULL_BRUSH));
				Ellipse(clipdc, x-4, y-4, x+5, y+5);
				Ellipse(clipdc, x-m_effectRadius, y-m_effectRadius, x+m_effectRadius, y+m_effectRadius);
				SelectObject(clipdc, hOldBrush);
			}

			BSTR btagName;
			pActiveElement->m_domElement->get_nodeName(&btagName);
			_bstr_t tagName = _bstr_t(btagName);

#if 0
			if (!wcscmp(tagName, L"animateMotion"))
			{
				CAnimateMotionElement* pAnimateMotion = (CAnimateMotionElement*)pActiveElement;
				DrawMotionPath(clipdc, pAnimateMotion);
			}
#endif

			DrawTargetElementsPathCurves(clipdc);

			/*
			if ((gApp->m_activeTool == TOOL_DIRECT) ||
					(gApp->m_activeTool == TOOL_PEN) ||
					(gApp->m_activeTool == TOOL_PENFREE) ||
					(gApp->m_activeTool == TOOL_PENADD) ||
					(gApp->m_activeTool == TOOL_PENDELETE) ||
					(gApp->m_activeTool == TOOL_PENCORNER))
			{
				if (!wcscmp(pTargetElement->m_domElement->tagName, L"path"))
				{
					DrawPathCurve(pActiveElement, hDC, GetMagnifyFactor());
				}
			}
			*/

			if (gApp->m_svgActiveTool == ID_SVGTOOL_SELECT)
			{
				CDblRect bbox = pDocument->CalculateTargetsBBox();

				if (bbox.right > bbox.left > 0 && bbox.bottom > bbox.top)
				{
					int x1 = bbox.left*m_magnify;
					int y1 = bbox.top*m_magnify;
					int x2 = bbox.right*m_magnify;
					int y2 = bbox.bottom*m_magnify;

					HBRUSH hOldBrush = (HBRUSH)SelectObject(clipdc, GetStockObject(NULL_BRUSH));
					Rectangle(clipdc, x1, y1, x2, y2);
					SelectObject(clipdc, hOldBrush);
				}
			}
		}

		if (m_dragging)
		{
			if (gApp->m_svgActiveTool == ID_SVGTOOL_ELLIPSE)
			{
				HBRUSH hOldBrush = (HBRUSH)SelectObject(clipdc, GetStockObject(NULL_BRUSH));
				Ellipse(clipdc, m_startpt.x, m_startpt.y, m_oldpt.x, m_oldpt.y);
				SelectObject(clipdc, hOldBrush);
			}
		}

		SelectObject(clipdc, hOldPen);
		DeleteObject(hPen);

		SetViewportOrgEx(clipdc, oldOrg.x, oldOrg.y, NULL);
	}

	return S_OK;
}

#if 0
long CWebEditControl::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

#if 0
	CComQIPtr<ISVGDocument> svgdoc = pDocument->GetDOMDocument();
	if (svgdoc)
	{
		HWND hwnd; get_hwnd(&hwnd);
		ATLASSERT(IsWindow(hwnd));

		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hwnd, &ps);
		ATLASSERT(hDC);

		ATLASSERT(pDocument != NULL);

		CRect	clip;
		GetClipBox(hDC, &clip);

		CComQIPtr<ISVGSVGElement> svg;
		svgdoc->get_documentElement((IDOMElement**)&svg);
		if (svg)
		{
			long scrollposX; m_horz->get_pos(&scrollposX);
			long scrollposY; m_vert->get_pos(&scrollposY);

		/*
			if (m_bShowRulers)
			{
				DrawRulers(pDC);
			}
		*/

			HDC dc = CreateCompatibleDC(NULL);
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(dc, m_hBitmap);

			BOOL bRedraw;

			if (!m_dragging || TRUE/* || !gApp->m_bFastFB*/)
				bRedraw = TRUE;
			else
				bRedraw = FALSE;

			if (bRedraw)
			{
				FillSolidRect(dc, 0, 0, m_imageRect.Width(), m_imageRect.Height(), RGB(190, 190, 190));

				POINT oldOrg;
				SetViewportOrgEx(dc, m_offset.x - scrollposX, m_offset.y - scrollposY, &oldOrg);

				FillSolidRect(dc, 0, 0, pDocument->GetWidth()*m_magnify, pDocument->GetHeight()*m_magnify, RGB(255, 255, 255));
				svg->DrawToHDC((DWORD)dc, m_magnifyMatrix, m_magnify);

				SetViewportOrgEx(dc, oldOrg.x, oldOrg.y, NULL);
			}

			CRect irect;
			if (irect.IntersectRect(&m_imageRect, &clip))
			{
				clip = irect;

				int state = SaveDC(hDC);

				IntersectClipRect(hDC, m_imageRect.left, m_imageRect.top, m_imageRect.right, m_imageRect.bottom);

				POINT org;
				org.x = 0;
				org.y = 0;
				org.x += m_imageRect.left;
				org.y += m_imageRect.top;

				clip.OffsetRect(-org.x, -org.y);

				SetViewportOrgEx(hDC, org.x, org.y, NULL);

				BOOL bDither = FALSE;//((DispBitsPixel == 16) && theApp.m_dither16BitDisplay);

				int	left = clip.left;
				int	top = clip.top;
				int	right = clip.right;
				int	bottom = clip.bottom;
			
				int	width = clip.right-clip.left+1;
				int	height = clip.bottom-clip.top+1;

				HBITMAP	hBitmap = NULL;
				LPBYTE	bits = NULL;
				LPBITMAPV4HEADER	bmi = NULL;

				int rowBytes = ROWBYTES(width, 24);
				int sizeImage = rowBytes*height;

				if (bmi = (LPBITMAPV4HEADER)GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPV4HEADER)))
				{
					bmi->bV4Size = sizeof(BITMAPV4HEADER);
					bmi->bV4Width = width;
					bmi->bV4Height = height;
					bmi->bV4Planes = 1;
					bmi->bV4BitCount = 24;
					bmi->bV4SizeImage = sizeImage;
					
					hBitmap = ::CreateDIBSection(NULL, (BITMAPINFO*)bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
					
					if (hBitmap)
					{
						HDC clipdc = CreateCompatibleDC(NULL);
						HBITMAP pOldBitmap = (HBITMAP)SelectObject(clipdc, hBitmap);

						SetViewportOrgEx(clipdc, -clip.left, -clip.top, NULL);

						BitBlt(clipdc, left, top, clip.Width(), clip.Height(), dc, clip.left, clip.top, SRCCOPY);

					//	SetViewportOrgEx(clipdc, -clip.left, -clip.top, NULL);

						if (TRUE/*!m_pDocument->m_bPlaying*/)
						{
							POINT oldOrg;
							OffsetViewportOrgEx(clipdc, m_offset.x - scrollposX, m_offset.y - scrollposY, &oldOrg);

							HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 200));
							HPEN hOldPen = (HPEN)SelectObject(clipdc, hPen);

							CElement* pActiveElement = pDocument->GetActiveElement();

							if (pActiveElement)
							{

								CElement* pTargetElement = NULL;
								if (pActiveElement) pTargetElement = pActiveElement->GetTargetElement();

								if (pDocument->m_activeTool == TOOL_SELECT ||
									pDocument->m_activeTool == TOOL_SKEW)
								{
									pTargetElement->DrawBBox(clipdc);
								}

								if (pDocument->m_activeTool == TOOL_ROTATE ||
									pDocument->m_activeTool == TOOL_SCALE ||
									pDocument->m_activeTool == TOOL_SKEW)
								{
									float x = m_pivotPt.x;
									float y = m_pivotPt.y;

									HBRUSH hOldBrush = (HBRUSH)SelectObject(clipdc, GetStockObject(NULL_BRUSH));
									Ellipse(clipdc, x-4, y-4, x+5, y+5);
									SelectObject(clipdc, hOldBrush);
								}

								if (pDocument->m_activeTool == TOOL_TWIRL)
								{
									float x = m_pivotPt.x;
									float y = m_pivotPt.y;

									HBRUSH hOldBrush = (HBRUSH)SelectObject(clipdc, GetStockObject(NULL_BRUSH));
									Ellipse(clipdc, x-4, y-4, x+5, y+5);
									Ellipse(clipdc, x-m_effectRadius, y-m_effectRadius, x+m_effectRadius, y+m_effectRadius);
									SelectObject(clipdc, hOldBrush);
								}

								BSTR btagName;
								pActiveElement->m_domElement->get_nodeName(&btagName);
								_bstr_t tagName = _bstr_t(btagName);

		#if 0
								if (!wcscmp(tagName, L"animateMotion"))
								{
									CAnimateMotionElement* pAnimateMotion = (CAnimateMotionElement*)pActiveElement;
									DrawMotionPath(clipdc, pAnimateMotion);
								}
		#endif

								DrawTargetElementsPathCurves(clipdc);

								/*
								if ((gApp->m_activeTool == TOOL_DIRECT) ||
										(gApp->m_activeTool == TOOL_PEN) ||
										(gApp->m_activeTool == TOOL_PENFREE) ||
										(gApp->m_activeTool == TOOL_PENADD) ||
										(gApp->m_activeTool == TOOL_PENDELETE) ||
										(gApp->m_activeTool == TOOL_PENCORNER))
								{
									if (!wcscmp(pTargetElement->m_domElement->tagName, L"path"))
									{
										DrawPathCurve(pActiveElement, hDC, GetMagnifyFactor());
									}
								}
								*/

								if (pDocument->m_activeTool == TOOL_SELECT)
								{
									_tagSVGRect bbox = pDocument->CalculateTargetsBBox();

									if (bbox.width > 0 && bbox.height > 0)
									{
										int x1 = bbox.x*m_magnify;
										int y1 = bbox.y*m_magnify;
										int x2 = (bbox.x + bbox.width)*m_magnify;
										int y2 = (bbox.y + bbox.height)*m_magnify;

										HBRUSH hOldBrush = (HBRUSH)SelectObject(clipdc, GetStockObject(NULL_BRUSH));
										Rectangle(clipdc, x1, y1, x2, y2);
										SelectObject(clipdc, hOldBrush);
									}
								}
							}

							if (m_dragging)
							{
								if (pDocument->m_activeTool == TOOL_ELLIPSE)
								{
									HBRUSH hOldBrush = (HBRUSH)SelectObject(clipdc, GetStockObject(NULL_BRUSH));
									Ellipse(clipdc, m_startpt.x, m_startpt.y, m_oldpt.x, m_oldpt.y);
									SelectObject(clipdc, hOldBrush);
								}
							}

							SelectObject(clipdc, hOldPen);
							DeleteObject(hPen);

							SetViewportOrgEx(clipdc, oldOrg.x, oldOrg.y, NULL);
						}

						if (TRUE/*bColorManagement || !m_hdd*/)
						{
							BitBlt(hDC, left, top, width, height, clipdc, left, top, SRCCOPY);
						/*
							StretchDIBits(
								hDC,

								left, top, width, height,
								left, top, width, height,

								m_bmBits, (LPBITMAPINFO)m_lpBmi,
								DIB_RGB_COLORS, SRCCOPY);
						*/
						}
						else
						{
						/*
						DrawDibDraw(m_hdd, pDC->m_hDC,
						left, top, width, height,
						(LPBITMAPINFOHEADER)bmi, bits,
						0, 0, width, height, 0);
							*/
						}

						SelectObject(clipdc, pOldBitmap);
						DeleteObject(hBitmap);
					}

					GlobalFree(bmi);
				}

		#if 0
				if (gApp->m_activeTool == TOOL_TEXT && m_pTextElement != NULL)
				{
					SVGLib::ISVGTextElementPtr text = m_pTextElement->m_domElement;
					SVGLib::ISVGPointPtr point = text->getStartPositionOfChar(m_cursorPos);

					int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

					MoveToEx(hDC, point->x, point->y, NULL);
					LineTo(hDC, point->x, point->y-20);

					SetROP2(hDC, oldR2);
				}
		#endif

				RestoreDC(hDC, state);
			}

			SelectObject(dc, hOldBitmap);
			DeleteDC(dc);
		}
		else
		{
			FillSolidRect(hDC, &clip, RGB(190, 190, 190));
		}

		EndPaint(hwnd, &ps);
		return 0;
	}
	else
#endif
	{
		return HANDLE_BASE<IHTMLControl>(m_puiwnd, uMsg, wParam, lParam);
	}
}
#endif

long CWebEditControl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	if (HANDLE_BASE<IHTMLControl>(m_puiwnd, uMsg, wParam, lParam) != 0)
//		return -1;

//	CComQIPtr<IUIWnd> thiswnd;
//	QueryInterface(IID_IUIWnd, (void**)&thiswnd);

	

//	m_horz->CreateControl(thiswnd, 0, 0, SBS_HORZ | WS_VISIBLE, 0, 0, 0, 0, NULL);
//	m_vert->CreateControl(thiswnd, 0, 0, SBS_VERT | WS_VISIBLE, 0, 0, 0, 0, NULL);

	HRESULT hr = IDispEventImpl<3, CWebEditControl, &DIID__IESvgDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventAdvise(m_pDocument);
	ATLASSERT(SUCCEEDED(hr));

	CComQIPtr<IUIManager> uiManager = gApp->m_frame;

	hr = IDispEventImpl<5, CWebEditControl, &DIID__IUIManagerEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(uiManager);
	ATLASSERT(SUCCEEDED(hr));

	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axhtmlControl.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
	m_axhtmlControl.AttachControl(m_htmlControl, &p);


#if 0
	m_htmlControl->AttachEditor(this);
#endif
#if 0
	HWND hwnd;
	get_hwnd(&hwnd);

	RevokeDragDrop(hwnd);	// Revoke base class registration
	::RegisterDragDrop(hwnd, (IDropTarget*)this);
#endif

	return 0;
}

long CWebEditControl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HRESULT hr = IDispEventImpl<3, CWebEditControl, &DIID__IESvgDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_pDocument);
	ATLASSERT(SUCCEEDED(hr));

	CComQIPtr<IUIManager> uiManager = gApp->m_frame;

	hr = IDispEventImpl<5, CWebEditControl, &DIID__IUIManagerEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(uiManager);
	ATLASSERT(SUCCEEDED(hr));

// NOTE: base class revokes, so mustn't do it here
//	HWND hwnd;
//	get_hwnd(&hwnd);
//	RevokeDragDrop(hwnd);	// Revoke base class

	return 0;//HANDLE_BASE<IUIView>(m_puiwnd, uMsg, wParam, lParam);
}

/*
HRESULT __stdcall CWebEditControl::OnHorzScroll(long code, long pos)
{
	long oldPos; m_horz->get_pos(&oldPos);

	HWND hwnd;
	get_hwnd(&hwnd);

	CRect client;
	GetClientRect(&client);

	CRect	rect(0, 0, client.right-16, client.bottom-16);

	HDC dc = CreateCompatibleDC(NULL);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(dc, m_hBitmap);
	ScrollDC(dc, oldPos-pos, 0, NULL, NULL, NULL, NULL);
	SelectObject(dc, hOldBitmap);

	m_horz->put_pos(pos);
	ScrollWindow(hwnd, (oldPos-pos), 0, &rect, &rect);

	Fire_changeviewbox();

	return S_OK;
}

HRESULT __stdcall CWebEditControl::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	HWND hwnd;
	get_hwnd(&hwnd);

	CRect client;
	GetClientRect(&client);

	CRect	rect(0, 0, client.right-16, client.bottom-16);
	
	HDC dc = CreateCompatibleDC(NULL);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(dc, m_hBitmap);
	ScrollDC(dc, 0, oldPos-pos, NULL, NULL, NULL, NULL);
	SelectObject(dc, hOldBitmap);

	m_vert->put_pos(pos);
	ScrollWindow(hwnd, 0, oldPos-pos, &rect, &rect);

	Fire_changeviewbox();

	return S_OK;
}
*/

long CWebEditControl::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return TRUE;
}

long CWebEditControl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	HANDLE_BASE<IHTMLControl>(m_puiwnd, uMsg, wParam, lParam);

	CRect client;
	GetClientRect(&client);

	m_axhtmlControl.MoveWindow(0, 0, client.right, client.bottom, TRUE);

	OnSize();

#if 0

	Fire_changeviewbox();
#endif

	return S_OK;
}

void CWebEditControl::OnSize()
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	m_offset.x = 0;
	m_offset.y = 0;
#if 0

	RECT	rect; GetClientRect(&rect);
	int sbHeight = GetSystemMetrics(SM_CYHSCROLL);
	int sbWidth = GetSystemMetrics(SM_CXVSCROLL);

	int cx = rect.right;
	int cy = rect.bottom;

	m_horz->MoveWindow(0, cy-sbHeight, cx-sbWidth, sbHeight, TRUE);
	m_vert->MoveWindow(cx-sbWidth, sbHeight, sbWidth, cy-sbHeight-sbHeight, TRUE);

//	m_sizeGrip->MoveWindow(cx-sbWidth, cy-sbHeight, sbWidth, sbHeight);
//	SetWindowPos(m_popup->GetHwnd(), NULL, cx-sbWidth, 0, sbWidth, sbHeight, SWP_NOZORDER);

	m_imageRect.left = 0;
	m_imageRect.top = 0;
	m_imageRect.right = cx-sbWidth;
	m_imageRect.bottom = cy-sbHeight;
/*
	if (m_bShowRulers)
	{
		m_imageRect.left += 16;
		m_imageRect.top += 16;
	}
*/
	CComQIPtr<ISVGDocument> svgdoc = pDocument->GetDOMDocument();
	if (svgdoc)
	{
		long width = pDocument->GetWidth();
		long height = pDocument->GetHeight();

	//	width *= GetMagnifyFactor();
	//	height *= GetMagnifyFactor();

	//	CRect client = m_imageRect;
	//	GetClientRect(&client);

		SIZE size;
		size.cx = (int)(width+400)*GetMagnifyFactor();
		size.cy = (int)(height+400)*GetMagnifyFactor();

		m_vert->SetInfo(-200*GetMagnifyFactor(), (width+200)*GetMagnifyFactor(), m_imageRect.Height());
		m_horz->SetInfo(-200*GetMagnifyFactor(), (height+200)*GetMagnifyFactor(), m_imageRect.Width());

//		m_vert->SetInfo(0*GetMagnifyFactor(), (width+0)*GetMagnifyFactor(), m_imageRect.Height());
//		m_horz->SetInfo(0*GetMagnifyFactor(), (height+0)*GetMagnifyFactor(), m_imageRect.Width());

		m_vert->ShowWindow(SW_SHOW, NULL);
		m_horz->ShowWindow(SW_SHOW, NULL);

		size.cx = max(size.cx, m_imageRect.Width());
		size.cy = max(size.cy, m_imageRect.Height());

	//	if (size.cx > width)
	//		m_offset.x = (size.cx-width)/2;
	//	else
			m_offset.x = 0;
		
	//	if (size.cy > height)
	//		m_offset.y = (size.cy-height)/2;
	//	else
			m_offset.y = 0;
	}
	else
	{
		m_vert->SetInfo(0, 0, 0);
		m_horz->SetInfo(0, 0, 0);
		m_vert->ShowWindow(SW_HIDE, NULL);
		m_horz->ShowWindow(SW_HIDE, NULL);
	}
#endif
}

STDMETHODIMP CWebEditControl::TranslateEvent(ILDOMEvent * inevent, ILDOMEvent * * outevent, VARIANT_BOOL * bCancel)
{
	BSTR btype;
	inevent->get_type(&btype);
	_bstr_t type = _bstr_t(btype, false);

	CComQIPtr<ILDOMMouseEvent> mouseevt = inevent;
	if (mouseevt)
	{
		long screenX;
		long screenY;
		mouseevt->get_screenX(&screenX);
		mouseevt->get_screenY(&screenY);

		POINT point;
		point.x = screenX;
		point.y = screenY;
		UINT nFlags = 0;
		int iButton = 0;

		if (!wcscmp(type, L"mousedown"))
		{
			OnButtonDown(nFlags, point, iButton, FALSE);
		}
		else if (!wcscmp(type, L"mouseup"))
		{
			OnButtonUp(nFlags, point, iButton);
		}
		else if (!wcscmp(type, L"mousemove"))
		{
			OnMouseMove(nFlags, point);
		}
	}

	*bCancel = VARIANT_TRUE;

	return S_OK;
}

void CWebEditControl::OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	CComQIPtr<ILDOMDocument> domdocument = pDocument->GetDOMDocument();

	CComQIPtr<ILSVGDocument> svgDocument = domdocument;
	if (svgDocument == NULL)
	{
	}
	else
	{
		CComQIPtr<ILSVGSVGElement> svg;
		pDocument->GetDOMDocument()->get_documentElement((ILDOMElement**)&svg);
		if (svg == NULL) return;

		HWND hwnd = m_hWnd;

//		SetFocus(hwnd);

		if (!m_dragging)
		{
			m_numMoves = 0;

			long scrollposX = 0;// m_horz->get_pos(&scrollposX);
			long scrollposY = 0;// m_vert->get_pos(&scrollposY);

			POINT pt = point;
			pt.x -= m_offset.x;
			pt.y -= m_offset.y;
			pt.x += scrollposX;
			pt.y += scrollposY;

			m_startpt = pt;
			m_oldpt = pt;

			/*
			HDC hDC = GetDC(hwnd);
			IntersectClipRect(hDC, m_imageRect.left, m_imageRect.top, m_imageRect.right, m_imageRect.bottom);
			*/
		//	POINT org;
		//	org.x = m_imageRect.left + m_offset.x-scrollposX;
		//	org.y = m_imageRect.left + m_offset.y-scrollposY;
		//	POINT oldOrg;
		//	SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);
		//	int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

			CComQIPtr<ILSVGMatrix> inverseMagnifyMatrix;
			m_magnifyMatrix->inverse(&inverseMagnifyMatrix);

			CComQIPtr<ILSVGPoint> svgpt0;
			svgpt0.CoCreateInstance(CLSID_LSVGPoint);
			svgpt0->put_x(pt.x);
			svgpt0->put_y(pt.y);

			CComQIPtr<ILSVGPoint> svgpt;
			svgpt0->matrixTransform(inverseMagnifyMatrix, &svgpt);

			CElementImpl* pActiveElement = pDocument->GetActiveElement();

			CElementImpl* pTargetElement = NULL;
			if (pActiveElement) pTargetElement = pActiveElement->GetTargetElement();

			switch (gApp->m_svgActiveTool)
			{
				case ID_SVGTOOL_SELECT:
				{
					m_hit = 0;
					CElementImpl* pElement = pDocument->GetSvgElement()->GetElementUnderPoint(svgpt0, m_magnifyMatrix, m_hit);
				//	pDocument->SetTargetElement(pElement, nFlags);

					m_hit = 1;
					m_dragging = 1;
#if 0
					if (pActiveElement)
					{
						if (!wcscmp(pActiveElement->m_domElement->tagName, L"motionPath"))
						{
							CAnimateMotionElement* pAnimateMotion = (CAnimateMotionElement*)pActiveElement;
						/*
							_bstr_t path = pElement->m_domElement->getAttribute(L"path");
							_bstr_t values = pElement->m_domElement->getAttribute(L"values");
							_bstr_t from = pElement->m_domElement->getAttribute(L"from");
							_bstr_t to = pElement->m_domElement->getAttribute(L"to");

							if (path.length() > 0)
							{
							}
							else if (values.length() > 0)
							{
							}
							else if (from.length() > 0 && to.length() > 0)
							{
								CArray<double,double> fromvalues;
								GetCommaSepValuesArray(CUString((BSTR)from), fromvalues);

								CArray<double,double> tovalues;
								GetCommaSepValuesArray(CUString((BSTR)to), tovalues);

								if (fromvalues.GetSize() == 2 && tovalues.GetSize() == 2)
								{
									float x = fromvalues[0];
									float y = fromvalues[1];

									float x2 = tovalues[0];
									float y2 = tovalues[1];
								}
							}
							*/
						}
						else
						{
							SVGLib::ISVGTransformablePtr locatable = pActiveElement->m_domElement;
							if (locatable)
							{
								SVGLib::_tagSVGRect rbbox = locatable->getBBox();

								RECT bbox = {rbbox.x, rbbox.y, rbbox.x + rbbox.width, rbbox.y + rbbox.height};

								if (m_hit == 2)
								{
									m_centerPt.x = bbox.right;
									m_centerPt.y = bbox.bottom;
								}
								/*
								else if (m_hit == 3)
								{
									cx = left += dx;
									bottom += dy;
								}
								else if (m_hit == 4)
								{
									left += dx;
								}
								else if (m_hit == 5)
								{
									right += dx;
									top += dy;
								}
								*/
								else if (m_hit == 6)
								{
									m_centerPt.x = bbox.left;
									m_centerPt.y = bbox.top;
								}
								/*
								else if (m_hit == 7)
								{
									right += dx;
								}
								else if (m_hit == 8)
								{
									top += dy;
								}
								else if (m_hit == 9)
								{
									bottom += dy;
								}
								*/


								m_dragging = 1;
							}
						}
					}
#endif
				}
				break;

				case ID_SVGTOOL_DIRECT:
					{
					//	DrawTargetElementsPathCurves(hDC);

						CElementImpl* pElement = pDocument->GetSvgElement()->FindPointUnderPoint(svgpt0, m_magnifyMatrix, m_curveCp, m_curveCtl);
						if (m_curveCp >= 0)
						{
							CPathElement* pathElement = (CPathElement*)pElement;

							if (m_curveCtl == 0)	// Clicked on anchor point
							{
								if (nFlags & MK_SHIFT)
								{
								// Toggle selection of anchor point
									if (pathElement->IsSegmentSelected(m_curveCp))
									{
										pathElement->DeselectSegment(m_curveCp);
									}
									else
									{
										pathElement->SelectSegment(m_curveCp);
										m_hit = 1;
										m_dragging = 1;
									}
								}
								else
								{
									if (!pathElement->IsSegmentSelected(m_curveCp))
									{
										// Deselect all elements (and their selected anchor points)
										for (int i = 0; i < pDocument->m_targetElements.GetSize(); i++)
										{
											CElementImpl* pElement = pDocument->m_targetElements[i];

											BSTR btagName;
											pElement->m_domElement->get_nodeName(&btagName);
											_bstr_t tagName = _bstr_t(btagName);
											
											if (!wcscmp(tagName, L"path"))
											{
												((CPathElement*)pElement)->m_selectedPoints.RemoveAll();
											}
										}

										pathElement->SelectSegment(m_curveCp);
									}

									m_hit = 1;
									m_dragging = 1;
								}
							}
							else	// Move control point
							{
								m_hit = 1;
								m_dragging = 1;
							}
						}
						else
						{
							pDocument->SetTargetElement(pElement, nFlags);

							if (pElement)
							{
							// What mode is this ??
								m_hit = 1;
								m_dragging = 1;
							}
							else
							{
							// Direct Selection Rectangle
								m_hit = 0;
								m_dragging = 1;
							}
						}

						/*
						HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 200));
						HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

						DrawTargetElementsPathCurves(hDC);

						SelectObject(hDC, hOldPen);
						DeleteObject(hPen);
						*/

				//		DrawTargetElementsPathCurves(hDC);
					}
					break;

				case ID_SVGTOOL_PATHPEN:
				case TOOL_PENFREE:
				case TOOL_PENADD:
				case TOOL_PENDELETE:
				case TOOL_PENCORNER:
				{
					double x = pt.x;
					double y = pt.y;

					CPathElement* pathElement = NULL;
					CComQIPtr<ILSVGPathElement> path;
					CComQIPtr<ILSVGPathSegList> seglist;
					int cp = -1;
					int ctl = 0;
					double onCurve_t;
					long onCurve_segIndex = -1;

					UINT activeTool = gApp->m_svgActiveTool;

					_bstr_t tagName;
					
					if (pTargetElement)
					{
						BSTR btagName;
						pTargetElement->m_domElement->get_nodeName(&btagName);
						tagName = _bstr_t(btagName);
					}

					if (pTargetElement && !wcscmp(tagName, L"path"))
					{
						pathElement = (CPathElement*)pTargetElement;
						path = pathElement->m_domElement;
						seglist = GetPathSegList(pActiveElement);//pathData->normalizedPathSegList;

					//	pathElement->DrawPathCurve(seglist, m_magnifyMatrix, hDC);

						CComQIPtr<ILSVGLocatable> locatable = pTargetElement->m_domElement;
						CComQIPtr<ILSVGMatrix> matrix0;
						locatable->getScreenCTM(&matrix0);

						CComQIPtr<ILSVGMatrix> matrix;
						matrix0->multiply(m_magnifyMatrix, &matrix);

						cp = pathElement->FindPoint(seglist, matrix, x, y, ctl);
						if (cp < 0)
						{
							GetPointOnSegList(seglist, pt.x, pt.y, 4, &onCurve_segIndex, &onCurve_t);
						}

						if (gApp->m_svgActiveTool == ID_SVGTOOL_PATHPEN)
						{
							if (cp >= 0 && ctl == 0)
							{
								activeTool = TOOL_PENDELETE;
							}
							else if (onCurve_segIndex >= 0)
							{
								activeTool = TOOL_PENADD;
							}
						}
						else
						{
						}
					}

					switch (activeTool)
					{
					case TOOL_PENADD:
						{
							pathElement->InsertAnchorPoint(onCurve_segIndex, onCurve_t);
							pathElement->m_selectedPoints.Add(onCurve_segIndex);
						}
						break;

					case TOOL_PENDELETE:
						{
							pathElement->DeleteAnchorPoint(cp);
						}
						break;

					case TOOL_PENCORNER:
						{
							if (cp >= 0)
							{
								pDocument->SetTargetElement(pathElement, 0);

								if (ctl == 0)
								{
									pathElement->m_selectedPoints.RemoveAll();

									seglist->LockUpdate();

									CPathSeg seg;
									seg = pathElement->GetPathSeg(seglist, cp);
									seg.x[0] = seg.x[1];
									seg.y[0] = seg.y[1];

									seg.x[2] = seg.x[1];
									seg.y[2] = seg.y[1];

									pathElement->PutPathSeg(seglist, cp, seg);

									seglist->UnlockUpdate();

									m_curveCp = cp;
									m_curveCtl = 1;
									pathElement->m_selectedPoints.Add(m_curveCp);

									m_hit = 1;	// Set both control points
								}
								else
								{
									m_curveCp = cp;
									m_curveCtl = ctl;

									m_hit = 2;	// Set only one control point
								}

								m_dragging = 1;
							}
						}
						break;

					case ID_SVGTOOL_PATHPEN:
						{
							if (seglist)
							{
								CComQIPtr<ILSVGPathSegCurvetoCubicAbs> seg;
								path->createSVGPathSegCurvetoCubicAbs(
									x, y,
									pathElement->m_lastx, pathElement->m_lasty,
									x, y,
									&seg);

								pathElement->m_lastx = x;
								pathElement->m_lasty = y;

								seglist->get_numberOfItems((unsigned long*)&m_curveCp);
								m_curveCtl = 1;

								pathElement->m_selectedPoints.RemoveAll();

								seglist->appendItem(seg, NULL);
							}
							else	// Create new path element
							{
								CComQIPtr<ILSVGPathElement> path;
								pDocument->GetDOMDocument()->createElement(L"path", (ILDOMElement**)&path);

#if 0
								_bstr_t style = gApp->m_pathSettings->m_domElement->getAttribute(L"style");
								if (style.length() > 0) path->setAttribute(L"style", style);
#endif

								CComQIPtr<ILSVGAnimatedPathData> pathData = path;

								pathData->get_normalizedPathSegList(&seglist);

								CComQIPtr<ILSVGPathSegMovetoAbs> movetoabs;
								path->createSVGPathSegMovetoAbs(pt.x, pt.y, &movetoabs);

								seglist->appendItem(movetoabs, NULL);

								svg->appendChild(path, NULL);
								pathElement = (CPathElement*)pDocument->m_pTree->FindDOMElement((ILDOMNode*)path);
								pathElement->m_lastx = x;
								pathElement->m_lasty = y;

								m_curveCp = 0;
								m_curveCtl = 1;

								pDocument->SetTargetElement(pathElement, 0);
							}

							pathElement->m_selectedPoints.Add(m_curveCp);

							m_hit = 1;
							m_dragging = 1;
						}
						break;

					case TOOL_PENFREE:
						{
	#if 0
							int cp = -1;
							int ctl = 0;
							SVGLib::ISVGPathSegListPtr seglist;
							CPathElement* pathElement = NULL;

							if (pActiveElement && !wcscmp(pActiveElement->m_domElement->tagName, L"path"))
							{
								pathElement = (CPathElement*)pActiveElement;

								SVGLib::ISVGAnimatedPathDataPtr pathData = pActiveElement->m_domElement;
								seglist = pathData->normalizedPathSegList;

								cp = pathElement->FindPoint(seglist, pt.x, pt.y, ctl);
							}

							if (cp >= 0 && ctl == 0 && (cp == 0 || cp == seglist->numberOfItems-1))
							{
							// Continue from another subpath

								m_pActivePathElement = pathElement;

								SVGLib::ISVGPathSegCurvetoCubicAbsPtr curveto = seglist->getItem(cp);
								if (curveto)
								{
									m_pointArray.Add(CDblPoint(curveto->x, curveto->y));
								}
								else
								{
									SVGLib::ISVGPathSegMovetoAbsPtr moveto = seglist->getItem(cp);
									if (moveto)
									{
										m_pointArray.Add(CDblPoint(moveto->x, moveto->y));
									}
								}
							}
							else
							{
							// New Subpath
								m_pActivePathElement = NULL;
								m_pointArray.Add(CDblPoint(pt.x, pt.y));
							}

							m_dragging = 1;
	#endif
						}
						break;
					}
				}
				break;

				case TOOL_ROTATE:
				case TOOL_SCALE:
				case TOOL_SKEW:
					{
						if (fabs(pt.x-m_pivotPt.x) < 8 &&
							fabs(pt.y-m_pivotPt.y) < 8)
						{
							m_hit = 2;
						}
						else
						{
							for (int i = 0; i < pDocument->m_targetElements.GetSize(); i++)
							{
								CElementImpl* pElement = pDocument->m_targetElements[i];
#if 0
								CComQIPtr<ISVGTransform> transform = pElement->GetMatrixTransform();

							// Remember the initial matrix
								if (pElement->m_initialMatrix == NULL)
									pElement->m_initialMatrix.CreateInstance("SVG.SVGMatrix");

								pElement->m_initialMatrix->a = transform->matrix->a;
								pElement->m_initialMatrix->b = transform->matrix->b;
								pElement->m_initialMatrix->c = transform->matrix->c;
								pElement->m_initialMatrix->d = transform->matrix->d;
								pElement->m_initialMatrix->e = transform->matrix->e;
								pElement->m_initialMatrix->f = transform->matrix->f;
#endif
							}

							m_hit = 1;
						}

						m_dragging = 1;
					}
					break;

				case TOOL_TWIRL:
					{
#if 0
						double dx = pt.x - m_pivotPt.x;
						double dy = pt.y - m_pivotPt.y;
						double l = sqrt(dx*dx + dy*dy);

						if (fabs(pt.x-m_pivotPt.x) < 8 &&
							fabs(pt.y-m_pivotPt.y) < 8)
						{
							m_hit = 2;
						}
						else if (fabs(l-m_effectRadius) < 8)
						{
							m_hit = 3;
						}
						else
						{
							for (int i = 0; i < m_pDocument->m_targetElements.GetSize(); i++)
							{
								CElement* pElement = m_pDocument->m_targetElements[i];

							// only process elements that support twirling
								if (!wcscmp(pElement->m_domElement->tagName, L"path"))
								{
									CPathElement* pathElement = (CPathElement*)pElement;

								//	pathElement->DrawPathCurve(hDC, GetMagnifyFactor());	// Erase

									pathElement->SetPolyPointsFromSegList();
								//	pathElement->DrawPolyPoints(hDC);
								}
							}

							m_hit = 1;

							{
								float x = m_pivotPt.x;
								float y = m_pivotPt.y;

								HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
								Ellipse(hDC, x-4, y-4, x+5, y+5);
								Ellipse(hDC, x-m_effectRadius, y-m_effectRadius, x+m_effectRadius, y+m_effectRadius);
								SelectObject(hDC, hOldBrush);
							}
						}

						m_dragging = 1;
#endif
					}
					break;

				case TOOL_TEXT:
					{
						m_hit = 0;
						CElementImpl* pElement = pDocument->GetSvgElement()->GetElementUnderPoint(svgpt, m_magnifyMatrix, m_hit);

						CComQIPtr<ILSVGTextContentElement> textContent;
						if (pElement) textContent = pElement->m_domElement;

						if (textContent)
						{
							pDocument->SetTargetElement(pElement, nFlags);

							textContent->getCharNumAtPosition(svgpt, &m_cursorPos);
							if (m_cursorPos >= 0)
							{
								m_initSelCharPos = m_cursorPos;
								m_startSelCharPos = m_cursorPos;
								m_endSelCharPos = m_cursorPos;

								m_pTextElement = (CTextElement*)pElement;

								m_hit = 1;
								m_dragging = 1;

								{
									/*
								CComQIPtr<ISVGTextContentElement> textContent = target;
								if (textContent)
								{
									CTextContent* pTextContent;
									textContent->GetNProp(L"pelement", (DWORD*)&pTextContent);
									pSVGElement->m_pSelectedTextElement = pTextContent->GetTextElement();

									long charpos = pSVGElement->m_pSelectedTextElement->getCharNumAtPosition(svgpt);
									if (charpos >= 0)
									{
										pSVGElement->m_initSelCharPos = charpos;
										pSVGElement->m_startSelCharPos = charpos;
										pSVGElement->m_endSelCharPos = charpos;

										m_dragging = 1;
									}
									else
									{
										pSVGElement->m_pSelectedTextElement = NULL;
									}
								}
								*/
								}
							}
						}
						else
						{
							CComQIPtr<ILSVGTextElement> textel;
							pDocument->GetDOMDocument()->createElement(L"text", (ILDOMElement**)&textel);

							double x; svgpt->get_x(&x);
							double y; svgpt->get_y(&y);

							ATLASSERT(0);
#if 0
							CComQIPtr<ILSVGAnimatedLength> ax;
							textel->get_x(&ax);
							CComQIPtr<ILSVGLength> xlength;
							ax->get_baseVal(&xlength);
							xlength->put_value(x);

							CComQIPtr<ILSVGAnimatedLength> ay;
							textel->get_y(&ay);
							CComQIPtr<ILSVGLength> ylength;
							ay->get_baseVal(&ylength);
							ylength->put_value(y);
#endif

							CComQIPtr<ILDOMText> text;
							pDocument->GetDOMDocument()->createTextNode(L"Hello", &text);
							textel->appendChild(text, NULL);

							svg->appendChild(textel, NULL);

							m_pTextElement = (CTextElement*)pDocument->m_pTree->FindDOMElement((ILSVGElement*)textel);
							pDocument->SetTargetElement(m_pTextElement, 0);
						}
					}
					break;

				case ID_SVGTOOL_CIRCLE:
				{
					m_radius = 0;
				//	Ellipse(hDC, m_startpt.x-m_radius, m_startpt.y-m_radius, m_startpt.x + m_radius+1, m_startpt.y + m_radius+1);

					m_dragging = 1;
				}
				break;

				case ID_SVGTOOL_ELLIPSE:
				{
				//	Ellipse(hDC, m_startpt.x, m_startpt.y, pt.x, pt.y);
					m_dragging = 1;
				}
				break;

				case TOOL_RECT:
				{
				//	Ellipse(hDC, m_startpt.x, m_startpt.y, pt.x, pt.y);
					m_dragging = 1;
				}
				break;

				case ID_SVGTOOL_LINE:
				{
				//	MoveToEx(hDC, m_startpt.x, m_startpt.y, NULL);
				//	LineTo(hDC, pt.x, pt.y);
					m_dragging = 1;
				}
				break;

				case TOOL_ZOOM:
					{
						m_dragging = 1;
						m_zoomRect.SetRectEmpty();
					}
					break;

				case TOOL_HAND:
					{
						::SetCursor(LoadCursor(_Module.m_hInst, MAKEINTRESOURCE(IDC_HAND2)));
						m_dragging = 1;
					}
					break;
			}

		//	SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		//	SetROP2(hDC, oldR2);
		//	ReleaseDC(hwnd, hDC);

			if (m_dragging)
			{
#if 0
				SetCapture(NULL);
#endif
			}
		}
	}
}

void CWebEditControl::OnButtonUp(UINT nFlags, POINT point, int iButton)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	CComQIPtr<ILDOMDocument> domdocument = pDocument->GetDOMDocument();

	CComQIPtr<ILSVGDocument> svgDocument = domdocument;
	if (svgDocument == NULL)
	{
		;//return HANDLE_BASE<IHTMLControl>(m_puiwnd, uMsg, wParam, lParam);
	}
	else
	{
		CComQIPtr<ILSVGSVGElement> svg;
		svgDocument->get_documentElement((ILDOMElement**)&svg);
		ASSERT(svg != NULL);

		HWND hwnd = m_hWnd;

		long scrollposX = 0;// m_horz->get_pos(&scrollposX);
		long scrollposY = 0;// m_vert->get_pos(&scrollposY);

		POINT pt = point;
		pt.x -= m_offset.x;
		pt.y -= m_offset.y;
		pt.x += scrollposX;
		pt.y += scrollposY;

		if (m_dragging)
		{
			/*
			HDC hDC = GetDC(hwnd);
			IntersectClipRect(hDC, m_imageRect.left, m_imageRect.top, m_imageRect.right, m_imageRect.bottom);
			POINT org;
			org.x = m_imageRect.left + m_offset.x-scrollposX;
			org.y = m_imageRect.left + m_offset.y-scrollposY;
			POINT oldOrg;
			SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);
			int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
			*/

			ReleaseCapture();
			m_dragging = 0;

			CElementImpl* pActiveElement = pDocument->GetActiveElement();

			switch (gApp->m_svgActiveTool)
			{
			case ID_SVGTOOL_SELECT:
				{
					InvalidateInvalidRect();

					CComQIPtr<IOleUndoManager> undoManager;
					pDocument->get_undoManager(&undoManager);

					if (m_hit == 1)
					{
						CWEUndoMoveObjects* undo = new CWEUndoMoveObjects;
						undo->AddRef();

						undo->m_pDocument = pDocument;
						undo->m_dx = m_oldpt.x-m_startpt.x;
						undo->m_dy = m_oldpt.y-m_startpt.y;
						undo->m_bSourceEditLast = pDocument->m_bSourceEditLast;
						undo->m_sourceText = m_sourceText;

						for (int i = 0; i < pDocument->m_targetElements.GetSize(); i++)
						{
							CElementImpl* pElement = pDocument->m_targetElements[i];

							GUID guid;
							pElement->m_domElement->get_uniqID(&guid);
							undo->m_targetElements.Add(guid);
						}

						undoManager->Add(undo);

						pDocument->m_bSourceEditLast = false;
						m_sourceText = NULL;
					}
					else
					{
					}
				}
				break;

			case TOOL_ROTATE:
			case TOOL_SCALE:
			case TOOL_SKEW:
				{
					InvalidateInvalidRect();
				}
				break;

#if 0
			case TOOL_TWIRL:
				{
					if (m_hit == 1)
					{
						for (int i = 0; i < m_pDocument->m_targetElements.GetSize(); i++)
						{
							CElement* pElement = m_pDocument->m_targetElements[i];
							if (!wcscmp(pElement->m_domElement->tagName, L"path"))
							{
								CPathElement* pathElement = (CPathElement*)pElement;

								SVGLib::ISVGAnimatedPathDataPtr pathData = pathElement->m_domElement;
								SVGLib::ISVGPathSegListPtr seglist = pathData->normalizedPathSegList;
								
								seglist->clear();
								pathElement->ConvertFlatToCurves(seglist);

								pathElement->m_subPoints.RemoveAll();
								pathElement->m_flatPoints.RemoveAll();
							}
						}

						{
							float x = m_pivotPt.x;
							float y = m_pivotPt.y;

							HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
							Ellipse(hDC, x-4, y-4, x+5, y+5);
							Ellipse(hDC, x-m_effectRadius, y-m_effectRadius, x+m_effectRadius, y+m_effectRadius);
							SelectObject(hDC, hOldBrush);
						}

						InvalidateInvalidRect();
					}
				}
				break;
#endif

			case ID_SVGTOOL_DIRECT:
				{
					if (m_hit == 0)	// Selection rectangle
					{
#if 0
						DrawFocusRect(hDC, m_startpt.x, m_startpt.y, m_oldpt.x, m_oldpt.y);

						if (!(nFlags & MK_SHIFT))
						{
							for (int i = 0; i < pDocument->m_targetElements.GetSize(); i++)
							{
								CElement* pElement = pDocument->m_targetElements[i];
								if (!wcscmp(pElement->m_domElement->tagName, L"path"))
								{
									((CPathElement*)pElement)->m_selectedPoints.RemoveAll();
								}
							}
						}

						double x1, y1, x2, y2;

						if (m_startpt.x < m_oldpt.x)
						{
							x1 = m_startpt.x;
							x2 = m_oldpt.x;
						}
						else
						{
							x2 = m_startpt.x;
							x1 = m_oldpt.x;
						}

						if (m_startpt.y < m_oldpt.y)
						{
							y1 = m_startpt.y;
							y2 = m_oldpt.y;
						}
						else
						{
							y2 = m_startpt.y;
							y1 = m_oldpt.y;
						}

						pDocument->m_pTree->SelectPointsInRect(x1, y1, x2, y2);
#endif
					}
					else
					{
					//	Invalidate();
						InvalidateInvalidRect();
					}
				}
				break;
		
			case ID_SVGTOOL_PATHPEN:
				{
					//Invalidate();
					InvalidateInvalidRect();
				}
				break;
				
#if 0
			case TOOL_PENFREE:
				{
					SVGLib::ISVGPathElementPtr path;
					
					if (m_pActivePathElement)	// Add to already existing path
					{
						path = m_pActivePathElement->m_domElement;
					}
					else
					{
						path = m_pDocument->GetDOMDocument()->createElement(L"path");
					}
					
					SVGLib::ISVGAnimatedPathDataPtr pathData = path;
					
					g_pathElement = path;
					g_pathSegList = pathData->normalizedPathSegList;
					g_pathSize = g_pathSegList->numberOfItems;

					int size = m_pointArray.GetSize();
					FitCurve((Point2*)m_pointArray.GetData(), size, gApp->m_fitCurveError);		//  Fit the Bezier curves
					
					if (!m_pActivePathElement)
					{
						m_pDocument->GetDOMDocument()->documentElement->appendChild(path);
						CPathElement* pathElement = (CPathElement*)m_pDocument->m_pTree->FindDOMElement(path);
						m_pDocument->SetTargetElement(pathElement, 0);
					}
				}
				break;
#endif

			case ID_SVGTOOL_CIRCLE:
			case ID_SVGTOOL_ELLIPSE:
			case TOOL_RECT:
				{
					CComQIPtr<ILSVGElement> element;
					
					if (gApp->m_svgActiveTool == ID_SVGTOOL_CIRCLE)
					{
#if 0
						Ellipse(hDC, m_startpt.x-m_radius, m_startpt.y-m_radius, m_startpt.x + m_radius+1, m_startpt.y + m_radius+1);
						
						float cx = m_startpt.x;
						float cy = m_startpt.y;
						float r = m_radius;
						
						if (gApp->m_bCreateAsPath)
						{
							SVGLib::ISVGPathElementPtr path = m_pDocument->GetDOMDocument()->createElement(L"path");
							
							SVGLib::ISVGAnimatedPathDataPtr pathData = path;
							SVGLib::ISVGPathSegListPtr seglist = pathData->pathSegList;
							
							seglist->LockUpdate();
							SetPathSegListToEllipse(seglist, cx-r, cy-r, cx+r, cy+r);
							seglist->UnlockUpdate();
							
							element = path;
						}
						else
						{
							SVGLib::ISVGCircleElementPtr circle = m_pDocument->GetDOMDocument()->createElement(L"circle");
							circle->cx->baseVal->value = cx;
							circle->cy->baseVal->value = cy;
							circle->r->baseVal->value = r;
							
							element = circle;
						}
#endif
					}
					else if (gApp->m_svgActiveTool == ID_SVGTOOL_ELLIPSE)
					{
					//	Ellipse(hDC, m_startpt.x, m_startpt.y, m_oldpt.x, m_oldpt.y);
						
						float width = m_oldpt.x - m_startpt.x;
						float height = m_oldpt.y - m_startpt.y;
						float cx = m_startpt.x + width/2;
						float cy = m_startpt.y + height/2;
						float rx = width/2;
						float ry = height/2;
						
#if 0
						if (gApp->m_bCreateAsPath)
						{
							SVGLib::ISVGPathElementPtr path = m_pDocument->GetDOMDocument()->createElement(L"path");
							
							SVGLib::ISVGAnimatedPathDataPtr pathData = path;
							SVGLib::ISVGPathSegListPtr seglist = pathData->pathSegList;
							
							seglist->LockUpdate();
							SetPathSegListToEllipse(seglist, cx-rx, cy-ry, cx+rx, cy+ry);
							seglist->UnlockUpdate();
							
							element = path;
						}
						else
#endif
						{
							CComQIPtr<ILSVGEllipseElement> ellipse;
							pDocument->GetDOMDocument()->createElement(L"ellipse", (ILDOMElement**)&ellipse);

							{
								CComQIPtr<ILSVGAnimatedLength> alength;
								ellipse->get_cx(&alength);
								CComQIPtr<ILSVGLength> length;
								alength->get_baseVal(&length);
								length->put_value(cx);
							}

							{
								CComQIPtr<ILSVGAnimatedLength> alength;
								ellipse->get_cy(&alength);
								CComQIPtr<ILSVGLength> length;
								alength->get_baseVal(&length);
								length->put_value(cy);
							}

							{
								CComQIPtr<ILSVGAnimatedLength> alength;
								ellipse->get_rx(&alength);
								CComQIPtr<ILSVGLength> length;
								alength->get_baseVal(&length);
								length->put_value(rx);
							}

							{
								CComQIPtr<ILSVGAnimatedLength> alength;
								ellipse->get_ry(&alength);
								CComQIPtr<ILSVGLength> length;
								alength->get_baseVal(&length);
								length->put_value(ry);
							}

							element = ellipse;
						}
					}
					else if (gApp->m_svgActiveTool == TOOL_RECT)
					{
#if 0
						SVGLib::ISVGRectElementPtr frect = gApp->m_rectSettings->m_domElement;
						int ewidth = frect->rx->baseVal->value*2;
						int eheight = frect->ry->baseVal->value*2;
						RoundRect(hDC, m_startpt.x, m_startpt.y, m_oldpt.x, m_oldpt.y, ewidth, eheight);

						float x = m_startpt.x;
						float y = m_startpt.y;
						float width = m_oldpt.x - m_startpt.x;
						float height = m_oldpt.y - m_startpt.y;
						float rx = frect->rx->baseVal->value;
						float ry = frect->ry->baseVal->value;

						if (gApp->m_bCreateAsPath)
						{
							SVGLib::ISVGPathElementPtr path = m_pDocument->GetDOMDocument()->createElement(L"path");

							SVGLib::ISVGAnimatedPathDataPtr pathData = path;
							SVGLib::ISVGPathSegListPtr seglist = pathData->pathSegList;

							seglist->LockUpdate();
							SetPathSegListToRoundRect(seglist, x, y, x+width-1, y+height-1, rx, ry, TRUE);
							seglist->UnlockUpdate();

							element = path;
						}
						else
						{
							SVGLib::ISVGRectElementPtr rect = m_pDocument->GetDOMDocument()->createElement(L"rect");

							rect->x->baseVal->value = x;
							rect->y->baseVal->value = y;
							rect->width->baseVal->value = width;
							rect->height->baseVal->value = height;
							rect->rx->baseVal->value = rx;
							rect->ry->baseVal->value = ry;

							element = rect;
						}
#endif
					}
					
					if (element)
					{
					//	_bstr_t style = gApp->m_pathSettings->m_domElement->getAttribute(L"style");
					//	if (style.length() > 0) element->setAttribute(L"style", style);
						
						svg->appendChild(element, NULL);
						pDocument->SetTargetElement(pDocument->m_pTree->FindDOMElement((ILDOMNode*)element), 0);
					}
				}
				break;

#if 0
			case TOOL_LINE:
				{
#if 0
					MoveToEx(hDC, m_startpt.x, m_startpt.y, NULL);
					LineTo(hDC, m_oldpt.x, m_oldpt.y);

					SVGLib::ISVGElementPtr element;

					SVGLib::ISVGLineElementPtr line = m_pDocument->GetDOMDocument()->createElement(L"line");
					line->x1->baseVal->value = m_startpt.x;
					line->y1->baseVal->value = m_startpt.y;
					line->x2->baseVal->value = m_oldpt.x;
					line->y2->baseVal->value = m_oldpt.y;

					element = line;

					if (element)
					{
						_bstr_t style = gApp->m_pathSettings->m_domElement->getAttribute(L"style");
						if (style.length() > 0) element->setAttribute(L"style", style);
						
						m_pDocument->GetDOMDocument()->documentElement->appendChild(element);
						m_pDocument->SetTargetElement(m_pDocument->m_pTree->FindDOMElement(element), 0);
					}
				}
				break;
#endif
#endif

			case TOOL_ZOOM:
				{
#if 0
					HDC hDC = GetDC(hwnd);
					IntersectClipRect(hDC, m_imageRect.left, m_imageRect.top, m_imageRect.right, m_imageRect.bottom);
					POINT org;
					org.x = m_imageRect.left + m_offset.x-scrollposX;
					org.y = m_imageRect.left + m_offset.y-scrollposY;
					POINT oldOrg;
					SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

					int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
					HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
#endif

					double aspect = (double)m_imageRect.Height()/m_imageRect.Width();

#if 0
				// Erase old zoomrect
					Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

					SelectObject(hDC, hOldBrush);
					SetROP2(hDC, oldR2);

					SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
					ReleaseDC(hwnd, hDC);
#endif

					m_zoomRect.NormalizeRect();

					if (m_zoomRect.Width() <= 2 || m_zoomRect.Height() <= 2)
					{
						double x = m_startpt.x/m_magnify;
						double y = m_startpt.y/m_magnify;

					//	double docwidth = m_imageRect.Width();///m_magnify;
					//	double docheight = m_imageRect.Height();///m_magnify;

						if (!(nFlags & MK_SHIFT/*MK_ALT*/))	// Zoom in
						{
							ZoomToRect2(
								x-m_imageRect.Width()/m_magnify/4.0,
								y-m_imageRect.Height()/m_magnify/4.0,
								x+m_imageRect.Width()/m_magnify/4.0,
								y+m_imageRect.Height()/m_magnify/4.0);
						}
						else	// Zoom out
						{
							ATLTRACE("Zoom out rect\n");

							ZoomToRect2(
								x-m_imageRect.Width()/m_magnify,
								y-m_imageRect.Height()/m_magnify,
								x+m_imageRect.Width()/m_magnify,
								y+m_imageRect.Height()/m_magnify);
						}
					}
					else
					{
					//	ZoomToRect(m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);
						ZoomToRect2(
							m_zoomRect.left/m_magnify,
							m_zoomRect.top/m_magnify,
							m_zoomRect.right/m_magnify,
							m_zoomRect.bottom/m_magnify
							);
					}
				}
				break;
			}

			/*
			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
			SetROP2(hDC, oldR2);
			ReleaseDC(hwnd, hDC);
			*/
		}
	}
}

#if 0
void CWebEditControl::ZoomToRect(double left, double top, double right, double bottom)
{
	int animate = 1;

	CDblRect zoomRect;
	zoomRect.left = left;
	zoomRect.top = top;
	zoomRect.right = right;
	zoomRect.bottom = bottom;

	HWND hwnd = m_hWnd;

	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	CRect orect;
	orect.left = scrollposX;
	orect.top = scrollposY;
	orect.right = scrollposX + m_imageRect.Width();
	orect.bottom = scrollposY + m_imageRect.Height();

	int total;

	if (animate == 1)
	{
		HDC hDC = GetDC();
		int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

		CRect zrect;

		int atotal = 50;

	//	CRect orect = m_imageRect;

		for (int i = 0; i <= atotal; i++)
		{
			if (i > 0)
				Rectangle(hDC, zrect.left, zrect.top, zrect.right, zrect.bottom);

			zrect.left = orect.left + (zoomRect.left-orect.left)*i/atotal;
			zrect.top = orect.top + (zoomRect.top-orect.top)*i/atotal;
			zrect.right = orect.right + (zoomRect.right-orect.right)*i/atotal;
			zrect.bottom = orect.bottom + (zoomRect.bottom-orect.bottom)*i/atotal;

			zrect.OffsetRect(-scrollposX, -scrollposY);

			Rectangle(hDC, zrect.left, zrect.top, zrect.right, zrect.bottom);

			Sleep(5);
		}

		SelectObject(hDC, hOldBrush);
		SetROP2(hDC, oldR2);
		ReleaseDC(hDC);

		total = 1;
	}
	else if (animate == 2)
	{
		total = 5;
	}
	else
	{
		total = 1;
	}

	double omagnify = m_magnify;

	for (int i = 1; i <= total; i++)
	{
		CDblRect zrect;
	/*
		zrect.left = orect.left + (zoomRect.left-orect.left)*i/total;
		zrect.top = orect.top + (zoomRect.top-orect.top)*i/total;
		zrect.right = orect.right + (zoomRect.right-orect.right)*i/total;
		zrect.bottom = orect.bottom + (zoomRect.bottom-orect.bottom)*i/total;
	*/
		zrect.left = zoomRect.left;
		zrect.top = zoomRect.top;
		zrect.right = zoomRect.right;
		zrect.bottom = zoomRect.bottom;

		double magnifyby = (double)m_imageRect.Width()/zrect.Width();

		ATLTRACE("%g/%g - magnifyby: %g\n", (double)m_imageRect.Width(), zrect.Width(), magnifyby);

		int cx = zrect.left*magnifyby;
		int cy = zrect.top*magnifyby;

		m_magnify = omagnify * magnifyby;
		m_magnifyMatrix->put_a(m_magnify);
		m_magnifyMatrix->put_d(m_magnify);

		OnSize();
		InvalidateRect(NULL, TRUE);

		setScrollposXY(cx, cy);

		UpdateWindow();
	}

	ATLTRACE("zoomfactor: %g\n", m_magnify);
}
#endif

void CWebEditControl::ZoomToRect2(double left, double top, double right, double bottom)
{
	CDblRect zoomRect;
	zoomRect.left = left;
	zoomRect.top = top;
	zoomRect.right = right;
	zoomRect.bottom = bottom;

	HWND hwnd = m_hWnd;

	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	CDblRect zrect;
	zrect.left = zoomRect.left;
	zrect.top = zoomRect.top;
	zrect.right = zoomRect.right;
	zrect.bottom = zoomRect.bottom;

	double oldmagnify = m_magnify;

//	m_magnify = (double)(pDocument->GetWidth()/**m_magnify*/)/zrect.Width();
	m_magnify = (double)(m_imageRect.Width()/**m_magnify*/)/zrect.Width();
	m_magnifyMatrix->put_a(m_magnify);
	m_magnifyMatrix->put_d(m_magnify);

	int cx = zrect.left*m_magnify;
	int cy = zrect.top*m_magnify;

	int animate = 1;

	if (animate == 1)
	{
	/*
		CRect orect;
		orect.left = scrollposX;
		orect.top = scrollposY;
		orect.right = scrollposX + m_imageRect.Width();
		orect.bottom = scrollposY + m_imageRect.Height();

		int total;

		double omagnify = m_magnify;
	*/

		HDC hDC = GetDC();
		int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

		CDblRect imageRect;
		imageRect.left = m_imageRect.left;
		imageRect.top = m_imageRect.top;
		imageRect.right = m_imageRect.right;
		imageRect.bottom = m_imageRect.bottom;

		CDblRect orect;
		CDblRect zRect;

		if (m_magnify > oldmagnify) // Zoom in
		{
			orect = imageRect;
			zRect = zoomRect;

			zRect.left *= oldmagnify;
			zRect.top *= oldmagnify;
			zRect.right *= oldmagnify;
			zRect.bottom *= oldmagnify;
		
			zRect.left -= scrollposX;
			zRect.top -= scrollposY;
			zRect.right -= scrollposX;
			zRect.bottom -= scrollposY;
		}
		else
		{
			zRect = imageRect;
			orect = zoomRect;

			orect.left += scrollposX;
			orect.top += scrollposY;
			orect.right += scrollposX;
			orect.bottom += scrollposY;

			orect.left /= oldmagnify;
			orect.top /= oldmagnify;
			orect.right /= oldmagnify;
			orect.bottom /= oldmagnify;

		/*
			orect.left /= m_magnify;
			orect.top /= m_magnify;
			orect.right /= m_magnify;
			orect.bottom /= m_magnify;
		*/
		}

		CRect zrect2;
		int atotal = 20;

		for (int i = 0; i <= atotal; i++)
		{
			if (i > 0)
				Rectangle(hDC, zrect2.left, zrect2.top, zrect2.right, zrect2.bottom);

			zrect2.left = orect.left + (zRect.left-orect.left)*i/atotal;
			zrect2.top = orect.top + (zRect.top-orect.top)*i/atotal;
			zrect2.right = orect.right + (zRect.right-orect.right)*i/atotal;
			zrect2.bottom = orect.bottom + (zRect.bottom-orect.bottom)*i/atotal;

			Rectangle(hDC, zrect2.left, zrect2.top, zrect2.right, zrect2.bottom);

			Sleep(1);
		}

		SelectObject(hDC, hOldBrush);
		SetROP2(hDC, oldR2);
		ReleaseDC(hDC);
	}

	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);
	{

		OnSize();
		InvalidateRect(NULL, TRUE);

		setScrollposXY(cx, cy);

		UpdateWindow();
	}

	ATLTRACE("zoomfactor: %g\n", m_magnify);
}

void CWebEditControl::OnMouseMove(UINT nFlags, POINT point)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	CComQIPtr<ILDOMDocument> domdocument = pDocument->GetDOMDocument();

	CComQIPtr<ILSVGDocument> svgDocument = domdocument;
	if (svgDocument == NULL)
	{
		;//return HANDLE_BASE<IHTMLControl>(m_puiwnd, uMsg, wParam, lParam);
	}
	else
	{
		long scrollposX = 0;// m_horz->get_pos(&scrollposX);
		long scrollposY = 0;// m_vert->get_pos(&scrollposY);

		POINT pt = point;
		pt.x -= m_offset.x;
		pt.y -= m_offset.y;
		pt.x += scrollposX;
		pt.y += scrollposY;

		CComQIPtr<ILSVGMatrix> inverseMagnifyMatrix;
		m_magnifyMatrix->inverse(&inverseMagnifyMatrix);

		CComQIPtr<ILSVGPoint> svgpt0;
		svgpt0.CoCreateInstance(CLSID_LSVGPoint);
		
		svgpt0->put_x(pt.x);
		svgpt0->put_y(pt.y);

		CComQIPtr<ILSVGPoint> svgpt;
		svgpt0->matrixTransform(inverseMagnifyMatrix, &svgpt);

		if (m_dragging)
		{
			CElementImpl* pActiveElement = pDocument->GetActiveElement();

			CElementImpl* pTargetElement = NULL;
			if (pActiveElement) pTargetElement = pActiveElement->GetTargetElement();

			float dx = pt.x - m_oldpt.x;
			float dy = pt.y - m_oldpt.y;

		/*
			HDC hDC = CreateCompatibleDC(NULL);
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, m_hBitmap);

			POINT org;
			org.x = m_offset.x;
			org.y = m_offset.y;
			POINT oldOrg;
			SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);
		*/

		//	SetBoundsRect(hDC, NULL, DCB_ENABLE | DCB_RESET);

			switch (gApp->m_svgActiveTool)
			{
			case ID_SVGTOOL_SELECT:
				{
					if (m_numMoves == 0)
					{
						if (pDocument->m_bSourceEditLast)
						{
						// Remember the source text before any changes to the DOM occurs
							CComQIPtr<ITextData> textDocument;
							m_pDocument->get_textDocument(&textDocument);
							BSTR p; textDocument->get_data(&p);
							m_sourceText = SysAllocString(p);	// Make a copy
						}
					}

					CComQIPtr<ILSVGPoint> oldpt20;
					oldpt20.CoCreateInstance(CLSID_LSVGPoint);
					oldpt20->put_x(m_oldpt.x);
					oldpt20->put_y(m_oldpt.y);
					CComQIPtr<ILSVGPoint> oldpt2;
					oldpt20->matrixTransform(inverseMagnifyMatrix, &oldpt2);

					CComQIPtr<ILSVGPoint> newpt20;
					newpt20.CoCreateInstance(CLSID_LSVGPoint);
					newpt20->put_x(pt.x);
					newpt20->put_y(pt.y);
					CComQIPtr<ILSVGPoint> newpt2;
					newpt20->matrixTransform(inverseMagnifyMatrix, &newpt2);

					for (int i = 0; i < pDocument->m_targetElements.GetSize(); i++)
					{
						CElementImpl* pElement = pDocument->m_targetElements[i];

						CComQIPtr<ILSVGTransformable> transformable = pElement->m_domElement;
						if (transformable)
						{
							CComQIPtr<ILSVGMatrix> matrix;
							transformable->getScreenCTM(&matrix);

							CComQIPtr<ILSVGMatrix> inversematrix;
							matrix->inverse(&inversematrix);

							CComQIPtr<ILSVGPoint> xnewpt2;
							newpt2->matrixTransform(inversematrix, &xnewpt2);

							CComQIPtr<ILSVGPoint> xoldpt2;
							oldpt2->matrixTransform(inversematrix, &xoldpt2);

							if (m_hit == 1)
							{
								double xnewpt2_x; xnewpt2->get_x(&xnewpt2_x);
								double xnewpt2_y; xnewpt2->get_y(&xnewpt2_y);

								double xoldpt2_x; xoldpt2->get_x(&xoldpt2_x);
								double xoldpt2_y; xoldpt2->get_y(&xoldpt2_y);

								pElement->Move(xnewpt2_x-xoldpt2_x, xnewpt2_y-xoldpt2_y);
							}
							else
							{
								/*
								SVGLib::ISVGPointPtr centersvgpt("SVG.SVGPoint");
								centersvgpt->x = m_centerPt.x;
								centersvgpt->y = m_centerPt.y;

								SVGLib::ISVGPointPtr icentersvgpt = centersvgpt->matrixTransform(imatrix);

								float cx = icentersvgpt->x;//m_centerPt.x;
								float cy = icentersvgpt->y;//m_centerPt.y;

								float sx = (isvgpt->x - icentersvgpt->x)/(ioldsvgpt->x - icentersvgpt->x);
								float sy = (isvgpt->y - icentersvgpt->y)/(ioldsvgpt->y - icentersvgpt->y);

								pActiveElement->Scale(cx, cy, sx, sy);
								*/
							}
						}

					//	pActiveElement->DrawBBox(hDC);
					//	EndPath(hDC);

					//	StrokePath(hDC);
					}
				}
				break;

			case ID_SVGTOOL_DIRECT:
				{
					if (m_hit == 0)	// Selection Rectangle
					{
					//	DrawFocusRect(hDC, m_startpt.x, m_startpt.y, m_oldpt.x, m_oldpt.y);
					//	DrawFocusRect(hDC, m_startpt.x, m_startpt.y, pt.x, pt.y);
					}
					else
					{
						if (m_curveCp >= 0)
						{
							CComQIPtr<ILSVGPoint> oldpt20;
							oldpt20.CoCreateInstance(CLSID_LSVGPoint);
							oldpt20->put_x(m_oldpt.x);
							oldpt20->put_y(m_oldpt.y);
							CComQIPtr<ILSVGPoint> oldpt2;
							oldpt20->matrixTransform(inverseMagnifyMatrix, &oldpt2);

							CComQIPtr<ILSVGPoint> newpt20;
							newpt20.CoCreateInstance(CLSID_LSVGPoint);
							newpt20->put_x(pt.x);
							newpt20->put_y(pt.y);
							CComQIPtr<ILSVGPoint> newpt2;
							newpt20->matrixTransform(inverseMagnifyMatrix, &newpt2);

							if (m_curveCtl == 0)	// Clicked on anchor point
							{
								for (int i = 0; i < pDocument->m_targetElements.GetSize(); i++)
								{
									CElementImpl* pElement = pDocument->m_targetElements[i];

									BSTR btagName;
									pElement->m_domElement->get_nodeName(&btagName);
									_bstr_t tagName = _bstr_t(btagName, false);

									if (!wcscmp(tagName, L"path"))
									{
										CPathElement* pathElement = (CPathElement*)pElement;

										CComQIPtr<ILSVGTransformable> transformable = pathElement->m_domElement;
										
										CComQIPtr<ILSVGMatrix> matrix;
										transformable->getScreenCTM(&matrix);

										CComQIPtr<ILSVGMatrix> inversematrix;
										matrix->inverse(&inversematrix);

										CComQIPtr<ILSVGPoint> xnewpt2;
										newpt2->matrixTransform(inversematrix, &xnewpt2);

										CComQIPtr<ILSVGPoint> xoldpt2;
										oldpt2->matrixTransform(inversematrix, &xoldpt2);

										CComQIPtr<ILSVGPathSegList> seglist = GetPathSegList(pathElement);

										double xnewpt2x; xnewpt2->get_x(&xnewpt2x);
										double xnewpt2y; xnewpt2->get_y(&xnewpt2y);
										
										double xoldpt2x; xoldpt2->get_x(&xoldpt2x);
										double xoldpt2y; xoldpt2->get_y(&xoldpt2y);

										pathElement->MovePoints(seglist, xnewpt2x-xoldpt2x, xnewpt2y-xoldpt2y, FALSE);
										
										PutPathSegList(pElement, seglist);
									}
								}
							}
							else	// Control point
							{
								CPathElement* pathElement = (CPathElement*)pActiveElement;

								CComQIPtr<ILSVGTransformable> transformable = pathElement->m_domElement;

								CComQIPtr<ILSVGMatrix> matrix;
								transformable->getScreenCTM(&matrix);

								CComQIPtr<ILSVGMatrix> inversematrix;
								matrix->inverse(&inversematrix);

								CComQIPtr<ILSVGPoint> xnewpt2;
								newpt2->matrixTransform(inversematrix, &xnewpt2);

								CComQIPtr<ILSVGPoint> xoldpt2;
								oldpt2->matrixTransform(inversematrix, &xoldpt2);

								CComQIPtr<ILSVGPathSegList> seglist = GetPathSegList(pathElement);

								double xnewpt2x; xnewpt2->get_x(&xnewpt2x);
								double xnewpt2y; xnewpt2->get_y(&xnewpt2y);

								pathElement->SetPathSegControlPoints(seglist, m_curveCp, m_curveCtl, xnewpt2x, xnewpt2y);
							}

							InvalidateRect(NULL, TRUE);
							UpdateWindow();
						}
						else
						{
							MessageBeep(-1);
						}
					}
				}
				break;

			case ID_SVGTOOL_PATHPEN:
			case TOOL_PENCORNER:
				{
					CPathElement* pathElement = (CPathElement*)pActiveElement;

					double x = pt.x;
					double y = pt.y;

					CComQIPtr<ILSVGAnimatedPathData> pathData = pathElement->m_domElement;

					CComQIPtr<ILSVGPathSegList> seglist;
					pathData->get_normalizedPathSegList(&seglist);

					if (m_hit == 1)
					{
						pathElement->SetPathSegControlPointsSameLength(seglist, m_curveCp, m_curveCtl, x, y);
					}
					else
					{
						pathElement->SetPathSegControlPoint(seglist, m_curveCp, m_curveCtl, x, y);
					}

					InvalidateRect(NULL, TRUE);
					UpdateWindow();
				}
				break;
				
			case TOOL_PENFREE:
				{
					m_pointArray.Add(CDblPoint(pt.x, pt.y));
					
					int size = m_pointArray.GetSize();
					
				//	MoveToEx(hDC, m_pointArray[size-2].x, m_pointArray[size-2].y, NULL);
				//	LineTo(hDC, m_pointArray[size-1].x, m_pointArray[size-1].y);
				}
				break;

			case TOOL_TEXT:
				{
					if (m_pTextElement)
					{
						CComQIPtr<ILSVGTextElement> text = m_pTextElement->m_domElement;

						long charpos;
						text->getCharNumAtPosition(svgpt, &charpos);

						if (charpos >= 0)
						{
							m_cursorPos = charpos;

							if (charpos < m_initSelCharPos)
							{
								m_startSelCharPos = charpos;
								m_endSelCharPos = m_initSelCharPos;
							}
							else
							{
								m_endSelCharPos = charpos;
								m_startSelCharPos = m_initSelCharPos;
							}

							text->selectSubString(m_startSelCharPos, m_endSelCharPos - m_startSelCharPos+1);

							InvalidateRect(NULL, TRUE);
							UpdateWindow();
						}
					}
				}
				break;

			case TOOL_TRANSFORM:
				{
#if 0
					for (int i = 0; i < m_pDocument->m_targetElements.GetSize(); i++)
					{
						CElement* pElement = m_pDocument->m_targetElements[i];

					//	pElement->DrawBBox(hDC);

						SVGLib::ISVGTransformPtr transform = pElement->GetMatrixTransform();

						if (transform)
						{
						}
					}
#endif
				}
				break;

			case TOOL_ROTATE:
			case TOOL_SCALE:
			case TOOL_SKEW:
				{
					if (m_hit == 1)
					{
					//	BeginPath(hDC);
					//	DrawTargetElementsPathCurves(hDC);

						for (int i = 0; i < pDocument->m_targetElements.GetSize(); i++)
						{
							CElementImpl* pElement = pDocument->m_targetElements[i];

							CComQIPtr<ILSVGTransform> transform = pElement->GetMatrixTransform();

							if (transform)
							{
								float cx = m_pivotPt.x;
								float cy = m_pivotPt.y;

								if (gApp->m_svgActiveTool == TOOL_ROTATE)
								{
									double oldangleX;
									{
										double dx = m_oldpt.x - cx;
										double dy = m_oldpt.y - cy;

										double distance = sqrt(dx*dx + dy*dy);
										double distance2 = distance;

										if (distance2 == 0.0) distance2 = 0.00001;
										if (dy < 0) distance2 =-distance2;
										double angle = acos(dx/distance2);
										if (dy < 0) angle += M_PI;

										oldangleX = angle * 180/M_PI;
									}

									double angleX;
									{
										double dx = pt.x - cx;
										double dy = pt.y - cy;

										double distance = sqrt(dx*dx + dy*dy);
										double distance2 = distance;

										if (distance2 == 0.0) distance2 = 0.00001;
										if (dy < 0) distance2 =-distance2;
										double angle = acos(dx/distance2);
										if (dy < 0) angle += M_PI;

										angleX = angle * 180/M_PI;
									}

								//	transform->setMatrix(transform->matrix->translate(-cx, -cy)->rotate(angleX-oldangleX)->translate(cx, cy));

									CComQIPtr<ILSVGMatrix> mat0;
									transform->get_matrix(&mat0);

									CComQIPtr<ILSVGMatrix> mat1;
									mat0->translate(-cx, -cy, &mat1);

									CComQIPtr<ILSVGMatrix> mat2;
									mat1->rotate(angleX-oldangleX, &mat2);

									CComQIPtr<ILSVGMatrix> mat3;
									mat2->translate(cx, cy, &mat3);
									
									transform->setMatrix(mat3);
								}
								else if (gApp->m_svgActiveTool == TOOL_SCALE)
								{
									float sx = (pt.x - cx)/(m_oldpt.x - cx);
									float sy = (pt.y - cy)/(m_oldpt.y - cy);

								//	transform->setMatrix(transform->matrix->translate(-cx, -cy)->scaleNonUniform(sx, sy)->translate(cx, cy));

									CComQIPtr<ILSVGMatrix> mat0;
									transform->get_matrix(&mat0);

									CComQIPtr<ILSVGMatrix> mat1;
									mat0->translate(-cx, -cy, &mat1);

									CComQIPtr<ILSVGMatrix> mat2;
									mat1->scaleNonUniform(sx, sy, &mat2);

									CComQIPtr<ILSVGMatrix> mat3;
									mat2->translate(cx, cy, &mat3);

									transform->setMatrix(mat3);
								}
								else if (gApp->m_svgActiveTool == TOOL_SKEW)
								{
#if 0
									double oldangleX;
									{
										double dx = m_oldpt.x - m_pivotPt.x;
										double dy = m_startpt.y - m_pivotPt.y;

										double distance = sqrt(dx*dx + dy*dy);
										double distance2 = distance;

										if (distance2 == 0.0) distance2 = 0.00001;
										if (dy < 0) distance2 =-distance2;
										double angle = acos(dx/distance2);
										if (dy < 0) angle += M_PI;

										oldangleX = 90 - (angle * 180/M_PI);
									}

									double angleX;
									{
										double dx = pt.x - m_pivotPt.x;
										double dy = m_startpt.y - m_pivotPt.y;

										double distance = sqrt(dx*dx + dy*dy);
										double distance2 = distance;

										if (distance2 == 0.0) distance2 = 0.00001;
										if (dy < 0) distance2 =-distance2;
										double angle = acos(dx/distance2);
										if (dy < 0) angle += M_PI;

										angleX = 90 - (angle * 180/M_PI);
									}

									TRACE("angle: %g\n", angleX);

									/*
									double oldangleY;
									{
										double dx = m_startpt.x - pActiveElement->m_pivot.x;
										double dy = m_oldpt.y - pActiveElement->m_pivot.y;

										double distance = sqrt(dx*dx + dy*dy);
										double distance2 = distance;

										if (distance2 == 0.0) distance2 = 0.00001;
										if (dy < 0) distance2 =-distance2;
										double angle = asin(dy/distance2);
										if (dy < 0) angle += M_PI;

										oldangleY = angle * 180/M_PI;
									}

									double angleY;
									{
										double dx = m_startpt.x - pActiveElement->m_pivot.x;
										double dy = pt.y - pActiveElement->m_pivot.y;

										double distance = sqrt(dx*dx + dy*dy);
										double distance2 = distance;

										if (distance2 == 0.0) distance2 = 0.00001;
										if (dy < 0) distance2 =-distance2;
										double angle = asin(dy/distance2);
										if (dy < 0) angle += M_PI;

										angleY = angle * 180/M_PI;
									}
									*/

								//	TRACE("%g\n", angleX-oldangleX);

									if (transform)
									{
										transform->setMatrix(pElement->m_initialMatrix->translate(0, -m_pivotPt.y)->skewX(angleX)->translate(0, m_pivotPt.y));
									//	transform->setMatrix(transform->matrix->translate(0, -m_pivotPt.y)->skewX((angleX-oldangleX))->translate(0, m_pivotPt.y));

										//	transform->setMatrix(transform->matrix->translate(-m_pivotPt.x, 0)->skewY(oldangleY-angleY)->translate(m_pivotPt.x, 0));
									}
#endif
								}
							}
							else
							{
								MessageBeep(-1);
							}

						//	pElement->DrawBBox(hDC, &m_drawSession);
						}

					//	DrawTargetElementsPathCurves(hDC);
					}
					else if (m_hit == 2)	// Pivot point
					{
						m_pivotPt.x = pt.x;
						m_pivotPt.y = pt.y;

						/*
						{
							float x = m_pivotPt.x;
							float y = m_pivotPt.y;

							HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
							m_drawSession.Ellipse(hDC, x-4, y-4, x+5, y+5);
							SelectObject(hDC, hOldBrush);
						}
						*/
					}

					InvalidateRect(NULL, TRUE);
					UpdateWindow();
				}
				break;

			case TOOL_TWIRL:
				{
#if 0
					if (m_hit == 1)
					{
						for (int i = 0; i < m_pDocument->m_targetElements.GetSize(); i++)
						{
							CElement* pElement = m_pDocument->m_targetElements[i];

							if (!wcscmp(pElement->m_domElement->tagName, L"path"))
							{
								CPathElement* pathElement = (CPathElement*)pElement;

							//	pathElement->DrawPolyPoints(hDC);

								pathElement->SetPolyPointsFromSegList();

							//	SVGLib::ISVGTransformPtr transform = pElement->GetMatrixTransform();

								double cx = m_pivotPt.x;
								double cy = m_pivotPt.y;

								double dangle;
								{
									static double doldvalue = 0;
									static double g_oldValue = 0;

									double radian;

									double dx = (double)(pt.x-cx);
									double dy = (double)(pt.y-cy);
									double distance = sqrt(dx*dx+dy*dy);
									double distance2 = distance;

									if (distance2 == 0.0) distance2 = 0.0001;
									radian = acos(dx/distance2);
									if (dy < 0) radian = M_PI*2 - radian;

									double dvalue = radian;//*(180.0/M_PI);

								//	long loldvalue;
								//	m_pProp->GetParamTags((PARAM_ANGLE_Value), &loldvalue, (TAG_DONE));

									if (m_numMoves == 0)
									{
										g_oldValue = radian;
										doldvalue = radian;
									//	g_oldValue = doldvalue;
									//	while (g_oldValue < 0) g_oldValue += M_PI*2;
									//	while (g_oldValue >= M_PI*2) g_oldValue -= M_PI*2;
									}

								//	double doldvalue = g_oldValue;//loldvalue/65536.0;

									double delta = dvalue - g_oldValue;

									if (delta < -M_PI)
									{
										delta = dvalue + (M_PI*2-g_oldValue);
									}
									else if (delta > M_PI)
									{
										delta = dvalue - g_oldValue - M_PI*2;
									}

									g_oldValue = dvalue;

									dvalue = doldvalue + delta;

									doldvalue = dvalue;

									dangle = dvalue;
								}

								/*
								double dangle;
								{
									double dx = pt.x - m_startpt.x;
									double dy = pt.y - m_startpt.y;

									double distance = sqrt(dx*dx + dy*dy);
									double distance2 = distance;

									if (distance2 == 0.0) distance2 = 0.00001;
									if (dy < 0) distance2 =-distance2;
									double angle = acos(dx/distance2);
									if (dy < 0) angle += M_PI;

									dangle = angle;// * 180/M_PI;
								}
								*/

								double maxdistance = m_effectRadius;

								int numpoints = pathElement->m_flatPoints.GetSize();
								DblPOINT* points = pathElement->m_flatPoints.GetData();

								for (int i = 0; i < numpoints; i++)
								{
									double dx = points[i].x-cx;
									double dy = points[i].y-cy;

									double distance = sqrt(dx*dx + dy*dy);

									if (distance < maxdistance)
									{
										if (distance == 0.0) distance = 0.01;

										double angle = acos(dx/distance);
										if (dy < 0) angle = M_PI*2 - angle;

										double addangle;
										addangle = ((maxdistance-distance)/maxdistance)*dangle;

										angle += addangle;

										double x2 = cos(angle)*distance;
										double y2 = sin(angle)*distance;

										points[i].x = x2 + cx;
										points[i].y = y2 + cy;
									}
									else
									{
									}
								}

							//	pathElement->DrawPolyPoints(hDC);
							}
						}
					}
					else
					{
						if (m_hit == 2)
						{
							m_pivotPt.x = pt.x;
							m_pivotPt.y = pt.y;
						}
						else if (m_hit == 3)
						{
							double dx = pt.x - m_pivotPt.x;
							double dy = pt.y - m_pivotPt.y;

							m_effectRadius = sqrt(dx*dx + dy*dy);
						}

						/*
						{
							float x = m_pivotPt.x;
							float y = m_pivotPt.y;

							HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
							Ellipse(hDC, x-4, y-4, x+5, y+5);
							Ellipse(hDC, x-m_effectRadius, y-m_effectRadius, x+m_effectRadius, y+m_effectRadius);
							SelectObject(hDC, hOldBrush);
						}
						*/
					}
#endif
				}
				break;
	
			case ID_SVGTOOL_CIRCLE:
				{
				//	Ellipse(hDC, m_startpt.x-m_radius, m_startpt.y-m_radius, m_startpt.x + m_radius+1, m_startpt.y + m_radius+1);

					float dx = m_oldpt.x - m_startpt.x;
					float dy = m_oldpt.y - m_startpt.y;
					
					m_radius = sqrt(dx*dx + dy*dy);
					
				//	Ellipse(hDC, m_startpt.x-m_radius, m_startpt.y-m_radius, m_startpt.x + m_radius+1, m_startpt.y + m_radius+1);
					InvalidateRect(NULL, TRUE);
					UpdateWindow();
				}
				break;
				
			case ID_SVGTOOL_ELLIPSE:
				{
				//	Ellipse(hDC, m_startpt.x, m_startpt.y, m_oldpt.x, m_oldpt.y);
				//	Ellipse(hDC, m_startpt.x, m_startpt.y, pt.x, pt.y);
					InvalidateRect(NULL, TRUE);
					UpdateWindow();
				}
				break;

			case TOOL_RECT:
				{
#if 0
					SVGLib::ISVGRectElementPtr rect = gApp->m_rectSettings->m_domElement;
					int ewidth = rect->rx->baseVal->value*2;
					int eheight = rect->ry->baseVal->value*2;

				//	RoundRect(hDC, m_startpt.x, m_startpt.y, m_oldpt.x, m_oldpt.y, ewidth, eheight);
				//	RoundRect(hDC, m_startpt.x, m_startpt.y, pt.x, pt.y, ewidth, eheight);
#endif
				}
				break;

			case ID_SVGTOOL_LINE:
				{
				//	DrawLine(hDC, m_startpt.x, m_startpt.y, pt.x, pt.y);

				/*
					MoveToEx(hDC, m_startpt.x, m_startpt.y, NULL);
					LineTo(hDC, m_oldpt.x, m_oldpt.y);

					MoveToEx(hDC, m_startpt.x, m_startpt.y, NULL);
					LineTo(hDC, pt.x, pt.y);
				*/
				}
				break;

			case TOOL_ZOOM:
				{
#if 0
					HDC hDC = GetDC(hwnd);
					IntersectClipRect(hDC, m_imageRect.left, m_imageRect.top, m_imageRect.right, m_imageRect.bottom);
					POINT org;
					org.x = m_imageRect.left + m_offset.x-scrollposX;
					org.y = m_imageRect.left + m_offset.y-scrollposY;
					POINT oldOrg;
					SetViewportOrgEx(hDC, org.x, org.y, &oldOrg);

					int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
					HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

				// Erase old zoomrect
					Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

					double aspect = (double)m_imageRect.Height()/m_imageRect.Width();

					m_zoomRect.left = m_startpt.x;
					m_zoomRect.top = m_startpt.y;
					if ((double)abs(pt.x-m_startpt.x)/m_imageRect.Width() > (double)abs(pt.y-m_startpt.y)/m_imageRect.Height())
					{
						double aspect = (double)m_imageRect.Height()/m_imageRect.Width();
						m_zoomRect.right = pt.x;
						m_zoomRect.bottom = m_startpt.y + (pt.x-m_startpt.x)*aspect;
					}
					else
					{
						double aspect = (double)m_imageRect.Width()/m_imageRect.Height();
						m_zoomRect.right = m_startpt.x + (pt.y-m_startpt.y)*aspect;
						m_zoomRect.bottom = pt.y;
					}

				// Draw new zoomrect
					Rectangle(hDC, m_zoomRect.left, m_zoomRect.top, m_zoomRect.right, m_zoomRect.bottom);

					SelectObject(hDC, hOldBrush);
					SetROP2(hDC, oldR2);

					SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
					ReleaseDC(hwnd, hDC);
#endif
				}
				break;

			case TOOL_HAND:
				{
					long posx = 0;// m_horz->get_pos(&posx);
					long posy = 0;// m_vert->get_pos(&posy);

					POINT pt = point;
					pt.x -= m_offset.x;
					pt.y -= m_offset.y;

					long newposx = m_startpt.x - pt.x;
					long newposy = m_startpt.y - pt.y;

					setScrollposXY(newposx, newposy);
				}
				break;
			}

			m_oldpt = pt;

			m_numMoves++;
		}
	}
}

HRESULT CWebEditControl::SetCursor(LONG x, LONG y, VARIANT_BOOL * bHandled)
{
	*bHandled = VARIANT_FALSE;

	POINT point;
	point.x = x;
	point.y = y;

	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);
	CComQIPtr<ILDOMDocument> domdocument = pDocument->GetDOMDocument();

	CComQIPtr<ILSVGDocument> svgDocument = domdocument;
	if (svgDocument)
	{
		switch (gApp->m_svgActiveTool)
		{
		case TOOL_ZOOM:
			{
				::SetCursor(LoadCursor(_Module.m_hInst, MAKEINTRESOURCE(IDC_ZOOM)));
				*bHandled = VARIANT_TRUE;
			}
			break;

		case TOOL_HAND:
			{
				::SetCursor(LoadCursor(_Module.m_hInst, MAKEINTRESOURCE(IDC_HAND)));
				*bHandled = VARIANT_TRUE;
			}
			break;
		}
	}

	return S_OK;
}

void CWebEditControl::InvalidateInvalidRect()
{
	InvalidateRect(NULL, TRUE);
#if 0
	SVGLib::ISVGSVGElementPtr svg = m_pDocument->GetDOMDocument()->documentElement;
	SVGLib::_tagSVGRect svgrect = svg->getInvalidBox();

	UpdateRect(svgrect);
#endif
}

void CWebEditControl::DrawTargetElementsPathCurves(HDC hDC)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	for (int i = 0; i < pDocument->m_targetElements.GetSize(); i++)
	{
		CElementImpl* pElement = pDocument->m_targetElements[i];
//		pElement->DrawPathCurve(pGraphics, m_magnifyMatrix);
	}
}

ILDOMText* MapCursorPos(ILSVGTextContentElement* textel, int cursorPos, int& newCursorPos)
{
	int ncharsSoFar = 0;

	CComPtr<ILDOMNode> node;
	textel->get_firstChild(&node);

	while (node != NULL)
	{
		LDOMNodeType nodeType;
		node->get_nodeType(&nodeType);

		if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<ILSVGTextContentElement> textContent = node;
			if (textContent != NULL)
			{
				ILDOMText* ftext = MapCursorPos(textContent, cursorPos-ncharsSoFar, newCursorPos);
				if (ftext != NULL)
				{
					return ftext;
				}

				long numberOfChars;
				textContent->getNumberOfChars(&numberOfChars);

				ncharsSoFar += numberOfChars;
			}
		}
		else if (nodeType == LNODE_TEXT)
		{
			CComQIPtr<ILDOMText> text = node;

			BSTR textdata;
			text->get_data(&textdata);

			int len = SysStringLen(textdata);
			SysFreeString(textdata);

			if (cursorPos < ncharsSoFar+len)
			{
				newCursorPos = cursorPos - ncharsSoFar;
				return text;
			}

			ncharsSoFar += len;
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return NULL;
}

long CWebEditControl::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLTRACE("OnKeydown\n");

	int nKey = (int) wParam;
	int lKeyData = lParam;
 
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	CComQIPtr<ILDOMDocument> doc;
	m_pDocument->get_DOMDocument(&doc);

	CComQIPtr<ILSVGDocument> svgdoc = doc;
	if (svgdoc)
	{
		CComQIPtr<ILSVGSVGElement> svg;
		svgdoc->get_documentElement((ILDOMElement**)&svg);
		ASSERT(svg != NULL);

	//	SVGLib::ISVGSVGElementPtr svg = m_pDocument->GetDOMDocument()->documentElement;

		if (gApp->m_svgActiveTool == TOOL_TEXT && m_pTextElement != NULL)
		{
			LONG bShift = (GetAsyncKeyState(VK_SHIFT) & (1<<15));

			CComQIPtr<ILSVGTextElement> text = m_pTextElement->m_domElement;

			switch (nKey)
			{
			case VK_LEFT:
			case VK_RIGHT:
			case VK_PRIOR:
			case VK_NEXT:
				{
					if (bShift)
					{
						if (m_initSelCharPos == -1)	// Starting new selection
						{
							m_initSelCharPos = m_cursorPos;
						}
					}
					else
					{
						svg->deSelectAll();

						m_initSelCharPos = -1;
						m_startSelCharPos = 0;
						m_endSelCharPos = -1;
					}

					switch (nKey)
					{
						case VK_LEFT:
							{
								if (m_cursorPos > 0)
									m_cursorPos--;
							}
							break;

						case VK_RIGHT:
							{
								long numberOfChars;
								text->getNumberOfChars(&numberOfChars);

								if (m_cursorPos < numberOfChars)
									m_cursorPos++;
							}
							break;

						case VK_PRIOR:
							{
								if (m_cursorPos > 0)
									m_cursorPos = 0;
							}
							break;

						case VK_NEXT:
							{
								long numberOfChars;
								text->getNumberOfChars(&numberOfChars);

								if (m_cursorPos < numberOfChars)
									m_cursorPos = numberOfChars;
							}
							break;
					}

					if (bShift)
					{
						if (m_cursorPos < m_initSelCharPos)
						{
							m_startSelCharPos = m_cursorPos;
							m_endSelCharPos = m_initSelCharPos;
						}
						else
						{
							m_endSelCharPos = m_cursorPos;
							m_startSelCharPos = m_initSelCharPos;
						}

						text->selectSubString(m_startSelCharPos, m_endSelCharPos - m_startSelCharPos+1);
					//	SetSelectionAndInvalidate(m_initSel, m_offset);
					}

					InvalidateRect(NULL, TRUE);
				}
				break;

			case VK_BACK:
					if (m_cursorPos > 0)
					{
						m_cursorPos--;
					}
					else
					{
						break;
					}

			case VK_DELETE:
				{
					long numberOfChars;
					text->getNumberOfChars(&numberOfChars);

					if (m_cursorPos < numberOfChars)
					{
						CComQIPtr<ILSVGTextElement> textel = m_pTextElement->m_domElement;

						int deleteAt;
						CComQIPtr<ILDOMText> textnode = MapCursorPos(textel, m_cursorPos, deleteAt);
						ATLASSERT(textnode != NULL);

						textnode->deleteData(deleteAt, 1);

	#if 0
						if (_bstr_t(textnode->data).length() == 0)
						{
						// TODO, delete textnode
						// TODO, if no more elements in parent element, delete that as well unless text element
						}
	#endif

						InvalidateRect(NULL, TRUE);
					}
				}
				break;

			default:
				return 0;//HANDLE_BASE<IHTMLControl>(m_puiwnd, uMsg, wParam, lParam);
			}
		}
		else
		{
			return 0;//HANDLE_BASE<IHTMLControl>(m_puiwnd, uMsg, wParam, lParam);
		}
	}
	else
	{
		return 0;//HANDLE_BASE<IHTMLControl>(m_puiwnd, uMsg, wParam, lParam);
	}

	return 0;
}

long CWebEditControl::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLTRACE("OnChar\n");

	TCHAR nKey = (TCHAR) wParam;
	int lKeyData = lParam;

	if (nKey == 8) return 0;
	if (nKey == '\r') nKey = '\n';

	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	CComQIPtr<ILDOMDocument> doc;
	m_pDocument->get_DOMDocument(&doc);

	CComQIPtr<ILSVGDocument> svgdoc = doc;
	if (svgdoc)
	{
		CComQIPtr<ILSVGSVGElement> svg;
		svgdoc->get_documentElement((ILDOMElement**)&svg);
		ASSERT(svg != NULL);

		if (m_pTextElement)
		{
			CComQIPtr<ILSVGTextElement> textel = m_pTextElement->m_domElement;

			int insertAt;
			CComQIPtr<ILDOMText> textnode = MapCursorPos(textel, m_cursorPos, insertAt);
			ATLASSERT(textnode != NULL);

			WCHAR c2[2] = {nKey, 0};
			textnode->insertData(insertAt, c2);
			m_cursorPos++;
		}
	}
	else
	{
		return 0;//HANDLE_BASE<IHTMLControl>(m_puiwnd, uMsg, wParam, lParam);
	}

	return 0;
}

HRESULT __stdcall CWebEditControl::OnActivatedObject(IUnknown* object)
{
	CComQIPtr<IWebElement> element;
	CComQIPtr<ILDOMNode> domelement;

	if (element = object)
	{
		InvalidateRect(NULL, TRUE);
	}
	else if (domelement = object)
	{
		CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

		CElementImpl* pPElement = pDocument->m_pTree->FindDOMElement(domelement);
		if (pPElement)
		{
			pDocument->SetTargetElement(pPElement, 0);

		/*
			CComQIPtr<IUIContextManager> uiManager;
			gApp->get_uiManager(&uiManager);

			IUnknown* unk;
			pPElement->QueryInterface(IID_IUnknown, (void**)&unk);

			uiManager->ActivateObject(unk);
			//unk->Release();
		*/
		}
	}

	return S_OK;
}

HRESULT __stdcall CWebEditControl::OnDeactivatedObject(IUnknown* object)
{
	CComQIPtr<IWebElement> element;
	CComQIPtr<ILDOMNode> domelement;

	if (element = object)
	{
		InvalidateRect(NULL, TRUE);
	}
	else if (domelement = object)
	{
		CComQIPtr<IUIManager> uiManager = gApp->m_frame;

		CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);
		CElementImpl* pPElement = pDocument->m_pTree->FindDOMElement(domelement);
		if (pPElement)
		{
			IUnknown* unk;
			pPElement->QueryInterface(IID_IUnknown, (void**)&unk);

			uiManager->ActivateObject(NULL, unk);
			//unk->Release();
		}
	}

	return S_OK;
}

HRESULT __stdcall CWebEditControl::OnDOMEvent(ILDOMEvent* evt)
{
//	SVGLib::IDOMMutationEventPtr pEvt = evt;

#if 0
	if (m_pDocument->m_bPlaying)
	{
		InvalidateInvalidRect();
	}
	else
#endif
	{
		if (m_dragging)
		{
			if (TRUE/*!gApp->m_bFastFB*/)
			{
				InvalidateInvalidRect();
			}
		}
		else
		{
			OnSize();

			if (evt)
			{
				InvalidateInvalidRect();
			}
			else
			{
				InvalidateRect(NULL, TRUE);
			}
		}
	}

	return S_OK;
}

STDMETHODIMP CWebEditControl::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;
	return S_OK;
}

STDMETHODIMP CWebEditControl::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;

#if 0
// Call base
	CComQIPtr<IDropTarget> basetarget = m_puiwnd;
	return basetarget->DragOver(grfKeyState, pt, pdwEffect);
#endif

	return S_OK;
}

STDMETHODIMP CWebEditControl::DragLeave()
{
	return S_OK;
}

STDMETHODIMP CWebEditControl::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

#if 0
	POINT point;
	point.x = ptl.x;
	point.y = ptl.y;
	ScreenToClient(&point);

	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	POINT pt = point;
	pt.x -= m_offset.x;
	pt.y -= m_offset.y;
	pt.x += scrollposX;
	pt.y += scrollposY;

	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	CComQIPtr<IDOMDocument> doc = pDocument->GetDOMDocument();
	
	CComQIPtr<ISVGDocument> svgdoc = doc;
	if (svgdoc)
	{
		CComQIPtr<ISVGSVGElement> svg;
		svgdoc->get_documentElement((IDOMElement**)&svg);

		if (svg)
		{
			COleDataObject dataObject;
			dataObject.Attach(pDataObject);

			HGLOBAL hData;

			if (hData = dataObject.GetGlobalData(CF_HDROP))
			{
				DROPFILES* dp = (DROPFILES*)GlobalLock(hData);
				if (dp)
				{
					char* p = (char*)(dp+1);

					int i = 0;
					TCHAR filename[512];
					while (*p)
					{
						filename[i++] = *p++;
					}
					filename[i] = 0;

					CComQIPtr<ISVGImageElement> image;
					pDocument->GetDOMDocument()->createElement(L"image", (IDOMElement**)&image);
					image->setAttribute(L"xlink:href", _bstr_t(filename));

					// x
					{
						CComQIPtr<ISVGAnimatedLength> alength;
						image->get_x(&alength);
						CComQIPtr<ISVGLength> length;
						alength->get_baseVal(&length);
						length->put_value(pt.x);
					}

					// y
					{
						CComQIPtr<ISVGAnimatedLength> alength;
						image->get_y(&alength);
						CComQIPtr<ISVGLength> length;
						alength->get_baseVal(&length);
						length->put_value(pt.y);
					}

					// width
					{
						CComQIPtr<ISVGAnimatedLength> alength;
						image->get_width(&alength);
						CComQIPtr<ISVGLength> length;
						alength->get_baseVal(&length);
						length->put_value(200);
					}

					// height
					{
						CComQIPtr<ISVGAnimatedLength> alength;
						image->get_height(&alength);
						CComQIPtr<ISVGLength> length;
						alength->get_baseVal(&length);
						length->put_value(200);
					}

					svg->appendChild(image, NULL);

					GlobalUnlock(hData);
				}

				*pdwEffect = DROPEFFECT_COPY;
			}
		}
	}

	if (*pdwEffect == DROPEFFECT_NONE)
	{
	// Call base
		CComQIPtr<IDropTarget> basetarget = m_puiwnd;
		return basetarget->Drop(pDataObject, grfKeyState, ptl, pdwEffect);
	}
#endif

	return S_OK;
}

STDMETHODIMP CWebEditControl::get_currentScale(double *pVal)
{
	*pVal = m_magnify;
	return S_OK;
}

STDMETHODIMP CWebEditControl::put_currentScale(double newVal)
{
	m_magnify = newVal;
	m_magnifyMatrix->put_a(m_magnify);
	m_magnifyMatrix->put_d(m_magnify);

	OnSize();
	InvalidateRect(NULL, TRUE);

	Fire_changeviewbox();

	return S_OK;
}

STDMETHODIMP CWebEditControl::get_scrollposX(long *pVal)
{
//	m_horz->get_pos(pVal);
	return S_OK;
}

STDMETHODIMP CWebEditControl::put_scrollposX(long newVal)
{
//	long posy; m_vert->get_pos(&posy);
//	setScrollposXY(newVal, posy);

	return S_OK;
}

STDMETHODIMP CWebEditControl::get_scrollposY(long *pVal)
{
//	m_vert->get_pos(pVal);
	return S_OK;
}

STDMETHODIMP CWebEditControl::put_scrollposY(long newVal)
{
//	long posx; m_horz->get_pos(&posx);
//	setScrollposXY(posx, newVal);

	return S_OK;
}

STDMETHODIMP CWebEditControl::setScrollposXY(long posx, long posy)
{
#if 0
	long oldPosX; m_horz->get_pos(&oldPosX);
	long oldPosY; m_vert->get_pos(&oldPosY);

	m_horz->put_pos(posx);
	m_vert->put_pos(posy);

// Retrieve the actual new position, restricted by min/max of scrollbar
	m_horz->get_pos(&posx);
	m_vert->get_pos(&posy);

	HWND hwnd;
	get_hwnd(&hwnd);

	CRect client;
	GetClientRect(&client);

	CRect	rect(0, 0, client.right-16, client.bottom-16);
	
	HDC dc = CreateCompatibleDC(NULL);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(dc, m_hBitmap);
	ScrollDC(dc, oldPosX-posx, oldPosY-posy, NULL, NULL, NULL, NULL);
	SelectObject(dc, hOldBitmap);

	ScrollWindow(hwnd, oldPosX-posx, oldPosY-posy, &rect, &rect);

	Fire_changeviewbox();
#endif

	return S_OK;
}

STDMETHODIMP CWebEditControl::GetViewBox(RECT *pbox)
{
#if 0
	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	int x = -m_imageRect.left + m_offset.x + (scrollposX);// + 200;
	int y = -m_imageRect.top + m_offset.y + (scrollposY);// + 200;
	int width = m_imageRect.Width();
	int height = m_imageRect.Height();

	pbox->left = x / m_magnify;
	pbox->top = y / m_magnify;
	pbox->right = (x + width) / m_magnify;
	pbox->bottom = (y + height) / m_magnify;
#endif

	return S_OK;
}

#if 0
STDMETHODIMP CWebEditControl::get_documentContainer(IDOMDocumentContainer **pVal)
{
	m_htmlControl->get_documentContainer(pVal);
	return S_OK;
}

STDMETHODIMP CWebEditControl::put_documentContainer(IDOMDocumentContainer *newVal)
{
	m_htmlControl->put_documentContainer(newVal);
	return S_OK;
}
#endif

BEGIN_CMD_MAP(CWebEditControl)
// Edit
	CMD_HANDLER(ID_EDIT_CUT, OnEditCut)
	CMD_UPDATE(ID_EDIT_CUT, OnEditCutCopyUpdate)
	CMD_HANDLER(ID_EDIT_COPY, OnEditCopy)
	CMD_UPDATE(ID_EDIT_COPY, OnEditCutCopyUpdate)
	CMD_HANDLER(ID_EDIT_PASTE, OnEditPaste)
	CMD_UPDATE(ID_EDIT_PASTE, OnEditPasteUpdate)
	CMD_HANDLER(ID_EDIT_CLEAR, OnEditDelete)
	CMD_UPDATE(ID_EDIT_CLEAR, OnEditDeleteUpdate)

// Object
/*
	CMD_HANDLER(&ID_OBJECT_GROUP, OnObjectGroup)
	CMD_UPDATE(&ID_OBJECT_GROUP, OnObjectGroupUpdate)
	CMD_HANDLER(&ID_OBJECT_UNGROUP, OnObjectUngroup)
	CMD_UPDATE(&ID_OBJECT_UNGROUP, OnObjectUngroupUpdate)

	CMD_HANDLER(&ID_OBJECT_COMPOUND_MAKE, OnObjectMakeCompound)
	CMD_UPDATE(&ID_OBJECT_COMPOUND_MAKE, OnObjectMakeCompoundUpdate)

// View
	CMD_HANDLER(&ID_VIEW_ZOOMIN, OnViewZoomin)
	CMD_HANDLER(&ID_VIEW_ZOOMOUT, OnViewZoomout)
	CMD_HANDLER(&ID_VIEW_ACTUALSIZE, OnViewActualSize)
*/
END_CMD_MAP()

#include "WEUndoDeleteObjects.h"

LRESULT CWebEditControl::OnEditCut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	pDocument->CopyTargetElementsToClipboard();
	//TODO DeleteTargetElements();

	return 0;
}

LRESULT CWebEditControl::OnEditCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	pDocument->CopyTargetElementsToClipboard();

	return 0;
}

void CWebEditControl::OnEditCutCopyUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	pCmdUI->Enable(pDocument->m_targetElements.GetSize() > 0);
}

LRESULT CWebEditControl::OnEditPaste(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	if (!pDocument->m_pActiveElement)
	{
		MessageBox("You must select an element before pasting", "WebEditor", MB_OK);
		return 0;
	}

	if (::OpenClipboard(NULL))
	{
		HGLOBAL hData = ::GetClipboardData(CF_UNICODETEXT);
		if (hData)
		{
			BSTR p = (BSTR)GlobalLock(hData);
			_bstr_t strdata = _bstr_t(L"<svg>") + _bstr_t(p) + _bstr_t(L"</svg");

			CComQIPtr<ILSVGDocument> xmldoc;
			xmldoc.CoCreateInstance(CLSID_LSVGDocument);

			VARIANT_BOOL success;
			xmldoc->loadXML(strdata, &success);
			if (success)
			{
				CComQIPtr<ILDOMNode>	parentNode;
				CComQIPtr<ILDOMNode> beforeNode;

				// Now decide where in relation to active element to insert the data

				// We check for elements that we know makes sense to paste something into
				// else we assume that the active element eiter don't allow children or
				// that the user don't expect to have children

				BSTR bactiveTagName;
				pDocument->m_pActiveElement->m_domElement->get_nodeName(&bactiveTagName);
				_bstr_t activeTagName = _bstr_t(bactiveTagName);

				if (!wcscmp(activeTagName, L"svg") ||	// This one's for sure
					!wcscmp(activeTagName, L"g") ||
					!wcscmp(activeTagName, L"defs") ||
					!wcscmp(activeTagName, L"a"))
				// Some others.. ?
				{
				// Paste as children under the active element
					parentNode = pDocument->m_pActiveElement->m_domElement;
					//beforeNode = NULL;
				}
				else
				{
				// Paste as siblings after the active element
					pDocument->m_pActiveElement->m_domElement->get_parentNode(&parentNode);
					pDocument->m_pActiveElement->m_domElement->get_nextSibling(&beforeNode);
				}

				pDocument->InsertSVGFragment(xmldoc, parentNode, beforeNode);
			}

			GlobalUnlock(hData);

			pDocument->SetModified(TRUE);
		}
		else
		{
			MessageBox("Couldn't get data from clipboard", "WebEditor", MB_OK);
		}

		::CloseClipboard();
	}
	else
	{
		MessageBox("Couldn't open clipboard", "WebEditor", MB_OK);
	}

	return 0;
}

void CWebEditControl::OnEditPasteUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(IsClipboardFormatAvailable(CF_UNICODETEXT));
}

LRESULT CWebEditControl::OnEditDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

/*
	if (pDocument->m_bSourceEditLast)
	{
	// Remember the source text before any changes to the DOM occurs
		CComQIPtr<ITextDocument> textDocument;
		m_pDocument->get_textDocument(&textDocument);
		BSTR p; textDocument->get_data(&p);
		m_sourceText = SysAllocString(p);	// Make a copy
	}
*/

	CComQIPtr<IOleUndoManager> undoManager;
	pDocument->get_undoManager(&undoManager);

	CWEUndoDeleteObjects* undo = new CWEUndoDeleteObjects;
	undo->AddRef();
	undo->m_pDocument = pDocument;
	undo->m_bSourceEditLast = pDocument->m_bSourceEditLast;
	undo->m_bRedo = true;

	for (int i = 0; i < pDocument->m_targetElements.GetSize(); i++)
	{
		CElement* pElement = (CElement*)pDocument->m_targetElements[i];

		GUID guid;

		CComQIPtr<ILDOMNode> parentNode;
		pElement->m_domElement->get_parentNode(&parentNode);

		CComQIPtr<ILDOMNode> beforeNode;
		pElement->m_domElement->get_nextSibling(&beforeNode);

		pElement->m_domElement->get_uniqID(&guid);
		undo->m_targetElements.Add(guid);

		parentNode->get_uniqID(&guid);
		undo->m_parentElements.Add(guid);

		if (beforeNode != NULL)
		{
			beforeNode->get_uniqID(&guid);
			undo->m_beforeElements.Add(guid);
		}
		else
		{
			undo->m_beforeElements.Add(GUID_NULL);
		}
	}

	undo->Do(undoManager);

	return 0;
}

void CWebEditControl::OnEditDeleteUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);
	pCmdUI->Enable(pDocument->m_targetElements.GetSize() > 0);
}

CElementImpl* CWebEditControl::MakeSelectedCompound()
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	CArray <CPathElement*, CPathElement*> layers;

	for (int i = 0 ; i < pDocument->m_targetElements.GetSize(); i++)
	{
		CPathElement* pLayer = (CPathElement*)pDocument->m_targetElements[i];

		BSTR btagName;
		pLayer->m_domElement->get_nodeName(&btagName);
		_bstr_t tagName = _bstr_t(btagName, false);

		if (!wcscmp(tagName, L"path"))
		{
			layers.Add(pLayer);
		}
	}

	if (layers.GetSize() > 0)
	{
		if (layers.GetSize() > 1)	// More than one must be selected
		{
			CComQIPtr<ILSVGAnimatedPathData> destPathData = layers[0]->m_domElement;
			
			CComQIPtr<ILSVGPathSegList> destSegList;
			destPathData->get_normalizedPathSegList(&destSegList);

			destSegList->LockUpdate();

			for (int i = 1; i < layers.GetSize(); i++)
			{
				CComQIPtr<ILSVGAnimatedPathData> srcPathData = layers[i]->m_domElement;

				CComQIPtr<ILSVGPathSegList> srcSegList;
				srcPathData->get_normalizedPathSegList(&srcSegList);

				unsigned long numberOfItems;
				srcSegList->get_numberOfItems(&numberOfItems);
				for (int j = 0; j < numberOfItems; j++)
				{
					CComQIPtr<ILSVGPathSeg> seg;
					srcSegList->getItem(j, &seg);

					//seg->AddRef();
					destSegList->appendItem(seg, NULL);
				}

			// Remove path element
				CComQIPtr<ILDOMNode> parentNode;
				layers[i]->m_domElement->get_parentNode(&parentNode);
				parentNode->removeChild(layers[i]->m_domElement, NULL);
			}

			destSegList->UnlockUpdate();
		}

		return layers[0];
	}

	return NULL;
}

LRESULT CWebEditControl::OnObjectMakeCompound(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	MakeSelectedCompound();

	return 0;
}

void CWebEditControl::OnObjectMakeCompoundUpdate(long iid, IUICmdUpdate* pCmdUI)
{
}

#include "WEUndoGroupObjects.h"

// hm.. should this be a CWebEditControl method
CElement* CESvgDocument::GroupTargetElements()
{
	CComQIPtr<IOleUndoManager> undoManager;
	/*pDocument->*/get_undoManager(&undoManager);

	CWEUndoGroupObjects* undo = new CWEUndoGroupObjects;
	undo->AddRef();
	undo->m_pDocument = this;//pDocument;
	undo->m_bSourceEditLast = /*pDocument->*/m_bSourceEditLast;
//	undo->m_bRedo = true;

	undo->DoInitial(undoManager);

#if 0
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CElement* pElement = (CElement*)m_targetElements[i];
		GUID guid;
		pElement->m_domElement->get_uniqID(&guid);
		undo->m_targetElements.Add(guid);
	}

	undo->Do(undoManager);

#if 0
	for (int i = 0; i < pDocument->m_targetElements.GetSize(); i++)
	{
		CElement* pElement = (CElement*)pDocument->m_targetElements[i];

		GUID guid;

		CComQIPtr<IDOMNode> parentNode;
		pElement->m_domElement->get_parentNode(&parentNode);

		CComQIPtr<IDOMNode> beforeNode;
		pElement->m_domElement->get_nextSibling(&beforeNode);

		pElement->m_domElement->get_uniqID(&guid);
		undo->m_targetElements.Add(guid);

		parentNode->get_uniqID(&guid);
		undo->m_parentElements.Add(guid);

		if (beforeNode != NULL)
		{
			beforeNode->get_uniqID(&guid);
			undo->m_beforeElements.Add(guid);
		}
		else
		{
			undo->m_beforeElements.Add(GUID_NULL);
		}
	}
#endif

#if 0
	CComQIPtr<IOleUndoManager> undoManager;
	pDocument->get_undoManager(&undoManager);

	if (m_hit == 1)
	{
		CWEUndoGroupObjects* undo = new CWEUndoGroupObjects;
		undo->AddRef();

		undo->m_pDocument = pDocument;
		undo->m_dx = m_oldpt.x-m_startpt.x;
		undo->m_dy = m_oldpt.y-m_startpt.y;
		undo->m_bSourceEditLast = pDocument->m_bSourceEditLast;
		undo->m_sourceText = m_sourceText;


		for (int i = 0; i < pDocument->m_targetElements.GetSize(); i++)
		{
			CElement* pElement = pDocument->m_targetElements[i];

			GUID guid;
			pElement->m_domElement->get_uniqID(&guid);
			undo->m_targetElements.Add(guid);
		}

		undoManager->Add(undo);

		pDocument->m_bSourceEditLast = false;

// We insert the group where the last element is found
// meaning, the topmost selected object decides where the
// group is inserted

	CElement* pParent = (CElement*)m_targetElements[0]->m_parent;

	CArray <CElement*, CElement*> layers;

// Build the array of selected objects
	UPOSITION pos = pParent->m_childList.GetHeadPosition();
	while (pos)
	{
		CElement* pLayer = (CElement*)pParent->m_childList.GetNext(pos);

		if (IsElementTarget(pLayer))
		{
			CComQIPtr<ISVGTransformable> transformable = pLayer->m_domElement;
			if (transformable != NULL)
			{
				layers.Add(pLayer);
			}
		}
	}

	CComQIPtr<IDOMNode> pBeforeLayer;
	layers[layers.GetSize()-1]->m_domElement->get_nextSibling(&pBeforeLayer);

	CComQIPtr<ISVGGElement> pGroup;
	GetDOMDocument()->createElement(L"g", (IDOMElement**)&pGroup);

	if (pBeforeLayer)
		pParent->m_domElement->insertBefore(pGroup, pBeforeLayer, NULL);
	else
		pParent->m_domElement->appendChild(pGroup, NULL);

	for (int i = 0; i < layers.GetSize(); i++)
	{
		pGroup->appendChild(layers[i]->m_domElement, NULL);	// Insert At end
	}

	CElement* pGroupElement = m_pTree->FindDOMElement((IDOMNode*)pGroup);
	return pGroupElement;
#endif
#endif
	return NULL;
}

LRESULT CWebEditControl::OnObjectGroup(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	if (pDocument->m_targetElements.GetSize() > 0)
	{
		CElement* pParent = (CElement*)pDocument->m_targetElements[0]->m_parent;
		for (int i = 1; i < pDocument->m_targetElements.GetSize(); i++)
		{
			if (pDocument->m_targetElements[i]->m_parent != pParent)
			{
				MessageBox("Can't make a group of objects that are within different groups.", "WebEditor", MB_OK);
				return 0;
			}
		}

		/*CElement* pGroup = */pDocument->GroupTargetElements();
		/*
		if (pGroup)
		{
			pDocument->SetTargetElement(pGroup, 0);
		}*/
	}

	return 0;
}

void CWebEditControl::OnObjectGroupUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	pCmdUI->Enable(pDocument->m_targetElements.GetSize() > 0);
}

LRESULT CWebEditControl::OnObjectUngroup(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);
	return 0;
}

void CWebEditControl::OnObjectUngroupUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	BOOL bEnable = FALSE;

// Check if any of the target elements are group 'g' elements
	for (int i = 0; i < pDocument->m_targetElements.GetSize(); i++)
	{
		CElement* pElement = (CElement*)pDocument->m_targetElements[i];
		BSTR btagName;
		pElement->m_domElement->get_nodeName(&btagName);
		_bstr_t tagName = _bstr_t(btagName, false);

		if (wcscmp(tagName, L"g"))
		{
			bEnable = TRUE;
			break;
		}
	}

	pCmdUI->Enable(bEnable);
}

LRESULT CWebEditControl::OnViewZoomin(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	double docwidth = m_imageRect.Width();///m_magnify;
	double docheight = m_imageRect.Height();///m_magnify;

	double x = scrollposX/m_magnify + docwidth/m_magnify/2.0;
	double y = scrollposY/m_magnify + docheight/m_magnify/2.0;

	ZoomToRect2(
		x-docwidth/m_magnify/4,
		y-docheight/m_magnify/4,
		x+docwidth/m_magnify/4,
		y+docheight/m_magnify/4);

	return 0;
}

LRESULT CWebEditControl::OnViewZoomout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	double docwidth = m_imageRect.Width();///m_magnify;
	double docheight = m_imageRect.Height();///m_magnify;

	double x = scrollposX/m_magnify + docwidth/m_magnify/2.0;
	double y = scrollposY/m_magnify + docheight/m_magnify/2.0;

	ZoomToRect2(
		x-docwidth/m_magnify,
		y-docheight/m_magnify,
		x+docwidth/m_magnify,
		y+docheight/m_magnify);

	return 0;
}

LRESULT CWebEditControl::OnViewActualSize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CESvgDocument* pDocument = ((CESvgDocument*)m_pDocument.p);

	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	double docwidth = m_imageRect.Width();///m_magnify;
	double docheight = m_imageRect.Height();///m_magnify;

	long x = scrollposX/m_magnify;
	long y = scrollposY/m_magnify;

	ZoomToRect2(
		x-docwidth/2,
		y-docheight/2,
		x+docwidth/2,
		y+docheight/2);

//	ZoomToRect(zoomRect);

	return 0;
}
