// AppearanceDlg.cpp : Implementation of CAppearanceDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "AppearanceDlg.h"
#include "PDDocumentView.h"

_bstr_t CreateValueUnitString(double specifiedValue, short unitType);

#define ATTR_OPACITY		-1
#define ATTR_COLOR		-2

class CAppearanceElement : public C2Obj
{
public:
//	CComQIPtr<IPDObject> m_object;
	CComPtr<IUnknown> m_object;

	bool m_activated;

	CAppearanceElement()
	{
		m_activated = false;
//		m_object = NULL;
	}
};

class CAppearanceObject : public CAppearanceElement
{
public:
	CUPtrList m_attrs;

	void BuildEffects();
};

class CAppearanceAttr : public CAppearanceElement
{
public:
	long m_type;

	CAppearanceAttr()
	{
		m_type = 0;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CAppearanceDlg

int CAppearanceDlg::FinalConstruct()
{
	HRESULT hr;

	hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
	if (FAILED(hr)) return hr;
	m_vert->put_direction(1);

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->FindMenu(IDR_APPEARANCE, &m_menu);

	return S_OK;
}

LRESULT CAppearanceDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CAppearanceDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	return 0;
}

LRESULT CAppearanceDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

	IDispEventImpl<1, CAppearanceDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	return 0;
}

Gdiplus::Brush* GetGdiBrush(IPDBrush* brush, PDBrushType brushType = BRUSH_NONE);

