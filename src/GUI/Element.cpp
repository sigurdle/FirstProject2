#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyClass* Element::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_IDProperty(),
	};

	return &depclass;
}

IMP_DEPENDENCY_PROPERTY(String, Element, ID, String()/*, new PropertyMetadata()*/);

Element::Element(DependencyClass* depClass) : DependencyObject(depClass)
{
}

void Element::RenderRetained(ManagedRetainedRenderContext renderContext)
{
	ASSERT(0);
}

void Element::SetRoot(IRootVisual* root)
{
	if (m_root != root)
	{
		OnSetRoot(root);
		m_root = root;
	}
}

String Element::get_typeName()
{
	return GetType()->get_Name();
}

String Element::get_namespaceURI()
{
	return nullptr;	// TODO
}

String Element::get_id()
{
	return nullptr;	// TODO
}

String Element::get_pseudoElementName()
{
	return nullptr;	// TODO
}

String Element::getAttribute(StringIn name)
{
	return nullptr;	// TODO
}

bool Element::hasAttribute(StringIn name)
{
	return false;
}

Style::ICSSElementResolver* Element::get_rparent()
{
	return nullptr;	// TODO
}

Style::ICSSElementResolver* Element::get_prevSibling()
{
	return nullptr;	// TODO
}

Style::ICSSElementResolver* Element::get_nextSibling()
{
	return nullptr;	// TODO
}

bool Element::IsInherited(Object* pProperty)
{
	return false;	// TODO
}

bool Element::IsValueInherit(Object* value)
{
	return false;	// TODO
}

}	// Gui
}	// System
