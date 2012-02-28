#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{
namespace Media
{

Clock::Clock(Timeline* timeline) : m_timeline(timeline)
{
	if (timeline == NULL) throw std::exception("null pointer");
}

Nullable<double> Clock::get_CurrentProgress()
{
	return m_currentProgress;
}

double Clock::get_CurrentTime()
{
	return m_currentTime;
}

bool Clock::get_HasControllableRoot()
{
// TODO
	return false;
}

// virtual
void Clock::DiscontinuousTimeMovement()
{
}

// virtual
void Clock::SpeedChanged()
{
}

// virtual
void Clock::Stopped()
{
}

}	// Media
}	// UI
}
