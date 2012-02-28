#pragma once

namespace System
{
namespace Web
{

class SVGEnumerationMarkerOrientationTypeValue :
	public CSingleObject
{
public:

	SVGEnumerationMarkerOrientationTypeValue* operator -> ()
	{
		return this;
	}

	CTOR SVGEnumerationMarkerOrientationTypeValue();

	operator SVGMarkerOrientationType ();
	SVGEnumerationMarkerOrientationTypeValue& operator = (SVGMarkerOrientationType value);
	SVGEnumerationMarkerOrientationTypeValue& operator += (SVGMarkerOrientationType value);

	void setStringValue(StringIn str);
	String getStringValue();

	void InterpolateValue(const SVGEnumerationMarkerOrientationTypeValue& a, const SVGEnumerationMarkerOrientationTypeValue& b, double t);

	/*
	System::Object* GetUnknown()
	{
		return NULL;
	}
	*/

public:

	SVGMarkerOrientationType m_value;
};

}	// Web
}
