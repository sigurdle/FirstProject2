#include "stdafx.h"
#include "LXUI2.h"
#include "ChildWindow.h"
#include "LXUIBoxWindow.h"
//#include "../LFC/XmlData.h"

#if AMIGA
#define _alloca alloca
#endif

#if 0
template<class T> T min(T v0, T v1)
{
	return v0 < v1? v0: v1;
}

template<class T> T max(T v0, T v1)
{
	return v0 > v1? v0: v1;
}
#endif

namespace System
{
namespace UI
{

//void SetValue(Dispatch* dispatch, void* _this, Method* method, Object* pObject, Type* pSourceType);


// LengthAnimation

/*
LengthAnimation::LengthAnimation()
{
	m_from = NULL;
	m_to = NULL;
}

Length* LengthAnimation::get_From()
{
	return m_from;
}

void LengthAnimation::set_From(Length* value)
{
	m_from = value;
}

Length* LengthAnimation::get_To()
{
	return m_to;
}

void LengthAnimation::set_To(Length* value)
{
	m_to = value;
}

Object* LengthAnimation::GetCurrentValue(Object* baseVal)
{
	double val = m_from->get_Value() + (m_to->get_Value() - m_from->get_Value()) * (m_currentTime / m_duration);

	return new Length(val);
}
*/

void ApplyStyle(Style* style, FrameworkElement* element);
Object* CreateObjectFromElement(Type* pType, Object* parentObject, XmlData::Node* node, Type** pReturnType);

__live_object_ptr<Style> ChildWindowStyle;

ChildWindow::ChildWindow()
{
	m_Container = NULL;

//	m_Title = NULL;
//	m_Content = NULL;

//	m_pBorder = NULL;
//	m_pBorder2 = NULL;
	m_CloseButton = NULL;
	m_pStatusbar = NULL;

	// Find a style with TargetType="ChildWindow"

	if (ChildWindowStyle == NULL)
	{
		ChildWindowStyle = new Style;

		//DataTemplate* pTemplate = new DataTemplate;
		XmlData::Document* document = new XmlData::Document;
		StringW* filename = MakeFilePath(_Module, L"../../../ChildWindowStyle.lxui");
		document->load(filename);

//		document->load(WSTR("C:/mmstudio/ChildWindowStyle.lxui"));

		Type* returnType;
		ChildWindowStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));
		/*
		ChildWindowStyle->Load(document->get_documentElement());
*/
	}

	set_Style(ChildWindowStyle);

//	TextString* title = new TextString(WSTR(""));
//	title->set_TextFill(new SolidColorBrush(new Color(255, 255, 255)));

	Init();
//	set_Title(title);
}

ChildWindow::~ChildWindow()
{
}

void ChildWindow::Init()
{
	/*
	{
		DataTemplate* pTemplate = new DataTemplate;
		XmlData::Document* document = new XmlData::Document;
#if WIN32
		document->load(WSTR("C:/ChildWindow.lxui"));
#else
		document->load(WSTR("WinHD_C:/ChildWindow.lxui"));
#endif

		pTemplate->Load(document->get_documentElement());
	//	put_ControlTemplate(pTemplate);
		m_ControlTemplate = pTemplate;
	}
	*/

	{
		/*
		DataTemplate* pTemplate = new DataTemplate;
		XmlData::Document* document = new XmlData::Document;
#if WIN32
		document->load(WSTR("C:/ChildWindow.lxui"));
#else
		document->load(WSTR("WinHD_C:/ChildWindow.lxui"));
#endif

		pTemplate->Load(document->get_documentElement());

		pTemplate->m_RootNode->SetProperties(this, this, m_objectpropertymap);
	//	put_ControlTemplate(pTemplate);
	*/

		ApplyStyle(get_Style(), this);

		InitScript();

	//	ASSERT(get_VisualTree());
	}
}

// virtual
void ChildWindow::OnApplyTemplate()
{
	ContentControl::OnApplyTemplate();

	m_CloseButton = dynamic_cast<ButtonBase*>(get_VisualTree()->FindChildByName(WSTR("CloseButton")));
}

/*
TextString* ChildWindow::get_Title()
{
	return m_Title;
}

void ChildWindow::set_Title(TextString* title)
{
	m_Title = title;
	PropertyChanged(ASTR("Title"));
}

StringW* ChildWindow::get_TitleText()
{
	if (m_Title)
	{
		return m_Title->get_TextContent();
	}
	else
	{
		return NULL;
	}
}

void ChildWindow::set_TitleText(StringW* title)
{
	if (m_Title)
	{
		m_Title->set_TextContent(title);
	}
}
*/

/*
UIElement* ChildWindow::get_Content()
{
	return m_Content;
}

void ChildWindow::set_Content(UIElement* content)
{
	m_Content = content;
	PropertyChanged(ASTR("Content"));

//	EnsureVisuals();
}
*/

void ChildWindow::set_StatusbarContent(UIElement* content)
{
	m_pStatusbar->set_Child(content);
}

