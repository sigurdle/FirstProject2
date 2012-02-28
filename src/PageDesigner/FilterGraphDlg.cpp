// FilterGraphDlg.cpp : Implementation of CFilterGraphDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "FilterGraphDlg.h"
#include "PDDocumentView.h"

#include "PDAppearance.h"
#include "PDFilterPrimitive.h"

int CFilterPrimitiveElement::GetInPinCount()
{
	long n;
	CComQIPtr<IPluginFilter> pluginFilter;
	m_pLayer->get_pluginFilter(&pluginFilter);
	if (pluginFilter)
	{
		pluginFilter->GetInPinCount(&n);
		return n;
	}

	return 0;
}

CFilterPrimitiveElement* CFilterPrimitiveElement::GetInPin(int n)
{
	CComPtr<IPDFilterPrimitive> pe;
	m_pLayer->GetInPin(n, &pe);

	UPOSITION pos = m_parent->m_items.GetHeadPosition();
	while (pos)
	{
		CFilterPrimitiveElement* p = (CFilterPrimitiveElement*)m_parent->m_items.GetNext(pos);
		if (p->m_pLayer == pe)
			return p;

	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CFilterGraphDlg

LRESULT CFilterGraphDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axhorz.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axhorz.AttachControl(m_horz, &p);
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

	IDispEventImpl<2, CFilterGraphDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);
	IDispEventImpl<3, CFilterGraphDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	::RegisterDragDrop(m_hWnd, this);

	return 0;
}

LRESULT CFilterGraphDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::RevokeDragDrop(m_hWnd);

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

	IDispEventImpl<2, CFilterGraphDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
	IDispEventImpl<3, CFilterGraphDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	return 0;
}

LRESULT CFilterGraphDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	HDC hDC = dc.m_hDC;

	CRect client;
	GetClientRect(&client);

	FillSolidRect(hDC, &client, RGB(255, 255, 255));

	int index = 0;

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
	if (m_pLayer)
	{
		if (m_pItemDrag)
		{
			CRect& rc = m_pItemDrag->m_rect;

			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

			Rectangle(hDC, rc.left-1, rc.top-1, rc.right+1, rc.bottom+1);

			SelectObject(hDC, hOldPen);
			DeleteObject(hPen);
		}

		UPOSITION pos = m_pLayer->m_items.GetHeadPosition();
		while (pos)
		{
			CFilterPrimitiveElement* pItem = (CFilterPrimitiveElement*)m_pLayer->m_items.GetNext(pos);

			CRect& rc = pItem->m_rect;

			CUString text;

			if ((int)pItem->m_type < 0)
			{
				text.Format("%s", (char*)pItem->m_name);
			}
			else// if (pItem->m_pLayer)
			{
			//	CElement* pLayer = (CElement*)pItem->m_pLayer;

			//	text.Format("%s(%d) (%d ms)", pItem->m_name, index, pLayer->m_processTime);
				text.Format("%s(%d)", (char*)pItem->m_name, index);

				for (int i = 0; i < pItem->GetInPinCount(); i++)
				{
				// Draw input pin
					{
						CRect rc(pItem->m_rect.left-6, pItem->m_rect.top + 2 + i*8, pItem->m_rect.left, pItem->m_rect.top + 2 + i*8 +6);
						Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
					}

					MoveToEx(hDC, rc.left, rc.top + 2 + 2 + i*8, NULL);

					CFilterPrimitiveElement* pIn;

					if ((m_dragging == 2) && (pItem == m_pItemDrag) && m_inpin == i)
					{
						if (m_pNearItem)
						{
							pIn = m_pNearItem;//->m_pLayer;
						}
						else
						{
							LineTo(hDC, m_oldpt.x, m_oldpt.y);
							pIn = NULL;
						}
					}
					else
					{
						pIn = pItem->GetInPin(i);
					}

					if (pIn)
					{
						CRect* rc2;

						BOOL bPossible = TRUE;

						/*
						if (pIn->m_type == (int)IN_SOURCEGRAPHIC)
						{
							rc2 = &m_pLayer->m_cItems[0]->m_rect;
						}
						else if (pIn->m_type == (int)IN_SOURCEALPHA)
						{
							rc2 = &m_pLayer->m_cItems[1]->m_rect;
						}
						else if (pIn->m_type == (int)IN_BACKGROUNDGRAPHIC)
						{
							rc2 = &m_pLayer->m_cItems[2]->m_rect;
						}
						else if (pIn->m_type == (int)IN_BACKGROUNDALPHA)
						{
							rc2 = &m_pLayer->m_cItems[3]->m_rect;
						}
						else
						*/
						{
						// If we reach the input, everything's okay,
						// if we reach this layer before the input pin, that
						// means the input pin is after us, therefore not possible
							UPOSITION pos = m_pLayer->m_items.GetHeadPosition();
							while (pos)
							{
								CFilterPrimitiveElement* pChild = (CFilterPrimitiveElement*)m_pLayer->m_items.GetNext(pos);
								if (pChild == pIn)
								{
									break;
								}
								else if (pChild == pItem)
								{
									bPossible = FALSE;
								}
							}

							rc2 = &pIn->m_rect;
						}

						HPEN hPen = CreatePen(PS_SOLID, 1, bPossible? RGB(0,0,0): RGB(200,0,0));
						HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

						LineTo(hDC, rc2->right, rc2->bottom-4);

						SelectObject(hDC, hOldPen);
						DeleteObject(hPen);
					}
				}

				index++;
			}

		// Draw output pin
			{
				CRect rc(pItem->m_rect.right, pItem->m_rect.bottom - 2 - 6, pItem->m_rect.right+6, pItem->m_rect.bottom - 2);
				Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
			}

			COLORREF clr;

			if ((int)pItem->m_type < 0)
				clr = RGB(90, 180, 255);
			else
				clr = RGB(190, 190, 190);

			FillSolidRect(hDC, &rc, clr);
			Draw3DRect(hDC, rc.left+1, rc.top+1, rc.Width()-2, rc.Height()-2, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));

			RECT trc = {rc.left+2, rc.top+2, rc.right-2, rc.bottom-2};
			DrawText(hDC, text, lstrlen(text), &trc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
	}

	SelectObject(hDC, hOldFont);

	RestoreDC(hDC, state);

	DeleteObject(hFont);

	return 0;
}

