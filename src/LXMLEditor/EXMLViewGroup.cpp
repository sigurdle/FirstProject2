#include "stdafx.h"
#include "LXMLEditor2.h"
#include "EXMLViewGroup.h"

#include "LXMLEditorApp.h"

#include "ESelectedElementImpl.h"	// TODO ??? Remove

#include "EXMLDocument.h"

#include "CSSProperty.h"
#include "EXMLLayoutView.h"
#include "SmilTimeGraphView.h"
#include "XMLGridView.h"
#include "SVGObjectsDlg.h"
#include "SourceView.h"	// TODO remove
#include "InspectorDlg.h"

#include "WEUndoGroupObjects.h"

#include "SVGFilterOptionsDlg.h"
#include "BasicShapeTool.h"

namespace System
{
namespace LXmlEdit
{

void GetNewElementInsertionAt(CEXMLViewGroup* viewGroup, Web::Element** pparentNode, Web::Node** pbeforeNode)
{
	ASSERT(0);
#if 0
	CComPtr<Web::Element> parentNode;
	CComPtr<Web::Node> beforeNode;

	if (static_cast<CEXMLViewGroup*>(viewGroup)->m_pActiveSelection &&
		static_cast<CEXMLViewGroup*>(viewGroup)->m_pActiveSelection->m_parent &&
		static_cast<CEXMLViewGroup*>(viewGroup)->m_pActiveSelection->m_parent->m_parent)
	{
		((CElement*)static_cast<CEXMLViewGroup*>(viewGroup)->m_pActiveSelection->m_parent)->m_eElement->get_domElement(&parentNode);
		if (static_cast<CEXMLViewGroup*>(viewGroup)->m_pActiveSelection->m_eElement)
			static_cast<CEXMLViewGroup*>(viewGroup)->m_pActiveSelection->m_eElement->get_domNode(&beforeNode);
	}


#if 0
	if (static_cast<CEXMLViewGroup*>(viewGroup)->m_svgActiveContainer)
	{
		if (SVGIsGraphicContainer(static_cast<CEXMLViewGroup*>(viewGroup)->m_svgActiveContainer))
		{
			static_cast<CEXMLViewGroup*>(viewGroup)->m_svgActiveContainer->get_domElement(&parentNode);
			beforeNode = NULL;	// Append as last
		}
		else
		{
			CComPtr<Web::Node> node;
			static_cast<CEXMLViewGroup*>(viewGroup)->m_svgActiveContainer->get_domNode(&node);
			node->get_parentNode((Web::Node**)&parentNode);

			node->get_nextSibling(&beforeNode);
		}
	}
#endif

	*pparentNode = parentNode;
	if (*pparentNode) (*pparentNode)->AddRef();

	if (pbeforeNode)
	{
		*pbeforeNode = beforeNode;
		if (*pbeforeNode) (*pbeforeNode)->AddRef();
	}
#endif
}

///////////////////////////////////

System::StringW* MakeRGBString(int colorFormat, double red, double green, double blue, double alpha)
{
	WCHAR buf[100] = {0};

	if (colorFormat == 0)
	{
		swprintf(buf, L"#%X%X%X", ((int)red)>>4, ((int)green)>>4, ((int)blue)>>4);
	}
	else if (colorFormat == 1)
	{
		swprintf(buf, L"#%2.2X%2.2X%2.2X", (int)red, (int)green, (int)blue);
	}
	else
	{
		if (alpha == 255)
		{
			if (colorFormat == 2)	// rgb
			{
				swprintf(buf, L"rgb(%d,%d,%d)", (int)red, (int)green, (int)blue);
			}
			else if (colorFormat == 3)	// rgb %
			{
				swprintf(buf, L"rgb(%f%%,%f%%,%f%%)", red*100/255, green*100/255, blue*100/255);
			}
		}
		else
		{
			if (colorFormat == 2)	// rgb
			{
				swprintf(buf, L"rgba(%d,%d,%d,%g)", (int)red, (int)green, (int)blue, (double)alpha/255);
			}
			else if (colorFormat == 3)	// rgb %
			{
				swprintf(buf, L"rgb(%.1g%%,%.1g%%,%.1g%%,%g)", red*100/255, green*100/255, blue*100/255, (double)alpha/255);
			}
		}
	}

	return new System::StringW(string_copy(buf));
}

bool SVGIsGraphicContainer(Web::Element* element)
{
	ASSERT(0);
#if 0
	{
		CComQIPtr<ILSVGSVGElement> e = element;
		if (e) return TRUE;
	}

	{
		CComQIPtr<ILSVGGElement> e = element;
		if (e) return TRUE;
	}

	{
		CComQIPtr<ILSVGSwitchElement> e = element;
		if (e) return TRUE;
	}

	{
		CComQIPtr<ILElementTimeContainer> e = element;
		if (e) return TRUE;
	}
#endif
	return false;
}

bool SVGIsGraphicContainer(Element* eelement)
{
	ASSERT(0);
	return 0;
#if 0
	CComPtr<Web::Element> element;
	eelement->get_domElement(&element);

	return SVGIsGraphicContainer(element);
#endif
}


#if 0
long CEXMLViewGroup::OnNcDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
//	int refcount = Release();
	return 0;
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CEXMLViewGroup

CEXMLViewGroup::CEXMLViewGroup()
{
	m_pDocument = NULL;
	m_layoutView = NULL;

	m_pActiveElement = NULL;
#if 0
	m_svgActiveContainer = NULL;
#endif
	m_pActiveTimeGraphNode = NULL;
	m_pActiveTimeGraphElement = NULL;
	m_pActiveSelection = NULL;

	m_activeReferenceElement = NULL;	// (for example an <ellipse> that has a mask or clip-path
	m_activeReferencedElement = NULL; // (for example a <mask> or <clipPath>

	m_colorEditing = WSTR("stroke");
	m_currentSelectionColorRed = -1;
	m_currentSelectionColorGreen = -1;
	m_currentSelectionColorBlue = -1;
	m_currentSelectionColorAlpha = -1;

//	m_bSelectingElement = FALSE;
}

int CEXMLViewGroup::FinalConstruct()
{
	ErrorCode hr;

	ASSERT(0);
#if 0
	hr = m_currentSelectionStyle.CoCreateInstance(CLSID_LCSSStyleDeclaration);
	if (FAILED(hr)) return hr;
#endif
	return 0;
}

void CEXMLViewGroup::FinalRelease()
{
	ASSERT(0);
#if 0
	for (int i = 0; i < m_views.GetSize(); i++)
	{
		int dwRef = m_views[i]->Release();
	}
#endif
	m_views.RemoveAll();
}

#if 0
ErrorCode CEXMLViewGroup::FindBehavior(BSTR bstrBehavior, BSTR bstrBehaviorUrl, ILElementBehaviorSite* pSite, ILElementBehavior** ppBehavior)
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
#if 0
	else if (!wcscmp(bstrBehavior, L"layoutView"))
	{
		CComObject<CEXMLLayoutView>* p;
		CComObject<CEXMLLayoutView>::CreateInstance(&p);
		if (p)
		{
			*ppBehavior = p;
		}
	}
#endif
	else if (!wcscmp(bstrBehavior, L"svgtools"))
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
	else
	*/
	if (!wcscmp(bstrBehavior, L"xml_layout"))
	{
		CComObject<CEXMLLayoutView>* p;
		CComObject<CEXMLLayoutView>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			p->m_viewGroup = this;
			*ppBehavior = p;
		}
	}
	else if (!wcscmp(bstrBehavior, L"xml_source"))
	{
		CComObject<CSourceView>* p;
		CComObject<CSourceView>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			p->m_viewGroup = this;
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
			p->m_viewGroup = this;
			*ppBehavior = p;
		}
	}
	else if (!wcscmp(bstrBehavior, L"xml_inspector"))
	{
		CComObject<CInspectorDlg>* p;
		CComObject<CInspectorDlg>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			p->m_viewGroup = this;
			*ppBehavior = p;
		}
	}
	else if (!wcscmp(bstrBehavior, L"objects"))
	{
		CComObject<CSVGObjectsDlg>* p;
		CComObject<CSVGObjectsDlg>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			p->m_viewGroup = this;
			*ppBehavior = p;
		}
	}
	/*
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
	*/
	else
		ASSERT(0);

	return S_OK;
}
#endif

void CEXMLViewGroup::ApplyCurrentSelectionColorToSelectedElements()
{
	ASSERT(0);
#if 0
	long nselected;
	GetSelectedCount(&nselected);

	if (nselected > 0)
	{
		for (int i = 0; i < nselected; i++)
		{
			CComPtr<IESelectedElement> selectedElement;
			GetSelectedElementN(i, &selectedElement);

			Element* eElement;
			selectedElement->get_eElement(&eElement);

			CComPtr<Web::Element> domElement;
			eElement->get_domElement(&domElement);

			CComQIPtr<ILElementCSSInlineStyle> stylable = domElement;
			if (stylable)
			{
				CComPtr<ILCSSStyleDeclaration> style;
				stylable->get_style(&style);

				CComPtr<ILCSSValue> cssvalue;
				style->getPropertyCSSValue(m_colorEditing, &cssvalue);

				int colorFormat;
				double red;
				double green;
				double blue;
				double alpha;

				if (cssvalue)
				{
				// Get previous color notation used by property
				// Note: It could also be 'transparent', 'currentColor'...
					CComBSTR cssText;
					cssvalue->get_cssText(&cssText);

					if (((BSTR)cssText)[0] == L'#')
					{
						if (cssText.Length() == 4)
							colorFormat = 0;	// hex #xxx
						else
							colorFormat = 1;	// hex #xxxxxx
					}
					else
					{
						colorFormat = 2;	// rgb
					}

					CComQIPtr<ILSVGColor> svgColor;
					CComQIPtr<ILCSSPrimitiveValue> primValue;

					if (svgColor = cssvalue)	// Both SVGColor and SVGPaint
					{
						LRGBColor rgbColor;
						svgColor->get_rgbColor(&rgbColor);

					// Get previous values
						red = rgbColor.GetRed();
						green = rgbColor.GetGreen();
						blue = rgbColor.GetBlue();
						alpha = 255;
					}
					else if (primValue = cssvalue)
					{
						LRGBColor rgbColor;
						primValue->getRGBColorValue(&rgbColor);

					// Get previous values
						if (rgbColor.m_rgbColor)
						{
							red = rgbColor.GetRed();
							green = rgbColor.GetGreen();
							blue = rgbColor.GetBlue();

							rgbColor.m_rgbColor->get_alpha(&alpha);
							alpha *= 255;
						}
						else	// It's 'transparent' or 'currentColor'
						{
							red = -1;
							green = -1;
							blue = -1;
							alpha = -1;
						}
					}
					else
						ASSERT(0);

				// Set new values (overriding previous values)
					if (m_currentSelectionColorRed >= 0 && m_currentSelectionColorRed <= 255) red = m_currentSelectionColorRed;
					if (m_currentSelectionColorGreen >= 0 && m_currentSelectionColorGreen <= 255) green = m_currentSelectionColorGreen;
					if (m_currentSelectionColorBlue >= 0 && m_currentSelectionColorBlue <= 255) blue = m_currentSelectionColorBlue;
					if (m_currentSelectionColorAlpha >= 0 && m_currentSelectionColorAlpha <= 255) alpha = m_currentSelectionColorAlpha;
				}
				else	// Setting property for first time, format color as specified in preferences
				{
					red = m_currentSelectionColorRed;
					green = m_currentSelectionColorGreen;
					blue = m_currentSelectionColorBlue;
					alpha = m_currentSelectionColorAlpha;

					colorFormat = static_cast<CLXMLEditorApp*>(m_pDocument->m_app.p)->m_colorFormat;
				}

			// Only set property if all channels are valid
				if (red >= 0 && red <= 255 &&
					green >= 0 && green <= 255 &&
					blue >= 0 && blue <= 255 &&
					alpha >= 0 && alpha <= 255)
				{
					style->setProperty(m_colorEditing, MakeRGBString(colorFormat, red, green, blue, alpha), NULL);
				}
			}
		}
	}
	else
	{
		/*
		ASSERT(	m_colorRed >= 0 && m_colorRed <= 255 &&
						m_colorGreen >= 0 && m_colorGreen <= 255 &&
						m_colorBlue >= 0 && m_colorBlue <= 255);
						*/

	}

	CComBSTR defaultColor;

	if (nselected > 0)
	{
		// Set default color to color of first element selected

		CComPtr<IESelectedElement> selectedElement;
		GetSelectedElementN(0, &selectedElement);

		Element* eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<Web::Element> domElement;
		eElement->get_domElement(&domElement);

		CComQIPtr<ILElementCSSInlineStyle> stylable = domElement;
		if (stylable)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			stylable->get_style(&style);

			style->getPropertyValue(m_colorEditing, &defaultColor);
		}
	}
	else
	{
		// Set default color to currentColor (the inverse of SetCurrentSelectionCSSStyle())

		/*
		if (m_currentSelectionColorRed >= 0 && m_currentSelectionColorRed <= 255) m_pDocument->m_defaultColorRed = m_currentSelectionColorRed;
		if (m_currentSelectionColorGreen >= 0 && m_currentSelectionColorGreen <= 255) m_pDocument->m_defaultColorGreen = m_currentSelectionColorGreen;
		if (m_currentSelectionColorBlue >= 0 && m_currentSelectionColorBlue <= 255) m_pDocument->m_defaultColorBlue = m_currentSelectionColorBlue;

		if (	m_pDocument->m_defaultColorRed >= 0 && m_pDocument->m_defaultColorRed <= 255 &&
				m_pDocument->m_defaultColorGreen >= 0 && m_pDocument->m_defaultColorGreen <= 255 &&
				m_pDocument->m_defaultColorBlue >= 0 && m_pDocument->m_defaultColorBlue <= 255)
		{
			defaultColor = MakeRGBString(m_pDocument->m_defaultColorRed, m_pDocument->m_defaultColorGreen, m_pDocument->m_defaultColorBlue);
		}
		*/
		if (	m_currentSelectionColorRed >= 0 && m_currentSelectionColorRed <= 255 &&
				m_currentSelectionColorGreen >= 0 && m_currentSelectionColorGreen <= 255 &&
				m_currentSelectionColorBlue >= 0 && m_currentSelectionColorBlue <= 255)
		{
			defaultColor = MakeRGBString(1/*TODO*/, m_currentSelectionColorRed, m_currentSelectionColorGreen, m_currentSelectionColorBlue, m_currentSelectionColorAlpha);
		}
	}

	/*
	if (	m_pDocument->m_defaultColorRed >= 0 && m_pDocument->m_defaultColorRed <= 255 &&
			m_pDocument->m_defaultColorGreen >= 0 && m_pDocument->m_defaultColorGreen <= 255 &&
			m_pDocument->m_defaultColorBlue >= 0 && m_pDocument->m_defaultColorBlue <= 255)
			*/

	if (defaultColor.Length())
	{
		m_pDocument->m_defaultStyle->setProperty(m_colorEditing, defaultColor, NULL);
	}
	else
	{
		m_pDocument->m_defaultStyle->removeProperty(m_colorEditing, NULL);
	}
