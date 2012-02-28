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

	for (i = 0; i < 3; i++)
	{
		m_slider[i]->put_channel(i);
	}

	IDispEventImpl<1, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_slider[0]);
	IDispEventImpl<2, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_slider[1]);
	IDispEventImpl<3, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_slider[2]);
//	IDispEventImpl<3, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_slider[2]);

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

	return 0;
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

STDMETHODIMP CColorDlg::OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
{
	//if (m_reentrance == 0)
	{
		m_reentrance++;

		SetColorFromTargets();

		m_reentrance--;
	}

	return S_OK;
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

//	SetChannels(nchannels);
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

	if (m_targetObjects.GetSize() == 1)
	{
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
}

void CColorDlg::SetColorOnTargets()
{
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
}

STDMETHODIMP CColorDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
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

	SetColorFromTargets();

	return S_OK;
}

STDMETHODIMP CColorDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
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

	return 0;
}
