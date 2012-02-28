#ifndef Web_SVGSVGElement_h
#define Web_SVGSVGElement_h

#include "SVGFitToViewBoxImpl.h"

namespace System
{
namespace Web
{

class SVGEXT SVGSVGElement : 
	public SVGLocatableElement,
//	public DocumentCSSImpl<SVGSVGElement>,	// The spec says so, for me it's still experimental
	public SVGStylableImpl<SVGSVGElement>,
//	public SVGLocatableImpl<SVGSVGElement>,
//	public SVGFitToViewBoxImpl,//<SVGSVGElement, ISVGFitToViewBox>,
	public ISVGFitToViewBox,
	public SVGTestsImpl<SVGSVGElement>,
	public SVGLangSpaceImpl<SVGSVGElement>,
//	public ElementEditASImpl<SVGSVGElement>,
	public ElementEditVALImpl<SVGSVGElement>,
	public SMILAnimationTargetImpl<SVGSVGElement>,
	public CSVGRenderElementImpl<SVGSVGElement>,

//	public CLElementTimeImpl<SVGSVGElement, ILElementTime>,// Am I sure about this?
//	public ElementTimeContainerImpl,//<SVGSVGElement>,

	//public ILSVGLocatable,

	private ISVGPointListener,	// listening to m_currentTranslate changes

	private AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>,
	private AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>,
	private AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>,
	private AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>,
	private AnimatedAttributeT<SVGAnimatedPreserveAspectRatio, 4>,
	private AnimatedAttributeT<SVGAnimatedRect, 5>
{
public:

	CTOR SVGSVGElement();
	CTOR SVGSVGElement(NamedNodeMap* attributes);
	~SVGSVGElement();

	static const unsigned short NAV_AUTO           = 1;
	static const unsigned short NAV_NEXT           = 2;
	static const unsigned short NAV_PREV           = 3;
	static const unsigned short NAV_UP             = 4;
	static const unsigned short NAV_UP_RIGHT       = 5;
	static const unsigned short NAV_RIGHT          = 6;
	static const unsigned short NAV_DOWN_RIGHT     = 7;
	static const unsigned short NAV_DOWN           = 8;
	static const unsigned short NAV_DOWN_LEFT      = 9;
	static const unsigned short NAV_LEFT           = 10;
	static const unsigned short NAV_UP_LEFT        = 11;

	XMLANIMATEDATTR(SVGSVGElement, SVGAnimatedLength, ISVGAnimatedLength*, x, 0)
	XMLANIMATEDATTR(SVGSVGElement, SVGAnimatedLength, ISVGAnimatedLength*, y, 1)
	XMLANIMATEDATTR(SVGSVGElement, SVGAnimatedLength, ISVGAnimatedLength*, width, 2)
	XMLANIMATEDATTR(SVGSVGElement, SVGAnimatedLength, ISVGAnimatedLength*, height, 3)

	AnimatedAttributeT<SVGAnimatedPreserveAspectRatio, 4>& preserveAspectRatio_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedPreserveAspectRatio, 4>*>(this);
	}

	AnimatedAttributeT<SVGAnimatedRect, 5>& viewBox_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedRect, 5>*>(this);
	}

//	double m_currentTimeSeconds;	// Use CLElementTime::m_activeTime

	void ZoomToRect(double x, double y, double width, double height, bool bAnimate);

	void ZoomToRect2(double left, double top, double right, double bottom)
	{
		ZoomToRect(left, top, right-left, bottom-top, true);
	}

	virtual double GetImplicitDuration()
	{
		return INDEFINITE;
	}

	String get_contentStyleType();
	void set_contentStyleType(StringIn newVal);
	String get_contentScriptType();
	void set_contentScriptType(StringIn newVal);
	double get_currentScale();
	void set_currentScale(double newVal);
	SVGPoint* get_currentTranslate();
	bool get_useCurrentView();
	void set_useCurrentView(bool newVal);
	ISVGViewSpec* get_currentView();
	SVGMatrix* createSVGMatrix();
	ISVGRect* createSVGRect();
	ISVGPoint* createSVGPoint();
	SVGAngle* createSVGAngle();
	SVGLength* createSVGLength();
	SVGTransform* createSVGTransform();
	SVGTransform* createSVGTransformFromMatrix(SVGMatrix* matrix);
	void setCurrentTime(double seconds);
	double getCurrentTime();
	void deSelectAll();
	long suspendRedraw(long max_wait_milliseconds);
	void unsuspendRedraw(long suspend_handle_id);
	void unsuspendRedrawAll();

	SMILTime* createSMILTime();
	SMILTimeList* createSMILTimeList();

	String get_timeContainer()
	{
		return WSTR("par");
	}
	void set_timeContainer(String newVal)
	{
		ASSERT(0);
	}

	virtual void Seek(double seconds);

// ISVGFitToViewBox

	ISVGAnimatedRect* get_viewBox()
	{
		return viewBox_attr();
	}

	ISVGAnimatedPreserveAspectRatio* get_preserveAspectRatio()
	{
		return preserveAspectRatio_attr();
	}

	Attr* get_viewBoxAttr()
	{
		return viewBox_attr();
	}

	Attr* get_preserveAspectRatioAttr()
	{
		return preserveAspectRatio_attr();
	}

	inline PSVGSVGElement* GetPElement()
	{
		return (PSVGSVGElement*)m_pNode;
	}

protected:

	virtual void OnPointChanged(SVGPoint* point, double oldx, double oldy);
	virtual bool OnRemoveItem(SVGPoint* point);

// EventTarget
	virtual bool dispatchEvent2(Event* evt, bool bCapture);

	friend class PSVGSVGElement;

	ElementTimeContainerImpl* m_timeContainerImpl;

	SVGPoint* m_currentTranslate;
	double m_currentScale;
};

}	// Web
}	// System

#endif // Web_SVGSVGElement_h
