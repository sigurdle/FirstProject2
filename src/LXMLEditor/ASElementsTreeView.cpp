// ASElementsTreeView.cpp : Implementation of CASElementsTreeView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "ASElementsTreeView.h"

#if 0

#include "DTDDocument.h"


/////////////////////////////////////////////////////////////////////////////
// CASElementsTreeView

int CASElementsTreeView::FinalConstruct()
{
	HRESULT hr;

//	hr = m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
	if (FAILED(hr)) return hr;

	m_treeCtl->SetSite(this);

	m_hIcons = ImageList_LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_ASTREEICONS), 16, 0, RGB(255, 255, 255));
	m_treeCtl->put_hImageList((DWORD)m_hIcons);

	m_treeCtl->InsertColumn(0, L"Name", 120, TRUE, TRUE, NULL);

	return 0;
}

void CASElementsTreeView::FinalRelease()
{
	if (m_hIcons)
	{
		ImageList_Destroy(m_hIcons);
		m_hIcons = NULL;
	}
}

void CASElementsTreeView::Populate(IUITreeItem* parentItem, IASContentModel* asCM)
{
	CComQIPtr<IASObjectList> subModels;
	asCM->get_subModels(&subModels);

	long length;
	subModels->get_length(&length);

	for (int i = 0; i < length; i++)
	{
		CComPtr<IASObject> asObject;
		subModels->item(i, &asObject);

		CComQIPtr<IASContentModel> asCM2 = asObject;
		if (asCM2)
		{
			Populate(parentItem, asCM2);
		}
		else
		{
			CComQIPtr<IASElementDeclaration> elementDecl = asObject;
			if (elementDecl)
			{
				CComPtr<IUITreeItem> newItem;
				m_treeCtl->InsertItem((DWORD)elementDecl.p, parentItem, NULL, NULL, 0/*m_iIcon*/, 1/*pNewItem->m_cChildren*/, &newItem);
			}
		}
	}
}

void CASElementsTreeView::Populate(IUITreeItem* item, IASElementDeclaration* elementDecl)
{
	CComQIPtr<IASNamedObjectMap> attributes;
	elementDecl->get_ASAttributeDecls(&attributes);

	long length;
	attributes->get_length(&length);

	for (int i = 0; i < length; i++)
	{
		CComPtr<IASAttributeDeclaration> attributeDecl;
		attributes->item(i, (IASObject**)&attributeDecl);

		CComPtr<IUITreeItem> newItem;
		m_treeCtl->InsertItem((DWORD)attributeDecl.p, item, NULL, NULL, 1/*m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
	}

	CComQIPtr<IASContentModel> asCM;
	elementDecl->get_asCM(&asCM);
	if (asCM)
	{
		Populate(item, asCM);
	}
}

void CASElementsTreeView::Populate(IUITreeItem* parentItem, IASNamedObjectMap* elementMap)
{
	long length;
	elementMap->get_length(&length);

	for (int i = 0; i < length; i++)
	{
		CComPtr<IASObject> asObject;
		elementMap->item(i, &asObject);

		CComQIPtr<IASElementDeclaration> elementDecl = asObject;
		ASSERT(elementDecl);

		CComPtr<IUITreeItem> newItem;
		m_treeCtl->InsertItem((DWORD)elementDecl.p, parentItem, NULL, NULL, 0/*m_iIcon*/, 1/*pNewItem->m_cChildren*/, &newItem);
	}
}

LRESULT CASElementsTreeView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axtreeCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axtreeCtl.AttachControl(m_treeCtl, &p);
	IDispEventImpl<4, CASElementsTreeView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

	CComQIPtr<IASNamedObjectMap> elementMap;
	m_document->m_dtdModel->get_elementDeclarations(&elementMap);

	{
		CComPtr<IUITreeItem> newItem;
		m_treeCtl->InsertItem((DWORD)NULL, NULL, NULL, L"Document Root", 2/*m_iIcon*/, -1/*pNewItem->m_cChildren*/, &newItem);
	}

	{
		CComPtr<IUITreeItem> newItem;
		m_treeCtl->InsertItem((DWORD)NULL, NULL, NULL, L"Global Templates", 3/*m_iIcon*/, -1/*pNewItem->m_cChildren*/, &newItem);

		Populate(newItem, elementMap);
	}

	return 0;
}

LRESULT CASElementsTreeView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<4, CASElementsTreeView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_treeCtl);

	return 0;
}

LRESULT CASElementsTreeView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axtreeCtl.MoveWindow(0, 0, client.right, client.bottom);
	return 0;
}

