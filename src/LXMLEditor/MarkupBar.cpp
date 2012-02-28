#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "MarkupBar.h"

#if 0

ILDOMNode* FindCommonContainer(ILDOMNode* node1, ILDOMNode* node2)
{
	CComPtr<ILDOMNode> parentNode1;
	node1->get_parentNode(&parentNode1);

	CArray<ILDOMNode*,ILDOMNode*> arr1;
	CArray<ILDOMNode*,ILDOMNode*> arr2;

	{
		CComPtr<ILDOMNode> parentNode = node1;
		//node1->get_parentNode(&parentNode);
		while (parentNode)
		{
			arr1.Add(parentNode);

			CComPtr<ILDOMNode> parent;
			parentNode->get_parentNode(&parent);
			parentNode = parent;
		}
	}

	{
		CComPtr<ILDOMNode> parentNode = node2;
		//node2->get_parentNode(&parentNode);
		while (parentNode)
		{
			arr2.Add(parentNode);

			CComPtr<ILDOMNode> parent;
			parentNode->get_parentNode(&parent);
			parentNode = parent;
		}
	}

	for (int i = 0; i < arr1.GetSize(); i++)
	{
		for (int j = 0; j < arr2.GetSize(); j++)
		{
			if (arr1[i] == arr2[j])
				return arr1[i];
		}
	}

	ATLASSERT(0);
	return NULL;
}

ILDOMNode* FindCommonContainerOuter(ILDOMNode* node1, ILDOMNode* node2)
{
	CComPtr<ILDOMNode> parentNode1;
	node1->get_parentNode(&parentNode1);

	CArray<ILDOMNode*,ILDOMNode*> arr1;
	CArray<ILDOMNode*,ILDOMNode*> arr2;

	{
		CComPtr<ILDOMNode> parentNode;// = node1;
		node1->get_parentNode(&parentNode);
		while (parentNode)
		{
			arr1.Add(parentNode);

			CComPtr<ILDOMNode> parent;
			parentNode->get_parentNode(&parent);
			parentNode = parent;
		}
	}

	{
		CComPtr<ILDOMNode> parentNode;// = node2;
		node2->get_parentNode(&parentNode);
		while (parentNode)
		{
			arr2.Add(parentNode);

			CComPtr<ILDOMNode> parent;
			parentNode->get_parentNode(&parent);
			parentNode = parent;
		}
	}

	for (int i = 0; i < arr1.GetSize(); i++)
	{
		for (int j = 0; j < arr2.GetSize(); j++)
		{
			if (arr1[i] == arr2[j])
				return arr1[i];
		}
	}

	ATLASSERT(0);
	return NULL;
}

////////////////////////////////////////////////////////////////////////
// CMarkupBar

void CMarkupBar::BuildMarkupTree(ILDOMRange* range)
{
#if 0
	m_range = range;

	m_markupItems.RemoveAll();
	CComPtr<ILDOMNode> startContainer;
	long startOffset;

	CComPtr<ILDOMNode> endContainer;
	long endOffset;

	range->get_startContainer(&startContainer);
	range->get_startOffset(&startOffset);

	range->get_endContainer(&endContainer);
	range->get_endOffset(&endOffset);

	if (startContainer && endContainer)
	{
		CComPtr<ILDOMNode> commonAncestorContainer = FindCommonContainer(startContainer, endContainer);

	//	range->get_commonAncestorContainer(&commonAncestorContainer);

		CDC dc;
		dc.CreateCompatibleDC(NULL);

		HFONT hOldFont = dc.SelectStockFont(DEFAULT_GUI_FONT);

		CComPtr<ILDOMNode> node = commonAncestorContainer;
		while (node)
		{
			CComPtr<ILDOMNode> parentNode;
			node->get_parentNode(&parentNode);

			if (parentNode == NULL)
				break;

			CMarkupItem* pItem = new CMarkupItem;
			pItem->m_node = node;

			BSTR bname;
			node->get_nodeName(&bname);

			LDOMNodeType nodeType;
			node->get_nodeType(&nodeType);

			if (nodeType == LNODE_ELEMENT)
			{
				WCHAR name[256];
				swprintf(name, L"<%s>", (BSTR)bname);
				pItem->m_name = name;
			}
			else
				pItem->m_name = bname;

			SysFreeString(bname);

			CSize size;
			dc.GetTextExtent(pItem->m_name, pItem->m_name.length(), &size);
			pItem->m_width = size.cx;

			m_markupItems.InsertAt(0, pItem);

			node = parentNode;
		}

		dc.SelectFont(hOldFont);
	}

	if (m_hWnd)
	{
		Invalidate();
	}
#endif
}

LRESULT CMarkupBar::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	CRect client;
	GetClientRect(&client);

	CRect rect = client;
	//rect.top = rect.bottom-16-1;

// Draw white dividing line
	dc.FillSolidRect(0, rect.top, client.right, 1, GetSysColor(COLOR_3DHILIGHT));
	/*
	rect.right++;
	rect.bottom++;
	dc.Draw3dRect(&rect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
	*/
	rect.top += 1;
	//rect.InflateRect(-1,-1);
	dc.FillSolidRect(&rect, GetSysColor(COLOR_BTNFACE));

	HFONT hOldFont = dc.SelectStockFont(DEFAULT_GUI_FONT);

	dc.SetBkMode(TRANSPARENT);

	int x = 0;

	for (int i = 0; i < m_markupItems.GetSize(); i++)
	{
		CMarkupItem* pItem = m_markupItems[i];

		CRect itemrect(rect.left+x, rect.top, rect.left+x+pItem->m_width+4, rect.bottom);

		dc.DrawText(pItem->m_name, pItem->m_name.length(), &itemrect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//dc.Draw3dRect(&itemrect, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));

		x += itemrect.Width();
	}

	dc.SelectFont(hOldFont);

	return 0;
}

LRESULT CMarkupBar::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	point.x -= 1;

	CMarkupItem* pFItem = NULL;

	int x = 0;
	for (int i = 0; i < m_markupItems.GetSize(); i++)
	{
		CMarkupItem* pItem = m_markupItems[i];

		x += pItem->m_width+4;

		if (point.x < x)
		{
			pFItem = pItem;
			break;
		}
	}

#if 0
	CComPtr<ILDOMDocument> document;
	window->get_document(&document);
#endif

	CComPtr<ILDOMRange> range = m_range;
	//window->get_selection(&range);

	if (pFItem)
	{
		range->selectNode(pFItem->m_node);
		//range->selectNodeContents(pFItem->m_node);
	}

	return 0;
}

#endif