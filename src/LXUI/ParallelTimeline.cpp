#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{
namespace Media
{

ParallelTimeline::ParallelTimeline()
{
}

Clock* ParallelTimeline::AllocateClock()
{
	ClockGroup* pClockGroup = new ClockGroup(this);

	int count = get_Children()->GetCount();

	for (int i = 0; i < count; i++)
	{
		Clock* pChildClock = get_Children()->get_Item(i)->CreateClock(false);
		pClockGroup->AddChild(pChildClock);
	}

	return pClockGroup;
}

}	// Media
}	// UI
}
