#pragma once

#include "XMLGridContainerNode.h"

namespace System
{

class CGridAttribute;

class XMLGRIDEXT CGridElement :
	public CGridContainerNode
{
public:
	CGridElement()
	{
		m_attrNameWidth = 80;
//		m_attrValueWidth = 40;
//		m_attributesHeight = 0;

		m_minWidth = m_attrNameWidth + 10;
	}

	list<CGridAttribute*> m_attributeList;
	list<CGridItem*> m_nodeList;

	UI::Button* m_expandButton;
	UI::UIElement* m_icon;
	UI::TextEdit* m_nodeNameEdit;

	int m_attrNameWidth;
//	int m_attrValueWidth;

//	int m_attributesHeight;

	virtual void BuildChildren();

	CGridAttribute* FindAttribute(System::StringW* name);

#if 0
	UPOSITION AddChildTail(CGridItem* pElement)
	{
		pElement->m_parent = this;
		return m_childList.AddTail(pElement);
	}
#endif

	void RebuildChildList();

	virtual void handleEvent(System::Event* evt);

	virtual void BuildXML(System::StringBuilderW& stream);
	virtual void BuildXML(System::IO::ISequentialByteStream* stream);

	virtual int HitTest(LDraw::PointD point, UINT nFlags, CGridItem* *pVal);

	virtual int Click(MSWindows::HDC hDC, LDraw::PointD point, UINT nFlags, bool bDblClk, CGridItem* *pVal);
//	virtual int ClickContent(HDC hDC, POINT point, UINT nFlags, BOOL bDblClk, CGridItem** pVal);

	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize);
	virtual void OnArrange(LDraw::SizeD finalSize);
//	virtual void Draw(HDC hDC, BOOL bSelected);

	CGridElement* FindDOMElement(LXmlEdit::Node* find)
	{
		ASSERT(0);
#if 0
		if (m_domNode == find) return this;

		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CGridElement* pParent = (CGridElement*)m_childList.GetNext(pos);

			if (pParent->m_domNode == find) return pParent;

			CGridElement* pFound = pParent->FindDOMElement(find);
			if (pFound) return pFound;
		}
#endif
		return NULL;
	}
};

}
