#include "stdafx.h"
#include "LXMLEditor.h"

#include "../LXML/cssunits.h"

namespace System
{
namespace LXmlEdit
{

#if 0

_bstr_t stripspaces(BSTR s);

long getnumber(BSTR* s);
double getfrac(BSTR *s);

double ParseValueUnitString(BSTR s, int* punitType)
{
	BSTR p = s;

// get sign
	int sign = 1;

	if ((*p == L'-') || (*p == L'+'))
	{
		if (*p == L'-') sign = -1;
		p++;
	}

// get number
	long integer = getnumber(&p);

// get fraction
	double fraction;
	if (*p == L'.' || *p == L',')
	{
		p++;
		fraction = getfrac(&p);
	}
	else
		fraction = 0;

	double specifiedValue = integer + fraction;
	if (sign == -1) specifiedValue = -specifiedValue;

	/*
	if (p[0] == L'p' && p[1] == L'x' && p[2] == 0)
		*punitType = CSS_PX;
		*/

	else if (p[0] == L'i' && p[1] == L'n' && p[2] == 0)
		*punitType = CSS_IN;

	else if (p[0] == L'm' && p[1] == L'm' && p[2] == 0)
		*punitType = CSS_MM;

	else if (p[0] == L'c' && p[1] == L'm' && p[2] == 0)
		*punitType = CSS_CM;

	else if (p[0] == L'p' && p[1] == L't' && p[2] == 0)
		*punitType = CSS_PT;

	else if (p[0] == L'p' && p[1] == L'c' && p[2] == 0)
		*punitType = CSS_PC;
/*
	else if (p[0] == L'p' && p[1] == L'c' && p[2] == 0)
		*punitType = CSS_EMS;

	else if (p[0] == L'e' && p[1] == L'm' && p[2] == 0)
		*punitType = CSS_EXS;
*/

	/*
	else if (p[0] == L'%' && p[1] == 0)
		*punitType = CSS_PERCENTAGE;
*/
	else if (p[0] == 0)
		*punitType = CSS_NUMBER;

	else
		*punitType = 0;//CSS_UNKNOWN; // ??

	return specifiedValue;
}

_bstr_t CreateValueUnitString(double specifiedValue, short unitType)
{
	WCHAR* unitstr;

	switch (unitType)
	{
//	case CSS_UNKNOWN:
	case CSS_NUMBER:		unitstr = L"";		break;

//	case CSS_PERCENTAGE:	unitstr = L"%";	break;
//	case CSS_EMS:			unitstr = L"em";	break;
//	case CSS_EXS:			unitstr = L"ex";	break;
//	case CSS_PX:			unitstr = L"px";	break;
	case CSS_CM:			unitstr = L"cm";	break;
	case CSS_MM:			unitstr = L"mm";	break;
	case CSS_IN:			unitstr = L"in";	break;
	case CSS_PT:			unitstr = L"pt";	break;
	case CSS_PC:			unitstr = L"pc";	break;
	}

	WCHAR str[64];
	swprintf(str, L"%g %s", specifiedValue, unitstr);

	return str;
}

double ConvertUserUnitToSpecifiedValue(double value, short unitType)
{
	HDC hDC = GetDC(NULL);
	double inchesPerPixel = GetDeviceCaps(hDC, LOGPIXELSX);
	ReleaseDC(NULL, hDC);

	switch (unitType)
	{
	case CSS_NUMBER:	return value; break;
	//case CSS_PX:		return value; break;
	case CSS_MM:		return value / (inchesPerPixel/25.4); break;
	case CSS_CM:		return value / (inchesPerPixel/2.54); break;
	case CSS_IN:		return value / (inchesPerPixel); break;
	case CSS_PT:		return value / (inchesPerPixel/72); break;
	case CSS_PC:		return value / (inchesPerPixel/72*12); break;

	//case CSS_EMS: break;
	//case CSS_EXS: break;

	//case CSS_PERCENTAGE:	break;
	default:
		return value;
	}

	return 0;
}

double ConvertSpecifiedValueToUserUnit(short unitType, double specifiedValue)
{
	HDC hDC = GetDC(NULL);
	double inchesPerPixel = GetDeviceCaps(hDC, LOGPIXELSX);
	ReleaseDC(NULL, hDC);

	switch (unitType)
	{
	case CSS_NUMBER:	return specifiedValue; break;
//	case UNIT_PX:		return specifiedValue; break;
	case CSS_MM:		return specifiedValue * (inchesPerPixel/25.4); break;
	case CSS_CM:		return specifiedValue * (inchesPerPixel/2.54); break;
	case CSS_IN:		return specifiedValue * (inchesPerPixel); break;
	case CSS_PT:		return specifiedValue * (inchesPerPixel/72); break;
	case CSS_PC:		return specifiedValue * (inchesPerPixel/72*12); break;
	//case CSS_EMS: break;
	//case CSS_EXS: break;
	}

	return 0;
}
#endif

double GetWindowTextValue(UI::Control* hWnd, bool* bTrans)
{
	ASSERT(0);
#if 0
	TCHAR buf[64];
	GetWindowText(hWnd, buf, sizeof(buf));
#endif
	System::StringW* bstr;// = _bstr_t(buf);
	bstr = stripspaces(bstr);

	if (bstr->Length() > 0)
	{
		int unitType;
		double specifiedValue = Web::ParseValueUnitString(bstr->c_str(), &unitType);
		if (unitType != 0)
		{
			if (bTrans) *bTrans = true;
			return Web::ConvertSpecifiedValueToUserUnit(unitType, specifiedValue);
		}
	}

	if (bTrans) *bTrans = false;
	return 0;
}

double GetDlgItemValue(UI::Control* hWnd, UINT nID, bool* bTrans)
{
	ASSERT(0);
#if 0
	return GetWindowTextValue(::GetDlgItem(hWnd, nID), bTrans);
#endif
	return 0;
}

void SetWindowTextValueCheckForSame(UI::Control* hWnd, double value, short unit)
{
	double specifiedValue = Web::ConvertUserUnitToSpecifiedValue(value, unit);
	System::StringW* bstr = Web::CreateValueUnitString(specifiedValue, unit);

	ASSERT(0);
#if 0
	TCHAR old[256];
	GetWindowText(hWnd, old, sizeof(old));
	if (wcscmp(bstr, _bstr_t(old)))
	{
		SetWindowText(hWnd, bstr);
	}
#endif
}

void SetWindowTextValue(UI::Control* hWnd, double value, short unit)
{
	ASSERT(0);
#if 0
	double specifiedValue = ConvertUserUnitToSpecifiedValue(value, unit);
	_bstr_t bstr = CreateValueUnitString(specifiedValue, unit);
	SetWindowText(hWnd, bstr);
#endif
}

void SetDlgItemValue(UI::Control* hWnd, UINT nID, double value, short unit)
{
	ASSERT(0);
#if 0
	double specifiedValue = ConvertUserUnitToSpecifiedValue(value, unit);
	_bstr_t bstr = CreateValueUnitString(specifiedValue, unit);
	SetDlgItemText(hWnd, nID, bstr);
#endif
}

double GetDlgItemAngle(UI::Control * hWnd, UINT nID, bool* bTrans)
{
	WCHAR buf[64];
	ASSERT(0);
#if 0
	GetDlgItemText(hWnd, nID, buf, sizeof(buf));
#endif

	if (bTrans) *bTrans = true;

	return getfnumber(buf);
}

void SetDlgItemAngle(UI::Control * hWnd, UINT nID, double value)
{
	ASSERT(0);
#if 0
	TCHAR buf[64];
	_stprintf(buf, _T("%g º"), value);
	SetDlgItemText(hWnd, nID, buf);
#endif
}

bool GetDlgItemIntX(UI::Control * hWnd, UINT nID, int minv, int maxv, int* pvalue)
{
	ASSERT(0);
#if 0
	BOOL pTranslated;
	int integer = GetDlgItemInt(hWnd, nID, &pTranslated, TRUE);

	if (!pTranslated || !(integer >= minv && integer <= maxv))
	{
		TCHAR msg[512];
		sprintf(msg, "Value must be between %d and %d", minv, maxv);
		MessageBox(hWnd, msg, "WebEditor", MB_OK);

		SendDlgItemMessage(hWnd, nID, EM_SETSEL, 0, -1);
		::SetFocus(GetDlgItem(hWnd, nID));

		return FALSE;
	}

	*pvalue = integer;
#endif
	return true;
}

}
}
