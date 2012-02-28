#include "stdafx.h"
#include "LXMLEditor2.h"
#include "SVGObjectsDlg.h"

#include "EXMLViewGroup.h"
#include "EXMLLayoutView.h"	// ??

#include "WEUndoDeleteObjects.h"

namespace System
{
namespace LXmlEdit
{

Web::Element* GetOwnerLayer(Web::Element* element)
{
	ASSERT(0);
	return NULL;
#if 0
	ASSERT(element != NULL);
	ASSERT(pVal != NULL);

	CComPtr<ILDOMNode> node = element;
//	element->get_parentNode(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> parentElement = node;
		if (parentElement)
		{
			if (IsLayer(parentElement) == S_OK)
			{
				(*pVal = parentElement)->AddRef();
				return S_OK;
			}
		}

		CComPtr<ILDOMNode> parentNode;
		node->get_parentNode(&parentNode);
		node = parentNode;
	}

	*pVal = NULL;
	return S_OK;
#endif
};

LDraw::Color GetLayerColor(Web::Element* element)
{
	if (element == NULL) return 0xff000000;

	ASSERT(element != NULL);

	System::StringW* rgbTrio = element->getAttributeNS(WSTR("http://ns.adobe.com/AdobeIllustrator/10.0/"), WSTR("rgbTrio"));

	LDraw::Color clr(79, 153, 255);

	if (rgbTrio)
	{
		if ((rgbTrio->c_str())[0] == L'#')
		{
			const OLECHAR* rgbTrio2 = &(rgbTrio->c_str())[1];
			uint16 r, g, b;
			swscanf(rgbTrio2, L"%4hx%4hx%4hx", &r, &g, &b);

			clr = LDraw::Color(r>>8, g>>8, b>>8);
		}
	}

	return clr;
}

void SetLayerColor(Web::Element* element, LDraw::Color color)
{
	WCHAR rgbTrio[64];
	swprintf(rgbTrio, L"#%4.4X%4.4X%4.4X", color.GetRed()<<8, color.GetGreen()<<8, color.GetBlue()<<8);

	element->setAttributeNS(WSTR("http://ns.adobe.com/AdobeIllustrator/10.0/"), WSTR("i:rgbTrio"), new System::StringW(string_copy(rgbTrio)));
}

bool IsLayer(Web::Element* element)
{
	/*
	CComQIPtr<ILSVGSVGElement> svgsvgElement = element;
	if (svgsvgElement)
	{
		return S_OK;
	}
	*/

	bool bLayer = element->hasAttributeNS(WSTR("http://ns.adobe.com/AdobeIllustrator/10.0/"), WSTR("layer"));
	if (bLayer)
	{
		return true;
	}

	return false;
}

Web::Element* SVGGetLayer(Web::Element* element)
{
	ASSERT(0);
	return 0;
#if 0
	ASSERT(element != NULL);
	ASSERT(pVal != NULL);

	CComPtr<ILDOMNode> node = element;
	while (node)
	{
		CComQIPtr<ILDOMElement> parentElement = node;
		if (parentElement)
		{
			if (IsLayer(parentElement) == S_OK)
			{
				(*pVal = parentElement)->AddRef();
				return S_OK;
			}
		}

		CComPtr<ILDOMNode> parentNode;
		node->get_parentNode(&parentNode);
		node = parentNode;
	}

	*pVal = NULL;
	return S_OK;
#endif
}

#if 0
#define LeftBorder	16

BOOL SVGIsGraphicContainer(ILDOMElement* element);

/////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CSVGRenderableObjectsWnd

CSVGRenderableObjectsWnd::CSVGRenderableObjectsWnd()
{
	m_expandedBitmap = NULL;
	m_visibleBitmap = NULL;

	m_pRoot = NULL;
	m_itemHeight = 20;

	HRESULT hr;

	hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
//	if (FAILED(hr)) return hr;
	m_vert->put_direction(1);
}

LRESULT CSVGRenderableObjectsWnd::OnCreate()
{
	{
		m_font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

		LOGFONT lf;
		m_font.GetLogFont(&lf);
		lf.lfWeight = FW_BOLD;
		m_boldFont.CreateFontIndirect(&lf);
	}

	m_expandedBitmap = new LDraw::Bitmap(_Module.GetResourceInstance(), (WCHAR*)MAKEINTRESOURCE(IDB_EXPANDED));
	m_visibleBitmap  = new LDraw::Bitmap(_Module.GetResourceInstance(), (WCHAR*)MAKEINTRESOURCE(IDB_VISIBLE));

#if 0
	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axvert.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CSVGRenderableObjectsWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);
#endif

	return 0;
}

LRESULT CSVGRenderableObjectsWnd::OnDestroy()
{
	IDispEventImpl<1, CSVGRenderableObjectsWnd, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	if (m_font) m_font.DeleteObject();
	if (m_boldFont) m_boldFont.DeleteObject();

	if (m_expandedBitmap)
	{
		delete m_expandedBitmap;
		m_expandedBitmap = NULL;
	}

	if (m_visibleBitmap)
	{
		delete m_visibleBitmap;
		m_visibleBitmap = NULL;
	}

	return 0;
}

void CSVGRenderableObjectsWnd::DrawItem(CElement* pItem, int level, int& y, CRect& clip, LDraw::Graphics* pGraphics, ILDOMElement* rulerElement)
{
	CRect frect(0, y, m_areaRect.Width(), y+m_itemHeight);
	if (TRUE)//frect.IntersectRect(&frect, &clip))
	{
		//CDCHandle dc(hDC);

		int x = LeftBorder + level*10;

		CRect itemrect(x, y+1, m_areaRect.right, y+m_itemHeight);

	// Draw horizontal split line
		pGraphics->FillRectangle(&LDraw::SolidBrush(FromCOLORREF(COLOR_3DSHADOW)), x, y, m_areaRect.Width()-x, 1);

		CRect itemrect2 = itemrect;
		itemrect2.left += 12;

		/*
		if (pItem->m_selected)
		{
		//	dc.SelectFont(boldFont);
		//	dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));

			//HBRUSH hBrush = CreateSolidBrush();

			dc.FillSolidRect(&itemrect2, GetSysColor(COLOR_HIGHLIGHT));
		}
		else
		{
			dc.FillSolidRect(&itemrect2, GetSysColor(COLOR_WINDOW));
		}
		*/

		if (pItem->m_eElement)
		{
			_bstr_t name;

			CComPtr<ILDOMElement> domElement;
			pItem->m_eElement->get_domElement(&domElement);

			BOOL bLayer = IsLayer(domElement) == S_OK;

			CComPtr<ILDOMElement> layer;
			SVGGetLayer(domElement, &layer);

			CComBSTR id;
			domElement->getAttribute(L"id", &id);
			if (id.Length())
			{
				name = id;
			}
			else
			{
				BSTR btagName;
				domElement->get_localName(&btagName);
				if (SysStringLen(btagName) == 0) domElement->get_tagName(&btagName);
				name = L"<" + _bstr_t(btagName, false) + L">";
			}

			// Draw visibility icon
#if 0	// Had this
			{
				CRect lrc(0, y, LeftBorder, y+m_itemHeight);
				dc.FillSolidRect(&lrc, GetSysColor(COLOR_BTNFACE));
				dc.Draw3dRect(&lrc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));

				CComQIPtr<ILSVGStylable> stylable = domElement;
				if (stylable)
				{
					CComPtr<ILCSSStyleDeclaration> style;
					stylable->get_style(&style);
					CComBSTR visibility;
					style->getPropertyValue(L"visibility", &visibility);
					if (visibility.Length() == 0 || !wcscmp(visibility, L"visible"))
					{
						TransparentBlt(dc.m_hDC, lrc.left+2, lrc.top+(lrc.Height()-12)/2, 12, 12, m_visibleBitmap, 0, 0, RGB(192, 192, 192));
					}
				}
			}
#endif

			if (rulerElement/*bLayer*/)
			{
				pGraphics->FillRectangle(&LDraw::SolidBrush(FromCOLORREF(GetSysColor(COLOR_BTNFACE))), itemrect.left, itemrect.top, itemrect.Width(), itemrect.Height());
			}
			else
			{
				pGraphics->FillRectangle(&LDraw::SolidBrush(FromCOLORREF(GetSysColor(COLOR_WINDOW))), itemrect.left, itemrect.top, itemrect.Width(), itemrect.Height());
			}

			if (pItem->HasChildren())
			{
			//	TransparentBlt(dc.m_hDC, itemrect.left+2, itemrect.top+(itemrect.Height()-14)/2, 10, 14, m_expandedBitmap, pItem->m_expanded*10, 0, RGB(192, 192, 192));
				pGraphics->DrawImage(m_expandedBitmap,
					LDraw::Rect(itemrect.left+2, itemrect.top+(itemrect.Height()-14)/2, 10, 14),
					pItem->m_expanded*10, 0, 10, 14,
					LDraw::UnitPixel, NULL);
			}

			itemrect.left += 12;

		// Draw horizontal split line
			//dc.FillSolidRect(x, y, m_areaRect.Width()-x, 1, GetSysColor(COLOR_3DSHADOW));

#if 0	// Had this
			if (pItem->m_selected)
			{
				dc.SelectFont(m_boldFont);
				dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));

				pGraphics->FillRectangle(&itemrect2, GetSysColor(COLOR_HIGHLIGHT));

#if 0
				HBRUSH hBrush = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));

				if (static_cast<CEXMLViewGroup*>(m_dlg->m_viewGroup.p)->m_svgActiveContainer == pItem->m_eElement)
				//if (m_pActiveSelection == pItem)
				{
					POINT pt[] =
					{
						itemrect.left, itemrect.top,
						itemrect.right-6, itemrect.top,
						itemrect.right, itemrect.top+6,
						itemrect.right, itemrect.bottom,
						itemrect.left, itemrect.bottom,
					};

					HPEN hOldPen = (HPEN)SelectObject(dc.m_hDC, GetStockObject(NULL_PEN));
					HBRUSH hOldBrush = (HBRUSH)SelectObject(dc.m_hDC, hBrush);

					dc.Polygon(pt, 5);

					SelectObject(dc.m_hDC, hOldPen);
					SelectObject(dc.m_hDC, hOldBrush);
				}
				else
				{
					dc.FillRect(&itemrect, hBrush);
				}

				DeleteObject(hBrush);
