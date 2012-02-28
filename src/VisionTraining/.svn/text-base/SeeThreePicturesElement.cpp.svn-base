#include "stdafx.h"
#include "VisionTraining.h"

namespace System
{
namespace VisionTraining
{

IMP_DEPENDENCY_PROPERTY(float, SeeThreePicturesElement, Dist, 100)
IMP_DEPENDENCY_PROPERTY(float, SeeThreePicturesElement, Delta, 1.0f)
IMP_DEPENDENCY_PROPERTY(Gui::Visual*, SeeThreePicturesElement, Picture, NULL)

Gui::DependencyClass* SeeThreePicturesElement::get_Class()
{
	static Gui::DependencyClass Class(typeid(SeeThreePicturesElement), Gui::FrameworkElement::get_Class());

	static Gui::DependencyProperty* properties[] =
	{
		get_DistProperty(),
		get_DeltaProperty(),
		get_PictureProperty(),
	};

	return &Class;
}

Gui::DependencyClass* SeeThreePicturesElement::pClass(get_Class());

SeeThreePicturesElement::SeeThreePicturesElement() : Gui::FrameworkElement(get_Class())
{
}

void SeeThreePicturesElement::Render(Gui::ManagedRenderContext renderContext)
{
	static Gui::Brush* blackBrush = new Gui::SolidColorBrush(0,0,0);
//	static Gui::Brush* redBrush = new Gui::SolidColorBrush(1,0,0);
//	static Gui::Brush* blueBrush = new Gui::SolidColorBrush(0,1,0);
//	static Gui::Brush* mixBrush = new Gui::SolidColorBrush(1,1,0);

	renderContext.FillRectangle(LDraw::RectF(0,0, 1200, 1024), blackBrush);

	float dist;
	float cy;

	float middlex = 500;

	dist = get_Dist();
	cy = 200;

	renderContext.PushTransform(new Gui::TranslateTransform(middlex - dist, cy));
	renderContext.DrawVisual(get_Picture());
	renderContext.Pop();

	renderContext.PushTransform(new Gui::TranslateTransform(middlex + dist, cy));
	renderContext.DrawVisual(get_Picture());
	renderContext.Pop();
}

void SeeThreePicturesElement::OnKey(Gui::KeyEventArgs* args)
{
	float delta = get_Delta();

	if (args->m_key == VK_UP)
	{
	}
	else if (args->m_key == VK_DOWN)
	{
	}
	else if (args->m_key == VK_RIGHT)
	{
		set_Dist(get_Dist() + delta);
	}
	else if (args->m_key == VK_LEFT)
	{
		set_Dist(get_Dist() - delta);
	}
}

}	// VisionTraining
}
