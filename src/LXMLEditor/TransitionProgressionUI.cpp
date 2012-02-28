#include "stdafx.h"
#include "LXMLEditor.h"
#include "TransitionProgressionUI.h"

#include "../LSMILTransitions/LSMILTransitionFactory.h"
#pragma comment(lib, "../LSMILTransitions/Debug/LSMILTransitions.lib")

using namespace System;

#define MAKEINTRESOURCE(i)  (LPSTR) ((uint32) ((uint16) (i))) 

#define IDB_BITMAPB                     296
#define IDB_BITMAPA                     297

//extern MSWindows::HINSTANCE g_hInstance;

namespace System
{
namespace LXmlEdit
{

CTransitionProgressionUI::CTransitionProgressionUI()
{
	m_progress = 0;
	m_reverse = false;

	m_previewRect.left = 0;
	m_previewRect.top = 0;
	m_previewRect.right = 80;//.SetRect(0, client.top+16, client.right, client.bottom-16);
	m_previewRect.bottom = 48;

	UI::DockPanel* panel = new UI::DockPanel;

	m_progressCtrl = new UI::HorizontalSlider;
	m_progressCtrl->set_Height(new UI::Length(16));
	UI::DockPanel::SetDock(m_progressCtrl, UI::DockPanel::Bottom);
	m_progressCtrl->SetInfo(0, 110, 10);
	panel->AddRChild(m_progressCtrl);

	m_image = new Image(this);
	UI::DockPanel::SetDock(m_image, UI::DockPanel::Fill);
	panel->AddRChild(m_image);

	set_VisualTree(panel);
}

CTransitionProgressionUI::~CTransitionProgressionUI()
{
}

void CTransitionProgressionUI::Image::OnRender(UI::Graphics* pGraphics)
{
//	CRect& rc = *(CRect*)di.prcBounds;
//	HDC hDC = di.hdcDraw;

	double uiwidth = get_ActualSize().Width;
	double uiheight = get_ActualSize().Height;

	int cx = uiwidth/2;
	int cy = uiheight/2;

	//SetBkMode(hDC, TRANSPARENT);
	LDraw::RectD trect = LDraw::RectD(LDraw::PointD(0,0), get_ActualSize());
	trect.Height = 16;

//	FillSolidRect(hDC, &trect, GetSysColor(COLOR_BTNFACE));

	char buf[64];
	sprintf(buf, "%.1f %%", m_pUI->m_progress*100);
	pGraphics->DrawString(new System::StringA(string_copy(buf)), GetFont(), LDraw::PointF(trect.X, trect.Y), new LDraw::SolidBrush(LDraw::Color(0,0,0)));/*, DT_CENTER | DT_SINGLELINE*/

	if (m_pUI->m_type->Length())
	{
		LDraw::RectI mediaRect(m_pUI->m_previewRect.left, 16/*m_pUI->m_previewRect.top*/, m_pUI->m_previewRect.GetWidth(), uiheight-16/*m_pUI->m_previewRect.Height()*/);

		LDraw::Bitmap* pBitmapA;
		LDraw::Bitmap* pBitmapB;
		double progress;

		if (!m_pUI->m_reverse)
		{
			pBitmapA = m_pUI->m_bitmap[0];
			pBitmapB = m_pUI->m_bitmap[1];
			progress = m_pUI->m_progress;
		}
		else
		{
			pBitmapA = m_pUI->m_bitmap[1];
			pBitmapB = m_pUI->m_bitmap[0];
			progress = 1 - m_pUI->m_progress;
		}

		LDraw::Bitmap* pResultBitmap = new LDraw::Bitmap((int)mediaRect.Width, (int)mediaRect.Height, LDraw::PixelFormat_t::RGB_32);
		if (pResultBitmap)
		{
			SMILTransitionFactory* transitionFactory = new SMILTransitionFactory;
			if (transitionFactory)
			{
				/*
				LDraw::RectD rectA;
				rectA.X = 0;
				rectA.Y = 0;
				rectA.Width = pBitmapA->GetWidth();
				rectA.Height = pBitmapA->GetHeight();

				LDraw::RectD rectB;
				rectB.X = 0;
				rectB.Y = 0;
				rectB.Width = pBitmapB->GetWidth();
				rectB.Height = pBitmapB->GetHeight();

				LDraw::RectD rect;
				rect.X = 0;
				rect.Y = 0;
				rect.Width = mediaRect.Width;
				rect.Height = mediaRect.Height;
				*/

				ISMILTransition* transition;
				transitionFactory->FindTransition(m_pUI->m_type, m_pUI->m_subtype, &transition);
				if (transition)
				{
					transitionFactory->ProcessTransition(transition,
						m_pUI->m_horzRepeat, m_pUI->m_vertRepeat,
						0, 0,
						progress,
						/*rectA,*/ pBitmapA,
						/*rectB,*/ pBitmapB,
						/*rect,*/ pResultBitmap);
				}

				//LDraw::Graphics graphics(hDC);

				pGraphics->DrawImage(pResultBitmap,
					mediaRect,
					0, 0, mediaRect.Width, mediaRect.Height/*,
					LDraw::UnitPixel*/);
			}

		//	delete pResultBitmap;
		}

	//	delete pBitmapA;
	//	delete pBitmapB;
	}
}

#if 0
LRESULT CTransitionProgressionUI::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
// Don't erase anything, everything done in OnDraw()
	return TRUE;
}

LRESULT CTransitionProgressionUI::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_progressCtrl.Create(m_hWnd, CRect(0, 0, 0, 0), NULL, WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS);
	m_progressCtrl.SetRange(0, 100);
	m_progressCtrl.SetTicFreq(25);

	m_progressCtrl.SetPos(m_progress*100);

	return 0;
}

LRESULT CTransitionProgressionUI::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_previewRect.SetRect(0, client.top+16, client.right, client.bottom-16);

	m_progressCtrl.MoveWindow(0, client.bottom-16, client.right, 16, TRUE);

	return 0;
}

LRESULT CTransitionProgressionUI::OnHScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nScrollCode = (int) LOWORD(wParam);  // scroll bar value 

	long pos = m_progressCtrl.GetPos();

	m_progress = (double)pos/100;

	InvalidateRect(NULL);

	if (nScrollCode == SB_ENDSCROLL)
	{
		Fire_OnChanged(m_progress);
	}

	return 0;
}
#endif

void CTransitionProgressionUI::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"posChange")
		{
			evt->stopPropagation();
			UI::SliderEvent* sliderEvt = dynamic_cast<UI::SliderEvent*>(evt);
			m_progress = sliderEvt->m_pos / 100;
			m_image->Invalidate();
		}
	}
}

void CTransitionProgressionUI::SetTransition(System::StringW* type, System::StringW* subtype, long horzRepeat, long vertRepeat, long borderWidth, LDraw::Color borderColor)
{
	m_type = type;
	m_subtype = subtype;
	m_horzRepeat = horzRepeat;
	m_vertRepeat = vertRepeat;

	Invalidate();
}

double CTransitionProgressionUI::get_progress() const
{
	return m_progress;
}

void CTransitionProgressionUI::set_progress(double newVal)
{
	m_progress = newVal;
	m_progressCtrl->set_pos(m_progress*100);
	Invalidate();
}

bool CTransitionProgressionUI::get_reverse() const
{
	return m_reverse;
}

void CTransitionProgressionUI::set_reverse(bool newVal)
{
	m_reverse = newVal;
	Invalidate();
}

}	// LXmlEdit
}
