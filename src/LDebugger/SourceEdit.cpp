#include "stdafx.h"
#include "LDebugger.h"

#ifdef AMIGA
#define new DEBUG_NEW
#endif

#include "SourceEdit.h"
#include "SourceEditFrame.h"

namespace System
{
namespace Debugger
{

void DrawYellowArrow(UI::Graphics* pGraphics, double midy);
void DrawGreenArrow(UI::Graphics* pGraphics, double midy);

SourceEdit::SourceEdit()
{
	m_pFrame = NULL;
}

#if 0
void SourceEdit::handleEvent(System::Event* evt)
{
	System::StringW* type = evt->get_type();

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*type == L"contextmenu")
		{
			evt->stopPropagation();
			UI::MouseEvent* mouseEvt = dynamic_cast<UI::MouseEvent*>(evt);

			OnContextMenu(mouseEvt);
			return;
		}
		else if (*type == L"command")
		{
			UI::CommandInvokeEvent* cmdEvt = dynamic_cast<UI::CommandInvokeEvent*>(evt);

			if (cmdEvt->get_Command() == ID_DEBUG_TOGGLEBREAKPOINT)
			{
				evt->stopPropagation();
				OnToggleBreakpoint(cmdEvt);
				return;
			}
		}
	}

	TextEdit::handleEvent(evt);
}
#endif

void SourceEdit::OnContextMenu(UI::MouseButtonEventArgs* args)
{
//	evt->stopPropagation();
	TextEdit::OnLButtonUp();

	ASSERT(0);
#if 0

	UI::Menu* menu = new UI::Menu();
	menu->SetRParent(this);
	menu->SetOwnerWindow(GetOwnerWindow());

	menu->AddItem(new UI::TextString(WSTR("Cut")), ID_EDIT_CUT);
	menu->AddItem(new UI::TextString(WSTR("Copy")), ID_EDIT_COPY);
	menu->AddItem(new UI::TextString(WSTR("Paste")), ID_EDIT_PASTE);
	menu->AddSeparator();
	menu->AddItem(new UI::TextString(WSTR("Insert/Remove Breakpoint")), ID_DEBUG_TOGGLEBREAKPOINT);

	ASSERT(0);
	//menu->GetMenuPopup()->Popup(menu, LDraw::PointI(evt->get_ScreenX(), evt->get_ScreenY()));
#if 0
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CMenu menu;
	menu.LoadMenu(IDR_SOURCE);
	menu.GetSubMenu(0).TrackPopupMenu(0, point.x, point.y, m_hWnd);
#endif
#endif
}

#if 0//_WINDOWS

LRESULT SourceEdit::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

#if 0
	TextEdit::OnLButtonDown(nFlags, point, FALSE/*bStartDrag*/);
#endif

	return 0;
}
#endif

void SourceEdit::OnToggleBreakpoint(UI::RoutedEventArgs* cmdEvt)
{
	int line = get_line();

	tylinebreakpointmap::iterator bi = m_breakpoints.find(line);
	if (bi != m_breakpoints.end())
	{
		ASSERT(0);
#if 0	// TODO, have this
		m_breakpoints.erase(line);
#endif
	}
	else
	{
		DebugBreakpoint* pBreakpoint = new DebugBreakpoint;
		pBreakpoint->m_filename = m_pFrame->m_filename;
		pBreakpoint->m_line = line;

		m_pFrame->m_ctx->m_userbreakpoints.Add(pBreakpoint);
		m_breakpoints.insert(tylinebreakpointmap::value_type(line, pBreakpoint));
	}
	Invalidate();
}

//extern SourceLocation* pLocation;

void SourceEdit::OnDrawLineNumber(UI::Graphics* pGraphics, const LDraw::RectD& rc, int nline)
{
	tylinebreakpointmap::iterator bi = m_breakpoints.find(nline);
	if (bi != m_breakpoints.end())
	{
		pGraphics->FillEllipse(new LDraw::SolidBrush(LDraw::Color(255, 20, 20)), 3, rc.Y+3, rc.Height-6, rc.Height-6);
//		pGraphics->DrawEllipse(&Gdiplus::Pen(Gdiplus::Color(0, 0, 0)), 3, rc.top+3, rc.Height()-6, rc.Height()-6);
	}

	// TODO, m_pFrame->m_pCurLocation
	if (m_pFrame->m_ctx->m_frame->m_pLocation)
	{
		if (m_pFrame->m_ctx->m_frame->m_pLocation->line == nline+1)
		{
			int midy = rc.Y + rc.Height/2;
			DrawYellowArrow(pGraphics, midy);
			return;
		}
	}

#if 0
	else if (m_active >= line->u.instr.address && m_active < line->u.instr.address+line->u.instr.nbytes)
	{
		int off = m_pFrame->m_Eip - line->u.instr.address;

		LDraw::Graphics graphics(dc);

		int midy = rc.top + rc.Height()/2;

		DrawGreenArrow(pGaphics, midy);

		/*
		if (m_bViewCodeBytes)
		{
			CSize size;
			dc.GetTextExtent(strbytes, off*2, &size);

			graphics.FillRectangle(&Gdiplus::SolidBrush(Gdiplus::Color(0, 190, 0)),
				codebytesX + size.cx, rc.top+1, 1, rc.Height()-2);
		}
		*/
	}
#endif
	TextEdit::OnDrawLineNumber(pGraphics, rc, nline);
}

}
}
