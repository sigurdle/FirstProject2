// EXMLDocumentStyleSheetsView.cpp : Implementation of CEXMLDocumentStyleSheetsView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "EXMLDocumentStyleSheetsView.h"

#include "EXMLViewGroup.h"	// TODO remove
#include "SourceView.h"	// TODO remove

#include "EStyleElement.h"
#include "ECSSDocument.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CEXMLDocumentStyleSheetsView

int CEXMLDocumentStyleSheetsView::FinalConstruct()
{
	HRESULT hr;

	hr = m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
	if (FAILED(hr)) return hr;

	m_treeCtl->InsertColumn(0, L"Name", 120, TRUE, TRUE, NULL);

	return S_OK;
}

LRESULT CEXMLDocumentStyleSheetsView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CBitmap bmIcons;
	bmIcons.LoadBitmap(MAKEINTRESOURCE(IDB_CSSSTYLESHEETS));

	m_icons.Create(16, 16, ILC_COLOR8 | ILC_MASK, 1, 5);
	m_icons.Add(bmIcons, RGB(255, 255, 255));

	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axtreeCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axtreeCtl.AttachControl(m_treeCtl, &p);
	IDispEventImpl<4, CEXMLDocumentStyleSheetsView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

	m_treeCtl->put_hImageList((long)(HIMAGELIST)m_icons);

	CComPtr<IEXMLDocument> document;
	m_viewGroup->get_eXMLDocument(&document);

	CComPtr<ILDOMDocument> domdocument;
	document->get_DOMDocument(&domdocument);

	PopulateStyleSheetElements(NULL, domdocument);

#if 0
	if (m_styleSheetList)
	{
		ASSERT(m_viewGroup);

		CComPtr<IEXMLDocument> eDocument;
		m_viewGroup->get_eXMLDocument(&eDocument);

		CComPtr<ILDOMDocument> domDocument;
		eDocument->get_DOMDocument(&domDocument);

	//	CComPtr<ILDOMElement> documentElement;
	//	domDocument->get_documentElement(&documentElement);

		PopulateStyleSheetElements(NULL, domDocument);
		/*
		PopulateStyleSheets(NULL, m_styleSheetList);
		*/

		{

			CComQIPtr<ILDOMEventTarget> eventTarget = domDocument;
			eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
		}

		IDispEventImpl<1, CEXMLDocumentStyleSheetsView, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->GetUnknown());
	}
	else if (m_styleSheet)
	{
		CComPtr<ILCSSRuleList> ruleList;
		m_styleSheet->get_cssRules(&ruleList);

		PopulateRules(NULL, ruleList);
	}

#endif

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->AddEventHandler(this);

	return 0;
}

LRESULT CEXMLDocumentStyleSheetsView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<4, CEXMLDocumentStyleSheetsView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_treeCtl);

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->RemoveEventHandler(this);

#if 0
	// Remove handlers on stylesheets
	{
		DWORD root;
		m_treeCtl->GetRootItem(&root);

		DWORD item;
		m_treeCtl->GetFirstChildItem(root, &item);
		while (item)
		{
			DWORD itemdata;
			m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

			CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
			if (styleSheet)
			{
				styleSheet->removeHandler(this);
			}

			m_treeCtl->GetNextSiblingItem(item, &item);
		}
	}

	{
		CComPtr<IEXMLDocument> eDocument;
		m_viewGroup->get_eXMLDocument(&eDocument);

		CComPtr<ILDOMDocument> domDocument;
		eDocument->get_DOMDocument(&domDocument);

		CComQIPtr<ILDOMEventTarget> eventTarget = domDocument;
		eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
		eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
	}
#endif

//	IDispEventImpl<1, CEXMLDocumentStyleSheetsView, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->GetUnknown());

	return 0;
}

LRESULT CEXMLDocumentStyleSheetsView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axtreeCtl.MoveWindow(0, 0, client.right, client.bottom);

	return 0;
}

void __stdcall CEXMLDocumentStyleSheetsView::OnViewGroupSelectionChanged()
{
}

#if 0

