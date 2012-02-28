// GradientSwatchOptionsDlg.h : Declaration of the CGradientSwatchOptionsDlg

#ifndef __GRADIENTSWATCHOPTIONSDLG_H_
#define __GRADIENTSWATCHOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

#include "SwatchOptionsBaseDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CGradientSwatchOptionsDlg
class CGradientSwatchOptionsDlg : 
	public CSwatchOptionsBaseDlg<CGradientSwatchOptionsDlg>,
	public IDispEventImpl<5, CGradientSwatchOptionsDlg, &DIID__IGradientEditEvents, &LIBID_PAGEDESIGNERLib, 1, 0>,
	public IDispEventImpl<6, CGradientSwatchOptionsDlg, &DIID__ISwatchesListEvents, &LIBID_PAGEDESIGNERLib, 1, 0>
{
public:
	CGradientSwatchOptionsDlg()
	{
	}

	~CGradientSwatchOptionsDlg()
	{
	}

	enum { IDD = IDD_GRADIENTSWATCHOPTIONSDLG };

	CComPtr<IPDSwatches> m_swatches;

	CComPtr<ISwatchesList> m_namedColors;
	CComPtr<IGradientEdit> m_gradientEdit;

	CComPtr<IPDGradient> m_gradient;
	CComPtr<IPDGradientStop> m_stop;

	PDGradientType m_gradientType;

	CArray<IPDSwatchGradient*,IPDSwatchGradient*> m_targetObjects;

	void SetStopColorMode(int index)
	{
		::ShowWindow(GetDlgItem(IDC_SWATCH_NAMEDCOLORS), (index == 2)? SW_SHOW: SW_HIDE);

		if (index >= 0 && index < 2)
		{
			if (index == 0)
				SetColorMode(COLORMODE_RGB);
			else if (index == 1)
				SetColorMode(COLORMODE_CMYK);
		}
		else// if (index == 2)
		{
			SetColorMode((PDColorMode)0);
		}
	}

	void SetChannelsFromColor(IPDColor* color)
	{
		double v;

		color->getChannel(0, &v);
		m_channelValue[0] = v;

		color->getChannel(1, &v);
		m_channelValue[1] = v;

		color->getChannel(2, &v);
		m_channelValue[2] = v;

		color->getChannel(3, &v);
		m_channelValue[3] = v;
	}

BEGIN_SINK_MAP(CGradientSwatchOptionsDlg)
	SINK_ENTRY_EX(1, DIID__IUIColorSliderEvents, /*dispid*/1, OnSetChannel0)
	SINK_ENTRY_EX(2, DIID__IUIColorSliderEvents, /*dispid*/1, OnSetChannel1)
	SINK_ENTRY_EX(3, DIID__IUIColorSliderEvents, /*dispid*/1, OnSetChannel2)
	SINK_ENTRY_EX(4, DIID__IUIColorSliderEvents, /*dispid*/1, OnSetChannel3)
   SINK_ENTRY_EX(5, DIID__IGradientEditEvents, /*dispid*/2, OnClickStop)
   SINK_ENTRY_EX(6, DIID__ISwatchesListEvents, /*dispid*/1, OnClickSwatch)
END_SINK_MAP()

	void __stdcall OnSetChannel0(long pos)
	{
		m_channelValue[0] = pos;
		SetChannelValues();

		CComPtr<IPDColor> color;
		m_stop->get_color(&color);
		color->putChannel(0, m_channelValue[0]);
	}

	void __stdcall OnSetChannel1(long pos)
	{
		m_channelValue[1] = pos;
		SetChannelValues();

		CComPtr<IPDColor> color;
		m_stop->get_color(&color);
		color->putChannel(1, m_channelValue[1]);
	}

	void __stdcall OnSetChannel2(long pos)
	{
		m_channelValue[2] = pos;
		SetChannelValues();

		CComPtr<IPDColor> color;
		m_stop->get_color(&color);
		color->putChannel(2, m_channelValue[2]);
	}

	void __stdcall OnSetChannel3(long pos)
	{
		m_channelValue[3] = pos;
		SetChannelValues();

		CComPtr<IPDColor> color;
		m_stop->get_color(&color);
		color->putChannel(3, m_channelValue[3]);
	}

	void __stdcall OnClickStop(IPDGradientStop* stop)
	{
		m_stop = stop;

		long index;

		CComPtr<IPDSwatch> stopSwatch;
		stop->get_swatch(&stopSwatch);
		if (stopSwatch)
		{
			m_namedColors->selectSwatch(stopSwatch);
			index = 2;
		}
		else
		{
			CComPtr<IPDColor> stopColor;
			stop->get_color(&stopColor);

			PDColorMode colorMode;
			stopColor->get_colorMode(&colorMode);

			SetChannelsFromColor(stopColor);
			SetChannelValues();

			index = (int)colorMode-1;
		}

		SetStopColorMode(index);
		::SendMessage(GetDlgItem(IDC_SWATCH_COLORMODE), CB_SETCURSEL, index, 0);
	}

	void __stdcall OnClickSwatch(IPDSwatch* swatch)
	{
		if (m_stop)
		{
			/*
			CComQIPtr<IPDSwatchColor> swatchColor = swatch;
			if (swatchColor)
			{
				CComPtr<IPDColor> color;
				swatchColor->get_color(&color);
			}
			*/

			m_stop->put_swatch(swatch);
		}
	}

BEGIN_MSG_MAP(CGradientSwatchOptionsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_SWATCH_COLORMODE, CBN_SELENDOK, OnColorMode)
	COMMAND_HANDLER(IDC_SWATCH_GRADIENTTYPE, CBN_SELENDOK, OnGradientType)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnGradientType(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		long index = ::SendMessage(GetDlgItem(IDC_SWATCH_GRADIENTTYPE), CB_GETCURSEL, 0, 0);
		m_gradientType = (PDGradientType)(index+1);

		return 0;
	}

	LRESULT OnColorMode(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		long index = ::SendMessage(GetDlgItem(IDC_SWATCH_COLORMODE), CB_GETCURSEL, 0, 0);

		if (m_stop)
		{
			if (index != 2)
			{
				CComPtr<IPDSwatch> swatch;
				m_stop->get_swatch(&swatch);
				if (swatch)
				{
			// From swatch to color
					CComQIPtr<IPDSwatchColor> swatchColor = swatch;

					CComPtr<IPDColor> color;
					swatchColor->get_color(&color);

					double v;

					color->getChannel(0, &v);
					m_channelValue[0] = v;

					color->getChannel(1, &v);
					m_channelValue[1] = v;

					color->getChannel(2, &v);
					m_channelValue[2] = v;

					color->getChannel(3, &v);
					m_channelValue[3] = v;

					m_stop->setColorRGB(m_channelValue[0], m_channelValue[1], m_channelValue[2]);
				}
			}
		}

		SetStopColorMode(index);

		return 0;
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CSwatchOptionsBaseDlg<CGradientSwatchOptionsDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);

		GetDlgControl(IDC_SWATCH_GRADIENT, IID_IGradientEdit, (void**)&m_gradientEdit);
		IDispEventImpl<5, CGradientSwatchOptionsDlg, &DIID__IGradientEditEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventAdvise(m_gradientEdit);

		GetDlgControl(IDC_SWATCH_NAMEDCOLORS, IID_ISwatchesList, (void**)&m_namedColors);
		IDispEventImpl<6, CGradientSwatchOptionsDlg, &DIID__ISwatchesListEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventAdvise(m_namedColors);

		::SendMessage(GetDlgItem(IDC_SWATCH_GRADIENTTYPE), CB_ADDSTRING, 0, (LPARAM)"Linear");
		::SendMessage(GetDlgItem(IDC_SWATCH_GRADIENTTYPE), CB_ADDSTRING, 0, (LPARAM)"Radial");

		::SendMessage(GetDlgItem(IDC_SWATCH_COLORMODE), CB_ADDSTRING, 0, (LPARAM)"RGB");
		::SendMessage(GetDlgItem(IDC_SWATCH_COLORMODE), CB_ADDSTRING, 0, (LPARAM)"CMYK");
		::SendMessage(GetDlgItem(IDC_SWATCH_COLORMODE), CB_ADDSTRING, 0, (LPARAM)"Named Color");

		CRect rect;
		::GetWindowRect(GetDlgItem(IDC_SWATCH_COLORSLIDERS), &rect);
		ScreenToClient(&rect);

		::MoveWindow(GetDlgItem(IDC_SWATCH_NAMEDCOLORS), rect.left, rect.top, rect.Width(), rect.Height(), TRUE);

		m_namedColors->put_swatches(m_swatches);

		int i;

	// Gradient Type
		PDGradientType gradientType = (PDGradientType)0;

		for (i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CComPtr<IPDGradient> gradient;
			m_targetObjects[i]->get_gradient(&gradient);

			PDGradientType gradientType2;
			gradient->get_type(&gradientType2);

			if (i == 0)
			{
				gradientType = gradientType2;
			}
			else if (gradientType != gradientType2)
			{
				gradientType = (PDGradientType)0;
				break;
			}
		}

		m_gradientType = gradientType;
		::SendMessage(GetDlgItem(IDC_SWATCH_GRADIENTTYPE), CB_SETCURSEL, (int)m_gradientType-1, 0);

		// Gradient stops
		if (m_targetObjects.GetSize() == 1)
		{
			CComPtr<IPDGradient> gradient;
			m_targetObjects[0]->get_gradient(&gradient);

			gradient->clone(&m_gradient);

			m_gradientEdit->put_gradient(m_gradient);
		}

		SetStopColorMode(-1);	// No stop selected

		return 1;  // Let the system set the focus
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		IDispEventImpl<5, CGradientSwatchOptionsDlg, &DIID__IGradientEditEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventUnadvise(m_gradientEdit);
		IDispEventImpl<6, CGradientSwatchOptionsDlg, &DIID__ISwatchesListEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventUnadvise(m_namedColors);

		return CSwatchOptionsBaseDlg<CGradientSwatchOptionsDlg>::OnDestroy(uMsg, wParam, lParam, bHandled);
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CSwatchOptionsBaseDlg<CGradientSwatchOptionsDlg>::OnOK(wNotifyCode, wID, hWndCtl, bHandled);

	// Gradient stops
		if (m_targetObjects.GetSize() == 1)
		{
			CComPtr<IPDSwatchGradient> swatch = m_targetObjects[0];

			CComPtr<IPDGradient> gradient;
			swatch->get_gradient(&gradient);

			m_gradient->copy(gradient);
		}

	// Gradient Type
		if ((int)m_gradientType != 0)
		{
			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				CComPtr<IPDSwatchGradient> swatch = m_targetObjects[i];

				CComPtr<IPDGradient> gradient;
				swatch->get_gradient(&gradient);

				gradient->put_type(m_gradientType);
			}
		}

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__GRADIENTSWATCHOPTIONSDLG_H_
