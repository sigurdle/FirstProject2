#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

#if 0

DependencyClass* Window::Class(get_Class());

DependencyClass* Window::get_Class()
{
	static DependencyClass Class(typeid(Window), &ContentControl::Class);

	get_LeftProperty();
	get_TopProperty();

	return &Class;
}

TypedDependencyProperty<float>* Window::get_LeftProperty()
{
	static TypedDependencyProperty<float> LeftProperty(get_Class(), WSTR("Left"), 0);
	return &LeftProperty;
}

TypedDependencyProperty<float>* Window::get_TopProperty()
{
	static TypedDependencyProperty<float> TopProperty(get_Class(), WSTR("Top"), 0);
	return &TopProperty;
}

TypedDependencyProperty<bool> Window::TopmostProperty(get_Class(), WSTR("Topmost"), false);
TypedDependencyProperty<StringW*> Window::TitleTextProperty(get_Class(), WSTR("TitleText"), NULL);
TypedDependencyProperty<Window*> Window::OwnerProperty(get_Class(), WSTR("Owner"), NULL);
TypedDependencyProperty<Element*> Window::IconProperty(get_Class(), WSTR("Icon"), NULL);

TypedDependencyProperty<float> Window::ContentLeftProperty(get_Class(), WSTR("ContentLeft"), _WindowVisual(_this().getShadowTree()).getClientLeft());
TypedDependencyProperty<float> Window::ContentTopProperty(get_Class(), WSTR("ContentTop"), _WindowVisual(_this().getShadowTree()).getClientTop());

TypedDependencyProperty<float> Window::RightProperty(get_Class(), WSTR("Right"), _this().getLeft() + _this().getWidth());
TypedDependencyProperty<float> Window::BottomProperty(get_Class(), WSTR("Bottom"), _this().getTop() + _this().getHeight());

TypedDependencyProperty<int> Window::StateProperty(get_Class(), WSTR("State"), 0);

TypedDependencyProperty<StringObject*> Window::RTProperty(get_Class(), WSTR("RT"), new ImmutableString<WCHAR>(L"Direct3D"));
#endif

#if 0
Window* Window::Find(const WCHAR* className, const WCHAR* windowName)
{
	return Window::FromHwnd(FindWindow(className, windowName));
}

_Window Window::Find(const Expressive::typed_expression<StringW*>& className)
{
	// TODO
	ASSERT(0);
	return Expressive::expression((Expressive::Expression*)NULL);
}

_Window Window::get_FocusWindow()
{
	return new BindingExpression(&FocusWindowBinding);
}

class WindowInit
{
public:

	CTOR WindowInit();

	Template* m_Template;
};

WindowInit::WindowInit()
{
	Refs refs;

//	_Window _templatedOwner(&TemplatedOwnerExpression::only);
	_Window _templatedOwner = Element::_this().getTemplatedOwner();//(&TemplatedOwnerExpression::only);

	m_Template =
	(
		tTemplate(refs,
			tObjectTemplate<WindowVisual>(refs.def(0),
			(
				tProperty(WindowVisual::LeftProperty) = _templatedOwner.getLeft(),
				tProperty(WindowVisual::TopProperty) = _templatedOwner.getTop(),
				tProperty(WindowVisual::WidthProperty) = _templatedOwner.getWidth(),
				tProperty(WindowVisual::HeightProperty) = _templatedOwner.getHeight(),
				tProperty(WindowVisual::TitleTextProperty) = _templatedOwner.getTitleText(),
				tProperty(WindowVisual::OpacityProperty) = _templatedOwner.getOpacity(),
				tProperty(WindowVisual::TopmostProperty) = _templatedOwner.getTopmost(),
				tProperty(WindowVisual::ClipProperty) = _templatedOwner.getClip(),
				tProperty(WindowVisual::IconProperty) = _templatedOwner.getIcon(),
				tProperty(WindowVisual::StateProperty) = _templatedOwner.getState(),
				tProperty(WindowVisual::RTProperty) = _templatedOwner.getRT(),

				tProperty(WindowVisual::ChildProperty) = tObjectTemplate<ContentElement>(
				(
					tProperty(ContentElement::get_ContentProperty()) = _templatedOwner.getContent()
				))
			))
		)
	);
}

WindowInit windowinit;