// ILDOMEventListener
STDMETHODIMP CEXMLDocumentStyleSheetsView::handleEvent(ILDOMEvent* evt)
{
	CComBSTR type;
	evt->get_type(&type);

//	BOOL bUpdate = FALSE;

	if (!wcscmp(type, L"DOMNodeInserted"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		CComQIPtr<ILLinkStyle> linkStyle = node;
		if (linkStyle)
		{
			CComPtr<ILCSSStyleSheet> styleSheet;
			linkStyle->get_sheet((ILStyleSheet**)&styleSheet);

			styleSheet->addHandler(this);

			DWORD newItem;
			m_treeCtl->InsertItem((DWORD)styleSheet.p, NULL/*parentItem*/, NULL, NULL, 0/*pNewItem->m_iIcon*/, 1/*pNewItem->m_cChildren*/, &newItem);

			CComPtr<ILCSSRuleList> ruleList;
			styleSheet->get_cssRules(&ruleList);

			PopulateRules(newItem, ruleList);
		}
	}
	else if (!wcscmp(type, L"DOMNodeRemovedFromDocument"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		CComQIPtr<ILLinkStyle> linkStyle = node;
		if (linkStyle)
		{
			CComPtr<ILCSSStyleSheet> styleSheet;
			linkStyle->get_sheet((ILStyleSheet**)&styleSheet);

			DWORD root;
			m_treeCtl->GetRootItem(&root);

			DWORD item;
			m_treeCtl->GetFirstChildItem(root, &item);
			while (item)
			{
				DWORD itemdata;
				m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

				CComQIPtr<ILCSSStyleSheet> styleSheet2 = (IUnknown*)itemdata;
				if (styleSheet2 == styleSheet)
				{
					m_treeCtl->DeleteItem(item);
					break;
				}

				m_treeCtl->GetNextSiblingItem(item, &item);
			}
		}

		/*
		for (int i = 0; i < m_listView.m_items.GetSize(); i++)
		{
			if (m_listView.m_items[i]->m_element == node)
			{
				CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_items[i]->m_element;
				eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);

				m_listView.DeleteItem(i);
				break;
			}
		}
*/
	}

	return S_OK;
}
#endif

#if 0
void __stdcall CEXMLDocumentStyleSheetsView::OnItemClick(DWORD item)
{
	DWORD itemdata;
	m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

	CComPtr<ILDOMRange> range;

	CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
	CComQIPtr<ILCSSRule> rule = (IUnknown*)itemdata;
	if (styleSheet)
	{
		CComPtr<ILDOMNode> ownerNode;
		styleSheet->get_ownerNode(&ownerNode);
		if (ownerNode)
		{
			CComPtr<ILDOMDocument> ownerDocument;
			ownerNode->get_ownerDocument(&ownerDocument);

			CComQIPtr<ILDOMDocumentRange> documentRange = ownerDocument;
			if (documentRange)
			{
				documentRange->createRange(&range);
				if (range)
				{
					range->selectNode(ownerNode);
				}
			}

		// hmm... either the following should create the range or the
		// above should do the following (or not???)
			CComPtr<IEXMLDocument> eDocument;
			m_viewGroup->get_eXMLDocument(&eDocument);

			CComPtr<IEElement> eElement;
			eDocument->GetEElementFromDOMElement(CComQIPtr<ILDOMElement>(ownerNode), &eElement);
			if (eElement)
			{
				m_viewGroup->ActivateElement(eElement, 0, NULL);
			}
		}
	}
	else if (rule)
	{
		long startOffset;
		rule->getTextOffset(0, &startOffset);

		long endOffset;
		rule->getTextOffset(3, &endOffset);

		CComPtr<ILCSSStyleSheet> styleSheet;
		rule->get_parentStyleSheet(&styleSheet);
		ASSERT(styleSheet);

		CComPtr<ILDOMNode> ownerNode;
		styleSheet->get_ownerNode(&ownerNode);
		if (ownerNode)
		{
			CComPtr<ILDOMNode> firstChild;
			ownerNode->get_firstChild(&firstChild);

			CComPtr<ILDOMDocument> ownerDocument;
			ownerNode->get_ownerDocument(&ownerDocument);

			CComQIPtr<ILDOMCharacterData> charData = firstChild;
			if (charData)
			{
				CComQIPtr<ILDOMDocumentRange> documentRange = ownerDocument;
				if (documentRange)
				{
					documentRange->createRange(&range);
					if (range)
					{
						range->setStart(charData, startOffset);
						range->setEnd(charData, endOffset);
					}
				}
			}
		}
	}

	if (range)
	{
		CEXMLViewGroup* pViewGroup = m_viewGroup;

		for (int i = 0; i < pViewGroup->m_views.GetSize(); i++)
		{
			CComQIPtr<ISourceView> sourceView = pViewGroup->m_views[i];
			if (sourceView)
			{
				((CSourceView*)sourceView.p)->SetRange(range);
			}
		}
	}
}
#endif

#include "ECSSDocument.h"

void __stdcall CEXMLDocumentStyleSheetsView::OnItemDblClick(IUITreeItem* item)
{
	DWORD itemdata;
	m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

	CComQIPtr<ILDOMNode> node = (IUnknown*)itemdata;

	CComQIPtr<ILDOMElement> element = node;

	if (element)
	{
		CComPtr<IEElement> eElement;
		m_viewGroup->m_pDocument->GetEElementFromDOMElement(element, &eElement);

		CEStyleElement* pStyleElement = static_cast<CEStyleElement*>(eElement.p);

		CComQIPtr<ILLinkStyle> linkStyle = node;

		CComPtr<ILCSSStyleSheet> styleSheet;
		linkStyle->get_sheet((ILStyleSheet**)&styleSheet);

		{
			ASSERT(0);
#if 0
			CComQIPtr<ILXAddin> addin = m_viewGroup->m_pDocument->m_app;

			WCHAR buf[512];
			swprintf(buf, L"%s/style", (BSTR)m_viewGroup->m_pDocument->m_fileTitle);

			pStyleElement->m_pCSSDocument->m_fileTitle = buf;
			pStyleElement->m_pCSSDocument->m_app = addin;
			pStyleElement->m_pCSSDocument->m_styleSheet = styleSheet;

			CComPtr<ILXAddinSite> addinSite;
			addin->GetSite(&addinSite);

			CComPtr<ILXFrameworkFrame> lxframe;
			addinSite->GetFrame(&lxframe);

			CComQIPtr<IEFrame> eframe = lxframe;

			pStyleElement->m_pCSSDocument->ShowViews(eframe);
#endif
		}
	}

	CComQIPtr<ILLinkStyle> linkStyle = node;

	if (linkStyle)
	{
	}

#if 0
	CComPtr<ILCSSStyleSheet> openStyleSheet;

	CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
	CComQIPtr<ILCSSRule> rule = (IUnknown*)itemdata;
	if (styleSheet)
	{
		CComBSTR href;
		styleSheet->get_href(&href);
		if (href.Length())
		{
			openStyleSheet = styleSheet;
		}
	}
	else if (rule)
	{
		CComQIPtr<ILCSSImportRule> importRule = rule;
		if (importRule)
		{
			importRule->get_styleSheet(&openStyleSheet);
		}
	}

	if (openStyleSheet)
	{
		CComObject<CECSSDocument>* pCSSDocument;
		CComObject<CECSSDocument>::CreateInstance(&pCSSDocument);
		if (pCSSDocument)
		{
			pCSSDocument->m_styleSheet = openStyleSheet;

			BSTR cssText;
			openStyleSheet->get_cssText(&cssText);
			pCSSDocument->m_textData->put_data(cssText);

#if 0
			AddDocument(pCSSDocument->GetUnknown(), NULL);
#endif
		}
	}
#endif
}

#if 0
void __stdcall CEXMLDocumentStyleSheetsView::OnEndLabelEdit(long item, BSTR text)
{
	DWORD itemdata;
	m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);
	if (itemdata)
	{
		CComQIPtr<ILCSSStyleRule> styleRule = (IUnknown*)itemdata;
		if (styleRule)
		{
			styleRule->put_selectorText(text);
		}
	}
	else
	{
		if (text && wcslen(text) > 0)
		{
			DWORD parentitem;
			m_treeCtl->GetParentItem(item, &parentitem);
			if (parentitem)
			{
				DWORD parentitemdata;
				m_treeCtl->GetItemInfo(parentitem, &parentitemdata, NULL, NULL);

				CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)parentitemdata;
				if (styleSheet)
				{
					CComPtr<ILCSSRuleList> cssRules;
					styleSheet->get_cssRules(&cssRules);

					long length;
					cssRules->get_length(&length);

					_bstr_t rule = text + _bstr_t(L" {}");

					long index;
					styleSheet->insertRule(rule, length, &index);

					CComPtr<ILCSSRule> cssrule;
					cssRules->item(index, &cssrule);

				// Select the newly inserted rule in the treeview
				// insertRule() will rebuild the parent list, so we need to do this
					{
						DWORD item;
						m_treeCtl->GetFirstChildItem(parentitem, &item);
						while (item)
						{
							DWORD itemdata;
							m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

							CComQIPtr<ILCSSRule> cssrule2 = (IUnknown*)itemdata;
							if (cssrule2 == cssrule)
							{
								m_treeCtl->SetSelectedItem(item);
								OnItemClick(item);	// hm.. maybe this should be called by the above
								break;
							}

							m_treeCtl->GetNextSiblingItem(item, &item);
						}
					}
				}
			}
		}
		else
		{
			m_treeCtl->DeleteItem(item);
		}
	}
}
#endif

