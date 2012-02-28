#pragma once

namespace System
{
namespace Web
{

class SVGEnumerationComponentTransferTypeValue : public Object
{
public:
	CTOR SVGEnumerationComponentTransferTypeValue();

	operator SVGComponentTransferType ();
	SVGEnumerationComponentTransferTypeValue& operator = (SVGComponentTransferType value);
	SVGEnumerationComponentTransferTypeValue& operator += (SVGComponentTransferType value);

	friend void SetAsString(SVGEnumerationComponentTransferTypeValue* p, StringIn value);
	friend String GetAsString(SVGEnumerationComponentTransferTypeValue* p);

	friend void SetAsInt(SVGEnumerationComponentTransferTypeValue* p, int value);
	friend int GetAsInt(SVGEnumerationComponentTransferTypeValue* p);

	void InterpolateValue(SVGEnumerationComponentTransferTypeValue& a, SVGEnumerationComponentTransferTypeValue& b, double t);

	SVGComponentTransferType m_value;
};

}	// Web
}
