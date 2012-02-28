#include "stdafx.h"
#include "LXUI2.h"
#include "MediaClock.h"

namespace System
{
namespace UI
{
namespace Media
{

MediaTimeline::MediaTimeline()
{
}

Clock* MediaTimeline::AllocateClock()
{
	MediaClock* pClock = new MediaClock(this);
	return pClock;
}

}	// Media
}	// UI
}
