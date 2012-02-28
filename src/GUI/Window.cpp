#include "stdafx.h"
#include "GUI2.h"
#include <shlguid.h>

#include <algorithm>

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, Window, Left, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, Window, Top, 0.0f)
//IMP_DEPENDENCY_PROPERTY(float, Window, Width, 0.0f)
//IMP_DEPENDENCY_PROPERTY(float, Window, Height, 0.0f)
IMP_DEPENDENCY_PROPERTY(bool, Window, Topmost, false)
IMP_DEPENDENCY_PROPERTY(String, Window, TitleText, nullptr)
IMP_DEPENDENCY_PROPERTY(Element*, Window, Icon, nullptr)
IMP_DEPENDENCY_PROPERTY(geometry, Window, Clip, nullptr)
IMP_DEPENDENCY_PROPERTY(Window*, Window, Owner, nullptr)
IMP_DEPENDENCY_PROPERTY(int, Window, State, 0)
IMP_DEPENDENCY_PROPERTY(bool, Window, InSizeMove, false)
IMP_DEPENDENCY_PROPERTY(bool, Window, CanMinimize, true)
IMP_DEPENDENCY_PROPERTY(bool, Window, CanMaximize, true)
IMP_DEPENDENCY_PROPERTY(bool, Window, HasContextHelp, false)
IMP_DEPENDENCY_PROPERTY(bool, Window, CanClose, true)
IMP_DEPENDENCY_PROPERTY(bool, Window, ShowInTaskbar, true)

IMP_DEPENDENCY_PROPERTY(gm::RectI, Window, RestoreBounds, gm::RectI())

IMP_DEPENDENCY_PROPERTY(String, Window, RT, String("Direct3D"))

IMP_DEPENDENCY_PROPERTY1(MS::Windows::Shell::TaskbarItemInfo*, Window, TaskbarItemInfo, nullptr, new PropertyMetadata(true))

// Computed properties
IMP_DEPENDENCY_PROPERTY(float, Window, Right, _this().getLeft() + _this().getWidth())
IMP_DEPENDENCY_PROPERTY(float, Window, Bottom, _this().getTop() + _this().getHeight())
IMP_DEPENDENCY_PROPERTY(float, Window, ClientLeft, _this().getBorderLeft())
IMP_DEPENDENCY_PROPERTY(float, Window, ClientTop, _this().getBorderTop())
IMP_DEPENDENCY_PROPERTY(float, Window, ClientWidth, _this().getWidth() - _this().getBorderLeftRight())
IMP_DEPENDENCY_PROPERTY(float, Window, ClientHeight, 0.0f/*_this().getHeight() - _this().getBorderTopBottom()*/)
IMP_DEPENDENCY_PROPERTY(float, Window, ClientRight, _this().getClientLeft() + _this().getClientWidth())
IMP_DEPENDENCY_PROPERTY(float, Window, ClientBottom, 0.0f/*_this().getClientTop() + _this().getClientHeight()*/)

DependencyClass* Window::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_LeftProperty(),
		get_TopProperty(),
	//	get_WidthProperty(),
	//	get_HeightProperty(),
		get_TopmostProperty(),
		get_TitleTextProperty(),
		get_IconProperty(),
		get_ClipProperty(),
	//	get_ChildProperty(),
		get_OwnerProperty(),
		get_StateProperty(),
		get_RTProperty(),
		get_InSizeMoveProperty(),
		get_CanMinimizeProperty(),
		get_CanMaximizeProperty(),
		get_HasContextHelpProperty(),
		get_CanCloseProperty(),
		get_ShowInTaskbarProperty(),
		get_RestoreBoundsProperty(),

		get_TaskbarItemInfoProperty(),

		get_RightProperty(),
		get_BottomProperty(),
		get_ClientLeftProperty(),
		get_ClientTopProperty(),
		get_ClientWidthProperty(),
		get_ClientHeightProperty(),
		get_ClientRightProperty(),
		get_ClientBottomProperty(),
	};

	return &depclass;
}

DependencyClass* Window::pClass(get_Class());

List<Window*> Window::s_windows;

unordered_map<HWND,Window*> Window::m_windows;

ValueBinding<Window*> Window::ActiveWindowBinding;
ValueBinding<Window*> Window::ForegroundWindowBinding;
ValueBinding<Window*> Window::FocusWindowBinding;

Window::Window() : ContentControl(get_Class())
{
	Init();

	s_windows.Add(this);	// TODO, not like this
}

Window::Window(Object* content) : ContentControl(get_Class(), content)
{
	Init();

	s_windows.Add(this);	// TODO, not like this
}

Window::Window(Object* content, gm::SizeF size) : ContentControl(get_Class(), content, size)
{
	Init();

	s_windows.Add(this);	// TODO, not like this
}

//static __live_object_ptr<Expressive::ADeclarationList> aexp;
static Expressive::ADeclarationList* aexp;

void Window::Init()
{
	set_TreeLevel(0);

	if (aexp == nullptr)
	{
		aexp = Expressive::Parser::ProgramFromFile("D:\\Window.gui");
	}

	Expressive::FrameContext frame;
	frame.m_variables["sc"] = this;

	Expressive::Expression* exp = Expressive::Translator::Translate(aexp, &frame);
	
	Object* obj = dynamic_cast<Expressive::StaticObjectExpression*>(exp)->m_obj;
	UIElement* element = dynamic_cast<UIElement*>(obj);

	/*
	m_contentContainer = dynamic_cast<UIElement*>(element->FindElement(L"Content"));

	if (m_contentContainer == nullptr)
	{
		raise(SystemException(L"ListBox - no content container in template"));
	}
	*/

	set_ShadowTree(element);
}

gm::RectI Window::GetRect()
{
	return gm::RectI(int(ceil(get_Left())), int(ceil(get_Top())), int(ceil(get_Width())), int(ceil(get_Height())));
}

String Window::ToString()
{
	IO::StringWriter str;
	str << L"Window(";
	str << get_TitleText();

	Object* content = get_Content();
	if (content)
	{
		str << ", " << content->ToString();
	}

	str << ")";
	return str.str();
}

