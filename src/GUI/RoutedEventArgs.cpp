#include "stdafx.h"
#include "GUI2.h"

namespace System
{

namespace Gui
{

EventArgs::EventArgs()
{
}

//template class GUIEXT signal2<Object*, RoutedEventArgs*>;

RoutedEventArgs::RoutedEventArgs()
{
	m_handled = false;
	m_routedEvent = NULL;
	m_source = NULL;
}

RoutedEventArgs::RoutedEventArgs(RoutedEvent* routedEvent)
{
	m_handled = false;
	m_routedEvent = routedEvent;
	m_source = NULL;
}

RoutedEventArgs::RoutedEventArgs(RoutedEvent* routedEvent, Object* source)
{
	m_handled = false;
	m_routedEvent = routedEvent;
	m_source = source;
}

RoutedEvent* RoutedEventArgs::get_RoutedEvent()
{
	return m_routedEvent;
}

void RoutedEventArgs::set_RoutedEvent(RoutedEvent* routedEvent)
{
	m_routedEvent = routedEvent;
}

void RoutedEventArgs::set_Handled(bool handled)
{
	m_handled = handled;
}

Object* RoutedEventArgs::get_Source()
{
	return m_source;
}

void RoutedEventArgs::set_Source(Object* source)
{
	OnSetSource(source);
	m_source = source;
//	OnSetSource(source);
}

void RoutedEventArgs::InvokeEventHandler(Object* genericTarget, IFunction* genericHandler)
{
	IFunction2<void, Object*, RoutedEventArgs*>* handler = dynamic_cast<IFunction2<void, Object*, RoutedEventArgs*>*>(genericHandler);
	ASSERT(handler);
	handler->Call(genericTarget, this);
}

void DragEventArgs::InvokeEventHandler(Object* genericTarget, IFunction* genericHandler)
{
	IFunction2<void, Object*, DragEventArgs*>* handler = dynamic_cast<IFunction2<void, Object*, DragEventArgs*>*>(genericHandler);
	ASSERT(handler);
	handler->Call(genericTarget, this);
}

// virtual
void RoutedEventArgs::OnSetSource(Object* source)
{
	// Override this if you want
}

#if 0
// CanExecuteRoutedEventArgs

CanExecuteRoutedEventArgs::CanExecuteRoutedEventArgs(ICommand* command, Object* parameter) :
	m_command(command),
	m_parameter(parameter),
	m_canExecute(false)
{
}

void CanExecuteRoutedEventArgs::InvokeEventHandler(Object* genericTarget, stub_interface_base* genericHandler)
{
	stub_interface2<void, Object*, CanExecuteRoutedEventArgs*>* handler = dynamic_cast<stub_interface2<void, Object*, CanExecuteRoutedEventArgs*>*>(genericHandler);
	ASSERT(handler);

	handler->invoke(genericTarget, this);
}

ICommand* CanExecuteRoutedEventArgs::get_Command()
{
	return m_command;
}

Object* CanExecuteRoutedEventArgs::get_Parameter()
{
	return m_parameter;
}

bool CanExecuteRoutedEventArgs::get_CanExecute()
{
	return m_canExecute;
}

void CanExecuteRoutedEventArgs::set_CanExecute(bool canExecute)
{
	m_canExecute = canExecute;
}

///

ExecutedRoutedEventArgs::ExecutedRoutedEventArgs(ICommand* command, Object* parameter) :
	m_command(command),
	m_parameter(parameter)
{
}

void ExecutedRoutedEventArgs::InvokeEventHandler(Object* genericTarget, stub_interface_base* genericHandler)
{
	stub_interface2<void, Object*, ExecutedRoutedEventArgs*>* handler = dynamic_cast<stub_interface2<void, Object*, ExecutedRoutedEventArgs*>*>(genericHandler);
	ASSERT(handler);

	handler->invoke(genericTarget, this);
}

ICommand* ExecutedRoutedEventArgs::get_Command()
{
	return m_command;
}

Object* ExecutedRoutedEventArgs::get_Parameter()
{
	return m_parameter;
}


//
#endif
InputEventArgs::InputEventArgs(int timestamp)
{
	m_timestamp = timestamp;
}

//

KeyboardEventArgs::KeyboardEventArgs(int timestamp) : InputEventArgs(timestamp)
{
}

KeyEventArgs::KeyEventArgs(
		void* /*KeyboardDevice*/ keyboard,
		void* /*PresentationSource*/ inputSource,
		int timestamp,
		int/*Key*/ key) :
	KeyboardEventArgs(timestamp),
	m_key(key)
{
}

void KeyEventArgs::InvokeEventHandler(Object* genericTarget, IFunction* genericHandler)
{
	IFunction2<void, Object*, KeyEventArgs*>* handler = dynamic_cast<IFunction2<void, Object*, KeyEventArgs*>*>(genericHandler);
	ASSERT(handler);
	handler->Call(genericTarget, this);
}

void TextCompositionEventArgs::InvokeEventHandler(Object* genericTarget, IFunction* genericHandler)
{
	IFunction2<void, Object*, TextCompositionEventArgs*>* handler = dynamic_cast<IFunction2<void, Object*, TextCompositionEventArgs*>*>(genericHandler);
	ASSERT(handler);
	handler->Call(genericTarget, this);
}

}	// Gui
}	// System
