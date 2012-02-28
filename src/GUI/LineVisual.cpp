#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, LineVisual, X1, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, LineVisual, Y1, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, LineVisual, X2, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, LineVisual, Y2, 0.0f)
IMP_DEPENDENCY_PROPERTY(Brush*, LineVisual, Brush, new SolidColorBrush());
IMP_DEPENDENCY_PROPERTY(float, LineVisual, Width, 1.0f)
IMP_DEPENDENCY_PROPERTY(StrokeStyle*, LineVisual, Style, nullptr)

DependencyClass* LineVisual::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_X1Property(),
		get_Y1Property(),
		get_X2Property(),
		get_Y2Property(),
		get_WidthProperty(),
		get_BrushProperty(),
		get_StyleProperty(),
	};

	return &depclass;
}

DependencyClass* LineVisual::pClass(get_Class());

LineVisual::LineVisual() : UIElement(get_Class())
{
}

/*
LineVisual::LineVisual(float x1, float y1, float x2, float y2, Brush* brush, float width) : Visual(&s_Class)
{
	set_X1(x1);
	set_Y1(y1);
	set_X2(x2);
	set_Y2(y2);
	set_Brush(brush);
	set_Width(width);
}
*/

LineVisual::LineVisual(typed<float> x1, typed<float> y1, typed<float> x2, typed<float> y2) : UIElement(get_Class())
{
	SetBinding(this, get_X1Property(), x1);
	SetBinding(this, get_Y1Property(), y1);
	SetBinding(this, get_X2Property(), x2);
	SetBinding(this, get_Y2Property(), y2);
}

LineVisual::LineVisual(
		typed<float> x1,
		typed<float> y1,
		typed<float> x2,
		typed<float> y2,
		typed<Brush*> brush,
		typed<float> strokeWidth) : UIElement(get_Class())
{
	SetBinding(this, get_X1Property(), x1);
	SetBinding(this, get_Y1Property(), y1);
	SetBinding(this, get_X2Property(), x2);
	SetBinding(this, get_Y2Property(), y2);
	SetBinding(this, get_BrushProperty(), brush);
	SetBinding(this, get_WidthProperty(), strokeWidth);
}

gm::PointF LineVisual::get_Start()
{
	return gm::PointF(get_X1(), get_Y1());
}

gm::PointF LineVisual::get_End()
{
	return gm::PointF(get_X2(), get_Y2());
}

void LineVisual::Render(ManagedRenderContext renderContext)
{
	renderContext.DrawLine(gm::PointF(get_X1(), get_Y1()), gm::PointF(get_X2(), get_Y2()), get_Brush(), get_Width(), get_Style());
}

void LineVisual::OnComputedPropertyValueChanged(PropertyValue* pPropertyValue, bool handled)
{
	if (pPropertyValue->m_dp == get_X1Property() ||
		pPropertyValue->m_dp == get_Y1Property() ||
		pPropertyValue->m_dp == get_X2Property() ||
		pPropertyValue->m_dp == get_Y2Property())
	{
		m_hitGeometry = NULL;
		/*
		if (m_hitGeometry)
		{
			m_hitGeometry->m_D2DGeometry->Release();
			m_hitGeometry->m_D2DGeometry = NULL;
		}
		*/
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyValue, handled);
}

Variant LineVisual::GetLocalPropertyValue(PropertyValue* pPropertyVal)
{
	if (pPropertyVal->m_dp == get_HitGeometryProperty())
	{
		return GetHitGeometry();
	}

	return baseClass::GetLocalPropertyValue(pPropertyVal);
}

geometry LineVisual::GetHitGeometry()
{
	if (m_hitGeometry == nullptr)
	{
		ComPtr<ID2D1PathGeometry> pD2D1Geometry;
		Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pD2D1Geometry);

		ComPtr<ID2D1GeometrySink> pGeometrySink;
		pD2D1Geometry->Open(&pGeometrySink);
	//	pGeometrySink->SetFillMode(D2D1_FILL_MODE_ALTERNATE: D2D1_FILL_MODE_WINDING);

		pGeometrySink->BeginFigure(cnv(get_Start()), D2D1_FIGURE_BEGIN_HOLLOW);
		pGeometrySink->AddLine(cnv(get_End()));
		pGeometrySink->EndFigure(D2D1_FIGURE_END_OPEN);
		pGeometrySink->Close();
		pGeometrySink.Release();

		// Widen into another PathGeometry
		ComPtr<ID2D1PathGeometry> pD2D1Geometry2;
		Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&pD2D1Geometry2);
		ComPtr<ID2D1GeometrySink> pGeometrySink2;
		pD2D1Geometry2->Open(&pGeometrySink2);

		pD2D1Geometry->Widen(get_Width(), nullptr, nullptr, pGeometrySink2);
		pGeometrySink2->Close();
	//	pGeometrySink2->Release();
	//	pD2D1Geometry->Release();	// We're done with the original path geometry

		m_hitGeometry = pD2D1Geometry2.Detach();
	}

	ASSERT(0);
	return nullptr;
	//return m_hitGeometry;

	/*
	PathGeometry* pGeometry = new PathGeometry;

	PathFigure* pFigure = new PathFigure;
	pFigure->m_segments.
	pGeometry->m_figures.push_back(pFigure);
	geometry(
	*/
}

}	// Gui
}	// System
