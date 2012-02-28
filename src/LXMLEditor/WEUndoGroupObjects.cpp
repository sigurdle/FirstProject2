#include "stdafx.h"
#include "LXMLEditor2.h"
#include "WEUndoGroupObjects.h"

#include "EXMLDocument.h"
#include "EXMLViewGroup.h"
#include "ESelectedElementImpl.h"

namespace System
{
namespace LXmlEdit
{

Web::Node* GetElementFromUniqID(Web::Node* parent, GUID& guid);

/////////////////////////////////////////////////////////////////////////////
// CWEUndoGroupObjects

System::StringW* CWEUndoGroupObjects::GetDescription()
{
	return WSTR("Group Objects");
}

void CWEUndoGroupObjects::OnNextAdd()
{
}

ErrorCode CWEUndoGroupObjects::DoInitial(CEXMLViewGroup* pView, IUndoManager *pUndoManager)
{
	ASSERT(0);
#if 0
	ATLASSERT(m_pDocument);
	CComQIPtr<ILDOMDocument> domdocument = m_pDocument->get_DOMDocument();

	CComQIPtr<ILDOMElement> documentElement;
	domdocument->get_documentElement(&documentElement);

// We insert the group where the last element is found
// meaning, the topmost selected object decides where the
// group is inserted

	CComPtr<IEElement> eElement;
	pView->m_targetElements[0]->get_eElement(&eElement);

	CComPtr<IEElement> eParentElement;
	eElement->get_parentNode(&eParentElement);

	CComPtr<ILDOMElement> parentElement;
	eParentElement->get_domElement(&parentElement);

	CArray<Web::Node*, Web::Node*> layers;

// Build the array of selected objects
//	UPOSITION pos = pParent->m_childList.GetHeadPosition();

	CComPtr<Web::Node> child;
	parentElement->get_firstChild(&child);
	while (child)
	{
		CComQIPtr<ILDOMElement> domElement = child;
		if (domElement)
		{
			CComPtr<IEElement> eElement;
			m_pDocument->GetEElementFromDOMElement(domElement, &eElement);

			CComPtr<IESelectedElement> selected;
			pView->GetSelectedElement(eElement, &selected);

			if (selected)
			{
				CComQIPtr<ILSVGLocatable> transformable = domElement;
				if (transformable != NULL)
				{
					layers.Add(domElement);
				}
			}
		}

		CComPtr<Web::Node> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	ATLASSERT(layers.GetSize() > 0);

	CComQIPtr<Web::Node> beforeNode;
	layers[layers.GetSize()-1]->/*m_domElement->*/get_nextSibling(&beforeNode);

// Remember the parent node of the group
	parentElement->get_uniqID(&m_parentgroupGUID);

// Remeber the before node of the group
	if (beforeNode)
	{
		beforeNode->get_uniqID(&m_beforegroupGUID);
	}
	else
	{
		m_beforegroupGUID = GUID_NULL;
	}

	for (int i = 0; i < layers.GetSize(); i++)
	{
		GUID guid;

	// Remember which node this had as parent
		CComPtr<Web::Node> parentNode;
		layers[i]->/*m_domElement->*/get_parentNode(&parentNode);
		parentNode->get_uniqID(&guid);
		m_parentElements.Add(guid);

	// Remember which node this was before
		CComPtr<Web::Node> beforeNode;
		layers[i]->/*m_domElement->*/get_nextSibling(&beforeNode);
		if (beforeNode)
		{
			beforeNode->get_uniqID(&guid);
			m_beforeElements.Add(guid);
		}
		else
			m_beforeElements.Add(GUID_NULL);

		layers[i]->/*m_domElement->*/get_uniqID(&guid);
		m_targetElements.Add(guid);
	}

	CoCreateGuid(&m_groupGUID);	// Create a unique GUID for the group

	m_bRedo = true;
	Do(pUndoManager);
#endif
//	CElement* pGroupElement = m_pTree->FindDOMElement((IDOMNode*)pGroup);
	return Success;
}

Web::Node* GetElementFromUniqID(Web::Node* parent, GUID& guid);;

void CWEUndoGroupObjects::Do(IUndoManager *pUndoManager)
{
	ASSERT(0);
#if 0
	ATLASSERT(m_pDocument);
	CComQIPtr<ILDOMDocument> domdocument;
	m_pDocument->get_DOMDocument(&domdocument);

	CComQIPtr<ILDOMElement> documentElement;
	domdocument->get_documentElement(&documentElement);

	if (m_bRedo)	// Redo (Group)
	{
		CWEUndoSourceLast::Do(pUndoManager);

		CComPtr<Web::Node> pParent = GetElementFromUniqID(documentElement, m_parentgroupGUID);

		CComQIPtr<Web::Node> beforeNode;

		if (m_beforegroupGUID != GUID_NULL)
			beforeNode = GetElementFromUniqID(documentElement, m_beforegroupGUID);

		CComPtr<ILSVGGElement> group;
		//m_document->createEElement(L"http://www.w3.org/2000/svg", L"g"
		domdocument->createElementNS(L"http://www.w3.org/2000/svg", L"g", (ILDOMElement**)&group);
		group->put_uniqID(m_groupGUID);

		pParent->/*m_domElement->*/insertBefore(group, CComVariant(beforeNode), NULL);

		for (int i = 0; i < m_targetElements.GetSize(); i++)
		{
			CComPtr<Web::Node> node = GetElementFromUniqID(documentElement, m_targetElements[i]);

		//	CElementImpl* pElement = m_pDocument->GetElementFromGUID(m_targetElements[i]);
			group->appendChild(node/*pElement->m_domElement*/, NULL);	// Insert At end
		}

		CComPtr<IEXMLViewGroup> viewGroup;
		m_pDocument->GetActiveViewGroup(&viewGroup);
		if (viewGroup)
		{
			CComPtr<IEElement> eelement;
			m_pDocument->GetEElementFromDOMElement(group, &eelement);

			viewGroup->ActivateElement(eelement, 0, NULL);
		}
	}
	else	// Undo (Ungroup)
	{
#if 0
		m_pDocument->SetTargetElement(NULL, 0);
#endif

		CComQIPtr<ILDOMElement> group = GetElementFromUniqID(documentElement, m_groupGUID);

		for (int i = m_targetElements.GetSize()-1; i >= 0; i--)
		{
			Web::Node* element = GetElementFromUniqID(documentElement, m_targetElements[i]);

			Web::Node* parentNode = GetElementFromUniqID(documentElement, m_parentElements[i]);
			ATLASSERT(parentNode);

			if (m_beforeElements[i] != GUID_NULL)
			{
				Web::Node* beforeNode = GetElementFromUniqID(documentElement, m_beforeElements[i]);
				ATLASSERT(beforeNode);
				parentNode->insertBefore(element, _variant_t(beforeNode), NULL);
			}
			else
			{
				parentNode->appendChild(element, NULL);
			}

#if 0
			m_pDocument->SetTargetElement(m_pDocument->m_pTree->FindDOMElement(element), MK_SHIFT);
#endif
		}

	// Finally delete the group element
		CComPtr<Web::Node> groupParentNode;
		group->get_parentNode(&groupParentNode);
		groupParentNode->removeChild(group, NULL);

		CWEUndoSourceLast::Do(pUndoManager);
	}

	m_bRedo = !m_bRedo;
	pUndoManager->Add(this);
#endif
}

}	// LXmlEdit
}