LRESULT CAppearanceDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_pTree)
	{
		if (dc.IntersectClipRect(m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom))
		{
			CPoint oldOrg = dc.SetViewportOrg(m_areaRect.left, m_areaRect.top -scrollposY);
			dc.SetBkMode(TRANSPARENT);

			HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

			LOGFONT lf;

			GetObject(hFont, sizeof(lf), &lf);
			lf.lfWeight = FW_BOLD;
			HFONT hFontSelected = CreateFontIndirect(&lf);

			GetObject(hFont, sizeof(lf), &lf);
			lf.lfItalic = TRUE;
			HFONT hFontItalic = CreateFontIndirect(&lf);

			HFONT hOldFont = dc.GetCurrentFont();

			CComQIPtr<IPDObjectWithAppearance> withAppearance = m_object;
			CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> withAppearanceStrokeFill = m_object;

			CComPtr<IPDObjectStroke> activeStroke;
			CComPtr<IPDObjectFill> activeFill;
			if (withAppearanceStrokeFill)
			{
				withAppearanceStrokeFill->get_activeStroke(&activeStroke);
				withAppearanceStrokeFill->get_activeFill(&activeFill);
			}

			C2Obj* pParentItem = m_pTree;
			UPOSITION pos = pParentItem->GetHeadPosition();
			int nextlevel = 0;

			int y = 0;

			while (pos)
			{
				int level = nextlevel;
				CAppearanceObject* pItem = (CAppearanceObject*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

				int x = level*10;

				CRect itemrect(x, y, m_areaRect.Width(), y+16);

				if (pItem->m_selected)
				{
					FillSolidRect(dc.m_hDC, &itemrect, GetSysColor(COLOR_HIGHLIGHT));
					dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
					dc.SelectFont(hFontSelected);
				}
				else
				{
					dc.SelectFont(hFont);
					dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
				}

				dc.DrawText(pItem->m_name, pItem->m_name.length(), &itemrect, DT_SINGLELINE | DT_VCENTER);

				if (!pItem->m_childList.IsEmpty() || !pItem->m_attrs.IsEmpty())
				{
					int xo = itemrect.left-8;
					int yo = itemrect.top+3;

					if (pItem->m_expanded)
					{
						POINT pts[3] =
						{
							xo, yo, 
							xo+6, yo,
							xo+3, yo+6
						};

						dc.Polygon(pts, 3);
					}
					else
					{
						POINT pts[3] =
						{
							xo, yo,
							xo, yo+6,
							xo+3, yo+3
						};

						dc.Polygon(pts, 3);
					}
				}

				if (pItem->m_expanded)
				{
					dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
					dc.SelectFont(hFont);

					UPOSITION pos2 = pItem->m_attrs.GetHeadPosition();
					while (pos2)
					{
						int x2 = x + 10;
						y += 16;

						CAppearanceAttr* pAttr = (CAppearanceAttr*)pItem->m_attrs.GetNext(pos2);
						CRect itemrect(x2, y, m_areaRect.Width(), y+16);

						dc.DrawText(pAttr->m_name, pAttr->m_name.length(), &itemrect, DT_SINGLELINE | DT_VCENTER);

						if (pAttr->m_type == ATTR_OPACITY)
						{
							CComQIPtr<IPDOpacityAndBlendMode> objectWithOpacity = pItem->m_object;

							double opacity;
							objectWithOpacity->get_opacity(&opacity);

							CUString str;
							str.Format("%g %%", opacity*100);

							CRect trect = itemrect;
							trect.left += 64;
							dc.DrawText(str, str.GetLength(), &trect, DT_SINGLELINE | DT_VCENTER);
						}
						else if (pAttr->m_type == ATTR_COLOR)
						{
							CComQIPtr<IPDObjectWithBrush> objectWithBrush = pItem->m_object;
							if (objectWithBrush)
							{
								CRect rc(itemrect.left+64, itemrect.top+4, itemrect.left+64+8, itemrect.top+4+8);

								if (IsUnknownEqualUnknown(objectWithBrush, activeStroke) ||
									IsUnknownEqualUnknown(objectWithBrush, activeFill))
								{
									dc.Rectangle(rc.left-2, rc.top-2, rc.right+2, rc.bottom+2);
								}

								Gdiplus::Graphics graphics(dc.m_hDC);

								CComPtr<IPDBrush> brush;
								objectWithBrush->get_brush(&brush);
								Gdiplus::Brush* pBrush = GetGdiBrush(brush);
								if (pBrush)
								{
									graphics.FillRectangle(pBrush, rc.left, rc.top, rc.Width(), rc.Height());
									delete pBrush;
								}
							}

							CComQIPtr<IPDObjectStroke> stroke = pItem->m_object;
							if (stroke)
							{
								CComQIPtr<IPDStrokeSettings> stroke2 = stroke;

								double strokeWeight;
								stroke2->get_strokeWeight(&strokeWeight);

								_bstr_t s = CreateValueUnitString(strokeWeight, UNIT_PT);

								CRect trect = itemrect;
								trect.left += 80;
								dc.DrawText(s, s.length(), &trect, DT_SINGLELINE | DT_VCENTER);
							}
						}
					}
				}
				else
				{
					CComQIPtr<IPDObjectWithBrush> objectWithBrush = pItem->m_object;
					if (objectWithBrush)
					{
						CRect rc(itemrect.left+64, itemrect.top+4, itemrect.left+64+8, itemrect.top+4+8);

						if (IsUnknownEqualUnknown(objectWithBrush, activeStroke) ||
							IsUnknownEqualUnknown(objectWithBrush, activeFill))
						{
							dc.Rectangle(rc.left-2, rc.top-2, rc.right+2, rc.bottom+2);
						}

						Gdiplus::Graphics graphics(dc.m_hDC);

						CComPtr<IPDBrush> brush;
						objectWithBrush->get_brush(&brush);
						Gdiplus::Brush* pBrush = GetGdiBrush(brush);
						if (pBrush)
						{
							graphics.FillRectangle(pBrush, rc.left, rc.top, rc.Width(), rc.Height());
							delete pBrush;
						}
					}

					CComQIPtr<IPDObjectStroke> stroke = pItem->m_object;
					if (stroke)
					{
						CComQIPtr<IPDStrokeSettings> stroke2 = stroke;

						double strokeWeight;
						stroke2->get_strokeWeight(&strokeWeight);

						_bstr_t s = CreateValueUnitString(strokeWeight, UNIT_PT);

						CRect trect = itemrect;
						trect.left += 80;
						dc.DrawText(s, s.length(), &trect, DT_SINGLELINE | DT_VCENTER);
					}
				}

				y += 16;
			}

		//
			if (withAppearance)
			{
				CComPtr<IPDAppearance> appearance;
				withAppearance->get_appearance(&appearance);

				if (appearance == NULL)
				{
					dc.SelectFont(hFontItalic);

					CRect trect(0, y, m_areaRect.Width(), y+16);
					_bstr_t s = L"Mixed Appearances";
					dc.DrawText(s, s.length(), &trect, DT_SINGLELINE | DT_VCENTER);
				}
			}

			dc.SelectFont(hOldFont);

			DeleteObject(hFontSelected);
			DeleteObject(hFontItalic);

			dc.SetViewportOrg(oldOrg);
		}
	}

	return 0;
}

