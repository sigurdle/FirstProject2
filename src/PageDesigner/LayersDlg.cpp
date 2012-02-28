// LayersDlg.cpp : Implementation of CLayersDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "LayersDlg.h"

//#include "PageDesignerApp.h"
//#include "PageDesignerFrame.h"

#include "PDDocumentView.h"

#include "PDObjectSelected.h"

#include "LayerOptionsDlg.h"

//extern CPageDesignerApp* gApp;

/////////////////////////////////////////////////////////////////////////////
// CLayersDlg

static int m_itemHeight = 20;

int CLayersDlg::FinalConstruct()
{
	HRESULT hr;

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->FindMenu(IDR_LAYERS, &m_menu);

	hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
	if (FAILED(hr)) return hr;
	m_vert->put_direction(1);

	return S_OK;
}

bool CLayersDlg::AnySelectedObjectsOnLayer(IPDLayer* layer)
{
	for (int i = 0; i < m_view->m_targetObjects.GetSize(); i++)
	{
		CComPtr<IPDLayer> objectLayer;
		m_view->m_targetObjects[i]->m_object->get_layer(&objectLayer);

		if (IsUnknownEqualUnknown(layer, objectLayer))
		{
			return true;
		}
	}

	return false;
}

LRESULT CLayersDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);

	if (m_view)
	{
		HBITMAP m_hVisibleBm = LoadBitmap(_Module.m_hInstResource, MAKEINTRESOURCE(IDB_VISIBLE));
		HBITMAP m_hLockedBm = LoadBitmap(_Module.m_hInstResource, MAKEINTRESOURCE(IDB_LOCKED));
		HBITMAP m_hActiveLayerBm = LoadBitmap(_Module.m_hInstResource, MAKEINTRESOURCE(IDB_ACTIVELAYER));

		int state = SaveDC(hDC);

		HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

		LOGFONT lf;
		GetObject(hFont, sizeof(lf), &lf);
		lf.lfWeight = FW_BOLD;

		HFONT hFontSelected = CreateFontIndirect(&lf);
		HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

//		HFONT hOldFont = (HFONT)SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));

		long scrollposY; m_vert->get_pos(&scrollposY);

		if (IntersectClipRect(hDC, m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom))
		{
			POINT oldOrg;
			SetViewportOrgEx(hDC, m_areaRect.left, m_areaRect.top - scrollposY, &oldOrg);

			CComPtr<IObjectMap> layers;
			m_view->m_document->get_layers(&layers);

			long nlayers;
			layers->get_length(&nlayers);

			int y = 0;

			for (long nlayer = nlayers-1; nlayer >= 0; nlayer--)
			{
				CComQIPtr<IPDLayer> layer;
				layers->item(nlayer, (IUnknown**)&layer);

				BSTR bname;
				layer->get_name(&bname);
				_bstr_t name = _bstr_t(bname, false);

				VARIANT_BOOL bVisible;
				layer->get_visible(&bVisible);

				VARIANT_BOOL bLocked;
				layer->get_locked(&bLocked);

				OLE_COLOR	color;
				layer->get_color(&color);

				MoveToEx(hDC, 0, y+m_itemHeight-1, NULL);
				LineTo(hDC, m_areaRect.right, y+m_itemHeight-1);

				MoveToEx(hDC, 36, y, NULL);
				LineTo(hDC, 36, y+m_itemHeight-1);

				FillSolidRect(hDC, 1, y+1, 34, m_itemHeight-2, GetSysColor(COLOR_BTNFACE));
				Draw3DRect(hDC, 0, y+1, 36, m_itemHeight-2, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));

				Draw3DRect(hDC, 4, y+3, 13, 13, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
				if (bVisible)
					TransparentBlt(hDC, 5, y+4, 11, 11, m_hVisibleBm, 0, 0, RGB(192, 192, 192));

				Draw3DRect(hDC, 19, y+3, 13, 13, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
				if (bLocked)
					TransparentBlt(hDC, 20, y+4, 11, 11, m_hLockedBm, 0, 0, RGB(192, 192, 192));

				if (IsLayerSelected(layer)/* || (m_view->m_activeLayer == layer)*/)
				{
					SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
					SetBkColor(hDC, GetSysColor(COLOR_HIGHLIGHT));
					SelectObject(hDC, hFontSelected);
				}
				else
				{
					SetTextColor(hDC, GetSysColor(COLOR_WINDOWTEXT));
					SetBkColor(hDC, GetSysColor(COLOR_WINDOW));
					SelectObject(hDC, hFont);
				}

				CRect trect(36, y+1, m_areaRect.right, y+m_itemHeight-1);
				FillSolidRect(hDC, &trect, GetBkColor(hDC));

				FillSolidRect(hDC, 36+4, y+4, 10, 10, color);

				trect.left += 4+12;
				DrawText(hDC, name, name.length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);

				if (m_view->m_activeLayer == layer)
				{
					TransparentBlt(hDC, trect.right-28, y+(m_itemHeight-16)/2, 16, 16, m_hActiveLayerBm, 0, 0, RGB(192, 192, 192));
				}

				if (AnySelectedObjectsOnLayer(layer))
				{
					HBRUSH hBrush = CreateSolidBrush(color);
					HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

					Rectangle(hDC, trect.right-10, trect.top+trect.Height()/2-2, trect.right-5, trect.top+trect.Height()/2+3);

					SelectObject(hDC, hOldBrush);
					DeleteObject(hBrush);
				}

				y += m_itemHeight;
			}

			SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);
		}

		SelectObject(hDC, hOldFont);

		DeleteObject(hFont);
		DeleteObject(hFontSelected);

		RestoreDC(hDC, state);

		DeleteObject(m_hVisibleBm);
		DeleteObject(m_hLockedBm);
		DeleteObject(m_hActiveLayerBm);
	}

	EndPaint(&ps);
	return 0;
}

