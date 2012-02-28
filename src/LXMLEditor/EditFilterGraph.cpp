// EditFilterGraph.cpp : Implementation of CEditFilterGraph

#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "EditFilterGraph.h"

#include "ESVGFilterElement.h"

#if 0

/*
#define IN_SOURCEGRAPHIC		((CFilterPrimitiveElement*)-2)
#define IN_SOURCEALPHA			((CFilterPrimitiveElement*)-3)
#define IN_BACKGROUNDGRAPHIC	((CFilterPrimitiveElement*)-4)
#define IN_BACKGROUNDALPHA		((CFilterPrimitiveElement*)-5)
#define IN_FILL					((CFilterPrimitiveElement*)-6)
#define IN_STROKE					((CFilterPrimitiveElement*)-7)
*/

/////////////////////////////////////////////////////////////////////////////
// CEditFilterGraph

void CEditFilterGraph::FinalRelease()
{
	if (m_pLayer)
	{
		CComPtr<IEXMLDocument> edocument;
		m_pLayer->get_ownerDocument(&edocument);
		HRESULT hr = IDispEventImpl<4, CEditFilterGraph, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(edocument);
		ASSERT(SUCCEEDED(hr));
	}

	IDispEventImpl<2, CEditFilterGraph, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
	IDispEventImpl<3, CEditFilterGraph, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);
}

