#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

DependencyProperty* RangeBase::s_MinimumProperty = RegisterProperty(WSTR("Minimum"), typeid(double), typeid(RangeBase), DoubleObject::GetObject(0.0), PropertyMetaData(None));
DependencyProperty* RangeBase::s_MaximumProperty = RegisterProperty(WSTR("Maximum"), typeid(double), typeid(RangeBase), DoubleObject::GetObject(1.0), PropertyMetaData(None));
DependencyProperty* RangeBase::s_ValueProperty = RegisterProperty(WSTR("Value"), typeid(double), typeid(RangeBase), DoubleObject::GetObject(0.0), PropertyMetaData(None));

RoutedEvent* RangeBase::s_ValueChangedEvent = EventManager::RegisterRoutedEvent(WSTR("ValueChanged"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, RoutedPropertyChangedEventArgs<double>*>), typeid(RangeBase));

template class UIEXT RoutedPropertyChangedEventArgs<double>;
template class UIEXT signal2<Object*, RoutedPropertyChangedEventArgs<double>*>;

RangeBase::RangeBase()
{
}

double RangeBase::get_Value()
{
	return static_cast<DoubleObject*>(GetValue(get_ValueProperty()))->GetValue();
}

void RangeBase::set_Value(double value)
{
	SetValue(get_ValueProperty(), DoubleObject::GetObject(value));
}

double RangeBase::get_Minimum()
{
	return static_cast<DoubleObject*>(GetValue(get_MinimumProperty()))->GetValue();
}

void RangeBase::set_Minimum(double minimum)
{
	SetValue(get_MinimumProperty(), DoubleObject::GetObject(minimum));
}

double RangeBase::get_Maximum()
{
	return static_cast<DoubleObject*>(GetValue(get_MaximumProperty()))->GetValue();
}

void RangeBase::set_Maximum(double maximum)
{
	SetValue(get_MaximumProperty(), DoubleObject::GetObject(maximum));
}

signal2<Object*, RoutedPropertyChangedEventArgs<double>*>& RangeBase::get_ValueChanged()
{
	RoutedEvent* routedEvent = get_ValueChangedEvent();
	int index = routedEvent->GetIndex();

	if (m_handlers[index] == NULL)
	{
		VERIFY(routedEvent->get_HandlerType()->GetClass());
		ClassType* pSigType = dynamic_cast<ClassType*>(routedEvent->get_HandlerType()->GetClass()->LookupType(ASTR("signal_type"))->GetStripped());
		VERIFY(pSigType);
		m_handlers[index] = (signal_base*)newobj(pSigType);
	}

	return *dynamic_cast<signal2<Object*, RoutedPropertyChangedEventArgs<double>*>*>(m_handlers[index]);
}

}	// UI
}
