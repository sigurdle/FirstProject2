// XSLTTemplatesDlg.cpp : Implementation of CXSLTTemplatesDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "XSLTTemplatesDlg.h"

#include "EXMLDocument.h"
#include "EXMLViewGroup.h"
#include "EXMLLayoutView.h"

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CXSLTTemplatesDlg

#if 0
int CXSLTTemplatesDlg::FinalConstruct()
{
	ErrorCode hr;

//	hr = m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
	if (FAILED(hr)) return hr;

//	m_treeCtl->SetSite(this);

//	m_hIcons = ImageList_LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_ASTREEICONS), 16, 0, RGB(255, 255, 255));
//	m_treeCtl->put_hImageList((DWORD)m_hIcons);

	m_treeCtl->InsertColumn(0, L"Name", 120, TRUE, TRUE, NULL);

	return 0;
}

LRESULT CXSLTTemplatesDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axtreeCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axtreeCtl.AttachControl(m_treeCtl, &p);
	IDispEventImpl<4, CXSLTTemplatesDlg, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->AddEventHandler(this);


	::RegisterDragDrop(m_hWnd, static_cast<IDropTarget*>(this));

	IDispEventImpl<2, CXSLTTemplatesDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_document);

	BuildTree();

	return 0;
}

LRESULT CXSLTTemplatesDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<2, CXSLTTemplatesDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_document);
	RevokeDragDrop(m_hWnd);

//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->RemoveEventHandler(this);

	IDispEventImpl<4, CXSLTTemplatesDlg, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_treeCtl);

	return 0;
}

LRESULT CXSLTTemplatesDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axtreeCtl.MoveWindow(0, 0, client.right, client.bottom);

	return 0;
}
#endif

#if 0
ErrorCode CXSLTTemplatesDlg::DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	return S_OK;
}

ErrorCode CXSLTTemplatesDlg::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	*pdwEffect = DROPEFFECT_COPY;

#if 0
	if (m_prevDropItem)
	{
		DWORD state;
		m_treeCtl->GetItemState(m_prevDropItem, &state);
		m_treeCtl->SetItemState(m_prevDropItem, state &~ 2);
		m_prevDropItem = NULL;
	}

	POINT point;
	point.x = pt.x;
	point.y = pt.y;
	::ScreenToClient(m_axtreeCtl.m_hWnd, &point);

	DWORD item;
	DWORD flags;
	m_treeCtl->HitTest(point, &flags, &item);
	if (item)
	{
		DWORD state;
		m_treeCtl->GetItemState(item, &state);
		m_treeCtl->SetItemState(item, state | 2);
		m_prevDropItem = item;
	}
#endif

	return S_OK;
}

ErrorCode CXSLTTemplatesDlg::DragLeave()
{
#if 0
	if (m_prevDropItem)
	{
		DWORD state;
		m_treeCtl->GetItemState(m_prevDropItem, &state);
		m_treeCtl->SetItemState(m_prevDropItem, state &~ 2);
		m_prevDropItem = NULL;
	}
#endif

	return S_OK;
}

ErrorCode CXSLTTemplatesDlg::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
#if 0
	CWebSite* pWebSite = (CWebSite*)m_document.p;

	DWORD parent_id;

	if (m_prevDropItem)
	{
		DWORD state;
		m_treeCtl->GetItemState(m_prevDropItem, &state);
		m_treeCtl->SetItemState(m_prevDropItem, state &~ 2);

		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(m_prevDropItem, (DWORD*)&pItem, NULL, NULL);

		if (pItem->m_type == 1)	// Dropped on directory
			parent_id = pItem->m_dbid;
		else
			parent_id = ((CSiteItem*)pItem->m_parent)->m_dbid;

		m_prevDropItem = NULL;
	}
	else
	{
		parent_id = m_rootFolderId;
	}
#endif

	ASSERT(0);
#if 0
	COleDataObjectWrapper dataObject;
	dataObject.Attach(pDataObject);

	HGLOBAL hData;

	if (hData = dataObject.GetGlobalData(RegisterClipboardFormat("Xmill.ASPath")))
	{
		WCHAR* xml = (WCHAR*)GlobalLock(hData);
		if (xml)
		{
		//
#if 0
			CComQIPtr<ILDOMElement> parentElement = parentNode;
			BSTR bnodeName;

			BSTR bnamespaceURI;
			parentElement->get_namespaceURI(&bnamespaceURI);
			_bstr_t namespaceURI = _bstr_t(bnamespaceURI, false);

			BSTR btagName;
			parentElement->get_localName(&btagName);	// Try local name first
			if (SysStringLen(btagName) == 0)
			{
				SysFreeString(btagName);
				parentElement->get_tagName(&btagName);	// Then try full qualified name
			}
			_bstr_t tagName = _bstr_t(btagName, false);

			if (!wcscmp(namespaceURI, L"http://www.w3.org/1999/XSL/Transform") && !wcsicmp(tagName, L"for-each"))
			{
			}
#endif

			CComPtr<ILDOMDocument> domdocument;
			m_document->get_DOMDocument(&domdocument);

			CComPtr<ILDOMElement> domdocumentElement;
			domdocument->get_documentElement(&domdocumentElement);

		//
			CComPtr<ILDOMDocument> document;
			document.CoCreateInstance(CLSID_LDOMDocument);
			VARIANT_BOOL bsuccess;
			document->loadXML(xml, &bsuccess);

			GlobalUnlock(xml);

			CComQIPtr<ILDOMElement> node;
			document->get_documentElement(&node);

			BSTR btagName;
			node->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);

			CComPtr<ILDOMElement> templateElement;
			domdocument->createElementNS(L"http://www.w3.org/1999/XSL/Transform", L"xsl:template", &templateElement);
			if (templateElement)
			{
				templateElement->setAttribute(L"match", tagName);

				domdocumentElement->appendChild(templateElement, NULL);
			}

#if 0
			CComPtr<ILDOMElement> element;

			CComQIPtr<ILDOMElement> node;
			document->get_documentElement(&node);
			while (node)
			{
				BSTR bnodeName;
				node->get_nodeName(&bnodeName);
				_bstr_t nodeName = _bstr_t(bnodeName, false);

				CComPtr<ILDOMElement> element2;
				m_document->createElementNS(L"http://www.w3.org/1999/XSL/Transform", L"xsl:for-each", &element2);
				if (element2)
				{
					element2->setAttribute(L"select", nodeName);

					if (element) element2->appendChild(element, NULL);
					element = element2;
				}

				CComPtr<ILDOMNode> firstChild;
				node->get_firstChild(&firstChild);
				node = firstChild;
			}

			if (element)
			{
			// Split the text in two at offset where we want to insert the new element
			// TODO, check for offset=0 and offset=right of text
				CComPtr<ILDOMText> rightText;
				text->splitText(m_dragOverOffset, &rightText);

				parentNode->insertBefore(element, rightText, NULL);

				success = TRUE;
			}
#endif
		}
	}
