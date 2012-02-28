#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "SVGToolsDlg.h"

#include "EXMLDocument.h"	// TODO remove
#include "EXMLViewGroup.h"
#include "LXMLEditorApp.h"	// TODO remove
//#include "WebEditorFrame.h"	// TODO remove

//HRESULT ApplyStyle(IWebXMLViewGroup* viewGroup);

#if 0
BOOL SelectionCanHavePaint(IEXMLViewGroup* viewGroup);
CComBSTR MakeRGBString(double red, double green, double blue);

/////////////////////////////////////////////////////

#if 0
class ATL_NO_VTABLE CCSSPaintColor : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IEColor
{
public:
	CCSSPaintColor()
	{
	}

	CComPtr<ILSVGPaint> m_cssvalue;
	CComPtr<IWebXMLViewGroup> m_viewGroup;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCSSPaintColor)
	COM_INTERFACE_ENTRY(IEColor)
END_COM_MAP()

public:
	STDMETHOD(get_red)(long *pVal)
	{
		CWebXMLViewGroup* pViewGroup = static_cast<CWebXMLViewGroup*>(m_viewGroup.p);
		CEXMLDocument* pDocument = pViewGroup->m_pDocument;

		if (m_cssvalue)
		{
			LSVGPaintType paintType;
			m_cssvalue->get_paintType(&paintType);

			if (paintType == SVG_PAINTTYPE_RGBCOLOR ||
				paintType == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR)
			{
				CComPtr<ILRGBColor> rgbColor;
				m_cssvalue->get_rgbColor(&rgbColor);

				CComPtr<ILCSSPrimitiveValue> cssred;
				rgbColor->get_red(&cssred);

				double red;
				cssred->getFloatValue(CSS_NUMBER, &red);
				*pVal = (BYTE)red;

				return S_OK;
			}
		}

		*pVal = -999999;
		return S_FALSE;
	}

	STDMETHOD(get_green)(long *pVal)
	{
		CWebXMLViewGroup* pViewGroup = static_cast<CWebXMLViewGroup*>(m_viewGroup.p);
		CEXMLDocument* pDocument = pViewGroup->m_pDocument;

		if (m_cssvalue)
		{
			LSVGPaintType paintType;
			m_cssvalue->get_paintType(&paintType);

			if (paintType == SVG_PAINTTYPE_RGBCOLOR ||
				paintType == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR)
			{
				CComPtr<ILRGBColor> rgbColor;
				m_cssvalue->get_rgbColor(&rgbColor);

				CComPtr<ILCSSPrimitiveValue> cssgreen;
				rgbColor->get_green(&cssgreen);

				double green;
				cssgreen->getFloatValue(CSS_NUMBER, &green);
				*pVal = (BYTE)green;

				return S_OK;
			}
		}

		*pVal = -999999;
		return S_FALSE;
	}

	STDMETHOD(get_blue)(long *pVal)
	{
		CWebXMLViewGroup* pViewGroup = static_cast<CWebXMLViewGroup*>(m_viewGroup.p);
		CEXMLDocument* pDocument = pViewGroup->m_pDocument;

		if (m_cssvalue)
		{
			LSVGPaintType paintType;
			m_cssvalue->get_paintType(&paintType);

			if (paintType == SVG_PAINTTYPE_RGBCOLOR ||
				paintType == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR)
			{
				CComPtr<ILRGBColor> rgbColor;
				m_cssvalue->get_rgbColor(&rgbColor);

				CComPtr<ILCSSPrimitiveValue> cssblue;
				rgbColor->get_blue(&cssblue);

				double blue;
				cssblue->getFloatValue(CSS_NUMBER, &blue);
				*pVal = (BYTE)blue;
				return S_OK;
			}
		}

		*pVal = -999999;
		return S_FALSE;
	}

	STDMETHOD(setRGBValue)(long red, long green, long blue)
	{
		if (red < 0) red = 0;
		if (green < 0) green = 0;
		if (blue < 0) blue = 0;

		ATLASSERT(red >= 0 && red <= 255);
		ATLASSERT(green >= 0 && green <= 255);
		ATLASSERT(blue >= 0 && blue <= 255);

		CEXMLViewGroup* pViewGroup = static_cast<CEXMLViewGroup*>(m_viewGroup.p);
		CEXMLDocument* pDocument = pViewGroup->m_pDocument;

		_bstr_t propertyName = (gApp->m_strokeOrFill == 0)? L"stroke": L"fill";

		WCHAR buf[32];
		swprintf(buf, L"#%2.2X%2.2X%2.2X", red, green, blue);

		if (TRUE)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			m_viewGroup->GetCurrentSelectionCSSStyle(&style);

			style->setProperty(propertyName, buf, NULL);

			pDocument->m_defaultColor = buf;//_bstr_t(b, false);	// hm.. should be called somewhere else

			// Apply to selected elements
			m_viewGroup->ApplyCurrentSelectionCSSStyle();
		}
		else
		{
#if 0
			pDocument->m_defaultStyle->setProperty(propertyName, buf, NULL);

			BSTR b;
			pDocument->m_defaultStyle->getPropertyValue(propertyName, &b);
			pDocument->m_defaultColor = _bstr_t(b, false);
#endif
		}

		return S_OK;
	}
};
#endif

