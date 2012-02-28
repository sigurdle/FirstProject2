#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

EventManager::Private* EventManager::s_private;

// static
RoutedEvent* EventManager::RegisterRoutedEvent(StringIn name, RoutingStrategy routingStrategy, const Type_Info& handlerType, ClassType* ownerType)
{
	if (s_private == nullptr)
	{
		s_private = new Private();
	}

	RoutedEvent* evt = new RoutedEvent(name, routingStrategy, handlerType, ownerType);
	evt->m_index = s_private->m_routedEvents.size();
	s_private->m_routedEvents.push_back(evt);

	return evt;
}

EventManager::PerClass::PerClass()
{
//	m_handlers.resize(EventManager::s_private->m_routedEvents.size());
}

// static
void EventManager::InvokeClassHandlers(ClassType* classType, Object* instance, RoutedEventArgs* args)
{
	RoutedEvent* routedEvent = args->get_RoutedEvent();

	PerClass* perclass = s_private->s_perclass.find(classType->get_QName())->second;
	if (perclass)
	{
		perclass->m_handlers.resize(EventManager::s_private->m_routedEvents.size());

		for (auto it = perclass->m_handlers[routedEvent->m_index].begin(); it != perclass->m_handlers[routedEvent->m_index].end(); ++it)
		{
			args->InvokeEventHandler(instance, *it);
		}
	}

	for (auto it = classType->m_bases.begin(); it != classType->m_bases.end(); ++it)
	{
		InvokeClassHandlers((*it)->m_pClass->AsClass(), instance, args);
	}
}

// static
void EventManager::RegisterClassHandler(ClassType* classType, RoutedEvent* pEvent, IFunction* handler)
{
	if (s_private == nullptr)
	{
		s_private = new Private();
	}

	PerClass* perclass = s_private->s_perclass[classType->get_QName()];
	if (perclass == nullptr)
	{
		perclass = new PerClass();
		s_private->s_perclass[classType->get_QName()] = perclass;
	}

	perclass->m_handlers.resize(EventManager::s_private->m_routedEvents.size());
	perclass->m_handlers[pEvent->m_index].push_back(handler);
}

// static
void EventManager::RegisterClassHandler(ClassType* classType, RoutedEvent* pEvent, IFunction* handler, bool handledEventsToo)
{
	ASSERT(0);
}

}	// Gui
}	// System
