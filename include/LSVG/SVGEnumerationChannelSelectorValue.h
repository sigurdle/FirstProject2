#pragma once

namespace System
{
namespace Web
{

class SVGEnumerationChannelSelectorValue :
	public Object
{
public:
	SVGEnumerationChannelSelectorValue();

	operator SVGChannelSelector ();
	SVGEnumerationChannelSelectorValue& operator = (SVGChannelSelector value);
//	SVGEnumerationChannelSelectorValue& operator += (SVGChannelSelector value);

	friend String GetAsString(SVGEnumerationChannelSelectorValue* p);
	friend void SetAsString(SVGEnumerationChannelSelectorValue* p, StringIn value);

	friend int GetAsInt(SVGEnumerationChannelSelectorValue* p);
	friend void SetAsInt(SVGEnumerationChannelSelectorValue* p, int value);

	void InterpolateValue(const SVGEnumerationChannelSelectorValue& a, const SVGEnumerationChannelSelectorValue& b, double t);

public:

	SVGChannelSelector m_value;
};

}	// Web
}
