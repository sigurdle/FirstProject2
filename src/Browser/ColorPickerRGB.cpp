#include "stdafx.h"
#include "ColorPickerRGB.h"

namespace System
{
extern int g_r;
extern int g_g;
extern int g_b;
extern int g_a;

using namespace UI;

ColorPickerRGB::ColorPickerRGB()
{
UI::DockPanel* p = new DockPanel;

	for (int i = 0; i < 3; i++)
	{
		DockPanel* p2 = new DockPanel;
		{
			{
				Border* pBorder = new Border(new Thickness(1));
				m_edit[i] = new TextEdit;
				m_edit[i]->set_Width(32);
				pBorder->set_Child(m_edit[i]);
				DockPanel::SetDock(pBorder, DockPanel::Right);
				p2->AddChild(pBorder);
			}

			{
				m_slider[i] = new ColorSlider;
				m_slider[i]->set_Height(20);
				DockPanel::SetDock(m_slider[i], DockPanel::Fill);
				p2->AddChild(m_slider[i]);
			}
		}
		DockPanel::SetDock(p2, DockPanel::Top);
		p->AddChild(p2);
	}


	set_VisualTree(p);
}

void ColorPickerRGB::UpdateControls()
{
	int r = m_slider[0]->get_pos()*255;
	int g = m_slider[1]->get_pos()*255;
	int b = m_slider[2]->get_pos()*255;

	g_r = r;
	g_g = g;
	g_b = b;
	g_a = 255;

	for (int i = 0; i < 3; i++)
	{
		WCHAR buf[32];
		swprintf_s(buf, L"%d", (int)(m_slider[i]->get_pos()*255));
		m_edit[i]->set_Text(new StringW(string_copy(buf)));
	}

	m_slider[0]->set_fromValue(Color::FromRgb(0, g, b));
	m_slider[0]->set_toValue(Color::FromRgb(255, g, b));

	m_slider[1]->set_fromValue(Color::FromRgb(r, 0, b));
	m_slider[1]->set_toValue(Color::FromRgb(r, 255, b));

	m_slider[2]->set_fromValue(Color::FromRgb(r, g, 0));
	m_slider[2]->set_toValue(Color::FromRgb(r, g, 255));
}

#if 0
void ColorPickerRGB::handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != System::CAPTURING_PHASE)
	{
		if (*type == L"ValueChange")
		{
			SliderEvent* sevt = dynamic_cast<SliderEvent*>(evt);

			UpdateControls();
		}
	}
}
#endif

}
