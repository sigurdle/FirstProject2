#include "stdafx.h"
#include "LXUI2.h"
#include "ScaleTransform.h"

namespace System
{
namespace UI
{

DependencyProperty* ScaleTransform::s_CenterXProperty = RegisterProperty(WSTR("CenterX"), typeid(double), typeid(ScaleTransform), DoubleObject::GetObject(0.0), PropertyMetaData(None));
DependencyProperty* ScaleTransform::s_CenterYProperty = RegisterProperty(WSTR("CenterY"), typeid(double), typeid(ScaleTransform), DoubleObject::GetObject(0.0), PropertyMetaData(None));
DependencyProperty* ScaleTransform::s_ScaleXProperty = RegisterProperty(WSTR("ScaleX"), typeid(double), typeid(ScaleTransform), DoubleObject::GetObject(1.0), PropertyMetaData(None));
DependencyProperty* ScaleTransform::s_ScaleYProperty = RegisterProperty(WSTR("ScaleY"), typeid(double), typeid(ScaleTransform), DoubleObject::GetObject(1.0), PropertyMetaData(None));

ScaleTransform::ScaleTransform()
{
}

/*
ScaleTransform::ScaleTransform(double scalex, double scaley, Point* center)
{
	m_ScaleX = scalex;
	m_ScaleY = scaley;
	m_Center = center;
}
*/

double ScaleTransform::get_CenterX()
{
	return static_cast<DoubleObject*>(GetValue(get_CenterXProperty()))->GetValue();
}

void ScaleTransform::set_CenterX(double newVal)
{
	SetValue(get_CenterXProperty(), DoubleObject::GetObject(newVal));
}

double ScaleTransform::get_CenterY()
{
	return static_cast<DoubleObject*>(GetValue(get_CenterYProperty()))->GetValue();
}

void ScaleTransform::set_CenterY(double newVal)
{
	SetValue(get_CenterYProperty(), DoubleObject::GetObject(newVal));
}

double ScaleTransform::get_ScaleX()
{
	return static_cast<DoubleObject*>(GetValue(get_ScaleXProperty()))->GetValue();
}

void ScaleTransform::set_ScaleX(double newVal)
{
	SetValue(get_ScaleXProperty(), DoubleObject::GetObject(newVal));
}

double ScaleTransform::get_ScaleY()
{
	return static_cast<DoubleObject*>(GetValue(get_ScaleYProperty()))->GetValue();
}

void ScaleTransform::set_ScaleY(double newVal)
{
	SetValue(get_ScaleYProperty(), DoubleObject::GetObject(newVal));
}

__release<LDraw::Matrix3f> ScaleTransform::get_Value()
{
	m_Value = NULL;

	if (m_Value == NULL)
	{
	//	if (m_Center != NULL)
		{
			double centerX = get_CenterX();
			double centerY = get_CenterY();
			double scaleX = get_ScaleX();
			double scaleY = get_ScaleY();

			LDraw::matrix3f m = LDraw::matrix3f::getTranslate(centerX, centerY) *
				LDraw::matrix3f::getScale(scaleX, scaleY) *
				LDraw::matrix3f::getTranslate(-centerX, -centerY);

			m_Value = new LDraw::Matrix3f(m);

			/*
			m_Value = LDraw::Matrix3f::GetTranslate(centerX, centerY);
			*m_Value *=	*LDraw::Matrix3f::GetScale(scaleX, scaleY);
			*m_Value *=	*LDraw::Matrix3f::GetTranslate(-centerX, -centerY);
			*/
		}
		/*
		else
		{
			m_Value = LDraw::Matrix3f::GetScale(m_ScaleX, m_ScaleY);
		}
		*/
	}

	return m_Value;
}

}	// UI
}
