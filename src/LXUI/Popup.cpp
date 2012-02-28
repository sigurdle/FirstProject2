#include "stdafx.h"
#include "LXUI2.h"
#include "Popup.h"

namespace System
{
namespace UI
{

DependencyProperty* Popup::s_ChildProperty = RegisterProperty(WSTR("Child"), typeid(Object), typeid(Popup), NULL, PropertyMetaData(None));
DependencyProperty* Popup::s_IsOpenProperty = RegisterProperty(WSTR("IsOpen"), typeid(bool), typeid(Popup), BoolObject::get_False(), PropertyMetaData(None));
DependencyProperty* Popup::s_StaysOpenProperty = RegisterProperty(WSTR("StaysOpen"), typeid(bool), typeid(Popup), BoolObject::get_True(), PropertyMetaData(None));
DependencyProperty* Popup::s_PopupAnimationProperty = RegisterProperty(WSTR("PopupAnimation"), typeid(PopupAnimation), typeid(Popup), IntObject::GetObject(PopupAnimation_None), PropertyMetaData(None));

Popup::Popup()
{
	TRACE("Popup::Popup()\n");

	{
	//	m_pAttachedToMenuElement = NULL;

#if 0
		SetAlpha(true);
#endif

//		m_pContent = NULL;
	}
}

#if 0
void Popup::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();

#if 0
	if (GetCapture() == m_hWnd && (phase == CAPTURING_PHASE || phase == AT_TARGET) && type == OLESTR("mouseout"))
	{
		MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

		long screenX = mouseEvt->get_ScreenX();
		long screenY = mouseEvt->get_ScreenY();

		RECT wrect;
		GetWindowRect(m_hWnd, &wrect);
		LDraw::RectI rect(wrect);

		if (!rect.Contains(screenX, screenY))
		{
			MouseEvent* evt = new MouseEvent;
			evt->InitMouseEvent(OLESTR("cancel"),	// "onpopuphiding"	???
				screenX,
				screenY
				);

			bool doDefault = dispatchEvent(evt);

			if (doDefault)
			{
				Close();
			}
			delete evt;
		}
	}
#endif

