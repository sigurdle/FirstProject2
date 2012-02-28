#include "stdafx.h"
#include "LSVG2.h"
#include "SVGPolygonElement.h"
#include "PSVGPolygonElement.h"

namespace System
{
namespace Web
{

	/*
attr_vtable SVGPolygonalShapeElement::s_pointsCallbacks =
{
	(GetBaseValString_t)&SVGPolygonalShapeElement::pointsGetBaseValString,
	(SetBaseValString_t)&SVGPolygonalShapeElement::pointsSetBaseValString,
	(GetBaseValObject_t)&SVGPolygonalShapeElement::pointsGetBaseValObject,
	(SetAnimValObject_t)&SVGPolygonalShapeElement::pointsSetAnimValObject,
//	SVGLengthValueHandler::GetSVGLengthValueHandler
};
*/

void AnimatedPoints::SetBaseValAsString(StringIn value)
{
	m_baseVal->setStringValue(value);
}

void AnimatedPoints::SetAnimVal(SVGPointList* value)
{
	m_animVal = value;
}

SVGPolygonalShapeElement::SVGPolygonalShapeElement(PSVGShapeElement* pElement) :
	SVGShapeElement(pElement),
	PolygonalPointsAttributeT<SVGPolygonalShapeElement>(NULL, WSTR("points"))
{
	ASSERT(0);
}

SVGPolygonalShapeElement::SVGPolygonalShapeElement(PSVGShapeElement* pElement, NamedNodeMap* attributes) :
	SVGShapeElement(pElement, attributes),
	PolygonalPointsAttributeT<SVGPolygonalShapeElement>(NULL, WSTR("points"))
{
#if 0
	UnspecifiedAttr(inner_ptr<Attr*>(this, &m_pointsAttr), NULL, WSTR("points"));
	ASSERT(0);
#if 0
	m_pointsAttr->m_callbacks = &s_pointsCallbacks;
#endif
	m_points = new SVGPointListMutable(m_pointsAttr->get_value());
	m_animatedPoints = new SVGPointList(m_points->m_p);

	m_points->m_changed = pointsBaseValChanged;
	m_points->m_changedArg = this;
#endif
}

Gui::Geometry* SVGPolygonalShapeElement::get_animatedGeometry()
{
	Gui::Geometry* geometry = points_attr().m_animated.m_animVal->GetGeometry();
	return geometry;
}

/*
void pointsBaseValChanged(Object* obj)
{
	SVGPolygonalShapeElement* e = static_cast<SVGPolygonalShapeElement*>(obj);
	e->m_pointsAttr->m_valueIsValid = false;
	e->GetPElement()->InvalidateBounds();
	// TODO AttrModifiedEvent
}

StringW* SVGPolygonalShapeElement::pointsGetBaseValString()
{
	return m_points->StringFromPointList();
}

void SVGPolygonalShapeElement::pointsSetBaseValString()
{
	m_points->setStringValue(m_pointsAttr->get_value());
	GetPElement()->InvalidateBounds();
	// TODO AttrModifiedEvent
}

Object* SVGPolygonalShapeElement::pointsGetBaseValObject()
{
	return m_points;
}

void SVGPolygonalShapeElement::pointsSetAnimValObject(Object* value)
{
	SVGPointList* pointList = static_cast<SVGPointList*>(value);

	m_animatedPoints->m_p = pointList->m_p;

	GetPElement()->InvalidateBounds();
}
*/

////

SVGPolygonElement::SVGPolygonElement(NamedNodeMap* attributes) : SVGPolygonalShapeElement(new PSVGPolygonElement(this), attributes)
{
}

}	// w3c
}
