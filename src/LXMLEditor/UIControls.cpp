#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "UIControls.h"

/*
CComBSTR CXMLData::GetDataValue(ILDOMElement* element)
{
	CComBSTR bstr;
	GetPathNodeValue(element, m_name, &bstr);

	return bstr;
}
*/

#if 0
#include "..\Utils\parsenumber.h"

//////////////////////////////////////////////////////////////////////////
// CXMLStringData

#if 0
// virtual
void CXMLStringData::InitValue(BSTR value)
{
	if (m_reentrancy == 0)
	{
		m_reentrancy++;

		m_value = value;

		for (int i = 0; i < m_controls.GetSize(); i++)
		{
			m_controls[i]->OnDataValueChanged(this);
		//	m_controls[i]->SetValue(value);
		}

		m_reentrancy--;
	}
}
#endif

//virtual
void CXMLStringData::SetValue(BSTR value)
{
	if (m_reentrancy == 0)
	{
		m_reentrancy++;

		m_value = value;

		for (int i = 0; i < m_controls.GetSize(); i++)
		{
			m_controls[i]->OnDataValueChanged(this);
		}

		m_controlWindow->OnDataValueChanged(this);

		m_reentrancy--;
	}
}

//virtual
_bstr_t CXMLStringData::GetValueAsString()
{
	return m_value;
}

///////////////////////////////////////////////////////////////////
// CSVGNumberListData

int GetCommaOrSpaceSepNumberArray(BSTR str, CArray<double,double>& values);

#if 0
// virtual
void CSVGNumberListData::InitValue(BSTR value)
{
	m_numberList.RemoveAll();
	GetCommaOrSpaceSepNumberArray(value, m_numberList);

//		CXMLAttribute::InitValue(value);
}
#endif

//virtual
void CSVGNumberListData::SetValue(BSTR value)
{
	if (m_reentrancy == 0)
	{
		m_reentrancy++;

		m_value = value;

		m_numberList.RemoveAll();
		GetCommaOrSpaceSepNumberArray(value, m_numberList);

		for (int i = 0; i < m_controls.GetSize(); i++)
		{
			m_controls[i]->OnDataValueChanged(this);
		}

		m_controlWindow->OnDataValueChanged(this);

		m_reentrancy--;
	}
}

// virtual
_bstr_t CSVGNumberListData::GetValueAsString()
{
	return m_value;
}

/////////////////////////////////////////////////////////////////
// CEditBox

LRESULT CEditBox::OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if ((uMsg == WM_KILLFOCUS) ||
		(uMsg == WM_KEYDOWN && wParam == VK_RETURN))
	{
		EndEdit();

		//if (uMsg == WM_KEYDOWN)
			return 0;
	}

	return m_wndEdit.DefWindowProc(uMsg, wParam, lParam);
}