#endif
}

/*
ErrorCode CEXMLViewGroup::RGBAValue(long red, long green, long blue, long alpha)
{
}
*/

void CEXMLViewGroup::ApplyCurrentSelectionColor()
{
	ApplyCurrentSelectionColorToSelectedElements();

	m_currentSelectionStyle->removeProperty(m_colorEditing);
	SetCurrentSelectionCSSProperty(m_colorEditing);

#if 0
	SetCurrentSelectionCSSStyle();	// Not neccessary to set all ??
#endif

	ASSERT(0);
#if 0
	Fire_ColorChanged();
#endif
}

/*
ErrorCode CEXMLViewGroup::setRGBAValue(long red, long green, long blue, long alpha)
{
	m_currentSelectionColorRed = red;
	m_currentSelectionColorGreen = green;
	m_currentSelectionColorBlue = blue;
	m_currentSelectionColorAlpha = alpha;

	ApplyCurrentSelectionColor();

	return S_OK;
}
*/

// IEViewGroup

#if 0
ErrorCode CViewSheet::OnDetachTab(IUIDlgSite* pDlgSite/*, IUIDockBar* dockBar*/)
{
#if 0
	CComPtr<IUIDlg> dlg;
	pDlgSite->GetDlg(&dlg);

// Get the index
	for (int i = 0; i < m_pViewGroup->m_views.GetSize(); i++)
	{
		if (m_pViewGroup->m_views[i] == dlg)
			break;
	}

	CComQIPtr<ILXAddin> addin = static_cast<CLXMLEditorApp*>(m_pViewGroup->m_pDocument->m_app.p);
	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	CComQIPtr<IEFrame> pFrame = lxframe;

	CComPtr<IUIDlgSheet> sheet;
	static_cast<CLXMLEditorApp*>(m_pViewGroup->m_pDocument->m_app.p)->m_uiManager->CreateDlgSheet(NULL, &sheet);

	{
		CComPtr<IUIDlgSite> dlgsite;
		sheet->GetDlgSite(&dlgsite);
		dockBar->DockControlBar(dlgsite, NULL);
	}

	for (int i = 0; i < 1; i++)
	{
		sheet->AddDialog(pDlgSite);
	}
	//for (int

	//pFrame->FloatControlBar(

// Convert this view (for all viewgroups of all open xml documents) into a palette
#endif

//
	return S_OK;
}
#endif

void CEXMLViewGroup::DragOut(UI::CView* view, UI::CUIDockBar* dockBar)
{
	ASSERT(0);
#if 0
	CDocumentWorkspace* pWorkspace = &static_cast<CLXMLEditorApp*>(m_pDocument->m_app.p)->m_xmlDocumentWorkspace;

	CComQIPtr<ILXAddin> addin = static_cast<CLXMLEditorApp*>(m_pDocument->m_app.p);
	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	CViewDlg* pViewDlg = new CViewDlg;
	static_cast<CLXMLEditorApp*>(m_pDocument->m_app.p)->m_uiManager->CreateDlgSheet(NULL, NULL, &/*pViewSheet->m_*/pViewDlg->m_sheet);
	pViewDlg->m_sheet->ShowTabs(FALSE);

	if (view->m_ownerSheet)
	{
		view->m_ownerSheet->RemoveView(view);
	}
	pViewDlg->m_view = view;
	view->m_ownerSheet = pViewDlg;

	pWorkspace->m_viewDialogs.Add(pViewDlg);

	{
		CComPtr<IUIDlgSite> dlgsite;
		/*pViewSheet->m_*/pViewDlg->m_sheet->GetDlgSite(&dlgsite);
		dockBar->DockControlBar(dlgsite, NULL);
	}

	// Dock all views of all viewgroups of all documents
	for (int i = 0; i < m_pDocument->m_viewGroups.GetSize(); i++)
	{
		IUIDlg* dlg = m_pDocument->m_viewGroups[i]->m_views[pViewDlg->m_view->m_index];

		CComPtr<IUIDlgSite> dlgSite;
		dlg->GetDlgSite(&dlgSite);;

		m_pDocument->m_viewGroups[i]->m_dialogs.Add(dlg);

		CComQIPtr<IUIDockBar>(/*pViewSheet->m_*/pViewDlg->m_sheet)->DockControlBar(dlgSite, NULL);
	}
#endif
}

// CViewGroup
int CEXMLViewGroup::OnGroupActivate(bool bActivate)
{
	ASSERT(0);
#if 0
	CComQIPtr<IUIActiveManager> uiManager = m_pDocument->m_app;

	if (bActivate)
	{
	//	uiManager->ActivateObject(NULL, m_pDocument->GetUnknown());
	//	uiManager->ActivateObject(m_pDocument->GetUnknown(), GetUnknown());

	//	static_cast<CLXMLEditorApp*>(m_pDocument->m_app.p)->m_scriptsBar->Show(TRUE);
	//	static_cast<CLXMLEditorApp*>(m_pDocument->m_app.p)->m_cssPropertiesBar->Show(TRUE);

		CViewGroup::Activate(bActivate);
	}
	else //if (!bActivate)
	{
		CViewGroup::Activate(bActivate);

	//	static_cast<CLXMLEditorApp*>(m_pDocument->m_app.p)->m_scriptsBar->Show(FALSE);
	//	static_cast<CLXMLEditorApp*>(m_pDocument->m_app.p)->m_cssPropertiesBar->Show(FALSE);

	//	uiManager->DeactivateObject(GetUnknown());
	//	uiManager->DeactivateObject(m_pDocument->GetUnknown());
	}
#endif
	return Success;
}

// CViewGroup
int CEXMLViewGroup::OnGroupClose()
{
	ASSERT(0);
#if 0
	BOOL bClose = FALSE;

	if (m_pDocument->m_viewGroups.GetSize() == 1)
	{
		if (TRUE)	// modified
		{
			CString text;
			text.Format("Save changes to %S?", (BSTR)m_pDocument->m_pathName);

			UINT nID = MessageBox(NULL, text, "LXMLEditor", MB_YESNOCANCEL);
			if (nID == IDCANCEL)
				return S_FALSE;
			if (nID == IDYES)
			{
				//m_pDocument->Save();
			}

			bClose = TRUE;
		}
		else
		{
			bClose = TRUE;
		}
	}
	else
	{
		bClose = TRUE;
	}

	if (bClose)
	{
		m_pDocument->RemoveViewGroup(this);
	}
#endif

	return Success;
}

void CEXMLViewGroup::Close()
{
	ASSERT(0);
#if 0
	for (int i = m_sheets.GetSize()-1; i >= 0; i--)
	{
		CComPtr<IUIDlgSite> dlgSite;
		m_sheets[i]->m_sheet->GetDlgSite(&dlgSite);

		CComPtr<IUIDockBar> dockBar;
		dockBar = dlgSite->m_pDockBar;//GetDockBar(&dockBar);

		dockBar->RemoveControlBar(dlgSite);

		m_sheets[i]->Release();
	}
	m_sheets.RemoveAll();
#endif
}

#if 0
long CEXMLViewGroup::OnMDIActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	UI::Control* hwndChildDeact = (UI::Control*) wParam;        // child being deactivated 
	UI::Control* hwndChildAct = (UI::Control*) lParam;          // child being activated 

	UI::Control* hwnd;
	get_hwnd(&hwnd);

	bool bActivate = (hwnd == hwndChildAct);

	return 0;
}
#endif

void CEXMLViewGroup::SetDocument(CEXMLDocument* pDocument)
{
	m_pDocument = pDocument;

	MessageBeep(-1);//ASSERT(0);
#if 0
	CComPtr<ILDOMDocument> document;
	m_pDocument->get_DOMDocument(&document);
	CComQIPtr<ILDOMEventTarget> eventTarget = document;
	ASSERT(eventTarget != NULL);

// Capture
	eventTarget->addEventListener(L"onactivate", (ILDOMEventListener*)this, VARIANT_TRUE);
#endif
}

void CEXMLViewGroup::handleEvent(System::Event* evt)
{
	ASSERT(0);
#if 0
	CComBSTR type;
	evt->get_type(&type);

	if (!wcscmp(type, L"onactivate"))
	{
		CComQIPtr<ILDOMUIEvent> uievt = evt;

		CComPtr<ILDOMAbstractView> view;
		uievt->get_view(&view);
		// TODO, check that the view is in this viewgroup

		CComPtr<ILDOMEventTarget> target;
		uievt->get_target(&target);
		CComQIPtr<Web::Element> element = target;

		CComPtr<Element> eElement;
		m_pDocument->GetEElementFromDOMElement(element, &eElement);
		if (eElement)
		{
			ActivateElement(eElement, 0, NULL);
		}
	}
#endif
}

#if 0
//virtual
void CEXMLViewGroup::OnFinalMessage(UI::Control* /*hWnd*/)
{
	for (int i = m_pDocument->m_viewGroups.GetSize()-1; i >= 0; i--)
	{
		if (m_pDocument->m_viewGroups[i] == this)
		{
			m_pDocument->m_viewGroups.RemoveAt(i);

			CEXMLDocument* pDocument = m_pDocument;

			int refcount = Release();
			//ASSERT(refcount == 0);

			if (pDocument->m_viewGroups.GetSize() == 0)
			{
				pDocument->CloseDocument();
			}

			break;
		}
	}
}
#endif

#if 0
long CEXMLViewGroup::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (m_pDocument->m_viewGroups.GetSize() == 1)
	{
		CUString msg;
		_bstr_t pathName;

		if (m_pDocument->m_pathName.length())
			pathName = m_pDocument->m_pathName;
		else
			pathName = m_pDocument->m_fileTitle;

		msg.Format("Save changes to %S?", (BSTR)pathName);

		int id = ::MessageBox(GetMainHwnd(), msg, "WebEditor", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
		if (id == IDCANCEL) return 0;

		if (id == IDYES)
		{
			// TODO save
		}
	}

	long lResult;
	bHandled = baseClass::ProcessWindowMessage(m_hWnd, uMsg, wParam, lParam, lResult);
	return lResult;
}
#endif

/*
// IUIActivatable
ErrorCode CEXMLViewGroup::OnActivate(IUIActiveManager *uiManager)
{
	return S_OK;
}

ErrorCode CEXMLViewGroup::OnDeactivate(IUIActiveManager *uiManager)
{
//	static_cast<CLXMLEditorApp*>(m_pDocument->m_app.p)->m_scriptsBar->Show(FALSE);

	return S_OK;
}
*/

///////

CEDocument* CEXMLViewGroup::get_eDocument()
{
	return m_pDocument;
}

CEXMLDocument* CEXMLViewGroup::get_eXMLDocument()
{
	return m_pDocument;
}

ErrorCode CEXMLViewGroup::GetActiveSelectedElement(/*[out,retval]*/ IESelectedElement* *pVal)
{
	*pVal = m_pActiveElement;
//	if (*pVal) (*pVal)->AddRef();

	return Success;
}

void CEXMLViewGroup::UpdateTitles(int n)
{
	WCHAR str[512];
	if (n == -1)
		swprintf(str, L"%s", m_pDocument->m_fileTitle->c_str());
	else
		swprintf(str, L"%s:%d", m_pDocument->m_fileTitle->c_str(), n);

	if (m_pDocument->m_modified)
		wcscat(str, L" *");

	for (int i = 0; i < m_sheets.GetSize(); i++)
	{
		UI::CViewSheet* pViewSheet = m_sheets[i];

	;//	MessageBeep(-1);ASSERT(0);
#if 0
		ILXUIElement* parentNode;
		pViewSheet->m_sheet->get_parentNode(&parentNode);
#endif

		((UI::TextString*)pViewSheet->m_tabElement->m_pBorder->get_Content())->set_TextContent(new System::StringW(string_copy(str)));
	}

#if 0
	CUString title;
	title = (BSTR)m_pDocument->m_fileTitle;
	if (m_pDocument->m_modified)
		title += " *";
	SetWindowText(title);
#endif
}

void CEXMLViewGroup::RemoveElementAsTarget(IESelectedElement* pElement)
{
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		if (m_targetElements[i] == pElement)
		{
//			m_targetElements[i]->Release();
			m_targetElements.RemoveAt(i);
			return;
		}
	}
	ASSERT(0);
}

void CEXMLViewGroup::AddElementAsTarget(IESelectedElement* /*CElementImpl* */ selectedElement)
{
#ifdef _DEBUG
	{
		Element* eElement;
		selectedElement->get_eElement(&eElement);

		for (int i = 0; i < m_targetElements.GetSize(); i++)
		{
			IESelectedElement* selectedElement2 = m_targetElements[i];

			Element* eElement2;
			selectedElement2->get_eElement(&eElement2);

			if (eElement == eElement2)
			{
				ASSERT(0);
			}
		}
	}
#endif

//	selectedElement->AddRef();
	m_targetElements.Add(selectedElement);
}

ErrorCode CEXMLViewGroup::GetSelectedElement(Element* pElement, IESelectedElement* *pVal)
{
	*pVal = NULL;

	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		IESelectedElement* pSelectedElement = m_targetElements[i];

		Element* eElement;
		pSelectedElement->get_eElement(&eElement);

		if (eElement == pElement)
		{
			*pVal = pSelectedElement;
			//(*pVal)->AddRef();
		}
	}

	return Success;
}