LRESULT CLayersDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CLayersDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	RegisterDragDrop(m_hWnd, static_cast<IDropTarget*>(this));

	return 0;
}

LRESULT CLayersDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

	IDispEventImpl<1, CLayersDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	RevokeDragDrop(m_hWnd);

	return 0;
}

LRESULT CLayersDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_view)
	{
		POINT pt = point;
		pt.y -= m_areaRect.top;
		pt.y += scrollposY;

		CComPtr<IObjectMap> layers;
		m_view->m_document->get_layers(&layers);

		long nlayers;
		layers->get_length(&nlayers);

		int layerIndex = nlayers - pt.y/m_itemHeight - 1;

		if (layerIndex >= 0 && layerIndex < nlayers)
		{
			int top = (nlayers - layerIndex - 1)*m_itemHeight;

			CComQIPtr<IPDLayer> layer;
			layers->item(layerIndex, (IUnknown**)&layer);

			if (pt.x < 36)
			{
				CRect vrc(4, top+3, 4+13, top+13);
				if (vrc.PtInRect(pt))
				{
					VARIANT_BOOL bVisible;
					layer->get_visible(&bVisible);

					layer->put_visible(bVisible? VARIANT_FALSE: VARIANT_TRUE);
				}

				CRect lrc(19, top+3, 19+13, top+13);
				if (lrc.PtInRect(point))
				{
					VARIANT_BOOL bLocked;
					layer->get_locked(&bLocked);

					layer->put_locked(bLocked? VARIANT_FALSE: VARIANT_TRUE);
				}
			}
			else if (pt.x > m_areaRect.Width()-12)
			{
				if (AnySelectedObjectsOnLayer(layer))
				{
				// Start of dragging objects between layers

					m_insertObjectsFromLayerIndex = layerIndex;
					m_insertObjectsOnLayerIndex = layerIndex;

					DrawSelectedObjectsMarker(m_insertObjectsOnLayerIndex);

					m_dragging = 1;
					SetCapture();
				}
			}
			else
			{
				bool bSelected = IsLayerSelected(layer);

				if (nFlags & MK_CONTROL)	// Toggle selected
				{
					if (bSelected)
					{
						DeselectLayer(layer);
					}
					else
					{
						SelectLayer(layer);
						if (m_selectedLayerIndex == -1) m_selectedLayerIndex = layerIndex;

						m_view->m_activeLayer = layer;

						//Fire_ClickSwatch(swatch);
					}

					Invalidate();
				}
				else
				{
					long startSel, endSel;

					if (!(nFlags & MK_SHIFT) || (m_selectedLayerIndex == -1))
					{
						startSel = endSel = layerIndex;
					}
					else if (layerIndex > m_selectedLayerIndex)
					{
						startSel = m_selectedLayerIndex;
						endSel = layerIndex;
					}
					else
					{
						startSel = layerIndex;
						endSel = m_selectedLayerIndex;
					}

					DeselectAll();

					for (long i = startSel; i <= endSel; i++)
					{
						CComPtr<IPDLayer> layer;
						layers->item(i, (IUnknown**)&layer);

						SelectLayer(layer);
					}

					if (!(nFlags & MK_SHIFT) || (m_selectedLayerIndex == -1))
						m_selectedLayerIndex = layerIndex;

				//	Fire_ClickSwatch(swatch);
					m_view->m_activeLayer = layer;

					Invalidate();
					UpdateWindow();

					ATLASSERT(m_insertObjectsOnLayerIndex == -1);

					{
						GUID guid;
						layer->get_uniqId(&guid);

						HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(GUID));

						if (hData)
						{
							GUID* p = (GUID*)GlobalLock(hData);
							*p = guid;
							GlobalUnlock(hData);

							CMyDropSource*  dropSource = new CMyDropSource;
							CMyDataObject* dataObject = new CMyDataObject;

							STGMEDIUM	stg = {0};
							stg.tymed = TYMED_HGLOBAL;
							stg.hGlobal = hData;
							stg.pUnkForRelease = NULL;
							
							FORMATETC	etc = {0};
							etc.cfFormat = RegisterClipboardFormat(_T("PageDesigner-Layer-Guid"));
							etc.tymed = TYMED_HGLOBAL;
							etc.ptd = NULL;
							etc.dwAspect = DVASPECT_CONTENT;
							etc.lindex = -1;

							dataObject->SetData(&etc, &stg, TRUE);

							DWORD dropEffect = 0;
							HRESULT hr = ::DoDragDrop(dataObject, dropSource, DROPEFFECT_LINK | DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect);

							if (hr == DRAGDROP_S_DROP)
							{
								if (dropEffect/* & DROPEFFECT_MOVE*/)
								{
								}
							}

							GlobalFree(hData);

						//	delete dataObject;
						//	delete dropSource;

				#if 0
							COleDataSource source;
							source.CacheGlobalData(CF_HDROP, hData, NULL);

							if (source.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, NULL, NULL) == DROPEFFECT_COPY)
							{
							}

							source.Empty();
				#endif
						}
					}
				}
			}
		}
	}

	return 0;
}