LRESULT CFilterGraphDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	int b = 0;

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	POINT pt = point;
	pt.x += scrollposX;
	pt.y += scrollposY;

	if (!m_dragging)
	{
		CFilterPrimitiveElement* pFItem = NULL;

		m_pNearItem = NULL;

		UPOSITION pos = m_pLayer->m_items.GetTailPosition();
		while (pos)
		{
			CFilterPrimitiveElement* pItem = (CFilterPrimitiveElement*)m_pLayer->m_items.GetPrev(pos);

		//	m_inpin

			if ((long)pItem->m_type > 0)
			{
				for (int i = 0; i < pItem->GetInPinCount(); i++)
				{
					CRect rc(pItem->m_rect.left-6, pItem->m_rect.top + 2 + i*8, pItem->m_rect.left, pItem->m_rect.top + 2 + i*8 +6);
					if (PtInRect(&rc, pt))
					{
						pFItem = pItem;
						m_inpin = i;
						m_dragging = 2;
						break;
					}
				}
			}

			if (PtInRect(pItem->m_rect, pt))
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

	return 0;
}

LRESULT CFilterGraphDlg::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_pItemDrag)
	{
		CComPtr<IPluginFilter> pluginFilter;
		m_pItemDrag->m_pLayer->get_pluginFilter(&pluginFilter);
		if (pluginFilter)
		{
			HRESULT hr = pluginFilter->ShowOptions(GetMainHwnd());
			if (hr == S_OK)
			{
				// TODO invalidate
			}
		}
	}

	return 0;
}

//#include "ESvgDocument.h"

