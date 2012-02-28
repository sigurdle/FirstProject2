#include "stdafx.h"
#include "LXUI2.h"
#include "CheckBox.h"

namespace System
{
namespace UI
{

DependencyProperty* ToggleButton::s_IsCheckedProperty = RegisterProperty(WSTR("IsChecked"), typeid(bool), typeid(ToggleButton), BoolObject::get_False(), PropertyMetaData(None));

RoutedEvent* ToggleButton::s_CheckedEvent = EventManager::RegisterRoutedEvent(WSTR("Checked"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, RoutedEventArgs*>), typeid(ToggleButton));
RoutedEvent* ToggleButton::s_UncheckedEvent = EventManager::RegisterRoutedEvent(WSTR("Unchecked"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, RoutedEventArgs*>), typeid(ToggleButton));

ToggleButton::ToggleButton()
{
}

// ????
// TODO, OnMouseLeftButtonDown
void ToggleButton::OnMouseDown(MouseButtonEventArgs* args)
{
	args->set_Handled(true);

//	CaptureMouse();

	if (!get_IsChecked())
	{
		SetValue(get_IsCheckedProperty(), BoolObject::get_True());
		RaiseEvent(new RoutedEventArgs(s_CheckedEvent));
	}
	else
	{
		SetValue(get_IsCheckedProperty(), BoolObject::get_False());
		RaiseEvent(new RoutedEventArgs(s_UncheckedEvent));
	}
}

signal2<Object*, RoutedEventArgs*>& ToggleButton::get_Checked()
{
	RoutedEvent* routedEvent = s_CheckedEvent;
	int index = routedEvent->GetIndex();

	if (m_handlers[index] == NULL)
	{
		ClassType* pSigType = dynamic_cast<ClassType*>(routedEvent->get_HandlerType()->GetClass()->LookupType(ASTR("signal_type"))->GetStripped());
		m_handlers[index] = (signal_base*)newobj(pSigType);
	}

	return *dynamic_cast<signal2<Object*, RoutedEventArgs*>*>(m_handlers[index]);
}

signal2<Object*, RoutedEventArgs*>& ToggleButton::get_Unchecked()
{
	RoutedEvent* routedEvent = s_UncheckedEvent;
	int index = routedEvent->GetIndex();

	if (m_handlers[index] == NULL)
	{
		ClassType* pSigType = dynamic_cast<ClassType*>(routedEvent->get_HandlerType()->GetClass()->LookupType(ASTR("signal_type"))->GetStripped());
		m_handlers[index] = (signal_base*)newobj(pSigType);
	}

	return *dynamic_cast<signal2<Object*, RoutedEventArgs*>*>(m_handlers[index]);
}

bool ToggleButton::get_IsChecked()
{
	return static_cast<BoolObject*>(GetValue(get_IsCheckedProperty()))->GetValue();
}

void ToggleButton::set_IsChecked(bool isChecked)
{
	SetValue(get_IsCheckedProperty(), BoolObject::GetObject(isChecked));
}

CheckBox::CheckBox()
{
}

}	// UI
}
