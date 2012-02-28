#include "stdafx.h"
#include "LSVG2.h"
#include "PSVGTextPositioningElement.h"
#include "SVGTextElement.h"
#include "PSVGFilterElement.h"

namespace System
{
namespace Web
{

void TextLayoutContext::AlignChunk(PElementBase* pPElement)
{
	// Align
	if (pPElement->m_computedTextAnchor == TextAnchor_end)
	{
		double dx = initialPos.X - curpos.X;

		for (int i = 0; i < chunk.GetSize(); i++)
		{
			chunk[i]->m_position.X += dx;
		}
	}
	else if (pPElement->m_computedTextAnchor == TextAnchor_middle)
	{
		double dx = (initialPos.X - curpos.X)/2;

		for (int i = 0; i < chunk.GetSize(); i++)
		{
			chunk[i]->m_position.X += dx;
		}
	}

	chunk.RemoveAll();
}

////////////////////////////////////////////////////////////////////////////////////
// CPSVGTextPositioningElement

void PSVGElement::LayoutGlyphs(vector<CGlyph*>& glyphs, TextLayoutContext* tlc, bool bDoX, bool bDoY, double& minx, double& miny, double& maxx, double& maxy)
{
	PSVGElement* pViewportElement = GetViewportElement();
	ASSERT(pViewportElement);

	gm::RectD viewBox = pViewportElement->GetViewBox();

	for (int i = 0; i < glyphs.GetSize(); i++)
	{
		int n;

	// x
		if (bDoX)
		{
			n = m_nCharCount;
			PSVGElement* pElement = this;
			do
			{
				SVGTextPositioningElementImpl* posText = dynamic_cast<SVGTextPositioningElementImpl*>(pElement->m_pNode);//pTextPosElement->m_pNode;

				if (posText)
				{
					//CLSVGTextElement* psvgElement = static_cast<CLSVGTextElement*>(posText.p);

					SVGLengthList* x = posText->get_x()->get_animVal();//(m_animated->m_animVal->m_value;

					uint numberOfItems = x->get_numberOfItems();
					if ((n+i) < numberOfItems)
					{
						tlc->AlignChunk(pElement);

						double value = LengthToUserUnits(x->getItem(n+i), viewBox.Width);
						//x->m_items[n+i]->get_value(&value);
						
						tlc->curpos.X = value;
						tlc->initialPos.X = value;
						break;
					}
				}

				if (pElement->m_parent == NULL) break;
				SVGElement* parentText = dynamic_cast<SVGElement*>(pElement->m_parent->m_pNode);
				if (parentText == NULL)
					break;

				pElement = (PSVGElement*)pElement->m_parent;

				n += pElement->m_nCharCount;
			}
			while (1);
		}

	// y
		if (bDoY)
		{
			n = m_nCharCount;

			PSVGElement* pElement = this;

			do
			{
				SVGTextPositioningElementImpl* posText = dynamic_cast<SVGTextPositioningElementImpl*>(pElement->m_pNode);//pTextPosElement->m_pNode;

				if (posText)
				{
					//CLSVGTextElement* psvgElement = static_cast<CLSVGTextElement*>(posText.p);

					SVGLengthList* y = posText->get_y()->get_animVal();

					uint numberOfItems = y->get_numberOfItems();
					if ((n+i) < numberOfItems)
					{
						tlc->AlignChunk(pElement);

						double value = LengthToUserUnits(y->getItem(n+i), viewBox.Height);
						//y->m_items[n+i]->get_value(&value);
						tlc->curpos.Y = value;
						tlc->initialPos.Y = value;
						break;
					}
				}

				if (pElement->m_parent == NULL) break;
				SVGElement* parentText = dynamic_cast<SVGElement*>(pElement->m_parent->m_pNode);
				if (parentText == NULL)
					break;

				pElement = (PSVGElement*)pElement->m_parent;

				n += pElement->m_nCharCount;
			}
			while (1);
		}

	// dx
		{
			n = m_nCharCount;
			PSVGElement* pElement = this;
			do
			{
				SVGTextPositioningElementImpl* posText = dynamic_cast<SVGTextPositioningElementImpl*>(pElement->m_pNode);//pTextPosElement->m_pNode;

				if (posText)
				{
					//CLSVGTextElement* psvgElement = static_cast<CLSVGTextElement*>(posText.p);

					SVGLengthList* dx = posText->get_dx()->get_animVal();

					uint numberOfItems = dx->get_numberOfItems();
					if ((n+i) < numberOfItems)
					{
						double value = LengthToUserUnits(dx->getItem(n+i), viewBox.Width);;
						//dx->m_items[n+i]->get_value(&value);
						tlc->curpos.X += value;
						break;
					}
				}

				if (pElement->m_parent == NULL) break;
				SVGElement* parentText = dynamic_cast<SVGElement*>(pElement->m_parent->m_pNode);
				if (parentText == NULL)
					break;

				pElement = (PSVGElement*)pElement->m_parent;

				n += pElement->m_nCharCount;
			}
			while (1);
		}

	// dy
		{
			n = m_nCharCount;
			PSVGElement* pElement = this;
			do
			{
				SVGTextPositioningElementImpl* posText = dynamic_cast<SVGTextPositioningElementImpl*>(pElement->m_pNode);//pTextPosElement->m_pNode;

				if (posText)
				{
					//CLSVGTextElement* psvgElement = static_cast<CLSVGTextElement*>(posText.p);

					SVGLengthList* dy = posText->get_dy()->get_animVal();

					uint numberOfItems = dy->get_numberOfItems();
					if ((n+i) < numberOfItems)
					{
						double value = LengthToUserUnits(dy->getItem(n+i), viewBox.Width);;
						//dy->m_items[n+i]->get_value(&value);
						tlc->curpos.Y += value;
						break;
					}
				}

				if (pElement->m_parent == NULL) break;
				SVGElement* parentText = dynamic_cast<SVGElement*>(pElement->m_parent->m_pNode);
				if (parentText == NULL)
					break;

				pElement = (PSVGElement*)pElement->m_parent;

				n += pElement->m_nCharCount;
			}
			while (1);
		}

		CGlyph* pGlyph = glyphs[i];

	// rotate

		{
			pGlyph->m_rotation = 0;

			n = m_nCharCount;
			PSVGElement* pElement = this;
			do
			{
				SVGTextPositioningElementImpl* posText = dynamic_cast<SVGTextPositioningElementImpl*>(pElement->m_pNode);

				if (posText)
				{
					//CLSVGTextElement* psvgElement = static_cast<CLSVGTextElement*>(posText.p);

#if 0
					SVGNumberList* rotate = posText->m_rotate->m_animated->m_animVal->m_value;

					if (rotate->m_items.GetSize() == 1)
					{
						pGlyph->m_rotation = rotate->m_items[0]->m_value;
						break;
					}
					else if ((n+i) < rotate->m_items.GetSize())
					{
						pGlyph->m_rotation = rotate->m_items[n+i]->m_value;
						break;
					}
#endif
				}

				if (pElement->m_parent == NULL) break;
				SVGElement* parentText = dynamic_cast<SVGElement*>(pElement->m_parent->m_pNode);
				if (parentText == NULL)
					break;

				pElement = (PSVGElement*)pElement->m_parent;

				n += pElement->m_nCharCount;
			}
			while (1);
		}

		pGlyph->m_position.X = tlc->curpos.X;
		pGlyph->m_position.Y = tlc->curpos.Y;

		tlc->chunk.Add(pGlyph);
		tlc->curpos.X += pGlyph->m_charWidth;

		/*
		{
			Gdiplus::Matrix matrix;

			matrix.RotateAt(pGlyph->m_rotation, pGlyph->m_position);
			matrix.Translate(pGlyph->m_position.X, pGlyph->m_position.Y);

			matrix.Scale(pGlyph->m_scale, -pGlyph->m_scale);

			pGlyph->m_graphicsPath.Transform(&matrix);
		}
		*/
	}

	m_nCharCount += glyphs.GetSize()-1;
}

// Layout for <text> and <tspan>
void PSVGElement::LayoutText(TextLayoutContext* tlc, bool bDoX, bool bDoY)
{
	SVGTextElement* psvgElement = static_cast<SVGTextElement*>(m_pNode);

	double minx = 999999;
	double miny = 999999;
	double maxx = -999999;
	double maxy = -999999;

	double curposX = tlc->curpos.X;
	m_textLength = 0;

	m_nCharCount = 0;

	if (m_glyphs.GetSize())
	{
		LayoutGlyphs(m_glyphs, tlc, bDoX, bDoY, minx, miny, maxx, maxy);
	}
	else
	{
		PNode** pos = m_childList.begin();
		while (pos != m_childList.end())
		{
			PNode* pNode = *pos;
			++pos;
			if (pNode->m_type == NODE_ELEMENT)
			{
				SVGElement* textContent = static_cast<SVGElement*>(pNode->m_pNode);
				if (textContent)
				{
					PSVGElement* pSVGTextContent = (PSVGElement*)pNode;

					pSVGTextContent->LayoutText(tlc, bDoX, bDoY);

					m_nCharCount += pSVGTextContent->m_nCharCount;

					/*
					if (pSVGTextContent->m_bounds.Width > 0 && pSVGTextContent->m_bounds.Height > 0)
					{
						minx = min(minx, pSVGTextContent->m_bounds.X);
						miny = min(miny, pSVGTextContent->m_bounds.Y);
						maxx = max(maxx, pSVGTextContent->m_bounds.X+pSVGTextContent->m_bounds.Width);
						maxy = max(maxy, pSVGTextContent->m_bounds.Y+pSVGTextContent->m_bounds.Height);
					}
					*/
				}
			}
			else
			{
				PText* pText = dynamic_cast<PText*>(pNode);

				PSVGText* pTextNode;
				if (pText->m_ext == NULL)
				{
					pTextNode = new PSVGText(pText);
					pText->m_ext = pTextNode;

					pTextNode->CalculateDimensions(NULL);
				}
				else
				{
					pTextNode = dynamic_cast<PSVGText*>(pText->m_ext);
				}

				LayoutGlyphs(pTextNode->m_glyphs, tlc, bDoX, bDoY, minx, miny, maxx, maxy);
			}
		}
	}

	m_textLength = tlc->curpos.X - curposX;

#if 0
	RectD bounds;
	bounds.X = minx;
	bounds.Y = miny;
	bounds.Width = maxx-minx;
	bounds.Height = maxy-miny;

	m_bounds = bounds;	// TODO

	GetFillUriElement();
	GetStrokeUriElement();
	GetFilterElement();

	if (m_pFilterElement)
	{
		m_filterRect = m_pFilterElement->CalculateFilterRegion(this);
	}
	else
	{
		m_filterRect.X = bounds.X;
		m_filterRect.Y = bounds.Y;
		m_filterRect.Width = bounds.Width;
		m_filterRect.Height = bounds.Height;
	}

	m_expandedBBox = m_filterRect;

	gmMatrix3 matrix = GetLocalAnimatedMatrix();
	//if (pMatrix)
	{
		CalculateScale(/*m_expandedBBox,*/ matrix);

	//	pMatrix->Release();
	}

//	CPSVGTextContentElement::LayoutText(curpos);
#endif
}

}	// Web
}	// System
