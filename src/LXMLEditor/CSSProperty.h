#pragma once

namespace System
{

enum
{
	CSSType_Unknown = 0,
	CSSType_Length,
	CSSType_Number,
	CSSType_String,
	CSSType_Uri,
	CSSType_Color,
	CSSType_Enum,
	CSSType_SVGColor,
	CSSType_SVGPaint
};

class CSSProperty
{
public:
	WCHAR* m_name;
	int m_category;
	bool	m_bInherited;
	WCHAR* m_initialCSS;

	struct
	{
		short m_type;
		WCHAR* m_enums;
		UINT m_nResource;
		double m_numberMinValue;
		double m_numberMaxValue;
		double m_numberScale;
	}
	d;
};

#define TYPE_URI()	{CSSType_Uri}
#define TYPE_COLOR()	{CSSType_Color}
#define TYPE_LENGTH()	{CSSType_Length}
#define TYPE_STRING()	{CSSType_String}
#define TYPE_ENUM(enums) {CSSType_Enum, enums, 0}
#define TYPE_ENUM_IMAGE(enums, nResource) {CSSType_Enum, enums, nResource}
#define TYPE_NUMBER(minValue, maxValue, scale) {CSSType_Number, NULL, 0, minValue, maxValue, scale}
#define TYPE_SVGCOLOR()	{CSSType_SVGColor}
#define TYPE_SVGPAINT()	{CSSType_SVGPaint}

extern CSSProperty CSSProperties[];
extern int g_nCSSProperties;

int GetCSSPropertyIndex(const WCHAR* propertyName);

}
