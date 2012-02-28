#include "stdafx.h"
#include "LFC.h"

namespace System
{

DoubleObject DoubleObject::s_Zero(0);
DoubleObject DoubleObject::s_NegativeZero(double_NegativeZero.value);
DoubleObject DoubleObject::s_One(double_One.value);
DoubleObject DoubleObject::s_NegativeInfinity(double_NegativeInfinity.value);
DoubleObject DoubleObject::s_PositiveInfinity(double_PositiveInfinity.value);
DoubleObject DoubleObject::s_NaN(double_NaN.value);
DoubleObject DoubleObject::s_Epsilon(DBL_EPSILON);
DoubleObject DoubleObject::s_MinValue(DBL_MIN);
DoubleObject DoubleObject::s_MaxValue(DBL_MAX);

DoubleObject* DoubleObject::GetObject(double value)
{
	if (value == s_Zero.m_value)						return &s_Zero;
	else if (value == s_NegativeZero.m_value)		return &s_NegativeZero;
	else if (value == s_One.m_value)					return &s_One;
	else if (value == s_NegativeInfinity.m_value)	return &s_NegativeInfinity;
	else if (value == s_PositiveInfinity.m_value)	return &s_PositiveInfinity;
	else if (value == s_NaN.m_value)					return &s_NaN;
	else if (value == s_Epsilon.m_value)				return &s_Epsilon;
	else if (value == s_MinValue.m_value)			return &s_MinValue;
	else if (value == s_MaxValue.m_value)			return &s_MaxValue;
	else												return new DoubleObject(value);
}

String DoubleObject::ToString()
{
	return String::FromNumber(m_value);

//	StringStream stream;
//	stream << m_value;
//	return stream->str();
}

}	// System
