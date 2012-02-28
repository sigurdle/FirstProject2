#include "stdafx.h"
#include "LXUI2.h"

namespace System
{

Object* box_cast(int value)
{
	return IntObject::GetObject(value);
}

Object* box_cast(double value)
{
	return DoubleObject::GetObject(value);
}

namespace UI
{
namespace Media
{

DependencyProperty* Timeline::s_DurationProperty = RegisterProperty(WSTR("Duration"), typeid(double), typeid(Timeline), DoubleObject::GetObject(1), PropertyMetaData(None));
DependencyProperty* Timeline::s_BeginTimeProperty = RegisterProperty(WSTR("BeginTime"), typeid(double), typeid(Timeline), DoubleObject::GetObject(0), PropertyMetaData(None));
DependencyProperty* Timeline::s_AutoReverseProperty = RegisterProperty(WSTR("AutoReverse"), typeid(bool), typeid(Timeline), BoolObject::GetObject(false), PropertyMetaData(None));
DependencyProperty* Timeline::s_FillBehaviorProperty = RegisterProperty(WSTR("FillBehavior"), typeid(FillBehavior), typeid(Timeline), IntObject::GetObject(FillBehavior_HoldEnd), PropertyMetaData(None));
DependencyProperty* Timeline::s_RepeatBehaviorProperty = RegisterProperty(WSTR("RepeatBehavior"), typeid(RepeatBehavior), typeid(Timeline), new RepeatBehavior(1.0), PropertyMetaData(None));
DependencyProperty* Timeline::s_SpeedRatioProperty = RegisterProperty(WSTR("SpeedRatio"), typeid(double), typeid(Timeline), DoubleObject::GetObject(1.0), PropertyMetaData(None));
DependencyProperty* Timeline::s_AccelerationRatioProperty = RegisterProperty(WSTR("Acceleration"), typeid(double), typeid(Timeline), DoubleObject::GetObject(0.0), PropertyMetaData(None));
DependencyProperty* Timeline::s_DecelerationRatioProperty = RegisterProperty(WSTR("Deceleration"), typeid(double), typeid(Timeline), DoubleObject::GetObject(0.0), PropertyMetaData(None));

Timeline::Timeline()
{
//	m_containingElement = NULL;
}

#define REMAINDER(t, d) (t - d*floor(t/d))

double Timeline::ActiveTimeToSimpleTime(double tau, int* iteration)
{
	// m_simpleDur has accounted for autoReverse
	double m_AD = 99999;
	double m_simpleDur = get_Duration();
	double m_dur = get_Duration();

	double AD = m_AD;//m_dur;// ? AD=Active Duration?
	double speed = get_SpeedRatio();//m_speed->m_value->m_value->m_value;

	double acc = get_AccelerationRatio();//m_accelerate->m_value->m_value->m_value;
	double dec = get_DecelerationRatio();//m_decelerate->m_value->m_value->m_value;

	if (acc+dec > 1)	// Ignore both attributes
	{
		acc = 0;
		dec = 0;
	}

	double taf;

	if (speed > 0) // i.e. if the local speed is forwards 
		taf = tau * speed;
	else //  i.e. if the local speed is backwards 
		taf = AD - tau * fabs(speed);

	//Let dur be the value of the simple duration as defined by the Timing and Synchronization model.
	// This is the actual simple duration, and not simply the dur attribute.
	//This value does not account for the effect of any time manipulations.
	double dur = m_dur;
	ASSERT(dur >= 0);
	//if (dur < 0) dur = INDEFINITE;	// indefinite (Is this correct?)

	// m_simpleDur has accounted for autoReverse
	double dur_ = m_simpleDur;

#if 1	// Have something like this
	double tsu = REMAINDER(taf, dur_);
#else
	double tsu = taf;
#endif

	if (iteration)
	{	// ??
		*iteration = (int)(taf/dur_);
	}

// Account for autoReverse behavior.
	double tsu_;

	if (!get_AutoReverse())
	{
		tsu_ = tsu;
	}
	else
	{
		if (tsu < dur)
			tsu_ = tsu;
		else
			//tsu_ = /*dur - (tsu - dur) =*/ 2*dur - tsu;
			tsu_ = 2*dur - tsu;
	}

// Calculate filtered time (tsf)

// Account for acceleration/deceleration
	double tsf;

	double dacc = acc*dur;
	double ddec = dec*dur;

	double r = 1 / (1 - acc/2 - dec/2);

	if (tsu_ >= 0 && tsu_ < dacc)
	{
		double rt = r * (tsu_ / dacc);

		tsf = tsu_ * rt / 2;
	}
	else if (tsu_ > (dur - ddec))
	{
		double rt = r * (dur - tsu_) / ddec;

		double tdec =  tsu_ - (dur - ddec);
		double pd =  tdec / ddec;

		tsf = r * (dur - dacc / 2 - ddec + tdec * (2 - pd) / 2);
	}
	else
	{
		tsf = r * (tsu_ - dacc / 2);
	}

//	tsf = tsf + m_iteration*dur_;	// ???? TODO remove this

	return tsf;
}

/*
Clock* Timeline::AllocateClock()
{
	throw exception("");
	ASSERT(0);
	return NULL;
}
*/

double Timeline::GetNaturalDuration()
{
	return 0;
}

/*
DependencyObject* Timeline::GetDependencyParent()
{
	// ??
	return NULL;
}
*/

/*
void Timeline::AddChild(System::Object* child)
{
	m_animations.push_back(dynamic_cast<Animation*>(child));
}

void Timeline::AddText(System::StringW* text)
{
}
*/

Clock* Timeline::CreateClock(bool controllable)
{
	Clock* clock = AllocateClock();
	VERIFY(clock);
	m_createdClocks.push_back(clock);

	return clock;
}

//double fps = 20;

Nullable<double> Timeline::get_BeginTime()
{
//	return static_cast<DoubleObject*>(GetValue(get_BeginTimeProperty()))->GetValue();
	return unbox_nullable_cast<double>(GetValue(get_BeginTimeProperty()));
}

void Timeline::set_BeginTime(Nullable<double> duration)
{
	SetValue(get_BeginTimeProperty(), box_nullable_cast(duration));
}

double Timeline::get_Duration()
{
	return static_cast<DoubleObject*>(GetValue(get_DurationProperty()))->GetValue();
}

void Timeline::set_Duration(double duration)
{
	SetValue(get_DurationProperty(), DoubleObject::GetObject(duration));
}

bool Timeline::get_AutoReverse()
{
	return static_cast<BoolObject*>(GetValue(get_AutoReverseProperty()))->GetValue();
}

void Timeline::set_AutoReverse(bool autoReverse)
{
	SetValue(get_AutoReverseProperty(), BoolObject::GetObject(autoReverse));
}

RepeatBehavior* Timeline::get_RepeatBehavior()
{
	return static_cast<RepeatBehavior*>(GetValue(get_RepeatBehaviorProperty()));
}

void Timeline::set_RepeatBehavior(RepeatBehavior* repeatBehavior)
{
	SetValue(get_RepeatBehaviorProperty(), repeatBehavior);
}

double Timeline::get_SpeedRatio()
{
	return static_cast<DoubleObject*>(GetValue(get_SpeedRatioProperty()))->GetValue();
}

double Timeline::get_AccelerationRatio()
{
	return static_cast<DoubleObject*>(GetValue(get_AccelerationRatioProperty()))->GetValue();
}

double Timeline::get_DecelerationRatio()
{
	return static_cast<DoubleObject*>(GetValue(get_DecelerationRatioProperty()))->GetValue();
}

/*
void Timeline::Begin(Animatable* containingElement)
{
	m_containingElement = containingElement;
	m_time = 0;
	m_timerID = SetTimer(1000.0 / fps, this);
}
*/

#if 0
void Timeline::dispatchEvent2(Event* evt, bool bCapture, bool* doDefault)
{
	m_time += 1.0 / fps;
//	MessageBeep(-1);

	for (int i = 0; i < m_animations.size(); i++)
	{
		Animation* animation = m_animations[i];

		if (m_time >= animation->get_Duration())
		{
		//	MessageBeep(-1);
			KillTimer(m_timerID);
			return;
		}

		ASSERT(0);
		DependencyProperty* property = NULL;//GetProperty(animation->m_targetProperty);

		animation->m_currentTime = m_time;

		//animation->Do(property, m_time);
		m_containingElement->ApplyAnimation(property, animation);
	}
}
#endif

}	// Media
}	// UI
}
