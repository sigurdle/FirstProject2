#include "stdafx.h"
#include "LXUI2.h"
#include "AnimationClock.h"

namespace System
{
namespace UI
{
namespace Media
{

AnimationClock::AnimationClock(AnimationTimeline* timeline) : Clock(timeline)
{
}

Object* AnimationClock::GetCurrentValue(Object* defaultOriginValue, Object* defaultDestinationValue)
{
	return get_Timeline()->GetCurrentValue(defaultOriginValue, defaultDestinationValue, this);
}

}	// Media
}	// UI
}
