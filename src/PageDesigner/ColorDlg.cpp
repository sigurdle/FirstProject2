// ColorDlg.cpp : Implementation of CColorDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "ColorDlg.h"

/*
#include "PageDesignerApp.h"
#include "PageDesignerFrame.h"

extern CPageDesignerApp* gApp;
*/

/////////////////////////////////////////////////////////////////////////////
// CColorDlg

STDMETHODIMP CColorDlg::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IColorDlg
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

int CColorDlg::FinalConstruct()
{
	HRESULT hr;

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->FindMenu(IDR_COLOR, &m_menu);

	return 0;
}

LRESULT CColorDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		GetDlgControl(IDC_SWATCH_CHANNELSLIDER0+i, IID_IUIColorSlider, (void**)&m_slider[i]);
	}

	GetDlgControl(IDC_COLOR_SPECTRUM, IID_IColorSpectrum, (void**)&m_spectrum);

	for (i = 0; i < 3; i++)
	{
		m_slider[i]->put_channel(i);
	}

	IDispEventImpl<1, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_slider[0]);
	IDispEventImpl<2, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_slider[1]);
	IDispEventImpl<3, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_slider[2]);
//	IDispEventImpl<3, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_slider[2]);

	IDispEventImpl<5, CColorDlg, &DIID__IColorSpectrumEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_spectrum);

	::GetWindowRect(GetDlgItem(IDC_COLOR_NONE), &m_rcNone);
	ScreenToClient(&m_rcNone);

	m_rcStrokeFill.SetRect(2, 2, 2+30, 2+30);

	{
		CComQIPtr<INotifySend> cp = gIApp;
		DWORD cookie;
		cp->Advise(this, &cookie);
	}

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	return 0;
}

LRESULT CColorDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

	IDispEventImpl<1, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[0]);
	IDispEventImpl<2, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[1]);
	IDispEventImpl<3, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[2]);

	IDispEventImpl<5, CColorDlg, &DIID__IColorSpectrumEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_spectrum);

	CComQIPtr<INotifySend> cp = gIApp;
	cp->Unadvise(this);

	return 0;
}

void DrawBrushWithOutline(Gdiplus::Graphics* pGraphics, Gdiplus::Rect& rc, IPDBrush* brush, int bFill);

LRESULT CColorDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	if (m_object)
	{
		Gdiplus::Graphics graphics(dc.m_hDC);

		Gdiplus::Rect strokerc(2+10, 2+10, 20, 20);
		Gdiplus::Rect fillrc(2, 2, 20, 20);

		CComPtr<IPDObjectStroke> stroke;
		m_object->get_activeStroke(&stroke);
		CComPtr<IPDBrush> strokeBrush;
		stroke->get_brush(&strokeBrush);

		CComPtr<IPDObjectFill> fill;
		m_object->get_activeFill(&fill);
		CComPtr<IPDBrush> fillBrush;
		fill->get_brush(&fillBrush);

		if (m_strokeOrFill == 0)
		{
			graphics.ExcludeClip(strokerc);
			DrawBrushWithOutline(&graphics, fillrc, fillBrush, 1);

			graphics.SetClip(strokerc);
			DrawBrushWithOutline(&graphics, strokerc, strokeBrush, 0);
		}
		else
		{
			graphics.ExcludeClip(fillrc);
			DrawBrushWithOutline(&graphics, strokerc, strokeBrush, 0);

			graphics.SetClip(fillrc);
			DrawBrushWithOutline(&graphics, fillrc, fillBrush, 1);
		}
	}

	{
		FillSolidRect(dc.m_hDC, &m_rcNone, RGB(255, 255, 255));

		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(dc.m_hDC, hPen);

		MoveToEx(dc.m_hDC, m_rcNone.left+1, m_rcNone.bottom-1, NULL);
		LineTo(dc.m_hDC, m_rcNone.right-1, m_rcNone.top+1);

		SelectObject(dc.m_hDC, hOldPen);
		DeleteObject(hPen);

		HBRUSH hOldBrush = (HBRUSH)SelectObject(dc.m_hDC, GetStockObject(NULL_BRUSH));
		Rectangle(dc.m_hDC, m_rcNone.left, m_rcNone.top, m_rcNone.right, m_rcNone.bottom);
		SelectObject(dc.m_hDC, hOldBrush);
	}

	return 0;
}

