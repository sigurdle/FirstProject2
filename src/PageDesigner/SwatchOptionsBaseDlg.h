#pragma once

template <class T> class ATL_NO_VTABLE CSwatchOptionsBaseDlg :
	public CAxDialogImpl<T>,
	public IDispEventImpl<1, T, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, T, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, T, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<4, T, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>
{
public:
	CSwatchOptionsBaseDlg()
	{
		m_channelValue[0] = 0;
		m_channelValue[2] = 0;
		m_channelValue[3] = 0;
		m_channelValue[4] = 0;
	}

	CComPtr<IUIColorSlider> m_channelSlider[4];

	int m_channelValue[4];
	PDColorMode m_colorMode;

	void SetChannelValues()
	{
		DWORD rgb = RGB(m_channelValue[0], m_channelValue[1], m_channelValue[2]);

		m_channelSlider[0]->put_rgb(rgb);
		m_channelSlider[1]->put_rgb(rgb);
		m_channelSlider[2]->put_rgb(rgb);

		SetDlgItemInt(IDC_SWATCH_CHANNELVALUE0, m_channelValue[0]);
		SetDlgItemInt(IDC_SWATCH_CHANNELVALUE1, m_channelValue[1]);
		SetDlgItemInt(IDC_SWATCH_CHANNELVALUE2, m_channelValue[2]);
	}

	void SetColorMode(PDColorMode colorMode)
	{
		m_colorMode = colorMode;

		CRect rect;
		::GetWindowRect(GetDlgItem(IDC_SWATCH_COLORSLIDERS), &rect);
		ScreenToClient(&rect);

		int nchannels;

		if (colorMode == COLORMODE_CMYK)			nchannels = 4;
		else if (colorMode == COLORMODE_RGB)	nchannels = 3;
		else if (colorMode == COLORMODE_LAB)	nchannels = 3;
		else nchannels = 0;

		for (int i = 0; i < 4; i++)
		{
			::ShowWindow(GetDlgItem(IDC_SWATCH_CHANNELNAME0+i), (nchannels >= i+1)? SW_SHOW: SW_HIDE);
			::ShowWindow(GetDlgItem(IDC_SWATCH_CHANNELSLIDER0+i), (nchannels >= i+1)? SW_SHOW: SW_HIDE);
			::ShowWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE0+i), (nchannels >= i+1)? SW_SHOW: SW_HIDE);
		}

		if (colorMode == COLORMODE_CMYK)
		{
			SetDlgItemText(IDC_SWATCH_CHANNELNAME0, "&Cyan");
			SetDlgItemText(IDC_SWATCH_CHANNELNAME1, "Ma&genta");
			SetDlgItemText(IDC_SWATCH_CHANNELNAME2, "&Yellow");
			SetDlgItemText(IDC_SWATCH_CHANNELNAME3, "&Black");
		}
		else if (colorMode == COLORMODE_RGB)
		{
			SetDlgItemText(IDC_SWATCH_CHANNELNAME0, "&Red");
			SetDlgItemText(IDC_SWATCH_CHANNELNAME1, "&Green");
			SetDlgItemText(IDC_SWATCH_CHANNELNAME2, "&Blue");

			m_channelSlider[0]->put_channel(0);
			m_channelSlider[1]->put_channel(1);
			m_channelSlider[2]->put_channel(2);
		}
		else if (colorMode == COLORMODE_LAB)
		{
			SetDlgItemText(IDC_SWATCH_CHANNELNAME0, "&L");
			SetDlgItemText(IDC_SWATCH_CHANNELNAME1, "&A");
			SetDlgItemText(IDC_SWATCH_CHANNELNAME2, "&B");
		}

		for (i = 0; i < nchannels; i++)
		{
			m_channelSlider[i]->put_rgb(RGB(m_channelValue[0], m_channelValue[1], m_channelValue[2]));
		}

		for (i = 0; i < nchannels; i++)
		{
			int y = rect.top + (rect.Height()-nchannels*24)/2 + 24*i+12;

			CRect oldrect;

		// Name
			::GetWindowRect(GetDlgItem(IDC_SWATCH_CHANNELNAME0+i), &oldrect);
			ScreenToClient(&oldrect);
			::SetWindowPos(GetDlgItem(IDC_SWATCH_CHANNELNAME0+i), NULL, oldrect.left, y-oldrect.Height()/2, 0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);

		// Slider
			::GetWindowRect(GetDlgItem(IDC_SWATCH_CHANNELSLIDER0+i), &oldrect);
			ScreenToClient(&oldrect);
			::SetWindowPos(GetDlgItem(IDC_SWATCH_CHANNELSLIDER0+i), NULL, oldrect.left, y-oldrect.Height()/2, 0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);

		// Value
			::GetWindowRect(GetDlgItem(IDC_SWATCH_CHANNELVALUE0+i), &oldrect);
			ScreenToClient(&oldrect);
			::SetWindowPos(GetDlgItem(IDC_SWATCH_CHANNELVALUE0+i), NULL, oldrect.left, y-oldrect.Height()/2, 0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
		}

		InvalidateRect(&rect);	// hmm..
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		GetDlgControl(IDC_SWATCH_CHANNELSLIDER0, IID_IUIColorSlider, (void**)&m_channelSlider[0]);
		GetDlgControl(IDC_SWATCH_CHANNELSLIDER1, IID_IUIColorSlider, (void**)&m_channelSlider[1]);
		GetDlgControl(IDC_SWATCH_CHANNELSLIDER2, IID_IUIColorSlider, (void**)&m_channelSlider[2]);
		GetDlgControl(IDC_SWATCH_CHANNELSLIDER3, IID_IUIColorSlider, (void**)&m_channelSlider[3]);

		IDispEventImpl<1, T, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_channelSlider[0]);
		IDispEventImpl<2, T, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_channelSlider[1]);
		IDispEventImpl<3, T, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_channelSlider[2]);
		IDispEventImpl<4, T, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_channelSlider[3]);

	// Swatch name
		if (static_cast<T*>(this)->m_targetObjects.GetSize() == 1)
		{
			BSTR bname;
			static_cast<T*>(this)->m_targetObjects[0]->get_name(&bname);
			SetDlgItemText(IDC_SWATCH_NAME, _bstr_t(bname, false));
		}
		else
		{
			::EnableWindow(GetDlgItem(IDC_SWATCH_NAME), FALSE);
		}

		return 1;
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		IDispEventImpl<1, T, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_channelSlider[0]);
		IDispEventImpl<2, T, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_channelSlider[1]);
		IDispEventImpl<3, T, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_channelSlider[2]);
		IDispEventImpl<4, T, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_channelSlider[3]);

		return 0;
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
	// Swatch Name
		if (static_cast<T*>(this)->m_targetObjects.GetSize() == 1)
		{
			CComQIPtr<IPDSwatch> swatch = static_cast<T*>(this)->m_targetObjects[0];

			TCHAR buf[256];
			GetDlgItemText(IDC_SWATCH_NAME, buf, sizeof(buf));
			swatch->put_name(_bstr_t(buf));
		}

		return 0;
	}
};
