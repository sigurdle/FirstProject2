#ifndef __SVGSHADOWABLEIMPL_H_
#define __SVGSHADOWABLEIMPL_H_

#include "SVGShadowElement.h"

namespace System
{
namespace Web
{

class WEBEXT SVGShadowableImpl : public ISVGShadowable
{
public:
	CTOR SVGShadowableImpl()
	{
		m_shadowElement = NULL;
#if 0
		m_elementDef = NULL;
#endif
	}

#if 0	// TODO have this
	ILSVGElementDefElement* m_elementDef;
#endif
	SVGShadowElement* m_shadowElement;

	SVGShadowElement* get_shadowTree() const
	{
		return m_shadowElement;
	}
};

}	// Web
}

#endif	// __SVGSHADOWABLEIMPL_H_