LRESULT CFilterGraphDlg::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nFlags = wParam;

	if (m_dragging)
	{
		ReleaseCapture();

		if (m_pItemDrag)
		{
			if (m_dragging == 1)
			{
				if ((int)m_pItemDrag->m_type > 0)
				{
				//	m_pItemDrag->m_pLayer->SetProp("FGraphPos", MAKEWPARAM(m_pItemDrag->m_rect.left, m_pItemDrag->m_rect.top));
				//	((CEffectCollection*)m_pLayer->GetEffects())->SetActiveEffect(m_pItemDrag->m_pLayer);
#if 0
					m_pLayer->m_pDocument->SetTargetElement(m_pItemDrag, nFlags);
#endif
				}
				else
				{
#if 0
					m_pLayer->m_pDocument->SetTargetElement(NULL, nFlags);
#endif
				}

				OnSize();
				Invalidate();
			}
			else if (m_dragging == 2)
			{
			// Script arranging pins
/*
				BSTR strin;
				if (m_inpin == 0)
					strin = L"in";
				else
					strin = L"in2";

				CComQIPtr<ISVGElement> dragElement = m_pItemDrag->m_domElement;
*/
				if (m_pNearItem)
				{
					m_pItemDrag->m_pLayer->SetInPin(m_inpin, m_pNearItem->m_pLayer);
					/*
					pluginFilter->SetIn
					CComQIPtr<ISVGElement> nearElement = m_pNearItem->m_domElement;
					if (m_pNearItem->m_type < 0)
					{
					}

					BSTR bresult;
					nearElement->getAttribute(L"result", &bresult);
					_bstr_t result = _bstr_t(bresult, false);

					if (result.length() == 0)
					{
						MessageBeep(-1);
					}

					dragElement->setAttribute(strin, result);
					*/
				}
				else
				{
					m_pItemDrag->m_pLayer->SetInPin(m_inpin, NULL);
					//dragElement->removeAttribute(strin);
				}

				Invalidate();
			}
		}

		m_dragging = 0;
	}

	return 0;
}

LRESULT CFilterGraphDlg::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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
			m_pItemDrag->m_rect.OffsetRect(offset.x, offset.y);
		}
		else if (m_dragging == 2)
		{
			CFilterPrimitiveElement* pIn = (CFilterPrimitiveElement*)m_pItemDrag->GetInPin(m_inpin);

			m_pNearItem = NULL;

			UPOSITION pos = m_pLayer->m_items.GetHeadPosition();
			while (pos)
			{
				CFilterPrimitiveElement* pItem = (CFilterPrimitiveElement*)m_pLayer->m_items.GetNext(pos);

				CRect rc(pItem->m_rect.right, pItem->m_rect.bottom - 2 - 6, pItem->m_rect.right+6, pItem->m_rect.bottom - 2);

				if (abs(pt.x-(pItem->m_rect.right+2)) < 16 && abs(pt.y-(pItem->m_rect.bottom-4)) < 16)
				{
					m_pNearItem = pItem;
					break;
				}
			}
		}

		Invalidate();

		m_oldpt = pt;
	}

	return 0;
}

LRESULT CFilterGraphDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	Invalidate();

	return 0;
}

void CFilterGraphDlg::OnSize()
{
	CRect client;
	GetClientRect(&client);

	int sbHeight = GetSystemMetrics(SM_CYHSCROLL);
	int sbWidth = GetSystemMetrics(SM_CXVSCROLL);

	int maxx = 0;
	int maxy = 0;

	if (m_pLayer)
	{
		UPOSITION pos = m_pLayer->m_items.GetHeadPosition();
		while (pos)
		{
			CFilterPrimitiveElement* pItem = (CFilterPrimitiveElement*)m_pLayer->m_items.GetNext(pos);

			CRect& rc = pItem->m_rect;
			maxx = max(maxx, rc.right);
			maxy = max(maxy, rc.bottom);
		}
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

	if (maxy > m_areaRect.bottom)
	{
		m_areaRect.right -= sbWidth;
		bVertSB = TRUE;
	}

	if (!bHorzSB)
	{
		if (maxx > m_areaRect.right)
		{
			m_areaRect.bottom -= sbHeight;
			bHorzSB = TRUE;
		}
	}

	if (bVertSB)
	{
		m_vert->SetInfo(0, maxy, m_areaRect.Height());

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
		m_horz->SetInfo(0, maxx, m_areaRect.Width());

		m_axhorz.MoveWindow(0, m_areaRect.bottom, m_areaRect.Width(), sbHeight);
		m_axhorz.ShowWindow(SW_SHOW);
	}
	else
	{
		m_horz->SetInfo(0, 0, 0);
		m_axhorz.ShowWindow(SW_HIDE);
	}
}

HRESULT __stdcall CFilterGraphDlg::OnHorzScroll(long code, long pos)
{
	long oldPos; m_horz->get_pos(&oldPos);

	CRect	rect = m_areaRect;

	m_horz->put_pos(pos);
	ScrollWindow((oldPos-pos), 0, &rect, &rect);

	return S_OK;
}

HRESULT __stdcall CFilterGraphDlg::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	CRect	rect = m_areaRect;
	
	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &rect, &rect);

	return S_OK;
}

