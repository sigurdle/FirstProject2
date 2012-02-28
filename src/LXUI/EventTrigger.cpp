#include "stdafx.h"
#include "LXUI2.h"
#include "EventTrigger.h"

namespace System
{
namespace UI
{

TriggerActionCollection::TriggerActionCollection()
{
}

EventTrigger::EventTrigger()
{
	m_actions = new TriggerActionCollection;
}

TriggerActionCollection* EventTrigger::get_Actions()
{
	return m_actions;
}

}	// UI
}
