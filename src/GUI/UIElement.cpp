#include "stdafx.h"
#include "GUI2.h"

#include<limits>

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, UIElement, Width, 0.0f)	// TODO NaN
IMP_DEPENDENCY_PROPERTY(float, UIElement, Height, 0.0f)	// TODO NaN
IMP_DEPENDENCY_PROPERTY(float, UIElement, MinWidth, 0.0f)	// TODO NaN
IMP_DEPENDENCY_PROPERTY(float, UIElement, MinHeight, 0.0f)	// TODO NaN
IMP_DEPENDENCY_PROPERTY(float, UIElement, MaxWidth, 0.0f)	// TODO NaN
IMP_DEPENDENCY_PROPERTY(float, UIElement, MaxHeight, 0.0f)	// TODO NaN
IMP_DEPENDENCY_PROPERTY(float, UIElement, ActualWidth, 0.0f)	// TODO NaN
IMP_DEPENDENCY_PROPERTY(float, UIElement, ActualHeight, 0.0f)	// TODO NaN
IMP_DEPENDENCY_PROPERTY(bool, UIElement, IsMouseCaptured, false)
IMP_DEPENDENCY_PROPERTY(bool, UIElement, HasFocus, false)
IMP_DEPENDENCY_PROPERTY(bool, UIElement, IsFocusable, false)
IMP_DEPENDENCY_PROPERTY(bool, UIElement, IsMouseOver, false)
IMP_DEPENDENCY_PROPERTY(bool, UIElement, IsMouseDirectlyOver, false)
IMP_DEPENDENCY_PROPERTY(bool, UIElement, IsStylusOver, false)
IMP_DEPENDENCY_PROPERTY(bool, UIElement, IsStylusDirectlyOver, false)
IMP_DEPENDENCY_PROPERTY(bool, UIElement, AllowDrop, true)
IMP_DEPENDENCY_PROPERTY(bool, UIElement, IsActive, false)
IMP_DEPENDENCY_PROPERTY(bool, UIElement, IsActivatable, true)
IMP_DEPENDENCY_PROPERTY(bool, UIElement, IsEnabled, true)
IMP_DEPENDENCY_PROPERTY(Cursor*, UIElement, Cursor, Cursors::get_Arrow())
IMP_DEPENDENCY_PROPERTY(UIElement*, UIElement, ShadowTree, nullptr)

IMP_DEPENDENCY_PROPERTY(Visual*, UIElement, FirstChild, nullptr)
IMP_DEPENDENCY_PROPERTY(Visual*, UIElement, LastChild, nullptr)

IMP_DEPENDENCY_PROPERTY(Thickness, UIElement, BorderThickness, Thickness())
IMP_DEPENDENCY_PROPERTY(Thickness, UIElement, Padding, Thickness())
IMP_DEPENDENCY_PROPERTY(Thickness, UIElement, Margin, Thickness())

IMP_DEPENDENCY_PROPERTY(HorizontalAlignment, UIElement, HorizontalAlignment, HorizontalAlignment_Left)
IMP_DEPENDENCY_PROPERTY(HorizontalAlignment, UIElement, HorizontalContentAlignment, HorizontalAlignment_Left)

/*
template<class T> class ImpRoutedEvent
{
public:
};
*/

IMP_ROUTEDEVENT(MouseButtonDown, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>))
IMP_ROUTEDEVENT(MouseButtonDownPreview, UIElement, RoutingStrategy_Tunnel, typeid(Event2<Object*, MouseButtonEventArgs*>))

IMP_ROUTEDEVENT(MouseButtonUp, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>))
IMP_ROUTEDEVENT(MouseButtonUpPreview, UIElement, RoutingStrategy_Tunnel, typeid(Event2<Object*, MouseButtonEventArgs*>))

IMP_ROUTEDEVENT(MouseLeftButtonDown, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>))
IMP_ROUTEDEVENT(MouseLeftButtonUp, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>))
IMP_ROUTEDEVENT(MouseRightButtonDown, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>))
IMP_ROUTEDEVENT(MouseRightButtonUp, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>))
IMP_ROUTEDEVENT(MouseMiddleButtonDown, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>))
IMP_ROUTEDEVENT(MouseMiddleButtonUp, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>))
IMP_ROUTEDEVENT(MouseLeftButtonDoubleClick, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>))
IMP_ROUTEDEVENT(MouseRightButtonDoubleClick, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>))
IMP_ROUTEDEVENT(MouseMiddleButtonDoubleClick, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>))
IMP_ROUTEDEVENT(MouseMove, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, MouseEventArgs*>))

