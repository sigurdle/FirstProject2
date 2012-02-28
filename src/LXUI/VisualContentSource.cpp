#include "stdafx.h"
#include "LXUI2.h"

#include "LXUIBoxWindow.h"

#if WIN32
#include "../OleDataObject.h"
#include "../Utils/IEnumfe.h"
#endif

//#include <stdlib.h>
#include <algorithm>

namespace System
{
namespace UI
{

VisualContentSource::VisualContentSource()
{
	m_pSite = NULL;

	m_bAlt = false;

//	m_lockUpdate = 0;

//	m_bInsideWindow = false;

//	m_bShowCursor = FALSE;
//	m_bShowCursor = TRUE;	// Fix, should blink with a timer

	m_pElementCapture = NULL;

	m_pHitElement = NULL;
	m_pElementHover = NULL;
	m_pElementActive = NULL;
	m_pElementFocus = NULL;

//	m_pOwnerWindow = this;	// ??

	{
#if 0
		Cursor* pCursor = new Cursor;
		Image* pImage = new Image(new FileImageSource(L"C:/arrow.png"));
		pCursor->put_Visual(pImage);
		put_Cursor(pCursor);
#else
#if WIN32
#if 0
		Cursor* pCursor = new Cursor(MSWindows::LoadCursorA(NULL, _IDC_ARROW));
		set_Cursor(pCursor);
#endif
#endif
#endif
	}
}

VisualContentSource::~VisualContentSource()
{
}

StringW* VisualContentSource::GetTitle()
{
	StringW* windowName = NULL;

	Window* pFrame = dynamic_cast<Window*>(GetVisualTree());
	if (pFrame)
	{
		windowName = dynamic_cast<StringW*>(pFrame->get_Title());
//		windowName = pFrame->get_Title()->ToString();
	}

	return windowName;
}

uint32 VisualContentSource::GetWindowStyle(uint32 windowStyle)
{
	windowStyle |= WS_OVERLAPPED;
	windowStyle |= WS_CAPTION;
	windowStyle |= WS_SYSMENU;
	windowStyle |= WS_THICKFRAME;
	windowStyle |= WS_MINIMIZEBOX;
	windowStyle |= WS_MAXIMIZEBOX;

	return windowStyle;
}

uint32 VisualContentSource::GetWindowAnimate()
{
	return 0;
}

void VisualContentSource::Close()
{
	if (m_Content)
	{
		ASSERT(m_Content->GetOwnerWindow() == this);
		m_Content->SetOwnerWindow(NULL);
		m_Content = NULL;
	}

	ASSERT(m_redrawList == NULL);

	/*
	// Clear the redrawList
	Visual* current = m_redrawList;
	while (current)
	{
		ASSERT(current->m_bRedraw);
		current->m_bRedraw = false;
		Visual* next = current->m_redrawNext;
		current->m_redrawNext = NULL;
		current = next;
	}
	m_redrawList = NULL;
	*/
}

void VisualContentSource::OnSized()
{
	// Clear the redrawList and add just the root visual
	Visual* current = m_redrawList;
	while (current)
	{
		ASSERT(current->m_bRedraw);
		current->m_bRedraw = false;
		Visual* next = current->m_redrawNext;
		current->m_redrawNext = NULL;
		current = next;
	}
	GetVisualTree()->m_bRedraw = true;
	m_redrawList = GetVisualTree();
}

void VisualContentSource::Redraw(Graphics* graphics)
{
	Visual* current = m_redrawList;
	while (current)
	{
		ASSERT(current->m_bRedraw);

		current->RenderNoTransform(graphics);

		current->m_bRedraw = false;

		Visual* next = current->m_redrawNext;
		current->m_redrawNext = NULL;

		current = next;
		m_redrawList = next;
	}
}

LDraw::SizeD VisualContentSource::Measure(LDraw::SizeD availSize)
{
	m_Content->Measure(availSize);
	return m_Content->get_DesiredSize();
}

LDraw::SizeD VisualContentSource::Arrange(LDraw::SizeD finalSize)
{
	m_Content->Arrange(LDraw::RectD(LDraw::PointD(0, 0), finalSize));
	return m_Content->get_ActualSize();
}

LDraw::Graphics3D* VisualContentSource::GetGraphics3D()
{
	return dynamic_cast<HwndSource*>(m_pSite)->m_pGraphics3D;
//	return m_pSite->m_pGraphics3D;
}

void VisualContentSource::SetSite(PresentationSource* pSite)
{
	m_pSite = pSite;
}

void VisualContentSource::OnActivate(bool bActive)
{
	BaseWindow* pWindow = dynamic_cast<BaseWindow*>(GetVisualTree());
	if (pWindow)
	{
		pWindow->set_IsActive(bActive);
	}

#if 0
	Event* evt = new Event;
	if (bActive)
	{
		evt->InitEvent(WSTR("activate"), true, true);
	}
	else
	{
		evt->InitEvent(WSTR("deactivate"), true, true);
	}
	m_Content->dispatchEvent(evt);
#endif
}

void VisualContentSource::AddStylusPlugin(IStylusPlugin* plugin)
{
	m_pSite->AddStylusPlugin(plugin);
}

UIElement* VisualContentSource::GetCapture() const
{
	return m_pElementCapture;
}

void VisualContentSource::SetCapture(UIElement* p)
{
	if (m_pSite)
	{
		m_pSite->SetCapture();
	}

	if (m_pElementCapture)
	{
		// TODO event "CaptureChanged"
	}

	m_pElementCapture = p;
}

void VisualContentSource::ReleaseCapture(UIElement* p)
{
	if (m_pElementCapture == p)
	{
		m_pElementCapture = NULL;
		if (m_pSite)
			m_pSite->ReleaseCapture();
	}
}

#if 0
LRESULT VisualContentSource::OnCaptureChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	HWND hwndNewCapture = (HWND) lParam;    // handle of window to gain mouse capture 

	if (m_pElementCapture != NULL)
	{
		//L"LostMouseCapture"
		//m_pElementCapture->

		m_pElementCapture = NULL;
	}

	return 0;
}
#endif

void VisualContentSource::OnMouseDown(UINT nFlags, LDraw::PointD screenpos, LDraw::PointD clientpos, int iButton, bool bDblClk)
{
//	m_startpt = clientpos;
	m_oldclientpos = clientpos;

	if (GetVisualTree())
	{
		clientpos.X += m_Content->m_expandedBBox.X;
		clientpos.Y += m_Content->m_expandedBBox.Y;

		Visual* pElement = NULL;

		if (m_pElementCapture)
			pElement = m_pElementCapture;
		else
			pElement = GetVisualTree()->HitTestElement(m_Content->GetParentToElementTransformMatrix(), LDraw::PointD(clientpos.X, clientpos.Y));

		if (pElement)
		{
			if (pElement->GetOwnerWindow() != this)
			{
				return;
			}
		}

		if (pElement == NULL)
		{
			pElement = GetVisualTree();
		}

		if (pElement)
		{
			m_pHitElement = pElement;

			IInputElement* eventTarget = dynamic_cast<IInputElement*>(pElement);//->m_eventTarget;
			ASSERT(eventTarget != NULL);
			if (eventTarget)
			{
				// TODO, support wrapping ?
				long msgtime = MSWindows::GetMessageTime();

				MouseButtonEventArgs* mouseArgs = new MouseButtonEventArgs(NULL, msgtime);
				mouseArgs->m_leftButton = (nFlags & MK_LBUTTON) == MK_LBUTTON;
				mouseArgs->m_rightButton = (nFlags & MK_RBUTTON) == MK_RBUTTON;
				mouseArgs->m_middleButton = (nFlags & MK_MBUTTON) == MK_MBUTTON;
				mouseArgs->m_screenX = screenpos.X;
				mouseArgs->m_screenY = screenpos.Y;
				mouseArgs->m_windowX = clientpos.X;
				mouseArgs->m_windowY = clientpos.Y;

				InputManager* inputManager = InputManager::get_Current();

				StagingAreaInputItem* stagingItem = new StagingAreaInputItem;
				stagingItem->m_input = mouseArgs;

				PreProcessInputEventArgs* preprocessArgs = new PreProcessInputEventArgs;
				preprocessArgs->m_inputManager = inputManager;
				preprocessArgs->m_stagingItem = stagingItem;	

				inputManager->PreProcessInput(inputManager/*??*/, preprocessArgs);
				//inputManager->PreNotifyInput(inputManager/*??*/, preprocessArgs);

				mouseArgs->set_RoutedEvent(Mouse::s_PreviewMouseDownEvent);
				eventTarget->RaiseEvent(mouseArgs);

				mouseArgs->set_RoutedEvent(Mouse::s_MouseDownEvent);
				eventTarget->RaiseEvent(mouseArgs);

				//inputManager->PostNotifyInput(inputManager/*??*/, preprocessArgs);
				//inputManager->PostProcessInput(inputManager/*??*/, preprocessArgs);

#if 0
				MouseEvent* mouseEvt = new MouseEvent;
				mouseEvt->InitMouseEvent(MouseEvent::mousedown, this, screenpos.X, screenpos.Y, nFlags & 1, (nFlags>>1)&1);
				mouseEvt->m_nclicks = bDblClk? 1: 0;

				bool doDefault = target->dispatchEvent(mouseEvt);
#endif
				bool doDefault = true;
				if (doDefault)
				{
#if 0
					if (m_pElementFocus)
					{
						Event* focusEvt = new Event;
						focusEvt->InitEvent(WSTR("killfocus"), true, false);
						m_pElementFocus->dispatchEvent(focusEvt);
						delete focusEvt;
					}

					m_pElementFocus = dynamic_cast<UIElement*>(m_pHitElement);

					if (m_pElementFocus)
					{
						Event* focusEvt = new Event;
						focusEvt->InitEvent(WSTR("getfocus"), true, false);
						m_pElementFocus->dispatchEvent(focusEvt);
						delete focusEvt;
					}
#endif
				}

			//	delete mouseEvt;
			}
		}
	}
}

__live_object_ptr<RoutedEvent> s_MouseMoveEvent = EventManager::RegisterRoutedEvent(WSTR("MouseMove"), RoutingStrategy_Bubble, typeid(int), typeid(Mouse));

void VisualContentSource::OnLostMouseCapture()
{
}

Visual* FindCommonAncestorOrSelf(Visual* v1, Visual* v2)
{
	if (v1 == NULL || v2 == NULL) throw new Exception(WSTR("null pointer"));

	if (v2->IsAncestorOf(v1))
	{
		return v2;
	}
	else
	{
		do
		{
			if (v1 == v2) return v1;

			if (v1->IsAncestorOf(v2))
			{
				return v1;
			}

			v1 = v1->GetRParent();
		}
		while (v1);
	}

	return NULL;
}

void VisualContentSource::OnMouseLeave(LDraw::PointD screenpos, LDraw::PointD clientpos)
{
	if (m_pElementHover)
	{
		UIElement* p = m_pElementHover;
		do
		{
			p->SetValue(UIElement::get_IsMouseOverProperty(), BoolObject::GetObject(false));
			p = dynamic_cast<UIElement*>(p->GetRParent());
		}
		while (p);

		m_pElementHover = NULL;
	}
}

void VisualContentSource::OnMouseMove(UINT nFlags, LDraw::PointD screenpos, LDraw::PointD clientpos)
{
	if (GetVisualTree())
	{
		clientpos.X += m_Content->m_expandedBBox.X;
		clientpos.Y += m_Content->m_expandedBBox.Y;

		if (m_pElementCapture == NULL)
		{
			Visual* pElement = NULL;

			/*
			if (m_pElementCapture)
			{
				pPElement = m_pElementCapture;
			}
			else
			*/
			if (true)//m_bInsideWindow)
			{
			//	TRACE("----------------------------\n");
				pElement = GetVisualTree()->HitTestElement(GetViewMatrix(), clientpos);

				if (pElement)
				{
					if (pElement->GetOwnerWindow() != this)
					{
						return;
					}
				}
			}

			if (pElement != m_pElementHover)
			{
				Visual* commonAncestor = NULL;

				if (m_pElementHover && pElement)
				{
					commonAncestor = FindCommonAncestorOrSelf(m_pElementHover, pElement);
				// Visual* ancestor = m_pElementHover->FindCommonVisualAncestor(pPElement);
				}

				if (m_pElementHover)	// mouseout on previous
				{
				// TODO, raise event

				// Set mouseover=false on previous down to common ancestor
					Visual* p = m_pElementHover;
					while (p != commonAncestor)
					{
						p->SetValue(UIElement::get_IsMouseOverProperty(), BoolObject::get_False());
						p = p->GetRParent();
					}
				}

				m_pElementHover = dynamic_cast<UIElement*>(pElement);

				if (m_pElementHover)	// mousein on new
				{
				// TODO, raise event

				// Set mouseover=true on new down to common ancestor
					Visual* p = m_pElementHover;
					while (p != commonAncestor)
					{
						p->SetValue(UIElement::get_IsMouseOverProperty(), BoolObject::get_True());
						p = p->GetRParent();
					}
				}
			}
		}

		if (m_pElementHover || m_pElementCapture)
		{
			if (true)
			{
				IInputElement* eventTarget;
				
				if (m_pElementCapture)
					eventTarget = dynamic_cast<IInputElement*>(m_pElementCapture);
				else
					eventTarget = dynamic_cast<IInputElement*>(m_pElementHover);

				// TODO, support wrapping ?
				long msgtime = MSWindows::GetMessageTime();

				MouseEventArgs* mouseArgs = new MouseEventArgs(NULL, msgtime);
				mouseArgs->m_screenX = screenpos.X;
				mouseArgs->m_screenY = screenpos.Y;
				mouseArgs->m_windowX = clientpos.X;
				mouseArgs->m_windowY = clientpos.Y;

				InputManager* inputManager = InputManager::get_Current();

				StagingAreaInputItem* stagingItem = new StagingAreaInputItem;
				stagingItem->m_input = mouseArgs;

				PreProcessInputEventArgs* preprocessArgs = new PreProcessInputEventArgs;
				preprocessArgs->m_inputManager = inputManager;
				preprocessArgs->m_stagingItem = stagingItem;	

				inputManager->PreProcessInput(inputManager/*??*/, preprocessArgs);
				//inputManager->PreNotifyInput(inputManager/*??*/, preprocessArgs);

				mouseArgs->set_RoutedEvent(Mouse::s_PreviewMouseMoveEvent);
				eventTarget->RaiseEvent(mouseArgs);

				mouseArgs->set_RoutedEvent(Mouse::s_MouseMoveEvent);
				eventTarget->RaiseEvent(mouseArgs);

				//inputManager->PostNotifyInput(inputManager/*??*/, preprocessArgs);
				//inputManager->PostProcessInput(inputManager/*??*/, preprocessArgs);
			}
			else
			{
#if 0
				MouseEvent* mouseevt = new MouseEvent;
			//	documentEvent->createEvent(WSTR("MouseEvents"), (ILDOMEvent**)&mouseevt);
				mouseevt->InitMouseEvent(MouseEvent::mousemove,
				//	VARIANT_TRUE,	// bubbles
				//	VARIANT_TRUE,	// cancelable
					this,	// viewArg
				//	0,		// detail
					screenpos.X, screenpos.Y,//,	// screen
					nFlags & 1,
					(nFlags>>1)&1
				/*	clientpos.x, clientpos.y, // client,
					(nFlags & MK_CONTROL)? VARIANT_TRUE: VARIANT_FALSE,
					(nFlags & MK_SHIFT)? VARIANT_TRUE: VARIANT_FALSE,
					(m_bAlt)? VARIANT_TRUE: VARIANT_FALSE,
					0,	// meta
					0,
					relatedTarget*/
					);

				EventTargetImpl* eventTarget;
				
				if (m_pElementCapture)
					eventTarget = dynamic_cast<EventTargetImpl*>(m_pElementCapture);
				else
					eventTarget = dynamic_cast<EventTargetImpl*>(m_pElementHover);

				if (eventTarget)
				{
					bool doDefault = eventTarget->dispatchEvent(mouseevt);
				}
				delete mouseevt;
#endif
			}
		}
	}

	m_oldclientpos = clientpos;
}

void VisualContentSource::OnMouseUp(UINT nFlags, LDraw::PointD screenpos, LDraw::PointD clientpos, int iButton)
{
	{

		clientpos.X += m_Content->m_expandedBBox.X;
		clientpos.Y += m_Content->m_expandedBBox.Y;

		if (true)
		{
			{
				/*
				if (m_pElementCapture)
				{
					MessageBeep(-1);
					// m_pElementCapture->ButtonUp(...)
				}
				else
				*/
				{
					if (GetVisualTree())
					{
						if (true)//m_pRootElement->m_pBox)
						{
							IInputElement* eventTarget;

							if (m_pElementCapture)
								eventTarget = dynamic_cast<IInputElement*>(m_pElementCapture);
							else
								eventTarget = dynamic_cast<IInputElement*>(m_pElementHover);

							if (eventTarget)
							{
								if (true)
								{
									// TODO, support wrapping ?
									long msgtime = MSWindows::GetMessageTime();

									MouseButtonEventArgs* mouseArgs = new MouseButtonEventArgs(NULL, msgtime);
									mouseArgs->m_leftButton = (nFlags & MK_LBUTTON) == MK_LBUTTON;
									mouseArgs->m_rightButton = (nFlags & MK_RBUTTON) == MK_RBUTTON;
									mouseArgs->m_middleButton = (nFlags & MK_MBUTTON) == MK_MBUTTON;
									mouseArgs->m_screenX = screenpos.X;
									mouseArgs->m_screenY = screenpos.Y;
									mouseArgs->m_windowX = clientpos.X;
									mouseArgs->m_windowY = clientpos.Y;

									InputManager* inputManager = InputManager::get_Current();

									StagingAreaInputItem* stagingItem = new StagingAreaInputItem;
									stagingItem->m_input = mouseArgs;

									PreProcessInputEventArgs* preprocessArgs = new PreProcessInputEventArgs;
									preprocessArgs->m_inputManager = inputManager;
									preprocessArgs->m_stagingItem = stagingItem;	

									inputManager->PreProcessInput(inputManager/*??*/, preprocessArgs);
									//inputManager->PreNotifyInput(inputManager/*??*/, preprocessArgs);

									mouseArgs->set_RoutedEvent(Mouse::s_PreviewMouseUpEvent);
									eventTarget->RaiseEvent(mouseArgs);

									mouseArgs->set_RoutedEvent(Mouse::s_MouseUpEvent);
									eventTarget->RaiseEvent(mouseArgs);

									//inputManager->PostNotifyInput(inputManager/*??*/, preprocessArgs);
									//inputManager->PostProcessInput(inputManager/*??*/, preprocessArgs);
								}
								else
								{
#if 0
									MouseEvent* mouseevt = new MouseEvent;
								//	documentEvent->createEvent(WSTR("MouseEvents"), (ILDOMEvent**)&mouseevt);
									mouseevt->InitMouseEvent(MouseEvent::mouseup,
									//	VARIANT_TRUE,	// bubbles
									//	VARIANT_TRUE,	// cancelable
										this,	// viewArg
									//	0,		// detail
										screenpos.X, screenpos.Y,	// screen
										nFlags & 1,
										(nFlags>>1)&1
									/*	clientpos.x, clientpos.y, // client,
										(nFlags & MK_CONTROL)? VARIANT_TRUE: VARIANT_FALSE,
										(nFlags & MK_SHIFT)? VARIANT_TRUE: VARIANT_FALSE,
										(m_bAlt)? VARIANT_TRUE: VARIANT_FALSE,
										0,	// meta
										0,
										NULL//relatedTarget
										*/
										);

									EventTargetImpl* eventTarget = dynamic_cast<EventTargetImpl*>(pElement);
									bool doDefault = eventTarget->dispatchEvent(mouseevt);

									if (doDefault)
									{
									}

									delete mouseevt;
#endif
								}
							}
						}
					}
				}
			}
		}
	}
}

Cursor* VisualContentSource::OnSetCursor(LDraw::PointD screenpos)
{
	Cursor* pCursor = NULL;

	if (m_pElementHover)
	{
#if 0

		QueryCursorEvent* mouseevt = new QueryCursorEvent;
		mouseevt->m_Cursor = dynamic_cast<FrameworkElement*>(m_pElementHover)->get_Cursor();

	//	documentEvent->createEvent(WSTR("MouseEvents"), (ILDOMEvent**)&mouseevt);
		mouseevt->InitQueryCursorEvent(WSTR("querycursor"),
		//	VARIANT_TRUE,	// bubbles
		//	VARIANT_TRUE,	// cancelable
		//	this,	// viewArg
		//	0,		// detail
			screenpos.X, screenpos.Y//,	// screen
		/*	clientpos.x, clientpos.y, // client,
			(nFlags & MK_CONTROL)? VARIANT_TRUE: VARIANT_FALSE,
			(nFlags & MK_SHIFT)? VARIANT_TRUE: VARIANT_FALSE,
			(m_bAlt)? VARIANT_TRUE: VARIANT_FALSE,
			0,	// meta
			0,
			relatedTarget*/
			);

		EventTargetImpl* eventTarget;
		
		eventTarget = dynamic_cast<EventTargetImpl*>(m_pElementHover);

		if (eventTarget)
		{

			bool doDefault = eventTarget->dispatchEvent(mouseevt);
			if (mouseevt->m_Cursor)
			{
				pCursor = mouseevt->m_Cursor;
			}
		}
		delete mouseevt;
#endif
	}

	return pCursor;

#if 0
	if (m_dragging)
	{
		if (m_dragging == 3)	// panning
		{
			::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND2)));
			return TRUE;
		}
	}
	else
	{
		VARIANT_BOOL bCancel = FALSE;

		LONG bCtrl = (GetAsyncKeyState(VK_CONTROL) & (1<<15));
		LONG bShift = (GetAsyncKeyState(VK_SHIFT) & (1<<15));

		CPElement* pElement = NULL;

		if (m_pRootElement->m_pBox)
		{
			pElement = m_pRootElement->m_pBox->HitTestElementBox(point.x, point.y);
		}
		else if (m_pSVGElement)
		{
			ASSERT(0);
#if 0
			pElement = m_pSVGElement->HitTestElement(GetViewMatrix(), PointD(point.x, point.y));
#endif
		}

		if (pElement == NULL)
		{
			pElement = m_pRootElement;
		}

		if (pElement)
		{
			CComQIPtr<ILDOMElement> documentElement;
			GetView()->m_document->get_documentElement(&documentElement);

#if 0
			CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
#endif

			/*
			CComPtr<ILSVGMatrix> mat0;
			svgsvgElement->createSVGMatrix(&mat0);

			CComPtr<ILSVGMatrix> mat1;
			mat0->scale(m_magnify, &mat1);

			CComPtr<ILSVGMatrix> mat;
			mat1->translate(m_currentTranslateX, m_currentTranslateY, &mat);
			*/

			if (TRUE)
			{
				CComQIPtr<CLDOMElementImplImpl> elementImpl = pElement->m_pNode;

				for (int i = 0; i < elementImpl->m_behaviors.GetSize(); i++)
				{
					CComQIPtr<ILHTMLPainter> htmlPainter = elementImpl->m_behaviors[i]->m_factory;

					if (htmlPainter)
					{
						/*
						CComPtr<ILCanvas> canvas;
						canvas.CoCreateInstance(CLSID_LCanvas);

						canvas->SetGdip((long)pC->m_pGraphics);
						*/

						HRESULT hr = htmlPainter->SetCursor(point);
						if (hr == S_OK)
							return TRUE;
					}
				}
			}

#if 0
			for (int i = 0; i < m_pSVGElement->m_behaviors.GetSize(); i++)
			{
				CComQIPtr<ILHTMLPainter> painter = m_pSVGElement->m_behaviors[i]->m_p;
				if (painter)
				{
					HRESULT hr = painter->SetCursor(point);
					if (hr == S_OK)
						return TRUE;
				}
			}
#endif

			if (TRUE)
			{
#if 0
				if (bCtrl)
				{
					HCURSOR hCursor;
					if (bShift)
						hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_ZOOMOUT));
					else
						hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_ZOOMIN));

					::SetCursor(hCursor);
					return TRUE;
				}
				else if (m_bAlt)
				{
					HCURSOR hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_HAND0));
					::SetCursor(hCursor);
					return TRUE;
				}
