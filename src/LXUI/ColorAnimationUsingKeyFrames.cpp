#include "stdafx.h"
#include "LXUI2.h"
#include "AnimationClock.h"
#include "ColorAnimationUsingKeyFrames.h"

#include <algorithm>

namespace System
{
namespace UI
{
namespace Media
{

// ColorKeyFrame

ColorKeyFrame::ColorKeyFrame()
{
	m_Value = NULL;
}

Color* ColorKeyFrame::get_Value()
{
	return m_Value;
}

void ColorKeyFrame::set_Value(Color* value)
{
	m_Value = value;
}

DiscreteColorKeyFrame::DiscreteColorKeyFrame()
{
}

LinearColorKeyFrame::LinearColorKeyFrame()
{
}

SplineColorKeyFrame::SplineColorKeyFrame()
{
}

// ColorKeyFrames

ColorKeyFrames::ColorKeyFrames()
{
}

/*
void ColorKeyFrames::AddChild(System::Object* child)
{
	ColorKeyFrame* keyframe = dynamic_cast<ColorKeyFrame*>(child);
	if (keyframe == NULL) THROW(-1);
	m_items.push_back(keyframe);
}

void ColorKeyFrames::AddText(System::StringW* text)
{
}
*/

// ColorAnimationUsingKeyFrames

ColorAnimationUsingKeyFrames::ColorAnimationUsingKeyFrames()
{
	m_keyFrames = NULL;
}

ColorKeyFrames* ColorAnimationUsingKeyFrames::get_KeyFrames()
{
	return m_keyFrames;
}

void ColorAnimationUsingKeyFrames::set_KeyFrames(ColorKeyFrames* keyFrames)
{
	m_keyFrames = keyFrames;
}

Object* ColorAnimationUsingKeyFrames::GetCurrentValue(Object* defaultOriginValue, Object* defaultDestinationValue, AnimationClock* animationClock)
{
	double currentTime = animationClock->get_CurrentTime();

	double* keyTimes = (double*)_alloca(m_keyFrames->m_items.size()*sizeof(double));

	{
		for (int i = 0; i < m_keyFrames->m_items.size(); i++)
		{
			ColorKeyFrame* keyFrame = m_keyFrames->m_items[i];

			KeyTime* keyTime = keyFrame->get_KeyTime();
			keyTimes[i] = keyTime->m_value;
		}
	}

	int leftkey = 0;
	for (int i = 0; i < m_keyFrames->m_items.size(); i++)
	{
		if (keyTimes[i] >= currentTime)
			break;

		leftkey = i;
	}

	double t;
	int rightkey;
	if (leftkey < m_keyFrames->m_items.size()-1)
	{
		rightkey = leftkey+1;
		double duration = (keyTimes[rightkey] - keyTimes[leftkey]);
		t = (currentTime - keyTimes[leftkey]) / duration;
	}
	else
	{
		rightkey = leftkey;
		t = 0;
	}

	Color* m_from = m_keyFrames->m_items[leftkey]->get_Value();
	Color* m_to = m_keyFrames->m_items[rightkey]->get_Value();

	// linear

	int r = m_from->get_R() + (m_to->get_R() - m_from->get_R()) * t;
	int g = m_from->get_G() + (m_to->get_G() - m_from->get_G()) * t;
	int b = m_from->get_B() + (m_to->get_B() - m_from->get_B()) * t;
	int a = m_from->get_A() + (m_to->get_A() - m_from->get_A()) * t;

	r = max(0, min(255, r));
	g = max(0, min(255, g));
	b = max(0, min(255, b));
	a = max(0, min(255, a));

	return new Color(Color::FromArgb(a, r, g, b));
}

}	// Media
}	// UI
}