RectBorder Window::GetBorders()
{
	UINT windowStyle = PlatformWindow::GetWindowStyle(this);
	UINT windowExStyle = PlatformWindow::GetWindowExStyle(this);

	RECT rect = {0,0,0,0};
	bool hasMenu = false;
	AdjustWindowRectEx(&rect, windowStyle, hasMenu, windowExStyle);

	return RectBorder(-rect.left, -rect.top, rect.right, rect.bottom);
}

gm::SizeF Window::GetSize()
{
	RECT rect;
	GetClientRect(m_platformWindow->get_Handle(), &rect);

	return gm::SizeF(rect.right, rect.bottom);
}

float Window::GetBorderLeft()
{
	return Window::GetBorders().Left;
}

float Window::GetBorderTop()
{
	return Window::GetBorders().Top;
}

float Window::GetBorderRight()
{
	return Window::GetBorders().Right;
}

float Window::GetBorderBottom()
{
	return Window::GetBorders().Bottom;
}

float Window::GetBorderLeftRight()
{
	RectBorder rectBorder = Window::GetBorders();
	return rectBorder.Left + rectBorder.Right;
}

float Window::GetBorderTopBottom()
{
	RectBorder rectBorder = Window::GetBorders();
	return rectBorder.Top + rectBorder.Bottom;
}

void Window::Restore()
{
	set_State(0);
}

void Window::Minimize()
{
	set_State(1);
}

void Window::Maximize()
{
	set_State(2);
}

Graphics::Bitmap* Window::GetContentBitmap()
{
	if (m_platformWindow)
	{
		return m_platformWindow->GetContentBitmap();
	}
	return nullptr;
}

OleContainer* Window::GetOleContainer()
{
	if (m_oleContainer == nullptr)
	{
		m_oleContainer = new OleContainer;
		m_oleContainer->m_window = this;
	}

	return m_oleContainer;
}

Variant Window::GetLocalPropertyValue(PropertyValue* pPropertyVal)
{
	if (pPropertyVal->m_dp == get_IconProperty())
	{
		WPARAM wParam = ICON_BIG;
		HICON hIcon = (HICON)SendMessageW(m_platformWindow->get_Handle(), WM_GETICON, wParam, 0);

	//	VisualElement* element;
	//	HIconVisual* visual = new HIconVisual;
	}

	return UIElement::GetLocalPropertyValue(pPropertyVal);
}

