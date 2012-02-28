#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"

#include "PLineBox.h"

#include "PElementBase.h"

namespace System
{
namespace Web
{

CHTMLineBox::CHTMLineBox()
{
//		m_maxascent = 0;
}

CHTMLineBox::~CHTMLineBox()
{
}

double CHTMLineBox::AdjustBottom()
{
	double maxascent = 0;
	// TODO, on stack
	vector<double> ascents;
	ascents.reserve(m_children.size());

	for (size_t i = 0; i < m_children.size(); ++i)
	{
		double ascent = m_children[i]->AdjustBottom();
		ascents.Add(ascent);
		maxascent = MAX(maxascent, ascent);
	}

	for (size_t i = 0; i < m_children.GetSize(); ++i)
	{
		m_children[i]->m_outerRect.Y = maxascent-ascents[i];
	}

	return maxascent;
}

void PElementBase::Adjust(CHTMLineBox* pBox)
{
	if (m_computedTextAlign == TextAlign_right)
	{
		int ncount = pBox->m_children.GetSize();
		if (ncount > 0)
		{
			double rightX = pBox->m_children[ncount-1]->m_outerRect.GetRight();

			double add = pBox->m_innerRect.Width-rightX;

			for (int i = 0; i < pBox->m_children.GetSize(); i++)
			{
				pBox->m_children[i]->m_outerRect.X += add;
			}
		}
	}
	else if (m_computedTextAlign == TextAlign_center)
	{
		int ncount = pBox->m_children.GetSize();
		if (ncount > 0)
		{
			double rightX = pBox->m_children[ncount-1]->m_outerRect.GetRight();

			double add = (pBox->m_innerRect.Width-rightX)/2;

			for (int i = 0; i < pBox->m_children.GetSize(); i++)
			{
				pBox->m_children[i]->m_outerRect.X += add;
			}
		}
	}

	if (false)
	{
		int width = pBox->m_innerRect.Width;
		int ncount = pBox->m_children.GetSize();

		if (ncount > 0)
		{
			CHTMBoxItem* pLast = pBox->m_children[ncount-1];
			int curright = pLast->m_outerRect.GetRight();

			double addspace = (double)(width-curright)/(ncount);

			for (int i = 1; i < ncount; i++)
			{
				CHTMBoxItem* pItem = pBox->m_children[i];
				pItem->m_outerRect.Translate(addspace*i, 0);
			}
		}
	}
}

#if 0
void CHTMLineBox::Adjust(CPElement* pElement)
{
	if (pElement->m_computedTextAlign == TextAlign_right)
	{
		int ncount = m_children.GetSize();
		if (ncount > 0)
		{
			double rightX = m_children[ncount-1]->m_outerRect.GetRight();

			double add = m_innerRect.Width-rightX;

			for (int i = 0; i < m_children.GetSize(); i++)
			{
				m_children[i]->m_outerRect.X += add;
			}
		}
	}
	else if (pElement->m_computedTextAlign == TextAlign_center)
	{
		int ncount = m_children.GetSize();
		if (ncount > 0)
		{
			double rightX = m_children[ncount-1]->m_outerRect.GetRight();

			double add = (m_innerRect.Width-rightX)/2;

			for (int i = 0; i < m_children.GetSize(); i++)
			{
				m_children[i]->m_outerRect.X += add;
			}
		}
	}

	if (FALSE)
	{
		int width = m_innerRect.Width;
		int ncount = m_children.GetSize();

		if (ncount > 0)
		{
			CHTMBoxItem* pLast = m_children[ncount-1];
			int curright = pLast->m_outerRect.GetRight();

			double addspace = (double)(width-curright)/(ncount);

			for (int i = 1; i < ncount; i++)
			{
				CHTMBoxItem* pItem = m_children[i];
				pItem->m_outerRect.Offset(addspace*i, 0);
			}
		}
	}
}
#endif

// virtual
int CHTMLineBox::HitTestElementBox(double x, double y, PElementBase** ppElement)
{
//	Gdiplus::RectF rc = GetAbsInnerRect();
//	if (rc.Contains(x, y))
	{
		for (size_t i = 0; i < m_renderChildren.GetSize(); ++i)
		{
			CHTMBoxItem* pBox = m_renderChildren[i];

			int nhit = pBox->HitTestElementBox(x, y, ppElement);
			if (nhit)
				return nhit;
		}
	}

	return 0;
}

//virtual
bool CHTMLineBox::getPosUnderPoint(double x, double y, PNode **pNode, long *pOffset)
{
	gm::RectF linerc = GetAbsInnerRect();
	if (linerc.Contains(x, y))
	{
		for (int i = 0; i < m_children.GetSize(); i++)
		{
			CHTMBoxItem* pBox = (CHTMBoxItem*)m_children[i];

		//	Gdiplus::Rect boxrc = pBox->GetAbsInnerRect();	// Had this
			gm::RectF boxrc = pBox->GetAbsOuterRect();

			double right;
			if (i < m_children.GetSize()-1)
			{
			//	CRect rboxrc = m_children[i+1]->GetAbsInnerRect();
				gm::RectF rboxrc = m_children[i+1]->GetAbsOuterRect();
				right = rboxrc.X-(rboxrc.GetLeft()-boxrc.GetRight())/2;
			}
			else
				right = linerc.GetRight();	// Allow clicking on entire line
				//right = boxrc.GetRight();

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

void CHTMLineBox::Draw(CHTMRenderContext* pC)
{
	m_absInnerRect = GetAbsInnerRect();
//	LDraw::RectF innerRect = GetAbsInnerRect();

//	/*LDraw::Matrix oldtransform =*/ pC->m_pGraphics->PushTransform();
//	pC->m_pGraphics->TranslateTransform(m_outerRect.X + m_innerRect.X, m_outerRect.Y + m_innerRect.Y);

//	pC->m_pGraphics->TranslateTransform(innerRect.X, innerRect.Y);

	//	pC->m_outerPos.X += m_outerRect.X;
//	pC->m_outerPos.Y += m_outerRect.Y;

#if 0
	LDraw::RectF innerRect = m_innerRect;
	innerRect.Offset(pC->m_outerPos.X, pC->m_outerPos.Y);

	if (true)//pC->m_clip.IntersectsWith(innerRect))
		pC->m_outerPos.X += m_innerRect.X;
		pC->m_outerPos.Y += m_innerRect.Y;
#endif
	//if (pC->m_clip.IntersectsWith(m_innerRect))
	{
		for (size_t i = 0; i < m_renderChildren.GetSize(); i++)
		{
			CHTMBoxItem* pBox = m_renderChildren[i];

			pBox->Draw(pC);
		}

#if 0
		pC->m_outerPos.X -= m_innerRect.X;
		pC->m_outerPos.Y -= m_innerRect.Y;
#endif
	}
//	pC->m_outerPos.X -= m_outerRect.X;
//	pC->m_outerPos.Y -= m_outerRect.Y;
//	pC->m_pGraphics->PopTransform();//oldtransform);
}

#if 0
bool CHTMLineBox::OnButtonDown(LDraw::PointD point, CPElementBase* *pVal)
{
	LDraw::RectF rect = GetAbsInnerRect();

	if (rect.Contains(point.X, point.Y))
	{
		for (int i = 0; i < m_children.size(); i++)
		{
			CHTMBoxItem* pBox = m_children[i];

			bool b = pBox->OnButtonDown(point, pVal);
			if (b) return b;
		}
	}

	return false;
}
#endif

}	// Web
}
