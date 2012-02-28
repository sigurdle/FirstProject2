#ifndef __LSVGANIMATEDBOOLEAN_H_
#define __LSVGANIMATEDBOOLEAN_H_

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class SVGEXT SVGAnimatedBoolean : public ISVGAnimatedBoolean
{
public:
	CTOR SVGAnimatedBoolean();

	CValueTypeWrapper<BooleanValue>* m_baseVal;
	CValueTypeWrapper<BooleanValue>* m_animVal;

	CATXMLAttr* m_pAttr;

// ILSVGAnimatedBoolean
public:
	bool get_animVal();
	bool get_baseVal();
	void set_baseVal(bool newVal);
};

}	// w3c
}

#endif //__LSVGANIMATEDBOOLEAN_H_
