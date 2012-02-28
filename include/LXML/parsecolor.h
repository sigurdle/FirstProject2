#ifndef __PARSECOLOR_H_
#define __PARSECOLOR_H_

//#define RGBA(r,g,b,a)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))
//#define GetAValue(rgb)			 ((BYTE)((rgb)>>24))

namespace System
{
namespace Web
{

WEBEXT int ParseRGBColor(const WCHAR* p, const WCHAR** pp, Graphics::Color* pVal);
WEBEXT int ParseRGBAColor(const WCHAR* p, const WCHAR** pp, Graphics::Color* pVal);
WEBEXT int ParseSingleRGBAColor(const WCHAR* p, Graphics::Color* pVal);
WEBEXT CSSUnitType ParseColor(const WCHAR* p, const WCHAR** pp, Graphics::Color* pVal);

}
}

#endif // __PARSECOLOR_H_
