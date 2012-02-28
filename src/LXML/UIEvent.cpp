#include "stdafx.h"
#include "LXML2.h"

namespace System
{
namespace Web
{

UIEvent::UIEvent()
{
	m_detail = 0;
	m_view = NULL;
}

IAbstractView* UIEvent::get_view() const
{
	return m_view;
}

void UIEvent::initUIEvent(StringIn typeArg, bool canBubbleArg, bool cancelableArg, IAbstractView* viewArg, int detailArg)
{
// Call base event init
	Event::initEvent(typeArg, canBubbleArg, cancelableArg);

	m_view = viewArg;
	m_detail = detailArg;
}

int UIEvent::get_detail() const
{
	return m_detail;
}

}	// w3c
}
