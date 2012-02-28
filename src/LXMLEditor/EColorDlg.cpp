// EColorDlg.cpp : Implementation of CEColorDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "EColorDlg.h"

#include "RGBSlidersDlg.h"	// TODO remove?
#include "HSLColorWheelDlg.h"	// TODO remove?
#include "NamedColorsDlg.h"	// TODO remove?

#include "EXMLDocument.h"	// TODO Remove
#include "EXMLViewGroup.h"	// TODO Remove

#if 0

void DrawPaint(HDC hDC, CRect& rc, CRect& rc2, WCHAR* paintStr, IEXMLDocument* edocument, ILHTMLActiveDocument* m_htmlActiveDoc, ILHTMLActiveView* m_htmlView);

/////////////////////////////////////////////////////////////////////////////
// CEColorDlg

int CEColorDlg::FinalConstruct()
{
	return S_OK;
}

void CEColorDlg::FinalRelease()
{
}

LRESULT CEColorDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	GetDlgControl(IDC_COLOR_ALPHASLIDER, IID_IUISlider, (void**)&m_alphaSlider);
	IDispEventImpl<1, CEColorDlg, &DIID__IUISliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_alphaSlider);

	m_alphaSlider->put_minValue(0);
	m_alphaSlider->put_maxValue(255);

	if (FALSE)
	{
#if 0
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
#endif
	}

	m_fillrc = CRect(6, 6, 6+18, 6+18);
	m_strokerc = CRect(6+9, 6+9, 6+18+9, 6+18+9);

	m_colorDlg = CreateColorPicker(m_nColorPicker);
	OnSize();

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->AddEventHandler(this);
	{
#if 0
		static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionStyle->addHandler(this);
#endif
		IDispEventImpl<7, CEColorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

		/*
		CComPtr<ILCSSStyleDeclaration> style;
		m_viewGroup->GetCurrentSelectionCSSStyle(&style);

		style->addHandler(this);
		*/

//		IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventAdvise(m_document);

		OnColorChanged();
	}

	return 0;
}

LRESULT CEColorDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->RemoveEventHandler(this);
	IDispEventImpl<7, CEColorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);

	m_htmlView.Release();
	m_htmlActiveDoc.Release();

	IDispEventImpl<1, CEColorDlg, &DIID__IUISliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_alphaSlider);

	return 0;
}

void CEColorDlg::DrawFillPaint(CDC& dc, CRect rc, WCHAR* fillStr)
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

void CEColorDlg::DrawStrokePaint(CDC& dc, CRect rc, WCHAR* strokeStr)
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
		rc2.InflateRect(-3, -3);
		dc.Draw3dRect(&rc2, RGB(0,0,0), RGB(0,0,0));

		//rc2.InflateRect(1, 1);
		DrawPaint(dc.m_hDC, rc, rc2, strokeStr, edocument, m_htmlActiveDoc, m_htmlView);
	}
	else
	{
		CRect rc2 = rc;
		rc2.InflateRect(-1-1-3, -1-1-3);
		dc.Draw3dRect(&rc2, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
	}
}

LRESULT CEColorDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	if (m_viewGroup)
	{
		if (!wcscmp(static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"stroke") ||
			!wcscmp(static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"fill"))
		{
#if 0
			CComPtr<ILCSSStyleDeclaration> style;

			CComBSTR strokeStr;
			CComBSTR fillStr;

			if (m_viewGroup)
			{
				//style = ((CEXMLDocument*)m_document.p)->m_defaultStyle;
				m_viewGroup->GetCurrentSelectionCSSStyle(&style);// = ((CWebXMLViewGroup*)m_viewGroup.p)->m_currentSelectionStyle;

				style->getPropertyValue(L"stroke", &strokeStr);
				//if (strokeStr.Length() == 0) strokeStr = L"";

				style->getPropertyValue(L"fill", &fillStr);
				//if (fillStr.Length() == 0) fillStr = L"";
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
				if (gApp->m_strokeOrFill == 0)
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
#endif
		}
		else if (!wcscmp(static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"stop-color") ||
					!wcscmp(static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"solid-color"))
		{
			CComPtr<ILCSSStyleDeclaration> style;
			static_cast<CEXMLViewGroup*>(m_viewGroup.p)->GetCurrentSelectionCSSStyle(&style);

			CComPtr<ILSVGColor> svgColor;
			style->getPropertyCSSValue(static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, (ILCSSValue**)&svgColor);

			if (svgColor)
			{
				LRGBColor rgbColor;
				svgColor->get_rgbColor(&rgbColor);

				double red = rgbColor.GetRed();
				double green = rgbColor.GetGreen();
				double blue = rgbColor.GetBlue();

				CRect rc = CRect(6, 6, 6+18+9, 6+18+9);

				dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
				rc.InflateRect(-1,-1);

				dc.FillSolidRect(&rc, RGB(red, green, blue));			

				if (!wcscmp(static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"stop-color"))
				{
					// TODO: draw knob
				}
			}
		}
		else if (!wcscmp(static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"color") ||
					!wcscmp(static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"background-color"))
		{
			CComPtr<ILCSSStyleDeclaration> style;
			static_cast<CEXMLViewGroup*>(m_viewGroup.p)->GetCurrentSelectionCSSStyle(&style);

			CComPtr<ILCSSPrimitiveValue> primValue;
			style->getPropertyCSSValue(static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, (ILCSSValue**)&primValue);

			if (primValue)
			{
				LRGBColor rgbColor;
				primValue->getRGBColorValue(&rgbColor);
				if (rgbColor.m_rgbColor)
				{
					double red = rgbColor.GetRed();
					double green = rgbColor.GetGreen();
					double blue = rgbColor.GetBlue();

					CRect rc = CRect(6, 6, 6+18+9, 6+18+9);

					dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
					rc.InflateRect(-1,-1);

					dc.FillSolidRect(&rc, RGB(red, green, blue));			
				}
			}
		}
	}

	return 0;
}

