#ifndef w3c_SVGMarkerElement_h
#define w3c_SVGMarkerElement_h

#include "SVGFitToViewBoxImpl.h"
#include "SVGEnumerationMarkerUnitTypeValue.h"
#include "SVGEnumerationMarkerOrientationTypeValue.h"

namespace System
{
namespace Web
{

class SVGEXT SVGMarkerElement : 

	public SVGElement,
	public SVGStylableImpl<SVGMarkerElement>,
//	public SVGFitToViewBoxImpl,//<SVGMarkerElement, ISVGFitToViewBox>,
	public SVGLangSpaceImpl<SVGMarkerElement>,
//	public SMILAnimationTargetImpl<SVGMarkerElement>,
//	public ElementEditASImpl<SVGMarkerElement>,
	public ElementEditVALImpl<SVGMarkerElement>,

	public ISVGFitToViewBox,
	public IElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGMarkerElement>,
	protected CNotifySendImpl<SVGMarkerElement>
{
public:
	CTOR SVGMarkerElement(NamedNodeMap* attributes);
	~SVGMarkerElement();

	ISVGAnimatedLength* get_refX();
	ISVGAnimatedLength* get_refY();
	ISVGAnimatedLength* get_markerWidth();
	ISVGAnimatedLength* get_markerHeight();
	ISVGAnimatedEnumeration* get_markerUnits();
	ISVGAnimatedEnumeration* get_orientType();
	SVGAnimatedAngle* get_orientAngle();
	void setOrientToAuto();
	void setOrientToAngle(SVGAngle* angle);

// ISVGFitToViewBox
	virtual ISVGAnimatedRect* get_viewBox()
	{
		return NULL;
//		return m_viewBox;
	}
	virtual ISVGAnimatedPreserveAspectRatio* get_preserveAspectRatio()
	{
		return NULL;
//		return m_preserveAspectRatio;
	}

	Attr* get_viewBoxAttr()
	{
		return NULL;
//		return m_viewBoxAttr;
	}

	Attr* get_preserveAspectRatioAttr()
	{
		return NULL;
//		return m_preserveAspectRatioAttr;
	}

protected:

//	CComObject<CATXMLAttr2T<CreateInstance<CLSVGAnimatedEnumerationT<CSVGEnumerationUnitTypeValue> >, CValueTypeWrapper<CSVGEnumerationUnitTypeValue> > >* m_MarkerUnits;
//	CComObject<CATXMLAttr2T<CreateInstance<CLSVGAnimatedEnumerationT<CSVGEnumerationUnitTypeValue> >, CValueTypeWrapper<CSVGEnumerationUnitTypeValue> > >* m_MarkerContentUnits;
	SVGAnimatedLength* m_refX;
	SVGAnimatedLength* m_refY;
	SVGAnimatedLength* m_markerWidth;
	SVGAnimatedLength* m_markerHeight;
//	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationMarkerUnitTypeValue> >, CValueTypeWrapper<SVGEnumerationMarkerUnitTypeValue> >* m_markerUnits;
//	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationMarkerOrientationTypeValue> >, CValueTypeWrapper<SVGEnumerationMarkerOrientationTypeValue> >* m_orientType;
//	CATXMLAttr2T<CreateInstanceT<SVGAnimatedAngle>, CValueTypeWrapper<CreateInstanceT<SVGAngle> > >* m_orientAngle;
};

}	// Web
}

#endif // w3c_SVGMarkerElement_h
