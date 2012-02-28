#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

RoutedEvent::RoutedEvent(StringIn name, RoutingStrategy routingStrategy, const Type_Info& handlerType, ClassType* ownerType) :
	m_name(name),
	m_routingStrategy(routingStrategy),
	m_handlerType(handlerType),
	m_ownerType(ownerType)
{
}

String RoutedEvent::get_Name()
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
	return m_ownerType;
}

}	// Gui
}	// System
