#include "stdafx.h"
#include "LXML2.h"
#include "TimeEvent.h"

namespace System
{
namespace Web
{

TimeEvent::TimeEvent()
{
	m_view = NULL;
	m_detail = 0;
}

void TimeEvent::initTimeEvent(StringIn typeArg, IAbstractView *viewArg, int detailArg)
{
	initEvent(typeArg, false/*canBubble*/, false/*cancelable*/);
	m_view = viewArg;
	m_detail = detailArg;
}

IAbstractView* TimeEvent::get_view()
{
	return m_view;
}

int TimeEvent::get_detail()
{
	return m_detail;
}

}	// Web
}
