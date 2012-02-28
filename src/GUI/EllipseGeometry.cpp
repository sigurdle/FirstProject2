#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, EllipseGeometry, CenterX, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, EllipseGeometry, CenterY, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, EllipseGeometry, RadiusX, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, EllipseGeometry, RadiusY, 0.0f)

DependencyClass* EllipseGeometry::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_CenterXProperty(),
		get_CenterYProperty(),
		get_RadiusXProperty(),
		get_RadiusYProperty(),
	};

	return &depclass;
}

DependencyClass* EllipseGeometry::pClass(get_Class());

EllipseGeometry::EllipseGeometry() : Geometry(get_Class()), m_D2DGeometry(NULL)
{
}

EllipseGeometry::EllipseGeometry(float cx, float cy, float rx, float ry) : Geometry(get_Class()), m_D2DGeometry(NULL)
{
	SetPropertyValue(get_CenterXProperty(), cx);
	SetPropertyValue(get_CenterYProperty(), cy);
	SetPropertyValue(get_RadiusXProperty(), rx);
	SetPropertyValue(get_RadiusYProperty(), ry);
}

void EllipseGeometry::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_CenterXProperty() ||
		pPropertyVal->m_dp == get_CenterYProperty() ||
		pPropertyVal->m_dp == get_RadiusXProperty() ||
		pPropertyVal->m_dp == get_RadiusYProperty())
	{
		if (m_D2DGeometry)
		{
			m_D2DGeometry->Release();
			m_D2DGeometry = NULL;
		}

		GetProperty(get_BoundsLeftProperty())->m_computedValue = undefined;
		GetProperty(get_BoundsTopProperty())->m_computedValue = undefined;
		GetProperty(get_BoundsWidthProperty())->m_computedValue = undefined;
		GetProperty(get_BoundsHeightProperty())->m_computedValue = undefined;
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

#if 0
bool EllipseGeometry::HasComputedPropertyValue(PropertyValue* pPropertyVal)
{
	if (pPropertyVal->m_dp == &BoundsLeftProperty ||
		pPropertyVal->m_dp == &BoundsTopProperty ||
		pPropertyVal->m_dp == &BoundsWidthProperty ||
		pPropertyVal->m_dp == &BoundsHeightProperty)
	{
		return true;
	}
}

Object* EllipseGeometry::GetComputedObjectValue(PropertyValue* pPropertyVal)
{
	/*
	ID2D1EllipseGeometry* g = GetD2DGeometry();

	D2D1_RECT_F bounds;
	g->GetBounds(NULL, &bounds);
	*/

	ASSERT(0);
	return NULL;
}
#endif

gm::RectF EllipseGeometry::GetBounds()
{
	float cx = get_CenterX();
	float cy = get_CenterY();
	float rx = get_RadiusX();
	float ry = get_RadiusY();

	return gm::RectF(gm::PointF(cx-rx, cy-ry), gm::PointF(cx+rx, cy+ry));
}

ID2D1EllipseGeometry* EllipseGeometry::GetD2DGeometry()
{
	if (m_D2DGeometry == NULL)
	{
		D2D1_ELLIPSE ellipse;
		ellipse.point.x = get_CenterX();
		ellipse.point.y = get_CenterY();
		ellipse.radiusX = get_RadiusX();
		ellipse.radiusY = get_RadiusY();

		Graphics::Direct10::get_D2DFactory()->CreateEllipseGeometry(ellipse, &m_D2DGeometry);
	}

	return m_D2DGeometry;
}

gm::PointF EllipseGeometry::get_Center()
{
	return gm::PointF(get_CenterX(), get_CenterY());
}

gm::PointF EllipseGeometry::get_Radius()
{
	return gm::PointF(get_RadiusX(), get_RadiusY());
}

HRGN EllipseGeometry::CreateHRGN()
{
	gm::PointF center = get_Center();
	gm::PointF radius = get_Radius();

	return CreateEllipticRgn(
		int(center.X - radius.X),
		int(center.Y - radius.Y),
		int(center.X + radius.X),
		int(center.Y + radius.Y));
}

void EllipseGeometry::RenderFill(ManagedRenderContext renderContext, Brush* brush)
{
	if (brush)
	{
		D2D1_ELLIPSE ellipse;
		ellipse.point.x = get_CenterX();
		ellipse.point.y = get_CenterY();
		ellipse.radiusX = get_RadiusX();
		ellipse.radiusY = get_RadiusY();

		renderContext.m_p->GetRT()->m_spRT->FillEllipse(ellipse, brush->Create(renderContext.m_p, NULL/*this*/));
	}
}

void EllipseGeometry::RenderStroke(ManagedRenderContext renderContext, Brush* brush, float width)
{
	if (brush)
	{
		D2D1_ELLIPSE ellipse;
		ellipse.point.x = get_CenterX();
		ellipse.point.y = get_CenterY();
		ellipse.radiusX = get_RadiusX();
		ellipse.radiusY = get_RadiusY();

		ID2D1StrokeStyle* strokeStyle = NULL;
		renderContext.m_p->GetRT()->m_spRT->DrawEllipse(ellipse, brush->Create(renderContext.m_p, NULL/*this*/), width, strokeStyle);
	}
}

}	// Gui
}	// System
