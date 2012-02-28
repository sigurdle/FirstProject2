// ScriptOutlineDlg.cpp : Implementation of CScriptOutlineDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "ScriptOutlineDlg.h"

#include "EXMLDocument.h"	// TODO, remove
#include "EXMLViewGroup.h"	// TODO, remove
#include "EScriptElement.h"
#include "EScriptDocument.h"

#include "WEUndoNewElement.h"
#include "UndoParent.h"

#include "EXMLViewGroup.h"	// TODO remove
#include "SourceView.h"	// TODO remove

#if 0

class CEvent
{
public:
	WCHAR* m_attName;
};

CEvent events[] =
{
	L"onload",
	L"onunload",
	L"onmousedown",
	L"onmouseup",
	L"onmousemove",
	L"onclick",
	L"onactivate",
	L"onfocusin",
	L"onfocusout",
	NULL
};

void SkipJScriptSpaces(BSTR data, long& pos, long len)
{
	while (pos < len)
	{
		if (data[pos] == L'/')	// Maybe start of comment
		{
			pos++;
			if (data[pos] == L'/')	// Single-line comment
			{
				pos++;
				while (pos < len)
				{
					pos++;
					if (data[pos] == L'\n')
						break;
				}
			}
			else if (data[pos] == L'*')	// Multi-line comment
			{
				pos++;
				while (pos < len)
				{
					if (data[pos] == L'*')
					{
						pos++;
						if (pos < len && data[pos] == L'/')
						{
							pos++;
							break;
						}
					}
					else
					{
						pos++;
					}
				}
			}
		}
		else if (iswspace(data[pos]))
		{
			pos++;
		}
		else
		{
			break;
		}
	}
}

void CScriptOutlineDlg::AddJScriptFunctions(IUITreeItem* parentItem, ILDOMCharacterData* chardataNode, BSTR data, long len)
{
	long pos = 0;
	while (pos < len)
	{
		SkipJScriptSpaces(data, pos, len);

		if (iswalpha(data[pos]))
		{
			long startpos = pos++;

			while (pos < len)
			{
				if (!iswalpha(data[pos]))
					break;
				pos++;
			}

			if (pos-startpos == 8 && !wcsncmp(&data[startpos], L"function", 8))
			{
				SkipJScriptSpaces(data, pos, len);

				if (iswalpha(data[pos]) || data[pos] == L'_')
				{
					// Get function name
					long startpos = pos++;
					while (pos < len)
					{
						if (!iswalnum(data[pos]) && data[pos] != L'_')
							break;
						pos++;
					}

					CItemFunction* pFItem = new CItemFunction;
					pFItem->m_node = chardataNode;
					pFItem->m_startOffset = startpos;
					pFItem->m_endOffset = pos;
					pFItem->m_name = SysAllocStringLen(&data[startpos], pos-startpos);

					m_treeCtl->InsertItem((DWORD)pFItem, parentItem, NULL, NULL, 4, 0, &pFItem->m_TreeItem);
				}
			}
		}
		else
		{
			pos++;
		}
	}
}

void CScriptOutlineDlg::AddVBScriptFunctions(IUITreeItem* parentItem, ILDOMCharacterData* chardataNode, BSTR data, long len)
{
	long pos = 0;
	while (pos < len)
	{
		if (data[pos] == L'"') // String
		{
			pos++;
			while (pos < len)
			{
				WCHAR c = data[pos++];
				if (c == '"') break;
			}
		}
		else if (data[pos] == L'\'') // Comment
		{
			pos++;
			while (pos < len)
			{
				WCHAR c = data[pos++];
				if (c == '\n') break;
			}
		}
		else if (iswalpha(data[pos]))
		{
			long startpos = pos++;

			while (pos < len)
			{
				if (!iswalpha(data[pos]))
					break;
				pos++;
			}

			if ((pos-startpos == 3 && !wcsnicmp(&data[startpos], L"Sub", 3)) ||
				(pos-startpos == 8 && !wcsnicmp(&data[startpos], L"Function", 8)))
			{
				// Skip spaces
				while (iswspace(data[pos])) pos++;

				// Get Sub/Function name
				if (iswalpha(data[pos]))
				{
					long startpos = pos++;
					while (pos < len)
					{
						if (!iswalnum(data[pos]) && data[pos] != L'_')
							break;
						pos++;
					}

					CItemFunction* pFItem = new CItemFunction;
					pFItem->m_name = SysAllocStringLen(&data[startpos], pos-startpos);

					m_treeCtl->InsertItem((DWORD)pFItem, parentItem, NULL, NULL, 4, 0, &pFItem->m_TreeItem);
				}
			}
		}
		else
		{
			pos++;
		}
	}
}

