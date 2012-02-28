#include "stdafx.h"
#include "LXUI2.h"

//#include <functional>

namespace System
{
namespace UI
{

DependencyProperty* BaseWindow::s_TitleProperty = RegisterProperty(WSTR("Title"), typeid(Object), typeid(BaseWindow), NULL, PropertyMetaData(None));
DependencyProperty* BaseWindow::s_IsActiveProperty = RegisterProperty(WSTR("IsActive"), typeid(bool), typeid(BaseWindow), BoolObject::get_False(), PropertyMetaData(None));

BaseWindow::BaseWindow()
{
}

Object* BaseWindow::get_Title()
{
	return GetValue(get_TitleProperty());
}

void BaseWindow::set_Title(Object* title)
{
	SetValue(get_TitleProperty(), title);
}

bool BaseWindow::get_IsActive()
{
	return static_cast<BoolObject*>(GetValue(get_IsActiveProperty()))->GetValue();
}

void BaseWindow::set_IsActive(bool isActive)
{
	SetValue(get_IsActiveProperty(), BoolObject::GetObject(isActive));
}

__live_object_ptr<Style> WindowStyle;

DependencyProperty* Window::s_LeftProperty = RegisterProperty(WSTR("Left"), typeid(double), typeid(Window), DoubleObject::get_NaN(), PropertyMetaData(None));
DependencyProperty* Window::s_TopProperty = RegisterProperty(WSTR("Top"), typeid(double), typeid(Window), DoubleObject::get_NaN(), PropertyMetaData(None));
DependencyProperty* Window::s_IconProperty = NULL;//RegisterProperty(WSTR("Icon"), typeid(ImageSource), typeid(Window), NULL, PropertyMetaData(None));
DependencyProperty* Window::s_TopmostProperty = RegisterProperty(WSTR("Topmost"), typeid(bool), typeid(Window), BoolObject::get_False(), PropertyMetaData(None));
DependencyProperty* Window::s_ShowInTaskbarProperty = RegisterProperty(WSTR("ShowInTaskbar"), typeid(bool), typeid(Window), BoolObject::get_True(), PropertyMetaData(None));

Window::Window()
{
	m_owner = NULL;
//	m_Title = NULL;
	m_CloseButton = NULL;
	m_MinimizeButton = NULL;
	m_MaximizeButton = NULL;
#if 0
	m_pBorder = NULL;
	m_pBorder2 = NULL;
#endif

	if (WindowStyle == NULL)
	{
//		FrameWindowStyle = new Style;

	//	DataTemplate* pTemplate = new DataTemplate;
		XmlData::Document* document = new XmlData::Document;

		StringW* filename = MakeFilePath(_Module, L"../../../FrameWindowStyle.lxui");
		document->load(filename);

		if (document->get_documentElement() == NULL)
		{
			throw std::exception("failed to load xml document");
		}

		Type* returnType;
		WindowStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));

		/*
		FrameWindowStyle->Load(document->get_documentElement());
		*/

	//	pTemplate->Load(document->get_documentElement());
	//	m_ControlTemplate = pTemplate;
	}

	set_Style(WindowStyle);

	/*
	ApplyStyle(get_Style(), this);

	InitScript();
	*/

	/*
	TextString* title = new TextString(WSTR("Hello"));
	title->set_TextFill(new SolidColorBrush(new Color(255, 255, 255)));

	set_Title(title);
	*/
}

Window::~Window()
{
}

UI::DesktopScreen* g_Desktop = new UI::DesktopScreen;

void Window::Show()
{
	VisualContentSource* contentSource = new VisualContentSource;
	contentSource->set_VisualTree(this);

	PresentationSource* source = g_Desktop->OpenWindow();
	source->SetClient(contentSource);
	source->Show(NULL, NULL);
/*
	UI::WindowBase2* pBase2 = new UI::WindowBase2;
	pBase2->set_VisualTree(this);

	UI::IWindowHost* site = g_Desktop->OpenWindow();
	site->SetClient(pBase2);
	site->Show(NULL, NULL);
	*/
}

double Window::get_Left()
{
	return static_cast<DoubleObject*>(GetValue(get_LeftProperty()))->GetValue();
}

void Window::set_Left(double left)
{
	SetValue(get_LeftProperty(), DoubleObject::GetObject(left));
}

double Window::get_Top()
{
	return static_cast<DoubleObject*>(GetValue(get_TopProperty()))->GetValue();
}

void Window::set_Top(double top)
{
	SetValue(get_TopProperty(), DoubleObject::GetObject(top));
}

bool Window::get_Topmost()
{
	return static_cast<BoolObject*>(GetValue(get_TopmostProperty()))->GetValue();
}

void Window::set_Topmost(bool topmost)
{
	SetValue(get_TopmostProperty(), BoolObject::GetObject(topmost));
}

bool Window::get_ShowInTaskbar()
{
	return static_cast<BoolObject*>(GetValue(get_ShowInTaskbarProperty()))->GetValue();
}

void Window::set_ShowInTaskbar(bool showInTaskbar)
{
	SetValue(get_ShowInTaskbarProperty(), BoolObject::GetObject(showInTaskbar));
}

Window* Window::get_Owner()
{
	return m_owner;
}

void Window::set_Owner(Window* owner)
{
	if (m_owner != owner)
	{
		if (m_owner)
		{
			// TODO
			VERIFY(0);
		}

		owner->m_ownedWindows->Add(this);
		m_owner = owner;
	}
}