#endif
			}
			else
#endif
			{
#if 0
				if (static_cast<CEXMLViewGroup*>(m_dlg->m_viewGroup.p)->m_svgActiveContainer == pItem->m_eElement)
				{
					POINT pt[] =
					{
						itemrect.right-6, itemrect.top,
						itemrect.right, itemrect.top,
						itemrect.right, itemrect.top+6,
					};

					HBRUSH hBrush = CreateSolidBrush(RGB(0,0,0));

					HPEN hOldPen = (HPEN)SelectObject(dc.m_hDC, GetStockObject(NULL_PEN));
					HBRUSH hOldBrush = (HBRUSH)SelectObject(dc.m_hDC, hBrush);

					dc.Polygon(pt, 3);

					SelectObject(dc.m_hDC, hOldPen);
					SelectObject(dc.m_hDC, hOldBrush);

					DeleteObject(hBrush);
				}
#endif

#if 0	// Had this
				dc.SelectFont(m_font);
				dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
#endif

			//	dc.FillSolidRect(&itemrect2, GetSysColor(COLOR_WINDOW));
			}

			CComPtr<IESelectedElement> selectedElement;
			m_dlg->m_viewGroup->GetSelectedElement(pItem->m_eElement, &selectedElement);

			if (pItem->m_bAnyTargeted)
			{
				COLORREF clr = GetLayerColor(layer);

				CRect colorRect = CRect(
					itemrect.right-10,
					itemrect.top+(itemrect.Height()-8)/2,
					itemrect.right-10+8,
					itemrect.top+(itemrect.Height()+8)/2);

				colorRect.InflateRect(-1,-1);

				pGraphics->FillRectangle(&LDraw::SolidBrush(FromCOLORREF(clr)), colorRect.left, colorRect.top, colorRect.Width(), colorRect.Height());

				if (pItem->m_bAllTargeted)
				{
					colorRect.InflateRect(1,1);
					//dc.Draw3dRect(&colorRect, RGB(0,0,0), RGB(0,0,0));
					pGraphics->DrawRectangle(&LDraw::Pen(LDraw::Color(0,0,0)), colorRect.left, colorRect.top, colorRect.Width(), colorRect.Height());
				}
			}
			else
				ASSERT(!pItem->m_bAllTargeted);

		//	Draw3DRect(hDC, &itemrect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));

			// Draw symbol for selected element in switch
			{
				CComPtr<ILDOMNode> parentNode;
				domElement->get_parentNode(&parentNode);
				CComQIPtr<ILSVGSwitchElement> switchElement = parentNode;
				if (switchElement)
				{
					ASSERT(0);
#if 0
					CComPtr<ILDOMElement> selectedSwitchElement;
					switchElement->getSelectedElement(&selectedSwitchElement);

					if (domElement == selectedSwitchElement)
					{
						dc.Ellipse(itemrect.left-8, itemrect.top, itemrect.left, itemrect.top+8);
					}
#endif
				}
			}

		// Draw symbol for wether this element is selected as a target or not
			{
#if 0
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, dc.GetTextColor());

				HPEN hOldPen = dc.SelectPen(pen);
				HBRUSH hOldBrush = dc.SelectBrush((HBRUSH)GetStockObject(NULL_BRUSH));
#endif

				CRect targetrc;
				targetrc.top = itemrect.top + m_itemHeight/2-8;
				targetrc.bottom = itemrect.top + m_itemHeight/2+8+1;
				targetrc.left = itemrect.right - 2-26-1;
				targetrc.right = itemrect.right - 2-10;

				targetrc.InflateRect(-4, -4);
				pGraphics->DrawEllipse(&LDraw::Pen(LDraw::Color(0,0,0)), targetrc.left, targetrc.top, targetrc.Width(), targetrc.Height());

				if (selectedElement)
				{
					targetrc.InflateRect(2, 2, 2, 2);
			//		dc.Ellipse(&targetrc);
					pGraphics->DrawEllipse(&LDraw::Pen(LDraw::Color(0,0,0)), targetrc.left, targetrc.top, targetrc.Width(), targetrc.Height());
				}

#if 0
				dc.SelectPen(hOldPen);
				dc.SelectBrush(hOldBrush);
#endif
			}

			CRect textitemrect = itemrect;
			textitemrect.left += 2;
			textitemrect.right -= 12;

			CRect tbounds = textitemrect;//(0,0,0,0);
