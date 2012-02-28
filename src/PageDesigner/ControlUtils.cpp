#include "stdafx.h"
#include "PageDesigner.h"

long getnumber(BSTR* s);
double getfrac(BSTR *s);
_bstr_t stripspaces(BSTR s);

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
		*punitType = UNIT_IN;

	else if (p[0] == L'm' && p[1] == L'm' && p[2] == 0)
		*punitType = UNIT_MM;

	else if (p[0] == L'c' && p[1] == L'm' && p[2] == 0)
		*punitType = UNIT_CM;

	else if (p[0] == L'p' && p[1] == L't' && p[2] == 0)
		*punitType = UNIT_PT;

	else if (p[0] == L'p' && p[1] == L'c' && p[2] == 0)
		*punitType = UNIT_PC;
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
		*punitType = UNIT_NUMBER;

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
	case UNIT_NUMBER:		unitstr = L"";		break;

//	case CSS_PERCENTAGE:	unitstr = L"%";	break;
//	case CSS_EMS:			unitstr = L"em";	break;
//	case CSS_EXS:			unitstr = L"ex";	break;
//	case CSS_PX:			unitstr = L"px";	break;
	case UNIT_CM:			unitstr = L"cm";	break;
	case UNIT_MM:			unitstr = L"mm";	break;
	case UNIT_IN:			unitstr = L"in";	break;
	case UNIT_PT:			unitstr = L"pt";	break;
	case UNIT_PC:			unitstr = L"pc";	break;
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
	case UNIT_NUMBER:	return value; break;
	//case CSS_PX:		return value; break;
	case UNIT_MM:		return value / (inchesPerPixel/25.4); break;
	case UNIT_CM:		return value / (inchesPerPixel/2.54); break;
	case UNIT_IN:		return value / (inchesPerPixel); break;
	case UNIT_PT:		return value / (inchesPerPixel/72); break;
	case UNIT_PC:		return value / (inchesPerPixel/72*12); break;

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
	case UNIT_NUMBER:	return specifiedValue; break;
//	case UNIT_PX:		return specifiedValue; break;
	case UNIT_MM:		return specifiedValue * (inchesPerPixel/25.4); break;
	case UNIT_CM:		return specifiedValue * (inchesPerPixel/2.54); break;
	case UNIT_IN:		return specifiedValue * (inchesPerPixel); break;
	case UNIT_PT:		return specifiedValue * (inchesPerPixel/72); break;
	case UNIT_PC:		return specifiedValue * (inchesPerPixel/72*12); break;
	//case CSS_EMS: break;
	//case CSS_EXS: break;
	}

	return 0;
}

double GetWindowTextValue(HWND hWnd, BOOL* bTrans)
{
	TCHAR buf[64];
	GetWindowText(hWnd, buf, sizeof(buf));

	_bstr_t bstr = _bstr_t(buf);
	bstr = stripspaces((BSTR)bstr);

	if (bstr.length() > 0)
	{
		int unitType;
		double specifiedValue = ParseValueUnitString((BSTR)bstr, &unitType);
		if (unitType != 0)
		{
			if (bTrans) *bTrans = TRUE;
			return ConvertSpecifiedValueToUserUnit(unitType, specifiedValue);
		}
	}

	if (bTrans) *bTrans = FALSE;
	return 0;
}

double GetDlgItemValue(HWND hWnd, UINT nID, BOOL* bTrans)
{
	return GetWindowTextValue(::GetDlgItem(hWnd, nID), bTrans);
}

void SetWindowTextValueCheckForSame(HWND hWnd, double value, short unit)
{
	double specifiedValue = ConvertUserUnitToSpecifiedValue(value, unit);
	_bstr_t bstr = CreateValueUnitString(specifiedValue, unit);

	TCHAR old[256];
	GetWindowText(hWnd, old, sizeof(old));
	if (wcscmp(bstr, _bstr_t(old)))
	{
		SetWindowText(hWnd, bstr);
	}
}

void SetWindowTextValue(HWND hWnd, double value, short unit)
{
	double specifiedValue = ConvertUserUnitToSpecifiedValue(value, unit);
	_bstr_t bstr = CreateValueUnitString(specifiedValue, unit);
	SetWindowText(hWnd, bstr);
}

void SetDlgItemValue(HWND hWnd, UINT nID, double value, short unit)
{
	double specifiedValue = ConvertUserUnitToSpecifiedValue(value, unit);
	_bstr_t bstr = CreateValueUnitString(specifiedValue, unit);
	SetDlgItemText(hWnd, nID, bstr);
}

double GetDlgItemAngle(HWND hWnd, UINT nID, BOOL* bTrans)
{
	TCHAR buf[64];
	GetDlgItemText(hWnd, nID, buf, sizeof(buf));

	if (bTrans) *bTrans = TRUE;

	return atof(buf);
}

void SetDlgItemAngle(HWND hWnd, UINT nID, double value)
{
	TCHAR buf[64];
	_stprintf(buf, _T("%g º"), value);
	SetDlgItemText(hWnd, nID, buf);
}