void Window::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_IsActiveProperty())
	{
		if (m_platformWindow)
		{
			bool isActive = get_IsActive();

			if (isActive)
			{
				SetForegroundWindow(m_platformWindow->get_Handle());
				//::SetWindowPos(m_platformWindow->get_Handle(), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE/* | SWP_NOZORDER*/);
			}
		}
	}
	else if (pPropertyVal->m_dp == get_OpacityProperty())
	{
		if (m_platformWindow)
		{
			m_platformWindow->OnOpacityChanged();
		}
	}
	else if (pPropertyVal->m_dp == get_ClipProperty())
	{
		if (m_platformWindow)
		{
			m_platformWindow->OnClipChanged();
		}
	}
	else if (pPropertyVal->m_dp == get_TitleTextProperty())
	{
		if (m_platformWindow)
		{
			m_platformWindow->OnTitleTextChanged();
		}
	}
	else if (pPropertyVal->m_dp == get_CanMinimizeProperty())
	{
		if (m_platformWindow)
		{
			bool has = get_CanMaximize();

			DWORD style = GetWindowLongW(m_platformWindow->get_Handle(), GWL_STYLE);
			if (has)
				style |= WS_MINIMIZEBOX;
			else
				style &= ~WS_MINIMIZEBOX;

			SetWindowLongW(m_platformWindow->get_Handle(), GWL_STYLE, style);
		}
	}
	else if (pPropertyVal->m_dp == get_CanMaximizeProperty())
	{
		if (m_platformWindow)
		{
			bool has = get_CanMaximize();

			DWORD style = GetWindowLongW(m_platformWindow->get_Handle(), GWL_STYLE);
			if (has)
				style |= WS_MAXIMIZEBOX;
			else
				style &= ~WS_MAXIMIZEBOX;

			SetWindowLongW(m_platformWindow->get_Handle(), GWL_STYLE, style);
		}
	}
	else if (pPropertyVal->m_dp == get_HasContextHelpProperty())
	{
		if (m_platformWindow)
		{
			bool has = get_HasContextHelp();

			DWORD exstyle = GetWindowLongW(m_platformWindow->get_Handle(), GWL_EXSTYLE);
			if (has)
				exstyle |= WS_EX_CONTEXTHELP;
			else
				exstyle &= ~WS_EX_CONTEXTHELP;

			SetWindowLongW(m_platformWindow->get_Handle(), GWL_EXSTYLE, exstyle);
		}
	}
	else if (pPropertyVal->m_dp == get_ShowInTaskbarProperty())
	{
		if (m_platformWindow)
		{
			bool show = get_ShowInTaskbar();

			/*
			DWORD exstyle = GetWindowLongW(m_platformWindow->get_Handle(), GWL_EXSTYLE);
			if (show)
			{
				exstyle |= WS_EX_APPWINDOW;
				exstyle &= ~WS_EX_TOOLWINDOW;
			}
			else
			{
				exstyle &= ~WS_EX_APPWINDOW;
				exstyle |= WS_EX_TOOLWINDOW;
			}

			SetWindowLongW(m_platformWindow->get_Handle(), GWL_EXSTYLE, exstyle);
			*/

			if (show)
			{
				MS::Windows::Shell::Private::pTaskbarList->AddTab(m_platformWindow->get_Handle());
			}
			else
			{
				MS::Windows::Shell::Private::pTaskbarList->DeleteTab(m_platformWindow->get_Handle());
			}
		}
	}

	else if (pPropertyVal->m_dp == get_FontFamilyProperty() ||
			pPropertyVal->m_dp == get_FontSizeProperty() ||
			pPropertyVal->m_dp == get_FontWeightProperty() ||
			pPropertyVal->m_dp == get_FontStyleProperty())
	{
		if (m_platformWindow)
		{
			LOGFONT lf = {0};
			// TODO: Copy16
			wcscpy_s(lf.lfFaceName, get_FontFamily().c_strw_flen<LF_FACESIZE>());
			lf.lfHeight = -get_FontSize();
			lf.lfWeight = get_FontWeight();

			HFONT hFont = CreateFontIndirect(&lf);
			ASSERT(hFont);

			SendMessageW(m_platformWindow->get_Handle(), WM_SETFONT, (WPARAM)hFont, TRUE/*bRedraw*/);

			/*
			String titleText = get_TitleText();

			SetWindowTextW(m_platformWindow->get_Handle(), CStringw(titleText).c_str());
			*/
		}
	}
	else if (pPropertyVal->m_dp == get_TopmostProperty())
	{
		if (m_platformWindow)
		{
			bool topmost = get_Topmost();
			if (topmost)
				SetWindowPos(m_platformWindow->get_Handle(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			else
				SetWindowPos(m_platformWindow->get_Handle(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
	}
	else if (pPropertyVal->m_dp == get_StateProperty())
	{
		if (m_platformWindow)
		{
			int state = GetPropertyValueInt(get_StateProperty());
			switch (state)
			{
			case 0:
				::ShowWindow(m_platformWindow->get_Handle(), SW_RESTORE);
				break;

			case 1:
				::ShowWindow(m_platformWindow->get_Handle(), SW_MINIMIZE);
				break;

			case 2:
				::ShowWindow(m_platformWindow->get_Handle(), SW_MAXIMIZE);
				break;
			}
		}
	}
	else if (pPropertyVal->m_dp == get_IsEnabledProperty())
	{
		if (m_platformWindow)
		{
			bool isEnabled = get_IsEnabled();
			::EnableWindow(m_platformWindow->get_Handle(), isEnabled);
		}
	}
	else if (pPropertyVal->m_dp == get_CanCloseProperty())
	{
		if (m_platformWindow)
		{
			if (get_CanClose())
			{
			//	SetWindowLongPtr(m_platformWindow->get_Handle(), 
			}
			else
			{
			}
			/*
			ULONG_PTR classStyle = ::GetClassLongPtr(m_platformWindow->get_Handle(), GCL_STYLE);

			if (get_CanClose()) classStyle &= ~CS_NOCLOSE;
			else classStyle |= CS_NOCLOSE;

			::SetClassLongPtr(m_platformWindow->get_Handle(), GCL_STYLE, classStyle);
			*/
		}
	}
	else if (pPropertyVal->m_dp == get_LeftProperty() ||
			pPropertyVal->m_dp == get_TopProperty())
	{
		if (m_platformWindow)
		{
			int x = int(get_Left());
			int y = int(get_Top());
			int cx = int(get_ActualWidth());	// ceil??
			int cy = int(get_ActualHeight());	// ceil??

			if (!get_InSizeMove() && !m_inSizeMove)
			{
				::SetWindowPos(m_platformWindow->get_Handle(), nullptr, x, y, cx, cy,
					SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE/* |
					SWP_ASYNCWINDOWPOS	// ??*/
					);
			}
		}
	}
	else if (pPropertyVal->m_dp == get_ActualWidthProperty() ||
			pPropertyVal->m_dp == get_ActualHeightProperty())
	{
		if (m_platformWindow)
		{
			int x = int(get_Left());
			int y = int(get_Top());
			int cx = int(get_ActualWidth());	// ceil??
			int cy = int(get_ActualHeight());	// ceil??

			if (!get_InSizeMove() && !m_inSizeMove)
			{
				::SetWindowPos(m_platformWindow->get_Handle(), nullptr, x, y, cx, cy,
					SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE/* |
					SWP_ASYNCWINDOWPOS	// ??*/
					);
			}
		}
	}
	else if (pPropertyVal->m_dp == get_RTProperty())
	{
		if (m_platformWindow)
		{
			m_platformWindow->ChangeTech();
		}
	}
#if 0
	else if (pPropertyVal->m_dp == get_ChildProperty())
	{
		/*
		MessageBeep(-1);
		if (m_platformWindow)
		{
		}
		*/
		InvalidateVisual();
	}
#endif
	else if (pPropertyVal->m_dp == get_ShadowTreeProperty())
	{
		UIElement* uielement = get_ShadowTree();

		if (uielement)
		{
			uielement->SetRoot(this);	// This is different from default UIElement implementation
			uielement->set_ParentWindow(this);	// This is different from default UIElement implementation

			uielement->set_Parent(this);
			uielement->set_TemplatedOwner(this);	// ??

			InvalidateMeasure();
		//	// ??
		//	uielement->ArrangeCore(gm::SizeF(get_ActualWidth(), get_ActualHeight()));
		}

		handled = true;
	}
	else if (pPropertyVal->m_dp == get_OwnerProperty())
	{
		Window* owner = get_Owner();

		if (m_platformWindow && m_platformWindow->get_Handle())
		{
			if (owner)
			{
				if (owner->m_platformWindow && owner->m_platformWindow->get_Handle())
				{
					::SetParent(m_platformWindow->get_Handle(), owner->m_platformWindow->get_Handle());
				}
			}
			else
			{
				::SetParent(m_platformWindow->get_Handle(), nullptr);
			}
		}
	}
	else if (pPropertyVal->m_dp == get_TaskbarItemInfoProperty())
	{
		MS::Windows::Shell::TaskbarItemInfo* info = get_TaskbarItemInfo();

		if (m_platformWindow)
		{
			HWND hWnd = m_platformWindow->get_Handle();
			if (hWnd)
			{
				double progress = info->get_ProgressValue();
				const ULONGLONG totalProgress = 1000000ULL;

			//	TBPFLAG tbFlags;
			//	MS::Windows::Shell::Private::pTaskbarList3->SetProgressState(hWnd, tbpFlags);
				MS::Windows::Shell::Private::pTaskbarList3->SetProgressValue(hWnd, progress*totalProgress, totalProgress);
			}
		}
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

void Window::OnComputedPropertyValueChanging(PropertyValue* pPropertyVal, const Variant& oldValue, const Variant& newValue, bool handled)
{
	if (pPropertyVal->m_dp == get_ShadowTreeProperty())
	{
	}

	baseClass::OnComputedPropertyValueChanging(pPropertyVal, oldValue, newValue, handled);
}

void Window::InvalidateRender()
{
	if (m_platformWindow)
	{
		m_platformWindow->InvalidateDraw();
	}
}

void Window::PostMessage(const MSG* msg)
{
	UIElement* child = get_ShadowTree();
	if (child)
	{
		ArrangeAll();

	//	child->DoLayout();
	}
}

Graphics::GraphicsI* Window::GetGI()
{
	if (m_platformWindow)
	{
		return m_platformWindow->GetGI();
	}
	return nullptr;
}

bool Window::ElementCaptureMouse(UIElement* element)
{
	if (element == nullptr)
	{
		raise(ArgumentNullException());
	}

	if (m_MouseCaptureElement != element)
	{
		m_MouseCaptureElement = element;
		m_MouseCaptureElement->SetCaptureMouse(true);
		if (m_platformWindow)
		{
			::SetCapture(m_platformWindow->get_Handle());
			return true;
		}
	}

	return true;
}

bool Window::ElementReleaseMouseCapture(UIElement* element)
{
	if (element == nullptr)
	{
		raise(ArgumentNullException());
	}

	if (m_MouseCaptureElement == element)
	{
		m_MouseCaptureElement->SetCaptureMouse(false);

		m_MouseCaptureElement = nullptr;
		if (m_platformWindow)
		{
			return !! ::ReleaseCapture();
		}
		else
			return true;
	}
	else
		return false;
}

bool showCursor = true;

void Window::ElementSetFocus(UIElement* element)
{
	if (m_FocusElement)
	{
		m_FocusElement->set_HasFocus(false);
	}

	m_FocusElement = element;

	if (m_FocusElement)
	{
		m_FocusElement->set_HasFocus(true);
	}
}

void Window::ElementSetMouseCursor(UIElement* element)
{
	if (element == nullptr)
	{
		raise(ArgumentNullException());
	}

	if (element->get_IsMouseDirectlyOver())
	{
		Cursor* pCursor = element->get_Cursor();
		if (pCursor)
		{
			::SetCursor(pCursor->GetHCursor());

			if (!showCursor)
			{
				showCursor = true;
				::ShowCursor(TRUE);
			}
		}
		else
		{
			if (showCursor)
			{
				::ShowCursor(FALSE);
				showCursor = false;
			}
		}
	}
}

/*
void Window::RenderRetained(ManagedRetainedRenderContext renderContext)
{
	UIElement* child = get_Child();
	if (child)
	{
		child->RenderRetained(renderContext);
	}
}
*/

void Window::OnWindowPosChanged(float left, float top)
{
	ASSERT(m_inSizeMove == false);
	m_inSizeMove = true;
	UpdatePropertyValue(get_LeftProperty(), left);
	UpdatePropertyValue(get_TopProperty(), top);
	m_inSizeMove = false;
}

void Window::OnWindowSizeChanged(float width, float height)
{
	ASSERT(m_inSizeMove == false);
	m_inSizeMove = true;
	UpdatePropertyValue(get_WidthProperty(), width);
	UpdatePropertyValue(get_HeightProperty(), height);
	m_inSizeMove = false;
}

void Window::OnLostMouseCapture(PlatformWindowProxy)
{
}

/*
void Window::OnWindowRectChanged(float left, float top, float width, float height)
{
	// Not used?
	ASSERT(0);

	UpdatePropertyValue(get_LeftProperty(), left);
	UpdatePropertyValue(get_TopProperty(), top);
	UpdatePropertyValue(get_WidthProperty(), width);
	UpdatePropertyValue(get_HeightProperty(), height);
}
*/


//////////////////////////////////
// PlatformWindowSite

void PlatformWindowSite::OnHelp(HELPINFO* helpinfo)
{
	gm::PointF pos(helpinfo->MousePos.x, helpinfo->MousePos.y);
}

bool PlatformWindowSite::OnSetCursor(UINT hitTest, POINT screenMousePos)
{
	if (hitTest == HTCLIENT)
	{
		gm::PointF clientMousePos(screenMousePos.x, screenMousePos.y);
		ScreenToClient(m_platformWindow->get_Handle(), (POINT*)&clientMousePos);

		IInputElement* hitElement = nullptr;

		if (m_MouseCaptureElement)
		{
			hitElement = m_MouseCaptureElement;
		}
		else
		{
			//Visual* child = get_Child();
			UIElement* child = GetRootElement();

			if (child)
			{
				hitElement = child->HitTest_(clientMousePos);
			}

		//	hitElement = child;
		}

		if (hitElement == nullptr)
		{
			hitElement = dynamic_cast<IInputElement*>(this);
		}

		if (hitElement)
		{
			/*
			MouseEventArgs* args = new MouseEventArgs(nullptr, 0);
			args->set_RoutedEvent(UIElement::MouseMoveEvent);
			args->m_screenpos = Point(float(screenMousePos.x), float(screenMousePos.y));
			args->m_clientpos = clientMousePos;

			hitElement->RaiseEvent(args);
			*/
			Cursor* pCursor = dynamic_cast<UIElement*>(hitElement)->get_Cursor();
			if (pCursor)
			{
				SetCursor(pCursor->GetHCursor());
				if (!showCursor)
				{
					showCursor = true;
					::ShowCursor(TRUE);
				}
				return true;
			}
			else
			{
				if (showCursor)
				{
					showCursor = false;
					::ShowCursor(FALSE);
				}
			}
		}
	}

	return false;
}

void PlatformWindowSite::OnMouseMove(gm::PointF clientMousePos)
{
	POINT screenMousePos;
	::GetCursorPos(&screenMousePos);

	UIElement* hitElement = nullptr;

	if (m_MouseCaptureElement)
	{
		hitElement = m_MouseCaptureElement;
	}
	else
	{
		//Visual* child = get_Child();
		UIElement* child = GetRootElement();

		if (child)
		{
			hitElement = child->HitTest_(clientMousePos);
		}
	}

	if (m_MouseOverElement != hitElement)
	{
		// Find common ancestor
		UIElement* commonAncestor = m_MouseOverElement->FindCommonAncestor(hitElement);
	//	ASSERT(commonAncestor);

		for (UIElement* p = m_MouseOverElement; p != commonAncestor; p = p->get_Parent())
		{
			p->set_IsMouseOver(false);
		}

		for (UIElement* p = hitElement; p != commonAncestor; p = p->get_Parent())
		{
			p->set_IsMouseOver(true);
		}

		if (m_MouseOverElement)
		{
			m_MouseOverElement->set_IsMouseDirectlyOver(false);
		}

		m_MouseOverElement = hitElement;

		if (m_MouseOverElement)
		{
			m_MouseOverElement->set_IsMouseDirectlyOver(true);
		}
	}

	if (hitElement)
	{
		MouseEventArgs* args = new MouseEventArgs(nullptr, 0);
		args->set_RoutedEvent(UIElement::get_MouseMoveEvent());
		args->m_screenpos = Point(float(screenMousePos.x), float(screenMousePos.y));
		args->m_clientpos = clientMousePos;

		hitElement->RaiseEvent(args);
	}
}

void PlatformWindowSite::OnSize(gm::RectI r)
{
	UIElement* uielement = dynamic_cast<UIElement*>(this);
	// Done in OnSizing
#if 0
	m_ownerVisual->OnWindowSizeChanged(windowWidth, windowHeight);
#endif

	int clientWidth = r.Width;
	int clientHeight = r.Height;

#if 0	// Event
	m_ownerVisual->OnSize(m_ownerVisual);
#endif

	// TODO, not here, like this ??
	UIElement* child = GetRootElement();
	if (child)
	{
		/*
		m_ownerVisual->set_ActualWidth(windowWidth);
		m_ownerVisual->set_ActualHeight(windowHeight);

		child->DoLayoutSize(gm::SizeF(clientWidth, clientHeight));
		*/
			
		uielement->m_desiredSize =  gm::SizeF(clientWidth, clientHeight);
		uielement->m_availSize = gm::SizeF(clientWidth, clientHeight);

		uielement->InvalidateMeasure();
		uielement->InvalidateArrange();
	}
}

LRESULT PlatformWindowSite::OnSizing(WPARAM edge, RECT* pScreenRect)
{
	Window* m_ownerVisual = dynamic_cast<Window*>(this);

	switch (edge)
	{
		case WMSZ_RIGHT:
		{
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_WidthProperty(), float(pScreenRect->right - pScreenRect->left));

			pScreenRect->left = m_ownerVisual->get_Left();
			pScreenRect->top = m_ownerVisual->get_Top();
			pScreenRect->bottom = pScreenRect->top + m_ownerVisual->get_Height();
		}
		break;

		case WMSZ_BOTTOM:
		{
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_HeightProperty(), float(pScreenRect->bottom - pScreenRect->top));

			pScreenRect->left = m_ownerVisual->get_Left();
			pScreenRect->top = m_ownerVisual->get_Top();
			pScreenRect->right = pScreenRect->left + m_ownerVisual->get_Width();
		}
		break;

		case WMSZ_LEFT:
		{
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_LeftProperty(), float(pScreenRect->left));
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_WidthProperty(), float(pScreenRect->right - pScreenRect->left));

			pScreenRect->right = pScreenRect->left + m_ownerVisual->get_Width();
			pScreenRect->bottom = pScreenRect->top + m_ownerVisual->get_Height();
		}
		break;

		case WMSZ_TOP:
		{
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_TopProperty(), float(pScreenRect->top));
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_HeightProperty(), float(pScreenRect->bottom - pScreenRect->top));

			pScreenRect->left = m_ownerVisual->get_Left();
			pScreenRect->right = pScreenRect->left + m_ownerVisual->get_Width();
		}
		break;

		case WMSZ_TOPLEFT:
		{
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_TopProperty(), float(pScreenRect->top));
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_LeftProperty(), float(pScreenRect->left));
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_WidthProperty(), float(pScreenRect->right - pScreenRect->left));
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_HeightProperty(), float(pScreenRect->bottom - pScreenRect->top));

			pScreenRect->right = pScreenRect->left + m_ownerVisual->get_Width();
			pScreenRect->bottom = pScreenRect->top + m_ownerVisual->get_Height();
		}
		break;

		case WMSZ_TOPRIGHT:
		{
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_TopProperty(), float(pScreenRect->top));
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_WidthProperty(), float(pScreenRect->right - pScreenRect->left));

			pScreenRect->left = m_ownerVisual->get_Left();
			pScreenRect->bottom = pScreenRect->top + m_ownerVisual->get_Height();
		}
		break;

		case WMSZ_BOTTOMLEFT:
		{
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_LeftProperty(), float(pScreenRect->left));
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_HeightProperty(), float(pScreenRect->bottom - pScreenRect->top));

			pScreenRect->top = m_ownerVisual->get_Top();
			pScreenRect->right = pScreenRect->left + m_ownerVisual->get_Width();
		}
		break;

		case WMSZ_BOTTOMRIGHT:
		{
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_WidthProperty(), float(pScreenRect->right - pScreenRect->left));
			m_ownerVisual->UpdatePropertyValue(m_ownerVisual->get_HeightProperty(), float(pScreenRect->bottom - pScreenRect->top));

			pScreenRect->left = m_ownerVisual->get_Left();
			pScreenRect->top = m_ownerVisual->get_Top();
		}
		break;
	}