void CEXMLViewGroup::DeselectElement(IESelectedElement* /*CElementImpl* */ pElement)
{
	ASSERT(0);
#if 0
	CComQIPtr<IUIManager> uiManager = gApp->m_frame;

	if (pElement == m_pActiveElement)
	{
		m_pActiveElement = NULL;
	}

	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		if (m_targetElements[i] == pElement)
		{
#if 0	// TODO remove
			uiManager->DeactivateObject(pElement);
#endif
			m_targetElements.RemoveAt(i);
			return;
		}
	}
#endif
}

void CEXMLViewGroup::DeselectAll()
{
	m_pActiveElement = NULL;

	for (int i = m_targetElements.GetSize()-1; i >= 0; i--)
	{
		IESelectedElement* pSelectedElement = m_targetElements[i];

//		pSelectedElement->Release();
		m_targetElements.RemoveAt(i);
	}
}

bool _extractFont(Web::Range* m_range, Web::ICSSStyleDeclaration* pTextFont, Web::Node* node, /*IDOMNode* parent,*/ int& hitStart)
{
	ASSERT(0);
#if 0
	CComPtr<Web::Node> m_startContainer;
	long m_startOffset;
	m_range->get_startContainer(&m_startContainer);
	m_range->get_startOffset(&m_startOffset);

	CComPtr<Web::Node> m_endContainer;
	long m_endOffset;
	m_range->get_endContainer(&m_endContainer);
	m_range->get_endOffset(&m_endOffset);

	CComPtr<ILDOMDocument> document;
	node->get_ownerDocument(&document);

	CComPtr<Web::NodeList> childNodes;
	node->get_childNodes(&childNodes);

	long nChildNodes;
	childNodes->get_length(&nChildNodes);

	int startOffset;
	int endOffset;

	if (node == m_startContainer)
	{
		hitStart = TRUE;
		startOffset = m_startOffset;
	}
	else
		startOffset = 0;

	if (node == m_endContainer)
	{
		endOffset = m_endOffset;
	}
	else
	{
		endOffset = nChildNodes;
	}

	for (int nchild = startOffset; nchild < endOffset; nchild++)
	{
		CComPtr<Web::Node> child;
		childNodes->item(nchild, &child);

		CComQIPtr<ILDOMCharacterData> text = child;
		if (text)
		{
			if (child == m_startContainer)
			{
				hitStart = TRUE;
			}

			if (child == m_endContainer)
			{
				return FALSE;
			}
		}
		else
		{
			CComQIPtr<Web::Element> element = child;

			bool bContinue = _extractFont(m_range, pTextFont, element, hitStart);

			if (hitStart)
			{
				CComQIPtr<ILElementCSSInlineStyle> stylable = element;
				if (stylable)
				{
					CComPtr<ILCSSStyleDeclaration> style2;
					stylable->get_style(&style2);

					for (int j = 0; j < g_nCSSProperties; j++)
					{
						CSSProperty* pProperty = &CSSProperties[j];

						if (pProperty->m_initialCSS != NULL)
						{
							CComBSTR value;
							pTextFont->getPropertyValue(pProperty->m_name, &value);

							CComBSTR value2;
							style2->getPropertyValue(pProperty->m_name, &value2);

							if ((BSTR)value == NULL)	// Not set
							{
								if (value2.Length())
								{
									pTextFont->setProperty(pProperty->m_name, value2, NULL);
								}
								/*
								if ((BSTR)value2 != NULL)
								{
									pTextFont->setProperty(pProperty->m_name, L"", NULL);
								}
								*/
							}
							else
							{
								if (value2.Length() > 0 && (value.Length() != value2.Length() ||
									wcscmp(value, value2)))
								{
									// The style is set, but the value differs between elements
									pTextFont->setProperty(pProperty->m_name, L"", NULL);
								}
							}
						}
					}
				}
				else	// element isn't CSS stylable
				{
					// Disable style editing all together
					//m_currentSelectionStyle.Release();
					pTextFont->set_cssText(L"");

					//j = g_nCSSProperties;
					//break;
				}

#if 0
				if (pTextFont->m_name.length())
				{
					_bstr_t fontname = _GetAttribute(element, L"font-family");
					if (wcscmp(fontname, pTextFont->m_name)) pTextFont->m_name = L"";
				}

				if (pTextFont->m_size != tomUndefined)
				{
					_bstr_t fontsize = _GetAttribute(element, L"font-size");
					if (atof(fontsize) != pTextFont->m_size) pTextFont->m_size = tomUndefined;
				}

				{
					Gdiplus::Font font(pTextFont->m_name, pTextFont->m_size);
					Gdiplus::FontFamily fontFamily;
					font.GetFamily(&fontFamily);
					int lineSpacing = fontFamily.GetLineSpacing(Gdiplus::FontStyleRegular);
					float lineSpacingPixel = font.GetSize() * lineSpacing / fontFamily.GetEmHeight(Gdiplus::FontStyleRegular);

					pTextFont->m_lineHeight = ConvertUserUnitToSpecifiedValue(lineSpacingPixel, UNIT_PT);
					/*
					if (pTextFont->m_lineHeight != tomUndefined)
					{
					}
					*/
				}

				if (pTextFont->m_appearance != NULL)
				{
					_bstr_t fillColor = _GetAttribute(element, L"fill-color");
					int r=0,g=0,b=0;
					sscanf(fillColor, "rgb(%d,%d,%d)", &r,&g,&b);

					CComObject<CPDBrush>* brush;
					CComObject<CPDBrush>::CreateInstance(&brush);
					brush->AddRef();
					CComPtr<IPDColor> color;
					brush->setColor(&color);
					color->setRGB(r,g,b);

					CPDObjectFill* p = (CPDObjectFill*)(IPDObjectFill*)pTextFont->m_subObjects->m_items[0];
					if (p->m_brush->IsEqual(brush) == S_FALSE)
					{
						pTextFont->m_subObjects->m_items.RemoveAll();	// TODO also release
						pTextFont->m_appearance->Release();
						pTextFont->m_appearance = NULL;
					}
				}
#endif
			}

			if (hitStart)
			{
			}

			if (!bContinue)
				return FALSE;
		}
	}

	if (node == m_endContainer)
	{
		return FALSE;
	}
#endif
	return true;
}

bool _setFont(Web::Node* m_startContainer, long m_startOffset, Web::Node* m_endContainer, long m_endOffset, Web::Range* m_range, Web::ICSSStyleDeclaration* pTextFont, Web::Node* node, /*IDOMNode* parent,*/ int& hitStart)
{
	ASSERT(0);
#if 0
	CComPtr<ILDOMDocument> document;
	node->get_ownerDocument(&document);

	LDOMNodeType nodeType;
	node->get_nodeType(&nodeType);

	if (nodeType == LNODE_ELEMENT)
	{
		CComPtr<Web::NodeList> childNodes;
		node->get_childNodes(&childNodes);

		long nChildNodes;
		childNodes->get_length(&nChildNodes);

		int startOffset;
		int endOffset;

		if (node == m_startContainer)
		{
			hitStart = TRUE;
			startOffset = m_startOffset;
		}
		else
			startOffset = 0;

		if (node == m_endContainer)
		{
			endOffset = m_endOffset;
		}
		else
		{
			endOffset = nChildNodes;
		}

		for (int nchild = startOffset; nchild < endOffset; nchild++)
		{
			CComPtr<Web::Node> child;
			childNodes->item(nchild, &child);

			//CComQIPtr<Web::Element> element = child;

			bool bContinue = _setFont(m_startContainer, m_startOffset, m_endContainer, m_endOffset, m_range, pTextFont, child, /*newElement,*/ hitStart);

			if (!bContinue)
				return FALSE;
		}

		if (node == m_endContainer)
		{
			return FALSE;
		}
	}
	else	// Text
	{
		CComQIPtr<ILDOMText> text = node;
		if (text)
		{
			CComPtr<Web::Node> parentNode;
			node->get_parentNode(&parentNode);

			CComPtr<Web::Node> before;
			if (text == m_endContainer)
			{
				CComPtr<ILDOMText> newText;
				text->splitText(m_endOffset, &newText);

				before = newText;
			}
			else
			{
				text->get_nextSibling(&before);
			}

			if (text == m_startContainer)
			{
				hitStart = TRUE;
			}

			if (hitStart)
			{
				CComPtr<Web::Element> styleElement;
				document->createElement(L"tspan", &styleElement);

				CComQIPtr<ILSVGStylable> stylable = styleElement;

				CComPtr<ILCSSStyleDeclaration> style;
				stylable->get_style(&style);

				/*
				if (pTextFont->m_name.length())
				{
					styleElement->setAttribute(L"font-family", pTextFont->m_name);
				}
				*/

				for (int j = 0; j < g_nCSSProperties; j++)
				{
					CSSProperty* pProperty = &CSSProperties[j];

					if (pProperty->m_initialCSS != NULL)
					{
						CComBSTR value;
						pTextFont->getPropertyValue(pProperty->m_name, &value);

						if (value.Length() > 0)	// defined
						{
							style->setProperty(pProperty->m_name, value, NULL/*priority*/);
						}
					}
				}

#if 0
				CComBSTR fontSize;
				pTextFont->getPropertyValue(L"font-size", &fontSize);

				if (fontSize.Length() > 0)	// defined
				{
					style->setProperty(L"font-size", fontSize, NULL/*priority*/);
				}
#endif

				CComPtr<ILDOMText> newText;
				text->splitText(m_startOffset, &newText);

				styleElement->appendChild(newText, NULL);

				//parent = styleElement;

				parentNode->insertBefore(styleElement, _variant_t(before), NULL);

				if (text == m_startContainer)
				{
					m_range->setStart(newText, 0);
				}

				if (text == m_endContainer)
				{
					int len = m_endOffset;
					if (text == m_startContainer) len -= m_startOffset;

					m_range->setEnd(newText, len);
				}
			}

			if (node == m_endContainer)
			{
				return FALSE;
			}
		}
	}
#endif
	return true;
}

// TODO, what does this bool return mean?
bool GetPropertyRGBColor(Web::ICSSStyleDeclaration* style, System::StringW* propertyName, double& red, double& green, double& blue, double& alpha)
{
	ASSERT(0);
#if 0
	red = -1;
	green = -1;
	blue = -1;
	alpha = -1;

	if (!wcscmp(propertyName, L"fill") || !wcscmp(propertyName, L"stroke"))
	{
		CComPtr<ILSVGPaint> svgPaint;
		style->getPropertyCSSValue(propertyName, (ILCSSValue**)&svgPaint);

		if (svgPaint)
		{
			LSVGPaintType paintType;
			svgPaint->get_paintType(&paintType);

			if (	paintType == SVG_PAINTTYPE_RGBCOLOR ||
					paintType == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR ||
					paintType == SVG_PAINTTYPE_URI_RGBCOLOR ||	// ??
					paintType == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)	// ??
			{
				LRGBColor rgbColor;
				svgPaint->get_rgbColor(&rgbColor);

				red = rgbColor.GetRed();
				green = rgbColor.GetGreen();
				blue = rgbColor.GetBlue();
				alpha = 255;
			}
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		CComPtr<ILCSSValue> cssvalue;
		style->getPropertyCSSValue(propertyName, &cssvalue);

		CComQIPtr<ILSVGColor> svgColor;
		CComQIPtr<ILCSSPrimitiveValue> primValue;

		if (svgColor = cssvalue)
		{
			LRGBColor rgbColor;
			svgColor->get_rgbColor(&rgbColor);

			red = rgbColor.GetRed();
			green = rgbColor.GetGreen();
			blue = rgbColor.GetBlue();
			alpha = 255;
		}
		else if (primValue = cssvalue)
		{
			LRGBColor rgbColor;
			primValue->getRGBColorValue(&rgbColor);

			if (rgbColor.m_rgbColor)	// Not valid if 'transparent' or 'currentColor'
			{
				red = rgbColor.GetRed();
				green = rgbColor.GetGreen();
				blue = rgbColor.GetBlue();

				rgbColor.m_rgbColor->get_alpha(&alpha);
				alpha *= 255;
			}
		}
		else
		{
			return FALSE;
		}
	}
#endif
	return true;
}

void CEXMLViewGroup::SetCurrentSelectionColor()
{
	ASSERT(0);
#if 0
	long ncount;
	GetSelectedCount(&ncount);

	if (ncount == 0)	// Set selection to same as default
	{
		GetPropertyRGBColor(m_pDocument->m_defaultStyle, m_colorEditing, m_currentSelectionColorRed, m_currentSelectionColorGreen, m_currentSelectionColorBlue, m_currentSelectionColorAlpha);
	}
	else
	{
		for (int i = 0; i < ncount; i++)
		{
			CComPtr<IESelectedElement> selectedElement;
			GetSelectedElementN(i, &selectedElement);

			Element* eElement;
			selectedElement->get_eElement(&eElement);

			CComPtr<Web::Element> domElement;
			eElement->get_domElement(&domElement);

			CComQIPtr<ILElementCSSInlineStyle> stylable = domElement;
			if (stylable)
			{
				CComPtr<ILCSSStyleDeclaration> style;
				stylable->get_style(&style);

				double red2;
				double green2;
				double blue2;
				double alpha2;

				if (GetPropertyRGBColor(style, m_colorEditing, red2, green2, blue2, alpha2))
				{
					if (i == 0)
					{
						m_currentSelectionColorRed = red2;
						m_currentSelectionColorGreen = green2;
						m_currentSelectionColorBlue = blue2;
						m_currentSelectionColorAlpha = alpha2;
					}
					else
					{
						if (m_currentSelectionColorRed != red2) m_currentSelectionColorRed = -1;
						if (m_currentSelectionColorGreen != green2) m_currentSelectionColorGreen = -1;
						if (m_currentSelectionColorBlue != blue2) m_currentSelectionColorBlue = -1;
						if (m_currentSelectionColorAlpha != alpha2) m_currentSelectionColorAlpha = -1;
					}
				}
				else
				{
					m_currentSelectionColorRed = -1;
					m_currentSelectionColorGreen = -1;
					m_currentSelectionColorBlue = -1;
					m_currentSelectionColorAlpha = -1;
					break;
				}
			}
		}
	}
#endif
}

bool CEXMLViewGroup::SetCurrentSelectionCSSProperty(System::StringW* propertyName)
{
	ASSERT(0);
#if 0
	long ncount;
	GetSelectedCount(&ncount);

	for (int i = 0; i < ncount; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		GetSelectedElementN(i, &selectedElement);

		CComPtr<Element> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<Web::Element> domElement;
		eElement->get_domElement(&domElement);

		CComQIPtr<ILElementCSSInlineStyle> stylable = domElement;
		if (stylable)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			stylable->get_style(&style);

			CComBSTR value2;
			style->getPropertyValue(propertyName, &value2);

			if (i == 0)	// first element
			{
				if ((BSTR)value2 != NULL)
				{
					m_currentSelectionStyle->setProperty(propertyName, value2, NULL);
				}
			}
			else
			{
				CComBSTR value;
				m_currentSelectionStyle->getPropertyValue(propertyName, &value);
				if (value2.Length() > 0 && (value.Length() != value2.Length() ||
					wcscmp(value, value2)))
				{
				//	m_currentSelectionStyle->removeProperty(pProperty->m_name, NULL);
					m_currentSelectionStyle->setProperty(propertyName, L"", NULL);
					break;
				}
			}
		}
		else	// element isn't CSS stylable
		{
			/*
			// Disable style editing all together
			m_currentSelectionStyle->set_cssText(L"");
			*/

			return FALSE;
			/*
			j = g_nCSSProperties;	// skip the rest of the properties
			break;
			*/
		}
	}
#endif
	return true;
}

