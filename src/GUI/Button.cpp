#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_ROUTEDEVENT(Click, Button, RoutingStrategy_Bubble, typeid(Event2<Object*, RoutedEventArgs*>));

DependencyClass* Button::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

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

	static RoutedEvent* events[] =
	{
		get_ClickEvent(),
	};

	return &depclass;
}

DependencyClass* Button::pClass(get_Class());

static Expressive::ADeclarationList* aexp;

Button::Button() : ButtonBase(get_Class())
{
	Init();
}

Button::Button(Object* content) : ButtonBase(get_Class(), content)
{
	Init();
}

void Button::Init()
{
	if (aexp == nullptr)
	{
		aexp = Expressive::Parser::ProgramFromFile("D:\\Button.gui");
	}

	Expressive::FrameContext frame;
	frame.m_variables["sc"] = this;

	Expressive::Expression* exp = Expressive::Translator::Translate(aexp, &frame);
	
	Object* obj = dynamic_cast<Expressive::StaticObjectExpression*>(exp)->m_obj;
	UIElement* element = dynamic_cast<UIElement*>(obj);

	/*
	m_contentContainer = dynamic_cast<UIElement*>(element->FindElement(L"Content"));

	if (m_contentContainer == NULL)
	{
		raise(SystemException(L"ListBox - no content container in template"));
	}
	*/

	set_ShadowTree(element);
}

void Button::OnMouseLeftButtonDown(MouseButtonEventArgs* args)
{
	if (!get_IsMouseCaptured())
	{
		CaptureMouse();
	}
}

void Button::OnMouseLeftButtonUp(MouseButtonEventArgs* args)
{
	if (get_IsMouseCaptured())
	{
		ReleaseMouseCapture();
		RaiseEvent(new RoutedEventArgs(get_ClickEvent(), this));
	}
}

}	// Gui
}	// System