// An application should return TRUE if it processes this message.
	return TRUE;
}

void print_children(Visual* visual, int level)
{
	for (int i = 0; i < level; ++i)
	{
		Console::get_Out() << " ";
	}
	Console::get_Out() << visual->GetType()->ToString() << " : ";
	Console::get_Out() << "level(" << dynamic_cast<UIElement*>(visual)->get_TreeLevel() << "), ";
	Console::get_Out() << "awidth(" << dynamic_cast<UIElement*>(visual)->get_ActualWidth() << "), ";
	Console::get_Out() << "aheight(" << dynamic_cast<UIElement*>(visual)->get_ActualHeight() << ")";
	Console::get_Out() << endl;

	size_t count = visual->GetChildrenCount();
	for (size_t i = 0; i < count; ++i)
	{
		Visual* child = visual->GetChild(i);

		print_children(child, level+1);
	}
}

GUIEXT void print_(Visual* visual)
{
	print_children(visual, 0);
}

void PlatformWindowSite::OnMouseButtonDown(gm::PointF clientMousePos, int button)
{
	POINT screenMousePos;
	::GetCursorPos(&screenMousePos);

	UIElement* hitElement = nullptr;

	UIElement* child = GetRootElement();
//	Visual* child = get_Child();
	if (child)
	{
		hitElement = child->HitTest_(clientMousePos);
	}
//	hitElement = child;

	if (hitElement)
	{
		MouseButtonEventArgs* args = new MouseButtonEventArgs(nullptr, 0);
		args->m_screenpos = Point(float(screenMousePos.x), float(screenMousePos.y));
		args->m_clientpos = clientMousePos;

		// Raise general mousedown event
		args->set_RoutedEvent(UIElement::get_MouseButtonDownEvent());
		hitElement->RaiseEvent(args);

		// Raise button mousedown event
		if (button == 0)			args->set_RoutedEvent(UIElement::get_MouseLeftButtonDownEvent());
		else if (button == 1)	args->set_RoutedEvent(UIElement::get_MouseMiddleButtonDownEvent());
		else						args->set_RoutedEvent(UIElement::get_MouseRightButtonDownEvent());

		hitElement->RaiseEvent(args);
	}
}