LRESULT CAppearanceDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposY; m_vert->get_pos(&scrollposY);

	point.x -= m_areaRect.left;
	point.y -= m_areaRect.top;
	point.y += scrollposY;

	if (m_pTree)
	{
		CAppearanceObject* pFItem = NULL;

		C2Obj* pParentItem = m_pTree;
		UPOSITION pos = pParentItem->GetHeadPosition();
		int nextlevel = 0;

		int y = 0;
		int xindent;

		while (pos)
		{
			int level = nextlevel;
			CAppearanceObject* pItem = (CAppearanceObject*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

			xindent = level*10;

			y += 16;

			if (pItem->m_expanded)
				y += pItem->m_attrs.GetCount()*16;

			if (point.y < y)
			{
				pFItem = pItem;
				break;
			}
		}

		CComQIPtr<IUIManager> uiManager = gIFrame;

		int x = point.x-xindent;
		if (x < 0 && x >= -8)
		{
			if (pFItem)
			{
				pFItem->m_expanded = !pFItem->m_expanded;
				OnSize();
				Invalidate();
			}
		}
		else
		{
			DeselectAll();

			if (pFItem && pFItem->m_parent && pFItem->m_parent->m_parent)
			{
				pFItem->m_selected = true;

				pFItem->m_activated = true;
				//uiManager->ActivateObject(m_object, pFItem->m_object);
				CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> withStrokeFill = m_object;

				CComQIPtr<IPDObjectStroke> _stroke = pFItem->m_object;
				CComQIPtr<IPDObjectFill> _fill = pFItem->m_object;

				if (_stroke)
				{
					withStrokeFill->put_activeStroke(_stroke);

					gIApp->put_strokeOrFill(0);
				}
				else if (_fill)
				{
					withStrokeFill->put_activeFill(_fill);

					gIApp->put_strokeOrFill(1);
				}

				if (_stroke)
				{
					CComPtr<IPDObjectStroke> stroke;
					withStrokeFill->get_activeStroke(&stroke);

					CComPtr<IPDBrush> brush;
					stroke->get_brush(&brush);

					uiManager->ActivateObject(withStrokeFill, brush);
				}
				else
				{
					CComPtr<IPDObjectFill> fill;
					withStrokeFill->get_activeFill(&fill);

					CComPtr<IPDBrush> brush;
					fill->get_brush(&brush);

					uiManager->ActivateObject(withStrokeFill, brush);
				}
			}

			Invalidate();
		}
	}

	return 0;
}

