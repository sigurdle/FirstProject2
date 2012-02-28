#include "stdafx.h"
#include "LXUI2.h"

#include "AnimationClock.h"

//#include <functional>

namespace System
{
namespace UI
{

extern DepState* depstate;

__live_object_ptr<TimeManager> g_timeManager;

namespace Media
{

/*
class testfun
{
public:
	void operator () (Object* sender)
	{
	}
};
*/

Animatable::Animatable()
{
	m_baseValues.resize(depstate->gindex);
	m_propertyClocks.resize(depstate->gindex);

	m_animatedPropertiesCount = 0;
}

bool Animatable::HasAnimatedProperties()
{
	return m_animatedPropertiesCount > 0;
}

Object* Animatable::GetAnimationBaseValue(DependencyProperty* pProperty)
{
	return m_baseValues[pProperty->gindex];
}

Object* Animatable::ComputeAnimVal(DependencyProperty* pProperty)
{
	int index = pProperty->gindex;

	Object* curValue = m_baseValues[index];

	list<AnimationClock*, __gc_allocator>::iterator it = m_propertyClocks[index].begin();
	while (it != m_propertyClocks[index].end())
	{
		AnimationClock* clock = *it;

		Object* destValue = NULL;	// ??
		curValue = clock->GetCurrentValue(curValue, destValue);

		++it;
	}

	return curValue;
}

Object* Animatable::ComputeProperty(DependencyProperty* pProperty)
{
	int index = pProperty->gindex;

	//if (m_baseValues[pProperty->gindex] == UnsetValue)
		m_baseValues[index] = ComputeBaseVal(pProperty);

	return ComputeAnimVal(pProperty);
		/*
	Object* curValue = m_baseValues[index];

	list<AnimationClock*, __gc_allocator>::iterator it = m_propertyClocks[index].begin();
	while (it != m_propertyClocks[index].end())
	{
		AnimationClock* clock = *it;

		Object* destValue = NULL;	// ??
		curValue = clock->GetCurrentValue(curValue, destValue);

		++it;
	}

	return curValue;
	*/
	//return m_baseValues[pProperty->gindex];	// TODO
}

Object* Animatable::ComputeBaseVal(DependencyProperty* pProperty)
{
	//DependencyObject* pParent;

	if (m_specifiedProperties[pProperty->gindex] != DependencyProperty::get_UnsetValue())	// Local value set
	{
		/*
		if (m_depCookies[pProperty->gindex] != NULL)
		{
			pParent = GetDependencyParent();

			pParent->RemoveDependant(pProperty, m_depCookies[pProperty->gindex]);
			m_depCookies[pProperty->gindex] = NULL;
		}
		*/

		return m_specifiedProperties[pProperty->gindex];
	}

	/*
	if (m_style)
	{
		Style::PropertyValue* propertyVal = m_style->m_depproperties[pProperty->gindex];
		if (propertyVal)
		{
			if (m_depCookies[pProperty->gindex] != NULL)
			{
				pParent = GetDependencyParent();

				pParent->RemoveDependant(pProperty, m_depCookies[pProperty->gindex]);
				m_depCookies[pProperty->gindex] = NULL;
			}

			return propertyVal->m_computedValue;
		}
	}
	*/

	/*
	if ((pProperty->m_metadata.m_flags & ChildInherits) && (pParent = GetDependencyParent()) != NULL)
	{
		if (m_depCookies[pProperty->gindex] == NULL)
			m_depCookies[pProperty->gindex] = pParent->AddDependant(pProperty, this);

		return pParent->ComputeProperty(pProperty);
	}
	else
	*/
	{
		return pProperty->m_defaultValue;
	}
}

void Animatable::ApplyAnimationClock(DependencyProperty* dp, AnimationClock* clock)
{
	ApplyAnimationClock(dp, clock, HandoffBehavior_SnapshotAndReplace);

#if 0

	if (m_computedProperties[dp->gindex] == UnsetValue)
	{
		m_baseValues[dp->gindex] = ComputeBaseVal(dp);
		m_computedProperties[dp->gindex] = m_baseValues[dp->gindex];
	}

	if (true)	// Composite
	{
		m_computedProperties[dp->gindex] = animation->GetCurrentValue(m_computedProperties[dp->gindex]);
	}
	else
	{
		m_computedProperties[dp->gindex] = animation->GetCurrentValue(m_baseValues[dp->gindex]);
	}

	OnPropertyChanged(dp);
#endif
}

int Animatable::OnCurrentTimeInvalidated(Object* sender)
{
	return 0;
}

void Animatable::ApplyAnimationClock(DependencyProperty* dp, AnimationClock* clock, HandoffBehavior handoffBehavior)
{
	if (dp == NULL) throw new Exception(WSTR("null pointer"));

	if (clock)
	{
		if (g_timeManager == NULL)
		{
			g_timeManager = new TimeManager;
		}

		if (m_animatedPropertiesCount == 0)
		{
			m_animated = g_timeManager->m_animatables.insert(g_timeManager->m_animatables.end(), this);
		}

		if (m_propertyClocks[dp->gindex].empty())
		{
			++m_animatedPropertiesCount;
		}

		if (handoffBehavior == HandoffBehavior_SnapshotAndReplace)
		{
			m_propertyClocks[dp->gindex].clear();
			m_propertyClocks[dp->gindex].push_back(clock);
		}
		else
		{
			m_propertyClocks[dp->gindex].push_back(clock);
		}

		g_timeManager->m_clocks.push_back(clock);

//		clock->CurrentTimeInvalidated.connect(std::bind1st(std::mem_fun1(&Animatable::OnCurrentTimeInvalidated), this));

//		clock->CurrentTimeInvalidated(clock);
	}
	else
	{
		if (!m_propertyClocks[dp->gindex].empty())
		{
			m_propertyClocks[dp->gindex].clear();
			--m_animatedPropertiesCount;

			if (m_animatedPropertiesCount == 0)
			{
				g_timeManager->m_animatables.erase(m_animated);
			}
		}
	}
}

void Animatable::BeginAnimation(DependencyProperty* dp, AnimationTimeline* timeline)
{
	BeginAnimation(dp, timeline, HandoffBehavior_SnapshotAndReplace);
}

void Animatable::BeginAnimation(DependencyProperty* dp, AnimationTimeline* timeline, HandoffBehavior handoffBehavior)
{
	if (dp == NULL) throw new Exception(WSTR("null pointer"));
	if (timeline == NULL) throw new Exception(WSTR("null pointer"));

	AnimationClock* clock = dynamic_cast<AnimationClock*>(timeline->CreateClock());

	ApplyAnimationClock(dp, clock, handoffBehavior);

	/*
	if (clock == NULL) throw exception("clock = NULL");

	if (m_propertyClocks[dp->gindex].empty())
	{
		++m_animatedPropertiesCount;
	}

	m_propertyClocks[property->gindex].clear();
	m_propertyClocks[property->gindex].push_back(clock);
	*/
}

}	// Media
}	// UI
}