#if 0
			dc.DrawText(name, name.length(), &tbounds, DT_SINGLELINE | DT_CALCRECT);

			dc.DrawText(name, name.length(), &textitemrect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
#endif

			if (TRUE)	// Check if object has mask
			{
#if 0	// Had this
				CComQIPtr<ILSVGStylable> stylable = domElement;
				if (stylable)
				{
					CComPtr<ILCSSStyleDeclaration> style;
					stylable->get_style(&style);

					CComPtr<ILCSSPrimitiveValue> cssvalue;
					style->getPropertyCSSValue(L"mask", (ILCSSValue**)&cssvalue);
					if (cssvalue)
					{
						for (int x = tbounds.left; x < tbounds.right; x += 6)
						{
							dc.FillSolidRect(x, textitemrect.top + (textitemrect.Height()-tbounds.Height())/2+tbounds.Height(), 3, 1, dc.GetTextColor());
						}
					}
				}
#endif
			}
		}
		else
		{
			if (rulerElement/*bLayer*/)
			{
				pGraphics->FillRectangle(&LDraw::SolidBrush(FromCOLORREF(COLOR_BTNFACE)), itemrect.left, itemrect.top, itemrect.Width(), itemrect.Height());
			}
			else
			{
				pGraphics->FillRectangle(&LDraw::SolidBrush(FromCOLORREF(COLOR_WINDOW)), itemrect.left, itemrect.top, itemrect.Width(), itemrect.Height());
			}

			if (pItem->m_selected)
			{
			//	dc.SelectFont(boldFont);
			//	dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));

				//HBRUSH hBrush = CreateSolidBrush();

				pGraphics->FillRectangle(&LDraw::SolidBrush(FromCOLORREF(COLOR_HIGHLIGHT)), itemrect2.left, itemrect2.top, itemrect2.Width(), itemrect2.Height());
			}
			/*
			else
			{
				dc.FillSolidRect(&itemrect2, GetSysColor(COLOR_WINDOW));
			}
			*/
		}
	}

	y += m_itemHeight;

	if (pItem->m_eElement)
	{
		CComPtr<ILDOMElement> domElement;
		pItem->m_eElement->get_domElement(&domElement);

		if (rulerElement/*m_dlg->m_viewGroup->m_layoutView->m_rulerElement*/ == domElement)
		{
			rulerElement = NULL;
		}
	}

	if (pItem->m_expanded)
	{
		DrawItemChildren(pItem, level+1, y, clip, pGraphics, rulerElement);
	}
}

void CSVGRenderableObjectsWnd::DrawItemChildren(C2Obj* pParentItem, int level, int& y, CRect& clip, LDraw::Graphics* pGraphics, ILDOMElement* rulerElement)
{
	UPOSITION pos = pParentItem->GetHeadPosition();
	while (pos)
	{
		CElement* pItem = (CElement*)pParentItem->GetNext(pos);

		DrawItem(pItem, level, y, clip, pGraphics, rulerElement);
	}
}

//LRESULT CSVGRenderableObjectsWnd::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
STDMETHODIMP CSVGRenderableObjectsWnd::Draw(ILCanvas* canvas)
{
	//CPaintDC dc(m_hWnd);
	LDraw::Graphics* pGraphics;
	canvas->GetGdip((long*)&pGraphics);

	if (m_pRoot)
	{
#if 0
		HFONT hOldFont = dc.GetCurrentFont();

		dc.SetBkMode(TRANSPARENT);
#endif

		if (TRUE)//dc.IntersectClipRect(m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom) > NULLREGION)
		{
			long scrollposY; m_vert->get_pos(&scrollposY);

#if 0
			dc.SetViewportOrg(m_areaRect.left, m_areaRect.top -scrollposY/* *m_itemHeight*/);
#endif

			CRect clip;
#if 0
			dc.GetClipBox(&clip);
#endif

			int y = 0;

			//C2Obj* pParentItem = m_pRoot;

			DrawItemChildren(m_pRoot, 0, y, clip, pGraphics, NULL/*m_dlg->m_viewGroup->m_layoutView->m_rulerElement*/);
#if 0

			UPOSITION pos = pParentItem->GetHeadPosition();
			int nextlevel = 0;

			while (pos)
			{
				int level = nextlevel;
				CElement* pItem = (CElement*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

				CRect frect(0, y, m_areaRect.Width(), y+m_itemHeight);
				if (frect.IntersectRect(&frect, &clip))
				{
					int x = LeftBorder + level*10;

					CRect itemrect(x, y+1, m_areaRect.right, y+m_itemHeight);

				// Draw horizontal split line
					dc.FillSolidRect(x, y, m_areaRect.Width()-x, 1, GetSysColor(COLOR_3DSHADOW));

					CRect itemrect2 = itemrect;
					itemrect2.left += 12;

					/*
					if (pItem->m_selected)
					{
					//	dc.SelectFont(boldFont);
					//	dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));

						//HBRUSH hBrush = CreateSolidBrush();

						dc.FillSolidRect(&itemrect2, GetSysColor(COLOR_HIGHLIGHT));
					}
					else
					{
						dc.FillSolidRect(&itemrect2, GetSysColor(COLOR_WINDOW));
					}
					*/

					if (pItem->m_eElement)
					{
						_bstr_t name;

						CComPtr<ILDOMElement> domElement;
						pItem->m_eElement->get_domElement(&domElement);

						BOOL bLayer = IsLayer(domElement) == S_OK;

						CComPtr<ILDOMElement> layer;
						SVGGetLayer(domElement, &layer);

						CComBSTR id;
						domElement->getAttribute(L"id", &id);
						if (id.Length())
						{
							name = id;
						}
						else
						{
							BSTR btagName;
							domElement->get_localName(&btagName);
							if (SysStringLen(btagName) == 0) domElement->get_tagName(&btagName);
							name = L"<" + _bstr_t(btagName, false) + L">";
						}

						// Draw visibility icon
						{
							CRect lrc(0, y, LeftBorder, y+m_itemHeight);
							dc.FillSolidRect(&lrc, GetSysColor(COLOR_BTNFACE));
							dc.Draw3dRect(&lrc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));

							CComQIPtr<ILSVGStylable> stylable = domElement;
							if (stylable)
							{
								CComPtr<ILCSSStyleDeclaration> style;
								stylable->get_style(&style);
								CComBSTR visibility;
								style->getPropertyValue(L"visibility", &visibility);
								if (visibility.Length() == 0 || !wcscmp(visibility, L"visible"))
								{
									TransparentBlt(dc.m_hDC, lrc.left+2, lrc.top+(lrc.Height()-12)/2, 12, 12, m_visibleBitmap, 0, 0, RGB(192, 192, 192));
								}
							}
						}

						if (bLayer)
						{
							dc.FillSolidRect(&itemrect, GetSysColor(COLOR_BTNFACE));
						}
						else
						{
							dc.FillSolidRect(&itemrect, GetSysColor(COLOR_WINDOW));
						}

						if (pItem->HasChildren())
						{
							TransparentBlt(dc.m_hDC, itemrect.left+2, itemrect.top+(itemrect.Height()-14)/2, 10, 14, m_expandedBitmap, pItem->m_expanded*10, 0, RGB(192, 192, 192));
						}

						itemrect.left += 12;

					// Draw horizontal split line
						//dc.FillSolidRect(x, y, m_areaRect.Width()-x, 1, GetSysColor(COLOR_3DSHADOW));

						if (pItem->m_selected)
						{
							dc.SelectFont(boldFont);
							dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));

							dc.FillSolidRect(&itemrect2, GetSysColor(COLOR_HIGHLIGHT));

#if 0
							HBRUSH hBrush = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));

							if (static_cast<CEXMLViewGroup*>(m_dlg->m_viewGroup.p)->m_svgActiveContainer == pItem->m_eElement)
							//if (m_pActiveSelection == pItem)
							{
								POINT pt[] =
								{
									itemrect.left, itemrect.top,
									itemrect.right-6, itemrect.top,
									itemrect.right, itemrect.top+6,
									itemrect.right, itemrect.bottom,
									itemrect.left, itemrect.bottom,
								};

								HPEN hOldPen = (HPEN)SelectObject(dc.m_hDC, GetStockObject(NULL_PEN));
								HBRUSH hOldBrush = (HBRUSH)SelectObject(dc.m_hDC, hBrush);

								dc.Polygon(pt, 5);

								SelectObject(dc.m_hDC, hOldPen);
								SelectObject(dc.m_hDC, hOldBrush);
							}
							else
							{
								dc.FillRect(&itemrect, hBrush);
							}

							DeleteObject(hBrush);
#endif
						}
						else
						{
#if 0
							if (static_cast<CEXMLViewGroup*>(m_dlg->m_viewGroup.p)->m_svgActiveContainer == pItem->m_eElement)
							{
								POINT pt[] =
								{
									itemrect.right-6, itemrect.top,
									itemrect.right, itemrect.top,
									itemrect.right, itemrect.top+6,
								};

								HBRUSH hBrush = CreateSolidBrush(RGB(0,0,0));

								HPEN hOldPen = (HPEN)SelectObject(dc.m_hDC, GetStockObject(NULL_PEN));
								HBRUSH hOldBrush = (HBRUSH)SelectObject(dc.m_hDC, hBrush);

								dc.Polygon(pt, 3);

								SelectObject(dc.m_hDC, hOldPen);
								SelectObject(dc.m_hDC, hOldBrush);

								DeleteObject(hBrush);
							}
#endif

							dc.SelectFont(font);
							dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));

							dc.FillSolidRect(&itemrect2, GetSysColor(COLOR_WINDOW));
						}

						CComPtr<IESelectedElement> selectedElement;
						m_dlg->m_viewGroup->GetSelectedElement(pItem->m_eElement, &selectedElement);

						if (pItem->m_bAnyTargeted)
						{
							COLORREF clr = GetLayerColor(layer);

							CRect colorRect = CRect(
								itemrect.right-10,
								itemrect.top+(itemrect.Height()-8)/2,
								itemrect.right-10+8,
								itemrect.top+(itemrect.Height()+8)/2);

							colorRect.InflateRect(-1,-1);

							dc.FillSolidRect(&colorRect, clr);

							if (pItem->m_bAllTargeted)
							{
								colorRect.InflateRect(1,1);
								dc.Draw3dRect(&colorRect, RGB(0,0,0), RGB(0,0,0));
							}
						}
						else
							ASSERT(!pItem->m_bAllTargeted);

					//	Draw3DRect(hDC, &itemrect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));

						// Draw symbol for selected element in switch
						{
							CComPtr<ILDOMNode> parentNode;
							domElement->get_parentNode(&parentNode);
							CComQIPtr<ILSVGSwitchElement> switchElement = parentNode;
							if (switchElement)
							{
								CComPtr<ILDOMElement> selectedSwitchElement;
								switchElement->getSelectedElement(&selectedSwitchElement);

								if (domElement == selectedSwitchElement)
								{
									dc.Ellipse(itemrect.left-8, itemrect.top, itemrect.left, itemrect.top+8);
								}
							}
						}

					// Draw symbol for wether this element is selected as a target or not
						{
							CPen pen;
							pen.CreatePen(PS_SOLID, 1, dc.GetTextColor());

							HPEN hOldPen = dc.SelectPen(pen);
							HBRUSH hOldBrush = dc.SelectBrush((HBRUSH)GetStockObject(NULL_BRUSH));

							CRect targetrc;
							targetrc.top = itemrect.top + m_itemHeight/2-8;
							targetrc.bottom = itemrect.top + m_itemHeight/2+8+1;
							targetrc.left = itemrect.right - 2-26-1;
							targetrc.right = itemrect.right - 2-10;

							targetrc.InflateRect(-4, -4);
							dc.Ellipse(&targetrc);

							if (selectedElement)
							{
								targetrc.InflateRect(2, 2, 2, 2);
								dc.Ellipse(&targetrc);
							}

							dc.SelectPen(hOldPen);
							dc.SelectBrush(hOldBrush);
						}

						CRect textitemrect = itemrect;
						textitemrect.left += 2;
						textitemrect.right -= 12;

						CRect tbounds = textitemrect;//(0,0,0,0);
						dc.DrawText(name, name.length(), &tbounds, DT_SINGLELINE | DT_CALCRECT);

						dc.DrawText(name, name.length(), &textitemrect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);

						if (TRUE)	// Check if object has mask
						{
							CComQIPtr<ILSVGStylable> stylable = domElement;
							if (stylable)
							{
								CComPtr<ILCSSStyleDeclaration> style;
								stylable->get_style(&style);

								CComPtr<ILCSSPrimitiveValue> cssvalue;
								style->getPropertyCSSValue(L"mask", (ILCSSValue**)&cssvalue);
								if (cssvalue)
								{
									for (int x = tbounds.left; x < tbounds.right; x += 6)
									{
										dc.FillSolidRect(x, textitemrect.top + (textitemrect.Height()-tbounds.Height())/2+tbounds.Height(), 3, 1, dc.GetTextColor());
									}
								}
							}
						}
					}
					else
					{
						dc.FillSolidRect(&itemrect, GetSysColor(COLOR_WINDOW));

						if (pItem->m_selected)
						{
						//	dc.SelectFont(boldFont);
						//	dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));

							//HBRUSH hBrush = CreateSolidBrush();

							dc.FillSolidRect(&itemrect2, GetSysColor(COLOR_HIGHLIGHT));
						}
						/*
						else
						{
							dc.FillSolidRect(&itemrect2, GetSysColor(COLOR_WINDOW));
						}
						*/
					}
				}

				y += m_itemHeight;
			}
