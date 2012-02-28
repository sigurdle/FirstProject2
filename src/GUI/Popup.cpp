#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(UIElement*, Popup, Child, nullptr)
IMP_DEPENDENCY_PROPERTY(bool, Popup, StaysOpen, false)
IMP_DEPENDENCY_PROPERTY(bool, Popup, IsOpen, false)

	/*
IMP_DEPENDENCY_PROPERTY(float, Popup, Left, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, Popup, Top, 0.0f)
//IMP_DEPENDENCY_PROPERTY(float, Window, Width, 0.0f)
//IMP_DEPENDENCY_PROPERTY(float, Window, Height, 0.0f)
IMP_DEPENDENCY_PROPERTY(bool, Popup, Topmost, false)
IMP_DEPENDENCY_PROPERTY(String, Popup, TitleText, nullptr)
IMP_DEPENDENCY_PROPERTY(Element*, Popup, Icon, nullptr)
IMP_DEPENDENCY_PROPERTY(geometry, Popup, Clip, nullptr)
IMP_DEPENDENCY_PROPERTY(Window*, Popup, Owner, nullptr)
*/
/*
IMP_DEPENDENCY_PROPERTY(int, Popup, State, 0)
IMP_DEPENDENCY_PROPERTY(bool, Popup, InSizeMove, false)
IMP_DEPENDENCY_PROPERTY(bool, Popup, CanMinimize, true)
IMP_DEPENDENCY_PROPERTY(bool, Popup, CanMaximize, true)
IMP_DEPENDENCY_PROPERTY(bool, Popup, HasContextHelp, false)
IMP_DEPENDENCY_PROPERTY(bool, Popup, CanClose, true)
IMP_DEPENDENCY_PROPERTY(bool, Popup, ShowInTaskbar, true)

IMP_DEPENDENCY_PROPERTY(gm::RectI, Popup, RestoreBounds, gm::RectI())

IMP_DEPENDENCY_PROPERTY(String, Popup, RT, String("Direct3D"))

IMP_DEPENDENCY_PROPERTY1(MS::Windows::Shell::TaskbarItemInfo*, Window, TaskbarItemInfo, nullptr, new PropertyMetadata(true))
*/

#if 0
// Computed properties
IMP_DEPENDENCY_PROPERTY(float, Popup, Right, _this().getLeft() + _this().getWidth())
IMP_DEPENDENCY_PROPERTY(float, Popup, Bottom, _this().getTop() + _this().getHeight())
IMP_DEPENDENCY_PROPERTY(float, Popup, ClientLeft, _this().getBorderLeft())
IMP_DEPENDENCY_PROPERTY(float, Popup, ClientTop, _this().getBorderTop())
IMP_DEPENDENCY_PROPERTY(float, Popup, ClientWidth, _this().getWidth() - _this().getBorderLeftRight())
IMP_DEPENDENCY_PROPERTY(float, Popup, ClientHeight, 0.0f/*_this().getHeight() - _this().getBorderTopBottom()*/)
IMP_DEPENDENCY_PROPERTY(float, Popup, ClientRight, _this().getClientLeft() + _this().getClientWidth())
IMP_DEPENDENCY_PROPERTY(float, Popup, ClientBottom, 0.0f/*_this().getClientTop() + _this().getClientHeight()*/)
#endif

DependencyClass* Popup::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_ChildProperty(),
		get_StaysOpenProperty(),
		get_IsOpenProperty(),
	};

	return &depclass;
}

DependencyClass* Popup::pClass(get_Class());

Popup::Popup() : FrameworkElement(get_Class())
{
}

void Popup::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_ChildProperty())
	{
		UIElement* child = get_Child();
		if (child)
		{
			child->set_Parent(this);
		}
	}
	else if (pPropertyVal->m_dp == get_IsOpenProperty())
	{
		if (get_IsOpen())
		{
			gm::PointI mousepos = Mouse::GetCursorPos();

			OpenIt(mousepos);

			// TODO
			/*
			EventArgs* args = new EventArgs;
			get_Opened()(this, args);
			*/
		}
		else
		{
			if (m_window)
			{
				m_window->GetPlatformWindow()->Close();

			// TODO
				/*
				EventArgs* args = new EventArgs;
				get_Closed()(this, args);
				*/
			}
		}
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

void Popup::OnMouseButtonDown(MouseButtonEventArgs* args)
{
//	MSWindows::RECT wrect;
//	MSWindows::GetWindowRect(m_pSite->GetHwnd(), &wrect);

	// cancel/popup hiding event
	gm::RectI rect = m_window->get_ActualWindowRect();

	gm::PointF screenpos = args->GetScreenPosition();

	if (!get_StaysOpen())
	{
		if (screenpos.X < rect.X ||
			screenpos.Y < rect.Y ||
			screenpos.X < rect.GetRight() ||
			screenpos.Y > rect.GetBottom())
		{
			// ???? TODO, send cancel event

			::SendMessageW(m_window->get_PWindow()->get_Handle(), WM_CLOSE, 0, 0);
		//	m_platformWindow->Hide();
		//	Close();
		//	m_pSite->Close();
		//	m_pSite = NULL;
		}
	}
}

void Popup::OpenIt(gm::PointI mousepos)
{
//	m_pAttachedToMenuElement = pMenuElement;

	UIElement* child = get_Child();

#if 0
	child->Measure(gm::SizeD(0, 0));
	child->Arrange(gm::RectF(gm::PointD(0, 0), child->get_DesiredSize()));

	int width = ceil(child->m_expandedBBox.Width);
	int height = ceil(child->m_expandedBBox.Height);

	LDraw::RectI menuRect = LDraw::Recti(point.X, point.Y, width, height);

	ASSERT(GetOwnerWindow());
	IScreen* pScreen = (/*pMenuElement->*/GetOwnerWindow()->m_pSite)->GetScreen();
#endif

//
// get the nearest monitor to the passed rect.
//
//	HMONITOR hMonitor = MonitorFromRect(&rc, MONITOR_DEFAULTTONEAREST);

	gm::BBoxi screenRect;
	::SystemParametersInfoW(SPI_GETWORKAREA, 0, &screenRect, 0);

#if 0
	if (menuRect.GetRight() > screenRect.right) menuRect.Translate(-(menuRect.GetRight() - screenRect.right), 0);
	if (menuRect.GetBottom() > screenRect.bottom) menuRect.Translate(0, -(menuRect.GetBottom() - screenRect.bottom));
	if (menuRect.GetLeft() < screenRect.left) menuRect.Translate((screenRect.left - menuRect.GetLeft()), 0);
	if (menuRect.GetTop() < screenRect.top) menuRect.Translate(0, (screenRect.top - menuRect.GetTop()));
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

	if (m_window == nullptr)
	{
		m_window = new PopupWindow(this);
	}

	m_window->m_windowRect = gm::RectI(mousepos, gm::SizeI(300, 200));
	m_window->Show();

#if 0
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
#endif

	if (!get_StaysOpen())
	{
		m_window->GetPlatformWindow()->CaptureMouse();
	}

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

#endif
}

////////////////////////////////////////////
// PopupWindow

gm::RectI Popup::PopupWindow::GetRect()
{
	return m_windowRect;
}

void Popup::PopupWindow::OnWindowPosChanged(float left, float top)
{
}

void Popup::PopupWindow::OnWindowSizeChanged(float width, float height)
{
}

void Popup::PopupWindow::OnLostMouseCapture(PlatformWindowProxy gotFocus)
{
	if (!m_owner->get_StaysOpen())
	{
		m_owner->set_IsOpen(false);
	}
}

}	// Gui
}	// System
