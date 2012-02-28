#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{
namespace Media
{

ClockCollection::ClockCollection()
{
}

ClockGroup::ClockGroup(TimelineGroup* timeline) : Clock(timeline)
{
	m_children = new ClockCollection();
}

ClockCollection* ClockGroup::get_Children()
{
	return m_children;
}

void ClockGroup::AddChild(Clock* clock)
{
	clock->m_parent = this;
	m_children->Add(clock);
}

}	// Media
}	// UI
}
