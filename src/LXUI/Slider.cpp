#include "stdafx.h"
#include "LXUI2.h"
#include "Slider.h"

namespace System
{
namespace UI
{

__live_object_ptr<Style> SliderStyle;

DependencyProperty* Slider::s_OrientationProperty = RegisterProperty(WSTR("Orientation"), typeid(Orientation), typeid(Slider), IntObject::GetObject(Orientation_Horizontal), PropertyMetaData(None));

Slider::Slider()
{
	if (SliderStyle == NULL)
	{
		SliderStyle = dynamic_cast<Style*>(FindResource(GetType()));
	}

	set_Style(SliderStyle);
/*
	ApplyStyle(get_Style(), this);

	InitScript();
	*/
}

Slider::Slider(Orientation orientation)
{
	if (SliderStyle == NULL)
	{
		SliderStyle = dynamic_cast<Style*>(FindResource(GetType()));
	}

	set_Style(SliderStyle);
/*
	ApplyStyle(get_Style(), this);

	InitScript();
*/
	set_Orientation(orientation);
}

Orientation Slider::get_Orientation()
{
	return (Orientation)static_cast<IntObject*>(GetValue(get_OrientationProperty()))->GetValue();
}

void Slider::set_Orientation(Orientation orientation)
{
	SetValue(get_OrientationProperty(), IntObject::GetObject(orientation));
}

void Slider::OnPropertyChanged(DependencyPropertyChangedEventArgs args)
{
	DependencyProperty* dp = args.get_Property();

	if (dp == get_ValueProperty())
	{
		double oldValue = static_cast<DoubleObject*>(args.get_OldValue())->GetValue();
		double newValue = static_cast<DoubleObject*>(args.get_NewValue())->GetValue();

		if (newValue != oldValue)	// ?? What about the first time?
		{
			RoutedPropertyChangedEventArgs<double>* args = new RoutedPropertyChangedEventArgs<double>(oldValue, newValue, get_ValueChangedEvent());

			RaiseEvent(args);
		}
	}

	Control::OnPropertyChanged(args);
}

}
}
