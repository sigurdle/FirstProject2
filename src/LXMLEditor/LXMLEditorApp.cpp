#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"


#include "LXMLEditorApp.h"

//#include "LXMLEditorFrame.h"

/*
#include "InspectorDlg.h"
#include "CSSPropertiesDlg.h"
#include "EColorDlg.h"
*/
//#include "SVGToolsDlg.h"
/*
#include "WENavigatorDlg.h"
#include "SVGSwatchesDlg.h"
#include "SVGFiltersDlg.h"
#include "SVGMasksDlg.h"
#include "SVGClipPathsDlg.h"
#include "SVGSymbolsDlg.h"
#include "SMILTransitionsDlg.h"
#include "EditFilterDlg.h"
#include "EditGradientDlg.h"
#include "SVGObjectsDlg.h"
#include "ScriptOutlineDlg.h"
#include "ElementAttrsDlg.h"
#include "ElementsDlg.h"
#include "EntitiesDlg.h"
#include "AnimationInspectorDlg.h"
#include "ASObjectInspectorDlg.h"
#include "AnimateAttributesDlg.h"
#include "SVGSwatchLibraryDlg.h"
#include "EXMLDocumentStyleSheetsView.h"

#include "SourceView.h"
#include "XMLGridView.h"
#include "EXMLLayoutView.h"
#include "HTMLFramesDesignView.h"
#include "SMILRegionsView.h"
#include "SMILTimeGraphView.h"
#include "XSLTTemplatesDlg.h"
#include "DTDView.h"
  */
#include "SVGToolsDlg.h"

#include "ToolOptionsDlg.h"
#include "ToolPresetsDlg.h"

#include "EXMLDocument.h"

#include "OpenURLDlg.h"
#include "FileNewDlg.h"
#include "PrefsTabsDlg.h"
#include "PrefsSourceDlg.h"
#include "PrefsFormatDlg.h"
#include "PrefsTransparencyDlg.h"

//////////////////////////////////////////////////

namespace System
{
namespace LXmlEdit
{

//extern "C" GUID CATID_LXMLEditorPlugin;

#if 0
void ComError(_com_error &e)
{
#if 0
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());

	CUString msg;
	msg.Format("\n\tSource :  %s \n\tdescription : %s \n ",(LPCSTR)bstrSource,(LPCSTR)bstrDescription);

	MessageBox(NULL/*TODO GetMainHwnd()*/, msg, "WebEditor", MB_OK);
#endif
}
#endif
	/*
	{
#define COLOR_XML_ELEMENT_NAME		1
#define COLOR_XML_ATTRIBUTE_NAME		2
#define COLOR_XML_ATTRIBUTE_VALUE	3
#define COLOR_XML_TAG_DELIMITER		4
#define COLOR_XML_COMMENT				5
#define COLOR_XML_OPERATOR				6

#define COLOR_JSCRIPT_KEYWORD			7
#define COLOR_JSCRIPT_STRING			8
#define COLOR_JSCRIPT_COMMENT			9

//		RegisterFormatStyle(L"
	}
	*/


/////////////////////////////////////////////
// CLElementBehaviorFactory

#if 0
ErrorCode CLElementBehaviorFactory::FindBehavior(BSTR bstrBehavior, BSTR bstrBehaviorUrl, ILElementBehaviorSite* pSite, ILElementBehavior** ppBehavior)
{
	if (ppBehavior == NULL) return E_POINTER;
	*ppBehavior = NULL;

	/*
	if (!wcscmp(bstrBehavior, L"svg_edit"))
	{
		CComObject<CLSVGBehavior>* pBehavior;
		CComObject<CLSVGBehavior>::CreateInstance(&pBehavior);
		if (pBehavior)
		{
			pBehavior->AddRef();

		// Behaviours WebEditor Document
			ASSERT(0);
#if 0
			pBehavior->m_pDocument = m_pDocument;
#endif

		// Get the behaviors viewGroup
			CComPtr<IUnknown> oleViewUnknown;
			pSite->GetDocumentView(&oleViewUnknown);

			CComQIPtr<IOleDocumentView> oleView = oleViewUnknown;

			CComPtr<IOleInPlaceSite> ip;
			oleView->GetInPlaceSite(&ip);
			if (ip)
			{
				CComQIPtr<IEXMLLayoutView> layoutView = ip;
				if (layoutView)
				{
					static_cast<CEXMLLayoutView*>(layoutView.p)->m_pBehavior = pBehavior;
					pBehavior->m_layoutView = static_cast<CEXMLLayoutView*>(layoutView.p);
					pBehavior->m_viewGroup = static_cast<CEXMLLayoutView*>(layoutView.p)->m_viewGroup;
					ASSERT(pBehavior->m_viewGroup);

					*ppBehavior = pBehavior;
				}
			}
		}
	}
	*/
	if (!wcscmp(bstrBehavior, L"svgtools"))
	{
		CComObject<CSVGToolsDlg>* p;
		CComObject<CSVGToolsDlg>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			p->m_app = m_pApp;
			*ppBehavior = p;
		}
	}
	/*
	else if (!wcscmp(bstrBehavior, L"xml_layout"))
	{
		CComObject<CEXMLLayoutView>* p;
		CComObject<CEXMLLayoutView>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			*ppBehavior = p;
		}
	}
	*/
	/*
	else if (!wcscmp(bstrBehavior, L"xml_source"))
	{
		CComObject<CSourceView>* p;
		CComObject<CSourceView>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			*ppBehavior = p;
		}
	}
	else if (!wcscmp(bstrBehavior, L"xml_timegraph"))
	{
		CComObject<CSmilTimeGraphView>* p;
		CComObject<CSmilTimeGraphView>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			*ppBehavior = p;
		}
	}
	*/
	/*
	else if (!wcscmp(bstrBehavior, L"xml_inspector"))
	{
		CComObject<CInspectorDlg>* p;
		CComObject<CInspectorDlg>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			*ppBehavior = p;
		}
	}
	*/
	/*
	else if (!wcscmp(bstrBehavior, L"objects"))
	{
		CComObject<CSVGObjectsDlg>* p;
		CComObject<CSVGObjectsDlg>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			*ppBehavior = p;
		}
	}
	*/
#if 0
	// X3D/MPEG-4
	else if (!wcscmp(bstrBehavior, L"scene_3dview"))
	{
		CComObject<CX3DView>* p;
		CComObject<CX3DView>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			*ppBehavior = p;
		}
	}
	else if (!wcscmp(bstrBehavior, L"scene_graph"))
	{
		CComObject<CSceneGraphDlg>* p;
		CComObject<CSceneGraphDlg>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			*ppBehavior = p;
		}
	}
#endif
	else
		ASSERT(0);

	return S_OK;
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CLXMLEditorApp

CLXMLEditorApp::CLXMLEditorApp()
{
//		m_xsltDocuments = NULL;

	m_pActiveTool = NULL;
	m_pActiveSelectionTool = NULL;

#if 0
	m_pElementBehaviorFactory = NULL;
#endif
//		m_ActiveDocument = NULL;

	m_strokeOrFill = 0;

	m_macroRecording = false;

// Preferences
	m_tabSize = 3;
	m_colorFormat = 1;	// hex #XXXXXX

	m_transpGridSizeX = 8;
	m_transpGridSizeY = 8;
#if 0
	m_transpGridColor0 = RGB(255, 255, 255);
	m_transpGridColor1 = RGB(194, 194, 194);
#endif
//	CComPtr<ILXUIDocument> appdocument;
//	m_spAddinSite->GetUIDocument(&appdocument);

//	CComQIPtr<IUIFrame> frame = m_frame;

#if 0
	// Add-ins
	{
		CComPtr<ICatInformation> catinfo;
		ErrorCode hr = S_OK;
 
		hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_ICatInformation,
			(LPVOID*)&catinfo);

		if(SUCCEEDED(hr))
		{
			CRegKey clsidkey;
			clsidkey.Open(HKEY_CLASSES_ROOT, "CLSID");

			CATID impl[1];
			impl[0] = CATID_LXMLEditorPlugin;

			CComPtr<IEnumCLSID> enumClsid;
			catinfo->EnumClassesOfCategories(1, impl, 0, NULL, &enumClsid);

			CLSID clsid;
			ULONG fetched;
			while ((enumClsid->Next(1, &clsid, &fetched) == S_OK) && (fetched == 1))
			{
				CComObject<CPluginClass>* pPluginClass;

				CComObject<CPluginClass>::CreateInstance(&pPluginClass);
				if (pPluginClass)
				{
					pPluginClass->AddRef();

					pPluginClass->m_app = this;

					LPOLESTR clsidstr;
					StringFromCLSID(clsid, &clsidstr);

					CRegKey key;
					key.Open(clsidkey, _bstr_t(clsidstr));

					CoTaskMemFree(clsidstr);

					TCHAR name[256];
					DWORD n = 255;
					key.QueryValue(name, NULL, &n);
					pPluginClass->m_name = name;

					pPluginClass->m_clsid = clsid;
					
					m_plugins.Add(pPluginClass);
				}
			}
		}
	}
#endif

#if 0	// Empty dock
	{
		CComPtr<IUIDlgSheet> sheet;
		m_uiManager->CreateDlgSheet(NULL, NULL, &sheet);
		sheet->SetMinimized(TRUE);

		CComPtr<IUIDlgSite> sheetSite;
		sheet->GetDlgSite(&sheetSite);
		frame->DockControlBar(sheetSite, 0, &CRect(9999,0,0,0));
	}
#endif

#if 0	// Had this
	TCHAR filename[512];
	GetModuleFileName(_Module.m_hInstResource, filename, 512);

	CComPtr<ILXFrameworkFrame> frame;
	m_spAddinSite->GetFrame(&frame);

	CComPtr<ILXFrameworkApp> app;
	frame->GetApp(&app);

	CComPtr<ILXUIMDIFrameElement> frameelement;
	frame->get_Element(&frameelement);

	CComPtr<ILXUIDocument> appdocument;
	app->get_Document(&appdocument);

	appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"toolbar", (ILDOMElement**)&m_toolsElement);
	frameelement->appendChild(m_toolsElement, NULL);

// Dialogs

	{
		{
			CComPtr<ILXUIMenuItemElement> menu;
			appdocument->loadMenu(_bstr_t(filename), IDR_MAINFRAME, &menu);

			CComPtr<ILXUIPageElement> page;
			appdocument->createMenuBarPage(L"MenuBar", menu, GetUnknown(), &page);

			frameelement->floatBar(page, 40, 40);

			/*
			CComPtr<ILXUIPageElement> page;
			appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", (ILDOMElement**)&page);
			if (page)
			{
				page->put_caption(_variant_t(L"MenuBar"));

				ILXUIElement* content;
				appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"content", (ILDOMElement**)&content);
				if (content)
				{
					CComPtr<ILXUIMenuBarElement> menubar;
					appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"menubar", (ILDOMElement**)&menubar);
					if (menubar)
					{
						menubar->setMenu(CComVariant(menu));

						content->appendChild(menubar, NULL);

						CComQIPtr<ILDOMEventTarget> eventTarget = menubar;
						eventTarget->addEventListener(L"command", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE);
					}
					page->appendChild(content, NULL);
				}

				frameelement->floatBar(page, 40, 40);
			}
			*/
		}
	}

#if 0
	{
		CComPtr<IUIMenuDlg> menuDlg;
		m_uiManager->CreateMenuDlg(&menuDlg);

		CComPtr<IMenuItem> menuItem;
		m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_MAINFRAME, &menuItem);

		CComPtr<IMenuItem> menuItem0 = menuItem;
		//menuItem->GetSubMenu(0, &menuItem0);

		menuDlg->InitMenu(menuItem0, this/*CComQIPtr<ICommandTarget>(GetFrame())*/, -1);

		CComPtr<IUIDlgSite> dlgsite;
		m_uiManager->CreateDlgSite(L"MenuBar", NULL, menuDlg, &dlgsite);

		frame->FloatControlBar(dlgsite, CPoint(40,40), CBRS_SIZE_DYNAMIC);
	}
#endif

#if 0	// Have this
	{
		CComObject<CToolOptionsDlg>* p;
		CComObject<CToolOptionsDlg>::CreateInstance(&p);
		p->AddRef();
		m_pToolOptionsDlg = p;

		m_uiManager->CreateDlgSheet(NULL, NULL, &m_pToolOptionsDlg->m_presetsPopup);

		m_uiManager->CreateDlgSheet(NULL, NULL, &m_pToolOptionsDlg->m_sheet);
		m_pToolOptionsDlg->m_sheet->ShowTabs(FALSE);

		CComPtr<IUIDlgSite> site;
		m_uiManager->CreateDlgSite(L"Tool Options", NULL, p, &site);

		frame->FloatControlBar(site, CPoint(40,40), CBRS_SIZE_DYNAMIC);
	}
#endif

	for (int i = 0; i < m_plugins.GetSize(); i++)
	{
		CComObject<CPluginClass>* pluginClass = m_plugins[i];

		pluginClass->m_p.CoCreateInstance(pluginClass->m_clsid);
		if (pluginClass->m_p)
		{
			pluginClass->m_p->SetSite(pluginClass);
		}
	}

	/*
	{
		CComObject<CSVGToolsDlg>* p;
		CComObject<CSVGToolsDlg>::CreateInstance(&p);
		if (p)
		{
			p->m_app = this;
			p->m_pUIManager = m_uiManager;

			CComPtr<IUIDlgSite> site;
			m_uiManager->CreateDlgSite(L"SVG Tools", NULL, p, &site);
			m_svgToolsBar = site;

			frame->FloatControlBar(m_svgToolsBar, CPoint(40,40), CBRS_SIZE_DYNAMIC);
			m_svgToolsBar->Show(FALSE);
		}
	}
	*/
	{
		CComPtr<ILXUIPageElement> page;
		appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", (ILDOMElement**)&page);

		{
			CComPtr<ILDOMElement> e;
			appdocument->createElementNS(NULL, L"content", &e);

			CComPtr<IUnknown> old;
			e->setUserData(L"n", this->GetUnknown(), NULL, &old);

			VARIANT vFactory;
			V_VT(&vFactory) = VT_UNKNOWN;
			V_UNKNOWN(&vFactory) = m_pElementBehaviorFactory;
			V_UNKNOWN(&vFactory)->AddRef();

			long cookie;
			e->addBehavior(L"#factory#svgtools", &vFactory, &cookie);

			page->appendChild(e, NULL);
		}

		frameelement->floatBar(page, 40, 40);
	}