/////////////////////////////////////////////////////////////////////////////
// CSVGToolsDlg

LRESULT CSVGToolsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(m_app->m_toolsElement);

#if 0	// Had this
	CComPtr<ILDOMAbstractView> view;
	m_behaviorSite->GetView(&view);

	CComPtr<ILViewNode> vnode;
	CComQIPtr<ILDOMViewCSS>(view)->GetViewNode(m_app->m_toolsElement, &vnode);

	m_menuDlg = CComQIPtr<IUIDlg>(vnode);
	ATLASSERT(m_menuDlg);

	m_menuDlg->Create(m_hWnd);
#endif

//	ATLASSERT(0);
#if 0
	CComPtr<IMenuItem> menu;
	m_pUIManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGTOOLS, &menu);
	if (menu == NULL)
		return -1;

//	CComObject<CUIMenuDlg>::CreateInstance(&m_menuDlg);//.CoCreateInstance(CLSID_UIMenuDlg);
//	m_menuDlg->AddRef();

	m_pUIManager->CreateMenuDlg(&m_menuDlg);

	CComPtr<IMenuItem> menu0;
	menu->GetSubMenu(0, &menu0);

	CComQIPtr<ICommandTarget> targetFrame = m_app;
	m_menuDlg->CreateForMenuItem(menu0, m_hWnd, targetFrame, -1);

	menu.Detach();	// ?? Doesn't CreateForMenuItem AddRef()?

	{
		CComPtr<IUnknown> spUnknown;
		::CoCreateInstance(CLSID_LHTMLActiveDocument, NULL, CLSCTX_ALL, IID_IUnknown, (void**)&spUnknown);

		m_htmlActiveDoc = spUnknown;
		if (m_htmlActiveDoc)
		{
			CComQIPtr<IOleDocument> oleDocument = m_htmlActiveDoc;
			CComPtr<IOleDocumentView> oleView;
			oleDocument->CreateView(NULL,// *pIPSite,
				NULL,///* [unique][in] */ IStream __RPC_FAR *pstm,
				0,///* [in] */ DWORD dwReserved,
				&oleView);
			m_htmlView = oleView;
		}
	}

	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
	uiActiveManager->AddEventHandler(this);
#endif

	return 0;
}

LRESULT CSVGToolsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->RemoveEventHandler(this);

	m_htmlActiveDoc.Release();
	m_htmlView.Release();

	if (m_menuDlg)
	{
		m_menuDlg->DestroyWindow();
		m_menuDlg.Release();
	}

	return 0;
}

LRESULT CSVGToolsDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	int top = client.bottom-64;

	if (m_menuDlg)
	{
		HWND hwnddlg;
		m_menuDlg->get_hwnd(&hwnddlg);

		::MoveWindow(hwnddlg, 0, 0, client.right, top, TRUE);
	}

	double nwidth = (client.Width()-2)/3.0;

	m_fillrc = CRect(8, top+6, 8+24, top+6+24);
	m_strokerc = CRect(8+12, top+6+12, 8+24+12, top+6+24+12);

	m_drc[0] = CRect(2, top+48+2, 2+16, top+48+2+14);
	m_drc[1] = CRect(2+16, top+2+48, 2+16+16, top+48+2+14);
	m_drc[2] = CRect(2+16+16, top+2+48, 2+16+16+16, top+48+2+14);

	return 0;
}

