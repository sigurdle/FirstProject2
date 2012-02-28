// ImageColorDlg.cpp : Implementation of CImageColorDlg
#include "stdafx.h"
#include "LXImageEditor.h"
#include "Image2.h"

#include "ImageColorDlg.h"

/*
#include "WebXMLDocument.h"	// TODO Remove
#include "WebXMLViewGroup.h"	// TODO Remove
#include "WebEditorApp.h"	// TODO Remove
#include "WebEditorFrame.h"	// TODO Remove
extern CWebEditorApp* gApp;	// TODO Remove
*/

#include "ImageDocument.h"	// TODO remove

//void DrawPaint(HDC hDC, CRect& rc, CRect& rc2, WCHAR* paintStr, IEXMLDocument* edocument, ILHTMLActiveDocument* m_htmlActiveDoc, ILHTMLActiveView* m_htmlView);

/////////////////////////////////////////////////////////////////////////////
// CImageColorDlg

int CImageColorDlg::FinalConstruct()
{
#if 0
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->FindMenu(IDR_IMAGECOLORDLG, &m_menu);
#endif

	return S_OK;
}

void CImageColorDlg::FinalRelease()
{
}

LRESULT CImageColorDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	GetDlgControl(IDC_COLOR_CHANNELSLIDER0, IID_IUIColorSlider, (void**)&m_slider[0]);
	GetDlgControl(IDC_COLOR_CHANNELSLIDER1, IID_IUIColorSlider, (void**)&m_slider[1]);
	GetDlgControl(IDC_COLOR_CHANNELSLIDER2, IID_IUIColorSlider, (void**)&m_slider[2]);

	IDispEventImpl<1, CImageColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_slider[0]);
	IDispEventImpl<2, CImageColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_slider[1]);
	IDispEventImpl<3, CImageColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_slider[2]);

	int i;

	for (i = 0; i < 3; i++)
	{
		m_slider[i]->put_channel(i);
		m_slider[i]->put_colorMode(2);
	}

	for (i = 0; i < 3; i++)
	{
		m_slider[i]->put_Enabled(FALSE);
		::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE0+i), FALSE);
		SetDlgItemText(IDC_SWATCH_CHANNELVALUE0+i, _T(""));
	}

	m_fillrc = CRect(6, 6, 6+18, 6+18);
	m_strokerc = CRect(6+9, 6+9, 6+18+9, 6+18+9);

#if 0
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);
#endif

	return 0;
}

LRESULT CImageColorDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);
#endif

	IDispEventImpl<1, CImageColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[0]);
	IDispEventImpl<2, CImageColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[1]);
	IDispEventImpl<3, CImageColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[2]);
//	IDispEventImpl<4, CImageColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[3]);

	for (int i = 0; i < 4; i++)
	{
		m_slider[i].Release();
	}

	return 0;
}

void CImageColorDlg::DrawFillPaint(CDC& dc, CRect rc, WCHAR* fillStr)
{
#if 0
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
#endif
}

void CImageColorDlg::DrawStrokePaint(CDC& dc, CRect rc, WCHAR* strokeStr)
{
#if 0
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
#endif
}

LRESULT CImageColorDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

#if 0
	if (m_viewGroup)
	{
		if (!wcscmp(static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"stroke") ||
			!wcscmp(static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"fill"))
		{
			CComPtr<ILCSSStyleDeclaration> style;

			CComBSTR strokeStr;
			CComBSTR fillStr;

			if (m_viewGroup)
			{
				//style = ((CWebXMLDocument*)m_document.p)->m_defaultStyle;
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
		}
		else if (!wcscmp(static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"stop-color") ||
					!wcscmp(static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"solid-color"))
		{
			CComPtr<ILCSSStyleDeclaration> style;
			m_viewGroup->GetCurrentSelectionCSSStyle(&style);

			CComPtr<ILSVGColor> svgColor;
			style->getPropertyCSSValue(static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, (ILCSSValue**)&svgColor);

			if (svgColor)
			{
				CLRGBColor rgbColor;
				svgColor->get_rgbColor(&rgbColor);

				double red = rgbColor.GetRed();
				double green = rgbColor.GetGreen();
				double blue = rgbColor.GetBlue();

				CRect rc = CRect(6, 6, 6+18+9, 6+18+9);

				dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
				rc.InflateRect(-1,-1);

				dc.FillSolidRect(&rc, RGB(red, green, blue));			

				if (!wcscmp(static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_colorEditing, L"stop-color"))
				{
					// TODO: draw knob
				}
			}
		}
	}
#endif

	return 0;
}