/*
RoutedEvent* UIElement::MouseButtonUpEvent = EventManager::RegisterRoutedEvent("MouseButtonUp", RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::MouseLeftButtonDownEvent = EventManager::RegisterRoutedEvent("MouseLeftButtonDown", RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::MouseLeftButtonUpEvent = EventManager::RegisterRoutedEvent("MouseLeftButtonUp", RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::MouseRightButtonDownEvent = EventManager::RegisterRoutedEvent("MouseRightButtonDown", RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::MouseRightButtonUpEvent = EventManager::RegisterRoutedEvent("MouseRightButtonUp", RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::MouseMiddleButtonDownEvent = EventManager::RegisterRoutedEvent("MouseMiddleButtonDown", RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::MouseMiddleButtonUpEvent = EventManager::RegisterRoutedEvent("MouseMiddleButtonUp", RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>), typeid(UIElement));

RoutedEvent* UIElement::MouseLeftButtonDoubleClickEvent = EventManager::RegisterRoutedEvent("MouseLeftButtonDoubleClick", RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::MouseRightButtonDoubleClickEvent = EventManager::RegisterRoutedEvent("MouseRightButtonDoubleClick", RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::MouseMiddleButtonDoubleClickEvent = EventManager::RegisterRoutedEvent("MouseMiddleButtonDoubleClick", RoutingStrategy_Bubble, typeid(Event2<Object*, MouseButtonEventArgs*>), typeid(UIElement));

RoutedEvent* UIElement::MouseMoveEvent = EventManager::RegisterRoutedEvent("MouseMove", RoutingStrategy_Bubble, typeid(Event2<Object*,MouseEventArgs*>), typeid(UIElement));
*/
IMP_ROUTEDEVENT(Key, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, KeyEventArgs*>));
IMP_ROUTEDEVENT(TextComposition, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, TextCompositionEventArgs*>));

IMP_ROUTEDEVENT(DragEnter, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, DragEventArgs*>));
IMP_ROUTEDEVENT(DragLeave, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, DragEventArgs*>));
IMP_ROUTEDEVENT(DragOver, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, DragEventArgs*>));
IMP_ROUTEDEVENT(DragDrop, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, DragEventArgs*>));

IMP_ROUTEDEVENT(ContextMenuOpening, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, ContextMenuEventArgs*>));
IMP_ROUTEDEVENT(QueryCursor, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, QueryCursorEventArgs*>));

IMP_ROUTEDEVENT(Activate, UIElement, RoutingStrategy_Bubble, typeid(Event2<Object*, RoutedEventArgs*>));

DependencyClass* UIElement::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_WidthProperty(),
		get_HeightProperty(),

		get_MinWidthProperty(),
		get_MinHeightProperty(),

		get_MaxWidthProperty(),
		get_MaxHeightProperty(),

		get_ActualWidthProperty(),
		get_ActualHeightProperty(),

		get_AllowDropProperty(),
		get_IsMouseCapturedProperty(),
		get_HasFocusProperty(),
		get_IsFocusableProperty(),
		get_IsActiveProperty(),
		get_IsActivatableProperty(),
		get_IsEnabledProperty(),
		get_IsMouseOverProperty(),
		get_IsMouseDirectlyOverProperty(),
		get_IsStylusOverProperty(),
		get_IsStylusDirectlyOverProperty(),

		get_CursorProperty(),
		get_ShadowTreeProperty(),

		get_FirstChildProperty(),
		get_LastChildProperty(),

		get_BorderThicknessProperty(),
		get_PaddingProperty(),
		get_MarginProperty(),

		get_HorizontalAlignmentProperty(),
		get_HorizontalContentAlignmentProperty(),
	};

	static RoutedEvent* e[] =
	{
		get_MouseButtonDownEvent(),
		get_MouseButtonUpEvent(),

		get_MouseLeftButtonDownEvent(),
		get_MouseLeftButtonUpEvent(),
		get_MouseRightButtonDownEvent(),
		get_MouseRightButtonUpEvent(),
		get_MouseMiddleButtonDownEvent(),
		get_MouseMiddleButtonUpEvent(),
		get_MouseLeftButtonDoubleClickEvent(),
		get_MouseRightButtonDoubleClickEvent(),
		get_MouseMiddleButtonDoubleClickEvent(),
		get_MouseMoveEvent(),
		get_KeyEvent(),
		get_TextCompositionEvent(),

		get_DragEnterEvent(),
		get_DragLeaveEvent(),
		get_DragOverEvent(),
		get_DragDropEvent(),

		get_QueryCursorEvent(),
		get_ContextMenuOpeningEvent(),

		get_ActivateEvent(),
	};

	return &depclass;
}

template class GUIEXT Event2<Object*, MouseEventArgs*>;
template class GUIEXT Event2<Object*, MouseButtonEventArgs*>;
template class GUIEXT Event2<Object*, KeyEventArgs*>;
template class GUIEXT Event2<Object*, TextCompositionEventArgs*>;
template class GUIEXT Event2<Object*, DragEventArgs*>;
template class GUIEXT Event2<Object*, ContextMenuEventArgs*>;
template class GUIEXT Event2<Object*, QueryCursorEventArgs*>;
template class GUIEXT Event2<Object*, RoutedEventArgs*>;

