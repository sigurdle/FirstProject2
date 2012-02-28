#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"
//#include "PreviewItem.h"

#if 0

#include "CSSStackingContext.h"

#include "PElementBase.h"
#include "PElementBox.h"
#if 0
#include "HTMContext.h"
#endif

namespace System
{
namespace Web
{

/*
CSS2, 9.9 Layered presentation

Each box belongs to one stacking context. Each box in a given stacking
context has an integer stack level, which is its position on the z-axis
relative to other boxes in the same stacking context. 

*/

void CSSStackingContext::AddElement(CPElementBase* pElement)
{
#if 0
// Insert sorted by elements computed z-index
	for (int i = 0; i < m_elements.GetSize(); i++)
	{
		if (pElement->m_computedZIndex < m_elements[i]->m_computedZIndex)
			break;
	}

	m_elements.InsertAt(i, pElement);
#endif
}

void CCSSStackingContext::RemoveElement(CPElementBase* pElement)
{
#if 0
	for (int i = 0; i < m_elements.GetSize(); i++)
	{
		if (m_elements[i] == pElement)
		{
			m_elements.RemoveAt(i);
			return;
		}
	}

	ASSERT(0);
#endif
}

void CCSSStackingContext::Draw(CHTMRenderContext* pC)
{
	ASSERT(0);
#if 0
	int nboxes = 0;

	CUPtrList visitedBoxList;

	for (int i = 0; i < m_elements.GetSize(); i++)
	{
		CPElement* pElement = m_elements[i];
		for (int j = 0; j < pElement->m_boxList.GetSize(); j++)
		{
			CHTMBoxItem* pBox = pElement->m_boxList[j];

			ASSERT(visitedBoxList.Find(pBox) == NULL);
			visitedBoxList.AddTail(pBox);

			pBox->Draw(pC);

			nboxes += 1;
		}

		if (pElement->m_pLocalStackingContext)
		{
			pElement->m_pLocalStackingContext->Draw(pC);
		}
	}

	TRACE("CCSSStackingContext::Draw() nboxes: %d\n", nboxes);
#endif
}

}	// Web
}

#endif