void CEXMLViewGroup::SetCurrentSelectionCSSStyle()
{
	ASSERT(0);
#if 0
	CComPtr<ISVGTool> activeTool;
	m_pDocument->m_app->GetActiveTool(VARIANT_FALSE, &activeTool);

	long toolID = 0;
	if (activeTool)
	{
		m_pDocument->m_app->GetToolID(activeTool, &toolID);
	}

	if (toolID == ID_TOOL_TEXT && m_layoutView)
	{
		ASSERT(0);
#if 0
		ASSERT(m_layoutView);
		CComQIPtr<ILHTMLActiveView> view = m_layoutView->m_pIOleDocView;

		CComPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);

		CComPtr<Range> domrange;
		window->get_selection(&domrange);

		CComPtr<Web::Node> commonAncestor;
		domrange->get_commonAncestorContainer(&commonAncestor);

#if 0
		_bstr_t fontname = _GetAttribute(commonAncestor, L"font-family");
		pTextFont->m_name = fontname;

		_bstr_t fontsize = _GetAttribute(commonAncestor, L"font-size");
		pTextFont->m_size = atof(fontsize);

		{
			{
				Gdiplus::Font font(pTextFont->m_name, pTextFont->m_size);
				Gdiplus::FontFamily fontFamily;
				font.GetFamily(&fontFamily);
				int lineSpacing = fontFamily.GetLineSpacing(Gdiplus::FontStyleRegular);
				float lineSpacingPixel = pTextFont->m_size/*font.GetSize()*/ * lineSpacing / fontFamily.GetEmHeight(Gdiplus::FontStyleRegular);

				UINT descent = fontFamily.GetCellDescent(Gdiplus::FontStyleRegular);
				float descentPixel = font.GetSize() * descent / fontFamily.GetEmHeight(Gdiplus::FontStyleRegular);

			//	pTextFont->m_lineHeight = ConvertUserUnitToSpecifiedValue(lineSpacingPixel, UNIT_PT);
				pTextFont->m_lineHeight = lineSpacingPixel;

				pTextFont->m_lineHeight = pTextFont->m_size*120/100;
				/*
				if (pTextFont->m_lineHeight != tomUndefined)
				{
				}
				*/
			}

		//	if (pTextFont->m_appearance != NULL)
			{
				CComObject<CPDAppearance>::CreateInstance(&pTextFont->m_appearance);
				pTextFont->m_appearance->AddRef();

				CComObject<CPDObjectFill>* fill;
				CComObject<CPDObjectFill>::CreateInstance(&fill);
				fill->AddRef();
				pTextFont->m_subObjects->m_items.Add((IPDObjectFill*)fill);

				{
					CPDObjectFill* p = (CPDObjectFill*)(IPDObjectFill*)pTextFont->m_subObjects->m_items[0];

					_bstr_t fillColor = _GetAttribute(commonAncestor, L"fill-color");
					int r=0,g=0,b=0;
					sscanf(fillColor, "rgb(%d,%d,%d)", &r,&g,&b);

					CComObject<CPDBrush>* brush = p->m_brush;
					//CComObject<CPDBrush>::CreateInstance(&brush);
					//brush->AddRef();
					CComPtr<IPDColor> color;
					brush->setColor(&color);
					color->setRGB(r,g,b);

					/*
					if (p->m_brush->IsEqual(brush) == S_FALSE)
					{
						pTextFont->m_appearance->Release();
						pTextFont->m_appearance = NULL;
					}
					*/
				}
			}
		}
#endif

		if (commonAncestor == NULL)	// No selection ..hm..
		{
			CComBSTR cssText;
			m_pDocument->m_defaultStyle->get_cssText(&cssText);

			m_currentSelectionStyle->set_cssText(cssText);
		}
		else
		{
		// hm..
			CComQIPtr<ILDOMCharacterData> chardata = commonAncestor;
			if (chardata)
			{
				CComPtr<Web::Node> parentNode;
				commonAncestor->get_parentNode(&parentNode);
				commonAncestor = parentNode;
			}

			m_currentSelectionStyle->set_cssText(L"");

			{
				CComQIPtr<ILElementCSSInlineStyle> stylable = commonAncestor;
				if (stylable)
				{
					CComPtr<ILCSSStyleDeclaration> style2;
					stylable->get_style(&style2);

					long length;
					style2->get_length(&length);

					for (int i = 0; i < length; i++)
					{
						CComBSTR item;
						style2->item(i, &item);

						CComBSTR value;
						style2->getPropertyValue(item, &value);


						m_currentSelectionStyle->setProperty(item, value, NULL);
					}
				}
			}

			int hitStart = 0;
			_extractFont(domrange, m_currentSelectionStyle, commonAncestor, hitStart);
		}
#endif
	}
	else
	{
		long ncount;
		GetSelectedCount(&ncount);

		if (ncount == 0)	// Set selection to same as default
		{
			CComBSTR cssText;
			m_pDocument->m_defaultStyle->get_cssText(&cssText);

		//	CComPtr

			m_currentSelectionStyle->set_cssText(cssText);
		}
		else
		{
			m_currentSelectionStyle->set_cssText(L"");

			for (int j = 0; j < g_nCSSProperties; j++)
			{
				CSSProperty* pProperty = &CSSProperties[j];

				if (pProperty->m_initialCSS != NULL)
				{
					if (!SetCurrentSelectionCSSProperty(pProperty->m_name))
					{
						// Disable style editing all together
						m_currentSelectionStyle->set_cssText(L"");
						//j = g_nCSSProperties;
						break;
					}
				}
			}
		}

		SetCurrentSelectionColor();	// ??
	}

	Fire_SelectionStyleChanged();
#endif
}

/*
 Set(or remove) propertyName from the m_currentSelectionStyle
 to all selected elements
*/

void CEXMLViewGroup::ApplyCurrentSelectionCSSProperty(System::StringW* propertyName)
{
	ASSERT(0);
#if 0
	CComBSTR value;
	m_currentSelectionStyle->getPropertyValue(propertyName, &value);

	long nselected;
	GetSelectedCount(&nselected);

	for (int i = 0; i < nselected; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		GetSelectedElementN(i, &selectedElement);

		Element* eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<Web::Element> domElement;
		eElement->get_domElement(&domElement);

		CComQIPtr<ILElementCSSInlineStyle> stylable = domElement;
		if (stylable)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			stylable->get_style(&style);

			if ((BSTR)value == NULL)
			{
				style->removeProperty(propertyName, NULL);
			}
			else if (value.Length() == 0)
			{
				// Unchanged
			}
			else
			{
				style->setProperty(propertyName, value, NULL/*priority*/);
			}
		}
	}
#endif
}

// TODO ??
ErrorCode CEXMLViewGroup::ApplyCurrentSelectionCSSStyle()
{
	ASSERT(0);
#if 0
	CComPtr<IEXMLDocument> document;
	get_eXMLDocument(&document);

//	CComBSTR cssText;
//	static_cast<CEXMLDocument*>(document.p)->m_defaultStyle->get_cssText(&cssText);

#if 0	// TODO, this is necessary for something, need to call it elsewhere where it was
	// neccessary
	((CEXMLViewGroup*)viewGroup)->m_currentSelectionStyle->set_cssText(cssText);
#endif

	CComPtr<ISVGTool> activeTool;
	m_pDocument->m_app->GetActiveTool(VARIANT_FALSE, &activeTool);

	long toolID = 0;
	m_pDocument->m_app->GetToolID(activeTool, &toolID);

	if (toolID == ID_TOOL_TEXT)
	{
		ASSERT(m_layoutView);
		CComQIPtr<ILHTMLActiveView> view = m_layoutView->m_pIOleDocView;

		CComPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);

		CComPtr<Range> domrange;
		window->get_selection(&domrange);

		CComPtr<Web::Node> commonAncestor;
		domrange->get_commonAncestorContainer(&commonAncestor);

		CComPtr<Web::Node> startContainer;
		long startOffset;
		domrange->get_startContainer(&startContainer);
		domrange->get_startOffset(&startOffset);

		CComPtr<Web::Node> endContainer;
		long endOffset;
		domrange->get_endContainer(&endContainer);
		domrange->get_endOffset(&endOffset);

		if (commonAncestor && startContainer && endContainer)	// There's something selected
		{
			int hitStart = 0;
			_setFont(startContainer, startOffset, endContainer, endOffset, domrange, m_currentSelectionStyle, commonAncestor, hitStart);
		}
	}
	else
	{
		long nselected;
		GetSelectedCount(&nselected);

		for (int j = 0; j < g_nCSSProperties; j++)
		{
			CSSProperty* pProperty = &CSSProperties[j];

			if (pProperty->m_initialCSS != NULL)
			{
				ApplyCurrentSelectionCSSProperty(pProperty->m_name);
			}
		}

		if (nselected > 0)
		{
		// Set default style to style of first element selected

			CComPtr<Element> eElement;
			m_targetElements[0]->get_eElement(&eElement);

			CComPtr<Web::Element> domElement;
			eElement->get_domElement(&domElement);

			CComQIPtr<ILElementCSSInlineStyle> stylable = domElement;
			if (stylable)
			{
				CComPtr<ILCSSStyleDeclaration> style;
				stylable->get_style(&style);

				CComBSTR cssText;
				style->get_cssText(&cssText);

				m_pDocument->m_defaultStyle->set_cssText(cssText);
			}
		}
		else
		{
			// Set m_defaultStyle style to m_currentSelectionStyle (the inverse of SetCurrentSelectionCSSStyle())

			CComBSTR cssText;
			m_currentSelectionStyle->get_cssText(&cssText);

			m_pDocument->m_defaultStyle->set_cssText(cssText);
		}
	}

	Fire_SelectionStyleChanged();
#endif

	return Success;
}

ErrorCode CEXMLViewGroup::GetCurrentSelectionCSSStyle(Web::CSSStyleDeclaration* *pVal)
{
	*pVal = m_currentSelectionStyle;
	//if (*pVal) (*pVal)->AddRef();

	return Success;
}

