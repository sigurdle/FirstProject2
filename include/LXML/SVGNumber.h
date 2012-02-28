#ifndef __SVGNUMBER_H_
#define __SVGNUMBER_H_

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class WEBEXT SVGNumber : public Object,
	public ISVGNumber,
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public IDispatchImpl<ILSVGNumber, &IID_ILSVGNumber, &LIBID_LXUILib>,
	public CNotifySendImpl<SVGNumber>
{
public:
	CTOR SVGNumber();
	CTOR SVGNumber(double value);

	SVGNumber& operator = (const SVGNumber& value);
	operator double () const;

	/*virtual*/ void setStringValue(StringIn bstr);
	/*virtual*/ String getStringValue();
	/*virtual*/ void InterpolateValue(SVGNumber* a, SVGNumber* b, double t);

	double get_value() const;
	void set_value(double newVal);

protected:

	double m_value;
};

}
}
#endif // __SVGNUMBER_H_