/*
UIElement::Init::Init()
{
	EventManager::RegisterClassHandler(typeid(UIElement), MouseButtonDownEvent, mem_fun(&UIElement::OnMouseButtonDown));
	EventManager::RegisterClassHandler(typeid(UIElement), MouseButtonUpEvent, mem_fun(&UIElement::OnMouseButtonUp));

	EventManager::RegisterClassHandler(typeid(UIElement), MouseLeftButtonDownEvent, mem_fun(&UIElement::OnMouseLeftButtonDown));
	EventManager::RegisterClassHandler(typeid(UIElement), MouseLeftButtonUpEvent, mem_fun(&UIElement::OnMouseLeftButtonUp));
	EventManager::RegisterClassHandler(typeid(UIElement), MouseRightButtonDownEvent, mem_fun(&UIElement::OnMouseRightButtonDown));
	EventManager::RegisterClassHandler(typeid(UIElement), MouseRightButtonUpEvent, mem_fun(&UIElement::OnMouseRightButtonUp));
	EventManager::RegisterClassHandler(typeid(UIElement), MouseMiddleButtonDownEvent, mem_fun(&UIElement::OnMouseMiddleButtonDown));
	EventManager::RegisterClassHandler(typeid(UIElement), MouseMiddleButtonUpEvent, mem_fun(&UIElement::OnMouseMiddleButtonUp));
	EventManager::RegisterClassHandler(typeid(UIElement), MouseLeftButtonDoubleClickEvent, mem_fun(&UIElement::OnMouseLeftButtonDoubleClick));
	EventManager::RegisterClassHandler(typeid(UIElement), MouseRightButtonDoubleClickEvent, mem_fun(&UIElement::OnMouseRightButtonDoubleClick));
	EventManager::RegisterClassHandler(typeid(UIElement), MouseMiddleButtonDoubleClickEvent, mem_fun(&UIElement::OnMouseMiddleButtonDoubleClick));
	EventManager::RegisterClassHandler(typeid(UIElement), MouseMoveEvent, mem_fun(&UIElement::OnMouseMove));
	EventManager::RegisterClassHandler(typeid(UIElement), KeyEvent, mem_fun(&UIElement::OnKey));
	EventManager::RegisterClassHandler(typeid(UIElement), TextCompositionEvent, mem_fun(&UIElement::OnTextComposition));

	EventManager::RegisterClassHandler(typeid(UIElement), DragEnterEvent, mem_fun(&UIElement::OnDragEnter));
	EventManager::RegisterClassHandler(typeid(UIElement), DragLeaveEvent, mem_fun(&UIElement::OnDragLeave));
	EventManager::RegisterClassHandler(typeid(UIElement), DragOverEvent, mem_fun(&UIElement::OnDragOver));
	EventManager::RegisterClassHandler(typeid(UIElement), DragDropEvent, mem_fun(&UIElement::OnDragDrop));

	EventManager::RegisterClassHandler(typeid(UIElement), QueryCursorEvent, mem_fun(&UIElement::OnQueryCursor));
	EventManager::RegisterClassHandler(typeid(UIElement), ContextMenuOpeningEvent, mem_fun(&UIElement::OnContextMenuOpening));

	EventManager::RegisterClassHandler(typeid(UIElement), ActivateEvent, mem_fun(&UIElement::OnActivate));
}

UIElement::Init UIElement::init;
*/

UIElement::UIElement(DependencyClass* depClass) : Visual(depClass)
{
}

UIElement::UIElement(DependencyClass* depClass, gm::SizeF size) : Visual(depClass)
{
	set_Width(size.Width);
	set_Height(size.Height);
}

UIElement::~UIElement()
{
	if (m_elementProvider)
	{
		m_elementProvider->Release();
		m_elementProvider = nullptr;
	}
}

void UIElement::OnComputedPropertyValueChanging(PropertyValue* pPropertyVal, const Variant& oldValue, const Variant& newValue, bool handled)
{
	if (pPropertyVal->m_dp == get_ShadowTreeProperty())
	{
		// remove old

		UIElement* uielement = get_ShadowTree();

		if (uielement)
		{
			uielement->SetRoot(nullptr);
			uielement->set_Parent(nullptr);
			uielement->set_ParentWindow(nullptr);
		}

		handled = true;
	}

	if (m_elementProvider)
	{
		PROPERTYID propertyId = 0;
		if (pPropertyVal->m_dp == Window::get_TitleTextProperty())
		{
			propertyId = UIA_NamePropertyId;
		}

		HRESULT hr;
		if (propertyId)
		{
			hr = UiaRaiseAutomationPropertyChangedEvent(m_elementProvider, propertyId, oldValue, newValue);
		}
	}

	baseClass::OnComputedPropertyValueChanging(pPropertyVal, oldValue, newValue, handled);
}

