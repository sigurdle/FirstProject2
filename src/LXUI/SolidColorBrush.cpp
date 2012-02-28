#include "stdafx.h"
#include "LXUI2.h"
#include "SolidColorBrush.h"

namespace System
{
namespace UI
{

	/*
class CreateIfNull
{
public:
	CreateIfNull();
};

CreateIfNull createifnull;

CreateIfNull::CreateIfNull()
{
	if (SolidColorBrush::ColorProperty == NULL)
	{
		SolidColorBrush::ColorProperty = RegisterProperty(WSTR("Color"), typeid(Color), typeid(SolidColorBrush), NULL, PropertyMetaData(None));
	}
}
*/

DependencyProperty* SolidColorBrush::s_ColorProperty = RegisterProperty(WSTR("Color"), typeid(Color), typeid(SolidColorBrush), new Color(), PropertyMetaData(None));

SolidColorBrush::SolidColorBrush()
{
	/*
	if (ColorProperty == NULL)
	{
		ColorProperty = RegisterProperty(WSTR("Color"), typeid(Color), typeid(SolidColorBrush), NULL, PropertyMetaData(None));
	}
	*/

//	m_Color = NULL;
//	m_Opacity = 1.0;
}

SolidColorBrush::SolidColorBrush(Color color)
{
	/*
	if (ColorProperty == NULL)
	{
		ColorProperty = RegisterProperty(WSTR("Color"), typeid(Color), typeid(SolidColorBrush), NULL, PropertyMetaData(None));
	}
*/
	set_Color(color);
}

SolidColorBrush::SolidColorBrush(Color color, double opacity)
{
	/*
	if (ColorProperty == NULL)
	{
		ColorProperty = RegisterProperty(WSTR("Color"), typeid(Color), typeid(SolidColorBrush), NULL, PropertyMetaData(None));
	}
	*/

	set_Color(color);
	set_Opacity(opacity);
}

// virtual
__release<LDraw::Brush> SolidColorBrush::CreateBrush(UIElement* pReferencingElement, double scaleX, double scaleY)
{
	int opacity = get_Opacity()*255;
	if (opacity < 0) opacity = 0;
	else if (opacity > 255) opacity = 255;

	Color color = get_Color();
//	if (color != NULL)
	{
		LDraw::Color dcolor = LDraw::Color(color.get_A()*opacity/255, color.get_R(), color.get_G(), color.get_B());
		return new LDraw::SolidBrush(dcolor);
	}
/*	else
	{
		return NULL;
	}
	*/
}

Color SolidColorBrush::get_Color()
{
	return *static_cast<Color*>(GetValue(get_ColorProperty()));
}

void SolidColorBrush::set_Color(Color newVal)
{
	SetValue(get_ColorProperty(), new Color(newVal));
}

}	// UI
}