HRESULT CEditFilterGraph::OnDraw(ATL_DRAWINFO& di)
{
	HDC hDC = di.hdcDraw;
	CRect& client = *(CRect*)di.prcBounds;

	CDCHandle dc(hDC);

	if (m_pLayer)
	{
		dc.FillSolidRect(&client, RGB(255, 255, 255));

		SetBkMode(hDC, TRANSPARENT);

		HFONT hFont = CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");

		int state = SaveDC(hDC);

		HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

		int sbHeight = GetSystemMetrics(SM_CYHSCROLL);
		int sbWidth = GetSystemMetrics(SM_CXVSCROLL);

		long scrollposX; m_horz->get_pos(&scrollposX);
		long scrollposY; m_vert->get_pos(&scrollposY);

		IntersectClipRect(hDC, 0, 0, m_areaRect.right, m_areaRect.bottom);
		SetViewportOrgEx(hDC, -scrollposX, -scrollposY, NULL);
		if (m_pItemDrag)
		{
			CRect rc;
			m_pItemDrag->get_rect(&rc);

			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, rc.left-1, rc.top-1, rc.right+1, rc.bottom+1);

			SelectObject(hDC, hOldPen);
			DeleteObject(hPen);
		}

		int index = 0;

		for (int i = 0; i < m_pLayer->m_items.GetSize(); i++)
		{
			IESVGFilterPrimitiveElement* pItem = m_pLayer->m_items[i];//m_pLayer->m_items->GetNext(pos);
			ASSERT(pItem);

			CRect itemrect;
			pItem->get_rect(&itemrect);

			CUString text;

			long type = pItem->get_type();
#if 0
			if ((int)pItem->m_type < 0)
			{
				text.Format("%s", (char*)pItem->m_name);
			}
			else// if (pItem->m_pLayer)
#endif	
			{
				CComBSTR name;
				pItem->get_name(&name);
				if (type > 0)
				{
				//	text.Format("%s(%d) (%d ms)", pItem->m_name, index, pLayer->m_processTime);
					text.Format("%S(%d)", &((BSTR)name)[2], index);	// skip fe
				}
				else
				{
					text = name;
				}

				long npins;
				pItem->GetInPinCount(&npins);

				for (int i = 0; i < npins; i++)
				{
					CRect rect;
					pItem->get_rect(&rect);
				// Draw input pin
					{
						CRect rc(rect.left-6, rect.top + 2 + i*8, rect.left, rect.top + 2 + i*8 +6);
						Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
					}

					MoveToEx(hDC, itemrect.left-6, itemrect.top + 2 + 2 + i*8, NULL);

					CComPtr<IESVGFilterPrimitiveElement> pIn;

					if ((m_dragging == 2) && (pItem == m_pItemDrag) && m_inpin == i)
					{
						if (m_pNearItem)
						{
							pIn = m_pNearItem;
						}
						else
						{
							LineTo(hDC, m_oldpt.x, m_oldpt.y);
							pIn = NULL;
						}
					}
					else
					{
						pItem->GetInPin(i, &pIn);
					}

					if (pIn)
					{
						CRect rc2;

						BOOL bPossible = TRUE;

						long type;
						pIn->get_type(&type);

						if (type < 0)
						{
							pIn->get_rect(&rc2);
						}
						else
						{
						// If we reach the input, everything's okay,
						// if we reach this layer before the input pin, that
						// means the input pin is after us, therefore not possible
							CComPtr<ILDOMNode> node;
							m_pLayer->m_domElement->get_firstChild(&node);
							while (node)
							{
								CComQIPtr<ILDOMElement> element = node;
								if (element)
								{
									CComPtr<IEElement> eElement;
									m_pLayer->m_pDocument->GetEElementFromDOMElement(element, &eElement);

									CComQIPtr<IESVGFilterPrimitiveElement> pChild = eElement;//m_pLayer->m_children[j];
									if (pChild)
									{
										if (pChild == pIn)
										{
											break;
										}
										else if (pChild == pItem)
										{
											bPossible = FALSE;
										}
									}
								}

								CComPtr<ILDOMNode> nextSibling;
								node->get_nextSibling(&nextSibling);
								node = nextSibling;
							}

							pIn->get_rect(&rc2);
						}

						HPEN hPen = CreatePen(PS_SOLID, 1, bPossible? RGB(0,0,0): RGB(200,0,0));
						HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

						LineTo(hDC, rc2.right+6, rc2.bottom-6);

						SelectObject(hDC, hOldPen);
						DeleteObject(hPen);
					}
				}

				if (type > 0)
					index++;
			}

		// Draw output pin
			{
				CRect rc(itemrect.right, itemrect.bottom - 2 - 6, itemrect.right+6, itemrect.bottom - 2);
				Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
			}

			COLORREF clr;

			if (type < 0)
				clr = RGB(90, 180, 255);
			else
				clr = RGB(190, 190, 190);

			FillSolidRect(hDC, &itemrect, clr);
			Draw3DRect(hDC, itemrect.left+1, itemrect.top+1, itemrect.Width()-2, itemrect.Height()-2, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));

			RECT trc = {itemrect.left+2, itemrect.top+2, itemrect.right-2, itemrect.bottom-2};
			DrawText(hDC, text, lstrlen(text), &trc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}

		SelectObject(hDC, hOldFont);

		RestoreDC(hDC, state);

		DeleteObject(hFont);
	}
	else
	{
		dc.FillSolidRect(&client, GetSysColor(COLOR_BTNFACE));
	}

	return S_OK;
}

LRESULT CEditFilterGraph::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axhorz.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axhorz.AttachControl(m_horz, &p);
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

	return 0;
}

LRESULT CEditFilterGraph::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	Invalidate();

	return 0;
}