void DrawPaintNone(HDC hDC, CRect& rc, CRect& rc2)
{
	int state = SaveDC(hDC);

	ExcludeClipRect(hDC, rc2.left, rc2.top, rc2.right, rc2.bottom);

	FillSolidRect(hDC, &rc, RGB(255, 255, 255));

	RestoreDC(hDC, state);

	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	MoveToEx(hDC, rc.right, rc.top, NULL);
	LineTo(hDC, rc.left, rc.bottom);

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

void DrawPaint(HDC hDC, CRect& rc, CRect& rc2, WCHAR* paintStr, IEXMLDocument* edocument, ILHTMLActiveDocument* m_htmlActiveDoc, ILHTMLActiveView* m_htmlView)
{
#if 0	// TODO, have this
	if (paintStr != NULL)
	{
		int state = SaveDC(hDC);

		if (wcslen(paintStr) > 0)
		{
			if (!wcscmp(paintStr, L"none"))
			{
				DrawPaintNone(hDC, rc, rc2);
				return;
			}

			ExcludeClipRect(hDC, rc2.left, rc2.top, rc2.right, rc2.bottom);

			CRect rect(0, 0, rc.Width(), rc.Height());

			CComQIPtr<IOleDocumentView> oleView = m_htmlView;
			oleView->SetRect(&rect);

			CComPtr<ILDOMDocument> xmldocument;
			edocument->get_DOMDocument(&xmldocument);

		//
			CComPtr<ILSVGDocument> svgDocument;
			svgDocument.CoCreateInstance(CLSID_LSVGDocument);
			
			VARIANT_BOOL bsuccess;
			svgDocument->loadXML(L"<svg/>", &bsuccess);
			
			CComPtr<ILDOMElement> documentElement;
			svgDocument->get_documentElement(&documentElement);

			CComPtr<ILSVGRectElement> rectElement;
			svgDocument->createElement(L"rect", (ILDOMElement**)&rectElement);
			
			// Add 1 to all sides because of antialiasing
			rectElement->setAttribute(L"x", L"-1");
			rectElement->setAttribute(L"y", L"-1");
			rectElement->setAttribute(L"width", _bstr_t(_variant_t((long)(rc.Width()+2))));
			rectElement->setAttribute(L"height", _bstr_t(_variant_t((long)(rc.Height()+2))));

			CComQIPtr<ILElementCSSInlineStyle> stylable = rectElement;

			CComPtr<ILCSSStyleDeclaration> style;
			stylable->get_style(&style);

			style->setProperty(L"stroke", L"none", NULL);

			if (paintStr != NULL)
			{
				style->setProperty(L"fill", paintStr, NULL);

				CComPtr<ILSVGPaint> paint;
				style->getPropertyCSSValue(L"fill", (ILCSSValue**)&paint);

				LSVGPaintType paintType;
				paint->get_paintType(&paintType);

				if (paintType == SVG_PAINTTYPE_RGBCOLOR ||
					paintType == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR)
				{
					CLRGBColor rgbColor;
					//CComPtr<ILRGBColor> rgbColor;
					paint->get_rgbColor(&rgbColor);

					/*
					CComPtr<ILCSSPrimitiveValue> cssred;
					rgbColor->get_red(&cssred);
					double red;
					cssred->getFloatValue(CSS_NUMBER, &red);

					CComPtr<ILCSSPrimitiveValue> cssgreen;
					rgbColor->get_green(&cssgreen);
					double green;
					cssgreen->getFloatValue(CSS_NUMBER, &green);

					CComPtr<ILCSSPrimitiveValue> cssblue;
					rgbColor->get_blue(&cssblue);
					double blue;
					cssblue->getFloatValue(CSS_NUMBER, &blue);
					*/
					int red = rgbColor.GetRed();
					int green = rgbColor.GetGreen();
					int blue = rgbColor.GetBlue();

					FillSolidRect(hDC, &rc, RGB(red, green, blue));			
				}
				else if (paintType == SVG_PAINTTYPE_URI_NONE ||
							paintType == SVG_PAINTTYPE_URI_CURRENTCOLOR ||
							paintType == SVG_PAINTTYPE_URI_RGBCOLOR ||
							paintType == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
				{
					CComBSTR uri;
					paint->get_uri(&uri);

					CComPtr<ILDOMElement> uriElement;
					xmldocument->getElementById(uri, &uriElement);
					if (uriElement)
					{
						CComPtr<ILSVGElement> paintElement;
						svgDocument->importNode(uriElement, VARIANT_TRUE, (ILDOMNode**)&paintElement);

						CComQIPtr<ILSVGLinearGradientElement> linearGradientElement = paintElement;
						CComQIPtr<ILSVGRadialGradientElement> radialGradientElement = paintElement;
						CComQIPtr<ILSVGPatternElement> patternElement = paintElement;

						if (linearGradientElement)
						{
							linearGradientElement->setAttribute(L"gradientUnits", L"objectBoundingBox");
							linearGradientElement->setAttribute(L"x1", L"0%");
							linearGradientElement->setAttribute(L"y1", L"0%");
							linearGradientElement->setAttribute(L"x2", L"100%");
							linearGradientElement->setAttribute(L"y2", L"0%");
						}
						else if (radialGradientElement)
						{
							radialGradientElement->setAttribute(L"gradientUnits", L"objectBoundingBox");
							radialGradientElement->setAttribute(L"cx", L"50%");
							radialGradientElement->setAttribute(L"cy", L"50%");
							radialGradientElement->setAttribute(L"r", L"50%");
						}

						documentElement->appendChild(paintElement, NULL);
					}

					documentElement->appendChild(rectElement, NULL);

					m_htmlActiveDoc->SetDocument(svgDocument);

					CComPtr<ILHTMLWindow> window;
					m_htmlView->GetHTMLWindow(&window);

		//	window->put_noscroll(VARIANT_TRUE);

			//
					BITMAPINFO bmi = {0};
					bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
					bmi.bmiHeader.biWidth = rc.Width();
					bmi.bmiHeader.biHeight = -rc.Height();
					bmi.bmiHeader.biBitCount = 24;
					bmi.bmiHeader.biPlanes = 1;

					HBITMAP hTBitmap;
					LPBYTE TBits = NULL;

					if (hTBitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&TBits, NULL, 0))
					{
						HDC hTDC = CreateCompatibleDC(NULL);
						HBITMAP hOldBitmap = (HBITMAP)SelectObject(hTDC, hTBitmap);

						FillSolidRect(hTDC, 0, 0, rc.Width(), rc.Height(), RGB(255, 255, 255));

						window->DrawToHdc(hTDC, rectElement, 1);

						BitBlt(hDC, rc.left, rc.top, rc.Width(), rc.Height(), hTDC, 0, 0, SRCCOPY);

						SelectObject(hTDC, hOldBitmap);
						DeleteDC(hTDC);

						DeleteObject(hTBitmap);
					}
				}
				else
					ATLASSERT(0);
			}
		}
		else
		{
			SetBkMode(hDC, TRANSPARENT);

			if (rc2.IsRectEmpty())
			{
				DrawText(hDC, "?", 1, &rc, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			}
			else
			{
//				int w = 12;
//				int h = 12;

				DrawText(hDC, "?", 1, &rc, DT_LEFT | DT_TOP | DT_SINGLELINE);
				DrawText(hDC, "?", 1, &rc, DT_RIGHT | DT_TOP | DT_SINGLELINE);
				DrawText(hDC, "?", 1, &rc, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);
				DrawText(hDC, "?", 1, &rc, DT_RIGHT | DT_BOTTOM | DT_SINGLELINE);
			}
		}

		RestoreDC(hDC, state);
	}
#endif
}

void CSVGToolsDlg::DrawFillPaint(CDC& dc, CRect rc, WCHAR* fillStr)
{
	if (fillStr)// && wcslen(fillStr) > 0)
	{
		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		CRect emptyrc(0,0,0,0);

//		dc.Rectangle(rc.left, rc.top, rc.right, rc.bottom);

		dc.Draw3dRect(&rc, RGB(0,0,0), RGB(0,0,0));
		rc.InflateRect(-1, -1);

		dc.Draw3dRect(&rc, RGB(255,255,255), RGB(255,255,255));
		rc.InflateRect(-1, -1);

		//rc.InflateRect(-2, -2);
		DrawPaint(dc.m_hDC, rc, emptyrc, fillStr, edocument, m_htmlActiveDoc, m_htmlView);
	}
}

void CSVGToolsDlg::DrawStrokePaint(CDC& dc, CRect rc, WCHAR* strokeStr)
{
	if (strokeStr)// && wcslen(strokeStr) > 0)
	{
		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		dc.Draw3dRect(&rc, RGB(0,0,0), RGB(0,0,0));
		rc.InflateRect(-1, -1);

		dc.Draw3dRect(&rc, RGB(255,255,255), RGB(255,255,255));
		rc.InflateRect(-1, -1);

		CRect rc2 = rc;
		rc2.InflateRect(-5, -5);
		dc.Draw3dRect(&rc2, RGB(0,0,0), RGB(0,0,0));

		//rc2.InflateRect(1, 1);
		DrawPaint(dc.m_hDC, rc, rc2, strokeStr, edocument, m_htmlActiveDoc, m_htmlView);
	}
	else
	{
		CRect rc2 = rc;
		rc2.InflateRect(-1-1-5, -1-1-5);
		dc.Draw3dRect(&rc2, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
	}
}

LRESULT CSVGToolsDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC pdc(m_hWnd);

	CRect clip;
	pdc.GetClipBox(&clip);

	CDC dc;
	dc.CreateCompatibleDC(pdc);

	CBitmap offbitmap;
	offbitmap.CreateCompatibleBitmap(pdc, clip.Width(), clip.Height());

	HBITMAP hOldBitmap = dc.SelectBitmap(offbitmap);

	dc.SetViewportOrg(-clip.left, -clip.top);

	CRect client;
	GetClientRect(&client);

	int top = client.bottom-64;

	dc.FillSolidRect(0, top, client.right, 64, GetSysColor(COLOR_BTNFACE/*COLOR_MENU*//*30*/));

	dc.Draw3dRect(2, top, client.right-4, 2, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
	dc.Draw3dRect(2, top+48-2, client.right-4, 2, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

	if (m_viewGroup)
	{
		BOOL m_bCanHavePaint = SelectionCanHavePaint(m_viewGroup);

		if (m_htmlActiveDoc && m_bCanHavePaint)
		{
			CComPtr<ILCSSStyleDeclaration> style;

			CComBSTR strokeStr;
			CComBSTR fillStr;

			if (m_viewGroup && m_bCanHavePaint)
			{
				CComQIPtr<IECSSSelection>(m_viewGroup)->GetCurrentSelectionCSSStyle(&style);

				style->getPropertyValue(L"stroke", &strokeStr);
				style->getPropertyValue(L"fill", &fillStr);
			}

			{
				int state = dc.SaveDC();
				dc.ExcludeClipRect(&m_strokerc);
				dc.ExcludeClipRect(&m_fillrc);

				CRect rc2;

				rc2 = m_strokerc;
				rc2.InflateRect(1, 1);
				dc.Draw3dRect(&rc2, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

				rc2 = m_fillrc;
				rc2.InflateRect(1, 1);
				dc.Draw3dRect(&rc2, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

				dc.RestoreDC(state);
			}

			{
				if (m_app->m_strokeOrFill == 0)
				{
					int state = dc.SaveDC();
					dc.ExcludeClipRect(&m_strokerc);
					DrawFillPaint(dc, m_fillrc, fillStr);

					dc.RestoreDC(state);
					DrawStrokePaint(dc, m_strokerc, strokeStr);
				}
				else
				{
					int state = dc.SaveDC();
					dc.ExcludeClipRect(&m_fillrc);
					DrawStrokePaint(dc, m_strokerc, strokeStr);

					dc.RestoreDC(state);
					DrawFillPaint(dc, m_fillrc, fillStr);
				}
			}

			if (m_viewGroup && m_bCanHavePaint)
			{
				CRect rc;
				CRect emptyrc(0,0,0,0);

				CComPtr<IEXMLDocument> document;
				m_viewGroup->get_eXMLDocument(&document);
				CEXMLDocument* pDocument = static_cast<CEXMLDocument*>(document.p);

				_bstr_t propertyName = (m_app->m_strokeOrFill==0)? L"stroke": L"fill";

				CComPtr<ILSVGPaint> paint;
				style->getPropertyCSSValue(propertyName, (ILCSSValue**)&paint);

				if (paint)
				{
					LSVGPaintType paintType;
					paint->get_paintType(&paintType);

					int active = -1;

					if (paintType == SVG_PAINTTYPE_RGBCOLOR ||
						paintType == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR)
					{
						active = 0;
					}
					else if (paintType == SVG_PAINTTYPE_URI_NONE ||
								paintType == SVG_PAINTTYPE_URI_CURRENTCOLOR ||
								paintType == SVG_PAINTTYPE_URI_RGBCOLOR ||
								paintType == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
					{
						active = 1;
					}
					else if (paintType == SVG_PAINTTYPE_NONE)
					{
						active = 2;
					}
					else if (paintType == SVG_PAINTTYPE_CURRENTCOLOR)
					{
						// TODO ?
					}

					if (active >= 0)
					{
						CRect rc = m_drc[active];
						dc.Draw3dRect(&rc, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DSHADOW));
						rc.InflateRect(-1, -1);
					//	dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DHILIGHT));
					//	rc.InflateRect(-1, -1);
					//	dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DHILIGHT));
						dc.FillSolidRect(&rc, GetSysColor(COLOR_3DHILIGHT));
					}
				}

				rc = m_drc[0];
				rc.InflateRect(-2, -2);
				dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DSHADOW));
				rc.InflateRect(-1, -1);
				DrawPaint(dc.m_hDC, rc, emptyrc, pDocument->m_lastColor, document, m_htmlActiveDoc, m_htmlView);

				rc = m_drc[1];
				rc.InflateRect(-2, -2);
				dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DSHADOW));
				rc.InflateRect(-1, -1);
				DrawPaint(dc.m_hDC, rc, emptyrc, pDocument->m_lastGradient, document, m_htmlActiveDoc, m_htmlView);

				rc = m_drc[2];
				rc.InflateRect(-2, -2);
				dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DSHADOW));
				rc.InflateRect(-1, -1);
				DrawPaintNone(dc.m_hDC, rc, emptyrc);
			}
		}
	}

	pdc.BitBlt(clip.left, clip.top, clip.Width(), clip.Height(), dc, clip.left, clip.top, SRCCOPY);

	dc.SelectBitmap(hOldBitmap);

	return 0;
}

