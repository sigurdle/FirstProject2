// WEUndoDeleteObjects.cpp : Implementation of CWEUndoDeleteObjects
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "WEUndoDeleteObjects.h"

#include "EXMLDocument.h"

#if 0
ILDOMNode* GetElementFromUniqID(ILDOMNode* parent, GUID& guid);

void WriteStringToStream(IStream* pStream, BSTR bstr)
{
	HRESULT hr;

	DWORD len = SysStringLen(bstr);
	hr = pStream->Write(&len, 4, NULL);
	ATLASSERT(SUCCEEDED(hr));

	hr = pStream->Write(bstr, len*2, NULL);
	ATLASSERT(SUCCEEDED(hr));
}

void ReadStringFromStream(IStream* pStream, BSTR* bstr)
{
	HRESULT hr;

	DWORD len;
	hr = pStream->Read(&len, 4, NULL);
	ATLASSERT(SUCCEEDED(hr));

	*bstr = SysAllocStringLen(NULL, len);
	hr = pStream->Read(*bstr, len*2, NULL);
	ATLASSERT(SUCCEEDED(hr));
}

HRESULT WriteElementToStream(IStream* pStream, ILDOMDocument* document, ILDOMElement* element)
{
	ATLASSERT(0);
#if 0
	HRESULT hr;

	GUID guid;
	element->get_uniqID(&guid);
	hr = WriteClassStm(pStream, guid);
	ATLASSERT(SUCCEEDED(hr));

	CComBSTR tagName;
	element->get_tagName(&tagName);
	tagName.WriteToStream(pStream);//WriteStringToStream(pStream, tagName);
	//SysFreeString(tagName);
	//tagName->

	long length;
	long i;

// Attributes
	CComPtr<ILDOMNamedNodeMap> attributes;
	element->get_attributes(&attributes);
	attributes->get_length(&length);

	pStream->Write(&length, 4, NULL);

	for (i = 0; i < length; i++)
	{
		CComQIPtr<ILDOMAttr> attr;
		attributes->item(i, (ILDOMNode**)&attr);

		BSTR name;
		attr->get_name(&name);

		BSTR value;
		attr->get_value(&value);

		WriteStringToStream(pStream, name);
		WriteStringToStream(pStream, value);

		SysFreeString(name);
		SysFreeString(value);
	}

// Children
	CComPtr<ILDOMNodeList> childNodes;
	element->get_childNodes(&childNodes);

	childNodes->get_length(&length);
	pStream->Write(&length, 4, NULL);

	for (i = 0; i < length; i++)
	{
		CComPtr<ILDOMNode> child;
		childNodes->item(i, &child);

		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);

		ATLASSERT(sizeof(LDOMNodeType) == 4);
		pStream->Write(&nodeType, 4, NULL);

		if (nodeType == NODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> childelement = child;
			WriteElementToStream(pStream, document, childelement);	// Recurse
		}
		else if (nodeType == NODE_TEXT)
		{
			CComQIPtr<ILDOMText> text = child;

			BSTR s;
			text->get_data(&s);

			WriteStringToStream(pStream, s);

			SysFreeString(s);
		}
	}
#endif
	return S_OK;
}

