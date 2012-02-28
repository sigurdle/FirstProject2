#ifndef SVGEnumerationUnitTypeValue_h
#define SVGEnumerationUnitTypeValue_h

namespace System
{
namespace Web
{

class SVGEnumerationUnitTypeValue : public Object
//	public CSingleObject
{
public:

	CTOR SVGEnumerationUnitTypeValue()
	{
		m_value = SVG_UNIT_TYPE_UNKNOWN;
	}

	SVGEnumerationUnitTypeValue& operator = (const SVGEnumerationUnitTypeValue& value)
	{
		m_value = value.m_value;
		return *this;
	}

	SVGEnumerationUnitTypeValue& operator += (const SVGEnumerationUnitTypeValue& value)
	{
		m_value = value.m_value;
		return *this;
	}

	void InterpolateValue(SVGEnumerationUnitTypeValue& a, SVGEnumerationUnitTypeValue& b, double t)
	{
		m_value = a.m_value;
	}

	friend String GetAsString(SVGEnumerationUnitTypeValue* e)
	{
		ASSERT(e);

		if (e->m_value == SVG_UNIT_TYPE_USERSPACEONUSE)
		{
			return WSTR("userSpaceOnUse");
		}
		else
		{
			ASSERT(e->m_value == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX);
			return WSTR("objectBoundingBox");
		}
	}

	friend void SetAsString(SVGEnumerationUnitTypeValue* e, StringIn str)
	{
		ASSERT(e);

		if (str == L"objectBoundingBox")
			e->m_value = SVG_UNIT_TYPE_OBJECTBOUNDINGBOX;
		else if (str == L"userSpaceOnUse")
			e->m_value = SVG_UNIT_TYPE_USERSPACEONUSE;
		else
			THROW(new Exception(WSTR("Invalid string value")));
	}

	friend int GetAsInt(SVGEnumerationUnitTypeValue* p)
	{
		return (int)p->m_value;
	}

	friend void SetAsInt(SVGEnumerationUnitTypeValue* p, int value)
	{
		ASSERT(p);

		if (value != SVG_UNIT_TYPE_OBJECTBOUNDINGBOX &&
			value != SVG_UNIT_TYPE_USERSPACEONUSE)
		{
			THROW(new Exception(WSTR("Invalid enum value")));
		}

		p->m_value = (SVGUnitType)value;
	}

	SVGUnitType m_value;
};

}	// Web
}

#endif // SVGEnumerationUnitTypeValue_h
