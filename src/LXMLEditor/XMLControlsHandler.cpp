#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "XMLControlsHandler.h"

#if 0
#include "..\Utils\WCharString.h"

//IMPORTEXPORT ILDOMElement* GetElementByTagName(ILDOMNode* parentNode, BSTR tagName, BOOL bDeep = TRUE);
//IMPORTEXPORT ILDOMElement* GetElementByTagNameNS(ILDOMNode* parentNode, BSTR ns, BSTR tagName, BOOL bDeep = TRUE);

void GetPathNode(ILDOMElement* contextElement, BSTR path, ILDOMNode* *pVal)
{
	*pVal = NULL;

	WCHAR* p = path;

	//while (*p)
	{
		BOOL bAttribute = FALSE;
		if (*p == L'@')
		{
			bAttribute = TRUE;
			p++;
		}
	
		CWCharString part = L"";
	// Get part
		while (*p && *p != '/')
		{
			part += *p++;
		}

		CComPtr<ILDOMNode> node;

		if (bAttribute)
		{
			CComPtr<ILDOMAttr> attrNode;
			contextElement->getAttributeNode(part, &attrNode);

			node = attrNode;

			*pVal = node;
			if (*pVal) (*pVal)->AddRef();
		}
		else
		{
			ILDOMElement* childElement = GetElementByTagName(contextElement, part, FALSE);

			if (childElement)
			{
				if (*p == '/')	// Recurse
				{
					p++;

					GetPathNode(childElement, p, &node);
				}
				else
				{
					*pVal = childElement;
					(*pVal)->AddRef();
				}
			}
		}
	}
}

void SetPathNodeValue(ILDOMElement* contextElement, BSTR path, BSTR value)
{
	WCHAR* p = path;

	BOOL bAttribute = FALSE;
	if (*p == L'@')
	{
		bAttribute = TRUE;
		p++;
	}

	CWCharString part = L"";
// Get part
	while (*p && *p != '/')
	{
		part += *p++;
	}

	CComPtr<ILDOMNode> node;

	if (bAttribute)
	{
		if (value != NULL)
			contextElement->setAttribute(part, value);
		else
			contextElement->removeAttribute(part);
	}
	else
	{
		if (value != NULL)
		{
			CComPtr<ILDOMElement> element = GetElementByTagName(contextElement, part, FALSE);
			if (element == NULL)
			{
				CComPtr<ILDOMDocument> ownerDocument;
				contextElement->get_ownerDocument(&ownerDocument);

				ownerDocument->createElement(part, &element);

				contextElement->appendChild(element, NULL);
			}

			if (*p == '/')	// Recurse
			{
				p++;

				SetPathNodeValue(element, p, value);
			}
			else
			{
				element->put_TextContent(value);
			}
		}
		else
		{
			CComPtr<ILDOMElement> element = GetElementByTagName(contextElement, part, FALSE);
			if (element)
			{
				if (*p == '/')	// Recurse
				{
					p++;

					SetPathNodeValue(element, p, value);
				}
				else
				{
					element->put_TextContent(NULL);
				}

				CComPtr<ILDOMNode> child;
				element->get_firstChild(&child);
				if (child == NULL)	// No children, remove the element
				{
					contextElement->removeChild(element, NULL);
				}
			}
		}
	}
}

HRESULT GetPathNodeValue(ILDOMElement* element, BSTR path, BSTR* pVal)
{
	CComPtr<ILDOMNode> node;
	::GetPathNode(element, path, &node);

	if (node)
	{
		CComQIPtr<ILDOMAttr> attr = node;
		if (attr)
		{
			CComBSTR value;
			attr->get_value(&value);

			*pVal = value.Detach();
			return S_OK;
		}
		else
		{
			CComBSTR value;
			node->get_textContent(&value);

			*pVal = value.Detach();
			return S_OK;
		}
	}

	*pVal = NULL;
	return S_OK;
}

/*
CComBSTR CXMLData::GetDataValue(ILDOMElement* element)
{
	CComBSTR bstr;
	GetPathNodeValue(element, m_name, &bstr);

	return bstr;
}
*/

////////////////////////////////////////////////////////////////////
// CXMLControlsHandler

