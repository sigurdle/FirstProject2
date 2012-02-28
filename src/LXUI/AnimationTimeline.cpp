#include "stdafx.h"
#include "LXUI2.h"
#include "AnimationClock.h"

#if 0
namespace System
{

namespace UI
{

	class ty
	{
	public:
		void operator () (Object* sender)
		{
		}
	};

class Test
{
public:

	Test()
	{
		m_sig(NULL);

		m_sig.connect(ty());
	}

		signal1<Object*> m_sig;

};
}

namespace UI
{


Test* test = new Test;

	/*
class UIEXT AnimationClock : public Clock
{
public:
	CTOR AnimationClock(AnimationTimeline* timeline);

	AnimationTimeline* get_Timeline()
	{
		return (AnimationTimeline*)m_timeline;
	}

	virtual Object* GetCurrentValue(Object* defaultOriginValue, Object* defaultDestinationValue);

	signal1<Object*> CurrentTimeInvalidated;

};
*/

}

}
#endif

namespace System
{
namespace UI
{
namespace Media
{

DependencyProperty* AnimationTimeline::s_IsAdditiveProperty = RegisterProperty(WSTR("IsAdditive"), typeid(bool), typeid(Timeline), BoolObject::GetObject(false), PropertyMetaData(None));
DependencyProperty* AnimationTimeline::s_IsCumulativeProperty = RegisterProperty(WSTR("IsCumulative"), typeid(bool), typeid(Timeline), BoolObject::GetObject(false), PropertyMetaData(None));

AnimationTimeline::AnimationTimeline()
{
}

// virtual
bool AnimationTimeline::IsDestinationDefault()
{
	return false;
}

AnimationClock* AnimationTimeline::CreateClock()
{
	return (AnimationClock*)Timeline::CreateClock(false);
	/*
	AnimationClock* clock = new AnimationClock(this);
	return clock;
	*/
}

Clock* AnimationTimeline::AllocateClock()
{
	AnimationClock* clock = new AnimationClock(this);
	return clock;
}

/*
StringW* Animation::get_TargetProperty()
{
	return m_targetProperty;
}

void Animation::set_TargetProperty(StringW* value)
{
	m_targetProperty = value;
}
*/

}	// Media
}	// UI
}