void CFilterGraphDlg::BuildItems()
{
	delete m_pLayer;

	m_pLayer = new CFilter;

	CPDAppearance* pFilter = static_cast<CPDAppearance*>(m_filter.p);

	CFilterPrimitiveElement* pItem;

	pItem = new CFilterPrimitiveElement(pFilter->m_cItems[0]);
	pItem->m_type = (int)IN_SOURCEGRAPHIC;
	pItem->m_parent = m_pLayer;
	m_pLayer->m_items.AddTail(pItem);

	pItem = new CFilterPrimitiveElement(pFilter->m_cItems[1]);
	pItem->m_type = (int)IN_SOURCEALPHA;
	pItem->m_parent = m_pLayer;
	m_pLayer->m_items.AddTail(pItem);

	pItem = new CFilterPrimitiveElement(pFilter->m_cItems[2]);
	pItem->m_type = (int)IN_BACKGROUNDGRAPHIC;
	pItem->m_parent = m_pLayer;
	m_pLayer->m_items.AddTail(pItem);

	pItem = new CFilterPrimitiveElement(pFilter->m_cItems[3]);
	pItem->m_type = (int)IN_BACKGROUNDALPHA;
	pItem->m_parent = m_pLayer;
	m_pLayer->m_items.AddTail(pItem);

	pItem = new CFilterPrimitiveElement(pFilter->m_cItems[4]);
	pItem->m_type = (int)-7;
	pItem->m_parent = m_pLayer;
	m_pLayer->m_items.AddTail(pItem);

	CComPtr<IObjectMap> filterEffects;
	m_filter->get_filterEffects(&filterEffects);

	long nfilters;
	filterEffects->get_length(&nfilters);

	for (int i = 0; i < nfilters; i++)
	{
		CComPtr<IPDFilterPrimitive> primitive;
		filterEffects->item(i, (IUnknown**)&primitive);

		pItem = new CFilterPrimitiveElement(primitive);
		pItem->m_parent = m_pLayer;
	//	pItem->m_pLayer = pLayer;
	//	pLayer->m_pItemUI = pItem;
	//	DWORD pos = pLayer->GetProp("FGraphPos");
	//	OffsetRect(&pItem->m_rect, (short)LOWORD(pos), (short)HIWORD(pos));

		pItem->m_type = 1;

		m_pLayer->m_items.AddTail(pItem);
	}
}

STDMETHODIMP CFilterGraphDlg::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
//	*pdwEffect = DROPEFFECT_MOVE;

	//m_insertObjectsOnLayerIndex = -1;

	return DragOver(grfKeyState, ptl, pdwEffect);

//	return S_OK;
}

STDMETHODIMP CFilterGraphDlg::DragLeave()
{
	/*
	if (m_insertObjectsOnLayerIndex >= 0)	// Erase old
	{
		DrawDragLayerMarker(m_insertObjectsOnLayerIndex);
		m_insertObjectsOnLayerIndex = -1;
	}
	*/

	return S_OK;
}

