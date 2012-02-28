#pragma once

namespace System
{
namespace Web
{

class SVGEnumerationMarkerUnitTypeValue : public Object
{
public:
	CTOR SVGEnumerationMarkerUnitTypeValue();

	operator SVGMarkerUnitType ();
	SVGEnumerationMarkerUnitTypeValue& operator = (SVGMarkerUnitType value);
	SVGEnumerationMarkerUnitTypeValue& operator += (SVGMarkerUnitType value);

	friend void SetAsString(SVGEnumerationMarkerUnitTypeValue* p, StringIn str);
	friend String GetAsString(SVGEnumerationMarkerUnitTypeValue* p);

	friend void SetAsInt(SVGEnumerationMarkerUnitTypeValue* p, int value);
	friend int GetAsInt(SVGEnumerationMarkerUnitTypeValue* p);

	void InterpolateValue(const SVGEnumerationMarkerUnitTypeValue& a, const SVGEnumerationMarkerUnitTypeValue& b, double t);

public:

	SVGMarkerUnitType m_value;
};

}	// Web
}