#if 0	// Have this
/////////////////
	m_uiManager->RegisterMenuDlg(24, IDR_STANDARD, L"Standard", 0, NULL);
	m_uiManager->RegisterMenuDlg(23, IDR_HTMLFORMATTING, L"Formatting", 0, NULL);

	// Application Workspace
	{
		m_appWorkspace.m_views.Add(new CView(0, L"Tool Presets"));

		{
			CComObject<CToolPresetsDlg>* p;
			CComObject<CToolPresetsDlg>::CreateInstance(&p);
			if (p)
			{
				p->AddRef();
				//m_pToolOptionsDlg = p;

				p->m_app = this;
				p->m_view = m_appWorkspace.m_views[0];

				//m_uiManager->CreateDlgSheet(NULL, NULL, &m_pToolOptionsDlg->m_sheet);
				//m_pToolOptionsDlg->m_sheet->ShowTabs(FALSE);

				CComPtr<IMenuItem> menu;
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_TOOLPRESETSDLG, &menu);

				CComPtr<IUIDlgSite> site;
				m_uiManager->CreateDlgSite(L"Tool Presets", menu, p, &site);

				CComQIPtr<IUIDockBar>(m_pToolOptionsDlg->m_presetsPopup)->DockControlBar(site, NULL);
				//frame->FloatControlBar(site, CPoint(0,0), CBRS_SIZE_DYNAMIC);
			}
			m_views.Add(p);
		}

		{
			for (int i = 0; i < m_tools.GetSize(); i++)
			{
				if (m_tools[i]->m_toolOptionsDlgSite)
				{
					CComQIPtr<IUIDockBar>(m_pToolOptionsDlg->m_sheet)->DockControlBar(m_tools[i]->m_toolOptionsDlgSite, NULL);
				}
			}
		}
	}
#endif
#endif

	// XML Document Workspace
	{
		{
			UI::CView* view = new UI::CView(0, WSTR("Layout"));
			//m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_XMLLAYOUTVIEW, &view->m_menu);
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(1, WSTR("Source"));
			//m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_XMLSOURCEVIEW, &view->m_menu);
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(2, WSTR("XML Grid"));
			//m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_XMLGRIDVIEW, &view->m_menu);
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(3, WSTR("Frames"));
			//m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_FRAMESDESIGNVIEW, &view->m_menu);
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(4, WSTR("TimeGraph"));
			//m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_TIMEGRAPHVIEW, &view->m_menu);
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(5, WSTR("Scripts"));
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(6, WSTR("Objects"));
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(7, WSTR("CSS Properties"));
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(8, WSTR("Swatches"));
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(9, WSTR("Stylesheets"));
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(10, WSTR("Element Inspector"));
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(11, WSTR("Filters"));
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(12, WSTR("Animate Attributes"));
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(13, WSTR("Symbols"));
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(14, WSTR("Gradient"));
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(15, WSTR("FilterGraph"));
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(16, WSTR("ClipPaths"));
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(17, WSTR("Color"));
	//		m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_COLORDLG, &view->m_menu);
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(18, WSTR("Test Attributes"));
			//m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_COLORDLG, &view->m_menu);
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(19, WSTR("Transitions"));
	//		m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SMILTRANSITIONSDLG, &view->m_menu);
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(20, WSTR("ElementTime"));
			//m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SMILTRANSITIONSDLG, &view->m_menu);
			m_xmlDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CDocumentSheet* pSheet = new UI::CDocumentSheet;
		//	CComObject<CDocumentSheet>::CreateInstance(&pSheet);
		//	pSheet->AddRef();

			pSheet->m_views.Add(m_xmlDocumentWorkspace.m_views[0]);
			m_xmlDocumentWorkspace.m_views[0]->m_ownerSheet = pSheet;

			pSheet->m_views.Add(m_xmlDocumentWorkspace.m_views[1]);
			m_xmlDocumentWorkspace.m_views[1]->m_ownerSheet = pSheet;

			pSheet->m_views.Add(m_xmlDocumentWorkspace.m_views[2]);
			m_xmlDocumentWorkspace.m_views[2]->m_ownerSheet = pSheet;

			pSheet->m_views.Add(m_xmlDocumentWorkspace.m_views[3]);
			m_xmlDocumentWorkspace.m_views[3]->m_ownerSheet = pSheet;

		//	pSheet->m_views.Add(m_xmlDocumentWorkspace.m_views[6]);
		//	m_xmlDocumentWorkspace.m_views[6]->m_ownerSheet = pSheet;

			m_xmlDocumentWorkspace.m_documentsSheets.Add(pSheet);
		}

		{
			UI::CDocumentSheet* pSheet = new UI::CDocumentSheet;
		//	CComObject<CDocumentSheet>::CreateInstance(&pSheet);
		//	pSheet->AddRef();

			pSheet->m_views.Add(m_xmlDocumentWorkspace.m_views[4]);
			m_xmlDocumentWorkspace.m_views[4]->m_ownerSheet = pSheet;

			m_xmlDocumentWorkspace.m_documentsSheets.Add(pSheet);
		}

		// Objects
		{
			UI::CUIFloatingFrame* floatingframe = new UI::CUIFloatingFrame;
		//	createObjectNS(m_appdocument, L"http://www.lerstad.com/2004/lxui", L"floatingframe", IID_ILXUIElement, (void**)&floatingframe);

			UI::CViewDlg* pViewDlg = new UI::CViewDlg;
			pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[6];
			pViewDlg->m_view->m_ownerSheet = pViewDlg;

#if 0
			CComPtr<ILXUIPageElement> page;
			appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", (ILDOMNode**)&page);
#endif

			UI::DockPanel* sheet = new UI::DockPanel;//CLXUIElement;
			//createObjectNS(m_appdocument, L"http://www.lerstad.com/2004/lxui", L"tabbox", IID_ILXUIElement, (void**)&sheet);

			UI::DockPanel* tabsElement = new UI::DockPanel;
		//	createObjectNS(m_appdocument, L"http://www.lerstad.com/2004/lxui", L"tabs", IID_ILXUIElement, (void**)&tabsElement);
			sheet->AddRChild(tabsElement);

			UI::DockPanel* tabpanelsElement = new UI::DockPanel;
			//createObjectNS(m_appdocument, L"http://www.lerstad.com/2004/lxui", L"tabpanels", IID_ILXUIElement, (void**)&tabpanelsElement);
			UI::DockPanel::SetDock(tabpanelsElement, UI::DockPanel::Fill);
			sheet->AddRChild(tabpanelsElement);

#if 0
			page->setContent(sheet);
#endif

			{
#if 0
				CComPtr<ILXUIPageElement> page;
				appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", (ILDOMNode**)&page);
#endif

				pViewDlg->m_sheet = new UI::CLXUITabBoxElement;//	createObjectNS(m_appdocument, L"http://www.lerstad.com/2004/lxui", L"tabbox", IID_ILXUIElement, (void**)&pViewDlg->m_sheet);
			//	pViewDlg->m_sheet->setAttribute(L"style", L"-moz-box-flex: 1;");

				pViewDlg->m_tabsElement = new UI::CLXUITabsElement;//createObjectNS(m_appdocument, L"http://www.lerstad.com/2004/lxui", L"tabs", IID_ILXUIElement, (void**)&pViewDlg->m_tabsElement);
				pViewDlg->m_sheet->m_Panel->AddRChild(pViewDlg->m_tabsElement);

				pViewDlg->m_tabpanelsElement = new UI::DockPanel;//createObjectNS(m_appdocument, L"http://www.lerstad.com/2004/lxui", L"tabpanels", IID_ILXUIElement, (void**)&pViewDlg->m_tabpanelsElement);
				UI::DockPanel::SetDock(pViewDlg->m_tabpanelsElement, UI::DockPanel::Fill);
				pViewDlg->m_sheet->m_Panel->AddRChild(pViewDlg->m_tabpanelsElement);

#if 0
				pViewDlg->m_sheet->setAttribute(L"showTabs", L"false");
				page->put_caption(_variant_t(pViewDlg->m_view->m_name));
				page->setContent(pViewDlg->m_sheet);

				sheet->appendChild(page, NULL);
#endif

				UI::TextString* tabElement = new UI::TextString(pViewDlg->m_view->m_name);
				//createObjectNS(m_appdocument, L"http://www.lerstad.com/2004/lxui", L"tab", IID_ILXUIElement, (void**)&tabElement);
				//tabElement->put_textContent(pViewDlg->m_view->m_name);

				tabsElement->AddRChild(tabElement);

				tabpanelsElement->AddRChild(pViewDlg->m_sheet);
			}

#if 0
			frameelement->floatBar(page, 40, 40);
#endif

			floatingframe->set_Content(sheet);

#if 0	// Had this
			m_pFrame->m_frame->appendChild(floatingframe, NULL);
#endif
		//	ASSERT(0);
#if 0
			m_popups.push_back(floatingframe);
#endif

			m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
		}

#if 0
		// Objects
		{
			CViewDlg* pViewDlg = new CViewDlg;
			pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[6];
			pViewDlg->m_view->m_ownerSheet = pViewDlg;

			CComPtr<IUIDlgSheet> sheet0;
			m_uiManager->CreateDlgSheet(NULL, NULL, &sheet0);
			{
				CComPtr<IMenuItem> menu;
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGOBJECTSDLG, &menu);

				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, menu, &pViewDlg->m_sheet);
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
			}

			CComPtr<IUIDlgSite> dlgsite;
			sheet0->GetDlgSite(&dlgsite);
			frame->FloatControlBar(dlgsite, CPoint(40,40), CBRS_SIZE_DYNAMIC);

			m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
		}
#endif

#if 0
		{
			CComPtr<IUIDlgSheet> sheet0;
			m_uiManager->CreateDlgSheet(NULL, NULL, &sheet0);

			// Scripts
			{
				CViewDlg* pViewDlg = new CViewDlg;
				pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[5];
				pViewDlg->m_view->m_ownerSheet = pViewDlg;

				{
					CComPtr<IMenuItem> menu;
					m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SCRIPTSDLG, &menu);

					m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, menu, &pViewDlg->m_sheet);
					pViewDlg->m_sheet->ShowTabs(FALSE);

					sheet0->AddDialog(pViewDlg->m_sheet);
				}

				m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
			}

			// Stylesheets
			{
				CViewDlg* pViewDlg = new CViewDlg;
				pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[9];
				pViewDlg->m_view->m_ownerSheet = pViewDlg;

				{
					m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, NULL, &pViewDlg->m_sheet);
					pViewDlg->m_sheet->ShowTabs(FALSE);

					sheet0->AddDialog(pViewDlg->m_sheet);
				}

				m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
			}

			CComPtr<IUIDlgSite> dlgsite;
			sheet0->GetDlgSite(&dlgsite);
			frame->FloatControlBar(dlgsite, CPoint(40,40), CBRS_SIZE_DYNAMIC);
		}

		// CSS Properties
		{
			CViewDlg* pViewDlg = new CViewDlg;
			pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[7];
			pViewDlg->m_view->m_ownerSheet = pViewDlg;

			CComPtr<IUIDlgSheet> sheet0;
			m_uiManager->CreateDlgSheet(NULL, NULL, &sheet0);
			{
				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, NULL, &pViewDlg->m_sheet);
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
			}

			CComPtr<IUIDlgSite> dlgsite;
			sheet0->GetDlgSite(&dlgsite);
			frame->FloatControlBar(dlgsite, CPoint(40,40), CBRS_SIZE_DYNAMIC);

			m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
		}

		{
			CComPtr<IUIDlgSheet> sheet0;
			m_uiManager->CreateDlgSheet(NULL, NULL, &sheet0);

		// SVG Swatches
			{
				CViewDlg* pViewDlg = new CViewDlg;
				pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[8];
				pViewDlg->m_view->m_ownerSheet = pViewDlg;

				CComPtr<IMenuItem> menu;
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGSWATCHESDLG, &menu);

				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, menu, &pViewDlg->m_sheet);
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
				m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
			}

		// SVG Filters
			{
				CViewDlg* pViewDlg = new CViewDlg;
				pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[11];
				pViewDlg->m_view->m_ownerSheet = pViewDlg;

				CComPtr<IMenuItem> menu;
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGFILTERSDLG, &menu);

				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, menu, &pViewDlg->m_sheet);
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
				m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
			}

		// SVG Symbols
			{
				CViewDlg* pViewDlg = new CViewDlg;
				pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[13];
				pViewDlg->m_view->m_ownerSheet = pViewDlg;

				CComPtr<IMenuItem> menu;
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGSYMBOLSDLG, &menu);

				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, menu, &pViewDlg->m_sheet);
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
				m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
			}

		// SVG ClipPaths
			{
				CViewDlg* pViewDlg = new CViewDlg;
				pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[16];
				pViewDlg->m_view->m_ownerSheet = pViewDlg;

				CComPtr<IMenuItem> menu;
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGCLIPPATHSDLG, &menu);

				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, menu, &pViewDlg->m_sheet);
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
				m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
			}

		// SMIL Transitions
			{
				CViewDlg* pViewDlg = new CViewDlg;
				pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[19];
				pViewDlg->m_view->m_ownerSheet = pViewDlg;

			//	CComPtr<IMenuItem> menu;
			//	m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGCLIPPATHSDLG, &menu);

				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, pViewDlg->m_view->m_menu, &pViewDlg->m_sheet);
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
				m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
			}

			CComPtr<IUIDlgSite> dlgsite;
			sheet0->GetDlgSite(&dlgsite);
			frame->FloatControlBar(dlgsite, CPoint(40,40), CBRS_SIZE_DYNAMIC);
		}
#endif

		// Element Inspector
		{
#if 0	// Had this
			CViewDlg* pViewDlg = new CViewDlg;
			pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[10];
			pViewDlg->m_view->m_ownerSheet = pViewDlg;

			CComPtr<ILXUIPageElement> page;
			appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", (ILDOMElement**)&page);

			ILXUIElement* sheet;
			appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"sheet", (ILDOMElement**)&sheet);

			page->setContent(sheet);

			{
				CComPtr<ILXUIPageElement> page;
				appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", (ILDOMElement**)&page);

				appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"sheet", (ILDOMElement**)&pViewDlg->m_sheet);
				pViewDlg->m_sheet->setAttribute(L"showTabs", L"false");
				page->put_caption(_variant_t(pViewDlg->m_view->m_name));
				page->setContent(pViewDlg->m_sheet);

				sheet->appendChild(page, NULL);
			}

			frameelement->floatBar(page, 40, 40);

			m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
