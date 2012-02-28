#include "stdafx.h"
#include "LXUI2.h"
#include "RotateTransform.h"

namespace System
{
namespace UI
{

DependencyProperty* RotateTransform::s_CenterXProperty = RegisterProperty(WSTR("CenterX"), typeid(double), typeid(RotateTransform), DoubleObject::GetObject(0.0), PropertyMetaData(None));
DependencyProperty* RotateTransform::s_CenterYProperty = RegisterProperty(WSTR("CenterY"), typeid(double), typeid(RotateTransform), DoubleObject::GetObject(0.0), PropertyMetaData(None));
DependencyProperty* RotateTransform::s_AngleProperty = RegisterProperty(WSTR("Angle"), typeid(double), typeid(RotateTransform), DoubleObject::GetObject(0.0), PropertyMetaData(None));

RotateTransform::RotateTransform()
{
}

RotateTransform::RotateTransform(double angle)
{
	set_Angle(angle);
}

RotateTransform::RotateTransform(double angle, Point center)
{
	set_Angle(angle);
	set_CenterX(center.X);
	set_CenterY(center.Y);
}

RotateTransform::RotateTransform(double angle, double centerX, double centerY)
{
	set_Angle(angle);
	set_CenterX(centerX);
	set_CenterY(centerY);
}

double RotateTransform::get_Angle()
{
	return static_cast<DoubleObject*>(GetValue(get_AngleProperty()))->GetValue();
}

void RotateTransform::set_Angle(double newVal)
{
	SetValue(get_AngleProperty(), DoubleObject::GetObject(newVal));
}

double RotateTransform::get_CenterX()
{
	return static_cast<DoubleObject*>(GetValue(get_CenterXProperty()))->GetValue();
}

void RotateTransform::set_CenterX(double newVal)
{
	SetValue(get_CenterXProperty(), DoubleObject::GetObject(newVal));
}

double RotateTransform::get_CenterY()
{
	return static_cast<DoubleObject*>(GetValue(get_CenterYProperty()))->GetValue();
}

void RotateTransform::set_CenterY(double newVal)
{
	SetValue(get_CenterYProperty(), DoubleObject::GetObject(newVal));
}

__release<LDraw::Matrix3f> RotateTransform::get_Value()
{
	m_Value = NULL;

	if (m_Value == NULL)
	{
		double centerX = get_CenterX();
		double centerY = get_CenterY();

		LDraw::matrix3f m = LDraw::matrix3f::getTranslate(centerX, centerY) *
								LDraw::matrix3f::getRotate(get_Angle()) *
								LDraw::matrix3f::getTranslate(-centerX, -centerY);

		m_Value = new LDraw::Matrix3f(m);
 	}

	return m_Value;
}

}	// UI
}
