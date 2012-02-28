#include "stdafx.h"
#include "LXUI2.h"
#include "Canvas.h"

namespace std
{
#include <float.h>
}

namespace System
{
namespace UI
{

// virtual
void Canvas::TopLeftPropertyChangedHandler::OnChanged(DependencyObject* object, DependencyProperty* property, Object* prevSpecifiedValue, Object* newValue)
{
	UIElement* uielement = dynamic_cast<UIElement*>(object);
	ASSERT(uielement);

	Canvas* pCanvas = dynamic_cast<Canvas*>(uielement->GetRParent());
	if (pCanvas)
	{
		pCanvas->InvalidateArrange();
	}
}

DependencyProperty* Canvas::s_LeftProperty = RegisterAttached(WSTR("Left"), typeid(double), typeid(Canvas), DoubleObject::get_NaN(),
																										  PropertyMetaData(None, new Canvas::TopLeftPropertyChangedHandler));

DependencyProperty* Canvas::s_TopProperty = RegisterAttached(WSTR("Top"), typeid(double), typeid(Canvas), DoubleObject::get_NaN(),
																										 PropertyMetaData(None, new Canvas::TopLeftPropertyChangedHandler));

DependencyProperty* Canvas::s_RightProperty = RegisterAttached(WSTR("Right"), typeid(double), typeid(Canvas), DoubleObject::get_NaN(),
																										 PropertyMetaData(None, new Canvas::TopLeftPropertyChangedHandler));

DependencyProperty* Canvas::s_BottomProperty = RegisterAttached(WSTR("Bottom"), typeid(double), typeid(Canvas), DoubleObject::get_NaN(),
																										 PropertyMetaData(None, new Canvas::TopLeftPropertyChangedHandler));

Canvas::Canvas()
{
//	m_Transform = NULL;
}

Canvas::~Canvas()
{
}

/*
ICollection* Canvas::get_Children()
{
	return const_cast<VisualNodes*>(get_rchildList());
}
*/

double Canvas::GetLeft(UIElement* pObject)
{
	return static_cast<DoubleObject*>(pObject->GetValue(get_LeftProperty()))->GetValue();
}

void Canvas::SetLeft(UIElement* pObject, double length)
{
	pObject->SetValue(get_LeftProperty(), DoubleObject::GetObject(length));
}

double Canvas::GetTop(UIElement* pObject)
{
	return static_cast<DoubleObject*>(pObject->GetValue(get_TopProperty()))->GetValue();
}

void Canvas::SetTop(UIElement* pObject, double length)
{
	pObject->SetValue(get_TopProperty(), DoubleObject::GetObject(length));
}

// virtual
LDraw::SizeD Canvas::MeasureOverride(LDraw::SizeD availSize)
{
	/*
	m_availSize = availSize;

	Length* m_Width = get_Width();
	if (m_Width)
	{
		double Value = m_Width->get_Value();
		if (m_Width->get_UnitType() == Length::UnitPercentage)
		{
			m_desiredSize.Width = Value * availSize.Width;
		}
		else
		{
			m_desiredSize.Width = Value;
		}
	}
	else
	{
		m_desiredSize.Width = availSize.Width;
	}

	Length* m_Height = get_Height();
	if (m_Height)
	{
		double Value = m_Height->get_Value();
		if (m_Height->get_UnitType() == Length::UnitPercentage)
		{
			m_desiredSize.Height = Value * availSize.Height;
		}
		else
		{
			m_desiredSize.Height = Value;
		}
	}
	else
	{
		m_desiredSize.Height = availSize.Height;
	}
	*/

	unsigned int ncount = get_InternalChildren()->GetCount();//get_rchildList()->get_Size();
	for (unsigned int i = 0; i < ncount; i++)
	{
		UIElement* pChildElement = get_InternalChildren()->get_Item(i);

		pChildElement->Measure(availSize);
//		pChildElement->SetLayoutOffset(pChildElement->m_computedLeft, pChildElement->m_computedTop);
	}

	// ??
	return availSize;
	return LDraw::SizeD(0,0);
}

//#define foreach(child, collection) for (child

// virtual
LDraw::SizeD Canvas::ArrangeOverride(LDraw::SizeD finalSize)
{
	//UIElement::OnArrange(finalSize);

	unsigned int ncount = get_InternalChildren()->GetCount();
	for (unsigned int i = 0; i < ncount; i++)
	{
		UIElement* pChildElement = get_InternalChildren()->get_Item(i);

		double left = GetLeft(pChildElement);
		double top = GetTop(pChildElement);
	//	double right = GetRight(pChildElement);
	//	double bottom = GetBottom(pChildElement);

		if (std::_isnan(left)) left = 0;
		if (std::_isnan(top)) top = 0;

		pChildElement->Arrange(
			LDraw::RectD(
				LDraw::PointD(left /*+ pChildElement->m_computedLeft*/, top /*+ pChildElement->m_computedTop*/),
				pChildElement->get_DesiredSize()));

		//pChildElement->SetLayoutOffset(left->get_Value() + pChildElement->m_computedLeft, top->get_Value() + pChildElement->m_computedTop);
	}

	return finalSize;
}

/*
// virtual
void Canvas::OnRender2(Graphics* pGraphics)
{
	UIElement::OnRender2(pGraphics);
}
*/

#if 0
Transform* Canvas::get_Transform() const
{
	return m_Transform;
}

void Canvas::put_Transform(/*[in]*/ Transform* newVal)
{
	m_Transform = newVal;
}
#endif

/*
Length* Canvas::get_X() const
{
	return m_X;
}

void Canvas::put_X(Length* newVal)
{
	m_X = newVal;
}

Length* Canvas::get_Y() const
{
	return m_Y;
}

void Canvas::put_Y(Length* newVal)
{
	m_Y = newVal;
}
*/

}	// UI
}
