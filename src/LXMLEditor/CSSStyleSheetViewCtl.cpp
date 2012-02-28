// CSSStyleSheetViewCtl.cpp : Implementation of CCSSStyleSheetViewCtlCtl

#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "CSSStyleSheetViewCtl.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CCSSStyleSheetViewCtlCtl

#define PANE_NAME			0
#define PANE_MEDIA		1
#define PANE_URL			2
#define PANE_SOURCE		3

/////////////////////////////////////////////////////////////////////////////
// CCSSStyleSheetViewCtl

int CCSSStyleSheetViewCtl::FinalConstruct()
{
	HRESULT hr;

	hr = m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
	if (FAILED(hr)) return hr;

	m_treeCtl->SetSite(this);

	m_treeCtl->InsertColumn(PANE_NAME, L"Name", 120, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_MEDIA, L"Media", 80, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_URL, L"Url", 80, TRUE, TRUE, NULL);
//	m_treeCtl->InsertColumn(PANE_STATUS, L"Status", 80, TRUE, TRUE, NULL);
//	m_treeCtl->InsertColumn(PANE_SIZE, L"Size", 60, FALSE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_SOURCE, L"Source", 80, TRUE, TRUE, NULL);

	GUID guid;
	::CoCreateGuid(&guid);

	LPOLESTR guidstr;
	StringFromCLSID(guid, &guidstr);
	m_userDataKey = guidstr;
	CoTaskMemFree(guidstr);

	return S_OK;
}

void CCSSStyleSheetViewCtl::FinalRelease()
{
}

STDMETHODIMP CCSSStyleSheetViewCtl::AddStyleSheet(IUnknown* parentItem, ILCSSStyleSheet* styleSheet)
{
	styleSheet->addHandler(this);

	CComPtr<ILCSSRuleList> rules;
	styleSheet->get_cssRules(&rules);

	PopulateRules(CComQIPtr<IUITreeItem>(parentItem), rules);

	return S_OK;
}

