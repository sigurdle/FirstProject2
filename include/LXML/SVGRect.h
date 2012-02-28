#ifndef w3c_SVGRect_h
#define w3c_SVGRect_h

#include "LSVGRectImpl.h"

namespace System
{
namespace Web
{

class WEBEXT SVGRect : 
	public SVGRectImpl
{
public:
	CTOR SVGRect();
	CTOR SVGRect(double x, double y, double width, double height);

	friend String GetAsString(SVGRect* rect);
	friend void SetAsString(SVGRect* rect, StringIn value);
};

}	// w3c
}

#endif // w3c_SVGRect_h