void PlatformWindowSite::OnMouseButtonDblClk(gm::PointF clientMousePos, int button)
{
	POINT screenMousePos;
	::GetCursorPos(&screenMousePos);

	UIElement* hitElement = nullptr;

	UIElement* child = GetRootElement();
//	Visual* child = get_Child();
	if (child)
	{
		hitElement = child->HitTest_(clientMousePos);
	}
//	hitElement = child;

	if (hitElement)
	{
		MouseButtonEventArgs* args = new MouseButtonEventArgs(nullptr, 0);

		if (button == 0)			args->set_RoutedEvent(UIElement::get_MouseLeftButtonDoubleClickEvent());
		else if (button == 1)	args->set_RoutedEvent(UIElement::get_MouseMiddleButtonDoubleClickEvent());
		else						args->set_RoutedEvent(UIElement::get_MouseRightButtonDoubleClickEvent());

		args->m_screenpos = Point(float(screenMousePos.x), float(screenMousePos.y));
		args->m_clientpos = clientMousePos;

		hitElement->RaiseEvent(args);
	}
}

void PlatformWindowSite::OnMouseButtonUp(gm::PointF clientMousePos, int button)
{
	POINT screenMousePos;
	::GetCursorPos(&screenMousePos);

	UIElement* hitElement = nullptr;

	if (m_MouseCaptureElement)
	{
		hitElement = m_MouseCaptureElement;
	}
	else
	{
//		Visual* child = get_Child();
		UIElement* child = GetRootElement();
		if (child)
		{
		//	hitElement = child->HitTest(clientMousePos);
		}
		hitElement = child;
	}

	if (hitElement)
	{
		MouseButtonEventArgs* args = new MouseButtonEventArgs(nullptr, 0);

		if (button == 0)			args->set_RoutedEvent(UIElement::get_MouseLeftButtonUpEvent());
		else if (button == 1)	args->set_RoutedEvent(UIElement::get_MouseMiddleButtonUpEvent());
		else						args->set_RoutedEvent(UIElement::get_MouseRightButtonUpEvent());

		args->m_screenpos = Point(float(screenMousePos.x), float(screenMousePos.y));
		args->m_clientpos = clientMousePos;

		hitElement->RaiseEvent(args);
	}
}