HRESULT ReadElementFromStream(IStream* pStream, ILDOMDocument* document, ILDOMElement** pelement)
{
	ATLASSERT(0);
#if 0
	GUID guid;
	ReadClassStm(pStream, &guid);

	CComBSTR tagName;
	//ReadStringFromStream(pStream, &tagName);
	tagName.ReadFromStream(pStream);

	CComPtr<ILDOMElement> element;
	document->createElement(tagName, &element);
	//SysFreeString(tagName);

	element->put_uniqID(guid);

	unsigned long length;
	unsigned long i;

// Attributes
	pStream->Read(&length, 4, NULL);
	for (i = 0; i < length; i++)
	{
		BSTR name;
		BSTR value;

		ReadStringFromStream(pStream, &name);
		ReadStringFromStream(pStream, &value);

		LXML::Attr* attr = document->createAttribute(name);
		attr->put_value(value);
		element->setAttributeNode(attr);	// Add the attribute to the element

		SysFreeString(name);
		SysFreeString(value);
	}

// Children
	pStream->Read(&length, 4, NULL);
	for (i = 0; i < length; i++)
	{
		LDOMNodeType nodeType;
		ATLASSERT(sizeof(LDOMNodeType) == 4);
		pStream->Read(&nodeType, 4, NULL);

		if (nodeType == NODE_ELEMENT)
		{
			CComPtr<ILDOMElement> childelement;
			ReadElementFromStream(pStream, document, &childelement);
			element->appendChild(childelement, NULL);
		}
		else
			ATLASSERT(0);
	}

	*pelement = element.Detach();
#endif
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CWEUndoMoveObjects

STDMETHODIMP CWEUndoDeleteObjects::GetDescription(/* [out] */ BSTR __RPC_FAR *pBstr)
{
	*pBstr = SysAllocString(L"Delete");
	return S_OK;
}

STDMETHODIMP CWEUndoDeleteObjects::GetUnitType(/* [out] */ CLSID __RPC_FAR *pClsid, /* [out] */ LONG __RPC_FAR *plID)
{
//	*pClsid = CLSID_WEUndoMoveObjects;
	*plID = 0;

	return S_OK;
}

STDMETHODIMP CWEUndoDeleteObjects::OnNextAdd(void)
{
	return S_OK;
}

STDMETHODIMP CWEUndoDeleteObjects::Do(/* [in] */ IOleUndoManager __RPC_FAR *pUndoManager)
{
	ATLASSERT(m_pDocument);

	CComPtr<ILDOMDocument> domdocument;
	m_pDocument->get_DOMDocument(&domdocument);

	CComQIPtr<ILDOMElement> documentElement;
	domdocument->get_documentElement(&documentElement);

	if (m_bRedo)
	{
		CWEUndoSourceLast::Do(pUndoManager);

		ATLASSERT(m_pStream == NULL);
	// Remember objects
		HRESULT hr = CreateStreamOnHGlobal(NULL, TRUE, &m_pStream);
		ATLASSERT(SUCCEEDED(hr));

		int i;

		DWORD n = m_targetElements.GetSize();
		m_pStream->Write(&n, 4, NULL);

		for (i = 0; i < n; i++)
		{
			CComQIPtr<ILDOMElement> pDOMElement = GetElementFromUniqID(documentElement, m_targetElements[i]);
			if (pDOMElement)
			{
				//CElementImpl* pElement = m_pDocument->m_pTree->FindDOMElement(pDOMElement);
				//if (pElement)
				{
					WriteElementToStream(m_pStream, domdocument, pDOMElement/*(ILDOMElement*)pElement->m_domElement*/);
				}
			}
		}

		// Seek to beginning
		LARGE_INTEGER offset;
		offset.QuadPart = 0;
		m_pStream->Seek(offset, STREAM_SEEK_SET, NULL);

	// Delete objects
		for (i = 0; i < n; i++)
		{
			ILDOMNode* pDOMElement = GetElementFromUniqID(documentElement, m_targetElements[i]);
			if (pDOMElement)
			{
				//CElementImpl* pElement = m_pDocument->m_pTree->FindDOMElement(pDOMElement);
				//if (pElement)
				{
					CComPtr<ILDOMNode> parentNode;
					pDOMElement/*pElement->m_domElement*/->get_parentNode(&parentNode);
					ATLASSERT(parentNode);

					parentNode->removeChild(pDOMElement/*pElement->m_domElement*/, NULL);
				}
			}
		}
	}
	else
	{
		ATLASSERT(0);
#if 0
		ATLASSERT(m_pStream != NULL);

		DWORD n;
		m_pStream->Read(&n, 4, NULL);

		for (int i = 0; i < n; i++)
		{
			CComPtr<ILDOMElement> element;
			ReadElementFromStream(m_pStream, domdocument, &element);

			ILDOMNode* parentNode = GetElementFromUniqID(documentElement, m_parentElements[i]);
			ATLASSERT(parentNode);

			if (m_beforeElements[i] != GUID_NULL)
			{
				ILDOMNode* beforeNode = GetElementFromUniqID(documentElement, m_beforeElements[i]);
				ATLASSERT(beforeNode);
				parentNode->insertBefore(element, beforeNode, NULL);
			}
			else
			{
				parentNode->appendChild(element, NULL);
			}
		}

		m_pStream->Release();
		m_pStream = NULL;

		CWEUndoSourceLast::Do(pUndoManager);
#endif
	}

	m_bRedo = !m_bRedo;
	pUndoManager->Add(this);
	return S_OK;
}

#endif