void UIElement::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_CursorProperty())
	{
		IRootVisual* root = GetRoot();
		if (root)
		{
			root->ElementSetMouseCursor(this);
		}
	}
	else if (pPropertyVal->m_dp == get_ShadowTreeProperty())
	{
		if (!handled)
		{
			UIElement* shadowTree = get_ShadowTree();
			if (shadowTree)
			{
				shadowTree->SetRoot(GetRoot());
				shadowTree->set_ParentWindow(get_ParentWindow());

				shadowTree->set_Parent(this);
				shadowTree->set_TemplatedOwner(this);

				InvalidateMeasure();
			}
		}
	}
	else if (pPropertyVal->m_dp == get_ParentProperty())
	{
		UIElement* parent = get_Parent();
		if (parent)
		{
			SetTreeLevel(parent->get_TreeLevel()+1);

			parent->InvalidateArrange();
		}
		else
		{
			set_TreeLevel(0);
		}
	}
	else if (pPropertyVal->m_dp == get_ParentWindowProperty())
	{
		Window* parentwindow = get_ParentWindow();

		UIElement* shadowTree = get_ShadowTree();
		if (shadowTree)
		{
			shadowTree->set_ParentWindow(parentwindow);
		}

		size_t nchildren = GetChildrenCount();
		for (size_t i = 0; i < nchildren; ++i)
		{
			Visual* child = GetChild(i);
			ASSERT(child);

			child->set_ParentWindow(parentwindow);
		}
	}
	else if (pPropertyVal->m_dp == get_TemplatedOwnerProperty())
	{
		UIElement* owner = get_TemplatedOwner();

		size_t nchildren = GetChildrenCount();
		for (size_t i = 0; i < nchildren; ++i)
		{
			Visual* child = GetChild(i);
			ASSERT(child);

			child->set_TemplatedOwner(owner);
		}
	}
	else if (pPropertyVal->m_dp == get_WidthProperty())
	{
		InvalidateMeasure();
		/*
		float minWidth = get_MinWidth();
		float width = get_Width();

		if (width < minWidth) width = minWidth;

		set_ActualWidth(width);
		*/
	}
	else if (pPropertyVal->m_dp == get_HeightProperty())
	{
		InvalidateMeasure();
/*
		float minHeight = get_MinHeight();
		float height = get_Height();

		if (height < minHeight) height = minHeight;

		set_ActualHeight(height);
		*/
	}
	else if (pPropertyVal->m_dp == get_ActualWidthProperty() ||
			pPropertyVal->m_dp == get_ActualHeightProperty())
	{
#if 0
		m_visibleGeometryValid = false;

		get_Parent();

		m_measureValid = false;

		WindowVisual* w = dynamic_cast<WindowVisual*>(GetRoot());
		if (w)
		{
			w->AddArrange(this, get_TreeLevel());
		//	w->m_arrangeList.push_back(this);
		}

		/*

		// Not here
		for (size_t i = 0; i < GetChildrenCount(); ++i)
		{
			Visual* child = GetChild(i);
			child->DoLayoutSize();
		}
		*/
#endif
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

void UIElement::Focus()
{
	IRootVisual* root = GetRoot();
	if (root)
	{
		root->ElementSetFocus(this);
	}
}

Layout* UIElement::get_Layout()
{
	return nullptr;
}

void UIElement::set_Layout(Layout* layout)
{
	ASSERT(0);
}

void UIElement::Render(ManagedRenderContext renderContext)
{
	size_t nchildren = GetChildrenCount();
	for (size_t i = 0; i < nchildren; ++i)
	{
		Visual* child = GetChild(i);
		child->Render_(renderContext);
	}

	if (!m_visualValid)
	{
		m_visualValid = true;
		if (m_visuals)
		{
			if (m_visuals->get_Children())
			{
				m_visuals->get_Children()->m_items.clear();
			}

			RetainedRenderContext rrc(GetRoot(), m_visuals);
			ManagedRetainedRenderContext retainedRenderContext(&rrc);
			RenderRetained(retainedRenderContext);
		}
	}

	if (m_visuals)
	{
		m_visuals->Render_(renderContext);
	}

#if 0

	UIElement* shadowTree = get_ShadowTree();

	if (shadowTree == nullptr)
	{
		m_visuals = new GroupVisual;
		set_ShadowTree(m_visuals);

		shadowTree = m_visuals;
		m_visualValid = false;
	}

	if (!m_visualValid)
	{
		m_visualValid = true;
		if (m_visuals)
		{
			if (m_visuals->get_Children())
			{
				m_visuals->get_Children()->m_items.clear();
			}

			RetainedRenderContext rrc(GetRoot(), m_visuals);
			ManagedRetainedRenderContext retainedRenderContext(&rrc);
			RenderRetained(retainedRenderContext);
		}
	}

	shadowTree->Render_(renderContext);
#endif
}

void UIElement::RenderRetained(ManagedRetainedRenderContext renderContext)
{
}

size_t UIElement::GetChildrenCount()
{
	return get_ShadowTree()? 1: 0;
}

Visual* UIElement::GetChild(size_t index)
{
	if (index > 0 || get_ShadowTree() == nullptr)
	{
		raise(ArgumentOutOfRangeException());
	}

	return get_ShadowTree();
}

size_t UIElement::GetLogicalChildrenCount()
{
	return 0;
}

Object* UIElement::GetLogicalChild(size_t position)
{
	raise(ArgumentOutOfRangeException());
}

// This is logical child
Object* UIElement::ReplaceChild(size_t position, Object* newChild)
{
	raise(ArgumentOutOfRangeException());
	return nullptr;

	/*
	VisualCollection* visuals = get_Children();
	Visual* oldChild = visuals->m_items[position];
	oldChild->set_Parent(NULL);
	oldChild->set_ChildPosition(-1);

	visuals->m_items[position] = newChild;
	newChild->set_Parent(this);
	newChild->set_ChildPosition(position);
	*/

}

/*
void UIElement::AddHandler(RoutedEvent* routedEvent, EventHandler handler)
{
	//get_RoutedEvent(routedEvent)->Connect(handler);
}

void UIElement::RemoveHandler(RoutedEvent* routedEvent, EventHandler handler)
{
	//get_RoutedEvent(routedEvent)->Disconnect(handler);
}
*/

/*
Event2<Object*,MouseButtonEventArgs*>& UIElement::get_LeftMouseButtonDownEvent()
{
	return *(Event2<Object*,MouseButtonEventArgs*>*)get_RoutedEvent(LeftMouseButtonDownEvent);
}

Event2<Object*,MouseButtonEventArgs*>& UIElement::get_LeftMouseButtonUpEvent()
{
	return *(Event2<Object*,MouseButtonEventArgs*>*)get_RoutedEvent(LeftMouseButtonUpEvent);
}

Event2<Object*,MouseEventArgs*>& UIElement::get_MouseMoveEvent()
{
	return *(Event2<Object*,MouseEventArgs*>*)get_RoutedEvent(MouseMoveEvent);
}
*/

/**

file://D:\Users\Sigurd\Documents\VSProjects\FirstProject2\src\GUI\FindCommonAncestor.png

*/

UIElement* UIElement::FindCommonAncestor(UIElement* element1)
{
	UIElement* element0 = this;

	// mark phase
	for (UIElement* p = element0; p != nullptr; p = p->get_Parent())
	{
		EnterCriticalSection(p->m_markedSection);
		p->m_marked = true;
	}

	UIElement* commonAncestor = nullptr;

	for (UIElement* p = element1; p != nullptr; p = p->get_Parent())
	{
		if (p->m_marked)
		{
			commonAncestor = p;
			break;
		}
	}

	// unmark
	for (UIElement* p = element0; p != nullptr; p = p->get_Parent())
	{
		p->m_marked = false;
		LeaveCriticalSection(p->m_markedSection);
	}

	return commonAncestor;
}

Event* UIElement::get_RoutedEvent(RoutedEvent* routedEvent)
{
	if (m_events[routedEvent->GetIndex()] == nullptr)
	{
		m_events[routedEvent->GetIndex()] = dynamic_cast<Event*>(newobj(routedEvent->get_HandlerType()));
		ASSERT(m_events[routedEvent->GetIndex()]);
	}

	return m_events[routedEvent->GetIndex()];
}

#if 0
void UIElement::AddHandler(RoutedEvent* routedEvent, stub_interface_base* handler)
{
	if (handler->GetType()->IsDerivedFrom(routedEvent->get_HandlerType()->GetClass()))
	{
		throw new Exception(WSTR("Handler of wrong type"));
	}

	int index = routedEvent->GetIndex();

	if (m_handlers[index] == NULL)
	{
		VERIFY(routedEvent->get_HandlerType()->GetClass());
		ClassType* pSigType = dynamic_cast<ClassType*>(routedEvent->get_HandlerType()->GetClass()->LookupType(ASTR("signal_type"))->GetStripped());
		m_handlers[index] = (signal_base*)newobj(pSigType);
	}

	m_handlers[index]->connect(handler);
}
#endif

//////////////////////

class EventRoute : public Object
{
public:
	// TODO
	list<UIElement*> ancestors;
};

UIElement* UIElement::HitTest(gm::PointF point)
{
	int nchildren = (int)GetChildrenCount();
	for (int i = nchildren-1; i >= 0; --i)
	{
		Visual* child = GetChild(i);
		ASSERT(child);

		UIElement* hitElement = child->HitTest_(point);
		if (hitElement != nullptr)
		{
			return hitElement;
		}
	}

	/*
	//  TODO remove, done above?
	UIElement* shadowTree = get_ShadowTree();
	if (shadowTree)
	{
		UIElement* hitElement = shadowTree->HitTest_(point);
		if (hitElement)
		{
			return hitElement;
		}
	}
	*/

	geometry hitGeometry = GetHitGeometry();
//	geometry hitGeometry = get_VisibleGeometry();
//	if (hitGeometry != nullptr)
	{
		if (hitGeometry.FillContains(point))
		{
			return this;
		}
	}

	return nullptr;
}

void UIElement::OnAddChild(VisualCollection* collection, Visual* element)
{
	ASSERT(element);

	element->SetRoot(GetRoot());
	element->set_Parent(this);
}

geometry UIElement::GetHitGeometry()
{
	return geometry(gm::RectF(0, 0, get_ActualWidth(), get_ActualHeight()));
}

geometry UIElement::MakeVisibleGeometry(geometry clip)
{
	m_visibleGeometryValid = true;

	//gm::RectF bounds = clip.GetBounds();

	geometry clipThis = get_Clip();
	if (clipThis != nullptr)
	{
		clip &= clipThis;
	}

#ifdef _DEBUG
	gm::RectF bounds = clip.GetBounds();
#endif

	geometry geom = GetHitGeometry();
#ifdef _DEBUG
	gm::RectF bounds2 = geom.GetBounds();
#endif

	clip &= geom;

#ifdef _DEBUG
	gm::RectF bounds3 = clip.GetBounds();
#endif

	size_t nchildren = GetChildrenCount();
	for (size_t i = nchildren; i > 0; --i)
	{
		Visual* child = GetChild(i-1);

		geometry geom2 = child->MakeVisibleGeometry(clip);

		clip |= geom2;
	}

	UIElement* shadowTree = get_ShadowTree();
	if (shadowTree)
	{
		geometry geom2 = shadowTree->MakeVisibleGeometry(clip);

#ifdef _DEBUG
	gm::RectF bounds5 = geom2.GetBounds();
#endif

		clip |= geom2;
	}

#ifdef _DEBUG
	gm::RectF bounds4 = clip.GetBounds();
#endif

	set_VisibleGeometry(clip);

	return clip;
}

void UIElement::RaiseEvent(RoutedEventArgs* args)
{
	args->m_originalSource = this;

	RoutedEvent* routedEvent = args->get_RoutedEvent();
	if (routedEvent == NULL)
	{
		raise(SystemException("routedEvent = NULL"));
	}

	// preview phase
	if (routedEvent->get_RoutingStrategy() == RoutingStrategy_Tunnel)
	{
#if 0
		EventRoute route;

		UIElement* p = this;//dynamic_cast<UIElement*>(GetRParent());
		while (p)
		{
			route.ancestors.push_front(p);
			p = dynamic_cast<UIElement*>(p->GetRParent());
		}

		list<UIElement*>::iterator it = route.ancestors.begin();
		while (it != route.ancestors.end())
		{
			UIElement* el = *it;

			// Class handlers
			if (!args->get_Handled())	// TODO
			{
				EventManager::InvokeClassHandlers(el/*args->get_Source()*/->GetType(), el, args);
			}

			// Instance handlers
			signal_base* sig = el->m_handlers[routedEvent->m_index];

			if (sig)
			{
				int nslots = sig->GetSlotCount();

			//	signal2<Object*,RoutedEventArgs*>::connection_type it2 = el->m_handlers[routedEvent->m_index]->m_slots.begin();
			//	while (it2 != el->m_handlers[routedEvent->m_index]->m_slots.end())
				for (int i = 0; i < nslots; i++)
				{
					stub_interface_base* slot = sig->GetSlot(i);

					if (!args->get_Handled())	// TODO
					{
						args->InvokeEventHandler(this, slot);
					}
				//	++it2;
				}
			}

			++it;
		}
#endif
	}
	else if (routedEvent->get_RoutingStrategy() == RoutingStrategy_Bubble)
	{
		EventRoute route;

		UIElement* p = this;
		do
		{
			route.ancestors.push_back(p);
			p = p->get_Parent();
		}
		while (p);

		if (args->get_Source() == nullptr)
		{
			args->set_Source(this);
		}

		for (auto it = route.ancestors.begin(); it != route.ancestors.end(); ++it)
		{
			UIElement* el = *it;

			// Class handlers
			if (!args->get_Handled())	// TODO
			{
				EventManager::InvokeClassHandlers(el->GetType(), el, args);
			}

			// Instance handlers

			Event* pEvent = el->m_events[routedEvent->GetIndex()];

			if (pEvent)
			{
				try
				{
					switch (pEvent->get_NumArgs())
					{
					case 2:
						{
							pEvent->Handle(el, args);
						}
						break;

					default:
						ASSERT(0);
					}
				}
				catch (Exception* e)
				{
					MessageBox(nullptr, e->get_Reason().c_strw(), L"GUI", MB_OK | MB_ICONERROR);
				}
			}

			args->set_Source(el);

#if 0
				list<IDispatch*>::iterator it = pEvent->m_handlers.begin();

				while (it != pEvent->m_handlers.end())
				{
					IDispatch* handler = *it;
					++it;

					if (!args->get_Handled())	// TODO
					{
						args->InvokeEventHandler(this, handler);
					}
				}

				/*
				int nslots = el->m_handlers[routedEvent->m_index]->GetSlotCount();

				signal2<Object*,RoutedEventArgs*>::connection_type it2 = el->m_handlers[routedEvent->m_index].m_slots.begin();
				while (it2 != el->m_handlers[routedEvent->m_index].m_slots.end())
				{
					args->InvokeEventHandler(this, *it2);
					++it2;
				}
				*/
			}
#endif
		}
	}
	else if (routedEvent->get_RoutingStrategy() == RoutingStrategy_Direct)
	{
		VERIFY(0);
	}
}

