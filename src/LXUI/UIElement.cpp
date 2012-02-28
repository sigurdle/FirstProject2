#include "stdafx.h"
#include "LXUI2.h"
#include "UIElement.h"
#include "SolidColorBrush.h"
#include "AnimationClock.h"

//#include "MenuItem.h"	// TODO remove

#include <cstdlib>
#include <functional>

#include <windows.h>
#undef GetObject

#include <d3d9.h>
#include <d3dx9.h>

#if AMIGA
#include "../amiga_header.h"
#endif

namespace System
{

#if 0

template<class T, class arg1_type, class arg2_type> class mem_fn_t
{
	mem_fn_t(void (T::*pm)(arg1_type)) : m_pm(pm)
	{
	}

	void operator () (T* p, arg1_type arg1)
	{
		(p->*m_pm)(arg1, arg2);
	}

	void (T::*m_pm)(arg1_type);
};

template<class T, class arg1_type, class arg2_type> mem_fn_t<T, arg1_type, arg2_type> mem_fn(void (T::*pm)(arg1_type, arg2_type))
{
	return mem_fn_t<T, arg1_type, arg2_type>(pm);
}
#endif

#if 0
template<class F, class arg1_type, class arg2_type> class binder1st
{
public:
	binder1st(const F& op, arg1_type arg1) : m_op(op) : m_arg1(arg1)
	{
	}

	void operator () (arg2_type arg2)
	{
		m_op(arg1, arg2);
	}

	F m_op;
	arg1_type m_arg1;
};

template<class arg1_type, class arg2_type> binder1st<arg1_type, arg2_type> bind(arg1_type arg1, arg2_type arg2)
{
	return binder1st<arg1_type, arg2_type>(arg1, arg2);
}
#endif

namespace UI
{

extern __live_object_ptr<TimeManager> g_timeManager;

extern double pixelsPerInch;

using namespace Media;

//

void InvalidateRenderChildren(Visual* visual);

FontFamily::FontFamily(StringW* familyName)
{
	m_fontFamily = new LDraw::FontFamily(familyName);
}

FontFamily::FontFamily(LDraw::FontFamily* family) : m_fontFamily(family)
{
}

FontFamily::~FontFamily()
{
}

LDraw::FontFamily* FontFamily::GetFamily()
{
	/*
	if (m_fontFamily == LDraw::FontFamily())
	{
		m_fontFamily = LDraw::FontFamily(WSTR("Courier New"));
//		m_fontFamily = new LDraw::FontFamily(WSTR("Verdana"));
//		m_fontFamily = new LDraw::FontFamily(WSTR("Times New Roman"));
	}
	*/

	return m_fontFamily;
}

////////////////////////////////////////////////////////////////////////////
// CPLXUIElementImpl

#if 0
// virtual
void CLXUIElementImpl::BuildChildren()
{
	ASSERT(0);
#if 0
	m_rchildList.RemoveAll();	// ???
#endif
	ASSERT(0);
#if 0
	CLXUINodeImpl* child = get_firstChild(&child);

	while (child != NULL)
	{
		short nodeType;
		child->get_nodeType(&nodeType);

		//CComQIPtr<ILViewNode, &IID_ILViewNode> v((IUnknown*)child);
		//if (v)
		{
			CPNode* pNode = dynamic_cast<CPNode*>(child);

			if (pNode->m_type == LNODE_ELEMENT)
			{
				CLDependencyObject* pElement = static_cast<CLDependencyObject*>(pNode);
				pElement->BuildChildren();
			}

			pNode->m_parent = this;
			m_childList.AddTail(pNode);
		}

		child = child->get_nextSibling();
	}
#endif
}
#endif

#if 0
// Global function.. ???
void /*CHTMLWindow::*/RemovingElement(CPNode* pPElement)
{
	pPElement->RemovedFromDocument();

	/*
	if (pPElement == m_pPElementHover)
	{
		m_pPElementHover = NULL;
	}
	*/
	if (pPElement->m_type == 1/*LNODE_ELEMENT*/)
	{
		UPOSITION pos = ((CLDependencyObject*)pPElement)->m_rchildList.GetHeadPosition();
		while (pos)
		{
			CPNode* p = (CPNode*)((CLDependencyObject*)pPElement)->m_rchildList.GetNext(pos);

			RemovingElement(p);
		}
	}
}
#endif

#if 0
void CPLXUIElementImpl::OnRemoving()
{
	CPElement* pParentElement = m_parent;//(CPElement*)CComQIPtr<CLDOMNodeImplImpl>(parentNode)->GetNodeOnFrame(m_pView);

	//if (pParentElement)
	{
#if 0
		CPNode* pPElement = NULL;

		/*
		for (int i = 0; i < CComQIPtr<CLDOMNodeImplImpl>(targetNode)->m_pNodes.GetSize(); i++)
		{
			if (CComQIPtr<CLDOMNodeImplImpl>(targetNode)->m_pNodes[i]->m_pView == this)
			{
				pPElement = (CPElement*)CComQIPtr<CLDOMNodeImplImpl>(targetNode)->m_pNodes[i];
				break;
			}
		}
		*/
		pPElement = (CPNode*)CComQIPtr<CLDOMNodeImplImpl>(targetNode)->GetNodeOnFrame(m_pView);
#endif

		if (CComQIPtr<ILDOMElement>(pPElement->m_pNode))
		{
			if (CComQIPtr<ILSVGElement>(pPElement->m_pNode) != NULL)	// TODO remove
			{
#if 0
				gmMatrix3 ctm = ((CPSVGElementImpl*)pPElement)->GetScreenCTM();

				RectD xrect;
				GetTransformRectBoundingBox(ctm.inverse(), ((CPSVGElementImpl*)pPElement)->m_expandedBBox, &xrect);

				CRect rect((int)xrect.X, (int)xrect.Y, (int)ceil(xrect.GetRight()), (int)ceil(xrect.GetBottom()));
				m_pWindow->InvalidateRect(&rect);
#endif
			}

#if 0
			m_pWindow->RemovingElement(pPElement);
#endif
		}

		UPOSITION pos;

		pos = pParentElement->m_childList.Find(pPElement);
		pParentElement->m_childList.RemoveAt(pos);

		if (CComQIPtr<ILSVGElement>(pParentElement->m_pNode) != NULL)
		{
			pos = ((CPSVGElementImpl*)pParentElement)->m_childListRender.Find(pPElement);
			if (pos)
			{
				((CPSVGElementImpl*)pParentElement)->m_childListRender.RemoveAt(pos);
			}
		}

		//CComQIPtr<CLDOMNodeImplImpl>(targetNode)->RemovePNode(pPElement);
		/*m_pView->*/RemovingElement(pPElement);
		pPElement->Release();

		pParentElement->BuildRenderChildren();
		pParentElement->RecalculateParentBounds();
	}
}
#endif

#if 0
void CLXUIElementImpl::OnInsertedChild(CLXUINodeImpl* node)
{
	MessageBeep(~0);
#if 0
	short nodeType;
	node->get_nodeType(&nodeType);

	//CComQIPtr<ILDOMElement> element(node);
	//if (element)
	if (nodeType == LNODE_ELEMENT)
	{
	//	CPElement* pParentElement = this;//(CPElement*)CComQIPtr<CLDOMNodeImplImpl>(parentNode)->GetNodeOnFrame(m_pView);

		//if (pParentElement)
		{
			CLDependencyObject* pPElement;

			if (FALSE)
			{
#if 0
				// First check if a view element of this view exists on the element
				pPElement = (CPElement*)CComQIPtr<CLDOMNodeImplImpl>(node)->CheckNodeOnFrame(m_pView);

				if (pPElement == NULL)	// It doesn't, create new
				{
					pPElement = m_pView->CreateElement(node);
					CComQIPtr<CLDOMNodeImplImpl>(node)->m_pNodes.Add(pPElement);
				}
#endif
			}
			else
			{
			//	CComQIPtr<ILViewNode, &IID_ILViewNode> v = (IUnknown*)node;
			//	ASSERT(v);

				pPElement = dynamic_cast<CLDependencyObject*>(node);
				pPElement->m_pView = m_pView;
			//	pPElement->m_pNode = node;
			//	pPElement->m_eventTarget = CComQIPtr<ILDOMEventTarget>(node);
			}

			pPElement->m_parent = this;
			pPElement->BuildChildren();

			UPOSITION pos = m_childList.GetHeadPosition();

			<ILXUINode> child;
			<ILXUIElement, &IID_ILXUIElement>((ILViewNode*)this)->/*m_pNode->*/get_firstChild(&child);

			while (child)
			{
				if (child == node)
					break;

				if (pos)
				{
					UPOSITION pos2 = pos;
					CPNode* pChild = (CPNode*)m_childList.GetNext(pos2);
					//ASSERT(pChild/*->m_pNode*/ != node);
					if (CComQIPtr<ILXUINode, &IID_ILXUINode>((IUnknown*)pChild) == child)
					{
						pos = pos2;	// Okay, advance pos
					}
				}

				CComPtr<ILXUINode> nextSibling;
				child->get_nextSibling(&nextSibling);
				child = nextSibling;
			}

			if (pos)
				m_childList.InsertBefore(pos, pPElement);
			else
				m_childList.AddTail(pPElement);

			/*pPElement->*/GetCSSPropertiesAndChildren();

			BuildRenderChildren();

			//pPEleemnt->BuildRenderChildren();
			pPElement->SetValuesFromAttributes();	// ??
			CalcDims(pPElement);

			// ??

			pPElement->InsertedIntoDocument();

#if 0	// TODO had this, but ????
			pPElement->OnMeasure(viewBox);
#endif
			pPElement->m_parent->RecalculateParentBounds();

#if 0
			if (CComQIPtr<ILXUIElement>(pPElement->m_pNode))
			{
				((CPLXUIElementImpl*)pPElement)->ShowAndChildren();
			}
#endif
		}
	}
	else
	{
	//	ASSERT(0);
#if 0
		CPElement* pParentElement = (CPElement*)CComQIPtr<CLDOMNodeImplImpl>(parentNode)->GetNodeOnFrame(m_pView);

//		pPElement->SetValuesFromAttributes();
//		CalcDims(pPElement);

		if (pParentElement)
		{
			//pParentNode->RemoveBoxes();
			pParentElement->RemoveChildren();
			pParentElement->BuildChildren();

			pParentElement->GetCSSPropertiesAndChildren();

			pParentElement->BuildRenderChildren();

			pParentElement->SetValuesFromAttributes();	// ??
			/*m_pWindow->*/CalcDims(pParentElement);
		}
#endif
	}
#endif
}
#endif

#if 0
// virtual
HRESULT CPLXUIElementImpl::OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID)
{
	ASSERT(0);
	if (type == (NotifyType)-1)	// Hack
	{
		// ????
		CComQIPtr<ILDOMElement> element = targetObject;
		if (element)
		{
			CPElement* pPElement = (CPElement*)CComQIPtr<CLDOMNodeImplImpl>(element)->CheckNodeOnFrame(m_pView);

			if (pPElement)
			{
				// Attribute
				pPElement->GetCSSPropertiesAndChildren();
				pPElement->BuildRenderChildren();
				pPElement->SetValuesFromAttributes();	// ??
				CalcDims(pPElement);
			}
		}

		return S_OK;
	}

	CComQIPtr<ILDOMNode> targetNode = targetObject;
	if (targetNode)
	{
		LDOMNodeType nodeType;
		targetNode->get_nodeType(&nodeType);

		if ((nodeType == LNODE_TEXT/* || nodeType == LNODE_CDATA_SECTION*/) &&
			(type == NOTIFY_MODIFY))
		{
			CComQIPtr<ILDOMCharacterData> charData = targetNode;

			CPTextNode* pText = (CPTextNode*)CComQIPtr<CLDOMNodeImplImpl>(charData)->GetNodeOnFrame(m_pView);
			if (pText)
			{
				pText->OnTextContentChanged();

				{
					HDC hDC = CreateCompatibleDC(NULL);
					{
						Gdiplus::Graphics graphics(hDC);

						CHTMCalcContext pC;
						//pC.m_pUI = m_pWindow->m_pUI;
						pC.m_pGraphics = &graphics;

						pC.m_pStringFormat = Gdiplus::StringFormat::GenericTypographic();

						graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintSystemDefault/*TextRenderingHintAntiAliasGridFit*//*TextRenderingHintAntiAlias*/);	// ??

						pText->CalculateDimensions(&pC);
					}
					DeleteDC(hDC);
				}

			// TODO, have common code for both svg and css box model
				if (TRUE)//m_pWindow->m_pSVGElement == NULL)
				{
					CPElement* pParent = pText->m_parent;

					pParent->RemoveBoxes();

					while (pParent)
					{
						if (pParent->m_computedDisplayRole == DisplayRole_table_cell)
						{
							pParent->CalculateMinMaxDimensions();
						}

						pParent = pParent->m_parent;
					}
				}
#if 0
				else
				{
					CPElement* pParent = pText->m_parent;

					while (pParent)
					{
						CComQIPtr<ILSVGTextElement> textElement = pParent->m_pNode;
						if (textElement)
						{
							CPSVGTextElement* pSVGTextElement = (CPSVGTextElement*)pParent;
							pSVGTextElement->CalculateBounds();

							pSVGTextElement->m_parent->RecalculateParentBounds();

							break;
						}

						pParent = pParent->m_parent;
					}
				}
#endif
				pText->m_parent->CalculateBoundsAndChildren();
				pText->m_parent->RecalculateParentBounds();
			}
		}
		else
		{
			CComPtr<ILDOMNode> parentNode;
			targetNode->get_parentNode(&parentNode);

			CComQIPtr<ILDOMElement> element = targetNode;

			if (element && type == NOTIFY_ADD)
			{
				OnInsertedChild();

			}
			else if (type == NOTIFY_REMOVE)
			{
				OnRemovingChild(pNode);
			}
			else
			{
// TODO, improve this a lot, inserting a text node currently triggers this one

					
					CComQIPtr<ILDOMDocument> document = parentNode;
					if (document)
					{
						/*
						if (type == NOTIFY_REMOVE)
						{
							m_htmTree->Release();
							m_htmTree = NULL;
							m_pSVGElement = NULL;

							m_element = NULL;
						}
						else
						{
						}
						*/
					}
					else
					{

#if 0
						CPNode* pPNode = (CPNode*)CComQIPtr<CLDOMNodeImplImpl>(targetNode)->GetNodeOnFrame(this);
						if (type == NOTIFY_REMOVE)
						{
							ASSERT(0);
							/*
							CPElement* pParentElement = (CPElement*)CComQIPtr<CLDOMNodeImplImpl>(parentNode)->GetNodeOnFrame(this);

							ASSERT(pParentElement);

							pPNode->RemovedFromDocument();//	m_pWindow->RemovingElement(pPElement);
								//pPElement->Release();
								*/
						}
						else
#endif
						{
					//		CPElement* pPElement = (CPElement*)CComQIPtr<CLDOMNodeImplImpl>(element)->GetNodeOnFrame(this);
							CPElement* pParentElement = (CPElement*)CComQIPtr<CLDOMNodeImplImpl>(parentNode)->GetNodeOnFrame(m_pView);

					//		pPElement->SetValuesFromAttributes();
					//		CalcDims(pPElement);

							if (pParentElement)
							{
								//pParentNode->RemoveBoxes();
								pParentElement->RemoveChildren();
								pParentElement->BuildChildren();

								pParentElement->GetCSSPropertiesAndChildren();

								pParentElement->BuildRenderChildren();

								pParentElement->SetValuesFromAttributes();	// ??
								/*m_pWindow->*/CalcDims(pParentElement);
							}
						}
					}
	//#endif
			}
		}
	}

	return S_OK;
}
#endif

/*
unsigned int VisualNodes::GetCount()
{
	return get_Size();
}

const Type_Info& VisualNodes::GetItemType() const
{
	return typeid(Visual);
}

unsigned int VisualNodes::get_Size() const
{
	return m_items.GetSize();
}

Visual* VisualNodes::Item(unsigned int index) const
{
	return m_items[index];
}

Object* VisualNodes::GetItem(unsigned int index)
{
	return Item(index);
}

//

unsigned int UIElementCollection::GetCount()
{
	return get_Size();
}

const Type_Info& UIElementCollection::GetItemType() const
{
	return typeid(UIElement);
}

unsigned int UIElementCollection::get_Size() const
{
	return m_items.GetSize();
}

UIElement* UIElementCollection::Item(unsigned int index) const
{
	return m_items[index];
}

Object* UIElementCollection::GetItem(unsigned int index)
{
	return Item(index);
}
*/

extern DepState* depstate;

/////////////////////////////////////////////////////////////
// UIElement

