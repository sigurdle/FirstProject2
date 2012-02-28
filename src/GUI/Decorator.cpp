#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(UIElement*, Decorator, Child, nullptr)

DependencyClass* Decorator::get_Class()
{
	static DependencyClass depclass(typeid(Decorator), FrameworkElement::get_Class());
/*
	static DependencyProperty* properties[] =
	{
		get_ParentProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
	};
*/
	return &depclass;
}

Decorator::Decorator(DependencyClass* depClass) : FrameworkElement(depClass)
{
}

size_t Decorator::GetChildrenCount()
{
	return get_Child()? 1:0;
}

void Decorator::AddChild(UIElement* element)
{
	if (get_Child() == NULL)
	{
		set_Child(element);
	}
	else
	{
		ASSERT(0);
	}
}

UIElement* Decorator::GetChild(size_t index)
{
	if (index != 0 || get_Child() == NULL)
	{
		raise(ArgumentOutOfRangeException());
	}

	return get_Child();
}

}	// Gui
}
