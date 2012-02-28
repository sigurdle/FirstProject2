// SVGElementMaskDlg.cpp : Implementation of CSVGElementMaskDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SVGElementMaskDlg.h"

#include "EXMLViewGroup.h"	// TODO remove

#if 0

/////////////////////////////////////////////////////////////////////////////
// CSVGElementMaskDlg

int CSVGElementMaskDlg::FinalConstruct()
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->FindMenu(IDR_SVGELEMENTMASKDLG, &m_menu);

	return 0;
}

LRESULT CSVGElementMaskDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->AddEventHandler(this);

	return 0;
}

LRESULT CSVGElementMaskDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->RemoveEventHandler(this);

	return 0;
}

LRESULT CSVGElementMaskDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	CPaintDC dc(m_hWnd);

	if (m_svgElement)
	{
		CComPtr<ILDOMDocument> document;
		m_svgElement->get_ownerDocument(&document);

		CComPtr<IUnknown> spUnknown;
		HRESULT hr = CoCreateInstance(CLSID_LHTMLActiveDocument, NULL, CLSCTX_ALL, IID_IUnknown, (void**)&spUnknown);

		CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = spUnknown;

		CComQIPtr<IOleDocument> oleDocument = spUnknown;

		CComPtr<IOleDocumentView> oleView;

		oleDocument->CreateView(NULL,// *pIPSite,
			NULL,///* [unique][in] */ IStream __RPC_FAR *pstm,
			0,///* [in] */ DWORD dwReserved,
			&oleView);

		CComQIPtr<ILHTMLActiveView> htmlView = oleView;

		CRect rect(0, 0, 80, 80);
		oleView->SetRect(&rect);

/*
			BSTR bid;
			m_items[i]->getAttribute(L"id", &bid);
			_bstr_t id = _bstr_t(bid, false);

			CComPtr<ILSVGDocument> svgDocument;
			svgDocument.CoCreateInstance(CLSID_LSVGDocument);

			VARIANT_BOOL bsuccess;
			svgDocument->loadXML(L"<svg/>", &bsuccess);

			CComPtr<ILDOMElement> documentElement;
			svgDocument->get_documentElement(&documentElement);

			CComPtr<ILSVGFilterElement> filterElement;
			svgDocument->importNode(m_items[i], VARIANT_TRUE, (ILDOMNode**)&filterElement);
			documentElement->appendChild(filterElement, NULL);

			CComPtr<ILSVGEllipseElement> ellipseElement;
			svgDocument->createElement(L"ellipse", (ILDOMElement**)&ellipseElement);

			ellipseElement->setAttribute(L"cx", _bstr_t(_variant_t(long((twidth)/2))));
			ellipseElement->setAttribute(L"cy", _bstr_t(_variant_t(long((theight)/2))));
			ellipseElement->setAttribute(L"rx", _bstr_t(_variant_t(long((twidth)*7/18))));
			ellipseElement->setAttribute(L"ry", _bstr_t(_variant_t(long((theight)*7/18))));

			_bstr_t style;
			style = L"fill:#0000ff; filter:url(#" + id + L")";
			ellipseElement->setAttribute(L"style", style);

			documentElement->appendChild(ellipseElement, NULL);
			*/

		htmlActiveDoc->SetDocument(document);

		int twidth = 80;
		int theight = 80;

		BITMAPINFO bmi = {0};
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = twidth;
		bmi.bmiHeader.biHeight = -theight;
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biPlanes = 1;

		HBITMAP hTBitmap;
		LPBYTE TBits = NULL;

		if (hTBitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&TBits, NULL, 0))
		{
			HDC hTDC = CreateCompatibleDC(NULL);
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(hTDC, hTBitmap);

			FillSolidRect(hTDC, 0, 0, twidth, theight, RGB(255, 255, 255));
#if 0
			htmlView->DrawToHdc(hTDC, m_svgElement, 1);
#endif
			dc.BitBlt(0, 0, twidth, theight, hTDC, 0, 0, SRCCOPY);

			SelectObject(hTDC, hOldBitmap);

			DeleteDC(hTDC);

			DeleteObject(hTBitmap);
		}

		CComQIPtr<ILSVGStylable> stylable = m_svgElement;
		if (stylable)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			stylable->get_style(&style);

			CComPtr<ILCSSPrimitiveValue> cssvalue;
			style->getPropertyCSSValue(L"mask", (ILCSSValue**)&cssvalue);
			if (cssvalue)
			{
				LCSSUnitType type;
				cssvalue->get_primitiveType(&type);
				if (type == CSS_URI)
				{
					BSTR burl;
					cssvalue->getStringValue(&burl);
					_bstr_t url = _bstr_t(burl, false);

					if (((BSTR)url)[0] == L'#')
					{
						_bstr_t uri = ((BSTR)url)+1;

						CComPtr<ILDOMElement> element;
						document->getElementById(uri, &element);
						if (element)
						{
							CComQIPtr<ILSVGMaskElement> maskElement = element;
							if (maskElement)
							{
								if (hTBitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&TBits, NULL, 0))
								{
									HDC hTDC = CreateCompatibleDC(NULL);
									HBITMAP hOldBitmap = (HBITMAP)SelectObject(hTDC, hTBitmap);

									FillSolidRect(hTDC, 0, 0, twidth, theight, RGB(0, 0, 0));
#if 0
									htmlView->DrawToHdc(hTDC, maskElement, 1);
#endif
									dc.BitBlt(100, 0, twidth, theight, hTDC, 0, 0, SRCCOPY);

									SelectObject(hTDC, hOldBitmap);

									DeleteDC(hTDC);

									DeleteObject(hTBitmap);
								}
							}
						}
					}
				}
			}
		}
	}