LRESULT CColorDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_rcNone.PtInRect(point))
	{
		m_brush->setNone();

		SetColorFromTargets();
	}
	else if (m_rcStrokeFill.PtInRect(point))
	{
		CRect strokerc(2+10, 2+10, 2+10+20, 2+10+20);
		CRect fillrc(2, 2, 2+20, 2+20);

		if (m_strokeOrFill == 0)
		{
			if (strokerc.PtInRect(point))
			{
				gIApp->put_strokeOrFill(0);
			}
			else if (fillrc.PtInRect(point))
			{
				gIApp->put_strokeOrFill(1);
			}
		}
		else
		{
			if (fillrc.PtInRect(point))
			{
				gIApp->put_strokeOrFill(1);
			}
			else if (strokerc.PtInRect(point))
			{
				gIApp->put_strokeOrFill(0);
			}
		}
	}

	return 0;
}

void __stdcall CColorDlg::OnSetColorRGB(long r, long g, long b)
{
	m_channelValue[0] = r;
	m_channelValue[1] = g;
	m_channelValue[2] = b;

	SetColorOnTargets();
}

void __stdcall CColorDlg::OnSetChannel0(long pos)
{
	m_reentrance++;

	if (m_colorModel < 0)
	{
		m_tint = pos/255.0;
	}
	else
	{
		m_channelValue[0] = pos;
	}

	SetColorOnTargets();

	m_reentrance--;
}

void __stdcall CColorDlg::OnSetChannel1(long pos)
{
	m_reentrance++;

	m_channelValue[1] = pos;
	SetColorOnTargets();

	m_reentrance--;
}

void __stdcall CColorDlg::OnSetChannel2(long pos)
{
	m_reentrance++;

	m_channelValue[2] = pos;
	SetColorOnTargets();

	m_reentrance--;
}

LRESULT CColorDlg::OnChannelValueChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	long value = GetDlgItemInt(wID);

	if (m_colorModel < 0)
	{
		if (value < 0) value = 0;
		else if (value > 100) value = 100;

		m_tint = value/100.0;
	}
	else
	{
		if (value < 0) value = 0;
		else if (value > 255) value = 255;

		m_channelValue[wID-IDC_SWATCH_CHANNELVALUE0] = value;
	}

	SetColorOnTargets();

	return 0;
}

void CColorDlg::SetChannels(int nchannels)
{
}

void CColorDlg::SetColorModel(long colorModel)
{
	m_colorModel = colorModel;

	int nchannels = 0;
	int i;

	if (colorModel < 0)	// Tint
	{
		nchannels = 1;
		SetDlgItemText(IDC_SWATCH_CHANNELNAME0, "T");
	}
	else if (abs(colorModel) == 1)	// Grayscale
	{
		nchannels = 1;
		SetDlgItemText(IDC_SWATCH_CHANNELNAME0, "G");
	}
	else if (abs(colorModel) == 2)	// RGB
	{
		nchannels = 3;
		SetDlgItemText(IDC_SWATCH_CHANNELNAME0, "R");
		SetDlgItemText(IDC_SWATCH_CHANNELNAME1, "G");
		SetDlgItemText(IDC_SWATCH_CHANNELNAME2, "B");
	}
	else if (abs(colorModel) == 3)	// HSB
	{
		nchannels = 3;
		SetDlgItemText(IDC_SWATCH_CHANNELNAME0, "H");
		SetDlgItemText(IDC_SWATCH_CHANNELNAME1, "S");
		SetDlgItemText(IDC_SWATCH_CHANNELNAME2, "B");
	}
	else if (abs(colorModel) == 4)	// CMYK
	{
		nchannels = 4;
		SetDlgItemText(IDC_SWATCH_CHANNELNAME0, "C");
		SetDlgItemText(IDC_SWATCH_CHANNELNAME1, "M");
		SetDlgItemText(IDC_SWATCH_CHANNELNAME2, "Y");
		SetDlgItemText(IDC_SWATCH_CHANNELNAME3, "K");
	}

	for (i = 0; i < 4; i++)
	{
		::ShowWindow(GetDlgItem(IDC_SWATCH_CHANNELNAME0+i), i < nchannels);
		::ShowWindow(GetDlgItem(IDC_SWATCH_CHANNELSLIDER0+i), i < nchannels);
		::ShowWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE0+i), i < nchannels);
	}

	for (i = 0; i < 4; i++)
	{
		m_slider[i]->put_colorMode(abs(colorModel));
	}
}

