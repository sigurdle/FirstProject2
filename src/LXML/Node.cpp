#include "stdafx.h"
#include "LXML2.h"
#include "Node.h"

#include "NodeList.h"
#include "DOMDocumentEvent.h"
#include "AnimationElement.h"

//#include "LHTMLWindow.h"
#include "Window.h"
#include "LXMLDocumentView.h"

namespace System
{
namespace Web
{

bool IsDocumentOrPartOfDocument(Node* node)
{
	ASSERT(node);
	do
	{
		NodeType nodeType = node->get_nodeType();

		if (nodeType == NODE_DOCUMENT)
			return true;

		node = node->get_parentNode();
	}
	while (node);

	return false;
}

void NodeInsertedIntoDocument(Node* node)
{
	NodeList* childNodes = node->get_childNodes();
	long length = childNodes->get_length();

	for (int i = 0; i < length; ++i)
	{
		Node* child = childNodes->item(i);

		NodeInsertedIntoDocument(child);
	}

	Document* ownerDocument = node->get_ownerDocument();

	DocumentEvent* ownerDocumentEvent = dynamic_cast<DocumentEvent*>(ownerDocument);
	ASSERT(ownerDocumentEvent != nullptr);

	MutationEvent* pEvent = dynamic_cast<MutationEvent*>(ownerDocumentEvent->createEvent(S("MutationEvent")));
	pEvent->initMutationEvent(S("DOMNodeInsertedIntoDocument"), false, false, nullptr/*relatedNode*/, nullptr, nullptr, nullptr, CHANGE_UNKNOWN);

	EventTarget* target = dynamic_cast<EventTarget*>(node);

	target->dispatchEvent(pEvent);
}

void NodeRemovedFromDocument(Node* node)
{
	NodeList* childNodes = node->get_childNodes();

	unsigned int length = childNodes->get_length();

	for (unsigned int i = 0; i < length; ++i)
	{
		Node* child = childNodes->item(i);

		NodeRemovedFromDocument(child);
	}

	Document* ownerDocument = node->get_ownerDocument();

	DocumentEvent* ownerDocumentEvent = dynamic_cast<DocumentEvent*>(ownerDocument);
	ASSERT(ownerDocumentEvent != nullptr);

	MutationEvent* event = dynamic_cast<MutationEvent*>(ownerDocumentEvent->createEvent(S("MutationEvent")));

	event->initMutationEvent(S("DOMNodeRemovedFromDocument"), false, false, NULL/*relatedNode*/, nullptr, nullptr, nullptr, CHANGE_UNKNOWN);

	EventTarget* target = dynamic_cast<EventTarget*>(node);

	target->dispatchEvent(event);
}

/////////////////////////////////////////////////////////////////////////////
// Node

Node::Node()
{
	m_childNodes = new NodeList;

#if 0
	m_pNode = NULL;

	m_xmlspace = 0;	// default

	m_parentNode = NULL;
	m_ownerDocument = NULL;
	m_firstChild = NULL;
	m_lastChild = NULL;

	m_nodeName = NULL;
	m_localName = NULL;
	m_namespaceURI = NULL;
	m_prefix = NULL;
#endif

	// TODO remove these
	m_textOffset[0] = -1;
	m_textOffset[1] = -1;
	m_textOffset[2] = -1;
	m_textOffset[3] = -1;
	m_textOffset[4] = -1;
	m_textOffset[5] = -1;
	m_textOffset[6] = -1;
	m_textOffset[7] = -1;
	m_textOffset[8] = -1;
	m_textOffset[9] = -1;
}

Node::~Node()
{
	delete m_childNodes;
}

ChildNode::ChildNode()
{
}

ChildNode::ChildNode(PNode* pNode)
{
	m_pNode = pNode;
}

Node* Node::cloneNode(bool deep) const
{
	return cloneNodeExport(m_ownerDocument, deep);
}

Document* Node::get_ownerDocument() const
{
	return m_ownerDocument;
}

NodeType Node::get_nodeType() const
{
	return NODE_INVALID;
}

Node* ChildNode::get_parentNode() const
{
	return m_parentNode;
}

void ChildNode::set_parentNode(Node *newVal)
{
	m_parentNode = newVal;
}

ChildNode* Node::get_firstChild() const
{
	return m_firstChild;
}

ChildNode* Node::get_lastChild() const
{
	return m_lastChild;
}

ChildNode* ChildNode::get_nextSibling() const
{
	return m_nextSibling;
}

void ChildNode::set_nextSibling(ChildNode *pVal)
{
	m_nextSibling = pVal;
}

void ChildNode::set_previousSibling(ChildNode *newVal)
{
	m_previousSibling = newVal;
}

ChildNode* ChildNode::get_previousSibling() const
{
	return m_previousSibling;
}

Node* Node::insertNode(Node* _newChild, Node* _pBefore)
{
	ChildNode* newChild = dynamic_cast<ChildNode*>(_newChild);
	ChildNode* pBefore = dynamic_cast<ChildNode*>(_pBefore);

	Node* pPrevParent = newChild->get_parentNode();
	if (pPrevParent)
	{
		pPrevParent->removeChild(newChild);
	}

	ChildNode* pAfter;

	if (pBefore)
		pAfter = pBefore->get_previousSibling();
	else
		pAfter = m_lastChild;

	newChild->set_nextSibling(pBefore);
	newChild->set_previousSibling(pAfter);

	if (pAfter == NULL)
		m_firstChild = newChild;
	else
		pAfter->set_nextSibling(newChild);

	if (pBefore == NULL)
		m_lastChild = newChild;
	else
		pBefore->set_previousSibling(newChild);

	if (pBefore)
	{
		for (int i = 0; i < m_childNodes->m_items.GetSize(); i++)
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
	newChild->set_parentNode(this);

//	TRACE("TODO\n");
#if 0
// Update computed xmlspace for inserted child(ren)
	CComQIPtr<ILDOMElement> newElement((IUnknown*)newChild);
	if (newElement)
	{
		CComBSTR xmlspace;
		newElement->getAttribute(OLESTR("xml:space"), &xmlspace);
		if (xmlspace.Length()==0)	// inherit from parent
		{
			CComQIPtr<CLDOMElementImplImpl>((IUnknown*)newChild)->m_xmlspace = m_xmlspace;
		}
		else	// explicitly set
		{
			CComQIPtr<CLDOMElementImplImpl>((IUnknown*)newChild)->m_xmlspace = cmpbstr(xmlspace, OLESTR("preserve")) == 0;
		}
	// TODO, update recursively for newChild
	}
#endif
	// SMIL Animation (TODO, not very well thought trough)
#if 0
	{
		CLDOMDocument* pDocument = static_cast<CLDOMDocument*>(static_cast<CLDOMDocumentImpl<ILDOMDocument>*>(m_ownerDocument));

		if (pDocument)
		{
			CComQIPtr<ILDOMElement> newElement = newChild;

			if (newElement)
			{
			// SMIL Animation (connect animate/set etc. elements to the elements they target)
				pDocument->BuildAnimationListForAllElements(newElement, pDocument->m_documentElement);

			// Set baseVal/animVal from attributes and parse 'style' attributes
				pDocument->UpdateAnimationElements(newElement);
			}
		}
	}
#endif

//	TRACE("TODO\n");
#if 0
	// Timing stuff (TODO)
	{
		ElementTimeImplImpl* elementTimeImpl((IUnknown*)newChild);
		if (elementTimeImpl)
		{
			elementTimeImpl->CalculateTimeBeforeParent();

			CComPtr<ILElementTimeContainer> parentTimeContainer;
			elementTimeImpl->get_parentTimeContainer(&parentTimeContainer);
			CComQIPtr<CLElementTimeContainerImplImpl> parentTimeContainerImpl((IUnknown*)parentTimeContainer);
			if (parentTimeContainerImpl)
			{
				parentTimeContainerImpl->RecalculateTime();
			}

			elementTimeImpl->CalculateTimeAfterParent();
		}
	}

	CComQIPtr<ILAnimationElement, &IID_ILAnimationElement> animation = (IUnknown*)newChild;
	if (animation)
	{
		CComQIPtr<CLAnimationElementImplImpl> pAnimation((IUnknown*)animation);

		pAnimation->SetValuesFromAttributes();
	}
#endif

	{
#if 0	// TODO
		for (int i = 0; i < m_pNodes.GetSize(); i++)
		{
			ASSERT(0);
			m_pNodes[i]->OnInsertedChild(newChild);
		}
#endif

#if 0
		if (TRUE)	// TODO, probably remove this (use above loop only)
		{
			CComQIPtr<INotifySend, &IID_INotifySend> cp = newChild;
			if (cp)
			{
				CComQIPtr<INotifyGet, &IID_INotifyGet> get = (IUnknown*)thisNode;
				if (get)
				{
					DWORD cookie;
					cp->Advise(get, &cookie);
				}

				cp->FireOnChanged(NOTIFY_ADD, newChild, DISPID_UNKNOWN);
			}
		}
#endif
	}

//	CComPtr<ILDOMDocument> ownerDocument;
//	newChild->get_ownerDocument(&ownerDocument);
//	if (ownerDocument)
	{
////////////////////////////////
// create an event notification

		DocumentEvent* ownerDocumentEvent = dynamic_cast<DocumentEvent*>(m_ownerDocument);

		if (ownerDocumentEvent == NULL)
			ownerDocumentEvent = dynamic_cast<DocumentEvent*>(this);

		if (ownerDocumentEvent)
		{
			MutationEvent* event = dynamic_cast<MutationEvent*>(ownerDocumentEvent->createEvent(S("MutationEvent")));

			EventTarget* eventTarget = dynamic_cast<EventTarget*>(newChild);

		//
			event->initMutationEvent(S("DOMNodeInserted"), true, false, this, nullptr, nullptr, nullptr, CHANGE_UNKNOWN);

			bool doDefault = eventTarget->dispatchEvent(event);

			if (IsDocumentOrPartOfDocument(this))
			{
			// Send "DOMNodeInsertedIntoDocument" to the node and it's children
				NodeInsertedIntoDocument(newChild);
			}
		}

		{
			Node* p = this;
			while (p)
			{
				if (p->m_pNode)
				{
					p->m_pNode->m_bArrangeValid = false;
				}

				p = p->get_parentNode();
			}
		}

#if 0
	//
		event->initMutationEvent(OLESTR("DOMSubtreeModified"), VARIANT_TRUE, VARIANT_FALSE, thisNode, NULL, NULL, NULL, CHANGE_UNKNOWN);
		eventTarget->dispatchEvent(event, &doDefault);
#endif
	}

	return newChild;
}

Node* Node::appendChild(Node* newChild)
{
	if (newChild == NULL) throw new Exception(WSTR("null pointer"));

	DocumentFragment* fragment = dynamic_cast<DocumentFragment*>(newChild);
	if (fragment)
	{
		Node* child = fragment->get_firstChild();
		while (child)
		{
			Node* nextSibling = child->get_nextSibling();

			insertNode(child, nullptr);

			child = nextSibling;
		}

		return nullptr;	// ??
	}
	else
	{
		return insertNode(newChild, nullptr);
	}
}

Node* Node::insertBefore(Node *newChild, Node* refChild)
{
	ASSERT(0);
	return nullptr;
#if 0

	if (newChild == NULL) return E_INVALIDARG;

	ILDOMNode *refChild;
	if (V_VT(&vrefChild) == VT_NULL || V_VT(&vrefChild) == VT_EMPTY)
	{
		refChild = NULL;
	}
	else if (V_VT(&vrefChild) == VT_UNKNOWN || V_VT(&vrefChild) == VT_DISPATCH)
	{
		if (V_UNKNOWN(&vrefChild))
		{
			refChild = CComQIPtr<ILDOMNode, &IID_ILDOMNode>(V_UNKNOWN(&vrefChild));
			if (refChild == NULL) return E_INVALIDARG;
		}
		else
			refChild = NULL;
	}
	else
		return E_INVALIDARG;

	CComQIPtr<ILDOMDocumentFragment, &IID_ILDOMDocumentFragment> fragment((IUnknown*)newChild);
	if (fragment)
	{
		CComPtr<ILDOMNode> child;
		fragment->get_firstChild(&child);
		while (child)
		{
			CComPtr<ILDOMNode> nextSibling;
			child->get_nextSibling(&nextSibling);

			insertNode(thisNode, child, refChild, NULL);

			child = nextSibling;
		}

		if (pVal)
		{
			*pVal = NULL;	// ??
		}

		return S_OK;
	}
	else
	{
		return insertNode(thisNode, newChild, refChild, pVal);
	}
#endif
}

Node* Node::removeChild(Node *oldChild)
{
	//ASSERT(0);
#if 0
	// Do this first?
	{
		CComQIPtr<INotifySend> cp = thisNode;
		if (cp)
		{
			cp->FireOnChanged(NOTIFY_REMOVE, oldChild, DISPID_UNKNOWN);
		}
	}
#endif

	Document* ownerDocument = oldChild->get_ownerDocument();

	if (ownerDocument)
	{
		ASSERT(ownerDocument != NULL);

		DocumentEvent* ownerDocumentEvent = dynamic_cast<DocumentEvent*>(ownerDocument);
		ASSERT(ownerDocumentEvent != NULL);

		MutationEvent* evt = dynamic_cast<MutationEvent*>(ownerDocumentEvent->createEvent(S("MutationEvent")));

	// Create a DOMNodeRemoved event
		evt->initMutationEvent(S("DOMNodeRemoved"), true, false, this, nullptr, nullptr, nullptr, CHANGE_UNKNOWN);

		EventTarget* target = dynamic_cast<EventTarget*>(oldChild);
		target->dispatchEvent(evt);

		NodeRemovedFromDocument(oldChild);
	}

// Do the work
	ChildNode* previous = oldChild->get_previousSibling();

	ChildNode* next = oldChild->get_nextSibling();

	if (previous != NULL)
		previous->set_nextSibling(next);
	else
		m_firstChild = next;

	if (next != NULL)
		next->set_previousSibling(previous);
	else
		m_lastChild = previous;

	oldChild->set_previousSibling(nullptr);
	oldChild->set_nextSibling(nullptr);

	for (int i = 0; i < m_childNodes->m_items.GetSize(); ++i)
	{
		if (m_childNodes->m_items[i] == oldChild)
		{
#if 0
			ASSERT(0);
			/////////
			CComQIPtr<INotifySend, &IID_INotifySend> cp = (IUnknown*)oldChild;
			if (cp)
			{
				CComQIPtr<INotifyGet, &IID_INotifyGet> get = (IUnknown*)thisNode;
				if (get)
				{
					cp->Unadvise(get);
				}
			}
#endif
			/////////

		//	m_childNodes->m_items.erase(&m_childNodes->m_items[i]);
			m_childNodes->m_items.RemoveAt(i);
			break;
		}
	}

	oldChild->set_parentNode(NULL);

	return oldChild;
}

Node* Node::replaceChild(Node *newChild, Node *oldChild)
{
	ASSERT(0);
#if 0
	ASSERT(newChild != NULL);
	ASSERT(oldChild != NULL);
	ASSERT(pVal != NULL);
	if (newChild == NULL) return E_INVALIDARG;
	if (oldChild == NULL) return E_INVALIDARG;
	if (pVal == NULL) return E_POINTER;

	if (TRUE)
	{
		CComQIPtr<ILDOMDocumentFragment, &IID_ILDOMDocumentFragment> fragment((IUnknown*)newChild);
		if (fragment)
		{
			CComPtr<ILDOMNode> beforeChild;
			oldChild->get_nextSibling(&beforeChild);

			thisNode->removeChild(oldChild, pVal);

			CComPtr<ILDOMNode> child;
			fragment->get_firstChild(&child);
			while (child)
			{
				CComPtr<ILDOMNode> nextSibling;
				child->get_nextSibling(&nextSibling);

				insertNode(thisNode, child, beforeChild, NULL);

				child = nextSibling;
			}
		}
		else
		{
			CComPtr<ILDOMNode> beforeChild;
			oldChild->get_nextSibling(&beforeChild);

			thisNode->removeChild(oldChild, pVal);

			insertBefore(thisNode, newChild, CComVariant(beforeChild), NULL);
		}
	}
	else
	{
#if 0
		for (int i = 0; i < m_childNodes->m_items.GetSize(); i++)
		{
			if (m_childNodes->m_items[i] == oldChild)
			{
				newChild->AddRef();
				m_childNodes->m_items[i] = newChild;

				*pVal = oldChild;
			}
		}
#endif
	}

	return S_OK;
#endif
	return NULL;
}

bool Node::hasChildNodes() const
{
	return (m_firstChild != NULL);
}

bool Node::hasAttributes() const
{
	return false;
}

bool Node::isSupported(StringIn feature, StringIn version)
{
	return false;
}

NamedNodeMap* Node::get_attributes() const
{
	return NULL;
}

NodeList* Node::get_childNodes() const
{
	return m_childNodes;
}

ErrorCode Node::getTextOffset(long which, long *offset)
{
	if (which >= 0 && which < 10)
	{
		*offset = m_textOffset[which];
		return Success;
	}
	else
	{
		ASSERT(0);
		*offset = -1;
		return Error;
	}
}

ErrorCode Node::setTextOffset(long which, long offset)
{
	if (which >= 0 && which < 10)
	{
		m_textOffset[which] = offset;
		return Success;
	}
	else
	{
		ASSERT(0);
		return Error;
	}
}

/*
ErrorCode Node::setWhiteSpace(long which, BSTR whitespace)
{
	// TODO: Add your implementation code here

	return S_OK;
}

ErrorCode Node::getWhiteSpace(long which, BSTR *whitespace)
{
	// TODO: Add your implementation code here

	return S_OK;
}
*/

String Node::get_nodeName() const
{
	return m_nodeName;
}

String Node::get_namespaceURI() const
{
	return m_namespaceURI;
}

void Node::set_namespaceURI(StringIn namespaceURI)
{
	m_namespaceURI = namespaceURI;
}

void Node::set_nodeName(StringIn qualifiedName)
{
	m_nodeName = qualifiedName;

// Set prefix and localName
	size_t ncolon = qualifiedName.find(':');
	if (ncolon != String::npos)
	{
		m_prefix = qualifiedName.LeftOf(ncolon);
		m_localName = qualifiedName.RightOf(ncolon+1);
	}
	else
	{
		m_prefix = nullptr;
		m_localName = m_nodeName;
	}
}

String Node::get_prefix() const
{
	return m_prefix;
}

void Node::set_prefix(StringIn prefix)
{
	m_prefix = prefix;
	return;


// ?????????
	/*
// Change nodename
	if (m_localName.Length())
	{
		m_nodeName = m_prefix;
		m_nodeName += L":";
		m_nodeName += m_localName;
	}
	else
	{
		m_nodeName = m_prefix;
		m_nodeName += L":";
		m_nodeName += m_nodeName;
	}
	*/
}

String Node::get_localName() const
{
	return m_localName;
}

void Node::set_localName(StringIn newVal)
{
	VERIFY(0);
//	m_localName = newVal;
}

String Node::get_textContent()
{
	Node* child = get_firstChild();

	if (child == nullptr) return nullptr;

	if (child->get_nextSibling() == nullptr)
	{
		return child->get_textContent();
	}
	else
	{
		String str;

		while (child != nullptr)
		{
			String str2 = child->get_textContent();
			str += str2;

			child = child->get_nextSibling();
		}

		return str;
	}
}

void Node::set_textContent(StringIn newVal)
{
	ASSERT(0);
}

}	// Web
}	// System
