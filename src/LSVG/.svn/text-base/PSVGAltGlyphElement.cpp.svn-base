#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGAltGlyphElement.h"
#include "SVGAltGlyphElement.h"

#include "PSVGGlyphElement.h"
#include "SVGGlyphElement.h"

#include "PSVGFontElement.h"
#include "SVGFontElement.h"

//#include "LHTMLWindow.h"
//#include "LXMLDocumentView.h"

namespace System
{
namespace Web
{

void DrawPathSegList(SVGPathSegList* seglist, Gui::Geometry* path, SVGMatrix* matrix);

PSVGAltGlyphElement::PSVGAltGlyphElement(SVGAltGlyphElement* element) : PSVGTextPositioningElement(element)
{
}

/*
//virtual
LDraw::Matrix3d* PSVGAltGlyphElement::GetLocalAnimatedMatrix()
{
	SVGAltGlyphElement* psvgElement = static_cast<SVGAltGlyphElement*>(m_pNode);
	return psvgElement->m_transform->m_animVal->consolidateToMatrix();
}
*/

//virtual
void PSVGAltGlyphElement::CalculateDimensions(CHTMCalcContext* pC)
{
	SVGAltGlyphElement* psvgElement = static_cast<SVGAltGlyphElement*>(m_pNode);

	ASSERT(0);
#if 0

	CComBSTR href;
	psvgElement->getAttributeNS(L"http://www.w3.org/1999/xlink", L"href", &href);
	if (href.Length()
	{
		if (((BSTR)href)[0] == L'#')
		{
			BSTR uri = &((BSTR)href)[1];

			CPElement* pElement = m_pWindow->m_htmTree->GetElementById(uri);
			if (pElement)
			{
				CComQIPtr<ILSVGGlyphElement> glyphElement = pElement->m_pNode;
				if (glyphElement)
				{
				}
				else
				{
					CComQIPtr<ILSVGAltGlyphDefElement> altGlyphDefElement = pElement->m_pNode;
					if (altGlyphDefElement)
					{
						UPOSITION pos = pElement->m_childList.GetHeadPosition();
						while (pos)
						{
							CPElement* pChildElement = (CPElement*)pElement->m_childList.GetNext(pos);

							CComQIPtr<ILSVGGlyphRefElement> glyphRefElement = pChildElement->m_pNode;
							if (glyphRefElement)
							{
								CComBSTR href;
								glyphRefElement->getAttributeNS(L"http://www.w3.org/1999/xlink", L"href", &href);
								if (href.Length())
								{
									if (((BSTR)href)[0] == L'#')
									{
										BSTR uri = &((BSTR)href)[1];
										CPElement* pUriElement = m_pWindow->m_htmTree->GetElementById(uri);

										if (pUriElement)
										{
											CComQIPtr<ILSVGGlyphElement> glyphElement = pUriElement->m_pNode;
											if (glyphElement)
											{
												CLSVGGlyphElement* psvgGlyphElement = static_cast<CLSVGGlyphElement*>(glyphElement.p);

												CPSVGFontElement* pSVGFont = (CPSVGFontElement*)pUriElement->m_parent;
												CLSVGFontElement* psvgFontElement = static_cast<CLSVGFontElement*>(pSVGFont->m_pNode);

												double scale = m_parent->m_computedFontSize / pSVGFont->GetUnitsPerEm();

												CGlyph* pGlyph = new CGlyph;

												pGlyph->m_seglist = psvgGlyphElement->m_d->m_value->m_value->m_normalizedseglist;
												pGlyph->m_seglist->AddRef();

												if (psvgGlyphElement->m_horiz_adv_x->m_specified)
													pGlyph->m_charWidth = psvgGlyphElement->m_horiz_adv_x->m_value->m_value->m_value;
												else
													pGlyph->m_charWidth = psvgFontElement->m_horiz_adv_x->m_value->m_value->m_value;

												pGlyph->m_charWidth *= scale;

												DrawPathSegList(pGlyph->m_seglist, &pGlyph->m_GraphicsPathF, NULL);

												m_glyphs.Add(pGlyph);
											}
										}
									}
								}
								else
								{
									// TODO
								}
							}
						}

						CGlyph* pGlyph = new CGlyph;
						m_glyphs.Add(pGlyph);

						return;
					}
				}
			}
		}
	}

	CPSVGTextContentElement::CalculateDimensions(pC);

#if 0
#if 0	// Had this
	m_pFont = m_pFrame->AddFont(m_computedFontFamily, m_computedFontSize, 0);
#endif

	RemoveChildren();

#if 0
	_bstr_t href = psvgElement->m_href->m_animated->m_animVal->m_value.m_value;
	if (href.length())
	{
		if (((BSTR)href)[0] == L'#')
		{
			BSTR id = &((BSTR)href)[1];

			CPElement* pPElement = m_pWindow->m_htmTree->GetElementById(id);
			if (pPElement)
			{
				CComQIPtr<ILDOMElement> element = pPElement->m_pNode;

				CComBSTR textContent;
				element->get_textContent(&textContent);

				if (textContent.Length())
				{
					// Not really a text node
					CComObject<CPSVGText>* pText;
					CComObject<CPSVGText>::CreateInstance(&pText);
					pText->AddRef();

					pText->m_parent = this;
					m_childList.AddTail(pText);

					pText->CalculateTextDimensions(pC, textContent, textContent.Length());
				}
			}
		}
	}
#endif
#endif
#endif
}

}
}