void UIElement::OnSetRoot(IRootVisual* root)
{
	UIElement* shadowTree = get_ShadowTree();
	if (shadowTree)
	{
		shadowTree->SetRoot(root);
	}

	size_t nchildren = GetChildrenCount();
	for (size_t i = 0; i < nchildren; ++i)
	{
		Visual* child = GetChild(i);
		ASSERT(child);

		child->SetRoot(root);
	}
}

Style::IStyleDeclaration* Element::get_inlineStyle(uint index)
{
	return NULL;
}

void UIElement::SetCaptureMouse(bool b)
{
	SetPropertyValue(get_IsMouseCapturedProperty(), b);
}

bool UIElement::CaptureMouse()
{
	IRootVisual* root = GetRoot();
	if (root)
	{
		bool b = root->ElementCaptureMouse(this);
		return b;
	}
	else
		return false;
}

void UIElement::ReleaseMouseCapture()
{
	IRootVisual* root = GetRoot();
	if (root)
	{
		root->ElementReleaseMouseCapture(this);
	}
}

void UIElement::OnQueryCursor(QueryCursorEventArgs* args)
{
	args->set_Cursor(get_Cursor());
}

void UIElement::Measure(gm::SizeF availSize)
{
	if (!m_inMeasure)
	{
		m_inMeasure = true;

		if (!m_measureValid || m_availSize != availSize)
		{
			m_availSize = availSize;

			MeasureCore(availSize);
		}

		m_inMeasure = false;
	}
}

