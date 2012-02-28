#include "stdafx.h"
#include "LSVG2.h"
#include "SVGAngle.h"

namespace System
{
namespace Web
{

SVGAngle::SVGAngle()
{
	m_unitType = SVG_ANGLETYPE_UNKNOWN;
	m_value = 0;
	m_valueInSpecifiedUnits = 0;
	m_valueAsString = WSTR("0");

//		m_pListener = NULL;
}

SVGAngle::~SVGAngle()
{
//		ATLASSERT(m_pListener == NULL);
}

SVGAngleType SVGAngle::get_unitType() const
{
	return m_unitType;
}

double SVGAngle::get_value() const
{
	return m_value;
}

double SVGAngle::get_valueInSpecifiedUnits() const
{
	return m_valueInSpecifiedUnits;
}

String SVGAngle::get_valueAsString()
{
	return m_valueAsString;
}

void SVGAngle::set_value(double newVal)
{
	if (m_value != newVal)
	{
		m_value = newVal;

		if (m_unitType == SVG_ANGLETYPE_UNKNOWN) m_unitType = SVG_ANGLETYPE_UNSPECIFIED;

		m_valueInSpecifiedUnits = ConvertDegreesToSpecifiedValue(m_value, m_unitType);
		m_valueAsString = CreateAngleUnitString(m_valueInSpecifiedUnits, m_unitType);

		if (m_pListener)
			m_pListener->OnChanged(this);
	}
}

void SVGAngle::set_valueInSpecifiedUnits(double newVal)
{
	if (m_valueInSpecifiedUnits != newVal)
	{
		m_valueInSpecifiedUnits = newVal;

		m_value = ConvertSpecifiedValueToDegrees(m_unitType, m_valueInSpecifiedUnits/*, 0*/);
		m_valueAsString = CreateAngleUnitString(m_valueInSpecifiedUnits, m_unitType);

		if (m_pListener)
			m_pListener->OnChanged(this);
	}
}

void SVGAngle::set_valueAsString(StringIn newVal)
{
	//if (wcsicmp(m_valueAsString, newVal))
	{
		m_valueAsString = newVal;

		//_bstr_t valueAsString = stripspaces(m_valueAsString);

		m_valueInSpecifiedUnits = ParseValueUnitString(CStringw(m_valueAsString).c_str(), (int*)&m_unitType);
		m_value = ConvertSpecifiedValueToDegrees(m_unitType, m_valueInSpecifiedUnits/*, percentageOf*/);

		if (m_pListener)
			m_pListener->OnChanged(this);
	}
}

// New value with new unit
void SVGAngle::newValueSpecifiedUnits(SVGAngleType unitType, double valueInSpecifiedUnits)
{
	if ((unitType != m_unitType) || (valueInSpecifiedUnits != m_valueInSpecifiedUnits))
	{
		m_unitType = unitType;
		m_valueInSpecifiedUnits = valueInSpecifiedUnits;
		m_value = ConvertSpecifiedValueToDegrees(m_unitType, m_valueInSpecifiedUnits/*, 0*/);
		m_valueAsString = CreateAngleUnitString(m_valueInSpecifiedUnits, m_unitType);

		if (m_pListener)
			m_pListener->OnChanged(this);
	}
}

// Keep the underlying value, change the unit
void SVGAngle::convertToSpecifiedUnits(SVGAngleType unitType)
{
	ASSERT(
		unitType == SVG_ANGLETYPE_UNSPECIFIED ||
		unitType == SVG_ANGLETYPE_DEG ||
		unitType == SVG_ANGLETYPE_RAD ||
		unitType == SVG_ANGLETYPE_GRAD);

	if (unitType == SVG_ANGLETYPE_UNKNOWN) THROW(-1);

	if (unitType != m_unitType)
	{
		m_value = ConvertSpecifiedValueToDegrees(m_unitType, m_valueInSpecifiedUnits/*, 0*/);
		m_unitType = unitType;
		m_valueInSpecifiedUnits = ConvertDegreesToSpecifiedValue(m_value, m_unitType);
		m_valueAsString = CreateAngleUnitString(m_valueInSpecifiedUnits, m_unitType);

		if (m_pListener)
			m_pListener->OnChanged(this);
	}
}

////////////////////////////////////////////////////////

/*
SVGAngle& SVGAngle::operator = (const SVGAngle& value)
{
	m_unitType = value.m_unitType;
	m_value = value.m_value;
	m_valueInSpecifiedUnits = value.m_valueInSpecifiedUnits;
	m_valueAsString = value.m_valueAsString;

	return *this;
}

SVGAngle& SVGAngle::operator += (const SVGAngle& value)
{
	m_unitType = value.m_unitType;
	m_value += value.m_value;
	m_valueInSpecifiedUnits += value.m_valueInSpecifiedUnits;
//	m_valueAsString = value->m_valueAsString;

	return *this;
}

SVGAngle::operator double () const
{
	return m_value;
}
*/

void SVGAngle::setStringValue(StringIn str)
{
	set_valueAsString(str);
}

String SVGAngle::getStringValue()
{
	return get_valueAsString();
}

// virtual
void SVGAngle::InterpolateValue(const SVGAngle& a, const SVGAngle& b, double t)
{
	ASSERT(0);
#if 0
// TODO, % need rethinking if one is % and the other is not
	newValueSpecifiedUnits(SVG_AngleTYPE_NUMBER, a->m_value + (b->m_value - a->m_value)*t);
#endif
}

}	// Web
}