//virtual
void CEditBox::Draw(HDC hDC, CRect rect)
{
	CDCHandle dc(hDC);

	dc.Draw3dRect(&rect, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
	rect.InflateRect(-1,-1);

	_bstr_t value = m_valueAsString;//CreateValueUnitString(m_valueInSpecifiedUnits, m_lengthType);
	if (value.length())
	{
		dc.DrawText(value, value.length(), &rect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}
}

// virtual
BOOL CEditBox::Activate(HWND hParent, POINT point, CRect rect)
{
	ATLASSERT(m_wndEdit == NULL);

	rect.InflateRect(-1,-1);
	rect.top++;

	m_hWndEdit = CreateWindowEx(0, "edit", NULL, /*WS_BORDER |*/ WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
		rect.left, rect.top, rect.Width(), rect.Height(), hParent, (HMENU)1, _Module.m_hInst, NULL);
	m_wndEdit.SubclassWindow(m_hWndEdit);
	//m_wndEdit.Attach(m_hWndEdit);

	m_wndEdit.SetWindowLong(GWL_USERDATA, (long)this);
	m_wndEdit.SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

	m_wndEdit.SetWindowText(_bstr_t(GetProperty(NULL)));
	m_wndEdit.SendMessage(EM_SETSEL, 0, -1);

	m_wndEdit.SetFocus();

	return TRUE;
}

//virtual
void CEditBox::Deactivate()
{
	EndEdit();
}

void CEditBox::EndEdit()
{
	USES_CONVERSION;

	if (m_wndEdit != NULL)
	{
		int nLen = m_wndEdit.GetWindowTextLength();

		TCHAR* buf = new TCHAR[nLen+1];
		m_wndEdit.GetWindowText(buf, nLen+1);

		_bstr_t value = buf;

		_bstr_t oldvalue = m_valueAsString;//GetValueAsString();

		if (oldvalue.length() == 0 || wcscmp(value, oldvalue))
		{
			SetProperty(NULL, value);//m_pData->SetValue(value);
		}

		delete buf;

		m_wndEdit.DestroyWindow();
		m_hWndEdit = NULL;
	}
}

// virtual
_variant_t CEditBox::GetProperty(BSTR name)
{
	if (name == NULL)
		return variant_t(m_valueAsString);

	ATLASSERT(0);
	return _variant_t();
}

// virtual
HRESULT CEditBox::SetProperty(BSTR name, _variant_t value)
{
	if (name == NULL)
	{
		m_valueAsString = value;
		m_pSite->OnControlValueChanged();
		return S_OK;
	}

	ATLASSERT(0);
	return E_FAIL;
}

/////////////////////////////////////////////////////////////////
// CXMLControlLength

#include "..\LXUI\cssunits.h"

// virtual
_variant_t CControlLength::GetProperty(BSTR name)
{
	return m_editBox->GetProperty(name);
}

// virtual
HRESULT CControlLength::SetProperty(BSTR name, _variant_t value)
{
	if (name == NULL)
	{
		m_editBox->m_valueAsString = value;
		m_valueInSpecifiedUnits = ParseValueUnitString(m_editBox->m_valueAsString, (int*)&m_lengthType);

		m_pSite->OnControlValueChanged();

		m_pSite->Redraw();	// TODO remove

		return S_OK;
	}

	ATLASSERT(0);
	return E_FAIL;
}

//virtual
void CControlLength::Draw(HDC hDC, CRect rect)
{
	CDCHandle dc(hDC);

	{
		CRect rc = rect;
		rc.right -= 16;

		m_editBox->Draw(hDC, rc);
	}

	{
		CRect rc = rect;
		rc.left = rc.right-16;

		dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
		//rc.InflateRect(-1,-1);

		POINT pt[3] =
		{
			rc.left+4,		rc.top+6,
			rc.left+4+8,	rc.top+6,
			rc.left+4+4,	rc.top+6+4
		};

		HPEN hOldPen = dc.SelectPen((HPEN)GetStockObject(NULL_PEN));
		HBRUSH hOldBrush = dc.SelectBrush((HBRUSH)GetStockObject(BLACK_BRUSH));

		dc.Polygon(pt, 3);

		dc.SelectPen(hOldPen);
		dc.SelectBrush(hOldBrush);
	}
}

// virtual
BOOL CControlLength::Activate(HWND hParent, POINT point, CRect rect)
{
	if (point.x > rect.Width()-16)
	{
		HMENU hMenu;
		hMenu = CreatePopupMenu();

		//AppendMenu(hMenu, MF_STRING, 1, _T("Unchanged"));
		//AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hMenu, MF_STRING, SVG_LENGTHTYPE_NUMBER, _T("Number"));
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hMenu, MF_STRING, SVG_LENGTHTYPE_PT, _T("Point"));
		AppendMenu(hMenu, MF_STRING, SVG_LENGTHTYPE_PC, _T("Pica"));
		AppendMenu(hMenu, MF_STRING, SVG_LENGTHTYPE_PX, _T("Pixel"));
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hMenu, MF_STRING, SVG_LENGTHTYPE_EMS, _T("em"));
		AppendMenu(hMenu, MF_STRING, SVG_LENGTHTYPE_EXS, _T("ex"));
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hMenu, MF_STRING, SVG_LENGTHTYPE_MM, _T("mm"));
		AppendMenu(hMenu, MF_STRING, SVG_LENGTHTYPE_CM, _T("cm"));
		AppendMenu(hMenu, MF_STRING, SVG_LENGTHTYPE_IN, _T("Inch"));
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hMenu, MF_STRING, SVG_LENGTHTYPE_PERCENTAGE, _T("%"));

		switch (m_lengthType)
		{
			case CSS_PERCENTAGE:
			case CSS_EMS:
			case CSS_EXS:
			case CSS_PX:
			case CSS_CM:
			case CSS_MM:
			case CSS_IN:
			case CSS_PT:
			case CSS_PC:
			case CSS_NUMBER:
				{
					CheckMenuItem(hMenu, m_lengthType, MF_BYCOMMAND | MF_CHECKED);
				}
				break;
		}

		CPoint point2(rect.right, rect.top);
		::ClientToScreen(hParent, &point2);

		UINT nID = ::TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_LEFTBUTTON, point2.x, point2.y, 0, hParent, NULL);

		DestroyMenu(hMenu);

		if (nID > 0)
		{
		// Convert value
			double value = ConvertSpecifiedValueToUserUnit(m_lengthType, m_valueInSpecifiedUnits);

			m_lengthType = (LSVGLengthType)nID;
			m_valueInSpecifiedUnits = ConvertUserUnitToSpecifiedValue(value, m_lengthType);
			_bstr_t stringValue  = CreateValueUnitString(m_valueInSpecifiedUnits, m_lengthType);

			SetProperty(NULL, stringValue);
		// Notify
			//m_controlWindow->OnControlValueChanged(this);
		}
	}
	else
	{
		rect.right -= 16;

		return m_editBox->Activate(hParent, point, rect);
	}

	return FALSE;
}

//virtual
void CControlLength::Deactivate()
{
	m_editBox->Deactivate();
}

/////////////////////////////////////////////////////////////////
// CXMLControlLength

// virtual
_variant_t CControlAnimateMotionRotate::GetProperty(BSTR name)
{
	return m_editBox.GetProperty(name);
}

// virtual
HRESULT CControlAnimateMotionRotate::SetProperty(BSTR name, _variant_t value)
{
	if (name == NULL)
	{
		m_editBox.m_valueAsString = value;
		if (!wcscmp(m_editBox.m_valueAsString, L"auto"))
		{
			m_angleType = SVG_ROTATE_AUTO;
		}
		else if (!wcscmp(m_editBox.m_valueAsString, L"auto-reverse"))
		{
			m_angleType = SVG_ROTATE_AUTO_REVERSE;
		}
		else
		{
			m_valueInSpecifiedUnits = ParseAngleUnitString(m_editBox.m_valueAsString, (int*)&m_angleType);
			m_angleType += SVG_ROTATE_ANGLE;
		}

		m_pSite->OnControlValueChanged();

		m_pSite->Redraw();	// TODO remove

		return S_OK;
	}

	ATLASSERT(0);
	return E_FAIL;
}

//virtual
void CControlAnimateMotionRotate::Draw(HDC hDC, CRect rect)
{
	CDCHandle dc(hDC);

	{
		CRect rc = rect;
		rc.right -= 16;

		m_editBox.Draw(hDC, rc);
	}

	{
		CRect rc = rect;
		rc.left = rc.right-16;

		dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
		//rc.InflateRect(-1,-1);

		POINT pt[3] =
		{
			rc.left+4,		rc.top+6,
			rc.left+4+8,	rc.top+6,
			rc.left+4+4,	rc.top+6+4
		};

		HPEN hOldPen = dc.SelectPen((HPEN)GetStockObject(NULL_PEN));
		HBRUSH hOldBrush = dc.SelectBrush((HBRUSH)GetStockObject(BLACK_BRUSH));

		dc.Polygon(pt, 3);

		dc.SelectPen(hOldPen);
		dc.SelectBrush(hOldBrush);
	}
}

