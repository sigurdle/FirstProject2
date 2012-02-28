// SVGFontGlyphsDlg.cpp : Implementation of CSVGFontGlyphsDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SVGFontGlyphsDlg.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CSVGFontGlyphsDlg

int CSVGFontGlyphsDlg::FinalConstruct()
{
	HRESULT hr;

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->FindMenu(IDR_SVGFONTGLYPHSDLG, &m_menu);

	/*
	hr = m_vert.CoCreateInstance(CLSID_UIScrollBar);
	if (FAILED(hr)) return hr;
	m_vert->put_direction(1);
	*/

	return 0;
}

LRESULT CSVGFontGlyphsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->AddEventHandler(this);

	return 0;
}

LRESULT CSVGFontGlyphsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->RemoveEventHandler(this);

	return 0;
}

LRESULT CSVGFontGlyphsDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	if (m_fontEElement)
	{
		CComPtr<ILDOMElement> fontElement;
		m_fontEElement->get_domElement(&fontElement);

		int y = 0;

		CComPtr<ILDOMNode> node;
		fontElement->get_firstChild(&node);
		while (node)
		{
			CComQIPtr<ILSVGGlyphElement> glyphElement = node;
			if (glyphElement)
			{
				BSTR bunicode;
				glyphElement->getAttribute(L"unicode", &bunicode);
				_bstr_t unicode = _bstr_t(bunicode, false);

				dc.TextOut(0, y, unicode, unicode.length());

				y += 18;
			}

			CComPtr<ILDOMNode> nextSibling;
			node->get_nextSibling(&nextSibling);
			node = nextSibling;
		}
	}

	return 0;
}

LRESULT CSVGFontGlyphsDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	return 0;
}

//#include "WebEditorApp.h"
//#include "WebEditorFrame.h"

#include "EXMLDocument.h"
#include "EXMLViewGroup.h"
#include "EXMLLayoutView.h"

LRESULT CSVGFontGlyphsDlg::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_fontEElement)
	{
		CComPtr<IEXMLDocument> eDocument;
		m_fontEElement->get_ownerDocument(&eDocument);

		CComPtr<ILDOMElement> fontElement;
		m_fontEElement->get_domElement(&fontElement);

		CArray<ILDOMElement*,ILDOMElement*> items;
		{
			CComPtr<ILDOMNode> node;
			fontElement->get_firstChild(&node);
			while (node)
			{
				CComQIPtr<ILSVGGlyphElement> glyphElement = node;
				if (glyphElement)
				{
					items.Add(glyphElement);
				}

				CComPtr<ILDOMNode> nextSibling;
				node->get_nextSibling(&nextSibling);
				node = nextSibling;
			}
		}

		int index = point.y/18;

		if (index >= 0 && index < items.GetSize())
		{
			CComObject<CEXMLViewGroup>* viewGroup;
			CComObject<CEXMLViewGroup>::CreateInstance(&viewGroup);
			if (viewGroup)
			{
				viewGroup->AddRef();

				{
					VARIANT vFactory;

					// Convert pGridFactory to the proper VARIANT data type 
					// for IHTMLElement2::AddBehavior
					V_VT(&vFactory) = VT_UNKNOWN;
					V_UNKNOWN(&vFactory) = static_cast<CEXMLDocument*>(eDocument.p)->m_pElementBehaviorFactory;

					// AddRef because we've copied the pGridFactory pointer 
					V_UNKNOWN(&vFactory)->AddRef();

					long cookie;
					items[index]->addBehavior(NULL, &vFactory, &cookie);
				}

				viewGroup->SetDocument(static_cast<CEXMLDocument*>(eDocument.p));
				//static_cast<CEXMLDocument*>(eDocument.p)->m_xmldocument->get_documentElement(&viewGroup->m_outerElement);
				viewGroup->m_outerElement = items[index];

				CComPtr<IEElement> eElement;
				eDocument->GetEElementFromDOMElement(items[index], &eElement);
				viewGroup->m_activeReferencedElement = eElement;

				/*
				// Add a source text bookmark on the viewgroup's outerElement, so that when the source
				// text is changed and the DOM is reparsed, we can find back to the DOM outerElement
				if (viewGroup->m_outerElement)
				{
					long startOffset;
					viewGroup->m_outerElement->getTextOffset(0, &startOffset);

					long endOffset;
					viewGroup->m_outerElement->getTextOffset(2, &endOffset);

					addBookmark(NULL, startOffset, endOffset-startOffset, &viewGroup->m_outerElementTextBookmark);
				}
				*/

				static_cast<CEXMLDocument*>(eDocument.p)->m_viewGroups.Add(viewGroup);

			//	gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&viewGroup->m_spFrame);

			//	CComObject<CUIMDIChild>* child;
			//	CComObject<CUIMDIChild>::CreateInstance(&child);
			//	child->AddRef();
			//	gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

				CComObject<CWebXMLViewGroup>* child = viewGroup;

				CComPtr<ILDOMDocument> xmldocument;
				eDocument->get_DOMDocument(&xmldocument);

				CComPtr<ILDOMElement> documentElement;
				xmldocument->get_documentElement(&documentElement);

				{
				// Layout
					CComObject<CSvgLayoutView>* layoutView;
					CComObject<CSvgLayoutView>::CreateInstance(&layoutView);
					if (layoutView)
					{
						gApp->m_frame->FindMenu(IDR_XMLLAYOUTVIEW, &layoutView->m_menu);
						layoutView->m_document = eDocument;

						layoutView->m_viewGroup = viewGroup;
						viewGroup->m_views.Add(layoutView);

						viewGroup->m_layoutView = layoutView;

						child->AddPage(layoutView, NULL);
					}
				}

				child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);

				child->UpdateFrameTitle();
			}
		}
	}
