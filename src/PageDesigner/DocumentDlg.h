#pragma once

template <class T> class ATL_NO_VTABLE CDocumentDlg :
	public CAxDialogImpl<T>
{
public:
	CDocumentDlg()
	{
		m_numPages = 1;
		m_facingPages = FALSE;

		m_pageWidth = 0;
		m_pageHeight = 0;
	}

	int m_numPages;
	double m_pageWidth;
	double m_pageHeight;
	BOOL m_facingPages;

	double m_PageSizePresets[10][2];

	void SetPageSizePreset()
	{
		double pageWidth = GetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEWIDTH);
		double pageHeight = GetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEHEIGHT);

		double value0;
		double value1;

		if (IsDlgButtonChecked(IDC_NEWDOC_ORIENTATION_PORTRAIT))
		{
			value0 = pageWidth;
			value1 = pageHeight;
		}
		else
		{
			value1 = pageWidth;
			value0 = pageHeight;
		}

		for (int i = 0; i < 10; i++)
		{
			if (	(m_PageSizePresets[i][0] == value0) &&
					(m_PageSizePresets[i][1] == value1))
			{
				break;
			}
		}

		::SendMessage(GetDlgItem(IDC_NEWDOC_PAGESIZE_PRESETS), CB_SETCURSEL, i, 0);
	}

	void SetOrientation()
	{
		double pageWidth = GetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEWIDTH);
		double pageHeight = GetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEHEIGHT);

		CheckDlgButton(IDC_NEWDOC_ORIENTATION_PORTRAIT, pageWidth <= pageHeight);
		CheckDlgButton(IDC_NEWDOC_ORIENTATION_LANDSCAPE, pageWidth > pageHeight);
	}

BEGIN_MSG_MAP(CDocumentDlg)
	COMMAND_HANDLER(IDC_NEWDOC_PAGESIZE_PRESETS, CBN_SELCHANGE, OnPageSizePreset)
	COMMAND_HANDLER(IDC_NEWDOC_PAGEWIDTH, EN_KILLFOCUS, OnChangeSize)
	COMMAND_HANDLER(IDC_NEWDOC_PAGEHEIGHT, EN_KILLFOCUS, OnChangeSize)
	COMMAND_HANDLER(IDC_NEWDOC_ORIENTATION_PORTRAIT, BN_CLICKED, OnOrientation)
	COMMAND_HANDLER(IDC_NEWDOC_ORIENTATION_LANDSCAPE, BN_CLICKED, OnOrientation)
