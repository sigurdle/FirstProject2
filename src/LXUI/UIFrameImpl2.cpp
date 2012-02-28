#include "stdafx.h"
#include "LXUI2.h"
#include "UIFrameImpl2.h"
#include "Screen.h"
//#include "WindowBase.h"

#if 0

#if WIN32

#include "../windows_header.h"

#include <ddraw.h>
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "Dxguid.lib")
#endif

namespace UI
{

using namespace System;

CUIFrameImpl2::CUIFrameImpl2()
{
	m_pClient = NULL;
	/*
	m_pClient->m_pFrame = this;
	m_pClient->m_pSite = this;
	*/

//	set_Width(new Length(800, Length::UnitAbsolute));
//	set_Height(new Length(600, Length::UnitAbsolute));
}

extern UIEXT __live_object_ptr<LayoutManager> pLayoutManager;

void CUIFrameImpl2::Show()
{
	m_pOwnerScreen->m_pCanvas->AddRChild(this/*dynamic_cast<Visual*>(pWindowClient)*/);
	m_pOwnerScreen->m_pCanvas->InvalidateMeasure();
	pLayoutManager->MeasureAll();

//	InvalidateMeasure();
//	OnMeasure(LDraw::SizeD(200, 200));
//	OnArrange(m_desiredSize);
}

LDraw::SizeD CUIFrameImpl2::OnMeasure(LDraw::SizeD availSize)
{
	m_pClientVisual->Measure(availSize);
	return m_pClientVisual->get_DesiredSize();
}

void CUIFrameImpl2::OnArrange(LDraw::SizeD finalSize)
{
	Control::OnArrange(finalSize);

	m_pClientVisual->Arrange(finalSize);

	/*
	m_expandedBBox.X = -4;
	m_expandedBBox.Y = -4;
	m_expandedBBox.Width += 8;
	m_expandedBBox.Height += 8;
	*/
}

void CUIFrameImpl2::Close()
{
	if (m_pClientVisual->get_VisualTree())
	{
	//	m_pClient->m_VisualTree->SetRParent(NULL);
	}
	ReleaseCapture();
	UIElement* parent = GetRParent();
	parent->RemoveRChild(this);
	// TODO, had this (TODO, have it in RemoveRChild())
#if 0
	parent->InvalidateMeasure();
#endif
}

void CUIFrameImpl2::OnRender(Graphics* pGraphics)
{
	m_pClientVisual->Render(pGraphics);
}

void CUIFrameImpl2::SetCapture()
{
	Control::SetCapture();
}

void CUIFrameImpl2::ReleaseCapture()
{
	Control::ReleaseCapture();
}

/*
void CUIFrameImpl2::InvalidateRect(const LDraw::RectD& rect)
{
	//MessageBeep(-1);
	Control::InvalidateRect(rect);
//	m_pOwnerScreen->Render();
}
*/

void CUIFrameImpl2::GetWindowRect(LDraw::Rect* lpRect) const
{
	lpRect->X = 0;
	lpRect->Y = 0;
	lpRect->Width = m_computedSize.Width;
	lpRect->Height = m_computedSize.Height;
}

void CUIFrameImpl2::SetWindowRect(double X, double Y, double Width, double Height)
{
	m_computedLeft = X;
	m_computedLeft = Y;

	set_Width(new Length(Width));
	set_Height(new Length(Height));

	InvalidateMeasure();
}

void CUIFrameImpl2::handleEvent(Event* evt)
{
	if (evt->get_eventPhase() != CAPTURING_PHASE)
	{
		StringW* type = evt->get_type();
		if (type == MouseEvent::mousemove)
		{
			evt->stopPropagation();

			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt.m_p);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			m_pClient->m_bInsideWindow = true;

			m_pClient->OnMouseMove(0, LDraw::PointD(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY()), LDraw::Point(point.X, point.Y));
		}
		else if (type == MouseEvent::mousedown)
		{
			evt->stopPropagation();

			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt.m_p);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			m_pClient->m_bInsideWindow = true;

			m_pClient->OnButtonDown(0, LDraw::PointD(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY()), LDraw::Point(point.X, point.Y), 0, false);
		}
		else if (type == MouseEvent::mouseup)
		{
			evt->stopPropagation();

			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt.m_p);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());

			m_pClient->m_bInsideWindow = true;

			m_pClient->OnButtonUp(0, LDraw::PointD(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY()), LDraw::Point(point.X, point.Y), 0);
		}
	}
}

}	// UI

#endif