LRESULT CLayersDlg::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_view)
	{
		POINT pt = point;
		pt.y -= m_areaRect.top;
		pt.y += scrollposY;

		CComPtr<IObjectMap> layers;
		m_view->m_document->get_layers(&layers);

		long nlayers;
		layers->get_length(&nlayers);

		int index = nlayers - pt.y/m_itemHeight - 1;

		if (index >= 0 && index < nlayers)
		{
			CComQIPtr<IPDLayer> layer;
			layers->item(index, (IUnknown**)&layer);

			if (point.x >= 36)
			{
				ShowLayerOptions();
			}
		}
	}

	return 0;
}

LRESULT CLayersDlg::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = 0;

		DrawSelectedObjectsMarker(m_insertObjectsOnLayerIndex);

		CComPtr<IObjectMap> layers;
		m_view->m_document->get_layers(&layers);

		long nlayers;
		layers->get_length(&nlayers);

		if (m_insertObjectsOnLayerIndex >= 0 && m_insertObjectsOnLayerIndex < nlayers)
		{
			if (m_insertObjectsFromLayerIndex != m_insertObjectsOnLayerIndex)
			{
				CComPtr<IPDLayer> fromlayer;
				layers->item(m_insertObjectsFromLayerIndex, (IUnknown**)&fromlayer);

				CComPtr<IPDLayer> tolayer;
				layers->item(m_insertObjectsOnLayerIndex, (IUnknown**)&tolayer);

				CComPtr<IPDObjectLayerGroup> toLayerGroup;
				m_view->m_activeSpread->getLayerGroupFromLayer(tolayer, &toLayerGroup);

				CComPtr<IPDGuides> toGuides;
				toLayerGroup->get_guides(&toGuides);

				for (int i = 0; i < m_view->m_targetObjects.GetSize(); i++)
				{
					CComPtr<IPDLayer> objectLayer;
					m_view->m_targetObjects[i]->m_object->get_layer(&objectLayer);

					if (IsUnknownEqualUnknown(fromlayer, objectLayer))
					{
						PDObjectType objectType;
						m_view->m_targetObjects[i]->m_object->get_objectType(&objectType);

						if (objectType == OBJECT_GUIDE)
						{
							toGuides->appendGuide((IPDGuide*)m_view->m_targetObjects[i]->m_object);
						}
						else
						{
							toLayerGroup->appendObject((IPDObject*)m_view->m_targetObjects[i]->m_object);
						}
					}
				}

				m_view->Invalidate();

				Invalidate();
			}
		}

		m_insertObjectsOnLayerIndex = -1;
	}

	return 0;
}