// virtual
BOOL CControlAnimateMotionRotate::Activate(HWND hParent, POINT point, CRect rect)
{
	if (point.x > rect.Width()-16)
	{
		HMENU hMenu;
		hMenu = CreatePopupMenu();

		AppendMenu(hMenu, MF_STRING, SVG_ROTATE_AUTO, _T("auto"));
		AppendMenu(hMenu, MF_STRING, SVG_ROTATE_AUTO_REVERSE, _T("auto-reverse"));
		AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
		AppendMenu(hMenu, MF_STRING, SVG_ROTATE_ANGLE + SVG_ANGLETYPE_UNSPECIFIED, _T("Unspecified (degrees)"));
		AppendMenu(hMenu, MF_STRING, SVG_ROTATE_ANGLE + SVG_ANGLETYPE_DEG, _T("Degrees"));
		AppendMenu(hMenu, MF_STRING, SVG_ROTATE_ANGLE + SVG_ANGLETYPE_RAD, _T("Radians"));
		AppendMenu(hMenu, MF_STRING, SVG_ROTATE_ANGLE + SVG_ANGLETYPE_GRAD, _T("Grads"));

		/*
		switch (m_lengthType)
		{
			case CSS_PERCENTAGE:
			case CSS_EMS:
			case CSS_EXS:
			case CSS_PX:
			case CSS_CM:
			case CSS_MM:
			case CSS_IN:
			case CSS_PT:
			case CSS_PC:
			case CSS_NUMBER:
			*/
				{
					CheckMenuItem(hMenu, m_angleType, MF_BYCOMMAND | MF_CHECKED);
				}
/*				break;
		}
*/
		CPoint point2(rect.right, rect.top);
		::ClientToScreen(hParent, &point2);

		UINT nID = ::TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_LEFTBUTTON, point2.x, point2.y, 0, hParent, NULL);

		DestroyMenu(hMenu);

		if (nID > 0)
		{
			if (nID < SVG_ROTATE_ANGLE)
			{
				m_angleType = nID;

				if (nID == SVG_ROTATE_AUTO)
				{
					SetProperty(NULL, L"auto");
				}
				else if (nID == SVG_ROTATE_AUTO_REVERSE)
				{
					SetProperty(NULL, L"auto-reverse");
				}
			}
			else
			{
			// Convert value
				double value;
				if (m_angleType >= SVG_ROTATE_ANGLE)
					value = ConvertSpecifiedValueToDegrees(m_angleType-SVG_ROTATE_ANGLE, m_valueInSpecifiedUnits);
				else
					value = 0;

				m_angleType = nID;
				m_valueInSpecifiedUnits = ConvertDegreesToSpecifiedValue(value, m_angleType-SVG_ROTATE_ANGLE);
				_bstr_t stringValue  = CreateAngleUnitString(m_valueInSpecifiedUnits, m_angleType-SVG_ROTATE_ANGLE);

				SetProperty(NULL, stringValue);
			}
		}
	}
	else
	{
		rect.right -= 16;

		return m_editBox.Activate(hParent, point, rect);
	}

	return FALSE;
}

//virtual
void CControlAnimateMotionRotate::Deactivate()
{
	m_editBox.Deactivate();
}

/////////////////////////////////////////////////////////////////
// CXMLControlNumber

// virtual
_variant_t CXMLControlNumber::GetProperty(BSTR name)
{
	if (name == NULL)
		return variant_t(m_value);

	ATLASSERT(0);
	return _variant_t();
}

// virtual
HRESULT CXMLControlNumber::SetProperty(BSTR name, _variant_t value)
{
	if (name == NULL)
	{
		m_value = value;
		m_pSite->Redraw();

		return S_OK;
	}

	ATLASSERT(0);
	return E_FAIL;
}

//virtual
void CXMLControlNumber::Draw(HDC hDC, CRect rect)
{
	CDCHandle dc(hDC);

	CRect rc = rect;
	dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DSHADOW));
	rc.InflateRect(-1,-1);

	if (m_value.length())
	{
		dc.DrawText(m_value, m_value.length(), &rc, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}
}

// virtual
BOOL CXMLControlNumber::Activate(HWND hParent, POINT point, CRect rect)
{
	ATLASSERT(m_wndEdit == NULL);

	m_hWndEdit = CreateWindowEx(0, "edit", NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
		rect.left, rect.top, rect.Width(), rect.Height(), hParent, (HMENU)1, _Module.m_hInst, NULL);
	m_wndEdit.SubclassWindow(m_hWndEdit);
	//m_wndEdit.Attach(m_hWndEdit);

	m_wndEdit.SetWindowLong(GWL_USERDATA, (long)this);
	m_wndEdit.SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

	m_wndEdit.SetWindowText(m_value);
	m_wndEdit.SendMessage(EM_SETSEL, 0, -1);

	m_wndEdit.SetFocus();

	return FALSE;
}

// virtual
void CXMLControlNumber::Deactivate()
{
	EndEdit();
}

void CXMLControlNumber::EndEdit()
{
	USES_CONVERSION;

	if (m_wndEdit != NULL)
	{
		int nLen = m_wndEdit.GetWindowTextLength();

		TCHAR* buf = new TCHAR[nLen+1];
		m_wndEdit.GetWindowText(buf, nLen+1);

		_bstr_t value = buf;

		if (m_value.length() == 0 || wcscmp(value, m_value))
		{
			m_value = value;
			m_pSite->OnControlValueChanged();
			//SetValue(value);
		}

		delete buf;

		m_wndEdit.DestroyWindow();
		m_hWndEdit = NULL;
	}
}

