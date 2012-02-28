#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

MouseButtonEventArgs::MouseButtonEventArgs(void* mousedevice, int timestamp) : MouseEventArgs(mousedevice, timestamp)
{
}

void MouseButtonEventArgs::InvokeEventHandler(Object* genericTarget, stub_interface_base* genericHandler)
{
	stub_interface2<void, Object*, MouseButtonEventArgs*>* handler = dynamic_cast<stub_interface2<void, Object*, MouseButtonEventArgs*>*>(genericHandler);
	ASSERT(handler);

	handler->invoke(genericTarget, this);
}

}	// UI
}