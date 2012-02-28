#include "stdafx.h"
#include "LXML2.h"
#include "NodeIterator.h"

#include "LDOMDocumentTraversalImpl.h"

namespace System
{
namespace Web
{

CLDOMNodeIterator::CLDOMNodeIterator()
{
	m_root = NULL;
	m_filter = NULL;

	m_pDocumentTraversal = NULL;

	m_referenceNode = NULL;
}

CLDOMNodeIterator::~CLDOMNodeIterator()
{
	if (m_pDocumentTraversal)
	{
		detach();	// ??
	}
}

Node* CLDOMNodeIterator::get_root()
{
	return m_root;
}

INodeFilter* CLDOMNodeIterator::get_filter()
{
	return m_filter;
}

FilterShow CLDOMNodeIterator::get_whatToShow()
{
	return m_whatToShow;
}

bool CLDOMNodeIterator::get_expandEntityReferences()
{
	return m_expandEntityReferences;
}

Node* CLDOMNodeIterator::nextNode()
{
	ASSERT(0);
#if 0
	if (m_pDocumentTraversal)
	{
	// TODO

		*pVal = m_referenceNode;
//		(*pVal)->AddRef();

		<Node> nextSibling;
		m_referenceNode->get_nextSibling(&nextSibling);

		m_referenceNode = nextSibling;

		return S_OK;
	}
#endif
	ASSERT(0);
	return NULL;
}

Node* CLDOMNodeIterator::previousNode()
{
	ASSERT(0);
#if 0
	if (m_pDocumentTraversal)
	{
	// TODO

		<Node> previousSibling;
		m_referenceNode->get_previousSibling(&previousSibling);

		m_referenceNode = previousSibling;

		*pVal = m_referenceNode;
//		(*pVal)->AddRef();

		return S_OK;
	}
#endif
	ASSERT(0);
	return NULL;
}

void CLDOMNodeIterator::detach()
{
	if (m_pDocumentTraversal)
	{
		CLDOMDocumentTraversalImplImpl* pDocumentTraversal = m_pDocumentTraversal;
		m_pDocumentTraversal = NULL;

		for (size_t i = 0; i < pDocumentTraversal->m_iterators.GetSize(); i++)
		{
			if (pDocumentTraversal->m_iterators[i] == this)
			{
				pDocumentTraversal->m_iterators.RemoveAt(i);
				return;
			}
		}
	}

	ASSERT(0);
}

}	// Web
}