LRESULT CXMLControlNumber::OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if ((uMsg == WM_KILLFOCUS) ||
		(uMsg == WM_KEYDOWN && wParam == VK_RETURN))
	{
		EndEdit();

		//if (uMsg == WM_KEYDOWN)
			return 0;
	}

	return m_wndEdit.DefWindowProc(uMsg, wParam, lParam);
}

////////////////////////////////////////////////////////////////
// CXMLControlCheckbox

// virtual
void CXMLControlCheckbox::Draw(HDC hDC, CRect rect)
{
	CDCHandle dc(hDC);

	int middle = rect.left + rect.Width()/2-20;

	CRect box(middle, rect.top+1, middle+16, rect.top+14);

	DWORD uState;
	if (m_value == 1)
		uState = DFCS_CHECKED;
	else if (m_value == 2)
		uState = DFCS_BUTTON3STATE;
	else
		uState = 0;

	dc.DrawFrameControl(&box, DFC_BUTTON, DFCS_BUTTONCHECK | uState);
}

// virtual
BOOL CXMLControlCheckbox::Activate(HWND hParent, POINT point, CRect rect)
{
	m_value = !m_value;

	m_pSite->Redraw();
	m_pSite->OnControlValueChanged();	// Do in EndDrag?

	return FALSE;
}

// virtual
void CXMLControlCheckbox::DoDrag(POINT point, CRect box)
{
}

// virtual
void CXMLControlCheckbox::Deactivate()
{
}

// virtual
_variant_t CXMLControlCheckbox::GetProperty(BSTR name)
{
	if (name == NULL)
	{
		if (m_value)
			return _bstr_t(L"true");
		else
			return _bstr_t(L"false");
	}

	ATLASSERT(0);
	return _variant_t();
}

// virtual
HRESULT CXMLControlCheckbox::SetProperty(BSTR name, _variant_t value)
{
	if (name == NULL)
	{
		if (!wcscmp(_bstr_t(value), L"true"))
			m_value = 1;
		else if (!wcscmp(_bstr_t(value), L"false"))
			m_value = 0;
		else
			m_value = 2;	// indeterminate

		return S_OK;
	}

	ATLASSERT(0);
	return E_FAIL;
}

////////////////////////////////////////////////////////////////
// CXMLControlSlider

//virtual
void CXMLControlSlider::Draw(HDC hDC, CRect rect)
{
	CDCHandle dc(hDC);

	rect.right -= 10;

	double range = m_maxValue-m_minValue;

	dc.Draw3dRect(rect.left + 5, rect.top + 4, rect.Width()+1, 3, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));

	int x = rect.left + 5+(rect.Width()*(m_value-m_minValue))/range;
	int y = rect.top+7;

	POINT pt[] =
	{
		x, y,
		x-5, y+5,
		x+5, y+5,
	};

	dc.Polygon(pt, 3);
}

//virtual
BOOL CXMLControlSlider::Activate(HWND hParent, POINT point, CRect rect)
{
	DoDrag(point, rect);
	return TRUE;	// Drag
}

//virtual
void CXMLControlSlider::DoDrag(POINT point, CRect rect)
{
	point.x -= 4;

//	CRect client;
//	GetClientRect(&client);

	rect.right -= 8;

	double range = m_maxValue-m_minValue;

	m_value = (point.x*range + m_minValue) / rect.Width();

	if (m_value < m_minValue) m_value = m_minValue;
	else if (m_value > m_maxValue) m_value = m_maxValue;

	m_pSite->OnControlValueChanged();	// Do in EndDrag?
}

//virtual
void CXMLControlSlider::Deactivate()
{
}

//virtual
_variant_t CXMLControlSlider::GetProperty(BSTR name)
{
	if (name == NULL)
	{
		WCHAR buf[64];
		swprintf(buf, L"%g", m_value);
		return _bstr_t(buf);
	}

	ATLASSERT(0);
	return E_FAIL;
}

//virtual
HRESULT CXMLControlSlider::SetProperty(BSTR name, _variant_t value)
{
	if (name == NULL)
	{
		try
		{
			m_value = getfnumber(_bstr_t(value));

			m_pSite->OnControlValueChanged();
			m_pSite->Redraw();	// TODO: hm.. ??

			return S_OK;
		}
		catch(_com_error& e)
		{
			return e.Error();
		}
	}

	ATLASSERT(0);
	return E_FAIL;
}

////////////////////////////////////////////////////////////////
// CXMLControlString

#if 0
// virtual
void CXMLControlString::SetValue(BSTR value)
{
	m_value = value;
	m_controlWindow->OnControlValueChanged(this);
}

// virtual
_bstr_t CXMLControlString::GetValueAsString()
{
	return m_value;
}
#endif

// virtual
_variant_t CXMLControlString::GetProperty(BSTR name)
{
	if (name == NULL)
		return variant_t(m_value);

	ATLASSERT(0);
	return _variant_t();
}

// virtual
HRESULT CXMLControlString::SetProperty(BSTR name, _variant_t value)
{
	if (name == NULL)
	{
		m_value = value;

		m_pSite->OnControlValueChanged();

		m_pSite->Redraw();	// TODO remove

		return S_OK;
	}

	ATLASSERT(0);
	return E_FAIL;
}

// virtual
void CXMLControlString::Draw(HDC hDC, CRect rect)
{
	CDCHandle dc(hDC);

	CRect rc = rect;
	dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DSHADOW));
	rc.InflateRect(-1,-1);

	if (m_value.length())
	{
		dc.DrawText(m_value, m_value.length(), &rc, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}
}

