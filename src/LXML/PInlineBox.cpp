#include "stdafx.h"
#include "LXML2.h"

#include "PInlineBox.h"

#include "PElementBase.h"

#include "PWord.h"
#include "PTextNode.h"

#include "Window.h"
//#include "LXMLDocumentView.h"

#include "HTMContext.h"

namespace System
{
namespace Web
{

// virtual
void CMarkupBox::Draw(CHTMRenderContext* pC)
{
	ASSERT(0);
#if 0
	LDraw::Font* pFont = m_pElement->m_pNode->m_ownerDocument->m_pWindow->m_pMarkupFont;//m_pElement->m_computedFontFamily[0]->GetGdipFont();

	LDraw::RectF trect = GetAbsOuterRect();

	//pC->m_pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 255, 0)), trect);

	if (pC->m_bInSelection)
	{
#if 0
		LDraw::Color color;
		color.SetFromCOLORREF(GetSysColor(COLOR_HIGHLIGHT));
		pC->m_pGraphics->FillRectangle(&LDraw::SolidBrush(color), trect);
#endif
	}

	LDraw::SizeF size(trect.Width - trect.Height/2, trect.Height);

	StringW* text = m_pElement->m_pNode->get_nodeName();

	LDraw::SolidBrush* textbrush = new LDraw::SolidBrush(LDraw::Color(255,0,0));	// TODO
	//const LDraw::StringFormat* pStringFormat = LDraw::StringFormat::GenericTypographic();

	if (m_start == 1)
	{
		LDraw::PointF pts[] =
		{
			LDraw::PointF(trect.X, trect.Y),
			LDraw::PointF(trect.X+size.Width, trect.Y),
			LDraw::PointF(trect.X+size.Width+size.Height/4, trect.Y+size.Height/2),
			LDraw::PointF(trect.X+size.Width, trect.Y+size.Height),
			LDraw::PointF(trect.X, trect.Y+size.Height),
			LDraw::PointF(trect.X, trect.Y),
		};

		pC->m_pGraphics->FillPolygon(new LDraw::SolidBrush(LDraw::Color(255, 200, 0)), pts, 6);
		pC->m_pGraphics->DrawPolygon(new LDraw::Pen(LDraw::Color(255, 0, 0)), pts, 6);
		pC->m_pGraphics->DrawString(text,
				pFont,
				LDraw::PointF(trect.X+1, trect.Y+1),
			//	pStringFormat,
				textbrush);
	}
	else
	{
		LDraw::PointF pts[] =
		{
			LDraw::PointF(trect.X, trect.GetBottom()-size.Height/2),
			LDraw::PointF(trect.X+size.Height/4, trect.GetBottom()-size.Height),
			LDraw::PointF(trect.X+size.Width+size.Height/4, trect.GetBottom()-size.Height),
			LDraw::PointF(trect.X+size.Width+size.Height/4, trect.GetBottom()),
			LDraw::PointF(trect.X+size.Height/4, trect.GetBottom()),
			LDraw::PointF(trect.X, trect.GetBottom()-size.Height/2),
		};

		pC->m_pGraphics->FillPolygon(new LDraw::SolidBrush(LDraw::Color(255, 200, 0)), pts, 6);
		pC->m_pGraphics->DrawPolygon(new LDraw::Pen(LDraw::Color(255, 0, 0)), pts, 6);
		pC->m_pGraphics->DrawString(text,
				pFont,
				LDraw::PointF(trect.X+size.Height/4, trect.GetBottom()-size.Height/*m_customBlockBottom*/),
			//	pStringFormat,
				textbrush);
	}
#endif
}

// virtual
void CMarkupBox::CalculateDimensions(CHTMCalcContext* /*pC*/)
{
	String text = m_pElement->m_pNode->get_nodeName();

	ASSERT(0);
#if 0

	LDraw::Font* pFont = m_pElement->m_pNode->m_ownerDocument->m_pWindow->m_pMarkupFont;//m_pElement->m_computedFontFamily[0]->GetGdipFont();

//	const LDraw::StringFormat* pStringFormat = LDraw::StringFormat::GenericTypographic();

//	LDraw::GraphicsO graphics;
	LDraw::RectF sizef;
	sizef.Width = LDraw::Graphics2D::MeasureString(text->c_str(), text->Length(), pFont, LDraw::SmoothingModeNone);//, LDraw::PointF(0,0), &sizef);

	m_outerRect.Width = sizef.Width + pFont->GetSize()/2;
	m_outerRect.Height = pFont->GetSize();//sizef.Height;
#endif
}

// virtual
bool CMarkupBox::getPosUnderPoint(double x, double y, PNode **pNode, long *pOffset)
{
// TODO

	gm::RectF trect = GetAbsOuterRect();

	if (trect.Contains(x, y))
	{

	// Does this select content of the element?

		*pNode = m_pElement;
		*pOffset = 0;

		return true;
	}

	return false;
}

/////////////////////////////////////////////////////////////////////

CHTMInlineBox::CHTMInlineBox()
{
	m_type = boxTypeInline;
}

/*
double CHTMInlineBox::GetMaxAscent()
{
	double maxascent = 0;
	for (int i = 0; i < m_children.GetSize(); i++)
	{
		if (m_children[i]->m_type == 3 || m_children[i]->m_type == 4)
		{
			maxascent = max(maxascent, ((CHTMPCharacterBox*)m_children[i])->m_pTextNode->m_ascentPixel);
		}
		else if (m_children[i]->m_type == boxTypeInline)
		{
			double ascent = ((CHTMInlineBox*)m_children[i])->GetMaxAscent();
			maxascent = max(maxascent, ascent);
		}
	}
}
*/

double CHTMInlineBox::AdjustBottom()
{
	double maxascent = 0;
	vector<double> ascents;

	ascents.reserve(m_children.size());

	int i;

	for (i = 0; i < m_children.size(); i++)
	{
		double ascent;
		if (m_children[i]->m_type == 3 || m_children[i]->m_type == 4)
		{
			ascent = ((CHTMPCharacterBox*)m_children[i])->m_pTextNode->m_ascentPixel;
		}
		else// if (m_children[i]->m_type == boxTypeInline)
		{
			ascent = (/*(CHTMInlineBox*)*/m_children[i])->AdjustBottom();
		}

		maxascent = MAX(maxascent, ascent);
		ascents.push_back(ascent);
	}

	for (i = 0; i < m_children.GetSize(); i++)
	{
		m_children[i]->m_outerRect.Y = maxascent-ascents[i];
	}

	return maxascent;
}

void CHTMInlineBox::Draw(CHTMRenderContext* pC)
{
	ASSERT(m_pElement);

	ASSERT(0);
#if 0

	LDraw::RectF innerRect = GetAbsInnerRect();

//	pC->m_outerPos.X += m_outerRect.X;
//	pC->m_outerPos.Y += m_outerRect.Y;
//	pC->m_pGraphics->TranslateTransform(m_outerRect.X, m_outerRect.Y);

	pC->m_pGraphics->PushTransform();
	pC->m_pGraphics->TranslateTransform(innerRect.X, innerRect.Y);

	DrawBoxShadow(pC);

	DrawBackground(pC);

	DrawBorder(pC);

	pC->m_pGraphics->PopTransform();//oldtransform);

//	pC->m_outerPos.X += m_innerRect.X;
//	pC->m_outerPos.Y += m_innerRect.Y;
//	pC->m_pGraphics->TranslateTransform(m_innerRect.X, m_innerRect.Y);

	DrawChildren(pC);

//	pC->m_outerPos.X -= m_innerRect.X;
//	pC->m_outerPos.Y -= m_innerRect.Y;
//	pC->m_pGraphics->TranslateTransform(-m_innerRect.X, -m_innerRect.Y);

	DrawOutline(pC);

//	pC->m_outerPos.X -= m_outerRect.X;
//	pC->m_outerPos.Y -= m_outerRect.Y;
#endif
}

// virtual
int CHTMInlineBox::HitTestElementBox(double x, double y, PElementBase** ppElement)
{
	gm::RectF rc = m_innerRect;//GetAbsInnerRect();
	if (rc.Contains(x, y))
	{
		for (int i = 0; i < m_renderChildren.GetSize(); ++i)
		{
			CHTMBoxItem* pBox = m_renderChildren[i];

			int nhit = pBox->HitTestElementBox(x, y, ppElement);
			if (nhit)
				return nhit;
		}

		*ppElement = (PElementBase*)m_pElement;	// TODO
		return 1;
	}

	return 0;
}

//virtual
bool CHTMInlineBox::getPosUnderPoint(double x, double y, PNode **pNode, long *pOffset)
{
//	LDraw::RectF linerc = GetAbsInnerRect();
//	if (linerc.Contains(x, y))
	{
		for (int i = 0; i < m_children.GetSize(); ++i)
		{
			CHTMBoxItem* pBox = m_children[i];

			gm::RectF boxrc = pBox->GetAbsOuterRect();

			double right = boxrc.GetRight();
			/*
			double right;
			if (i < m_children.GetSize()-1)
			{
			//	CRect rboxrc = m_children[i+1]->GetAbsInnerRect();
				LDraw::RectF rboxrc = m_children[i+1]->GetAbsOuterRect();
				right = rboxrc.X-(rboxrc.GetLeft()-boxrc.GetRight())/2;
			}
			else
				right = linerc.GetRight();	// Allow clicking on entire line
				//right = boxrc.GetRight();
			*/

			if (x < right)
			{
				bool b = pBox->getPosUnderPoint(x, y, pNode, pOffset);
				if (b)
				{
					return true;
				}
			}
		}
	}

	return false;
}

}	// Web
}