void CColorDlg::SetColorFromTargets()
{
	BOOL bEnable = FALSE;

	if (m_brush)
	{
		PDBrushType brushType;
		m_brush->get_brushType(&brushType);

		if (brushType == BRUSH_COLOR)
		{
			CComPtr<IPDColor> color;
			m_brush->get_color(&color);

			color->getChannel(0, &m_channelValue[0]);
			color->getChannel(1, &m_channelValue[1]);
			color->getChannel(2, &m_channelValue[2]);
			color->getChannel(3, &m_channelValue[3]);
			DWORD colorvalue = RGB(m_channelValue[0], m_channelValue[1], m_channelValue[2]);

			BOOL bEnable;
			if (m_channelValue[0] == tomUndefined) bEnable = 2;
			else if (m_channelValue[1] == tomUndefined) bEnable = 2;
			else if (m_channelValue[2] == tomUndefined) bEnable = 2;
			else if (m_channelValue[3] == tomUndefined) bEnable = 2;
			else
				bEnable = 1;

			SetColorModel(2);	// rgb

			if (bEnable == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					m_slider[i]->put_rgb(colorvalue);
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					m_slider[i]->put_pos(m_channelValue[i]);
				}
			}

			for (int i = 0; i < 4; i++)
			{
				m_slider[i]->put_Enabled(bEnable);

				if (m_channelValue[i] != tomUndefined)
					SetDlgItemInt(IDC_SWATCH_CHANNELVALUE0+i, m_channelValue[i]);
				else
					SetDlgItemText(IDC_SWATCH_CHANNELVALUE0+i, "");
			}
		}
		else
		{
			BOOL bEnable = FALSE;

			m_slider[0]->put_Enabled(bEnable);
			m_slider[1]->put_Enabled(bEnable);
			m_slider[2]->put_Enabled(bEnable);
			m_slider[3]->put_Enabled(bEnable);
		}
	}
	else
	{
		BOOL bEnable = FALSE;

		m_slider[0]->put_Enabled(bEnable);
		m_slider[1]->put_Enabled(bEnable);
		m_slider[2]->put_Enabled(bEnable);
		m_slider[3]->put_Enabled(bEnable);
	}

	InvalidateRect(&m_rcStrokeFill);

/*
	CComQIPtr<IPDObjectWithBrush> withBrush = m_targetObjects[0];
	if (withBrush)
	{

		CComPtr<IPDBrush> brush;
		withBrush->get_brush(&brush);

			PDBrushType brushType;
			brush->get_brushType(&brushType);
			if (brushType == BRUSH_COLOR)
			{
				CComPtr<IPDColor> color;
				brush->get_color(&color);

				PDColorMode pdcolorMode;
				color->get_colorMode(&pdcolorMode);

				color->getChannel(0, &m_channelValue[0]);
				color->getChannel(1, &m_channelValue[1]);
				color->getChannel(2, &m_channelValue[2]);
				color->getChannel(3, &m_channelValue[3]);
				DWORD colorvalue = RGB(m_channelValue[0], m_channelValue[1], m_channelValue[2]);

				int colorModel;
				if (pdcolorMode == COLORMODE_RGB)
				{
					colorModel = 2;
				}
				else if (pdcolorMode == COLORMODE_CMYK)
				{
					colorModel = 3;
				}

				CComPtr<IPDSwatch> swatch;
				brush->get_swatch(&swatch);
				if (swatch)
				{
					SetColorModel(-colorModel);	// tint

					brush->get_colorTint(&m_tint);

					m_slider[0]->put_fromValue(RGB(255, 255, 255));
					m_slider[0]->put_toValue(colorvalue);

					m_slider[0]->put_pos(m_tint*255);

					SetDlgItemInt(IDC_SWATCH_CHANNELVALUE0, m_tint*100);
				}
				else
				{
					SetColorModel(colorModel);

					for (int i = 0; i < 4; i++)
					{
						m_slider[i]->put_rgb(colorvalue);
						SetDlgItemInt(IDC_SWATCH_CHANNELVALUE0+i, m_channelValue[i]);
					}
				}

				bEnable = TRUE;
			}
		}
	}

	m_slider[0]->put_Enabled(bEnable);
	m_slider[1]->put_Enabled(bEnable);
	m_slider[2]->put_Enabled(bEnable);
	m_slider[3]->put_Enabled(bEnable);
	*/
}