// virtual
BOOL CXMLControlString::Activate(HWND hParent, POINT point, CRect rect)
{
	ATLASSERT(m_wndEdit == NULL);

	m_hWndEdit = CreateWindowEx(0, "edit", NULL, WS_BORDER | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
		rect.left, rect.top, rect.Width(), rect.Height(), hParent, (HMENU)1, _Module.m_hInst, NULL);
	m_wndEdit.SubclassWindow(m_hWndEdit);
	//m_wndEdit.Attach(m_hWndEdit);

	m_wndEdit.SetWindowLong(GWL_USERDATA, (long)this);
	m_wndEdit.SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

	m_wndEdit.SetWindowText(m_value);
	m_wndEdit.SendMessage(EM_SETSEL, 0, -1);

	m_wndEdit.SetFocus();

	return FALSE;
}

// virtual
void CXMLControlString::Deactivate()
{
	EndEdit();
}

void CXMLControlString::EndEdit()
{
	USES_CONVERSION;

	if (m_wndEdit != NULL)
	{
		int nLen = m_wndEdit.GetWindowTextLength();

		TCHAR* buf = new TCHAR[nLen+1];
		m_wndEdit.GetWindowText(buf, nLen+1);

		_bstr_t value = buf;

		if (m_value.length() == 0 || wcscmp(value, m_value))
		{
			SetProperty(NULL, value);
		}

		delete buf;

		m_wndEdit.DestroyWindow();
		m_hWndEdit = NULL;
	}
}

LRESULT CXMLControlString::OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if ((uMsg == WM_KILLFOCUS) ||
		(uMsg == WM_KEYDOWN && wParam == VK_RETURN))
	{
		EndEdit();

		//if (uMsg == WM_KEYDOWN)
			return 0;
	}

	return m_wndEdit.DefWindowProc(uMsg, wParam, lParam);
}

//////////////////////////////////////////////////////////
// CXMLControlPopup

// virtual
void CXMLControlPopup::Draw(HDC hDC, CRect rect)
{
	CDCHandle dc(hDC);

	CRect rc = rect;

	dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
	rc.InflateRect(-1,-1);

	dc.Draw3dRect(&rc, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));
	rc.InflateRect(-1,-1);

	CRect trect = rc;
	trect.right -= 20;

	dc.Draw3dRect(trect.right+1, trect.top+2, 2, trect.Height()-4, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

	POINT pt[3] =
	{
		trect.right+6,		trect.top+5,
		trect.right+6+10,	trect.top+5,
		trect.right+6+5,	trect.top+5+5
	};

	HPEN hOldPen = dc.SelectPen((HPEN)GetStockObject(NULL_PEN));
	HBRUSH hOldBrush = dc.SelectBrush((HBRUSH)GetStockObject(BLACK_BRUSH));

	dc.Polygon(pt, 3);

	dc.SelectPen(hOldPen);
	dc.SelectBrush(hOldBrush);

	if (m_value.length())
	{
		dc.DrawText(m_value, m_value.length(), &trect, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS);
	}
}

// virtual
BOOL CXMLControlPopup::Activate(HWND hParent, POINT /*point*/, CRect rect)
{
	HMENU hMenu;
	hMenu = CreatePopupMenu();

	for (int i = 0; i < m_enumStrings.GetSize(); i++)
	{
		UINT nFlags = MF_STRING;
		if (m_value.length() && !wcscmp(m_value, m_enumStrings[i])) nFlags |= MF_CHECKED;

		AppendMenu(hMenu, nFlags, i+1, m_enumStrings[i]);
	}

	CPoint point(rect.left, rect.bottom);
	::ClientToScreen(hParent, &point);

	UINT nID = ::TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_LEFTBUTTON, point.x, point.y, 0, hParent, NULL);

	DestroyMenu(hMenu);

	if (nID > 0)
	{
		if (m_value.length() == 0 || wcscmp(m_value, m_enumStrings[nID-1]))
		{
			::InvalidateRect(hParent, &rect, TRUE);	// TODO, do this in SetValue()
			SetProperty(NULL, m_enumStrings[nID-1]);
		}
	}

	return FALSE;
}

// virtual
void CXMLControlPopup::Deactivate()
{
}

///////////////////////////////////////////////////////////
// CXMLControlColorCurve

// virtual
void CXMLControlColorCurve::Draw(HDC hDC, CRect rect)
{
	CDCHandle dc(hDC);

	CRect rc = rect;
	dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DSHADOW));
	rc.InflateRect(-1,-1);

#if 0
	BYTE values[256];

	double amplitude = atof(m_controlWindow->GetControl("amplitude")->GetValueAsStringD());
	double exponent = atof(m_controlWindow->GetControl("exponent")->GetValueD());
	double offset = atof(m_controlWindow->GetControl("offset")->GetValueD());

	for (int i = 0; i < 256; i++)
	{
		int n = (amplitude * pow(i/255.0, exponent) + offset)*255;

		if (n < 0) n = 0;
		else if (n > 255) n = 255;

		values[i] = (BYTE)n;
	}

	for (int x = 0; x < rc.Width(); x++)
	{
		int n = x*255/rc.Width();
		ATLASSERT(n < 256);

		int y = values[n]*rc.Height()/255;

		dc.SetPixelV(rc.left+x, rc.bottom-y, RGB(0,0,0));
	}
#endif
}

// virtual
BOOL CXMLControlColorCurve::Activate(HWND hParent, POINT point, CRect rect)
{
	return FALSE;
}

// virtual
void CXMLControlColorCurve::Deactivate()
{
}

///////////////////////////////////////////////////////////////
// CXMLControlColorMatrix

