#include "stdafx.h"
#include "LXUI2.h"
#include "Path.h"

namespace System
{
namespace UI
{

DependencyProperty* Geometry::s_TransformProperty = RegisterProperty(WSTR("Transform"), typeid(Transform), typeid(Geometry), NULL, PropertyMetaData(None));

GeometryCollection::GeometryCollection()
{
}

DependencyProperty* RectangleGeometry::s_RadiusXProperty = RegisterProperty(WSTR("RadiusX"), typeid(double), typeid(RectangleGeometry), DoubleObject::GetObject(0.0), PropertyMetaData(None));
DependencyProperty* RectangleGeometry::s_RadiusYProperty = RegisterProperty(WSTR("RadiusY"), typeid(double), typeid(RectangleGeometry), DoubleObject::GetObject(0.0), PropertyMetaData(None));
DependencyProperty* RectangleGeometry::s_RectProperty = RegisterProperty(WSTR("Rect"), typeid(Rect), typeid(RectangleGeometry), new Rect(), PropertyMetaData(None));

RectangleGeometry::RectangleGeometry()
{
}

double RectangleGeometry::get_RadiusX()
{
	return static_cast<DoubleObject*>(GetValue(get_RadiusXProperty()))->GetValue();
}

void RectangleGeometry::set_RadiusX(double radiusX)
{
	SetValue(get_RadiusXProperty(), box_cast(radiusX));
}

double RectangleGeometry::get_RadiusY()
{
	return static_cast<DoubleObject*>(GetValue(get_RadiusYProperty()))->GetValue();
}

void RectangleGeometry::set_RadiusY(double radiusY)
{
	SetValue(get_RadiusYProperty(), box_cast(radiusY));
}

Rect RectangleGeometry::get_Rect()
{
	return *static_cast<Rect*>(GetValue(get_RectProperty()));
}

void RectangleGeometry::set_Rect(Rect rect)
{
	SetValue(get_RectProperty(), new Rect(rect));
}

Rect RectangleGeometry::get_Bounds()
{
	// ??
	return get_Rect();
//	return m_bounds;
}

EllipseGeometry::EllipseGeometry()
{
}

Rect EllipseGeometry::get_Bounds()
{
	return Rect();
}

CombinedGeometry::CombinedGeometry()
{
}

Rect CombinedGeometry::get_Bounds()
{
	return Rect();
}

DependencyProperty* GeometryGroup::s_ChildrenProperty = RegisterProperty(WSTR("Children"), typeid(GeometryCollection), typeid(GeometryGroup), NULL, PropertyMetaData(None));

GeometryGroup::GeometryGroup()
{
}

Rect GeometryGroup::get_Bounds()
{
	return Rect();
}

// StreamGeometryContext

void StreamGeometryContext::BeginFigure(Point startpoint, bool isFilled, bool isClosed)
{
}

void StreamGeometryContext::BezierTo(Point ctlpoint1, Point ctlpoint2, Point endpoint, bool isStroked, bool isSmoothJoined)
{
}

void StreamGeometryContext::LineTo(Point point, bool isStroked, bool isSmoothJoined)
{
}

void StreamGeometryContext::Close()
{
}

// StreamGeometry

StreamGeometry::StreamGeometry()
{
}

StreamGeometryContext* StreamGeometry::Open()
{
	return NULL;
}

Rect StreamGeometry::get_Bounds()
{
	return Rect();
}

namespace Shapes
{

DependencyProperty* Path::s_DataProperty = RegisterProperty(WSTR("Data"), typeid(Geometry), typeid(Path), NULL, PropertyMetaData(AffectsMeasure));

Path::Path()
{
}

Geometry* Path::get_Data()
{
	return static_cast<Geometry*>(GetValue(get_DataProperty()));
}

void Path::set_Data(Geometry* data)
{
	SetValue(get_DataProperty(), data);
}

}	// Shapes
}	// UI
}