void CCSSStyleSheetViewCtl::InsertRule(IUITreeItem* parentItem, IUITreeItem* beforeItem, ILCSSRule* rule, IUITreeItem* *pVal)
{
	CComPtr<IUITreeItem> newItem;

	LCSS::LCSSType type;
	rule->get_type(&type);

	switch (type)
	{
	case LCSS::COMMENT_RULE:	// comment (this is an Extension to the CSS OM)
		{
			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"Comment", 4/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case STYLE_RULE:
		{
			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, NULL, 1/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	// @rules

	case LCSS::UNKNOWN_RULE:
		{
			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@unknown", 3/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case LCSS::CHARSET_RULE:
		{
			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@charset", 3/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case LCSS::IMPORT_RULE:
		{
			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@import", 2/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case LCSS::PAGE_RULE:
		{
			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@page", 3/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case LCSS::FONT_FACE_RULE:
		{
			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@font-face", 3/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case LCSS::COLOR_PROFILE_RULE:
		{
			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@color-profile", 5/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case LCSS::MEDIA_RULE:
		{
			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@media", 3/*pNewItem->m_iIcon*/, -1/*pNewItem->m_cChildren*/, &newItem);

			CComQIPtr<ILCSSMediaRule> mediaRule = rule;

			CComPtr<ILCSSRuleList> ruleList;
			mediaRule->get_cssRules(&ruleList);

			PopulateRules(newItem, ruleList);	// Recurse
		}
		break;

	default:
		ATLASSERT(0);
	}

	rule->setUserData(m_userDataKey, newItem, NULL);

	*pVal = newItem;
	(*pVal)->AddRef();
}

void CCSSStyleSheetViewCtl::PopulateRules(IUITreeItem* parentItem, ILCSSRuleList* ruleList)
{
	long nrules;
	ruleList->get_length(&nrules);

	for (int i = 0; i < nrules; i++)
	{
		CComPtr<ILCSSRule> rule;
		ruleList->item(i, &rule);

		CComPtr<IUITreeItem> newItem;

		InsertRule(parentItem, NULL, rule, &newItem);
	}
}

void CCSSStyleSheetViewCtl::PopulateStyleSheets(IUITreeItem* parentItem, ILStyleSheetList* styleSheetList)
{
	long nstylesheets;
	styleSheetList->get_length(&nstylesheets);
	for (int i = 0; i < nstylesheets; i++)
	{
		CComPtr<ILCSSStyleSheet> styleSheet;
		m_styleSheetList->item(i, (ILStyleSheet**)&styleSheet);

		CComPtr<IUITreeItem> newItem;
		m_treeCtl->InsertItem((DWORD)styleSheet.p, parentItem, NULL, NULL, 0/*pNewItem->m_iIcon*/, 1/*pNewItem->m_cChildren*/, &newItem);

		styleSheet->addHandler(this);

		CComPtr<ILCSSRuleList> ruleList;
		styleSheet->get_cssRules(&ruleList);

		PopulateRules(newItem, ruleList);
	}
}

BOOL CCSSStyleSheetViewCtl::AnyLinkStyleChildren(ILDOMNode* parentNode)
{
	CComPtr<ILDOMNode> node;
	parentNode->get_firstChild(&node);

	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CComQIPtr<ILLinkStyle> linkStyle = node;
			if (linkStyle)
			{
				return TRUE;
			}
			else
			{
				BOOL bAny = AnyLinkStyleChildren(element);
				if (bAny)
					return TRUE;
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return FALSE;
}

LRESULT CCSSStyleSheetViewCtl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CBitmap bmIcons;
	bmIcons.LoadBitmap(MAKEINTRESOURCE(IDB_CSSSTYLESHEETS));

	m_icons.Create(16, 16, ILC_COLOR8 | ILC_MASK, 1, 5);
	m_icons.Add(bmIcons, RGB(255, 255, 255));

	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axtreeCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axtreeCtl.AttachControl(m_treeCtl, &p);
	IDispEventImpl<4, CCSSStyleSheetViewCtl, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

	m_treeCtl->put_hImageList((long)(HIMAGELIST)m_icons);

#if 0	// Had this
	if (m_styleSheetList)
	{
		ATLASSERT(m_viewGroup);

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

		IDispEventImpl<1, CCSSStyleSheetViewCtl, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->GetUnknown());
	}
	else if (m_styleSheet)
	{
		CComPtr<ILCSSRuleList> ruleList;
		m_styleSheet->get_cssRules(&ruleList);

		PopulateRules(NULL, ruleList);
	}
#endif

//	m_treeCtl->put_hImageList((DWORD)m_hFileIcons);

	return 0;
}

LRESULT CCSSStyleSheetViewCtl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// TODO, this doesn't seem right
	// Remove handlers on stylesheets
	{
		CComPtr<IUITreeItem> root;
		m_treeCtl->GetRootItem(&root);

		CComPtr<IUITreeItem> item;
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

			CComPtr<IUITreeItem> nextItem;
			m_treeCtl->GetNextSiblingItem(item, &nextItem);
			item = nextItem;
		}
	}

#if 0	// Had this
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

//	IDispEventImpl<1, CCSSStyleSheetViewCtl, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->GetUnknown());
	IDispEventImpl<4, CCSSStyleSheetViewCtl, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_treeCtl);

	m_icons.Destroy();

	return 0;
}

LRESULT CCSSStyleSheetViewCtl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axtreeCtl.MoveWindow(0, 0, client.right, client.bottom);

	return 0;
}

#if 0
void __stdcall CCSSStyleSheetViewCtl::OnViewGroupSelectionChanged()
{
}
#endif

void GetParentRuleList(ILCSSRule* rule, ILCSSRuleList* *pVal);
int GetRuleIndex(ILCSSRuleList* ruleList, ILCSSRule* rule);

STDMETHODIMP CCSSStyleSheetViewCtl::handleCSSEvent(/*[in]*/ LCSSObjectType objectType, /*[in]*/ LCSSEventType eventType, /*[in]*/ ILCSSStyleSheet* styleSheet, /*[in]*/ IUnknown* pObject)
{
	if (objectType == LCSSObject_Rule)
	{
		CComQIPtr<ILCSSRule> rule = pObject;

		CComPtr<IUnknown> p;
		rule->getUserData(m_userDataKey, &p);
		CComQIPtr<IUITreeItem> treeItem = p;

		if (eventType == LCSSEvent_Insert)
		{
			CComPtr<ILCSSRuleList> parent;
			GetParentRuleList(rule, &parent);
			int index = GetRuleIndex(parent, rule);

			CComPtr<IUITreeItem> parentItem;
			m_treeCtl->GetRootItem(&parentItem);

			CComPtr<IUITreeItem> beforeItem;
			parentItem->ChildItem(index, &beforeItem);

			CComPtr<IUITreeItem> item;
			InsertRule(parentItem, beforeItem, rule, &item);
		}
		else if (eventType == LCSSEvent_Remove)
		{
			rule->setUserData(m_userDataKey, NULL, NULL);	// remove user data
			m_treeCtl->DeleteItem(treeItem);
		}
		else if (eventType == LCSSEvent_Modify)
		{
			m_treeCtl->UpdateItem(treeItem);
		}
		else
			ATLASSERT(0);
	}

	return S_OK;
}

STDMETHODIMP CCSSStyleSheetViewCtl::SelectRule(VARIANT vtrule)
{
	CComQIPtr<ILCSSRule> rule = vtrule.punkVal;
	if (rule)
	{
		CComPtr<IUnknown> p;
		rule->getUserData(m_userDataKey, &p);
		CComQIPtr<IUITreeItem> treeItem = p;

		m_treeCtl->SetSelectedItem(treeItem);
	}
	else
	{
		m_treeCtl->SetSelectedItem(NULL);
	}

	return S_OK;
}

#if 0
STDMETHODIMP CCSSStyleSheetViewCtl::handleCSSEvent(ILCSSStyleSheet* styleSheet, long type)
{
	DWORD root;
	m_treeCtl->GetRootItem(&root);

	DWORD selecteditem;
	m_treeCtl->GetSelectedItem(&selecteditem);

	CComQIPtr<ILCSSRule> cssrule;
	if (selecteditem)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(selecteditem, &itemdata, NULL, NULL);

		cssrule = (IUnknown*)itemdata;
	}

	DWORD item;
	m_treeCtl->GetFirstChildItem(root, &item);
	while (item)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

		CComQIPtr<ILCSSStyleSheet> styleSheet2 = (IUnknown*)itemdata;
		if (styleSheet2 == styleSheet)
		{
			m_treeCtl->ResetContent(item);

			CComPtr<ILCSSRuleList> ruleList;
			styleSheet->get_cssRules(&ruleList);

			PopulateRules(item, ruleList);

			DWORD parentitem = item;
			if (cssrule)	// Previously selected rule
			{
				// Search through and see if we can't reselect it
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
						break;
					}

					m_treeCtl->GetNextSiblingItem(item, &item);
				}
			}
			break;
		}

		m_treeCtl->GetNextSiblingItem(item, &item);
	}

	return S_OK;
}
#endif