void CEditFilterGraph::OnSize()
{
	CRect client;
	GetClientRect(&client);

	if (m_pLayer)
	{
		int sbHeight = GetSystemMetrics(SM_CYHSCROLL);
		int sbWidth = GetSystemMetrics(SM_CXVSCROLL);

		int minx = 0;
		int miny = 0;
		int maxx = 0;
		int maxy = 0;

		for (int i = 0; i < m_pLayer->m_items.GetSize(); i++)
		{
			CComQIPtr<IESVGFilterPrimitiveElement> pItem = m_pLayer->m_items[i];

			CRect rc;
			pItem->get_rect(&rc);
			rc.right += 6;	// Make room for result pin

			minx = min(minx, rc.left);
			miny = min(miny, rc.top);
			maxx = max(maxx, rc.right);
			maxy = max(maxy, rc.bottom);
		}

		m_areaRect.left = 0;
		m_areaRect.top = 0;
		m_areaRect.right = client.right;
		m_areaRect.bottom = client.bottom;

		BOOL bVertSB = FALSE;
		BOOL bHorzSB = FALSE;

		if (maxx > m_areaRect.right)
		{
			m_areaRect.bottom -= sbHeight;
			bHorzSB = TRUE;
		}

		if (maxy-miny > m_areaRect.bottom)
		{
			m_areaRect.right -= sbWidth;
			bVertSB = TRUE;
		}

		if (!bHorzSB)
		{
			if (maxx-minx > m_areaRect.right)
			{
				m_areaRect.bottom -= sbHeight;
				bHorzSB = TRUE;
			}
		}

		if (bVertSB)
		{
			m_vert->SetInfo(miny, maxy, m_areaRect.Height());

			m_axvert.MoveWindow(m_areaRect.right, 0, sbWidth, m_areaRect.Height());
			m_axvert.ShowWindow(SW_SHOW);
		}
		else
		{
			m_vert->SetInfo(0, 0, 0);
			m_axvert.ShowWindow(SW_HIDE);
		}

		if (bHorzSB)
		{
			m_horz->SetInfo(minx, maxx, m_areaRect.Width());

			m_axhorz.MoveWindow(0, m_areaRect.bottom, m_areaRect.Width(), sbHeight);
			m_axhorz.ShowWindow(SW_SHOW);
		}
		else
		{
			m_horz->SetInfo(0, 0, 0);
			m_axhorz.ShowWindow(SW_HIDE);
		}
	}
	else
	{
		m_vert->SetInfo(0, 0, 0);
		m_axvert.ShowWindow(SW_HIDE);

		m_horz->SetInfo(0, 0, 0);
		m_axhorz.ShowWindow(SW_HIDE);
	}
}

LRESULT CEditFilterGraph::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	int b = 0;

	if (m_pLayer)
	{
		long scrollposX; m_horz->get_pos(&scrollposX);
		long scrollposY; m_vert->get_pos(&scrollposY);

		POINT pt = point;
		pt.x += scrollposX;
		pt.y += scrollposY;

		if (!m_dragging)
		{
			IESVGFilterPrimitiveElement* pFItem = NULL;

			m_pNearItem = NULL;

			for (int i = m_pLayer->m_items.GetSize()-1; i >= 0; i--)
			{
				CComQIPtr<IESVGFilterPrimitiveElement> pItem = m_pLayer->m_items[i];
				ASSERT(pItem);

				CRect itemrect;
				pItem->get_rect(&itemrect);
	#if 0
				if ((long)pItem->m_type > 0)
	#endif
				{
					long npins;
					pItem->GetInPinCount(&npins);

					for (int i = 0; i < npins; i++)
					{
						CRect rc(itemrect.left-6, itemrect.top + 2 + i*8, itemrect.left, itemrect.top + 2 + i*8 +6);
						if (PtInRect(&rc, pt))
						{
							pFItem = pItem;
							m_inpin = i;
							m_dragging = 2;
							break;
						}
					}
				}

				if (PtInRect(itemrect, pt))
				{
					m_dragging = 1;
					pFItem = pItem;
				}

				if (m_dragging)
				{
					break;
				}
			}

			if (pFItem)
			{
				m_pItemDrag = pFItem;

				if (b == 0)
				{
	#if 0
					CAdjustLayer* pLayer = m_pItemDrag->m_pLayer;
					if ((long)pLayer > 0)
					{
						if (pLayer->m_effectRecord->outImage)
						{
							HDC hdc = GetDC(NULL);

							pLayer->m_effectRecord->outImage->DrawImageToDC(hdc, 0, 0, 100, 100);

							ReleaseDC(NULL, hdc);
						}
					}
	#endif
				}
			}
			else
			{
				m_pItemDrag = NULL;
			}

			Invalidate();

			if (m_dragging)
			{
				m_oldpt = pt;

				SetCapture();
			}
		}
	}

	return 0;
}

