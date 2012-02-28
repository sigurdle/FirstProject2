#include "stdafx.h"
#include "LXMLEditor2.h"
#include "EntitiesDlg.h"

//#include "WebEditorApp.h"
//#include "WebEditorFrame.h"

#include "EXMLDocument.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CEntitiesDlg

CEntitiesDlg::CEntitiesDlg()
{
}

CEntitiesDlg::~CEntitiesDlg()
{
}

#if 0
void __stdcall CEntitiesDlg::OnViewGroupSelectionChanged()
{
	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);

	m_entities.RemoveAll();

	if (selectedElement)
	{
		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> element;
		eElement->get_domElement(&element);

		CComPtr<ILDOMDocument> ownerDocument;
		element->get_ownerDocument(&ownerDocument);
		if (ownerDocument)
		{
			CComQIPtr<ILDocumentAS> documentAS = ownerDocument;
			if (documentAS)
			{
				CComQIPtr<IASModel> asModel;
				documentAS->get_activeASModel(&asModel);
				if (asModel)
				{
					CComQIPtr<IASNamedObjectMap> elementDeclarations;
					asModel->get_elementDeclarations(&elementDeclarations);

					CComBSTR tagName;
					element->get_tagName(&tagName);

					CComQIPtr<IASElementDeclaration> elementDecl;

					elementDeclarations->getNamedItem(tagName, (IASObject**)&elementDecl);
					if (elementDecl)
					{
						CComPtr<IASContentModel> asCM;
						elementDecl->get_asCM(&asCM);

						if (asCM)
						{
							AddCMElements(asCM);
						}
					}
				}
			}
		}
	}

	OnSize();
	Invalidate();
}
#endif

STDMETHODIMP CEntitiesDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLDocument> edocument = object;
	if (edocument)
	{
		ASSERT(m_entities.GetSize() == 0);

		m_edocument = edocument;

		CComPtr<ILDOMDocument> document;
		m_edocument->get_DOMDocument(&document);

		CComQIPtr<ILDocumentAS> asDocument = document;
		if (asDocument)
		{
			CComPtr<IASModel> asModel;
			asDocument->get_activeASModel(&asModel);

			if (asModel)
			{
				CComPtr<IASNamedObjectMap> entityDecls;
				asModel->get_entityDeclarations(&entityDecls);

				long length;
				entityDecls->get_length(&length);

				for (int i = 0; i < length; i++)
				{
					CComPtr<IASEntityDeclaration> entity;
					entityDecls->item(i, (IASObject**)&entity);

					m_entities.Add(entity);
				}
			}
		}

		if (m_hWnd)
		{
			Invalidate();
			OnSize();
		}

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CEntitiesDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	m_entities.RemoveAll();

//	IDispEventImpl<4, CEntitiesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
	m_edocument.Release();

	if (m_hWnd)
	{
		OnSize();
		Invalidate();
	}

	return S_OK;
}

HRESULT __stdcall CEntitiesDlg::OnDOMEvent(ILDOMEvent* evt)
{
	return S_OK;
}

void __stdcall CEntitiesDlg::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	m_vert->put_pos(pos);

	CRect	rect = m_areaRect;
	ScrollWindow(0, oldPos-pos, &rect, &rect);
}

#include "EXMLViewGroup.h"
#include "EXMLLayoutView.h"	// TODO remove

long CEntitiesDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_edocument)
	{
		int index = point.y/16;

#if 0
		if (index >= 0 && index < m_elements.GetSize())
		{
			if (static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_layoutView)
			{
				CComQIPtr<ILHTMLActiveView> view = static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_layoutView->m_pIOleDocView;

				CComPtr<ILHTMLWindow> window;
				view->GetHTMLWindow(&window);

				CComPtr<ILDOMDocument> document;
				window->get_document(&document);

				CComPtr<ILDOMRange> range;
				window->get_selection(&range);

				if (range)
				{
					CComPtr<ILDOMElement> element;
					document->createElement(m_elements[index], &element);

					range->surroundContents(element);
				}
			}
		}
#endif
	}

	return 0;
}

void CEntitiesDlg::OnSize()
{
	CRect client;
	GetClientRect(&client);

	int height = m_entities.GetSize()*m_itemHeight;

	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.bottom = client.bottom;

	if (client.bottom > height)
	{
		m_areaRect.right = client.right;
		m_axvert.ShowWindow(SW_HIDE);

		m_vert->put_pos(0);
	}
	else
	{
		m_areaRect.right = client.right-16;

		m_axvert.ShowWindow(SW_SHOW);
		m_axvert.MoveWindow(m_areaRect.right, 0, 16, client.bottom, TRUE);

		m_vert->SetInfo(0, height, client.bottom);
	}
}

long CEntitiesDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

long CEntitiesDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axvert.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<3, CEntitiesDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	m_font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	m_itemHeight = 16;

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->AddEventHandler(this);

	return 0;
}

long CEntitiesDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->RemoveEventHandler(this);

	IDispEventImpl<3, CEntitiesDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	if (m_font)
	{
		DeleteObject(m_font);
		m_font = NULL;
	}

	return 0;
}

long CEntitiesDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	if (m_edocument)
	{
		long scrollposY; m_vert->get_pos(&scrollposY);

		HFONT hOldFont = dc.SelectFont(m_font);

		dc.SetBkMode(TRANSPARENT);

		if (dc.IntersectClipRect(m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom) > NULLREGION)
		{
			dc.SetViewportOrg(0, -scrollposY, NULL);

			int y = 0;

			for (int i = 0; i < m_entities.GetSize(); i++)
			{
				CRect itemrect(0, y, m_areaRect.Width(), y+m_itemHeight);

				CRect namerect = itemrect;
				namerect.right = 80;

				CRect valuerect = itemrect;
				valuerect.left = 80;

				CComBSTR name;
				m_entities[i]->get_nodeName(&name);

				CComBSTR value;
				m_entities[i]->get_entityValue(&value);;

				dc.DrawText(_bstr_t(name), name.Length(), &namerect, DT_SINGLELINE);

				dc.DrawText(_bstr_t(value), value.Length(), &valuerect, 0);

				y += m_itemHeight;
			}
		}

		dc.SelectFont(hOldFont);
	}

	return 0;
}

#endif