/*
void CScriptOutlineDlg::AddClientScripts(IUITreeItem* parentItem, ILDOMElement* pelement)
{
	CComPtr<ILDOMNode> node;
	pelement->get_firstChild(&node);
	while (node != NULL)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CComBSTR tagName;
			element->get_tagName(&tagName);

			if (!wcscmp(tagName, L"script"))
			{
				CComBSTR language;
				element->getAttribute(L"language", &language);

				CItemScript* pScriptItem = new CItemScript;
				if (language.Length() == 0)
				{
					pScriptItem->m_name = L"JScript";
				}
				else if (
					!wcsicmp(language, L"jscript") ||
					!wcsicmp(language, L"javascript"))
				{
					pScriptItem->m_name = L"JScript";
				}
				else if (
					!wcsicmp(language, L"vbs") ||
					!wcsicmp(language, L"vbscript"))
				{
					pScriptItem->m_name = L"VBScript";
				}
				else
				{
					pScriptItem->m_name = language;
				}

				pScriptItem->m_element = element;

				m_treeCtl->InsertItem((DWORD)pScriptItem, parentItem, NULL, NULL, 3, 1, &pScriptItem->m_TreeItem);
				m_treeCtl->Expand(pScriptItem->m_TreeItem, TV_EXPAND, NULL);

				CComPtr<ILDOMNode> firstnode;
				element->get_firstChild(&firstnode);
				if (firstnode)
				{
					CComQIPtr<ILDOMCharacterData> chardataNode = firstnode;
					if (chardataNode)
					{
						CComBSTR data;
						chardataNode->get_data(&data);
						long len = SysStringLen(data);

						if (!wcscmp(pScriptItem->m_name, L"JScript"))
						{
							AddJScriptFunctions(pScriptItem->m_TreeItem, chardataNode, data, len);
						}
						else if (!wcscmp(pScriptItem->m_name, L"VBScript"))
						{
							AddVBScriptFunctions(pScriptItem->m_TreeItem, chardataNode, data, len);
						}
					}
				}
			}

			AddClientScripts(parentItem, element);	// Recurse
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
}
*/