void UIElement::MeasureCore(gm::SizeF availSize)
{

	/*
	if (GetPropertyValue(get_WidthProperty()).IsUndefined())
	{
		get_Width();
			
	}
	*/

	m_measureValid = true;
	gm::SizeF desiredSize = MeasureOverride(availSize);

	if (desiredSize.Width == std::numeric_limits<float>::infinity())
	{
		raise(Exception("Measure returned desiredSize.Width=positive_infinity"));
	}

	if (	m_desiredSize != desiredSize)
	{
		m_desiredSize = desiredSize;

		UIElement* parent = get_Parent();
		if (parent)
		{
			parent->OnChildDesiredSizeChanged(this);
		}
	}
}

gm::SizeF UIElement::MeasureOverride(gm::SizeF availSize)
{
	gm::SizeF desiredSize;

	size_t nchildren = GetChildrenCount();
	for (size_t i = 0; i < nchildren; ++i)
	{
		UIElement* child = dynamic_cast<UIElement*>(GetChild(i));
		child->Measure(availSize);
		desiredSize = child->m_desiredSize;
	}

	/*
	UIElement* shadowTree = get_ShadowTree();
	if (shadowTree)
	{
		shadowTree->MeasureCore(availSize);
		return shadowTree->m_desiredSize;
	}
	*/

	return desiredSize;
}

