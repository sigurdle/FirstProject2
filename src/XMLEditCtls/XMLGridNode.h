#pragma once

namespace System
{

class CGridElement;
class CGridContainer;
class CXMLGridCtl;

void DrawTopLeft(UI::Graphics * hDC, LDraw::RectI* rc, LDraw::Color clr);

class XMLGRIDEXT CGridItem :
public UI::Control//IXMLGridNode
{
public:
	CGridItem()
	{
		m_pUI = NULL;

		m_minWidth = 0;
		m_optimalWidth = 0;

	//	m_pos.x = 0;
	//	m_pos.y = 0;
	//	m_size.cx = 0;
	//	m_size.cy = 0;

		m_parent = NULL;
		m_selected = false;

		m_bEditChanged = false;
		m_hWndEdit = NULL;

		m_domNode = NULL;
	}

	~CGridItem()
	{
	}

	void FinalRelease()
	{
		RemoveChildren();
	}

	CXMLGridCtl* m_pUI;

	LXmlEdit::Node* m_domNode;

	LDraw::PointD m_pos;
//	CSize m_size;
//	CRect m_contentRect;

	int m_minWidth;
	int m_optimalWidth;

	bool m_selected;
	bool m_bEditChanged;
	CGridContainer* m_parent;

	int m_nameHeight;

//	CUPtrList m_childList;

	UI::Control* m_hWndEdit;

	LDraw::BBoxi GetAbsRect();

	virtual void Deselect()
	{
		m_selected = false;
	}

	bool IsNodeDescendant(CGridItem* pNode)
	{
		ASSERT(0);
#if 0
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CGridItem* pNode2 = (CGridItem*)m_childList.GetNext(pos);

			if (pNode2 == pNode)
			{
				return TRUE;
			}

			BOOL b = pNode2->IsNodeDescendant(pNode);
			if (b) return TRUE;
		}
#endif
		return false;
	}

	bool IsSelected(bool bDeep)
	{
		if (m_selected)
			return true;

		ASSERT(0);
#if 0
		if (bDeep)
		{
			UPOSITION pos = m_childList.GetHeadPosition();
			while (pos)
			{
				CGridItem* pItem = (CGridItem*)m_childList.GetNext(pos);

				BOOL bSelected = pItem->IsSelected(TRUE);
				if (bSelected)
					return TRUE;
			}
		}
#endif
		return false;
	}

	void RemoveChildren()
	{
		ASSERT(0);
#if 0
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CGridItem* pItem = (CGridItem*)m_childList.GetNext(pos);
		//	pItem->Release();
		}
		m_childList.RemoveAll();
#endif
	}

	virtual void BuildChildren()
	{
	}

	virtual void BuildSelectedXML(System::StringBuilderW& stream);

	virtual void BuildSelectedXML(System::IO::ISequentialByteStream* stream);

	virtual void BuildXML(System::StringBuilderW& strbuilder) = 0;
	virtual void BuildXML(System::IO::ISequentialByteStream* stream) = 0;

	Web::NodeType GetNodeType()
	{
		return m_domNode->get_nodeType();
	}

	virtual System::StringW* GetNodeName() = 0;
/*	virtual void Size(HDC hDC, int width) = 0;
	virtual void SizeContent(HDC hDC, int width)
	{
	}
*/
	virtual void RecalculateParentSize(MSWindows::HDC hDC)
	{
	}

//	virtual void Draw(HDC hDC, BOOL bSelected) = 0;
	virtual void DrawContent(MSWindows::HDC hDC, bool bSelected)
	{
	}

	virtual int HitTest(LDraw::PointD point, UINT nFlags, CGridItem* *pVal)
	{
		*pVal = NULL;
		return 0;
	}

	virtual int HitTestContent(LDraw::PointD point, UINT nFlags, CGridItem* *pVal)
	{
		*pVal = NULL;
		return 0;
	}

	virtual int Click(MSWindows::HDC hDC, LDraw::PointD point, UINT nFlags, bool bDblClk, CGridItem* *pVal)
	{
		*pVal = NULL;
		return 0;
	}

	virtual int ClickContent(MSWindows::HDC hDC, LDraw::PointD point, UINT nFlags, bool bDblClk, CGridItem** pVal)
	{
		*pVal = NULL;
		return 0;
	}

	virtual void EndEdit()
	{
	}
	
	virtual void OnEditChange(MSWindows::HDC hDC, CGridItem* m_pTree)
	{
	}

	LXmlEdit::Node* get_node()
	{
		return m_domNode;
	}
};

class XMLGRIDEXT CGridNode : public CGridItem
{
public:
	CGridNode()
	{
	}

	void FinalRelease()
	{
		CGridItem::FinalRelease();
	}

	virtual System::StringW* GetNodeName()
	{
		return NULL;
#if 0
		BSTR bnodeName;
		m_domNode->get_nodeName(&bnodeName);
		return _bstr_t(bnodeName, false);
#endif
	}
};

class XMLGRIDEXT ChildNodes : public UI::Control
{
public:
	Array<CGridItem*> m_items;

//	virtual void OnRender2(LDraw::Graphics* pGraphics);
	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize);
	virtual void OnArrange(LDraw::SizeD finalSize);
};

class XMLGRIDEXT CGridContainer :
	public CGridNode
{
public:
	ChildNodes* m_childNodes;

	bool m_expanded;

	void DrawExpand(MSWindows::HDC hDC, bool bOver);

//	void ResizeChildren(HDC hDC, int maxx);
//	int SizeChildren(HDC hDC, int width);

//	void CalculateChildrenSize();

	virtual void Deselect();

	virtual int Click(MSWindows::HDC hDC, LDraw::PointD point, UINT nFlags, bool bDblClk, CGridItem** pVal);

//	virtual void DrawContent(HDC hDC, BOOL bSelected);
//	virtual void SizeContent(HDC hDC, int width);
};

class CGridEmpty :
	public CGridNode
{
public:
	CGridEmpty()
	{
	}
/*
	void FinalRelease()
	{
		CGridNode::FinalRelease();
	}
*/
	virtual void Size(MSWindows::HDC hDC, int width)
	{
		ASSERT(0);
#if 0
		m_desiredSize.Height = 10;
		m_desiredSize.Width = width;
#endif
	}

	virtual void Draw(MSWindows::HDC hDC, bool bSelected)
	{
		ASSERT(0);
#if 0
		//if (m_selected) bSelected = TRUE;
		bSelected = m_selected;

		CRect rect(0, 0, m_size.cx, m_size.cy);

		FillSolidRect(hDC, &rect, bSelected? RGB(138, 200, 235): RGB(255, 255, 255));
		DrawTopLeft(hDC, &rect, RGB(200, 200, 200));
#endif
	}

	virtual int Click(MSWindows::HDC hDC, LDraw::PointD point, UINT nFlags, bool bDblClk, CGridItem* *pVal)
	{
		ASSERT(0);
#if 0
		if (point.x >= 0 && point.y >= 0 && point.x < m_size.cx && point.y < m_size.cy)
		{
			*pVal = this;
			return 1;
		}
#endif
		return 0;
	}

	virtual int HitTest(LDraw::PointD point, UINT nFlags, CGridItem* *pVal)
	{
		ASSERT(0);
#if 0
		if (point.x >= 0 && point.y >= 0 && point.x < m_size.cx && point.y < m_size.cy)
		{
			*pVal = this;
			return 1;
		}
#endif
		return 0;
	}

	virtual void BuildXML(System::StringBuilderW& stream)
	{
	}

	virtual void BuildXML(System::IO::ISequentialByteStream* stream)
	{
	}
};

}	// System
