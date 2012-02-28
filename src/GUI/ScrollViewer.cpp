#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, ScrollViewer, ExtentWidth, 0.0f)	// Read-only
IMP_DEPENDENCY_PROPERTY(float, ScrollViewer, ExtentHeight, 0.0f)	// Read-only
IMP_DEPENDENCY_PROPERTY(float, ScrollViewer, ScrollableWidth, 0.0f)	// Read-only
IMP_DEPENDENCY_PROPERTY(float, ScrollViewer, ScrollableHeight, 0.0f)	// Read-only
IMP_DEPENDENCY_PROPERTY(float, ScrollViewer, ViewportWidth, 0.0f)	// Read-only
IMP_DEPENDENCY_PROPERTY(float, ScrollViewer, ViewportHeight, 0.0f)	// Read-only
IMP_DEPENDENCY_PROPERTY(float, ScrollViewer, HorizontalOffset, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, ScrollViewer, VerticalOffset, 0.0f)

DependencyClass* ScrollViewer::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_ExtentWidthProperty(),
		get_ExtentHeightProperty(),
		get_ScrollableWidthProperty(),
		get_ScrollableHeightProperty(),
		get_ViewportWidthProperty(),
		get_ViewportHeightProperty(),
		get_HorizontalOffsetProperty(),
		get_VerticalOffsetProperty(),
	};

	return &depclass;
}

DependencyClass* ScrollViewer::pClass(get_Class());

static Expressive::ADeclarationList* aexp;

ScrollViewer::ScrollViewer() : ContentControl(get_Class())
{
	if (aexp == NULL)
	{
		aexp = Expressive::Parser::ProgramFromFile("D:\\ScrollViewer.gui");
	}

	Expressive::FrameContext frame;
	frame.m_variables["sc"] = this;

	Expressive::Expression* exp = Expressive::Translator::Translate(aexp, &frame);
//	Expressive::Expression* exp = Expressive::Translator::Translate(dynamic_cast<Expressive::AExpressionDeclaration*>(aexp->m_items[1])->m_exp);
	
	Object* obj = dynamic_cast<Expressive::StaticObjectExpression*>(exp)->m_obj;
	UIElement* element = dynamic_cast<UIElement*>(obj);
	set_ShadowTree(element);
}

}	// Gui
}	// System