#endif
		}

#if 0
		dc.SelectFont(hOldFont);
#endif
	}

	return 0;
}

LRESULT CSVGRenderableObjectsWnd::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_pRoot)
	{
		POINT pt = point;
		pt.y += /*-m_fnumHeight*/ + scrollposY;//*m_itemHeight;

		int y = 0;
		int top;
		int left;

#if 0
		if (static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_activeReferencedElement)
		{
			top = y;

			y += m_itemHeight;

			if (pt.y < y)
			{
				static_cast<CEXMLViewGroup*>(m_viewGroup.p)->ReferenceBack();
				return 0;
			}
		}
#endif

		CElement* pFElement = NULL;

		C2Obj* pParentItem = m_pRoot;
		UPOSITION pos = pParentItem->GetHeadPosition();
		int nextlevel = 0;

		while (pos)
		{
			int level = nextlevel;
			CElement* pItem = (CElement*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

			left = LeftBorder + level*10;
			top = y;

			y += m_itemHeight;

			if (pt.y < y)
			{
				pFElement = pItem;
				break;
			}
		}

		if (pFElement)
		{
			if (pt.x < LeftBorder)
			{
				CComPtr<ILDOMElement> domElement;
				pFElement->m_eElement->get_domElement(&domElement);

				CComQIPtr<ILSVGStylable> stylable = domElement;
				if (stylable)
				{
					CComPtr<ILCSSStyleDeclaration> style;
					stylable->get_style(&style);
					CComBSTR visibility;
					style->getPropertyValue(L"visibility", &visibility);

				// Toggle
					if (visibility.Length() == 0 || !wcscmp(visibility, L"visible"))
					{
						style->setProperty(L"visibility", L"hidden", NULL);
					}
					else
					{
						style->setProperty(L"visibility", L"visible", NULL);
					}

					InvalidateRect(&m_areaRect);	// TODO remove
				}
			}
			else if (pt.x >= left)
			{
				if (pt.x < left+12)	// Expand/Unexpand
				{
					if (pFElement->HasChildren())
					{
						pFElement->m_expanded = !pFElement->m_expanded;
						ResetVScrollSize();
						InvalidateRect(&m_areaRect);
					}
				}
				else if (pt.x < m_areaRect.Width()-28)
				{
					if (m_dlg->m_viewGroup->m_pActiveSelection)
					{
						if (!(nFlags & MK_SHIFT) ||
							m_dlg->m_viewGroup->m_pActiveSelection->GetParentNode() != pFElement->GetParentNode())
						{
							m_dlg->m_viewGroup->m_pActiveSelection->GetParentNode()->DeselectAll();
						}
					}

					m_dlg->m_viewGroup->m_pActiveSelection = pFElement;
#if 0
					static_cast<CEXMLViewGroup*>(m_dlg->m_viewGroup)->m_svgActiveContainer = m_dlg->m_viewGroup->m_pActiveSelection->m_eElement;
#endif

					pFElement->m_selected = true;
					InvalidateRect(&m_areaRect);
				}
				else //if (pt.x > m_areaRect.Width()-20)
				{
					m_dlg->m_viewGroup->ActivateElement(pFElement->m_eElement, nFlags, NULL);
				}
			}
		}
		else
		{
			if (!(nFlags & MK_SHIFT))
			{
				if (m_dlg->m_viewGroup->m_pActiveSelection)
				{
					m_dlg->m_viewGroup->m_pActiveSelection->GetParentNode()->DeselectAll();
				}
			}

			m_dlg->m_viewGroup->m_pActiveSelection = NULL;

			InvalidateRect(&m_areaRect);
		}
	}

	return 0;
}