LRESULT CSVGToolsDlg::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HDC hDC = (HDC)wParam;

	return TRUE;
}

LRESULT CSVGToolsDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect client;
	GetClientRect(&client);

	int top = client.bottom-64;

	if (m_viewGroup)
	{
		BOOL m_bCanHavePaint = SelectionCanHavePaint(m_viewGroup);

		if (m_bCanHavePaint)
		{
			CComPtr<IEXMLDocument> document;
			m_viewGroup->get_eXMLDocument(&document);

			CEXMLDocument* pDocument = static_cast<CEXMLDocument*>(document.p);

			if (point.y > top)
			{
				if (point.y < top+48)
				{
					if (m_app->m_strokeOrFill == 0)
					{
						if (!m_strokerc.PtInRect(point) && m_fillrc.PtInRect(point))
						{
							m_app->m_strokeOrFill = 1;
							static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_colorEditing = L"fill";

							CComPtr<ILSVGPaint> paint;
							pDocument->m_defaultStyle->getPropertyCSSValue(L"fill", (ILCSSValue**)&paint);

							if (paint)
							{
								LSVGPaintType paintType;
								paint->get_paintType(&paintType);

								if (paintType == SVG_PAINTTYPE_RGBCOLOR ||
									paintType == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR)
								{
									LRGBColor rgbColor;
									paint->get_rgbColor(&rgbColor);

									/*
									pDocument->m_defaultColorRed = rgbColor.GetRed();
									pDocument->m_defaultColorGreen = rgbColor.GetGreen();
									pDocument->m_defaultColorBlue = rgbColor.GetBlue();
									pDocument->m_lastColor = MakeRGBString(pDocument->m_defaultColorRed, pDocument->m_defaultColorGreen, pDocument->m_defaultColorBlue);
									*/
								}
							}

							Invalidate();

							/*
							BSTR b;
							pDocument->m_defaultStyle->getPropertyValue(L"fill", &b);
							pDocument->m_defaultColor = _bstr_t(b, false);
							*/
						}
					}
					else
					{
						if (!m_fillrc.PtInRect(point) && m_strokerc.PtInRect(point))
						{
							m_app->m_strokeOrFill = 0;
							static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_colorEditing = L"stroke";

							CComPtr<ILSVGPaint> paint;
							pDocument->m_defaultStyle->getPropertyCSSValue(L"stroke", (ILCSSValue**)&paint);
							if (paint)
							{
								LSVGPaintType paintType;
								paint->get_paintType(&paintType);

								if (paintType == SVG_PAINTTYPE_RGBCOLOR ||
									paintType == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR)
								{
									LRGBColor rgbColor;
									paint->get_rgbColor(&rgbColor);

									/*
									pDocument->m_defaultColorRed = rgbColor.GetRed();
									pDocument->m_defaultColorGreen = rgbColor.GetGreen();
									pDocument->m_defaultColorBlue = rgbColor.GetBlue();
									pDocument->m_defaultColor = MakeRGBString(pDocument->m_defaultColorRed, pDocument->m_defaultColorGreen, pDocument->m_defaultColorBlue);
									*/
								}
							}

							/*
							BSTR b;
							pDocument->m_defaultStyle->getPropertyValue(L"stroke", &b);
							pDocument->m_defaultColor = _bstr_t(b, false);
							*/

							Invalidate();
						}
					}

					static_cast<CEXMLViewGroup*>(m_viewGroup.p)->SetCurrentSelectionColor();

					static_cast<CEXMLViewGroup*>(m_viewGroup.p)->Fire_ColorChanged();
				}
				else if (point.y >= top+48)
				{
					_bstr_t propertyName = (m_app->m_strokeOrFill == 0)? L"stroke": L"fill";

					CComPtr<ILCSSStyleDeclaration> style;
					CComQIPtr<IECSSSelection>(m_viewGroup)->GetCurrentSelectionCSSStyle(&style);

					BOOL bApply = FALSE;

					if (m_drc[0].PtInRect(point))	// Color
					{
						//if (pDocument->m_defaultColor.length())
						style->setProperty(propertyName, pDocument->m_lastColor/*MakeRGBString(pDocument->m_defaultColorRed, pDocument->m_defaultColorGreen, pDocument->m_defaultColorBlue)*/, NULL);
						//else
						//	style->removeProperty(propertyName, NULL);

						bApply = TRUE;
					}
					else if (m_drc[1].PtInRect(point))	// Gradient/Pattern
					{
						if (pDocument->m_lastGradient.Length())
							style->setProperty(propertyName, pDocument->m_lastGradient, NULL);
						else
							style->removeProperty(propertyName, NULL);

						bApply = TRUE;
					}
					else if (m_drc[2].PtInRect(point))	// None
					{
						style->setProperty(propertyName, L"none", NULL);
						bApply = TRUE;
					}

					if (bApply)
					{
						Invalidate();	// ??TODO remove??

						CComQIPtr<IECSSSelection>(m_viewGroup)->ApplyCurrentSelectionCSSStyle();

						static_cast<CEXMLViewGroup*>(m_viewGroup.p)->SetCurrentSelectionColor();
						static_cast<CEXMLViewGroup*>(m_viewGroup.p)->Fire_ColorChanged();
					}
				}
			}
		}
	}

	return 0;
}