#endif
		}

		/*
		{
			CViewDlg* pViewDlg = new CViewDlg;
			pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[10];
			pViewDlg->m_view->m_ownerSheet = pViewDlg;

			CComPtr<IUIDlgSheet> sheet0;
			m_uiManager->CreateDlgSheet(NULL, NULL, &sheet0);
			{
				//CComPtr<IMenuItem> menu;
				//m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGSWATCHESDLG, &menu);

				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, NULL, &pViewDlg->m_sheet);
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
			}

			CComPtr<IUIDlgSite> dlgsite;
			sheet0->GetDlgSite(&dlgsite);
			frame->FloatControlBar(dlgsite, CPoint(40,40), CBRS_SIZE_DYNAMIC);

			m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
		}
		*/

	// Scene Document Workspace
	{
		{
			UI::CView* view = new UI::CView(0, WSTR("3DView"));
			//m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_XMLLAYOUTVIEW, &view->m_menu);
			m_sceneDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(1, WSTR("SceneGraph"));
			//m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_XMLLAYOUTVIEW, &view->m_menu);
			m_sceneDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CDocumentSheet* pSheet = new UI::CDocumentSheet;
		//	CComObject<CDocumentSheet>::CreateInstance(&pSheet);
		//	pSheet->AddRef();

			pSheet->m_views.Add(m_sceneDocumentWorkspace.m_views[0]);
			m_sceneDocumentWorkspace.m_views[0]->m_ownerSheet = pSheet;

			/*
			pSheet->m_views.Add(m_xmlDocumentWorkspace.m_views[1]);
			m_xmlDocumentWorkspace.m_views[1]->m_ownerSheet = pSheet;

			pSheet->m_views.Add(m_xmlDocumentWorkspace.m_views[2]);
			m_xmlDocumentWorkspace.m_views[2]->m_ownerSheet = pSheet;

			pSheet->m_views.Add(m_xmlDocumentWorkspace.m_views[3]);
			m_xmlDocumentWorkspace.m_views[3]->m_ownerSheet = pSheet;

		//	pSheet->m_views.Add(m_xmlDocumentWorkspace.m_views[6]);
		//	m_xmlDocumentWorkspace.m_views[6]->m_ownerSheet = pSheet;
		*/

			m_sceneDocumentWorkspace.m_documentsSheets.Add(pSheet);
		}
/*
		{
			CComObject<CDocumentSheet>* pSheet;
			CComObject<CDocumentSheet>::CreateInstance(&pSheet);
			pSheet->AddRef();

			pSheet->m_views.Add(m_xmlDocumentWorkspace.m_views[4]);
			m_xmlDocumentWorkspace.m_views[4]->m_ownerSheet = pSheet;

			m_xmlDocumentWorkspace.m_documentsSheets.Add(pSheet);
		}
*/

		// SceneGraph
		{
#if 0	// Had this
			CViewDlg* pViewDlg = new CViewDlg;
			pViewDlg->m_view = m_sceneDocumentWorkspace.m_views[1];
			pViewDlg->m_view->m_ownerSheet = pViewDlg;

			CComPtr<ILXUIPageElement> page;
			appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", (ILDOMElement**)&page);

			ILXUIElement* sheet;
			appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"sheet", (ILDOMElement**)&sheet);

			page->setContent(sheet);

			{
				CComPtr<ILXUIPageElement> page;
				appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", (ILDOMElement**)&page);

				appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"sheet", (ILDOMElement**)&pViewDlg->m_sheet);
				pViewDlg->m_sheet->setAttribute(L"showTabs", L"false");
				page->put_caption(_variant_t(pViewDlg->m_view->m_name));
				page->setContent(pViewDlg->m_sheet);

				sheet->appendChild(page, NULL);
			}

			frameelement->floatBar(page, 200, 200);

			m_sceneDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
#endif
		}
	}

#if 0
		{
			CComPtr<IUIDlgSheet> sheet0;
			m_uiManager->CreateDlgSheet(NULL, NULL, &sheet0);

		// Gradient
			{
				CViewDlg* pViewDlg = new CViewDlg;
				pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[14];
				pViewDlg->m_view->m_ownerSheet = pViewDlg;

				CComPtr<IMenuItem> menu;
				//m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGSWATCHESDLG, &menu);

				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, menu, &pViewDlg->m_sheet);
				{
					CComPtr<IUIDlgSite> dlgsite;
					pViewDlg->m_sheet->GetDlgSite(&dlgsite);
					dlgsite->Show(FALSE);
				}
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
				m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
			}

		// FilterGraph
			{
				CViewDlg* pViewDlg = new CViewDlg;
				pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[15];
				pViewDlg->m_view->m_ownerSheet = pViewDlg;

				CComPtr<IMenuItem> menu;
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_EDITFILTERDLG, &menu);

				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, menu, &pViewDlg->m_sheet);
				{
					CComPtr<IUIDlgSite> dlgsite;
					pViewDlg->m_sheet->GetDlgSite(&dlgsite);
					dlgsite->Show(FALSE);
				}
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
				m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
			}

		// Color
			{
				CViewDlg* pViewDlg = new CViewDlg;
				pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[17];
				pViewDlg->m_view->m_ownerSheet = pViewDlg;

				CComPtr<IMenuItem> menu;
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_COLORDLG, &menu);

				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, menu, &pViewDlg->m_sheet);
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
				m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
			}

			CComPtr<IUIDlgSite> dlgsite;
			sheet0->GetDlgSite(&dlgsite);
			frame->FloatControlBar(dlgsite, CPoint(40,40), CBRS_SIZE_DYNAMIC);
		}

		// Animate attributes
		{
			CViewDlg* pViewDlg = new CViewDlg;
			pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[12];
			pViewDlg->m_view->m_ownerSheet = pViewDlg;

			CComPtr<IUIDlgSheet> sheet0;
			m_uiManager->CreateDlgSheet(NULL, NULL, &sheet0);
			{
				//CComPtr<IMenuItem> menu;
				//m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGSWATCHESDLG, &menu);

				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, NULL, &pViewDlg->m_sheet);
				{
					CComPtr<IUIDlgSite> dlgsite;
					pViewDlg->m_sheet->GetDlgSite(&dlgsite);
					dlgsite->Show(FALSE);
				}
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
			}

			CComPtr<IUIDlgSite> dlgsite;
			sheet0->GetDlgSite(&dlgsite);
			frame->FloatControlBar(dlgsite, CPoint(40,40), CBRS_SIZE_DYNAMIC);

			m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
		}

		{
			CComPtr<IUIDlgSheet> sheet0;
			m_uiManager->CreateDlgSheet(NULL, NULL, &sheet0);

		// Test Attributes (for children of <switch>)
			{
				CViewDlg* pViewDlg = new CViewDlg;
				pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[18];
				pViewDlg->m_view->m_ownerSheet = pViewDlg;

				{
					m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, NULL, &pViewDlg->m_sheet);
					pViewDlg->m_sheet->ShowTabs(FALSE);

					sheet0->AddDialog(pViewDlg->m_sheet);
					m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
				}
			}

		// ElementTime Attributes
			{
				CViewDlg* pViewDlg = new CViewDlg;
				pViewDlg->m_view = m_xmlDocumentWorkspace.m_views[20];
				pViewDlg->m_view->m_ownerSheet = pViewDlg;

				{
					m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, NULL, &pViewDlg->m_sheet);
					pViewDlg->m_sheet->ShowTabs(FALSE);

					sheet0->AddDialog(pViewDlg->m_sheet);
					m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
				}
			}

			CComPtr<IUIDlgSite> dlgsite;
			sheet0->GetDlgSite(&dlgsite);
			frame->FloatControlBar(dlgsite, CPoint(40,40), CBRS_SIZE_DYNAMIC);

			//m_xmlDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
		}
	}

	{
		m_layoutViewWorkspace.m_views.Add(new CView(0, L"Navigator"));
		{
			CViewDlg* pViewDlg = new CViewDlg;
			pViewDlg->m_view = m_layoutViewWorkspace.m_views[0];
			pViewDlg->m_view->m_ownerSheet = pViewDlg;

			CComPtr<IUIDlgSheet> sheet0;
			m_uiManager->CreateDlgSheet(NULL, NULL, &sheet0);
			{
				CComPtr<IMenuItem> menu;
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_NAVIGATORDLG, &menu);

				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, menu, &pViewDlg->m_sheet);
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
			}

			CComPtr<IUIDlgSite> dlgsite;
			sheet0->GetDlgSite(&dlgsite);
			frame->FloatControlBar(dlgsite, CPoint(40,40), CBRS_SIZE_DYNAMIC);

			m_layoutViewWorkspace.m_viewDialogs.Add(pViewDlg);
		}
#endif
	}

	// CSS Document Workspace
	{
		{
			UI::CView* view = new UI::CView(0, WSTR("CSS Definitions"));
	//		m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_CSSSTYLESHEETVIEW, &view->m_menu);
			m_cssDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(1, WSTR("Source"));
	//		m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_CSSSOURCEVIEW, &view->m_menu);
			m_cssDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(2, WSTR("CSS Properties"));
			m_cssDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CView* view = new UI::CView(3, WSTR("Rule"));
			m_cssDocumentWorkspace.m_views.Add(view);
		}

		{
			UI::CDocumentSheet* pSheet = new UI::CDocumentSheet;
		//	CComObject<CDocumentSheet>::CreateInstance(&pSheet);
		//	pSheet->AddRef();

			pSheet->m_views.Add(m_cssDocumentWorkspace.m_views[0]);
			m_cssDocumentWorkspace.m_views[0]->m_ownerSheet = pSheet;

			pSheet->m_views.Add(m_cssDocumentWorkspace.m_views[1]);
			m_cssDocumentWorkspace.m_views[1]->m_ownerSheet = pSheet;

			m_cssDocumentWorkspace.m_documentsSheets.Add(pSheet);
		}

#if 0
		{
			CViewDlg* pViewDlg = new CViewDlg;
			pViewDlg->m_view = m_cssDocumentWorkspace.m_views[2];
			pViewDlg->m_view->m_ownerSheet = pViewDlg;

		// Same sheet as xml document workspace
			pViewDlg->m_sheet = m_xmlDocumentWorkspace.m_viewDialogs[3]->m_sheet;

			m_cssDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
		}

		{
			CViewDlg* pViewDlg = new CViewDlg;
			pViewDlg->m_view = m_cssDocumentWorkspace.m_views[3];
			pViewDlg->m_view->m_ownerSheet = pViewDlg;

			CComPtr<IUIDlgSheet> sheet0;
			m_uiManager->CreateDlgSheet(NULL, NULL, &sheet0);
			{
				m_uiManager->CreateDlgSheet(pViewDlg->m_view->m_name, NULL, &pViewDlg->m_sheet);
				pViewDlg->m_sheet->ShowTabs(FALSE);

				sheet0->AddDialog(pViewDlg->m_sheet);
			}

			CComPtr<IUIDlgSite> dlgsite;
			sheet0->GetDlgSite(&dlgsite);
			frame->FloatControlBar(dlgsite, CPoint(40,40), CBRS_SIZE_DYNAMIC);

			m_cssDocumentWorkspace.m_viewDialogs.Add(pViewDlg);
		}
#endif
	}

	m_Canvas = new UI::ChildWindowContainer;

	set_Width(new UI::Length(600));
	set_Height(new UI::Length(400));

	set_TitleText(WSTR("LXMLEditor"));
	set_Content(m_Canvas);
}

CLXMLEditorApp::~CLXMLEditorApp()
{
//		ASSERT(m_frame == NULL);
//		ASSERT(m_xsltDocuments == NULL);

//		ASSERT(m_documents.GetSize() == 0);
}

