#include "stdafx.h"
#include "LXMLEditor2.h"
#include "EElementImpl.h"

namespace System
{
namespace LXmlEdit
{

Node::Node()
{
	m_childNodes = NULL;
	m_firstChild = NULL;
	m_lastChild = NULL;
	m_nextSibling = NULL;
	m_previousSibling = NULL;
	m_parentNode = NULL;
	m_ownerDocument = NULL;

	m_localName = NULL;
}

NodeList* Node::get_childNodes()
{
	return m_childNodes;
}

NamedNodeMap* Node::get_attributes()
{
	return NULL;
}

Node* Node::insertNode(Node *newChild, Node* pBefore)
{
	Node* pPrevParent = newChild->get_parentNode();
	if (pPrevParent)
	{
		ASSERT(0);
		//pPrevParent->removeChild(newChild);
	}

	Node* pAfter;

	if (pBefore)
		pAfter = pBefore->get_previousSibling();
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
		for (int i = 0; i < m_childNodes->m_items.size(); i++)
		{
			if (m_childNodes->m_items[i] == pBefore)
			{
				m_childNodes->m_items.InsertAt(i, newChild);
			//	m_childNodes->m_items.insert(&m_childNodes->m_items[i], newChild);
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

	return newChild;
}

///////////////////////////////////////////////
// Element

Element::Element()
{
//	m_domElement = NULL;
	m_childNodes = new NodeList;
}

Element::~Element()
{
	delete m_childNodes;
}

/////////////////////////////////////////////
// Attr

Attr::Attr()
{
	m_prefix = NULL;

	m_childNodes = new NodeList;
}

Attr::~Attr()
{
	delete m_childNodes;
}

System::StringW* Attr::get_prefix()
{
	return m_prefix;
}

System::StringW* Attr::get_localName()
{
	return m_localName;
}

System::StringW* Attr::get_value()
{
	return dynamic_cast<Text*>(m_childNodes->m_items[0])->get_data();
}

void Attr::set_value(System::StringW* newVal)
{
	dynamic_cast<Text*>(m_childNodes->m_items[0])->set_data(newVal);
}

}	// LXmlEdit
}
