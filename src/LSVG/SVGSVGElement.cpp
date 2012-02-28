#include "stdafx.h"
#include "LSVG2.h"
#include "SVGSVGElement.h"
#include "PSVGSVGElement.h"

//bool DoAnimationsForAllElements(Element* element, /*double oldTime,*/ double currentTime);

namespace System
{
namespace Web
{

#if 0
// TODO, not here
SVGFitToViewBoxImpl::SVGFitToViewBoxImpl(SVGElement* element)
{
	element->UnspecifiedAttr(inner_ptr<Attr*>(element, &m_viewBoxAttr), NULL, WSTR("viewBox"));
	element->UnspecifiedAttr(inner_ptr<Attr*>(element, &m_preserveAspectRatioAttr), NULL, WSTR("preserveAspectRatio"));

	m_viewBox = NULL;
	m_preserveAspectRatio = NULL;

//	element->AddXMLAttribute(NewXMLAttr(&m_viewBox, NULL, WSTR("viewBox")));
//	element->AddXMLAttribute(NewXMLAttr(&m_preserveAspectRatio, NULL, WSTR("preserveAspectRatio")));
}
#endif

ImmutableString<WCHAR> xlinkNamespaceURI = WSTR("http://www.w3.org/1999/xlink");

SVGSVGElement::SVGSVGElement() :
	SVGLocatableElement(new PSVGSVGElement(this)),//, SVGFitToViewBoxImpl(this),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>(this, NULL, WSTR("x")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>(this, NULL, WSTR("y")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>(this, NULL, WSTR("width")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>(this, NULL, WSTR("height")),
	AnimatedAttributeT<SVGAnimatedPreserveAspectRatio, 4>(this, NULL, WSTR("preserveAspectRatio"), WSTR("'xMidYMid meet")),
	AnimatedAttributeT<SVGAnimatedRect, 5>(this, NULL, WSTR("viewBox"))
{
	m_currentScale = 1.0;
	m_currentTranslate = new SVGPoint;
	m_currentTranslate->m_owner = this;

#if 0

#if 0
	UnspecifiedAttr(inner_ptr<Attr*>(this, &m_xAttr), NULL, WSTR("x"));
	UnspecifiedAttr(inner_ptr<Attr*>(this, &m_yAttr), NULL, WSTR("y"));
	UnspecifiedAttr(inner_ptr<Attr*>(this, &m_widthAttr), NULL, WSTR("width"));
	UnspecifiedAttr(inner_ptr<Attr*>(this, &m_heightAttr), NULL, WSTR("height"));
#endif

//		m_currentTimeSeconds = 0.0;
	m_currentScale = 1.0;
	m_currentTranslate = new SVGPoint;
	m_currentTranslate->m_pListener = this;

	AddXMLAttribute(NewXMLAttr(&m_x, NULL, WSTR("x"), WSTR("0")));
	AddXMLAttribute(NewXMLAttr(&m_y, NULL, WSTR("y"), WSTR("0")));
	AddXMLAttribute(NewXMLAttr(&m_width, NULL, WSTR("width"), WSTR("100%")));
	AddXMLAttribute(NewXMLAttr(&m_height, NULL, WSTR("height"), WSTR("100%")));

	SetAllValues(this);	// ???
#endif
}

SVGSVGElement::SVGSVGElement(NamedNodeMap* attributes) :
	SVGLocatableElement(new PSVGSVGElement(this), attributes),
//, SVGFitToViewBoxImpl(this)
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>(this, NULL, WSTR("x")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>(this, NULL, WSTR("y")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>(this, NULL, WSTR("width")),
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>(this, NULL, WSTR("height")),
	AnimatedAttributeT<SVGAnimatedPreserveAspectRatio, 4>(this, NULL, WSTR("preserveAspectRatio"), WSTR("'xMidYMid meet")),
	AnimatedAttributeT<SVGAnimatedRect, 5>(this, NULL, WSTR("viewBox"))
{
	/*
	UnspecifiedAttr(inner_ptr<Attr*>(this, &m_xAttr), NULL, WSTR("x"));
	UnspecifiedAttr(inner_ptr<Attr*>(this, &m_yAttr), NULL, WSTR("y"));
	UnspecifiedAttr(inner_ptr<Attr*>(this, &m_widthAttr), NULL, WSTR("width"));
	UnspecifiedAttr(inner_ptr<Attr*>(this, &m_heightAttr), NULL, WSTR("height"));

	m_x = new SVGAnimatedLength;
	m_y = new SVGAnimatedLength;
	m_width = new SVGAnimatedLength;
	m_height = new SVGAnimatedLength;

	SetAsString(m_x->m_baseVal, m_xAttr->get_value());
	SetAsString(m_y->m_baseVal, m_yAttr->get_value());
	SetAsString(m_width->m_baseVal, m_widthAttr->get_value());
	SetAsString(m_height->m_baseVal, m_heightAttr->get_value());
*/
//		m_currentTimeSeconds = 0.0;
	m_currentScale = 1.0;
	m_currentTranslate = new SVGPoint;
	m_currentTranslate->m_owner = this;

	/*
	AddXMLAttribute(NewXMLAttr(&m_x, NULL, WSTR("x"), WSTR("0")));
	AddXMLAttribute(NewXMLAttr(&m_y, NULL, WSTR("y"), WSTR("0")));
	AddXMLAttribute(NewXMLAttr(&m_width, NULL, WSTR("width"), WSTR("100%")));
	AddXMLAttribute(NewXMLAttr(&m_height, NULL, WSTR("height"), WSTR("100%")));

	SetAllValues(this);	// ???
	*/
}

SVGSVGElement::~SVGSVGElement()
{
	if (m_currentTranslate)
	{
		m_currentTranslate->m_owner = NULL;
		delete m_currentTranslate;
		m_currentTranslate = NULL;
	}
}

// virtual
void SVGSVGElement::OnPointChanged(SVGPoint* point, double oldx, double oldy)
{
	ASSERT(point == m_currentTranslate);

	// TODO do something here
	ASSERT(0);
}

// virtual
bool SVGSVGElement::OnRemoveItem(SVGPoint* point)
{
	ASSERT(point == m_currentTranslate);
//	// Not legal
	return false;
}

void SVGSVGElement::ZoomToRect(double x, double y, double width, double height, bool bAnimate)
{
	ASSERT(0);
#if 0	// Had this
	CComPtr<ILHTMLWindow> window;
	m_ownerDocument->get_window(&window);

	double oldmagnify = get_currentScale();

	double translateX = m_currentTranslate->get_x();
	double translateY = m_currentTranslate->get_y();

	long innerWidth;
	long innerHeight;
	window->get_innerWidth(&innerWidth);
	window->get_innerHeight(&innerHeight);

	CRect m_areaRect;
	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.right = innerWidth;
	m_areaRect.bottom = innerHeight;

	CDblRect zoomdrect;
	zoomdrect.left = x;
	zoomdrect.top = y;
	zoomdrect.right = x+width;
	zoomdrect.bottom = y+height;

/*
	CDblRect zoomRect;
	zoomRect.left = x;
	zoomRect.top = y;
	zoomRect.right = x+width;
	zoomRect.bottom = y+height;

// Convert screen rectangle to viewport
	CDblRect zoomdrect;
	zoomdrect.left = (zoomRect.left-translateX)/oldmagnify;// + translateX;
	zoomdrect.top = (zoomRect.top-translateY)/oldmagnify;// + translateY;
	zoomdrect.right = (zoomRect.right-translateX)/oldmagnify;// + translateX;
	zoomdrect.bottom = (zoomRect.bottom-translateY)/oldmagnify;// + translateY;
*/

// Set new scale
	double magnify = /*oldmagnify **/ (double)(m_areaRect.Width())/(width)/*zoomRect.Width()*/;

// Set new translate XY
	double cx = zoomdrect.left*magnify;//*magnify - translateX;
	double cy = zoomdrect.top*magnify;//*magnify - translateY;

	set_currentScale(magnify);
	m_currentTranslate->set_x(-cx);
	m_currentTranslate->set_y(-cy);
#endif

}

bool SVGSVGElement::dispatchEvent2(Event* evt, bool bCapture)
{
	DOMEventPhaseType phase = evt->get_eventPhase();

	if (phase != CAPTURING_PHASE)	// ??
	{
#if 0
		CComBSTR type;
		evt->get_type(&type);

		if (!wcscmp(type, L"mousedown"))
		{
			Fire_onmousedown(evt);
		}
		else if (!wcscmp(type, L"mouseup"))
		{
			Fire_onmouseup(evt);
		}
		else if (!wcscmp(type, L"mousemove"))
		{
			Fire_onmousemove(evt);
		}
		else if (!wcscmp(type, L"keydown"))
		{
			Fire_onkeydown(evt);
		}
		else if (!wcscmp(type, L"keyup"))
		{
			Fire_onkeyup(evt);
		}
		else if (!wcscmp(type, L"contextmenu"))
		{
			Fire_oncontextmenu(evt);
		}
		else if (!wcscmp(type, L"select"))
		{
			Fire_onselect(evt);
		}
#endif
	}

	return EventTarget::dispatchEvent2(evt, bCapture);
}

/*
ISVGAnimatedLength* SVGSVGElement::get_x()
{
	return x_attr();
}

ISVGAnimatedLength* SVGSVGElement::get_y()
{
	return y_attr();
}

ISVGAnimatedLength* SVGSVGElement::get_width()
{
	return width_attr();
}

ISVGAnimatedLength* SVGSVGElement::get_height()
{
	return height_attr();
}
*/

void SeekAllAnimations(Element* element, double seekTo)
{
	ASSERT(0);
#if 0
	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<Element> element2 = node;
		if (element2)
		{
			CComQIPtr<CLElementTimeImplImpl> elementTime = element2;
			if (elementTime)
			{
				elementTime->Seek(seekTo);
			}
			else
			{
				SeekAllAnimations(element2, seekTo);
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
#endif
}

// TODO, use common code for this
void SVGSVGElement::Seek(double seconds)
{
	ASSERT(0);
#if 0
//	m_tau = seconds;
	if (seconds != m_tau)
	{
		CLElementTimeContainerImpl<SVGSVGElement>::Seek(seconds);

	//	SeekAllAnimations(this, seconds);

		ILSVGElement* svgElement = this;//reinterpret_cast<ISVGElement*>(this/*GetControllingUnknown()*/);
		bool bAny = DoAnimationsForAllElements(svgElement, /*m_currentTimeSeconds,*/ seconds);

		//if (bAny)
		{
		// TODO, fix up here
			CComQIPtr<CLDOMDocumentImplImpl> pDocument(m_ownerDocument);

			for (int n = 0; n < pDocument->m_pViews.GetSize(); n++)
			{
				pDocument->m_pViews[n]->m_pRootElement->GetCSSPropertiesAndChildren();
				ASSERT(0);
#if 0
				pDocument->m_pViews[n]->Flow();

				if (pDocument->m_pViews[n]->m_pUI)
				{
					pDocument->m_pViews[n]->m_pUI->InvalidateRect(
						&pDocument->m_pViews[n]->m_client, FALSE);
				}
#endif
			}
		}
	}
#endif
}

//	m_currentTimeSeconds = seconds;

void SVGSVGElement::setCurrentTime(/*[in]*/ double seconds)
{
	Seek(seconds);
}

double SVGSVGElement::getCurrentTime()
{
	ASSERT(m_timeContainerImpl);
	return m_timeContainerImpl->m_tau;
}

void SVGSVGElement::deSelectAll()
{
	// TODO
	ASSERT(0);
}

String SVGSVGElement::get_contentScriptType()
{
	return getAttribute(WSTR("contentScriptType"));
}

void SVGSVGElement::set_contentScriptType(StringIn newVal)
{
	setAttribute(WSTR("contentScriptType"), newVal);
}

String SVGSVGElement::get_contentStyleType()
{
	return getAttribute(WSTR("contentStyleType"));
}

void SVGSVGElement::set_contentStyleType(StringIn newVal)
{
	setAttribute(WSTR("contentStyleType"), newVal);
}

double SVGSVGElement::get_currentScale()
{
	return m_currentScale;
}

void SVGSVGElement::set_currentScale(double newVal)
{
	newVal = MAX(newVal, 0.00001);
	newVal = MIN(newVal, 99999);

	if (m_currentScale != newVal)
	{
		m_currentScale = newVal;

	// TODO, update something
		ASSERT(0);
	}
}

SVGPoint* SVGSVGElement::get_currentTranslate()
{
	return m_currentTranslate;
}

bool SVGSVGElement::get_useCurrentView()
{
	ASSERT(0);
	THROW(-1);
	return false;
}

void SVGSVGElement::set_useCurrentView(bool newVal)
{
	ASSERT(0);
	THROW(-1);
}

ISVGViewSpec* SVGSVGElement::get_currentView()
{
	ASSERT(0);
	return NULL;
}

ISVGPoint* SVGSVGElement::createSVGPoint()
{
	return new SVGPoint;
}

SVGAngle* SVGSVGElement::createSVGAngle()
{
	return new SVGAngle;
}

SVGLength* SVGSVGElement::createSVGLength()
{
	return new SVGLengthMutable;
}

ISVGRect* SVGSVGElement::createSVGRect()
{
	return new SVGRect;
}

SVGMatrix* SVGSVGElement::createSVGMatrix()
{
	return new SVGMatrix;
}

SVGTransform* SVGSVGElement::createSVGTransform()
{
	return new SVGTransform;
}

SVGTransform* SVGSVGElement::createSVGTransformFromMatrix(SVGMatrix* matrix)
{
/*
	CComObject<CLSVGTransform>* pTransform;
	CComObject<CLSVGTransform>::CreateInstance(&pTransform);
	if (pTransform)
	{
		pTransform->AddRef();
		pTransform->setMatrix(matrix);

		*pVal = pTransform;
	}
	else
		*pVal = NULL;
*/
	ASSERT(0);
	return NULL;
}

// Extension
SMILTime* SVGSVGElement::createSMILTime()
{
/*
	CComObject<CLSMILTime>* p;
	CComObject<CLSMILTime>::CreateInstance(&p);
	if (p)
	{
		p->AddRef();
		*pVal = p;
	}
	else
		*pVal = NULL;
*/
	ASSERT(0);
	return NULL;
}

// Extension
SMILTimeList* SVGSVGElement::createSMILTimeList()
{
/*
	CComObject<CLSMILTimeList>* p;
	CComObject<CLSMILTimeList>::CreateInstance(&p);
	if (p)
	{
		p->AddRef();
		*pVal = p;
	}
	else
		*pVal = NULL;
*/
	ASSERT(0);
	return NULL;
}

long SVGSVGElement::suspendRedraw(long max_wait_milliseconds)
{
	// TODO
	return 0;
}

void SVGSVGElement::unsuspendRedraw(long suspend_handle_id)
{
	// TODO
}

void SVGSVGElement::unsuspendRedrawAll()
{
	// TODO
}

}	// Web
}	// System