#if 0
int CLXMLEditorApp::FinalConstruct()
{
	ErrorCode hr;
/*
	hr = CComObject<CXSLTDocuments>::CreateInstance(&m_xsltDocuments);
	if (FAILED(hr)) return hr;
	m_xsltDocuments->AddRef();
*/

	/*
	{
		CComObject<CImageApp>* pApp;
		CComObject<CImageApp>::CreateInstance(&pApp);
		pApp->AddRef();

		g_pImageApp = pApp;
	}
	*/

#if 0
	CComObject<CLElementBehaviorFactory>::CreateInstance(&m_pElementBehaviorFactory);
	m_pElementBehaviorFactory->AddRef();
	m_pElementBehaviorFactory->m_pApp = this;
#endif

	{
		CFormatWindow* pWindow;

		{
			pWindow = new CFormatWindow;

			HDC hDC = GetDC(NULL);

			memset(&pWindow->m_lf, 0, sizeof(pWindow->m_lf));
			strcpy(pWindow->m_lf.lfFaceName, _T("Courier New"));
			pWindow->m_lf.lfHeight = -MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72);

			ReleaseDC(NULL, hDC);

			pWindow->m_name = L"Source Windows";
			pWindow->RegisterFormatColor(L"Text Selection", -1, -1, COLOR_HIGHLIGHTTEXT, COLOR_HIGHLIGHT);
			pWindow->RegisterFormatColor(L"Text", -1, -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Preprocessing Instruction", RGB(0, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Element Name", RGB(128, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Attribute Name", RGB(192, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Attribute Value", RGB(0, 0, 255), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Tag Delimiter", RGB(128, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Operator", RGB(192, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Comment", RGB(160, 160, 160), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Invalid", RGB(0, 0, 0), RGB(255, 128, 0), COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"CSS Comment", RGB(160, 160, 160), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"CSS Rule", RGB(128, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"CSS Property Name", RGB(192, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"CSS Property Value", RGB(0, 0, 255), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"CSS Comment", RGB(160, 160, 160), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script Keyword", RGB(0, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script String", RGB(192, 0, 0), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script Comment", RGB(0, 192, 0), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);

			m_formatWindows.Add(pWindow);
		}

		{
			pWindow = new CFormatWindow;
			pWindow->m_name = L"XML Grid";

			//HDC hDC = GetDC(NULL);

			HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
			GetObject(hFont, sizeof(pWindow->m_lf), &pWindow->m_lf);
			//memset(&pWindow->m_lf, 0, sizeof(pWindow->m_lf));
			//strcpy(pWindow->m_lf.lfFaceName, _T("Courier New"));
			//pWindow->m_lf.lfHeight = -MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72);

			//ReleaseDC(NULL, hDC);

			/*
			pWindow->RegisterFormatColor(L"Text Selection", -1, -1, COLOR_HIGHLIGHTTEXT, COLOR_HIGHLIGHT);
			pWindow->RegisterFormatColor(L"Text", -1, -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Element Name", RGB(128, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Attribute Name", RGB(192, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Attribute Value", RGB(0, 0, 255), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Tag Delimiter", RGB(128, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Operator", RGB(192, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Comment", RGB(160, 160, 160), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script Keyword", RGB(0, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script String", RGB(192, 0, 0), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script Comment", RGB(0, 192, 0), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			*/

			m_formatWindows.Add(pWindow);
		}

		{
			pWindow = new CFormatWindow;

			HDC hDC = GetDC(NULL);

			memset(&pWindow->m_lf, 0, sizeof(pWindow->m_lf));
			strcpy(pWindow->m_lf.lfFaceName, _T("Courier New"));
			pWindow->m_lf.lfHeight = -MulDiv(8, GetDeviceCaps(hDC, LOGPIXELSY), 72);

			ReleaseDC(NULL, hDC);

			pWindow->m_name = L"TimeGraph";
			pWindow->RegisterFormatColor(L"Text Selection", -1, -1, COLOR_HIGHLIGHTTEXT, COLOR_HIGHLIGHT);
			pWindow->RegisterFormatColor(L"Text", -1, -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Element Name", RGB(128, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Attribute Name", RGB(192, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Attribute Value", RGB(0, 0, 255), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Tag Delimiter", RGB(128, 0, 128), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Operator", RGB(192, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"XML Comment", RGB(160, 160, 160), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			//pWindow->RegisterFormatColor(L"CSS Comment", RGB(160, 160, 160), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script Keyword", RGB(0, 0, 192), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script String", RGB(192, 0, 0), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);
			pWindow->RegisterFormatColor(L"Script Comment", RGB(0, 192, 0), -1, COLOR_WINDOWTEXT, COLOR_WINDOW);

			m_formatWindows.Add(pWindow);
		}
	}

	return S_OK;
}

void CLXMLEditorApp::FinalRelease()
{
#if 0
	if (m_pElementBehaviorFactory)
	{
		m_pElementBehaviorFactory->Release();
		m_pElementBehaviorFactory = NULL;
	}
#endif
}
#endif

/*
void CLXMLEditorApp::RemoveDocument(CEXMLDocument* pDocument)
{

}
*/

#if 0	// TODO, had this
ErrorCode CLXMLEditorApp::CreateNewDocument(BSTR pathName, IEDocument **pVal)
{
	if (pVal == NULL) return E_POINTER;

	TCHAR ext[512];
	_splitpath(_bstr_t(pathName), NULL, NULL, NULL, ext);

	IEDocument* document;
	
	if (
		!stricmp(ext, ".htm") ||
		!stricmp(ext, ".html") ||
		!stricmp(ext, ".shtml") ||
		!stricmp(ext, ".asp") ||

		!stricmp(ext, ".svg") ||

		!stricmp(ext, ".smil") ||
		!stricmp(ext, ".smi") ||

		!stricmp(ext, ".xml") ||
		!stricmp(ext, ".xsd")/* ||

		!stricmp(ext, ".wmf") ||
		!stricmp(ext, ".emf")*/)
	{
	//	document.CoCreateInstance(CLSID_EXMLDocument);
	}
	else if (!stricmp(ext, ".dtd"))
	{
	//	document.CoCreateInstance(CLSID_EDTDDocument);
	}
	else if (
		!stricmp(ext, ".js") ||
		!stricmp(ext, ".vbs"))
	{
	//	document.CoCreateInstance(CLSID_EScriptDocument);
	}
/*
	else if (!stricmp(ext, ".css"))
	{
	//	pDocument = new CCSSDocument;
	}
*/
	else
	{
	//	document.CoCreateInstance(CLSID_ETextDocument);
	}

	if (document != NULL)
	{
#if 0
		document->NewDocument();
		document->ShowViews();
		m_frame->ActivateObject(NULL, document);
#endif
	}

	*pVal = document;
	(*pVal)->AddRef();

	return S_OK;
}
#endif

#if 0
ErrorCode CLXMLEditorApp::SetSite(ILXAddinSite* pSite)
{
	m_spAddinSite = pSite;

	m_appdocument.CoCreateInstance(CLSID_LXUIDocument);//CComPtr<ILXUIDocument> appdocument;
	//m_spAddinSite->GetUIDocument(&appdocument);

#if 0
	CComPtr<ILDOMElement> root;
	m_appdocument->get_documentElement(&root);
#endif

	CComObject<CLXMLEditorFrame>::CreateInstance(&m_pFrame);
	m_pFrame->AddRef();

	{
		//CComPtr<ILXUIMDIFrameElement> mdiframe;
		createObjectNS(m_appdocument, L"http://www.lerstad.com/2004/lxui", L"mdiframe", IID_ILXUIMDIFrameElement, (void**)&m_pFrame->m_frame);

		CComQIPtr<ILDOMEventTarget>(m_pFrame->m_frame)->addEventListener(L"command", static_cast<ILDOMEventListener*>(this), VARIANT_FALSE);
		{
			ILXUIElement* titlebar;
			createObjectNS(m_appdocument, L"http://www.lerstad.com/2004/lxui", L"titlebar", IID_ILXUIElement, (void**)&titlebar);
			titlebar->put_textContent(L"LXMLEditor");

			m_pFrame->m_frame->appendChild(titlebar, NULL);
		}

		{
#if 0
			CComPtr<ILXUIDocument> doc;
			doc.CoCreateInstance(CLSID_LXUIDocument);

			CComPtr<ILDOMNode> documentElement;
		//	VARIANT_BOOL success;
			doc->loadXAML(_variant_t(L"C:\\lxmleditor_menubar.xml"), &documentElement);

			//doc->get_documentElement(&documentElement);

			CComPtr<ILDOMNode> menubar;
			doc->removeChild(documentElement, &menubar);

			m_appdocument->adoptNode(documentElement, NULL/*&menubar*/);

			m_pFrame->m_frame->appendChild(menubar, NULL);
#endif
			ILXUIElement* menubar;
			m_appdocument->loadXAML(_variant_t(L"C:\\lxmleditor_menubar.xml"), &menubar);
			m_pFrame->m_frame->appendChild(menubar, NULL);
		}

		/*
		{
			ILXUIElement* mdiclient;
			m_appdocument->createObjectNS(L"http://www.lerstad.com/2004/lxui", L"mdiclient", &mdiclient);

			m_pFrame->m_frame->appendChild(mdiclient, NULL);
		}
		*/

		m_pFrame->m_frame->Show();
#if 0
		root->appendChild(m_pFrame->m_frame, NULL);
#endif
	}

	OnCreateFrame();

	BOOL bHandled;
	OnFileOpen(0, 0, NULL, bHandled);

	//ASSERT(0);
#if 0

	if (m_spAddinSite)
	{
		m_spAddinSite->GetFrame(&m_frame);

		CComPtr<IUnknown> uiManager;
		m_spAddinSite->GetUIManager(&uiManager);
		//m_uiManager = CComQIPtr<IUIManager>(uiManager);

		SetUIManager(CComQIPtr<IUIManager>(uiManager));
		OnCreateFrame();
	}
#endif

#if 0
	{
		CComPtr<ILDOMElement> vbox;
		appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"div", (ILDOMElement**)&vbox);

		CComPtr<ILDOMElement> tabbox;
		appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"tabbox", (ILDOMElement**)&tabbox);

		CComPtr<ILDOMElement> tabs;
		appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"tabs", (ILDOMElement**)&tabs);
		tabbox->appendChild(tabs, NULL);

		CComPtr<ILDOMElement> tabpanels;
		appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"tabpanels", (ILDOMElement**)&tabpanels);
		tabbox->appendChild(tabpanels, NULL);

		CComPtr<ILDOMElement> tab;
		appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"tab", (ILDOMElement**)&tab);
		tab->put_textContent(L"Build");
		tabs->appendChild(tab, NULL);

		CComPtr<ILDOMElement> p;
		appdocument->createElementNS(L"http://www.w3.org/1999/xhtml", L"div", (ILDOMElement**)&p);
		{
			STARTUPINFO si;
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			si.dwFlags = STARTF_USESTDHANDLES;

			SECURITY_ATTRIBUTES sa;
			// Set up the security attributes struct.
			sa.nLength = sizeof(SECURITY_ATTRIBUTES);
			sa.lpSecurityDescriptor = NULL;
			sa.bInheritHandle = TRUE;

			HANDLE hOutputRead;
			HANDLE hOutputWrite;
			CreatePipe(&hOutputRead, &hOutputWrite, &sa, 0);

			si.hStdOutput = hOutputWrite;
			si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
			si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

			PROCESS_INFORMATION pi;
			ZeroMemory( &pi, sizeof(pi) );

			// Start the child process. 
			if( !CreateProcess("C:\\WINNT\\Microsoft.NET\\Framework\\v1.1.4322\\csc.exe",
				"/debug+ /out:C:\\HelloCS.exe \"C:\\Program Files\\Microsoft.NET\\SDK\\v1.1\\Samples\\Tutorials\\PlatformIntroduction\\HelloWorld\\CS\\helloCS.cs\"", // Command line. 
				NULL,             // Process handle not inheritable. 
				NULL,             // Thread handle not inheritable. 
				TRUE,            // Set handle inheritance to TRUE. 
				CREATE_NEW_CONSOLE,                // No creation flags. 
				NULL,             // Use parent's environment block. 
				NULL,             // Use parent's starting directory. 
				&si,              // Pointer to STARTUPINFO structure.
				&pi )             // Pointer to PROCESS_INFORMATION structure.
				) 
			{
				MessageBox(NULL, "CreateProcess failed.", "", MB_OK);
			}

	// Close pipe handles (do not continue to modify the parent).
			// You need to make sure that no handles to the write end of the
			// output pipe are maintained in this process or else the pipe will
			// not close when the child process exits and the ReadFile will hang.
			if (!CloseHandle(hOutputWrite)) MessageBox(NULL, "CloseHandle", "", MB_OK);
	//      if (!CloseHandle(hInputRead )) MessageBox(NULL, "CloseHandle", "", MB_OK);
	//      if (!CloseHandle(hErrorWrite)) MessageBox(NULL, "CloseHandle", "", MB_OK);


			// Wait until child process exits.
			WaitForSingleObject(pi.hProcess, INFINITE);

			CString str;

			while (TRUE)
			{
				char buf[60];
				ULONG nRead;
				if (!ReadFile(hOutputRead, buf, 60, &nRead, NULL) || nRead == 0)
				{
					if (GetLastError() == ERROR_BROKEN_PIPE)
						break; // pipe done - normal exit path.
					else
						MessageBox(NULL, "ReadFile", "", MB_OK); // Something bad happened.
				}

				str += CString(buf, nRead);
			}
			
			// Close process and thread handles. 
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);

			p->put_textContent(_bstr_t(str));

			tabpanels->appendChild(p, NULL);
		}

		vbox->appendChild(tabbox, NULL);

		m_pFrame->m_frame->appendChild(vbox, NULL);
	}
#endif

	return S_OK;
}
#endif

#if 0
ErrorCode CLXMLEditorApp::CreateDlg(UINT nID, IUIDlg* *pVal)
{
	ASSERT(0);
#if 0
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;

	switch (nID)
	{
	case 70:
		{
			CComPtr<IUIMenuDlg> menuDlg;
			m_uiManager->CreateMenuDlg(&menuDlg);

			CComPtr<IMenuItem> menuItem;
			m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_MAINFRAME, &menuItem);

			CComPtr<IMenuItem> menuItem0 = menuItem;
			//menuItem->GetSubMenu(0, &menuItem0);

			menuDlg->InitMenu(menuItem0, this/*CComQIPtr<ICommandTarget>(GetFrame())*/, -1);

			(*pVal = menuDlg)->AddRef();
		}
		break;

	case 71:
		{
			CComPtr<IUIMenuDlg> menuDlg;
			m_uiManager->CreateMenuDlg(&menuDlg);

			CComPtr<IMenuItem> menuItem;
			m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_STANDARD, &menuItem);

			CComPtr<IMenuItem> menuItem0;
			menuItem->GetSubMenu(0, &menuItem0);

			menuDlg->InitMenu(menuItem0, this/*CComQIPtr<ICommandTarget>(GetFrame())*/, -1);

			(*pVal = menuDlg)->AddRef();
		}
		break;

	case 1:
		{
			CComObject<CInspectorDlg>* p;
			CComObject<CInspectorDlg>::CreateInstance(&p);
			(*pVal = p)->AddRef();
			p->m_app = this;
		}
		break;

	case 50:
		/*
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
	case 58:
	case 59:
	*/
		{
			CComObject<CCSSPropertiesDlg>* p;
			CComObject<CCSSPropertiesDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
			//	p->m_category = nID-50;
				p->m_app = this;
			}
		}
		break;

	case 3:
		{
			CComObject<CEColorDlg>* p;
			CComObject<CEColorDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_COLORDLG, &p->m_menu);
				p->m_app = this;
			}
		}
		break;

	case 4:
		{
			CComObject<CSVGToolsDlg>* p;
			CComObject<CSVGToolsDlg>::CreateInstance(&p);
			if (p)
			{
				p->m_app = this;
				(*pVal = p)->AddRef();
			}
		}
		break;

	case 5:
		{
			CComObject<CWENavigatorDlg>* p;
			CComObject<CWENavigatorDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_NAVIGATORDLG, &p->m_menu);
				p->m_app = this;
			}
		}
		break;

	case 6:
		{
			CComObject<CSVGSwatchesDlg>* p;
			CComObject<CSVGSwatchesDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGSWATCHESDLG, &p->m_menu);
				p->m_app = this;
			}
		}
		break;

	case 7:
		{
			CComObject<CSVGFiltersDlg>* p;
			CComObject<CSVGFiltersDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGFILTERSDLG, &p->m_menu);
				p->m_app = this;
			}
		}
		break;

	case 8:
		{
			CComObject<CSVGSymbolsDlg>* p;
			CComObject<CSVGSymbolsDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGSYMBOLSDLG, &p->m_menu);
				p->m_app = this;
			}
		}
		break;

	case 9:
		{
			CComObject<CSVGMasksDlg>* p;
			CComObject<CSVGMasksDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGMASKSDLG, &p->m_menu);
				p->m_app = this;
			}
		}
		break;

	case 10:
		{
			CComObject<CSVGClipPathsDlg>* p;
			CComObject<CSVGClipPathsDlg>::CreateInstance(&p);
			(*pVal = p)->AddRef();
			p->m_app = this;
		}
		break;

	case 11:
		{
			CComObject<CSMILTransitionsDlg>* p;
			CComObject<CSMILTransitionsDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SMILTRANSITIONSDLG, &p->m_menu);
				p->m_app = this;
			}
		}
		break;

	case 12:
		{
			CComObject<CEditFilterDlg>* p;
			CComObject<CEditFilterDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_EDITFILTERDLG, &p->m_menu);
				p->m_app = this;
			}
		}
		break;

	case 13:
		{
			CComObject<CEditGradientDlg>* p;
			CComObject<CEditGradientDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				p->m_app = this;
			}
		}
		break;

	case 14:
		{
			CComObject<CSVGObjectsDlg>* p;
			CComObject<CSVGObjectsDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGOBJECTSDLG, &p->m_menu);
				p->m_app = this;
			}
		}
		break;

	case 15:
		{
			CComObject<CScriptOutlineDlg>* p;
			CComObject<CScriptOutlineDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SCRIPTSDLG, &p->m_menu);
				p->m_app = this;
			}
		}
		break;

	case 16:
		{
			CComObject<CElementAttrsDlg>* p;
			CComObject<CElementAttrsDlg>::CreateInstance(&p);
			(*pVal = p)->AddRef();
			p->m_app = this;
		}
		break;

	case 17:
		{
			CComObject<CElementsDlg>* p;
			CComObject<CElementsDlg>::CreateInstance(&p);
			(*pVal = p)->AddRef();
		}
		break;

	case 18:
		{
			CComObject<CEntitiesDlg>* p;
			CComObject<CEntitiesDlg>::CreateInstance(&p);
			(*pVal = p)->AddRef();
		}
		break;

	case 19:
		{
			CComObject<CAnimationInspectorDlg>* p;
			CComObject<CAnimationInspectorDlg>::CreateInstance(&p);
			(*pVal = p)->AddRef();
			p->m_app = this;
		}
		break;

	case 20:
		{
			CComObject<CASObjectInspectorDlg>* p;
			CComObject<CASObjectInspectorDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				p->m_app = this;
			}
		}
		break;

	case 21:
		{
			CComObject<CAnimateAttributesDlg>* p;
			CComObject<CAnimateAttributesDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				p->m_app = this;
			}
		}
		break;

	case 22:
		{
			CComObject<CEXMLDocumentStyleSheetsView>* p;
			CComObject<CEXMLDocumentStyleSheetsView>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_XMLSTYLESHEETSVIEW, &p->m_menu);
				p->m_app = this;
			}
		}
		break;

	case 25:
		{
			CComObject<CSVGSwatchLibraryDlg>* p;
			CComObject<CSVGSwatchLibraryDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_SVGSWATCHLIBRARYDLG, &p->m_menu);
				p->m_app = this;
			}
		}
		break;

	case 26:
		{
			CComObject<CEXMLLayoutView>* p;
			CComObject<CEXMLLayoutView>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
				m_uiManager->FindMenu(_Module.GetResourceInstance(), IDR_XMLLAYOUTVIEW, &p->m_menu);
			}
		}
		break;
	}
#endif

	return S_OK;
}
#endif

// CViewGroup
int CLXMLEditorApp::OnGroupActivate(bool bActivate)
{
	if (bActivate)
	{
		CViewGroup::Activate(bActivate);
	}
	else
	{
		CViewGroup::Activate(bActivate);
	}

	return 0;
}

int CLXMLEditorApp::OnGroupClose()
{
	return 0;
}

