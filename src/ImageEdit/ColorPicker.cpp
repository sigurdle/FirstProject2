#include "stdafx.h"
#include "ImageEdit.h"

namespace System
{
namespace ImageEdit
{

Gui::DependencyClass* ColorPicker::get_Class()
{
	static Gui::DependencyClass Class(typeid(ColorPicker), UIElement::get_Class());

	static Gui::DependencyProperty* properties[] =
	{
		get_RedProperty(),
		get_GreenProperty(),
		get_BlueProperty(),
	};

	return &Class;
}

IMP_DEPENDENCY_PROPERTY(float, ColorPicker, Red, 0)
IMP_DEPENDENCY_PROPERTY(float, ColorPicker, Green, 0)
IMP_DEPENDENCY_PROPERTY(float, ColorPicker, Blue, 0)

ColorPicker::ColorPicker() : Gui::UIElement(get_Class())
{
}

void ColorPicker::RenderRetained(Gui::ManagedRetainedRenderContext renderContext)
{
	Gui::GradientStopCollection* stops = new Gui::GradientStopCollection();
	stops->m_colors.Add(Gui::ColorF(0, 0, 0));
	stops->m_colors.Add(Gui::ColorF(1, 1, 1));
	stops->m_offsets.Add(0);
	stops->m_offsets.Add(1);

	Gui::LinearGradientBrush* gradient = new Gui::LinearGradientBrush();
	gradient->set_Stops(stops);

	gradient->set_X1(0);
	gradient->set_Y1(0);
	gradient->set_X2(400);
	gradient->set_Y2(0);

//	gradient->m_end = gm::PointF(400, 0);

	renderContext.FillRectangle(gm::RectF(0, 0, 400, 50), gradient);

	Expressive::typed_expression<float> x = *GetProperty(get_RedProperty());

	renderContext.DrawLine(x * 400.0f, 0, x * 400.0f, 50, new Gui::SolidColorBrush(1, 0, 0), 3);
}

void ColorPicker::OnLeftMouseButtonDown(Gui::MouseButtonEventArgs* args)
{
	CaptureMouse();

	OnMouseMove(args);
	/*
	Gui::Point pt = args->GetClientPosition();	// TODO

	float gray = pt.X / 400;

	SetPropertyValue(get_RedProperty(), gray);
	SetPropertyValue(get_GreenProperty(), gray);
	SetPropertyValue(get_BlueProperty(), gray);
	*/
}

void ColorPicker::OnLeftMouseButtonUp(Gui::MouseButtonEventArgs* args)
{
	ReleaseMouseCapture();
}

void ColorPicker::OnMouseMove(Gui::MouseEventArgs* args)
{
	Gui::Point pt = args->GetClientPosition();	// TODO

	if (get_HasMouseCapture())
	{
		float gray = pt.X / 400;

		SetPropertyValue(get_RedProperty(), gray);
		SetPropertyValue(get_GreenProperty(), gray);
		SetPropertyValue(get_BlueProperty(), gray);
	}
}

}
}
