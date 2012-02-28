#include "stdafx.h"
#include "XMLEditCtls.h"
#include "XMLGridNode.h"

#include "XMLGridCtl.h"

namespace System
{

LDraw::BBoxi CGridItem::GetAbsRect()
{
	ASSERT(0);
	return LDraw::BBoxi();
#if 0
	CRect rect(m_pos.x, m_pos.y, m_pos.x+m_size.cx, m_pos.y+m_size.cy);

	CGridItem* pItem = m_parent;
	while (pItem)
	{
		rect.OffsetRect(pItem->m_pos.x, pItem->m_pos.y);

		pItem = pItem->m_parent;
	}

	return rect;
#endif
}

}
