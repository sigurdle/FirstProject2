#include "stdafx.h"
#include "LXUI2.h"
#include "Layout.h"
#include "DockPanel.h"
#include "SolidColorBrush.h"
#include "ChildWindow.h"
#include "ChildWindowContainer.h"

namespace System
{
namespace UI
{

CView::CView(int index, StringW* name)
{
	m_index = index;
	m_name = name;
}

void CViewDlg::RemoveView(CView* view)
{
	ASSERT(0);
}

CViewSheet::CViewSheet()
{
	m_tabElement = NULL;
	m_pViewGroup = NULL;
}

void CViewSheet::Setup()
{
	ASSERT(0);
#if 0
	CComQIPtr<ILDOMEventTarget> eventTarget = m_sheet;

	eventTarget->addEventListener(L"DLGActivate", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE);
	eventTarget->addEventListener(L"DLGDeactivate", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE);
#endif
}

CDocumentSheet::CDocumentSheet()
{
	m_tabsElement = NULL;
	m_tabpanelsElement = NULL;
	m_sheet = NULL;
}

void CDocumentSheet::Setup()
{
	MessageBeep((UINT)-1);//ATLASSERT(0);
#if 0
	ILDOMEventTarget* eventTarget = m_sheet;

	eventTarget->addEventListener(L"DLGActivate", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE);
	eventTarget->addEventListener(L"DLGDeactivate", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE);
#endif
}

void CDocumentSheet::RemoveView(CView* view)
{
	for (int i = 0; i < m_views.GetSize(); i++)
	{
		if (m_views[i] == view)
		{
			m_views.RemoveAt(i);
			return;
		}
	}

	ASSERT(0);
}

///////////////////////////////////////////////////////////////////////////
// CDocumentWorkspace


void CDocumentWorkspace::Create(ChildWindowContainer* pFrame, CViewGroup* viewGroup)
{
//	CComQIPtr<IUIMDIFrame> mdiframe = pFrame;

#if 0
	CComQIPtr<ILXFrameworkFrame> frame = pFrame;
//	m_spAddinSite->GetFrame(&frame);

	CComPtr<ILXFrameworkApp> app;
	frame->GetApp(&app);

	CComPtr<ILXUIMDIFrameElement> frameelement;
	pFrame->GetMDIFrame(&frameelement);

//	CComPtr<ILDOMElement> mdiclient = GetElementByTagNameNS(frameelement, L"http://www.lerstad.com/2004/lxui", L"mdiclient", TRUE);
	CComPtr<ILXUIMDIClientElement> mdiclient;
	frameelement->getMDIClient(&mdiclient);

	CComPtr<ILXUIDocument> appdocument;
	frameelement->get_ownerDocument(&appdocument);
#endif

// Create

	// Palettes
	{
		for (int i = 0; i < m_viewDialogs.GetSize(); i++)
		{
			CView* view = m_viewDialogs[i]->m_view;

			UIElement* tabpanelElement = viewGroup->m_views[view->m_index];
			viewGroup->m_dialogs.Add(tabpanelElement);

		//	ILXUIElement* tabElement;
		//	createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"tab", IID_ILXUIElement, (void**)&tabElement);
			TabElement* tabElement = new TabElement(new TextString(view->m_name));
			//tabElement->put_textContent(view->m_name);
			DockPanel::SetDock(tabElement, DockPanel::Left);
#if 0
			CComPtr<ILXUIPageElement> page;
			appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", &page);
			page->put_caption(_variant_t(view->m_name));
			page->setContent(dlg);

			m_viewDialogs[i]->m_sheet->appendChild(page, NULL);
#endif

			m_viewDialogs[i]->m_tabsElement->AddChild(tabElement);
			ASSERT(0);
#if 0
			m_viewDialogs[i]->m_tabpanelsElement->AddRChild(tabpanelElement);
#endif
		//	CComQIPtr<IUIDockBar>(m_viewDialogs[i]->m_sheet)->DockControlBar(dlgsite, NULL);
		}
	}

	ChildWindow* mdichildren[16] = {0};

	// MDI child views
	for (int i = 0; i < m_documentsSheets.GetSize(); i++)
	{
#if 0
		static_cast<CLXMLEditorApp*>(m_app.p)->m_documentsSheets[i]->m_groups.Add(viewGroup);
#endif

		CViewSheet* pViewSheet = new CViewSheet;
		//CComObject<CViewSheet>::CreateInstance(&pViewSheet);
		//pViewSheet->AddRef();
		pViewSheet->m_pViewGroup = viewGroup;


		//pFrame->CreateViewSheet(L"", pViewSheet, &pViewSheet->m_sheet);
		pViewSheet->m_sheet = new CLXUITabBoxElement;//createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"tabbox", IID_ILXUIElement, (void**)&pViewSheet->m_sheet);
		//pViewSheet->m_sheet->set

		pViewSheet->m_tabsElement = new CLXUITabsElement;//createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"tabs", IID_ILXUIElement, (void**)&pViewSheet->m_tabsElement);
		//pViewSheet->m_tabsElement->set_Background(new UI::SolidColorBrush(new UI::Color(255, 0, 0)));
		DockPanel::SetDock(pViewSheet->m_tabsElement, DockPanel::Top);

		/*
		CLXUITabsElement* test = new CLXUITabsElement;//UI::Border;
		{
			TextEdit* test2 = new TextEdit;
			test2->set_Text(WSTR("Hello there"));
			test->AddChild(test2);
		}
		*/
	//	test->set_VisualTree(NULL);
		//test->set_Background(new UI::SolidColorBrush(new UI::Color(255, 0, 0)));
		//DockPanel::SetDock(test, DockPanel::Fill);
		ASSERT(0);
#if 0
		pViewSheet->m_sheet->m_Panel->AddRChild(pViewSheet->m_tabsElement);
#endif
		pViewSheet->m_tabpanelsElement = new DockPanel;//createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"tabpanels", IID_ILXUIElement, (void**)&pViewSheet->m_tabpanelsElement);
		DockPanel::SetDock(pViewSheet->m_tabpanelsElement, DockPanel::Fill);
		ASSERT(0);
#if 0
		pViewSheet->m_sheet->m_Panel->AddRChild(pViewSheet->m_tabpanelsElement);
#endif

#if 0
		pViewSheet->Setup();
#endif

		viewGroup->m_sheets.Add(pViewSheet);
		viewGroup->m_dialogs.Add(pViewSheet->m_sheet);

		// Add views in the appropriate sheet
		for (int j = 0; j < m_documentsSheets[i]->m_views.GetSize(); j++)
		{
			CView* view = m_documentsSheets[i]->m_views[j];

			UIElement* tabpanelElement = viewGroup->m_views[view->m_index];
			DockPanel::SetDock(tabpanelElement, DockPanel::Fill);

			//CComPtr<IUIDlgSite> dlgsite;
			//app->m_uiManager->CreateDlgSite(view->m_name, view->m_menu, dlg, &dlgsite);
			TabElement* tabElement = new TabElement(new TextString(view->m_name));
		//	DockPanel::SetDock(tabElement, DockPanel::Left);

		//	createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"tab", IID_ILXUIElement, (void**)&tabElement);
		//	tabElement->put_textContent(view->m_name);

			//page->setContent(dlg);

#if 0
			pViewSheet->m_sheet->appendChild(page, NULL);
#endif
			pViewSheet->m_tabsElement->AddChild(tabElement);
			pViewSheet->m_tabpanelsElement->AddChild(tabpanelElement);

			//CComQIPtr<IUIDockBar>(pViewSheet->m_sheet)->DockControlBar(dlgsite, NULL);
		}

		if (m_documentsSheets[i]->m_sheet == NULL)
		{
#if 0
			CComPtr<ILXUIPageElement> page;
			appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", (ILDOMElement**)&page);
#endif

			ASSERT(m_documentsSheets[i]->m_sheet == NULL);
			m_documentsSheets[i]->m_sheet = new CLXUITabBoxElement;//createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"tabbox", IID_ILXUIElement, (void**)&m_documentsSheets[i]->m_sheet);
			m_documentsSheets[i]->m_sheet->set_Background(new SolidColorBrush(Color::FromRgb(180, 200, 255)));

			ASSERT(m_documentsSheets[i]->m_tabsElement == NULL);
			m_documentsSheets[i]->m_tabsElement = new CLXUITabsElement;//createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"tabs", IID_ILXUIElement, (void**)&m_documentsSheets[i]->m_tabsElement);
		//	m_documentsSheets[i]->m_tabsElement->AddChild(new TextString(WSTR("Hello")));
			m_documentsSheets[i]->m_sheet->m_Panel->AddChild(m_documentsSheets[i]->m_tabsElement);

			ASSERT(m_documentsSheets[i]->m_tabpanelsElement == NULL);
			m_documentsSheets[i]->m_tabpanelsElement = new DockPanel;//createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"tabpanels", IID_ILXUIElement, (void**)&m_documentsSheets[i]->m_tabpanelsElement);
			DockPanel::SetDock(m_documentsSheets[i]->m_tabpanelsElement, DockPanel::Fill);
			m_documentsSheets[i]->m_sheet->m_Panel->AddChild(m_documentsSheets[i]->m_tabpanelsElement);

#if 0
			page->setContent(m_documentsSheets[i]->m_sheet);
#endif

			m_documentsSheets[i]->Setup();

			ChildWindow* mdichild = new ChildWindow;//createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"mdichild", IID_ILXUIMDIChildElement, (void**)&mdichild);
			mdichild->set_Width(200.0);
			mdichild->set_Height(200.0);

#if 0
			ILXUIElement* titlebar;
			createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"titlebar", IID_ILXUIElement, (void**)&titlebar);
			titlebar->put_textContent(L"-");
			mdichild->appendChild(titlebar, NULL);
#endif

//			mdichild->appendChild(m_documentsSheets[i]->m_sheet, NULL);
			mdichild->set_Content(m_documentsSheets[i]->m_sheet);
#if 0
			mdichild->appendChild(page, NULL);
#endif

			mdichildren[i] = mdichild;

#if 0
			mdiclient->appendChild(mdichild, NULL);

			mdichild->Show();
#endif
			/*
			pFrame->CreateViewSheet(NULL, m_documentsSheets[i], &m_documentsSheets[i]->m_sheet);
			CComPtr<IUIDlgSite> dlgsite;
			app->m_uiManager->CreateDlgSite(NULL, NULL, m_documentsSheets[i]->m_sheet, &dlgsite);

			CComPtr<IUIMDIChild> childFrame;
			mdiframe->CreateChildFrameDlgSite(dlgsite, &childFrame);
			*/
		}

		/*
		CComPtr<IUIDlgSite> dlgsite;
		pViewSheet->m_sheet->GetDlgSite(&dlgsite);
		CComQIPtr<IUIDockBar>(m_documentsSheets[i]->m_sheet)->DockControlBar(dlgsite, NULL);
		*/
		{
#if 0
			CComPtr<ILXUIPageElement> page;
			appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", (ILDOMElement**)&page);

			page->setContent(pViewSheet->m_sheet);
			m_documentsSheets[i]->m_sheet->appendChild(page, NULL);
#endif

			//ILXUIElement* tabElement;
			ASSERT(pViewSheet->m_tabElement == NULL);
			pViewSheet->m_tabElement = new TabElement(new TextString(WSTR("Another")));//createObjectNS(appdocument, L"http://www.lerstad.com/2004/lxui", L"tab", IID_ILXUIElement, (void**)&pViewSheet->m_tabElement);
			//pViewSheet->m_tabElement->put_textContent(L"");	// TODO remove this

		//	DockPanel::put_Dock(pViewSheet->m_tabElement, DockPanel::Left);
			m_documentsSheets[i]->m_tabsElement->AddChild(pViewSheet->m_tabElement);
			DockPanel::SetDock(pViewSheet->m_sheet, DockPanel::Fill);
			m_documentsSheets[i]->m_tabpanelsElement->AddChild(pViewSheet->m_sheet);
		}
	}

	{
		for (int i = 0; i < m_documentsSheets.GetSize(); i++)
		{
			if (mdichildren[i])
			{
				pFrame->AddChild(mdichildren[i]);
			}
		}
	}

#if 0
	{
		CComBSTR xml;
		appdocument->saveXML(CComVariant(), &xml);

		MessageBox(NULL, _bstr_t(xml), "", MB_OK);
	}
#endif
}

}	// UI
}