// virtual
void CXMLControlColorMatrix::Draw(HDC hDC, CRect rect)
{
	CDCHandle dc(hDC);

	for (int i = 0; i < 5; i++)
	{
		int x = i*10;
		dc.MoveTo(rect.left+x, rect.top);
		dc.LineTo(rect.left+x, rect.bottom);
	}

	for (i = 0; i < 4; i++)
	{
		int y = i*10;
		dc.MoveTo(rect.left, rect.top+y);
		dc.LineTo(rect.right, rect.top+y);
	}

	/*
	if (m_pAttr->m_value.length())
	{
		dc.DrawText(m_pAttr->m_value, m_pAttr->m_value.length(), &rect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}
	*/
}

// virtual
BOOL CXMLControlColorMatrix::Activate(HWND hParent, POINT point, CRect rect)
{
	return FALSE;
}

// virtual
void CXMLControlColorMatrix::Deactivate()
{
}

////////////////////////////////////////////////////////////////
// CXMLControlHueRotate

double CXMLControlHueRotate::GetAngle(POINT point, CRect box)
{
	CPoint pt = point;

//	int cx = /*box.left+*/box.Width()/2;
//	int cy = /*box.top+*/box.Height()/2;
	int cx = /*box.left+*/60/2;
	int cy = /*box.top+*/60/2;

	double radian;

	double dx = (double)(pt.x-cx);
	double dy = (double)(pt.y-cy);
	double distance = sqrt(dx*dx+dy*dy);
	double distance2 = distance;

	if (distance2 == 0.0) distance2 = 0.0001;
	radian = acos(dx/distance2);
	if (dy < 0) radian = M_PI*2 - radian;

	double dvalue = radian*(180.0/M_PI);

	return dvalue;
}

//virtual
_variant_t CXMLControlHueRotate::GetProperty(BSTR name)
{
	if (name == NULL)
	{
		WCHAR buf[64];
		swprintf(buf, L"%g", m_value);
		return _bstr_t(buf);
	}

	ASSERT(0);
	return E_FAIL;
}

//virtual
HRESULT CXMLControlHueRotate::SetProperty(BSTR name, _variant_t value)
{
	if (name == NULL)
	{
		try
		{
			m_value = getfnumber(_bstr_t(value));

			m_pSite->OnControlValueChanged();
			m_pSite->Redraw();	// TODO: hm.. ??

			return S_OK;
		}
		catch(_com_error& e)
		{
			return e.Error();
		}
	}

	ASSERT(0);
	return E_FAIL;
}

// virtual
void CXMLControlHueRotate::Draw(HDC hDC, CRect rect)
{
	CDCHandle dc(hDC);

	for (int y = 0; y < 60; y++)
	{
		for (int x = 0; x < 60; x++)
		{
			int dx = x-30;
			int dy = y-30;

			double distance = sqrt(dx*dx+dy*dy);

			if (distance > 20 && distance < 30)
			{
				double distance2 = distance;

				if (distance2 == 0.0) distance2 = 0.00001;
				if (dy < 0) distance2 =-distance2;
				double radangle = acos(dx/distance2);
				if (dy < 0) radangle += M_PI;

				COLORREF clr = HLStoRGB(HLS(gmDegrees(radangle)*255/360, 128, 200));

				dc.SetPixelV(rect.left + x, rect.top + y, clr);
			}
			else if (distance > 9 && distance < 19)
			{
				double distance2 = distance;

				if (distance2 == 0.0) distance2 = 0.00001;
				if (dy < 0) distance2 =-distance2;
				double radangle = acos(dx/distance2);
				if (dy < 0) radangle += M_PI;

				double deg = gmDegrees(radangle);
				deg -= m_value;
				while (deg < 0) deg += 360;
				while (deg >= 360) deg -= 360;

				COLORREF clr = HLStoRGB(HLS(deg*255/360, 128, 200));

				dc.SetPixelV(rect.left + x, rect.top + y, clr);
			}
		}
	}

	{
		int x = rect.left + cos(gmRadians(m_value))*25 + 30;
		int y = rect.top + sin(gmRadians(m_value))*25 + 30;

		dc.Ellipse(x-3, y-3, x+4, y+4);
	}

	/*
	_bstr_t stringValue = m_pData->GetValue();

	if (stringValue.length())
	{
		dc.DrawText(stringValue, stringValue.length(), &rect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}
	*/
}

static double g_oldValue;
static int m_numMoves;

// virtual
BOOL CXMLControlHueRotate::Activate(HWND hParent, POINT point, CRect rect)
{
	m_numMoves = 0;
	/*
	g_oldValue = GetAngle(point, rect);
	while (g_oldValue < 0) g_oldValue += 360;
	while (g_oldValue >= 360) g_oldValue -= 360;
*/

	DoDrag(point, rect);

	return TRUE;
}