//

#if 0
ErrorCode CLXMLEditorApp::BindToObjectMoniker(IMoniker* moniker, IBindCtx* bindctx, IUnknown* *pVal)
{
	ASSERT(0);
	ErrorCode hr;
#if 0

	//CComQIPtr<IEFrame> eframe = m_frame;

	CComPtr<IUnknown> spUnknown;

	LPOLESTR displayName;
	moniker->GetDisplayName(bindctx, NULL, &displayName);
	_bstr_t url = displayName;
	CoTaskMemFree(displayName);

	TCHAR* ext = PathFindExtension(url);

	if (!stricmp(ext, ".dtd") ||
		!stricmp(ext, ".mod") ||
		!stricmp(ext, ".ent"))
	{
		//hr = spUnknown.CoCreateInstance(CLSID_EDTDDocument);
	//	hr = spUnknown.CoCreateInstance(CLSID_EXMLDocument);
		if (SUCCEEDED(hr))
		{
			CComQIPtr<IPersistMoniker> persistMoniker = spUnknown;
			hr = persistMoniker->Load(TRUE, moniker, bindctx, 0);
		}
	}
	else if (!stricmp(ext, ".wrl") ||
				!stricmp(ext, ".x3d"))
	{
	//	hr = spUnknown.CoCreateInstance(CLSID_ESceneDocument);
		if (SUCCEEDED(hr))
		{
			CComQIPtr<IPersistMoniker> persistMoniker = spUnknown;
			hr = persistMoniker->Load(TRUE, moniker, bindctx, 0);
		}
	}
	else if (!stricmp(ext, ".js"))
	{
	//	hr = spUnknown.CoCreateInstance(CLSID_EScriptDocument);
		if (SUCCEEDED(hr))
		{
			CComQIPtr<IPersistMoniker> persistMoniker = spUnknown;
			hr = persistMoniker->Load(TRUE, moniker, bindctx, 0);
		}
	}
	else
	{
#ifdef _DEBUG
		PWSTR mime;
		::FindMimeFromData(bindctx, url, NULL, 0, NULL, 0, &mime, 0);
#endif

		PSTR rgszTypes[6] =
		{
			"text/html",	// CFSTR_MIME_HTML
			"text/xml",
			"image/svg+xml",
			"application/smil",
			"text/css",
			"text/plain",
		};

		CLSID rgclsID[6];
#if 0
		rgclsID[0] = CLSID_EXMLDocument;
		rgclsID[1] = CLSID_EXMLDocument;
		rgclsID[2] = CLSID_EXMLDocument;
		rgclsID[3] = CLSID_EXMLDocument;
		rgclsID[4] = CLSID_ECSSDocument;
	// TODO javascript
		rgclsID[5] = CLSID_ETextDocument;
#endif

		hr = RegisterMediaTypeClass(bindctx, 6, rgszTypes, rgclsID, 0);
		ASSERT(SUCCEEDED(hr));

		hr = moniker->BindToObject(bindctx, NULL, IID_IUnknown, (void**)&spUnknown);
	}

	if (spUnknown)
	{
		// TODO, don't do this here
		IEDocument* edocument = spUnknown;
		if (edocument)
		{
			m_xmlDocuments.Add(dynamic_cast<CEXMLDocument*>(edocument));

		//	edocument->SetApp(this);
			ASSERT(0);
#if 0
			edocument->ShowViews(m_pFrame);
#endif
		}

		*pVal = edocument;
		(*pVal)->AddRef();

		edocument.Detach();	// TODO, add to a document list
	}
#endif
	return hr;
}
#endif

ErrorCode CLXMLEditorApp::OpenDocument(System::StringW* pathName, /*[out,retval]*/ System::Object* *pVal)
{
	return 0;
}
#if 0

ErrorCode CLXMLEditorApp::OpenDocument(BSTR pathName, IUnknown* *pVal)
{
	ErrorCode hr;

	CComPtr<IBindCtx> bindctx;
//	hr = CreateAsyncBindCtx(NULL, this, NULL, &bindctx);
	hr = CreateBindCtx(0, &bindctx);
	if (SUCCEEDED(hr))
	{
		CComPtr<IMoniker> moniker;

		hr = CreateURLMoniker(NULL, pathName, &moniker);
		if (SUCCEEDED(hr))
		{
			/*
			CComPtr<IStream> stream;
			if (SUCCEEDED(moniker->BindToStorage(bindctx, NULL, IID_IStream, (void**)&stream)))
			{
				MessageBox(NULL, "success", "", MB_OK);
			}
			else
				MessageBox(NULL, "failed", "", MB_OK);
				*/
				

			CComPtr<IUnknown> document;
			return BindToObjectMoniker(moniker, bindctx, &document);
		}
	}

	return hr;

#if 0
	hr = HlinkCreateBrowseContext(NULL, IID_IHlinkBrowseContext, (void**)&m_frame->m_hlinkBrowseContext);

	CComPtr<IMoniker> moniker;
	hr = CreateURLMoniker(NULL, pathName, &moniker);
	if (SUCCEEDED(hr))
	{
		CComPtr<IBindCtx> bindctx;
		hr = CreateBindCtx(0, &bindctx);
		if (SUCCEEDED(hr))
		{
			CComPtr<IHlink> hlink;

			hr = HlinkCreateFromMoniker(
				moniker,
				NULL, // pwzLocation
				L"test",	// friendlyName
				NULL,//&hlsite,
				0,	// siteData
				NULL,
				IID_IHlink,
				(void**)&hlink);

			::HlinkNavigate(hlink, m_frame, 0, bindctx, NULL, m_frame->m_hlinkBrowseContext);
		}
	}

	CComQIPtr<IActiveCntDocument> document;

	for (int i = 0; i < m_documents.GetSize(); i++)
	{
		CComBSTR pathName2;
		m_documents[i]->get_filePath(&pathName2);
		if (pathName2.Length())
		{
			if (!wcsicmp(pathName, pathName2))
			{
				document = m_documents[i];
				break;
			}	
		}
	}

	if (document)
	{
		document->Activate();
	}
	else
	{
		TCHAR ext[512];
		_splitpath(_bstr_t(pathName), NULL, NULL, NULL, ext);

		if (
			!strnicmp(_bstr_t(pathName), "http", 4) ||
			!stricmp(ext, ".htm") ||
			!stricmp(ext, ".html") ||
			!stricmp(ext, ".xpq") ||
			!stricmp(ext, ".shtml") ||
			!stricmp(ext, ".asp") ||

			!stricmp(ext, ".svg") ||

			!stricmp(ext, ".smil") ||
			!stricmp(ext, ".smi") ||

			!stricmp(ext, ".xslt") ||
			!stricmp(ext, ".xml") ||
			!stricmp(ext, ".xsd")/* ||

			!stricmp(ext, ".wmf") ||
			!stricmp(ext, ".emf")*/)
		{
//			document.CoCreateInstance(CLSID_EXMLDocument);
		}
		else if (!stricmp(ext, ".dtd"))
		{
			document.CoCreateInstance(CLSID_DTDDocument);
		}
		else if (
			!stricmp(ext, ".js") ||
			!stricmp(ext, ".vbs"))
		{
			document.CoCreateInstance(CLSID_ExtScriptDocument);
		}
	/*
		else if (!stricmp(ext, ".css"))
		{
		//	pDocument = new CCSSDocument;
		}
	*/
		else
		{
			if ((StgIsStorageFile(_bstr_t(pathName)) == S_OK) ||
				!stricmp(ext, ".pddoc"))
			{
				document.CoCreateInstance(CLSID_ActiveCntDocument);
			}
			else
			{
				document.CoCreateInstance(CLSID_TextDocument);
			}
		}

		if (document != NULL)
		{
		//	m_frame->ActivateObject(NULL, document);

			CComQIPtr<IPersistFile> ifile = document;
			if (ifile != NULL)
			{
				ErrorCode hr = ifile->Load(pathName, STGM_READ);
				if (SUCCEEDED(hr))
				{
					m_documents.Add(document);
					document->Show();
					document.Detach();

				//	m_frame->ActivateObject(NULL, document);
				}
				else
				{
					MessageBox(GetMainHwnd(), "Error loading file", "WebEditor", MB_OK);
				}
			}
			else
			{
				MessageBox(GetMainHwnd(), "Document didn't support loading from file", "WebEditor", MB_OK);
			}
		}
		else
		{
			MessageBox(GetMainHwnd(), "Couldn't create document object", "WebEditor", MB_OK);
		}
	}
#endif

	return S_OK;
}
#endif

#if 0
ErrorCode CLXMLEditorApp::OpenDocument(IUnknown* filesystem, BSTR pathName, VARIANT_BOOL *success)
{
	CComQIPtr<IWebDocument> document;

	for (int i = 0; i < m_documents.GetSize(); i++)
	{
		BSTR pathName2;
		m_documents[i]->get_filePath(&pathName2);
		if (!wcsicmp(pathName, pathName2))
		{
			document = m_documents[i];
			break;
		}
	}

	if (document)
	{
		document->Activate();
	}
	else
	{
		TCHAR ext[512];
		_splitpath(_bstr_t(pathName), NULL, NULL, NULL, ext);

		if (
			!stricmp(ext, ".htm") ||
			!stricmp(ext, ".html") ||
			!stricmp(ext, ".shtml") ||
			!stricmp(ext, ".asp") ||

			!stricmp(ext, ".svg") ||

			!stricmp(ext, ".smil") ||
			!stricmp(ext, ".smi") ||

			!stricmp(ext, ".xslt") ||
			!stricmp(ext, ".xml") ||
			!stricmp(ext, ".xsd")/* ||

			!stricmp(ext, ".wmf") ||
			!stricmp(ext, ".emf")*/)
		{
			document.CoCreateInstance(CLSID_WebXMLDocument);
		}
		else if (!stricmp(ext, ".dtd"))
		{
			document.CoCreateInstance(CLSID_DTDDocument);
		}
		else if (
			!stricmp(ext, ".js") ||
			!stricmp(ext, ".vbs"))
		{
			document.CoCreateInstance(CLSID_ExtScriptDocument);
		}
		else if (!stricmp(ext, ".css"))
		{
			document.CoCreateInstance(CLSID_ECSSDocument);
		}
		else
		{
			document.CoCreateInstance(CLSID_TextDocument);
		}

		if (document != NULL)
		{
		//	m_frame->ActivateObject(NULL, document);

			CComQIPtr<IPersistFile> ifile = document;
			if (ifile != NULL)
			{
				ErrorCode hr = ifile->Load(pathName, STGM_READ);
				if (SUCCEEDED(hr))
				{
					m_documents.Add(document);
					document->ShowViews();
					document.Detach();

				//	m_frame->ActivateObject(NULL, document);
				}
				else
				{
					MessageBox(GetMainHwnd(), "Error loading file", "WebEditor", MB_OK);
				}
			}
			else
			{
				MessageBox(GetMainHwnd(), "Document didn't support loading from file", "WebEditor", MB_OK);
			}
		}
	}

	return S_OK;
}
#endif

#if 0
static BOOL bScannedFonts = FALSE;
static int numFonts = 0;

//static CArray<CString, CString> fontsArray;

static char prevFont[512];

int CALLBACK FontFamExProc(
  ENUMLOGFONTEX *lpelfe,    // pointer to logical-font data
  NEWTEXTMETRICEX *lpntme,  // pointer to physical-font data
  int FontType,             // type of font
  LPARAM lParam)             // application-defined data
{
	IUIComboBox* hWndComboBox = (IUIComboBox*)lParam;

	if (FontType & TRUETYPE_FONTTYPE)
	{
		if (stricmp(lpelfe->elfLogFont.lfFaceName, prevFont) != 0)
		{
			strcpy(prevFont, lpelfe->elfLogFont.lfFaceName);

			long index;
			hWndComboBox->AddString(_bstr_t(prevFont), &index);

		/*
		// Insert sorted
			for (int i = 0; i < fontsArray.GetSize(); i++)
			{
				if (fontsArray.GetAt(i) > lpelfe->elfLogFont.lfFaceName)
				{
					fontsArray.InsertAt(i, lpelfe->elfLogFont.lfFaceName);
					goto here;
				}
			}

			fontsArray.Add(lpelfe->elfLogFont.lfFaceName);
		*/

	//here:

			numFonts++;
		}
	}

	return 1;	// Continue enumeration
}

void ScanFonts(IUIComboBox* hWndComboBox)
{
	if (TRUE /*!bScannedFonts*/)
	{
		HDC	hDC = GetDC(NULL);
		LOGFONT	lf = {0};
		lf.lfCharSet = DEFAULT_CHARSET;
		
		int result = EnumFontFamiliesEx(
			hDC,					// handle to device context
			&lf,					// pointer to logical font information
			(FONTENUMPROC)FontFamExProc,    // pointer to callback function
			(LPARAM)hWndComboBox,						// application-supplied data
			0);					// reserved; must be zero

		ReleaseDC(NULL, hDC);

		bScannedFonts = TRUE;
	}
}
#endif