Window::Window() : ContentControl(get_Class())
{
	set_Template(windowinit.m_Template);
}

Window::Window(DependencyClass* depClass) : ContentControl(depClass)
{
	set_Template(windowinit.m_Template);
}

float Window::get_Left()
{
	return GetPropertyValueFloat(get_LeftProperty());
}

void Window::set_Left(float left)
{
	SetPropertyValue(get_LeftProperty(), left);
}

float Window::get_Top()
{
	return GetPropertyValueFloat(get_TopProperty());
}

void Window::set_Top(float top)
{
	SetPropertyValue(get_TopProperty(), top);
}

bool Window::get_Topmost()
{
	return GetPropertyValueBool(&TopmostProperty);
}

void Window::set_Topmost(bool topmost)
{
	SetPropertyValue(&TopmostProperty, topmost);
}

int Window::get_State()
{
	return GetPropertyValueInt(&StateProperty);
}

String Window::get_TitleText()
{
	return static_cast<StringObject*>(GetPropertyValue(&TitleTextProperty));
}

void Window::set_TitleText(StringIn title)
{
	SetPropertyValue(&TitleTextProperty, String(title));
}

void Window::set_Owner(Window* owner)
{
	SetPropertyValue(&OwnerProperty, owner);
}

Window* Window::get_Owner()
{
	return static_cast<Window*>(GetPropertyValue(&OwnerProperty));
//	return get_OwnerProperty()->GetValue();
}

Element* Window::get_Icon()
{
	return static_cast<Element*>(GetPropertyValue(&IconProperty));
}

void Window::set_Icon(Element* element)
{
	SetPropertyValue(&IconProperty, element);
}

void Window::set_RT(StringIn rt)
{
	SetPropertyValue(&RTProperty, String(rt));
}

void Window::Restore()
{
	SetPropertyValue(&StateProperty, 0);
}

void Window::Minimize()
{
	SetPropertyValue(&StateProperty, 1);
}

void Window::Maximize()
{
	SetPropertyValue(&StateProperty, 2);
}

Object* Create(Refs2* refs, Window* ownerWindow, UIElement* templatedOwner, Object* object)
{
	ObjectTemplate* objectTemplate = dynamic_cast<ObjectTemplate*>(object);
	if (objectTemplate)
	{
		map<int, Expressive::StaticObjectExpression*> irefs;

		Object* object = objectTemplate->Create(refs, irefs, ownerWindow, templatedOwner, NULL);
		return object;
	}
	else
	{
		return object;
	}
}

UIElement* Window::CreateShadowTree()
{
	UIElement* contentVisual = CreateObjectShadowTree(get_Content());

	Template* pTemplate = m_Template;
/*
	if (pTemplate == NULL)
	{

		pTemplate = m_Template;
	}
*/
	if (pTemplate)
	{

		Object* object = Create(pTemplate->m_refs, this, this, pTemplate->m_object);

		UIElement* element = dynamic_cast<UIElement*>(object);

		return element;
	}
	else
	{
		ASSERT(0);
	}

	return NULL;
}