void PlatformWindowSite::OnKeyDown(UINT wParam, UINT lParam)
{
//	POINT screenMousePos;
//	::GetCursorPos(&screenMousePos);

	IInputElement* hitElement = nullptr;

	if (m_FocusElement)
	{
		hitElement = m_FocusElement;
	}
	else
	{
//		Visual* child = get_Child();
		UIElement* child = GetRootElement();
		if (child)
		{
		//	hitElement = child->HitTest(clientMousePos);
		}
		hitElement = child;
	}

	if (hitElement)
	{
		KeyEventArgs* args = new KeyEventArgs(nullptr, nullptr, 0, wParam);

		args->set_RoutedEvent(UIElement::get_KeyEvent());

		hitElement->RaiseEvent(args);
	}
}

void PlatformWindowSite::OnChar(UINT wParam, UINT lParam)
{
	if (wParam == 8) return;	// ignore backspace

//	POINT screenMousePos;
//	::GetCursorPos(&screenMousePos);

	IInputElement* hitElement = nullptr;

	if (m_FocusElement)
	{
		hitElement = m_FocusElement;
	}
	else
	{
//		Visual* child = get_Child();
		UIElement* child = GetRootElement();
		if (child)
		{
		//	hitElement = child->HitTest(clientMousePos);
		}
		hitElement = child;
	}

	if (hitElement)
	{
		TextCompositionEventArgs* args = new TextCompositionEventArgs(nullptr, 0);

		WCHAR str[2] = {wParam, 0};
		args->m_text = String(str);

		args->set_RoutedEvent(UIElement::get_TextCompositionEvent());

		hitElement->RaiseEvent(args);
	}
}

/*
UIElement* Window::CreateShadowTree()
{
	ASSERT(0);
	return nullptr;
}
*/

bool PlatformWindowSite::Show()
{
	if (m_platformWindow == nullptr)
	{
		m_platformWindow = new PlatformWindow(this);
	}

	return m_platformWindow->Show();
}

void PlatformWindowSite::Hide()
{
	if (m_platformWindow)
	{
		m_platformWindow->Hide();
	}
}