void CScriptOutlineDlg::BuildTree(ILDOMElement* element, IUITreeItem* *pVal)
{
	CComPtr<IUITreeItem> item;

	CComBSTR tagName;
	element->get_tagName(&tagName);

	if (!wcscmp(tagName, L"script"))
	{
		CComBSTR language;
		element->getAttribute(L"language", &language);

		CItemScript* pScriptItem = new CItemScript;
		if (language.Length() == 0)
		{
			pScriptItem->m_name = L"JScript";	// Default
		}
		else if (
			!wcsicmp(language, L"text/ecmascript") ||
			!wcsicmp(language, L"jscript") ||
			!wcsicmp(language, L"javascript"))
		{
			pScriptItem->m_name = L"JScript";
		}
		else if (
			!wcsicmp(language, L"vbs") ||
			!wcsicmp(language, L"vbscript"))
		{
			pScriptItem->m_name = L"VBScript";
		}
		else
		{
			pScriptItem->m_name = language;
		}

		pScriptItem->m_element = element;

		m_treeCtl->CreateItem((DWORD)pScriptItem, NULL, 3, -1/*cChildren*/, &pScriptItem->m_TreeItem);
		item = pScriptItem->m_TreeItem;

		m_treeCtl->Expand(pScriptItem->m_TreeItem, TV_EXPAND, NULL);

		LXML::Node* node = element->get_firstChild();
		while (node)
		{
			LXML::CharacterData* chardataNode = node;
			if (chardataNode)
			{
				sysstring data = chardataNode->get_data();
				long len = SysStringLen(data);

				if (!wcscmp(pScriptItem->m_name, L"JScript"))
				{
					AddJScriptFunctions(pScriptItem->m_TreeItem, chardataNode, data, len);
				}
				else if (!wcscmp(pScriptItem->m_name, L"VBScript"))
				{
					AddVBScriptFunctions(pScriptItem->m_TreeItem, chardataNode, data, len);
				}
			}

			CComPtr<ILDOMNode> nextSibling;
			node->get_nextSibling(&nextSibling);
			node = nextSibling;
		}
	}
	else
	{
#if 0
		CItemElement* pElement = new CItemElement;
		pElement->m_element = element;
		pElement->m_name = tagName;

		m_treeCtl->CreateItem((DWORD)pElement, NULL, 0, -1/*cChildren*/, &pElement->m_TreeItem);
		item = pElement->m_TreeItem;

		m_treeCtl->Expand(item, TV_EXPAND, NULL);
#endif

		int n = 0;
		while (events[n].m_attName)
		{
			CComBSTR value;
			element->getAttribute(events[n].m_attName, &value);
			if (value.Length())
			{
				CItemEvent* pEventItem = new CItemEvent;
				pEventItem->m_name = events[n].m_attName;

				m_treeCtl->CreateItem((DWORD)pEventItem, NULL, 2, 0/*cChildren*/, &pEventItem->m_TreeItem);
			//	item = pScriptItem->m_TreeItem;

				if (item == NULL)
				{
					CItemElement* pElement = new CItemElement;
					pElement->m_element = element;
					pElement->m_name = tagName;

					m_treeCtl->CreateItem((DWORD)pElement, NULL, 0, -1/*cChildren*/, &pElement->m_TreeItem);
					item = pElement->m_TreeItem;

					m_treeCtl->Expand(item, TV_EXPAND, NULL);
				}

				item->AppendItem(pEventItem->m_TreeItem);
			}

			n++;
		}
	}

	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node != NULL)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CComPtr<IUITreeItem> childitem;
			BuildTree(element, &childitem);

			if (childitem)
			{
				if (item == NULL)
				{
					CItemElement* pElement = new CItemElement;
					pElement->m_element = element;
					pElement->m_name = tagName;

					m_treeCtl->CreateItem((DWORD)pElement, NULL, 0, -1/*cChildren*/, &pElement->m_TreeItem);
					item = pElement->m_TreeItem;

					m_treeCtl->Expand(item, TV_EXPAND, NULL);
				}

				item->AppendItem(childitem);
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	if (item)
		(*pVal =	item)->AddRef();
	else
		*pVal = NULL;
}

