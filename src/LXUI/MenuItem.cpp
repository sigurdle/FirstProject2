#include "stdafx.h"
#include "LXUI2.h"
#include "MenuItem.h"

#include <functional>

namespace System
{
namespace UI
{

//void ApplyStyle(Style* style, FrameworkElement* element);
//Object* CreateObjectFromElement(Type* pType, Object* parentObject, XmlData::Node* node, Type** pReturnType);

__live_object_ptr<Style> MenuItemStyle;

DependencyProperty* MenuItem::s_IsSubmenuOpenProperty = RegisterProperty(WSTR("IsSubmenuOpen"), typeid(bool), typeid(MenuItem), BoolObject::get_False(), PropertyMetaData(None));
DependencyProperty* MenuItem::s_CommandProperty = RegisterProperty(WSTR("Command"), typeid(ICommand), typeid(MenuItem), NULL, PropertyMetaData(None));
DependencyProperty* MenuItem::s_CommandParameterProperty = RegisterProperty(WSTR("CommandParameter"), typeid(Object), typeid(MenuItem), NULL, PropertyMetaData(None));
DependencyProperty* MenuItem::s_CommandTargetProperty = RegisterProperty(WSTR("CommandTarget"), typeid(IInputElement), typeid(MenuItem), NULL, PropertyMetaData(None));

MenuItem::MenuItem()
{
	Init();
}

MenuItem::MenuItem(Object* header, ICommand* command, Object* commandParameter)
{
	Init();

	if (header) set_Header(header);
	if (command) set_Command(command);
	if (commandParameter) set_CommandParameter(commandParameter);
}

MenuItem::~MenuItem()
{
}

void MenuItem::Init()
{
	if (MenuItemStyle == NULL)
	{
		XmlData::Document* document = new XmlData::Document;

		StringW* filename = MakeFilePath(_Module, L"../../../MenuItemStyle.lxui");
		document->load(filename);

		Type* returnType;
		MenuItemStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));
	}

	set_Style(MenuItemStyle);

	/*
	ApplyStyle(get_Style(), this);

	InitScript();
	*/
}

void MenuItem::AddItem(Object* item)
{
	MenuItem* menuitem = dynamic_cast<MenuItem*>(item);
	if (menuitem == NULL)
	{
		menuitem = new MenuItem;
		menuitem->set_Header(item);
	}

//	m_owner->m_itemContainerGenerator->m_containers.push_back(listboxitem);

	if (m_itemsPresenter)
	{
		m_itemsPresenter->m_panel->AddChild(menuitem);
	}
}

// virtual
ICommand* MenuItem::get_Command()
{
	return dynamic_cast<ICommand*>(GetValue(get_CommandProperty()));
}

static void _CanExecuteChanged(Object* object)
{
	((MenuItem*)object)->CanExecuteChanged();
}

void MenuItem::set_Command(ICommand* command)
{
	SetValue(get_CommandProperty(), dynamic_cast<Object*>(command));

	// TODO, not here
	if (command)
	{

		ICommand* oldCommand = NULL;
		if (oldCommand)
		{
			ASSERT(0);
			//disconnect
		}

		if (command)
		{
			command->get_CanExecuteChanged().connect(_CanExecuteChanged);
		//	get_Command()->get_CanExecuteChanged().connect(std::bind1st(std::mem_fun(&MenuItem::CanExecuteChanged), this);
			CanExecuteChanged();
		}
	}
}

// virtual
Object* MenuItem::get_CommandParameter()
{
	return GetValue(get_CommandParameterProperty());
}

void MenuItem::set_CommandParameter(Object* commandParameter)
{
	SetValue(get_CommandParameterProperty(), commandParameter);
}

void MenuItem::CanExecuteChanged()
{
	ICommand* command = get_Command();
	RoutedCommand* routedCommand = dynamic_cast<RoutedCommand*>(command);
	if (routedCommand)
	{
		IInputElement* commandTarget = get_CommandTarget();
		if (commandTarget == NULL) commandTarget = this;	// ??

		bool canExecute = routedCommand->CanExecute(get_CommandParameter(), commandTarget);

		set_IsEnabled(canExecute);
	}
	else
	{
		bool canExecute = command->CanExecute(get_CommandParameter());

		set_IsEnabled(canExecute);
	}
}

void MenuItem::set_CommandTarget(IInputElement* commandTarget)
{
	SetValue(get_CommandTargetProperty(), dynamic_cast<Object*>(commandTarget));
}

// virtual
IInputElement* MenuItem::get_CommandTarget()
{
	return dynamic_cast<IInputElement*>(GetValue(get_CommandTargetProperty()));
}

/*
long MenuItem::get_CmdID() const
{
	return m_CmdID;
}
*/

bool MenuItem::get_IsSubmenuOpen()
{
	return static_cast<BoolObject*>(GetValue(get_IsSubmenuOpenProperty()))->GetValue();
}

void MenuItem::set_IsSubmenuOpen(bool isSubmenuOpen)
{
	SetValue(get_IsSubmenuOpenProperty(), BoolObject::GetObject(isSubmenuOpen));
}

void MenuItem::OnMouseDown(MouseButtonEventArgs* args)
{
	args->set_Handled(true);

	if (get_HasItems())
	{
		set_IsSubmenuOpen(true);
	}
}

void MenuItem::OnMouseUp(MouseButtonEventArgs* args)
{
	args->set_Handled(true);

//	return;
	if (!get_HasItems())
	{
		ICommand* command = get_Command();
		if (command)
		{
			RoutedCommand* routedCommand = dynamic_cast<RoutedCommand*>(command);
			if (routedCommand)
			{
				IInputElement* commandTarget = get_CommandTarget();
				if (commandTarget == NULL) commandTarget = this;	// ??

				routedCommand->Execute(get_CommandParameter(), commandTarget);
			}
			else
			{
				command->Execute(get_CommandParameter());
			}
		}
	}
}

#if 0
void MenuItem::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	if (evt->get_eventPhase() != CAPTURING_PHASE)
	{
		if (type == MouseEvent::mouseover)
		{
			evt->stopPropagation();
			m_pBorder->set_Background(new SolidColorBrush(new Color(120, 190, 255)));
			Invalidate();
		}
		else if (type == MouseEvent::mouseout)
		{
			evt->stopPropagation();
			m_pBorder->set_Background(NULL);
			Invalidate();
		}
		else if (type == MouseEvent::mousedown)
		{
			evt->stopPropagation();
		}
		else if (type == MouseEvent::mouseup)
		{
			evt->stopPropagation();

		//	printf("sending command\n");
		//	fflush(stdout);
			{
				CommandInvokeEvent* evt = new CommandInvokeEvent;
				evt->InitCommandInvokeEvent(WSTR("command"), m_CmdID);

				dispatchEvent(evt);
			}
		}
	}
}
#endif

}	// UI
}