#if 0
ErrorCode CLXMLEditorApp::SetUIManager(IUIManager* newVal)
{
	m_uiManager = newVal;

// Commands
	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Window and Help", &group);

		//m_uiManager->AddCommandID(ID_HELP_TOPICS, L"Help Topics...", group, NULL);
		m_uiManager->AddCommandID(ID_APP_ABOUT, L"About...", group, NULL);

		m_uiManager->AddCommandID(ID_WINDOW_NEW, L"New Window", group, NULL);
		m_uiManager->AddCommandID(ID_WINDOW_NEWWINDOWONACTIVEELEMENT, L"New Window on Active Element", group, NULL);
		m_uiManager->AddCommandID(ID_WINDOW_SPLIT, L"Split Window", group, NULL);

		m_uiManager->AddCommandID(ID_WINDOW_SWATCHLIBRARIES_OPEN, L"Open...", group, NULL);
		m_uiManager->AddCommandID(ID_WINDOW_SYMBOLLIBRARIES_OPEN, L"Open...", group, NULL);
		m_uiManager->AddCommandID(ID_WINDOW_FILTERLIBRARIES_OPEN, L"Open...", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"File", &group);

		m_uiManager->AddCommandID(ID_FILE_NEW, L"New...", group, NULL);
		m_uiManager->AddCommandID(ID_FILE_NEW_DEFAULT, L"New", group, NULL);
		m_uiManager->AddCommandID(ID_FILE_OPEN, L"Open...", group, NULL);
		m_uiManager->AddCommandID(ID_FILE_OPENURL, L"Open URL...", group, NULL);
		m_uiManager->AddCommandID(ID_FILE_SAVE, L"Save", group, NULL);
		m_uiManager->AddCommandID(ID_FILE_SAVE_AS, L"Save As...", group, NULL);

//		m_uiManager->AddCommandID(ID_FILE_NEWSITE, L"New Site...", group, NULL);
//		m_uiManager->AddCommandID(ID_FILE_OPENSITE, L"Open Site...", group, NULL);

//		m_uiManager->AddCommandID(ID_FILE_NEW_NEWSITEM, L"New NewsItem", group, NULL);

//		m_uiManager->AddCommandID(ID_FILE_MOUNTWORKGROUPSITE, L"Mount Workgroup Site...", group, NULL);

//		m_uiManager->AddCommandID(ID_FILE_PROPERTIES, L"Properties...", group, NULL);

//		m_uiManager->AddCommandID(ID_FILE_PRINT, L"Print...", group, NULL);
//		m_uiManager->AddCommandID(ID_FILE_PAGE_SETUP, L"Page Setup...", group, NULL);

//		m_uiManager->AddCommandID(ID_FILE_OPENDATABASE, L"Open Database...", group, NULL);

		m_uiManager->AddCommandID(ID_FILE_PLACE, L"Place Image...", group, NULL);

//		m_uiManager->AddCommandID(ID_FILE_FTPBROWSER, L"FTP Browser...", group, NULL);
//		m_uiManager->AddCommandID(ID_FILES_PREFS, L"Preferences", group, NULL);

//		m_uiManager->AddCommandID(ID_APP_EXIT, L"Exit", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"SVG FilterGraph", &group);

		m_uiManager->AddCommandID(ID_EDITFILTER_DELETEPRIMITIVE, L"Delete Primitive", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_BLEND, L"Blend", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_COLORMATRIX, L"Color Matrix", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_COMPONENTTRANSFER, L"Component Transfer", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_COMPOSITE, L"Composite", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_CONVOLVEMATRIX, L"Convolve Matrix", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_DIFFUSELIGHTING, L"Diffuse Lighting", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_DISPLACEMENTMAP, L"Displacement Map", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_FLOOD, L"Flood", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_GAUSSIANBLUR, L"Gaussian Blur", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_IMAGE, L"Image", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_MERGE, L"Merge", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_MORPHOLOGY, L"Morphology", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_OFFSET, L"Offset", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_SPECULARLIGHTING, L"Specular Lighting", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_TILE, L"Tile", group, NULL);
		m_uiManager->AddCommandID(ID_EDITFILTER_TURBULENCE, L"Turbulence", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Site", &group);
/*
		m_uiManager->AddCommandID(ID_SITE_FTP_CONNECT, L"Connect", group, NULL);
		m_uiManager->AddCommandID(ID_SITE_FTP_DISCONNECT, L"Disconnect", group, NULL);
*/
		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Text Formatting", &group);

		//m_uiManager->AddCommandID(ID_TEXT_FACE, L"Font Face", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Edit", &group);

		m_uiManager->AddCommandID(ID_EDIT_UNDO, L"Undo", group, NULL);
		m_uiManager->AddCommandID(ID_EDIT_REDO, L"Redo", group, NULL);

		m_uiManager->AddCommandID(ID_EDIT_CUT, L"Cut", group, NULL);
		m_uiManager->AddCommandID(ID_EDIT_COPY, L"Copy", group, NULL);
		m_uiManager->AddCommandID(ID_EDIT_PASTE, L"Paste", group, NULL);
		m_uiManager->AddCommandID(ID_EDIT_PASTE_SPECIAL, L"Paste Special...", group, NULL);

		m_uiManager->AddCommandID(ID_EDIT_XPATHQUERY, L"XPath Query...", group, NULL);
		m_uiManager->AddCommandID(ID_EDIT_ADVANCED_TABIFYSELECTION, L"Tabify Selection", group, NULL);
		m_uiManager->AddCommandID(ID_EDIT_ADVANCED_UNTABIFYSELECTION, L"Untabify Selection", group, NULL);
		m_uiManager->AddCommandID(ID_EDIT_ADVANCED_MAKESELECTIONUPPERCASE, L"Make Selection Uppercase", group, NULL);
		m_uiManager->AddCommandID(ID_EDIT_ADVANCED_MAKESELECTIONLOWERCASE, L"Make Selection Lowercase", group, NULL);

		m_uiManager->AddCommandID(ID_EDIT_CLEAR, L"Clear", group, NULL);
//		m_uiManager->AddCommandID(ID_EDIT_EMPTYCLIPBOARD, L"Empty Clipboard", group, NULL);

		m_uiManager->AddCommandID(ID_FILE_CUSTOMIZE, L"Customize...", group, NULL);
		m_uiManager->AddCommandID(ID_EDIT_OPTIONS, L"Options...", group, NULL);

//		m_uiManager->AddCommandID(ID_EDIT_DEFINEPATTERN, L"Define Pattern...", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Site", &group);

//		m_uiManager->AddCommandID(ID_SITE_RESCAN, L"Rescan", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"View", &group);

		m_uiManager->AddCommandID(ID_VIEW_CSSEDITOR, L"CSS Editor", group, NULL);

		m_uiManager->AddCommandID(ID_VIEW_WORDWRAP, L"Word Wrap", group, NULL);
		m_uiManager->AddCommandID(ID_VIEW_LINENUMBERS, L"Line Numbers", group, NULL);
		m_uiManager->AddCommandID(ID_VIEW_VIEWWHITESPACE, L"View Whitespace", group, NULL);

		m_uiManager->AddCommandID(ID_VIEW_REFRESH, L"Refresh", group, NULL);

		m_uiManager->AddCommandID(ID_VIEW_ZOOMIN, L"Zoom In", group, NULL);
		m_uiManager->AddCommandID(ID_VIEW_ZOOMOUT, L"Zoom Out", group, NULL);
		m_uiManager->AddCommandID(ID_VIEW_ACTUALSIZE, L"Actual Size", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Site Files", &group);
/*
		m_uiManager->AddCommandID(ID_FILES_HOMEPAGE, L"Set as Homepage", group, NULL);
		m_uiManager->AddCommandID(ID_FILES_NEWFOLDER, L"New Folder", group, NULL);
*/
		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Object", &group);

		m_uiManager->AddCommandID(ID_OBJECT_TRANSFORM_CLEAR, L"Clear", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_TRANSFORM_CONSOLIDATE, L"Consolidate", group, NULL);

		m_uiManager->AddCommandID(ID_OBJECT_GROUP, L"Group", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_UNGROUP, L"Ungroup", group, NULL);

		m_uiManager->AddCommandID(ID_OBJECT_ARRANGE_BRINGTOFRONT, L"Bring to Front", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_ARRANGE_BRINGFORWARD, L"Bring Forward", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_ARRANGE_SENDBACKWARD, L"Send Backward", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_ARRANGE_SENDTOBACK, L"Send to Back", group, NULL);

		m_uiManager->AddCommandID(ID_OBJECT_CONVERTTOPATH, L"Convert To Path", group, NULL);

		m_uiManager->AddCommandID(ID_OBJECT_ALIGN_HORIZONTALLEFT, L"Horizontal Left", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_ALIGN_HORIZONTALRIGHT, L"Horizontal Right", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_ALIGN_HORIZONTALCENTER, L"Horizontal Center", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_ALIGN_VERTICALTOP, L"Vertical Top", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_ALIGN_VERTICALBOTTOM, L"Vertical Bottom", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_ALIGN_VERTICALCENTER, L"Vertical Center", group, NULL);

		m_uiManager->AddCommandID(ID_OBJECT_ENVELOPEDISTORT_MAKEWITHMESH, L"Make With Mesh...", group, NULL);

		m_uiManager->AddCommandID(ID_SELECT_BACK, L"Back", group, NULL);

		m_uiManager->AddCommandID(ID_OBJECT_EDITPAINT, L"Edit Paint", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_EDITMASK, L"Edit Mask", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_EDITCLIPPINGPATH, L"Edit Clipping Path", group, NULL);

/*

		m_uiManager->AddCommandID(ID_OBJECT_COMPOUND_MAKE, L"Make Compound", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_COMPOUND_RELEASE, L"Release Compound", group, NULL);
		m_uiManager->AddCommandID(ID_OBJECT_REVERSEPATH, L"Reverse Path", group, NULL);
*/
		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Color", &group);

		m_uiManager->AddCommandID(ID_COLOR_INVERT, L"Invert", group, NULL);
		m_uiManager->AddCommandID(ID_COLOR_COMPLEMENT, L"Complement", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

/*
	{
		CComQIPtr<ICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Convert", &group);

		m_uiManager->AddCommandID(ID_CONVERT_IMPORTDATABASEDATA, L"Convert Database data...", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}
*/
	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Convert", &group);

		m_uiManager->AddCommandID(ID_XSL_ASSIGNXSL, L"Assign XSL...", group, NULL);
		m_uiManager->AddCommandID(ID_XSL_GOTOXSL, L"Goto XSL", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"SVG Tools", &group);

		m_uiManager->AddCommandID(ID_SVGTOOL_TOGGLEFILLSTROKE, L"Toggle Fill/Stroke", group, NULL);
		/*
		AddCommandID(ID_SVGTOOL_SELECT, L"Select", group, NULL);
		AddCommandID(ID_SVGTOOL_DIRECT, L"Direct", group, NULL);
		*/
		/*
		AddCommandID(ID_SVGTOOL_PATHPEN, L"Pen", group, NULL);
		AddCommandID(ID_SVGTOOL_PATHADDANCHOR, L"Pen Add", group, NULL);
		AddCommandID(ID_SVGTOOL_PATHDELETEANCHOR, L"Pen Delete", group, NULL);
		AddCommandID(ID_SVGTOOL_PATHCORNER, L"Pen Corner", group, NULL);
		*/
		/*
		AddCommandID(ID_SVGTOOL_CIRCLE, L"Circle", group, NULL);
		AddCommandID(ID_SVGTOOL_ELLIPSE, L"Ellipse", group, NULL);
		AddCommandID(ID_SVGTOOL_RECTANGLE, L"Rectangle", group, NULL);
		AddCommandID(ID_SVGTOOL_LINE, L"Line", group, NULL);
		*/
//		m_uiManager->AddCommandID(ID_TOOL_TEXT, L"Text", group, NULL);

//		m_uiManager->AddCommandID(ID_TOOL_ROTATE, L"Rotate", group, NULL);
//		m_uiManager->AddCommandID(ID_TOOL_SCALE, L"Scale", group, NULL);
//		m_uiManager->AddCommandID(ID_TOOL_SKEW, L"Skew", group, NULL);
//		m_uiManager->AddCommandID(ID_TOOL_TWIRL, L"Twirl", group, NULL);

		/*
		m_uiManager->AddCommandID(ID_IMAGETOOL_SELECT, L"Select", group, NULL);

		m_uiManager->AddCommandID(ID_IMAGETOOL_RECTANGULARMARQUEE, L"Rectangular Marquee", group, NULL);
		m_uiManager->AddCommandID(ID_IMAGETOOL_ELLIPTICALMARQUEE, L"Elliptical Marquee", group, NULL);
		m_uiManager->AddCommandID(ID_IMAGETOOL_MAGICWAND, L"Magic Wand", group, NULL);

		m_uiManager->AddCommandID(ID_IMAGETOOL_PAINTBRUSH, L"Paintbrush", group, NULL);
		m_uiManager->AddCommandID(ID_IMAGETOOL_ELLIPSE, L"Ellipse", group, NULL);
		*/

		m_uiManager->AddCommandID(ID_TOOL_TEXT, L"Text", group, NULL);
		m_uiManager->AddCommandID(ID_TOOL_TEXTPATH, L"Path Text", group, NULL);

		m_uiManager->AddCommandID(ID_SVGTOOL_GRADIENT, L"Gradient", group, NULL);

		m_uiManager->AddCommandID(ID_TOOL_ZOOM, L"Zoom", group, NULL);
		m_uiManager->AddCommandID(ID_TOOL_HAND, L"Hand", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Filters/Swatches/Symbols", &group);

		m_uiManager->AddCommandID(ID_FILTERS_NEWFILTER, L"New Filter...", group, NULL);
		m_uiManager->AddCommandID(ID_FILTERS_SELECTALLUNUSED, L"Select All Unused", group, NULL);

		m_uiManager->AddCommandID(ID_SVGFILTERS_DELETEFILTER, L"Delete Filter", group, NULL);
		m_uiManager->AddCommandID(ID_SVGSWATCHES_DELETESWATCH, L"Delete Swatch", group, NULL);

		m_uiManager->AddCommandID(ID_SVGLIST_LARGETHUMBNAILS, L"Large Thumbnails", group, NULL);
		m_uiManager->AddCommandID(ID_SVGLIST_SMALLTHUMBNAILS, L"Small Thumbnails", group, NULL);
		m_uiManager->AddCommandID(ID_SVGLIST_SMALLLISTVIEW, L"Small List View", group, NULL);
		m_uiManager->AddCommandID(ID_SVGLIST_LARGELISTVIEW, L"Large List View", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Element Mask", &group);

		m_uiManager->AddCommandID(ID_ELEMENTMASK_MAKEMASK, L"Make Mask", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Symbols", &group);

		m_uiManager->AddCommandID(ID_SYMBOLS_NEWSYMBOL, L"New Symbol...", group, NULL);
		m_uiManager->AddCommandID(ID_SYMBOLS_PLACESYMBOL, L"Place Symbol", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}
	
	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Abstract Schema", &group);

		m_uiManager->AddCommandID(ID_ASGRAPH_CHANGEMODEL_SEQUENCE, L"Sequence", group, NULL);
		m_uiManager->AddCommandID(ID_ASGRAPH_CHANGEMODEL_CHOICE, L"Choice", group, NULL);
		m_uiManager->AddCommandID(ID_ASGRAPH_CHANGEMODEL_ALL, L"All", group, NULL);
		m_uiManager->AddCommandID(ID_ASGRAPH_OPTIONAL, L"Optional", group, NULL);
		m_uiManager->AddCommandID(ID_ASGRAPH_UNBOUNDED, L"Unbounded", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"XML", &group);

		m_uiManager->AddCommandID(ID_XML_TABLE_DISPLAYASTABLE, L"Display as Table", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"SMIL", &group);

		m_uiManager->AddCommandID(ID_SMILLAYOUTS_NEWTOPLAYOUT, L"New topLayout", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"SMIL TimeGraph", &group);

		m_uiManager->AddCommandID(ID_TIMEGRAPH_OPTIONS, L"TimeGraph Options...", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	/*
	// Query Design
	{
		CComQIPtr<ICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Query Design", &group);

		m_uiManager->AddCommandID(ID_QUERYDESIGN_RUN, L"Run", group, NULL);
		m_uiManager->AddCommandID(ID_QUERYDESIGN_ADDTABLE, L"Add Table", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}
	*/

	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Insert", &group);

		m_uiManager->AddCommandID(ID_INSERT_IMAGE, L"Image...", group, NULL);

		m_uiManager->AddCommandID(ID_INSERT_FORM_ONELINETEXTBOX, L"One-Line Text Box", group, NULL);
		m_uiManager->AddCommandID(ID_INSERT_FORM_CHECKBOX, L"Check Box", group, NULL);
		m_uiManager->AddCommandID(ID_INSERT_FORM_RADIOBUTTON, L"Radio Button", group, NULL);
		m_uiManager->AddCommandID(ID_INSERT_FORM_PUSHBUTTON, L"Push Button", group, NULL);
		m_uiManager->AddCommandID(ID_INSERT_FORM_SCROLLINGTEXTBOX, L"Scrolling Text Box", group, NULL);
		m_uiManager->AddCommandID(ID_INSERT_FORM_DROPDOWNMENU, L"Dropdown Menu", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	// Formatting
	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Formatting", &group);

		{
			CComPtr<IUICommand> cmd;
			m_uiManager->AddCommandID(ID_FORMATTING_FORMAT, L"Format", group, &cmd);
			cmd->put_windowClassname(L"ComboBox");
			cmd->put_windowStyle(CBS_AUTOHSCROLL | CBS_DROPDOWNLIST | WS_VSCROLL);
			cmd->put_itemWidth(100);
			cmd->AddString(L"None");
			cmd->AddString(L"Header 1");
			cmd->AddString(L"Header 2");
			cmd->AddString(L"Header 3");
			cmd->AddString(L"Header 4");
			cmd->AddString(L"Header 5");
			cmd->AddString(L"Header 6");
			cmd->AddString(L"Preformatted");
			cmd->AddString(L"Address");
		}

		m_uiManager->AddCommandID(ID_FORMATTING_NUMBEREDLIST, L"Numbered List", group, NULL);
		m_uiManager->AddCommandID(ID_FORMATTING_UNNUMBEREDLIST, L"Unnumbered List", group, NULL);
		
		/*
		AddCommandID(ID_CHARACTER_FONTFACE, L"Font", group, NULL);
		AddCommandID(ID_CHARACTER_FONTSIZE, L"Font Size", group, NULL);
		AddCommandID(ID_PARAGRAPH_ALIGNLEFT, L"Align Left", group, NULL);
		AddCommandID(ID_PARAGRAPH_ALIGNRIGHT, L"Align Right", group, NULL);
		AddCommandID(ID_PARAGRAPH_ALIGNCENTER, L"Align Center", group, NULL);
		AddCommandID(ID_PARAGRAPH_ALIGNJUSTIFY, L"Align Justify", group, NULL);
		*/

		m_uiManager->AppendCommandGroup(group);
	}

	// Table
	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Table", &group);

		m_uiManager->AddCommandID(ID_TABLE_INSERT_TABLE, L"Table...", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	// CSS
	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"CSS", &group);

		m_uiManager->AddCommandID(ID_CSS_NEWINTERNALSTYLEELEMENT, L"New Internal Style Element", group, NULL);
		m_uiManager->AddCommandID(ID_CSS_NEWIMPORTRULE, L"New Import Rule...", group, NULL);
		m_uiManager->AddCommandID(ID_CSS_NEWCLASSSTYLE, L"New Style Rule", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	// Navigator Dialog
	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"Navigator", &group);

		m_uiManager->AddCommandID(ID_NAVIGATOR_PALETTEOPTIONS, L"Palette Options...", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}
	
	// CSSProperties
	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"CSSProperties", &group);

		m_uiManager->AddCommandID(ID_CSSPROPERTIES_TABBEDVIEW, L"Tabbed View", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	// SVG Objects
	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"SVG Objects", &group);

		m_uiManager->AddCommandID(ID_SVGOBJECTS_NEWLAYER, L"New Layer...", group, NULL);
		m_uiManager->AddCommandID(ID_SVGOBJECTS_NEWSUBLAYER, L"New Sublayer...", group, NULL);
		m_uiManager->AddCommandID(ID_SVGOBJECTS_NEWVIEWPORT, L"New Viewport", group, NULL);
		m_uiManager->AddCommandID(ID_SVGOBJECTS_DELETESELECTION, L"Delete Selection", group, NULL);
		m_uiManager->AddCommandID(ID_SVGOBJECTS_SELECTIONOPTIONS, L"Options for Selection...", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	// SVG Objects
	{
		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"SVG Fonts/Glyphs", &group);

		m_uiManager->AddCommandID(ID_SVGFONTS_NEWFONT, L"New Font...", group, NULL);
		m_uiManager->AddCommandID(ID_SVGGLYPHS_NEWGLYPH, L"New Glyph...", group, NULL);

		m_uiManager->AppendCommandGroup(group);
	}

	m_uiManager->AddToolbarCommands(_Module.GetResourceInstance(), IDR_MAINFRAME);
	m_uiManager->AddToolbarCommands(_Module.GetResourceInstance(), IDR_SVGTOOLS);

	return S_OK;
}
#endif

#if 0
// ILDOMEventListener
ErrorCode CLXMLEditorApp::handleEvent(ILDOMEvent* evt)
{
	CComQIPtr<ILDOMUIEvent> uievt = evt;
	if (uievt)
	{
		long cmdid;
		uievt->get_detail(&cmdid);

		{
			WORD nCode = WM_COMMAND;
			WORD nID = (WORD)cmdid;
			const CmdEntry* entry = GetCmdEntries();

		//	if (nCode != -1)
			{
				UI::Control* hWnd = NULL;
#if 0
				if (pCmdUI) pCmdUI->get_hwndControl(&hWnd);

				*bHandled = FALSE;
#endif

				while (entry->iid != 0)
				{
					if (entry->type == 1)
					{
						if (nID == entry->iid)
						{
							BOOL bHandled2 = TRUE;
							(this->*entry->func)((WORD)nCode, (WORD)nID, hWnd, bHandled2);

#if 0
							*bHandled = bHandled2;
#endif
							return S_OK;
						}
					}
					entry++;
				}
			}
		}
	}
	return S_OK;
}
#endif

BEGIN_CMD_MAP(CLXMLEditorApp)

#if 0
//	CMD_HANDLER(ID_TOOLS_SCANFORMEDIAFILES, OnScanMediaFiles)

// File
	CMD_HANDLER(ID_FILE_NEW, OnFileNew)
	CMD_HANDLER(ID_FILE_NEW_DEFAULT, OnFileNewDefault)
	CMD_HANDLER(ID_FILE_OPEN, OnFileOpen)
	CMD_HANDLER(ID_FILE_OPENURL, OnFileOpenURL)

//	CMD_HANDLER(ID_FILE_NEWSITE, OnFileNewSite)
//	CMD_HANDLER(ID_FILE_OPENSITE, OnFileOpenSite)
//	CMD_HANDLER(ID_FILE_MOUNTWORKGROUPSITE, OnFileMountWorkgroupSite)

//	CMD_HANDLER(ID_FILE_NEW_NEWSITEM, OnNewNewsItem)

//	CMD_HANDLER(ID_FILE_FTPBROWSER, OnFileFTPBrowser)

//	CMD_HANDLER(ID_FILE_OPENDATABASE, OnFileOpenDatabase)

// Edit
//	CMD_HANDLER(ID_FILE_CUSTOMIZE, OnCustomize)
	CMD_HANDLER(ID_EDIT_OPTIONS, OnOptions)

//	CMD_HANDLER(ID_CONVERT_IMPORTDATABASEDATA, OnConvertImportDatabaseData)

// SVGTool
	CMD_HANDLER(ID_SVGTOOL_SELECT, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_SELECT, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_DIRECT, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_DIRECT, OnSVGToolUpdate)

	CMD_HANDLER(ID_TOOL_TEXT, OnSVGTool)
	CMD_UPDATEUI(ID_TOOL_TEXT, OnSVGToolUpdate)
	CMD_HANDLER(ID_TOOL_TEXTPATH, OnSVGTool)
	CMD_UPDATEUI(ID_TOOL_TEXTPATH, OnSVGToolUpdate)

//	CMD_HANDLER(ID_SVGTOOL_SVGELEMENT, OnSVGTool)
//	CMD_UPDATEUI(ID_SVGTOOL_SVGELEMENT, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_CIRCLE, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_CIRCLE, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_ELLIPSE, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_ELLIPSE, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_RECTANGLE, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_RECTANGLE, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_ROUNDEDRECTANGLE, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_ROUNDEDRECTANGLE, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_LINE, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_LINE, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_RECTANGULARGRID, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_RECTANGULARGRID, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_POLARGRID, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_POLARGRID, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_CUSTOMSHAPE, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_CUSTOMSHAPE, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_PATHPEN, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_PATHPEN, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_POLYGON, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_POLYGON, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_PENCIL, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_PENCIL, OnSVGToolUpdate)

//	CMD_HANDLER(ID_SVGTOOL_POLYLINE, OnSVGTool)
//	CMD_UPDATEUI(ID_SVGTOOL_POLYLINE, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_FREETRANSFORM, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_FREETRANSFORM, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_EYEDROPPER, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_EYEDROPPER, OnSVGToolUpdate)
	CMD_HANDLER(ID_SVGTOOL_PAINTBUCKET, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_PAINTBUCKET, OnSVGToolUpdate)

// Liquify
	CMD_HANDLER(ID_SVGTOOL_WARP, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_WARP, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_TWIRL, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_TWIRL, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_PUCKER, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_PUCKER, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_BLOAT, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_BLOAT, OnSVGToolUpdate)

// Symbolism
	CMD_HANDLER(ID_SVGTOOL_SYMBOL_SPRAYER, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_SYMBOL_SPRAYER, OnSVGToolUpdate)
	CMD_HANDLER(ID_SVGTOOL_SYMBOL_SHIFTER, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_SYMBOL_SHIFTER, OnSVGToolUpdate)
	CMD_HANDLER(ID_SVGTOOL_SYMBOL_SCRUNCHER, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_SYMBOL_SCRUNCHER, OnSVGToolUpdate)
	CMD_HANDLER(ID_SVGTOOL_SYMBOL_SIZER, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_SYMBOL_SIZER, OnSVGToolUpdate)
	CMD_HANDLER(ID_SVGTOOL_SYMBOL_SPINNER, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_SYMBOL_SPINNER, OnSVGToolUpdate)
	CMD_HANDLER(ID_SVGTOOL_SYMBOL_SCREENER, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_SYMBOL_SCREENER, OnSVGToolUpdate)
	CMD_HANDLER(ID_SVGTOOL_SYMBOL_STYLER, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_SYMBOL_STYLER, OnSVGToolUpdate)

//
	CMD_HANDLER(ID_SVGTOOL_GRADIENT, OnSVGTool)
	CMD_UPDATEUI(ID_SVGTOOL_GRADIENT, OnSVGToolUpdate)

	CMD_HANDLER(ID_TOOL_ZOOM, OnSVGTool)
	CMD_UPDATEUI(ID_TOOL_ZOOM, OnSVGToolUpdate)

	CMD_HANDLER(ID_TOOL_HAND, OnSVGTool)
	CMD_UPDATEUI(ID_TOOL_HAND, OnSVGToolUpdate)

	CMD_HANDLER(ID_SVGTOOL_TOGGLEFILLSTROKE, OnSVGToggleFillStroke)

//	CMD_HANDLER(ID_FILES_PREFS, OnFilePrefs)

// Edit
//	CMD_HANDLER(ID_EDIT_EMPTYCLIPBOARD, OnEditEmptyClipboard)
//	CMD_UPDATEUI(ID_EDIT_EMPTYCLIPBOARD, OnEditEmptyClipboardUpdate)

// Help
//	CMD_HANDLER(ID_HELP_TOPICS, OnHelp)
//	CMD_HANDLER(ID_APP_ABOUT, OnAbout)


	CMD_HANDLER(ID_TOOLS_MACRO_RECORD, OnMacroRecord)

//
//	CMD_UPDATEUI(&ID_TEXT_FACE, OnFontfaceUpdate)
// Window

	CMD_HANDLER(ID_WINDOW_SWATCHLIBRARIES_OPEN, OnSwatchLibrariesOpen)
	CMD_HANDLER(ID_WINDOW_SYMBOLLIBRARIES_OPEN, OnSymbolLibrariesOpen)
	CMD_HANDLER(ID_WINDOW_FILTERLIBRARIES_OPEN, OnFilterLibrariesOpen)
#endif
END_CMD_MAP()

long CLXMLEditorApp::OnMacroRecord(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	if (!m_macroRecording)
	{
		m_macroRecording = true;
	}
	else
	{
		m_macroRecording = false;

		//
		IEDocument* document;
	//	document.CoCreateInstance(CLSID_EScriptDocument);
	}

	return 0;
}

long CLXMLEditorApp::OnFileOpen(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
//	USES_CONVERSION;

#if 0
	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIFrame> frame = lxframe;
#endif

	ASSERT(0);
#if 0
	UI::Control* hWnd = NULL;
	//frame->get_hwnd(&hWnd);

	static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
												"XHTML (*.htm,*.html,*.shtml)\0*.htm;*.html;*.shtml\0"
												"SVG (*.svg)\0*.svg\0"
												"SMIL (*.smil,*.smi)\0*.smil;*.smi\0"
												"XML Schema (*.xsd)\0*.xsd\0"
												"XML (*.xml)\0*.xml\0"
												"XSLT (*.xslt)\0*.xslt\0"
												"DTD (*.dtd)\0*.dtd\0"
												"ASP (*.asp)\0*.asp\0"
												"StyleSheet (*.css)\0*.css\0"
												"JavaScript (*.js)\0*.js\0"
												"Java (*.java)\0*.java\0"
												"Text (*.txt)\0*.txt\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename
	
	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400;//sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	
	if (GetOpenFileName(&ofn))
	{
		CComPtr<IUnknown> document;
		ErrorCode hr = OpenDocument(A2W(sbuffer), &document);
		if (FAILED(hr))
		{
			// TODO, check IError or something
			MessageBox(hWnd, "Failed to open document", "LXMLEditor", MB_OK);
		}
	}
#endif
	return 0;
}

long CLXMLEditorApp::OnFileOpenURL(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIFrame> frame = lxframe;

	UI::Control* hWnd;
	frame->get_hwnd(&hWnd);

	COpenURLDlg dlg;
	//dlg.m_url = L"http://www.w3.org";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20021112/svggen/painting-fill-01-t.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20021112/svggen/script-handle-01-t.svg";

//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20021112/svggen/interact-dom-01-t.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20021112/svggen/interact-order-01-t.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20021112/svggen/interact-events-01-t.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20021112/svggen/interact-cursor-01-b.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20021112/svggen/pservers-pattern-01-b.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20021112/svggen/text-align-01-b.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20021112/svggen/struct-symbol-01-b.svg";

//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20011026/paint-markers-BE-03.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20011026/color-colorProf-BE-03.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20011026/masking-clipPath-BE-01.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20011026/masking-clipPath-BE-02.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20011026/masking-clipRule-BE-03.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20011026/masking-groupOpac-BE-04.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20011026/paint-fill-BE-01.svg";
//	dlg.m_url = L"http://www.w3.org/Graphics/SVG/Test/20011026/paint-stroke-BE-02.svg";

	dlg.m_url = L"ftp://w00005125:A7h2GH@lerstad.com/pendulum.svg";

	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_url.length())
		{
			CComPtr<IUnknown> document;
			ErrorCode hr = OpenDocument(dlg.m_url, &document);
			if (FAILED(hr))
			{
				// TODO, check IError or something
				MessageBox(hWnd, "Failed to open document", "LXMLEditor", MB_OK);
			}
		}
	}
#endif

	return 0;
}

/*
long CLXMLEditorApp::OnScanMediaFiles(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	return 0;
}
*/

//#include "AboutDlg.h"

long CLXMLEditorApp::OnSVGToggleFillStroke(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	m_strokeOrFill = !m_strokeOrFill;

// TODO, change in CColorDlg ??

	return 0;
}

#if 0
//#include "FTPView.h"

long CLXMLEditorApp::OnFileFTPBrowser(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	CComObject<CUIMDIChild>* child;
	CComObject<CUIMDIChild>::CreateInstance(&child);
	if (child)
	{
		child->AddRef();
		gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

		{
		// FTPView
			CComObject<CFTPView>* pFtpView;
			CComObject<CFTPView>::CreateInstance(&pFtpView);
			if (pFtpView)
			{
				gApp->m_frame->FindMenu(IDR_FTPVIEW, &pFtpView->m_menu);
//				pFtpView->m_document = this;
				child->AddPage(pFtpView, NULL);
			}
		}

		child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);
	}

	return 0;
}
#endif

long CLXMLEditorApp::OnSwatchLibrariesOpen(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIFrame> frame = lxframe;

	UI::Control* hWnd;
	frame->get_hwnd(&hWnd);

	static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
												"svg (*.svg)\0*.svg\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename
	
	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	ofn.nFilterIndex = 2;
	
	if (GetOpenFileName(&ofn))
	{
		TCHAR filename[256];
		_splitpath(sbuffer, NULL, NULL, filename, NULL);

#if 0
		CComPtr<IUIDlgClass> rdlg;
		m_uiManager->RegisterDlg(25, _bstr_t(filename), 0, &rdlg);
		if (rdlg)
		{
			CComPtr<IUIDlg> dlg;
			rdlg->CreateDlg(&dlg);
			if (dlg)
			{
				CComQIPtr<ISVGSwatchLibraryDlg> libraryDlg = dlg;
				libraryDlg->Load(_bstr_t(sbuffer));

				CComPtr<IUIDlgSheet> sheet;
				m_uiManager->CreateDlgSheet(NULL, &sheet);

				sheet->AddPage(rdlg, NULL);

				CComPtr<IUIDlgSite> dlgsite;
				m_uiManager->CreateDlgSite(sheet, &dlgsite);

				frame->FloatControlBar(dlgsite, CPoint(0,0), CBRS_SIZE_DYNAMIC);
			}
		}
#endif
	}
#endif

	return 0;
}

long CLXMLEditorApp::OnSymbolLibrariesOpen(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIFrame> frame = lxframe;

	UI::Control* hWnd;
	frame->get_hwnd(&hWnd);

	static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
												"svg (*.svg)\0*.svg\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename
	
	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	ofn.nFilterIndex = 2;
	
	if (GetOpenFileName(&ofn))
	{
		TCHAR filename[256];
		_splitpath(sbuffer, NULL, NULL, filename, NULL);

		ASSERT(0);
#if 0
		CComPtr<IUIDlgClass> registeredDlg;
		m_frame->RegisterDlg(CLSID_SVGSymbolLibraryDlg, _bstr_t(filename), 0, &registeredDlg);
		if (registeredDlg)
		{
			CComPtr<IUIDlg> dlg;
			registeredDlg->CreateDlg(&dlg);
			if (dlg)
			{
				CComQIPtr<ISVGSymbolLibraryDlg> libraryDlg = dlg;
				libraryDlg->Load(_bstr_t(sbuffer));
			}
		}
#endif
	}
#endif

	return 0;
}

long CLXMLEditorApp::OnFilterLibrariesOpen(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIFrame> frame = lxframe;

	UI::Control* hWnd;
	frame->get_hwnd(&hWnd);

	static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
												"svg (*.svg)\0*.svg\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename
	
	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	ofn.nFilterIndex = 2;
	
	if (GetOpenFileName(&ofn))
	{
		TCHAR filename[256];
		_splitpath(sbuffer, NULL, NULL, filename, NULL);

		ASSERT(0);
#if 0
		CComPtr<IUIDlgClass> registeredDlg;
		m_frame->RegisterDlg(CLSID_SVGFilterLibraryDlg, _bstr_t(filename), 0, &registeredDlg);
		if (registeredDlg)
		{
			CComPtr<IUIDlg> dlg;
			registeredDlg->CreateDlg(&dlg);
			if (dlg)
			{
				CComQIPtr<ISVGFilterLibraryDlg> libraryDlg = dlg;
				libraryDlg->Load(_bstr_t(sbuffer));
			}
		}
#endif
	}
#endif

	return 0;
}

#if 0
#include "NewsItemDocument.h"

long CLXMLEditorApp::OnNewNewsItem(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	CComObject<CNewsItemDocument>* pDocument;
	CComObject<CNewsItemDocument>::CreateInstance(&pDocument);
	if (pDocument)
	{
		pDocument->AddRef();

		pDocument->m_nmldocument.CoCreateInstance(CLSID_LNewsMLDocument);

		pDocument->ShowView();
	}

	return 0;
}
#endif

ErrorCode CLXMLEditorApp::SetActiveToolByID(long wID)
{
	CTool* pTool = NULL;
	for (int i = 0; i < m_tools.GetSize(); i++)
	{
		if (m_tools[i]->m_id == wID)
		{
			pTool = m_tools[i];
			break;
		}
	}

	if (m_pActiveTool != pTool)
	{
		ASSERT(0);
#if 0
		if (m_pActiveTool)
		{
			m_pToolOptionsDlg->m_sheet->SetActivePage(NULL);
			m_pActiveTool->m_tool->OnDeactivate(this);
		}

		m_pActiveTool = pTool;

		if (m_pActiveTool)
		{
			m_pToolOptionsDlg->m_sheet->SetActivePage(m_pActiveTool->m_toolOptionsDlgSite);
			m_pActiveTool->m_tool->OnActivate(this);

			switch (wID)
			{
			case ID_SVGTOOL_SELECT:
			case ID_SVGTOOL_DIRECT:
				m_pActiveSelectionTool = m_pActiveTool;
				break;

				/*
			case ID_SVGTOOL_WARP:
			case ID_SVGTOOL_TWIRL:
			case ID_SVGTOOL_PUCKER:
			case ID_SVGTOOL_BLOAT:
				{
					if (wNotifyCode == BN_DBLCLK)
					{
						CPropertySheet* sheet = new CPropertySheet("Tool", 0, GetMainHwnd());

						CBrushDimensionsDlg	brush;
						brush.m_brushSettings = this;
						sheet->AddPage(brush);

						sheet->DoModal();
					}
				}
				break;
				*/
			}

		}
#endif

		ASSERT(0);
#if 0
		Fire_ActiveToolChange();
#endif
	}

	return Success;
}

long CLXMLEditorApp::OnSVGTool(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIFrame> frame = lxframe;

	UI::Control* hWnd;
	frame->get_hwnd(&hWnd);

	if (wNotifyCode == BN_DBLCLK)
	{
		if (m_pActiveTool)
		{
			m_pActiveTool->m_tool->Options(hWnd);
		}
	}
	else
	{
		SetActiveToolByID(wID);
	}
#endif

	return 0;
}

void CLXMLEditorApp::OnSVGToolUpdate(long id, UI::IUICmdUpdate* pCmdUI)
{
	if (m_pActiveTool)
	{
		pCmdUI->SetCheck(m_pActiveTool->m_id == id);
	}
}

long CLXMLEditorApp::OnFileNew(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	USES_CONVERSION;

	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	UI::Control* hWnd;
	lxframe->GetWindow(&hWnd);

	CFileNewDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CComPtr<IUnknown> document;
		ErrorCode hr = OpenDocument(A2W(dlg.m_pathName), &document);
		if (FAILED(hr))
		{
			// TODO, check IError or something
			MessageBox(hWnd, "Failed to open document", "LXMLEditor", MB_OK);
		}
	}
#endif

	return 0;
}

long CLXMLEditorApp::OnFileNewDefault(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	//CEXMLDocument* pDocument = new CEXMLDocument;

#if 0

	if (pDocument != NULL)
	{
		pDocument->NewDocument();
		pDocument->ShowViews();

#if 0
		m_frame->ActivateObject(NULL, pDocument->GetUnknown());
#endif
	}
#endif

	return 0;
}

long CLXMLEditorApp::OnEditEmptyClipboard(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIFrame> frame = lxframe;

	UI::Control* hWnd;
	frame->get_hwnd(&hWnd);

	if (MessageBox(hWnd, "Are you sure you want to empty the clipboard?", "WebEditor", MB_YESNO) == IDYES)
	{
		if (OpenClipboard(NULL))
		{
			EmptyClipboard();
			CloseClipboard();
		}
	}
#endif

	return 0;
}

void CLXMLEditorApp::OnEditEmptyClipboardUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	pCmdUI->Enable(CountClipboardFormats() > 0);
#endif
}

void CLXMLEditorApp::OnFontfaceUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
#if 0
	CComQIPtr<IUIMenuDlg> dlg;
	pCmdUI->get_dlg(&dlg);

	CComQIPtr<IMenuItem> menuItem;
	pCmdUI->get_menuItem(&menuItem);

	CRect itemrect;
	dlg->GetItemRect(menuItem, &itemrect);

	CComQIPtr<IUIComboBox> box;
	box.CoCreateInstance(CLSID_UIComboBox);

	//box->CreateControl(dlg, 0, 0, WS_VISIBLE, itemrect.left, itemrect.top, itemrect.Width(), itemrect.Height(), NULL);

//	pCmdUI->get_controlItem((IUIControl**)&box);

	//ScanFonts(box);
/*
	long index;

	box->AddString(L"1", &index);
	box->AddString(L"2", &index);
	box->AddString(L"3", &index);
	box->AddString(L"4", &index);
*/

	box.Detach();
#endif
}