void CAppearanceDlg::DeselectAll()
{
	CComQIPtr<IUIManager> uiManager = gIFrame;

	// Deselect all (except for first object)
	//if (m_pTree)
	C2Obj* pParentItem = (C2Obj*)m_pTree->m_childList.GetHead();
	UPOSITION pos = pParentItem->GetHeadPosition();
	int nextlevel = 0;
	while (pos)
	{
		int level = nextlevel;
		CAppearanceObject* pItem = (CAppearanceObject*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

		//if (uiManager->IsObjectActive(pItem->m_object) == S_OK)
		if (pItem->m_activated)
		{
			CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> withStrokeFill = m_object;

			CComQIPtr<IPDObjectStroke> _stroke = pItem->m_object;
			if (_stroke)
			{
				CComPtr<IPDObjectStroke> stroke;
				withStrokeFill->get_activeStroke(&stroke);

				CComPtr<IPDBrush> brush;
				stroke->get_brush(&brush);

				uiManager->DeactivateObject(brush);
			}
			else
			{
				CComPtr<IPDObjectFill> fill;
				withStrokeFill->get_activeFill(&fill);

				CComPtr<IPDBrush> brush;
				fill->get_brush(&brush);

				uiManager->DeactivateObject(brush);
			}

			//	uiManager->DeactivateObject(pItem->m_object);
			pItem->m_activated = false;
		}

		pItem->m_selected = false;
	}
}

LRESULT CAppearanceDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	Invalidate();

	return 0;
}

void CAppearanceDlg::OnSize()
{
	CRect client;
	GetClientRect(&client);

	m_areaRect = client;
	m_areaRect.InflateRect(-1, -1);

	long height = 0;

	if (m_pTree)
	{
		C2Obj* pParentItem = m_pTree;
		UPOSITION pos = pParentItem->GetHeadPosition();
		int nextlevel = 0;

		while (pos)
		{
			int level = nextlevel;
			CAppearanceObject* pItem = (CAppearanceObject*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

			if (pItem->m_expanded)
			{
				height += pItem->m_attrs.GetCount()*16;
			}

			height += 16;
		}
	}

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

HRESULT __stdcall CAppearanceDlg::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &m_areaRect, &m_areaRect);

	return S_OK;
}

void CAppearanceObject::BuildEffects()
{
	CComQIPtr<IUIManager> uiManager = gIFrame;

	/*
	CComQIPtr<IPDTextRange> textRange = m_object;
	if (textRange)
	{
		CComPtr<IPDStory> story;
		textRange->GetStory(&story);

		CComPtr<IPDTextFont> textFont;
		story->GetTextFont(textRange, &textFont);

		{
			CAppearanceObject* pItem = new CAppearanceObject;
			textFont->get_fillBrush((IPDBrush**)&pItem->m_object);
			pItem->m_name = L"Fill";

			m_attrs.AddTail(pItem);
		}

		{
			CAppearanceObject* pItem = new CAppearanceObject;
			textFont->get_strokeBrush((IPDBrush**)&pItem->m_object);
			pItem->m_name = L"Stroke";
			m_attrs.AddTail(pItem);
		}
	}
	*/

	CComQIPtr<IPDObjectWithBrush> objectWithBrush = m_object;
	if (objectWithBrush)
	{
		CAppearanceAttr* pItem = new CAppearanceAttr;
		pItem->m_object = objectWithBrush;
		pItem->m_name = L"color";
		pItem->m_type = ATTR_COLOR;

		m_attrs.AddTail(pItem);
	}

	CComQIPtr<IPDOpacityAndBlendMode> withOpacity = m_object;
	if (withOpacity)
	{
		CAppearanceAttr* pItem = new CAppearanceAttr;
		pItem->m_object = withOpacity;
		pItem->m_name = L"opacity";
		pItem->m_type = ATTR_OPACITY;

		m_attrs.AddTail(pItem);
	}

	CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> frame = m_object;
	if (frame)
	{
		CComPtr<IObjectMap> subObjects;
		frame->get_subObjects(&subObjects);

		long nsubObjects;
		subObjects->get_length(&nsubObjects);

		for (int i = 0; i < nsubObjects; i++)
		{
			CComPtr<IPDObjectWithBrush> objectWithBrush;
			subObjects->item(i, (IUnknown**)&objectWithBrush);
	
			PDObjectType objectType;
			objectWithBrush->get_objectType(&objectType);

			CAppearanceObject* pItem = new CAppearanceObject;
			pItem->m_object = objectWithBrush;

			if (uiManager->IsObjectActive(pItem->m_object) == S_OK)
				pItem->m_selected = true;

			if (objectType == PATH_STROKE)
			{
				pItem->m_name = "Stroke";
			}
			else if (objectType == PATH_FILL)
			{
				pItem->m_name = "Fill";
			}
			else
				ATLASSERT(0);

			//uiManager->ActivateObject(m_object, pItem->m_object);	// ??

			pItem->BuildEffects();
			AddChildTail(pItem);
		}
	}

	CComQIPtr<IPDObjectWithAppearance> withAppearance = m_object;
	if (withAppearance)
	{
		CComPtr<IPDAppearance> appearance;
		withAppearance->get_appearance(&appearance);

		if (appearance)
		{
			CComPtr<IObjectMap> filters;
			appearance->get_filterEffects(&filters);

			long nfilters;
			filters->get_length(&nfilters);
			for (int i = 0; i < nfilters; i++)
			{
				CComPtr<IPDFilterPrimitive> filter;
				filters->item(i, (IUnknown**)&filter);

				CComPtr<IPluginFilter> pluginFilter;
				filter->get_pluginFilter(&pluginFilter);

				CComPtr<IPluginFilterClass> pluginclass;
				pluginFilter->GetPluginFilterClass(&pluginclass);

				BSTR bname;
				pluginclass->GetName(&bname);

				CAppearanceObject* pItem = new CAppearanceObject;
				pItem->m_object = filter;
				pItem->m_name = _bstr_t(bname, false);

				AddChildTail(pItem);
			}
		}
	}
}