#if 0
Visual* Window::CreateVisual()
{
	Visual* contentVisual = CreateObjectVisual(get_Content());

	Template* pTemplate = m_Template;

	if (pTemplate == NULL)
	{
		Refs refs;

		Window::_Window _templateOwner(&TemplateOwnerExpression::only);

		set_Template
		(
			tTemplate(refs,
				tObjectTemplate<WindowVisual>(refs.def(0),
				(
					tProperty(WindowVisual::LeftProperty) = _templateOwner.getLeft(),
					tProperty(WindowVisual::TopProperty) = _templateOwner.getTop(),
					tProperty(WindowVisual::WidthProperty) = _templateOwner.getWidth(),
					tProperty(WindowVisual::HeightProperty) = _templateOwner.getHeight(),
					tProperty(WindowVisual::TitleTextProperty) = _templateOwner.getTitleText(),
					tProperty(WindowVisual::OpacityProperty) = _templateOwner.getOpacity(),
					tProperty(WindowVisual::TopmostProperty) = _templateOwner.getTopmost(),
					tProperty(WindowVisual::ClipProperty) = _templateOwner.getClip(),

					tProperty(WindowVisual::ChildProperty) = tObjectTemplate<ContentVisual>(
					(
						tProperty(ContentVisual::ContentProperty) = _templateOwner.getContent()
					))
				))
			)
		);

		pTemplate = m_Template;
	}

	if (pTemplate)
	{

		Object* object = Create(pTemplate->m_refs, this, pTemplate->m_object);

		Visual* visual = dynamic_cast<Visual*>(object);

		return visual;
	}
	else
	{
		ASSERT(0);
		/*
		WindowVisual* windowVisual = new WindowVisual;
		contentVisual->m_root = windowVisual;

		windowVisual->get_TitleTextProperty()->AddIn(new PropertyBinding(get_TitleTextProperty()));
		windowVisual->get_WidthProperty()->AddIn(new PropertyBinding(get_WidthProperty()));
		windowVisual->get_HeightProperty()->AddIn(new PropertyBinding(get_HeightProperty()));
		windowVisual->get_OpacityProperty()->AddIn(new PropertyBinding(get_OpacityProperty()));
		windowVisual->get_ClipProperty()->AddIn(new PropertyBinding(get_ClipProperty()));

	//	windowVisual->set_Opacity(get_Opacity());
	//	windowVisual->set_Clip(get_Clip());

		windowVisual->set_Child(contentVisual);

		return windowVisual;
		*/
	}

	/*
	Gui::TextVisual* textVisual = new Gui::TextVisual();
	textVisual->m_text = get_TitleText();
	textVisual->m_brush = new Gui::SolidColorBrush(1, 0, 0);
	textVisual->m_fontFamily = new Gui::FontFamily(StringW(false, L"Gabriola"));
	textVisual->m_size = 30.0f;
	textVisual->m_layoutRect = LDraw::RectF(0, 0, 400, 60);
	textVisual->m_layoutRect.Inflate(-10, -10);
	textVisual->m_transformMatrix = D2D1::Matrix3x2F::Rotation(20, D2D1::Point2F(0, 0));

	textVisual->set_Opacity(get_Opacity());
	textVisual->set_Clip(get_Clip());

	return textVisual;
	*/

	return NULL;
}
#endif

bool Window::Show()
{
	return static_cast<WindowVisual*>(get_ShadowTree())->Show();
}

void Window::Hide()
{
	return static_cast<WindowVisual*>(get_ShadowTree())->Hide();
}

void Window::OnMouseButtonDown(LDraw::PointF clientMousePos, int button)
{
}

// static
Window* Window::get_GetDesktopWindow()
{
	return FromHwnd(::GetDesktopWindow());
}

bool Window::OnSetRoot(IRootVisual* root)
{
	ASSERT(0);
	/*

	Element* element = get_Icon();
	if (element)
	{
		element->SetRoot(root);
	}
*/
	return true;
}
#endif

///////////////////////
// ForeignWindow

//DependencyClass ForeignWindow::s_Class(typeid(ForeignWindow), &Window::s_Class);

ForeignWindow::ForeignWindow()
{
}

bool ForeignWindow::HasLocalPropertyValue(PropertyValue* pPropertyVal)
{
	if (pPropertyVal->m_dp == get_ContentProperty())
	{
		return true;
	}
	else if (pPropertyVal->m_dp == get_TitleTextProperty())
	{
		return true;
	}
	else if (pPropertyVal->m_dp == get_LeftProperty())
	{
		return true;
	}
	else if (pPropertyVal->m_dp == get_TopProperty())
	{
		return true;
	}
	else if (pPropertyVal->m_dp == get_WidthProperty())
	{
		return true;
	}
	else if (pPropertyVal->m_dp == get_HeightProperty())
	{
		return true;
	}
	else if (pPropertyVal->m_dp == get_TopmostProperty())
	{
		return true;
	}
	else if (pPropertyVal->m_dp == get_OpacityProperty())
	{
		return true;
	}
#if 0
	else if (pPropertyVal->m_dp == &ParentProperty)
	{
		//HWND hWndParent = ::GetParent(m_hWnd);
		HWND hWndParent = ::GetAncestor(m_wnd->get_Handle(), GA_PARENT);

		PlatformWindow::MyWin* p = new PlatformWindow::MyWin;
	//	p->pWindow = pWindow;

		ForeignWindow* fw = FromHwnd(hWndParent);
		return fw;
	}
#endif
	else if (pPropertyVal->m_dp == get_OwnerProperty())
	{
		return true;
	}
	else if (pPropertyVal->m_dp == get_IconProperty())
	{
		return true;
	}

	return baseClass::HasLocalPropertyValue(pPropertyVal);
}