STDMETHODIMP CFilterGraphDlg::DragOver(DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

/*	if (m_insertObjectsOnLayerIndex >= 0)	// Erase old
	{
		DrawDragLayerMarker(m_insertObjectsOnLayerIndex);
	}
*/
	POINT point;
	point.x = ptl.x;
	point.y = ptl.y;
	ScreenToClient(&point);

	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	point.y += scrollposY;

	*pdwEffect = DROPEFFECT_COPY;

	return S_OK;
}

#include "PageDesignerApp.h"
extern CPageDesignerApp* gApp;

STDMETHODIMP CFilterGraphDlg::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

	COleDataObjectWrapper dataObject;
	dataObject.Attach(pDataObject);

	HGLOBAL hData;

	if (hData = dataObject.GetGlobalData(RegisterClipboardFormat(_T("PageDesigner-Effect-Guid"))))
	{
		CLSID* pguid = (CLSID*)GlobalLock(hData);

		if (m_pLayer)
		{
			CPluginFilterClass* pClass = NULL;
			for (int i = 0; i < gApp->m_pluginFilters.GetSize(); i++)
			{
				CPluginFilterClass* pPluginFilterClass = gApp->m_pluginFilters[i];
				if (pPluginFilterClass->m_clsid == *pguid)
				{
					pClass = pPluginFilterClass;
					break;
				}
			}

			if (pClass)
			{
				CComPtr<IPluginFilter> pluginfilter;
				pluginfilter.CoCreateInstance(pClass->m_clsid);
				if (pluginfilter)
				{
					pluginfilter->SetPluginFilterClass(pClass);

					CComObject<CPDFilterPrimitive>* pFilterPrimitive;
					CComObject<CPDFilterPrimitive>::CreateInstance(&pFilterPrimitive);
					if (pFilterPrimitive)
					{
						pFilterPrimitive->m_name = pClass->m_name;
						pFilterPrimitive->put_pluginFilter(pluginfilter);

						m_filter->insertEffect(pFilterPrimitive, NULL);

						BuildItems();

						OnSize();
						Invalidate();

						*pdwEffect = DROPEFFECT_COPY;
					}
				}
			}
		}

		GlobalUnlock(hData);
	}

	return S_OK;
}

STDMETHODIMP CFilterGraphDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IPDDocumentView> view = object;
	if (view)
	{
		ATLASSERT(m_view == NULL);	// Assume only one active view at a time
		m_view = static_cast<CComObject<CPDDocumentView>*>(view.p);
		m_view->AddRef();
//		IDispEventImpl<3, CLayersDlg, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventAdvise(m_view->m_document);

		/*
		if (!IsLayerSelected(m_view->m_activeLayer))
		{
			SelectLayer(m_view->m_activeLayer);
		}
		*/

		{
			CComQIPtr<INotifySend> cp = m_view->m_document;
			DWORD cookie;
			cp->Advise(this, &cookie);
		}

		*cookie = 1;
	}
	else
	{
		CComQIPtr<IPDObjectWithAppearance> objectWithAppearance = object;
		if (objectWithAppearance)
		{
			if (m_filter)	// Keep track of only one at once
			{
				m_filter.Release();

				delete m_pLayer;
				m_pLayer = NULL;
			}

			objectWithAppearance->get_appearance(&m_filter);
			*cookie = 1;

			BuildItems();
		}
	}

	if (m_hWnd)
	{
		OnSize();
		Invalidate();
	}

	return S_OK;
}

STDMETHODIMP CFilterGraphDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	if (IsUnknownEqualUnknown((IPDDocumentView*)m_view, object))
	{
		ATLASSERT(cookie == 1);
		ATLASSERT(m_view != NULL);

		CComQIPtr<INotifySend> cp = m_view->m_document;
		cp->Unadvise(this);

		m_view->Release();
		m_view = NULL;
	}
	else if (IsUnknownEqualUnknown(m_filter, object))
	{
		m_filter.Release();

		delete m_pLayer;
		m_pLayer = NULL;
	}

	if (m_hWnd)
	{
		OnSize();
		Invalidate();
	}

	return S_OK;
}