#if 0
LRESULT CSVGRenderableObjectsWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.right = client.right-16;
	m_areaRect.bottom = client.bottom;

	m_axvert.MoveWindow(client.right-16, 0, 16, m_areaRect.Height());
//	m_sizeGrip.MoveWindow(client.right-16, client.bottom-16, 16, 16);

	ResetVScrollSize();

	return 0;
}
#endif

void CSVGRenderableObjectsWnd::ResetVScrollSize()
{
	if (m_pRoot)
	{
		int nitems = 0;
		C2Obj* pParentItem = m_pRoot;

		UPOSITION pos = pParentItem->GetHeadPosition();
		int nextlevel = 0;

		while (pos)
		{
			int level = nextlevel;
			C2Obj* pItem = (C2Obj*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);
			nitems++;
		}

	//	m_vert->SetInfo(0, nitems, (m_areaRect.Height()+m_itemHeight-1)/m_itemHeight);
		m_vert->SetInfo(0, nitems*m_itemHeight, m_areaRect.Height());
	}
	else
	{
		m_vert->SetInfo(0, 0, m_areaRect.Height());
	}
}

void __stdcall CSVGRenderableObjectsWnd::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	/*
	if (m_edit)
	{
		CRect wrect;
		::GetWindowRect(m_edit, &wrect);
		ScreenToClient((LPPOINT)&wrect.left);
		ScreenToClient((LPPOINT)&wrect.right);
		::SetWindowPos(m_edit, NULL, wrect.left, wrect.top + (oldPos-pos), 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOREDRAW);
	}
	*/

	CRect	rect = m_areaRect;
	
	m_vert->put_pos(pos);

#if 0
	::ScrollWindow(m_hWnd, 0, (oldPos-pos)/* *m_itemHeight*/, &rect, &rect);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CSVGObjectsDlg

int CSVGObjectsDlg::FinalConstruct()
{
	HRESULT hr;

	GUID guid;
	::CoCreateGuid(&guid);

	LPOLESTR guidstr;
	StringFromCLSID(guid, &guidstr);
	m_userDataKey = guidstr;
	CoTaskMemFree(guidstr);

	return 0;
}

void CSVGObjectsDlg::FinalRelease()
{
}

// ILElementBehavior
STDMETHODIMP CSVGObjectsDlg::Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite)
{
	m_behaviorSite = pBehaviorSite;

	OnCreate();

	return S_OK;
}

STDMETHODIMP CSVGObjectsDlg::Detach()
{
	OnDestroy();

	m_behaviorSite.Release();
	return S_OK;
}

LRESULT CSVGObjectsDlg::OnCreate()
{
	/*
	CComPtr<ILDOMElement> element;
	m_behaviorSite->GetElement(&element);

	CComPtr<IUnknown> unk;
	element->getUserData(L"n", &unk);
	CComQIPtr<IEXMLViewGroup> viewGroup(unk);

	m_viewGroup = static_cast<CEXMLViewGroup*>(viewGroup.p);
	*/
	ASSERT(m_viewGroup);

	m_renderableWnd.m_dlg = this;

	m_renderableWnd.m_areaRect.left = 0;
	m_renderableWnd.m_areaRect.top = 0;
	m_renderableWnd.m_areaRect.right = 200;
	m_renderableWnd.m_areaRect.bottom = 120;

	m_renderableWnd.OnCreate();
#if 0	// Had this
	m_renderableWnd.Create(m_hWnd, CRect(0,0,0,0), NULL, WS_VISIBLE | WS_CHILD);

	m_sizeGrip.Create(m_hWnd, CRect(0, 0, 0, 0), NULL, WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP);//, , m_hWnd, 1/*NULL, _Module.m_hInst, NULL*/);
#endif

//	CComQIPtr<IUIActiveManager> uiManager = m_app;
//	uiManager->AddEventHandler(this);

	m_viewGroup->get_eXMLDocument(&m_document);
	//m_document = static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_pDocument;
	IDispEventImpl<2, CSVGObjectsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_document);

	IDispEventImpl<3, CSVGObjectsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->GetUnknown());

	BuildTree();//delete m_pTree;

	return 0;
}

LRESULT CSVGObjectsDlg::OnDestroy()
{
//	CComQIPtr<IUIActiveManager> uiManager = m_app;
//	uiManager->RemoveEventHandler(this);

	IDispEventImpl<3, CSVGObjectsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->GetUnknown());
	IDispEventImpl<2, CSVGObjectsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);

	return 0;
}

void CSVGObjectsDlg::SetIsTargeted(CElement* pElement)
{
	if (!pElement->m_bAllTargeted)
	{
		CComPtr<IESelectedElement> selectedElement;
		m_viewGroup->GetSelectedElement(pElement->m_eElement, &selectedElement);

		if (selectedElement)
		{
			pElement->m_bAnyTargeted = pElement->m_bAllTargeted = true;
		}
	}

// Process the children
	UPOSITION pos = pElement->m_childList.GetHeadPosition();
	while (pos)
	{
		CElement* pChildElement = (CElement*)(C2Obj*)pElement->m_childList.GetNext(pos);

		if (pElement->m_bAllTargeted)
		{
			pChildElement->m_bAnyTargeted = pChildElement->m_bAllTargeted = true;
		}
		else
		{
			pChildElement->m_bAnyTargeted = pChildElement->m_bAllTargeted = false;
		}

		SetIsTargeted(pChildElement);
	}

// After having processed the children

	if (!pElement->m_bAllTargeted)
	{
		pos = pElement->m_childList.GetHeadPosition();
		while (pos)
		{
			CElement* pChildElement = (CElement*)(C2Obj*)pElement->m_childList.GetNext(pos);

			if (pChildElement->m_bAnyTargeted)
			{
				pElement->m_bAnyTargeted = true;
				break;
			}
		}

		if (pElement->m_bAnyTargeted)
		{
			pElement->m_bAllTargeted = true; // Assume

			pos = pElement->m_childList.GetHeadPosition();
			while (pos)
			{
				CElement* pChildElement = (CElement*)(C2Obj*)pElement->m_childList.GetNext(pos);

				if (!pChildElement->m_bAnyTargeted || !pChildElement->m_bAllTargeted)
				{
					pElement->m_bAllTargeted = false;
					break;
				}
			}
		}
	}
}

