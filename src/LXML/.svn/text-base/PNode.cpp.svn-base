#include "stdafx.h"
#include "LXML2.h"

#include "PNode.h"
#include "Window.h"
#include "LXMLDocumentView.h"

namespace System
{
namespace Web
{

PNode::PNode(ChildNode* node)
{
	m_pNode = node;

	m_parent = NULL;
	m_rparent = NULL;

//	m_pView = NULL;
	m_pWindow = NULL;	// TODO, should be removed

	m_selected = 0;

	m_pC = NULL;
	m_pSharedBox = NULL;
}

PNode::~PNode()
{
#if 0
	// ???
	if (m_pNode)
	{
		for (int i = 0; i < CComQIPtr<CLDOMNodeImplImpl>(m_pNode)->m_pNodes.GetSize(); i++)
		{
			if (CComQIPtr<CLDOMNodeImplImpl>(m_pNode)->m_pNodes[i] == this)
			{
				CComQIPtr<CLDOMNodeImplImpl>(m_pNode)->m_pNodes.RemoveAt(i);
				break;
			}
		}
	}
#endif
}

CHTMLWindow* PNode::GetWindow()
{
	ASSERT(m_pNode);
	VERIFY(m_pNode->m_ownerDocument);
	return m_pNode->m_ownerDocument->m_pWindow;
}

// virtual
void PNode::RemovedFromDocument()
{
#if 0
	CComQIPtr<CLDOMNodeImplImpl>(m_pNode)->RemovePNode(this);
#endif
}

#if 0
CPNode* CPNode::GetPrevNode()
{
	if (m_parent)
	{
		UPOSITION pos = m_parent->m_childList.Find(this);
		m_parent->m_childList.GetPrev(pos);
		if (pos) return (CPNode*)m_parent->m_childList.GetAt(pos);
	}

	return NULL;
}

PNode* PNode::GetNextNode()
{
	if (m_parent)
	{
		UPOSITION pos = m_parent->m_childList.Find(this);
		m_parent->m_childList.GetNext(pos);
		if (pos) return (CPNode*)m_parent->m_childList.GetAt(pos);
	}

	return NULL;
}

int PNode::GetDOMNodesIndex()
{
	int index = -1;

	ASSERT(0);
#if 0
	CComPtr<ILDOMNode> node;
	node = m_pNode;
	while (node)
	{
		index++;

		CComPtr<ILDOMNode> previousSibling;
		node->get_previousSibling(&previousSibling);
		node = previousSibling;
	}
#endif
	return index;
}
#endif

#if 0
STDMETHODIMP CPNode::GetNode(/*[out,retval]*/ ILDOMNode** pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pNode;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPNode::GetPresentation(/*[out,retval]*/ ILPresentation* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pView;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}
#endif

#if 0
CHTMPElement* CPNode::FindParentElement(LPCTSTR tagname)
{
	CHTMPElement* pElement = (CHTMPElement*)m_parent;
	while (pElement)
	{
#if 0
		ASSERT(pElement->m_pNode->nodeType == SVGLib::NODE_ELEMENT);
#endif

		CComQIPtr<ILHTMLElement> element = pElement->m_pNode;
		BSTR etagName;
		element->get_tagName(&etagName);
		if (!wcscmp(etagName, _bstr_t(tagname)))
		{
			SysFreeString(etagName);
			return pElement;
		}
		SysFreeString(etagName);

		pElement = (CHTMPElement*)pElement->m_parent;
	}
	return NULL;
}
#endif

}
}
