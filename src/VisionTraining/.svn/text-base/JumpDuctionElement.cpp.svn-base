#include "stdafx.h"
#include "VisionTraining.h"

namespace System
{
namespace VisionTraining
{

IMP_DEPENDENCY_PROPERTY(float, JumpDuctionElement, InDist, 100)
IMP_DEPENDENCY_PROPERTY(float, JumpDuctionElement, OutDist, 50)
IMP_DEPENDENCY_PROPERTY(bool, JumpDuctionElement, InMode, true)
IMP_DEPENDENCY_PROPERTY(float, JumpDuctionElement, Delta, 2.0f)
IMP_DEPENDENCY_PROPERTY(Gui::Color*, JumpDuctionElement, LeftEyeColor, Gui::Color::get_GreenColor())
IMP_DEPENDENCY_PROPERTY(Gui::Color*, JumpDuctionElement, RightEyeColor, Gui::Color::get_MagentaColor())
IMP_DEPENDENCY_PROPERTY(float, JumpDuctionElement, Darken, 0.5f)

Gui::DependencyClass* JumpDuctionElement::get_Class()
{
	static Gui::DependencyClass Class(typeid(JumpDuctionElement), Gui::FrameworkElement::get_Class());

	static Gui::DependencyProperty* properties[] =
	{
		get_InDistProperty(),
		get_OutDistProperty(),
		get_InModeProperty(),
		get_DeltaProperty(),
		get_LeftEyeColorProperty(),
		get_RightEyeColorProperty(),

		get_DarkenProperty(),
	};

	return &Class;
}

Gui::DependencyClass* JumpDuctionElement::pClass(get_Class());

JumpDuctionElement::JumpDuctionElement() : Gui::FrameworkElement(get_Class())
{
}

void JumpDuctionElement::Render(Gui::ManagedRenderContext renderContext)
{
	static Gui::Brush* blackBrush = new Gui::SolidColorBrush(Gui::Color::get_BlackColor());

	renderContext.FillRectangle(LDraw::RectF(0,0, 1900, 1200), blackBrush);

//	if (m_leftEyeBrush == NULL)
	{
		m_leftEyeBrush = new Gui::SolidColorBrush(*get_LeftEyeColor() * get_Darken());
		m_rightEyeBrush = new Gui::SolidColorBrush(*get_RightEyeColor() * get_Darken());
		m_mixEyeBrush = new Gui::SolidColorBrush(*Gui::Color::get_WhiteColor() * get_Darken());
	}

	/*
	static Gui::Brush* leftBrush = new Gui::SolidColorBrush(1,0,1);	// magenta
	static Gui::Brush* rightBrush = new Gui::SolidColorBrush(0,1,0);	// green
	*/
//	Gui::Brush* mixBrush = new Gui::SolidColorBrush(Color::get_WhiteColor());	// white

	float rx = 30;
	float ry = rx;
	float strokewidth = 15;

	float dist;
	float cy;

	float middlex = 500;

	{
		dist = get_InDist();
		cy = 200;
//		renderContext.DrawEllipse(middlex - dist, cy, rx, ry, leftBrush, strokewidth);
//		renderContext.DrawEllipse(middlex + dist, cy, rx, ry, rightBrush, strokewidth);

		Gui::EllipseGeometry ellipse1(middlex - dist, cy, rx, ry);
		Gui::EllipseGeometry ellipse2(middlex + dist, cy, rx, ry);

		Gui::geometry geom1(ellipse1.Widen(strokewidth));
		Gui::geometry geom2(ellipse2.Widen(strokewidth));

		renderContext.FillGeometry(geom1 - geom2, m_rightEyeBrush);
		renderContext.FillGeometry(geom2 - geom1, m_leftEyeBrush);
		renderContext.FillGeometry(geom1 & geom2, m_mixEyeBrush);
	}

	dist = get_OutDist();
	cy = 500;
	renderContext.DrawEllipse(middlex - dist, cy, rx, ry, m_leftEyeBrush, strokewidth);
	renderContext.DrawEllipse(middlex + dist, cy, rx, ry, m_rightEyeBrush, strokewidth);
}

void JumpDuctionElement::OnKey(Gui::KeyEventArgs* args)
{
	float delta = get_Delta();

	if (args->m_key == VK_UP)
	{
		set_InMode(true);
	}
	else if (args->m_key == VK_DOWN)
	{
		set_InMode(false);
	}
	else if (args->m_key == VK_RIGHT)
	{
		if (get_InMode())
			set_InDist(get_InDist() + delta);
		else
			set_OutDist(get_OutDist() + delta);
	}
	else if (args->m_key == VK_LEFT)
	{
		if (get_InMode())
			set_InDist(get_InDist() - delta);
		else
			set_OutDist(get_OutDist() - delta);
	}
}

}	// VisionTraining
}