#endif

				//CPElement* pElement = NULL;
				//HitTestSVGElement(m_pSVGElement, svgsvgElement, mat, point.x, point.y, &pElement, NULL/*&pNode*/, NULL/*&offset*/);
				HCURSOR hCursor = NULL;

				if (pElement->m_pCursorUriElement)
				{
					ASSERT(0);
#if 0
					CLSVGCursorElement* psvgelement = static_cast<CLSVGCursorElement*>(pElement->m_pCursorUriElement->m_pNode);

					hCursor = psvgelement->GetCursor();
#endif
				}
				else
				{
					switch (pElement->m_computedCursor)
					{
					case Cursor_auto:
						{
#if 0
							CComQIPtr<ILSVGTextElement> textElement;
							if (pElement)
								textElement = pElement->m_pNode;
							
							if (textElement)	// Over Text
							{
								hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_TEXTTEXTNS));
							}
							else
#endif
							{
								hCursor = ::LoadCursor(NULL, IDC_ARROW);
							}
						}
						break;
						
					case Cursor_crosshair:
						{
							hCursor = ::LoadCursor(NULL, IDC_CROSS);
						}
						break;
					case Cursor_default:
						{
							hCursor = ::LoadCursor(NULL, IDC_ARROW);
						}
						break;
					case Cursor_pointer:
						{
							hCursor = ::LoadCursor(NULL, IDC_HAND);
						}
						break;
					case Cursor_move:
						{
							hCursor = ::LoadCursor(NULL, IDC_SIZEALL);
						}
						break;
					case Cursor_e_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_E));
						}
						break;
					case Cursor_ne_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_NE));
						}
						break;
					case Cursor_nw_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_NW));
						}
						break;
					case Cursor_n_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_N));
						}
						break;
					case Cursor_se_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_SE));
						}
						break;
					case Cursor_sw_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_SW));
						}
						break;
					case Cursor_s_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_S));
						}
						break;
					case Cursor_w_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_W));
						}
						break;
					case Cursor_text:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_TEXTTEXTNS));
						}
						break;
					case Cursor_wait:
						{
							hCursor = ::LoadCursor(NULL, IDC_WAIT);
						}
						break;
					case Cursor_help:
						{
							hCursor = ::LoadCursor(NULL, IDC_HELP);
						}
						break;
					case Cursor_progress:
						{
						}
						break;
					case Cursor_copy:
						{
						}
						break;
					case Cursor_alias:
						{
						}
						break;
					case Cursor_context_menu:
						{
						}
						break;
					case Cursor_cell:
						{
						}
						break;
					case Cursor_all_scroll:
						{
						}
						break;
					case Cursor_col_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_COL));
						}
						break;
					case Cursor_row_resize:
						{
							hCursor = ::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZE_ROW));
						}
						break;
					case Cursor_no_drop:
						{
						}
						break;
					case Cursor_not_allowed:
						{
							hCursor = ::LoadCursor(NULL, IDC_NO);
						}
						break;
					case Cursor_vertical_text:
						{
						}
						break;
					}
				}

				/*
				CComQIPtr<ILSVGTextElement> textElement;
				if (pElement)
					textElement = pElement->m_pNode;

				if (textElement)	// Over Text
				{
					SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_TEXTTEXTNS)));
					return TRUE;
				}
				*/

				if (hCursor)
				{
					::SetCursor(hCursor);
					return TRUE;
				}
			}
		}
	}
#endif
}

void VisualContentSource::OnContextMenu(LDraw::PointD screenpos, LDraw::PointD clientpos)
{
	if (GetVisualTree())
	{
		Visual* pElement = NULL;

		pElement = GetVisualTree()->HitTestElement(GetViewMatrix(), LDraw::PointD(clientpos.X, clientpos.Y));

		if (pElement == NULL)
		{
			pElement = m_Content;
		}

		if (pElement)
		{
			ASSERT(0);
#if 0
			EventTargetImpl* target = dynamic_cast<EventTargetImpl*>(pElement);//->m_eventTarget;
			ASSERT(target != NULL);
			if (target)
			{
				MouseEvent* mouseEvt = new MouseEvent;
				mouseEvt->InitMouseEvent(WSTR("contextmenu"),
					this,
					screenpos.X, screenpos.Y,	// screen
					0,
					0
					);

				bool doDefault = target->dispatchEvent(mouseEvt);
				delete mouseEvt;
			}
#endif
		}
	}

#if 0
	CPoint pt = point;
	pt.x -= m_client.left;
	pt.y -= m_client.top;

	if (m_pSVGElement)
	{
		CComQIPtr<ILDOMDocumentEvent> documentEvent = GetView()->m_document;
		ASSERT(documentEvent != NULL);

		CComQIPtr<ILDOMElement> documentElement;
		GetView()->m_document->get_documentElement(&documentElement);

#if 0
		CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
#endif

	//	VARIANT_BOOL editMode;
	//	m_documentContainer->get_editMode(&editMode);

		//CComPtr<ILSVGMatrix> mat;
		//svgsvgElement->createSVGMatrix(&mat);

//		CPElement* pElement = NULL;
//		HitTestSVGElement(m_pSVGElement, svgsvgElement, mat, pt.x, pt.y, &pElement, NULL, NULL);
		ASSERT(0);
#if 0
		CPSVGElementImpl* pElement = m_pSVGElement->HitTestElement(GetViewMatrix(), PointD(point.x, point.y));

		if (pElement == NULL)
		{
			pElement = m_pSVGElement;
		}

		if (pElement)
		{
		//	m_pHitElement = NULL;
		//	BOOL b = pElement->OnButtonDown(point, &m_pHitElement);
		// Do something hm.. ??

	/*
	clientX and clientY parameters for mouse events represent viewport
	coordinates for the corresponding 'svg' element.

	relatedNode is the corresponding outermost 'svg' element
	*/

			CComQIPtr<ILDOMEventTarget> target = pElement->m_pNode;
			ASSERT(target != NULL);
			if (target)
			{
				CComQIPtr<ILDOMEventTarget> relatedTarget = svgsvgElement;
				ASSERT(relatedTarget != NULL);

				CComPtr<ILDOMMouseEvent> mouseevt;

				documentEvent->createEvent(WSTR("MouseEvents"), (ILDOMEvent**)&mouseevt);
				mouseevt->initMouseEvent(WSTR("contextmenu"),
					VARIANT_TRUE,	// bubbles
					VARIANT_TRUE,	// cancelable
					GetView(),	// viewArg
					0,		// detail
					pt.x, pt.y,	// screen
					pt.x, pt.y, // client,	// TODO
					0,//(nFlags & MK_CONTROL)? VARIANT_TRUE: VARIANT_FALSE,
					0,//(nFlags & MK_SHIFT)? VARIANT_TRUE: VARIANT_FALSE,
					(/*m_pUI->*/m_bAlt)? VARIANT_TRUE: VARIANT_FALSE,
					0,	// meta
					0,
					relatedTarget
					);

				VARIANT_BOOL doDefault;
				target->dispatchEvent(mouseevt, &doDefault);

				if (doDefault)
				{
					HMENU hMenu = ::LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_SVG));

					::TrackPopupMenu(GetSubMenu(hMenu, 0), TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, 0, m_cwnd, NULL);

					::DestroyMenu(hMenu);
				}
			}
		}
