#include "stdafx.h"
#include "LXUI2.h"
#include "AnimationClock.h"

#include <algorithm>

namespace System
{
namespace UI
{
namespace Media
{

Type* ColorAnimationBase::get_TargetPropertyType()
{
	ASSERT(0);
	return NULL;
}

//////////

// TODO
DependencyProperty* ColorAnimation::s_ByProperty;
DependencyProperty* ColorAnimation::s_FromProperty;
DependencyProperty* ColorAnimation::s_ToProperty;

ColorAnimation::ColorAnimation()
{
}

Nullable<Color> ColorAnimation::get_From()
{
	Color* value = static_cast<Color*>(GetValue(get_FromProperty()));
	if (value)
		return Nullable<Color>(*value);
	else
		return Nullable<Color>();
}

void ColorAnimation::set_From(Nullable<Color> value)
{
	if (value.HasValue())
		SetValue(get_FromProperty(), new Color(value.Value()));
	else
		SetValue(get_FromProperty(), NULL);
}

Nullable<Color> ColorAnimation::get_To()
{
	Color* value = static_cast<Color*>(GetValue(get_ToProperty()));
	if (value)
		return Nullable<Color>(*value);
	else
		return Nullable<Color>();
}

void ColorAnimation::set_To(Nullable<Color> value)
{
	if (value.HasValue())
		SetValue(get_ToProperty(), new Color(value.Value()));
	else
		SetValue(get_ToProperty(), NULL);
}

Object* ColorAnimation::GetCurrentValue(Object* defaultOriginValue, Object* defaultDestinationValue, AnimationClock* animationClock)
{
	double t = animationClock->get_CurrentProgress();
	//double duration = get_Duration();

	//double t = (currentTime / duration);

	Nullable<Color> from = get_From();
	Nullable<Color> to = get_To();

	int r = from.Value().get_R() + (to.Value().get_R() - from.Value().get_R()) * t;
	int g = from.Value().get_G() + (to.Value().get_G() - from.Value().get_G()) * t;
	int b = from.Value().get_B() + (to.Value().get_B() - from.Value().get_B()) * t;
	int a = from.Value().get_A() + (to.Value().get_A() - from.Value().get_A()) * t;

	r = max(0, min(255, r));
	g = max(0, min(255, g));
	b = max(0, min(255, b));
	a = max(0, min(255, a));

	return new Color(Color::FromArgb(a, r, g, b));
}

}	// Media
}	// UI
}