void UIElement::Arrange(gm::RectF finalRect)
{
	if (!m_inArrange)
	{
		m_inArrange = true;

		if (!m_arrangeValid)
		{
			m_arrangeValid = true;

			ArrangeCore(finalRect);
		}

		m_inArrange = false;
	}
}

void UIElement::ArrangeCore(gm::RectF finalRect)
{
	Variant width = GetProperty(get_WidthProperty())->GetLocalValue();
	Variant height = GetProperty(get_HeightProperty())->GetLocalValue();

	if (!width.IsUndefined()) finalRect.Width = width;
	if (!height.IsUndefined()) finalRect.Height = height;

	gm::SizeF finalSize = ArrangeOverride(finalRect.GetSize());

	m_visualOffset.X = finalRect.X;
	m_visualOffset.Y = finalRect.Y;

	set_ActualWidth(finalSize.Width);
	set_ActualHeight(finalSize.Height);
}

gm::SizeF UIElement::ArrangeOverride(gm::SizeF size)
{
//	LayoutChildren();

	gm::SizeF finalSize;

	size_t nchildren = GetChildrenCount();
	for (size_t i = 0; i < nchildren; ++i)
	{
		UIElement* child = dynamic_cast<UIElement*>(GetChild(i));

		child->Arrange(gm::RectF(gm::PointF(0,0),size));
		finalSize = child->get_ActualSize();
	}

	/*
	UIElement* shadowTree = get_ShadowTree();
	if (shadowTree)
	{
		shadowTree->ArrangeCore(size);
		return shadowTree->get_ActualSize();
	}
	*/

	return finalSize;
}