#endif
	}

#if 0
	CComObject<CMenuItem>* menu;
	CComObject<CMenuItem>::CreateInstance(&menu);
	if (menu)
	{
		menu->AddRef();

		BOOL b;
		menu->LoadMenu((long)_Module.GetResourceInstance(), IDR_LHTMLVIEW, &b);

		CComPtr<IMenuItem> subMenu;
		menu->GetSubMenu(0, &subMenu);

		long selectedID;
		subMenu->PopupMenu(this, point, 0, &selectedID);

		menu->Release();
	}
#endif
#endif
}


#if 0
long VisualContentSource::SetElement(ILDOMElement* element)
{
	ASSERT(0);
#if 0
	ASSERT(element);	// A CHTMFrame must have a valid document/root element (?)
	if (m_element != element)	// TODO, better comparison ??
	{
		FreeImage();

		m_element = element;

		if (m_element)
		{
			m_element->get_ownerDocument(&m_document);

			CComQIPtr<CLDOMDocumentImplImpl>(m_document)->AddView(this);

			CComQIPtr<INotifySend> cp = m_document;
			ASSERT(cp);
			DWORD cookie;
			cp->Advise(this, &cookie);

			DoneParsing();
		}

		if (m_pUI)
		{
			if (m_pUI->m_hWnd)
			{
				m_pUI->InvalidateRect(NULL, TRUE);
			}
		}
	}
#endif
	return 0;
}
#endif

#if 0
// Setup script, after the document object has been created, but before it is loaded
void VisualContentSource::PrepareScripting()
{
	ASSERT(0);
#if 0

		/* ?? TODO

		  For each OBJECT element in the document, call this (if not here, then somewhere)

		  hr = m_activeScript = AddTypeLib(
			 REFGUID guidTypeLib,  // CLSID of type library
			 DWORD dwMaj,          // major version number
			 DWORD dwMin,          // minor version number
			 DWORD dwFlags         // option flags
		);

		*/
	}
#endif
}
#endif

#if 0
void AddScriptlet(IActiveScriptParse* activeScript, BSTR id, BSTR event, BSTR code)
{
	BSTR actualScriptletName = NULL;
	EXCEPINFO excepinfo = {0};

	HRESULT hr = activeScript->AddScriptlet(
		NULL,// address of default name of scriptlet
		code,          // address of scriptlet text
		id, // address of item name
		NULL, // address of subitem name
		event,//WSTR("onmousedown(evt)",// address of event name
		WSTR(""),//NULL,// address of end-of-scriptlet delimiter
		0L,// application-defined value for debugging
		0,// starting line of the script
		0,//SCRIPTTEXT_ISVISIBLE ,// ???????DWORD dwFlags,               // scriptlet flags
		&actualScriptletName,             // address of actual name of scriptlet
		&excepinfo        // address of exception information
		);
	if (FAILED(hr))
	{
		MessageBox(NULL, "failed to add scriptlet", "JScript", MB_OK);
	}

	TRACE("\nactualScriptName: %S\n\n", actualScriptletName);
	SysFreeString(actualScriptletName);
}

void AddScriptlets(IActiveScriptParse* activeScript, ILDOMElement* element)
{
	BSTR bid;
	element->getAttribute(WSTR("id"), &bid);
	_bstr_t id = _bstr_t(bid, false);

	BSTR bcode;
	_bstr_t code;

	/*
	element->getAttribute(WSTR("onload", &bcode);
	code = _bstr_t(bcode, false);
	if (code.length())
	{
		AddScriptlet(activeScript, id, WSTR("onload"), code);
	}
	*/

	element->getAttribute(WSTR("onmousedown"), &bcode);
	code = _bstr_t(bcode, false);
	if (code.length()) AddScriptlet(activeScript, id, WSTR("onmousedown"), code);

	element->getAttribute(WSTR("onchange"), &bcode);
	code = _bstr_t(bcode, false);
	if (code.length()) AddScriptlet(activeScript, id, WSTR("onchange"), code);

	element->getAttribute(WSTR("onclick"), &bcode);
	code = _bstr_t(bcode, false);
	if (code.length()) AddScriptlet(activeScript, id, WSTR("onclick"), code);

	ILDOMNode* child;
	element->get_firstChild(&child);
	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);
		if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> childelement = child;
			AddScriptlets(activeScript, childelement);
		}

		CComQIPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
}
#endif

#if 0
void VisualContentSource::AddNamedElements(IActiveScript* script, ILDOMElement* parent)
{
	CComQIPtr<ILDOMNode> node;
	parent->get_firstChild(&node);
	while (node != NULL)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			BSTR bid;
			element->getAttribute(WSTR("id"), &bid);
			_bstr_t id = _bstr_t(bid, false);
			if (id.length() > 0)
			{
				script->AddNamedItem(id, SCRIPTITEM_ISVISIBLE | SCRIPTITEM_ISSOURCE);

				CNamedItem item;
				item.m_name = id;
				CComQIPtr<IDispatch> elementdisp = element;
				item.m_pDisp = elementdisp;
				m_namedItems.Add(item);
			}

			AddNamedElements(script, element);
		}

		CComQIPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
}
#endif


//void BuildAnimationListForAllElements(ILDOMElement* element, ILDOMElement* svgElement);

//#include "C:\Program Files\Microsoft Speech SDK 5.1\Include\sapi.h"
//#pragma comment(lib, "C:\\Program Files\\Microsoft Speech SDK 5.1\\Lib\sapi.lib")


	#if 0
					if (!editMode)
					{
						CComQIPtr<IActiveScriptParse> activeScriptParse = m_activeScript;

						AddScriptlets(activeScriptParse, documentElement);

					// window events ?
						AddScriptlet(activeScriptParse, WSTR("globalwindow2"), WSTR("onload"), WSTR("OnLoad()");

					// force the engine to connect any outbound interfaces to the 
					// host's objects
						HRESULT hr = m_activeScript->SetScriptState(SCRIPTSTATE_CONNECTED);
						ASSERT(SUCCEEDED(hr));

						// Start playing document
						{
							m_totalIntendedTime = 0;

							LONG uDelay = (LONG)(1000/m_frameRate);

							m_videoTimeID = timeSetEvent(uDelay, 0, (LPTIMECALLBACK)PlaybackProc, (DWORD)this, TIME_PERIODIC);

							if (!m_videoTimeID)
							{
							//	m_bPlaying = FALSE;
							//	UpdateAllViews(NULL);

								MessageBox(NULL, "Video playback Timer could not be created", "", MB_OK);
							}
						}
					}
					else
	#endif

#if 0
void VisualContentSource::DrawCursor(CPNode* pItem, int offset, BOOL bStippled /* = FALSE */)
{
						ASSERT(0);
#if 0
	if (pItem)
	{
		HDC hDC = GetDC();

		CPTextNodeBase* pTextNode = (CPTextNodeBase*)pItem;
		if (pTextNode)
		{
			PointD pos;
			double height;
			gmMatrix3 mat0;
			BOOL b = pTextNode->GetCursorPosition(offset, &pos, &height, &mat0);

			gmMatrix3 mat = mat0/* *
								gmMatrix3::scale(m_magnify, m_magnify) *
								gmMatrix3::translate(m_currentTranslateX, m_currentTranslateY)*/;

			if (b)
			{
				if (!bStippled)
				{
					int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

					HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
					HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

					gmVector2 v0 = mat.transform(gmVector2(pos.X, pos.Y));
					gmVector2 v1 = mat.transform(gmVector2(pos.X, pos.Y+height));

					MoveToEx(hDC, v0[0], v0[1], NULL);
					LineTo(hDC, v1[0], v1[1]);

					SelectObject(hDC, hOldPen);
					DeleteObject(hPen);

					SetROP2(hDC, oldR2);
				}
				else
				{
					RECT frc = {pos.X, pos.Y, pos.X+2, pos.Y+height};
					DrawFocusRect(hDC, &frc);
				}
			}
			else
			{
#if 0
#ifdef DEBUG
				// Find out where why
				long wordoffset;
				CHTMPCharacterBox* pCharBox = pTextNode->GetWordAtCursorPos(offset, wordoffset);
				ASSERT(0);
#endif
#endif
			}
		}

		ReleaseDC(hDC);
	}
#endif
}
#endif

#if 0
void VisualContentSource::ToggleCursor()
{
	m_bShowCursor = !m_bShowCursor;
//	DrawCursor(m_curContainer, m_curOffset);
}


void VisualContentSource::ShowCursor()
{
	if (!m_bShowCursor)
	{
		ToggleCursor();
	}
}

void VisualContentSource::HideCursor()
{
	if (m_bShowCursor)
	{
		ToggleCursor();
	}
}
#endif

#if 0

void VisualContentSource::MoveCursorLeft()
{
	ASSERT(0);
#if 0
	if (m_cursorItem)
	{
		if (m_cursorOffset == 0)
		{
			if (m_cursorItem->m_parent)
			{
				CPNode* pPrevNode = m_cursorItem->GetPrevNode();
				if (pPrevNode)
				{
					m_cursorItem = pPrevNode;

					CComQIPtr<ILDOMText> prevText = pPrevNode->m_pNode;
					if (prevText)
					{
						unsigned long textlength;
						prevText->get_dataLength(&textlength);
						m_cursorOffset = textlength;
					}
					else
						m_cursorOffset = 0;
				}
			}
		}
		else
		{
			m_cursorOffset--;
		}
	}
#endif
}

void VisualContentSource::MoveCursorRight()
{
	ASSERT(0);
#if 0
	if (m_cursorItem)
	{
		CComQIPtr<IDOMText> text = m_cursorItem->m_pNode;

		unsigned long textlength;
		text->get_dataLength(&textlength);

		ASSERT(m_cursorOffset <= textlength);

		if (m_cursorOffset == textlength-1) // hm?? -1 ??
		{
			ASSERT(0);
		/* Have this
			UPOSITION pos = m_cursorItem->m_parent->m_childList.Find(m_cursorItem);
			m_cursorItem->m_parent->m_childList.GetNext(pos);
			m_cursorItem = (CHTMPItem*)m_cursorItem->m_parent->m_childList.GetAt(pos);

			m_cursorOffset = 0;
			*/
		}
		else
		{
			m_cursorOffset++;
		}
	}
#endif
}
#endif


///////////////////////////////////////////////////////////////////

#if 0	// Had this
int CompareTreePosition(ILDOMNode* pThis, ILDOMNode* pNode);

enum
{
	tomCharacter	= 1,
	tomWord	= 2,
	tomSentence	= 3,
	tomParagraph	= 4,
	tomLine	= 5,
};

#if _WINDOWS
ILDOMNode* RightMost(ILDOMNode* node, long& offset)
{
	CComPtr<ILDOMNode> lastChild;
	node->get_lastChild(&lastChild);

	if (lastChild)
	{
		return RightMost(lastChild, offset);
	}

	CComQIPtr<ILDOMCharacterData> text = node;
	if (text)
	{
		BSTR bdata;
		text->get_data(&bdata);
		_bstr_t data = _bstr_t(bdata);

		offset = data.length();
	}
	else
		ASSERT(0);

	return node;
}

ILDOMNode* PreviousTextOrNonEmptyElement(ILDOMNode* node)
{
	VARIANT_BOOL hasChildNodes;
	LDOMNodeType nodeType;

	CComPtr<ILDOMNode> previousSibling;
	node->get_previousSibling(&previousSibling);

	if (previousSibling)
	{
		previousSibling->get_nodeType(&nodeType);
		previousSibling->hasChildNodes(&hasChildNodes);
	}

	while (previousSibling && (nodeType == NODE_ELEMENT && !hasChildNodes))
	{
		CComPtr<ILDOMNode> previousSibling2;
		previousSibling->get_previousSibling(&previousSibling2);
		previousSibling = previousSibling2;

		if (previousSibling)
		{
			previousSibling->get_nodeType(&nodeType);
			previousSibling->hasChildNodes(&hasChildNodes);
		}
	}

	if (previousSibling)
		return previousSibling.Detach();
	else
		return NULL;
}

HRESULT MoveCursorLeft(ILDOMNode* startContainer, ILDOMNode* topMostParent, long startOffset, ILDOMNode* *container, long* offset)
{
	if (startOffset > 0)	// Moving within the same text node
	{
		(*container = startContainer)->AddRef();
		*offset = startOffset-1;

		return S_OK;
	}
	else
	{
		CComPtr<ILDOMNode> node;
		node = startContainer;

		CComPtr<ILDOMNode> previousSibling = PreviousTextOrNonEmptyElement(node);

		while (previousSibling == NULL)
		{
			CComPtr<ILDOMNode> parentNode;
			node->get_parentNode(&parentNode);
			node = parentNode;
			if (node == topMostParent) break;

			previousSibling = PreviousTextOrNonEmptyElement(node);
		}

		if (previousSibling)
		{
			node = RightMost(previousSibling, startOffset);

			(*container = node)->AddRef();
			*offset = startOffset-1;

			return S_OK;
		}
	}

	return S_FALSE;
}

ILDOMNode* LeftMost(ILDOMNode* node, long& offset)
{
	CComPtr<ILDOMNode> firstChild;
	node->get_firstChild(&firstChild);

	if (firstChild)
	{
		return LeftMost(firstChild, offset);
	}

	CComQIPtr<ILDOMCharacterData> text = node;
	if (text)
	{
		offset = 0;
	}
	else
		ASSERT(0);

	return node;
}

ILDOMNode* NextTextOrNonEmptyElement(ILDOMNode* node)
{
	VARIANT_BOOL hasChildNodes;
	LDOMNodeType nodeType;

	CComPtr<ILDOMNode> nextSibling;
	node->get_nextSibling(&nextSibling);

	if (nextSibling)
	{
		nextSibling->get_nodeType(&nodeType);
		nextSibling->hasChildNodes(&hasChildNodes);
	}

	while (nextSibling && (nodeType == NODE_ELEMENT && !hasChildNodes))
	{
		CComPtr<ILDOMNode> nextSibling2;
		nextSibling->get_nextSibling(&nextSibling2);
		nextSibling = nextSibling2;

		if (nextSibling)
		{
			nextSibling->get_nodeType(&nodeType);
			nextSibling->hasChildNodes(&hasChildNodes);
		}
	}

	if (nextSibling)
		return nextSibling.Detach();
	else
		return NULL;
}

HRESULT MoveCursorRight(ILDOMNode* startContainer, ILDOMNode* topMostParent, long startOffset, ILDOMNode* *container, long* offset)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDOMCharacterData> text = startContainer;
	BSTR bdata;
	text->get_data(&bdata);
	_bstr_t data = _bstr_t(bdata, false);

	if (startOffset < data.length())
	{
		(*container = startContainer)->AddRef();
		*offset = startOffset+1;

		return S_OK;
	}
	else
	{
		CComPtr<ILDOMNode> node;
		node = startContainer;

		CComPtr<ILDOMNode> nextSibling = NextTextOrNonEmptyElement(node);

		while (nextSibling == NULL)
		{
			CComPtr<ILDOMNode> parentNode;
			node->get_parentNode(&parentNode);
			node = parentNode;
			if (node == topMostParent) break;

			nextSibling = NextTextOrNonEmptyElement(node);
		}

		if (nextSibling)
		{
			node = LeftMost(nextSibling, startOffset);

			(*container = node)->AddRef();
			*offset = startOffset+1;

			return S_OK;
		}
	}
#endif
	return S_FALSE;
}
#endif

