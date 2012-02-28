#include "stdafx.h"
#include "LXML.h"
#include "LXML2.h"
#include "ASXMLSchemaModel.h"

#include "ASXMLSchemaModelGroup.h"
#include "ASXMLSchemaElementDefinition.h"

#if 0

namespace LXML
{

int GetElementAttributeInteger(Node* node, const sysstring& name, int defVal);


#if 0

// IASObject
STDMETHODIMP CModelGroup::cloneASObject(/*[in]*/ bool deep, /*[out,retval]*/ IASObject** pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	ASSERT(m_pSchema);

	CComObject<CModelGroup>* pCM;
	CComObject<CModelGroup>::CreateInstance(&pCM);
	if (pCM)
	{
		pCM->AddRef();
		pCM->m_pSchema = m_pSchema;

		ASContentModelTypeOp Operator;
		get_listOperator(&Operator);

		long minOccurs;
		get_minOccurs(&minOccurs);

		long maxOccurs;
		get_maxOccurs(&maxOccurs);

		if (Operator == AS_SEQUENCE)
			m_pSchema->m_xmlDocument->createElement(L"sequence", &pCM->m_element);
		else if (Operator == AS_CHOICE)
			m_pSchema->m_xmlDocument->createElement(L"choice", &pCM->m_element);
		else if (Operator == AS_ALL)
			m_pSchema->m_xmlDocument->createElement(L"all", &pCM->m_element);

		if (pCM->m_element == NULL)	// AS_NONE (atomic)
		{
			ASSERT(m_subModels->m_items.GetSize() == 1);

			CComPtr<IASObject> asObject;
			m_subModels->m_items[0]->cloneASObject(deep, &asObject);

			asObject->GetElement(&pCM->m_element);

			unsigned long length;
			pCM->appendsubModel(asObject, &length);
		}
		else
		{
			if (deep)
			{
				for (int i = 0; i < m_subModels->m_items.GetSize(); i++)
				{
					CComPtr<IASObject> asObject;
					m_subModels->m_items[i]->cloneASObject(deep, &asObject);
					if (asObject)
					{
						unsigned long length;
						pCM->appendsubModel(asObject, &length);
						//pCM->m_subModels->m_items.Add(asObject.Detach());
					}
				}
			}
		}

		pCM->set_minOccurs(minOccurs);
		pCM->set_maxOccurs(maxOccurs);

		*pVal = pCM;
	}

	return S_OK;
}

// IASContentModel

STDMETHODIMP CModelGroup::appendsubModel(/*[in]*/ IASObject* newNode, /*[out,retval]*/ unsigned long* length)
{
	if (newNode == NULL) return E_INVALIDARG;
	if (length == NULL) return E_POINTER;

	insertBeforeSubModel(newNode, NULL, NULL);

	*length = m_subModels->m_items.GetSize();

	return S_OK;
}

STDMETHODIMP CModelGroup::insertBeforeSubModel(/*[in]*/ IASObject* newObject, /*[in]*/ IASObject* refObject, /*[out,retval]*/ IASObject* *pVal)
{
	if (newObject == NULL) return E_INVALIDARG;

	if (m_subModels == NULL)
	{
		CComObject<CASXMLObjectList>::CreateInstance(&m_subModels);
		m_subModels->AddRef();
	}

	for (int i = 0; i < m_subModels->m_items.GetSize(); i++)
	{
		if (m_subModels->m_items[i] == refObject)
		{
			break;
		}
	}

	newObject->AddRef();
	m_subModels->m_items.InsertAt(i, newObject);

// Update DOM
	CComPtr<ILDOMElement> newNodeElement;
	newObject->GetElement(&newNodeElement);

	CComPtr<ILDOMElement> refNodeElement;
	if (refObject)
		refObject->GetElement(&refNodeElement);

	if (m_element != newNodeElement)
	{
		m_element->insertBefore(newNodeElement, _variant_t(refNodeElement), NULL);
	}
	// else AS_NONE (atomic)

// Notify userhandlers
	{
		for (int i = 0; i < m_userdataList.GetSize(); i++)
		{
			CUserData* userdata = m_userdataList[i];
			userdata->m_handler->_handle((ASUserDataHandleType)8/*operation*/, userdata->m_key, userdata->m_data, newObject, NULL);
		}
	}

//
	if (pVal)
	{
		*pVal = newObject;
		(*pVal)->AddRef();
	}

	return S_OK;
}

STDMETHODIMP CModelGroup::replacesubModel(/*[in]*/ IASObject* oldNode, /*[in]*/ IASObject* newNode)
{
	if (oldNode == NULL) return E_INVALIDARG;
	if (newNode == NULL) return E_INVALIDARG;

	for (int i = 0; i < m_subModels->m_items.GetSize(); i++)
	{
		if (m_subModels->m_items[i] == oldNode)
		{
			m_subModels->m_items[i] = newNode;
			newNode->AddRef();

		// Update DOM
			CComPtr<ILDOMElement> oldNodeElement;
			oldNode->GetElement(&oldNodeElement);

			CComPtr<ILDOMElement> newNodeElement;
			newNode->GetElement(&newNodeElement);

			if (newNodeElement)
			{
				CComPtr<ILDOMNode> result;
				m_element->replaceChild(newNodeElement, oldNodeElement, &result);
			}
			else	// Content type is AS_NONE (atomic)
			{
				newNode->SetElement(oldNodeElement);
				CComQIPtr<IASContentModel> newCM = newNode;
				newCM->UpdateElement();
			}
			break;
		}
	}

	return S_OK;
}

STDMETHODIMP CModelGroup::removeSubModel(/*[in]*/ IASObject* oldObject)
{
	if (oldObject == NULL) return E_INVALIDARG;

	for (int i = 0; i < m_subModels->m_items.GetSize(); i++)
	{
		if (m_subModels->m_items[i] == oldObject)
		{
			m_subModels->m_items.RemoveAt(i);

		// Update DOM
			CComPtr<ILDOMElement> oldElement;
			oldObject->GetElement(&oldElement);

			m_element->removeChild(oldElement, NULL);

		// Notify userhandlers
			{
				for (int i = 0; i < m_userdataList.GetSize(); i++)
				{
					CUserData* userdata = m_userdataList[i];
					userdata->m_handler->_handle((ASUserDataHandleType)8/*operation*/, userdata->m_key, userdata->m_data, oldObject, NULL);
				}
			}

			oldObject->Release();

			return S_OK;
		}
	}

	ASSERT(0);
	return S_OK;
}

STDMETHODIMP CModelGroup::get_listOperator(ASContentModelTypeOp *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	if (m_element == NULL)
	{
		*pVal = AS_NONE;
	}
	else
	{
		CComBSTR tagName;
		m_element->get_tagName(&tagName);

		if (!wcscmp(tagName, L"sequence"))
			*pVal = AS_SEQUENCE;
		else if (!wcscmp(tagName, L"choice"))
			*pVal = AS_CHOICE;
		else if (!wcscmp(tagName, L"all"))
			*pVal = AS_ALL;
		else
			*pVal = AS_NONE;
	}

	return S_OK;
}

STDMETHODIMP CModelGroup::set_listOperator(ASContentModelTypeOp newVal)
{
// We must be a true content model, not a AS_NONE (atomic) content model
	ASSERT(m_element != NULL);
	if (m_element == NULL) return E_FAIL;

	WCHAR* nodeName;

	if (newVal == AS_SEQUENCE)
		nodeName = L"sequence";
	else if (newVal == AS_CHOICE)
		nodeName = L"choice";
	else if (newVal == AS_ALL)
		nodeName = L"all";
	else
	{
		ASSERT(0);
		return E_FAIL;
	}

	CComPtr<ILDOMNode> newNode;
	m_pSchema->m_xmlDocument->renameNode(m_element, L"http://www.w3.org/2001/XMLSchema", nodeName, &newNode);

// We don't support that a new element (and it's children) were re-created
	ASSERT(newNode == m_element);

	return S_OK;
}
#endif

void CModelGroup::BuildDefs(Element* m_element)
{
	ASSERT(m_pSchema);

	Node* child = m_element->get_firstChild();
	while (child != NULL)
	{
		Element* element = dynamic_cast<Element*>(child);
		if (element)
		{
			sysstring tagName = element->get_tagName();

			IASObject/*CSchemaNode*/ * pNode = NULL;

			if (tagName == OLESTR("element"))
			{
				ASSERT(0);
				CElementDefinition* pElement = NULL;//new CElementDefinition;

			//	pElement->m_element = element;
				pElement->m_pSchema = m_pSchema;

				pElement->BuildDefs(element);

				int minOccurs = GetElementAttributeInteger(element, L"minOccurs", 1);
				int maxOccurs = GetElementAttributeInteger(element, L"maxOccurs", 1);

				// Wrap element in CModelGroup if (minOccurs!=1 || maxOccurs != 1)
				if (minOccurs  != 1 || maxOccurs != 1)
				{
					ASSERT(0);
					CModelGroup* pCM = NULL;//new CModelGroup;
					pCM->m_pSchema = m_pSchema;
				//	pCM->m_element = element;
					pCM->m_listOperator = AS_ATOMIC;
					pCM->m_minOccurs = minOccurs;
					pCM->m_maxOccurs = maxOccurs;

				//	pElement->m_pParentModelGroup = pCM;
					pCM->m_subModels->m_items.Add(pElement);

					m_subModels->m_items.Add(pCM);

					pNode = pCM;
				}
				else
				{
				//	pElement->m_pParentModelGroup = this;
					m_subModels->m_items.Add(pElement);
					pNode = pElement;
				}
			}
			else if (*tagName == L"sequence" ||
						*tagName == L"choice" ||
						*tagName == L"all")
			{
				ASSERT(0);
				CModelGroup* pCM = NULL;//new CModelGroup;

			//	pCM->m_element = element;
				pCM->m_pSchema = m_pSchema;

			// TODO, add to subModels ?
				m_subModels->m_items.Add(pCM);

				pCM->BuildDefs(element);	// Recurse

				pNode = pCM;
			}

			if (!pNode)
			{
				WCHAR msg[256];
				swprintf(msg, L"Unsupported element %s", tagName.c_str());
				THROW(-1);
			}

//			m_nodes.Add(pNode);
		}

		child = child->get_nextSibling();
	}
}

}	// LXML

#endif