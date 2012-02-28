#ifndef __SVGFitToViewBoxImpl_h_
#define __SVGFitToViewBoxImpl_h_

#include "SVGAnimatedRect.h"
#include "SVGRectViewBox.h"

#include "SVGPreserveAspectRatio.h"
#include "SVGAnimatedPreserveAspectRatio.h"

namespace System
{
namespace Web
{

#if 0
/*template <class T, class IBase>*/ class SVGEXT SVGFitToViewBoxImpl //:
	//public IBase
{
public:
	CTOR SVGFitToViewBoxImpl(SVGElement* element);

	ISVGAnimatedRect* get_viewBox()
	{
		return m_viewBox;
	}

	ISVGAnimatedPreserveAspectRatio* get_preserveAspectRatio()
	{
		return m_preserveAspectRatio;
	}

public:

	Attr* m_viewBoxAttr;
	Attr* m_preserveAspectRatioAttr;

	SVGAnimatedRect* m_viewBox;
	SVGAnimatedPreserveAspectRatio* m_preserveAspectRatio;
};
#endif

}	// w3c
}

#endif // __SVGFitToViewBoxImpl_h_