#if 0
void ChildWindow::EnsureVisuals()
{
//	FillToStroke* p = new FillToStroke;
//	EditTransform* p = new EditTransform;
//	DropShadow* p = new DropShadow;
	{
		m_pBorder = new Border;
		m_pBorder->put_BorderThickness(Thickness(Length(1), Length(1), Length(1), Length(1)));
		m_pBorder->m_LeftBrush = new SolidColorBrush(Color(255, 255, 255));
		m_pBorder->m_TopBrush = new SolidColorBrush(Color(255, 255, 255));
		m_pBorder->m_RightBrush = new SolidColorBrush(Color(90, 90, 90));
		m_pBorder->m_BottomBrush = new SolidColorBrush(Color(90, 90, 90));
		m_pBorder->put_Background(new SolidColorBrush(Color(102, 136, 187)));

		{
			m_pBorder2 = new Border;
		//	m_pBorder2->put_BackgroundBrush(new SolidColorBrush(new Color(102, 136, 187)));
			m_pBorder2->put_BorderThickness(Thickness(Length(3), Length(3), Length(3), Length(3)));
		/*
		pBorder->m_LeftBrush = new CLLinearGradientBrush(new Color(255, 255, 255), new Color(190, 190, 190), new Point(0, 0), new Point(0, 1));
		pBorder->m_TopBrush = new CLLinearGradientBrush(new Color(255, 255, 255), new Color(190, 190, 190), new Point(0, 0), new Point(1, 0));
		pBorder->m_RightBrush = new CLLinearGradientBrush(new Color(190, 190, 190), new Color(0, 0, 0), new Point(0, 0), new Point(0, 1));
		pBorder->m_BottomBrush = new CLLinearGradientBrush(new Color(190, 190, 190), new Color(0, 0, 0), new Point(0, 0), new Point(1, 0));
		*/

			{
				DockPanel* pDockPanel = new DockPanel;
				{
					DockPanel* pDockPanel2 = new DockPanel;
					{
						m_CloseButton = new Button(new TextString(WSTR("X")));
						pDockPanel2->put_Dock(m_CloseButton, DockPanel::Right);
						pDockPanel2->AddRChild(m_CloseButton);
					}
					{
						Mover* p = new Mover();
						{
							Border* pCanvas = new Border;
							pCanvas->put_BorderThickness(Thickness(Length(2), Length(2), Length(2), Length(2)));
						//	pCanvas->put_BackgroundBrush(new SolidColorBrush(new Color(102, 136, 187)));

							{
								pCanvas->put_Content(m_Title);
							}
							p->put_VisualTree(pCanvas);
						}

						DockPanel::put_Dock(p, DockPanel::Fill);
						pDockPanel2->AddRChild(p);
					}
					pDockPanel->AddRChild(pDockPanel2);
				}

				{
					m_pStatusbar = new Border(Thickness(Length(0.0), Length(0.0), Length(0.0), Length(0.0)));

					{
						DockPanel* panel = new DockPanel;

						{
							Sizer* pSizeBox = new Sizer();
							UI::DockPanel::put_Dock(pSizeBox, DockPanel::Right);
							panel->AddRChild(pSizeBox);
						}

						m_pStatusbar->put_Content(panel);
					}

					UI::DockPanel::put_Dock(m_pStatusbar, DockPanel::Bottom);
					pDockPanel->AddRChild(m_pStatusbar);
				}

				{
					pDockPanel->put_Dock(m_Content, DockPanel::Fill);

					pDockPanel->AddRChild(m_Content);
				}
				m_pBorder2->put_Content(pDockPanel);
			}
			m_pBorder->put_Content(m_pBorder2);
		}
//		p->put_Content(m_pBorder);
	}
//	put_VisualTree(p);

	put_VisualTree(m_pBorder);
}
#endif

#if 0
void ChildWindow::handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase == CAPTURING_PHASE)
	{
		if (type == MouseEvent::mousedown)
		{
			Event* evt = new Event;
			evt->InitEvent(WSTR("ClickActivate"), true/*bubbles*/, true/*cancelable*/);

			bool doDefault = dispatchEvent(evt);
		}
	}
	else
	{
		if (*type == L"activate")
		{
			evt->stopPropagation();

			/*
			if (m_pBorder)
			{
				m_pBorder->set_Background(new SolidColorBrush(new Color(102, 136, 187)));
				Invalidate();
			}
			*/
		}
		else if (*type == L"deactivate")
		{
			evt->stopPropagation();

			/*
			if (m_pBorder)
			{
				m_pBorder->set_Background(new SolidColorBrush(new Color(200, 200, 200)));
				Invalidate();
			}
			*/
		}
		else if (*type == L"click" && evt->get_target() == m_CloseButton)
		{
			evt->stopPropagation();

			Event* evt = new Event;
			evt->InitEvent(WSTR("close"), false/*bubbles*/, true/*cancelable*/);

			bool doDefault = dispatchEvent(evt);
			if (doDefault)
			{
				Invalidate();

				Visual* pParent = GetRParent();

				pParent->RemoveRChild(this);

			//	pParent->Invalidate();
			}
		}
	}
}
#endif

}	// UI
}
