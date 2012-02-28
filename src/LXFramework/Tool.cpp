#include "stdafx.h"
#include "WebEditor.h"
#include "SvgEditor2.h"
#include "resource.h"

CToolEntry::CToolEntry(int id, LPCTSTR name, HBITMAP hBitmap)
{
	m_id = id;
	m_name = name;
	m_bitmap = hBitmap;
}

CToolEntry::~CToolEntry()
{
	if (m_bitmap)
	{
		DeleteObject(m_bitmap);
	}
}

CToolEntry* CToolGroup::FindToolByID(int id)
{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CToolBase* pToolB = (CToolBase*)m_childList.GetNext(pos);

		if (pToolB->m_childList.IsEmpty())
		{
			CToolEntry* pToolE = (CToolEntry*)pToolB;
			if (pToolE->m_id == id)
				return pToolE;
		}
		else
		{
			CToolGroup* pToolG = (CToolGroup*)pToolB;

		// Recurse
			CToolEntry* pToolE = pToolG->FindToolByID(id);
			if (pToolE)
				return pToolE;
		}
	}

	return NULL;
}
