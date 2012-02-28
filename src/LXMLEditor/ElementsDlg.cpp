// ElementsDlg.cpp : Implementation of CElementsDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "ElementsDlg.h"

//#include "WebEditorApp.h"
//#include "WebEditorFrame.h"

#include "EXMLDocument.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CElementsDlg

CElementsDlg::CElementsDlg()
{
}

CElementsDlg::~CElementsDlg()
{
}

void CElementsDlg::AddCMElements(IASContentModel* asCM)
{
	CComPtr<IASObjectList> sublist;
	asCM->get_subModels(&sublist);

	long length;
	sublist->get_length(&length);
	for (int i = 0; i < length; i++)
	{
		CComPtr<IASObject> sub;
		sublist->item(i, &sub);

		ASObjectType type;
		sub->get_asNodeType(&type);

		if (type == AS_CONTENTMODEL)
		{
			CComQIPtr<IASContentModel> asCM = sub;
			AddCMElements(asCM);
		}
		else
		{
			CComBSTR name;
			sub->get_nodeName(&name);

			m_elements.Add(_bstr_t(name));
		}
	}
}


void __stdcall CElementsDlg::OnViewGroupSelectionChanged()
{
	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);

	m_elements.RemoveAll();

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

STDMETHODIMP CElementsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;
	if (viewGroup)
	{
		m_viewGroup = viewGroup;
		IDispEventImpl<4, CElementsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CElementsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	IDispEventImpl<4, CElementsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
	m_viewGroup.Release();

	return S_OK;
}

HRESULT __stdcall CElementsDlg::OnDOMEvent(ILDOMEvent* evt)
{
	return S_OK;
}

void __stdcall CElementsDlg::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	m_vert->put_pos(pos);

	CRect	rect = m_areaRect;
	ScrollWindow(0, oldPos-pos, &rect, &rect);
}

#include "EXMLViewGroup.h"
#include "EXMLLayoutView.h"	// TODO remove

long CElementsDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	long scrollposY; m_vert->get_pos(&scrollposY);

	if (m_viewGroup)
	{
		int index = point.y/16;

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
				ATLASSERT(0);
#if 0
				window->get_selection(&range);
#endif

				if (range)
				{
					CComPtr<ILDOMElement> element;
					document->createElement(m_elements[index], &element);

					range->surroundContents(element);
				}
			}
		}
	}

	return 0;
}

void CElementsDlg::OnSize()
{
	CRect client;
	GetClientRect(&client);

	int height = m_elements.GetSize()*m_itemHeight;

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

long CElementsDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

long CElementsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axvert.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<3, CElementsDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	m_font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	m_itemHeight = 16;

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->AddEventHandler(this);

	return 0;
}

long CElementsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->RemoveEventHandler(this);

	IDispEventImpl<3, CElementsDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	if (m_font)
	{
		DeleteObject(m_font);
		m_font = NULL;
	}

	return 0;
}

long CElementsDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	if (m_viewGroup)
	{
		long scrollposY; m_vert->get_pos(&scrollposY);

		HFONT hOldFont = dc.SelectFont(m_font);

		dc.SetBkMode(TRANSPARENT);

		if (dc.IntersectClipRect(m_areaRect.left, m_areaRect.top, m_areaRect.right, m_areaRect.bottom) > NULLREGION)
		{
			dc.SetViewportOrg(0, -scrollposY, NULL);

			int y = 0;

			for (int i = 0; i < m_elements.GetSize(); i++)
			{
				_bstr_t name = m_elements[i];

				dc.TextOut(0, y, _bstr_t(name), name.length());

				y += m_itemHeight;
			}
		}

		dc.SelectFont(hOldFont);
	}

	return 0;
}

#endif