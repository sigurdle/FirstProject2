#ifndef Web_PSVGFontElement_h
#define Web_PSVGFontElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGFontElement : public PSVGElement
{
public:
	CTOR PSVGFontElement(SVGFontElement* element) : PSVGElement(element)
	{
	}

	int FindGlyph(WCHAR* data, PSVGGlyphElement* *pVal);
	void FindMissingGlyph(PSVGGlyphElement* *pVal);

	double GetHorizOriginX()
	{
		ASSERT(0);
#if 0
		CComQIPtr<ILDOMElement> element = m_pNode;

		CComBSTR v;
		element->getAttribute(L"horiz-origin-x", &v);
		if (v.Length())
		{
			return getfnumber(v);
		}
		else
#endif
			return 0;
	}

	double GetHorizOriginY()
	{
		ASSERT(0);
#if 0
		CComQIPtr<ILDOMElement> element = m_pNode;

		CComBSTR v;
		element->getAttribute(L"horiz-origin-y", &v);
		if (v.Length())
		{
			return getfnumber(v);
		}
		else
#endif
			return 0;
	}

	double GetVertOriginX()
	{
		ASSERT(0);
#if 0
		CComQIPtr<ILDOMElement> element = m_pNode;

		CComBSTR v;
		element->getAttribute(L"vert-origin-x", &v);
		if (v.Length())
		{
			return getfnumber(v);
		}
		else
#endif
			return 0;
	}

	double GetVertOriginY()
	{
		ASSERT(0);
#if 0
		CComQIPtr<ILDOMElement> element = m_pNode;

		CComBSTR v;
		element->getAttribute(L"vert-origin-y", &v);
		if (v.Length())
		{
			return getfnumber(v);
		}
		else
#endif
			return 0;
	}

/// font-face
	double GetUnitsPerEm()
	{
		ASSERT(0);
#if 0
		PSVGElement* pFontFace = (PSVGElement*)GetElementByTagNameNS(L"http://www.w3.org/2000/svg", L"font-face", FALSE);
		if (pFontFace)
		{
			CComQIPtr<ILDOMElement> element = pFontFace->m_pNode;

			CComBSTR v;
			element->getAttribute(L"units-per-em", &v);
			if (v.Length())
			{
				return getfnumber(v);
			}
			else
				return 1000;
		}
#endif
		return 0;
	}

	double GetCapHeight()
	{
		ASSERT(0);
#if 0
		PSVGElement* pFontFace = (PSVGElement*)GetElementByTagNameNS(L"http://www.w3.org/2000/svg", L"font-face", FALSE);
		if (pFontFace)
		{
			CComQIPtr<ILDOMElement> element = pFontFace->m_pNode;

			CComBSTR v;
			element->getAttribute(L"cap-height", &v);
			if (v.Length())
			{
				return getfnumber(v);
			}
		}
#endif
		return 0;
	}

	double GetXHeight()
	{
		ASSERT(0);
#if 0
		PSVGElement* pFontFace = (PSVGElement*)GetElementByTagNameNS(L"http://www.w3.org/2000/svg", L"font-face", FALSE);
		if (pFontFace)
		{
			CComQIPtr<ILDOMElement> element = pFontFace->m_pNode;

			CComBSTR v;
			element->getAttribute(L"x-height", &v);
			if (v.Length())
			{
				return getfnumber(v);
			}
		}
#endif
		return 0;
	}

	double GetAscent()
	{
		ASSERT(0);
#if 0
		PSVGElement* pFontFace = (PSVGElement*)GetElementByTagNameNS(L"http://www.w3.org/2000/svg", L"font-face", FALSE);
		if (pFontFace)
		{
			CComQIPtr<ILDOMElement> element = pFontFace->m_pNode;

			CComBSTR v;
			element->getAttribute(L"ascent", &v);
			if (v.Length())
			{
				return getfnumber(v);
			}
		}
#endif
		return GetUnitsPerEm() - GetVertOriginY();
	}

	double GetDescent()
	{
		ASSERT(0);
#if 0
		PSVGElement* pFontFace = (PSVGElement*)GetElementByTagNameNS(L"http://www.w3.org/2000/svg", L"font-face", FALSE);
		if (pFontFace)
		{
			CComQIPtr<ILDOMElement> element = pFontFace->m_pNode;

			CComBSTR v;
			element->getAttribute(L"descent", &v);
			if (v.Length())
			{
				return getfnumber(v);
			}
		}
#endif
		return GetVertOriginY();
	}
};

}	// Web
}

#endif // Web_PSVGFontElement_h
