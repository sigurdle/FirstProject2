#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

// KeyTime

KeyTime::KeyTime()
{
}

KeyTime* KeyTime::s_Paced = new KeyTime;
KeyTime* KeyTime::s_Uniform = new KeyTime;

// static
KeyTime* KeyTime::FromPercent(double value)
{
	KeyTime* k = new KeyTime;
	k->m_kind = Kind_Percentage;
	k->m_value = value;
	return k;
}

// static
KeyTime* KeyTime::FromTimeSpan(double value)
{
	KeyTime* k = new KeyTime;
	k->m_kind = Kind_TimeSpan;
	k->m_value = value;
	return k;
}

// KeyFrame

KeyFrame::KeyFrame()
{
	m_keyTime = NULL;
}

KeyTime* KeyFrame::get_KeyTime()
{
	return m_keyTime;
}

void KeyFrame::set_KeyTime(KeyTime* value)
{
	m_keyTime = value;
}

}	// UI
}
