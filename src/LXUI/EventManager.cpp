#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

EventManager::RegisteredEvents* EventManager::s_registeredEvents;

// static
RoutedEvent* EventManager::RegisterRoutedEvent(StringW* name, RoutingStrategy routingStrategy, const Type_Info& handlerType, const Type_Info& ownerType)
{
	if (s_registeredEvents == NULL)
	{
		s_registeredEvents = new RegisteredEvents;
	//	AddPersistentLiveRoot((void**)&s_registeredEvents);
	}

	RoutedEvent* evt = new RoutedEvent(name, routingStrategy, handlerType, ownerType);
	evt->m_index = s_registeredEvents->m_items.size();

	s_registeredEvents->m_items.push_back(evt);

	return evt;
}

map<StringA*,EventManager::PerClass*> EventManager::s_perclass;

EventManager::PerClass::PerClass()
{
	m_handlers.resize(EventManager::s_registeredEvents->m_items.size());
}

/*
// TODO remove this
class EventManagerInit
{
public:
	EventManagerInit()
	{
		AddPersistentLiveRoot((void**)&EventManager::s_perclass);
	}
};

static EventManagerInit init;
*/

// static
void EventManager::InvokeClassHandlers(ClassType* classType, Object* instance, RoutedEventArgs* args)
{
	RoutedEvent* routedEvent = args->get_RoutedEvent();

	PerClass* perclass = s_perclass.find(classType->get_QName())->second;
	if (perclass)
	{
		list<stub_interface_base*>::iterator it = perclass->m_handlers[routedEvent->m_index].begin();
		while (it != perclass->m_handlers[routedEvent->m_index].end())
		{
			args->InvokeEventHandler(instance, *it);
			++it;
		}
	}

	for (int i = 0; i < classType->m_bases.size(); i++)
	{
		InvokeClassHandlers(classType->m_bases[i]->m_pClass->GetClass(), instance, args);
	}
}

// static
void EventManager::RegisterClassHandler(const Type_Info& classType, RoutedEvent* pEvent, stub_interface_base* handler)
{
	PerClass* perclass = s_perclass[classType.GetType()->GetClass()->get_QName()];
	if (perclass == NULL)
	{
		perclass = new PerClass;
		s_perclass[classType.GetType()->GetClass()->get_QName()] = perclass;
	}

	perclass->m_handlers[pEvent->m_index].push_back(handler);
}

// static
void EventManager::RegisterClassHandler(const Type_Info& classType, RoutedEvent* pEvent, stub_interface_base* handler, bool handledEventsToo)
{
	ASSERT(0);
}

}	// UI
}
