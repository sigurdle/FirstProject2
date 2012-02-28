#include "stdafx.h"
#include "LXUI2.h"
#include "GradientBrush.h"
#include "GradientStop.h"
#include "GradientStopCollection.h"

namespace System
{
namespace UI
{

DependencyProperty* GradientBrush::s_GradientStopsProperty = RegisterProperty(WSTR("GradientStops"), typeid(GradientStopCollection), typeid(GradientBrush), NULL, PropertyMetaData(None));

GradientBrush::GradientBrush()
{
}

GradientStopCollection* GradientBrush::get_GradientStops()
{
	return static_cast<GradientStopCollection*>(GetValue(get_GradientStopsProperty()));
}

void GradientBrush::set_GradientStops(GradientStopCollection* newVal)
{
	SetValue(get_GradientStopsProperty(), newVal);
}

}	// UI
}