#endif

	return 0;
}

STDMETHODIMP CSVGFontGlyphsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;

	if (viewGroup)
	{
		ATLASSERT(m_viewGroup == NULL);
		m_viewGroup = viewGroup;

		IDispEventImpl<1, CSVGFontGlyphsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

		OnViewGroupSelectionChanged();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CSVGFontGlyphsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ATLASSERT(m_viewGroup);
	IDispEventImpl<1, CSVGFontGlyphsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
	m_viewGroup.Release();
	m_fontEElement = NULL;

	/*
	m_editGraph->put_activeElement(NULL);
	*/

	return S_OK;
}

void __stdcall CSVGFontGlyphsDlg::OnViewGroupSelectionChanged()
{
	m_fontEElement = NULL;

	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);
	if (selectedElement)
	{
		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> element;
		eElement->get_domElement(&element);

		CComQIPtr<ILSVGFontElement> fontElement = element;
		if (fontElement)
		{
			m_fontEElement = eElement;
		}
	}

	if (m_hWnd)
	{
		Invalidate();
	}
}

BEGIN_CMD_MAP(CSVGFontGlyphsDlg)
	CMD_HANDLER(ID_SVGGLYPHS_NEWGLYPH, OnFontNewGlyph)
END_CMD_MAP()

#include "SVGGlyphOptionsDlg.h"

LRESULT CSVGFontGlyphsDlg::OnFontNewGlyph(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_fontEElement)
	{
		CSVGGlyphOptionsDlg dlg;

		if (dlg.DoModal() == IDOK)
		{
			CComPtr<ILDOMElement> fontElement;
			m_fontEElement->get_domElement(&fontElement);

			CComPtr<IEXMLDocument> eDocument;
			m_fontEElement->get_ownerDocument(&eDocument);

			CComPtr<ILDOMDocument> document;
			eDocument->get_DOMDocument(&document);

			CComPtr<ILDOMElement> glyphElement = document->createElementNS(L"http://www.w3.org/2000/svg", L"glyph");
			if (glyphElement)
			{
				glyphElement->setAttribute(L"unicode", dlg.m_unicode);

				fontElement->appendChild(glyphElement, NULL);
			}
		}
	}

	return 0;
}

#endif