#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, ScaleTransform, ScaleX, 1.0f)
IMP_DEPENDENCY_PROPERTY(float, ScaleTransform, ScaleY, 1.0f)

DependencyClass* ScaleTransform::get_Class()
{
	static DependencyClass depclass(typeid(ScaleTransform), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_ScaleXProperty(),
		get_ScaleYProperty(),
	};

	return &depclass;
}

DependencyClass* ScaleTransform::pClass(get_Class());

ScaleTransform::ScaleTransform() : Transform(get_Class())
{
}

ScaleTransform::ScaleTransform(typed<float> scaleX, typed<float> scaleY) : Transform(get_Class())
{
	SetBinding(this, get_ScaleXProperty(), scaleX);
	SetBinding(this, get_ScaleYProperty(), scaleY);
}

gm::matrix3f ScaleTransform::get_Matrix()
{
	return gm::matrix3f::getScale(get_ScaleX(), get_ScaleY());
}

}	// Gui
}	// System
