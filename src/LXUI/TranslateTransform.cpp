#include "stdafx.h"
#include "LXUI2.h"
#include "TranslateTransform.h"

namespace System
{
namespace UI
{

DependencyProperty* TranslateTransform::s_XProperty = RegisterProperty(WSTR("X"), typeid(double), typeid(TranslateTransform), DoubleObject::GetObject(0.0), PropertyMetaData(None));
DependencyProperty* TranslateTransform::s_YProperty = RegisterProperty(WSTR("Y"), typeid(double), typeid(TranslateTransform), DoubleObject::GetObject(0.0), PropertyMetaData(None));

TranslateTransform::TranslateTransform()
{
}

TranslateTransform::TranslateTransform(double x, double y)
{
	set_X(x);
	set_Y(y);
}

double TranslateTransform::get_X()
{
	return static_cast<DoubleObject*>(GetValue(get_XProperty()))->GetValue();
}

void TranslateTransform::set_X(double x)
{
	SetValue(get_XProperty(), DoubleObject::GetObject(x));
}

double TranslateTransform::get_Y()
{
	return static_cast<DoubleObject*>(GetValue(get_YProperty()))->GetValue();
}

void TranslateTransform::set_Y(double y)
{
	SetValue(get_YProperty(), DoubleObject::GetObject(y));
}

__release<LDraw::Matrix3f> TranslateTransform::get_Value()
{
	return LDraw::Matrix3f::GetTranslate(get_X(), get_Y());
}

}	// UI
}