LRESULT CLayersDlg::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_dragging)
	{
		long scrollposY; m_vert->get_pos(&scrollposY);

		POINT pt = point;
		pt.y -= m_areaRect.top;
		pt.y += scrollposY;

		CComPtr<IObjectMap> layers;
		m_view->m_document->get_layers(&layers);

		long nlayers;
		layers->get_length(&nlayers);

		DrawSelectedObjectsMarker(m_insertObjectsOnLayerIndex);

		m_insertObjectsOnLayerIndex = nlayers - pt.y/m_itemHeight - 1;

		DrawSelectedObjectsMarker(m_insertObjectsOnLayerIndex);
	}

	return 0;
}

STDMETHODIMP CLayersDlg::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_MOVE;

	m_insertObjectsOnLayerIndex = -1;

	return DragOver(grfKeyState, ptl, pdwEffect);

//	return S_OK;
}

STDMETHODIMP CLayersDlg::DragLeave()
{
	if (m_insertObjectsOnLayerIndex >= 0)	// Erase old
	{
		DrawDragLayerMarker(m_insertObjectsOnLayerIndex);
		m_insertObjectsOnLayerIndex = -1;
	}

	return S_OK;
}

STDMETHODIMP CLayersDlg::DragOver(DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

	if (m_insertObjectsOnLayerIndex >= 0)	// Erase old
	{
		DrawDragLayerMarker(m_insertObjectsOnLayerIndex);
	}

	POINT point;
	point.x = ptl.x;
	point.y = ptl.y;
	ScreenToClient(&point);

	long scrollposY; m_vert->get_pos(&scrollposY);

	point.y += scrollposY;

	if (m_view != NULL)
	{
		CComPtr<IObjectMap> layers;
		m_view->m_document->get_layers(&layers);

		long nlayers;
		layers->get_length(&nlayers);

		long layerIndex = nlayers - ((point.y+m_itemHeight/2)/m_itemHeight);
		if (layerIndex < 0) layerIndex = 0;
		else if (layerIndex > nlayers) layerIndex = nlayers;

		if (layerIndex >= 0)
		{
			m_insertObjectsOnLayerIndex = layerIndex;

		// Draw New
			DrawDragLayerMarker(m_insertObjectsOnLayerIndex);

			*pdwEffect = DROPEFFECT_MOVE;
		}
	}

	return S_OK;
}

