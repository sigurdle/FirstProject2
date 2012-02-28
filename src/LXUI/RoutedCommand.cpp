#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

RoutedCommand::RoutedCommand()
{
}

bool RoutedCommand::CanExecute(Object* parameter)
{
	ASSERT(0);
	return false;
}

bool RoutedCommand::CanExecute(Object* parameter, IInputElement* target)
{
	CanExecuteRoutedEventArgs* args = new CanExecuteRoutedEventArgs(this, parameter);

	args->set_RoutedEvent(CommandManager::get_PreviewCanExecuteEvent());
	target->RaiseEvent(args);

	if (!args->get_Handled())
	{
		args->set_RoutedEvent(CommandManager::get_CanExecuteEvent());
		target->RaiseEvent(args);
	}

	return args->get_CanExecute();
}

void RoutedCommand::Execute(Object* parameter)
{
	ASSERT(0);
}

void RoutedCommand::Execute(Object* parameter, IInputElement* target)
{
	ExecutedRoutedEventArgs* args = new ExecutedRoutedEventArgs(this, parameter);

	args->set_RoutedEvent(CommandManager::get_PreviewExecutedEvent());
	target->RaiseEvent(args);

	if (!args->get_Handled())
	{
		args->set_RoutedEvent(CommandManager::get_ExecutedEvent());
		target->RaiseEvent(args);
	}
}

signal1<Object*>& RoutedCommand::get_CanExecuteChanged()
{
	return CanExecuteChanged;
}

// RoutedUICommand

RoutedUICommand::RoutedUICommand()
{
}

}
}
