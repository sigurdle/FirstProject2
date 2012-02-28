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

namespace System
{

class C2Obj
{
public:
	bool	m_expanded;
	bool	m_selected;
	int m_itemHeight;

	System::StringW*	m_name;

	C2Obj* m_parent;
	Array<C2Obj*> m_childList;

public:
	C2Obj();
	virtual ~C2Obj();

	typedef C2Obj** UPOSITION;

	C2Obj* Iterate(C2Obj* &pParentItem, UPOSITION& pos, int& level, bool recurse = true);
	int GetItemHeight() { return m_itemHeight;}

	int CountVisibleComponents();
	int CountChildren();

	bool IsDescendant(C2Obj* pItem);

	void SetExpanded(bool expanded) { m_expanded = expanded; }
	bool IsExpanded() { return m_expanded; }

	bool IsSelected() { return m_selected; }
	void SetSelected(bool bSel) { m_selected = bSel; }

	void FreeChildren();

#if 0
	C2Obj* GetAt(UPOSITION pos)
	{
		return (C2Obj*)m_childList.GetAt(pos);
	}

	UPOSITION AddChildTail(C2Obj* pChild)
	{
		ATLASSERT(0);
		return 0;
#if 0
		pChild->m_parent = this;
		UPOSITION pos = m_childList.AddTail(pChild);

		return pos;
#endif
	}

	UPOSITION AddChildHead(C2Obj* pChild)
	{
		pChild->m_parent = this;
		return m_childList.AddHead(pChild);
	}

	bool HasChildren()
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
#endif

/*
	UPOSITION InsertSorted(C2Obj* pChild)
	{
		pChild->m_parent = this;
		return m_childList.InsertSorted(pChild);
	}
*/
};

}

//#pragma pack(pop)