STDMETHODIMP CLayersDlg::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL ptl, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_NONE;

	if (m_insertObjectsOnLayerIndex >= 0)
	{
	// Erase old
		DrawDragLayerMarker(m_insertObjectsOnLayerIndex);

		COleDataObjectWrapper dataObject;
		dataObject.Attach(pDataObject);

		HGLOBAL hData;

		CComPtr<IObjectMap> layers;
		m_view->m_document->get_layers(&layers);

		long nlayers;
		layers->get_length(&nlayers);

		if (hData = dataObject.GetGlobalData(RegisterClipboardFormat(_T("PageDesigner-Layer-Guid"))))
		{
			GUID* pguid = (GUID*)GlobalLock(hData);

			CComPtr<IPDLayer> layer;
			m_view->m_document->getLayerByUniqId(*pguid, &layer);

			CComPtr<IPDLayer> beforeLayer;

			if (m_insertObjectsOnLayerIndex < nlayers)
				layers->item(m_insertObjectsOnLayerIndex, (IUnknown**)&beforeLayer);
			else
				beforeLayer = NULL;

			if (!IsUnknownEqualUnknown(layer, beforeLayer))
			{
				CComPtr<IPDLayer> nextLayer;
				layer->get_nextSibling(&nextLayer);
				if (!IsUnknownEqualUnknown(nextLayer, beforeLayer))
				{
					m_view->m_document->insertLayerBefore(layer, beforeLayer);
				}
			}

			GlobalUnlock(hData);
		}

		m_insertObjectsOnLayerIndex = -1;
	}

	return S_OK;
}

void CLayersDlg::DrawDragLayerMarker(long index)
{
	long scrollposY; m_vert->get_pos(&scrollposY);

	CComPtr<IObjectMap> layers;
	m_view->m_document->get_layers(&layers);

	long nlayers;
	layers->get_length(&nlayers);

	HDC hDC = GetDC();

	int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

	int x = m_areaRect.right - 7;
	int y = (nlayers-index)*m_itemHeight + m_areaRect.top - scrollposY;

	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0,0,0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	MoveToEx(hDC, 0, y-2, NULL);
	LineTo(hDC, m_areaRect.Width(), y-2);

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);

	SetROP2(hDC, oldR2);

	ReleaseDC(hDC);
}

void CLayersDlg::DrawSelectedObjectsMarker(long index)
{
	long scrollposY; m_vert->get_pos(&scrollposY);

	CComPtr<IObjectMap> layers;
	m_view->m_document->get_layers(&layers);

	long nlayers;
	layers->get_length(&nlayers);

	HDC hDC = GetDC();

	int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

	int x = m_areaRect.right - 7;
	int y = (nlayers-index-1)*m_itemHeight + m_areaRect.top - scrollposY;

	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0,0,0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

	Rectangle(hDC, x-2, y+m_itemHeight/2-2, x+4, y+m_itemHeight/2+4);

	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);

	SetROP2(hDC, oldR2);

	ReleaseDC(hDC);
}

void CLayersDlg::ShowLayerOptions()
{
	if (m_view)
	{
		if (m_selectedLayers.GetSize() > 0)
		{
			CLayerOptionsDlg dlg;
			for (int i = 0; i < m_selectedLayers.GetSize(); i++)
			{
				dlg.m_targetObjects.Add(m_selectedLayers[i]);
			}

			if (dlg.DoModal(GetMainHwnd()) == IDOK)
			{
			}
		}
	}
}

LRESULT CLayersDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	Invalidate();
	OnSize();

	return 0;
}