void CAppearanceDlg::BuildItems()
{
	delete m_pTree;
	m_pTree = new C2Obj;

	CAppearanceObject* pItem = new CAppearanceObject;
	pItem->m_object = m_object;

	CComQIPtr<IPDTextFont> textFont = m_object;
	if (textFont)
	{
		pItem->m_name = "Characters";
	}
	else
	{
		CComQIPtr<IPDObjectSelection> sel = m_object;

		long objectType;
		sel->get_objectType(&objectType);

		switch (objectType)
		{
		case tomUndefined:
			pItem->m_name = L"Mixed Objects";
			break;

		case 0:
			pItem->m_name = L"No Selection";
			break;

		case OBJECT_FRAME:
			pItem->m_name = L"Path";
			break;

		case CONTENT_GRAPHIC:
			pItem->m_name = L"Image";
			break;

		case OBJECT_GROUP:
			pItem->m_name = L"Group";
			break;
		}
	}
	
	pItem->m_expanded = true;
	m_pTree->AddChildTail(pItem);

	pItem->BuildEffects();
}

STDMETHODIMP CAppearanceDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
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
		//	cp->Advise(this, &cookie);
		}

		*cookie = 1;
	}
	else
	{
		CComQIPtr<IPDObjectWithBrush> objectWithBrush = object;
		if (objectWithBrush == NULL)
		{
			CComPtr<IPDTextFont> textFont;
			CComQIPtr<IPDObjectWithAppearance> objectWithAppearance;

			CComQIPtr<IPDTextRange> textRange = object;
			if (textRange)
			{
				CComPtr<IPDStory> story;
				textRange->GetStory(&story);

				story->GetTextFont(textRange, &textFont);

				objectWithAppearance = textFont;
			}

			CComQIPtr<IPDObjectSelection> sel = object;
			if (sel)
			{
				objectWithAppearance = sel;
			}

		//	if ((objectWithAppearance = object) != NULL || (textFont) != NULL)
			if (objectWithAppearance)
			{
				if (m_object)
				{
					DeselectAll();

					CComQIPtr<INotifySend> cp = m_object;
					if (cp) cp->Unadvise(this);

					m_object.Release();

					delete m_pTree;
					m_pTree = NULL;
				}

				m_object = objectWithAppearance;

				{
					DWORD cookie;
					CComQIPtr<INotifySend> cp = m_object;
					if (cp) cp->Advise(this, &cookie);
				}
				*cookie = 1;

				BuildItems();
			}
		}
	}

	if (m_hWnd)
	{
		OnSize();
		Invalidate();
	}

	return S_OK;
}

