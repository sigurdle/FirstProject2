// ColorSwatchOptionsDlg.h : Declaration of the CColorSwatchOptionsDlg

#ifndef __COLORSWATCHOPTIONSDLG_H_
#define __COLORSWATCHOPTIONSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

#include "SwatchOptionsBaseDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CColorSwatchOptionsDlg
class CColorSwatchOptionsDlg : 
	public CSwatchOptionsBaseDlg<CColorSwatchOptionsDlg>
{
public:
	CColorSwatchOptionsDlg()
	{
	}

	~CColorSwatchOptionsDlg()
	{
	}

	PDColorType m_colorType;
	CArray<IPDSwatchColor*,IPDSwatchColor*> m_targetObjects;

	enum { IDD = IDD_COLORSWATCHOPTIONSDLG };

	void SetColorName()
	{
		if (IsDlgButtonChecked(IDC_SWATCH_NAMEWITHCOLORVALUE))
		{
			::ShowWindow(GetDlgItem(IDC_SWATCH_NAME), SW_HIDE);
			::ShowWindow(GetDlgItem(IDC_SWATCH_NAMEWITHCOLORVALUENAME), SW_SHOW);
		}
		else
		{
			::ShowWindow(GetDlgItem(IDC_SWATCH_NAME), SW_SHOW);
			::ShowWindow(GetDlgItem(IDC_SWATCH_NAMEWITHCOLORVALUENAME), SW_HIDE);
		}
	}

BEGIN_SINK_MAP(CColorSwatchOptionsDlg)
	SINK_ENTRY_EX(1, DIID__IUIColorSliderEvents, /*dispid*/1, OnSetChannel0)
	SINK_ENTRY_EX(2, DIID__IUIColorSliderEvents, /*dispid*/1, OnSetChannel1)
	SINK_ENTRY_EX(3, DIID__IUIColorSliderEvents, /*dispid*/1, OnSetChannel2)
	SINK_ENTRY_EX(4, DIID__IUIColorSliderEvents, /*dispid*/1, OnSetChannel3)
END_SINK_MAP()

	void __stdcall OnSetChannel0(long pos)
	{
		m_channelValue[0] = pos;
		SetChannelValues();
	}

	void __stdcall OnSetChannel1(long pos)
	{
		m_channelValue[1] = pos;
		SetChannelValues();
	}

	void __stdcall OnSetChannel2(long pos)
	{
		m_channelValue[2] = pos;
		SetChannelValues();
	}

	void __stdcall OnSetChannel3(long pos)
	{
		m_channelValue[3] = pos;
		SetChannelValues();
	}

BEGIN_MSG_MAP(CColorSwatchOptionsDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_SWATCH_COLORTYPE, CBN_SELENDOK, OnColorType)
	COMMAND_HANDLER(IDC_SWATCH_COLORMODE, CBN_SELENDOK, OnColorMode)
	COMMAND_HANDLER(IDC_SWATCH_NAMEWITHCOLORVALUE, BN_CLICKED, OnNameWithColorValue)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnNameWithColorValue(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		SetColorName();
		return 0;
	}

	LRESULT OnColorType(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		long index = ::SendMessage(GetDlgItem(IDC_SWATCH_COLORTYPE), CB_GETCURSEL, 0, 0);
		if (index == 0)
			m_colorType = COLORTYPE_PROCESS;
		else
			m_colorType = COLORTYPE_SPOT;

		return 0;
	}

	LRESULT OnColorMode(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		long index = ::SendMessage(GetDlgItem(IDC_SWATCH_COLORMODE), CB_GETCURSEL, 0, 0);
		if (index == 0)
			SetColorMode(COLORMODE_RGB);
		else
			SetColorMode(COLORMODE_CMYK);

		return 0;
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return CSwatchOptionsBaseDlg<CColorSwatchOptionsDlg>::OnDestroy(uMsg, wParam, lParam, bHandled);
	}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CSwatchOptionsBaseDlg<CColorSwatchOptionsDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);

		::SendMessage(GetDlgItem(IDC_SWATCH_COLORTYPE), CB_ADDSTRING, 0, (LPARAM)"Process");
		::SendMessage(GetDlgItem(IDC_SWATCH_COLORTYPE), CB_ADDSTRING, 0, (LPARAM)"Spot");

		::SendMessage(GetDlgItem(IDC_SWATCH_COLORMODE), CB_ADDSTRING, 0, (LPARAM)"RGB");
		::SendMessage(GetDlgItem(IDC_SWATCH_COLORMODE), CB_ADDSTRING, 0, (LPARAM)"CMYK");

		int i;

	// Color Type
		PDColorType colorType = (PDColorType)0;

		for (i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CComPtr<IPDSwatchColor> swatch = m_targetObjects[i];

			PDColorType colorType2;
			swatch->get_colorType(&colorType2);

			if (i == 0)
			{
				colorType = colorType2;
			}
			else if (colorType != colorType2)
			{
				colorType = (PDColorType)0;
				break;
			}
		}

		::SendMessage(GetDlgItem(IDC_SWATCH_COLORTYPE), CB_SETCURSEL, (WPARAM)colorType-1, 0);
		m_colorType = colorType;

	// Color mode
		PDColorMode colorMode = (PDColorMode)0;

		for (i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CComPtr<IPDSwatchColor> swatch = m_targetObjects[i];

			CComPtr<IPDColor> color;
			swatch->get_color(&color);

			PDColorMode colorMode2;
			color->get_colorMode(&colorMode2);

			if (i == 0)
			{
				colorMode = colorMode2;
			}
			else if (colorMode != colorMode2)
			{
				colorMode = (PDColorMode)0;
				break;
			}
		}

		::SendMessage(GetDlgItem(IDC_SWATCH_COLORMODE), CB_SETCURSEL, (WPARAM)colorMode-1, 0);
		SetColorMode(colorMode);

	// Name with Color Value

		VARIANT_BOOL nameWithColorValue;
		for (i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CComPtr<IPDSwatchColor> swatch = m_targetObjects[i];

			VARIANT_BOOL nameWithColorValue2;
			swatch->get_nameWithColorValue(&nameWithColorValue2);

			if (i == 0)
			{
				nameWithColorValue = nameWithColorValue2;
			}
			else if (nameWithColorValue != nameWithColorValue2)
			{
				nameWithColorValue = 1;
				break;
			}
		}

		CheckDlgButton(IDC_SWATCH_NAMEWITHCOLORVALUE, nameWithColorValue == VARIANT_TRUE? BST_CHECKED: (nameWithColorValue == VARIANT_FALSE? BST_UNCHECKED: BST_INDETERMINATE));

	// Swatch name
		if (m_targetObjects.GetSize() == 1)
		{
//			BSTR bname;
//			m_targetObjects[0]->get_name(&bname);
			//SetDlgItemText(IDC_SWATCH_NAMEWITHCOLORVALUENAME, _bstr_t(bname, false));
		}
		else
		{
			::SetWindowLong(GetDlgItem(IDC_SWATCH_NAMEWITHCOLORVALUE), GWL_STYLE, ::GetWindowLong(GetDlgItem(IDC_SWATCH_NAMEWITHCOLORVALUE), GWL_STYLE) | BS_AUTO3STATE);
		}

	// Channel values
		if (m_targetObjects.GetSize() == 1)
		{
			CComPtr<IPDSwatchColor> swatch = m_targetObjects[0];

			CComPtr<IPDColor> color;
			swatch->get_color(&color);

			double v;

			color->getChannel(0, &v);
			m_channelValue[0] = v;

			color->getChannel(1, &v);
			m_channelValue[1] = v;

			color->getChannel(2, &v);
			m_channelValue[2] = v;

			color->getChannel(3, &v);
			m_channelValue[3] = v;

			SetChannelValues();
		}
		else
		{
			::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELSLIDER0), FALSE);
			::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELSLIDER2), FALSE);
			::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELSLIDER3), FALSE);
			::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELSLIDER3), FALSE);

			::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE0), FALSE);
			::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE2), FALSE);
			::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE3), FALSE);
			::EnableWindow(GetDlgItem(IDC_SWATCH_CHANNELVALUE3), FALSE);
		}

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CSwatchOptionsBaseDlg<CColorSwatchOptionsDlg>::OnOK(wNotifyCode, wID, hWndCtl, bHandled);

	// Color type
		if (m_colorType != (PDColorType)0)
		{
			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				CComPtr<IPDSwatchColor> swatch = m_targetObjects[i];

				swatch->put_colorType(m_colorType);
			}
		}

	// Color mode
		if (m_colorMode != (PDColorMode)0)
		{
			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				CComPtr<IPDSwatchColor> swatch = m_targetObjects[i];

				CComPtr<IPDColor> color;
				swatch->get_color(&color);

				color->put_colorMode(m_colorMode);
			}
		}

	// Color values
		if (m_targetObjects.GetSize() == 1)
		{
			CComPtr<IPDSwatchColor> swatch = m_targetObjects[0];

			CComPtr<IPDColor> color;
			swatch->get_color(&color);

			color->putChannel(0, m_channelValue[0]);
			color->putChannel(1, m_channelValue[1]);
			color->putChannel(2, m_channelValue[2]);
			color->putChannel(3, m_channelValue[3]);
		}

	// Name with Color Value
		int bNameWithColorValue = IsDlgButtonChecked(IDC_SWATCH_NAMEWITHCOLORVALUE);

		if (bNameWithColorValue == BST_CHECKED || bNameWithColorValue == BST_UNCHECKED)
		{
			for (int i = 0; i < m_targetObjects.GetSize(); i++)
			{
				CComPtr<IPDSwatchColor> swatch = m_targetObjects[i];
				swatch->put_nameWithColorValue(bNameWithColorValue == BST_CHECKED? VARIANT_TRUE: VARIANT_FALSE);
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

#endif //__COLORSWATCHOPTIONSDLG_H_