IESelectedElement* CEXMLViewGroup::ActivateElement(/*[in]*/ Element* pElement, /*[in]*/ long nFlags)
{
	ASSERT(0);
	return NULL;
#if 0
	CComPtr<IESelectedElement> selectedElement;
	GetSelectedElement(pElement, &selectedElement);

	//bool bFirstActivated = m_targetElements.GetSize() == 0;

	if (m_pActiveElement)
	{
		CComPtr<Element> eElement;
		m_pActiveElement->get_eElement(&eElement);

		if (eElement == pElement)
		{
			if (pElement)
			{
#if 0	// Had this
				ASSERT(IsElementTarget(pElement));
#endif
			}

			if (pVal)
			{
				*pVal = m_pActiveElement;
				(*pVal)->AddRef();
			}

			return S_OK;
		}
	}

//	CComQIPtr<IUIManager> uiManager;// = gApp->m_frame;

	Fire_SelectionChanging();

	if (nFlags & MK_SHIFT)
	{
		if (pElement)
		{
		// Toggle selection of element

			if (selectedElement)	// Already selected, unselect
			{
				RemoveElementAsTarget(selectedElement);
				m_pActiveElement = NULL;
			}
			else	// Previously not selected, select
			{
				pElement->CreateSelectedElement(this, &selectedElement);
				if (selectedElement)
				{
					AddElementAsTarget(selectedElement);
					m_pActiveElement = selectedElement;
				}
			}
		}
	}
	else
	{
#if 0
		// Deselect all elements
		for (int i = 0; i < m_targetElements.GetSize(); i++)
		{
			CElementImpl* pElement = m_targetElements[i];

			BSTR tagName;
			pElement->m_domElement->get_nodeName(&tagName);

			if (!wcscmp(tagName, L"path"))
			{
				((CPathElement*)pElement)->m_selectedPoints.RemoveAll();
			}

			SysFreeString(tagName);
		}
#endif

		if (selectedElement)	// Previously selected
		{
		}
		else
		{
		//	m_targetElements.RemoveAll();	// TODO ??
			DeselectAll();

		//
			if (pElement)
			{
				pElement->CreateSelectedElement(this, &selectedElement);
				if (selectedElement)
				{
					AddElementAsTarget(selectedElement);
				}
			}
		}

		m_pActiveElement = selectedElement;
	}

//	Fire_domevent(NULL);

	{
	//	m_currentSelectionStyle.Release();
	//	m_currentSelectionStyle.CoCreateInstance(CLSID_LCSSStyleDeclaration);

		SetCurrentSelectionCSSStyle();
	}

	if (m_pActiveElement)
	{
		CComPtr<Element> eElement;
		m_pActiveElement->get_eElement(&eElement);

		CComPtr<Web::Element> domElement;
		eElement->get_domElement(&domElement);

		CComPtr<ILDOMDocument> xmldocument;
		m_pDocument->get_DOMDocument(&xmldocument);

		//if (m_bSelectingElement == 0)
		if (TRUE)
		{
		//	m_bSelectingElement++;

			CComQIPtr<ILDOMDocumentRange> documentRange = xmldocument;
			if (documentRange)
			{
				CComPtr<Range> range;
				documentRange->createRange(&range);
				if (range)
				{
					range->selectNode(domElement);

					for (int i = 0; i < m_views.GetSize(); i++)
					{
						CComQIPtr<ISourceView> sourceView = m_views[i];
						if (sourceView)
						{
							if (((CSourceView*)sourceView.p)->m_bSelectingElement == 0)
							{
								((CSourceView*)sourceView.p)->SetRange(range);
							}
						}
					}
				}
			}
		}

		/*
		{
			CSelectionItem* pSelectectionItem = new CSelectionItem;

			CComBSTR tagName;
			domElement->get_tagName(&tagName);

			pSelectectionItem->m_name = tagName;
			m_pSelectionHistory->AddChildTail(pSelectectionItem);
		}
  */
		if (TRUE/* TODO: uiManager->IsObjectActive(GetUnknown()) == S_OK*/)	// If this viewgroup is active
		{
			if (!(nFlags & MK_SHIFT)/*bFirstActivated*/)
			{
				// Copy the elements style to default style
				CComQIPtr<ILElementCSSInlineStyle> stylable = domElement;
				if (stylable)
				{
				// Set defaultStyle to the style of the activated element
				// TODO, take into account all selected elements ?

					CComPtr<ILCSSStyleDeclaration> style;
					stylable->get_style(&style);

					CComBSTR cssText;
					style->get_cssText(&cssText);

					m_pDocument->m_defaultStyle->set_cssText(cssText);

				// SVG
				// Update defaultColor/defaultGradient

					if (!wcscmp(m_colorEditing, L"stroke") || !wcscmp(m_colorEditing, L"fill"))
					{
						//_bstr_t propertyName = m_colorEditing;//(gApp->m_strokeOrFill == 0)? L"stroke": L"fill";

						CComPtr<ILSVGPaint> paint;
						m_pDocument->m_defaultStyle->getPropertyCSSValue(m_colorEditing/*propertyName*/, (ILCSSValue**)&paint);

						if (paint)
						{
							CComBSTR paintcssText;
							paint->get_cssText(&paintcssText);

							LSVGPaintType paintType;
							paint->get_paintType(&paintType);

							if (paintType == SVG_PAINTTYPE_RGBCOLOR ||
								paintType == SVG_PAINTTYPE_RGBCOLOR_ICCCOLOR)
							{
								m_pDocument->m_lastColor = paintcssText;

								/*
								CComPtr<ILRGBColor> rgbColor;
								paint->get_rgbColor(&rgbColor);

								CComPtr<ILCSSPrimitiveValue> cssred;
								rgbColor->get_red(&cssred);
								double red;
								cssred->getFloatValue(CSS_NUMBER, &red);

								CComPtr<ILCSSPrimitiveValue> cssgreen;
								rgbColor->get_green(&cssgreen);
								double green;
								cssgreen->getFloatValue(CSS_NUMBER, &green);

								CComPtr<ILCSSPrimitiveValue> cssblue;
								rgbColor->get_blue(&cssblue);
								double blue;
								cssblue->getFloatValue(CSS_NUMBER, &blue);

								m_colorRed = red;
								m_colorGreen = green;
								m_colorBlue = blue;
								*/
							}
							else if (paintType == SVG_PAINTTYPE_URI_NONE ||
										paintType == SVG_PAINTTYPE_URI_CURRENTCOLOR ||
										paintType == SVG_PAINTTYPE_URI_RGBCOLOR ||
										paintType == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
							{
								m_pDocument->m_lastGradient = paintcssText;
							}
							else if (paintType == SVG_PAINTTYPE_NONE)
							{
							}
							else if (paintType == SVG_PAINTTYPE_CURRENTCOLOR)
							{
								// TODO ?
							}
						}
						else
						{
						}
					}
				}
			}
		}
	}

	Fire_SelectionChanged();
	Fire_ColorChanged();	// ???

	if (pVal)
	{
		*pVal = selectedElement;
		if (*pVal) (*pVal)->AddRef();
	}
#endif
}

#if 0
void CEXMLViewGroup::ActivateElement(CElementImpl* pElement, UINT nFlags)
{
	bool bInvalidate = FALSE;

	if (m_pActiveSelection == pElement)
	{
		if (nFlags & MK_SHIFT)
		{
		// Deselect active element
			m_pActiveSelection->m_selected = FALSE;
			m_pActiveSelection = NULL;
//			m_domActiveElement = NULL;

			bInvalidate = TRUE;
		}
	}
	else
	{
		if (m_pActiveSelection)
		{
			if (pElement)
			{
				if ((m_pActiveSelection->m_parent != pElement->m_parent) || !(nFlags & MK_SHIFT))
				{
					((CElement*)m_pActiveSelection->m_parent)->DeselectAll();
				}
			}
			else
			{
				if (!(nFlags & MK_SHIFT))
				{
					((CElement*)m_pActiveSelection->m_parent)->DeselectAll();
				}
			}
		}

		m_pActiveSelection = pElement;
		/*
		if (m_pActiveSelection)
			m_domActiveElement = m_pActiveSelection->m_domElement;
		else
			m_domActiveElement = NULL;
			*/

		if (m_pActiveSelection)
		{
			m_pActiveSelection->m_selected = TRUE;
		}

		bInvalidate = TRUE;
	}

	if (bInvalidate)
	{
		Fire_domevent(NULL);

#if 0
		UpdateAllViews(NULL);

		if (gApp->m_pActiveDocument == this)
		{
			gApp->SetDialogsElement();
		}
#endif
	}
}
#endif

long CEXMLViewGroup::GetSelectedCount() const
{
	return m_targetElements.GetSize();
}

IESelectedElement* CEXMLViewGroup::GetSelectedElementN(long n)
{
	if (n >= 0 && n < m_targetElements.GetSize())
	{
		return m_targetElements[n];
	}
	else
	{
		return NULL;
	}
}

#if 0
// ICommandTarget
ErrorCode CEXMLViewGroup::OnCmdMsg(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, bool * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try document
	CComQIPtr<ICommandTarget> target = m_pDocument;
	target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	return S_OK;
}
#endif

BEGIN_CMD_MAP(CEXMLViewGroup)
#if 0
// File
	CMD_HANDLER(ID_FILE_PLACE, OnFilePlace)
//
	CMD_HANDLER(ID_WINDOW_NEWWINDOWONACTIVEELEMENT, OnNewWindowOnActiveElement)
	CMD_HANDLER(ID_WINDOW_SPLIT, OnWindowSplit)

// Edit
	CMD_HANDLER(ID_EDIT_DESELECT, OnDeselectAll)

// Insert
	CMD_HANDLER(ID_INSERT_FOREIGNOBJECT, OnInsertForeignObject)
	CMD_HANDLER(ID_INSERT_VIDEO, OnInsertVideo)
	CMD_HANDLER(ID_INSERT_AUDIO, OnInsertAudio)
	CMD_HANDLER(ID_SVGOBJECTS_NEWVIEWPORT, OnNewViewport)
	CMD_HANDLER(ID_INSERT_SWITCH, OnNewSwitch)

//	CMD_HANDLER(ID_INSERT_ANIMATECOLOR, OnInsertAnimateColor)
	CMD_HANDLER(ID_SMIL_INSERT_VIDEO, OnSmilInsertVideo)

// Object

	CMD_HANDLER(ID_OBJECT_GROUP, OnObjectGroup)
	CMD_UPDATEUI(ID_OBJECT_GROUP, OnObjectGroupUpdate)
	CMD_HANDLER(ID_OBJECT_UNGROUP, OnObjectUngroup)
	CMD_UPDATEUI(ID_OBJECT_UNGROUP, OnObjectUngroupUpdate)

	CMD_HANDLER(ID_OBJECT_COMPOUNDPATH_MAKE, OnObjectCompoundPathMake)
	CMD_UPDATEUI(ID_OBJECT_COMPOUNDPATH_MAKE, OnObjectCompoundPathMakeUpdate)
	CMD_HANDLER(ID_OBJECT_COMPOUNDPATH_RELEASE, OnObjectCompoundPathRelease)
	CMD_UPDATEUI(ID_OBJECT_COMPOUNDPATH_RELEASE, OnObjectCompoundPathReleaseUpdate)

	CMD_HANDLER(ID_OBJECT_TRANSFORM_CLEAR, OnObjectTransformClear)
	CMD_UPDATEUI(ID_OBJECT_TRANSFORM_CLEAR, OnObjectTransformClearUpdate)
	CMD_HANDLER(ID_OBJECT_TRANSFORM_CONSOLIDATE, OnObjectTransformConsolidate)
	CMD_UPDATEUI(ID_OBJECT_TRANSFORM_CONSOLIDATE, OnObjectTransformConsolidateUpdate)

	CMD_HANDLER(ID_OBJECT_ARRANGE_BRINGTOFRONT, OnObjectArrangeFront)
	CMD_HANDLER(ID_OBJECT_ARRANGE_SENDTOBACK, OnObjectArrangeBack)
	CMD_HANDLER(ID_OBJECT_ARRANGE_BRINGFORWARD, OnObjectArrangeForward)
	CMD_HANDLER(ID_OBJECT_ARRANGE_SENDBACKWARD, OnObjectArrangeBackward)

	CMD_UPDATEUI(ID_OBJECT_ARRANGE_BRINGTOFRONT, OnObjectArrangeHigherUpdate)
	CMD_UPDATEUI(ID_OBJECT_ARRANGE_SENDTOBACK, OnObjectArrangeLowerUpdate)
	CMD_UPDATEUI(ID_OBJECT_ARRANGE_BRINGFORWARD, OnObjectArrangeHigherUpdate)
	CMD_UPDATEUI(ID_OBJECT_ARRANGE_SENDBACKWARD, OnObjectArrangeLowerUpdate)

	CMD_HANDLER(ID_SELECT_BACK, OnSelectBack)

// Window
	CMD_HANDLER(ID_WINDOW_NEW, OnWindowNew)
#endif
END_CMD_MAP()

#if 0
void CEXMLDocument::NewWindow()
{
	ShowViews(NULL);
#if 0
	CComObject<CWebXMLViewGroup>* viewGroup;
	CComObject<CWebXMLViewGroup>::CreateInstance(&viewGroup);
	if (viewGroup)
	{
		viewGroup->AddRef();

		viewGroup->SetDocument(this);
		m_xmldocument->get_documentElement(&viewGroup->m_outerElement);

		// Add a source text bookmark on the viewgroup's outerElement, so that when the source
		// text is changed and the DOM is reparsed, we can find back to the DOM outerElement
		if (viewGroup->m_outerElement)
		{
			long startOffset;
			viewGroup->m_outerElement->getTextOffset(0, &startOffset);

			long endOffset;
			viewGroup->m_outerElement->getTextOffset(2, &endOffset);

			addBookmark(NULL, startOffset, endOffset-startOffset, &viewGroup->m_outerElementTextBookmark);
		}

		m_viewGroups.Add(viewGroup);

		gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&viewGroup->m_spFrame);

	//	CComObject<CUIMDIChild>* child;
	//	CComObject<CUIMDIChild>::CreateInstance(&child);
	//	child->AddRef();
	//	gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

		CComObject<CWebXMLViewGroup>* child = viewGroup;

		CComPtr<Web::Element> documentElement;
		m_xmldocument->get_documentElement(&documentElement);

		if (documentElement)
		{
			CComBSTR nsURI;
			documentElement->get_namespaceURI(&nsURI);

			if (!wcscmp(nsURI, L"http://www.w3.org/1999/XSL/Transform"))
			{
			// XSL Templates
				CComObject<CXSLTTemplatesDlg>* templatesView;
				CComObject<CXSLTTemplatesDlg>::CreateInstance(&templatesView);
				if (templatesView)
				{
					gApp->m_frame->FindMenu(IDR_XSLTEMPLATESVIEW, &templatesView->m_menu);
					templatesView->m_document = this;
					templatesView->m_viewGroup = viewGroup;
					viewGroup->m_views.Add(templatesView);

					child->AddPage(templatesView, NULL);

					viewGroup->m_splitx = 160;
				}
			}
		}

		{
		// Layout
			CComObject<CSvgLayoutView>* layoutView;
			CComObject<CSvgLayoutView>::CreateInstance(&layoutView);
			if (layoutView)
			{
				gApp->m_frame->FindMenu(IDR_XMLLAYOUTVIEW, &layoutView->m_menu);
				layoutView->m_document = this;

				layoutView->m_viewGroup = viewGroup;
				viewGroup->m_views.Add(layoutView);

				viewGroup->m_layoutView = layoutView;

				child->AddPage(layoutView, NULL);
			}

		// Source
			CComObject<CSourceView>* sourceView;
			CComObject<CSourceView>::CreateInstance(&sourceView);
			if (sourceView)
			{
				gApp->m_frame->FindMenu(IDR_XMLSOURCEVIEW, &sourceView->m_menu);
				sourceView->m_document = this;

				sourceView->m_viewGroup = viewGroup;
				viewGroup->m_views.Add(sourceView);

				child->AddPage(sourceView, NULL);
			}

//#if 0
		// GridView
			CComObject<CXMLGridView>* xmlgridView;
			CComObject<CXMLGridView>::CreateInstance(&xmlgridView);
			if (xmlgridView)
			{
				gApp->m_frame->FindMenu(IDR_XMLGRIDVIEW, &xmlgridView->m_menu);
				xmlgridView->m_document = this;

				xmlgridView->m_viewGroup = viewGroup;
				viewGroup->m_views.Add(xmlgridView);

				child->AddPage(xmlgridView, NULL);
			}
//#endif

		// FramesDesign
			CComObject<CHTMLFramesDesignView>* framesDesignView;
			CComObject<CHTMLFramesDesignView>::CreateInstance(&framesDesignView);
			if (framesDesignView)
			{
				gApp->m_frame->FindMenu(IDR_FRAMESDESIGNVIEW, &framesDesignView->m_menu);
				framesDesignView->m_document = this;

				framesDesignView->m_viewGroup = viewGroup;
				viewGroup->m_views.Add(framesDesignView);

				child->AddPage(framesDesignView, NULL);
			}

			CComQIPtr<ILDocumentStyle> documentStyle = m_xmldocument;
			if (documentStyle)
			{
				CComObject<CCSSStyleSheetView>* cssView;
				CComObject<CCSSStyleSheetView>::CreateInstance(&cssView);
				if (cssView)
				{
					cssView->m_viewGroup = viewGroup;

					CComPtr<ILStyleSheetList> styleSheetList;
					documentStyle->get_styleSheets(&styleSheetList);

					gApp->m_frame->FindMenu(IDR_CSSSTYLESHEETVIEW, &cssView->m_menu);
					cssView->m_styleSheetList = styleSheetList;
					child->AddPage(cssView, NULL);
				}
			}
#if 0
		// SMIL Layout regions
			CComObject<CSmilRegionsView>* pSMILRegionsView;
			CComObject<CSmilRegionsView>::CreateInstance(&pSMILRegionsView);
			if (pSMILRegionsView)
			{
				//gApp->m_frame->FindMenu(IDR_FRAMESDESIGNVIEW, &pSMILRegionsView->m_menu);
				//pSMILRegionsView->m_document = this;
				//pSMILRegionsView->

				pSMILRegionsView->m_viewGroup = viewGroup;
				viewGroup->m_views.Add(pSMILRegionsView);

				child->AddPage(pSMILRegionsView, NULL);
			}

		// SMIL/HTML TimeGraph
			CComObject<CSmilTimeGraphView>* pTimeGraphView;
			CComObject<CSmilTimeGraphView>::CreateInstance(&pTimeGraphView);
			if (pTimeGraphView)
			{
				gApp->m_frame->FindMenu(IDR_TIMEGRAPHVIEW, &pTimeGraphView->m_menu);
				pTimeGraphView->m_document = this;

				pTimeGraphView->m_viewGroup = viewGroup;
				viewGroup->m_views.Add(pTimeGraphView);

				child->AddPage(pTimeGraphView, NULL);
			}

		// Schema Diagram
			CComObject<CSchemaDiagramView>* pSchemaDiagramView;
			CComObject<CSchemaDiagramView>::CreateInstance(&pSchemaDiagramView);
			if (pSchemaDiagramView)
			{
				gApp->m_frame->FindMenu(IDR_SCHEMAVIEW, &pSchemaDiagramView->m_menu);
				pSchemaDiagramView->m_viewGroup = viewGroup;
				pSchemaDiagramView->m_asModel = m_schemaModel;
				viewGroup->m_views.Add(pSchemaDiagramView);

				child->AddPage(pSchemaDiagramView, NULL);
			}

		// Preview
			CComObject<CWebPreviewView>* previewView;
			CComObject<CWebPreviewView>::CreateInstance(&previewView);
			if (previewView)
			{
				gApp->m_frame->FindMenu(IDR_XMLPREVIEWVIEW, &previewView->m_menu);
				previewView->m_document = this;

				previewView->m_viewGroup = viewGroup;
				viewGroup->m_views.Add(previewView);

				child->AddPage(previewView, NULL);
			}
#endif
		}

		child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);

		child->UpdateFrameTitle();
	}
