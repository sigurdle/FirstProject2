#include "stdafx.h"
#include "LSVG2.h"

//#include "PSVGFontElement.h"
#include "SVGFontElement.h"

#include "SVGGlyphElement.h"
#include "SVGMissingGlyphElement.h"

namespace System
{
namespace Web
{

void PSVGFontElement::FindMissingGlyph(PSVGGlyphElement* *pVal)
{
	ASSERT(0);
#if 0
	ASSERT(pVal != NULL);

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CPElement* pElement = (CPElement*)m_childList.GetNext(pos);

		CComQIPtr<ILSVGMissingGlyphElement> missingGlyphElement = pElement->m_pNode;
		if (missingGlyphElement)
		{
			*pVal = (CPSVGGlyphElement*)pElement;
			return;
		}
	}

	*pVal = NULL;
#endif
}

int PSVGFontElement::FindGlyph(WCHAR* data, PSVGGlyphElement* *pVal)
{
	ASSERT(0);
#if 0
	ASSERT(pVal != NULL);

	CComPtr<ILSVGMissingGlyphElement> m_missingGlyphElement;

	CComPtr<ILDOMNode> node;
	m_pNode->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILSVGGlyphElement> glyphElement = node;
		if (glyphElement)
		{
			CComBSTR unicode;
			glyphElement->getAttribute(L"unicode", &unicode);

			if (unicode.Length())
			{
				if (!wcsncmp(unicode, data, unicode.Length()))
				{
					for (int i = 0; i < static_cast<CLSVGGlyphElement*>(glyphElement.p)->m_pNodes.GetSize(); i++)
					{
						ASSERT(0);
#if 0
						if (static_cast<CLSVGGlyphElement*>(glyphElement.p)->m_pNodes[i]->m_pWindow == m_pWindow)
						{
							*pVal = (CPSVGGlyphElement*)static_cast<CLSVGGlyphElement*>(glyphElement.p)->m_pNodes[i];
							return unicode.Length();
						}
#endif
					}

					ASSERT(0);
				}
			}
		}
		else
		{
			if (m_missingGlyphElement == NULL)	// Use first encountered only ?
			{
			// Remember this, so we don't need to do a second pass if it turns out we need it
				CComQIPtr<ILSVGMissingGlyphElement> missingGlyphElement = node;
				if (missingGlyphElement)
				{
					m_missingGlyphElement = missingGlyphElement;
				}
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

// Use missing glyph
	if (m_missingGlyphElement)
	{
		ASSERT(0);
#if 0
		for (int i = 0; i < static_cast<CLSVGMissingGlyphElement*>(m_missingGlyphElement.p)->m_pNodes.GetSize(); i++)
		{
			ASSERT(0);
#if 0
			if (static_cast<CLSVGMissingGlyphElement*>(m_missingGlyphElement.p)->m_pNodes[i]->m_pWindow == m_pWindow)
			{
				*pVal = (CPSVGGlyphElement*)static_cast<CLSVGMissingGlyphElement*>(m_missingGlyphElement.p)->m_pNodes[i];
				return 1;
			}
#endif
		}
#endif
	}

	*pVal = NULL;
//	ASSERT(0);	// TODO remove
#endif
	return 1;
}

}	// LSVG
}
