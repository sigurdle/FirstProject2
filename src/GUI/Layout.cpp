#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, Layout, DesiredWidth, float_NaN.value)
IMP_DEPENDENCY_PROPERTY(float, Layout, DesiredHeight, float_NaN.value)
IMP_DEPENDENCY_PROPERTY(float, Layout, ActualWidth, float_NaN.value)
IMP_DEPENDENCY_PROPERTY(float, Layout, ActualHeight, float_NaN.value)

DependencyClass* Layout::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_DataProperty(),
	};
	*/

	return &depclass;
}

//DependencyClass* Layout::pClass(get_Class());

Layout::Layout(UIElement* element) : DependencyObject(get_Class()), m_element(element)
{
}

size_t Layout::GetChildrenCount()
{
	return 0;
}

Layout* Layout::GetChild(size_t index)
{
	return nullptr;
}

void Layout::AddChild(Layout* child)
{
}

gm::SizeF Layout::get_DesiredSize()
{
	return gm::SizeF(0,0);
}

// PanelLayout

size_t PanelLayout::GetChildrenCount()
{
	return m_children.size();
}

Layout* PanelLayout::GetChild(size_t index)
{
	return m_children[index];
}

void PanelLayout::AddChild(Layout* child)
{
	m_children.push_back(child);
}

// StackLayout

StackLayout::StackLayout(UIElement* element) : PanelLayout(element)
{
	m_direction = Direction_Horizontal;
}

gm::SizeF StackLayout::PreLayOut(gm::RectF availRect)
{
	return gm::SizeF(0,0);
}

gm::SizeF StackLayout::LayOut(gm::RectF layoutRect)
{
	float y = 0;

	gm::RectF childRect(0, 0, layoutRect.Width, 0);

	size_t nchildren = GetChildrenCount();
	for (size_t i = 0; i < nchildren; ++i)
	{
		Layout* child = GetChild(i);

		gm::SizeF desiredSize = child->get_DesiredSize();

		childRect.Y = y;
		childRect.Height = 0;

		child->LayOut(childRect);
	}

	return gm::SizeF(0,0);
}

}
}
