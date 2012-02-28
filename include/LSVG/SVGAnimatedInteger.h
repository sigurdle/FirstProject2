#ifndef __SVGANIMATEDINTEGER_H_
#define __SVGANIMATEDINTEGER_H_

//#include "LongValue.h"

namespace System
{
namespace Web
{

class SVGEXT SVGAnimatedInteger :
	public Object,
	public ISVGAnimatedInteger
{
public:
	CTOR SVGAnimatedInteger();

	int get_animVal() const;
	int get_baseVal() const;
	void set_baseVal(int newVal);

	// TODO, CreateInstance ???
	CValueTypeWrapper<LongValue>* m_baseVal;
	CValueTypeWrapper<LongValue>* m_animVal;

	CATXMLAttr* m_pAttr;
};

}	// w3c
}

#endif //__SVGANIMATEDINTEGER_H_