void CScriptOutlineDlg::BuildTree()
{
	m_treeCtl->ResetContent(NULL);

	if (m_viewGroup)
	{
		CComPtr<IEXMLDocument> edocument;
		m_viewGroup->get_eXMLDocument(&edocument);

		CComPtr<ILDOMDocument> domdocument;
		edocument->get_DOMDocument(&domdocument);

		CComPtr<ILDOMElement> documentElement;
		domdocument->get_documentElement(&documentElement);

		{
			CItem* pItem = new CItem;
			pItem->m_name = L"Client Scripts";
			m_treeCtl->InsertItem((DWORD)pItem, NULL, NULL, NULL, 0, 1, &pItem->m_TreeItem);
			m_treeCtl->Expand(pItem->m_TreeItem, TV_EXPAND, NULL);

			if (documentElement)
			{
			//	AddClientScripts(pItem->m_TreeItem, documentElement);

				CComPtr<IUITreeItem> treeItem;
				BuildTree(documentElement, &treeItem);
				if (treeItem)
				{
					pItem->m_TreeItem->AppendItem(treeItem);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CScriptOutlineDlg

LRESULT CScriptOutlineDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = m_hWnd;
	//get_hwnd(&hwnd);

//	m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
	m_treeCtl->SetSite(this);
	m_treeCtl->InsertColumn(0, L"", 160, TRUE, TRUE, NULL);

	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axtreeCtl.Create(hwnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axtreeCtl.AttachControl(m_treeCtl, &p);

	m_hIcons = ImageList_LoadBitmap(_Module.m_hInstResource, MAKEINTRESOURCE(IDB_SCRIPTOUTLINE), 16, 0, CLR_NONE);
	m_treeCtl->put_hImageList((DWORD)m_hIcons);

	IDispEventImpl<4, CScriptOutlineDlg, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

#if 1
	CComPtr<IEXMLDocument> document;
	m_viewGroup->get_eXMLDocument(&document);
	IDispEventImpl<2, CScriptOutlineDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(document);

	BuildTree();
#endif

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->AddEventHandler(this);

	return 0;
}

LRESULT CScriptOutlineDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 1
	CComPtr<IEXMLDocument> document;
	m_viewGroup->get_eXMLDocument(&document);
	IDispEventImpl<2, CScriptOutlineDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(document);
#endif

//	CComQIPtr<IUIActiveManager> uiActiveManager = m_app;
//	uiActiveManager->RemoveEventHandler(this);

	IDispEventImpl<4, CScriptOutlineDlg, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_treeCtl);
	m_treeCtl.Release();

	if (m_hIcons)
	{
		ImageList_Destroy(m_hIcons);
		m_hIcons = NULL;
	}

	return 0;
}

LRESULT CScriptOutlineDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axtreeCtl.MoveWindow(0, 0, client.right, client.bottom, TRUE);

	return 0;
}

STDMETHODIMP CScriptOutlineDlg::GetItemText(ULONG itemdata, LONG column, BSTR * pVal)
{
	CItem* pItem = (CItem*)itemdata;
	*pVal = SysAllocString(pItem->m_name);

	return S_OK;
}

void __stdcall CScriptOutlineDlg::OnItemClick(IUITreeItem* item)
{
	DWORD itemdata;
	m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

	CComPtr<IEXMLDocument> edocument;
	m_viewGroup->get_eXMLDocument(&edocument);

	CComPtr<ILDOMDocument> document;
	edocument->get_DOMDocument(&document);

	CItem* pItem = (CItem*)itemdata;
	if (pItem->m_type == SO_FUNCTION)
	{
		CItemFunction* pFItem = (CItemFunction*)pItem;

		CComQIPtr<ILDOMDocumentRange> documentRange = document;
		if (documentRange)
		{
			CComPtr<ILDOMRange> range;
			documentRange->createRange(&range);
			if (range)
			{
				range->setStart(pFItem->m_node, pFItem->m_startOffset);
				range->setEnd(pFItem->m_node, pFItem->m_endOffset);

				CEXMLViewGroup* pViewGroup = static_cast<CEXMLViewGroup*>(m_viewGroup);

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
	}
}

void __stdcall CScriptOutlineDlg::OnItemDblClick(IUITreeItem* item)
{
	ATLASSERT(0);
#if 0
	DWORD itemdata;
	m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

	CItem* pItem = (CItem*)itemdata;
	if (pItem->m_type == SO_SCRIPT)
	{
		CItemScript* pScript = (CItemScript*)pItem;

		CComPtr<IEElement> eElement;
		m_viewGroup->m_pDocument->GetEElementFromDOMElement(pScript->m_element, &eElement);

		CEScriptElement* pScriptElement = static_cast<CEScriptElement*>(eElement.p);

		{
			CComQIPtr<ILXAddin> addin = m_viewGroup->m_pDocument->m_app;

			pScriptElement->m_pScriptDocument->m_app = addin;

			CComPtr<ILXAddinSite> addinSite;
			addin->GetSite(&addinSite);

			CComPtr<ILXFrameworkFrame> lxframe;
			addinSite->GetFrame(&lxframe);

			ATLASSERT(0);
#if 0
			CComQIPtr<IEFrame> eframe = lxframe;

			pScriptElement->m_pScriptDocument->ShowViews(eframe);
#endif
		}
	}
#endif
}

#if 0
STDMETHODIMP CScriptOutlineDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
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

		m_viewGroup = viewGroup;

		CComPtr<IEXMLDocument> document;
		m_viewGroup->get_eXMLDocument(&document);
		IDispEventImpl<2, CScriptOutlineDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(document);

		BuildTree();

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CScriptOutlineDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
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

	CComPtr<IEXMLDocument> document;
	m_viewGroup->get_eXMLDocument(&document);
	IDispEventImpl<2, CScriptOutlineDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(document);

	m_viewGroup.Release();

	return S_OK;
}
#endif

HRESULT __stdcall CScriptOutlineDlg::OnDOMEvent(ILDOMEvent* evt)
{
	BuildTree();

	return S_OK;
}

BEGIN_CMD_MAP(CScriptOutlineDlg)
	CMD_HANDLER(ID_SCRIPTS_NEWSCRIPT, OnScriptsNewScript)
END_CMD_MAP()

LRESULT CScriptOutlineDlg::OnScriptsNewScript(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_viewGroup)
	{
		CComPtr<IEXMLDocument> eXMLDocument;
		m_viewGroup->get_eXMLDocument(&eXMLDocument);

		CComQIPtr<IEDocument> eDocument = eXMLDocument;

		CComPtr<ILDOMDocument> document;
		eXMLDocument->get_DOMDocument(&document);

		CComPtr<ILDOMElement> documentElement;
		document->get_documentElement(&documentElement);

		//CSVGFilterOptionsDlg dlg;
		//dlg.m_document = document;

		//if (dlg.DoModal() == IDOK)
		{
			CComPtr<IOleUndoManager> undoManager;
			eDocument->get_undoManager(&undoManager);

			CComObject<CUndoParent>* pParentUndo;
			CComObject<CUndoParent>::CreateInstance(&pParentUndo);
			if (pParentUndo)
			{
				pParentUndo->AddRef();	// ???
				undoManager->Open(pParentUndo);

				//CComPtr<ILSVGElement> svgDefsElement;
				//eXMLDocument->FindOrCreateSVGDefs(&svgDefsElement);

				//CComPtr<ILDOMElement> headElement = FindByTagNameNS(documentElement, L"http://www.w3.org/2001/SMIL20/Language", L"head");

				//if (headElement)
				{
					CComPtr<ILDOMElement> svgFilterElement;
					document->createElement(/*L"http://www.w3.org/2001/SMIL20/Language",*/ L"script", (ILDOMElement**)&svgFilterElement);

					if (svgFilterElement)
					{
						CComPtr<ILDOMCDATASection> cdata;
						document->createCDATASection(CComBSTR(L""), &cdata);
						svgFilterElement->appendChild(cdata, NULL);

						
						//svgFilterElement->setAttribute(L"id", dlg.m_id);

						//CComPtr<IOleUndoManager> undoManager;
						//m_document->get_undoManager(&undoManager);

						CComObject<CWEUndoNewElement>* pUndo;
						CComObject<CWEUndoNewElement>::CreateInstance(&pUndo);
						if (pUndo)
						{
						//	pUndo->AddRef();
							pUndo->m_pDocument = static_cast<CEXMLDocument*>(eXMLDocument.p);

							pUndo->DoInitial(undoManager, svgFilterElement, documentElement, NULL);

							// TODO: do this here?
							//CComPtr<IWebXMLViewGroup> viewGroup;
							//m_document->GetActiveViewGroup(&viewGroup);
							//if (viewGroup)
							{
								CEXMLViewGroup* pViewGroup = static_cast<CEXMLViewGroup*>(m_viewGroup);

								CComPtr<IEElement> eElement;
								eXMLDocument->GetEElementFromDOMElement(svgFilterElement, &eElement);
#if 0	// ???
								pViewGroup->m_activeReferencedElement = eElement;	// ??? reference element is still NULL
#endif
								m_viewGroup->ActivateElement(eElement, 0, NULL);
							}
						}
					}
				}
				/*
				else
				{
					MessageBox("No head element", "LXMLEditor", MB_OK);
				}
				*/

				undoManager->Close(pParentUndo, TRUE/*commit*/);
			}
		}
	}

	return 0;
}

#endif