#include "EXMLDocument.h"

LRESULT CEditFilterGraph::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nFlags = wParam;

	if (m_dragging)
	{
		ReleaseCapture();

		if (m_pItemDrag)
		{
			if (m_dragging == 1)
			{
				long type;
				m_pItemDrag->get_type(&type);

				if (type > 0)
				{
				//	m_pItemDrag->m_pLayer->SetProp("FGraphPos", MAKEWPARAM(m_pItemDrag->m_rect.left, m_pItemDrag->m_rect.top));
				//	((CEffectCollection*)m_pLayer->GetEffects())->SetActiveEffect(m_pItemDrag->m_pLayer);
					//ASSERT(0);
#if 0
					m_pLayer->m_pDocument->SetTargetElement(m_pItemDrag, nFlags);
#endif
				}
				else
				{
					// hm...
					//m_pLayer->m_pDocument->SetTargetElement(NULL, nFlags);
				}

				OnSize();
				Invalidate();
			}
			else if (m_dragging == 2)
			{
		//		CComQIPtr<ILSVGElement> dragElement;
		//		m_pItemDrag->get_domElement((ILDOMElement**)&dragElement);

				if (m_pNearItem)
				{
					CComBSTR result;
					m_pNearItem->get_resultString(&result);//_bstr_t(bresult, false);

				// result attribute isn't set for the element,
				// create a unique name and set it on the the result attribute
					if (result.Length() == 0)
					{
						int n = 0;

						while (1)
						{
							WCHAR buf[32];
							swprintf(buf, L"result%d", n);

							CComPtr<ILDOMNode> child;
							m_pLayer->m_domElement->get_firstChild(&child);
							while (child)
							{
								CComQIPtr<ILSVGFilterPrimitiveStandardAttributes> fe = child;
								if (fe)
								{
									CComQIPtr<ILDOMElement> element = fe;

									CComBSTR feresult;
									element->getAttribute(L"result", &feresult);

									if (feresult.Length() && !wcscmp(buf, feresult))
									{
										n++;
										break;
									}
								}

								CComPtr<ILDOMNode> nextSibling;
								child->get_nextSibling(&nextSibling);
								child = nextSibling;
							}

							if (child != NULL)
								continue;

							result = buf;
							break;
						}

						ASSERT(result.Length() > 0);

						CComPtr<ILDOMElement> domElement;
						m_pNearItem->get_domElement(&domElement);

						domElement->setAttribute(L"result", result);
					}

					m_pItemDrag->SetInPinString(m_inpin, result);
				}
				else
				{
					m_pItemDrag->ClearInPin(m_inpin);
				}

				Invalidate();
			}
		}

		m_dragging = 0;
	}

	return 0;
}

LRESULT CEditFilterGraph::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_dragging)
	{
		POINT pt = point;
		pt.x += scrollposX;
		pt.y += scrollposY;

		ASSERT(m_pItemDrag);
		POINT offset;
		offset.x = pt.x - m_oldpt.x;
		offset.y = pt.y - m_oldpt.y;

		if (m_dragging == 1)
		{
			if (offset.x != 0 || offset.y != 0)
			{
				CRect itemrect;
				m_pItemDrag->get_rect(&itemrect);

				itemrect.OffsetRect(offset.x, offset.y);

				m_pItemDrag->put_rect(itemrect);

				InvalidateRect(&m_areaRect);
			}
		}
		else if (m_dragging == 2)
		{
			CComPtr<IESVGFilterPrimitiveElement> pIn;
			m_pItemDrag->GetInPin(m_inpin, &pIn);

			m_pNearItem = NULL;

			/*
			UPOSITION pos = m_pLayer->m_items->GetHeadPosition();
			while (pos)
			*/
			for (int i = 0; i < m_pLayer->m_items.GetSize(); i++)
			{
				CComQIPtr<IESVGFilterPrimitiveElement> pItem = m_pLayer->m_items[i];
				ASSERT(pItem);

				CRect itemrect;
				pItem->get_rect(&itemrect);

				CRect rc(itemrect.right, itemrect.bottom - 2 - 6, itemrect.right+6, itemrect.bottom - 2);

				if (abs(pt.x-(itemrect.right+2)) < 16 && abs(pt.y-(itemrect.bottom-4)) < 16)
				{
					m_pNearItem = pItem;
					break;
				}
			}

			InvalidateRect(&m_areaRect);
		}

		m_oldpt = pt;
	}

	return 0;
}