STDMETHODIMP CSVGObjectsDlg::Draw(ILCanvas* canvas)
{
	m_renderableWnd.Draw(canvas);	// ??

	if (m_pTree)
	{
		CComPtr<ILDOMDocument> domDocument;
		m_document->get_DOMDocument(&domDocument);

#if 0
		HFONT hOldFont = dc.GetCurrentFont();

		CFontHandle font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		LOGFONT lf;
		font.GetLogFont(&lf);
		lf.lfWeight = FW_BOLD;
		CFont boldFont;
		boldFont.CreateFontIndirect(&lf);

		dc.SetBkMode(TRANSPARENT);

		if (static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferencedElement)
		{
			if (static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferenceElement)
			{
				IEElement* eElement = static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferenceElement;

				CComPtr<ILDOMElement> domElement;
				eElement->get_domElement(&domElement);

				_bstr_t name;

				CComBSTR id;
				domElement->getAttribute(L"id", &id);
				if (id.Length())
				{
					name = id;
				}
				else
				{
					BSTR btagName;
					domElement->get_localName(&btagName);
					if (SysStringLen(btagName) == 0) domElement->get_tagName(&btagName);
					name = L"<" + _bstr_t(btagName, false) + L">";
				}

				CRect textitemrect(16, 0+1, m_areaRect.Width(), 0+20-1);

				dc.DrawText(name, name.length(), &textitemrect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
			}
		}

		dc.SelectFont(hOldFont);
#endif
	}

	return 0;
}

LRESULT CSVGObjectsDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	//long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_pTree)
	{
		POINT pt = point;
		//pt.y += /*-m_fnumHeight*/ + scrollposY*m_itemHeight;

//		int y = 0;
//		int top;
		int left;

		if (static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferencedElement)
		{
		//	top = y;

		//	y += m_itemHeight;

			if (pt.y < 20)
			{
				static_cast<CEXMLViewGroup*>(m_viewGroup)->ReferenceBack();
				return 0;
			}
		}
	}

	return 0;
}

void CSVGObjectsDlg::OnSize()
{
#if 0
	CRect client;
	GetClientRect(&client);

	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.right = client.right;//-16;
	m_areaRect.bottom = client.bottom-16;

	if (static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferencedElement)
	{
	//	if (static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_activeReferenceElement)
		{
			m_areaRect.top = 20;
		}
	}

	m_renderableWnd.MoveWindow(0, m_areaRect.top, client.right, m_areaRect.Height());
#endif
}

#if 0
LRESULT CSVGObjectsDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	OnSize();

	m_sizeGrip.MoveWindow(client.right-16, client.bottom-16, 16, 16);

	return 0;
}
#endif

STDMETHODIMP CSVGObjectsDlg::OnDragOut(IUIDockBar* dockBar)
{
	static_cast<CEXMLViewGroup*>(m_viewGroup)->DragOut(m_view, dockBar);
	return S_OK;
}

void CSVGObjectsDlg::SetRoot()
{
	if (m_renderableWnd.m_pRoot)
	{
		m_renderableWnd.m_pRoot->m_childList.RemoveAll();
		delete m_renderableWnd.m_pRoot;
		m_renderableWnd.m_pRoot = NULL;
	}

	if (m_referencedElement == NULL)
	{
		CComPtr<ILDOMDocument> domdocument;
		m_document->get_DOMDocument(&domdocument);

		CComPtr<ILDOMElement> documentElement;
		domdocument->get_documentElement(&documentElement);

		m_renderableWnd.m_pRoot = new C2Obj;
	//	m_renderableWnd.m_pRoot->AddChildTail(m_pTree);
		CElement* pElement = m_pTree->FindElement(documentElement);
		if (pElement)
		{
			m_renderableWnd.m_pRoot->m_childList.AddTail((C2Obj*)pElement);
		}
	}
	else
	{
		CComPtr<ILDOMElement> element;
		m_referencedElement->get_domElement(&element);

		m_renderableWnd.m_pRoot = new C2Obj;
		CElement* pElement = m_pTree->FindElement(element);
		if (pElement)
		{
			m_renderableWnd.m_pRoot->m_childList.AddTail((C2Obj*)pElement);
		}
	}
}

void __stdcall CSVGObjectsDlg::OnViewGroupSelectionChanged()
{
	ASSERT(m_viewGroup);

	if (m_referencedElement != static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferencedElement)
	{
		m_referencedElement = static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferencedElement;

		SetRoot();

		m_renderableWnd.ResetVScrollSize();

		OnSize();

#if 0
		CComPtr<IESelectedElement> selectedElement;
		m_viewGroup->GetActiveSelectedElement(&selectedElement);
		if (selectedElement)
		{
			CComPtr<IEElement> eElement;
			selectedElement->get_eElement(&eElement);

			m_pTree->MakeExpanded(eElement);
		}

		ResetVScrollSize();
#endif
	}

	if (!m_pTree->m_childList.IsEmpty())
	{
		CElement* pElement = (CElement*)(C2Obj*)m_pTree->m_childList.GetHead();

		pElement->m_bAnyTargeted = pElement->m_bAllTargeted = false;
		SetIsTargeted(pElement);
	}

//	if (m_hWnd)
	{
		InvalidateRect(&m_areaRect);
		m_renderableWnd.InvalidateRect(&m_renderableWnd.m_areaRect);
	}
}

void __stdcall CSVGObjectsDlg::OnDOMEvent(ILDOMEvent* evt)
{
	if (m_pTree)
	{
		if (evt == NULL)
		{
			//if (m_hWnd)
			{
				InvalidateRect(&m_areaRect);
			}
			return;
		}

		CComBSTR type;
		evt->get_type(&type);

		if (!wcscmp(type, L"DOMNodeRemoved") ||
			!wcscmp(type, L"DOMNodeRemovedFromDocument"))
		{
			CComQIPtr<ILDOMMutationEvent> mut = evt;

			CComPtr<ILDOMEventTarget> target;
			mut->get_target(&target);
			CComQIPtr<ILDOMNode> node = target;

			if (m_viewGroup->m_pActiveSelection)
			{
				ASSERT(m_viewGroup->m_pActiveSelection->m_eElement);
				CComPtr<ILDOMNode> node2;
				m_viewGroup->m_pActiveSelection->m_eElement->get_domNode(&node2);
				if (node2 == node)
				{
					m_viewGroup->m_pActiveSelection = NULL;
				}
			}
		}

		if (!wcscmp(type, L"DOMNodeInserted"))
		{
			CComQIPtr<ILDOMMutationEvent> mut = evt;
		
			CComPtr<ILDOMEventTarget> target;
			mut->get_target(&target);
			CComQIPtr<ILDOMNode> node = target;

			BOOL bAdd = IsAddableElement(node);

			if (bAdd)
			{
				CComPtr<ILDOMNode> parentNode;
				node->get_parentNode(&parentNode);

				CElement* pParentElement = m_pTree->FindElement(parentNode);
				if (pParentElement)
				{
					CComQIPtr<ILDOMElement> element = node;

					CComObject<CElement>* pElement;
					CComObject<CElement>::CreateInstance(&pElement);
					if (pElement)
					{
						pElement->AddRef();

						CComPtr<IEElement> eElement;
						m_document->GetEElementFromDOMElement(element, &eElement);
						ASSERT(eElement);

						pElement->m_parent = pParentElement;
						pElement->m_node = element;
						pElement->m_eElement = eElement;
						BuildChildren(pElement, m_document);

						UPOSITION pos = pParentElement->m_childList.GetHeadPosition();

						CComPtr<ILDOMNode> child;
						parentNode->get_lastChild(&child);

						while (child)
						{
							if (child == node)
								break;

							if (pos)
							{
								UPOSITION pos2 = pos;
								CElement* pChild = (CElement*)(C2Obj*)pParentElement->m_childList.GetNext(pos2);
								if (pChild->m_node == child)
								{
									pos = pos2;	// Okay, advance pos
								}
							}

							CComPtr<ILDOMNode> prevSibling;
							child->get_previousSibling(&prevSibling);
							child = prevSibling;
	/*
							CComPtr<ILDOMNode> nextSibling;
							child->get_nextSibling(&nextSibling);
							child = nextSibling;
							*/
						}

						if (pos)
							pParentElement->m_childList.InsertBefore(pos, (C2Obj*)pElement);
						else
							pParentElement->m_childList.AddTail((C2Obj*)pElement);
					}

					//if (m_hWnd)
					{
						m_renderableWnd.InvalidateRect(&m_renderableWnd.m_areaRect);
						m_renderableWnd.ResetVScrollSize();

						InvalidateRect(&m_areaRect);
					}
				}
			}
		}
		else if (!wcscmp(type, L"DOMNodeRemoved"))
		{
			CComQIPtr<ILDOMMutationEvent> mut = evt;

			CComPtr<ILDOMEventTarget> target;
			mut->get_target(&target);
			CComQIPtr<ILDOMNode> node = target;

			CElement* pElement = m_pTree->FindElement(node);
			if (pElement)
			{
				UPOSITION pos = pElement->m_parent->m_childList.Find((C2Obj*)pElement);
				ASSERT(pos);
				pElement->m_parent->m_childList.RemoveAt(pos);

				delete pElement;

				//if (m_hWnd)
				{
					m_renderableWnd.InvalidateRect(&m_renderableWnd.m_areaRect);
					m_renderableWnd.ResetVScrollSize();

					InvalidateRect(&m_areaRect);
				}
			}
		}
	}
}

