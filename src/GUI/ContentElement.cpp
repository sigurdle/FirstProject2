#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

UIElement* CreateObjectShadowTree(Object* object)
{
	if (object == nullptr) return nullptr;

	if (UIElement* uielement = dynamic_cast<UIElement*>(object))
	{
		return uielement;
	}
	else if (StringObject* str = dynamic_cast<StringObject*>(object))
	{
		TextVisual* textElement = new TextVisual;
		textElement->set_Text(str);

		return textElement;
	}
	else if (Graphics::Bitmap* bm = dynamic_cast<Graphics::Bitmap*>(object))
	{
		DrawBitmapVisual* bmElement = new DrawBitmapVisual(bm);

		return bmElement;
	}

	return nullptr;
}

IMP_DEPENDENCY_PROPERTY(Object*, ContentElement, Content, nullptr)

DependencyClass* ContentElement::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_ContentProperty()
	};

	return &depclass;
}

DependencyClass* ContentElement::pClass(get_Class());

ContentElement::ContentElement() : UIElement(get_Class())
{
}

void ContentElement::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_ContentProperty())
	{
		Object* content = get_Content();
		if (content)
		{
			UIElement* element = CreateObjectShadowTree(content);
			set_ShadowTree(element);

			// TODO
	//		element->set_LogicalParent(get_LogicalParent());
		}
		else
		{
			set_ShadowTree(nullptr);
		}
	}
	else if (pPropertyVal->m_dp == get_LogicalParentProperty())
	{
		/*
		UIElement* element = get_ShadowTree();
		if (element)
		{
			element->set_LogicalParent(get_LogicalParent());
		}
		*/
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

}	// Gui
}	// System
