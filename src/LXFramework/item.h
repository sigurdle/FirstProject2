#pragma once

//#pragma pack(push, 8)

/*
class CStringObject// : public CObject
{
public:
};
*/

/*
class CSortedList : public CObList
{
public:
	CSortedList(int i) : CObList(i) {}
	POSITION InsertSorted(CStringObject* newElement);
	POSITION InsertCompare(CStringObject* newElement, int (*func)(CStringObject*, CStringObject*));
};
*/

class C2Obj
{
public:
	BYTE	m_expanded;
	BYTE	m_selected;
	short m_itemHeight;

	_bstr_t	m_name;

	C2Obj*	m_parent;
	CUPtrList m_childList;

public:
	C2Obj();
	virtual ~C2Obj();

	C2Obj* Iterate(C2Obj* &pParentItem, UPOSITION& pos, int& level, BOOL recurse = TRUE);
	int GetItemHeight() { return m_itemHeight;}

	int CountVisibleComponents();
	int CountChildren();

	BOOL IsDescendant(C2Obj* pItem);

	void SetExpanded(BOOL expanded) { m_expanded = expanded; }
	BOOL IsExpanded() { return m_expanded; }

	BOOL IsSelected() { return m_selected; }
	void SetSelected(BOOL bSel) { m_selected = bSel; }

	void FreeChildren();

	C2Obj* GetAt(UPOSITION pos)
	{
		return (C2Obj*)m_childList.GetAt(pos);
	}

	UPOSITION AddChildTail(C2Obj* pChild)
	{
		pChild->m_parent = this;
		UPOSITION pos = m_childList.AddTail(pChild);

		return pos;
	}

	UPOSITION AddChildHead(C2Obj* pChild)
	{
		pChild->m_parent = this;
		return m_childList.AddHead(pChild);
	}

	BOOL HasChildren()
	{
		return !m_childList.IsEmpty();
	}

	UPOSITION GetHeadPosition()
	{
		return m_childList.GetHeadPosition();
	}

	C2Obj* GetNext(UPOSITION& pos)
	{
		return (C2Obj*)m_childList.GetNext(pos);
	}

	UPOSITION InsertAfter(UPOSITION afterPos, C2Obj* pChild)
	{
		pChild->m_parent = this;
		return m_childList.InsertAfter(afterPos, pChild);
	}

	UPOSITION InsertBefore(UPOSITION beforePos, C2Obj* pChild)
	{
		pChild->m_parent = this;
		return m_childList.InsertBefore(beforePos, pChild);
	}

/*
	UPOSITION InsertSorted(C2Obj* pChild)
	{
		pChild->m_parent = this;
		return m_childList.InsertSorted(pChild);
	}
*/
};

//#pragma pack(pop)
