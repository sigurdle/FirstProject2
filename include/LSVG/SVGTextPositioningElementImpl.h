#pragma once

#include "SVGTextContentElementImpl.h"

#include "SVGAnimatedLengthList.h"
#include "SVGAnimatedNumberList.h"

namespace System
{
namespace Web
{

#if 0
class SVGEXT SVGTextPositioningElementImplImpl : public SVGTextContentElementImpl
{
public:
	CTOR SVGTextPositioningElementImplImpl(PSVGElement* pelement, NamedNodeMap* attributes) : SVGTextContentElementImpl(pelement, attributes)
	{
		m_x = NULL;
		m_y = NULL;
		m_dx = NULL;
		m_dy = NULL;
		m_rotate = NULL;
	}
/*
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLengthList>, CValueTypeWrapper<CreateInstanceT<SVGLengthList> > >* m_x;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLengthList>, CValueTypeWrapper<CreateInstanceT<SVGLengthList> > >* m_y;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLengthList>, CValueTypeWrapper<CreateInstanceT<SVGLengthList> > >* m_dx;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLengthList>, CValueTypeWrapper<CreateInstanceT<SVGLengthList> > >* m_dy;
*/
	SVGAnimatedLengthList* m_x;
	SVGAnimatedLengthList* m_y;
	SVGAnimatedLengthList* m_dx;
	SVGAnimatedLengthList* m_dy;

	SVGAnimatedNumberList* m_rotate;
};
#endif

class SVGEXT SVGTextPositioningElementImpl : public SVGTextContentElementImpl,
	private AnimatedAttributeAffectsBoundsT<SVGAnimatedLengthList, 0>,
	private AnimatedAttributeAffectsBoundsT<SVGAnimatedLengthList, 1>,
	private AnimatedAttributeAffectsBoundsT<SVGAnimatedLengthList, 2>,
	private AnimatedAttributeAffectsBoundsT<SVGAnimatedLengthList, 3>
	//private AnimatedAttributeAffectsBoundsT<SVGTextPositioningElementImpl, SVGAnimatedLengthList, 4>
{
protected:

	CTOR SVGTextPositioningElementImpl(PSVGElement* pelement, NamedNodeMap* attributes) : SVGTextContentElementImpl(pelement, attributes),
		AnimatedAttributeAffectsBoundsT<SVGAnimatedLengthList, 0>(this, NULL, WSTR("x")),
		AnimatedAttributeAffectsBoundsT<SVGAnimatedLengthList, 1>(this, NULL, WSTR("y")),
		AnimatedAttributeAffectsBoundsT<SVGAnimatedLengthList, 2>(this, NULL, WSTR("dx")),
		AnimatedAttributeAffectsBoundsT<SVGAnimatedLengthList, 3>(this, NULL, WSTR("dy"))
//		AnimatedAttributeAffectsBoundsT<SVGTextPositioningElementImpl, SVGAnimatedLengthList, 4>(NULL, WSTR("rotate"))
	{
	}

public:

	XMLANIMATEDATTR(SVGTextPositioningElementImpl, SVGAnimatedLengthList, SVGAnimatedLengthList*, x, 0)
	XMLANIMATEDATTR(SVGTextPositioningElementImpl, SVGAnimatedLengthList, SVGAnimatedLengthList*, y, 1)
	XMLANIMATEDATTR(SVGTextPositioningElementImpl, SVGAnimatedLengthList, SVGAnimatedLengthList*, dx, 2)
	XMLANIMATEDATTR(SVGTextPositioningElementImpl, SVGAnimatedLengthList, SVGAnimatedLengthList*, dy, 3)
//	XMLANIMATEDATTR(SVGTextPositioningElementImpl, SVGAnimatedNumberList, SVGAnimatedNumberList*, rotate, 4)

	/*
		SVGAnimatedLengthList* get_x()
	{
		return m_x;
	}

	SVGAnimatedLengthList* get_y()
	{
		return m_y;
	}

	SVGAnimatedLengthList* get_dx()
	{
		return m_dx;
	}

	SVGAnimatedLengthList* get_dy()
	{
		return m_dy;
	}

	SVGAnimatedNumberList* get_rotate()
	{
		return m_rotate;
	}
	*/
};

}	// Web
}	// System