#endif
}
#endif

long CEXMLViewGroup::OnNewSwitch(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<Web::Element> parentNode;
	CComPtr<Web::Node> beforeNode;

	GetNewElementInsertionAt(this, &parentNode, &beforeNode);
	if (parentNode)
	{
		CComPtr<Element> eSVGElement;
		m_pDocument->createEElementNS(L"http://www.w3.org/2000/svg", L"switch", &eSVGElement);

		if (eSVGElement)
		{
			CComPtr<Web::Element> element;
			eSVGElement->get_domElement(&element);

			/*
			element->setAttribute(L"x", L"0");
			element->setAttribute(L"y", L"0");
			element->setAttribute(L"width", L"100%");
			element->setAttribute(L"height", L"100%");
			*/

			parentNode->insertBefore(element, CComVariant(beforeNode), NULL);
		}
	}
	else
	{
		MessageBox(NULL, "Select an appropriate insertion point", "LXMLEditor", MB_OK);
	}
#endif
	return 0;
}

long CEXMLViewGroup::OnNewViewport(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<Web::Element> parentNode;
	CComPtr<Web::Node> beforeNode;
	GetNewElementInsertionAt(this, &parentNode, &beforeNode);

	if (parentNode)
	{
		CComPtr<Element> eSVGElement;
		m_pDocument->createEElementNS(L"http://www.w3.org/2000/svg", L"svg", &eSVGElement);

		if (eSVGElement)
		{
			CComPtr<Web::Element> element;
			eSVGElement->get_domElement(&element);

			element->setAttribute(L"x", L"0");
			element->setAttribute(L"y", L"0");
			element->setAttribute(L"width", L"100%");
			element->setAttribute(L"height", L"100%");

			parentNode->insertBefore(element, CComVariant(beforeNode), NULL);
		}
	}
	else
	{
		MessageBox(NULL, "Select an appropriate insertion point", "LXMLEditor", MB_OK);
	}
#endif
	return 0;
}

long CEXMLViewGroup::OnDeselectAll(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ActivateElement(NULL, 0);
	return 0;
}

long CEXMLViewGroup::OnWindowNew(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILXAddin> addin = m_pDocument->m_app;

	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	ASSERT(0);
#if 0

	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	CComQIPtr<IEFrame> eframe = lxframe;

	m_pDocument->ShowViews(eframe);
#endif
#endif
	return 0;
}

ErrorCode CEXMLViewGroup::ReferenceBack()
{
	m_activeReferencedElement = NULL;	// TODO, go back

	Element* eElement = m_activeReferenceElement;
	m_activeReferenceElement = NULL;
	ActivateElement(eElement, 0);

	return Success;
}

long CEXMLViewGroup::OnSelectBack(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ReferenceBack();

	return 0;
}

//#include "WEUndoNewElement.h"
//#include "UndoParent.h"

long CEXMLViewGroup::OnObjectTransformClear(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComPtr<Element> eElement;
		m_targetElements[i]->get_eElement(&eElement);

		CComPtr<Web::Element> domElement;
		eElement->get_domElement(&domElement);

		CComQIPtr<ILSVGTransformable> transformable = domElement;
		if (transformable)
		{
		// hm... 
			domElement->removeAttribute(L"transform");
		}
	}
#endif
	return 0;
}

void CEXMLViewGroup::OnObjectTransformClearUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	bool bEnable = FALSE;

	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComPtr<Element> eElement;
		m_targetElements[i]->get_eElement(&eElement);

		CComPtr<Web::Element> domElement;
		eElement->get_domElement(&domElement);

		CComQIPtr<ILSVGTransformable> transformable = domElement;
		if (transformable)
		{
			VARIANT_bool bHasTransform;
			domElement->hasAttribute(L"transform", &bHasTransform);
			if (bHasTransform)
			{
				bEnable = TRUE;
				break;
			}
		}
	}

	pCmdUI->Enable(bEnable);
#endif
}

long CEXMLViewGroup::OnObjectTransformConsolidate(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComPtr<Element> eElement;
		m_targetElements[i]->get_eElement(&eElement);

		CComPtr<Web::Element> domElement;
		eElement->get_domElement(&domElement);

		CComQIPtr<ILSVGTransformable> transformable = domElement;
		if (transformable)
		{
			CComPtr<ILSVGAnimatedTransformList>  atransformlist;
			transformable->get_transform(&atransformlist);

			CComPtr<ILSVGTransformList> basetransformlist;
			atransformlist->get_baseVal(&basetransformlist);

			CComPtr<ILSVGTransform> transform;
			basetransformlist->consolidate(&transform);
		}
	}
#endif
	return 0;
}

void CEXMLViewGroup::OnObjectTransformConsolidateUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	bool bEnable = FALSE;

	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComPtr<Element> eElement;
		m_targetElements[i]->get_eElement(&eElement);

		CComPtr<Web::Element> domElement;
		eElement->get_domElement(&domElement);

		CComQIPtr<ILSVGTransformable> transformable = domElement;
		if (transformable)
		{
			CComPtr<ILSVGAnimatedTransformList>  atransformlist;
			transformable->get_transform(&atransformlist);

			CComPtr<ILSVGTransformList> basetransformlist;
			atransformlist->get_baseVal(&basetransformlist);

			long numberOfItems;
			basetransformlist->get_numberOfItems(&numberOfItems);
			if (numberOfItems > 1)
			{
				bEnable = TRUE;
				break;
			}
		}
	}

	pCmdUI->Enable(bEnable);
#endif
}

long CEXMLViewGroup::OnInsertForeignObject(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	m_pDocument->m_app->SetActiveToolByID(ID_SVGTOOL_FOREIGNOBJECT);

	CComPtr<ISVGTool> tool;
	m_pDocument->m_app->GetActiveTool(VARIANT_FALSE, &tool);

	CComPtr<ILDOMDocument> document;
	m_pDocument->get_DOMDocument(&document);

	CComPtr<Element> eElement;
	m_pDocument->createEElementNS(L"http://www.w3.org/2000/svg", L"foreignObject", &eElement);

	CComPtr<Web::Element> element;
	eElement->get_domElement(&element);
	if (element)
	{
		CComPtr<Web::Element> topElement;
		document->createElementNS(L"http://www.w3.org/1999/xhtml", L"p", &topElement);
		if (topElement)
		{
			topElement->setAttribute(L"xmlns", L"http://www.w3.org/1999/xhtml");

			CComPtr<ILDOMText> textNode;
			document->createTextNode(L"Type here", &textNode);

			topElement->appendChild(textNode, NULL);
		}

		element->appendChild(topElement, NULL);
	}

	static_cast<CBasicShapeTool*>(tool.p)->m_elementToPlace = CComQIPtr<IESVGElement>(eElement);
#endif
	return 0;
}

long CEXMLViewGroup::OnFilePlace(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILXAddin> addin = m_pDocument->m_app;
	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	UI::Control* hWnd;
	CComQIPtr<IUIWnd> wnd = lxframe;
	wnd->get_hwnd(&hWnd);

	static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
												"All Images (*.png;*.jpg;*.jpeg;*.gif;*.svg)\0*.png;*.jpg;*.jpeg;*.gif;*.svg\0"
												"JPEG (*.jpeg;*.jpg)\0*.jpeg;*.jpg\0"
												"PNG (*.png)\0*.png\0"
												"GIF (*.gif)\0*.gif\0"
												"SVG (*.svg)\0*.svg\0"
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
		TCHAR* filename = sbuffer;//[256];
		//_splitpath(sbuffer, NULL, NULL, filename, NULL);


		CComPtr<ILDOMDocument> document;
		m_pDocument->get_DOMDocument(&document);

		CComPtr<Web::Element> documentElement;
		document->get_documentElement(&documentElement);

		CComPtr<Element> erootElement;
		m_pDocument->GetEElementFromDOMElement(documentElement, &erootElement);

		CComPtr<Element> eimageElement;
		m_pDocument->createEElementNS(L"http://www.w3.org/2000/svg", L"image", &eimageElement);

		CComPtr<Web::Element> domElement;
		eimageElement->get_domElement(&domElement);

		domElement->setAttributeNS(L"http://www.w3.org/1999/xlink", L"href", _bstr_t(filename));
		domElement->setAttribute(L"x", _bstr_t(_variant_t(long(0))));
		domElement->setAttribute(L"y", _bstr_t(_variant_t(long(0))));
		domElement->setAttribute(L"width", _bstr_t(_variant_t(long(100))));
		domElement->setAttribute(L"height", _bstr_t(_variant_t(long(100))));

		erootElement->appendChild(eimageElement);

		ActivateElement(eimageElement, 0, NULL);
	}
#endif

	return 0;
}

static LPCTSTR VideoFilesFilter = _T(	"All Files\0*.*\0"
											"All Video (*.mpg;*.mpeg;*.fli;*.flc;*.gif;*.iff)\0*.mpg;*.mpeg;*.flc;*.fli;*.gif;*.iff\0"
											"MPEG (*.mpg;*.mpeg)\0*.mpg;*.mpeg\0"
											"Flic (*.fli;*.flc)\0*.fli;*.flc\0"
											"GIF (*.gif)\0*.gif\0"
											"IFF (*.iff)\0*.iff\0"
											);

long CEXMLViewGroup::OnInsertVideo(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILXAddin> addin = m_pDocument->m_app;
	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	UI::Control* hWnd;
	CComQIPtr<IUIWnd> wnd = lxframe;
	wnd->get_hwnd(&hWnd);

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
	ofn.lpstrFilter = VideoFilesFilter;
	ofn.nFilterIndex = 2;

	if (GetOpenFileName(&ofn))
	{
		TCHAR* filename = sbuffer;//[256];
		//_splitpath(sbuffer, NULL, NULL, filename, NULL);


		/*
		CComPtr<ILDOMDocument> document;
		m_pDocument->get_DOMDocument(&document);

		CComPtr<Web::Element> documentElement;
		document->get_documentElement(&documentElement);
		*/

	//	CComPtr<Element> erootElement;
	//	m_pDocument->GetEElementFromDOMElement(documentElement, &erootElement);

		CComPtr<Element> eimageElement;
		m_pDocument->createEElementNS(L"http://www.w3.org/2000/svg", L"video", &eimageElement);
		if (eimageElement)
		{
			CComPtr<Web::Element> domElement;
			eimageElement->get_domElement(&domElement);

			domElement->setAttributeNS(L"http://www.w3.org/1999/xlink", L"href", _bstr_t(filename));
			/*
			domElement->setAttribute(L"x", _bstr_t(_variant_t(long(0))));
			domElement->setAttribute(L"y", _bstr_t(_variant_t(long(0))));
			domElement->setAttribute(L"width", _bstr_t(_variant_t(long(100))));
			domElement->setAttribute(L"height", _bstr_t(_variant_t(long(100))));
			*/


			domElement->setAttribute(L"begin", L"20");
			domElement->setAttribute(L"clipBegin", L"5");
			//domElement->setAttribute(L"clipEnd", L"20");

			{
				m_pDocument->m_app->SetActiveToolByID(ID_SVGTOOL_FOREIGNOBJECT);

				CComPtr<ISVGTool> tool;
				m_pDocument->m_app->GetActiveTool(VARIANT_FALSE, &tool);

				static_cast<CBasicShapeTool*>(tool.p)->m_elementToPlace = CComQIPtr<IESVGElement>(eimageElement);
			}
		}

	//	erootElement->appendChild(eimageElement);

	//	ActivateElement(eimageElement, 0, NULL);
	}
#endif

	return 0;
}

