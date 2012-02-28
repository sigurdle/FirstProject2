#include "stdafx.h"
#include "LXUI2.h"
#include "Thumb.h"

namespace System
{
namespace UI
{

void DragDeltaEventArgs::InvokeEventHandler(Object* genericTarget, stub_interface_base* genericHandler)
{
	stub_interface2<void, Object*, DragDeltaEventArgs*>* handler = dynamic_cast<stub_interface2<void, Object*, DragDeltaEventArgs*>*>(genericHandler);
	ASSERT(handler);

	handler->invoke(genericTarget, this);
}

/*
Thumb::Thumb()
{
	Border* pBorder = new Border(new Thickness(1));
	pBorder->set_BorderBrush(new LinearGradientBrush(new Color(255, 255, 255), new Color(0, 0, 0), new Point(0, 0), new Point(0, 1)));
//	pBorder->set_BorderBrush(new SolidColorBrush(new Color(0, 0, 0)));
	pBorder->set_Background(new SolidColorBrush(new Color(80, 114, 158)));

	set_VisualTree(pBorder);
}
*/

DependencyProperty* Thumb::s_IsDraggingProperty = RegisterProperty(WSTR("IsDragging"), typeid(bool), typeid(Thumb), BoolObject::get_False(), PropertyMetaData(None));

RoutedEvent* Thumb::s_DragStartedEvent;
RoutedEvent* Thumb::s_DragCompletedEvent;
RoutedEvent* Thumb::s_DragDeltaEvent = EventManager::RegisterRoutedEvent(WSTR("DragDelta"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, DragDeltaEventArgs*>), typeid(Thumb));

//void ApplyStyle(Style* style, FrameworkElement* element);
//Object* CreateObjectFromElement(Type* pType, Object* parentObject, XmlData::Node* node, Type** pReturnType);

__live_object_ptr<Style> ThumbStyle;

Thumb::Thumb()
{
	m_dragging = false;

	if (ThumbStyle == NULL)
	{
		XmlData::Document* document = new XmlData::Document;

		StringW* filename = MakeFilePath(_Module, L"../../../ThumbStyle.lxui");
		document->load(filename);

		Type* returnType;
		ThumbStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));
	}

	set_Style(ThumbStyle);
/*
	ApplyStyle(get_Style(), this);
	InitScript();
	*/
}

bool Thumb::get_IsDragging()
{
	return static_cast<BoolObject*>(GetValue(get_IsDraggingProperty()))->GetValue();
}

void Thumb::set_IsDragging(bool dragging)
{
	SetValue(get_IsDraggingProperty(), BoolObject::GetObject(dragging));
}

void Thumb::OnMouseDown(MouseButtonEventArgs* args)
{
	if (!m_dragging)
	{
		CaptureMouse();
		set_IsDragging(true);
		m_dragging = true;
		m_oldpoint = args->GetPosition(dynamic_cast<IInputElement*>(GetRParent()));//LDraw::PointD(mouseevt->get_ScreenX(), mouseevt->get_ScreenY());
	}

	args->set_Handled(true);
}

void Thumb::OnMouseUp(MouseButtonEventArgs* args)
{
	if (m_dragging)
	{
		ReleaseMouseCapture();
		set_IsDragging(false);
		m_dragging = false;
	}

	args->set_Handled(true);
}

void Thumb::OnMouseMove(MouseEventArgs* args)
{
//	Point point(mouseevt->get_ScreenX(), mouseevt->get_ScreenY());
	Point point = args->GetPosition(dynamic_cast<IInputElement*>(GetRParent()));//point(mouseevt->get_ScreenX(), mouseevt->get_ScreenY());

	if (m_dragging)
	{
#if 0
		DragDeltaEvent* dragevent = new DragDeltaEvent;
		dragevent->InitEvent(WSTR("DragDelta"), true, true);

		dragevent->m_HorizontalChange = point.X - m_oldpoint.X;
		dragevent->m_VerticalChange = point.Y - m_oldpoint.Y;

		m_oldpoint = point;

		dispatchEvent(dragevent);
#endif

		DragDeltaEventArgs* args = new DragDeltaEventArgs;
		args->set_RoutedEvent(get_DragDeltaEvent());
		args->m_HorizontalChange = point.X - m_oldpoint.X;
		args->m_VerticalChange = point.Y - m_oldpoint.Y;
		m_oldpoint = point;

		RaiseEvent(args);
	}

	args->set_Handled(true);
}

#if 0
void Thumb::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	if (evt->get_eventPhase() != CAPTURING_PHASE)
	{
		if (type == MouseEvent::mousedown)
		{
			MouseEvent* mouseevt = static_cast<MouseEvent*>(evt);

			if (!m_dragging)
			{
				CaptureMouse();
				m_dragging = true;
				m_oldpoint = LDraw::PointD(mouseevt->get_ScreenX(), mouseevt->get_ScreenY());
			}

		//	OnLButtonDown(static_cast<MouseEvent*>(evt));
			evt->stopPropagation();
		}
		else if (type == MouseEvent::mouseup)
		{
			if (m_dragging)
			{
				ReleaseMouseCapture();
				m_dragging = false;
			}
		//	OnLButtonUp(static_cast<MouseEvent*>(evt));
			evt->stopPropagation();
		}
		else if (type == MouseEvent::mousemove)
		{
			MouseEvent* mouseevt = static_cast<MouseEvent*>(evt);

			//LDraw::PointD point = ScreenToClient(evt->get_ScreenX(), evt->get_ScreenY());
			LDraw::PointD point(mouseevt->get_ScreenX(), mouseevt->get_ScreenY());

			if (m_dragging)
			{
				DragDeltaEvent* dragevent = new DragDeltaEvent;
				dragevent->InitEvent(WSTR("DragDelta"), true, true);

				dragevent->m_HorizontalChange = point.X - m_oldpoint.X;
				dragevent->m_VerticalChange = point.Y - m_oldpoint.Y;

				m_oldpoint = point;

				dispatchEvent(dragevent);
			}

		//	OnMouseMove(static_cast<MouseEvent*>(evt));
			evt->stopPropagation();
		}
	}
}
#endif

}	// UI
}