#if 0
STDMETHODIMP CEXMLDocumentStyleSheetsView::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IEXMLViewGroup> viewGroup = object;
	if (viewGroup)
	{
		/*
		if (m_document != NULL)
		{
			IDispEventImpl<2, CScriptOutlineDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);
		}
		*/

		m_viewGroup = static_cast<CEXMLViewGroup*>(viewGroup.p);

		CComPtr<IEXMLDocument> document;
		m_viewGroup->get_eXMLDocument(&document);

		CComPtr<ILDOMDocument> domdocument;
		document->get_DOMDocument(&domdocument);

	//	IDispEventImpl<2, CScriptOutlineDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(document);

	//	BuildTree();

		{
#if 0
			m_ctl->SetNode(domdocument);
#endif
		}

		*cookie = 1;
	}

	return S_OK;
}
#endif

BOOL CEXMLDocumentStyleSheetsView::AnyLinkStyleChildren(ILDOMNode* parentNode)
{
	CComPtr<ILDOMNode> node;
	parentNode->get_firstChild(&node);

	while (node)
	{
		CComQIPtr<ILLinkStyle> linkStyle = node;
		if (linkStyle)
		{
			return TRUE;
		}
		else
		{
			BOOL bAny = AnyLinkStyleChildren(node);
			if (bAny)
				return TRUE;
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return FALSE;
}

void CEXMLDocumentStyleSheetsView::PopulateStyleSheetElements(IUITreeItem* parentItem, ILDOMNode* parentNode)
{
	CComPtr<ILDOMNode> node;
	parentNode->get_firstChild(&node);

	while (node)
	{
		CComQIPtr<ILLinkStyle> linkStyle = node;
		if (linkStyle)
		{
			CComPtr<ILStyleSheet> styleSheet;
			linkStyle->get_sheet(&styleSheet);

			if (styleSheet)
			{
				CComBSTR href;
				styleSheet->get_href(&href);

				CComBSTR nodeName;
				node->get_nodeName(&nodeName);

				CComPtr<IUITreeItem> newItem;
				m_treeCtl->InsertItem((DWORD)node.p, parentItem, NULL, nodeName, 0/*pNewItem->m_iIcon*/, -1/*pNewItem->m_cChildren*/, &newItem);

				if (href.Length() == 0)	// Internal style sheet
				{
					CComQIPtr<ILCSSStyleSheet> cssStyleSheet = styleSheet;
					if (cssStyleSheet)
					{
						CComPtr<ILCSSRuleList> ruleList;
						cssStyleSheet->get_cssRules(&ruleList);

					//	PopulateRules(newItem, ruleList);
					}
				}
			}
		}
		else
		{
			BOOL bAny = AnyLinkStyleChildren(node);
			if (bAny)
			{
				CComBSTR nodeName;
				node->get_nodeName(&nodeName);

				CComPtr<IUITreeItem> newItem;
				m_treeCtl->InsertItem((DWORD)node.p, parentItem, NULL, nodeName, 0/*pNewItem->m_iIcon*/, 1/*pNewItem->m_cChildren*/, &newItem);

				PopulateStyleSheetElements(newItem, node);	// Recurse
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
}

#if 0
STDMETHOD(SetNode)(/*[in]*/ ILDOMNode* node)
{
	m_treeCtl->ResetContent(NULL);
	PopulateStyleSheetElements(NULL, node);
	return S_OK;
}

STDMETHODIMP CEXMLDocumentStyleSheetsView::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
#if 0
	CComQIPtr<IWebXMLDocument> document = object;
	if (document)
	{
		if (document == m_document)
		{
			IDispEventImpl<2, CScriptOutlineDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);
			m_document.Release();
		}
	}
#endif

//	CComPtr<IEXMLDocument> document;
//	m_viewGroup->get_eXMLDocument(&document);
//	IDispEventImpl<2, CScriptOutlineDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(document);

	m_viewGroup = NULL;//.Release();

	return S_OK;
}
#endif

#if 0
// ICommandTarget
STDMETHODIMP CEXMLDocumentStyleSheetsView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try viewgroup
	CComQIPtr<ICommandTarget> target = m_viewGroup;
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

	return S_OK;
}
#endif

BEGIN_CMD_MAP(CEXMLDocumentStyleSheetsView)
// Edit
	CMD_HANDLER(ID_EDIT_CLEAR, OnEditClear)
	CMD_UPDATE(ID_EDIT_CLEAR, OnEditClearUpdate)

// CSS
	CMD_HANDLER(ID_CSS_NEWINTERNALSTYLEELEMENT, OnNewInternalStyleElement)

	CMD_HANDLER(ID_CSS_NEWIMPORTRULE, OnNewImportRule)
	CMD_UPDATE(ID_CSS_NEWIMPORTRULE, OnNewRuleUpdate)

	CMD_HANDLER(ID_CSS_NEWCLASSSTYLE, OnNewStyleRule)
	CMD_UPDATE(ID_CSS_NEWCLASSSTYLE, OnNewRuleUpdate)

	CMD_HANDLER(ID_CSS_DISABLEDSTYLESHEET, OnDisabledStylesheet)
	CMD_UPDATE(ID_CSS_DISABLEDSTYLESHEET, OnDisabledStylesheetUpdate)
END_CMD_MAP()

LRESULT CEXMLDocumentStyleSheetsView::OnDisabledStylesheet(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	DWORD activeitem;
	m_ctl->GetSelectedItem(&activeitem);

	if (activeitem)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(activeitem, &itemdata, NULL, NULL);

		CComQIPtr<ILStyleSheet> styleSheet = (IUnknown*)itemdata;
		if (styleSheet)
		{
			VARIANT_BOOL disabled;
			styleSheet->get_disabled(&disabled);

		// Toggle
			styleSheet->put_disabled(~disabled);
		}
	}
#endif

	return 0;
}

void CEXMLDocumentStyleSheetsView::OnDisabledStylesheetUpdate(long iid, IUICmdUpdate* pCmdUI)
{
#if 0
	BOOL bEnable = FALSE;
	BOOL bCheck = FALSE;

	DWORD activeitem;
	m_treeCtl->GetSelectedItem(&activeitem);

	if (activeitem)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(activeitem, &itemdata, NULL, NULL);

		CComQIPtr<ILStyleSheet> styleSheet = (IUnknown*)itemdata;
		if (styleSheet)
		{
			VARIANT_BOOL disabled;
			styleSheet->get_disabled(&disabled);

			bCheck = disabled;
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
	pCmdUI->SetCheck(bCheck);
#endif
}

LRESULT CEXMLDocumentStyleSheetsView::OnEditClear(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	DWORD activeitem;
	m_treeCtl->GetSelectedItem(&activeitem);

	if (activeitem)
	{
		DWORD parentitem;
		m_treeCtl->GetParentItem(activeitem, &parentitem);

		CArray<DWORD,DWORD> items;

		DWORD item;
		m_treeCtl->GetFirstChildItem(parentitem, &item);
		while (item)
		{
			DWORD state;
			m_treeCtl->GetItemState(item, &state);
			if (state & 1)
			{
				DWORD itemdata;
				m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

				items.Add(itemdata);
			}

			DWORD nextitem;
			m_treeCtl->GetNextSiblingItem(item, &nextitem);
			item = nextitem;
		}

		for (int i = 0; i < items.GetSize(); i++)
		{
			DWORD itemdata = items[i];

			CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
			if (styleSheet)
			{
				CComPtr<ILDOMNode> ownerNode;
				styleSheet->get_ownerNode(&ownerNode);
				if (ownerNode)
				{
					CComPtr<ILDOMNode> parentNode;
					ownerNode->get_parentNode(&parentNode);
					parentNode->removeChild(ownerNode, NULL);
				}
			}
			else
			{
				CComQIPtr<ILCSSRule> cssRule = (IUnknown*)itemdata;
				if (cssRule)
				{
					CComPtr<ILCSSStyleSheet> styleSheet;
					cssRule->get_parentStyleSheet(&styleSheet);

					CComPtr<ILCSSRuleList> ruleList;
					styleSheet->get_cssRules(&ruleList);

					long length;
					ruleList->get_length(&length);

					for (int i = 0; i < length; i++)
					{
						CComPtr<ILCSSRule> cssRule2;
						ruleList->item(i, &cssRule2);

						if (cssRule2 == cssRule)
						{
							styleSheet->deleteRule(i);
							break;
						}
					}
				}
			}
		}
	}
#endif

	return 0;
}

void CEXMLDocumentStyleSheetsView::OnEditClearUpdate(long iid, IUICmdUpdate* pCmdUI)
{
#if 0
	BOOL bEnable = FALSE;

	DWORD activeitem;
	m_treeCtl->GetSelectedItem(&activeitem);

	if (activeitem)
	{
		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
#endif
}

LRESULT CEXMLDocumentStyleSheetsView::OnNewInternalStyleElement(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<IEXMLDocument> eDocument;
	m_viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<ILDOMDocument> domDocument;
	eDocument->get_DOMDocument(&domDocument);

	CComPtr<ILDOMElement> documentElement;
	domDocument->get_documentElement(&documentElement);

	if (documentElement)
	{
		CComPtr<ILDOMNode> firstChild;
		documentElement->get_firstChild(&firstChild);

		CComPtr<ILDOMElement> styleElement;
		domDocument->createElement(L"style", &styleElement);
		if (styleElement)
		{
			styleElement->setAttribute(L"type", L"text/css");

			documentElement->insertBefore(styleElement, _variant_t(firstChild), NULL);
		}
	}

	return 0;
}

LRESULT CEXMLDocumentStyleSheetsView::OnNewStyleRule(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	DWORD item;
	m_treeCtl->GetSelectedItem(&item);
	if (item)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

		CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
		if (styleSheet == NULL)	// Try parent item
		{
			m_treeCtl->GetParentItem(item, &item);
			if (item)
			{
				m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);
				styleSheet = (IUnknown*)itemdata;
			}
		}

		if (styleSheet)
		{
			DWORD newItem;
			m_treeCtl->InsertItem((DWORD)NULL, item, NULL, NULL, 1/*pNewItem->m_iIcon*/, -1/*pNewItem->m_cChildren*/, &newItem);

			CComPtr<IUIEdit> edit;
			m_treeCtl->EditLabel(newItem, &edit);
		}
	}
#endif

	return 0;
}

LRESULT CEXMLDocumentStyleSheetsView::OnNewImportRule(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	DWORD item;
	m_treeCtl->GetSelectedItem(&item);
	if (item)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

		CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
		if (styleSheet == NULL)	// Try parent item
		{
			m_treeCtl->GetParentItem(item, &item);
			if (item)
			{
				m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);
				styleSheet = (IUnknown*)itemdata;
			}
		}

		if (styleSheet)
		{
			static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
														"CSS Stylesheets (*.css)\0*.css\0"
														);

			TCHAR sbuffer[4096];
			strcpy(sbuffer, "");	// Initial filename
			
			TCHAR curdir[MAX_PATH];
			GetCurrentDirectory(sizeof(curdir), curdir);

			OPENFILENAME	ofn = {0};
			ofn.lStructSize = sizeof(OPENFILENAME);
			ASSERT(0);
			ofn.hwndOwner = NULL;//GetMainHwnd();
			ofn.hInstance = _Module.m_hInst;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
			ofn.lpstrFile = sbuffer;
			ofn.nMaxFile = sizeof(sbuffer);
			ofn.lpstrInitialDir = curdir;
			ofn.lpstrFilter = FilesFilter;
			ofn.nFilterIndex = 2;
			
			if (GetOpenFileName(&ofn))
			{
				_bstr_t rule = L"@import" + _bstr_t(sbuffer);

			//	insertRule(in DOMString rule, index);
			}
		}
	}
#endif

	return 0;
}

void CEXMLDocumentStyleSheetsView::OnNewRuleUpdate(long iid, IUICmdUpdate* pCmdUI)
{
#if 0
	BOOL bEnable = FALSE;

	DWORD item;
	m_treeCtl->GetSelectedItem(&item);
	if (item)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

		CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
		if (styleSheet == NULL)	// Try parent item
		{
			m_treeCtl->GetParentItem(item, &item);
			if (item)
			{
				m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);
				styleSheet = (IUnknown*)itemdata;
			}
		}

		if (styleSheet)
		{
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
#endif
}

#endif