END_MSG_MAP()

	LRESULT OnChangeSize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		SetOrientation();
		SetPageSizePreset();
		return 0;
	}

	LRESULT OnOrientation(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		double pageWidth = GetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEWIDTH);
		double pageHeight = GetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEHEIGHT);

		double minValue, maxValue;

		if (pageWidth <= pageHeight)
		{
			minValue = pageWidth;
			maxValue = pageHeight;
		}
		else
		{
			minValue = pageHeight;
			maxValue = pageWidth;
		}

		if (IsDlgButtonChecked(IDC_NEWDOC_ORIENTATION_PORTRAIT))
		{
			SetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEWIDTH, minValue, UNIT_IN);
			SetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEHEIGHT, maxValue, UNIT_IN);
		}
		else
		{
			SetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEWIDTH, maxValue, UNIT_IN);
			SetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEHEIGHT, minValue, UNIT_IN);
		}

		return 0;
	}

	LRESULT OnPageSizePreset(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		long index = ::SendMessage(GetDlgItem(IDC_NEWDOC_PAGESIZE_PRESETS), CB_GETCURSEL, 0, 0);

		if (index < 10)
		{
			if (IsDlgButtonChecked(IDC_NEWDOC_ORIENTATION_PORTRAIT))
			{
				SetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEWIDTH, m_PageSizePresets[index][0], UNIT_IN);
				SetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEHEIGHT, m_PageSizePresets[index][1], UNIT_IN);
			}
			else
			{
				SetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEWIDTH, m_PageSizePresets[index][1], UNIT_IN);
				SetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEHEIGHT, m_PageSizePresets[index][0], UNIT_IN);
			}
		}

		return 0;
	}

	void OnInitDialog()
	{
		CenterWindow();

		::SendMessage(GetDlgItem(IDC_NEWDOC_ORIENTATION_PORTRAIT), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_ORIENTATION_PORTRAIT)));
		::SendMessage(GetDlgItem(IDC_NEWDOC_ORIENTATION_LANDSCAPE), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_ORIENTATION_LANDSCAPE)));

		::SendMessage(GetDlgItem(IDC_NEWDOC_PAGESIZE_PRESETS), CB_ADDSTRING, 0, (LPARAM)"Letter");
		::SendMessage(GetDlgItem(IDC_NEWDOC_PAGESIZE_PRESETS), CB_ADDSTRING, 0, (LPARAM)"Legal");
		::SendMessage(GetDlgItem(IDC_NEWDOC_PAGESIZE_PRESETS), CB_ADDSTRING, 0, (LPARAM)"Tabloid");
		::SendMessage(GetDlgItem(IDC_NEWDOC_PAGESIZE_PRESETS), CB_ADDSTRING, 0, (LPARAM)"Letter - Half");
		::SendMessage(GetDlgItem(IDC_NEWDOC_PAGESIZE_PRESETS), CB_ADDSTRING, 0, (LPARAM)"Legal - Half");
		::SendMessage(GetDlgItem(IDC_NEWDOC_PAGESIZE_PRESETS), CB_ADDSTRING, 0, (LPARAM)"A4");
		::SendMessage(GetDlgItem(IDC_NEWDOC_PAGESIZE_PRESETS), CB_ADDSTRING, 0, (LPARAM)"A3");
		::SendMessage(GetDlgItem(IDC_NEWDOC_PAGESIZE_PRESETS), CB_ADDSTRING, 0, (LPARAM)"A5");
		::SendMessage(GetDlgItem(IDC_NEWDOC_PAGESIZE_PRESETS), CB_ADDSTRING, 0, (LPARAM)"B5");
		::SendMessage(GetDlgItem(IDC_NEWDOC_PAGESIZE_PRESETS), CB_ADDSTRING, 0, (LPARAM)"Compact Disc");
		::SendMessage(GetDlgItem(IDC_NEWDOC_PAGESIZE_PRESETS), CB_ADDSTRING, 0, (LPARAM)"Custom");

	// Letter
		m_PageSizePresets[0][0] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 612);
		m_PageSizePresets[0][1] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 792);

	// Legal
		m_PageSizePresets[1][0] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 612);
		m_PageSizePresets[1][1] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 1008);

	// Tabloid
		m_PageSizePresets[2][0] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 792);
		m_PageSizePresets[2][1] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 1224);

	// Letter Half
		m_PageSizePresets[3][0] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 396);
		m_PageSizePresets[3][1] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 612);

	// Legal Half
		m_PageSizePresets[4][0] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 504);
		m_PageSizePresets[4][1] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 612);

	// A4
		m_PageSizePresets[5][0] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 595.276);
		m_PageSizePresets[5][1] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 841.89);

	// A3
		m_PageSizePresets[6][0] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 841.89);
		m_PageSizePresets[6][1] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 1190.551);

	// A5
		m_PageSizePresets[7][0] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 419.528);
		m_PageSizePresets[7][1] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 595.276);

	// B5
		m_PageSizePresets[8][0] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 498.898);
		m_PageSizePresets[8][1] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 708.661);

	// Compact Disc
		m_PageSizePresets[9][0] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 340);
		m_PageSizePresets[9][1] = ConvertSpecifiedValueToUserUnit(UNIT_PT, 342);

		CUString str;

		SetDlgItemInt(IDC_NEWDOC_NUMBEROFPAGES, m_numPages);

		CheckDlgButton(IDC_NEWDOC_FACINGPAGES, m_facingPages);

	// Page Size
		SetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEWIDTH, m_pageWidth, UNIT_IN);
		SetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEHEIGHT, m_pageHeight, UNIT_IN);

		SetOrientation();
		SetPageSizePreset();
	}

	BOOL OnOK()
	{
		m_numPages = GetDlgItemInt(IDC_NEWDOC_NUMBEROFPAGES);
//		m_numPagesCtl->get_value(&numPages);
		if (m_numPages < 1 || m_numPages > 9999)
		{
			MessageBox("Number of pages must be between 1..9999", "PageDesigner", MB_OK);
			::SetFocus(GetDlgItem(IDC_NEWDOC_NUMBEROFPAGES));
			::SendMessage(GetDlgItem(IDC_NEWDOC_NUMBEROFPAGES), EM_SETSEL, 0, -1);
			return 0;
		}

		m_facingPages = IsDlgButtonChecked(IDC_NEWDOC_FACINGPAGES);
	/*
		m_pageWidthCtl->get_value(&m_pageWidth);
		if (m_pageWidth <= 0)
		{
			MessageBox("pageWidth must be > 0", "PageDesigner", MB_OK);
			return 0;
		}

		m_pageHeightCtl->get_value(&m_pageHeight);
		if (m_pageHeight <= 0)
		{
			MessageBox("pageHeight must be > 0", "PageDesigner", MB_OK);
			return 0;
		}
	*/

//		TCHAR buf[256];

	// Page Size
		m_pageWidth = GetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEWIDTH);
		if (m_pageWidth <= 0)
		{
			MessageBox("pageWidth must be > 0", "PageDesigner", MB_OK);
			return 0;
		}

		m_pageHeight = GetDlgItemValue(m_hWnd, IDC_NEWDOC_PAGEHEIGHT);
		if (m_pageHeight <= 0)
		{
			MessageBox("pageHeight must be > 0", "PageDesigner", MB_OK);
			return 0;
		}

		return 1;
	}
};
