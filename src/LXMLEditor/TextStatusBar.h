#pragma once

namespace System
{

class CTextStatusBar : public UI::Control//CWindowImpl<CTextStatusBar>
{
public:
	CTextStatusBar()
	{
	}

//	CScrollBar m_sizeGrip;

	System::StringW* m_text;

	/*
BEGIN_MSG_MAP(CTextStatusBar)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/
};

}
