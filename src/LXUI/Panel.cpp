#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

DependencyProperty* Panel::s_IsItemsHostProperty = RegisterProperty(WSTR("IsItemsHost"), typeid(bool), typeid(Panel), BoolObject::get_False());
DependencyProperty* Panel::s_BackgroundProperty = RegisterProperty(WSTR("Background"), typeid(Brush), typeid(Panel), NULL, PropertyMetaData(AffectsRender));

Panel::Panel()
{
	m_Children = new UIElementCollection;
	m_Children->m_owner = this;
}

bool Panel::get_IsItemsHost()
{
	return static_cast<BoolObject*>(GetValue(get_IsItemsHostProperty()))->GetValue();
}

void Panel::set_IsItemsHost(bool isItemsHost)
{
	SetValue(get_IsItemsHostProperty(), BoolObject::GetObject(isItemsHost));
}

Brush* Panel::get_Background()
{
	return static_cast<Brush*>(GetValue(get_BackgroundProperty()));
}

void Panel::set_Background(Brush* pBrush)
{
	SetValue(get_BackgroundProperty(), pBrush);
}

unsigned int Panel::get_VisualChildrenCount()
{
	return m_Children->m_items.size();
}

Visual* Panel::GetVisualChild(unsigned int index)
{
	if (index < m_Children->m_items.size())
		return m_Children->m_items[index];
	else
		throw new ArgumentOutOfRangeException();
}

UIElementCollection* Panel::get_Children()
{
	return m_Children;
}

UIElementCollection* Panel::get_InternalChildren()
{
	// TODO ?
	return m_Children;
}

void Panel::AddText(System::StringW* str)
{
	throw new Exception(WSTR("Text child not supported"));
}

void Panel::AddChild(UIElement* child)
{
	if (child == NULL)
		throw new Exception(WSTR("null child not supported"));

	/*
	child->SetRParent(this);
	child->SetOwnerWindow(GetOwnerWindow());
	*/
//	AddVisualChild(child);

	get_Children()->Add(child);
}

void Panel::AddChild(Object* obj)
{
	UI::UIElement* uielement = dynamic_cast<UI::UIElement*>(obj);
	if (uielement == NULL)
	{
		new Exception(WSTR("Child is not a UIElement"));
	}

	AddChild(uielement);
}

void Panel::OnRenderBackground(Graphics* pGraphics)
{
	Brush* pBackgroundBrush = get_Background();
	if (pBackgroundBrush)
	{
		LDraw::SizeD actualSize = get_ActualSize();
		__release<LDraw::Brush> brush = pBackgroundBrush->CreateBrush(this, 1, 1);
		pGraphics->FillRectangle(brush, 0, 0, actualSize.Width, actualSize.Height);
	}

//	OnRender(pGraphics);

	//OnRender3(pGraphics);
}

}	// UI
}
