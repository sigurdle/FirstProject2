#include "stdafx.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

#include "LFC.h"

#if 0

#include "Event.h"
#include "EventTargetImpl.h"

namespace System
{

Event::Event()
{
	m_eventPhase = UNKNOWN_PHASE;

	m_type = NULL;
	m_target = NULL;

	m_bStopPropagation = false;
	m_bPreventDefault = false;
}

Event::~Event()
{
}

StringW* Event::get_type() const
{
	return m_type;
}

bool Event::get_bubbles() const
{
	return m_bubbles;
}

bool Event::get_cancelable() const
{
	return m_cancelable;
}

void Event::preventDefault()
{
	m_bPreventDefault = true;
}

void Event::stopPropagation()
{
	m_bStopPropagation = true;
}

bool Event::isDefaultPrevented() const
{
	return m_bPreventDefault;
}

bool Event::isPropagationStopped() const
{
	return m_bStopPropagation;
}

EventPhaseType Event::get_eventPhase() const
{
	return m_eventPhase;
}

/*
HRESULT Event::set_eventPhase(EventPhaseType newVal)
{
	m_eventPhase = newVal;
	return S_OK;
}
*/

EventTargetImpl* Event::get_target() const
{
	return m_target;
}

void Event::set_target(EventTargetImpl* newVal)
{
	m_target = newVal;
}

EventTargetImpl* Event::get_currentTarget() const
{
	return m_currentTarget;
}

void Event::set_currentTarget(EventTargetImpl* newVal)
{
	m_currentTarget = newVal;
}

void Event::InitEvent(StringW* eventTypeArg, bool canBubbleArg, bool cancelableArg)
{
	m_type = eventTypeArg;
	m_bubbles = canBubbleArg;
	m_cancelable = cancelableArg;
}

}	// System

#endif
