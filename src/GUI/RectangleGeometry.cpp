#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, RectangleGeometry, Left, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RectangleGeometry, Top, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RectangleGeometry, Width, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RectangleGeometry, Height, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RectangleGeometry, Right, _this().getLeft() + _this().getWidth())
IMP_DEPENDENCY_PROPERTY(float, RectangleGeometry, Bottom, _this().getTop() + _this().getHeight())

DependencyClass* RectangleGeometry::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_LeftProperty(),
		get_TopProperty(),
		get_WidthProperty(),
		get_HeightProperty(),
		get_RightProperty(),
		get_BottomProperty(),
	};

	return &depclass;
}

DependencyClass* RectangleGeometry::pClass(get_Class());

RectangleGeometry::RectangleGeometry() : Geometry(get_Class())
{
}

RectangleGeometry::RectangleGeometry(gm::RectF rect) : Geometry(get_Class())
{
	SetPropertyValue(get_LeftProperty(), rect.X);
	SetPropertyValue(get_TopProperty(), rect.Y);
	SetPropertyValue(get_WidthProperty(), rect.Width);
	SetPropertyValue(get_HeightProperty(), rect.Height);
}

RectangleGeometry::RectangleGeometry(gm::PointF topleft, gm::SizeF size) : Geometry(get_Class())
{
	SetPropertyValue(get_LeftProperty(), topleft.X);
	SetPropertyValue(get_TopProperty(), topleft.Y);
	SetPropertyValue(get_WidthProperty(), size.Width);
	SetPropertyValue(get_HeightProperty(), size.Height);
}

RectangleGeometry::RectangleGeometry(float left, float top, float width, float height) : Geometry(get_Class())
{
	SetPropertyValue(get_LeftProperty(), left);
	SetPropertyValue(get_TopProperty(), top);
	SetPropertyValue(get_WidthProperty(), width);
	SetPropertyValue(get_HeightProperty(), height);
}

void RectangleGeometry::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_LeftProperty() ||
		pPropertyVal->m_dp == get_TopProperty() ||
		pPropertyVal->m_dp == get_WidthProperty() ||
		pPropertyVal->m_dp == get_HeightProperty())
	{
		m_D2DGeometry.Release();
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

gm::RectF RectangleGeometry::GetBounds()
{
//	return Geometry::GetBounds();
	return GetRect();
}

gm::RectF RectangleGeometry::GetRect()
{
	float left = get_Left();
	float top = get_Top();
	float width = get_Width();
	float height = get_Height();

	return gm::RectF(left, top, width, height);
}

bool RectangleGeometry::FillContainsPoint(gm::PointF point)
{
	return GetRect().Contains(point);
}

ID2D1RectangleGeometry* RectangleGeometry::GetD2DGeometry()
{
	if (m_D2DGeometry == nullptr)
	{
		gm::RectF r(GetRect());

		D2D1_RECT_F rect;
		rect.left = r.GetLeft();
		rect.top = r.GetTop();
		rect.right = r.GetRight();
		rect.bottom = r.GetBottom();

		Graphics::Direct10::get_D2DFactory()->CreateRectangleGeometry(rect, &m_D2DGeometry);
	}

	return m_D2DGeometry;
}

HRGN RectangleGeometry::CreateHRGN()
{
	gm::RectF rect = GetRect();
	return CreateRectRgn(rect.GetLeft(), rect.GetTop(), rect.GetRight(), rect.GetBottom());
}

Geometry* RectangleGeometry::CombineWithGeometry(Geometry* geometry, D2D1_COMBINE_MODE combineMode, const D2D1_MATRIX_3X2_F* inputGeometryTransform)
{
	if (inputGeometryTransform == nullptr)
	{
		if (combineMode == D2D1_COMBINE_MODE_INTERSECT)
		{
			if (auto rgeometry = dynamic_cast<RectangleGeometry*>(geometry))
			{
				gm::RectF r1 = GetBounds();
				gm::RectF r2 = rgeometry->GetBounds();

				gm::RectF r;
				bool intersected = gm::RectF::Intersect(r, r1, r2);
				if (intersected)
					return new RectangleGeometry(r);
				else
					return &EmptyGeometry::empty;
			}
		}
	}

	return baseClass::CombineWithGeometry(geometry, combineMode, inputGeometryTransform);
}

void RectangleGeometry::RenderFill(ManagedRenderContext renderContext, Brush* brush)
{
	if (renderContext.m_p->GetRT()->m_spRT)
	{
		if (brush)
		{
			D2D1_RECT_F rect;
			rect.left = get_Left();
			rect.top = get_Top();
			rect.right = rect.left + get_Width();
			rect.bottom = rect.top + get_Height();

			renderContext.m_p->GetRT()->m_spRT->FillRectangle(rect, brush->Create(renderContext.m_p, NULL/*this*/));
		//	renderContext.m_p->GetRT()->m_spRT->EndDraw();
		//	renderContext.m_p->GetRT()->m_spRT->Flush();
		}
	}
}

void RectangleGeometry::RenderStroke(ManagedRenderContext renderContext, Brush* brush, float width)
{
	if (renderContext.m_p->GetRT()->m_spRT)
	{
		if (brush)
		{
#if 0
			D2D1_RECT_F rect;
			rect.left = get_Left();
			rect.top = get_Top();
			rect.right = rect.left + get_Width();
			rect.bottom = rect.top + get_Height();

			ID2D1StrokeStyle* strokeStyle = NULL;
			
			renderContext.m_p->GetRT()->m_spRT->DrawRectangle(rect, brush->Create(renderContext.m_p, NULL/*this*/), width, strokeStyle);
#endif

			gm::RectF rect;
			rect.X = get_Left();
			rect.Y = get_Top();
			rect.Width = get_Width();
			rect.Height = get_Height();

			renderContext.StrokeRectangle(rect, brush, width);
		}
	}
}

}	// Gui
}