CElement* CBaseNode::FindElement(ILDOMNode* node)
{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CElement* pElement = (CElement*)(C2Obj*)m_childList.GetNext(pos);

		if (pElement->m_node == node) return pElement;

		CElement* pF = pElement->FindElement(node);
		if (pF)
			return pF;
	}

	return NULL;
}

BOOL CBaseNode::MakeExpanded(IEElement* eElement)
{
	ASSERT(eElement);

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CElement* pElement = (CElement*)(C2Obj*)m_childList.GetNext(pos);

		if (pElement->m_eElement == eElement)
		{
			m_expanded = true;
			return TRUE;
		}

		if (pElement->MakeExpanded(eElement))
		{
			m_expanded = true;
			return TRUE;
		}
	}

	return FALSE;
}

void CSVGObjectsDlg::BuildChildren(CBaseNode* pNode, IEXMLDocument* edocument)
{
	ASSERT(pNode->m_node);

	CComPtr<ILDOMNode> node;
	pNode->m_node->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> childElement = node;
		if (childElement)
		{
			BOOL bAdd = TRUE;//IsAddableElement(childElement);

			if (bAdd)
			{
				CComPtr<IEElement> eElement;
				edocument->GetEElementFromDOMElement(childElement, &eElement);

				CComObject<CElement>* pChild;
				CComObject<CElement>::CreateInstance(&pChild);
				if (pChild)
				{
					pChild->AddRef();

					pChild->m_node = childElement;
					pChild->m_eElement = eElement;

					BuildChildren(pChild, edocument);

					pNode->AddChildHead(pChild);
				}
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	CComQIPtr<ILDOMElement> element = pNode->m_node;
	if (element)
	{
		if (SVGIsGraphicContainer(element))
		{
			CComObject<CElement>* p;
			CComObject<CElement>::CreateInstance(&p);
			pNode->AddChildHead(p);
		}
	}
}

BOOL CSVGObjectsDlg::IsAddableElement(ILDOMNode* node)
{
	return TRUE;

	BOOL bAdd = false;

	if (m_elementType == 1)
	{
		CComQIPtr<ISVGRenderElement> renderElement = node;
		if (renderElement)
		{
			bAdd = true;
		}
	}
	else if (m_elementType == 2)
	{
		CComQIPtr<ILSVGFilterPrimitiveStandardAttributes> fe = node;
		if (fe)
		{
			bAdd = true;
		}
		else
		{
			CComQIPtr<ILSVGFEPointLightElement> e = node;
			if (e)
			{
				bAdd = true;
			}
			else
			{
				CComQIPtr<ILSVGFEDistantLightElement> e = node;
				if (e)
				{
					bAdd = true;
				}
				else
				{
					CComQIPtr<ILSVGFESpotLightElement> e = node;
					if (e)
					{
						bAdd = true;
					}
				}
			}
		}
	}
	else if (m_elementType == 3)
	{
		CComQIPtr<ILSVGStopElement> stop = node;
		if (stop)
		{
			bAdd = true;
		}
	}

	return bAdd;
}

void CSVGObjectsDlg::BuildTree()
{
	ASSERT(m_pTree == NULL);
	ASSERT(m_document);

	CComPtr<ILDOMDocument> domdocument;
	m_document->get_DOMDocument(&domdocument);

	m_referencedElement = static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferencedElement;

#if 0
	if (m_referencedElement)
	{
		CComPtr<ILDOMElement> domElement;
		static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_activeReferencedElement->get_domElement(&domElement);

		m_pTree = new CNode;
		m_pTree->m_node = NULL;

		CComQIPtr<ILSVGFilterElement> filter = domElement;
		CComQIPtr<ILSVGGradientElement> gradient = domElement;

		CElement* pElement = new CElement;

		pElement->m_node = domElement;
		pElement->m_eElement = static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_activeReferencedElement;
		ASSERT(pElement->m_eElement);

		if (filter)
			m_elementType = 2;
		else if (gradient)
			m_elementType = 3;
		else
			m_elementType = 1;

		BuildChildren(pElement, m_document);

		m_pTree->AddChildTail(pElement);
	}
	else
#endif
	{
		CComObject<CNode>::CreateInstance(&m_pTree);
		m_pTree->AddRef();
		m_pTree->m_node = domdocument;

		m_elementType = 1;

		BuildChildren(m_pTree, m_document);

		SetRoot();
		/*
		if (m_referencedElement == NULL)
		{
			m_renderableWnd.m_pRoot = m_pTree;
		}
		else
		{
			CComPtr<ILDOMElement> element;
			m_referencedElement->get_domElement(&element);

			m_renderableWnd.m_pRoot = m_pTree->FindElement(element);
		}
		*/
	}
}

#if 0
// IUIEventHandler
STDMETHODIMP CSVGObjectsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLDocument> document = object;
	if (document)
	{
		if (m_document)
		{
			IDispEventImpl<2, CSVGObjectsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);
		}
		else
		{
//			ASSERT(m_pTree == NULL);
		}

		m_document = document;
		IDispEventImpl<2, CSVGObjectsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_document);

		if (m_hWnd)
		{
			m_renderableWnd.ResetVScrollSize();
			Invalidate();
		}

		*cookie = 1;
	}

	CComQIPtr<IEXMLViewGroup> viewGroup = object;
	if (viewGroup)
	{
		ASSERT(m_viewGroup == NULL);

		m_viewGroup = viewGroup;
		IDispEventImpl<3, CSVGObjectsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

		BuildTree();//delete m_pTree;
		//m_pTree = NULL;

		//OnViewGroupSelectionChanged();

		if (m_hWnd)
		{
			InvalidateRect(&m_areaRect);
		}

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CSVGObjectsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	CComQIPtr<IEXMLDocument> document = object;
	if (document)
	{
		ASSERT(m_viewGroup == NULL);
		ASSERT(m_document == document);

		IDispEventImpl<2, CSVGObjectsDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);

		m_document.Release();
	}

	CComQIPtr<IEXMLViewGroup> viewGroup = object;
	if (viewGroup)
	{
		IDispEventImpl<3, CSVGObjectsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
		m_viewGroup.Release();

		m_pActiveSelection = NULL;
		m_pTree->Release();
		m_pTree = NULL;

		ASSERT(m_document != NULL);
	}

	if (m_hWnd)
	{
		m_renderableWnd.ResetVScrollSize();
		Invalidate();
	}

	return S_OK;
}
#endif

