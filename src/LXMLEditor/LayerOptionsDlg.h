#ifndef __LAYEROPTIONSDLG_H_
#define __LAYEROPTIONSDLG_H_

#include "resource.h"       // main symbols

#include "ControlUtils.h"

namespace System
{
namespace LXmlEdit
{

class CLayerOptionsDlg : 
	public CAxDialogImpl<CLayerOptionsDlg>
{
public:
	CLayerOptionsDlg()
	{
	}

	~CLayerOptionsDlg()
	{
	}

	int m_isLayer;
	LDraw::Color m_color;

	void SetColorIndex();

	enum { IDD = IDD_LAYEROPTIONSDLG };

	long OnColor(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnChangeColorList(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

//	long OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

//	long OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_isLayer = IsDlgButtonChecked(IDC_LAYER_ISLAYER);
		EndDialog(wID);
		return 0;
	}

	long OnCancel(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

}
}

#endif //__LAYEROPTIONSDLG_H_
