#include "stdafx.h"
#include "GUI2.h"
//#include "MouseEventArgs.h"

namespace System
{
namespace Gui
{

MouseEventArgs::MouseEventArgs(void* mousedevice, int timestamp) : InputEventArgs(timestamp)
{
}

Point MouseEventArgs::GetPosition(UIElement* relativeTo)
{
	gm::matrix3f m = gm::matrix3f::getIdentity();

	Visual* p = relativeTo;
	Visual* parent;
	while (parent = p->get_Parent())
	{
		Transform* transform = p->get_Transform();
		if (transform)
		{
			m *= transform->get_Matrix();
		}

		p = parent;
	}

	return m.getInverse().transform(m_clientpos);

	/*
	Visual* visual = dynamic_cast<Visual*>(relativeTo);
	ASSERT(visual);
	return visual->WindowToElement(m_windowX, m_windowY);
	*/
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

void MouseEventArgs::InvokeEventHandler(Object* genericTarget, IFunction* genericHandler)
{
	IFunction2<void, Object*, MouseEventArgs*>* handler = dynamic_cast<IFunction2<void, Object*, MouseEventArgs*>*>(genericHandler);
	ASSERT(handler);

	handler->Call(genericTarget, this);
}

}	// UI
}