HRESULT __stdcall CImageColorDlg::OnSlider0SetPos(long pos)
{
	OnSliderPos(0, pos);
	return S_OK;
}

HRESULT __stdcall CImageColorDlg::OnSlider1SetPos(long pos)
{
	OnSliderPos(1, pos);
	return S_OK;
}

HRESULT __stdcall CImageColorDlg::OnSlider2SetPos(long pos)
{
	OnSliderPos(2, pos);
	return S_OK;
}

HRESULT __stdcall CImageColorDlg::OnSlider3SetPos(long pos)
{
	OnSliderPos(3, pos);
	return S_OK;
}

void CImageColorDlg::OnSliderPos(int channel, long nPos)
{
	m_channelValue[channel] = nPos;

	COLORREF clr = RGB(m_channelValue[0], m_channelValue[1], m_channelValue[2]);

	for (int i = 0; i < 3; i++)
	{
		if (i != channel)
		{
			m_slider[i]->put_rgb(clr);
		}
		else
		{
			SetDlgItemInt(IDC_SWATCH_CHANNELVALUE0+i, nPos);
		}
	}

	CComPtr<IImageDocument> document;
	m_view->GetDocument(&document);

	static_cast<CImageDocument*>(document.p)->m_color[0] = m_channelValue[0];
	static_cast<CImageDocument*>(document.p)->m_color[1] = m_channelValue[1];
	static_cast<CImageDocument*>(document.p)->m_color[2] = m_channelValue[2];

	OnColorChanged();	// TODO remove

#if 0
	ATLASSERT(m_viewGroup);
	static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->setRGBValue(m_channelValue[0], m_channelValue[1], m_channelValue[2]);
#endif
//	m_color->setRGBValue(m_channelValue[0], m_channelValue[1], m_channelValue[2]);
}

void CImageColorDlg::UpdateSliders()
{
}

#if 0
STDMETHODIMP CImageColorDlg::SetColor(IEColor *color)
{
	ATLASSERT(0);
/*
	m_color = color;

	if (m_color)
	{
		HRESULT hr[3];

		long r, g, b;
		hr[0] = m_color->get_red(&r);
		hr[1] = m_color->get_green(&g);
		hr[2] = m_color->get_blue(&b);

		m_channelValue[0] = r;
		m_channelValue[1] = g;
		m_channelValue[2] = b;

		BOOL bEnable;
		if (hr[0] == S_FALSE) bEnable = FALSE;
		else if (hr[1] == S_FALSE) bEnable = FALSE;
		else if (hr[2] == S_FALSE) bEnable = FALSE;
		else bEnable = TRUE;

		if (bEnable)
		{
			DWORD clr = RGB(m_channelValue[0], m_channelValue[1], m_channelValue[2]);

			for (int i = 0; i < 3; i++)
			{
				m_slider[i]->put_rgb(clr);
				m_slider[i]->put_Enabled(TRUE);
				SetDlgItemInt(IDC_SWATCH_CHANNELVALUE0+i, m_channelValue[i]);
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				m_slider[i]->put_pos(m_channelValue[i]);
				m_slider[i]->put_Enabled(TRUE);
			}
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			m_slider[i]->put_Enabled(FALSE);
		}
	}
*/
	return S_OK;
}
#endif