#if 0
HRESULT VisualContentSource::ExtendIt(ILDOMNode* container, long offset, int bShift)
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;

// Dectivate previous range
//	uiManager->DeactivateObject(m_range);

	if (bShift)
	{
		CComPtr<ILDOMNode> startContainer;
		long startOffset;

		CComPtr<ILDOMNode> endContainer;
		long endOffset;

		if (container == m_initContainer->m_pNode)	// start and end share container
		{
			startContainer = container;
			endContainer = container;

			if (offset < m_initOffset)
			{
				startOffset = offset;
				endOffset = m_initOffset;
			}
			else
			{
				startOffset = m_initOffset;
				endOffset = offset;
			}
		}
		else
		{
			int cmp = CompareTreePosition(container, m_initContainer->m_pNode);
			ASSERT(cmp != 0);

			if (cmp == -1)
			{
				startContainer = container;
				startOffset = offset;

				endContainer = m_initContainer->m_pNode;
				endOffset = m_initOffset;
			}
			else
			{
				startContainer = m_initContainer->m_pNode;
				startOffset = m_initOffset;

				endContainer = container;
				endOffset = offset;
			}
		}

		m_range->setStart(startContainer, startOffset);
		m_range->setEnd(endContainer, endOffset);
	}
	else
	{
		m_initContainer = m_pRootElement->FindDOMElement(container);
		m_initOffset = offset;

		m_range->setStart(container, offset);
		m_range->setEnd(container, offset);
	}

	m_curContainer = m_pRootElement->FindDOMElement(container);
	m_curOffset = offset;
	ASSERT(m_curOffset >= 0);

	// Activate new range
//	uiManager->ActivateObject(GetUnknown(), m_range);

	return S_OK;
}

STDMETHODIMP VisualContentSource::TypeText(BSTR bstr)
{
	if (m_range)
	{
		CComPtr<ILDOMNode> startContainer;
		long startOffset;
		m_range->get_startContainer(&startContainer);
		m_range->get_startOffset(&startOffset);

		CComQIPtr<ILDOMText> text = startContainer;
		if (text)
		{
			text->insertData(startOffset, bstr);

			MoveRight(tomCharacter, 1, 0, NULL);

			return S_OK;
		}
	}

	return E_FAIL;
}

HRESULT GetTopMostTextContentElement(ILDOMNode* node, ILDOMNode* *pVal)
{
	CComPtr<ILDOMNode> node2 = node;
	while (node2)
	{
		CComPtr<ILDOMNode> parentNode;
		node2->get_parentNode(&parentNode);

		ASSERT(0);

#if 0
		CComQIPtr<ILSVGTextContentElement> textContent = parentNode;
		if (textContent == NULL)
		{
			break;
		}
#endif

		node2 = parentNode;
	}

	ASSERT(node2);

	*pVal = node2;
	(*pVal)->AddRef();
	return S_OK;
}


STDMETHODIMP VisualContentSource::Delete(/*[in]*/ long Unit, /*[in]*/ long Count, /*[out,retval]*/ long* pDelta)
{
//	CPDTextRangeImpl<IPDTextSelection>::Delete(Unit, Count, pDelta);
	{
		if (Count == 0)	// Delete all characters in range
		{
			m_range->deleteContents();
		}
		else
		{
			CComPtr<ILDOMNode> m_curContainer;
			long m_curOffset;

			m_range->get_startContainer(&m_curContainer);
			m_range->get_startOffset(&m_curOffset);
			ASSERT(m_curOffset >= 0);

			if (Count > 0)	// Delete
			{
				CComPtr<ILDOMNode> topMost;
				GetTopMostTextContentElement(m_curContainer, &topMost);

				CComPtr<ILDOMNode> container;
				long offset;
				if (MoveCursorRight(m_curContainer, topMost, m_curOffset, &container, &offset) == S_OK)
				{
					m_range->setEnd(container, offset);
					m_range->deleteContents();

					/*
					m_curContainer = container;
					m_curOffset = offset;
					m_initContainer = container;
					m_initOffset = offset;
					*/
				}
			}
			else	// Backspace
			{
				CComPtr<ILDOMNode> topMost;
				GetTopMostTextContentElement(m_curContainer, &topMost);

				CComPtr<ILDOMNode> container;
				long offset;
				if (MoveCursorLeft(m_curContainer, topMost, m_curOffset, &container, &offset) == S_OK)
				{
					m_range->setStart(container, offset);
					m_range->deleteContents();
	/*
					m_range->Set(
					m_curContainer = container;
					m_curOffset = offset;
					m_initContainer = container;
					m_initOffset = offset;
					*/
				}
			}
		}
	}

	CComPtr<ILDOMNode> startContainer;
	long startOffset;
	m_range->get_startContainer(&startContainer);
	m_range->get_startOffset(&startOffset);

	m_curContainer = m_pRootElement->FindDOMElement(startContainer);
	m_curOffset = startOffset;
	ASSERT(m_curOffset >= 0);

	m_initContainer = m_pRootElement->FindDOMElement(startContainer);
	m_initOffset = startOffset;
	ASSERT(m_initOffset >= 0);

	return S_OK;
}

STDMETHODIMP VisualContentSource::MoveRight(long Unit, long Count, long Extend, long *pDelta)
{
	CComPtr<ILDOMNode> topMost;
	GetTopMostTextContentElement(m_curContainer->m_pNode, &topMost);

	CComPtr<ILDOMNode> container;
	long offset;
	if (MoveCursorRight(m_curContainer->m_pNode, topMost, m_curOffset, &container, &offset) == S_OK)
	{
		ExtendIt(container, offset, Extend);
	}

	return S_OK;
}

STDMETHODIMP VisualContentSource::MoveLeft(long Unit, long Count, long Extend, long *pDelta)
{
	CComPtr<ILDOMNode> topMost;
	GetTopMostTextContentElement(m_curContainer->m_pNode, &topMost);

	CComPtr<ILDOMNode> container;
	long offset;
	if (MoveCursorLeft(m_curContainer->m_pNode, topMost, m_curOffset, &container, &offset) == S_OK)
	{
		ExtendIt(container, offset, Extend);
	}

	return S_OK;
}


void InsertFocusElement(ILDOMElement* element, CUPtrList& list)
{
	list.AddTail(element);
}

