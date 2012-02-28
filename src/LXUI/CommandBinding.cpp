#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

CommandBindingCollection::CommandBindingCollection()
{
}

//

CommandBinding::CommandBinding()
{
	m_command = NULL;
}

CommandBinding::CommandBinding(ICommand* command,
		ExecutedHandler_arg executedHandler,
		CanExecuteHandler_arg canExecuteHandler
		/*
	const signal2<Object*, ExecutedRoutedEventArgs*>::slot_function_type& ExecutedHandler,
	const signal2<Object*, CanExecuteRoutedEventArgs*>::slot_function_type& CanExecuteHandler
	*/)
{
	m_command = command;

	Executed.connect(executedHandler);
	CanExecute.connect(canExecuteHandler);
}

ICommand* CommandBinding::get_Command()
{
	return m_command;
}

void CommandBinding::set_Command(ICommand* command)
{
	m_command = command;
}

/*
Object* CommandBinding::get_Parameter()
{
	return m_parameter;
}
*/

}	// UI
}
