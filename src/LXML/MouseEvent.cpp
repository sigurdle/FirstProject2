#include "stdafx.h"
#include "LXML2.h"
#include "MouseEvent.h"

namespace System
{
namespace Web
{

MouseEvent::MouseEvent()
{
	m_screenX = 0;
	m_screenY = 0;
	m_clientX = 0;
	m_clientY = 0;
	m_ctrlKey = false;
	m_shiftKey = false;
	m_altKey = false;
	m_button = 0;
	m_relatedTarget = NULL;
}

MouseEvent::~MouseEvent()
{
}

int MouseEvent::get_screenX() const
{
	return m_screenX;
}

int MouseEvent::get_screenY() const
{
	return m_screenY;
}

int MouseEvent::get_clientX() const
{
	return m_clientX;
}

int MouseEvent::get_clientY() const
{
	return m_clientY;
}

bool MouseEvent::get_ctrlKey() const
{
	return m_ctrlKey;
}

bool MouseEvent::get_shiftKey() const
{
	return m_shiftKey;
}

bool MouseEvent::get_altKey() const
{
	return m_altKey;
}

bool MouseEvent::get_metaKey() const
{
	// TODO: Add your implementation code here
	ASSERT(0);
	return false;
}

int MouseEvent::get_button() const
{
	return m_button;
}

EventTarget* MouseEvent::get_relatedTarget() const
{
	return m_relatedTarget;
}

void MouseEvent::initMouseEvent(StringIn typeArg, bool canBubbleArg, bool cancelableArg, IAbstractView* viewArg, int detailArg, int screenXArg, int screenYArg, int clientXArg, int clientYArg, bool ctrlKeyArg, bool shiftKeyArg, bool altKeyArg, bool metaKeyArg, unsigned short buttonArg, EventTarget* relatedTargetArg)
{
	UIEvent::initUIEvent(typeArg, canBubbleArg, cancelableArg, viewArg, detailArg);

	m_screenX = screenXArg;
	m_screenY = screenYArg;
	m_clientX = clientXArg;
	m_clientY = clientYArg;
	m_ctrlKey = ctrlKeyArg;
	m_shiftKey = shiftKeyArg;
	m_altKey = altKeyArg;
	m_button = buttonArg;
	m_relatedTarget = relatedTargetArg;
}

}	// Web
}