// ILDOMEventListener
STDMETHODIMP CCSSStyleSheetViewCtl::handleEvent(ILDOMEvent* evt)
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

			CComPtr<IUITreeItem> newItem;
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

			CComPtr<IUITreeItem> root;
			m_treeCtl->GetRootItem(&root);

			CComPtr<IUITreeItem> item;
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

void __stdcall CCSSStyleSheetViewCtl::OnItemClick(IUITreeItem* item)
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

#if 0	// Had this
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
#endif
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
		ATLASSERT(styleSheet);

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
#if 0	// Had this
		CEXMLViewGroup* pViewGroup = m_viewGroup;

		for (int i = 0; i < pViewGroup->m_views.GetSize(); i++)
		{
			CComQIPtr<ISourceView> sourceView = pViewGroup->m_views[i];
			if (sourceView)
			{
				((CSourceView*)sourceView.p)->SetRange(range);
			}
		}
#endif
	}
}

//#include "WebEditorApp.h"	// TODO remove

//#include "ActiveCntDocument.h"// TODO remove

#include "ECSSDocument.h"

void __stdcall CCSSStyleSheetViewCtl::OnItemDblClick(IUITreeItem* item)
{
	DWORD itemdata;
	m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

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
}

void __stdcall CCSSStyleSheetViewCtl::OnEndLabelEdit(IUITreeItem* item, BSTR text)
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
			CComPtr<IUITreeItem> parentitem;
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
						CComPtr<IUITreeItem> item;
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

