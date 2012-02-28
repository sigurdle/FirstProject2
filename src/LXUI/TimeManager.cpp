#include "stdafx.h"
#include "LXUI.h"

namespace System
{
namespace UI
{

using namespace Media;

TimeManager::TimeManager()
{
	m_tps = 18;

	m_curTime = 0;
// TODO

//	m_timerID = SetTimer(1000.0 / m_tps, this);
}

//void TimeManager::dispatchEvent2(Event* evt, bool bCapture, bool* doDefault)
void TimeManager::OnTimer(UINT nID)
{
	m_curTime += 1/m_tps;

	list<Clock*, __gc_allocator>::iterator it = m_clocks.begin();
	while (it != m_clocks.end())
	{
		Clock* clock = *it;

		clock->m_currentGlobalTime += 1/m_tps;

		clock->m_currentTime = clock->get_Timeline()->ActiveTimeToSimpleTime(clock->m_currentGlobalTime, &clock->m_currentIteration);

		// TODO
		clock->m_currentProgress = clock->m_currentTime / clock->get_Timeline()->get_Duration();

		clock->CurrentTimeInvalidated(clock);

		++it;
	}

	{
		list<IAnimatable*, __gc_allocator>::iterator it = m_animatables.begin();
		while (it != m_animatables.end())
		{
			IAnimatable* animatable = *it;

			unsigned int count = GetPropertyCount();

			for (unsigned int i = 0; i < count; i++)
			{
				ASSERT(0);
#if 0
				list<AnimationClock*, __gc_allocator>::iterator it = animatable->m_propertyClocks[i].begin();

				if (it != animatable->m_propertyClocks[i].end())
				{
					animatable->InvalidateProperty(GetProperty(i));

#if 0
					animatable->ComputeAnimVal();

					Object* curValue = animatable->m_baseValues[i];

					while (it != animatable->m_propertyClocks[i].end())
					{
						AnimationClock* clock = *it;

						Object* destValue = NULL;	// ??
						curValue = clock->GetCurrentValue(curValue, destValue);

						++it;
					}

					Object* oldValue = animatable->m_computedProperties[i];
					animatable->m_computedProperties[i] = curValue;
#if 1
					animatable->OnPropertyChanged(GetProperty(i), oldValue, NULL);
#endif
#endif
				}
#endif
			}

			++it;
		}
	}

}

}	// UI
}