STDMETHODIMP CASElementsTreeView::GetItemText(ULONG itemdata, LONG column, BSTR * pVal)
{
	ASSERT(pVal);
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;

	CComQIPtr<IASObject> asObject = (IUnknown*)itemdata;

	CComQIPtr<IASElementDeclaration> elementDecl = asObject;
	CComQIPtr<IASAttributeDeclaration> attributeDecl = asObject;

	if (elementDecl)
	{
		elementDecl->get_nodeName(pVal);
	}
	else if (attributeDecl)
	{
		attributeDecl->get_nodeName(pVal);
	}

	return S_OK;
}

#include "..\OleDataObject.h"

HRESULT __stdcall CASElementsTreeView::OnItemClick(IUITreeItem* item)
{
	IUnknown* p;
	m_treeCtl->GetItemInfo(item, (DWORD*)&p, NULL, NULL);

	CComQIPtr<IASElementDeclaration> elementDecl = p;
	if (elementDecl)
	{
		CComPtr<ILDOMDocument> document;
		document.CoCreateInstance(CLSID_LDOMDocument);

		CComPtr<ILDOMNode> node = document;

		CComPtr<IUITreeItem> item2 = item;
		while (item2)
		{
			IUnknown* p;
			m_treeCtl->GetItemInfo(item2, (DWORD*)&p, NULL, NULL);

			CComQIPtr<IASElementDeclaration> elementDecl2 = p;
			if (elementDecl2 == NULL) break;

			BSTR bnodeName;
			elementDecl2->get_nodeName(&bnodeName);
			_bstr_t nodeName = _bstr_t(bnodeName, false);

			CComPtr<ILDOMElement> element2;
			document->createElement(nodeName, &element2);

			node->appendChild(element2, NULL);
			node = element2;

			CComPtr<IUITreeItem> parentItem;
			m_treeCtl->GetParentItem(item2, &parentItem);
			item2 = parentItem;
		}

		BSTR bxml;
		document->saveXML(_variant_t(/*NULL*/), &bxml);
		_bstr_t xml = _bstr_t(bxml, false);

		HGLOBAL hData = GlobalAlloc(GMEM_SHARE, (xml.length()+1)*2);
		if (hData)
		{
			WCHAR* p = (WCHAR*)GlobalLock(hData);
			if (p)
			{
				UINT cFormat = RegisterClipboardFormat("Xmill.ASPath");
				CopyMemory(p, (BSTR)xml, (xml.length()+1)*2);
				GlobalUnlock(hData);

				COleDataObject* dataObject;
				CComObject<COleDataObject>::CreateInstance(&dataObject);
				dataObject->AddRef();

				CMyDropSource*  dropSource = new CMyDropSource;

				/*
				STGMEDIUM	stg = {0};
				stg.tymed = TYMED_HGLOBAL;
				stg.hGlobal = hData;
				stg.pUnkForRelease = NULL;
				
				FORMATETC	etc = {0};
				etc.cfFormat = CF_HDROP;//CF_UNICODETEXT;//49285;//RegisterClipboardFormat(CFSTR_SHELLURL);//CF_TEXT;
				etc.tymed = TYMED_HGLOBAL;
				etc.ptd = NULL;
				etc.dwAspect = DVASPECT_CONTENT;
				etc.lindex = -1;
				*/
				STGMEDIUM stgm;
				stgm.tymed = TYMED_HGLOBAL;
				stgm.pUnkForRelease = NULL;
				stgm.hGlobal = hData;

				FORMATETC etc = { cFormat, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
				dataObject->SetData(&etc, &stgm, TRUE);

				DWORD dropEffect = 0;
				HRESULT hr = ::DoDragDrop(dataObject, dropSource, DROPEFFECT_LINK | DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect);

				if (hr == DRAGDROP_S_DROP)
				{
					if (dropEffect/* & DROPEFFECT_MOVE*/)
					{
					}
				}

				dataObject->Release();
			}
			GlobalFree(hData);
		}
	}

	return S_OK;
}

HRESULT __stdcall CASElementsTreeView::OnItemExpanding(IUITreeItem* item, VARIANT_BOOL bExpanding, BOOL* bCancel)
{
	IUnknown* p;
	m_treeCtl->GetItemInfo(item, (DWORD*)&p, NULL, NULL);

	CComQIPtr<IASElementDeclaration> elementDecl = p;
	if (elementDecl)
	{
		if (bExpanding)
			Populate(item, elementDecl);
		else
			m_treeCtl->ResetContent(item);
	}

	return S_OK;
}

#endif