// virtual
void CXMLControlHueRotate::DoDrag(POINT point, CRect box)
{
	CPoint pt = point;
	/*
	pt.x = point.x - m_scrollArea.left;
	pt.y = point.y;
	
	CAngleProperty* pAngle = (CAngleProperty*)m_pProp->TOP();
	
	CRect arect(x+m_pProp->m_indentX, y+1, m_scrollArea.Width()-40, y+34);
	int middle = arect.left + arect.Width()/2-20;
	CRect box(middle, arect.top, middle+34, arect.bottom);
	*/
	/*
	int cx = box.left+box.Width()/2;
	int cy = box.top+box.Height()/2;

	double radian;

	double dx = (double)(pt.x-cx);
	double dy = (double)(pt.y-cy);
	double distance = sqrt(dx*dx+dy*dy);
	double distance2 = distance;

	if (distance2 == 0.0) distance2 = 0.0001;
	radian = acos(dx/distance2);
	if (dy < 0) radian = M_PI*2 - radian;

	double dvalue = radian*(180.0/M_PI);
*/
	double dvalue = GetAngle(point, box);

	//long loldvalue ;
	//m_pProp->GetParamTags((PARAM_ANGLE_Value), &loldvalue, (TAG_DONE));
	double doldvalue = m_value;//loldvalue/65536.0;

	if (m_numMoves == 0)
	{
		g_oldValue = doldvalue;
		while (g_oldValue < 0) g_oldValue += 360;
		while (g_oldValue >= 360) g_oldValue -= 360;
	}

	double delta = dvalue - g_oldValue;

	if (delta < -180)
	{
		delta = dvalue + (360-g_oldValue);
	}
	else if (delta > 180)
	{
		delta = dvalue - g_oldValue - 360;
	}

	g_oldValue = dvalue;

	dvalue = doldvalue + delta;

	m_value = dvalue;

	m_pSite->Redraw();

	m_numMoves++;
	/*
	m_pProp->SetParamTags(
		(PARAM_Update), 0,
		(PARAM_ANGLE_Value), (long)(dvalue*65536.0), (TAG_DONE));

	m_pLayer->TOP()->OnUserChangedParam(m_pProp, m_paramIndex+1, TRUE);
	*/

	m_pSite->OnControlValueChanged();	// Do in EndDrag?
}

// virtual
void CXMLControlHueRotate::Deactivate()
{
}

//////////////////////////////////////////////////////////////////////////////////
// CXMLControlDistantLight

#define DEFAULT_VEC                         {0.00, 0.00, 1.00}      // Default start vector
#define DEFAULT_DIFFUSE                     RGB( 100,  100, 100)      // Default diffuse color
#define DEFAULT_AMBIENT                     RGB( 20,  20,  20)      // Default ambient color
#define DEFAULT_LIGHT                       RGB(200, 200, 200)      // Default light color
#define DEFAULT_START_BACKGROUND_COLOR      RGB(  0,   0,   0)      // Default gradient background start color
#define DEFAULT_END_BACKGROUND_COLOR        RGB(140,   0, 120)      // Default gradient background end color
#define DEFAULT_SPEC_EXP                    25.0                    // Default specular intensity

// Calculate lightning effect for specific pixel on ball's surface
COLORREF CXMLControlDistantLight::CalcLight(gmVector3& dVec, double dx, double dy, double dz)
{
	m_clrDiffuse = DEFAULT_DIFFUSE;
	m_clrAmbient = DEFAULT_AMBIENT;
	m_clrLight = DEFAULT_LIGHT;
	
	m_dSpecularExponent = DEFAULT_SPEC_EXP;
	
	double NL = dx * dVec[0] + dy * dVec[1] + dz * dVec[2], 
		RV = 2.0 * NL,
		rx = dVec[0] - (dx * RV),
		ry = dVec[1] - (dy * RV),
		rz = dVec[2] - (dz * RV);
	
	if (NL < 0.0)   // Diffuse coefficient
		NL = 0.0;
	
	RV = max (0.0, -rz);
	RV = double(pow (RV, m_dSpecularExponent));
	
	int r = int (	double(GetRValue(m_clrDiffuse)) * NL +  // Diffuse
						double(GetRValue(m_clrLight)) * RV +    // Specular
						double(GetRValue(m_clrAmbient)));       // Ambient
		
	int g = int (	double(GetGValue(m_clrDiffuse)) * NL +  // Diffuse
						double(GetGValue(m_clrLight)) * RV +    // Specular
						double(GetGValue(m_clrAmbient)));       // Ambient    
		
	int b = int (  double(GetBValue(m_clrDiffuse)) * NL +  // Diffuse
						double(GetBValue(m_clrLight)) * RV +    // Specular
						double(GetBValue(m_clrAmbient)));       // Ambient
	
	r = min (255, r);   // Cutoff highlight
	g = min (255, g);
	b = min (255, b);

	return RGB(BYTE(r),BYTE(g),BYTE(b));
}

// Rotate our vector around the X and Y axis
void CXMLControlDistantLight::RotateByXandY (double XRot, double YRot)
{   // Angles are in radians
	
	if (XRot == 0.0 && YRot == 0.0)
		return;
	
//	double length = m_dVec.length();

	double cx = cos(XRot);
	double sx = sin(XRot);
	double cy = cos(YRot);
	double sy = sin(YRot);
	
	double dx = m_dVec[0] * cy + m_dVec[1] * sx * sy + m_dVec[2] * cx * sy;
	double dy = m_dVec[1] * cx - m_dVec[2] * sx;
	double dz = -m_dVec[0] * sy + m_dVec[1] * sx * cy + m_dVec[2] * cx * cy;
	
	if (!m_bFrontVector || dz >= 0.0)  // Vector is bounds free
	{
		m_dVec[0] = dx;// * length;
		m_dVec[1] = dy;// * length;
		m_dVec[2] = dz;// * length;
	//	Normalize ();
	}
	else    // Otherwise, do not allow Z to be negative (light shines from behind)
	{
		m_dVec[0] = dx;
		m_dVec[1] = dy;
		m_dVec[2] = 0.0;
#if 0
		Normalize();
#endif
	}
}

#define EPS                                 1.0e-6                  // Epsilon

inline void SETPIXEL(RGBTRIPLE* p, COLORREF clr)
{
	p->rgbtRed = GetRValue(clr);
	p->rgbtGreen = GetGValue(clr);
	p->rgbtBlue = GetBValue(clr);
}

