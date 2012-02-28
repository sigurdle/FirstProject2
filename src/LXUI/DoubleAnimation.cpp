#include "stdafx.h"
#include "LXUI2.h"
#include "AnimationClock.h"
#include "DoubleAnimation.h"

namespace System
{
namespace UI
{
namespace Media
{

DependencyProperty* DoubleAnimation::s_ByProperty = RegisterProperty(WSTR("By"), typeid(Nullable<double>), typeid(DoubleAnimation), NULL, PropertyMetaData(None));
DependencyProperty* DoubleAnimation::s_FromProperty = RegisterProperty(WSTR("From"), typeid(Nullable<double>), typeid(DoubleAnimation), NULL, PropertyMetaData(None));
DependencyProperty* DoubleAnimation::s_ToProperty = RegisterProperty(WSTR("To"), typeid(Nullable<double>), typeid(DoubleAnimation), NULL, PropertyMetaData(None));

DoubleAnimation::DoubleAnimation()
{
}

bool DoubleAnimation::IsDestinationDefault()
{
	Nullable<double> to = get_To();
	if (to.HasValue()) return false;

	Nullable<double> by = get_By();
	if (by.HasValue()) return false;

	return true;
}

Object* DoubleAnimation::GetCurrentValue(Object* defaultOriginValue, Object* defaultDestinationValue, AnimationClock* animationClock)
{
	double t = animationClock->get_CurrentProgress();

	Nullable<double> by = get_From();
	Nullable<double> from = get_From();
	Nullable<double> to = get_To();

	if (!from.HasValue())
		from = unbox_cast<double>(defaultOriginValue);

	if (!to.HasValue())
	{
		if (by.HasValue())
		{
			to = from + by;
		}
		else
			to = unbox_cast<double>(defaultDestinationValue);
	}

	double val = from + (to - from) * t;

	return box_cast(val);
}

/*
void DoubleAnimation::Do(DependencyProperty* property, double tim)
{
//	double val = m_dur
}
*/

Nullable<double> DoubleAnimation::get_By()
{
	return unbox_nullable_cast<double>(GetValue(get_ByProperty()));
}

void DoubleAnimation::set_By(Nullable<double> value)
{
	SetValue(get_ByProperty(), box_nullable_cast(value));
}

Nullable<double> DoubleAnimation::get_From()
{
	return unbox_nullable_cast<double>(GetValue(get_FromProperty()));
}

void DoubleAnimation::set_From(Nullable<double> value)
{
	SetValue(get_FromProperty(), box_nullable_cast(value));
}

Nullable<double> DoubleAnimation::get_To()
{
	return unbox_nullable_cast<double>(GetValue(get_ToProperty()));
}

void DoubleAnimation::set_To(Nullable<double> value)
{
	SetValue(get_ToProperty(), box_nullable_cast(value));
}

}	// Media
}	// UI
}
