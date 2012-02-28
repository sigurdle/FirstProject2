#include "stdafx.h"
#include "item.h"

/*
POSITION CSortedList::InsertSorted(CStringObject* newElement)
{
	POSITION	pos = GetHeadPosition();

	while (pos)
	{
		POSITION oldpos = pos;
		CStringObject*	element = (CStringObject*)GetNext(pos);

		if (newElement->m_name < element->m_name)
			return InsertBefore(oldpos, newElement);
	}

// If we've gotten here, insert at end
	return AddTail(newElement);
}
*/

/*
UPOSITION CSortedList::InsertCompare(CStringObject* newElement, int (*func)(CStringObject*, CStringObject*))
{
	UPOSITION	pos = GetHeadPosition();

	while (pos)
	{
		UPOSITION oldpos = pos;
		CStringObject*	element = (CStringObject*)GetNext(pos);

		if (func(newElement, element) < 0)
			return InsertBefore(oldpos, newElement);
	}

// If we've gotten here, insert at end
	return AddTail(newElement);
}
*/

C2Obj::C2Obj()
{
	m_selected = FALSE;
	m_expanded = FALSE;
	m_parent = NULL;
	m_itemHeight = 14;
}

C2Obj::~C2Obj()
{
	UPOSITION pos = m_childList.GetHeadPosition();

	while (pos)
	{
		C2Obj* obj = (C2Obj*)m_childList.GetNext(pos);
		delete obj;
	}

	m_childList.RemoveAll();
}

C2Obj* C2Obj::Iterate(C2Obj* &pParentItem, UPOSITION& pos, int& level, BOOL recurse/* = TRUE*/)
{
	C2Obj* pItem = (C2Obj*)m_childList.GetNext(pos);

	if (pItem->HasChildren() && (recurse || pItem->IsExpanded()))
	{
		pParentItem = pItem;
		pos = pParentItem->GetHeadPosition();
		level++;
	}

	C2Obj* pI = this;

	while (!pos && pI->m_parent && (level > 0))
	{
		UPOSITION thisPos = pI->m_parent->m_childList.Find(pI);

		pParentItem = pI->m_parent;
		pI = pParentItem;
		pos = thisPos;
		pParentItem->m_childList.GetNext(pos);	// Skip this
		level--;
	}

	return pItem;
}

BOOL C2Obj::IsDescendant(C2Obj* pItem)
{
	if (this == pItem) return TRUE;

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		C2Obj* pLay = (C2Obj*)m_childList.GetNext(pos);

		if (pLay == pItem) return TRUE;
		if (pLay->IsDescendant(pItem)) return TRUE;
	}

	return FALSE;
}

int C2Obj::CountVisibleComponents()
{
	int count = 0;
	UPOSITION pos = m_childList.GetHeadPosition();

	while (pos)
	{
		C2Obj* obj = (C2Obj*)m_childList.GetNext(pos);

		if (obj->HasChildren() && obj->IsExpanded())
		{
			count += obj->CountVisibleComponents();
		}

		count++;
	}

	return count;
}

int C2Obj::CountChildren()
{
	int count = 0;
	UPOSITION pos = m_childList.GetHeadPosition();

	while (pos)
	{
		C2Obj* obj = (C2Obj*)m_childList.GetNext(pos);

		if (obj->HasChildren())
		{
			count += obj->CountChildren();
		}

		count++;
	}

	return count;
}
