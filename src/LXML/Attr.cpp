#include "stdafx.h"
#include "LXML2.h"
#include "Attr.h"

#include "AnimationTarget.h"

namespace System
{
namespace Web
{

Attr::Attr()
{
	m_ownerElement = NULL;
	m_specified = false;
	m_valueIsValid = true;

//	m_pListener = NULL;
//	m_pATAttr = NULL;
}

Attr::~Attr()
{
}

NodeType Attr::get_nodeType() const
{
	return NODE_ATTRIBUTE;
}

Node* Attr::get_parentNode() const
{
	return NULL;
}

ChildNode* Attr::get_previousSibling() const
{
	return NULL;
}

ChildNode* Attr::get_nextSibling() const
{
	return NULL;
}

void Attr::set_parentNode(Node *newVal)
{
	ASSERT(0);
	throw std::exception("Attr cannot have parent");
}

void Attr::set_previousSibling(ChildNode *newVal)
{
	ASSERT(0);
	throw std::exception("Attr cannot set previousSibling");
}

void Attr::set_nextSibling(ChildNode *newVal)
{
	ASSERT(0);
	throw std::exception("Attr cannot set nextSibling");
}

String Attr::get_nodeValue()
{
	return get_value();
}

void Attr::set_nodeValue(StringIn newVal)
{
	set_value(newVal);
}

Node* Attr::cloneNodeExport(Document* ownerDocument, bool deep) const
{
	Attr* pNewAttr = new Attr;

	pNewAttr->m_ownerDocument = ownerDocument;

	pNewAttr->m_nodeName = m_nodeName;
	pNewAttr->m_prefix = m_prefix;
	pNewAttr->m_localName = m_localName;
	pNewAttr->m_namespaceURI = m_namespaceURI;

	// TODO: specified

	// Clone children (regardless of deep since we're an attribute (?))
	for (unsigned int i = 0; i < m_childNodes->m_items.GetSize(); i++)
	{
		Node* node = m_childNodes->m_items[i]->cloneNodeExport(ownerDocument, true);

		pNewAttr->appendChild(node);
	}

	return pNewAttr;
}

String Attr::get_name() const
{
	return get_nodeName();
}

/*
STDMETHODIMP CLDOMAttr::set_name(BSTR newVal)
{
	return set_nodeName(newVal);
}
*/

String Attr::get_value()
{
#if 0
	if (!m_valueIsValid)
	{
		(m_ownerElement->*ComputeStringValue)();
		m_valueIsValid = true;
	}
#endif

	if (!m_valueIsValid)
	{
	//	ASSERT(m_callbacks);
	//	StringW* str = m_callbacks->GetBaseValString(m_ownerElement);

	//	StringW* str = (m_ownerElement->*m_callbacks->GetBaseValString)();
		String str = m_owner->GetBaseValAsString();

		//	StringW* str = m_notify->OnGetBaseValString();

		m_valueIsValid = true;

		if (m_firstChild == NULL)
		{
			Text* text = m_ownerDocument->createTextNode(str);
			m_firstChild = text;
		}
		else
		{
			CharacterData* chardata = dynamic_cast<CharacterData*>(m_firstChild);
			if (chardata)
			{
				chardata->m_data = str;
			}
			else
			{
				ASSERT(0);
				throw std::exception("TODO: != CharacterData");
			}
		}
	}

	return get_textContent();
}

void Attr::set_value(StringIn newVal)
{
	String prevValue = nullptr;
	if (false)
	{
		prevValue = get_value();
	}

	m_valueIsValid = true;

// Optimize if there is one single textnode already there
	Text* textNode;
#if 0
	CComQIPtr<ILDOMText, &IID_ILDOMText> textNode;
	if ((m_childNodes->m_items.GetSize() == 1) && (textNode = m_childNodes->m_items[0]))
	{
		textNode->set_data(newVal);
	}
	else
#endif
	{
		for (int i = m_childNodes->m_items.GetSize()-1; i >= 0; i--)
		{
			removeChild(m_childNodes->m_items[i]);
		}

		textNode = m_ownerDocument->createTextNode(newVal);
		appendChild(textNode);
	}

#if 0
	ASSERT(m_callbacks);
	(m_ownerElement->*m_callbacks->SetBaseValString)();
#endif
	if (m_owner)
	{
		m_owner->UpdateBaseValString();
	}

//	m_callbacks->SetBaseValString(m_ownerElement);
//	m_notify->OnSetBaseValString();

	/*
	if (m_pListener)
	{
		m_pListener->OnAttrValueChanged(m_nodeName, this);
	}
	*/

	if (false)
	{
		EventTarget* eventTarget = dynamic_cast<EventTarget*>(m_ownerElement);
		if (eventTarget)
		{
			DocumentEvent* ownerDocumentEvent = dynamic_cast<DocumentEvent*>(m_ownerDocument);
			if (ownerDocumentEvent)
			{
				MutationEvent* evt;
				
				evt = dynamic_cast<MutationEvent*>(ownerDocumentEvent->createEvent(WSTR("MutationEvent")));

				if (evt)
				{
				// Create an attr modification event
					evt->initMutationEvent(WSTR("DOMAttrModified"), true, false, this, prevValue, newVal, m_nodeName, CHANGE_MODIFICATION);

					eventTarget->dispatchEvent(evt);
				}
			}
		}
	}
}

bool Attr::get_specified() const
{
	return m_specified;
}

/*
STDMETHODIMP CLDOMAttr::set_specified(bool newVal)
{
	m_specified = newVal;
	return S_OK;
}
*/

Element* Attr::GetOwnerElement()
{
	return m_ownerElement;

// TODO ??

	//return m_owner->GetElement();
}

Element* Attr::get_ownerElement()
{
	return GetOwnerElement();
//	return m_ownerElement;
}

void Attr::SetOwnerElement(Element *newVal)
{
	m_ownerElement = newVal;
}

}	// Web
}
