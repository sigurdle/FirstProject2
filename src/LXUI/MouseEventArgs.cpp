#include "stdafx.h"
#include "LXUI2.h"
#include "MouseEventArgs.h"

namespace System
{
namespace UI
{

MouseEventArgs::MouseEventArgs(void* mousedevice, int timestamp) : InputEventArgs(timestamp)
{
}

Point MouseEventArgs::GetPosition(IInputElement* relativeTo) const
{
	// TODO, improve

	Visual* visual = dynamic_cast<Visual*>(relativeTo);
	ASSERT(visual);
	return visual->WindowToElement(m_windowX, m_windowY);
}

MouseButtonState MouseEventArgs::get_LeftButton() const
{
	return (MouseButtonState)m_leftButton;
}

MouseButtonState MouseEventArgs::get_RightButton() const
{
	return (MouseButtonState)m_rightButton;
}

MouseButtonState MouseEventArgs::get_MiddleButton() const
{
	return (MouseButtonState)m_middleButton;
}

MouseButtonState MouseEventArgs::get_XButton1() const
{
	return (MouseButtonState)m_XButton1;
}

MouseButtonState MouseEventArgs::get_XButton2() const
{
	return (MouseButtonState)m_XButton2;
}

void MouseEventArgs::InvokeEventHandler(Object* genericTarget, stub_interface_base* genericHandler)
{
	stub_interface2<void, Object*, MouseEventArgs*>* handler = dynamic_cast<stub_interface2<void, Object*, MouseEventArgs*>*>(genericHandler);
	ASSERT(handler);

	handler->invoke(genericTarget, this);
}

}	// UI
}