STDMETHODIMP CAppearanceDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	if (IsUnknownEqualUnknown((IPDDocumentView*)m_view, object))
	{
		CComQIPtr<INotifySend> cp = m_view->m_document;
		//cp->Unadvise(this);

		m_view->Release();
		m_view = NULL;
	}
	else if (IsUnknownEqualUnknown(m_object, object))
	{
		DeselectAll();

		{
			CComQIPtr<INotifySend> cp = m_object;
			if (cp) cp->Unadvise(this);
		}

		m_object.Release();

		delete m_pTree;
		m_pTree = NULL;
	}

	if (m_hWnd)
	{
		OnSize();
		Invalidate();
	}

	return S_OK;
}

// INotifyGet
STDMETHODIMP CAppearanceDlg::OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
{
	CComQIPtr<IPDObjectSelection> sel = m_object;
	m_view->SetObjectSelection(sel);

//	DeselectAll();
	BuildItems();

	if (m_hWnd)
	{
		OnSize();
		Invalidate();
	}

	return S_OK;
}

// ICommandTarget
STDMETHODIMP CAppearanceDlg::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try view
	CComQIPtr<ICommandTarget> view = m_view;
	if (view) view->OnCmdMsg(nID, nCode, pCmdUI, bHandled);

	return S_OK;
}

BEGIN_CMD_MAP(CAppearanceDlg)
	CMD_HANDLER(ID_APPEARANCE_ADDNEWSTROKE, OnAddNewStroke)
	CMD_UPDATE(ID_APPEARANCE_ADDNEWSTROKE, OnAddNewStrokeUpdate)
	CMD_HANDLER(ID_APPEARANCE_ADDNEWFILL, OnAddNewFill)
	CMD_UPDATE(ID_APPEARANCE_ADDNEWFILL, OnAddNewFillUpdate)
END_CMD_MAP()

LRESULT CAppearanceDlg::OnAddNewStroke(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComQIPtr<IPDObjectSelection> sel = m_object;
	if (sel)
	{
		long objectType;
		sel->get_objectType(&objectType);

		if (objectType == OBJECT_FRAME)
		{
			CComPtr<IPDObjectStroke> stroke;
			stroke.CoCreateInstance(CLSID_PDObjectStroke);

			sel->appendSubObject(stroke);
		}
	}

	return 0;
}

void CAppearanceDlg::OnAddNewStrokeUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	CComQIPtr<IPDObjectSelection> sel = m_object;
	if (sel)
	{
		long objectType;
		sel->get_objectType(&objectType);

		if (objectType == OBJECT_FRAME)
			bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}

LRESULT CAppearanceDlg::OnAddNewFill(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComQIPtr<IPDObjectSelection> sel = m_object;
	if (sel)
	{
		long objectType;
		sel->get_objectType(&objectType);

		if (objectType == OBJECT_FRAME)
		{
			CComPtr<IPDObjectFill> stroke;
			stroke.CoCreateInstance(CLSID_PDObjectFill);

			sel->appendSubObject(stroke);
		}
	}

	return 0;
}

void CAppearanceDlg::OnAddNewFillUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;

	CComQIPtr<IPDObjectSelection> sel = m_object;
	if (sel)
	{
		long objectType;
		sel->get_objectType(&objectType);

		if (objectType == OBJECT_FRAME)
			bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
}
