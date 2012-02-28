#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(Object*, ContentControl, Content, nullptr)
IMP_DEPENDENCY_PROPERTY(float, ContentControl, ContentWidth, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, ContentControl, ContentHeight, 0.0f)

DependencyClass* ContentControl::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_ContentProperty(),
		get_ContentWidthProperty(),
		get_ContentHeightProperty(),
	};

	return &depclass;
}

ContentControl::ContentControl(DependencyClass* depClass) : Control(depClass)
{
}

ContentControl::ContentControl(DependencyClass* depClass, Object* content) : Control(depClass)
{
	set_Content(content);
}

ContentControl::ContentControl(DependencyClass* depClass, Object* content, gm::SizeF size) : Control(depClass, size)
{
	set_Content(content);
}

size_t ContentControl::GetLogicalChildrenCount()
{
	return get_Content() != NULL? 1: 0;
}

Object* ContentControl::GetLogicalChild(size_t position)
{
	Object* content = get_Content();
	if (position != 0 || content == NULL)
	{
		raise(ArgumentOutOfRangeException());
	}

	return content;
}

Object* ContentControl::ReplaceChild(size_t position, Object* newChild)
{
	Object* oldContent = get_Content();
	if (position != 0 || oldContent == NULL)
	{
		raise(ArgumentOutOfRangeException());
	}

	set_Content(newChild);

	return oldContent;
}

void ContentControl::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_ContentProperty())
	{
		// ??
		Object* content = get_Content();
		UIElement* uielement = dynamic_cast<UIElement*>(content);
		if (uielement)
		{
			uielement->set_LogicalParent(this);
		}
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

}	// Gui
}	// System