void CEColorDlg::SetColorPickerColor()
{
	double red = static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionColorRed;
	double green = static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionColorGreen;
	double blue = static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionColorBlue;

	CComQIPtr<IEColorPicker> picker = m_colorDlg;
	if (picker)
	{
		picker->SetRGBColorValue(red, green, blue);
	}
}

void __stdcall CEColorDlg::OnColorChanged()
{
	SetColorPickerColor();

	/*
	else
	{
		for (int i = 0; i < 3; i++)
		{
			m_slider[i]->put_Enabled(FALSE);
			::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE0+i), FALSE);
			SetDlgItemText(IDC_SWATCH_CHANNELVALUE0+i, _T(""));
		}
	}
	*/

	CRect rc = CRect(6, 6, 6+18+9, 6+18+9);
	InvalidateRect(&rc);
}

#if 0
// IUIEventHandler
STDMETHODIMP CEColorDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;
	if (viewGroup)
	{
		if (m_viewGroup != NULL)
		{
			/*
			CComPtr<ILCSSStyleDeclaration> style;
			m_viewGroup->GetCurrentSelectionCSSStyle(&style);

			style->removeHandler(this);
			*/

#if 0
			static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionStyle->removeHandler(this);
#endif
	//		CComQIPtr<ILDOMEventTarget> eventTarget = m_xmlDocument;
	//		eventTarget->removeEventListener(L"DOMNodeInserted", this, VARIANT_TRUE);

	//		IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);

			IDispEventImpl<7, CEColorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
		}

		m_viewGroup = viewGroup;
#if 0
		static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionStyle->addHandler(this);
#endif
		IDispEventImpl<7, CEColorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

		/*
		CComPtr<ILCSSStyleDeclaration> style;
		m_viewGroup->GetCurrentSelectionCSSStyle(&style);

		style->addHandler(this);
		*/

//		IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventAdvise(m_document);

		OnColorChanged();

		/*
		if (m_hWnd)
		{
			Invalidate();
		}
		*/

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CEColorDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
//	ASSERT(IsUnknownEqualUnknown(m_document, object));

//	IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);

	/*
	CComPtr<ILCSSStyleDeclaration> style;
	m_viewGroup->GetCurrentSelectionCSSStyle(&style);

	style->removeHandler(this);
	*/

	IDispEventImpl<7, CEColorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);

#if 0
	static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionStyle->removeHandler(this);
#endif
	m_viewGroup.Release();

	// Tell m_colorDlg
	// TODO picker->Enable(FALSE) ??
	CComQIPtr<IEColorPicker> picker = m_colorDlg;
	if (picker)
	{
		picker->SetRGBColorValue(-1, -1, -1);
	}
	/*
	for (int i = 0; i < 3; i++)
	{
		m_slider[i]->put_Enabled(FALSE);
		if (m_hWnd)
		{
			::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE0+i), FALSE);
			SetDlgItemText(IDC_SWATCH_CHANNELVALUE0+i, _T(""));
		}
	}
	*/

	if (m_hWnd)
	{

		Invalidate();
	}

	return S_OK;
}
#endif

LRESULT CEColorDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	return 0;
}

void CEColorDlg::OnSize()
{
	if (m_colorDlg)
	{
		CRect client;
		GetClientRect(&client);

		HWND hWnd;
		m_colorDlg->get_hwnd(&hWnd);
		::MoveWindow(hWnd, 50, 0, client.right-50, 76, TRUE);
	}
}