Variant ForeignWindow::GetLocalPropertyValue(PropertyValue* pPropertyVal)
{
	if (pPropertyVal->m_dp == get_ContentProperty())
	{
		if (m_content == nullptr)
		{
			m_content = new ClientAreaContent;
		}

		return m_content;
	}
	else if (pPropertyVal->m_dp == get_TitleTextProperty())
	{
		WCHAR buffer[1204];
		GetWindowTextW(m_wnd->get_Handle(), buffer, _countof(buffer)-1);
		return String(buffer);
	}
	else if (pPropertyVal->m_dp == get_LeftProperty())
	{
		RECT windowRect;
		GetWindowRect(m_wnd->get_Handle(), &windowRect);
		return float(windowRect.left);
	}
	else if (pPropertyVal->m_dp == get_TopProperty())
	{
		RECT windowRect;
		GetWindowRect(m_wnd->get_Handle(), &windowRect);
		return float(windowRect.top);
	}
	else if (pPropertyVal->m_dp == get_WidthProperty())
	{
		RECT windowRect;
		GetWindowRect(m_wnd->get_Handle(), &windowRect);
		return float(windowRect.right - windowRect.left);
	}
	else if (pPropertyVal->m_dp == get_HeightProperty())
	{
		RECT windowRect;
		GetWindowRect(m_wnd->get_Handle(), &windowRect);
		return float(windowRect.bottom - windowRect.top);
	}
	else if (pPropertyVal->m_dp == get_TopmostProperty())
	{
		UINT exStyle = GetWindowLongW(m_wnd->get_Handle(), GWL_EXSTYLE);
		return bool((exStyle & WS_EX_TOPMOST) == WS_EX_TOPMOST);
	}
	else if (pPropertyVal->m_dp == get_OpacityProperty())
	{
		// Not tested

		COLORREF colorKey;
		BYTE alpha;
		DWORD flags;
		GetLayeredWindowAttributes(m_wnd->get_Handle(), &colorKey, &alpha, &flags);

		return float(float(alpha) * (1.0f/255.0f));
	}
#if 0
	else if (pPropertyVal->m_dp == &ParentProperty)
	{
		//HWND hWndParent = ::GetParent(m_hWnd);
		HWND hWndParent = ::GetAncestor(m_wnd->get_Handle(), GA_PARENT);

		PlatformWindow::MyWin* p = new PlatformWindow::MyWin;
	//	p->pWindow = pWindow;

		ForeignWindow* fw = FromHwnd(hWndParent);
		return fw;
	}
#endif
	else if (pPropertyVal->m_dp == get_OwnerProperty())
	{
		ASSERT(0);
		/*
		//HWND hWndParent = ::GetParent(m_hWnd);
		HWND hWndParent = ::GetAncestor(m_hWnd, GA_PARENT);

		PlatformWindow::MyWin* p = new PlatformWindow::MyWin;
	//	p->pWindow = pWindow;

		ForeignWindow* fw = FromHwnd(hWndParent);
		return fw;
		*/
	}
	else if (pPropertyVal->m_dp == get_IconProperty())
	{
		WPARAM wParam = ICON_BIG;
		HICON hIcon = (HICON)SendMessageW(m_wnd->get_Handle(), WM_GETICON, wParam, 0);

		Graphics::Bitmap* bitmap = Graphics::Bitmap::FromHICON(hIcon);
		/*
		HIconVisual* visual = new HIconVisual;
		visual->m_hIcon = hIcon;

		VisualElement* element = new VisualElement();
		element->set_Visual(visual);
		*/
		DrawBitmapVisual* element = new DrawBitmapVisual;
		//element->SetRoot(this);
		element->set_Bitmap(bitmap);

		return element;
	}

	return baseClass::GetLocalPropertyValue(pPropertyVal);
}

Visual* ForeignWindow::CreateVisual()
{
	WindowThumbnailVisual* p = new WindowThumbnailVisual(m_wnd->get_Handle());

	return p;
}

#if 0
LDraw::Bitmap* Window::GetContentBitmap()
{
	return static_cast<WindowVisual*>(get_ShadowTree())->GetContentBitmap();
}
#endif

}	// Gui
}	// System
