#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

MouseButtonEventArgs::MouseButtonEventArgs(void* mousedevice, int timestamp) : MouseEventArgs(mousedevice, timestamp)
{
}

void MouseButtonEventArgs::InvokeEventHandler(Object* genericTarget, IFunction* genericHandler)
{
	IFunction2<void, Object*, MouseButtonEventArgs*>* handler = dynamic_cast<IFunction2<void, Object*, MouseButtonEventArgs*>*>(genericHandler);
	ASSERT(handler);

	handler->Call(genericTarget, this);
}

}	// Gui
}
