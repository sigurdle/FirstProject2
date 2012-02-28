#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"

#include "HTMContext.h"

#include "PElementBox.h"
#include "PInlineBox.h"
#include "PLineBox.h"
#include "PBlockBox.h"
#include "PParentBox.h"

#include "PElementBase.h"

namespace System
{
namespace Web
{

void /*CHTMFlowInlineContext::*/PlaceRelativeOnTop(CHTMParentBox* pThisBox)
{
// Place on top
	{
		int n = pThisBox->m_children.GetSize();
		for (int i = 0; i < n; )
		{
			CHTMBoxItem* pBox = pThisBox->m_children[i];
			if (pBox->m_type == 11)
			{
				if (((CHTMElementBox*)pBox)->m_pElement->m_computedPosition == Position_relative)
				{
					ASSERT(0);
#if 0
					pThisBox->m_children.RemoveAt(i);
					n--;
					//pBox->m_parentBox = NULL;
					pBox->SetParentNULL();
					pThisBox->AddChildBox(pBox);
#endif
					continue;
				}
			}
			i++;
		}
	}
}

/////////////////////////
// CHTMFlowInlineContext

CHTMFlowInlineContext::CHTMFlowInlineContext()
{
	m_type = 2;
	m_pElement = NULL;
	m_pCurInlineBox = NULL;

	m_bAnonymous = false;
}

CHTMFlowInlineContext::~CHTMFlowInlineContext()
{
	CHTMInlineBox* pInlineBox = m_pCurInlineBox;

	if (pInlineBox)
	{
		if (m_pElement->m_computedPosition == Position_relative)
		{
			m_pElement->m_computedLeft = m_pElement->m_specifiedLeft;	// TODO
			m_pElement->m_computedTop = m_pElement->m_specifiedTop;	// TODO
			pInlineBox->m_outerRect.Translate(m_pElement->m_computedLeft, m_pElement->m_computedTop);
		}

		PlaceRelativeOnTop(pInlineBox);
	}
}

void CHTMFlowInlineContext::PlaceInlineBox(CHTMBoxItem* pBox)
{
	if (PlaceOnSame(NULL, pBox))
		return;

	if (pBox->m_type == boxTypeBlock &&
		((CHTMBlockBox*)pBox)->m_pElement->m_computedFloat == Float_left)
	{
	}
	else
	{
		PlaceInlineBox2(NULL, pBox);
	}
#if 0
	m_pElement->AddBox(pBox);	// ??
#endif
}

/*
 ? A block context's line box is conceptually the same as an inlinecontext's inline box ?
*/

int CHTMFlowInlineContext::PlaceOnSame(CHTMFlowInlineContext* pC, CHTMBoxItem* pBox)
{
	CHTMInlineBox* pInlineBox = m_pCurInlineBox;

	if (m_pParentC->PlaceOnSame(this, pBox))
		return 1;

	if (pC)
		pC->m_floatLeft = m_floatLeft;

#if 0
	if (pBox->m_type == boxTypeBlock &&
		((CHTMBlockBox*)pBox)->m_pElement->m_computedFloat == Float_left)
	{
		return;
	}
#endif

	if (m_pCurInlineBox == NULL)
	{
		if (pInlineBox)
		{
			if (m_pElement->m_computedPosition == Position_relative)
			{
				m_pElement->m_computedLeft = m_pElement->m_specifiedLeft;	// TODO
				m_pElement->m_computedTop = m_pElement->m_specifiedTop;	// TODO
				pInlineBox->m_outerRect.Translate(m_pElement->m_computedLeft, m_pElement->m_computedTop);
			}

			PlaceRelativeOnTop(pInlineBox);
		}

		m_curpos.X = 0;

		if (pC)
		{
			pC->m_pCurInlineBox = NULL;
		}
	}

	return 0;
}

void CHTMFlowInlineContext::PlaceInlineBox2(CHTMFlowInlineContext* pC, CHTMBoxItem* pBox)
{
	/*
	if (pBox->m_type == boxTypeBlock &&
		((CHTMBlockBox*)pBox)->m_pElement->m_computedFloat == Float_left)
	{
		m_pParentC->PlaceInlineBox2(this, pBox);
		return;
	}
	*/

//	pC->m_pElement->m_pStackingContext->
	if (m_pCurInlineBox == NULL)
	{
		if (!m_bAnonymous)
			m_pCurInlineBox = m_pElement->CreateInlineBox();
		else
			m_pCurInlineBox = m_pElement->CreateAnonymousInlineBox();

	//	m_pElement->AddBox(m_pCurInlineBox);	// Added by the calls above

		m_pCurInlineBox->m_innerRect.X =
			m_pCurInlineBox->m_computedPadding[0] +
			m_pCurInlineBox->m_computedMargin[0] +
			m_pCurInlineBox->m_computedBorderWidth[0];

		m_pCurInlineBox->m_innerRect.Y =
			m_pCurInlineBox->m_computedPadding[1] +
			m_pCurInlineBox->m_computedMargin[1] +
			m_pCurInlineBox->m_computedBorderWidth[1];

	// Do this here?
		/*
		m_pCurInlineBox->m_outerRect.Width =
			m_pCurInlineBox->m_innerRect.Width +
			m_pCurInlineBox->m_computedPadding[0] +
			m_pCurInlineBox->m_computedPadding[2] +
			m_pCurInlineBox->m_computedMargin[0] +
			m_pCurInlineBox->m_computedMargin[2] +
			m_pCurInlineBox->m_computedBorderWidth[0];
			m_pCurInlineBox->m_computedBorderWidth[2];
			*/

		m_pCurInlineBox->m_outerRect.Y -= m_pCurInlineBox->m_computedPadding[1] +
														m_pCurInlineBox->m_computedMargin[1] +
														m_pCurInlineBox->m_computedBorderWidth[1];

		/*
		m_pCurInlineBox->m_outerRect.Height =
			m_pCurInlineBox->m_innerRect.Height +
			m_pCurInlineBox->m_computedPadding[1] +
			m_pCurInlineBox->m_computedPadding[3] +
			m_pCurInlineBox->m_computedMargin[1]+
			m_pCurInlineBox->m_computedMargin[3] +
			m_pCurInlineBox->m_computedBorderWidth[1];
			m_pCurInlineBox->m_computedBorderWidth[3];
			*/
	}

	if (pC)
	{
		// If the inline box doesn't have a parent box, create one
		if (pC->m_pCurInlineBox->m_parentBox == NULL)
		{
			m_pCurInlineBox->AddChildBox(pC->m_pCurInlineBox);
			//pC->m_pCurInlineBox->m_pElement->m_pStackingContext->AddElementBox(pC->m_pCurInlineBox);	// ???

			pC->m_pCurInlineBox->m_outerRect.X = m_curpos.X;
		}

		pC->m_pCurInlineBox->m_outerRect.Width =
			pC->m_pCurInlineBox->m_innerRect.Width +
			pC->m_pCurInlineBox->m_computedPadding[0] +
			pC->m_pCurInlineBox->m_computedPadding[2] +
			pC->m_pCurInlineBox->m_computedMargin[0] +
			pC->m_pCurInlineBox->m_computedMargin[2] +
			pC->m_pCurInlineBox->m_computedBorderWidth[0];
			pC->m_pCurInlineBox->m_computedBorderWidth[2];

			/*
		pC->m_pCurInlineBox->m_outerRect.Y -= pC->m_pCurInlineBox->m_computedPadding[1] +
														pC->m_pCurInlineBox->m_computedMargin[1] +
														pC->m_pCurInlineBox->m_computedBorderWidth[1];
														*/

		pC->m_pCurInlineBox->m_outerRect.Height =
			pC->m_pCurInlineBox->m_innerRect.Height +
			pC->m_pCurInlineBox->m_computedPadding[1] +
			pC->m_pCurInlineBox->m_computedPadding[3] +
			pC->m_pCurInlineBox->m_computedMargin[1] +
			pC->m_pCurInlineBox->m_computedMargin[3] +
			pC->m_pCurInlineBox->m_computedBorderWidth[1];
			pC->m_pCurInlineBox->m_computedBorderWidth[3];

		m_curpos.X = pC->m_pCurInlineBox->m_outerRect.GetRight();
	}
	else
	{
		if (pBox->m_parentBox != m_pCurInlineBox)
			m_pCurInlineBox->AddChildBox(pBox);
		pBox->m_outerRect.X = m_curpos.X;

		m_curpos.X = pBox->m_outerRect.GetRight();
	}

// Adjust inline box
	if (pC)
	{
		m_pCurInlineBox->m_innerRect.Width = pC->m_pCurInlineBox->m_outerRect.GetRight();
		m_pCurInlineBox->m_innerRect.Height = MAX(m_pCurInlineBox->m_innerRect.Height, pC->m_pCurInlineBox->m_outerRect.GetBottom());
	}
	else
	{
		m_pCurInlineBox->m_innerRect.Width = pBox->m_outerRect.GetRight();
		m_pCurInlineBox->m_innerRect.Height = MAX(m_pCurInlineBox->m_innerRect.Height, pBox->m_outerRect.GetBottom());
	}

	m_pParentC->PlaceInlineBox2(this, pBox);
}

/////////////////////////
// CHTMFlowBlockContext

CHTMFlowBlockContext::CHTMFlowBlockContext()
{
	m_type = 1;

	m_maxx = 0;

	m_pBlockBox = NULL;
	m_pCurLineBox = NULL;

	m_linepos.X = 0;
	m_linepos.Y = 0;

	m_bCanBreak = false;

	m_pWindow = NULL;

// float info
//	m_pPrevLeftFloatBox = NULL;
}

void CHTMFlowBlockContext::done()
{
	if (m_pCurLineBox)
	{
		// TODO, call this somewhere else
		m_pCurLineBox->AdjustBottom();
		m_pElement->Adjust(m_pCurLineBox);

		//ATLTRACE("lineWidth: %g\n", m_pCurLineBox->m_innerRect.Width);
		//m_pCurLineBox->PlaceRelativeOnTop();
	}
}

CHTMFlowBlockContext::~CHTMFlowBlockContext()
{
	done();

	if (m_pBlockBox)
	{
		for (int nline = 0; nline < m_pBlockBox->m_children.GetSize(); nline++)
		{
			CHTMLineBox* pLineBox = (CHTMLineBox*)m_pBlockBox->m_children[nline];
			
			int n = pLineBox->m_children.GetSize();
			for (int i = 0; i < n; )
			{
				CHTMBoxItem* pBox = pLineBox->m_children[i];
				if (pBox->m_type == 11)
				{
					if (((CHTMElementBox*)pBox)->m_pElement->m_computedPosition == Position_relative)
					{
						ASSERT(0);
#if 0
						pLineBox->m_children.RemoveAt(i);
#endif
						n--;

						pBox->m_outerRect.Translate(pLineBox->m_outerRect.X, pLineBox->m_outerRect.Y);
						//pBox->m_parentBox = NULL;
						pBox->SetParentNULL();
						m_pBlockBox->AddChildBox(pBox);

						continue;
					}
				}
				i++;
			}
		}
	}
}

int CHTMFlowBlockContext::PlaceOnSame(CHTMFlowInlineContext* pC, CHTMBoxItem* pBox)
{
	//ASSERT(pC);

	if (pBox->m_type == boxTypeBlock &&
		((CHTMBlockBox*)pBox)->m_pElement->m_computedClear == Clear_none)
	{
	}

	if (pBox->m_type == boxTypeBlock &&
		((CHTMBlockBox*)pBox)->m_pElement->m_computedFloat == Float_left)
	{
		CHTMBlockBox* pBlockBox = (CHTMBlockBox*)pBox;

		pBlockBox->m_outerRect.X = m_floatLeft;
		pBlockBox->m_outerRect.Y = 0;//TODO m_pCurLineBox->m_outerRect.Y;
		m_pBlockBox->AddChildBox(pBlockBox);

#if 0
		// Check if there's room for it on current line
		if ((m_linepos.X + m_curpos.X + pBox->m_outerRect.Width) <= m_pBlockBox->m_innerRect.Width)
		{
			// There was room on current line
			if (m_pCurLineBox)
			{
				// Move current line to right of float
				m_pCurLineBox->m_outerRect.X += pBox->m_outerRect.Width;

			// Place it immediately
				pBlockBox->m_outerRect.X = 0;
				pBlockBox->m_outerRect.Y = m_pCurLineBox->m_outerRect.Y;
				m_pBlockBox->AddChildBox(pBlockBox);
			}
		}
		else
		{
		// There was no room on current line
		// we'll wait to place it until current line is full

			m_pPrevLeftFloatBox = pBlockBox;	// Place it later
			pC->m_pPrevLeftFloatBox = m_pPrevLeftFloatBox;
		}
#endif

		m_floatBottom = MAX(m_floatBottom, pBox->m_outerRect.GetBottom());
		m_floatLeft = pBox->m_outerRect.GetRight();
	//	m_floatLeft = pBox->m_outerRect.Width;
		pC->m_floatLeft = m_floatLeft;
		pC->m_floatBottom = m_floatBottom;

		m_linepos.X = pC->m_floatLeft;	// Next line will start here ?
		m_curpos.X = 0;
	}
	else
	{
		int skip = 0;
		bool bCanBreak = (pBox->m_type == 4);	// We can break at this box (e.g space)

		if (pBox->m_type == 0xA)	// linefeed, end line
		{
			if (m_pCurLineBox)
			{
				m_pCurLineBox->AdjustBottom();
				m_pElement->Adjust(m_pCurLineBox);
				m_pCurLineBox = NULL;
				if (pC) pC->m_pCurInlineBox = NULL;
			}

			m_linepos.X = 0;
			m_curpos.X = 0;

			//m_curpos.X = m_floatLeft;	// on right side of any float
			m_curpos.Y = 0;
			return -1;
		}

	// Reached right border, wrap to next line (create new line box)
		if (m_pElement->m_computedWrapOption == WrapOption_wrap &&
			(m_linepos.X + m_curpos.X + pBox->m_outerRect.Width) > m_pBlockBox->m_innerRect.Width)
		{
			//if (m_bCanBreak || bCanBreak)
			{
				// If a space (U+0020) at the end of a line has 'all-space-treatment' set to 'collapse', it is also removed. 
				if (pBox->m_type == 4 && m_pElement->m_computedAllSpaceTreatment == AllSpaceTreatment_collapse)
					skip = 1;

				if (m_pCurLineBox)
				{
					if (m_pPrevLeftFloatBox)	// Place float box
					{
						m_pPrevLeftFloatBox->m_outerRect.X = 0;
						m_pPrevLeftFloatBox->m_outerRect.Y = m_pCurLineBox->m_outerRect.GetBottom();
						m_pBlockBox->AddChildBox(m_pPrevLeftFloatBox);

						//m_floatLeft = m_pPrevLeftFloatBox->m_outerRect.GetRight();

						m_floatBottom = m_pPrevLeftFloatBox->m_outerRect.GetBottom();
						pC->m_floatBottom = m_floatBottom;

						m_pPrevLeftFloatBox = NULL;
						pC->m_pPrevLeftFloatBox = NULL;
					}

					//ATLTRACE("lineWidth: %g\n", m_pCurLineBox->m_innerRect.Width);

					m_pCurLineBox->AdjustBottom();
					m_pElement->Adjust(m_pCurLineBox);
					m_pCurLineBox = NULL;
					if (pC) pC->m_pCurInlineBox = NULL;
				}

				m_linepos.X = m_floatLeft;
				m_curpos.X = 0;

				//m_curpos.X = m_floatLeft;	// on right side of any float
				m_curpos.Y = 0;
			}


#if 0
		// If there still is no room on the line, begin new line
		// below any floats
			if ((m_linepos.X + m_curpos.X + pBox->m_outerRect.Width) > m_pBlockBox->m_innerRect.Width)
			{
#if 0
				ASSERT(0);	// Not sure if this is ever called
#endif

				m_linepos.Y = max(m_linepos.Y, 0/*m_floatBottom*/);
				// We've gone below the float, so reset the left edge to 0
				m_linepos.X = 0;
			}
#endif
		}

		m_bCanBreak = bCanBreak;

		if (skip)
			return -1;
	}

	return 0;
}

void CHTMFlowBlockContext::PlaceInlineBox2(CHTMFlowInlineContext* pC, CHTMBoxItem* pBox)
{

	/*
	if (m_bIgnore)
	{
		m_bIgnore = false;
		return;
	}
	*/

#if 0	// Allow NULL pC ??
	ASSERT(pC);
#endif

	if (pBox->m_type == boxTypeBlock &&
		((CHTMBlockBox*)pBox)->m_pElement->m_computedFloat == Float_left)
	{
		CHTMBlockBox* pBlockBox = (CHTMBlockBox*)pBox;
		return;
	}

	if (m_pCurLineBox == NULL)
	{
	//	1. If a space (U+0020) at the beginning of a line has all-space-treatment' set to 'collapse', it is removed. 
		if (pBox->m_type == 4 && m_pElement->m_computedAllSpaceTreatment == AllSpaceTreatment_collapse)
			return;

		m_pCurLineBox = new CHTMLineBox;

		m_pCurLineBox->m_outerRect.X = m_linepos.X;
		m_pCurLineBox->m_outerRect.Y = m_linepos.Y;

		/*
		{
			pC->m_pCurInlineBox->m_outerRect.Y -= 
		}
		*/

		m_pCurLineBox->m_outerRect.Width = m_pBlockBox->m_innerRect.Width-m_linepos.X;

		m_pCurLineBox->m_innerRect.X = 0;
		m_pCurLineBox->m_innerRect.Y = 0;
		m_pCurLineBox->m_innerRect.Width = m_pCurLineBox->m_outerRect.Width;

		m_pBlockBox->AddChildBox(m_pCurLineBox);
	}

	if (pC)
	{
		if (pC->m_pCurInlineBox->m_parentBox == NULL)
		{
			m_pCurLineBox->AddChildBox(pC->m_pCurInlineBox);
			//pC->m_pCurInlineBox->m_pElement->m_pStackingContext->AddElementBox(pC->m_pCurInlineBox);	// ???
			//pC->m_pCurInlineBox->m_pElement->AddBox(pC->m_pCurInlineBox);

			pC->m_pCurInlineBox->m_outerRect.X = m_curpos.X;

			pC->m_pCurInlineBox->m_outerRect.Width = pC->m_pCurInlineBox->m_innerRect.Width;
			pC->m_pCurInlineBox->m_outerRect.Height = pC->m_pCurInlineBox->m_innerRect.Height;
		}

		pC->m_pCurInlineBox->m_outerRect.Width =
			pC->m_pCurInlineBox->m_innerRect.Width +
			pC->m_pCurInlineBox->m_computedPadding[0] +
			pC->m_pCurInlineBox->m_computedPadding[2] +
			pC->m_pCurInlineBox->m_computedMargin[0] +
			pC->m_pCurInlineBox->m_computedMargin[2] +
			pC->m_pCurInlineBox->m_computedBorderWidth[0];
			pC->m_pCurInlineBox->m_computedBorderWidth[2];

			/*
		pC->m_pCurInlineBox->m_outerRect.Y -= pC->m_pCurInlineBox->m_computedPadding[1] +
														pC->m_pCurInlineBox->m_computedMargin[1] +
														pC->m_pCurInlineBox->m_computedBorderWidth[1];
*/
		pC->m_pCurInlineBox->m_outerRect.Height =
			pC->m_pCurInlineBox->m_innerRect.Height +
			pC->m_pCurInlineBox->m_computedPadding[1] +
			pC->m_pCurInlineBox->m_computedPadding[3] +
			pC->m_pCurInlineBox->m_computedMargin[1]+
			pC->m_pCurInlineBox->m_computedMargin[3] +
			pC->m_pCurInlineBox->m_computedBorderWidth[1];
			pC->m_pCurInlineBox->m_computedBorderWidth[3];

		m_curpos.X = pC->m_pCurInlineBox->m_outerRect.GetRight();
	}
	else
	{
		if (pBox->m_parentBox != m_pCurLineBox)
			m_pCurLineBox->AddChildBox(pBox);
		pBox->m_outerRect.X = m_curpos.X;

		m_curpos.X = pBox->m_outerRect.GetRight();
	}

	if (m_curpos.X > m_maxx) m_maxx = m_curpos.X;
	ASSERT(m_maxx < 100000);

	double blocklineheight = m_pElement->m_computedLineHeight;

// Adjust line box
	if (pC)
	{
		// Check against innerRect since margins/border/padding of inline box doesn't affect line height
		if (pC->m_pCurInlineBox->m_innerRect.Height > m_pCurLineBox->m_innerRect.Height)
		{
			m_pCurLineBox->m_innerRect.Height = MAX(pC->m_pCurInlineBox->m_innerRect.Height, blocklineheight);
			m_pCurLineBox->m_outerRect.Height = m_pCurLineBox->m_innerRect.Height;

			m_linepos.Y = MAX(m_linepos.Y, m_pCurLineBox->m_outerRect.GetBottom());
		}
	}
	else
	{
		// Check against outerRect in this case ??
		if (pBox->m_outerRect.Height > m_pCurLineBox->m_innerRect.Height)
		{
			m_pCurLineBox->m_innerRect.Height = MAX(pBox->m_outerRect.Height, blocklineheight);
			m_pCurLineBox->m_outerRect.Height = m_pCurLineBox->m_innerRect.Height;

			m_linepos.Y = MAX(m_linepos.Y, m_pCurLineBox->m_outerRect.GetBottom());
		}
	}
}

}	// Web
}

