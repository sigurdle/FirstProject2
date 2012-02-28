#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

RoutedEvent::RoutedEvent(StringW* name, RoutingStrategy routingStrategy, const Type_Info& handlerType, const Type_Info& ownerType) :
	m_name(name),
	m_routingStrategy(routingStrategy),
	m_handlerType(handlerType),
	m_ownerType(ownerType)
{
}

StringW* RoutedEvent::get_Name()
{
	return m_name;
}

RoutingStrategy RoutedEvent::get_RoutingStrategy()
{
	return m_routingStrategy;
}

ClassType* RoutedEvent::get_HandlerType()
{
	return dynamic_cast<ClassType*>(m_handlerType.GetType());
}

ClassType* RoutedEvent::get_OwnerType()
{
	return dynamic_cast<ClassType*>(m_ownerType.GetType());
}

}	// UI
}