DependencyProperty* UIElement::s_AllowDropProperty = RegisterProperty(WSTR("AllowDrop"), typeid(bool), typeid(UIElement), BoolObject::get_False(), PropertyMetaData(None));
DependencyProperty* UIElement::s_VisibilityProperty = RegisterProperty(WSTR("Visibility"), typeid(VisibilityState), typeid(UIElement), IntObject::GetObject(Visible), PropertyMetaData(AffectsMeasure));
DependencyProperty* UIElement::s_OpacityProperty = RegisterProperty(WSTR("Opacity"), typeid(double), typeid(UIElement), DoubleObject::GetObject(1.0), PropertyMetaData(AffectsRender));
DependencyProperty* UIElement::s_OpacityMaskProperty = RegisterProperty(WSTR("OpacityMask"), typeid(Brush), typeid(UIElement), NULL, PropertyMetaData(AffectsRender));
DependencyProperty* UIElement::s_CompositingModeProperty = RegisterProperty(WSTR("CompositingMode"), typeid(CompositingMode), typeid(UIElement), IntObject::GetObject(SourceOver), PropertyMetaData(AffectsRender));
DependencyProperty* UIElement::s_IsMouseCapturedProperty = RegisterProperty(WSTR("IsMouseCaptured"), typeid(bool), typeid(UIElement), BoolObject::GetObject(false), PropertyMetaData(None));
DependencyProperty* UIElement::s_IsMouseCaptureWithinProperty = RegisterProperty(WSTR("IsMouseCaptureWithin"), typeid(bool), typeid(UIElement), BoolObject::GetObject(false), PropertyMetaData(None));
DependencyProperty* UIElement::s_IsMouseOverProperty = RegisterProperty(WSTR("IsMouseOver"), typeid(bool), typeid(UIElement), BoolObject::GetObject(false), PropertyMetaData(None));
DependencyProperty* UIElement::s_IsEnabledProperty = RegisterProperty(WSTR("IsEnabled"), typeid(bool), typeid(UIElement), BoolObject::GetObject(true), PropertyMetaData(None));
DependencyProperty* UIElement::s_IsFocusedProperty = RegisterProperty(WSTR("IsFocused"), typeid(bool), typeid(UIElement), BoolObject::GetObject(false), PropertyMetaData(None));
DependencyProperty* UIElement::s_IsKeyboardFocusedProperty = RegisterProperty(WSTR("IsKeyboardFocused"), typeid(bool), typeid(UIElement), BoolObject::GetObject(false), PropertyMetaData(None));
DependencyProperty* UIElement::s_IsKeyboardFocuseWithinProperty = RegisterProperty(WSTR("IsKeyboardFocuseWithin"), typeid(bool), typeid(UIElement), BoolObject::GetObject(false), PropertyMetaData(None));
DependencyProperty* UIElement::s_SnapsToDevicePixelsProperty = RegisterProperty(WSTR("SnapsToDevicePixels"), typeid(bool), typeid(UIElement), BoolObject::GetObject(false), PropertyMetaData(AffectsRender));
DependencyProperty* UIElement::s_ClipProperty = RegisterProperty(WSTR("Clip"), typeid(Geometry), typeid(UIElement), NULL, PropertyMetaData(AffectsRender));
DependencyProperty* UIElement::s_FocusableProperty = RegisterProperty(WSTR("Focusable"), typeid(bool), typeid(UIElement), BoolObject::GetObject(true/*TODO false*/), PropertyMetaData(None));

RoutedEvent* UIElement::s_MouseLeftButtonDownEvent = EventManager::RegisterRoutedEvent(WSTR("MouseLeftButtonDown"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*,MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::s_MouseRightButtonDownEvent = EventManager::RegisterRoutedEvent(WSTR("MouseRightButtonDown"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*,MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::s_MouseLeftButtonUpEvent = EventManager::RegisterRoutedEvent(WSTR("MouseLeftButtonUp"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*,MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::s_MouseRightButtonUpEvent = EventManager::RegisterRoutedEvent(WSTR("MouseRightButtonUp"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*,MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::s_KeyDownEvent = EventManager::RegisterRoutedEvent(WSTR("KeyDown"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*,KeyEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::s_KeyUpEvent = EventManager::RegisterRoutedEvent(WSTR("KeyUp"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*,KeyEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::s_DragEnterEvent = EventManager::RegisterRoutedEvent(WSTR("DragEnter"), RoutingStrategy_Bubble, typeid(int), typeid(UIElement));
RoutedEvent* UIElement::s_DragLeaveEvent = EventManager::RegisterRoutedEvent(WSTR("DragLeave"), RoutingStrategy_Bubble, typeid(int), typeid(UIElement));
RoutedEvent* UIElement::s_DragOverEvent = EventManager::RegisterRoutedEvent(WSTR("DragOver"), RoutingStrategy_Bubble, typeid(int), typeid(UIElement));
RoutedEvent* UIElement::s_DropEvent = EventManager::RegisterRoutedEvent(WSTR("Drop"), RoutingStrategy_Bubble, typeid(int), typeid(UIElement));

RoutedEvent* UIElement::s_PreviewMouseLeftButtonDownEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewMouseLeftButtonDown"), RoutingStrategy_Tunnel, typeid(stub_interface2<void, Object*,MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::s_PreviewMouseRightButtonDownEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewMouseRightButtonDown"), RoutingStrategy_Tunnel, typeid(stub_interface2<void, Object*,MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::s_PreviewMouseLeftButtonUpEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewMouseLeftButtonUp"), RoutingStrategy_Tunnel, typeid(stub_interface2<void, Object*,MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::s_PreviewMouseRightButtonUpEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewMouseRightButtonUp"), RoutingStrategy_Tunnel, typeid(stub_interface2<void, Object*,MouseButtonEventArgs*>), typeid(UIElement));
RoutedEvent* UIElement::s_PreviewDragEnterEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewDragEnter"), RoutingStrategy_Tunnel, typeid(int), typeid(UIElement));
RoutedEvent* UIElement::s_PreviewDragLeaveEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewDragLeave"), RoutingStrategy_Tunnel, typeid(int), typeid(UIElement));
RoutedEvent* UIElement::s_PreviewDragOverEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewDragOver"), RoutingStrategy_Tunnel, typeid(int), typeid(UIElement));
RoutedEvent* UIElement::s_PreviewDropEvent = EventManager::RegisterRoutedEvent(WSTR("PreviewDrop"), RoutingStrategy_Tunnel, typeid(int), typeid(UIElement));

#if 0
template<class T, class arg1_type> class stub_test2 : public stub_interface2<Object*, arg1_type>
{
public:

	CTOR stub_test2(void (T::*pm)(arg1_type)) : m_pm(pm)
	{
	}

	void invoke(Object* p, arg1_type arg1)
	{
		(((T*)p)->*m_pm)(arg1);
	}

	void (T::*m_pm)(arg1_type);
};
#endif

/*
typedef stub_interface2<Object*,MouseEventArgs*>* MouseEventHandler;
typedef stub_interface2<Object*,MouseButtonEventArgs*>* MouseButtonEventHandler;

template<class F> stub_interface2<Object*,MouseEventArgs*>* newMouseEventHandler(const F& f)
{
	return new stub2<F,Object*,MouseEventArgs*>(f);
}

template<class F> stub_interface2<Object*,MouseButtonEventArgs*>* newMouseButtonEventHandler(const F& f)
{
	return new stub2<F, Object*,MouseButtonEventArgs*>(f);
}
*/

UIElement::Static::Static()
{
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_MouseDownEvent, mem_fun(&UIElement::OnMouseDown));
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_MouseUpEvent, mem_fun(&UIElement::OnMouseUp));
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_MouseMoveEvent, mem_fun(&UIElement::OnMouseMove));
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_MouseEnterEvent, mem_fun(&UIElement::OnMouseEnter));
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_MouseLeaveEvent, mem_fun(&UIElement::OnMouseLeave));

	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_PreviewMouseDownEvent, mem_fun(&UIElement::OnPreviewMouseDown));
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_PreviewMouseUpEvent, mem_fun(&UIElement::OnPreviewMouseUp));
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_PreviewMouseMoveEvent, mem_fun(&UIElement::OnPreviewMouseMove));
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_PreviewMouseEnterEvent, mem_fun(&UIElement::OnPreviewMouseEnter));
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_PreviewMouseLeaveEvent, mem_fun(&UIElement::OnPreviewMouseLeave));

	EventManager::RegisterClassHandler(typeid(UIElement), s_KeyDownEvent, mem_fun(&UIElement::OnKeyDown));
	EventManager::RegisterClassHandler(typeid(UIElement), s_KeyUpEvent, mem_fun(&UIElement::OnKeyUp));

	// ??
	EventManager::RegisterClassHandler(typeid(UIElement), CommandManager::get_PreviewCanExecuteEvent(), mem_fun(&UIElement::OnPreviewCanExecute));
	EventManager::RegisterClassHandler(typeid(UIElement), CommandManager::get_CanExecuteEvent(), mem_fun(&UIElement::OnCanExecute));
	EventManager::RegisterClassHandler(typeid(UIElement), CommandManager::get_PreviewExecutedEvent(), mem_fun(&UIElement::OnPreviewExecuted));
	EventManager::RegisterClassHandler(typeid(UIElement), CommandManager::get_ExecutedEvent(), mem_fun(&UIElement::OnExecuted));

	EventManager::RegisterClassHandler(typeid(UIElement), TextCompositionManager::s_TextInputEvent, mem_fun(&UIElement::OnTextInput));

	/*
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_MouseDownEvent, mem_fun(&UIElement::OnMouseDown));
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_MouseUpEvent, mem_fun(&UIElement::OnMouseUp));
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_MouseMoveEvent, mem_fun(&UIElement::OnMouseMove));
	*/

	/*
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_MouseDownEvent, newMouseButtonEventHandler(mem_fun(&UIElement::OnMouseDown)));
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_MouseUpEvent, newMouseButtonEventHandler(mem_fun(&UIElement::OnMouseUp)));
	EventManager::RegisterClassHandler(typeid(UIElement), Mouse::s_MouseMoveEvent, newMouseEventHandler(mem_fun(&UIElement::OnMouseMove)));
	*/
}

UIElement::Static* UIElement::s_static;

UIElement::UIElement()
{
	if (s_static == NULL)
	{
		s_static = new Static;
	}

	m_parent = NULL;	// ??

	m_pOwnerWindow = NULL;
 	m_rparent = NULL;

//	m_width = NULL;
//	m_height = NULL;

	m_computedLeft = 0;
	m_computedTop = 0;

	m_redrawNext = NULL;
	m_bRedraw = false;

	m_bInMeasure = false;
	m_bMeasureValid = false;
	m_bArrangeValid = false;
	m_availSizeDontCare = false;
	m_bInPosition = false;
 
	m_bInMeasureList = false;
	m_bInArrangeList = false;

	m_availSize.Width = -1;	// Means that Measure has never been called

//	m_VisualTree = NULL;

	m_pReferencingRenderCommand = NULL;

	m_pDockParent = NULL;

	m_transformMatrix = LDraw::Matrix3f::GetIdentity();

	//m_pFont = NULL;

#if 0
	m_rchildList = new VisualNodes;	// ??
#endif

	m_Filter = NULL;
//	m_LayoutTransform = NULL;
	m_RenderTransform = NULL;

	m_handlers.resize(EventManager::s_registeredEvents->m_items.size());

	m_commandBindings = new CommandBindingCollection;

//	get_MouseDown().connect(std::bind1st(std::mem_fun1(&UIElement::OnMouseDown), this));
//	get_MouseDown().connect(mem_fn(&UIElement::OnMouseDown));

	m_baseValues.resize(depstate->gindex);
	m_propertyClocks.resize(depstate->gindex);

	m_animatedPropertiesCount = 0;
}

UIElement::~UIElement()
{
}

bool UIElement::get_AllowDrop()
{
	return static_cast<BoolObject*>(GetValue(get_AllowDropProperty()))->GetValue();
}

void UIElement::set_AllowDrop(bool allowDrop)
{
	SetValue(get_AllowDropProperty(), BoolObject::GetObject(allowDrop));
}

Geometry* UIElement::get_Clip()
{
	return static_cast<Geometry*>(GetValue(get_ClipProperty()));
}

void UIElement::set_Clip(Geometry* geometry)
{
	SetValue(get_ClipProperty(), geometry);
}

Brush* UIElement::get_OpacityMask()
{
	return static_cast<Brush*>(GetValue(get_OpacityMaskProperty()));
}

void UIElement::set_OpacityMask(Brush* brush)
{
	SetValue(get_OpacityMaskProperty(), brush);
}

signal2<Object*, MouseEventArgs*>& UIElement::get_MouseMove()
{
	RoutedEvent* routedEvent = Mouse::s_MouseMoveEvent;
	int index = routedEvent->m_index;

	if (m_handlers[index] == NULL)
	{
		VERIFY(routedEvent->get_HandlerType()->GetClass());
		ClassType* pSigType = dynamic_cast<ClassType*>(routedEvent->get_HandlerType()->GetClass()->LookupType(ASTR("signal_type"))->GetStripped());
		m_handlers[index] = (signal_base*)newobj(pSigType);
	}

	return *dynamic_cast<signal2<Object*, MouseEventArgs*>*>(m_handlers[index]);
}

signal2<Object*, MouseButtonEventArgs*>& UIElement::get_MouseDown()
{
	RoutedEvent* routedEvent = Mouse::s_MouseDownEvent;
	int index = routedEvent->m_index;

	if (m_handlers[index] == NULL)
	{
		ClassType* pSigType = dynamic_cast<ClassType*>(routedEvent->get_HandlerType()->GetClass()->LookupType(ASTR("signal_type"))->GetStripped());
		m_handlers[index] = (signal_base*)newobj(pSigType);
	}

	return *dynamic_cast<signal2<Object*, MouseButtonEventArgs*>*>(m_handlers[index]);
}

signal2<Object*, MouseButtonEventArgs*>& UIElement::get_MouseUp()
{
	RoutedEvent* routedEvent = Mouse::s_MouseUpEvent;
	int index = routedEvent->m_index;

	if (m_handlers[index] == NULL)
	{
		VERIFY(routedEvent->get_HandlerType()->GetClass());
		ClassType* pSigType = dynamic_cast<ClassType*>(routedEvent->get_HandlerType()->GetClass()->LookupType(ASTR("signal_type"))->GetStripped());
		m_handlers[index] = (signal_base*)newobj(pSigType);
	}

	return *dynamic_cast<signal2<Object*, MouseButtonEventArgs*>*>(m_handlers[index]);
}

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

void UIElement::AddHandler(RoutedEvent* routedEvent, stub_interface_base* handler, bool handledEventsToo)
{
	// TODO
	VERIFY(0);
}

void UIElement::RemoveHandler(RoutedEvent* event, stub_interface_base* handler)
{
	// TODO
	VERIFY(0);
}

class EventRoute : public Object
{
public:
	// TODO
	list<UIElement*> ancestors;
};