void CColorDlg::SetColorOnTargets()
{
	CComPtr<IPDColor> color;
	//brush->get_color(&color);
	m_brush->setColor(&color);
	color->setRGB(m_channelValue[0], m_channelValue[1], m_channelValue[2]);

	/*
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComQIPtr<IPDObjectWithBrush> withBrush = m_targetObjects[i];
		if (withBrush)
		{
			CComPtr<IPDBrush> brush;
			withBrush->get_brush(&brush);

			if (m_colorModel < 0)
			{
				brush->put_colorTint(m_tint);
			}
			else
			{
				CComPtr<IPDColor> color;
				//brush->get_color(&color);
				brush->setColor(&color);
				color->setRGB(m_channelValue[0], m_channelValue[1], m_channelValue[2]);
			}
		}
	}
	*/
}

STDMETHODIMP CColorDlg::OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
{
	if (targetObject == gIApp)
	{
		gIApp->get_strokeOrFill(&m_strokeOrFill);
		InvalidateRect(&m_rcStrokeFill);

		GetBrush();
	}

	//if (m_reentrance == 0)
	{
		m_reentrance++;

		SetColorFromTargets();

		m_reentrance--;
	}

	return S_OK;
}

void CColorDlg::GetBrush()
{
	if (m_brush)
	{
		{
			CComQIPtr<INotifySend> cp = m_brush;
			cp->Unadvise(this);
		}
		m_brush.Release();
	}

	if (m_object)
	{
		if (m_strokeOrFill == 0)
		{
			CComPtr<IPDObjectStroke> stroke;
			m_object->get_activeStroke(&stroke);

			stroke->get_brush(&m_brush);
		}
		else
		{
			CComPtr<IPDObjectFill> fill;
			m_object->get_activeFill(&fill);

			fill->get_brush(&m_brush);
		}

		if (m_brush)
		{
			CComQIPtr<INotifySend> cp = m_brush;
			DWORD cookie;
			cp->Advise(this, &cookie);
		}
	}
}

STDMETHODIMP CColorDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> sel = object;
	if (sel)
	{
		m_object = sel;
		GetBrush();
	}

	/*
	CComQIPtr<IPDBrush> brush = object;
	if (brush)
	{
		m_brush = brush;

		{
			CComQIPtr<INotifySend> cp = brush;
			DWORD cookie;
			cp->Advise(this, &cookie);
		}

		*cookie = 1;
	}
	*/
	/*
	CComQIPtr<IPDGradientStop> stop;
	CComQIPtr<IPDObjectWithBrush> withBrush;

	if (stop = object)
	{
		m_stop = stop;
		*cookie = 1;

		CComPtr<IPDColor> color;
		m_stop->get_color(&color);
		double red; color->getChannel(0, &red);
		double green; color->getChannel(0, &green);
		double blue; color->getChannel(0, &blue);

		COLORREF clr = RGB(red, green, blue);

		m_slider[0]->put_rgb(clr);
		m_slider[1]->put_rgb(clr);
		m_slider[2]->put_rgb(clr);
	}
	else if (withBrush = object)
	{
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_targetObjects[i], object))
			{
				return S_OK;
			}
		}

		{
			CComQIPtr<INotifySend> cp = withBrush;
			DWORD cookie;
			cp->Advise(this, &cookie);
		}

		m_targetObjects.Add(withBrush.Detach());

		*cookie = m_targetObjects.GetSize();
	}
	*/

	SetColorFromTargets();

	return S_OK;
}

STDMETHODIMP CColorDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	/*
	ATLASSERT(m_brush);
	{
		CComQIPtr<INotifySend> cp = m_brush;
		cp->Unadvise(this);
	}
	m_brush.Release();
	*/
	m_object.Release();
	GetBrush();

	SetColorFromTargets();

	/*
	if (m_stop)
	{
		m_stop.Release();
	}
	else
	{
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_targetObjects[i], object))
			{
				CComQIPtr<INotifySend> cp = m_targetObjects[i];
				cp->Unadvise(this);

				m_targetObjects[i]->Release();
				m_targetObjects.RemoveAt(i);
				break;
			}
		}
	}
  */

	SetColorFromTargets();

	return S_OK;
}

