#ifndef __LSVGANIMATEDANGLE_H_
#define __LSVGANIMATEDANGLE_H_

#include "SVGAngle.h"

namespace System
{
namespace Web
{

class SVGEXT SVGAnimatedAngle : 
	public ISingleObjectListener
{
public:
	CTOR SVGAnimatedAngle();
	~SVGAnimatedAngle();

	CValueTypeWrapper<CreateInstanceT<SVGAngle> >* m_baseVal;
	CValueTypeWrapper<CreateInstanceT<SVGAngle> >* m_animVal;

	CATXMLAttr* m_pAttr;

	virtual void OnChanged(CSingleObject* pSVGAngle)
	{
		m_pAttr->OnBaseValChanged();
	}

	SVGAngle* get_animVal();
	SVGAngle* get_baseVal();
};

}	// w3c
}

#endif //__LSVGANIMATEDANGLE_H_
