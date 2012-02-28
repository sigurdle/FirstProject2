#pragma once

extern double ConvertUserUnitToSpecifiedValue(double value, short unitType);
extern double ConvertSpecifiedValueToUserUnit(short unitType, double specifiedValue);

namespace System
{
namespace LXmlEdit
{

	template<class T> class CAxDialogImpl : public UI::Control
	{
	public:
		void SetDlgItemInt(UINT, int);
		void SetDlgItemText(UINT, const char *);
		void SetDlgItemText(UINT, const WCHAR *);
		void SetDlgItemText(UINT, System::StringA*);
		void SetDlgItemText(UINT, System::StringW*);
		void CheckDlgButton(UINT, bool);
		bool IsDlgButtonChecked(UINT);
		void CheckRadioButton(UINT, UINT, UINT);

		int GetDlgItemInt(UINT);
		void GetDlgItemText(UINT, char*, UINT);
		void GetDlgItemText(UINT, WCHAR*, UINT);

		int DoModal()
		{
			ASSERT(0);
			return 0;
		}

		int DoModal(UI::Control*)
		{
			ASSERT(0);
			return 0;
		}

		void EndDialog(UINT)
		{
		}
	};

	template<class T> class CAxPropertyPageImpl : public CAxDialogImpl<T>
	{
	};

extern double GetWindowTextValue(UI::Control * hWnd, bool* bTrans = NULL);
extern double GetDlgItemValue(UI::Control * hWnd, UINT nID, bool* bTrans = NULL);
extern void SetWindowTextValue(UI::Control * hWnd, double value, short unit);
extern void SetWindowTextValueCheckForSame(UI::Control * hWnd, double value, short unit);
extern void SetDlgItemValue(UI::Control * hWnd, UINT nID, double value, short unit);

extern double GetDlgItemAngle(UI::Control * hWnd, UINT nID, bool* bTrans = NULL);
extern void SetDlgItemAngle(UI::Control * hWnd, UINT nID, double value);

extern bool GetDlgItemIntX(UI::Control * hWnd, UINT nID, int minv, int maxv, int* pvalue);

}	// LXmlEdit
}
