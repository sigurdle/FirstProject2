#ifndef Web_CSSUnits_h
#define Web_CSSUnits_h

namespace System
{
namespace Web
{

WEBEXT double ParseValueUnitString(const WCHAR* s, int* punitType);
WEBEXT CSSUnitType ParseValueUnitString(const WCHAR* s, const WCHAR** pp, double *pspecifiedValue);
WEBEXT String CreateValueUnitString(double specifiedValue, short unitType);
WEBEXT double ConvertUserUnitToSpecifiedValue(double value, short unitType);
WEBEXT double ConvertSpecifiedValueToUserUnit(short unitType, double specifiedValue/*, double percentageOf*/);
//double GetCSSValue(BSTR buf, BOOL* bTrans = NULL);

WEBEXT double ParseAngleUnitString(const WCHAR* s, int* punitType);
WEBEXT String CreateAngleUnitString(double specifiedValue, short unitType);
WEBEXT double ConvertDegreesToSpecifiedValue(double value, short unitType);
WEBEXT double ConvertSpecifiedValueToDegrees(short unitType, double specifiedValue);

}	// Web
}

#endif // Web_CSSUnits_h