void __stdcall CCSSStyleSheetViewCtl::OnItemStateChange(IUITreeItem* item, long oldState, long newState)
{
	DWORD itemdata;
	m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

	if (itemdata)
	{
		CComQIPtr<ILCSSRule> rule = (IUnknown*)itemdata;
		if (rule)
		{
			Fire_RuleStateChange(rule, oldState, newState);
		}
	}
}

STDMETHODIMP CCSSStyleSheetViewCtl::GetItemText(ULONG itemdata, LONG column, BSTR * pVal)
{
	*pVal = NULL;

	CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
//	CSiteItem* pNode = (CSiteItem*)itemdata;

	CComQIPtr<ILCSSRule> rule = (IUnknown*)itemdata;
	CComQIPtr<ILCSSStyleRule> styleRule = (IUnknown*)itemdata;
	CComQIPtr<ILCSSMediaRule> mediaRule = (IUnknown*)itemdata;
	CComQIPtr<ILCSSImportRule> importRule = (IUnknown*)itemdata;

	switch (column)
	{
	case PANE_NAME:
		/*
		if (styleSheet)
		{
			CComPtr<ILDOMNode> ownerNode;
			styleSheet->get_ownerNode(&ownerNode);

			if (ownerNode)
			{
				CComBSTR tagName;
				ownerNode->get_nodeName(&tagName);
				if (!wcscmp(tagName, L"style"))
				{
					*pVal = SysAllocString(L"Internal style");
				}
				else
				{
					BSTR bhref;
					styleSheet->get_href(&bhref);

					*pVal = bhref;
				}
			}
			else
			{
				BSTR bhref;
				styleSheet->get_href(&bhref);

				*pVal = bhref;
			}
		}
		else
			*/
			if (styleRule)
		{
			styleRule->get_selectorText(pVal);
		}
		break;

	case PANE_MEDIA:
		{
			if (styleSheet)
			{
				CComPtr<ILMediaList> media;
				styleSheet->get_media(&media);

				media->get_mediaText(pVal);
			}
			else if (mediaRule)
			{
				CComPtr<ILMediaList> media;
				mediaRule->get_media(&media);

				media->get_mediaText(pVal);
			}
		}
		break;

	case PANE_URL:
		{
			if (styleSheet)
			{
				styleSheet->get_href(pVal);
			}
			else if (importRule)
			{
				importRule->get_href(pVal);
			}
		}
		break;

	case PANE_SOURCE:
		{
			if (styleRule)
			{
				CComPtr<ILCSSStyleDeclaration> decl;
				styleRule->get_style(&decl);
				if (decl)
				{
					decl->get_cssText(pVal);
				}
			}
			else if (mediaRule)
			{
				*pVal = NULL;	// No text
			}
			else if (importRule)
			{
				*pVal = NULL;	// No text
			}
			else if (rule)
			{
				rule->get_cssText(pVal);
			}
		}
		break;
	}

	return S_OK;
}

STDMETHODIMP CCSSStyleSheetViewCtl::get_styleSheet(ILCSSStyleSheet **pVal)
{
	return m_styleSheet.CopyTo(pVal);
}

STDMETHODIMP CCSSStyleSheetViewCtl::putref_styleSheet(ILCSSStyleSheet *newVal)
{
	m_styleSheet = newVal;
	return S_OK;
}

STDMETHODIMP CCSSStyleSheetViewCtl::DeleteSelection()
{
	CComPtr<IUITreeItem> activeitem;
	m_treeCtl->GetSelectedItem(&activeitem);

	if (activeitem)
	{
		CComPtr<IUITreeItem> parentitem;
		m_treeCtl->GetParentItem(activeitem, &parentitem);

		CArray<DWORD,DWORD> items;

		CComPtr<IUITreeItem> item;
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

			CComPtr<IUITreeItem> nextitem;
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

	return S_OK;
}

#endif