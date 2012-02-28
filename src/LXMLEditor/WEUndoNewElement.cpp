// WEUndoNewElement.cpp : Implementation of CWEUndoNewElement
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "WEUndoNewElement.h"

#include "EXMLDocument.h"

#if 0

ILDOMNode* GetElementFromUniqID(ILDOMNode* parent, GUID& guid);

void WriteStringToStream(IStream* pStream, BSTR bstr);
void ReadStringFromStream(IStream* pStream, BSTR* bstr);
HRESULT WriteElementToStream(IStream* pStream, ILDOMDocument* document, ILDOMElement* element);
HRESULT ReadElementFromStream(IStream* pStream, ILDOMDocument* document, ILDOMElement** pelement);

/////////////////////////////////////////////////////////////////////////////
// CWEUndoMoveObjects

STDMETHODIMP CWEUndoNewElement::GetDescription(/* [out] */ BSTR __RPC_FAR *pBstr)
{
	*pBstr = SysAllocString(L"New Element");
	return S_OK;
}

STDMETHODIMP CWEUndoNewElement::GetUnitType(/* [out] */ CLSID __RPC_FAR *pClsid, /* [out] */ LONG __RPC_FAR *plID)
{
//	*pClsid = CLSID_WEUndoMoveObjects;
	*plID = 0;

	return S_OK;
}

STDMETHODIMP CWEUndoNewElement::OnNextAdd(void)
{
	return S_OK;
}

HRESULT CWEUndoNewElement::DoInitial(IOleUndoManager *undoManager, ILDOMNode* node, ILDOMNode* parentNode, ILDOMNode* beforeNode)
{
	parentNode->get_uniqID(&m_guidParentNode);

	if (beforeNode)
		beforeNode->get_uniqID(&m_guidBeforeNode);
	else
		m_guidBeforeNode = GUID_NULL;

	node->get_uniqID(&m_guidNode);

	parentNode->insertBefore(node, CComVariant(beforeNode), NULL);

//	m_bRedo = true;
//	Do(undoManager);
	undoManager->Add(this);

	return S_OK;
}

STDMETHODIMP CWEUndoNewElement::Do(/* [in] */ IOleUndoManager __RPC_FAR *pUndoManager)
{
	ATLASSERT(m_pDocument);
	CComQIPtr<ILDOMDocument> domdocument;
	m_pDocument->get_DOMDocument(&domdocument);

	CComQIPtr<ILDOMElement> documentElement;
	domdocument->get_documentElement(&documentElement);

	if (m_bRedo)
	{
		CWEUndoSourceLast::Do(pUndoManager);

		ATLASSERT(m_pStream != NULL);

		CComPtr<ILDOMElement> element;
		ReadElementFromStream(m_pStream, domdocument, &element);

		ILDOMNode* parentNode = GetElementFromUniqID(documentElement, m_guidParentNode);
		ATLASSERT(parentNode);

		if (m_guidBeforeNode != GUID_NULL)
		{
			ILDOMNode* beforeNode = GetElementFromUniqID(documentElement, m_guidBeforeNode);
			ATLASSERT(beforeNode);
			parentNode->insertBefore(element, _variant_t(beforeNode), NULL);
		}
		else
		{
			parentNode->appendChild(element, NULL);
		}

		m_pStream->Release();
		m_pStream = NULL;
	}
	else	// undo
	{
		ATLASSERT(0);
#if 0
		ATLASSERT(m_pStream == NULL);

	// Remember element
		HRESULT hr = CreateStreamOnHGlobal(NULL, TRUE, &m_pStream);
		ATLASSERT(SUCCEEDED(hr));

		ILDOMNode* pDOMElement = GetElementFromUniqID(documentElement, m_guidNode);
		if (pDOMElement)
		{
			CElementImpl* pElement = m_pDocument->m_pTree->FindDOMElement(pDOMElement);
			if (pElement)
			{
				WriteElementToStream(m_pStream, domdocument, (ILDOMElement*)pElement->m_domElement);
			}
			else
				ATLASSERT(0);

			CComQIPtr<ILDOMNode> parentNode;
			pDOMElement/*pElement->m_domElement*/->get_parentNode(&parentNode);
			ATLASSERT(parentNode);

			parentNode->removeChild(pDOMElement/*pElement->m_domElement*/, NULL);
		}

		// Seek to beginning
		LARGE_INTEGER offset;
		offset.QuadPart = 0;
		m_pStream->Seek(offset, STREAM_SEEK_SET, NULL);

		CWEUndoSourceLast::Do(pUndoManager);
#endif
	}

	m_bRedo = !m_bRedo;
	pUndoManager->Add(this);

	return S_OK;
}

#endif