HRESULT PlatformWindowSite::DragEnter(
	::IDataObject* pDataObject,
	/* [in] */ DWORD grfKeyState,
	/* [in] */ POINTL pt,
	/* [out][in] */ __RPC__inout DWORD *pdwEffect)
{
	m_pDataObject = pDataObject;

	/*
	if (m_pDataObject != pDataObject)
	{
		m_pDataObject = pDataObject;
		m_dataObject = new DataObject;
		m_dataObject->m_pDataObject = m_pDataObject;
	}*/

	if (m_dropTargetHelper == nullptr)
	{
		HRESULT hr;
		hr = m_dropTargetHelper.CoCreateInstance(CLSID_DragDropHelper);
		if (FAILED(hr)) return hr;
	}

//	ComPtr<IEnumFORMATETC> enumfmt;
//	pDataObject->EnumFormatEtc(DATADIR_GET, &enumfmt);

	/*
	FORMATETC fetc;
	DWORD fetched;
	while ((enumfmt->Next(1, &fetc, &fetched) == S_OK) && fetched)
	{
		DebugTrace("Format " << fetc.cfFormat << "\n");
//CF_TEXT
	}
	*/

	UIElement* hitElement = nullptr;

	gm::PointF screenMousePos(float(pt.x), float(pt.y));

	ScreenToClient(m_platformWindow->get_Handle(), (POINT*)&pt);
	Point clientMousePos(pt.x, pt.y);

	UIElement* child = GetRootElement();
	if (child)
	{
		hitElement = child->HitTest_(clientMousePos);
	}

	if (hitElement == nullptr)
	{
		hitElement = GetRootWindow();
	}

	if (hitElement)
	{
		m_DragOverElement = hitElement;

		DragEventArgs* args = new DragEventArgs(pDataObject);
		args->set_RoutedEvent(UIElement::get_DragEnterEvent());
	//	args->m_screenpos = Point(float(screenMousePos.x), float(screenMousePos.y));
	//	args->m_clientpos = clientMousePos;

		hitElement->RaiseEvent(args);
	}

// Call IDragImages::DragEnter last
	m_dropTargetHelper->DragEnter(m_platformWindow->get_Handle(), pDataObject, (POINT*)&pt, *pdwEffect);
	return S_OK;
}

HRESULT PlatformWindowSite::DragOver(
    /* [in] */ DWORD grfKeyState,
    /* [in] */ POINTL pt,
    /* [out][in] */ __RPC__inout DWORD *pdwEffect)
{

	Point screenMousePos(pt.x, pt.y);

	ScreenToClient(m_platformWindow->get_Handle(), (POINT*)&pt);
	Point clientMousePos(pt.x, pt.y);

	if (m_DragOverElement)
	{
		DragEventArgs* args = new DragEventArgs(m_pDataObject);
		args->set_RoutedEvent(UIElement::get_DragLeaveEvent());
	//	args->m_screenpos = Point(float(screenMousePos.x), float(screenMousePos.y));
	//	args->m_clientpos = clientMousePos;

		m_DragOverElement->RaiseEvent(args);
	}

	UIElement* child = GetRootElement();
	if (child)
	{
		m_DragOverElement = child->HitTest_(clientMousePos);
	}

	if (m_DragOverElement == nullptr)
	{
		m_DragOverElement = GetRootWindow();
	}

	if (m_DragOverElement)
	{
		DragEventArgs* args = new DragEventArgs(m_pDataObject);
		args->set_RoutedEvent(UIElement::get_DragEnterEvent());
	//	args->m_screenpos = Point(float(screenMousePos.x), float(screenMousePos.y));
	//	args->m_clientpos = clientMousePos;

		m_DragOverElement->RaiseEvent(args);
	}

// Call IDragImages::DragEnter last
	m_dropTargetHelper->DragOver((POINT*)&pt, *pdwEffect);
	return S_OK;
}

HRESULT PlatformWindowSite::DragLeave()
{
	if (m_DragOverElement)
	{
		DragEventArgs* args = new DragEventArgs(m_pDataObject);
		args->set_RoutedEvent(UIElement::get_DragLeaveEvent());
	//	args->m_screenpos = Point(float(screenMousePos.x), float(screenMousePos.y));
	//	args->m_clientpos = clientMousePos;

		m_DragOverElement->RaiseEvent(args);
		m_DragOverElement = nullptr;
	}

	m_dropTargetHelper->DragLeave();
	return S_OK;
}

HRESULT PlatformWindowSite::Drop(
	/* [unique][in] */ ::IDataObject* pDataObject,
    /* [in] */ DWORD grfKeyState,
    /* [in] */ POINTL pt,
    /* [out][in] */ DWORD* pdwEffect)
{
	if (m_DragOverElement)
	{
		DragEventArgs* args = new DragEventArgs(pDataObject);
		args->set_RoutedEvent(UIElement::get_DragDropEvent());
	//	args->m_screenpos = Point(float(screenMousePos.x), float(screenMousePos.y));
	//	args->m_clientpos = clientMousePos;

		m_DragOverElement->RaiseEvent(args);
	}

	return m_dropTargetHelper->Drop(pDataObject, (POINT*)&pt, *pdwEffect);
//	return S_OK;
}

void Window::AddMeasure(UIElement* pVisual, int level)
{
	ASSERT(pVisual);

	auto before = std::lower_bound(m_measureList.begin(), m_measureList.end(), level);
	m_measureList.insert(before, VisualPair(pVisual, level));
}

void Window::AddArrange(UIElement* pVisual, int level)
{
	ASSERT(pVisual);

	auto before = std::lower_bound(m_arrangeList.begin(), m_arrangeList.end(), level);
	m_arrangeList.insert(before, VisualPair(pVisual, level));
}