void UIElement::RaiseEvent(RoutedEventArgs* args)
{
	if (args->get_Source() == NULL)
	{
		args->set_Source(this);
	}

	RoutedEvent* routedEvent = args->get_RoutedEvent();

	// preview phase
	if (routedEvent->get_RoutingStrategy() == RoutingStrategy_Tunnel)
	{
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
	}
	else if (routedEvent->get_RoutingStrategy() == RoutingStrategy_Bubble)
	{
		EventRoute route;

		UIElement* p = this;//dynamic_cast<UIElement*>(GetRParent());
		while (p)
		{
			route.ancestors.push_back(p);
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

				for (int i = 0; i < nslots; i++)
				{
					stub_interface_base* slot = sig->GetSlot(i);
					if (!args->get_Handled())	// TODO
					{
						args->InvokeEventHandler(this, slot);
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

			++it;
		}
	}
	else if (routedEvent->get_RoutingStrategy() == RoutingStrategy_Direct)
	{
		VERIFY(0);
	}
}

void UIElement::OnMouseDown(MouseButtonEventArgs* args)
{
}

void UIElement::OnMouseLeftButtonDown(MouseButtonEventArgs* args)
{
}

void UIElement::OnMouseRightButtonDown(MouseButtonEventArgs* args)
{
}

void UIElement::OnMouseUp(MouseButtonEventArgs* args)
{
}

void UIElement::OnMouseLeftButtonUp(MouseButtonEventArgs* args)
{
}

void UIElement::OnMouseRightButtonUp(MouseButtonEventArgs* args)
{
}

void UIElement::OnMouseEnter(MouseEventArgs* args)
{
}

void UIElement::OnMouseLeave(MouseEventArgs* args)
{
}

void UIElement::OnMouseMove(MouseEventArgs* args)
{
}

void UIElement::OnGotMouseCapture(MouseEventArgs* args)
{
}

void UIElement::OnLostMouseCapture(MouseEventArgs* args)
{
}

void UIElement::OnKeyDown(KeyEventArgs* args)
{
}

void UIElement::OnKeyUp(KeyEventArgs* args)
{
}

void UIElement::OnTextInput(TextCompositionEventArgs* args)
{
}

void UIElement::OnPreviewMouseDown(MouseButtonEventArgs* args)
{
}

void UIElement::OnPreviewMouseLeftButtonDown(MouseButtonEventArgs* args)
{
}

void UIElement::OnPreviewMouseRightButtonDown(MouseButtonEventArgs* args)
{
}

void UIElement::OnPreviewMouseUp(MouseButtonEventArgs* args)
{
}

void UIElement::OnPreviewMouseLeftButtonUp(MouseButtonEventArgs* args)
{
}

void UIElement::OnPreviewMouseRightButtonUp(MouseButtonEventArgs* args)
{
}

void UIElement::OnPreviewMouseEnter(MouseEventArgs* args)
{
}

void UIElement::OnPreviewMouseLeave(MouseEventArgs* args)
{
}

void UIElement::OnPreviewMouseMove(MouseEventArgs* args)
{
}

void UIElement::OnPreviewGotMouseCapture(MouseEventArgs* args)
{
}

void UIElement::OnPreviewLostMouseCapture(MouseEventArgs* args)
{
}

bool UIElement::get_IsMouseCaptured()
{
	return static_cast<BoolObject*>(GetValue(get_IsMouseCapturedProperty()))->GetValue();
}

void UIElement::OnPropertyChanged(DependencyPropertyChangedEventArgs args)	// The effective value has changed
{
	Visual::OnPropertyChanged(args);

	DependencyProperty* pProperty = args.get_Property();

	if (pProperty->m_metadata.m_flags & AffectsParentMeasure)
	{
		GetParent()->InvalidateMeasure();
	}
	else if (pProperty->m_metadata.m_flags & AffectsParentArrange)
	{
		GetParent()->InvalidateArrange();
	}
	
	if (pProperty->m_metadata.m_flags & AffectsMeasure)
	{
		InvalidateMeasure();
	}
	else if (pProperty->m_metadata.m_flags & AffectsArrange)
	{
		InvalidateArrange();
	}
	else if (pProperty->m_metadata.m_flags & AffectsRender)
	{
		InvalidateRender();
	}
}

bool UIElement::CaptureMouse()
{
	// TODO, check that we're enabled

	VisualContentSource* pOwnerWindow = GetOwnerWindow();
	ASSERT(pOwnerWindow);
	if (pOwnerWindow)
	{
		pOwnerWindow->SetCapture(this);
		return true;
	}

	return false;
}

void UIElement::ReleaseMouseCapture()
{
	VisualContentSource* pOwnerWindow = GetOwnerWindow();
	ASSERT(pOwnerWindow);
	if (pOwnerWindow)
	{
		pOwnerWindow->ReleaseCapture(this);
	}
}

Object* UIElement::ComputeBaseVal(DependencyProperty* pProperty)
{
	// TODO
	VERIFY(0);
	return NULL;
	/*

	DependencyObject* pParent;

	if (m_specifiedProperties[pProperty->gindex] != UnsetValue)	// Local value set
	{
		if (m_depCookies[pProperty->gindex] != NULL)
		{
			pParent = GetDependencyParent();

			pParent->RemoveDependant(pProperty, m_depCookies[pProperty->gindex]);
			m_depCookies[pProperty->gindex] = NULL;
		}

		return m_specifiedProperties[pProperty->gindex];
	}

	if (m_style)
	{
		Style::Setter* propertyVal = m_style->m_Setters->m_depproperties[pProperty->gindex];
		if (propertyVal)
		{
			if (m_depCookies[pProperty->gindex] != NULL)
			{
				pParent = GetDependencyParent();

				pParent->RemoveDependant(pProperty, m_depCookies[pProperty->gindex]);
				m_depCookies[pProperty->gindex] = NULL;
			}

		//	return propertyVal->m_computedValue;
			return propertyVal->m_value;
		}
	}

	if ((pProperty->m_metadata.m_flags & ChildInherits) && (pParent = GetDependencyParent()) != NULL)
	{
		if (m_depCookies[pProperty->gindex] == NULL)
			m_depCookies[pProperty->gindex] = pParent->AddDependant(pProperty, this);

		return pParent->ComputeProperty(pProperty);
	}
	else
	{
		return pProperty->m_defaultValue;
	}
	*/
}

#if 0
// virtual
void UIElement::handleEvent(System::Event* evt)
{
}
#endif

UIElement* UIElement::get_Parent()
{
	return m_parent;
//	return dynamic_cast<DependencyObject*>(m_rparent);
}

UIElement* UIElement::get_Filter()
{
	return m_Filter;
}

void UIElement::set_Filter(UIElement* Filter)
{
	m_Filter = Filter;
	if (m_Filter)
	{
		m_Filter->m_rparent = this;
	}
}

LDraw::SizeD UIElement::get_DesiredSize() const
{
	return m_desiredSize;
}

void UIElement::SetParent(UIElement* parent)
{
	m_parent = parent;
}

UIElement* UIElement::GetParent()
{
	return m_parent;
}

__release<LDraw::Region> UIElement::GetVisibleRegion()
{
	return m_visibleRegion;
}

void UIElement::PlaceControls(PlatformWindow hWndParent/*, CHTMFlowBlockContext* pC*/)
{
}

void UIElement::Render(Graphics* pGraphics)
{
	pGraphics->PushTransform();
	pGraphics->MultiplyTransform(m_transformMatrix);

	RenderNoTransform(pGraphics);

	pGraphics->PopTransform();
}

// virtual
void Visual::RenderNoTransform(Graphics* pGraphics)
{
//	pGraphics->PushTransform();
//	pGraphics->MultiplyTransform(m_transformMatrix);

//	LDraw::Matrix oldTransform = pGraphics->GetTransform();
//	LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();

#if 0
	if (m_LayoutTransform)
	{
		__release<LDraw::Matrix3f> layoutTransform = m_LayoutTransform->get_Value();

		LDraw::SizeD size = get_ActualSize();
		LDraw::RectD rc(0, 0, size.Width, size.Height);
		LDraw::RectD rect;
		LDraw::GetTransformRectBoundingBox(layoutTransform, rc, &rect);

		layoutTransform->Translate(-rect.X, -rect.Y, LDraw::MatrixOrderAppend);

		pGraphics->MultiplyTransform(layoutTransform);
	}
#endif

	EdgeMode edgeMode = get_EdgeMode();
	if (edgeMode != EdgeMode_Unspecified)
	{
//		pGraphics->SetSmoothingMode(edgeMode == EdgeMode_AntiAliased? LDraw::SmoothingModeAntiAlias: LDraw::SmoothingModeNone);
	}

//	HRGN hRgn = ExtCreateRegion(NULL, 0, NULL);
//	HRGN hRgn = CreateRectRgn(m_expandedBBox.X, m_expandedBBox.Y, m_expandedBBox.GetRight(), m_expandedBBox.GetBottom());

#if 0//AMIGA

	LDraw::RectF oldclip = pGraphics->m_clip2;
	LDraw::RectF rect(m_expandedBBox.X, m_expandedBBox.Y, m_expandedBBox.Width, m_expandedBBox.Height);

	pGraphics->m_clip2 = LDraw::RectF::Intersect(pGraphics->m_clip2, rect, pGraphics->m_clip2);

	if (!pGraphics->m_clip2.IsEmpty())
	{
		_OnRender(pGraphics);
	}

	pGraphics->m_clip2 = oldclip;

#else

#if 0
	LDraw::RectF clip;
	pGraphics->GetClipBounds(&clip);

	LDraw::RectD xrect = m_expandedBBox;
	//GetTransformRectBoundingBox(pGraphics->m_transform, m_expandedBBox, &xrect);

	if (xrect.IntersectsWith(clip))
	{
#endif

#if 0
	LDraw::RectI invalidBounds;
	pGraphics->m_invalidRegion->GetRegionRect(&invalidBounds);
	ASSERT(!invalidBounds.IsEmpty());
#endif

//	LDraw::RectI elementBounds;
//	m_visibleWithChildrenRegion->GetRegionRect(&elementBounds);
	
//	if (!elementBounds.IsEmpty() && invalidBounds.IntersectsWith(elementBounds))
	{
	//	LDraw::Region oldClip;
	//	pGraphics->GetClip(&oldClip);
		pGraphics->PushClip();
		if (true)//m_bClip)
		{
#if 1//AMIGA

#if 0
			LDraw::Region* rgn;

			if (false && dynamic_cast<TextEdit*>(this))
			{
				rgn = m_visibleRegion;
				pGraphics->IntersectClip(rgn/*dynamic_cast<UIElement*>(this)->m_visibleRegion*/);
				pGraphics->Clear(LDraw::Color(255,0,0));

				rgn = m_visibleRegion->GetIntersection(pGraphics->m_invalidRegion);
				pGraphics->IntersectClip(rgn/*dynamic_cast<UIElement*>(this)->m_visibleRegion*/);
				pGraphics->Clear(LDraw::Color(0,255,0));
			}
			else
			{
				/*
				if (m_visibleRegion.m_p != pGraphics->m_invalidRegion.m_p)
					rgn = m_visibleRegion->GetIntersection(pGraphics->m_invalidRegion);
				else
				*/
					rgn = m_visibleRegion;

			//	pGraphics->IntersectClip(rgn/*dynamic_cast<UIElement*>(this)->m_visibleRegion*/);
			}
#endif

		//	if (dynamic_cast<UIElement*>(this))
			{
			}

#else
			LDraw::RectI rect(m_expandedBBox.X, m_expandedBBox.Y, m_expandedBBox.Width, m_expandedBBox.Height);
			pGraphics->IntersectClip(rect);
#endif
		}

//		gmVector2 xpt = pGraphics->m_transform.transform(gmVector2(rect.X, rect.Y));

//		LDraw::RectD rect;
//		LDraw::RectD::Intersect(rect, m_expandedBBox, pGraphics->m_clip.m_clipBounds._RectD());

	// Clip away children
#if 0
		HRGN hRgn = CreateRectRgn(pGraphics->m_clip.m_clipBounds.X, pGraphics->m_clip.m_clipBounds.Y, pGraphics->m_clip.m_clipBounds.GetRight(), pGraphics->m_clip.m_clipBounds.GetBottom());

		// Clip away children
		{
			int size = get_rchildList().size();

			LDraw::RectF clip;
			pGraphics->GetClipBounds(&clip);

			for (int i = 0; i < size; i++)
			{
				UIElement* pElement = get_rchildList()[i];
				if (pElement->get_Visibility() == Visible)
				{
					if (clip.IntersectsWith(pElement->m_expandedBBoxParent))
					{
					//GetTransformRectBoundingBox(m_transform.inverse(), m_clip.m_clipBounds, bounds);

						pElement->Clip(pGraphics, hRgn);
					}
				}
			}
		}

		// Intersect with parent
		if (pGraphics->m_clip.m_hRgn)
		{
			RECT rect;
			GetRgnBox(pGraphics->m_clip.m_hRgn, &rect);
			CombineRgn(hRgn, hRgn, pGraphics->m_clip.m_hRgn, RGN_AND);

			GetRgnBox(pGraphics->m_clip.m_hRgn, &rect);
		}
#endif
	//	pGraphics->m_clip.m_hRgn = hRgn;

		if (m_Filter)		// ??
		{
			m_Filter->Render(pGraphics);
		}
		else
		{
			//LDraw::BBox rect;
		//	if (!pGraphics->IsClipEmpty())
			{
				_OnRender(pGraphics);
			}
		}

//		DeleteObject(hRgn);

	//	pGraphics->SetClip(&oldClip);
		pGraphics->PopClip();

	}
#endif

//	pGraphics->SetSmoothingMode(oldSmoothingMode);
}

DependencyObject* UIElement::GetDependencyParent()
{
//	printf("UIElement::GetDependencyParent()\n");
	return m_rparent;
}

/*
Transform* UIElement::get_LayoutTransform()
{
	return m_LayoutTransform;
}

void UIElement::set_LayoutTransform(Transform* transform)
{
	m_LayoutTransform = transform;
}
*/

Transform* UIElement::get_RenderTransform()
{
	return m_RenderTransform;
}

void UIElement::set_RenderTransform(Transform* transform)
{
	m_RenderTransform = transform;
}

bool UIElement::get_SnapsToDevicePixels()
{
	return static_cast<BoolObject*>(GetValue(get_SnapsToDevicePixelsProperty()))->GetValue();
}

void UIElement::set_SnapsToDevicePixels(bool snapsToDevicePixels)
{
	SetValue(get_SnapsToDevicePixelsProperty(), BoolObject::GetObject(snapsToDevicePixels));
}

double UIElement::get_Opacity()
{
	return static_cast<DoubleObject*>(GetValue(get_OpacityProperty()))->GetValue();
}

void UIElement::set_Opacity(double opacity)
{
	SetValue(get_OpacityProperty(), DoubleObject::GetObject(opacity));
}

VisibilityState UIElement::get_Visibility()
{
	return (VisibilityState)static_cast<IntObject*>(GetValue(get_VisibilityProperty()))->GetValue();
}

void UIElement::set_Visibility(VisibilityState newVal)
{
//	InvalidateRender();
//	InvalidateMeasure();	// ??

	SetValue(get_VisibilityProperty(), IntObject::GetObject(newVal));

//	InvalidateRender();
//	InvalidateMeasure();	// ??

#if 0
	UIElement* parent = GetRParent();
	if (parent)
	{
		// TODO
#if 0
		parent->InvalidateMeasure();
#endif
	}
#endif
}

CompositingMode UIElement::get_CompositingMode()
{
	return (CompositingMode)static_cast<IntObject*>(GetValue(get_CompositingModeProperty()))->GetValue();
}

void UIElement::set_CompositingMode(CompositingMode newVal)
{
	SetValue(get_CompositingModeProperty(), IntObject::GetObject(newVal));
//	InvalidateRender();
}

bool UIElement::get_IsMouseOver()
{
	return static_cast<BoolObject*>(GetValue(get_IsMouseOverProperty()))->GetValue();
}

bool UIElement::get_IsMouseDirectlyOver()
{
	ASSERT(0);
	return false;
//	return static_cast<BoolObject*>(GetValue(get_IsMouseOverProperty()))->GetValue();
}

bool UIElement::get_IsEnabled()
{
	return static_cast<BoolObject*>(GetValue(get_IsEnabledProperty()))->GetValue();
}

void UIElement::set_IsEnabled(bool enabled)
{
	SetValue(get_IsEnabledProperty(), BoolObject::GetObject(enabled));
}

bool UIElement::get_Focusable()
{
	return static_cast<BoolObject*>(GetValue(get_FocusableProperty()))->GetValue();
}

void UIElement::set_Focusable(bool focusable)
{
	SetValue(get_FocusableProperty(), BoolObject::GetObject(focusable));
}

bool UIElement::get_IsFocused()
{
	return static_cast<BoolObject*>(GetValue(get_IsFocusedProperty()))->GetValue();
}

bool UIElement::get_IsKeyboardFocused()
{
	return static_cast<BoolObject*>(GetValue(get_IsKeyboardFocusedProperty()))->GetValue();
}

bool UIElement::get_IsKeyboardFocusWithin()
{
	return static_cast<BoolObject*>(GetValue(get_IsKeyboardFocuseWithinProperty()))->GetValue();
}

void UIElement::OnPreviewCanExecute(CanExecuteRoutedEventArgs* args)
{
	unsigned int count = m_commandBindings->GetCount();
	for (unsigned int i = 0; i < count; i++)
	{
		CommandBinding* commandBinding = m_commandBindings->get_Item(i);

		if (commandBinding->get_Command() == args->get_Command())
		{
			commandBinding->PreviewCanExecute(this, args);
		}
	}
}

void UIElement::OnCanExecute(CanExecuteRoutedEventArgs* args)
{
	unsigned int count = m_commandBindings->GetCount();
	for (unsigned int i = 0; i < count; i++)
	{
		CommandBinding* commandBinding = m_commandBindings->get_Item(i);

		if (commandBinding->get_Command() == args->get_Command())
		{
			commandBinding->CanExecute(this, args);
		}
	}
}

void UIElement::OnPreviewExecuted(ExecutedRoutedEventArgs* args)
{
	unsigned int count = m_commandBindings->GetCount();
	for (unsigned int i = 0; i < count; i++)
	{
		CommandBinding* commandBinding = m_commandBindings->get_Item(i);

		if (commandBinding->get_Command() == args->get_Command())
		{
			commandBinding->PreviewExecuted(this, args);
		}
	}
}

void UIElement::OnExecuted(ExecutedRoutedEventArgs* args)
{
	unsigned int count = m_commandBindings->GetCount();
	for (unsigned int i = 0; i < count; i++)
	{
		CommandBinding* commandBinding = m_commandBindings->get_Item(i);

		if (commandBinding->get_Command() == args->get_Command())
		{
			commandBinding->Executed(this, args);
		}
	}
}

CommandBindingCollection* UIElement::get_CommandBindings()
{
	return m_commandBindings;
}

/*
VisualNodes* UIElement::get_rchildList() const
{
	return m_rchildList;
}
*/

unsigned int UIElement::get_VisualChildrenCount()
{
	return 0;//m_rchildList->m_items.size();
}

Visual* UIElement::GetVisualChild(unsigned int index)
{
	THROW(std::exception("Index out of range"));
	//return m_rchildList->m_items[index];
}

double UIElement::get_VisualOpacity()
{
	return get_Opacity();
}

bool UIElement::IsDescendantOf(UIElement* pVisual)
{
	UIElement* pParent = dynamic_cast<UIElement*>(GetRParent());

	if (pParent == NULL)
		return false;

	if (pParent == pVisual)
		return true;

	return pParent->IsDescendantOf(pVisual);
}

bool UIElement::IsAscendantOf(UIElement* pVisual)
{
	if (pVisual == NULL) return false;
	return pVisual->IsDescendantOf(this);
}

VisualContentSource* Visual::GetOwnerWindow() const
{
	return m_pOwnerWindow;
}

void Visual::SetOwnerWindow(VisualContentSource* pWindow)
{
	if (m_pOwnerWindow != pWindow) // Not fully tested
	{
		m_pOwnerWindow = pWindow;

		if (m_bRedraw)
		{
			// Another approach, instead of redraw list on WindowBase OnClose
			// would be to add to window redrawList here
		}

		unsigned int size = get_VisualChildrenCount();//get_rchildList()->get_Size();

		for (unsigned int i = 0; i < size; i++)
		{
			Visual* pElement = GetVisualChild(i);//(*get_rchildList())[i];
			pElement->SetOwnerWindow(pWindow);
		}

		/*
		if (get_VisualTree())
		{
			Visual* pVisual = get_VisualTree();

			pVisual->SetOwnerWindow(pWindow);
		}
		*/
	}
}

UIElement* RecalculateParent(UIElement* pThis)
{
	ASSERT(0);
#if 0
	LDraw::SizeD oldDesiredSize = pThis->m_desiredSize;
	pThis->Measure(pThis->m_availSize);	// Remeasure with same availSize as last time

	if (pThis->m_desiredSize != pThis->m_computedSize.Width || pThis->m_desiredHeight != pThis->m_computedHeight)
	{
		if (dynamic_cast<CUIFloatingFrame*>(pThis) == NULL)
		{
			if (pThis->GetRParent())
			{
				return RecalculateParent(pThis->GetRParent());
			}
		}
	}
#endif
	return pThis;
}

void Control::set_VisualTree(UIElement* newVal)
{
//	printf("Control::set_VisualTree\n");

	ASSERT(this);

	if (m_VisualTree)
	{
		RemoveVisualChild(m_VisualTree);
		/*
		m_VisualTree->SetRParent(NULL);
		m_VisualTree = NULL;
		*/
	}

	m_VisualTree = newVal;

	if (m_VisualTree)
	{
		AddVisualChild(m_VisualTree);
		/*
		m_VisualTree->SetRParent(this);
		m_VisualTree->SetOwnerWindow(GetOwnerWindow());
		*/
	}

#if 0
	SetValue(VisualTreeProperty, newVal);

	printf("UIElement::set_VisualTree\n");

	if (m_VisualTree != newVal)
	{
		if (m_VisualTree)
		{
		;//	delete m_VisualTree;//->m_rparent = NULL;
			m_VisualTree->SetRParent(NULL);
		}

		m_VisualTree = newVal;

		if (m_VisualTree)
		{
			m_VisualTree->SetRParent(this);

			m_VisualTree->SetOwnerWindow(m_pOwnerWindow);	// must update this right ?

//			m_VisualTree->InvalidateMeasure();
//			m_VisualTree->Invalidate();
		}
	}
#endif
}

#if 0
void UIElement::AddRChild(Visual* pChild)
{
	ASSERT(pChild->GetRParent() == NULL);
	pChild->SetRParent(this);

	WindowBase* pOwnerWindow = GetOwnerWindow();
//	if (pOwnerWindow != pChild->get_OwnerWindow())
	pChild->SetOwnerWindow(pOwnerWindow);

	ASSERT(0);
#if 0
	m_rchildList->m_items.Add(pChild);
#endif

#if 0
	if (pOwnerWindow)
	{
	//	pChild->m_bMeasureValid = true;
	//	pChild->InvalidateMeasure();
		OnChildDesiredSizeChanged(pChild);
	}
#endif
}
#endif

void Visual::RemoveRChild(Visual* pChild)
{
	ASSERT(0);

#if 0
	ASSERT(pChild->GetRParent() == this);
	pChild->SetRParent(NULL);

	long size = m_rchildList->get_Size();
	for (int i = 0; i < size; i++)
	{
		if ((*m_rchildList)[i] == pChild)
		{
			m_rchildList->m_items.RemoveAt(i);//m_rchildList.m_items.begin()+i);

			InvalidateMeasure();

			/*
			{
				UIElement* pVisual = RecalculateParent(this);
				ASSERT(pVisual);
				pVisual->Arrange(LDraw::SizeF(pVisual->m_desiredWidth, pVisual->m_desiredHeight));
				pVisual->Invalidate();
			}
			*/

			return;
		}
	}
	ASSERT(0);
#endif
}

void UIElement::ReplaceRChild(UIElement* oldChild, UIElement* newChild)
{
	ASSERT(0);
#if 0
// TODO, improve
	RemoveRChild(oldChild);
	AddRChild(newChild);

	// TODO, only if not already done
	newChild->CalculateBoundsAndChildren(LDraw::SizeD(0, 0));

	UIElement* pVisual = RecalculateParent(this);
	ASSERT(pVisual);
	pVisual->Arrange(LDraw::SizeF(pVisual->m_desiredWidth, pVisual->m_desiredHeight));
#endif
}

void UIElement::AppendRChild(UIElement* pChild)
{
//	AddRChild(pChild);

	ASSERT(0);

#if 0
	// TODO, only if not already done
	pChild->OnMeasure(LDraw::SizeD(0, 0));

	UIElement* pVisual = RecalculateParent(this);
	ASSERT(pVisual);
	pVisual->Arrange(pVisual->m_desiredSize);
	pVisual->Invalidate();
#endif
}

void Visual::CreateOpaqueRegion(Graphics* pGraphics)
{
	/*
	{
		LDraw::Region* rgn1 = new LDraw::Region(LDraw::RectI(0, 0, 60, 60));
		LDraw::Region* rgn2 = new LDraw::Region(LDraw::RectI(0, 0, 60, 40));

		rgn1->Union(rgn2);

		rgn1->m_data->Compress();
	}
	*/

	pGraphics->PushTransform();
	pGraphics->MultiplyTransform(m_transformMatrix);

	CreateOpaqueRegionNoTransform(pGraphics);

	pGraphics->PopTransform();
}

void Visual::CreateOpaqueRegionNoTransform(Graphics* pGraphics)
{
	/*
	{
		LDraw::Region* rgn1 = new LDraw::Region(LDraw::RectI(0, 0, 60, 60));
		LDraw::Region* rgn2 = new LDraw::Region(LDraw::RectI(0, 0, 60, 40));

		rgn1->Union(rgn2);

		rgn1->m_data->Compress();
	}
	*/

#if 0	// TODO, not sure
	if (get_VisualTree())
	{
		get_VisualTree()->CreateOpaqueRegion(pGraphics);

		m_opaqueRegion = get_VisualTree()->m_opaqueRegion;
		m_bDrawsOutsideOpaqueRegion = get_VisualTree()->m_bDrawsOutsideOpaqueRegion;
	}
	else
#endif
	{
		m_opaqueRegion = OnGetOpaqueRegion(pGraphics->GetTransform());

	//	LDraw::vector2f xpt = pGraphics->GetTransform()->Transform(LDraw::PointF(m_expandedBBox.X, m_expandedBBox.Y));
	//	LDraw::RectI rect(xpt[0], xpt[1], m_expandedBBox.Width, m_expandedBBox.Height);
		LDraw::Region* rect = new LDraw::Region(m_expandedBBox, pGraphics->GetTransform()->m_matrix, 10, true);

		pGraphics->PushTransform();

		if (m_childrenTransformMatrix)
		{
			pGraphics->MultiplyTransform(m_childrenTransformMatrix);
		}

		int size = get_VisualChildrenCount();//rchildList->get_Size();
		for (int i = size-1; i >= 0; i--)
		{
			Visual* pElement = GetVisualChild(i);//(*m_rchildList)[i];

			pElement->CreateOpaqueRegion(pGraphics);
			ASSERT(pElement->m_opaqueRegion);

			//pElement->m_visibleRegion = new LDraw::Region(rect);

			if (m_opaqueRegion->m_refcount > 1) m_opaqueRegion = m_opaqueRegion->Clone();
			m_opaqueRegion->Union(pElement->m_opaqueRegion);
			m_opaqueRegion->Intersect(rect);
		}

		pGraphics->PopTransform();
	}
}

void Visual::CreateOpaqueRegion2NoTransform(Graphics* pGraphics)
{
	/*
	{
		LDraw::Region* rgn1 = new LDraw::Region(LDraw::RectI(0, 0, 60, 60));
		LDraw::Region* rgn2 = new LDraw::Region(LDraw::RectI(0, 0, 60, 40));

		rgn1->Union(rgn2);

		rgn1->m_data->Compress();
	}
	*/

#if 0	// TODO, not sure
	if (get_VisualTree())
	{
		//m_VisualTree->CreateOpaqueRegion(pGraphics);
		m_opaqueRegion = get_VisualTree()->m_opaqueRegion;
		m_bDrawsOutsideOpaqueRegion = get_VisualTree()->m_bDrawsOutsideOpaqueRegion;
	}
	else
#endif
	{
		m_opaqueRegion = OnGetOpaqueRegion(pGraphics->GetTransform());

	//	LDraw::vector2f xpt = pGraphics->GetTransform()->Transform(LDraw::PointF(m_expandedBBox.X, m_expandedBBox.Y));
	//	LDraw::RectI rect(xpt[0], xpt[1], m_expandedBBox.Width, m_expandedBBox.Height);
		LDraw::Region* rect = new LDraw::Region(m_expandedBBox, pGraphics->GetTransform()->m_matrix, 10, true);

		int size = get_VisualChildrenCount();//m_rchildList->get_Size();
		for (int i = size-1; i >= 0; i--)
		{
			Visual* pElement = GetVisualChild(i);//(*m_rchildList)[i];

		//	pElement->CreateOpaqueRegion(pGraphics);
		//	ASSERT(pElement->m_opaqueRegion);

			//pElement->m_visibleRegion = new LDraw::Region(rect);

			if (m_opaqueRegion->m_refcount > 1) m_opaqueRegion = m_opaqueRegion->Clone();
			m_opaqueRegion->Union(pElement->m_opaqueRegion);
			m_opaqueRegion->Intersect(rect);
		}
	}
}

// virtual
void Visual::CreateLayerStuff(Graphics* pGraphics)
{
	/*
	if (dynamic_cast<ScrollViewer*>(this))
	{
		MessageBeep(-1);
	}
	*/

//	printf("CreateLayerStuff..\n");
//	Delay(20);

	pGraphics->PushTransform();
	pGraphics->MultiplyTransform(m_transformMatrix);

	m_windowToElementTransform = pGraphics->GetTransform();

	if (m_childrenTransformMatrix)
	{
		pGraphics->MultiplyTransform(m_childrenTransformMatrix);
	}

	ASSERT(m_visibleRegion.m_p != NULL);
	ASSERT(m_visibleWithChildrenRegion.m_p != NULL);

#if 0	// TODO, not sure
	if (get_VisualTree())
	{
		get_VisualTree()->m_visibleRegion = m_visibleRegion;
		get_VisualTree()->m_visibleWithChildrenRegion = m_visibleWithChildrenRegion;
		get_VisualTree()->m_bRenderValid = false;

		get_VisualTree()->CreateLayerStuff(pGraphics);

		m_visibleRegion = get_VisualTree()->m_visibleRegion;
		m_visibleWithChildrenRegion = get_VisualTree()->m_visibleWithChildrenRegion;
	}
	else
#endif
	{
		/*
		if (m_visibleRegion == NULL)
		{
			LDraw::vector2f xpt = pGraphics->GetTransform()->Transform(LDraw::PointF(m_expandedBBox.X, m_expandedBBox.Y));
			LDraw::RectI rect(xpt[0], xpt[1], m_expandedBBox.Width, m_expandedBBox.Height);

			m_visibleRegion = new LDraw::Region(rect);
		}
		*/

		int size = get_VisualChildrenCount();//m_rchildList->get_Size();
		for (int i = size-1; i >= 0; i--)
		{
			Visual* pElement = GetVisualChild(i);//(*m_rchildList)[i];

			if (pElement->IsVisible())//pElement->get_Visibility() == Visible)
			{

				//pElement->m_opaqueRegion = pElement->OnGetOpaqueRegion(pGraphics->GetTransform());

				if (pElement->GetClipMode())
				{
					pGraphics->PushTransform();
					pGraphics->MultiplyTransform(pElement->m_transformMatrix);

					// Initialize the visible region to the element's bounds
					/*
					{
						LDraw::vector2f xpt = pGraphics->GetTransform()->Transform(LDraw::PointF(pElement->m_expandedBBox.X, pElement->m_expandedBBox.Y));
						LDraw::RectI rect(xpt[0], xpt[1], pElement->m_expandedBBox.Width, pElement->m_expandedBBox.Height);
						pElement->m_visibleRegion = new LDraw::Region(rect);
					}
					*/
					pElement->m_visibleRegion = new LDraw::Region(pElement->m_expandedBBox, pGraphics->GetTransform()->m_matrix, 10, true);
					pElement->m_bRenderValid = false;

					pElement->m_visibleRegion->Intersect(m_visibleRegion);

					//	pElement->m_visibleWithChildrenRegion->Intersect(m_visibleRegion);

					pElement->m_visibleWithChildrenRegion = pElement->m_visibleRegion;

					ASSERT(pElement->m_opaqueRegion);
					if (m_visibleRegion->m_refcount > 1) m_visibleRegion = m_visibleRegion->Clone();
					m_visibleRegion->Exclude(pElement->m_opaqueRegion);
				//	m_visibleRegion->Exclude(pElement->m_visibleRegion);

					pGraphics->PopTransform();
				}
				else
				{
					pElement->m_visibleRegion = m_visibleRegion;
					pElement->m_visibleWithChildrenRegion = pElement->m_visibleRegion;
					pElement->m_bRenderValid = false;
				}

				ASSERT(pElement->m_visibleRegion.m_p != NULL);
				pElement->CreateLayerStuff(pGraphics);
			}
		}
	}

	pGraphics->PopTransform();
}

#if 0
// virtual
void UIElement::SetLayoutOffset(double x, double y)
{
//	printf("SetLayoutOffset(%d, %d)", (int)x, (int)y);
	m_transformMatrix = LDraw::Matrix3f::GetTranslate(x, y);
	m_inverseTransformMatrix = NULL;
	m_windowTransform = NULL;
	/*
	UIElement* parent = GetRParent();
	if (parent)
	{
		m_windowTransform = new LDraw::Matrix3f(m_transformMatrix->m_matrix * parent->GetWindowToElementTransformMatrix()->m_matrix);
	}
	*/

	LDraw::GetTransformRectBoundingBox(m_transformMatrix, m_expandedBBox, &m_expandedBBoxParent);	// ??
#if 0
//	 = GetBounding
	m_expandedBBox.Offset(x, y);
#endif

	//GetTransformRectBoundingBox(matrix, m_bounds, &m_expandedBBox);
}

void UIElement::SetLayoutTransform(LDraw::Matrix3f* transform)
{
	printf("UIElement::SetLayoutTransform\n");

	m_transformMatrix = transform;
	LDraw::GetTransformRectBoundingBox(m_transformMatrix, m_expandedBBox, &m_expandedBBoxParent);	// ??
}
#endif

/*
EventTargetImpl* UIElement::GetParentEventTarget()
{
//	printf("UIElement::GetParentEventTarget()\n");
	return dynamic_cast<EventTargetImpl*>(GetRParent());
}
*/

LDraw::PointD Visual::ScreenToElement(double screenX, double screenY)
{
	ASSERT(0);
	return LDraw::PointD();
}

LDraw::PointD Visual::WindowToElement(double ScreenX, double ScreenY)
{
//	ASSERT(relativeTo != NULL);
//	if (relativeTo == NULL) return NULL;

	VisualContentSource* pOwnerWindow = GetOwnerWindow();
	ASSERT(pOwnerWindow);

#if 1

	stack<Visual*> stack;

	LDraw::matrix3f m = LDraw::matrix3f::getIdentity();
	Visual* r = this;
	while (r != pOwnerWindow->m_Content)
	{
		stack.push(r);
		r = r->GetRParent();
	}
	stack.push(r);

	LDraw::PointD xpt = LDraw::PointD(ScreenX, ScreenY);

	while (stack.size())
	{
		Visual* r = stack.top();
		stack.pop();

		xpt = r->TransformPointToClient(xpt);
	}

	return xpt;

#else

	LDraw::matrix3f m = LDraw::matrix3f::getIdentity();
	const UIElement* r = this;
	while (r != pOwnerWindow)
	{
		m = r->GetLocalAnimatedMatrix()->m_matrix * m;

		r = const_cast<const UIElement*>(r->GetRParent());
	}

	LDraw::vector2f xpt = m.getInverse().transform(LDraw::vector2f(ScreenX, ScreenY));
	return LDraw::PointD(xpt[0], xpt[1]);

#endif
}

LDraw::PointD Visual::TransformPointToClient(LDraw::PointD point)
{
//	printf("UIElement::TransformPointToClient()\n");
	if (m_inverseTransformMatrix == NULL)
	{
		m_inverseTransformMatrix = GetParentToElementTransformMatrix()->GetInverse();
	}

	return m_inverseTransformMatrix->Transform(point);
}

// virtual
__release<LDraw::Matrix3f> Visual::GetWindowToElementTransformMatrix()
{
	if (m_windowToElementTransform == NULL)
	{
		Visual* parent = GetRParent();
		if (parent == NULL)	// hm
		{
			m_windowToElementTransform = LDraw::Matrix3f::GetIdentity();
		}
		else
		{
			ASSERT(parent);

			if (parent->m_childrenTransformMatrix)
			{
				m_windowToElementTransform = new LDraw::Matrix3f(GetParentToElementTransformMatrix()->m_matrix * parent->m_childrenTransformMatrix->m_matrix * parent->GetWindowToElementTransformMatrix()->m_matrix);
			}
			else
			{
				m_windowToElementTransform = new LDraw::Matrix3f(GetParentToElementTransformMatrix()->m_matrix * parent->GetWindowToElementTransformMatrix()->m_matrix);
			}
		}
	}

	return m_windowToElementTransform;
}

// virtual
__release<LDraw::Matrix3f> Visual::GetParentToElementTransformMatrix()
{
//	printf("UIElement::GetLocalAnimatedMatrix()\n");
	return m_transformMatrix;
}

void UIElement::_OnRender2(Graphics* pGraphics)
{
#if 0	// TODO, not sure
	if (get_VisualTree())
	{
		get_VisualTree()->Render(pGraphics);
	}
	else
#endif
	{

	pGraphics->PushClip();
	if (false)
	{
		ASSERT(m_visibleRegion != NULL);
		if (m_visibleRegion != NULL)
			pGraphics->IntersectClip(m_visibleRegion);
	}

	pGraphics->IntersectClip(m_expandedBBox);

	Brush* opacityMask = get_OpacityMask();
	if (opacityMask)
	{
		pGraphics->SetOpacityMask(opacityMask->CreateBrush(this, 1, 1));
	}

	OnRenderBackground(pGraphics);
	OnRender(pGraphics);

		if (m_childrenTransformMatrix)
		{
			pGraphics->MultiplyTransform(m_childrenTransformMatrix);
		}

		int size = get_VisualChildrenCount();//get_rchildList()->get_Size();

#if AMIGA

		for (int i = 0; i < size; i++)
		{
			UIElement* pElement = (*get_rchildList())[i];
			if (pElement->get_Visibility() == Visible)
			{
				pElement->Render(pGraphics);
			}
		}

#else

	//	LDraw::RectF clip;
	//	pGraphics->GetClipBounds(&clip);

		for (int i = 0; i < size; i++)
		{
			Visual* pElement = GetVisualChild(i);//(*get_rchildList())[i];
			if (pElement->IsVisible())//get_Visibility() == Visible)
			{
#if 0	// Have this ???
				if (clip.IntersectsWith(pElement->m_expandedBBoxParent))
#endif
				{
					pGraphics->PushClip();

					//LDraw::Region oldClip;
					//pGraphics->GetClip(&oldClip);

				//GetTransformRectBoundingBox(m_transform.inverse(), m_clip.m_clipBounds, bounds);

				//	RGNDATA rd;
				//	rd.rdh.dwSize = sizeof(RGNDATAHEADER);

#if 0	// TODO, had this
					LDraw::Region pRgn;
					pGraphics->GetClip(&pRgn);//LDraw::Region(pGraphics->m_clip);//CreateRectRgn(0, 0, 0, 0);
				//	CombineRgn(pRgn->m_hRgn, pGraphics->m_clip.m_hRgn, NULL, RGN_COPY);

					// clip away siblings above us
					for (int j = i+1; j < size; j++)
					{
						UIElement* pElement2 = get_rchildList()[j];
						pElement2->Clip(pGraphics, pRgn);
					}

#if 0
					pElement->m_visibleRegion.From(&pRgn);
#endif

					pGraphics->SetClip(&pRgn);
#endif

#if 0	// Have this
					if (!pGraphics->IsClipEmpty())
#endif

					{
						pElement->Render(pGraphics);
					}

					pGraphics->PopClip();//SetClip(&oldClip);
				}
			}
		}
#endif

	}

	pGraphics->PopClip();

	pGraphics->SetOpacityMask(NULL);
}

void UIElement::OnRenderBackground(Graphics* pGraphics)
{
}

void UIElement::OnRender(Graphics* pGraphics)
{
}

#if 0
void UIElement::ComputeVisibleRegion(Graphics* pGraphics)
{
	gmMatrix3 oldTransform = pGraphics->m_transform;
	pGraphics->MultiplyTransform(m_transformMatrix);

	if (m_VisualTree)
	{
	}
	else
	{
		int size = get_rchildList().size();

		LDraw::RectF clip;
		pGraphics->GetClipBounds(&clip);

		// Clip out siblings
		int i;
		for (i = 0; i < size; i++)
		{
			UIElement* pElement = get_rchildList()[i];
			if (pElement == this)
				break;
		}

		for (i++; i < size; i++)
		{
			UIElement* pElement = get_rchildList()[i];
			if (pElement->get_Visibility() == Visible)
			{
				if (clip.IntersectsWith(pElement->m_expandedBBoxParent))
				{
				//GetTransformRectBoundingBox(m_transform.inverse(), m_clip.m_clipBounds, bounds);

					pElement->ComputeVisibleRegion(pGraphics, rgn);
				}
				m_visibleRegion.Exclude(*pElement->GetVisibleRegion());
			}
		}
	}

	pGraphics->m_transform = oldTransform;
}
#endif

// virtual
__release<LDraw::Region> Visual::OnGetOpaqueRegion(LDraw::Matrix3f* transform)
{
/*
	LDraw::vector2f xpt = transform->Transform(LDraw::PointF(m_expandedBBox.X, m_expandedBBox.Y));
	LDraw::RectI rect(xpt[0], xpt[1], m_expandedBBox.Width, m_expandedBBox.Height);

	return new LDraw::Region(rect);

	return NULL;
	*/
	m_bDrawsOutsideOpaqueRegion = true;
	return LDraw::Region::GetEmptyRegion();

//	LDraw::Region* rgn = new LDraw::Region;
//	rgn->MakeEmpty();
//	return rgn;

#if 0

	__release<LDraw::Matrix3f> transform2 = *transform * *GetLocalAnimatedMatrix();
	if (m_VisualTree)
	{
		m_VisualTree->OnGetRegion(transform2, rgn);
	}
	else
	{
		int size = get_rchildList().get_Size();
		for (int i = 0; i < size; i++)
		{
			UIElement* pElement = get_rchildList()[i];
			if (pElement->get_Visibility() == Visible)
			{
				__release<LDraw::Region> childrgn = new LDraw::Region;
				pElement->OnGetRegion(transform2, childrgn);

				rgn->Union(childrgn);
			}
		}
	}
#endif
}

#if 0
// virtual
void UIElement::Clip(Graphics* pGraphics, LDraw::Region * rgn)
{
	pGraphics->PushTransform();
	//LDraw::Matrix3f oldTransform = pGraphics->GetTransform();
	pGraphics->MultiplyTransform(m_transformMatrix);

	if (m_VisualTree)
	{
		//CComQIPtr<ILViewNode, &IID_ILViewNode> v((IUnknown*)m_VisualTree);
		//UIElement* pVisual = dynamic_cast<UIElement*>(m_VisualTree);

		m_VisualTree->Clip(pGraphics, rgn);
	}
	else
	{
		int size = get_rchildList()->get_Size();

	//	LDraw::RectF clip;
	//	pGraphics->GetClipBounds(&clip);

		for (int i = 0; i < size; i++)
		{
			UIElement* pElement = (*get_rchildList())[i];
			if (pElement->get_Visibility() == Visible)
			{
			//	if (clip.IntersectsWith(pElement->m_expandedBBoxParent))
				{
				//GetTransformRectBoundingBox(m_transform.inverse(), m_clip.m_clipBounds, bounds);

					pElement->Clip(pGraphics, rgn);
				}
			}
		}
	}

	pGraphics->PopTransform();
//	pGraphics->SetTransform(oldTransform);
}
#endif

// virtual
bool Visual::HitTest(double x, double y/*, long pointerEvents*/)
{
	return true;//??
}

//virtual
Visual* Visual::HitTestElement(LDraw::Matrix3f* matrix2, LDraw::PointD pt)
{
	__release<LDraw::Matrix3f> matrix = *GetParentToElementTransformMatrix() * *matrix2;

	LDraw::PointD xpt = matrix->GetInverse()->Transform(pt);

	if (m_expandedBBox.Contains(xpt.X, xpt.Y))
	{
#if 0	// TODO, nots sure
		if (get_VisualTree())
		{
			Visual* pVisual = get_VisualTree();

			Visual* pHitElement = pVisual->HitTestElement(matrix, pt);
			if (pHitElement)
				return pHitElement;
		}
		else
#endif
		{
			if (m_childrenTransformMatrix)
			{
				matrix = *m_childrenTransformMatrix * *matrix;
			}

			Visual* pHitElement = HitTestChildren(matrix, pt);
			if (pHitElement)
			{
				return pHitElement;
			}
		}

		if (HitTest(xpt.X, xpt.Y))
		{
			return this;
		}
	}

	return NULL;
}

/*
// virtual
void UIElement::RecalculateParentBounds()	// Called by child
{
//	CalculateBoundsAndChildren
	if (GetRParent())
	{
		UIElement* pParent = dynamic_cast<UIElement*>(GetRParent());
		RecalculateParentBounds();//CalculateBoundsAndChildrenRecalculateParentBounds();
	}
}
*/

bool UIElement::NeedOffScreenBitmap()
{
	return false;
}

//virtual
void UIElement::OnChildDesiredSizeChanged(UIElement* child)
{
	if (!m_bInMeasure)
	{
		VERIFY(!m_bInMeasure);
		InvalidateMeasure();
	}
}

//virtual
LDraw::SizeD UIElement::MeasureCore(LDraw::SizeD availSize)
{
	VERIFY(0);
	return LDraw::SizeD(0,0);

#if 0
	LDraw::SizeD desiredSize;

	if (get_VisualTree())
	{
		UIElement* pVisual = dynamic_cast<UIElement*>(get_VisualTree());

#if 0
		ASSERT(pVisual->GetRParent() == this);
#endif
		pVisual->Measure(availSize/*LDraw::SizeD(m_desiredWidth, m_desiredHeight)*/);

		desiredSize = pVisual->m_desiredSize;

		/*
		availSize.Width = pVisual->m_desiredWidth;//pVisual->m_expandedBBox.Width;
		availSize.Height = pVisual->m_desiredHeight;//pVisual->m_expandedBBox.Height;
		*/
	}
	else
	{
//		unsigned int size = get_rchildList()->get_Size();
//		ASSERT(size == 0);
	}

#if 0	// ??
//	m_availSize = viewBox;
//	m_desiredWidth = 0;//availSize.Width;
//	m_desiredHeight = 0;//availSize.Height;
//	m_desiredWidth = availSize.Width;
//	m_desiredHeight = availSize.Height;

	long size = get_rchildList().get_Size();
	for (int i = 0; i < size; i++)
	{
		UIElement* pChildElement = get_rchildList()[i];

		pChildElement->Measure(availSize);
	}
#endif

	/*
	m_expandedBBox.X = 0;
	m_expandedBBox.Y = 0;
	m_expandedBBox.Width = m_computedSize.Width;
	m_expandedBBox.Height = m_computedHeight;
	*/

	/*
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
//		availSize.Width = m_desiredWidth;
	}
	else
	{
//		m_desiredWidth = 0;//viewBox.Width;
	}

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
//		availSize.Height = m_desiredHeight;
	}
	else
	{
//		m_desiredHeight = 0;//viewBox.Height;
	}
	*/

	return desiredSize;
#endif
}

// virtual
void UIElement::ArrangeCore(LDraw::RectD finalRect)
{
	// TODO
	// set offset and RenderBounds

	/*
	m_expandedBBox = finalRect;
	m_expandedBBox.X -= m_finalRect.X;
	m_expandedBBox.Y -= m_finalRect.Y;
	*/

	m_expandedBBox.X = 0;
	m_expandedBBox.Y = 0;
	m_expandedBBox.Width = finalRect.Width;
	m_expandedBBox.Height = finalRect.Height;

	m_transformMatrix = LDraw::Matrix3f::GetTranslate(finalRect.X, finalRect.Y);
	m_inverseTransformMatrix = NULL;
	m_windowToElementTransform = NULL;

#if 0
	if (get_VisualTree())
	{
		UIElement* pVisual = dynamic_cast<UIElement*>(m_VisualTree);

	//	pVisual->CalculateBoundsAndChildren(LDraw::RectD(0, 0, m_computedSize.Width, m_computedHeight));
		pVisual->Arrange(LDraw::RectD(LDraw::PointD(0, 0), finalSize));

		m_computedSize = pVisual->m_computedSize;

		m_expandedBBox = pVisual->m_expandedBBox;
	//	m_expandedBBox.Y = 0;
	//	m_expandedBBox.Width = m_computedSize.Width;
	//	m_expandedBBox.Height = m_computedHeight;

//		m_computedSize.Width = pVisual->m_expandedBBox.Width;
//		m_computedHeight = pVisual->m_expandedBBox.Height;
	}
	else
	{
		double minX = 0;
		double minY = 0;
		double maxX = m_computedSize.Width;
		double maxY = m_computedSize.Height;

		int size = get_VisualChildrenCount();//rchildList()->get_Size();
		for (int i = 0; i < size; i++)
		{
			Visual* pVisual = GetVisualChild(i);//(*get_rchildList())[i];
			pVisual->Arrange(LDraw::RectD(LDraw::PointD(0, 0), pVisual->get_DesiredSize()));

			minX = MIN(minX, pVisual->m_expandedBBox.X);
			minY = MIN(minY, pVisual->m_expandedBBox.Y);
			maxX = MAX(maxX, pVisual->m_expandedBBox.GetRight());
			maxY = MAX(maxY, pVisual->m_expandedBBox.GetBottom());

		}

		m_expandedBBox.X = minX;
		m_expandedBBox.Y = minY;
		m_expandedBBox.Width = maxX-minX;
		m_expandedBBox.Height = maxY-minY;
	}
#endif
}

Visual* UIElement::HitTestChildren(LDraw::Matrix3f* matrix, LDraw::PointD pt)
{
	//gmMatrix3 matrix = GetViewBoxMatrix() *  matrix2;

//	printf("children\n");
	int size = (int)get_VisualChildrenCount();
	for (int i = size-1; i >= 0; i--)
	{
		Visual* pVisual = GetVisualChild(i);
		/*
		TRACE("\t%s - mo(%d)", pVisual->GetType()->get_Name()->c_str(), dynamic_cast<UIElement*>(pVisual)->get_IsMouseOver());
		MenuItem* menuItem = dynamic_cast<MenuItem*>(pVisual);
		if (menuItem)
		{
			TRACE(" - %S", dynamic_cast<StringW*>(menuItem->get_Header())->c_str());
		}
		TRACE("\n");
		*/

		if (pVisual)
		{
			if (pVisual->IsVisible())//get_Visibility() == Visible)
			{
				Visual* pHitElement = pVisual->HitTestElement(matrix, pt);

				if (pHitElement)
				{
					/*
					TRACE("\t\tHit: (ow): %p- %s", pHitElement->GetOwnerWindow(), pHitElement->GetType()->get_Name()->c_str());
					if (MenuItem* p = dynamic_cast<MenuItem*>(pHitElement))
					{
						TRACE(" - %S", dynamic_cast<StringW*>(p->get_Header())->c_str());
					}
					else if (TextString* p = dynamic_cast<TextString*>(pHitElement))
					{
						TRACE(" - %S", p->get_TextContent()->c_str());
					}
					TRACE("\n");
					*/

					return pHitElement;
				}
			}
		}
	}

	return NULL;
}

void AssertValidMeasureChildren(UIElement* element)
{
	return;
#if 0
	if (!element->IsMeasureValid())
	{
		MessageBeep(-1);
	}

	if (element->get_VisualTree())
	{
		AssertValidMeasureChildren(element->get_VisualTree());
	}

	int nchildren = element->get_rchildList()->get_Size();
	for (int i = 0; i < nchildren; i++)
	{
		AssertValidMeasureChildren(element->get_rchildList()->Item(i));
	}
#endif
}

void AssertValidArrangeChildren(UIElement* element)
{
	return;

#if 0
	if (!element->IsArrangeValid())
	{
		MessageBeep(-1);
	}

	if (element->get_VisualTree())
	{
		AssertValidMeasureChildren(element->get_VisualTree());
		AssertValidArrangeChildren(element->get_VisualTree());
	}

	int nchildren = element->get_rchildList()->get_Size();
	for (int i = 0; i < nchildren; i++)
	{
		AssertValidMeasureChildren(element->get_rchildList()->Item(i));
		AssertValidArrangeChildren(element->get_rchildList()->Item(i));
	}
#endif
}

bool UIElement::IsMeasureValid() const
{
	return m_bMeasureValid;
}

bool UIElement::IsArrangeValid() const
{
	return m_bArrangeValid;
}

void UIElement::Measure(LDraw::SizeD availSize)
{
//	printf("UIElement::Measure\n");

	VERIFY(!m_bInMeasure);

	if (m_bInMeasure)
		return;

	if (!m_bMeasureValid || (!m_availSizeDontCare && (availSize.Width != m_availSize.Width || availSize.Height != m_availSize.Height)))
	{
		m_bInMeasure = true;

		LDraw::SizeD oldDesiredSize = m_desiredSize;

		m_availSize = availSize;

		LDraw::SizeD newDesiredSize = MeasureCore(availSize);

		ASSERT(newDesiredSize.Width >= 0 && newDesiredSize.Height >= 0);

		ASSERT(oldDesiredSize == m_desiredSize);	// Shouldn't have changed it

		m_bMeasureValid = true;

		if (oldDesiredSize.Width != newDesiredSize.Width || oldDesiredSize.Height != newDesiredSize.Height)
		{
			m_desiredSize = newDesiredSize;

			UIElement* parent = dynamic_cast<UIElement*>(GetRParent());
			if (parent)
			{
				if (!parent->m_bInMeasure)
				{
					parent->OnChildDesiredSizeChanged(this);
				}
			}
		}

		m_bInMeasure = false;
	}
	else
	{
		// TODO ASSERT recursively that all children have valid measure
		AssertValidMeasureChildren(this);
	}
}

void UIElement::Arrange(LDraw::RectD finalRect)
{
	VERIFY(!m_bInArrange);

//	printf("UIElement::Arrange\n");

//	if (!m_bArrangeValid/* || finalRect.Width != m_computedSize.Width || finalRect.Height != m_computedSize.Height*/)
	if (!m_bArrangeValid || finalRect != m_finalRect)
	{
		m_bInArrange = true;

		/*
		m_bRenderValid = false;	// ??
		if (m_Filter)
		{
			m_bRenderValid = false;	// ??
		}
		*/

		m_finalRect = finalRect;

	m_computedLeft = finalRect.X;
	m_computedTop = finalRect.Y;
	m_computedSize.Width = finalRect.Width;
	m_computedSize.Height = finalRect.Height;

		/*
		m_expandedBBox.X = 0;
		m_expandedBBox.Y = 0;
		m_expandedBBox.Width = m_computedSize.Width;
		m_expandedBBox.Height = m_computedSize.Height;
		*/

		ArrangeCore(finalRect);

		m_bArrangeValid = true;

		m_bRenderValid = false;

		m_bInArrange = false;
	}
	else
	{
		AssertValidArrangeChildren(this);

		/*
		// ??
		m_transformMatrix = LDraw::Matrix3f::GetTranslate(finalRect.X, finalRect.Y);
		m_inverseTransformMatrix = NULL;
		m_windowToElementTransform = NULL;
		*/
	}

//	printf("SetLayoutOffset(%d, %d)", (int)x, (int)y);
	/*
	UIElement* parent = GetRParent();
	if (parent)
	{
		m_windowTransform = new LDraw::Matrix3f(m_transformMatrix->m_matrix * parent->GetWindowToElementTransformMatrix()->m_matrix);
	}
	*/

	LDraw::GetTransformRectBoundingBox(m_transformMatrix, m_expandedBBox, &m_expandedBBoxParent);	// ??
#if 0
//	 = GetBounding
	m_expandedBBox.Offset(x, y);
#endif

	//GetTransformRectBoundingBox(matrix, m_bounds, &m_expandedBBox);
}

LDraw::RectD Visual::GetWindowToElementBounds()
{
	LDraw::RectD xrect;
	LDraw::GetTransformRectBoundingBox(GetWindowToElementTransformMatrix(), LDraw::RectD(0, 0, m_computedSize.Width, m_computedSize.Height), &xrect);

	return xrect;

#if 0
	ASSERT(m_pOwnerWindow);

	__release<LDraw::Matrix3f> transform = GetParentToElementTransformMatrix();
	UIElement* p = dynamic_cast<UIElement*>(GetRParent());
	while (p != m_pOwnerWindow)
	{
		transform = *transform * *p->GetParentToElementTransformMatrix();
		p = dynamic_cast<UIElement*>(p->GetRParent());
	}

	transform = *transform * *LDraw::Matrix3f::GetTranslate(-m_pOwnerWindow->m_expandedBBox.X, -m_pOwnerWindow->m_expandedBBox.Y);

	LDraw::RectD xrect;
//	GetTransformRectBoundingBox(transform, m_expandedBBox, &xrect);
	LDraw::GetTransformRectBoundingBox(transform, LDraw::RectD(0, 0, m_computedSize.Width, m_computedSize.Height), &xrect);

	return xrect;
#endif
}

LDraw::RectD UIElement::GetScreenBounds()
{
	ASSERT(m_pOwnerWindow);

	__release<LDraw::Matrix3f> transform = GetParentToElementTransformMatrix();
	UIElement* p = dynamic_cast<UIElement*>(GetRParent());
	while (p != m_pOwnerWindow->m_Content)
	{
		transform = *transform * *p->GetParentToElementTransformMatrix();
		p = dynamic_cast<UIElement*>(p->GetRParent());
	}

#if 0	// TODO
	transform = *transform * *LDraw::Matrix3f::GetTranslate(-m_pOwnerWindow->m_expandedBBox.X, -m_pOwnerWindow->m_expandedBBox.Y);
#endif

	LDraw::RectD wrect;
	m_pOwnerWindow->m_pSite->GetLogicalWindowRect(&wrect);
	transform = *transform * *LDraw::Matrix3f::GetTranslate(wrect.X, wrect.Y);

	LDraw::RectD xrect;
//	GetTransformRectBoundingBox(transform, m_expandedBBox, &xrect);
	LDraw::GetTransformRectBoundingBox(transform, LDraw::RectD(0, 0, m_computedSize.Width, m_computedSize.Height), &xrect);

	return xrect;
}

unsigned int GetLevel(Visual* pVisual)
{
	unsigned int level = 0;
	Visual* pParent = pVisual->GetRParent();
	while (pParent)
	{
		level++;
		pParent = pParent->GetRParent();
	}

	return level;
}

LayoutManager::LayoutManager()
{
	m_windowList = NULL;
}

void PresentationSource::MeasureAll()
{
//	std::list<VisualPair>::iterator it = m_measureList.begin();
	while (!m_measureList.empty())
	{
		VisualPair p = m_measureList.front();//*it;
		m_measureList.pop_front();

		//if (!p.pVisual->m_bMeasureValid)
		{
			VERIFY(p.pVisual->m_bInMeasureList);
			p.pVisual->m_bInMeasureList = false;
			VERIFY(p.pVisual->m_availSize.Width != -1);	// Measure must have been called at least once before to give it an initial availSize
			p.pVisual->Measure(p.pVisual->m_availSize);

		//	TRACE("Measure: %s\n", typeid(p.pVisual).raw_name());
		//	p.pVisual->Arrange(p.pVisual->m_computedSize);
	//		p.pVisual->Arrange(p.pVisual->m_desiredSize);
		}
	//	p.pVisual->Invalidate();
	}
//	m_measureList.clear();

	while (!m_arrangeList.empty())
	{
		VisualPair p = m_arrangeList.front();//*it;
		m_arrangeList.pop_front();
		VERIFY(p.pVisual->m_bInArrangeList);
		p.pVisual->m_bInArrangeList = false;

		if (p.pVisual->GetRParent() == NULL)
		{
//			MessageBeep(-1);
		}

		if (!p.pVisual->m_bArrangeValid)
		{
			// TODO, call OnArrange instead

			if (p.pVisual->GetRParent() == NULL)	// ??
			{
//				MessageBeep(-1);
			//	VERIFY(0);
#if 0
				ASSERT(dynamic_cast<WindowBase*>(p.pVisual);
				p.pVisual->Arrange(LDraw::RectD(LDraw::PointD(p.pVisual->m_computedLeft, p.pVisual->m_computedTop), p.pVisual->get_DesiredSize()));
				((NativeWindow*)((WindowBase*)p.pVisual)->m_pSite)->CreateRegions();
				p.pVisual->Invalidate();
#endif
			}
			else
			{
				p.pVisual->Arrange(LDraw::RectD(LDraw::PointD(p.pVisual->m_computedLeft, p.pVisual->m_computedTop), p.pVisual->get_ActualSize()));
				p.pVisual->SetPositionAndSize(p.pVisual->m_computedLeft, p.pVisual->m_computedTop, p.pVisual->m_computedSize.Width, p.pVisual->m_computedSize.Height);
			}

			// TODO, calculate visible regions etc.

		//	p.pVisual->Invalidate();

		//	p.pVisual->Arrange(p.pVisual->m_computedSize);
	//		p.pVisual->Arrange(p.pVisual->m_desiredSize);
		}
	//	p.pVisual->Invalidate();
	}
}

void LayoutManager::RemoveWindow(PresentationSource* window)
{
	m_windowList = InternalRemoveWindow(window);
}

PresentationSource* LayoutManager::InternalRemoveWindow(PresentationSource* window)
{
	if (m_windowList == NULL) return NULL;

	if (window == m_windowList)
	{
		window = window->m_pNextWindow;
		m_windowList->m_pNextWindow = NULL;
		return window;
	}
	else
	{
		PresentationSource* prev = m_windowList;
		PresentationSource* w = prev->m_pNextWindow;

		while (w)
		{
			if (w == window)
			{
				prev->m_pNextWindow = w->m_pNextWindow;
				return m_windowList;
			}

			prev = w;
			w = w->m_pNextWindow;
		}

		return m_windowList;
	}
}

void LayoutManager::RenderAll()
{
//	m_renderCritSec.Lock();

	PresentationSource* pWindow = m_windowList;
	m_windowList = NULL;

	//while (!m_windowList.empty())
	while (pWindow)
	{
		ASSERT(pWindow->m_bInvalidated);
		/*
		if (dynamic_cast<HwndSource*>(pWindow))
		{
			if (dynamic_cast<HwndSource*>(pWindow)->m_renderTargetUpdated)
			{
				ASSERT(!dynamic_cast<HwndSource*>(pWindow)->m_renderTargetUpdated);
			}
		}
		*/

		PresentationSource* pWindowNext = pWindow->m_pNextWindow;
		pWindow->m_pNextWindow = NULL;
		pWindow->m_bInvalidated = false;

	//	ASSERT(pWindowNext == NULL);

		if (false)
		{
			dynamic_cast<UI::HwndSource*>(pWindow)->CreateRegions();
		}

		//IUpdate* pWindow = m_windowList.front();
		//m_windowList.pop_front();

//		m_renderCritSec.Unlock();
		//if (!pWindow->m_invalidRegion.IsEmpty())
		{
			pWindow->Render();
			/*
			LDraw::RegionRect* pRect = pWindow->m_invalidRegion.m_hRgn->m_rect;
			while (pRect)
			{
				LDraw::RectD rect(pRect->m_bbox.left, pRect->m_bbox.top, pRect->m_bbox.Width(), pRect->m_bbox.Height());
				pWindow->Render(rect);

				pRect = pRect->m_next;
			}
			*/
		}
//		m_renderCritSec.Lock();

	//	ASSERT(pWindow->m_pNextWindow == pWindowNext);
		pWindow = pWindowNext;
	}

//	m_renderCritSec.Unlock();
}

void PresentationSource::AddMeasure(UIElement* pVisual, int level)
{
	list<VisualPair, __gc_allocator>::iterator it = m_measureList.begin();
	while (it != m_measureList.end())
	{
		VisualPair& other = *it;
		if (pVisual == other.pVisual)	// Already in the list
			return;

		if (level < other.level)	// Insert before this one
		{
			VisualPair pair;
			pair.level = level;
			pair.pVisual = pVisual;
			m_measureList.insert(it, pair);
			return;
		}

		++it;
	}

	// Insert at end
	VisualPair pair;
	pair.level = level;
	pair.pVisual = pVisual;
	m_measureList.push_back(pair);
}

void PresentationSource::AddArrange(UIElement* pVisual, int level)
{
	list<VisualPair, __gc_allocator>::iterator it = m_arrangeList.begin();
	while (it != m_arrangeList.end())
	{
		VisualPair& other = *it;
		if (pVisual == other.pVisual)	// Already in the list
			return;

		if (level < other.level)	// Insert before this one
		{
			VisualPair pair;
			pair.level = level;
			pair.pVisual = pVisual;
			m_arrangeList.insert(it, pair);
			return;
		}

		++it;
	}

	// Insert at end
	VisualPair pair;
	pair.level = level;
	pair.pVisual = pVisual;
	m_arrangeList.push_back(pair);
}

UIEXT __live_object_ptr<LayoutManager> pLayoutManager = new LayoutManager;

void UIElement::InvalidateMeasure()
{
	if (m_bMeasureValid)
//	if (!m_bInMeasureList/* && m_availSize.Width != -1*/)
	{
		int level = GetLevel(this);

		VERIFY(!m_bInMeasureList);
		m_bMeasureValid = false;
		m_bInMeasureList = true;
	//	pLayoutManager->AddMeasure(this, level);
		GetOwnerWindow()->m_pSite->AddMeasure(this, level);

		if (!m_bInArrangeList)	// hmm ???
		{
			ASSERT(!m_bInArrangeList);
			m_bArrangeValid = false;
			m_bInArrangeList = true;
			GetOwnerWindow()->m_pSite->AddArrange(this, level);
		}
	}
}

void UIElement::InvalidateArrange()
{

//	if (!m_bInArrangeList)
	if (m_bArrangeValid)
	{
		int level = GetLevel(this);

		if (!m_bInArrangeList)
		{
			VERIFY(!m_bInArrangeList);
			m_bArrangeValid = false;
			m_bInArrangeList = true;
			GetOwnerWindow()->m_pSite->AddArrange(this, level);
		}
	}
}

void UIElement::RenderChanged()
{
	RenderChanged(m_expandedBBox);
}

void UIElement::RenderChanged(const LDraw::RectD &area)
{
	InvalidateRect(area);
}

// rect is in local space
void UIElement::InvalidateRect(const LDraw::RectD &area)
{
		//m_bRenderValid = false;	// ??
	if (get_Visibility() != Visible)
		return;

#if 0
	UIElement* rparent = GetRParent();

	if (rparent)
	{
		// first clip it to our visible bounds
		LDraw::RectD crect;
		LDraw::RectD::Intersect(crect, area, m_expandedBBox);

		/*
		// convert from local space to parent space
		gmMatrix3 transform = GetLocalAnimatedMatrix();

		LDraw::RectD xrect;
		LDraw::GetTransformRectBoundingBox(transform, crect, &xrect);

		GetRParent()->InvalidateChildRect(xrect);

		*/

		rparent->InvalidateChildRect(crect, GetParentToElementTransformMatrix());
	}
#endif
}

#if 0
void UIElement::InvalidateChildRect(const LDraw::RectD& rect, LDraw::Matrix3f* transform)
{
	//m_bRenderValid = false;	// ??
	if (get_Visibility() != Visible)
		return;

	__release<LDraw::Matrix3f> transform2 = *transform * *GetParentToElementTransformMatrix();

	UIElement* rparent = GetRParent();
	if (rparent)
	{
	//	printf("InvalidateChildRect\n");
	//	return;

		rparent->InvalidateChildRect(rect, transform2);
	}
}
#endif

#if 0
void UIElement::InvalidateRect(CRect* rect)
{
	if (m_pOwnerWindow)
	{
#if _WINDOWS
		if (m_pOwnerWindow->GetHwnd())
		{
			::InvalidateRect(m_pOwnerWindow->GetHwnd(), NULL, TRUE);
		}
#else
		if (m_pOwnerWindow->m_pWindow)
		{
			m_pOwnerWindow->Invalidate();
		}
#endif
	}
}
#endif

bool UIElement::Focus()
{
	// TODO improve
	if (get_IsEnabled() && get_Focusable())
	{
		GetOwnerWindow()->m_pElementFocus = this;
		return true;
	}

	return false;
}

UIElement* UIElement::FindName(StringW* name)
{
	if (*get_Name() == *name)
	{
		return this;
	}

	return FindChildByName(name);
}

UIElement* UIElement::FindChildByName(StringW* name)
{
	int ncount = get_VisualChildrenCount();//rchildList()->get_Size();

	for (int i = 0; i < ncount; i++)
	{
		UIElement* pChild = dynamic_cast<UIElement*>(GetVisualChild(i));
		UIElement* p2 = pChild->FindName(name);
		if (p2)
		{
			return p2;
		}
	}

	return NULL;
}

Visual* Visual::FindByType(ClassType* pType)
{
	if (GetType()->IsDerivedFrom(pType))
		return this;

	int ncount = get_VisualChildrenCount();//rchildList()->get_Size();

	for (int i = 0; i < ncount; i++)
	{
		Visual* pChild = GetVisualChild(i);
		Visual* p2 = pChild->FindByType(pType);
		if (p2)
		{
			return p2;
		}
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////
// TextString

DependencyProperty* TextString::s_TextFillProperty = RegisterProperty(WSTR("TextFill"), typeid(Brush), typeid(TextString), (Brush*)1, PropertyMetaData(ChildInherits));

TextString::TextString()
{
	if (s_TextFillProperty->m_defaultValue == (Brush*)1)
	{
		s_TextFillProperty->m_defaultValue = new SolidColorBrush(Color::FromRgb(0,0,0));
	}
//	SetClipMode(false);
	m_string = NULL;
}

TextString::TextString(StringW* str)
{
	if (s_TextFillProperty->m_defaultValue == (Brush*)1)
	{
		s_TextFillProperty->m_defaultValue = new SolidColorBrush(Color::FromRgb(0,0,0));
	}

//	SetClipMode(false);

//	m_availSizeDontCare = true;
	m_string = str;
}

TextString::~TextString()
{
}

Brush* TextString::get_TextFill()
{
	return dynamic_cast<Brush*>(GetValue(s_TextFillProperty));
}

void TextString::set_TextFill(Brush* newVal)
{
	SetValue(s_TextFillProperty, newVal);
}

void TextString::set_TextContent(StringW* text)
{
//	printf("TextString::put_TextContent()\n");
	m_string = text;
	InvalidateMeasure();
}

StringW* TextString::get_TextContent() const
{
	return m_string;
}

void TextString::OnRender(Graphics* pGraphics)
{
	if (m_string)
	{
	//	pGraphics->DrawString(m_string.c_str(), m_string.length(), m_font, LDraw::PointF(0+1, 1), &LDraw::SolidBrush(LDraw::Color::Black));
		__release<LDraw::Brush> FillBrush = get_TextFill()->CreateBrush(this, 1, 1);
	//	pGraphics->DrawString(m_string.c_str(), m_string.length(), GetFont(), LDraw::PointF(0, 0), pFillBrush);

		pGraphics->DrawString(m_string, Control::GetFont(this), LDraw::RectF(0, 0, m_computedSize.Width, m_computedSize.Height), FillBrush);
	}
}

LDraw::SizeD TextString::MeasureOverride(LDraw::SizeD /*availSize*/)
{
//	printf("TextString::OnMeasure()\n");

	if (m_string)
	{
		LDraw::Font* font = Control::GetFont(this);

		double width = LDraw::Graphics2D::MeasureString(m_string->c_str(), m_string->Length(), font, LDraw::SmoothingModeNone);
		double height = font->GetSize();

		return LDraw::SizeD(width, height);
	}
	else
	{
		return LDraw::SizeD(0, 0);
	}
}

//LDraw::Font* g_pFont;

// static
LDraw::Font* Control::GetFont(DependencyObject* object)
{
	LDraw::FontFamily* fontFamily = GetFontFamily(object)->GetFamily();
	double fontSize = GetFontSize(object);

	//double fontSize2 = fontSize;

	FontWeights::FontWeight fontWeight = GetFontWeight(object);
	FontStyles::FontStyle fontStyle = GetFontStyle(object);

	uint16 style = 0;
	if (fontWeight >= 500) style |= 1;
	if (fontStyle == FontStyles::Italic || fontStyle == FontStyles::Oblique) style |= 2;

	LDraw::Font* font = object->m_font;
	if (font != NULL)
	{
		if (font->GetSize() != (float)fontSize || font->GetStyle() != style || font->GetFamily()->GetName() != fontFamily->GetName())
		{
			object->m_font = NULL;
		}
	}

	if (object->m_font == NULL)
	{
		DependencyObject* parent = object->GetDependencyParent();

		if (parent &&
			GetFontSize(parent) == fontSize &&
			GetFontWeight(parent) == fontWeight &&
			GetFontStyle(parent) == fontStyle &&
			GetFontFamily(parent)->GetFamily() == fontFamily)	// TODO ??
		{
			object->m_font = GetFont(parent);
		}
		else
		{
			/*
			if (g_pFont)
			{
				object->m_font = g_pFont;
			}
			else
			*/
			{
				double fontSize2 = fontSize * (pixelsPerInch / 96);
				object->m_font = new LDraw::Font(fontFamily, fontSize2, style);
				object->m_font->m_size = fontSize;

			//	g_pFont = object->m_font;
			}
		}
	}

	return object->m_font;
}

void UIElement::SetPosition(double x, double y)
{
	ASSERT(0);
#if 0

	ASSERT(this != GetRParent()->get_VisualTree());

	{
		Visual* p = this;
		while (p)
		{
			if (p->m_bInPosition)
				return;

			p = p->GetRParent();
		}
	}

	m_bInPosition = true;

	Visual* window = this;

	Visual* window2 = window;

//	LDraw::BBox bbox0;
//	window->m_visibleRegion->GetRegionBox(&bbox0);

	if (window->GetOwnerWindow() == NULL)
	{
		ASSERT(0);
		//window->SetLayoutOffset(x/*Canvas::GetLeft(window)->get_Value()*/, y/*Canvas::GetTop(window)->get_Value()*/);
		return;
	}

	LDraw::RectD bounds0 = window->GetWindowToElementBounds();

	// Move the window
	window->GetOwnerWindow()->m_pSite->InvalidateRegion(window->m_visibleWithChildrenRegion);
//window->/*get_VisualTree()->*/InvalidateRender();

	{
		{
			m_bRenderValid = false;

			Visual* p = GetRParent();
			while (p)
			{
				p->m_bRenderValid = false;
				/*
				if (p->m_Filter)
				{
					Visual* v = p->m_Filter;
					while (v != p)
					{
						v->m_bRenderValid = false;
						v = v->GetRParent();
					}

				//	p->m_Filter->m_bRenderValid = false;
				}
				*/
				p = p->GetRParent();
			}
		}

		if (GetOwnerWindow())
		{
			Visual* p = GetRParent();
			while (p)
			{
				if (!p->m_bDrawsOutsideOpaqueRegion)
				{
					break;
				}

				p = p->GetRParent();
			}

			ASSERT(p);

			if (!p->m_bRedraw)
			{
				p->m_bRedraw = true;

				p->m_redrawNext = GetOwnerWindow()->m_pSite->m_redrawList;
				GetOwnerWindow()->m_pSite->m_redrawList = p;
			}
			else
			{
				Visual* p2 = GetOwnerWindow()->m_pSite->m_redrawList;
				while (p2)
				{
					if (p == p2)
						break;
					p2 = p2->m_redrawNext;
				}

				ASSERT(p2 != NULL);
			}

			//get_OwnerWindow()->m_pSite->InvalidateRegion(m_visibleRegion);
		}
	}

	/*
	Canvas::SetLeft(window, new Length(Canvas::GetLeft(window)->get_Value() + dx));
	Canvas::SetTop(window, new Length(Canvas::GetTop(window)->get_Value() + dy));
	*/

#if 0	// TODO, had this
	window->SetLayoutOffset(x/*Canvas::GetLeft(window)->get_Value()*/, y/*Canvas::GetTop(window)->get_Value()*/);
#endif
	ASSERT(0);
#if 0
	window->Arrange(LDraw::RectD(x, y, window->get_ActualSize().Width, window->get_ActualSize().Height));
#endif

	window->m_windowToElementTransform = new LDraw::Matrix3f(window->GetRParent()->GetWindowToElementTransformMatrix()->m_matrix);
	if (window->GetRParent()->m_childrenTransformMatrix)
	{
		window->m_windowToElementTransform->m_matrix = window->GetRParent()->m_childrenTransformMatrix->m_matrix * window->m_windowToElementTransform->m_matrix;
	}

	window->m_windowToElementTransform->m_matrix = window->GetParentToElementTransformMatrix()->m_matrix * window->m_windowToElementTransform->m_matrix;

//	LDraw::BBox bbox1 = bbox0;
//	bbox1.Offset(dx, dy);
	LDraw::RectD bounds1 = window->GetWindowToElementBounds();

	//window->m_visibleRegion->GetRegionBox(&bbox0);

	{
		Graphics* graphics = new Graphics(new LDraw::GraphicsO);
		graphics->m_p->SetTransform(window->GetWindowToElementTransformMatrix());
		window->CreateOpaqueRegionNoTransform(graphics);
	}

	Visual* parent = window->GetRParent();

	while (parent)
	{
		list<Visual*> recalclist;

		// All the previous siblings that intersects
		{
			int i = 0;
			while (true)
			{
				ASSERT(i < parent->get_VisualChildrenCount());

				Visual* child = parent->GetVisualChild(i);

				if (child == window)
				{
					break;
				}

				LDraw::RectD childbounds = child->GetWindowToElementBounds();

				//if (child->m_visibleRegion->expandedBBoxParent.IntersectsWith(window->m_expandedBBoxParent))
				if (childbounds.IntersectsWith(bounds0) ||
					childbounds.IntersectsWith(bounds1))
				{
					child->m_bRegionValid = false;
					recalclist.push_front(child);
				}

				i++;
			}
		}

		if (window2 == window)
		{
			window->m_bRegionValid = false;
			recalclist.push_front(window);
		}

		/*
		// All the previous siblings that intersects must be recalculated
		{
			int i = 0;

			while (true)
			{
				UIElement* child = (*parent->get_rchildList())[i];

				if (child == window)
				{
					break;
				}

				if (child->m_expandedBBoxParent.IntersectsWith(window->m_expandedBBoxParent))
				{
					if (child->m_bRegionValid)
					{
						child->m_bRegionValid = false;
						recalclist.push_back(child);
					}
				}

				i++;
			}
		}
		*/

		{
			/*
			__release<LDraw::Matrix3f> parentTransform = new LDraw::Matrix3f(LDraw::Matrix3f::GetIdentity()->m_matrix);
			UIElement* p = parent;
			while (p)
			{
				parentTransform->m_matrix = parentTransform->m_matrix * p->GetParentToElementTransformMatrix()->m_matrix;

				p = p->GetRParent();
			}
			*/
			__release<LDraw::Matrix3f> parentTransform = parent->GetWindowToElementTransformMatrix();

			//NativeWindow* pFrame = dynamic_cast<NativeWindow*>(get_OwnerWindow()->m_pSite);
			Graphics* graphics = new Graphics(new LDraw::GraphicsO/*pFrame->m_pGraphicsO*/);

			/*
			pFrame->m_pClientVisual->CreateOpaqueRegion(graphics);	// TODO
			*/

			graphics->PushTransform();
			graphics->m_p->SetTransform(parentTransform);

			parent->CreateOpaqueRegion2NoTransform(graphics);

			if (parent == parent->GetRParent()->get_VisualTree())
			{
				parent->GetRParent()->m_opaqueRegion = parent->m_opaqueRegion;
				parent->GetRParent()->m_bDrawsOutsideOpaqueRegion = parent->m_bDrawsOutsideOpaqueRegion;
			}
			//ASSERT(parent != parent->GetRParent()->get_VisualTree());

			{
				// Initialize the parent visible region
				{
				// Initialize the visible region to the element's bounds
					/*
				{
					LDraw::vector2f xpt = graphics->GetTransform()->Transform(LDraw::PointF(parent->m_expandedBBox.X, parent->m_expandedBBox.Y));
					LDraw::RectI rect(xpt[0], xpt[1], parent->m_expandedBBox.Width, parent->m_expandedBBox.Height);
					parent->m_visibleRegion = new LDraw::Region(rect);
				}
				*/

				}
				parent->m_visibleRegion = parent->m_visibleWithChildrenRegion;
				parent->m_bRenderValid = false;

				// And exclude all the children that are in front of the moved window
				{
					int i = 0;
					while (true)
					{
						Visual* child = parent->GetVisualChild(i);

						i++;

						if (child == window)
							break;
					}

					while (i < parent->get_VisualChildrenCount())
					{
						Visual* child = parent->GetVisualChild(i);

						ASSERT(child->m_opaqueRegion);
						if (parent->m_visibleRegion->m_refcount > 1) parent->m_visibleRegion = parent->m_visibleRegion->Clone();
						parent->m_visibleRegion->Exclude(child->m_opaqueRegion);

						i++;
					}
				}
			}

			// Recalc the regions of the siblings that are behind the moved window and which intersected the moved window
			// We also update the visible region of the parent as well
			list<Visual*>::iterator it = recalclist.begin();
			while (it != recalclist.end())
			{
				Visual* element = *it;

				element->m_bRenderValid = false;
				InvalidateRenderChildren(element);

				element->m_bRegionValid = true;

				graphics->PushTransform();
			//	graphics->MultiplyTransform(element->GetParentToElementTransformMatrix());
				graphics->m_p->SetTransform(element->m_windowToElementTransform);

				// Initialize the visible region to the element's bounds
				/*
				{
					LDraw::vector2f xpt = graphics->GetTransform()->Transform(LDraw::PointF(element->m_expandedBBox.X, element->m_expandedBBox.Y));
					LDraw::RectI rect(xpt[0], xpt[1], element->m_expandedBBox.Width, element->m_expandedBBox.Height);
					element->m_visibleRegion = new LDraw::Region(rect);
				}
				*/
				element->m_visibleRegion = new LDraw::Region(element->m_expandedBBox, graphics->GetTransform()->m_matrix, 10, true);
				element->m_bRenderValid = false;

				element->m_visibleRegion->Intersect(parent->m_visibleRegion);

				element->m_visibleWithChildrenRegion = element->m_visibleRegion;

				ASSERT(element->m_opaqueRegion);
				if (parent->m_visibleRegion->m_refcount > 1) parent->m_visibleRegion = parent->m_visibleRegion->Clone();
				parent->m_visibleRegion->Exclude(element->m_opaqueRegion);

				graphics->PopTransform();

				element->CreateLayerStuff(graphics);

				++it;
			}

			graphics->PopTransform();
		}

		/*
		{
			NativeWindow* pFrame = dynamic_cast<NativeWindow*>(get_OwnerWindow()->m_pSite);
			//pFrame->CreateRegions();

			Graphics* graphics = new Graphics(pFrame->m_pGraphicsO);

			pFrame->m_pClientVisual->CreateOpaqueRegion(graphics);



			pFrame->m_pClientVisual->m_visibleRegion = new LDraw::Region(LDraw::RectI(0, 0, pFrame->m_pClientVisual->m_expandedBBox.Width, pFrame->m_pClientVisual->m_expandedBBox.Height));	// infinite //m_pClientVisual->OnGetRegion(graphics->GetTransform());
			pFrame->m_pClientVisual->m_visibleWithChildrenRegion = new LDraw::Region(LDraw::RectI(0, 0, pFrame->m_pClientVisual->m_expandedBBox.Width, pFrame->m_pClientVisual->m_expandedBBox.Height));	// infinite //m_pClientVisual->OnGetRegion(graphics->GetTransform());
			pFrame->m_pClientVisual->CreateLayerStuff(graphics);
		}
		*/

	//	InvalidateRenderChildren(window);

		if (!parent->m_bDrawsOutsideOpaqueRegion)
			break;

		window = parent;
		parent = parent->GetRParent();
	}

	window2->GetOwnerWindow()->m_pSite->InvalidateRegion(window2->m_visibleWithChildrenRegion);
	//window2->/*get_VisualTree()->*/InvalidateRender();

	m_bInPosition = false;
#endif
}

void UIElement::SetPositionAndSize(double x, double y, double width, double height)
{
#if 0
	TRACE("SetPositionAndSize\n");

	m_bRenderValid = false;

	Visual* p = GetRParent();
	while (p)
	{
		p->m_bRenderValid = false;
		/*
		if (p->m_Filter)
		{
			UIElement* v = p->m_Filter;
			while (v != p)
			{
				v->m_bRenderValid = false;
				v = v->GetRParent();
			}

		//	p->m_Filter->m_bRenderValid = false;
		}
		*/
		p = p->GetRParent();
	}

	if (GetOwnerWindow())
	{
		Visual* p = this;
		while (p)
		{
			if (!p->m_bDrawsOutsideOpaqueRegion)
			{
				break;
			}

			p = p->GetRParent();
		}

		if (p == NULL)
		{
			return;	// Means that the window hasn't been laid out yet
		}

		ASSERT(p);

		// If the element isn't already set to redraw, add it to a redraw list
		if (!p->m_bRedraw)
		{
			// If there's already a parent that's in the renderlist, don't add us as well
			Visual* p2 = p->GetRParent();
			while (p2)
			{
				if (p2->m_bRedraw) break;
				p2 = p2->GetRParent();
			}

			if (p2 == NULL)
			{
				p->m_bRedraw = true;

#ifdef _DEBUG
				{
					// Verify that it's not already in the list
					Visual* redrawList = GetOwnerWindow()->m_pSite->m_redrawList;
					Visual* p2 = redrawList;
					while (p2)
					{
						if (p == p2)
							break;
						p2 = p2->m_redrawNext;
					}

					ASSERT(p2 == NULL);
				}
#endif

				p->m_redrawNext = GetOwnerWindow()->m_pSite->m_redrawList;
				GetOwnerWindow()->m_pSite->m_redrawList = p;
			}
		}
		else
		{
#ifdef _DEBUG
			// Verify that it's in the list
			Visual* redrawList = GetOwnerWindow()->m_pSite->m_redrawList;
			Visual* p2 = redrawList;
			while (p2)
			{
				if (p == p2)
					break;
				p2 = p2->m_redrawNext;
			}

			ASSERT(p2 != NULL);
#endif
		}

		GetOwnerWindow()->m_pSite->InvalidateRegion(m_visibleRegion);
	}
	else
	{
	//	ASSERT(0);
#if 0
		WindowBase* pWindow = dynamic_cast<WindowBase*>(this);
		if (pWindow)
		{
			if (pWindow->m_pSite)
			{
				pWindow->m_bRedraw = true;
				pWindow->m_pSite->m_redrawList = pWindow;
				pWindow->m_pSite->InvalidateRegion(m_visibleRegion);
			}
		}
#endif
	}
#endif
//	GetOwnerWindow()->m_pSite->InvalidateRegion(NULL);
	InvalidateRender();
//	Arrange(LDraw::RectD(x, y, width, height));
	return;

	{
		Visual* p = this;
		while (p)
		{
			if (p->m_bInPosition)
				return;

			p = p->GetRParent();
		}
	}

	m_bInPosition = true;

	Visual* window = this;

	Visual* window2 = window;

//	LDraw::BBox bbox0;
//	window->m_visibleRegion->GetRegionBox(&bbox0);
	LDraw::RectD bounds0 = window->GetWindowToElementBounds();

	// Move the window
	VisualContentSource* ownerWindow = window->GetOwnerWindow();
	ASSERT(ownerWindow);
//	if (ownerWindow == NULL)
//		 ownerWindow = dynamic_cast<WindowBase*>(window);

	ownerWindow->m_pSite->InvalidateRegion(window->m_visibleWithChildrenRegion);
	//window->/*get_VisualTree()->*/InvalidateRender();

	{
		{
			m_bRenderValid = false;

			Visual* p = GetRParent();
			while (p)
			{
				p->m_bRenderValid = false;
				/*
				if (p->m_Filter)
				{
					UIElement* v = p->m_Filter;
					while (v != p)
					{
						v->m_bRenderValid = false;
						v = v->GetRParent();
					}

				//	p->m_Filter->m_bRenderValid = false;
				}
				*/
				p = p->GetRParent();
			}
		}

		if (GetOwnerWindow())
		{
			Visual* p = GetRParent();
			while (p)
			{
				if (!p->m_bDrawsOutsideOpaqueRegion)
				{
					break;
				}

				if (p->GetRParent() == NULL) break;	// TODO remove

				p = p->GetRParent();
			}

			ASSERT(p);

			if (!p->m_bRedraw)
			{
				p->m_bRedraw = true;

				p->m_redrawNext = GetOwnerWindow()->m_redrawList;
				GetOwnerWindow()->m_redrawList = p;
			}

			//get_OwnerWindow()->m_pSite->InvalidateRegion(m_visibleRegion);
		}
	}

	/*
	Canvas::SetLeft(window, new Length(Canvas::GetLeft(window)->get_Value() + dx));
	Canvas::SetTop(window, new Length(Canvas::GetTop(window)->get_Value() + dy));
	*/

	dynamic_cast<UIElement*>(window)->Arrange(LDraw::RectD(x, y, width, height));
	//window->SetLayoutOffset(x/*Canvas::GetLeft(window)->get_Value()*/, y/*Canvas::GetTop(window)->get_Value()*/);

	window->m_windowToElementTransform = new LDraw::Matrix3f(window->GetParentToElementTransformMatrix()->m_matrix * window->GetRParent()->GetWindowToElementTransformMatrix()->m_matrix);

//	LDraw::BBox bbox1 = bbox0;
//	bbox1.Offset(dx, dy);
	LDraw::RectD bounds1 = window->GetWindowToElementBounds();

	//window->m_visibleRegion->GetRegionBox(&bbox0);

	{
		ASSERT(0);
		Graphics* graphics = NULL;//new Graphics(new LDraw::GraphicsO);
		graphics->m_p->SetTransform(window->GetWindowToElementTransformMatrix());
		window->CreateOpaqueRegionNoTransform(graphics);
	}

	Visual* parent = window->GetRParent();

	while (parent)
	{
		list<Visual*> recalclist;

		// All the previous siblings that intersects
		{
			int i = 0;
			while (true)
			{
#if 0
				if (window == parent->get_VisualTree())
				{
					ASSERT(parent->get_VisualChildrenCount() == 0);
					break;
				}
#endif

				ASSERT(i < parent->get_VisualChildrenCount());

				Visual* child = parent->GetVisualChild(i);

				if (child == window)
				{
					break;
				}

				LDraw::RectD childbounds = child->GetWindowToElementBounds();

				//if (child->m_visibleRegion->expandedBBoxParent.IntersectsWith(window->m_expandedBBoxParent))
				if (childbounds.IntersectsWith(bounds0) ||
					childbounds.IntersectsWith(bounds1))
				{
					child->m_bRegionValid = false;
					recalclist.push_front(child);
				}

				i++;
			}
		}

		if (window2 == window)
		{
			window->m_bRegionValid = false;
			recalclist.push_front(window);
		}

		/*
		// All the previous siblings that intersects must be recalculated
		{
			int i = 0;

			while (true)
			{
				UIElement* child = (*parent->get_rchildList())[i];

				if (child == window)
				{
					break;
				}

				if (child->m_expandedBBoxParent.IntersectsWith(window->m_expandedBBoxParent))
				{
					if (child->m_bRegionValid)
					{
						child->m_bRegionValid = false;
						recalclist.push_back(child);
					}
				}

				i++;
			}
		}
		*/

		{
			/*
			__release<LDraw::Matrix3f> parentTransform = new LDraw::Matrix3f(LDraw::Matrix3f::GetIdentity()->m_matrix);
			UIElement* p = parent;
			while (p)
			{
				parentTransform->m_matrix = parentTransform->m_matrix * p->GetParentToElementTransformMatrix()->m_matrix;

				p = p->GetRParent();
			}
			*/
			__release<LDraw::Matrix3f> parentTransform = parent->GetWindowToElementTransformMatrix();

			//NativeWindow* pFrame = dynamic_cast<NativeWindow*>(get_OwnerWindow()->m_pSite);
			ASSERT(0);
			Graphics* graphics = NULL;//new Graphics(new LDraw::GraphicsO/*pFrame->m_pGraphicsO*/);

			/*
			pFrame->m_pClientVisual->CreateOpaqueRegion(graphics);	// TODO
			*/

			graphics->PushTransform();
			graphics->m_p->SetTransform(parentTransform);

			parent->CreateOpaqueRegion2NoTransform(graphics);

			{
				// Initialize the parent visible region
				parent->m_visibleRegion = parent->m_visibleWithChildrenRegion;
				parent->m_bRenderValid = false;

				// And exclude all the children that are in front of the moved window
				{
					int i = 0;
					while (true)
					{
#if 0
						if (window == parent->get_VisualTree())
						{
							ASSERT(parent->get_VisualChildrenCount() == 0);
						//	i++;
							break;
						}
#endif

						Visual* child = parent->GetVisualChild(i);

						i++;

						if (child == window)
							break;
					}

					while (i < parent->get_VisualChildrenCount())
					{
						Visual* child = parent->GetVisualChild(i);

						ASSERT(child->m_opaqueRegion);
						if (parent->m_visibleRegion->m_refcount > 1) parent->m_visibleRegion = parent->m_visibleRegion->Clone();
						parent->m_visibleRegion->Exclude(child->m_opaqueRegion);

						i++;
					}
				}
			}

			// Recalc the regions of the siblings that are behind the moved window and which intersected the moved window
			// We also update the visible region of the parent as well
			list<Visual*>::iterator it = recalclist.begin();
			while (it != recalclist.end())
			{
				Visual* element = *it;

				element->m_bRenderValid = false;
				InvalidateRenderChildren(element);

				element->m_bRegionValid = true;

				graphics->PushTransform();
				graphics->MultiplyTransform(element->GetParentToElementTransformMatrix());

				// Initialize the visible region to the element's bounds
				{
					LDraw::vector2f xpt = graphics->GetTransform()->Transform(LDraw::PointF(element->m_expandedBBox.X, element->m_expandedBBox.Y));
					LDraw::RectI rect(xpt[0], xpt[1], element->m_expandedBBox.Width, element->m_expandedBBox.Height);
					element->m_visibleRegion = new LDraw::Region(rect);
					element->m_bRenderValid = false;
				}

				element->m_visibleRegion->Intersect(parent->m_visibleRegion);

				element->m_visibleWithChildrenRegion = element->m_visibleRegion;

				ASSERT(element->m_opaqueRegion);
				if (parent->m_visibleRegion->m_refcount > 1) parent->m_visibleRegion = parent->m_visibleRegion->Clone();
				parent->m_visibleRegion->Exclude(element->m_opaqueRegion);

				graphics->PopTransform();

				element->CreateLayerStuff(graphics);

				++it;
			}

			graphics->PopTransform();
		}

		/*
		{
			NativeWindow* pFrame = dynamic_cast<NativeWindow*>(get_OwnerWindow()->m_pSite);
			//pFrame->CreateRegions();

			Graphics* graphics = new Graphics(pFrame->m_pGraphicsO);

			pFrame->m_pClientVisual->CreateOpaqueRegion(graphics);



			pFrame->m_pClientVisual->m_visibleRegion = new LDraw::Region(LDraw::RectI(0, 0, pFrame->m_pClientVisual->m_expandedBBox.Width, pFrame->m_pClientVisual->m_expandedBBox.Height));	// infinite //m_pClientVisual->OnGetRegion(graphics->GetTransform());
			pFrame->m_pClientVisual->m_visibleWithChildrenRegion = new LDraw::Region(LDraw::RectI(0, 0, pFrame->m_pClientVisual->m_expandedBBox.Width, pFrame->m_pClientVisual->m_expandedBBox.Height));	// infinite //m_pClientVisual->OnGetRegion(graphics->GetTransform());
			pFrame->m_pClientVisual->CreateLayerStuff(graphics);
		}
		*/

	//	InvalidateRenderChildren(window);

		if (!parent->m_bDrawsOutsideOpaqueRegion)
			break;

		window = parent;
		parent = parent->GetRParent();
	}

	window2->GetOwnerWindow()->m_pSite->InvalidateRegion(window2->m_visibleWithChildrenRegion);

	m_bInPosition = false;
}

// IAnimatable

bool UIElement::HasAnimatedProperties()
{
	return m_animatedPropertiesCount > 0;
}

Object* UIElement::GetAnimationBaseValue(DependencyProperty* pProperty)
{
	return m_baseValues[pProperty->gindex];
}

Object* UIElement::ComputeAnimVal(DependencyProperty* pProperty)
{
	int index = pProperty->gindex;

	Object* curValue = m_baseValues[index];

	list<AnimationClock*, __gc_allocator>::iterator it = m_propertyClocks[index].begin();
	while (it != m_propertyClocks[index].end())
	{
		AnimationClock* clock = *it;

		Object* destValue = NULL;	// ??
		curValue = clock->GetCurrentValue(curValue, destValue);

		++it;
	}

	return curValue;
}

Object* UIElement::ComputeProperty(DependencyProperty* pProperty)
{
	int index = pProperty->gindex;

	//if (m_baseValues[pProperty->gindex] == UnsetValue)
		m_baseValues[index] = ComputeBaseVal(pProperty);

	return ComputeAnimVal(pProperty);
		/*
	Object* curValue = m_baseValues[index];

	list<AnimationClock*, __gc_allocator>::iterator it = m_propertyClocks[index].begin();
	while (it != m_propertyClocks[index].end())
	{
		AnimationClock* clock = *it;

		Object* destValue = NULL;	// ??
		curValue = clock->GetCurrentValue(curValue, destValue);

		++it;
	}

	return curValue;
	*/
	//return m_baseValues[pProperty->gindex];	// TODO
}

#if 0
Object* UIElement::ComputeBaseVal(DependencyProperty* pProperty)
{
	//DependencyObject* pParent;

	if (m_specifiedProperties[pProperty->gindex] != DependencyProperty::get_UnsetValue())	// Local value set
	{
		/*
		if (m_depCookies[pProperty->gindex] != NULL)
		{
			pParent = GetDependencyParent();

			pParent->RemoveDependant(pProperty, m_depCookies[pProperty->gindex]);
			m_depCookies[pProperty->gindex] = NULL;
		}
		*/

		return m_specifiedProperties[pProperty->gindex];
	}

	/*
	if (m_style)
	{
		Style::PropertyValue* propertyVal = m_style->m_depproperties[pProperty->gindex];
		if (propertyVal)
		{
			if (m_depCookies[pProperty->gindex] != NULL)
			{
				pParent = GetDependencyParent();

				pParent->RemoveDependant(pProperty, m_depCookies[pProperty->gindex]);
				m_depCookies[pProperty->gindex] = NULL;
			}

			return propertyVal->m_computedValue;
		}
	}
	*/

	/*
	if ((pProperty->m_metadata.m_flags & ChildInherits) && (pParent = GetDependencyParent()) != NULL)
	{
		if (m_depCookies[pProperty->gindex] == NULL)
			m_depCookies[pProperty->gindex] = pParent->AddDependant(pProperty, this);

		return pParent->ComputeProperty(pProperty);
	}
	else
	*/
	{
		return pProperty->m_defaultValue;
	}
}
#endif

void UIElement::ApplyAnimationClock(DependencyProperty* dp, AnimationClock* clock)
{
	ApplyAnimationClock(dp, clock, HandoffBehavior_SnapshotAndReplace);

#if 0

	if (m_computedProperties[dp->gindex] == UnsetValue)
	{
		m_baseValues[dp->gindex] = ComputeBaseVal(dp);
		m_computedProperties[dp->gindex] = m_baseValues[dp->gindex];
	}

	if (true)	// Composite
	{
		m_computedProperties[dp->gindex] = animation->GetCurrentValue(m_computedProperties[dp->gindex]);
	}
	else
	{
		m_computedProperties[dp->gindex] = animation->GetCurrentValue(m_baseValues[dp->gindex]);
	}

	OnPropertyChanged(dp);
#endif
}

/*
int UIElement::OnCurrentTimeInvalidated(Object* sender)
{
	return 0;
}
*/

void UIElement::ApplyAnimationClock(DependencyProperty* dp, AnimationClock* clock, HandoffBehavior handoffBehavior)
{
	if (dp == NULL) throw new Exception(WSTR("null pointer"));

	if (clock)
	{
		if (g_timeManager == NULL)
		{
			g_timeManager = new TimeManager;
		}

		if (m_animatedPropertiesCount == 0)
		{
			m_animated = g_timeManager->m_animatables.insert(g_timeManager->m_animatables.end(), this);
		}

		if (m_propertyClocks[dp->gindex].empty())
		{
			++m_animatedPropertiesCount;
		}

		if (handoffBehavior == HandoffBehavior_SnapshotAndReplace)
		{
			m_propertyClocks[dp->gindex].clear();
			m_propertyClocks[dp->gindex].push_back(clock);
		}
		else
		{
			m_propertyClocks[dp->gindex].push_back(clock);
		}

		g_timeManager->m_clocks.push_back(clock);

//		clock->CurrentTimeInvalidated.connect(std::bind1st(std::mem_fun1(&Animatable::OnCurrentTimeInvalidated), this));

//		clock->CurrentTimeInvalidated(clock);
	}
	else
	{
		if (!m_propertyClocks[dp->gindex].empty())
		{
			m_propertyClocks[dp->gindex].clear();
			--m_animatedPropertiesCount;

			if (m_animatedPropertiesCount == 0)
			{
				g_timeManager->m_animatables.erase(m_animated);
			}
		}
	}
}

void UIElement::BeginAnimation(DependencyProperty* dp, AnimationTimeline* timeline)
{
	BeginAnimation(dp, timeline, HandoffBehavior_SnapshotAndReplace);
}

void UIElement::BeginAnimation(DependencyProperty* dp, AnimationTimeline* timeline, HandoffBehavior handoffBehavior)
{
	if (dp == NULL) throw new Exception(WSTR("null pointer"));
	if (timeline == NULL) throw new Exception(WSTR("null pointer"));

	AnimationClock* clock = dynamic_cast<AnimationClock*>(timeline->CreateClock());

	ApplyAnimationClock(dp, clock, handoffBehavior);

	/*
	if (clock == NULL) throw exception("clock = NULL");

	if (m_propertyClocks[dp->gindex].empty())
	{
		++m_animatedPropertiesCount;
	}

	m_propertyClocks[property->gindex].clear();
	m_propertyClocks[property->gindex].push_back(clock);
	*/
}

}	// UI
}