// virtual
BOOL CXMLControlsHandler::PathNodeExists(BSTR path)
{
	long ncount;
	m_viewGroup->GetSelectedCount(&ncount);

	for (int i = 0; i < ncount; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		m_viewGroup->GetSelectedElementN(i, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

		CComPtr<ILDOMNode> node;
		::GetPathNode(domElement, path, &node);

		if (node == NULL)
		{
			return FALSE;
		}
	}

	return TRUE;
}

// virtual
HRESULT CXMLControlsHandler::SetPathNodeValue(BSTR path, BSTR value)
{
	if (!m_bAnimation)
	{
		long ncount;
		m_viewGroup->GetSelectedCount(&ncount);

		for (int i = 0; i < ncount; i++)
		{
			CComPtr<IESelectedElement> selectedElement;
			m_viewGroup->GetSelectedElementN(i, &selectedElement);

			CComPtr<IEElement> eElement;
			selectedElement->get_eElement(&eElement);

			CComPtr<ILDOMElement> domElement;
			eElement->get_domElement(&domElement);

			::SetPathNodeValue(domElement, path, value);
		}
	}
	else
	{
		long ncount;
		m_viewGroup->GetSelectedCount(&ncount);

		for (int i = 0; i < ncount; i++)
		{
			CComPtr<IESelectedElement> selectedElement;
			m_viewGroup->GetSelectedElementN(i, &selectedElement);

			CComPtr<IEElement> eElement;
			selectedElement->get_eElement(&eElement);

			CComPtr<ILDOMElement> domElement;
			eElement->get_domElement(&domElement);

			CComBSTR attributeName;
			domElement->getAttribute(L"attributeName", &attributeName);

			if (!wcscmp(attributeName, &path[1]))
			{
			//	::SetPathNodeValue(domElement, path, value);

				CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;

				//if (wcscmp(attributeName, 
				if (selectedAnimationElement)//TRUE)	// TODO
				{
					//CComQIPtr<ILSMILAnimationTarget> animationTarget = animationTarget;

					CComQIPtr<ILAnimateXXX> animateXXX = domElement;

					long ncount;
					selectedAnimationElement->GetSelectedKeyTimesCount(&ncount);

					for (int i = 0; i < ncount; i++)
					{
						long keyFrame;
						selectedAnimationElement->GetKeyTimeSelected(i, &keyFrame);

						CComPtr<ILSMILAttributeValue> attributeValue;
						animateXXX->GetValue(keyFrame, &attributeValue);

						attributeValue->setStringValue(value);
					}
				}
			}
		}
	}

	return S_OK;
}

HRESULT CXMLControlsHandler::SetPathNodeValueIfNotExists(BSTR path, BSTR value)
{
	long ncount = m_viewGroup->GetSelectedCount();

	for (int i = 0; i < ncount; i++)
	{
		CComPtr<IESelectedElement> selectedElement = m_viewGroup->GetSelectedElementN(i);

		CComPtr<IEElement> eElement = selectedElement->get_eElement();

		CComPtr<ILDOMElement> domElement = eElement->get_domElement();

		CComPtr<ILDOMNode> node;
		::GetPathNode(domElement, path, &node);

		if (node == NULL)
		{
			::SetPathNodeValue(domElement, path, value);
		}
	}

	return S_OK;
}

HRESULT CXMLControlsHandler::GetPathNodeValue(BSTR path, BSTR* pVal)
{
	*pVal = NULL;

	if (!m_bAnimation)
	{
		long ncount;
		m_viewGroup->GetSelectedCount(&ncount);

		CComBSTR value;

		for (int i = 0; i < ncount; i++)
		{
			CComPtr<IESelectedElement> selectedElement;
			m_viewGroup->GetSelectedElementN(i, &selectedElement);

			CComPtr<IEElement> eElement;
			selectedElement->get_eElement(&eElement);

			CComPtr<ILDOMElement> domElement;
			eElement->get_domElement(&domElement);

			CComBSTR value2;
			::GetPathNodeValue(domElement, path, &value2);

			if (i == 0)
			{
				value = value2;
			}
			else if (cmpbstr(value, value2))
			{
				value.Empty();
				break;
			}
		}

		*pVal = value.Detach();
	}
	else
	{
		long ncount;
		m_viewGroup->GetSelectedCount(&ncount);

		for (int i = 0; i < ncount; i++)
		{
			CComPtr<IESelectedElement> selectedElement;
			m_viewGroup->GetSelectedElementN(i, &selectedElement);

			CComPtr<IEElement> eElement;
			selectedElement->get_eElement(&eElement);

			CComPtr<ILDOMElement> domElement;
			eElement->get_domElement(&domElement);

			CComBSTR attributeName;
			domElement->getAttribute(L"attributeName", &attributeName);

			if (!wcscmp(attributeName, &path[1]))
			{
				CComQIPtr<IESelectedAnimationElement> selectedAnimationElement = selectedElement;

				//if (wcscmp(attributeName, 
				if (selectedAnimationElement)//TRUE)	// TODO
				{
					//CComQIPtr<ILSMILAnimationTarget> animationTarget = animationTarget;

					CComQIPtr<ILAnimateXXX> animateXXX = domElement;

					long ncount;
					selectedAnimationElement->GetSelectedKeyTimesCount(&ncount);

					CComBSTR value;

					for (int i = 0; i < ncount; i++)
					{
						long keyFrame;
						selectedAnimationElement->GetKeyTimeSelected(i, &keyFrame);

						//CComPtr<ILSMILXMLAttr> attr;
						//animationTarget->animatableXMLAttrItemByName(L"", &attribute);

						CComPtr<ILSMILAttributeValue> attributeValue;
						animateXXX->GetValue(keyFrame, &attributeValue);

						CComBSTR value2;
						if (attributeValue)
							attributeValue->getStringValue(&value2);

						if (i == 0)
						{
							value = value2;
						}
						else if (cmpbstr(value, value2))
						{
							value.Empty();
							break;
						}
					}

					*pVal = value.Detach();
					return S_OK;
				}
			}
		}
	}

	return S_OK;
}

// virtual
void CXMLControlsHandler::OnDataValueChanged(CXMLData* pData)
{
	if (m_reentrancy == 0)
	{
		m_reentrancy++;

		_bstr_t value = pData->GetValueAsString();

		if (value.length())
			SetPathNodeValue(pData->m_name, value);
		else
			SetPathNodeValue(pData->m_name, NULL);

		m_reentrancy--;
	}
}

void CXMLControlsHandler::UpdateData(CXMLData* pData)
{
	if (m_reentrancy == 0)
	{
		m_reentrancy++;

	//	long ncount;
	//	m_viewGroup->GetSelectedCount(&ncount);

		CComBSTR value;
		GetPathNodeValue(pData->m_name, &value);

#if 0
		for (int i = 0; i < ncount; i++)
		{
			CComPtr<IESelectedElement> selectedElement;
			m_viewGroup->GetSelectedElementN(i, &selectedElement);

			CComPtr<IEElement> eElement;
			selectedElement->get_eElement(&eElement);

			CComPtr<ILDOMElement> domElement;
			eElement->get_domElement(&domElement);

			CComBSTR value2 = pData->GetDataValue(domElement);

			if (i == 0)
			{
				value = value2;
			}
			else if (wcscmp(value, value2))
			{
				value.Empty();
				break;
			}
		}
#endif

		pData->SetValue(value);

		m_reentrancy--;
	}

#if 0
	if (m_reentrancy == 0)
	{
		m_reentrancy++;

		long ncount;
		m_viewGroup->GetSelectedCount(&ncount);

		CComBSTR value;

		for (int i = 0; i < ncount; i++)
		{
			CComPtr<IESelectedElement> selectedElement;
			m_viewGroup->GetSelectedElementN(i, &selectedElement);

			CComPtr<IEElement> eElement;
			selectedElement->get_eElement(&eElement);

			CComPtr<ILDOMElement> domElement;
			eElement->get_domElement(&domElement);

			//CComBSTR value2 = pData->GetDataValue(domElement);
			CComBSTR value2;
			::GetPathNodeValue(domElement, pData->m_name, &value2);

			if (i == 0)
			{
				value = value2;
			}
			else if (cmpbstr(value, value2))
			{
				value.Empty();
				break;
			}
		}

		pData->SetValue(value);

		m_reentrancy--;
	}
#endif
}

void CXMLControlsHandler::Setup()
{
}

void CXMLControlsHandler::OnUIValueChanged(CControl* pControl)
{
	for (int i = 0; i < pControl->m_dataConnections.GetSize(); i++)
	{
		CDataConnection* pDataConnection = pControl->m_dataConnections[i];

		_bstr_t value = pControl->GetProperty(pDataConnection->m_propertyName);
		pDataConnection->m_pData->SetValue(value);
	}
}

#endif