#endif

	return S_OK;
}
#endif

ErrorCode __stdcall CXSLTTemplatesDlg::OnDOMEvent(Web::Event* evt)
{
	ASSERT(0);
#if 0
	m_treeCtl->ResetContent(NULL);
#endif
	BuildTree();

	return Success;
}

ErrorCode __stdcall CXSLTTemplatesDlg::OnItemClick(ULONG_PTR item)
{
	ASSERT(0);
#if 0
	IUnknown* p;
	m_treeCtl->GetItemInfo(item, (DWORD*)&p, NULL, NULL);

	CComQIPtr<ILDOMElement> element = p;
	if (element)
	{
		CEXMLDocument* pDocument = (CEXMLDocument*)m_document.p;

		for (int i = 0; i < pDocument->m_viewGroups.GetSize(); i++)
		{
			CWebXMLViewGroup* pViewGroup = (CWebXMLViewGroup*)pDocument->m_viewGroups[i];
			for (int j = 0; j < pViewGroup->m_views.GetSize(); j++)
			{
				CComQIPtr<ISvgLayoutView> layout = pViewGroup->m_views[j];
				if (layout)
				{
					CSvgLayoutView* pLayout = (CSvgLayoutView*)layout.p;

					CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = pLayout->m_spUnknown;
					if (htmlActiveDoc)
					{
						htmlActiveDoc->SetElement(element/*m_viewGroup->m_outerElement*/);
					}
				}
			}
		}
	}
#endif

	return Success;
}

void CXSLTTemplatesDlg::BuildTree()
{
	ASSERT(0);
#if 0
	CComPtr<ILDOMDocument> document;
	m_document->get_DOMDocument(&document);

	CComPtr<ILDOMNodeList> nodelist;
	document->getElementsByTagNameNS(L"http://www.w3.org/1999/XSL/Transform", L"template", &nodelist);

	long length;
	nodelist->get_length(&length);
	for (int i = 0; i < length; i++)
	{
		CComPtr<ILDOMElement> element;
		nodelist->item(i, (ILDOMNode**)&element);

		BSTR bmatch;
		element->getAttribute(L"match", &bmatch);
		_bstr_t match = _bstr_t(bmatch, false);

		CComPtr<IUITreeItem> newItem;
		m_treeCtl->InsertItem((DWORD)element.p, NULL, NULL, match, -1, 0, &newItem);
	}
#endif
}

// IUIEventHandler
ErrorCode CXSLTTemplatesDlg::handleActivateObjectEvent(System::Object* object, long* cookie)
{
#if 0
//	CComQIPtr<IDocumentsClass> documentsClass = object;
	CComQIPtr<IWebXMLDocument> document = object;
/*
	if (documentsClass)
	{
		m_documentsClass = documentsClass;
	}
	else
		*/
	if (document)
	{
		CComPtr<IDocumentsClass> documentsClass;
		document->GetDocumentsClass(&documentsClass);
		if (documentsClass /* == XSLT*/)
		{
			if (m_document != NULL)
			{
				IDispEventImpl<2, CXSLTTemplatesDlg, &DIID__IESvgDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);
			}

			m_document = document;
			IDispEventImpl<2, CXSLTTemplatesDlg, &DIID__IESvgDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventAdvise(m_document);

			m_treeCtl->ResetContent(NULL);
			BuildTree();

			*cookie = 1;
		}
	}
#endif

	return Success;
}

ErrorCode CXSLTTemplatesDlg::handleDeactivateObjectEvent(System::Object* object, long cookie, bool* bAllow)
{
#if 0
	ATLASSERT(IsUnknownEqualUnknown(m_document, object));

	/*
	IDispEventImpl<2, CXSLTTemplatesDlg, &DIID__IESvgDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);
	m_document = NULL;

	m_treeCtl->ResetContent(NULL);
	*/

//	m_symbols.RemoveAll();
//	Invalidate();
#endif

	return Success;
}

}	// LXmlEdit
}
