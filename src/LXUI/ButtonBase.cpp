#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

DependencyProperty* ButtonBase::s_IsPressedProperty = RegisterProperty(WSTR("IsPressed"), typeid(bool), typeid(ButtonBase), BoolObject::GetObject(false), PropertyMetaData(None));
DependencyProperty* ButtonBase::s_CommandProperty = RegisterProperty(WSTR("Command"), typeid(ICommand), typeid(ButtonBase), NULL, PropertyMetaData(None));
DependencyProperty* ButtonBase::s_CommandParameterProperty = RegisterProperty(WSTR("CommandParameter"), typeid(Object), typeid(ButtonBase), NULL, PropertyMetaData(None));
DependencyProperty* ButtonBase::s_CommandTargetProperty = RegisterProperty(WSTR("CommandTarget"), typeid(IInputElement), typeid(ButtonBase), NULL, PropertyMetaData(None));

RoutedEvent* ButtonBase::s_ClickEvent = EventManager::RegisterRoutedEvent(WSTR("Click"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, RoutedEventArgs*>), typeid(ButtonBase));

ButtonBase::ButtonBase()
{
}

signal2<Object*, RoutedEventArgs*>& ButtonBase::get_Click()
{
	RoutedEvent* routedEvent = get_ClickEvent();
	int index = routedEvent->GetIndex();

	if (m_handlers[index] == NULL)
	{
		ClassType* pSigType = dynamic_cast<ClassType*>(routedEvent->get_HandlerType()->GetClass()->LookupType(ASTR("signal_type"))->GetStripped());
		m_handlers[index] = (signal_base*)newobj(pSigType);
	}

	return *dynamic_cast<signal2<Object*, RoutedEventArgs*>*>(m_handlers[index]);
}

bool ButtonBase::get_IsPressed()
{
	return static_cast<BoolObject*>(GetValue(get_IsPressedProperty()))->GetValue();
}

// virtual
ICommand* ButtonBase::get_Command()
{
	return dynamic_cast<ICommand*>(GetValue(get_CommandProperty()));
}

static void _CanExecuteChanged(Object* object)
{
	((ButtonBase*)object)->CanExecuteChanged();
}

void ButtonBase::set_Command(ICommand* command)
{
	SetValue(get_CommandProperty(), dynamic_cast<Object*>(command));

	// TODO, not here
	get_Command()->get_CanExecuteChanged().connect(&_CanExecuteChanged);
	CanExecuteChanged();
}

// virtual
Object* ButtonBase::get_CommandParameter()
{
	return GetValue(get_CommandParameterProperty());
}

void ButtonBase::set_CommandParameter(Object* commandParameter)
{
	SetValue(get_CommandParameterProperty(), commandParameter);
}

void ButtonBase::CanExecuteChanged()
{
	IInputElement* commandTarget = get_CommandTarget();
	if (commandTarget == NULL) commandTarget = this;	// ??

	RoutedCommand* routedCommand = dynamic_cast<RoutedCommand*>(get_Command());
	bool canExecute = routedCommand->CanExecute(get_CommandParameter(), commandTarget);

	set_IsEnabled(canExecute);
}

void ButtonBase::set_CommandTarget(IInputElement* commandTarget)
{
	SetValue(get_CommandTargetProperty(), dynamic_cast<Object*>(commandTarget));
}

// virtual
IInputElement* ButtonBase::get_CommandTarget()
{
	return dynamic_cast<IInputElement*>(GetValue(get_CommandTargetProperty()));
}

// virtual
void ButtonBase::OnClick()
{
	RoutedEventArgs* args = new RoutedEventArgs;
	args->set_RoutedEvent(get_ClickEvent());

	RaiseEvent(args);
}

}	// UI
}