long CEXMLViewGroup::OnInsertAudio(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILXAddin> addin = m_pDocument->m_app;
	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	UI::Control* hWnd;
	CComQIPtr<IUIWnd> wnd = lxframe;
	wnd->get_hwnd(&hWnd);

	static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
												"All Audio (*.wav;*.aif;*.aiff;*.au;*.voc;*.iff)\0*.wav;*.aif;*.aiff;*.au;*.voc;*.iff\0"
												"WAV (*.wav)\0*.wav\0"
												"AIFF (*.aif;*.aiff)\0*.aif;*.aiff\0"
												"Sun AU (*.au)\0*.au\0"
												"VOC (*.voc)\0*.voc\0"
												"IFF (*.iff)\0*.iff\0"
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
		TCHAR* filename = sbuffer;//[256];
		//_splitpath(sbuffer, NULL, NULL, filename, NULL);


		CComPtr<ILDOMDocument> document;
		m_pDocument->get_DOMDocument(&document);

		CComPtr<Web::Element> documentElement;
		document->get_documentElement(&documentElement);

		CComPtr<Element> erootElement;
		m_pDocument->GetEElementFromDOMElement(documentElement, &erootElement);

		CComPtr<Element> eimageElement;
		m_pDocument->createEElementNS(L"http://www.w3.org/2000/svg", L"audio", &eimageElement);

		CComPtr<Web::Element> domElement;
		eimageElement->get_domElement(&domElement);

		domElement->setAttributeNS(L"http://www.w3.org/1999/xlink", L"href", _bstr_t(filename));
		/*
		domElement->setAttribute(L"x", _bstr_t(_variant_t(long(0))));
		domElement->setAttribute(L"y", _bstr_t(_variant_t(long(0))));
		domElement->setAttribute(L"width", _bstr_t(_variant_t(long(100))));
		domElement->setAttribute(L"height", _bstr_t(_variant_t(long(100))));
		*/

		erootElement->appendChild(eimageElement);

		ActivateElement(eimageElement, 0, NULL);
	}
#endif

	return 0;
}

long CEXMLViewGroup::OnSmilInsertVideo(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	if (m_svgActiveContainer)
	{
		CComQIPtr<ILXAddin> addin = m_pDocument->m_app;
		CComPtr<ILXAddinSite> addinSite;
		addin->GetSite(&addinSite);

		CComPtr<ILXFrameworkFrame> lxframe;
		addinSite->GetFrame(&lxframe);

		UI::Control* hWnd;
		CComQIPtr<IUIWnd> wnd = lxframe;
		wnd->get_hwnd(&hWnd);

		TCHAR sbuffer[4096];
		strcpy(sbuffer, "");	// Initial filename
		
		TCHAR curdir[MAX_PATH];
		GetCurrentDirectory(sizeof(curdir), curdir);

		OPENFILENAME ofn = {0};
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.hInstance = _Module.m_hInst;
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
		ofn.lpstrFile = sbuffer;
		ofn.nMaxFile = sizeof(sbuffer);
		ofn.lpstrInitialDir = curdir;
		ofn.lpstrFilter = VideoFilesFilter;
		ofn.nFilterIndex = 2;

		if (GetOpenFileName(&ofn))
		{
			TCHAR* filename = sbuffer;//[256];
			//_splitpath(sbuffer, NULL, NULL, filename, NULL);


			/*
			CComPtr<ILDOMDocument> document;
			m_pDocument->get_DOMDocument(&document);

			CComPtr<Web::Element> documentElement;
			document->get_documentElement(&documentElement);
			*/

		//	CComPtr<Element> erootElement;
		//	m_pDocument->GetEElementFromDOMElement(documentElement, &erootElement);

			CComPtr<Element> eimageElement;
			m_pDocument->createEElementNS(L"http://www.w3.org/2001/SMIL20/Language", L"video", &eimageElement);
			if (eimageElement)
			{
				CComPtr<Web::Element> regionElement;
				m_svgActiveContainer->get_domElement(&regionElement);

				CComBSTR regionId;
				regionElement->getAttribute(L"id", &regionId);

				CComPtr<Web::Element> domElement;
				eimageElement->get_domElement(&domElement);

				domElement->setAttribute(L"src", _bstr_t(filename));

				domElement->setAttribute(L"region", regionId);

				domElement->setAttribute(L"begin", L"20");	// TODO

				CComPtr<Web::Element> region;
				m_svgActiveContainer->get_domElement(&region);

				m_pActiveTimeGraphElement->m_parent->m_domElement->insertBefore(domElement, CComVariant(m_pActiveTimeGraphElement->m_domElement), NULL);

				/*
				{
					m_pDocument->m_app->SetActiveToolByID(ID_SVGTOOL_FOREIGNOBJECT);

					CComPtr<ISVGTool> tool;
					m_pDocument->m_app->GetActiveTool(VARIANT_FALSE, &tool);

					static_cast<CBasicShapeTool*>(tool.p)->m_elementToPlace = CComQIPtr<IESVGElement>(eimageElement);
				}
				*/
			}

		//	erootElement->appendChild(eimageElement);

		//	ActivateElement(eimageElement, 0, NULL);
		}
	}
#endif

	return 0;
}

#if 0
long CEXMLViewGroup::OnInsertAnimateColor(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	CComBSTR attributeType = L"XML";//m_attributes[m_index].m_attributeType;
	CComBSTR attributeName = L"backgroundColor";//m_attributes[m_index].m_attributeName;

	CComPtr<Web::Element> animationElement;

	document->createElement(L"animate", &animationElement);

	CComBSTR value;

	if (!wcscmp(attributeType, L"XML"))
	{
		element->getAttributeNS(namespaceURI, attributeName, &value);
	}
#if 0
	else
	{
		CComPtr<ILHTMLWindow> window;
		static_cast<CEXMLViewGroup*>(m_viewGroup.p)->m_layoutView->m_pBehavior->GetHTMLWindow(&window);

		CComQIPtr<ILDOMViewCSS> cssView = window;

		CComPtr<ILCSSStyleDeclaration> style;
		cssView->getComputedStyle(element, NULL, &style);

		style->getPropertyValue(attributeName, &value);
	}
#endif

	CComBSTR values;
	values = value;
	values += L";";
	values += value;

	animationElement->setAttribute(L"keyTimes", L"0;1");
	animationElement->setAttribute(L"values", values);

	animationElement->setAttribute(L"attributeType", attributeType);
	animationElement->setAttribute(L"attributeName", attributeName);

	animationElement->setAttribute(L"begin", L"0");
	animationElement->setAttribute(L"dur", L"60");

	m_pActiveTimeElement->m_parent->m_domElement->insertBefore(domElement, CComVariant(m_pActiveTimeElement->m_domElement), NULL);

	return 0;
}
#endif

void CEXMLViewGroup::GetCompoundPathTargetElements(Array<CESVGPathElement*>& layers)
{
	ASSERT(0);
#if 0
	if (m_pActiveElement)
	{
		CComPtr<Element> eElement;
		m_pActiveElement->get_eElement(&eElement);
		
		CComPtr<Web::Element> domElement;
		eElement->get_domElement(&domElement);

		CComPtr<Web::Node> parentNode;
		domElement->get_parentNode(&parentNode);

		CComPtr<Web::Node> child;
		parentNode->get_firstChild(&child);
		while (child)
		{
			CComQIPtr<Web::Element> domElement = child;
			if (domElement)
			{
				CComPtr<Element> eElement;
				m_pDocument->GetEElementFromDOMElement(domElement, &eElement);

				CComPtr<IESelectedElement> selected;
				GetSelectedElement(eElement, &selected);

				if (selected)
				{
					CComQIPtr<IESVGPathElement> path = eElement;
					if (path != NULL)
					{
						layers.Add(path);
					}
				}
			}

			CComPtr<Web::Node> nextSibling;
			child->get_nextSibling(&nextSibling);
			child = nextSibling;
		}
	}
#endif
}

long CEXMLViewGroup::OnObjectCompoundPathMake(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	if (m_pActiveElement)
	{
		CComPtr<Element> eElement;
		m_pActiveElement->get_eElement(&eElement);
		
		CComPtr<Web::Element> domElement;
		eElement->get_domElement(&domElement);

		CComPtr<Web::Node> parentNode;
		domElement->get_parentNode(&parentNode);

		CArray<IESVGPathElement*, IESVGPathElement*> layers;

		GetCompoundPathTargetElements(layers);

		if (layers.GetSize() >= 2)	// At least two objects must be selected
		{
			IESVGPathElement* pDestShape = layers[0];

			CComPtr<ILSVGPathElement> pathElement;
			pDestShape->get_domElement((Web::Element**)&pathElement);

			CComQIPtr<ILSVGAnimatedPathData> pathdata = pathElement;
			CComPtr<ILSVGPathSegList> destseglist;
			pathdata->get_pathSegList(&destseglist);

			destseglist->LockUpdate();

			for (int j = 1; j < layers.GetSize(); j++)
			{
				CComPtr<Web::Element> pathElement;
				layers[j]->get_domElement(&pathElement);

				CComQIPtr<ILSVGAnimatedPathData> pathdata = pathElement;
				CComPtr<ILSVGPathSegList> seglist;
				pathdata->get_pathSegList(&seglist);

				parentNode->removeChild(pathElement, NULL);

			//	CComPtr<IESVGPath> path;
			//	layers[j]->GetPath(&path);

				{
					long numberOfItems;
					seglist->get_numberOfItems(&numberOfItems);
					for (int i = 0; i < numberOfItems; i++)
					{
						CComPtr<ILSVGPathSeg> seg;
						seglist->getItem(0, &seg); // 0 since it gets removed from seglist

						destseglist->appendItem(seg, NULL);
					}
				}
			}

			destseglist->UnlockUpdate();
		}
	}
#endif
	return 0;
}

void CEXMLViewGroup::OnObjectCompoundPathMakeUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	Array<CESVGPathElement*> layers;

	GetCompoundPathTargetElements(layers);

	pCmdUI->Enable(layers.GetSize() >= 2);
}

long CEXMLViewGroup::OnObjectCompoundPathRelease(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	if (m_pActiveElement)
	{
		CComPtr<Element> eElement;
		m_pActiveElement->get_eElement(&eElement);

		CComQIPtr<IESVGPathElement> esvgElement = eElement;
		if (esvgElement)
		{
			CComPtr<Web::Element> element;
			esvgElement->get_domElement(&element);

			CComBSTR style;
			element->getAttribute(L"style", &style);

			CComBSTR transform;
			element->getAttribute(L"transform", &transform);

			CComPtr<Web::Node> parentNode;
			element->get_parentNode(&parentNode);

			CComPtr<Web::Node> nextSibling;
			element->get_nextSibling(&nextSibling);

			CComQIPtr<ILSVGAnimatedPathData> pathData = element;
			CComPtr<ILSVGPathSegList> seglist;
			pathData->get_pathSegList(&seglist);

			long numberOfItems;
			seglist->get_numberOfItems(&numberOfItems);

			seglist->LockUpdate();

			int i = 0;

		// Skip first subpath
			for (i = 1; i < numberOfItems; i++)
			{
				CComPtr<ILSVGPathSeg> seg;
				seglist->getItem(i, &seg);

				LSVGPathSegType segType;
				seg->get_pathSegType(&segType);

				if (segType == PATHSEG_MOVETO_ABS ||
					segType == PATHSEG_MOVETO_REL)
				{
					break;
				}
			}

			// Create <path> elements for remaining subpaths
			while (i < numberOfItems)
			{
#ifdef _DEBUG
				CComPtr<ILSVGPathSeg> seg;
				seglist->getItem(i, &seg);

				LSVGPathSegType segType;
				seg->get_pathSegType(&segType);

				ASSERT(segType == PATHSEG_MOVETO_ABS || segType == PATHSEG_MOVETO_REL);
#endif

				for (int j = i+1; j < numberOfItems; j++)
				{
					CComPtr<ILSVGPathSeg> seg;
					seglist->getItem(j, &seg);

					LSVGPathSegType segType;
					seg->get_pathSegType(&segType);

					if (segType == PATHSEG_MOVETO_ABS ||
						segType == PATHSEG_MOVETO_REL)
					{
						break;
					}
				}

				CComPtr<IESVGPathElement> ePathElement;
				m_pDocument->createEElementNS(L"http://www.w3.org/2000/svg", L"path", (Element**)&ePathElement);
				if (ePathElement)
				{
					CComPtr<Web::Element> element2;
					ePathElement->get_domElement(&element2);

					CComQIPtr<ILSVGAnimatedPathData> pathData = element2;
					CComPtr<ILSVGPathSegList> seglist2;
					pathData->get_pathSegList(&seglist2);

					seglist2->LockUpdate();

					for (int n = i; n < j; n++)
					{
						CComPtr<ILSVGPathSeg> seg;
						seglist->getItem(i, &seg);

						seglist2->appendItem(seg, NULL);
					}

					numberOfItems -= j-i;

					seglist2->UnlockUpdate();

					if (style.Length())
					{
						element2->setAttribute(L"style", style);
					}

					if (transform.Length())
					{
						element2->setAttribute(L"transform", transform);
					}

					parentNode->insertBefore(element2, CComVariant(nextSibling), NULL);

					ActivateElement(ePathElement, MK_SHIFT, NULL);
				}

			//	i = j;
			}

			seglist->UnlockUpdate();

#if 0
			CComPtr<IESVGPath> path;
			esvgElement->GetPath(&path);

			long nsubpaths;
			path->GetSubPathCount(&nsubpaths);

			if (nsubpaths > 1)
			{
				CComPtr<ILSVGPathSegList> seglist;
				path->GetPathSegList(&seglist);
				seglist->LockUpdate();

				for (int i = 1; i < nsubpaths; i++)
				{
					CComPtr<IESVGSubPath> subpath;
					path->GetSubPath(i, &subpath);
					//CComObject<CSubPath>* pSubPath = static_cast<CComObject<CSubPath>*>(subpath.p);

					CComPtr<IESVGPathElement> ePathElement;
					m_pDocument->createEElementNS(L"http://www.w3.org/2000/svg", L"path", (Element**)&ePathElement);
					if (ePathElement)
					{
						CComPtr<Web::Element> domElement;
						ePathElement->get_domElement(&domElement);

						CComPtr<IESVGPath> path;
						ePathElement->GetPath(&path);

						path->InsertSubPathBefore(subpath, 0);

						if (style.Length())
						{
							domElement->setAttribute(L"style", style);
						}

						if (transform.Length())
						{
							domElement->setAttribute(L"transform", transform);
						}

						parentNode->insertBefore(domElement, _variant_t(nextSibling), NULL);

						ActivateElement(ePathElement, MK_SHIFT, NULL);
					}
				}
			}
#endif
		}
	}
#endif
	return 0;
}