long CLXMLEditorApp::OnHelp(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
#if 0
	HELPLib::IHelpFramePtr help;
	help.CreateInstance("Help.HelpFrame");

	help->ShowHelp("C:\\mmsx\\2DAnimator\\Help\\TOC.xml");
	help->AddRef();	// ??
#endif

	return 0;
}

#if 0
long CLXMLEditorApp::OnAbout(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	CAboutDlg dlg;
	dlg.DoModal(GetMainHwnd());

	return 0;
}
#endif

#if 0
long CLXMLEditorApp::OnFilePrefs(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	HINSTANCE hLib = LoadLibrary("C:\\mmsx\\mmstudioplugins\\DOMCOREMOD.dll");
	if (hLib)
	{
		HTMLModalDialogProc HTMLModalDialog = (HTMLModalDialogProc)GetProcAddress(hLib, "HTMLModalDialog");
		if (HTMLModalDialog)
		{
			_variant_t arg;// = (IDispatch*)m_uiManager;

			_variant_t result;
			HTMLModalDialog(GetMainHwnd(), L"C:\\MMStudio\\app_prefs.html", &arg, L"", &result);
		}
		else
		{
			MessageBox(GetMainHwnd(), "Couldn't find proc", "WebEditor", MB_OK);
		}

		FreeLibrary(hLib);
	}
	else
	{
		MessageBox(GetMainHwnd(), "Couldn't load library", "WebEditor", MB_OK);
	}

	return 0;
}
#endif