WindowCollection* Window::get_OwnedWindows()
{
	return m_ownedWindows;
}

/*
StringW* Window::get_TitleText()
{
	if (m_Title)
	{
		return m_Title->get_TextContent();
	}
	return NULL;
}

void Window::set_TitleText(StringW* title)
{
//	printf("Window::set_TitleText()...");

	if (m_Title)
	{
		WindowBase* pOwnerWindow = GetOwnerWindow();
		if (pOwnerWindow && static_cast<NativeWindow*>((pOwnerWindow)->m_pSite)->GetHwnd())
		{
#if WIN32
			MSWindows::SetWindowTextW(static_cast<NativeWindow*>((pOwnerWindow)->m_pSite)->GetHwnd(), title->c_str());
#else
			ASSERT(0);
#endif
		}

	//	printf("m_Title->put_TextContent()");
		m_Title->set_TextContent(title);
	}
	else
	{
		//std::printf("m_Title = NULL");
	}

//	printf("..\n");
}
*/

void Window::OnActivate(bool bActive)
{
#if 0
	if (m_pBorder2)
	{
		if (bActive)
			m_pBorder2->set_Background(new SolidColorBrush(new Color(102, 136, 187)));
		else
			m_pBorder2->set_Background(new SolidColorBrush(new Color(200, 200, 200)));

		m_pBorder2->Invalidate();
	}
#endif
}

#if 0
void Window::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (*type == L"click")
		{
			if (evt->get_target() == m_CloseButton)
			{
				evt->stopPropagation();
				{
					Event* evt = new Event;
					evt->InitEvent(WSTR("close"), false/*bubbles*/, true/*cancelable*/);
					bool doDefault = dispatchEvent(evt);
					if (doDefault)
					{
						//dynamic_cast<WindowHost*>(dynamic_cast<WindowBase*>(GetRParent())->m_pSite)->Close();
#if WIN32
						MSWindows::SendMessageA(static_cast<NativeWindow*>(GetOwnerWindow()->m_pSite)->GetHwnd(), WM_CLOSE, 0, 0);
#else
						ASSERT(0);
#endif
					}

					delete evt;
				}
			}
			else if (evt->get_target() == m_MinimizeButton)
			{
				evt->stopPropagation();
				{
#if 0
					Event* evt = new Event;
					evt->initEvent(WSTR("close"), false/*bubbles*/, true/*cancelable*/);
					bool doDefault = dispatchEvent(evt);
					if (doDefault)
					{
						dynamic_cast<WindowHost*>(dynamic_cast<WindowBase*>(GetRParent())->m_pSite)->Close();
					}

					delete evt;
#endif
#if WIN32
					MSWindows::CloseWindow(static_cast<NativeWindow*>(GetOwnerWindow()->m_pSite)->GetHwnd());
#else
					ASSERT(0);
#endif
				}
			}
		}
	}

	Control::handleEvent(evt);
}
#endif

void Window::OnClose(Object* sender, RoutedEventArgs* args)
{
	// TODO, raise some event

	MSWindows::SendMessageW(static_cast<HwndSource*>(GetOwnerWindow()->m_pSite)->GetHwnd(), WM_CLOSE, 0, 0);
}

#if 0
template<class F> class binder1st_t
{
public:
	binder1st_t(const F& f, typename F::argument1_type arg1) : m_f(f), m_arg1(arg1)
	{
	}

	void operator () (typename F::argument2_type arg2, typename F::argument3_type arg3) const
	{
		m_f(m_arg1, arg2, arg3);
	}

	F m_f;
	typename F::argument1_type m_arg1;
};

template<class F> function2<typename F::argument2_type, typename F::argument3_type> bind(F f, typename F::argument1_type arg1)
{
	return binder1st_t<F>(f, arg1);
}

template<class F> class binder2st_t
{
public:
	binder2st_t(const F& f, typename F::argument1_type arg1, typename F::argument2_type arg2) : m_f(f), m_arg1(arg1), m_arg2(arg2)
	{
	}

	void operator () (typename F::argument3_type arg3, typename F::argument4_type arg4) const
	{
		m_f(m_arg1, m_arg2, arg3, arg4);
	}

	F m_f;
	typename F::argument1_type m_arg1;
	typename F::argument2_type m_arg2;
};

template<class F> function2<typename F::argument3_type, typename F::argument4_type> bind3(F f, typename F::argument1_type arg1, typename F::argument2_type arg2)
{
	return binder2st_t<F>(f, arg1, arg2);
}
#endif

// virtual
void Window::OnApplyTemplate()
{
	ContentControl::OnApplyTemplate();

	m_CloseButton = dynamic_cast<ButtonBase*>(static_cast<UIElement*>(get_VisualTree())->FindChildByName(WSTR("CloseButton")));
	m_MinimizeButton = dynamic_cast<ButtonBase*>(static_cast<UIElement*>(get_VisualTree())->FindChildByName(WSTR("MinimizeButton")));

	if (m_CloseButton == NULL)
	{
		throw new Exception(WSTR("Couldn't find CloseButton"));
	}

	ASSERT(m_CloseButton);
	ASSERT(m_MinimizeButton);

//	mem_fun2(&Window::OnClose);
//	m_CloseButton->get_Click().connect(std::bind1st(mem_fun2(&Window::OnClose), this));

	m_CloseButton->get_Click().connect(bind1st_of_3(mem_fun2(&Window::OnClose), this));

	//m_MinimizeButton->get_Click().connect(std::bind1st(std::mem_fun1(&Window::OnClose), this));
}

}
}
