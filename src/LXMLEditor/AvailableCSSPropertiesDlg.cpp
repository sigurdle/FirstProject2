// AvailableCSSPropertiesDlg.cpp : Implementation of CAvailableCSSPropertiesDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "AvailableCSSPropertiesDlg.h"

#include "CSSProperty.h"

extern WCHAR* CSSCategories[];
extern int g_nCSSCategories;

#if 0

/////////////////////////////////////////////////////////////////////////////
// CAvailableCSSPropertiesDlg

LRESULT CAvailableCSSPropertiesDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	for (int i = 0; i < g_nCSSCategories; i++)
	{
		_bstr_t name = CSSCategories[i];

		SendDlgItemMessage(IDC_CSSCATEGORY, LB_ADDSTRING, 0, (LPARAM)(TCHAR*)name);
	}

	return 1;  // Let the system set the focus
}

LRESULT CAvailableCSSPropertiesDlg::OnCategoryChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int catindex = SendDlgItemMessage(wID, LB_GETCURSEL);
	if (catindex >= 0)
	{
		SendDlgItemMessage(IDC_CSSPROPERTY, LB_RESETCONTENT);
		SetDlgItemText(IDC_CSSPROPERTY_INFO, NULL);

		for (int i = 0; i < g_nCSSProperties; i++)
		{
			CSSProperty* pProperty = &CSSProperties[i];

			if (pProperty->m_category == catindex)
			{
				_bstr_t name = pProperty->m_name;
				int index = SendDlgItemMessage(IDC_CSSPROPERTY, LB_ADDSTRING, 0, (LPARAM)(TCHAR*)name);
				SendDlgItemMessage(IDC_CSSPROPERTY, LB_SETITEMDATA, index, (LPARAM)pProperty);
			}
		}
	}

	return 0;
}

LRESULT CAvailableCSSPropertiesDlg::OnPropertyChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = SendDlgItemMessage(wID, LB_GETCURSEL);
	if (index >= 0)
	{
		CSSProperty* pProperty = (CSSProperty*)SendDlgItemMessage(IDC_CSSPROPERTY, LB_GETITEMDATA, index, NULL);

		CString str;
		str.Format(	"Initial value:\t%S\n"
						"Inherited:\t%s",
					pProperty->m_initialCSS,
					pProperty->m_bInherited? "yes": "no");

		SetDlgItemText(IDC_CSSPROPERTY_INFO, str);
	}

	return 0;
}

LRESULT CAvailableCSSPropertiesDlg::OnPropertyDblClk(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int index = SendDlgItemMessage(wID, LB_GETCURSEL);
	if (index >= 0)
	{
		CSSProperty* pProperty = (CSSProperty*)SendDlgItemMessage(IDC_CSSPROPERTY, LB_GETITEMDATA, index, NULL);

		m_style->setProperty(pProperty->m_name, pProperty->m_initialCSS, NULL);
		m_viewGroup->ApplyCurrentSelectionCSSStyle();
	}

	return 0;
}

#endif