void __stdcall CImageColorDlg::OnColorChanged()
{
	/*
	double red = static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionColorRed;
	double green = static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionColorGreen;
	double blue = static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionColorBlue;
*/
	CComPtr<IImageDocument> document;
	m_view->GetDocument(&document);

	long red = static_cast<CImageDocument*>(document.p)->m_color[0];
	long green = static_cast<CImageDocument*>(document.p)->m_color[1];
	long blue = static_cast<CImageDocument*>(document.p)->m_color[2];

	if (TRUE/*m_color*/)
	{
		HRESULT hr[3];

		long r = red, g = green, b = blue;
		hr[0] = !(r>=0 && r<=255);
		hr[1] = !(g>=0 && g<=255);
		hr[2] = !(b>=0 && b<=255);

		m_channelValue[0] = r;
		m_channelValue[1] = g;
		m_channelValue[2] = b;

		BOOL bEnable;
		if (hr[0] != S_OK) bEnable = FALSE;
		else if (hr[1] != S_OK) bEnable = FALSE;
		else if (hr[2] != S_OK) bEnable = FALSE;
		else bEnable = TRUE;

		if (bEnable)
		{
			DWORD clr = RGB(m_channelValue[0], m_channelValue[1], m_channelValue[2]);

			for (int i = 0; i < 3; i++)
			{
				m_slider[i]->put_rgb(clr);
				m_slider[i]->put_Enabled(1);

				::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE0+i), TRUE);
				SetDlgItemInt(IDC_SWATCH_CHANNELVALUE0+i, m_channelValue[i]);
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				m_slider[i]->put_pos(m_channelValue[i]);
				m_slider[i]->put_Enabled(2);

				::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE0+i), TRUE);

				if (hr[i] == S_OK) 
					SetDlgItemInt(IDC_SWATCH_CHANNELVALUE0+i, m_channelValue[i]);
				else
					SetDlgItemText(IDC_SWATCH_CHANNELVALUE0+i, _T(""));
			}
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			m_slider[i]->put_Enabled(FALSE);
			::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE0+i), FALSE);
			SetDlgItemText(IDC_SWATCH_CHANNELVALUE0+i, _T(""));
		}
	}

	CRect rc = CRect(6, 6, 6+18+9, 6+18+9);
	InvalidateRect(&rc);
}

// IUIEventHandler
STDMETHODIMP CImageColorDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IImageView> view = object;
	if (view)
	{
		m_view = view;

		OnColorChanged();

#if 0
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

			IDispEventImpl<7, CImageColorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);
		}

		m_viewGroup = viewGroup;
#if 0
		static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionStyle->addHandler(this);
#endif
		IDispEventImpl<7, CImageColorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

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
#endif

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CImageColorDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	m_view.Release();
#if 0
//	ATLASSERT(IsUnknownEqualUnknown(m_document, object));

//	IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);

	/*
	CComPtr<ILCSSStyleDeclaration> style;
	m_viewGroup->GetCurrentSelectionCSSStyle(&style);

	style->removeHandler(this);
	*/

	IDispEventImpl<7, CImageColorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);

#if 0
	static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionStyle->removeHandler(this);
#endif
	m_viewGroup.Release();

	for (int i = 0; i < 3; i++)
	{
		m_slider[i]->put_Enabled(FALSE);
		if (m_hWnd)
		{
			::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE0+i), FALSE);
			SetDlgItemText(IDC_SWATCH_CHANNELVALUE0+i, _T(""));
		}
	}

	if (m_hWnd)
	{

		Invalidate();
	}
#endif
	return S_OK;
}

BEGIN_CMD_MAP(CImageColorDlg)
	CMD_HANDLER(ID_COLOR_INVERT, OnColorInvert)
	CMD_HANDLER(ID_COLOR_COMPLEMENT, OnColorComplement)
//	CMD_UPDATE(ID_SVGOBJECTS_DELETESELECTION, OnDeleteSelectionUpdate)
END_CMD_MAP()

LRESULT CImageColorDlg::OnColorInvert(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CImageColorDlg::OnColorComplement(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}