#if 0
// ICommandTarget
STDMETHODIMP CSVGObjectsDlg::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try layoutview ???
	{
		CComQIPtr<ICommandTarget> target = m_viewGroup->m_layoutView;
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

// Try viewgroup
	{
		CComQIPtr<ICommandTarget> target = m_viewGroup;
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

	return S_OK;
}
#endif

BEGIN_CMD_MAP(CSVGObjectsDlg)
	CMD_HANDLER(ID_SVGOBJECTS_NEWLAYER, OnNewLayer)
	CMD_HANDLER(ID_SVGOBJECTS_NEWSUBLAYER, OnNewSubLayer)

	CMD_HANDLER(ID_SVGOBJECTS_DELETESELECTION, OnDeleteSelection)
	CMD_UPDATE(ID_SVGOBJECTS_DELETESELECTION, OnDeleteSelectionUpdate)

	CMD_HANDLER(ID_SVGOBJECTS_SELECTIONOPTIONS, OnSelectionOptions)
/*

	CMD_HANDLER(ID_FILTERS_SELECTALLUNUSED, OnFiltersSelectAllUnused)

	CMD_HANDLER(ID_SVGLIST_LARGETHUMBNAILS, OnFiltersThumbnailView)
	CMD_HANDLER(ID_SVGLIST_SMALLLISTVIEW, OnFiltersSmallListView)
	CMD_HANDLER(ID_SVGLIST_LARGELISTVIEW, OnFiltersLargeListView)
	CMD_UPDATE(ID_SVGLIST_LARGETHUMBNAILS, OnFiltersThumbnailViewUpdate)
	CMD_UPDATE(ID_SVGLIST_SMALLLISTVIEW, OnFiltersSmallListViewUpdate)
	CMD_UPDATE(ID_SVGLIST_LARGELISTVIEW, OnFiltersLargeListViewUpdate)
	*/
END_CMD_MAP()

#include "EXMLDocument.h"	// TODO remove

#include "LayerOptionsDlg.h"

void GetNewElementInsertionAt(IEXMLViewGroup* viewGroup, ILDOMElement** pparentNode, ILDOMNode** pbeforeNode);

// 
LRESULT CSVGObjectsDlg::OnNewLayer(int wNotifyCode, int wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_viewGroup->m_pActiveSelection)
	{
		CLayerOptionsDlg dlg;

		if (dlg.DoModal() == IDOK)
		{
			CComPtr<IEElement> eGElement;
			m_document->createEElementNS(L"http://www.w3.org/2000/svg", L"g", &eGElement);

			CComPtr<ILDOMElement> element;
			eGElement->get_domElement(&element);

			element->setAttributeNS(L"http://ns.adobe.com/AdobeIllustrator/10.0/", L"i:layer", L"yes");
			SetLayerColor(element, dlg.m_color);

			CComPtr<ILDOMElement> activeElement;
			m_viewGroup->m_pActiveSelection->m_eElement->get_domElement(&activeElement);

			CComPtr<ILDOMNode> parentNode;
			activeElement->get_parentNode(&parentNode);

			CComPtr<ILDOMNode> nextSibling;
			activeElement->get_nextSibling(&nextSibling);

			parentNode->insertBefore(element, _variant_t(nextSibling), NULL);
		}
	}

	return 0;
}

LRESULT CSVGObjectsDlg::OnNewSubLayer(int wNotifyCode, int wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CSVGObjectsDlg::OnDeleteSelection(int wNotifyCode, int wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_viewGroup->m_pActiveSelection)
	{
		if (m_viewGroup->m_pActiveSelection->m_parent && m_viewGroup->m_pActiveSelection->m_parent->m_parent)
		{
			CComQIPtr<IEDocument> eDocument = m_document;

			CComQIPtr<IOleUndoManager> undoManager;
			eDocument->get_undoManager(&undoManager);

			CComObject<CWEUndoDeleteObjects>* pUndo;
			CComObject<CWEUndoDeleteObjects>::CreateInstance(&pUndo);
			if (pUndo)
			{
				//pUndo->AddRef();
				pUndo->m_pDocument = static_cast<CEXMLDocument*>(m_document.p);
				//m_activeSpread->get_uniqId(&pUndo->m_spreadGUID);
				//pUndo->m_pView = this;
				pUndo->m_bRedo = true;

				CElement* pParentElement = (CElement*)m_viewGroup->m_pActiveSelection->m_parent;

				CComPtr<ILDOMNode> domParentNode;
				pParentElement->m_eElement->get_domNode(&domParentNode);

				GUID parentGuid;
				domParentNode->get_uniqID(&parentGuid);

				UPOSITION pos = pParentElement->m_childList.GetHeadPosition();
				while (pos)
				{
					CElement* pElement = (CElement*)(C2Obj*)pParentElement->m_childList.GetNext(pos);

					if (pElement->m_selected)
					{
						CComPtr<ILDOMNode> domNode;
						pElement->m_eElement->get_domNode(&domNode);

						GUID guid;
						domNode->get_uniqID(&guid);

						pUndo->m_targetElements.Add(guid);

						pUndo->m_parentElements.Add(parentGuid);

						CComPtr<ILDOMNode> domBeforeNode;
						domNode->get_nextSibling(&domBeforeNode);

						if (domBeforeNode != NULL)
						{
							domBeforeNode->get_uniqID(&guid);
							pUndo->m_beforeElements.Add(guid);
						}
						else
						{
							pUndo->m_beforeElements.Add(GUID_NULL);
						}
					}
				}

				pUndo->Do(undoManager);
			}
		}
	}

	return 0;
}

void CSVGObjectsDlg::OnDeleteSelectionUpdate(long wID, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;
	if (m_viewGroup->m_pActiveSelection)
	{
		if (m_viewGroup->m_pActiveSelection->m_parent && m_viewGroup->m_pActiveSelection->m_parent->m_parent)
		{
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
}

LRESULT CSVGObjectsDlg::OnSelectionOptions(int wNotifyCode, int wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_viewGroup->m_pActiveSelection)
	{
		CArray<CElement*,CElement*> selection;

		UPOSITION pos = m_viewGroup->m_pActiveSelection->m_parent->m_childList.GetHeadPosition();
		while (pos)
		{
			CElement* pElement = (CElement*)(C2Obj*)m_viewGroup->m_pActiveSelection->m_parent->m_childList.GetNext(pos);
			if (pElement->m_selected)
			{
				selection.Add(pElement);
			}
		}

		if (selection.GetSize() > 0)
		{
			CLayerOptionsDlg dlg;

			for (int i = 0; i < selection.GetSize(); i++)
			{
				CComPtr<ILDOMElement> element;
				selection[i]->m_eElement->get_domElement(&element);

				BOOL isLayer = IsLayer(element) == S_OK;
				COLORREF color = GetLayerColor(element);

				if (i == 0)
				{
					dlg.m_isLayer = isLayer;
				}
				else if (dlg.m_isLayer != isLayer)
				{
					dlg.m_isLayer = 2; // BST_INDETERMINATE
				}

				if (i == 0)
				{
					dlg.m_color = color;
				}
				else if (dlg.m_color != color)
				{
					dlg.m_color = -1;
				}
			}

			if (dlg.DoModal() == IDOK)
			{
				for (int i = 0; i < selection.GetSize(); i++)
				{
					CComPtr<ILDOMElement> element;
					selection[i]->m_eElement->get_domElement(&element);
		
					if (dlg.m_isLayer == 1)
					{
						element->setAttributeNS(L"http://ns.adobe.com/AdobeIllustrator/10.0/", L"i:layer", L"yes");
						SetLayerColor(element, dlg.m_color);
					}
					else if (dlg.m_isLayer == 0)
					{
						element->removeAttributeNS(L"http://ns.adobe.com/AdobeIllustrator/10.0/", L"rgbTrio");
						element->removeAttributeNS(L"http://ns.adobe.com/AdobeIllustrator/10.0/", L"layer");
					}

					InvalidateRect(&m_areaRect);
					m_renderableWnd.InvalidateRect(&m_renderableWnd.m_areaRect);
				}
			}
		}
	}

	return 0;
}

#endif

}	// LXmlEdit
}
