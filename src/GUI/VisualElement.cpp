#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(Visual*, VisualElement, Visual, nullptr/*, new PropertyMetadata(true)*/)

VisualElement::VisualElement() : UIElement(get_Class())
{
}

VisualElement::VisualElement(Visual* visual) : UIElement(get_Class())
{
	set_Visual(visual);
}

void VisualElement::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_VisualProperty())
	{
		Visual* visual = get_Visual();
		if (visual)
		{
			visual->SetRoot(GetRoot());
		}
	}

	UIElement::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

Visual* VisualElement::CreateVisual()
{
	return get_Visual();
}

}	// Gui
}	// System
