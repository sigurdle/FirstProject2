#pragma once

#include "XMLGridNode.h"

namespace System
{

class XMLGRIDEXT CGridContainerNode :
	public CGridContainer
{
public:
	int m_childrenIndent;

	CGridContainerNode()
	{
		m_childrenIndent = 60;
		m_expanded = true;
	}

	void FinalRelease()
	{
		CGridContainer::FinalRelease();
	}

#if 0
	UPOSITION AddChildTail(CGridItem* pElement)
	{
		pElement->m_parent = this;
		return m_childList.AddTail(pElement);
	}
#endif

	void RebuildChildList();

	virtual void BuildChildren() = 0;

	virtual void BuildXML(System::StringBuilderW& stream) = 0;
	virtual void BuildXML(System::IO::ISequentialByteStream* stream) = 0;

	int GetChildrenWidth();

	virtual void RecalculateParentSize(MSWindows::HDC hDC);

//	virtual int HitTest(POINT point, UINT nFlags, CGridItem* *pVal);
	virtual int HitTestContent(LDraw::PointD point, UINT nFlags, CGridItem* *pVal);

//	virtual int Click(HDC hDC, POINT point, UINT nFlags, BOOL bDblClk, CGridItem* *pVal);
	virtual int ClickContent(MSWindows::HDC hDC, LDraw::PointD point, UINT nFlags, bool bDblClk, CGridItem** pVal);

//	virtual void Size(HDC hDC, int width);
//	virtual void Draw(HDC hDC, BOOL bSelected);

	virtual System::StringW* GetNodeName()
	{
		return m_domNode->get_nodeName();
	}

	virtual void OnEditChange(MSWindows::HDC hDC, CGridItem* m_pTree);
	virtual void EndEdit();
};
}
