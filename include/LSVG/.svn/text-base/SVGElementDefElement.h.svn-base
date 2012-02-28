// LSVGElementDefElement.h : Declaration of the CLSVGElementDefElement

#ifndef __LSVGELEMENTDEFELEMENT_H_
#define __LSVGELEMENTDEFELEMENT_H_

//#include "resource.h"       // main symbols

#include "LSVGElementDefElement.h"
//#include "LElementEditASImpl.h"
#include "LElementEditVALImpl.h"
#include "LSVGStylableImpl.h"
#include "AnimationTarget.h"

namespace Web
{
namespace Web
{

class SVGEXT CLSVGElementDefElement : 

	public SVGElement,
	public SVGStylableImpl<CLSVGElementDefElement>,
//	public CLElementEditASImpl<CLSVGElementDefElement>,
	public ElementEditVALImpl<CLSVGElementDefElement>,
	public SMILAnimationTargetImpl<CLSVGElementDefElement>,

	protected CNotifyGetImpl<CLSVGElementDefElement>,
	protected CNotifySendImpl<CLSVGElementDefElement>
{
public:
	CTOR CLSVGElementDefElement()
	{
		SetAllValues(this);	// ???
	}

};

}	// Web
}	// System

#endif //__LSVGELEMENTDEFELEMENT_H_