long CLXMLEditorApp::OnOptions(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<ILXFrameworkFrame> lxframe;
	m_spAddinSite->GetFrame(&lxframe);

	CComQIPtr<IUIFrame> frame = lxframe;

	UI::Control* hWnd;
	frame->get_hwnd(&hWnd);

	CPropertySheet sheet("Options", 0, hWnd);
	sheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	CPrefsTabsDlg tabs;
	tabs.m_tabSize = m_tabSize;

	CPrefsSourceDlg source;
	source.m_colorFormat = m_colorFormat;

	CPrefsFormatDlg format;
	{
		for (int i = 0; i < m_formatWindows.GetSize(); i++)
		{
			CFormatWindow* pWindow = new CFormatWindow;
			*pWindow = *m_formatWindows[i];
			format.m_formatWindows.Add(pWindow);
		}
	}
	//tabs.m_tabSize = m_tabSize;

	CPrefsTransparencyDlg transp;
	/*
	transp.m_gridSize = 

		m_transpGridSizeX = 8;
		m_transpGridSizeY = 8;
		m_transpGridColor0 = RGB(255, 255, 255);
		m_transpGridColor1 = RGB(194, 194, 194);
		*/

//	brush.m_brushSettings = this;
	sheet.AddPage(tabs);
	sheet.AddPage(source);
	sheet.AddPage(format);
	sheet.AddPage(transp);

	if (sheet.DoModal() == IDOK)
	{
		m_tabSize = tabs.m_tabSize;
		m_colorFormat = source.m_colorFormat;

		{
			for (int i = 0; i < m_formatWindows.GetSize(); i++)
			{
				*m_formatWindows[i] = *format.m_formatWindows[i];
			}
		}

		TCHAR szPath[_MAX_PATH];

		/*
		SHGetFolderPath(
			NULL,
			CSIDL_LOCAL_APPDATA ,// nFolder,
			NULL,//HANDLE hToken,
			0,//DWORD dwFlags,
			szPath);

		MessageBox(NULL, szPath, "", MB_OK);
		*/

		Fire_OnPrefsChange();
	}
#endif

	return 0;
}

int CLXMLEditorApp::get_tabSize()
{
	return m_tabSize;
}

ErrorCode CLXMLEditorApp::AddTool(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ISVGToolFactory* factory, System::Object* /*pToolDlg*/, /*[in]*/ long toolId, /*[in]*/ System::StringW* name, System::StringW* imageFilename)
{
	ASSERT(0);
#if 0
	CComPtr<ILXFrameworkApp> app;
	m_frame->GetApp(&app);

	CComPtr<ILXUIDocument> appdocument;
	app->get_Document(&appdocument);

	CTool* pTool = new CTool;
	pTool->m_id = toolId;

	CComPtr<IUIDlg> pToolDlg;
	factory->FindTool(pTool->m_id, (IUnknown**)&pToolDlg, &pTool->m_tool);
	if (pTool->m_tool)
	{
#if 0
		if (pToolDlg)
		{
			m_uiManager->CreateDlgSite(name, NULL, CComQIPtr<IUIDlg>(pToolDlg), &pTool->m_toolOptionsDlgSite);
		}
#endif

		CComQIPtr<IUICommandGroup> group;
		m_uiManager->CreateCommandGroup(L"SVG Tools", &group);

		m_uiManager->AddCommandID(pTool->m_id, name, group, &pTool->m_command);

		{
			CComPtr<ILDOMElement> toolButton;
			appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"button", (ILDOMElement**)&toolButton);

			WCHAR fullpath[512];
			swprintf(fullpath, L"C:\\%s", imageFilename);

			toolButton->setAttribute(L"src", fullpath);
			toolButton->put_textContent(name);

			m_toolsElement->appendChild(toolButton, NULL);
		}

		m_tools.Add(pTool);
	}
#endif

	return Success;
}

ErrorCode CLXMLEditorApp::RemoveTool(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ long toolId)
{
	return Success;
}

ErrorCode CLXMLEditorApp::GetToolID(/*[in]*/ ISVGTool* tool, /*[out,retval]*/ long *pVal)
{
	if (tool == NULL)
	{
		*pVal = 0;
		return Success;
	}

	for (int i = 0; i < m_tools.GetSize(); i++)
	{
		if (m_tools[i]->m_tool == tool)
		{
			*pVal = m_tools[i]->m_id;
			return Success;
		}
	}

	*pVal = NULL;
	ASSERT(0);
	return Success;
}

ErrorCode CLXMLEditorApp::GetActiveTool(bool bSelection, ISVGTool **pVal)
{
	*pVal = NULL;

	if (bSelection)
	{
		if (m_pActiveSelectionTool)
			*pVal = m_pActiveSelectionTool->m_tool;
	}
	else
	{
		if (m_pActiveTool)
			*pVal = m_pActiveTool->m_tool;
	}

//	if (*pVal) (*pVal)->AddRef();

	return Success;
}

#if 0
ErrorCode CLXMLEditorApp::get_ActiveDocument(IActiveCntDocument **pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = m_ActiveDocument;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}
#endif

}	// LXmlEdit
}
