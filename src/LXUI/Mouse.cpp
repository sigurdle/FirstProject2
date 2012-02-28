#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

RoutedEvent* Mouse::s_MouseMoveEvent = EventManager::RegisterRoutedEvent(WSTR("MouseMove"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, MouseEventArgs*>), typeid(Mouse));
RoutedEvent* Mouse::s_PreviewMouseMoveEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewMouseMove"), RoutingStrategy_Tunnel, typeid(stub_interface2<void, Object*, MouseEventArgs*>), typeid(Mouse));

RoutedEvent* Mouse::s_MouseLeaveEvent = EventManager::RegisterRoutedEvent(WSTR("MouseLeave"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, MouseEventArgs*>), typeid(Mouse));
RoutedEvent* Mouse::s_PreviewMouseLeaveEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewMouseLeave"), RoutingStrategy_Tunnel, typeid(stub_interface2<void, Object*, MouseEventArgs*>), typeid(Mouse));

RoutedEvent* Mouse::s_MouseEnterEvent = EventManager::RegisterRoutedEvent(WSTR("MouseEnter"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, MouseEventArgs*>), typeid(Mouse));
RoutedEvent* Mouse::s_PreviewMouseEnterEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewMouseEnter"), RoutingStrategy_Tunnel, typeid(stub_interface2<void, Object*, MouseEventArgs*>), typeid(Mouse));

RoutedEvent* Mouse::s_MouseDownEvent = EventManager::RegisterRoutedEvent(WSTR("MouseDown"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, MouseButtonEventArgs*>), typeid(Mouse));
RoutedEvent* Mouse::s_PreviewMouseDownEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewMouseDown"), RoutingStrategy_Tunnel, typeid(stub_interface2<void, Object*, MouseButtonEventArgs*>), typeid(Mouse));

RoutedEvent* Mouse::s_MouseUpEvent = EventManager::RegisterRoutedEvent(WSTR("MouseUp"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, MouseButtonEventArgs*>), typeid(Mouse));
RoutedEvent* Mouse::s_PreviewMouseUpEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewMouseUp"), RoutingStrategy_Tunnel, typeid(stub_interface2<void, Object*, MouseButtonEventArgs*>), typeid(Mouse));

RoutedEvent* TextCompositionManager::s_TextInputEvent = EventManager::RegisterRoutedEvent(WSTR("TextInput"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, TextCompositionEventArgs*>), typeid(TextCompositionManager));

}	// UI

template class UIEXT signal2<Object*, UI::MouseEventArgs*>;
template class UIEXT signal2<Object*, UI::MouseButtonEventArgs*>;

}
