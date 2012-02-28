#include "stdafx.h"
#include "LXML2.h"
#include "GenericElement.h"

namespace System
{
namespace Web
{

GenericElement::GenericElement(StringIn namespaceURI, StringIn localName, StringIn qualifiedName) : Element(new PGenericElement(this))
{
	m_namespaceURI = namespaceURI;
	m_nodeName = qualifiedName;
	m_localName = localName;

	/*
	m_pElement = new PElement;
	m_pNode = m_pElement;
	m_pNode->m_pNode = this;
	*/
}

GenericElement::GenericElement(StringIn namespaceURI, StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes) : Element(new PGenericElement(this), attributes)
{
	m_namespaceURI = namespaceURI;
	m_nodeName = qualifiedName;
	m_localName = localName;

	/*
	m_pElement = new PElement;
	m_pNode = m_pElement;
	m_pNode->m_pNode = this;
	*/
}

String GenericElement::get_namespaceURI() const
{
	return m_namespaceURI;
}

}	// Web
}
