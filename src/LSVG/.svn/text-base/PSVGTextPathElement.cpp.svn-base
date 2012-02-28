#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGTextPathElement.h"
#include "SVGTextPathElement.h"

//#include "PSVGMaskElement.h"
//#include "PSVGFilterElement.h"

#include "SVGPathElement.h"

namespace System
{
namespace Web
{

void DrawPathSegList(SVGPathSegList* seglist, LDraw::GraphicsPathF* path, SVGMatrix* matrix);
void GetPathSegListBBox(SVGPathSegList* seglist, SVGMatrix* matrix, LDraw::RectD* bbox);

PSVGTextPathElement::PSVGTextPathElement(SVGTextPathElement* element) : PSVGTextContentElement(element)
{
	m_pPathElement = NULL;
}

/*
//virtual
LDraw::Matrix3d* PSVGTextPathElement::GetLocalAnimatedMatrix()
{
	SVGTextPathElement* psvgElement = static_cast<SVGTextPathElement*>(m_pNode);

	LDraw::Matrix3d* matrix = psvgElement->m_transform->m_animVal->consolidateToMatrix();
	matrix = *matrix * *m_animateMotionMatrix;

	return matrix;
}
*/

void PSVGTextPathElement::AlignToPath(PSVGTextContentElement* pElement, SVGPathSegList* pSegList)
{
	ASSERT(0);
#if 0
	UPOSITION pos = pElement->m_childList.GetHeadPosition();
	while (pos)
	{
		CPNode* pNode = (CPNode*)pElement->m_childList.GetNext(pos);
		if (pNode->m_type == LNODE_ELEMENT)
		{
			ASSERT(0);
#if 0
			CComQIPtr<ILSVGTextContentElement> textContent = pNode->m_pNode;
			if (textContent)
			{
				CPSVGTextContentElement* pSVGTextContent = (CPSVGTextContentElement*)pNode;

				AlignToPath(pSVGTextContent, pSegList);
			}
#endif
		}
		else
		{
			CPSVGText* pTextNode = (CPSVGText*)pNode;

			for (int i = 0; i < pTextNode->m_glyphs.GetSize(); i++)
			{
				CGlyph* pGlyph = pTextNode->m_glyphs[i];

			// Get position
				double x, y;
				pSegList->getPointOnLength(pGlyph->m_position.X, &x, &y, NULL);

			// Get rotation
				double x2, y2;
				double rotation;
				pSegList->getPointOnLength(pGlyph->m_position.X+pGlyph->m_charWidth/2, &x2, &y2, &rotation);

				gmMatrix3 mat =	gmMatrix3::translate(-x, -y+pGlyph->m_position.Y) *
										gmMatrix3::rotate(rotation) *
										gmMatrix3::translate(x, y);

				gmVector2 v = mat.transform(gmVector2(x, y));

				pGlyph->m_position.X = v[0];
				pGlyph->m_position.Y = v[1];
				pGlyph->m_rotation += rotation;
			}
		}
	}
#endif
}

// virtual
void PSVGTextPathElement::ReferenceInvalid(PElementBase/*PSVGElement*/ * pPElement)
{
	if (pPElement == m_pPathElement)
	{
		m_pPathElement = NULL;
	// TODO
	}
	else
	{
		PSVGElement::ReferenceInvalid(pPElement);
	}
}

PSVGElement* PSVGTextPathElement::GetHrefPathElement()
{
	ASSERT(0);
#if 0
	SVGTextPathElement* psvgElement = static_cast<SVGTextPathElement*>(m_pNode);

	_bstr_t href = psvgElement->m_href->m_animated->m_animVal->m_value;
	if (href.length())
	{
		if (((BSTR)href)[0] == L'#')
		{
			BSTR id = &((BSTR)href)[1];
			CPElement* pPElement = m_pWindow->m_htmTree->GetElementById(id);
			if (pPElement)
			{
				CComQIPtr<ILSVGPathElement> pathElement = pPElement->m_pNode;
				if (pathElement)
				{
					return (PSVGElement*)pPElement;
				}
			}
		}
	}
#endif
	return NULL;
}

// virtual
void PSVGTextPathElement::LayoutText(TextLayoutContext* /*tlc*/, bool /*bDoX*/, bool /*bDoY*/)
{
	ASSERT(0);
#if 0
// Remove reference to old path element
	if (m_pPathElement)
	{
		UPOSITION pos = m_pPathElement->m_referencingElements.Find(this);
		ASSERT(pos);
		m_pPathElement->m_referencingElements.RemoveAt(pos);
	}

// Get referenced path element
	SVGTextPathElement* psvgElement = static_cast<SVGTextPathElement*>(m_pNode);

	m_pPathElement = GetHrefPathElement();
	if (m_pPathElement)
	{
		m_pPathElement->m_referencingElements.AddTail(this);

		CComQIPtr<ILSVGPathElement> pathElement = m_pPathElement->m_pNode;
		CLSVGPathElement* pPathElement = static_cast<CLSVGPathElement*>(pathElement.p);

		CComObject<SVGPathSegList>* pSegList = pPathElement->m_d->m_animated->m_animVal->m_value->m_normalizedseglist;
		ASSERT(pSegList);

		double startOffsetValue;
		if (psvgElement->m_startOffset->m_animated->m_animVal->m_value->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
		{
			double pathLength;
			pSegList->getLength(&pathLength);

			startOffsetValue = pathLength * psvgElement->m_startOffset->m_animated->m_animVal->m_value->m_valueInSpecifiedUnits / 100;
		}
		else
		{
			psvgElement->m_startOffset->m_animated->m_animVal->m_value->get_value(&startOffsetValue);
		}

	// First layout the text on a horizontal line
		CTextLayoutContext tlc;
		tlc.curpos.X = startOffsetValue;
		tlc.curpos.Y = 0;

		CPSVGTextContentElement::LayoutText(&tlc, true/*x*/, false/*y*/);

	// Then align the text along the path
		AlignToPath(this, pSegList);
	}
#endif
}

//virtual
void PSVGTextPathElement::CalculateBounds()
{
	PSVGElement::FreeCachedBitmap();

	LayoutText(NULL, 0, 0);	// ??
}

}	// w3c
}