void UIElement::OnChildDesiredSizeChanged(UIElement* child)
{
	InvalidateMeasure();
	InvalidateArrange();
}

UIElement::ElementProviderFragment* UIElement::GetElementProvider()
{
	if (m_elementProvider == nullptr)
	{
		m_elementProvider = new ElementProviderFragment(this);
		m_elementProvider->AddRef();
	}

	return m_elementProvider;
}

HRESULT STDMETHODCALLTYPE UIElement::ElementProviderFragment::QueryInterface(REFIID riid, void **ppvObject)
{
	if (riid == __uuidof(IUnknown))								*ppvObject = static_cast<IRawElementProviderSimple*>(this);
	else if (riid == __uuidof(IRawElementProviderSimple))		*ppvObject = static_cast<IRawElementProviderSimple*>(this);
	else if (riid == __uuidof(IRawElementProviderFragment))		*ppvObject = static_cast<IRawElementProviderFragment*>(this);
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	AddRef();
	return S_OK;
}

HRESULT UIElement::ElementProviderFragment::get_ProviderOptions(ProviderOptions *pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	if (pRetVal == nullptr) return E_POINTER;

	*pRetVal = ProviderOptions_ServerSideProvider | ProviderOptions_UseComThreading;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE UIElement::ElementProviderFragment::GetPatternProvider( 
/* [in] */ PATTERNID patternId,
/* [retval][out] */ __RPC__deref_out_opt IUnknown **pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	if (pRetVal == nullptr) return E_POINTER;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE UIElement::ElementProviderFragment::GetPropertyValue(PROPERTYID propertyId, VARIANT* pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	if (pRetVal == nullptr) return E_POINTER;

	pRetVal->vt = VT_EMPTY;

	switch (propertyId)
	{
	case UIA_NamePropertyId:
		pRetVal->vt = VT_BSTR;
		pRetVal->bstrVal = SysAllocString(m_owner->get_ID().c_strw());
		break;

	case UIA_IsEnabledPropertyId:
		pRetVal->vt = VT_BOOL;
		pRetVal->boolVal = m_owner->get_IsEnabled()? VARIANT_TRUE: VARIANT_FALSE;
		break;

		/*
	default:
		pRetVal->vt = VT_UNKNOWN;
		return UiaGetReservedNotSupportedValue(&pRetVal->punkVal);
		*/
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE UIElement::ElementProviderFragment::get_HostRawElementProvider(IRawElementProviderSimple** pRetVal)
{
	if (m_owner == NULL) return UIA_E_ELEMENTNOTAVAILABLE;
//	return UiaHostProviderFromHwnd(m_owner->get_Handle(), pRetVal);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE UIElement::ElementProviderFragment::Navigate(NavigateDirection direction, IRawElementProviderFragment **pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	if (pRetVal == nullptr) return E_POINTER;

	UIElement* other;

	switch (direction)
	{
	case NavigateDirection_Parent:
		{
			other = m_owner->get_Parent();
		}
		break;

	case NavigateDirection_NextSibling:
		{
			other = dynamic_cast<UIElement*>(m_owner->get_NextSibling());
		}
		break;

	case NavigateDirection_PreviousSibling:
		{
			other = dynamic_cast<UIElement*>(m_owner->get_PreviousSibling());
		}
		break;

	case NavigateDirection_FirstChild:
		{
			other = dynamic_cast<UIElement*>(m_owner->get_FirstChild());
		}
		break;

	default:
		return E_INVALIDARG;
	}

	if (other)
	{
		*pRetVal = other->GetElementProvider();
		if (*pRetVal) (*pRetVal)->AddRef();
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE UIElement::ElementProviderFragment::GetRuntimeId(SAFEARRAY **pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE UIElement::ElementProviderFragment::get_BoundingRectangle(UiaRect* pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;

	gm::BBoxf bounds = m_owner->m_bounds;

	pRetVal->left = bounds.left;
	pRetVal->top = bounds.top;
	pRetVal->width = bounds.GetWidth();
	pRetVal->height = bounds.GetHeight();

	return S_OK;
}

HRESULT STDMETHODCALLTYPE UIElement::ElementProviderFragment::GetEmbeddedFragmentRoots(SAFEARRAY * *pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE UIElement::ElementProviderFragment::SetFocus()
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE UIElement::ElementProviderFragment::get_FragmentRoot(IRawElementProviderFragmentRoot **pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;

	Window* root = dynamic_cast<Window*>(m_owner->GetRoot());
	ASSERT(root);

	*pRetVal = root->GetElementProviderRoot();
	(*pRetVal)->AddRef();

	return S_OK;
}

}	// Gui
}	// System
