#include "stdafx.h"
#include "HTML2.h"
#include "SVGLength.h"

namespace System
{
namespace Web
{

	/*
SVGLengthValue SVGLengthValue::s_values[4] =
{
	SVGLengthValue(0, 0, NULL, SVG_LENGTHTYPE_UNKNOWN),
	SVGLengthValue(0, 0, WSTR("0"), SVG_LENGTHTYPE_NUMBER),
	SVGLengthValue(1, 1, WSTR("1"), SVG_LENGTHTYPE_NUMBER),
	SVGLengthValue(100, 100, WSTR("100%"), SVG_LENGTHTYPE_PERCENTAGE),
};
*/

SVGLengthValue::SVGLengthValue()
{
	m_unitType = SVG_LENGTHTYPE_UNKNOWN;
	m_value = 0;
	m_valueInSpecifiedUnits = 0;
	m_valueAsString = NULL;
}

SVGLengthMutable::SVGLengthMutable()
{
}

String SVGLengthValue::get_valueAsString()
{
	return m_valueAsString;
}

void SVGLengthValue::ParseString(StringIn str)
{
	m_valueAsString = str;

	if (m_valueAsString)
	{
		int unitType;
		m_valueInSpecifiedUnits = ParseValueUnitString(CStringw(m_valueAsString).c_str(), &unitType);
		m_unitType = (SVGLengthType)unitType;

		m_value = ConvertSpecifiedValueToUserUnit(m_unitType, m_valueInSpecifiedUnits);
	}
}

bool SVGLengthValue::Equals(const SVGLengthValue* other) const
{
	if (m_unitType != other->m_unitType) return false;
	if (m_valueInSpecifiedUnits != other->m_valueInSpecifiedUnits) return false;

	return true;
}

bool SVGLengthValue::Equals(const Object* other) const
{
	if (other == this) return true;
	if (other->GetType() != GetType()) return false;

	const SVGLengthValue* otherLength = static_cast<const SVGLengthValue*>(other);

	return Equals(otherLength);
}

/////////

SVGLength::SVGLength()
{
	m_p = new SVGLengthValue;
	/*
	m_p = &SVGLengthValue::s_values[0];
	++m_p->m_refcount;
	*/
}

SVGLength::~SVGLength()
{
}

bool SVGLength::Equals(const Object* other) const
{
	if (other == this) return true;

	const SVGLength* otherLength = dynamic_cast<const SVGLength*>(other);
	if (otherLength == NULL) return false;

	return m_p->Equals(otherLength->m_p);
}

/*
bool ImmutableSVGLength::Equals(const Object* other) const
{
	if (other == this) return true;
	if (other->GetType() != GetType()) return false;

	return m_p->Equals(static_cast<const ImmutableSVGLength*>(other)->m_p);
}
*/

double SVGLength::get_value()
{
	return m_p->m_value;
}

double SVGLength::get_valueInSpecifiedUnits()
{
	return m_p->m_valueInSpecifiedUnits;
}

String SVGLength::get_valueAsString()
{
	return m_p->get_valueAsString();
}

void SVGLengthMutable::set_value(double newVal)
{
	if (m_p->m_value != newVal)
	{
		/*
		if (m_p->m_refcount > 1)
		{
			--m_p->m_refcount;
			m_p = new SVGLengthValue(*m_p);
		}
		*/

		m_p->m_value = newVal;

		if (m_p->m_unitType == SVG_LENGTHTYPE_UNKNOWN) m_p->m_unitType = SVG_LENGTHTYPE_NUMBER;

		m_p->m_valueInSpecifiedUnits = ConvertUserUnitToSpecifiedValue(m_p->m_value, m_p->m_unitType);

		// TODO, set it to NULL 
		m_p->m_valueAsString = CreateValueUnitString(m_p->m_valueInSpecifiedUnits, m_p->m_unitType);

		if (m_owner)
			m_owner->OnChanged(this);
	}
}

void SVGLengthMutable::set_valueInSpecifiedUnits(double newVal)
{
	if (m_p->m_valueInSpecifiedUnits != newVal)
	{
		/*
		if (m_p->m_refcount > 1)
		{
			--m_p->m_refcount;
			m_p = new SVGLengthValue(*m_p);
		}
		*/

		m_p->m_valueInSpecifiedUnits = newVal;

		m_p->m_value = ConvertSpecifiedValueToUserUnit(m_p->m_unitType, m_p->m_valueInSpecifiedUnits);
		m_p->m_valueAsString = CreateValueUnitString(m_p->m_valueInSpecifiedUnits, m_p->m_unitType);

		if (m_owner)
			m_owner->OnChanged(this);
	}
}

void SVGLengthMutable::set_valueAsString(StringIn newVal)
{
	if (SetAsString(newVal))
	{
		if (m_owner)
			m_owner->OnChanged(this);
	}
}

// New value with new unit
void SVGLengthMutable::newValueSpecifiedUnits(SVGLengthType unitType, double valueInSpecifiedUnits)
{
	if ((unitType != m_p->m_unitType) || (valueInSpecifiedUnits != m_p->m_valueInSpecifiedUnits))
	{
		/*
		if (m_p->m_refcount > 1)
		{
			--m_p->m_refcount;
			m_p = new SVGLengthValue(*m_p);
		}
		*/

		m_p->m_unitType = unitType;
		m_p->m_valueInSpecifiedUnits = valueInSpecifiedUnits;
		m_p->m_value = ConvertSpecifiedValueToUserUnit(m_p->m_unitType, m_p->m_valueInSpecifiedUnits/*, 0*/);
		m_p->m_valueAsString = CreateValueUnitString(m_p->m_valueInSpecifiedUnits, m_p->m_unitType);

		if (m_owner)
			m_owner->OnChanged(this);
	}
}

// Keep the underlying value, change the unit
void SVGLengthMutable::convertToSpecifiedUnits(SVGLengthType unitType)
{
	if (unitType != m_p->m_unitType)
	{
		/*
		if (m_p->m_refcount > 1)
		{
			--m_p->m_refcount;
			m_p = new SVGLengthValue(*m_p);
		}
		*/

		m_p->m_value = ConvertSpecifiedValueToUserUnit(m_p->m_unitType, m_p->m_valueInSpecifiedUnits/*, 0*/);
		m_p->m_unitType = unitType;
		m_p->m_valueInSpecifiedUnits = ConvertUserUnitToSpecifiedValue(m_p->m_value, m_p->m_unitType);
		m_p->m_valueAsString = CreateValueUnitString(m_p->m_valueInSpecifiedUnits, m_p->m_unitType);

		if (m_owner)
			m_owner->OnChanged(this);
	}
}

////////////////////////////////////////////////////////

/*
void SVGLength::operator = (const SVGLength& value)
{
	m_unitType = value.m_unitType;
	m_value = value.m_value;
	m_valueInSpecifiedUnits = value.m_valueInSpecifiedUnits;
	m_valueAsString = value.m_valueAsString;
}

void SVGLength::operator += (const SVGLength& value)
{
	m_unitType = value.m_unitType;
	m_value += value.m_value;
	m_valueInSpecifiedUnits += value.m_valueInSpecifiedUnits;
	m_valueAsString = CreateValueUnitString(m_valueInSpecifiedUnits, m_unitType);
}
*/

/*
SVGLength::operator double () const
{
	return m_value;
}
*/

HTMLEXT String GetAsString(SVGLength* pLength)
{
	return pLength->get_valueAsString();
}

HTMLEXT void SetAsString(SVGLength* pLength, StringIn str)
{
	pLength->SetAsString(str);
}

bool SVGLength::SetAsString(StringIn str)
{
//	if (newVal == NULL) THROW(-1);

	//if (wcsicmp(m_valueAsString, newVal))
	{
		/*
		if (m_p->m_refcount > 1)
		{
			--m_p->m_refcount;
			m_p = new SVGLengthValue(*m_p);
		}
		*/

		m_p->m_valueAsString = str;

		//_bstr_t valueAsString = stripspaces(m_valueAsString);

		if (m_p->m_valueAsString)	// ??
		{
			int unitType;
			CStringw cstr(m_p->m_valueAsString);
			m_p->m_valueInSpecifiedUnits = ParseValueUnitString(cstr.c_str(), &unitType);
			m_p->m_unitType = (SVGLengthType)unitType;

			m_p->m_value = ConvertSpecifiedValueToUserUnit(m_p->m_unitType, m_p->m_valueInSpecifiedUnits);

			return true;
		}
	}

	return false;
}

/*
System::StringW* SVGLength::GetAsString()
{
	return get_valueAsString();
}
*/

void SVGLength::InterpolateValue(const SVGLength& a, const SVGLength& b, double t)
{
	ASSERT(0);
// TODO, % need rethinking if one is % and the other is not
	//newValueSpecifiedUnits(SVG_LENGTHTYPE_NUMBER, a.m_value + (b.m_value - a.m_value)*t);
}

void SVGLength::set_valueAsString(StringIn newVal)
{
	readOnly();
}

void SVGLength::set_valueInSpecifiedUnits(double newVal)
{
	readOnly();
}

void SVGLength::set_value(double newVal)
{
	readOnly();
}

void SVGLength::convertToSpecifiedUnits(SVGLengthType unitType)
{
	readOnly();
}

void SVGLength::newValueSpecifiedUnits(SVGLengthType unitType, double valueInSpecifiedUnits)
{
	readOnly();
}

void SVGLength::readOnly()
{
	throw std::exception("object is Readonly");
}

//////////

SVGLengthValueHandler SVGLengthValueHandler::s_svgLengthValueHandler;

Object* SVGLengthValueHandler::Create() const
{
	return new SVGLengthMutable;
}

void SVGLengthValueHandler::ParseString(Object* value, StringIn str) const
{
	// ParseString ??

	static_cast<SVGLengthMutable*>(value)->set_valueAsString(str);
}

void SVGLengthValueHandler::InterpolateValue(Object* _dest, Object* _a, Object* _b, double t)
{
	SVGLength* dest = static_cast<SVGLength*>(_dest);
	SVGLength* a = static_cast<SVGLength*>(_a);
	SVGLength* b = static_cast<SVGLength*>(_b);

	dest->m_p->m_value = a->m_p->m_value + (b->m_p->m_value - a->m_p->m_value)*t;
}

}	// Web
}// sYSTEM
