#include "stdafx.h"
#include "ListView.h"

namespace System
{

#if 0
void ListView::handleEvent(System::Event* evt)
{
#if WIN32
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"ActivateItem")
		{
			UI::TreeItem* item = dynamic_cast<UI::TreeItem*>(evt->get_target());

			LDraw::FontFamilyStyles* p = dynamic_cast<LDraw::FontFamilyStyles*>(item->m_userdata);

			UI::UIElement* v = (UI::UIElement*)__RTDynamicCast(m_itemVisual, 0, (void*)&typeid(Object), (void*)&typeid(UI::UIElement), 0);

			SetFontFamily(v, new UI::FontFamily(new LDraw::FontFamily(p)));

			//	view->m_table->m_pTree->m_pSingleSelection;
		}
	}
#else
	VERIFY(0);
#endif
}
#endif

}