STDMETHODIMP CEditFilterGraph::get_activeElement(IEElement **pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal = m_pLayer;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CEditFilterGraph::put_activeElement(IEElement *newVal)
{
	if (m_pLayer)
	{
		CComPtr<IEXMLDocument> edocument;
		m_pLayer->get_ownerDocument(&edocument);
		HRESULT hr = IDispEventImpl<4, CEditFilterGraph, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(edocument);
		ASSERT(SUCCEEDED(hr));
	}

	m_pLayer = static_cast<CESVGFilterElement*>(newVal);

	if (m_pLayer)
	{
		CComPtr<IEXMLDocument> edocument;
		m_pLayer->get_ownerDocument(&edocument);
		HRESULT hr = IDispEventImpl<4, CEditFilterGraph, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(edocument);
		ASSERT(SUCCEEDED(hr));

		m_pLayer->BuildItems();
	}

	OnSize();
	InvalidateRect(NULL, TRUE);

	return S_OK;
}

HRESULT __stdcall CEditFilterGraph::OnDOMEvent(ILDOMEvent* evt)
{
	if (m_pLayer)
	{
		CComBSTR type;
		evt->get_type(&type);

		if (!wcscmp(type, L"DOMNodeInserted"))
		{
			CComQIPtr<ILDOMMutationEvent> mut = evt;
		
			CComPtr<ILDOMEventTarget> target;
			mut->get_target(&target);
			CComQIPtr<ILDOMNode> node = target;

			m_pLayer->BuildItems();
		}
		else if (!wcscmp(type, L"DOMNodeRemoved"))
		{
			CComQIPtr<ILDOMMutationEvent> mut = evt;

			CComPtr<ILDOMEventTarget> target;
			mut->get_target(&target);
			CComQIPtr<ILDOMNode> node = target;

			for (int i = 0; i < m_pLayer->m_items.GetSize(); i++)
			{
				CComPtr<ILDOMElement> domElement;
				m_pLayer->m_items[i]->get_domElement(&domElement);
				
				if (domElement == node)
				{
					m_pLayer->m_items.RemoveAt(i);
					break;
				}
			}
		}

		OnSize();
		InvalidateRect(&m_areaRect);
	}

	return S_OK;
}

void __stdcall CEditFilterGraph::OnHorzScroll(long code, long pos)
{
	long oldPos; m_horz->get_pos(&oldPos);

	CRect	rect = m_areaRect;

	m_horz->put_pos(pos);
	ScrollWindow((oldPos-pos), 0, &rect, &rect);
}

void __stdcall CEditFilterGraph::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	CRect	rect = m_areaRect;
	
	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &rect, &rect);
}

STDMETHODIMP CEditFilterGraph::DeleteSelectedPrimitive()
{
	if (m_pItemDrag)
	{
		CComPtr<ILDOMElement> domElement;
		m_pItemDrag->get_domElement(&domElement);
		if (domElement)
		{
			m_pItemDrag = NULL;

			CComPtr<ILDOMNode> parentNode;
			domElement->get_parentNode(&parentNode);

			parentNode->removeChild(domElement, NULL);
		}
	}

	return S_OK;
}

#endif