// virtual
void CXMLControlDistantLight::Draw(HDC hDC, CRect rect)
{
	CDCHandle dc(hDC);

	int m_iRadius = min(rect.Width(), rect.Height())/2;

	int m_iWidth = m_iRadius*2;
	int m_iHeight = m_iRadius*2;

	int m_iXCenter = m_iWidth/2;
	int m_iYCenter = m_iHeight/2;

	int m_iSqrRadius = m_iRadius * m_iRadius;

	int left = rect.left + (rect.Width()-m_iWidth)/2;
	int top = rect.top + (rect.Height()-m_iHeight)/2;

	gmVector3 dVec = m_dVec;
	dVec.normalize();

	LPBITMAPINFO m_lpbmi = (LPBITMAPINFO)GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPINFOHEADER));
	if (m_lpbmi)
	{
	// Allocate a bitmap just the size of the invalid clip rect
		m_lpbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_lpbmi->bmiHeader.biWidth = m_iWidth;
		m_lpbmi->bmiHeader.biHeight = -m_iWidth;
		m_lpbmi->bmiHeader.biBitCount = 24;
		m_lpbmi->bmiHeader.biPlanes = 1;

		HBITMAP hTBitmap;
		LPBYTE TBits = NULL;

		if (hTBitmap = CreateDIBSection(NULL, m_lpbmi, DIB_RGB_COLORS, (void**)&TBits, NULL, 0))
		{
			HDC hTDC = CreateCompatibleDC(NULL);
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(hTDC, hTBitmap);

			for (int y=0; y<m_iHeight; y++)   // Scan all rows
			{
				RGBTRIPLE* pixel = (RGBTRIPLE*)(TBits + ROWBYTES(m_iWidth, 24)*y);

				for (int x=0; x<m_iWidth; x++)  // Scan all columns
				{
					int xf = x-m_iXCenter;  // Find distance from center
					int yf = y-m_iYCenter;

					if (xf*xf + yf*yf <= m_iSqrRadius)    // Point on ball surface
					{
						double vx = double(xf) / double(m_iRadius);
						double vy = double(yf) / double(m_iRadius);
						double vz = sqrt (1.0 - vx*vx - vy*vy);     // Find ball's normal

						SETPIXEL(pixel, CalcLight(dVec, vx,vy,vz));
					}
					else
					{
						SETPIXEL(pixel, RGB(0,0,0));
					}

					pixel++;
				}
			}

			BitBlt(hDC, rect.left, rect.top, m_iWidth, m_iHeight, hTDC, 0, 0, SRCCOPY);

			SelectObject(hTDC, hOldBitmap);
			DeleteObject(hTBitmap);
			DeleteDC(hTDC);
		}
		GlobalFree(m_lpbmi);
	}
}

// virtual
BOOL CXMLControlDistantLight::Activate(HWND hParent, POINT point, CRect rect)
{
	m_iLastMouse = point;

	return TRUE;	// Drag
}

// virtual
void CXMLControlDistantLight::DoDrag(POINT point, CRect box)
{
	RotateByXandY(
		-double(point.y - m_iLastMouse.y) / m_dSensitivity,
		double(point.x - m_iLastMouse.x) / m_dSensitivity);
	
	m_iLastMouse = point;

	m_pSite->Redraw();

//	Fire_OnChanged(m_dVec[0], m_dVec[1], m_dVec[2]);

	m_pSite->OnControlValueChanged();
}

// virtual
void CXMLControlDistantLight::Deactivate()
{
}

double GetLineAngle(double x1, double y1, double x2, double y2);

//virtual
_variant_t CXMLControlDistantLight::GetProperty(BSTR name)
{
	/*
	if (!wcscmp(name, L"x"))
	{
		return _variant_t(m_dVec[0]);
	}
	else if (!wcscmp(name, L"y"))
	{
		return _variant_t(m_dVec[1]);
	}
	else if (!wcscmp(name, L"z"))
	{
		return _variant_t(m_dVec[2]);
	}
	else
	*/
	{
/*	double NL = dx * dVec[0] + dy * dVec[1] + dz * dVec[2], 
		RV = 2.0 * NL,
		rx = dVec[0] - (dx * RV),
		ry = dVec[1] - (dy * RV),
		rz = dVec[2] - (dz * RV);

	if (NL < 0.0)   // Diffuse coefficient
		NL = 0.0;

	RV = max (0.0, -rz);
*/
		if (!wcscmp(name, L"azimuth"))
		{
			double azimuth = GetLineAngle(0, 0, m_dVec[0], m_dVec[1]);

			WCHAR buf[32];
			swprintf(buf, L"%g", gmDegrees(azimuth));

			return _variant_t(buf);
		}
		else if (!wcscmp(name, L"elevation"))
		{
			double elevation = GetLineAngle(0, 0, m_dVec[1], m_dVec[2]);

			WCHAR buf[32];
			swprintf(buf, L"%g", gmDegrees(elevation));

			return _variant_t(buf);
		}
	}

	return _variant_t();
}

//

//virtual
HRESULT CXMLControlDistantLight::SetProperty(BSTR name, _variant_t value)
{
#if 0
	if (!wcscmp(name, L"azimuth"))
	{
		try
		{
			m_azimuth = getfnumber(_bstr_t(value));

			m_dVec[0] = cos(gmRadians(m_azimuth)) * cos(gmRadians(m_elevation));
	      m_dVec[1] = sin(gmRadians(m_azimuth)) * cos(gmRadians(m_elevation));
			m_dVec[2] = sin(gmRadians(m_elevation));
 //     Normalize ();
		}
		catch(_com_error& e)
		{
			return e.Error();
		}
	}
	else if (!wcscmp(name, L"elevation"))
	{
		try
		{
			m_elevation = getfnumber(_bstr_t(value));

			m_dVec[0] = cos(gmRadians(m_azimuth)) * cos(gmRadians(m_elevation));
	      m_dVec[1] = sin(gmRadians(m_azimuth)) * cos(gmRadians(m_elevation));
			m_dVec[2] = sin(gmRadians(m_elevation));
		}
		catch(_com_error& e)
		{
			return e.Error();
		}
	}
#endif

	m_pSite->Redraw();

	return S_OK;
}

#endif