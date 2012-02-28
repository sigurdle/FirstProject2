#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{
namespace Media
{

DependencyProperty* TimelineGroup::s_ChildrenProperty = RegisterProperty(WSTR("Children"), typeid(TimelineCollection), typeid(TimelineGroup), NULL, PropertyMetaData(None));

TimelineCollection::TimelineCollection()
{
}

//

TimelineGroup::TimelineGroup()
{
	set_Children(new TimelineCollection());
}

TimelineCollection* TimelineGroup::get_Children()
{
	return static_cast<TimelineCollection*>(GetValue(get_ChildrenProperty()));
}

void TimelineGroup::set_Children(TimelineCollection* children)
{
	SetValue(get_ChildrenProperty(), children);
}

}	// Media
}	// UI
}