void Window::MeasureAll()
{
	while (!m_measureList.empty())
	{
		VisualPair p = m_measureList.front();
		m_measureList.pop_front();
		VERIFY(p.pVisual->m_inMeasureList);
		p.pVisual->m_inMeasureList = false;

		gm::SizeF availSize;
		if (p.pVisual->get_Parent())
			availSize = p.pVisual->get_Parent()->get_ActualSize();
		else
			availSize = m_availSize;
		p.pVisual->Measure(availSize);
	}

#if 0
	while (!m_measureList.empty())
	{
		VisualPair p = m_measureList.front();//*it;
		m_measureList.pop_front();

		//if (!p.pVisual->m_bMeasureValid)
		{
			VERIFY(p.pVisual->m_inMeasureList);
			p.pVisual->m_inMeasureList = false;
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

		if (p.pVisual->GetRParent() == nullptr)
		{
//			MessageBeep(-1);
		}

		if (!p.pVisual->m_bArrangeValid)
		{
			// TODO, call OnArrange instead

			if (p.pVisual->GetRParent() == nullptr)	// ??
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
#endif
}

void Window::ArrangeAll()
{
	MeasureAll();
	ASSERT(m_measureList.empty());

	while (!m_arrangeList.empty())
	{
		VisualPair p = m_arrangeList.front();
		m_arrangeList.pop_front();
		VERIFY(p.pVisual->m_inArrangeList);
		p.pVisual->m_inArrangeList = false;

		gm::RectF finalRect(gm::PointF(0, 0), p.pVisual->m_desiredSize);

		ASSERT(!m_inSizeMove);
		m_inSizeMove = true;

		p.pVisual->Arrange(finalRect);

		m_inSizeMove = false;

		MeasureAll();
		ASSERT(m_measureList.empty());
	}
}

// virtual
Window::ElementProviderRoot* Window::GetElementProvider()
{
	if (m_elementProvider == nullptr)
	{
		m_elementProvider = new ElementProviderRoot(this);
		m_elementProvider->AddRef();
	}

	return (ElementProviderRoot*)m_elementProvider;
}

HRESULT STDMETHODCALLTYPE Window::ElementProviderRoot::QueryInterface(REFIID riid, void** ppvObject)
{
	if (riid == __uuidof(IUnknown))								*ppvObject = static_cast<IRawElementProviderSimple*>(this);
	else if (riid == __uuidof(IRawElementProviderSimple))		*ppvObject = static_cast<IRawElementProviderSimple*>(this);
	else if (riid == __uuidof(IRawElementProviderFragment))		*ppvObject = static_cast<IRawElementProviderFragment*>(this);
	else if (riid == __uuidof(IRawElementProviderFragmentRoot))	*ppvObject = static_cast<IRawElementProviderFragmentRoot*>(this);
	else
	{
		*ppvObject = nullptr;
		return E_NOINTERFACE;
	}

	AddRef();
	return S_OK;
}

HRESULT Window::ElementProviderRoot::get_ProviderOptions(ProviderOptions *pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	if (pRetVal == nullptr) return E_POINTER;

	*pRetVal = ProviderOptions_ServerSideProvider | ProviderOptions_UseComThreading;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE Window::ElementProviderRoot::GetPatternProvider(PATTERNID patternId, IUnknown** pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	if (pRetVal == nullptr) return E_POINTER;

	*pRetVal = nullptr;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE Window::ElementProviderRoot::GetPropertyValue(PROPERTYID propertyId, VARIANT* pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	if (pRetVal == nullptr) return E_POINTER;

	pRetVal->vt = VT_EMPTY;

	switch (propertyId)
	{
	case UIA_NativeWindowHandlePropertyId:
		pRetVal->vt = VT_I4;
		pRetVal->lVal = (LONG)GetOwner()->m_platformWindow->get_Handle();
		break;

	//case UIA_IsWindowPatternAvailablePropertyId:
		/*
	default:
		pRetVal->vt = VT_UNKNOWN;
		return UiaGetReservedNotSupportedValue(&pRetVal->punkVal);
		*/
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE Window::ElementProviderRoot::get_HostRawElementProvider(IRawElementProviderSimple** pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	return UiaHostProviderFromHwnd(GetOwner()->m_platformWindow->get_Handle(), pRetVal);
}

HRESULT STDMETHODCALLTYPE Window::ElementProviderRoot::ElementProviderFromPoint(double x, double y, IRawElementProviderFragment** pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	if (pRetVal == nullptr) return E_POINTER;

	POINT pt;
	pt.x = (LONG)x;
	pt.y = (LONG)y;
	ScreenToClient(GetOwner()->m_platformWindow->get_Handle(), &pt);

	*pRetVal = nullptr;

	UIElement* child = GetOwner()->get_ShadowTree();

	if (child)
	{
		UIElement* hitElement = child->HitTest_(gm::PointF(float(pt.x), float(pt.y)));

		if (hitElement)
		{
			*pRetVal = hitElement->GetElementProvider();
			(*pRetVal)->AddRef();
		}
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE Window::ElementProviderRoot::GetFocus(IRawElementProviderFragment** pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	if (pRetVal == nullptr) return E_POINTER;

	*pRetVal = nullptr;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE Window::ElementProviderRoot::get_FragmentRoot(IRawElementProviderFragmentRoot** pRetVal)
{
	if (m_owner == nullptr) return UIA_E_ELEMENTNOTAVAILABLE;
	if (pRetVal == nullptr) return E_POINTER;

	*pRetVal = this;
	(*pRetVal)->AddRef();

	return S_OK;
}

// static
Window* Window::FromHwnd(HWND hWnd)
{
	if (hWnd == nullptr) return nullptr;
	ASSERT(::IsWindow(hWnd));
	if (!::IsWindow(hWnd)) return nullptr;

	DWORD processId;
	GetWindowThreadProcessId(hWnd, &processId);
	if (processId == GetCurrentProcessId())
	{
		PlatformWindow::MyWin* win =(PlatformWindow::MyWin*)GetPropW(hWnd, L"sigurd_lerstad_gui_window");
		if (win)
		{
			ASSERT(0);
			return nullptr;
		//	Window* window = dynamic_cast<Window*>(static_cast<PlatformWindow*>(win->pWindow)->get_OwnerVisual()->get_TemplatedOwner());
		//	ASSERT(window);
		//	return window;
		}
		else
			return nullptr;
	}
	else
	{
		Window* & window = m_windows[hWnd];

	// TODO, I could check the class and provide special for each foreign window class type that I know

		if (window == nullptr)
		{
			ForeignWindow* fwindow = new ForeignWindow();
			fwindow->m_wnd = new ForeignPlatformWindow(fwindow, hWnd);

			window = fwindow;
		}

		return window;
	}
}

}	// Gui
}	// System