void CEXMLViewGroup::OnObjectCompoundPathReleaseUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	bool bEnable = FALSE;
	if (m_pActiveElement)
	{
		CComPtr<Element> eElement;
		m_pActiveElement->get_eElement(&eElement);

		CComQIPtr<IESVGPathElement> esvgElement = eElement;
		if (esvgElement)
		{
			CComPtr<Web::Element> element;
			esvgElement->get_domElement(&element);

			CComQIPtr<ILSVGAnimatedPathData> pathData = element;

			CComPtr<ILSVGPathSegList> seglist;
			pathData->get_pathSegList(&seglist);

			int n = 0;
			long numberOfItems;
			seglist->get_numberOfItems(&numberOfItems);
			for (int i = 0; i < numberOfItems; i++)
			{
				CComPtr<ILSVGPathSeg> seg;
				seglist->getItem(i, &seg);

				LSVGPathSegType segType;
				seg->get_pathSegType(&segType);

				if (segType == PATHSEG_MOVETO_ABS ||
					segType == PATHSEG_MOVETO_REL)
				{
					n++;
					if (n == 2) break;
				}
			}

			if (n > 1)
			{
				bEnable = TRUE;
			}
		}
	}
	pCmdUI->Enable(bEnable);
#endif
}

long CEXMLViewGroup::OnObjectGroup(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	if (m_targetElements.GetSize() >= 1)
	{
		CWEUndoGroupObjects* pUndo = new CWEUndoGroupObjects;
		if (pUndo)
		{
#if 0
			pUndo->AddRef();
#endif
			pUndo->m_pDocument = m_pDocument;
			//m_activeSpread->get_uniqId(&pUndo->m_spreadGUID);

			//CComPtr<IOleUndoManager> undoManager;
			//m_document->get_undoManager(&undoManager);

			pUndo->DoInitial(this, m_pDocument->m_undoManager);

			m_pDocument->m_undoManager->Add(pUndo);
		}
	}

	return 0;
}

void CEXMLViewGroup::OnObjectGroupUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	bool bEnable = false;
	if (m_targetElements.GetSize() >= 1)
	{
		bEnable = true;
	}

	pCmdUI->Enable(bEnable);
}

long CEXMLViewGroup::OnObjectUngroup(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	if (m_pActiveElement)
	{
		CComPtr<Element> eElement;
		m_pActiveElement->get_eElement(&eElement);

		CComPtr<Web::Element> element;
		eElement->get_domElement(&element);

		CComQIPtr<ILSVGGElement> g = element;
		if (g)
		{
			DeselectAll();

			CComPtr<Web::Node> parentNode;
			g->get_parentNode(&parentNode);

			CComPtr<Web::Node> node;
			g->get_firstChild(&node);
			while (node)
			{
				CComPtr<Web::Node> nextSibling;
				node->get_nextSibling(&nextSibling);

				parentNode->insertBefore(node, _variant_t(g), NULL);

				CComQIPtr<Web::Element> element = node;
				if (element)
				{
					CComPtr<Element> eElement;
					m_pDocument->GetEElementFromDOMElement(element, &eElement);
					ActivateElement(eElement, MK_SHIFT, NULL);
				}

				node = nextSibling;
			}

			parentNode->removeChild(g, NULL);
		}
	}
#endif
	return 0;
}

void CEXMLViewGroup::OnObjectUngroupUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	bool bEnable = FALSE;

	if (m_pActiveElement)
	{
		CComPtr<Element> eElement;
		m_pActiveElement->get_eElement(&eElement);

		CComPtr<Web::Element> element;
		eElement->get_domElement(&element);

		CComQIPtr<ILSVGGElement> g = element;
		if (g)
		{
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
#endif
}

long CEXMLViewGroup::OnWindowSplit(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
#if 0
	CRect client;
	GetClientRect(&client);
	m_splitx = client.Width()/2;

	OnSize();
#endif

	return 0;
}

long CEXMLViewGroup::OnNewWindowOnActiveElement(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	if (m_pActiveElement)
	{
		CComQIPtr<Web::Element> element = m_pActiveElement->GetElement()->m_domElement;
		if (element)
		{
			CComObject<CEXMLViewGroup>* viewGroup;
			CComObject<CEXMLViewGroup>::CreateInstance(&viewGroup);
			if (viewGroup)
			{
				viewGroup->AddRef();
				viewGroup->m_pDocument = m_pDocument;
				viewGroup->m_outerElement = element;

				m_pDocument->m_viewGroups.Add(viewGroup);

				CComObject<CUIMDIChild>* child;
				CComObject<CUIMDIChild>::CreateInstance(&child);
				child->AddRef();
				gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

				{
				// Layout
					CComObject<CSvgLayoutView>* layoutView;
					CComObject<CSvgLayoutView>::CreateInstance(&layoutView);
					if (layoutView)
					{
						gApp->m_frame->FindMenu(IDR_XMLLAYOUTVIEW, &layoutView->m_menu);
						layoutView->m_document = m_pDocument;

						layoutView->m_viewGroup = viewGroup;
						viewGroup->m_views.Add(layoutView);

						child->AddPage(layoutView, NULL);
					}

				// GridView
					CComObject<CXMLGridView>* xmlgridView;
					CComObject<CXMLGridView>::CreateInstance(&xmlgridView);
					if (xmlgridView)
					{
						gApp->m_frame->FindMenu(IDR_XMLGRIDVIEW, &xmlgridView->m_menu);
						xmlgridView->m_document = m_pDocument;

						xmlgridView->m_viewGroup = viewGroup;
						viewGroup->m_views.Add(xmlgridView);

						child->AddPage(xmlgridView, NULL);
					}
				}

				child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);
			}
		}
	}
#endif
	return 0;
}

long CEXMLViewGroup::OnObjectArrangeFront(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComPtr<Element> eElement;
		m_targetElements[i]->get_eElement(&eElement);

		CComPtr<Web::Element> object;
		eElement->get_domElement(&object);

		if (object)
		{
			CComPtr<Web::Node> parentNode;
			object->get_parentNode(&parentNode);

			if (parentNode)
			{
				CComPtr<Web::Node> nextSibling;
				object->get_nextSibling(&nextSibling);

				if (nextSibling)
				{
					parentNode->appendChild(object, NULL);
					ActivateElement(eElement, MK_SHIFT, NULL);
				}
			}
		}
	}

#if 0
	if (m_pActiveElement)
	{
		CComQIPtr<ILSVGElement> element = m_pActiveElement->GetElement()->m_domElement;

		CComQIPtr<Web::Node> nextSibling;
		element->get_nextSibling(&nextSibling);

		if (nextSibling != NULL)
		{
			CComQIPtr<Web::Node> parentNode;
			element->get_parentNode(&parentNode);

			parentNode->appendChild(element, NULL);
			SetTargetElement(m_pDocument->m_pTree->FindDOMElement((Web::Node*)element), 0);
		}
	}
#endif
#endif
	return 0;
}

long CEXMLViewGroup::OnObjectArrangeBack(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComPtr<Element> eElement;
		m_targetElements[i]->get_eElement(&eElement);

		CComPtr<Web::Element> object;
		eElement->get_domElement(&object);

		if (object)
		{
			CComPtr<Web::Node> parentNode;
			object->get_parentNode(&parentNode);

			if (parentNode)
			{
				CComPtr<Web::Node> firstChild;
				parentNode->get_firstChild(&firstChild);

				if (firstChild)
				{
					parentNode->insertBefore(object, _variant_t(firstChild), NULL);
					ActivateElement(eElement, MK_SHIFT, NULL);
				}
			}
		}
	}

#if 0
	if (m_pActiveElement)
	{
		CComQIPtr<ILSVGElement> element = m_pActiveElement->GetElement()->m_domElement;

		CComQIPtr<Web::Node> previousSibling;
		element->get_previousSibling(&previousSibling);
		
		if (previousSibling != NULL)
		{
			CComQIPtr<Web::Node> parentNode;
			element->get_parentNode(&parentNode);

			CComQIPtr<Web::Node> firstChild;
			parentNode->get_firstChild(&firstChild);

			parentNode->insertBefore(element, firstChild, NULL);
			SetTargetElement(m_pDocument->m_pTree->FindDOMElement((Web::Node*)element), 0);
		}
	}
#endif
#endif
	return 0;

}

long CEXMLViewGroup::OnObjectArrangeForward(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComPtr<Element> eElement;
		m_targetElements[i]->get_eElement(&eElement);

		CComPtr<Web::Element> object;
		eElement->get_domElement(&object);

		if (object)
		{
			CComPtr<Web::Node> parentNode;
			object->get_parentNode(&parentNode);

			if (parentNode)
			{
				CComPtr<Web::Node> nextSibling;
				object->get_nextSibling(&nextSibling);

				if (nextSibling)
				{
					CComPtr<Web::Node> nextnextSibling;
					nextSibling->get_nextSibling(&nextnextSibling);

					parentNode->insertBefore(object, _variant_t(nextnextSibling), NULL);

					ActivateElement(eElement, MK_SHIFT, NULL);
				}
			}
		}
	}

#if 0
	if (m_pActiveElement)
	{
		CComQIPtr<ILSVGElement> element = m_pActiveElement->GetElement()->m_domElement;

		CComQIPtr<Web::Node> nextSibling;
		element->get_nextSibling(&nextSibling);

		if (nextSibling != NULL)
		{
			CComQIPtr<Web::Node> parentNode;
			element->get_parentNode(&parentNode);

			CComQIPtr<Web::Node> nextnextSibling;
			nextSibling->get_nextSibling(&nextnextSibling);

			if (nextnextSibling == NULL)
				parentNode->appendChild(element, NULL);
			else
				parentNode->insertBefore(element, nextnextSibling, NULL);
			SetTargetElement(m_pDocument->m_pTree->FindDOMElement((Web::Node*)element), 0);
		}
	}
#endif
#endif
	return 0;
}

long CEXMLViewGroup::OnObjectArrangeBackward(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComPtr<Element> eElement;
		m_targetElements[i]->get_eElement(&eElement);

		CComPtr<Web::Element> object;
		eElement->get_domElement(&object);

		if (object)
		{
			CComPtr<Web::Node> parentNode;
			object->get_parentNode(&parentNode);

			if (parentNode)
			{
				CComPtr<Web::Node> previousSibling;
				object->get_previousSibling(&previousSibling);

				if (previousSibling)
				{
					parentNode->insertBefore(object, _variant_t(previousSibling), NULL);
					ActivateElement(eElement, MK_SHIFT, NULL);
				}
			}
		}
	}

#if 0
	if (m_pActiveElement)
	{
		CComQIPtr<ILSVGElement> element = m_pActiveElement->GetElement()->m_domElement;

		CComQIPtr<Web::Node> previousSibling;
		element->get_previousSibling(&previousSibling);

		if (previousSibling != NULL)
		{
			CComQIPtr<Web::Node> parentNode;
			element->get_parentNode(&parentNode);

			parentNode->insertBefore(element, previousSibling, NULL);
			SetTargetElement(m_pDocument->m_pTree->FindDOMElement((Web::Node*)element), 0);
		}
	}
#endif
#endif
	return 0;
}

void CEXMLViewGroup::OnObjectArrangeHigherUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	BOOL bEnable = FALSE;

	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComPtr<Element> eElement;
		m_targetElements[i]->get_eElement(&eElement);

		CComPtr<Web::Element> object;
		eElement->get_domElement(&object);

		if (object)
		{
			CComPtr<Web::Node> parentNode;
			object->get_parentNode(&parentNode);

			if (parentNode)
			{
				CComPtr<Web::Node> nextSibling;
				object->get_nextSibling(&nextSibling);

				if (nextSibling)
				{
					bEnable = TRUE;
					break;
				}
			}
		}
	}

	pCmdUI->Enable(bEnable);
#endif
}

void CEXMLViewGroup::OnObjectArrangeLowerUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	BOOL bEnable = FALSE;

	for (int i = 0; i < m_targetElements.GetSize(); i++)
	{
		CComPtr<Element> eElement;
		m_targetElements[i]->get_eElement(&eElement);

		CComPtr<Web::Element> object;
		eElement->get_domElement(&object);

		if (object)
		{
			CComPtr<Web::Node> parentNode;
			object->get_parentNode(&parentNode);

			if (parentNode)
			{
				CComPtr<Web::Node> previousSibling;
				object->get_previousSibling(&previousSibling);

				if (previousSibling)
				{
					bEnable = TRUE;
					break;
				}
			}
		}
	}

	pCmdUI->Enable(bEnable);
#endif
}

#if 0
void CEXMLViewGroup::OnObjectArrangeForwardUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;
#if 0
	if (m_pActiveElement)
	{
		CComQIPtr<Web::Node> nextSibling;
		m_pActiveElement->GetElement()->m_domElement->get_nextSibling(&nextSibling);

		if (nextSibling != NULL)
		{
			bEnable = TRUE;
		}
	}
#endif
	pCmdUI->Enable(bEnable);
}

void CEXMLViewGroup::OnObjectArrangeBackwardUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
#if 0
	BOOL bEnable = FALSE;

	if (m_pActiveElement)
	{
		CComQIPtr<Web::Node> previousSibling;
		m_pActiveElement->GetElement()->m_domElement->get_previousSibling(&previousSibling);

		if (previousSibling != NULL)
		{
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
#endif
}
#endif

}	// LXmlEdit
}
