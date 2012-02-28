#include "stdafx.h"
#include "LXUI2.h"
#include "ChildWindow.h"
#include "ChildWindowContainer.h"
#include "Canvas.h"

namespace System
{
namespace UI
{

void ApplyStyle(Style* style, FrameworkElement* element);
Object* CreateObjectFromElement(Type* pType, Object* parentObject, XmlData::Node* node, Type** pReturnType);

__live_object_ptr<Style> ChildWindowContainerStyle;

ChildWindowContainer::ChildWindowContainer()
{
	m_ActiveChild = NULL;
	m_Canvas = NULL;

	if (ChildWindowContainerStyle == NULL)
	{
		ChildWindowContainerStyle = new Style;

		XmlData::Document* document = new XmlData::Document;

		StringW* filename = MakeFilePath(_Module, L"../../../ChildWindowContainerStyle.lxui");
		document->load(filename);

		Type* returnType;
		ChildWindowContainerStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));
		/*
		ChildWindowContainerStyle->Load(document->get_documentElement());
		*/
	}

	set_Style(ChildWindowContainerStyle);

	ApplyStyle(get_Style(), this);

	//	UpdatedVisualTree();	// ??
	InitScript();

//		ASSERT(get_VisualTree());
}

ChildWindowContainer::~ChildWindowContainer()
{
}

ChildWindow* ChildWindowContainer::get_ActiveChild() const
{
	return m_ActiveChild;
}

void ChildWindowContainer::AddItem(Object* item)
{
	ChildWindow* listboxitem = dynamic_cast<ChildWindow*>(item);
	if (listboxitem == NULL)
	{
		listboxitem = new ChildWindow;
		listboxitem->set_Content(item);
	}

//	m_owner->m_itemContainerGenerator->m_containers.push_back(listboxitem);

	m_itemsPresenter->m_panel->AddChild(listboxitem);
}

// virtual
void ChildWindowContainer::OnApplyTemplate()
{
	Selector::OnApplyTemplate();

	m_Canvas = dynamic_cast<Canvas*>(static_cast<UIElement*>(get_VisualTree())->FindChildByName(WSTR("ContentArea")));
	//ASSERT(m_Canvas);
}

void ChildWindowContainer::AddChild(ChildWindow* pWindow)
{
	ASSERT(0);

//	pWindow->SetOwnerWindow(get_OwnerWindow());	// ??? TODO, not here

	pWindow->Measure(LDraw::SizeD(0, 0));
	pWindow->Arrange(LDraw::RectD(LDraw::PointD(0, 0), pWindow->get_DesiredSize()));

	pWindow->m_Container = this;
#if 0
	m_Canvas->AddRChild(pWindow);
#endif
	/*
	UIElement* pVisual = RecalculateParent(this);
	ASSERT(pVisual);
	pVisual->Arrange(LDraw::SizeD(pVisual->m_desiredSize.Width, pVisual->m_desiredSize.Height));
	*/
	m_Canvas->InvalidateRender();
}

#if 0
void ChildWindowContainer::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (*type == L"ClickActivate")
		{
			ChildWindow* pWindow = dynamic_cast<ChildWindow*>(evt->get_target());

			if (pWindow != m_ActiveChild)
			{
				if (m_ActiveChild)
				{
					Event* evt = new Event;
					evt->InitEvent(WSTR("deactivate"), true, true);

					bool doDefault = m_ActiveChild->dispatchEvent(evt);
				}

				m_ActiveChild = pWindow;

				if (m_ActiveChild)
				{
					Event* evt = new Event;
					evt->InitEvent(WSTR("activate"), true, true);

					bool doDefault = m_ActiveChild->dispatchEvent(evt);

					// TODO, change the logical tree, the visual tree should update automatically
#if 0
					// Bring to front
					if (false)
					{
						Visual* parent = m_ActiveChild->GetRParent();
						parent->RemoveRChild(m_ActiveChild);
						parent->AddRChild(m_ActiveChild);
					}
#endif

					delete evt;

				//	((CUIFrameImpl*)get_OwnerWindow()->m_pSite)->CreateRegions();
				//	m_ActiveChild->get_OwnerWindow()->m_pSite->InvalidateRegion(m_ActiveChild->m_visibleRegion);

					m_ActiveChild->InvalidateRender();

				}
			}
		}
	}
}
#endif

}	// UI
}
