#include "stdafx.h"
#include "LSVG2.h"
#include "SVGElementInstance.h"

#include "SVGElementInstanceList.h"
#include "SVGUseElement.h"

namespace System
{
namespace Web
{

SVGElementInstance::SVGElementInstance()
{
	m_correspondingElement = NULL;
	m_correspondingUseElement = NULL;

	m_parentNode = NULL;
	m_nextSibling = NULL;
	m_previousSibling = NULL;
	m_firstChild = NULL;
	m_lastChild = NULL;

	m_childNodes = new SVGElementInstanceList;
}

SVGElementInstance::~SVGElementInstance()
{
}

void SVGElementInstance::AppendInstance(SVGElementInstance* newChild)
{
//	newChild->AddRef();

	SVGElementInstance* pBefore = NULL;

	SVGElementInstance* pAfter;

	if (pBefore)
		pAfter = pBefore->m_previousSibling;
	else
		pAfter = m_lastChild;

	newChild->m_nextSibling = pBefore;
	newChild->m_previousSibling = pAfter;

	if (pAfter == NULL)
		m_firstChild = newChild;
	else
		pAfter->m_nextSibling = newChild;

	if (pBefore == NULL)
		m_lastChild = newChild;
	else
		pBefore->m_previousSibling = newChild;

	if (pBefore)
	{
		for (int i = 0; i < m_childNodes->m_items.GetSize(); i++)
		{
			if (m_childNodes->m_items[i] == pBefore)
			{
				m_childNodes->m_items.InsertAt(i, newChild);
				break;
			}
		}
	}
	else
	{
		m_childNodes->m_items.Add(newChild);
	}

// Set new child node's parent to this element
	newChild->m_parentNode = this;
}

void SVGElementInstance::BuildTree(SVGUseElement* correspondingUseElement, SVGElement* correspondingElement)
{
	ASSERT(0);
#if 0
	m_correspondingUseElement = static_cast<CLSVGUseElement*>(correspondingUseElement);
	m_correspondingElement = correspondingElement;

	CComPtr<ILDOMNode> node;
	m_correspondingElement->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILSVGElement> svgElement = node;
		if (svgElement)
		{
			CComObject<SVGElementInstance>* pInstance;
			CComObject<SVGElementInstance>::CreateInstance(&pInstance);
			if (pInstance)
			{
				pInstance->AddRef();

				pInstance->BuildTree(correspondingUseElement, svgElement);	// Recurse
				AppendInstance(pInstance);

				pInstance->Release();
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
#endif
}

/////////////////////////////////////////////////////////////////////

SVGElement* SVGElementInstance::get_correspondingElement()
{
	return m_correspondingElement;
}

SVGUseElement* SVGElementInstance::get_correspondingUseElement()
{
	return m_correspondingUseElement;
}

SVGElementInstance* SVGElementInstance::get_parentNode()
{
	return m_parentNode;
}

SVGElementInstanceList* SVGElementInstance::get_childNodes()
{
	return m_childNodes;
}

SVGElementInstance* SVGElementInstance::get_firstChild()
{
	return m_firstChild;
}

SVGElementInstance* SVGElementInstance::get_lastChild()
{
	return m_lastChild;
}

SVGElementInstance* SVGElementInstance::get_previousSibling()
{
	return m_previousSibling;
}

SVGElementInstance* SVGElementInstance::get_nextSibling()
{
	return m_nextSibling;
}

}	// w3c
}
