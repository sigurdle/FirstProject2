#ifndef w3c_SVGLinearGradientElement_h
#define w3c_SVGLinearGradientElement_h

//#include "resource.h"       // main symbols

#include "SVGGradientElementImpl.h"
#include "PSVGGradientElement.h"
//#include "PSVGLinearGradientElement.h"

namespace System
{
namespace Web
{

class SVGEXT SVGLinearGradientElement : 

	public SVGGradientElementImpl<SVGLinearGradientElement>,
//	public ElementEditASImpl<SVGLinearGradientElement>,
	public ElementEditVALImpl<SVGLinearGradientElement>
//	public SMILAnimationTargetImpl<SVGLinearGradientElement>,

//	protected CNotifyGetImpl<SVGLinearGradientElement>,
//	protected CNotifySendImpl<SVGLinearGradientElement>
{
public:

	CTOR SVGLinearGradientElement(NamedNodeMap* attributes);

	inline PSVGLinearGradientElement* GetPElement()
	{
		return (PSVGLinearGradientElement*)m_pNode;
	}

	SVGAnimatedLength* get_x1();
	SVGAnimatedLength* get_y1();
	SVGAnimatedLength* get_x2();
	SVGAnimatedLength* get_y2();

public:

	SVGAnimatedLength* m_x1;
	SVGAnimatedLength* m_y1;
	SVGAnimatedLength* m_x2;
	SVGAnimatedLength* m_y2;
};

}	// w3c
}

#endif // w3c_SVGLinearGradientElement_h
