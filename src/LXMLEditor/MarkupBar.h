#pragma once

namespace System
{
namespace LXmlEdit
{

class Node;

class CMarkupItem
{
public:
	Node* m_node;
	System::StringW* m_name;
	int m_width;
};

class CMarkupBar : public UI::Control//CWindowImpl<CMarkupBar>
{
public:
	CMarkupBar()
	{
	}

	Array<CMarkupItem*> m_markupItems;

	Web::Range* m_range;

	void BuildMarkupTree(Web::Range* range);

	/*
BEGIN_MSG_MAP(CMarkupBar)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	*/
};

}	// LXmlEdit
}
