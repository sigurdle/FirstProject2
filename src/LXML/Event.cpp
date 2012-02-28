#include "stdafx.h"
#include "LXML.h"

namespace System
{
namespace Web
{

Event::Event()
{
	m_eventPhase = UNKNOWN_PHASE;

	m_type = nullptr;
	m_bStopPropagation = false;
	m_bPreventDefault = false;
}

Event::~Event()
{
}

void Event::preventDefault()
{
	m_bPreventDefault = true;
}

bool Event::get_bubbles()
{
	return m_bubbles;
}

bool Event::get_cancelable()
{
	return m_cancelable;
}

DOMEventPhaseType Event::get_eventPhase()
{
	return m_eventPhase;
}

bool Event::isDefaultPrevented()
{
	return m_bPreventDefault;
}

bool Event::isPropagationStopped()
{
	return m_bStopPropagation;
}

String Event::get_type()
{
	return m_type;
}

EventTarget* Event::get_target()
{
	return m_target;
}

EventTarget* Event::get_currentTarget()
{
	ASSERT(0);
	return NULL;
}

void Event::initEvent(StringIn eventTypeArg, bool canBubbleArg, bool cancelableArg)
{
	m_type = eventTypeArg;
	m_bubbles = canBubbleArg;
	m_cancelable = cancelableArg;
}

}
}