#endif

	return 0;
}

LRESULT CSVGElementMaskDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_viewGroup)
	{
		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		CComPtr<ILDOMDocument> document;
		edocument->get_DOMDocument(&document);

		if (point.x > 100)
		{
			CComQIPtr<ILSVGStylable> stylable = m_svgElement;
			if (stylable)
			{
				CComPtr<ILCSSStyleDeclaration> style;
				stylable->get_style(&style);

				CComPtr<ILCSSPrimitiveValue> cssvalue = style->getPropertyCSSValue(L"mask");
				if (cssvalue)
				{
					LCSS::LCSSUnitType type = cssvalue->get_primitiveType();
					if (type == LCSS::CSS_URI)
					{
						sysstring url = cssvalue->getStringValue();

						if (((BSTR)url)[0] == L'#')
						{
							_bstr_t uri = ((BSTR)url)+1;

							LXML::Element* element = document->getElementById(uri);
							if (element)
							{
								LSVG::CLSVGMaskElement* maskElement = element;
								if (maskElement)
								{
									CComPtr<IEElement> eelement;
									edocument->GetEElementFromDOMElement(maskElement, &eelement);

									CComPtr<IEElement> refelement;
									edocument->GetEElementFromDOMElement(m_svgElement, &refelement);

									static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_activeReferencedElement = eelement;
									static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_activeReferenceElement = refelement;
								}
							}
						}
					}
				}
			}
		}
	}
#endif
	return 0;
}

// IUIEventHandler
STDMETHODIMP CSVGElementMaskDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	ATLASSERT(0);
#if 0
	CComQIPtr<IEXMLViewGroup> viewGroup = object;
	if (viewGroup)
	{
		m_viewGroup = viewGroup;

		if (m_hWnd)
		{
			Invalidate();
		}

		*cookie = 1;
	}

	CComQIPtr<IEElement> eelement = object;
	if (eelement)
	{
		CComPtr<ILDOMElement> element;
		eelement->get_domElement(&element);

		CComQIPtr<ILSVGElement> svgElement = element;
		if (svgElement)
		{
			m_svgElement = svgElement;

			if (m_hWnd)
			{
				Invalidate();
			}

			*cookie = 1;
		}
	}
#endif
	return S_OK;
}

STDMETHODIMP CSVGElementMaskDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	CComQIPtr<IEXMLViewGroup> viewGroup;
	if (viewGroup)
	{
		ATLASSERT(m_svgElement == NULL);
		m_viewGroup.Release();
	}
	else
	{
		ATLASSERT(m_viewGroup != NULL);
		m_svgElement.Release();
	}

	if (m_hWnd)
	{
		Invalidate();
	}

	return S_OK;
}

BEGIN_CMD_MAP(CSVGElementMaskDlg)
	CMD_HANDLER(ID_ELEMENTMASK_MAKEMASK, OnMakeMask)
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

LRESULT CSVGElementMaskDlg::OnMakeMask(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILDOMDocument> xmldocument;

	m_svgElement->get_ownerDocument(&xmldocument);

	CComPtr<ILSVGMaskElement> maskElement;
	xmldocument->createElement(L"mask", (ILDOMElement**)&maskElement);

	_bstr_t id = L"test";

	maskElement->setAttribute(L"id", id);

	// TODO, put inside defs

	CComPtr<ILDOMElement> documentElement;
	xmldocument->get_documentElement(&documentElement);
	documentElement->appendChild(maskElement, NULL);

	_bstr_t maskUrl = L"url(#" + id + L")";

	CComQIPtr<ILSVGStylable> stylable = m_svgElement;

	CComPtr<ILCSSStyleDeclaration> style;
	stylable->get_style(&style);

	style->setProperty(L"mask", maskUrl, NULL);

	return 0;
}

#endif