BEGIN_CMD_MAP(CColorDlg)
	CMD_HANDLER(ID_COLOR_GRAYSCALE, OnColorGrayscale)
	CMD_UPDATE(ID_COLOR_GRAYSCALE, OnColorGrayscaleUpdate)
	CMD_HANDLER(ID_COLOR_RGB, OnColorRGB)
	CMD_UPDATE(ID_COLOR_RGB, OnColorRGBUpdate)
	CMD_HANDLER(ID_COLOR_HSB, OnColorHSB)
	CMD_UPDATE(ID_COLOR_HSB, OnColorHSBUpdate)
	CMD_HANDLER(ID_COLOR_ADDTOSWATCHES, OnColorAddtoSwatches)
END_CMD_MAP()

LRESULT CColorDlg::OnColorGrayscale(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetColorModel(1);
	return 0;
}

void CColorDlg::OnColorGrayscaleUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_colorModel == 1);
}

LRESULT CColorDlg::OnColorRGB(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_colorModel != 2)
	{
		if (m_colorModel == -2)
		{
			m_channelValue[0] = 255-((255-m_channelValue[0])*m_tint);
			m_channelValue[1] = 255-((255-m_channelValue[1])*m_tint);
			m_channelValue[2] = 255-((255-m_channelValue[2])*m_tint);
			m_channelValue[3] = 255-((255-m_channelValue[3])*m_tint);
		}

		SetColorModel(2);

		SetColorOnTargets();
	}

	return 0;
}

void CColorDlg::OnColorRGBUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_colorModel == 2);
}

LRESULT CColorDlg::OnColorHSB(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetColorModel(3);
	return 0;
}

void CColorDlg::OnColorHSBUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_colorModel == 3);
}

LRESULT CColorDlg::OnColorAddtoSwatches(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	if (m_targetObjects.GetSize() == 1)
	{
		CComQIPtr<IPDObjectWithBrush> object = m_targetObjects[0];
		if (object)
		{
			CComPtr<IPDDocument> document;
			object->get_document(&document);

			CComPtr<IPDSwatches> swatches;
			document->get_swatches(&swatches);

			CComPtr<IPDSwatch> newSwatch;

			if (m_colorModel < 0)	// tint
			{
				CComPtr<IPDBrush> brush;
				object->get_brush(&brush);

				CComPtr<IPDSwatch> swatch;
				brush->get_swatch(&swatch);

				CComQIPtr<IPDSwatchColor> swatchColor = swatch;	// TODO could be tint

				CComPtr<IPDSwatchTint> swatchTint;
				swatches->createSwatchTint(swatchColor, &swatchTint);
				if (swatchTint)
				{
					swatchTint->put_tint(m_tint);

					newSwatch = swatchTint;
				}
			}
			else
			{
				CComPtr<IPDSwatchColor> swatchColor;
				swatches->createSwatchColor(&swatchColor);
				if (swatchColor)
				{
					CComPtr<IPDColor> color;
					swatchColor->get_color(&color);

					PDColorMode pdcolorMode;
					if (m_colorModel == 2)
						pdcolorMode = COLORMODE_RGB;
					else if (m_colorModel == 3)
						pdcolorMode = COLORMODE_CMYK;
					else
						ATLASSERT(0);

					color->put_colorMode(pdcolorMode);
					color->putChannel(0, m_channelValue[0]);
					color->putChannel(1, m_channelValue[1]);
					color->putChannel(2, m_channelValue[2]);
					color->putChannel(3, m_channelValue[3]);

					newSwatch = swatchColor;
				}
			}

			if (newSwatch)
			{
				swatches->appendSwatch(newSwatch);
/*
				for (int i = 0; i < m_targetObjects.GetSize(); i++)
				{
					CComQIPtr<IPDObjectWithBrush> withBrush = m_targetObjects[i];
					if (withBrush)
					{
						CComPtr<IPDBrush> brush;
						withBrush->get_brush(&brush);

						brush->put_swatch(newSwatch);
					}
				}
				*/
			}
		}
	}
#endif

	return 0;
}