	if (phase != CAPTURING_PHASE)
	{
#if 0
		if (type == MouseEvent::mouseout)
		{
		//	if (phase == AT_TARGET)
			{
		//		MessageBeep(-1);
			}
			/*
			evt->stopPropagation();

			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

			long screenX = mouseEvt->get_ScreenX();
			long screenY = mouseEvt->get_ScreenY();

			RECT wrect;
			GetWindowRect(m_hWnd, &wrect);
			LDraw::RectI rect(wrect);

			if (!rect.Contains(screenX, screenY))
			{
				MouseEvent* evt = new MouseEvent;
				evt->InitMouseEvent(OLESTR("cancel"),	// "onpopuphiding"	???
					screenX,
					screenY
					);

				bool doDefault = dispatchEvent(evt);

				if (doDefault)
				{
					Close();
				}
			}
			*/
		}
		else
#endif
			if (*type == L"mousedown")
		{
			evt->stopPropagation();

			MouseEvent* mouseEvt = static_cast<MouseEvent*>(evt);

			long screenX = mouseEvt->get_ScreenX();
			long screenY = mouseEvt->get_ScreenY();

			LDraw::RectD rect =
		//	m_pWindowHost->GetWindowRect(&rect);
			GetScreenBounds();

			if (!rect.Contains(screenX, screenY))
			{

				MouseEvent* cancelEvt = new MouseEvent;
				cancelEvt->InitMouseEvent(WSTR("cancel"),	// "onpopuphiding"	???
					mouseEvt->GetOwnerWindow(),
					screenX,
					screenY,
					mouseEvt->m_bShift,
					mouseEvt->m_bCtrl
					);

				bool doDefault = dispatchEvent(cancelEvt);
#if 0
				if (doDefault)
				{
					m_pWindowHost->Close();
					/*
					MouseEvent* mouseEvt = new MouseEvent;
					mouseEvt->InitMouseEvent(L"mousedown", screenX, screenY);
					m_pAttachedToMenuElement->dispatchEvent(mouseEvt);
					*/
				}
#endif
				delete cancelEvt;
			}
			else
			{
				MessageBeep(-1);
			}
		}
		else if (*type == L"onpopupshowing")
		{
			if (phase != AT_TARGET)
			{
			;//	evt->preventDefault();
			}
		}
		else if (*type == L"cancel")
		{
			MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

			long screenX = mouseEvt->get_ScreenX();
			long screenY = mouseEvt->get_ScreenY();

			LDraw::RectD rect = GetScreenBounds();
		//	m_pWindowHost->GetWindowRect(&rect);

			if (!rect.Contains(screenX, screenY))
			{
				// If the mouse isn't within out window, close our window, and let the 'cancel' event bubble upwards
				dynamic_cast<WindowHost*>(GetOwnerWindow()->m_pSite)->Close();
			}
			else
			{
				// If the mouse is within our window, stop the 'cancel' propagation here and set the capture to our window
				evt->stopPropagation();
				dynamic_cast<WindowHost*>(GetOwnerWindow()->m_pSite)->SetCapture();

#if _WINDOWS
				/*
				// And then 'fake' a mouse click also
				*/

#if 0	// TODO
				POINT point;
				point.x = screenX;
				point.y = screenY;
				::ScreenToClient(dynamic_cast<CUIFrameImpl*>(/*get_OwnerWindow()->*/m_pWindowHost)->m_hWnd, &point);

				/*get_OwnerWindow()->*/OnMouseMove(0, LDraw::PointI(screenX, screenY), LDraw::PointI(point.x, point.y));
				/*get_OwnerWindow()->*/OnButtonDown(0, LDraw::PointI(screenX, screenY), LDraw::PointI(point.x, point.y), 0, false);
#endif
#endif
			}
		}
	}
}
#endif

void Popup::PopupWindowBase::OnMouseDown(UINT nFlags, LDraw::PointD screenpos, LDraw::PointD clientpos, int iButton, bool bDblClk)
{
	if (!m_popup->get_StaysOpen())
	{
		LDraw::RectD windowRect;
		m_pSite->GetLogicalWindowRect(&windowRect);

		if (!windowRect.Contains(screenpos))
		{
			// ???? TODO, send cancel event

			m_popup->set_IsOpen(false);
			/*

			Popup* popup = m_popup;
			popup->m_pSite->Close();
			popup->m_pSite = NULL;
			*/
			return;
		}
	}

	VisualContentSource::OnMouseDown(nFlags, screenpos, clientpos, iButton, bDblClk);
}

void Popup::PopupWindowBase::OnMouseLeave(LDraw::PointD screenpos, LDraw::PointD clientpos)
{
	VisualContentSource::OnMouseLeave(screenpos, clientpos);
}

void Popup::PopupWindowBase::OnLostMouseCapture()
{
	if (!m_popup->get_StaysOpen())
	{
		m_popup->set_IsOpen(false);
	}
}

uint32 Popup::PopupWindowBase::GetWindowStyle(uint32 windowStyle)
{
	windowStyle |= WS_POPUP;
	/*
	windowStyle |= WS_CAPTION;
	windowStyle |= WS_SYSMENU;
	windowStyle |= WS_THICKFRAME;
	windowStyle |= WS_MINIMIZEBOX;
	windowStyle |= WS_MAXIMIZEBOX;
	*/

	return windowStyle;
}

uint32 Popup::PopupWindowBase::GetWindowAnimate()
{
	// TODO

	return m_popup->get_PopupAnimation() != PopupAnimation_None;
}

#if 0
void Popup::OnMouseDown(MouseButtonEventArgs* args)
{
//	MSWindows::RECT wrect;
//	MSWindows::GetWindowRect(m_pSite->GetHwnd(), &wrect);
	// cancel/popup hiding event
	LDraw::RectI wrect;
	m_pSite->GetWindowRect(&wrect);

	Point screenpos = args->GetScreenPosition();

	if (!get_StaysOpen())
	{
		if (screenpos.X < wrect.X ||
			screenpos.Y < wrect.Y ||
			screenpos.X < wrect.GetRight() ||
			screenpos.Y > wrect.GetBottom())
		{
			// ???? TODO, send cancel event

			m_pSite->Close();
			m_pSite = NULL;
		}
	}
}
#endif

#if 0
LRESULT Popup::OnLButtonDown(Event* evt)
{
	ASSERT
	/*
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	CRect client;
	GetClientRect(&client);
	*/


	if (!client.PtInRect(point))
	{
	// Fire event
		CComQIPtr<ILDOMDocumentEvent> documentEvent = m_ownerDocument;
		ASSERT(documentEvent);

		CComPtr<ILDOMEvent> evt;
		documentEvent->createEvent(L""/*UIEvents"*/, &evt);
		evt->initEvent(L"cancel",	// "onpopuphiding"	???
			VARIANT_TRUE,	// bubbles
			VARIANT_TRUE	// cancelable
			);

		ASSERT(evt);
		if (evt)
		{
			CComQIPtr<ILDOMEventTarget> eventTarget(GetUnknown());
			ASSERT(eventTarget);

			VARIANT_BOOL doDefault;
			eventTarget->dispatchEvent(evt, &doDefault);

			if (doDefault)
			{
			}
		}

		return 0;
	}
	else
	{
		return baseClass::OnLButtonDown(uMsg, wParam, lParam, bHandled);
	}
}
#endif

LDraw::SizeD Popup::MeasureOverride(LDraw::SizeD availSize)
{
	return LDraw::SizeD(0, 0);
}

LDraw::SizeD Popup::ArrangeOverride(LDraw::SizeD finalSize)
{
//	ASSERT(finalSize.Width == 0);
//	ASSERT(finalSize.Height == 0);
	return finalSize;
}

bool Popup::get_IsOpen()
{
	return static_cast<BoolObject*>(GetValue(get_IsOpenProperty()))->GetValue();
}

void Popup::set_IsOpen(bool isOpen)
{
	SetValue(get_IsOpenProperty(), BoolObject::GetObject(isOpen));
}

bool Popup::get_StaysOpen()
{
	return static_cast<BoolObject*>(GetValue(get_StaysOpenProperty()))->GetValue();
}

void Popup::set_StaysOpen(bool staysOpen)
{
	SetValue(get_StaysOpenProperty(), BoolObject::GetObject(staysOpen));
}

PopupAnimation Popup::get_PopupAnimation()
{
	return (PopupAnimation)static_cast<IntObject*>(GetValue(get_PopupAnimationProperty()))->GetValue();
}

void Popup::set_PopupAnimation(PopupAnimation popupAnimation)
{
	SetValue(get_PopupAnimationProperty(), IntObject::GetObject(popupAnimation));
}

UIElement* Popup::get_Child()
{
	return static_cast<UIElement*>(GetValue(get_ChildProperty()));
}

void Popup::set_Child(UIElement* child)
{
	SetValue(get_ChildProperty(), child);
//	m_pContent = pContent;

#if 0
#if 0//WIN32
	DropShadow* pShadow = new DropShadow;
	{
		Border* pBorder = new Border(Thickness(Length(1), Length(1), Length(1), Length(1)));
		{
			pBorder->set_Content(m_pContent);
		}
		pShadow->set_Content(pBorder);
	}
	//pShadow->SetOwnerWindow(this);
	set_VisualTree(pShadow);

#else

	Border* pBorder = new Border(new Thickness(1));
	{
		pBorder->set_Child(m_pContent);
	}
//	pBorder->SetOwnerWindow(this);
	set_VisualTree(pBorder);

#endif
#endif
}

void Popup::SetOwnerWindow(VisualContentSource* pWindow)
{
	if (pWindow == NULL)
	{
		if (m_pSite)
		{
			m_pSite->Close();
			m_pSite = NULL;
		}
	}

	FrameworkElement::SetOwnerWindow(pWindow);
}

void Popup::OpenIt(/*Menu* pMenuElement,*/ LDraw::PointI point)
{
//	m_pAttachedToMenuElement = pMenuElement;

	UIElement* child = get_Child();

	child->Measure(LDraw::SizeD(0, 0));
	child->Arrange(LDraw::RectD(LDraw::PointD(0, 0), child->get_DesiredSize()));

	int width = ceil(child->m_expandedBBox.Width);
	int height = ceil(child->m_expandedBBox.Height);

	LDraw::RectI menuRect = LDraw::Recti(point.X, point.Y, width, height);

	ASSERT(GetOwnerWindow());
	IScreen* pScreen = (/*pMenuElement->*/GetOwnerWindow()->m_pSite)->GetScreen();

#if WIN32

	if (false)
	{
//
    // get the nearest monitor to the passed rect.
    //
	//	HMONITOR hMonitor = MonitorFromRect(&rc, MONITOR_DEFAULTTONEAREST);

		LDraw::BBoxi screenRect;
		MSWindows::SystemParametersInfoW(SPI_GETWORKAREA, 0, &screenRect, 0);

		if (menuRect.GetRight() > screenRect.right) menuRect.Translate(-(menuRect.GetRight() - screenRect.right), 0);
		if (menuRect.GetBottom() > screenRect.bottom) menuRect.Translate(0, -(menuRect.GetBottom() - screenRect.bottom));
		if (menuRect.GetLeft() < screenRect.left) menuRect.Translate((screenRect.left - menuRect.GetLeft()), 0);
		if (menuRect.GetTop() < screenRect.top) menuRect.Translate(0, (screenRect.top - menuRect.GetTop()));
	}

#endif

	/*
	ScreenWindow* pScreenWindow = NULL;
	UIElement* pUIElement = pMenuElement;
	while (pUIElement)
	{
		pScreenWindow = dynamic_cast<ScreenWindow*>(pUIElement);
		if (pScreenWindow)
			break;
		pUIElement = pUIElement->GetRParent();
	}
	*/

//	SetRParent(NULL);

	PopupWindowBase* pBase = new PopupWindowBase;
//	pBase->SetRParent(m_pAttachedToMenuElement);

	pBase->m_popup = this;
#if 0
	pBase->SetRParent(m_pAttachedToMenuElement);
//	m_pAttachedToMenuElement->AddRChild(pBase);
#endif
//	child->SetRParent(NULL);	// Visual parent
	pBase->set_VisualTree(child);

	PresentationSource* pSite = pScreen->OpenWindow();
	pSite->SetClient(pBase);
	pSite->Show(&menuRect, GetOwnerWindow()->m_pSite);
	m_pSite = pSite;

	ASSERT(child->GetOwnerWindow() == pBase);

	//pSite->SetWindowRect(menuRect.X, menuRect.Y, menuRect.Width, menuRect.Height);

	if (!get_StaysOpen())
	{
		pSite->SetCapture();
	}

#if 0
#if 0
	//GetRParent()->SetRParent(m_pAttachedToMenuElement);
#if 0
	CUIFrameImpl* frame = new CUIFrameImpl;
#if 0
	ASSERT(0);
	frame->m_pClient = this;
	m_pSite = frame;
#endif
	frame->SetContent(this);

	frame->m_pClient->SetRParent(m_pAttachedToMenuElement);


	HWND hWndParent = dynamic_cast<CUIFrameImpl*>(m_pAttachedToMenuElement->get_OwnerWindow()->m_pSite)->GetHwnd();

	ASSERT(frame->m_hWnd == NULL);
//	Create(hWndParent, rect, NULL/*titlebarText.c_str()*/, /*WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME |*/ WS_POPUP | WS_CLIPCHILDREN, 0/*WS_EX_LAYERED*/);
	CreateWindowEx(0, "lxui_window_class", NULL, WS_POPUP | WS_CLIPCHILDREN,
		menuRect.X + m_expandedBBox.X, menuRect.Y + m_expandedBBox.Y, m_expandedBBox.Width, m_expandedBBox.Height, hWndParent, NULL, _Module.m_hInstance, (CUIFrameImpl*)frame);

	if (frame->m_hWnd)
	{
		::ShowWindow(frame->m_hWnd, SW_SHOW/*nCmdShow*/);
	//	Render();
	}
#endif

	/*
	CreateWindowEx(WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
		"lxui_window_class",//m_hWndParent,//NULL,
		CRect(menuRect.left, menuRect.top, menuRect.left+width, menuRect.top+height),
		NULL,
		WS_POPUP,// | WS_VISIBLE | WS_CAPTION,// | WS_THICKFRAME | WS_SYSMENU,// | WS_CAPTION,
		,// | ,
		0);

	UpdateWindowSize();

	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
*/

	// TODO, have this
	MessageBeep(-1);
#if 0
	m_pWindowHost->SetWindowRect(menuRect.X, menuRect.Y, m_computedSize.Width, m_computedSize.Height);
	m_pWindowHost->SetCapture();
#endif
#if 0	// TODO, have this
	::SetCapture(frame->m_hWnd);
#endif

#elif AMIGA

	ASSERT(0);

#if 0

	m_windowRect.X = point.X;
	m_windowRect.Y = point.Y;
	m_windowRect.Width = (int)m_expandedBBox.Width;
	m_windowRect.Height = (int)m_expandedBBox.Height;

	m_pWindow = OpenWindowTags(NULL,
		(WA_Left), m_windowRect.X,
		(WA_Top), m_windowRect.Y,
		(WA_Width), m_windowRect.Width,
		(WA_Height), m_windowRect.Height,
		(WA_Flags), WFLG_REPORTMOUSE |
						WFLG_BORDERLESS |
						WFLG_ACTIVATE |
						WFLG_SIMPLE_REFRESH,
		(WA_IDCMP), 0,	// Set later
		(WA_MinWidth), 64,
		(WA_MinHeight), 24,
		(WA_MaxWidth), ~0,
		(WA_MaxHeight), ~0,
		(TAG_DONE));

	if (m_pWindow)
	{
		m_pWindow->UserPort = pUserPort;

// Apparently these aren't automatically done after opening window
		SetBitmapSize(m_windowRect.Width, m_windowRect.Height);
		Render();

		m_WindowUserData.pHandler = staticIntuiMsgHandler;
		m_WindowUserData.pData = reinterpret_cast<void*>(static_cast<CUIFrameImpl*>(this));

		m_pWindow->UserData = reinterpret_cast<signed char*>(&m_WindowUserData);

		ModifyIDCMP(m_pWindow,	IDCMP_REFRESHWINDOW |
										IDCMP_MOUSEMOVE |
										IDCMP_MOUSEBUTTONS |
										IDCMP_RAWKEY |
										//IDCMP_VANILLAKEY |
										IDCMP_CHANGEWINDOW |
										IDCMP_INACTIVEWINDOW/* |
										IDCMP_NEWSIZE*/);
	}

#endif

#endif
#endif
}

#if WIN32

#if 0
void Popup::OnCaptureChanged()
{
	return;	// ???

	Event* evt = new Event;
	evt->initEvent(L"cancel",	// "onpopuphiding"	???
		true,	// bubbles
		true	// cancelable
		);

	bool doDefault = dispatchEvent(evt);

	if (doDefault)
	{
		m_pSite->Close();
	}
}

#endif

#elif AMIGA

bool Popup::IntuiMsgHandler(const struct IntuiMessage* pMsg)
{
	// TODO, have something like this
#if 0
	if (pMsg->Class == IDCMP_INACTIVEWINDOW)
	{
		MouseEvent* evt = new MouseEvent;
		evt->InitMouseEvent(WSTR("cancel"),
			dynamic_cast<CLXUIFrameImpl*>(m_pSite)->m_pWindow->MouseX + dynamic_cast<CLXUIFrameImpl*>(m_pSite)->m_pWindow->LeftEdge,
			dynamic_cast<CLXUIFrameImpl*>(m_pSite)->m_pWindow->MouseY + dynamic_cast<CLXUIFrameImpl*>(m_pSite)->m_pWindow->TopEdge
/*			true,	// bubbles
			false	// cancelable	// The amiga has no way of canceling this
			*/
			);

		bool doDefault = dispatchEvent(evt);
	//	Close();
		delete evt;

		return true;
	}
	else
	{
		return CUIFrameImpl::IntuiMsgHandler(pMsg);
	}
#endif
	return true;
}

#endif

void Popup::OnPropertyChanged(DependencyPropertyChangedEventArgs args)
{
	if (args.get_Property() == get_ChildProperty())
	{
		UIElement* oldElement = static_cast<UIElement*>(args.get_OldValue());
		UIElement* newElement = static_cast<UIElement*>(args.get_NewValue());

		if (oldElement != newElement)
		{
			if (oldElement)
			{
				/*
				oldElement->SetOwnerWindow(NULL);
				oldElement->SetRParent(NULL);
				*/
				RemoveVisualChild(oldElement);
			}

			if (newElement)
			{
				/*
				newElement->SetOwnerWindow(GetOwnerWindow());
				newElement->SetRParent(this);
				*/
				AddVisualChild(newElement);
			}
		}
	}
	else if (args.get_Property() == get_IsOpenProperty())
	{
		if (args.get_NewValue() == BoolObject::get_True())
		{
			MSWindows::POINT point;
			MSWindows::GetCursorPos(&point);

			OpenIt(LDraw::PointI(point.x, point.y));

			EventArgs* args = new EventArgs;
			get_Opened()(this, args);
		}
		else
		{
			if (m_pSite)
			{
				m_pSite->Close();
				m_pSite = NULL;

				EventArgs* args = new EventArgs;
				get_Closed()(this, args);
			}
		}
	}

	FrameworkElement::OnPropertyChanged(args);
}

unsigned int Popup::get_VisualChildrenCount()
{
	return (get_Child() != NULL)? 1: 0;
}

Visual* Popup::GetVisualChild(unsigned int index)
{
	UIElement* child = get_Child();

	if (child == NULL || index != 0)
	{
		throw new Exception(WSTR("Index out of range"));
	}

	return child;
}

}	// UI
}
