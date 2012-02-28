#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

RoutedEvent* CommandManager::s_CanExecuteEvent = EventManager::RegisterRoutedEvent(WSTR("CanExecute"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, CanExecuteRoutedEventArgs*>), typeid(CommandManager));
RoutedEvent* CommandManager::s_PreviewCanExecuteEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewCanExecute"), RoutingStrategy_Tunnel, typeid(stub_interface2<void, Object*, CanExecuteRoutedEventArgs*>), typeid(CommandManager));
RoutedEvent* CommandManager::s_ExecutedEvent = EventManager::RegisterRoutedEvent(WSTR("Executed"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, ExecutedRoutedEventArgs*>), typeid(CommandManager));
RoutedEvent* CommandManager::s_PreviewExecutedEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewExecuted"), RoutingStrategy_Tunnel, typeid(stub_interface2<void, Object*, ExecutedRoutedEventArgs*>), typeid(CommandManager));

// static
void CommandManager::AddCanExecuteHandler(UIElement* element, CanExecuteHandler_arg handler)
{
//	element->m_bindings.push_back(handler);
}

// static
void CommandManager::AddExecutedHandler(UIElement* element, ExecutedHandler_arg handler)
{
}

// static
void CommandManager::AddPreviewCanExecuteHandler(UIElement* element, CanExecuteHandler_arg handler)
{
}

// static
void CommandManager::AddPreviewExecutedHandler(UIElement* element, ExecutedHandler_arg handler)
{
}

// static
void RegisterClassCommandBinding(Type_Info& classType, CommandBinding* commandBinding)
{
}

}
}
