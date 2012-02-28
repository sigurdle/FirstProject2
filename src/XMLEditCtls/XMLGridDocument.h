#pragma once

#include "XMLGridContainerNode.h"

namespace System
{

class XMLGRIDEXT CGridDocument :
	public CGridContainerNode
{
public:
	CGridDocument(LXmlEdit::CEXMLDocument* node)
	{
		m_domNode = node;
	}

	/*
	void FinalRelease()
	{
		CGridContainerNode::FinalRelease();
	}
	*/

#if 0
	UPOSITION AddChildTail(CGridItem* pElement)
	{
		pElement->m_parent = this;
		return m_childList.AddTail(pElement);
	}
#endif

	void RebuildChildList();

	virtual void BuildChildren();

	virtual void BuildXML(System::StringBuilderW& stream);
	virtual void BuildXML(System::IO::ISequentialByteStream* stream);

	virtual int HitTest(LDraw::PointD point, UINT nFlags, CGridItem* *pVal)
	{
		// ??????? Should never be called
		ASSERT(0);
		return 0;
	}

	virtual int Click(MSWindows::HDC hDC, LDraw::PointD point, UINT nFlags, bool bDblClk, CGridItem* *pVal)
	{
		// Should never be called
		ASSERT(0);
		return 0;
	}
//	virtual int ClickContent(HDC hDC, POINT point, UINT nFlags, BOOL bDblClk, CGridItem** pVal);

	virtual void Size(MSWindows::HDC hDC, int width)
	{
		// Should never be called
		ASSERT(0);
//		SizeContent(hDC, width);
	}
	virtual void Draw(MSWindows::HDC hDC, bool bSelected)
	{
		// Should never be called
		ASSERT(0);
	}
};

}