void BuildFocusList(ILDOMElement* element, CUPtrList& list)
{
	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> element2 = node;
		if (element2)
		{
			CComBSTR tagName;
			element2->get_tagName(&tagName);

			if (!wcscmp(tagName, WSTR("a"))
			{
				InsertFocusElement(element2, list);
			}

			BuildFocusList(element2, list);
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
}
#endif
#endif

//#include <ocidl.h>

#if 0
HDC VisualContentSource::GetDC()
{
	ASSERT(0);
	return NULL;
#if 0	// Had this
	if (m_pUI)
	{
		return m_pUI->GetDC();
	}
	else
	{
		ASSERT(m_pActiveDocument->m_hWnd == NULL);

//		CRect rect = m_imageRect;
//		rect.OffsetRect(m_pActiveDocument->m_rcPos.left, m_pActiveDocument->m_rcPos.top);

		HDC hDC;
		HRESULT hr = m_pActiveDocument->m_spInPlaceSite->GetDC(NULL/*&rect*/, OLEDC_NODRAW, &hDC);
		if (FAILED(hr))
		{
//			if (hr == OLE_E_NESTEDPAINT)
			{
				ASSERT(0);
			}
		}

		ASSERT(hDC);

		OffsetViewportOrgEx(hDC, m_pActiveDocument->m_rcPos.left, m_pActiveDocument->m_rcPos.top, NULL);

		return hDC;
	}
#endif
}

void VisualContentSource::ReleaseDC(HDC hDC)
{
	ASSERT(0);
#if 0	// Had this
	if (m_pUI)
	{
		m_pUI->ReleaseDC(hDC);
	}
	else
	{
		m_pActiveDocument->m_spInPlaceSite->ReleaseDC(hDC);
	}
#endif
}

void VisualContentSource::ScreenToClient(CPoint* ppoint)
{
	ASSERT(0);
#if 0	// Had this
	if (m_pUI)
	{
		m_pUI->ScreenToClient(ppoint);
	}
	else
	{
		HWND hwnd;
		m_pActiveDocument->m_spInPlaceSite->GetWindow(&hwnd);

		::ScreenToClient(hwnd, ppoint);

		ppoint->x -= m_pActiveDocument->m_rcPos.left;
		ppoint->y -= m_pActiveDocument->m_rcPos.top;
	}
#endif
}
#endif

///////////////////////////////////////////////////////////////////

void VisualContentSource::OnKeyDown(int vk, bool bControl, bool bShift)
//void VisualContentSource::OnKeyDown(int nKey, int lKeyData)
{
	IInputElement* eventTarget = m_pElementFocus;//->m_eventTarget;
	if (eventTarget)
	{
		// TODO, support wrapping ?
		long msgtime = MSWindows::GetMessageTime();

		KeyEventArgs* keyArgs = new KeyEventArgs(NULL, NULL, msgtime, vk);
	//	mouseArgs->m_leftButton = (nFlags & MK_LBUTTON) == MK_LBUTTON;
	//	mouseArgs->m_rightButton = (nFlags & MK_RBUTTON) == MK_RBUTTON;
	//	mouseArgs->m_middleButton = (nFlags & MK_MBUTTON) == MK_MBUTTON;
	//	mouseArgs->m_X = screenpos.X;
	//	mouseArgs->m_Y = screenpos.Y;

		InputManager* inputManager = InputManager::get_Current();

		StagingAreaInputItem* stagingItem = new StagingAreaInputItem;
		stagingItem->m_input = keyArgs;

		PreProcessInputEventArgs* preprocessArgs = new PreProcessInputEventArgs;
		preprocessArgs->m_inputManager = inputManager;
		preprocessArgs->m_stagingItem = stagingItem;	

		inputManager->PreProcessInput(inputManager/*??*/, preprocessArgs);
		//inputManager->PreNotifyInput(inputManager/*??*/, preprocessArgs);

	//	keyArgs->set_RoutedEvent(Mouse::s_PreviewMouseDownEvent);
	//	eventTarget->RaiseEvent(mouseArgs);

		keyArgs->set_RoutedEvent(UIElement::get_KeyDownEvent());
		eventTarget->RaiseEvent(keyArgs);
	}
#if 0
	long virtKey = 0;
	if (nKey == VK_DELETE)
		virtKey = DOM_VK_DELETE;

	CComQIPtr<ILDOMDocumentEvent> documentEvent = GetView()->m_document;
	ASSERT(documentEvent != NULL);

	CComQIPtr<ILDOMElement> documentElement;
	GetView()->m_document->get_documentElement(&documentElement);

	CComQIPtr<ILDOMEventTarget> relatedTarget = documentElement;
	ASSERT(relatedTarget != NULL);

	CComPtr<ILTextEvent> textevt;

	documentEvent->createEvent(WSTR("TextEvent"), (ILDOMEvent**)&textevt);
	textevt->initTextEvent(
		WSTR("keydown"),	// typeArg
		VARIANT_TRUE,	// canBubbleArg
		VARIANT_TRUE,	// cancelableArg
		this,	// viewArg
		0,		// detailArg
		NULL,	// outputStringArg
		nKey,	// keyValArg
		virtKey,	// virtKeyValArg
		VARIANT_FALSE,	// visibleOutputGeneratedArg
		VARIANT_FALSE	// numPadArg
		);
	textevt->initModifier(DOM_VK_LEFT_ALT, m_bAlt);

	VARIANT_BOOL doDefault = VARIANT_TRUE;
	ASSERT(0);
#if 0
	CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
	if (svgsvgElement)
	{
		CComQIPtr<ILDOMEventTarget> eventTarget = svgsvgElement;

		eventTarget->dispatchEvent(textevt, &doDefault);
	}
#endif

	if (doDefault)
	{
		LONG bCtrl = (GetAsyncKeyState(VK_CONTROL) & (1<<15));
		LONG bShift = (GetAsyncKeyState(VK_SHIFT) & (1<<15));

#if 0
		if (svgsvgElement)
		{
			//if (m_bAlt)
			{
				CPoint point;
				GetCursorPos(&point);
				ScreenToClient(&point);

				OnSetCursor(/*HTCLIENT, 0,*/ point);
			}
		}
		else
#endif
		{
			HideCursor();

			if (nKey == VK_TAB)
			{
				CComPtr<ILDOMElement> documentElement;
				GetView()->m_document->get_documentElement(&documentElement);

				CUPtrList list;
				BuildFocusList(documentElement, list);

				CPElement* pElement = NULL;

				if (m_pPElementFocus)
				{
					UPOSITION pos = list.Find(m_pPElementFocus->m_pNode);
					ASSERT(pos);

					if (!bShift)
					{
						list.GetNext(pos);
						if (pos == NULL)	// Wrap to beginning
						{
							pos = list.GetHeadPosition();
						}
					}
					else
					{
						list.GetPrev(pos);

						if (pos == NULL)	// Wrap to end
						{
							pos = list.GetTailPosition();
						}
					}

					if (pos)
					{
						ILDOMElement* element = (ILDOMElement*)list.GetAt(pos);

						pElement = (CPElement*)m_pRootElement->FindDOMElement(element);
					}
				}
				else
				{
					// First
					if (!list.IsEmpty())
					{
						pElement = (CPElement*)m_pRootElement->FindDOMElement((ILDOMNode*)list.GetHead());
					}
				}

				if (m_pPElementFocus != pElement)
				{
					if (m_pPElementFocus)
					{
						m_pPElementFocus->m_bFocus = false;
						m_pPElementFocus->m_bActive = false;
						m_pPElementFocus->GetCSSPropertiesAndChildren();
					}

					m_pPElementFocus = pElement;

					if (m_pPElementFocus)
					{
						m_pPElementFocus->m_bFocus = true;
						m_pPElementFocus->m_bActive = true;
						m_pPElementFocus->GetCSSPropertiesAndChildren();

						scrollIntoView(m_pPElementFocus);
					}

					Flow();	// hm.. optimize this somehow

					InvalidateRect(NULL);	// TODO ?
				}
			}
			else if (nKey == VK_RETURN)
			{
				if (m_pPElementFocus)
				{
					CComQIPtr<ILDOMElement> element = m_pPElementFocus->m_pNode;

					CComBSTR href;
					element->getAttribute(WSTR("href"), &href);

					TCHAR absurl[2048];
					{
						CComBSTR documentUrl;
						GetView()->m_document->get_url(&documentUrl);

						DWORD resultLen = sizeof(absurl);
						InternetCombineUrl(_bstr_t(documentUrl), _bstr_t(href), absurl, &resultLen, 0);
					}

					GotoLocation(_bstr_t(absurl));
				}
			}
			else
			{
				if (m_curContainer)
				{
					switch (nKey)
					{
					case VK_LEFT:
						{
							MoveLeft(bCtrl? tomWord: tomCharacter, 1, bShift, NULL);
						}
						break;

					case VK_RIGHT:
						{
							MoveRight(bCtrl? tomWord: tomCharacter, 1, bShift, NULL);
						}
						break;

					case VK_BACK:
					case VK_DELETE:
						{
							VARIANT_BOOL bCollapsed;
							m_range->get_collapsed(&bCollapsed);
							if (bCollapsed)
							{
								if (nKey == VK_BACK)
								{
									Delete(tomCharacter, -1, NULL);
								}
								else
								{
									Delete(tomCharacter, 1, NULL);
								}

							//	m_pUI->Invalidate();	// TODO remove
							}
							else
							{
								Delete(tomCharacter, 0, NULL);
								//ClearSelection();
							}
						}
						break;

			#if 0
					case VK_UP:
					case VK_DOWN:
					case VK_HOME:
					case VK_END:
					case VK_PRIOR:
					case VK_NEXT:
						{
							/*
							if (bShift)
							{
								if (m_initSel == -1)	// Starting new selection
								{
									m_initSel = m_offset;
								}
							}
							else
							{
								ClearSelectionAndInvalidate();
							}
				*/
							switch (nKey)
							{
							case VK_LEFT:	MoveCursorLeft(); break;
							case VK_RIGHT:	MoveCursorRight(); break;
						//	case VK_UP:		MoveCursorUp(); break;
						//	case VK_DOWN:	MoveCursorDown(); break;
						//	case VK_HOME:	MoveCursorBegLine(); break;
						//	case VK_END:	MoveCursorEndLine(); break;
						//	case VK_PRIOR:	MoveCursorPageUp(); break;
						//	case VK_NEXT:	MoveCursorPageDown(); break;
							}
				/*
							if (bShift)
							{
								SetSelectionAndInvalidate(m_initSel, m_offset);
							}
							*/
						}
						break;

					case VK_BACK:
						{
							MoveCursorLeft();
						}
						// Fall through

					case VK_DELETE:
						{
							CLXUIText* pPText = (CLXUIText*)m_cursorItem;

							CComQIPtr<ILDOMText> text = pPText->m_pNode;
							ASSERT(text);

							// Update DOM and Source
							text->deleteData(m_cursorOffset, 1);

							if (pPText->m_text.GetLength() == 1)
							{
							// Delete the current item
								POSITION thispos = pPText->m_parent->m_childList.Find(pPText);
								POSITION nextpos = thispos;
								pPText->m_parent->m_childList.GetNext(nextpos);
								CLXUIText* pPNextText = (CLXUIText*)pPText->m_parent->m_childList.GetAt(nextpos);

								m_cursorItem = pPNextText;
								m_cursorOffset = 0;//pPNextText->m_text.GetLength();

								((CHTMPElement*)pPNextText->m_parent)->MoveTextOffsets(thispos, -1);

								// Remove and delete this item
								pPNextText->m_parent->m_childList.RemoveAt(thispos);
								delete pPText;
							}
							else if (m_cursorOffset == pPText->m_text.GetLength())
							{
							// Join this item with next

							// Update Render
								POSITION thispos = pPText->m_parent->m_childList.Find(pPText);
								POSITION nextpos = thispos;
								pPText->m_parent->m_childList.GetNext(nextpos);
								CLXUIText* pPNextText = (CLXUIText*)pPText->m_parent->m_childList.GetAt(nextpos);

							//	m_cursorItem = pPNextText;
							//	m_cursorOffset = pPText->m_text.GetLength();

								pPText->m_text += pPNextText->m_text;

								// Remove and delete next item
								pPText->m_parent->m_childList.RemoveAt(nextpos);
								delete pPNextText;

								((CHTMPElement*)pPText->m_parent)->MoveTextOffsets(thispos, -1);
							}
							else	// In the middle of a word
							{
								POSITION thispos = pPText->m_parent->m_childList.Find(pPText);

							//	m_cursorOffset--;
								pPText->m_text.Delete(m_cursorOffset, 1);

								((CHTMPElement*)pPText->m_parent)->MoveTextOffsets(thispos, -1);
							}
						}
						break;
				#endif

					default:
						return;
					}
				}
			}

		//	ScrollIntoView(m_line, m_col);

			ShowCursor();
		}
	}
#endif
}

#if 0
void VisualContentSource::OnKeyUp(int nKey, int lKeyData)
{
	{
		long virtKey = 0;
		if (nKey == VK_DELETE)
			virtKey = DOM_VK_DELETE;

		CComQIPtr<ILDOMDocumentEvent> documentEvent = GetView()->m_document;
		ASSERT(documentEvent != NULL);

		CComQIPtr<ILDOMElement> documentElement;
		GetView()->m_document->get_documentElement(&documentElement);

		CComQIPtr<ILDOMEventTarget> relatedTarget = documentElement;
		ASSERT(relatedTarget != NULL);

		CComPtr<ILTextEvent> textevt;
	
		documentEvent->createEvent(WSTR("TextEvent"), (ILDOMEvent**)&textevt);
		textevt->initTextEvent(
			WSTR("keyup"),	// typeArg
			VARIANT_TRUE,	// canBubbleArg
			VARIANT_TRUE,	// cancelableArg
			this,	// viewArg
			0,		// detailArg
			NULL,	// outputStringArg
			nKey,	// keyValArg
			virtKey,	// virtKeyValArg
			VARIANT_FALSE,	// visibleOutputGeneratedArg
			VARIANT_FALSE	// numPadArg
			);
		textevt->initModifier(DOM_VK_LEFT_ALT, m_bAlt);

		ASSERT(0);
#if 0
		CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;
		if (svgsvgElement)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget = svgsvgElement;

			VARIANT_BOOL doDefault;
			eventTarget->dispatchEvent(textevt, &doDefault);

			if (doDefault)
			{
				if (svgsvgElement)
				{
					//if (m_bAlt)
					{
						CPoint point;
						GetCursorPos(&point);
						ScreenToClient(&point);

						OnSetCursor(/*HTCLIENT, 0,*/ point);
					}
				}
			}
		}
#endif
	}
}
#endif

#if 0
void VisualContentSource::OnChar(uint16 nKey, int lKeyData)
{
#if 0
	if (nKey == 8) return;
	if (nKey == '\r') nKey = '\n';

	WCHAR c2[2] = {nKey, 0};
//	WCHAR c2[2] = {31000, 0};

	TypeText(c2);

#if 0
	if (m_cursorItem)
	{
		CLXUIText* pPText = (CLXUIText*)m_cursorItem;

		if (nKey == '\n')
		{
#if 0
// Hard RETURN, Put 
			CHTMPElement* pPParent = (CHTMPElement*)m_cursorItem->m_parent;
			CHTMElement* pParent = (CHTMElement*)pPParent->m_pNode;

			CHTMText* pText = (CHTMText*)pPText->m_pNode;

			int len = pText->m_text.GetLength();

		// Split the Text
			CHTMText* pNewText = new CHTMText;
			pNewText->m_HTM = m_pDocument;
			pNewText->m_text = pText->m_text.Right(len - pPText->m_charOffset);

			pText->m_text = pText->m_text.Left(pPText->m_charOffset);

		// Create a new P tag
			CHTMElement* pTag = m_pDocument->createElement("P");

			if (!stricmp(pParent->m_tagName, "P"))
			{
				POSITION pos = pParent->m_pParent->m_childList.Find(pParent);
				pParent->m_pParent->m_childList.InsertAfter(pos, pTag);
				pTag->m_pParent = pParent->m_pParent;
			}
			else
			{
				POSITION pos = pText->m_pParent->m_childList.Find(pText);
				pText->m_pParent->m_childList.InsertAfter(pos, pTag);
				pTag->m_pParent = pText->m_pParent;
			}

		// Add the right side of the split text to the new P tag
			pTag->m_childList.AddTail(pNewText);
			pNewText->m_pParent = pTag;

			pTag->m_pParent->m_pPElement->m_childList.RemoveAll();	// TODO, free also
			pTag->m_pParent->m_pPElement->BuildTree(this, pTag->m_pParent);
#endif
		}
		else
		{
#if 0
			if (nKey == ' ')	// Space
			{
				if (m_cursorOffset > 0)
				{
					CHTMText* pText = (CHTMText*)pPText->m_pNode;

					int len = pPText->m_text.GetLength();
					int rightlen = len-m_cursorOffset;

					if (rightlen > 0)
					{
						if (rightlen < len)
						{
						// Update DOM and Source
							pText->InsertChar(pPText->m_charOffset+m_cursorOffset, nKey, TRUE /* Update source */);

						// Update render
							CLXUIText* pPNewText = new CLXUIText;
							pPNewText->m_pNode = pPText->m_pNode;
							pPNewText->m_pFrame = this;
							pPNewText->m_charOffset = pPText->m_charOffset+m_cursorOffset+1;

							pPNewText->m_text = pPText->m_text.Right(rightlen);
							pPText->m_text = pPText->m_text.Left(m_cursorOffset);

							POSITION pos = pPText->m_parent->m_childList.Find(pPText);

							((CHTMPElement*)pPText->m_parent)->MoveTextOffsets(pos, 1);

							pPText->m_parent->m_childList.InsertAfter(pos, pPNewText);
							pPNewText->m_parent = pPText->m_parent;

						// Position the cursor at the beginning of the newly created item
							m_cursorItem = pPNewText;
							m_cursorOffset = 0;
						}
						else
						{
							m_cursorOffset++;
						}
					}
				}
			}
			else
#endif
			{
				CComQIPtr<ILDOMText> text = pPText->m_pNode;
				ASSERT(text);

				WCHAR data[2] = {nKey, 0};
				text->insertData(m_cursorOffset, data);

				m_cursorOffset++;
			}
		}

		OnSize();
		m_pUI->InvalidateRect(&m_client, TRUE);

		ShowCursor();
	}
#endif
#endif
}
#endif

#if 0
BOOL VisualContentSource::CursorPositionFromPoint(CPoint point, CPNode** pItem, long* offset)
{
	UIElement* pHTMElement = m_VisualTree;

#if 0
	if (pHTMElement->m_pBox)
	{
		return pHTMElement->m_pBox->getPosUnderPoint(point.x, point.y, pItem, offset);
	}
	else
#endif
	{
		*pItem = NULL;
		return FALSE;
	}
}
#endif

#if 0
#if _WINDOWS
DWORD VisualContentSource::OnDragOver(LPDATAOBJECT pDataObject, DWORD dwKeyState, POINTL abspoint)
{
	ASSERT(0);	// I Had this
#if 0
	POINT point;
	point.x = abspoint.x;
	point.y = abspoint.y;
	m_pUI->ScreenToClient(&point);

	point.x -= m_client.left;
	point.y -= m_client.top;

	CHTMPItem* pItem = NULL;
	int offset = 0;

// Erase previous cursor
	DrawCursor(m_dragOverItem, m_dragOverOffset, TRUE);

//	BOOL bOver = m_pRootElement->m_pBox->getPosUnderPoint(point.x, point.y, &m_dragOverItem, &m_dragOverOffset);

	if (CursorPositionFromPoint(point, &m_dragOverItem, &m_dragOverOffset))
	{
	}

// Draw new cursor
	DrawCursor(m_dragOverItem, m_dragOverOffset, TRUE);
#endif

	if (dwKeyState & MK_CONTROL)
		return DROPEFFECT_COPY;
	else
		return DROPEFFECT_MOVE;
}

BOOL VisualContentSource::OnDrop(LPDATAOBJECT hDataObject, DWORD dropEffect, POINTL point)
{
#if 0
// Erase dragover cursor
	DrawCursor(m_dragOverItem, m_dragOverOffset, TRUE);

	COleDataObjectWrapper dataObject;
	dataObject.Attach(hDataObject);

	HGLOBAL hData;

	BOOL success = FALSE;

	if (hData = dataObject.GetGlobalData(CF_HDROP))
	{
		DROPFILES* dp = (DROPFILES*)GlobalLock(hData);
		if (dp)
		{
			WCHAR wfilename[512];
			if (dp->fWide)
			{
				WCHAR* p = (WCHAR*)(dp+1);

				int i = 0;
				while (*p)
				{
					wfilename[i++] = *p++;
				}
				wfilename[i] = 0;
			}
			else
			{
				char* p = (char*)(dp+1);

				int i = 0;
				while (*p)
				{
					wfilename[i++] = *p++;
				}
				wfilename[i] = 0;
			}

			int width = 64;
			int height = 64;

#if 0			// TODO, get size of image
			{
				CIVideo* pVideo = (CIVideo*)sBasic->CreateCmdTarget(IID_AVIDEO);
				ASSERT(pVideo);

				if (pVideo->ImportVideoTags((IV_FileName), (LPCTSTR)filename, (TAG_DONE)) == 0)
				{
					width = pVideo->GetWidth();
					height = pVideo->GetHeight();
				}

				pVideo->Release();
				pVideo = NULL;
			}
#endif

#if 0
			CComPtr<ILHTMLImageElement> img;
			GetView()->m_document->createElementNS(WSTR("http://www.w3.org/1999/xhtml"), WSTR("img"), (ILDOMElement**)&img);
			if (img)
			{
				img->put_src(wfilename/*_bstr_t(filename)*/);

				/*
				if (width > 0)
				{
					char buf[64];

					wsprintf(buf, "%d", width);
					img->setAttribute(WSTR("width"), _bstr_t(buf));

					sprintf(buf, "%d", height);
					img->setAttribute(WSTR("height"), _bstr_t(buf));
				}
				*/

				CLXUIText* pPText = (CLXUIText*)m_dragOverItem;

				CComQIPtr<ILDOMText> text = pPText->m_pNode;

				CComQIPtr<ILDOMNode> parentNode;
				text->get_parentNode(&parentNode);

			// Split the text in two at offset where we want to insert the new element
			// TODO, check for offset=0 and offset=right of text
				CComQIPtr<ILDOMText> rightText;
				text->splitText(m_dragOverOffset, &rightText);

				parentNode->insertBefore(img, _variant_t(rightText), NULL);
			}
#endif
		}

		GlobalUnlock(hData);

		success = TRUE;
	}
	else if (hData = dataObject.GetGlobalData(RegisterClipboardFormat("MMStudio-HTML")))
	{
#if 0
		char* p = (char*)GlobalLock(hData);
		if (p)
		{
			CHTMDoc* pDoc = new CHTMDoc;
			pDoc->m_pText = new CHTMDocument;
			pDoc->m_pText->m_textData = p;
			pDoc->m_pText->m_textLen = lstrlen(p);
			pDoc->parseText();

			CLXUIText* pPText = (CLXUIText*)m_dragOverItem;
			CHTMPElement* pPParent = (CHTMPElement*)pPText->m_parent;
			CHTMElement* pParent = (CHTMElement*)pPParent->m_pNode;

			CHTMElement* pImg = pDoc->m_documentElement;

		// Inserting in middle of text, split text in two and insert the IMG inbetween
			CHTMText* pText = (CHTMText*)pPText->m_pNode;

			int len = pText->m_text.GetLength();
		// Create right text node
			CHTMText* pRightText = m_pDocument->createTextNode(pText->m_text.Right(len - (pPText->m_charOffset + m_dragOverOffset)));

		// Set new text of left text node
			pText->m_text = pText->m_text.Left(pPText->m_charOffset + m_dragOverOffset);

		// Insert IMG, then new text node after the left text node
			POSITION pos = pText->m_pParent->m_childList.Find(pText);
			ASSERT(pos);

			pos = pText->m_pParent->m_childList.InsertAfter(pos, pImg);
			pImg->m_pParent = pText->m_pParent;

			pText->m_pParent->m_childList.InsertAfter(pos, pRightText);
			pRightText->m_pParent = pText->m_pParent;

		// Update source
			pParent->SetInnerHTML(pParent->GetInnerHTML());

		// Rebuild the rendering tree
			pPParent->RemoveChildren();
			pPParent->BuildTree(this, pParent);

		// Invalidate this view
			OnSize();
			m_pUI->InvalidateRect(&m_client);

		// Invalidate all other views
			if (TRUE)
			{
				m_pDocument->m_pText->CreateHTMLTree();
				m_pDocument->m_pText->UpdateAllViews(m_pUI);
			}

			pDoc->m_pText->m_textData = NULL;
			delete pDoc->m_pText;

			pDoc->m_documentElement = NULL;
			delete pDoc;
		}

		GlobalUnlock(hData);

		success = TRUE;
#endif
	}
	else if (hData = dataObject.GetGlobalData(RegisterClipboardFormat("Xmill.ASPath")))
	{
		WCHAR* xml = (WCHAR*)GlobalLock(hData);
		if (xml)
		{
			CLXUIText* pPText = (CLXUIText*)m_dragOverItem;
			CComQIPtr<ILDOMText> text = pPText->m_pNode;
			CComQIPtr<ILDOMNode> parentNode;
			text->get_parentNode(&parentNode);

		//
#if 0
			CComQIPtr<ILDOMElement> parentElement = parentNode;
			BSTR bnodeName;

			BSTR bnamespaceURI;
			parentElement->get_namespaceURI(&bnamespaceURI);
			_bstr_t namespaceURI = _bstr_t(bnamespaceURI, false);

			BSTR btagName;
			parentElement->get_localName(&btagName);	// Try local name first
			if (SysStringLen(btagName) == 0)
			{
				SysFreeString(btagName);
				parentElement->get_tagName(&btagName);	// Then try full qualified name
			}
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(namespaceURI, WSTR("http://www.w3.org/1999/XSL/Transform") && !wcsicmp(tagName, WSTR("for-each"))
			{
			}
#endif

		//
			CComPtr<ILDOMDocument> document;
			document.CoCreateInstance(CLSID_LDOMDocument);
			VARIANT_BOOL bsuccess;
			document->loadXML(xml, &bsuccess);

			GlobalUnlock(xml);

			CComPtr<ILDOMElement> element;

			CComQIPtr<ILDOMElement> node;
			document->get_documentElement(&node);
			while (node)
			{
				BSTR bnodeName;
				node->get_nodeName(&bnodeName);
				_bstr_t nodeName = _bstr_t(bnodeName, false);

				CComPtr<ILDOMElement> element2;
				GetView()->m_document->createElementNS(WSTR("http://www.w3.org/1999/XSL/Transform"), WSTR("xsl:for-each"), &element2);
				if (element2)
				{
					element2->setAttribute(WSTR("select"), nodeName);

					if (element) element2->appendChild(element, NULL);
					element = element2;
				}

				CComPtr<ILDOMNode> firstChild;
				node->get_firstChild(&firstChild);
				node = firstChild;
			}

			if (element)
			{
			// Split the text in two at offset where we want to insert the new element
			// TODO, check for offset=0 and offset=right of text
				CComPtr<ILDOMText> rightText;
				text->splitText(m_dragOverOffset, &rightText);

				parentNode->insertBefore(element, _variant_t(rightText), NULL);

				success = TRUE;
			}
		}
	}

	m_dragOverItem = NULL;
	m_dragOverOffset = -1;

	return success;
#endif
	return 0;
}
#endif // _WINDOWS
#endif

/*
//#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
//#endif

//#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
//#endif
*/

#if 0
STDMETHODIMP VisualContentSource::put_magnify(/*[in]*/ double newVal)
{
	newVal = max(newVal, 0.0001);
	newVal = min(newVal, 99999);

	if (m_magnify != newVal)
	{
		m_magnify = newVal;
		OnSize();	// ??
/*
		PositionFrames();
		*/
#if 0	// I Had this
		if (m_pUI)
		{
			m_pUI->InvalidateRect(&m_client);
		}
#endif

		ASSERT(0);
#if 0
		Fire_onzoom();
#endif
	}

	return S_OK;
}

STDMETHODIMP VisualContentSource::get_currentTranslateX(/*[out, retval]*/ double *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_currentTranslateX;
	return S_OK;
}

STDMETHODIMP VisualContentSource::get_currentTranslateY(/*[out, retval]*/ double *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_currentTranslateY;
	return S_OK;
}

STDMETHODIMP VisualContentSource::setCurrentTranslate(/*[in]*/ double x, /*[in]*/ double y)
{
	ASSERT(0);
#if 0
	if (m_currentTranslateX != x || m_currentTranslateY != y)
	{
		double dx = x - m_currentTranslateX;
		double dy = y - m_currentTranslateY;

		m_currentTranslateX = x;
		m_currentTranslateY = y;

		//OnSize();	// ??
		if (m_scrollX)
		{
			CComQIPtr<IUIScrollBar> scroll = m_scrollX->m_spUnknown;
			scroll->put_pos(-m_currentTranslateX);
		}

		if (m_scrollY)
		{
			CComQIPtr<IUIScrollBar> scroll = m_scrollY->m_spUnknown;
			scroll->put_pos(-m_currentTranslateY);
		}
/*
	PositionFrames();
	*/
		ASSERT(0);
#if 0	// Had this
		if (m_pUI)
		{
			if (TRUE)
			{
				CRect rect = m_imageRect;
				rect.OffsetRect(m_client.left, m_client.top);

				m_pUI->ScrollWindow(int(dx), int(dy), &rect, &rect);
			}
			else
			{
				m_pUI->InvalidateRect(&m_client);
			}
		}
#endif

		ASSERT(0);
#if 0
		Fire_onscroll();
#endif
	}
#endif
	return S_OK;
}
#endif

#if 0
STDMETHODIMP VisualContentSource::GetOleView(/*[out,retval]*/ ILHTMLActiveView* *pVal)
{
	ASSERT(0);
#if 0	// I Had this
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pUI;
	if (*pVal) (*pVal)->AddRef();
#endif
	return S_OK;
}
#endif

#if 0
BEGIN_CMD_MAP(VisualContentSource)
/*
	CMD_HANDLER(ID_VIEW_WORDWRAP, OnViewWordWrap)
	CMD_UPDATE(ID_VIEW_WORDWRAP, OnViewWordWrapUpdate)
	CMD_HANDLER(ID_VIEW_LINENUMBERS, OnViewLineNumbers)
	CMD_UPDATE(ID_VIEW_LINENUMBERS, OnViewLineNumbersUpdate)
	*/
END_CMD_MAP()
#endif

///////////////////////////////////////////////////

#if 0
//////////////////////////
/// IBindStatusCallback

STDMETHODIMP VisualContentSource::OnStartBinding( 
													/* [in] */ DWORD dwReserved,
													/* [in] */ IBinding __RPC_FAR *pib)
{
	return S_OK;
}

STDMETHODIMP VisualContentSource::GetPriority(/* [out] */ LONG __RPC_FAR *pnPriority)
{
	return S_OK;
}

STDMETHODIMP VisualContentSource::OnLowResource(/* [in] */ DWORD reserved)
{
	return S_OK;
}

STDMETHODIMP VisualContentSource::OnProgress( 
											  /* [in] */ ULONG ulProgress,
											  /* [in] */ ULONG ulProgressMax,
											  /* [in] */ ULONG ulStatusCode,
											  /* [in] */ LPCWSTR szStatusText)
{
	return S_OK;
}

STDMETHODIMP VisualContentSource::OnStopBinding( 
												  /* [in] */ HRESULT hresult,
												  /* [unique][in] */ LPCWSTR szError)
{
	return S_OK;
}

STDMETHODIMP VisualContentSource::GetBindInfo( 
												/* [out] */ DWORD __RPC_FAR *grfBINDF,
												/* [unique][out][in] */ BINDINFO __RPC_FAR *pbindinfo)
{
	DWORD cbSize = pbindinfo->cbSize;        
	memset(pbindinfo,0,cbSize);
	pbindinfo->cbSize = cbSize;

//	*grfBINDF = 0;
	*grfBINDF = BINDF_ASYNCHRONOUS;	// Default ?

//	*grfBINDF = BINDF_ASYNCHRONOUS;	// Default ?

	return S_OK;
}

STDMETHODIMP VisualContentSource::OnDataAvailable( 
													 /* [in] */ DWORD grfBSCF,
													 /* [in] */ DWORD dwSize,
													 /* [in] */ FORMATETC __RPC_FAR *pformatetc,
													 /* [in] */ STGMEDIUM __RPC_FAR *pstgmed)
{
#if 0
	m_bufferdata = (BYTE*)realloc(m_bufferdata, m_bufferlen + dwSize);
	if (m_bufferdata)
	{
		ULONG dwRead;
		pstgmed->pstm->Read(m_bufferdata+m_bufferlen, dwSize, &dwRead);

		//ASSERT(dwRead == dwSize);

		m_bufferlen += dwRead;

		return S_OK;
	}
	else
	{
		return E_OUTOFMEMORY;
	}
#endif
	return S_OK;
}

STDMETHODIMP VisualContentSource::OnObjectAvailable( 
														/* [in] */ REFIID riid,
														/* [iid_is][in] */ IUnknown __RPC_FAR *punk)
{
	HRESULT hr;

	m_spUnknown = punk;

	m_spOleObject = m_spUnknown;
	m_spOleDocument = m_spUnknown;

	hr = m_spOleObject->SetClientSite(this);
	hr = m_spOleObject->Advise(this, &m_dwAdvise);

//	hr = OleRun(m_spUnknown);

	CRect rc(0,0,300,300);
	//GetClientRect(&rc);
	hr = m_spOleObject->DoVerb(OLEIVERB_SHOW, NULL, this, 0, m_pUI->m_hWnd, &rc);

	return S_OK;
}
#endif

////////////

#if 0
#include "DOMParser.h"
#include "LDOMNamedNodeMap.h"

long VisualContentSource::GotoLocation(BSTR url)
{
	ASSERT(0);
#if 0
	//FreeImage();

	{
		HRESULT hr;

		CComPtr<IHlinkFrame> pHlinkFrame;

		CComQIPtr<IOleClientSite> pCS = m_pUI->m_document->m_spClientSite;//m_lpClientSite;
		CComQIPtr<IServiceProvider> pSP = pCS;
		if (pSP)
			pSP->QueryService(SID_SHlinkFrame, IID_IHlinkFrame, (void**)&pHlinkFrame);
		
		if (pHlinkFrame == NULL) // Try complicated way
		{
			CComQIPtr<IOleInPlaceSite> pIPS = m_pUI->m_spInPlaceSite;//pCS;

			CComPtr<IOleInPlaceFrame> pIPF;
			CComPtr<IOleInPlaceUIWindow> pIPUI;
			RECT pos, clip;
			OLEINPLACEFRAMEINFO frameInfo;
			pIPS->GetWindowContext(&pIPF, &pIPUI, &pos, &clip, &frameInfo);
			pIPF->QueryInterface(IID_IHlinkFrame, (void**)&pHlinkFrame);
		}

		CComPtr<IHlinkBrowseContext> bc;
		hr = HlinkCreateBrowseContext(NULL, IID_IHlinkBrowseContext, (void**)&bc);

	//	m_pUI->m_document->m_pHBC = bc;

		CComPtr<IMoniker> moniker;

//		if (SUCCEEDED(hr))
		{
			CComPtr<IBindCtx> bindctx;
			hr = CreateAsyncBindCtx(NULL, this, NULL, &bindctx);
		//hr = CreateBindCtx(0, &bindctx);
			if (SUCCEEDED(hr))
			{
			hr = CreateURLMoniker(/*NULL*/m_pUI->m_document->m_curMoniker, url, &moniker);
		//	ULONG chEaten;
		//	hr = MkParseDisplayNameEx(bindctx, url, &chEaten, &moniker);
			ASSERT(SUCCEEDED(hr));

			PSTR rgszTypes[3] =
			{
				"text/html",	// CFSTR_MIME_HTML
				"image/svg+xml",
				"text/plain",
			};

			CLSID rgclsID[3];
			rgclsID[0] = CLSID_LHTMLActiveDocument;
			rgclsID[1] = CLSID_LHTMLActiveDocument;
			rgclsID[2] = CLSID_LHTMLActiveDocument;

			hr = RegisterMediaTypeClass(bindctx, 3, rgszTypes, rgclsID, 0);

			//hr = ::HlinkSimpleNavigateToMoniker(moniker, NULL, NULL, m_pUI->m_document->GetUnknown(), bindctx, NULL/*this*/, 0/*HLNF_INTERNALJUMP*/, 0);
				
				CComPtr<IHlink> hlink;

				hr = HlinkCreateFromMoniker(
					moniker,
					NULL, // pwzLocation
					WSTR("test"),	// friendlyName
					this,//&hlsite,
					1,	// siteData
					NULL,
					IID_IHlink,
					(void**)&hlink);

				hr = hlink->Navigate(0, bindctx, NULL, bc);
				//hr = ::HlinkNavigatehlink, pHlinkFrame, 0, bindctx, NULL, bc);
			}
		}
	}
#if 0
	CComPtr<ILDOMImplementation> impl;
	impl.CoCreateInstance(CLSID_LDOMImplementation);

	CComPtr<ILDOMBuilder> builder;
	impl->createDOMBuilder(1, NULL, &builder);

	CComPtr<ILDOMDocument> document;
	builder->parseURI(url, &document);

	if (document)
	{
	// Look for xsl-stylesheet
		CComPtr<ILDOMNode> child;
		document->get_firstChild(&child);
		while (child)
		{
			CComQIPtr<ILDOMProcessingInstruction> pi = child;
			if (pi)
			{
				BSTR btarget;
				pi->get_target(&btarget);
				_bstr_t target = _bstr_t(btarget, false);

				if (!wcscmp(target, WSTR("stylesheet"))
				{
					BSTR bdata;
					pi->get_data(&bdata);
					_bstr_t data = _bstr_t(bdata, false);

					CComObject<CLDOMNamedNodeMap>* attributes;
					CComObject<CLDOMNamedNodeMap>::CreateInstance(&attributes);
					if (attributes)
					{
						attributes->AddRef();

						CDOMParser parser;
						parser.m_textData = data;
						parser.m_textLen = data.length();
						parser.m_document = document;

						parser.ParseAttributes(NULL, attributes);

						CComPtr<ILDOMAttr> hrefNode;
						attributes->getNamedItem(WSTR("href"), (ILDOMNode**)&hrefNode);
						if (hrefNode)
						{
							BSTR bhref;
							hrefNode->get_value(&bhref);
							_bstr_t href = _bstr_t(bhref, false);

							if (href.length())
							{
								CComPtr<ILDOMDocument> xslDocument;
								VARIANT_BOOL bsuccess;

							// TODO, some monikers, some services already defined for this ??
								CComQIPtr<IXMLDocumentInMemoryProvider> imp = m_pUI->m_document->m_spClientSite;
								if (imp)
								{
									imp->GetInMemoryDocument(href, &xslDocument);
									if (xslDocument)
										bsuccess = VARIANT_TRUE;
								}

								if (xslDocument == NULL)
								{
									xslDocument.CoCreateInstance(CLSID_LDOMDocument);
									xslDocument->load(href, &bsuccess);
								}

								if (bsuccess)
								{
									CComPtr<ILXSLTemplate> xslTemplate;
									xslTemplate.CoCreateInstance(CLSID_LXSLTemplate);
									if (xslTemplate)
									{
										xslTemplate->putref_stylesheet(xslDocument);

										CComPtr<ILXSLProcessor> xslProcessor;

										xslTemplate->createProcessor(&xslProcessor);

										CComPtr<ILDOMElement> documentElement;
										m_document->get_documentElement(&documentElement);

										xslProcessor->put_input(_variant_t((IUnknown*)m_document));
										VARIANT_BOOL done;
										xslProcessor->transform(&done);
										if (done)
										{
											_variant_t output;
											xslProcessor->get_output(&output);

											_bstr_t bstrOutput = output;

										//	::MessageBox(NULL, bstrOutput, "", MB_OK);
										//	VARIANT_BOOL bsuccess;
										//	m_document->loadXML(bstrOutput, &bsuccess);

											CComPtr<ITextData> textData;
											textData.CoCreateInstance(CLSID_TextData);
											textData->put_data(bstrOutput.copy());

											m_document.Release();
											builder->parseTextData(textData, &m_document);
										}
									}
								}
							}
						}

						attributes->Release();
					}
					break;
				}
			}

			CComPtr<ILDOMNode> nextSibling;
			child->get_nextSibling(&nextSibling);
			child = nextSibling;
		}

		/*
		if (m_document)
			m_document->get_documentElement(&m_element);
			*/
		SetDocument(document);
	}
#endif
	//DoneParsing();
#endif

	return 0;
}
#endif

#if 0
STDMETHODIMP VisualContentSource::svgGetRBBox(/*[in]*/ILSVGElement* element, /*[out,retval]*/ ILSVGRect** pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	ASSERT(0);

#if 0
	CComQIPtr<CLSVGElementImplImpl> pElement = element;

	for (int i = 0; i < pElement->m_pNodes.GetSize(); i++)
	{
		if (pElement->m_pNodes[i]->GetView() == GetView())
		{
			CPSVGElementImpl* pSVGElement = (CPSVGElementImpl*)pElement->m_pNodes[i];

			CComObject<CLSVGRect>* pRect;
			CComObject<CLSVGRect>::CreateInstance(&pRect);
			if (pRect)
			{
				RectD bounds = pSVGElement->m_bounds;

				pRect->m_x = bounds.X;
				pRect->m_y = bounds.Y;
				pRect->m_width = bounds.Width;
				pRect->m_height = bounds.Height;

				(*pVal = pRect)->AddRef();
			}

			return S_OK;
		}
	}
#endif

	ASSERT(0);
	return S_OK;
}

STDMETHODIMP VisualContentSource::svgGetBBox(/*[in]*/ILSVGElement* element, /*[out,retval]*/ ILSVGRect** pVal)
{
	ASSERT(0);
#if 0
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	CComQIPtr<CLSVGElementImplImpl> pElement = element;

	for (int i = 0; i < pElement->m_pNodes.GetSize(); i++)
	{
		if (pElement->m_pNodes[i]->m_pWindow == this)
		{
			CPSVGElementImpl* pSVGElement = (CPSVGElementImpl*)pElement->m_pNodes[i];

			CComObject<CLSVGRect>* pRect;
			CComObject<CLSVGRect>::CreateInstance(&pRect);
			if (pRect)
			{
				RectD xbounds = pSVGElement->m_xbounds;

				pRect->m_x = xbounds.X;
				pRect->m_y = xbounds.Y;
				pRect->m_width = xbounds.Width;
				pRect->m_height = xbounds.Height;

				(*pVal = pRect)->AddRef();
			}

			return S_OK;
		}
	}
#endif

	ASSERT(0);
	return S_OK;
}

STDMETHODIMP VisualContentSource::svgGetScreenBBox(/*[in]*/ ILSVGElement *element, /*[out,retval]*/ ILSVGRect **pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	ASSERT(0);
#if 0

	*pVal =  NULL;

	CPSVGElementImpl* pSVGElement = (CPSVGElementImpl*)CComQIPtr<CLSVGElementImplImpl>(element)->GetNodeOnFrame(GetView());

	if (pSVGElement)
	{
		CComObject<CLSVGRect>* psvgRect;
		CComObject<CLSVGRect>::CreateInstance(&psvgRect);
		if (psvgRect)
		{
			psvgRect->AddRef();

			RectD bbox = pSVGElement->GetScreenBBox();

			psvgRect->m_x = bbox.X;
			psvgRect->m_y = bbox.Y;
			psvgRect->m_width = bbox.Width;
			psvgRect->m_height = bbox.Height;

			*pVal = psvgRect;
		}
		return S_OK;
	}
#endif

	ASSERT(0);
	return S_OK;
}
#endif

__release<LDraw::Matrix3f> VisualContentSource::GetViewMatrix() const
{
	return LDraw::Matrix3f::GetIdentity();

//	return gmMatrix3::translate(-m_expandedBBox.X, -m_expandedBBox.Y);
#if 0
	gmMatrix3 mat;
//	mat = m_pMatrix->m_matrix/* *
			gmMatrix3::scale(m_magnify, m_magnify) *
			gmMatrix3::translate(m_currentTranslateX, m_currentTranslateY)*/;

	return mat;
#endif
}

#if 0
gmMatrix3 VisualContentSource::svgGetScreenCTM(CPSVGElementImpl* pSVGElement)
{
	ASSERT(0);
	gmMatrix3 matrix;// Had this = pSVGElement->GetScreenCTM();
#if 0

//#if 0	// Decided to not have this ?
	matrix = matrix * GetViewMatrix();
	/*
	matrix = matrix * gmMatrix3::scale(m_magnify, m_magnify) * gmMatrix3::translate(m_currentTranslateX, m_currentTranslateY);
	matrix = matrix * m_pMatrix->m_matrix;
//#endif
*/
#endif
	return matrix;
}
#endif

#if 0

STDMETHODIMP VisualContentSource::svgGetScreenCTM(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal)
{
	ASSERT(element != NULL);
	ASSERT(pVal != NULL);
	if (element == NULL) return E_INVALIDARG;
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	CPSVGElementImpl* pSVGElement = (CPSVGElementImpl*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(GetView());

	if (pSVGElement)
	{
		CComObject<SVGMatrix>* pMatrix;
		CComObject<SVGMatrix>::CreateInstance(&pMatrix);
		if (pMatrix)
		{
			pMatrix->AddRef();

			pMatrix->m_matrix = svgGetScreenCTM(pSVGElement);//pSVGElement->GetScreenCTM/*2*/();

			//pMatrix->m_matrix = pMatrix->m_matrix * gmMatrix3::scale(m_magnify, m_magnify) * gmMatrix3::translate(m_currentTranslateX, m_currentTranslateY);
			*pVal = pMatrix;
		}
	}

	return S_OK;
}

STDMETHODIMP VisualContentSource::svgGetScreenCTM2(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal)
{
	ASSERT(0);
#if 0
	ASSERT(element != NULL);
	ASSERT(pVal != NULL);
	if (element == NULL) return E_INVALIDARG;
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	CPSVGElementImpl* pSVGElement = (CPSVGElementImpl*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(GetView());

	if (pSVGElement)
	{
		CComObject<SVGMatrix>* pMatrix;
		CComObject<SVGMatrix>::CreateInstance(&pMatrix);
		if (pMatrix)
		{
			pMatrix->AddRef();

			pMatrix->m_matrix = pSVGElement->GetScreenCTM2();

			// ??
			//pMatrix->m_matrix = pMatrix->m_matrix * gmMatrix3::scale(m_magnify, m_magnify) * gmMatrix3::translate(m_currentTranslateX, m_currentTranslateY);
			pMatrix->m_matrix = pMatrix->m_matrix * GetViewMatrix();

			*pVal = pMatrix;
		}
	}
#endif

	return S_OK;
}

STDMETHODIMP VisualContentSource::svgGetScreenNCTM(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal)
{
	ASSERT(0);
	return S_OK;
}

STDMETHODIMP VisualContentSource::svgGetScreenNCTM2(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal)
{
	ASSERT(element != NULL);
	ASSERT(pVal != NULL);
	if (element == NULL) return E_INVALIDARG;
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	CPSVGElementImpl* pSVGElement = (CPSVGElementImpl*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(GetView());

	if (pSVGElement)
	{
		CComObject<SVGMatrix>* pMatrix;
		CComObject<SVGMatrix>::CreateInstance(&pMatrix);
		if (pMatrix)
		{
			pMatrix->AddRef();

			ASSERT(0);
#if 0
			pMatrix->m_matrix = pSVGElement->GetScreenCTM2();

			/*
			// ??
			//pMatrix->m_matrix = pMatrix->m_matrix * gmMatrix3::scale(m_magnify, m_magnify) * gmMatrix3::translate(m_currentTranslateX, m_currentTranslateY);
			pMatrix->m_matrix = pMatrix->m_matrix * GetViewMatrix();
			*/
#endif

			*pVal = pMatrix;
		}
	}

	return S_OK;
}

STDMETHODIMP VisualContentSource::svgGetViewTransformMatrix(/*[out,retval]*/ ILSVGMatrix* *pVal)
{
	ASSERT(0);
	return S_OK;
}

STDMETHODIMP VisualContentSource::svgGetElementViewBoxMatrix(/*[in]*/ ILSVGElement* element, /*[out,retval]*/ ILSVGMatrix* *pVal)
{
	ASSERT(element != NULL);
	ASSERT(pVal != NULL);
	if (element == NULL) return E_INVALIDARG;
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	CPSVGElementImpl* pSVGElement = (CPSVGElementImpl*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(GetView());

	if (pSVGElement)
	{
		CComObject<SVGMatrix>* pMatrix;
		CComObject<SVGMatrix>::CreateInstance(&pMatrix);
		if (pMatrix)
		{
			pMatrix->AddRef();
			ASSERT(0);
#if 0
			pMatrix->m_matrix = pSVGElement->GetViewBoxMatrix();
#endif
			*pVal = pMatrix;
		}
	}

	return S_OK;
}
#endif

#if 0
STDMETHODIMP VisualContentSource::get_selection(ILDOMRange **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_range;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}
#endif

#if 0
STDMETHODIMP VisualContentSource::get_contentWidth(double *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = GetSVGWidth();
	return S_OK;
}

STDMETHODIMP VisualContentSource::get_contentHeight(double *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = GetSVGHeight();
	return S_OK;
}
#endif

#if 0
STDMETHODIMP VisualContentSource::ZoomToRect(double x, double y, double width, double height, VARIANT_BOOL bAnimate)
{
	ASSERT(0);
#if 0
	double oldmagnify;
	double translateX;
	double translateY;
	get_magnify(&oldmagnify);
	get_currentTranslateX(&translateX);
	get_currentTranslateY(&translateY);

	long innerWidth;
	long innerHeight;
	get_innerWidth(&innerWidth);
	get_innerHeight(&innerHeight);

	CRect m_areaRect;
	m_areaRect.left = 0;
	m_areaRect.top = 0;
	m_areaRect.right = innerWidth;
	m_areaRect.bottom = innerHeight;

	CDblRect zoomRect;
	zoomRect.left = x;
	zoomRect.top = y;
	zoomRect.right = x+width;
	zoomRect.bottom = y+height;

// Convert screen rectangle to viewport
	CDblRect zoomdrect;
	zoomdrect.left = (zoomRect.left-translateX)/oldmagnify;// + translateX;
	zoomdrect.top = (zoomRect.top-translateY)/oldmagnify;// + translateY;
	zoomdrect.right = (zoomRect.right-translateX)/oldmagnify;// + translateX;
	zoomdrect.bottom = (zoomRect.bottom-translateY)/oldmagnify;// + translateY;

// Set new scale
	double magnify = oldmagnify * (double)(m_areaRect.Width())/zoomRect.Width();

// Set new translate XY
	double cx = zoomdrect.left*magnify;//*magnify - translateX;
	double cy = zoomdrect.top*magnify;//*magnify - translateY;

	if (bAnimate)
	{
		ASSERT(0);
#if 0	// Had this
		if (m_pUI)
		{
			HWND hWnd = m_pUI->m_hWnd;
			if (hWnd)
			{
				HDC hDC = ::GetDC(hWnd);
				int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

				HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

				CDblRect imageRect;
				imageRect.left = m_areaRect.left;
				imageRect.top = m_areaRect.top;
				imageRect.right = m_areaRect.right;
				imageRect.bottom = m_areaRect.bottom;

				CDblRect fromrect;
				CDblRect torect;

				if (magnify > oldmagnify) // Zoom in
				{
					fromrect = zoomRect;
					torect = imageRect;
				}
				else
				{
					fromrect = imageRect;
					//torect = zoomRect;
/*
					torect.left = imageRect.left*magnify/oldmagnify + translateX;
					torect.top = imageRect.top*magnify/oldmagnify + translateY;
					torect.right = imageRect.right*magnify/oldmagnify + translateX;
					torect.bottom = imageRect.bottom*magnify/oldmagnify + translateY;
*/
					torect.left = (imageRect.left-translateX)*magnify/oldmagnify - cx;
					torect.top = (imageRect.top-translateY)*magnify/oldmagnify - cy;
					torect.right = (imageRect.right-translateX)*magnify/oldmagnify - cx;
					torect.bottom = (imageRect.bottom-translateY)*magnify/oldmagnify - cy;

/*
					torect.left *= magnify/oldmagnify;
					torect.top *= magnify/oldmagnify;
					torect.right *= magnify/oldmagnify;
					torect.bottom *= magnify/oldmagnify;
*/
		//			ASSERT(0);
				}

				int atotal = 40;

				CRect rect;

				for (int i = 0; i <= atotal; i++)
				{
					if (i > 0)	// Erase previous rectangle
						Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

					rect.left = fromrect.left + (torect.left - fromrect.left)*i/atotal;
					rect.top = fromrect.top + (torect.top - fromrect.top)*i/atotal;
					rect.right = fromrect.right + (torect.right - fromrect.right)*i/atotal;
					rect.bottom = fromrect.bottom + (torect.bottom - fromrect.bottom)*i/atotal;

				// Draw rectangle
					Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

					Sleep(5);
				}

			// Erase last rect
				Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

				SelectObject(hDC, hOldBrush);
				SetROP2(hDC, oldR2);
				::ReleaseDC(hWnd, hDC);
			}
		}
#endif
	}

	put_magnify(magnify);
	setCurrentTranslate(-cx, -cy);
#endif

	return S_OK;
}

STDMETHODIMP VisualContentSource::setInnerSize(/*[in]*/ long width, /*[in]*/ long height)
{
	m_imageRect.right = width;
	m_imageRect.bottom = height;

	Flow();

	return S_OK;
}

STDMETHODIMP VisualContentSource::DrawToBuffer(/*[in]*/ long width, /*[in]*/ long height, /*[in]*/ long rowbytes, /*[in]*/ long pixelFormat, /*[in]*/ void* buffer)
{
	return S_OK;
}
#endif

#if 0
STDMETHODIMP VisualContentSource::DrawToHdc(HDC hDC, ILDOMElement *element, double magnify)
{
	if (m_pRootElement)
	{
	// TODO
		CPSVGElementImpl* pSVGElement = (CPSVGElementImpl*)m_pRootElement->FindDOMElement(element);

		Gdiplus::Graphics graphics(hDC);

		CHTMRenderContext rcontext;

		ASSERT(0);
#if 0

		rcontext.m_clip = pSVGElement->m_expandedBBox;

		//Gdiplus::GraphicsState state = graphics.Save();	// TODO, just save matrix, it's probably faster

		graphics.ScaleTransform(float(magnify), float(magnify));
		pSVGElement->Render(&rcontext, &graphics, magnify, magnify);
	//	pSVGElement->Render2(&graphics, magnify, magnify);
#endif

		//graphics.Restore(state);
	}
	else
		ASSERT(0);

	return S_OK;
}

STDMETHODIMP VisualContentSource::DrawToHdc4(HDC hDC, ILDOMElement *element, double magnify)
{
	if (m_pRootElement)
	{
// TODO
		CPSVGElementImpl* pSVGElement = (CPSVGElementImpl*)m_pRootElement->FindDOMElement(element);
		if (pSVGElement)
		{
			Gdiplus::Graphics graphics(hDC);

			CHTMRenderContext rcontext;
			ASSERT(0);
#if 0
		// TODO, is this correct, or should it be m_bounds ?
			rcontext.m_clip = Gdiplus::RectF(0, 0, pSVGElement->m_bounds.Width, pSVGElement->m_bounds.Height);//m_expandedBBox;

		//	Gdiplus::GraphicsState state = graphics.Save();	// TODO, just save matrix, it's probably faster

			graphics.ScaleTransform(float(magnify), float(magnify));
			pSVGElement->Render4(&rcontext, NULL, &graphics, magnify, magnify, FALSE, FALSE);
#endif
		//	graphics.Restore(state);
		}
	}
	else
		ASSERT(0);

	return S_OK;
}
#endif

#if 0
STDMETHODIMP VisualContentSource::svgDrawElementToBuffer(/*[in]*/ ILSVGElement* element, /*[in]*/ ILSVGMatrix* pmatrix, /*[in]*/ long width, /*[in]*/ long height, /*[in]*/ long rowbytes, /*[in]*/ long pixelFormat, /*[in]*/ void* buffer)
{
	if (m_pRootElement)
	{
// TODO
		CPSVGElementImpl* pSVGElement = (CPSVGElementImpl*)m_pRootElement->FindDOMElement(element);
		if (pSVGElement)
		{
			Gdiplus::Bitmap bitmap(width, height, rowbytes, pixelFormat, (LPBYTE)buffer);
			{
				Gdiplus::Graphics graphics(&bitmap);

				CHTMRenderContext rcontext;
			// TODO, is this correct, or should it be m_bounds ?
			//	rcontext.m_clip = Gdiplus::RectF(0, 0, pSVGElement->m_bounds.Width, pSVGElement->m_bounds.Height);//m_expandedBBox;
				rcontext.m_clip = Gdiplus::RectF(0, 0, width, height);

				//Gdiplus::GraphicsState state = graphics.Save();	// TODO, just save matrix, it's probably faster

				Matrix matrix = static_cast<SVGMatrix*>(pmatrix)->m_matrix;

				Gdiplus::Matrix gdipmatrix;
				matrix.GetGdipMatrix(gdipmatrix);
				graphics.SetTransform(&gdipmatrix);

				double scaleX, scaleY;
				CalculateScale(matrix, &scaleX, &scaleY);

				ASSERT(0);
#if 0

				//graphics.ScaleTransform(float(magnify), float(magnify));
				pSVGElement->Render4(&rcontext, NULL, &graphics, scaleX, scaleY, FALSE, FALSE);
#endif
				//graphics.Restore(state);
			}
		}
	}
	else
		ASSERT(0);

	return S_OK;
}
#endif

#if 0
STDMETHODIMP VisualContentSource::get_noscroll(VARIANT_BOOL *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_noscroll;
	return S_OK;
}

STDMETHODIMP VisualContentSource::put_noscroll(VARIANT_BOOL newVal)
{
	m_noscroll = newVal;
	return S_OK;
}
#endif

#if 0
STDMETHODIMP VisualContentSource::LocateCursor(ILDOMNode *container, long offset)
{
	m_curContainer = m_pRootElement->FindDOMElement(container);
	m_curOffset = offset;
	ASSERT(m_curOffset >= 0);

	if (m_range)
	{
		m_range->setStart(container, offset);
		m_range->setEnd(container, offset);
	}

	ASSERT(0);
#if 0	// TODO have this
	if (m_pUI)
	{
		if (m_pUI->m_hWnd)
		{
			CRect rect = m_imageRect;
			rect.OffsetRect(m_client.left, m_client.top);
			m_pUI->InvalidateRect(&rect);
		}
	}
#endif

	return S_OK;
}
#endif

#if 0
STDMETHODIMP VisualContentSource::svgGetPositionOfGlyph(ILSVGTextContentElement *element, long glyphnum, ILSVGPoint **pVal)
{
	ASSERT(0);
#if 0
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;
	
	CPSVGElement* pSVGElement = (CPSVGElement*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(GetView());

	if (pSVGElement)
	{
/*
	for (int i = 0; i < pElement->m_pNodes.GetSize(); i++)
	{
		if (pElement->m_pNodes[i]->m_pWindow == this)
		{
			CPSVGTextContentElement* pSVGElement = (CPSVGTextContentElement*)pElement->m_pNodes[i];
			*/

			CGlyph* pGlyph = pSVGElement->GetGlyphAtIndex(glyphnum);

			CComObject<CLSVGPoint>* pPoint;
			CComObject<CLSVGPoint>::CreateInstance(&pPoint);
			if (pPoint)
			{
				pPoint->AddRef();

				pPoint->m_x = pGlyph->m_position.X;
				pPoint->m_y = pGlyph->m_position.Y;

				*pVal = pPoint;
			}
//		}
	}
#endif

	return S_OK;
}

STDMETHODIMP VisualContentSource::svgGetGlyphSegList(ILSVGTextContentElement *element, long glyphnum, ILSVGPathSegList **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP VisualContentSource::svgGetNumberOfGlyphs(ILSVGTextContentElement *element, long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	ASSERT(0);
#if 0

	CPSVGElement* pSVGElement = (CPSVGElement*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(GetView());
//	CLSVGTextElement* pElement = static_cast<CLSVGTextElement*>(element);

//	for (int i = 0; i < pElement->m_pNodes.GetSize(); i++)
//	{
//		if (pElement->m_pNodes[i]->m_pWindow == this)
		if (pSVGElement)
		{
			//CPSVGTextContentElement* pSVGElement = (CPSVGTextContentElement*)pElement->m_pNodes[i];

			*pVal = pSVGElement->GetNumberOfGlyphs();
		}
//	}
#endif

	return S_OK;
}

STDMETHODIMP VisualContentSource::svgGetGlyphTextContentElement(ILSVGTextContentElement *element, long glyphnum, ILSVGTextContentElement **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP VisualContentSource::svgAddGlyphToSegList(ILSVGTextContentElement *element, long glyphnum, ILSVGPathSegList *seglist)
{
	ASSERT(0);
#if 0
//	CLSVGTextElement* pElement = static_cast<CLSVGTextElement*>(element);

	CPSVGElement* pSVGElement = (CPSVGElement*)CComQIPtr<CLDOMElementImplImpl>(element)->GetNodeOnFrame(GetView());

//	for (int i = 0; i < pElement->m_pNodes.GetSize(); i++)
//	{
//		if (pElement->m_pNodes[i]->m_pWindow == this)
		if (pSVGElement)
		{
			//CPSVGTextContentElement* pSVGElement = (CPSVGTextContentElement*)pElement->m_pNodes[i];

			CGlyph* pGlyph = pSVGElement->GetGlyphAtIndex(glyphnum);
			if (pGlyph)
			{
				if (pGlyph->m_seglist)
				{
					static_cast<CLSVGPathSegList*>(seglist)->AddSegList(pGlyph->m_seglist);
				}
			}
		}
	//}
#endif

	return S_OK;
}

STDMETHODIMP VisualContentSource::svgGetFilterRegion(ILSVGElement *element, ILSVGRect **pVal)
{
	ASSERT(0);
#if 0
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal =  NULL;

	CComQIPtr<CLSVGElementImplImpl> pElement(element);

	for (int i = 0; i < pElement->m_pNodes.GetSize(); i++)
	{
		if (pElement->m_pNodes[i]->m_pWindow == this)
		{
			CPSVGElementImpl* pSVGElement = (CPSVGElementImpl*)pElement->m_pNodes[i];

			CComObject<CLSVGRect>* psvgRect;
			CComObject<CLSVGRect>::CreateInstance(&psvgRect);
			if (psvgRect)
			{
				psvgRect->AddRef();

				RectD bbox = pSVGElement->m_filterRect;

				psvgRect->m_x = bbox.X;
				psvgRect->m_y = bbox.Y;
				psvgRect->m_width = bbox.Width;
				psvgRect->m_height = bbox.Height;

				*pVal = psvgRect;
			}

			return S_OK;
		}
	}

	ASSERT(0);
#endif

	return S_OK;
}
#endif

#if 0
STDMETHODIMP VisualContentSource::get_showMarkup(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_bShowMarkup;
	return S_OK;
}

STDMETHODIMP VisualContentSource::put_showMarkup(VARIANT_BOOL newVal)
{
	ASSERT(0);
#if 0
	if (m_bShowMarkup != newVal)
	{
		m_bShowMarkup = newVal;

		CalcDims(m_pRootElement);

		ASSERT(0);
#if 0	// Had this
		if (m_pUI)
		{
			Flow();

			if (m_pUI->m_hWnd)
			{
				m_pUI->Invalidate();
			}
		}
#endif
	}
#endif

	return S_OK;
}
#endif

#if 0
void VisualContentSource::scrollIntoView(CLDependencyObjectImpl *pElement)
{
	ASSERT(0);
#if 0
	if (pElement->m_boxList.GetSize() > 0)
	{
		CHTMBoxItem* pBox = pElement->m_boxList[0];

		//Gdiplus::RectF rc = pBox->m_outerRect;

	// Find the nearest parent block box with scrollbars
		CHTMBoxItem* pBox2 = pBox->m_parentBox;
		while (pBox2)
		{
		//	rc.Offset(pBox2->m_outerRect.X, pBox2->m_outerRect.Y);

			if (pBox2->m_type == boxTypeBlock)
			{
				CHTMBlockBox* pBlockBox = (CHTMBlockBox*)pBox2;

				Gdiplus::RectF rc2 = pBlockBox->GetAbsOuterRect();

				Gdiplus::RectF rc = pBox->GetAbsOuterRect();
				rc.Offset(-rc2.X, -rc2.Y);

				if (pBlockBox->m_pElement->m_scrollY)
				{
					CComQIPtr<IUIScrollBar> scrollY = pBlockBox->m_pElement->m_scrollY->m_spUnknown;

					long scrollposY;
					scrollY->get_pos(&scrollposY);

					if (rc.GetBottom() > pBlockBox->m_innerRect.Height+scrollposY)
					{
					// scroll down
						scrollposY += rc.GetBottom()-(pBlockBox->m_innerRect.Height+scrollposY);

						pBlockBox->m_pElement->m_scrollY->OnScroll(0, scrollposY);
					}
					else if (rc.GetTop() < scrollposY)
					{
					// scroll up
						scrollposY += rc.GetTop() - scrollposY;

						if (scrollposY < 0) scrollposY = 0;

						pBlockBox->m_pElement->m_scrollY->OnScroll(0, scrollposY);
					}
				}
			}

			pBox2 = pBox2->m_parentBox;
		}

		//Gdiplus::RectF rc = pBox->GetAbsOuterRect();
	}
#endif
}
#endif

#if 0
STDMETHODIMP VisualContentSource::scrollIntoView(ILDOMElement *element)
{
	CPElement* pElement = (CPElement*)m_pRootElement->FindDOMElement(element);
	if (pElement)
	{
		scrollIntoView(pElement);
	}

	return S_OK;
}
#endif

void VisualContentSource::set_VisualTree(UIElement* newVal)
{
//	printf("VisualContentSource::set_VisualTree\n");

//	if (newVal != m_VisualTree)
	{
		m_Content = newVal;

		if (m_Content)
		{
			m_Content->SetOwnerWindow(this);
		}

		//Control::set_VisualTree(newVal);

//		m_VisualTree = newVal;
//		m_VisualTree->SetOwnerWindow(this);
	}
}

void VisualContentSource::AddRChild(UIElement* pChild)
{
	ASSERT(0);
	/*
	ASSERT(pChild->m_rparent == NULL);
	pChild->m_rparent = this;

	VisualContentSource* pOwnerWindow = this;
	if (pOwnerWindow != pChild->m_pOwnerWindow)
		pChild->SetOwnerWindow(pOwnerWindow);

	m_rchildList->m_items.Add(pChild);
	*/
}

#if 0
void VisualContentSource::InvalidateRect(const LDraw::RectD& rect)
{
	if (m_pSite)
	{
		m_pSite->InvalidateRect(rect);
	}
}
#endif

#if 0
// virtual
void VisualContentSource::InvalidateChildRect(const LDraw::RectD& rect, LDraw::Matrix3f* transform)
{
	m_bRenderValid = false;	// ??

	LDraw::RectD xrect;
	LDraw::GetTransformRectBoundingBox(transform, rect, &xrect);

#if 0//AMIGA

	if (m_pSite)
	{
		m_pSite->InvalidateRect(LDraw::RectI(xrect.X, xrect.Y, xrect.Width, xrect.Height));
	}

#else
	__release<LDraw::Region> rgn = new LDraw::Region(LDraw::RectI(xrect.X, xrect.Y, ceil(xrect.Width), ceil(xrect.Height)));

//	printf("VisualContentSource::InvalidateChildRect\n");
//	return;

//#if 0	// TODO
//	rgn.Union(xrect);
//#endif

	if (m_pSite)
	{
		m_pSite->InvalidateRegion(rgn);
	}
#endif
}
#endif

#if 0
void VisualContentSource::OnKeyDown(int vk, bool bControl, bool bShift)
{
	IInputElement* p = m_pElementFocus;
	if (p == NULL)
	;//	p = m_pClientVisual;

	if (p)
	{
		ASSERT(0);
#if 0
		KeyEvent* evt = new KeyEvent;
		evt->InitEvent(WSTR("keydown"), true, true);
		evt->vk = vk;
		evt->bControl = bControl;
		evt->bShift = bShift;

		bool doDefault = p->dispatchEvent(evt);

		delete evt;
#endif
	}
}
#endif

void VisualContentSource::OnKeyUp(int vk, bool bControl, bool bShift)
{
}

void VisualContentSource::OnChar(int nChar, bool bControl, bool bShift)
{
	if (m_pElementFocus)
	{
		TextCompositionEventArgs* textArgs = new TextCompositionEventArgs(NULL, NULL);
		WCHAR wChar = nChar;
		textArgs->m_text = new StringW(string_copy(&wChar, 1));

		InputManager* inputManager = InputManager::get_Current();

		StagingAreaInputItem* stagingItem = new StagingAreaInputItem;
		stagingItem->m_input = textArgs;

		PreProcessInputEventArgs* preprocessArgs = new PreProcessInputEventArgs;
		preprocessArgs->m_inputManager = inputManager;
		preprocessArgs->m_stagingItem = stagingItem;	

		inputManager->PreProcessInput(inputManager/*??*/, preprocessArgs);
		//inputManager->PreNotifyInput(inputManager/*??*/, preprocessArgs);

	//	keyArgs->set_RoutedEvent(Mouse::s_PreviewMouseDownEvent);
	//	eventTarget->RaiseEvent(mouseArgs);

		textArgs->set_RoutedEvent(TextCompositionManager::s_TextInputEvent);
		m_pElementFocus->RaiseEvent(textArgs);
	}

#if 0
		CharEvent* evt = new CharEvent;
		evt->InitEvent(WSTR("char"), true, true);
		evt->cCharCode = nChar;    // character code 
		evt->bControl = bControl;
		evt->bShift = bShift;

		m_pElementFocus->dispatchEvent(evt);

		delete evt;
#endif
}

/*
void VisualContentSource::InvalidateRegion(const LDraw::Rgn* pRgn)
{
	if (m_pSite)
	{
		m_pSite->InvalidateRegion(pRgn);
	}
}
*/

LDraw::PointD VisualContentSource::TransformPointToClient(LDraw::PointD point)
{
	ASSERT(0);

//	point = m_Content->TransformPointToClient(point);

	LDraw::RectI rect;
//	dynamic_cast<WindowHost*>(m_pSite)->GetWindowRect(&rect);
	return LDraw::PointD(point.X - rect.X, point.Y - rect.Y);
}

}	// UI
}
