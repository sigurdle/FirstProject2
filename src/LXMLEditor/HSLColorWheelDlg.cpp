#include "stdafx.h"
#include "LXMLEditor2.h"

#include "HSLColorWheelDlg.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CHSLColorWheelDlg

int CHSLColorWheelDlg::FinalConstruct()
{
	return S_OK;
}

void CHSLColorWheelDlg::FinalRelease()
{
}

LRESULT CHSLColorWheelDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	GetDlgControl(IDC_COLORWHEEL, IID_IUIHSLColorWheel, (void**)&m_colorWheel);
//	IDispEventImpl<1, CHSLColorWheelDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_slider[0]);

	int i;

	/*
	for (i = 0; i < 3; i++)
	{
		m_slider[i]->put_channel(i);
		m_slider[i]->put_colorMode(2);
	}
	*/

	m_colorWheel->put_Enabled(FALSE);

	/*
	for (i = 0; i < 3; i++)
	{
		::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE0+i), FALSE);
		SetDlgItemText(IDC_SWATCH_CHANNELVALUE0+i, _T(""));
	}
	*/

	return 0;
}

LRESULT CHSLColorWheelDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	IDispEventImpl<1, CHSLColorWheelDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[0]);
	IDispEventImpl<2, CHSLColorWheelDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[1]);
	IDispEventImpl<3, CHSLColorWheelDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[2]);
//	IDispEventImpl<4, CHSLColorWheelDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_slider[3]);

	for (int i = 0; i < 4; i++)
	{
		m_slider[i].Release();
	}
#endif

	return 0;
}

#if 0

LRESULT CHSLColorWheelDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	return 0;
}

HRESULT __stdcall CHSLColorWheelDlg::OnSlider0SetPos(long pos)
{
	OnSliderPos(0, pos);
	return S_OK;
}

HRESULT __stdcall CHSLColorWheelDlg::OnSlider1SetPos(long pos)
{
	OnSliderPos(1, pos);
	return S_OK;
}

HRESULT __stdcall CHSLColorWheelDlg::OnSlider2SetPos(long pos)
{
	OnSliderPos(2, pos);
	return S_OK;
}

HRESULT __stdcall CHSLColorWheelDlg::OnSlider3SetPos(long pos)
{
	OnSliderPos(3, pos);
	return S_OK;
}

void CHSLColorWheelDlg::OnSliderPos(int channel, long nPos)
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

#if 0
	ATLASSERT(m_viewGroup);
	static_cast<CEXMLViewGroup*>(m_viewGroup.p)->setRGBValue(m_channelValue[0], m_channelValue[1], m_channelValue[2]);
#endif
	m_site->SetRGBColorValue(m_channelValue[0], m_channelValue[1], m_channelValue[2]);

//	m_color->setRGBValue(m_channelValue[0], m_channelValue[1], m_channelValue[2]);
}

#if 0
void CHSLColorWheelDlg::UpdateSliders()
{
}
#endif

#if 0
STDMETHODIMP CHSLColorWheelDlg::SetColor(IEColor *color)
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
#endif

STDMETHODIMP CHSLColorWheelDlg::SetRGBColorValue(/*[in]*/ long red, /*[in]*/ long green, /*[in]*/ long blue)
{
#if 0
	/*
	double red = static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionColorRed;
	double green = static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionColorGreen;
	double blue = static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionColorBlue;
	*/

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

	/*
	CRect rc = CRect(6, 6, 6+18+9, 6+18+9);
	InvalidateRect(&rc);
	*/
#endif
	return S_OK;
}

#if 0
#endif

BEGIN_CMD_MAP(CHSLColorWheelDlg)
//	CMD_HANDLER(ID_COLOR_INVERT, OnColorInvert)
//	CMD_HANDLER(ID_COLOR_COMPLEMENT, OnColorComplement)
//	CMD_UPDATE(ID_SVGOBJECTS_DELETESELECTION, OnDeleteSelectionUpdate)
END_CMD_MAP()

#endif