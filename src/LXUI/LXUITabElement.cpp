#include "stdafx.h"
#include "LXUI2.h"
#include "LXUITabElement.h"

namespace System
{
namespace UI
{

TabElement::TabElement()
{
	m_pBorder = new Border(new Thickness(1));
//	m_pBorder->m_LeftBrush = new SolidColorBrush(Color(0,0,0));
//	m_pBorder->m_TopBrush = new SolidColorBrush(Color(0,0,0));

	set_VisualTree(m_pBorder);
}

TabElement::TabElement(UIElement* content)
{
	m_pBorder = new Border(new Thickness(1));

	m_pBorder->set_Child(content);

//	m_pBorder->m_LeftBrush = new SolidColorBrush(Color(0,0,0));
//	m_pBorder->m_TopBrush = new SolidColorBrush(Color(0,0,0));

	set_VisualTree(m_pBorder);
}

#if 0
void TabElement::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (*type == L"mousedown")
		{
			evt->stopPropagation();

			Event* clickEvt = new Event;
			clickEvt->InitEvent(WSTR("click"), true, true);
			dispatchEvent(clickEvt);
		}
	}
}
#endif

}	// UI
}
