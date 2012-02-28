#include "stdafx.h"
#include "LXML.h"

//#include "parsenumber.h"
//#include "parsestring.h"

namespace System
{
namespace Web
{

WEBEXT CSSUnitType ParseValueUnitString(const WCHAR* s, const WCHAR** pp, double *pspecifiedValue)
{
	const WCHAR* p = s;

	double specifiedValue = getfnumber(&p);
	if (p == NULL)
	{
		if (pp)
			*pp = p;
		return CSS_UNKNOWN;
	}

	CSSUnitType unitType;

	if (p[0] == L'p' && p[1] == L'x')
	{
		unitType = CSS_PX;
		p += 2;
	}
	else if (p[0] == L'i' && p[1] == L'n')
	{
		unitType = CSS_IN;
		p += 2;
	}
	else if (p[0] == L'm' && p[1] == L'm')
	{
		unitType = CSS_MM;
		p += 2;
	}
	else if (p[0] == L'c' && p[1] == L'm')
	{
		unitType = CSS_CM;
		p += 2;
	}
	else if (p[0] == L'p' && p[1] == L't')
	{
		unitType = CSS_PT;
		p += 2;
	}
	else if (p[0] == L'p' && p[1] == L'c')
	{
		unitType = CSS_PC;
		p += 2;
	}
	else if (p[0] == L'e' && p[1] == L'm')
	{
		unitType = CSS_EMS;
		p += 2;
	}
	else if (p[0] == L'e' && p[1] == L'x')
	{
		unitType = CSS_EXS;
		p += 2;
	}
	else if (p[0] == L'%')
	{
		unitType = CSS_PERCENTAGE;
		p += 1;
	}
	else// if (p[0] == 0)
	{
		unitType = CSS_NUMBER;
	}
/*
	else
		unitType = CSS_UNKNOWN; // ??
*/

	if (pp)
		*pp = p;

	if (pspecifiedValue)
		*pspecifiedValue = specifiedValue;

	return unitType;
}

// Parse a CSS/SVG length value, with optional blank space on either side
WEBEXT double ParseValueUnitString(const WCHAR* s, int* punitType)
{
	ASSERT(s != NULL);

	const WCHAR* p = s;

	while (*p == L' ') p++;// Skip spaces

	double specifiedValue;
	*punitType = ParseValueUnitString(p, &p, &specifiedValue);
	if (p == NULL)
	{
		*punitType = CSS_UNKNOWN;
		return 0;
	}

	while (*p == L' ') p++;// Skip spaces

	if (*p != 0)	// must be null-terminated
	{
		*punitType = CSS_UNKNOWN;
		return 0;
	}

	return specifiedValue;

#if 0
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
	if (*p == L'.')
	{
		p++;
		fraction = getfrac(&p);
	}
	else
		fraction = 0;

	double specifiedValue = integer + fraction;
	if (sign == -1) specifiedValue = -specifiedValue;

	if (p[0] == L'p' && p[1] == L'x' && p[2] == 0)
		*punitType = CSS_PX;

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

	else if (p[0] == L'e' && p[1] == L'm' && p[2] == 0)
		*punitType = CSS_EMS;

	else if (p[0] == L'e' && p[1] == L'x' && p[2] == 0)
		*punitType = CSS_EXS;

	else if (p[0] == L'%' && p[1] == 0)
		*punitType = CSS_PERCENTAGE;

	else if (p[0] == 0)
		*punitType = CSS_NUMBER;

	else
		*punitType = CSS_UNKNOWN; // ??

	return specifiedValue;
#endif
}

WEBEXT String CreateValueUnitString(double specifiedValue, short unitType)
{
	WCHAR* unitstr;

	switch (unitType)
	{
	case CSS_UNKNOWN:
	case CSS_NUMBER:		unitstr = L"";		break;

	case CSS_PERCENTAGE:	unitstr = L"%";	break;
	case CSS_EMS:			unitstr = L"em";	break;
	case CSS_EXS:			unitstr = L"ex";	break;
	case CSS_PX:			unitstr = L"px";	break;
	case CSS_CM:			unitstr = L"cm";	break;
	case CSS_MM:			unitstr = L"mm";	break;
	case CSS_IN:			unitstr = L"in";	break;
	case CSS_PT:			unitstr = L"pt";	break;
	case CSS_PC:			unitstr = L"pc";	break;
	}

	WCHAR str[64];
	swprintf_s(str, L"%g%s", specifiedValue, unitstr);

	return string_copy(str);
}

WEBEXT double ParseAngleUnitString(StringVariant::const_iterator<WCHAR> s, int* punitType)
{
	ASSERT(0);
	return 0;
#if 0
	const WCHAR* p = s;

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
	if (*p == L'.')
	{
		p++;
		fraction = getfrac(&p);
	}
	else
		fraction = 0;

	double specifiedValue = integer + fraction;
	if (sign == -1) specifiedValue = -specifiedValue;

	if (p[0] == L'd' && p[1] == L'e' && p[2] == L'g' && p[3] == 0)
		*punitType = SVG_ANGLETYPE_DEG;

	else if (p[0] == L'r' && p[1] == L'a' && p[2] == L'd' && p[3] == 0)
		*punitType = SVG_ANGLETYPE_RAD;

	else if (p[0] == L'g' && p[1] == L'r' && p[2] == L'a' && p[3] == L'd' && p[4] == 0)
		*punitType = SVG_ANGLETYPE_GRAD;

	else if (p[0] == 0)
		*punitType = SVG_ANGLETYPE_UNSPECIFIED;

	else
		*punitType = SVG_ANGLETYPE_UNKNOWN; // ??

	return specifiedValue;
#endif
}

WEBEXT String CreateAngleUnitString(double specifiedValue, short unitType)
{
	WCHAR* unitstr;

	switch (unitType)
	{
	case SVG_ANGLETYPE_UNKNOWN:
	case SVG_ANGLETYPE_UNSPECIFIED:	unitstr = L"";		break;

	case SVG_ANGLETYPE_DEG:		unitstr = L"deg";	break;
	case SVG_ANGLETYPE_RAD:		unitstr = L"rad";	break;
	case SVG_ANGLETYPE_GRAD:	unitstr = L"grad";	break;
	}

	WCHAR str[64];
	swprintf_s(str, L"%g%s", specifiedValue, unitstr);

	return string_copy(str);
}

/*
Note: CSSUnitType and SVGLengthType have the same enumeration for

UNKNOWN = 0
NUMBER	= 1,
PERCENTAGE	= 2,
EMS	= 3,
EXS	= 4,
PX	= 5,
CM	= 6,
MM	= 7,
IN	= 8,
PT	= 9,
PC	= 10
*/

/*
Absolute length units are only useful when the physical properties of the output medium are known. The absolute units are: 

in: inches -- 1 inch is equal to 2.54 centimeters.  (25.4 millimeters). 
cm: centimeters 
mm: millimeters 
pt: points -- the points used by CSS2 are equal to 1/72th of an inch. 
pc: picas -- 1 pica is equal to 12 points. 
*/

WEBEXT double ConvertUserUnitToSpecifiedValue(double value, short unitType)
{
	// TODO
#if 0//_WINDOWS
	HDC hDC = GetDC(NULL);
	double pixelsPerInch = GetDeviceCaps(hDC, LOGPIXELSX);
	ReleaseDC(NULL, hDC);
#else
	double pixelsPerInch = 96;
#endif

	switch (unitType)
	{
	case CSS_NUMBER:	return value; break;
	case CSS_PX:		return value/* / (pixelsPerInch/90)*/; break;
	case CSS_MM:		return value / (pixelsPerInch/25.4); break;
	case CSS_CM:		return value / (pixelsPerInch/2.54); break;
	case CSS_IN:		return value / (pixelsPerInch); break;
	case CSS_PT:		return value / (pixelsPerInch/72); break;
	case CSS_PC:		return value / (pixelsPerInch/72*12); break;

	case CSS_EMS: break;
	case CSS_EXS: break;

	case CSS_PERCENTAGE:	break;
	}

	return 0;
}

WEBEXT double ConvertSpecifiedValueToUserUnit(short unitType, double specifiedValue/*, double percentageOf*/)
{
	// TODO
#if 0//_WINDOWS
	HDC hDC = GetDC(NULL);
	double pixelsPerInch = GetDeviceCaps(hDC, LOGPIXELSX);
	ReleaseDC(NULL, hDC);
#else
	double pixelsPerInch = 96;
#endif

	switch (unitType)
	{
	case CSS_NUMBER:	return specifiedValue; break;
	case CSS_PX:		return specifiedValue/* * (pixelsPerInch/90)*/; break;
	case CSS_MM:		return specifiedValue * (pixelsPerInch/25.4); break;
	case CSS_CM:		return specifiedValue * (pixelsPerInch/2.54); break;
	case CSS_IN:		return specifiedValue * (pixelsPerInch); break;
	case CSS_PT:		return specifiedValue * (pixelsPerInch/72); break;
	case CSS_PC:		return specifiedValue * (pixelsPerInch/72*12); break;
	case CSS_EMS: break;
	case CSS_EXS: break;
/*
	case CSS_PERCENTAGE:
		return percentageOf * specifiedValue / 100;
		break;
*/
	}

	return 0;
}

#if 0//_WINDOWS
double GetCSSValue(BSTR buf, BOOL* bTrans)
{
	//_bstr_t bstr = _bstr_t(buf);
	_bstr_t bstr = stripspaces(buf/*(BSTR)bstr*/);

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
#endif

WEBEXT double ConvertDegreesToSpecifiedValue(double value, short unitType)
{
	switch (unitType)
	{
	case SVG_ANGLETYPE_UNSPECIFIED:
	case SVG_ANGLETYPE_DEG:				return value; break;

	case SVG_ANGLETYPE_RAD:				return value * (M_PI/180); break;

	case SVG_ANGLETYPE_GRAD:			return value * ((double)400/360); break;

	default:
		ASSERT(0);
	}

	return 0;
}

WEBEXT double ConvertSpecifiedValueToDegrees(short unitType, double specifiedValue/*, double percentageOf*/)
{
	switch (unitType)
	{
	case SVG_ANGLETYPE_UNSPECIFIED:
	case SVG_ANGLETYPE_DEG:				return specifiedValue; break;

	case SVG_ANGLETYPE_RAD:				return specifiedValue * (180/M_PI); break;

	case SVG_ANGLETYPE_GRAD:			return specifiedValue * ((double)360/400); break;

	case SVG_ANGLETYPE_UNKNOWN:		return 0; break;

	default:
		ASSERT(0);
	}

	return 0;
}

}	// Web
}