CComPtr<IUIDlg> CEColorDlg::CreateColorPicker(int nColorPicker)
{
	CComPtr<IUIDlg> colorDlg;

	if (nColorPicker == 0)
	{
		/*
		CComObject<CColorPickerGrayscaleDlg>* p;
		CComObject<CColorPickerGrayscaleDlg>::CreateInstance(&p);
		if (p)
		{
			colorDlg = p;
		}
		*/
	}
	else if (nColorPicker == 1)
	{
		CComObject<CRGBSlidersDlg>* p;
		CComObject<CRGBSlidersDlg>::CreateInstance(&p);
		if (p)
		{
			colorDlg = p;
		}
	}
	else if (nColorPicker == 2)
	{
		CComObject<CHSLColorWheelDlg>* p;
		CComObject<CHSLColorWheelDlg>::CreateInstance(&p);
		if (p)
		{
			colorDlg = p;
		}
	}
	else if (nColorPicker == 3)
	{
		CComObject<CNamedColorsDlg>* p;
		CComObject<CNamedColorsDlg>::CreateInstance(&p);
		if (p)
		{
			colorDlg = p;
		}
	}
	else
		ASSERT(0);

	if (colorDlg)
	{
		CComQIPtr<IEColorPicker> colorpicker = colorDlg;
		if (colorpicker)
		{
			colorpicker->SetSite(this);
			colorDlg->Create(m_hWnd);

			HWND hWnd;
			colorDlg->get_hwnd(&hWnd);
			if (hWnd)
			{
				::ShowWindow(hWnd, SW_SHOW);

				return colorDlg;
			}
		}
	}

	return NULL;
}

void CEColorDlg::SetColorPicker(int nColorPicker)
{
	if (m_nColorPicker != nColorPicker)
	{
		CComPtr<IUIDlg> colorDlg = CreateColorPicker(nColorPicker);

		if (colorDlg)
		{
		// Remove previous color picker
			if (m_colorDlg)
			{
				m_colorDlg->DestroyWindow();
				m_colorDlg.Release();
			}

			m_colorDlg = colorDlg;
			m_nColorPicker = nColorPicker;

			SetColorPickerColor();

			OnSize();
		}
		else
		{
			MessageBox("Failed to create color picker", "LXMLEditor", MB_OK | MB_ICONERROR);
		}
	}
}

// IEColorSite
STDMETHODIMP CEColorDlg::SetRGBColorValue(/*[in]*/ long red, /*[in]*/ long green, /*[in]*/ long blue)
{
	static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionColorRed = red;
	static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionColorGreen = green;
	static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionColorBlue = blue;

	static_cast<CEXMLViewGroup*>(m_viewGroup.p)->ApplyCurrentSelectionColor();

// The above does the same
//	ASSERT(m_viewGroup);
//	static_cast<CEXMLViewGroup*>(m_viewGroup.p)->setRGBAValue(red, green, blue, m_alpha);

	return S_OK;
}

void __stdcall CEColorDlg::OnAlphaSliderPos(long code, long pos)
{
	m_alpha = pos;

	TCHAR buf[64];
	sprintf(buf, "%.1f", (double)m_alpha*100/255);
	SetDlgItemText(IDC_COLOR_ALPHAVALUE, buf);

	static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionColorAlpha = m_alpha;

	static_cast<CEXMLViewGroup*>(m_viewGroup.p)->ApplyCurrentSelectionColor();
}

BEGIN_CMD_MAP(CEColorDlg)
	CMD_HANDLER(ID_COLOR_GRAYSCALE, OnColorGrayscale)
	CMD_UPDATE(ID_COLOR_GRAYSCALE, OnColorGrayscaleUpdate)
	CMD_HANDLER(ID_COLOR_RGBSLIDERS, OnColorRGBSliders)
	CMD_UPDATE(ID_COLOR_RGBSLIDERS, OnColorRGBSlidersUpdate)
	CMD_HANDLER(ID_COLOR_HSLWHEEL, OnColorHSLWheel)
	CMD_UPDATE(ID_COLOR_HSLWHEEL, OnColorHSLWheelUpdate)
	CMD_HANDLER(ID_COLOR_NAMEDCOLORS, OnColorNamedColors)
	CMD_UPDATE(ID_COLOR_NAMEDCOLORS, OnColorNamedColorsUpdate)

	CMD_HANDLER(ID_COLOR_INVERT, OnColorInvert)
	CMD_HANDLER(ID_COLOR_COMPLEMENT, OnColorComplement)
//	CMD_UPDATE(ID_SVGOBJECTS_DELETESELECTION, OnDeleteSelectionUpdate)
END_CMD_MAP()

LRESULT CEColorDlg::OnColorGrayscale(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetColorPicker(0);
	return 0;
}

void CEColorDlg::OnColorGrayscaleUpdate(long id, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_nColorPicker == 0);
}

LRESULT CEColorDlg::OnColorRGBSliders(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetColorPicker(1);
	return 0;
}

void CEColorDlg::OnColorRGBSlidersUpdate(long id, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_nColorPicker == 1);
}

LRESULT CEColorDlg::OnColorHSLWheel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetColorPicker(2);
	return 0;
}

void CEColorDlg::OnColorHSLWheelUpdate(long id, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_nColorPicker == 2);
}

LRESULT CEColorDlg::OnColorNamedColors(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetColorPicker(3);
	return 0;
}

void CEColorDlg::OnColorNamedColorsUpdate(long id, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_nColorPicker == 3);
}

LRESULT CEColorDlg::OnColorInvert(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CEColorDlg::OnColorComplement(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

#endif
