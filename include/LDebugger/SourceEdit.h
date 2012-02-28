#ifndef __SOURCEEDIT_H_
#define __SOURCEEDIT_H_

#include "resource.h"

/*
class FileBreakpoint
{
public:
};
*/

namespace System
{
namespace Debugger
{

typedef map<int,DebugBreakpoint*> tylinebreakpointmap;

class SourceEdit : public UI::TextEdit
{
public:
	CTOR SourceEdit();

	SourceEditFrame* m_pFrame;
	tylinebreakpointmap m_breakpoints;

#if 0//_WINDOWS
	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnToggleBreakpoint(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
#endif

protected:

//	virtual void handleEvent(System::Event* evt);

	virtual void OnDrawLineNumber(UI::Graphics* pGraphics, const LDraw::RectD& rc, int nline);

	void OnToggleBreakpoint(UI::RoutedEventArgs* cmdEvt);
	void OnContextMenu(UI::MouseButtonEventArgs* args);
};

}
}

#endif // __SOURCEEDIT_H_