// ILCSSStyleDeclarationHandler
STDMETHODIMP CSVGToolsDlg::handleCSSEvent(/*[in]*/ long type, /*[in]*/ BSTR propertyName)
{
	CRect client;
	GetClientRect(&client);
	if (m_hWnd)
	{
		// TODO have this
		InvalidateRect(&CRect(0, client.bottom-64, 64, client.bottom));
	}
	return S_OK;
}

#if 0
// IUIEventHandler
STDMETHODIMP CSVGToolsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;
	if (viewGroup)
	{
		if (m_viewGroup != NULL)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			CComQIPtr<IECSSSelection>(m_viewGroup)->GetCurrentSelectionCSSStyle(&style);

			style->removeHandler(this);

#if 0
			static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionStyle->removeHandler(this);
#endif
	//		CComQIPtr<ILDOMEventTarget> eventTarget = m_xmlDocument;
	//		eventTarget->removeEventListener(L"DOMNodeInserted", this, VARIANT_TRUE);

	//		IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);
		}

		m_viewGroup = viewGroup;
#if 0
		static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionStyle->addHandler(this);
#endif

		CComPtr<ILCSSStyleDeclaration> style;
		CComQIPtr<IECSSSelection>(m_viewGroup)->GetCurrentSelectionCSSStyle(&style);

		style->addHandler(this);

//		IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventAdvise(m_document);

		if (m_hWnd)
		{
			Invalidate();
		}

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CSVGToolsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
//	ATLASSERT(IsUnknownEqualUnknown(m_document, object));

//	IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);

	CComPtr<ILCSSStyleDeclaration> style;
	CComQIPtr<IECSSSelection>(m_viewGroup)->GetCurrentSelectionCSSStyle(&style);

	style->removeHandler(this);

#if 0
	static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionStyle->removeHandler(this);
#endif
	m_viewGroup.Release();

	if (m_hWnd)
	{
		Invalidate();
	}

	return S_OK;
}
#endif

#endif