void CLayersDlg::OnSize()
{
	CRect client;
	GetClientRect(&client);

	m_areaRect = client;
	m_areaRect.InflateRect(-1, -1);

	long nlayers = 0;

	if (m_view)
	{
		CComPtr<IObjectMap> layers;
		m_view->m_document->get_layers(&layers);

		layers->get_length(&nlayers);
	}

	int height = nlayers*m_itemHeight;

	if (height > m_areaRect.Height())
	{
		m_areaRect.right -= 16;

		m_axvert.MoveWindow(m_areaRect.right, 0, 16, m_areaRect.bottom);
		m_vert->SetInfo(0, height, m_areaRect.Height());
	}
	else
	{
		m_axvert.MoveWindow(0, 0, 0, 0);
		m_vert->SetInfo(0, 0, m_areaRect.Height());
	}
}

/*
void __stdcall CLayersDlg::OnLayerOptionsChanged(IPDLayer* layer)
{
	OnSize();
	Invalidate();
}
*/

// ICommandTarget
STDMETHODIMP CLayersDlg::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try view
	CComQIPtr<ICommandTarget> view = m_view;
	if (view) view->OnCmdMsg(nID, nCode, pCmdUI, bHandled);

	return S_OK;
}

STDMETHODIMP CLayersDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IPDDocumentView> view = object;
	if (view)
	{
		ATLASSERT(m_view == NULL);	// Assume only one active view at a time
		m_view = static_cast<CComObject<CPDDocumentView>*>(view.p);
		m_view->AddRef();
//		IDispEventImpl<3, CLayersDlg, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventAdvise(m_view->m_document);

		if (!IsLayerSelected(m_view->m_activeLayer))
		{
			SelectLayer(m_view->m_activeLayer);
		}

		{
			CComQIPtr<INotifySend> cp = m_view->m_document;
			DWORD cookie;
			cp->Advise(this, &cookie);
		}

		if (m_hWnd)
		{
			OnSize();
			Invalidate();
		}

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CLayersDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ATLASSERT(cookie == 1);
	ATLASSERT(m_view != NULL);

	DeselectAll();

	CComQIPtr<INotifySend> cp = m_view->m_document;
	cp->Unadvise(this);

//	IDispEventImpl<3, CLayersDlg, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventUnadvise(m_view->m_document);
	m_view->Release();
	m_view = NULL;

	if (m_hWnd)
	{
		OnSize();
		Invalidate();
	}

	return S_OK;
}

HRESULT __stdcall CLayersDlg::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &m_areaRect, &m_areaRect);

	return S_OK;
}

BEGIN_CMD_MAP(CLayersDlg)
	CMD_HANDLER(ID_LAYERS_LAYEROPTIONS, OnLayerOptions)
	CMD_HANDLER(ID_LAYERS_DELETE, OnLayerDelete)
	CMD_UPDATE(ID_LAYERS_DELETE, OnLayerDeleteUpdate)
END_CMD_MAP()

#include "LayerOptionsDlg.h"

LRESULT CLayersDlg::OnLayerOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ShowLayerOptions();

	return 0;
}

LRESULT CLayersDlg::OnLayerDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_view)
	{
		CComPtr<IObjectMap> layers;
		m_view->m_document->get_layers(&layers);

		long nlayers;
		layers->get_length(&nlayers);

		if ((m_selectedLayers.GetSize() > 0) && (m_selectedLayers.GetSize() < nlayers))
		{
			for (int i = m_selectedLayers.GetSize()-1; i >= 0; i--)
			{
				m_view->m_document->deleteLayer(m_selectedLayers[i]);
			}

			m_selectedLayers.RemoveAll();

			Invalidate();	// TODO remove
			m_view->Invalidate();	// TODO remove
		}
	}

	return 0;
}

void CLayersDlg::OnLayerDeleteUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;
	if (m_view)
	{
		CComPtr<IObjectMap> layers;
		m_view->m_document->get_layers(&layers);

		long nlayers;
		layers->get_length(&nlayers);

		if ((m_selectedLayers.GetSize() > 0) && (m_selectedLayers.GetSize() < nlayers))
		{
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
}
