#include "stdafx.h"
#include "LXML2.h"
#include "AnimationTarget.h"

#include "ScriptSite.h"

//#include "LHTMLWindow.h"
#if 0
#include "LBoxWindow.h"
#endif

//#include "LXMLDocumentView.h"

#include "PElement.h"

namespace System
{
namespace Web
{

struct CEvent
{
public:
	ImmutableString<wchar_t> attName;
	ImmutableString<wchar_t> eventName;
};

CEvent events[] =
{
	{WSTR("onclick"), WSTR("click")},
	{WSTR("onmousedown"), WSTR("mousedown")},
	{WSTR("onmouseup"), WSTR("mouseup")},
	{WSTR("onmouseover"), WSTR("mouseover")},
	{WSTR("onmouseout"), WSTR("mouseout")},
	{WSTR("onmousemove"), WSTR("mousemove")},
	{WSTR("onload"), WSTR("SVGLoad")},
	{WSTR("onunload"), WSTR("SVGUnload")},
	{WSTR("onzoom"),	WSTR("SVGZoom")},
};

AttributeContentListener::AttributeContentListener(Element* element, StringIn code, bool preventDefaultOnReturnValue)
{
	m_preventDefaultOnReturnValue = preventDefaultOnReturnValue;
	m_element = element;

	if (code != nullptr)
	{
		m_pFun = new JSVM::ScriptFunction;

		ecma::ScriptCode* scriptcode = new ecma::ScriptCode;
		scriptcode->AddText(code);

	//	uint8* m_codeData;
	//	ULONG m_codeLength;
	//	ActionContext* m_pContext;

		m_pFun->m_codeData = scriptcode->m_code.begin();
		m_pFun->m_codeLength = scriptcode->m_code.size();
		m_pFun->m_pContext = scriptcode->m_as_context;

		m_pFun->m_args.push_back(String(L"event"));
	}
	else
	{
		m_pFun = nullptr;
	}
}

void AttributeContentListener::handleEvent(Event* evt)
{
	JSVM::ScriptFunction* fun = m_pFun;//dynamic_cast<ActionScripting::ActionScriptFunction*>(elt.m_variant.m_pObject);

	if (fun)
	{
		JSVM::VM vm;
	//	vm.m_global = m_element;

		ASSERT(0);
#if 0	// Have this
		vm.m_gui_threadId = Gui::gui_threadId;
#endif

		vm.m_global = dynamic_cast<Node*>(evt->get_target())->m_ownerDocument->m_pWindow->m_pScriptGlobal;
		JSVM::StackFrame* frame = dynamic_cast<Node*>(evt->get_target())->m_ownerDocument->m_pWindow->m_pScriptGlobal;

	//	ActionScripting::StackFrame* frame = new ActionScripting::StackFrame;

		frame->m_variables["this"] = m_element;

		vm.push(evt);

		try
		{
			fun->dispatch(&vm, frame, 1);

			if (vm.m_stack.size())
			{
				Variant retval = vm.pop();

				/*
				If the function returns the exact boolean value false, the event's preventDefault()
				method must then invoked. Exception: for historical reasons, for the HTML mouseover event,
				the preventDefault() method must be called when the function returns true instead.
				*/
				if (retval.IsBool() &&
					retval.u.bool_val == m_preventDefaultOnReturnValue)
				{
					evt->preventDefault();
				}
			}
		}
		catch (Exception* e)
		{
			MessageBoxW(nullptr, e->get_Reason().c_strw(), L"js", MB_OK);
		}
		catch (std::exception& e)
		{
			MessageBoxA(nullptr, e.what(), "js", MB_OK);
		}
	}
}

///////////////////////////////////////////////////////////////////////////
// Element

Element::Element(PElementBase* pElement) : ChildNode(pElement)
{
//	m_pElement = pElement;
//	m_pNode = pElement;

//	m_dwScriptCookie = 0;
	m_bSetStyleAttribute = 0;

	m_attributes = new NamedNodeMap;
	m_attributes->m_pListener = this;
}

Element::Element(PElementBase* pElement, NamedNodeMap* attributes) : ChildNode(pElement)
{
//	m_pElement = pElement;
//	m_pNode = pElement;

//	m_dwScriptCookie = 0;
	m_bSetStyleAttribute = 0;

	if (attributes)
		m_attributes = attributes;
	else
		m_attributes = new NamedNodeMap;

	m_attributes->m_pListener = this;

	for (size_t i = 0; i < m_attributes->m_items.GetSize(); ++i)
	{
		Attr* attr = dynamic_cast<Attr*>(m_attributes->m_items[i]);
		if (attr == nullptr)
		{
			raise(DOMException("not an attr"));
		}

		attr->SetOwnerElement(this);
	//	attr->m_pListener = this;
	}
}

Element::~Element()
{
	m_attributes->m_pListener = nullptr;
	delete m_attributes;
}

void Element::AddAttributeContentEventHandler(StringIn type, StringIn attributeName, bool preventDefaultOnReturnValue)
{
	addEventListenerNS(nullptr, type, new AttributeContentListener(this, getAttribute(attributeName), preventDefaultOnReturnValue), false, NULL);
}

void Element::UnspecifiedAttr(inner_ptr<Attr*> ppAttr, StringIn namespaceURI, StringIn localName)
{
	Attr* attr = (Attr*)m_attributes->getNamedItemNS(namespaceURI, localName);
	if (attr == nullptr)
	{
		attr = new Attr;
		attr->set_namespaceURI(namespaceURI);
		attr->set_nodeName(localName);
	//	m_attributes->setNamedItemNS(attr);
	//	ASSERT(!attr->get_specified());
		m_attributes->m_items.Add(attr);
	}
	else
	{
		attr->m_specified = true;
	}

	*ppAttr.ptr = attr;
	attr->m_ppAttr = ppAttr;
}

TypeInfo* Element::get_schemaTypeInfo()
{
	return m_schemaTypeInfo;
}

CATXMLAttr* Element::GetXMLAttribute(StringIn attributeName)
{
	for (int i = 0; i < m_xmlAttrs.GetSize(); ++i)
	{
		if (m_xmlAttrs[i]->m_attributeName == attributeName)
		{
			return m_xmlAttrs[i];
		}
	}

	return nullptr;
}

void Element::SetValues(StringIn namespaceURI, StringIn attrName, Element* element)
{
	for (int i = 0; i < m_xmlAttrs.GetSize(); ++i)
	{
		if (m_xmlAttrs[i]->m_namespaceURI == namespaceURI &&
			m_xmlAttrs[i]->m_attributeName == attrName)
		{
			m_xmlAttrs[i]->SetValues(element);
			//break; There can be several attrs connected to the same attribute

		// TODO: a better way would be that the ILDOMAttr has a list of attrs
		}
	}
}

void Element::SetAttribute(StringIn namespaceURI, StringIn attrName, Element* element)
{
	for (int i = 0; i < m_xmlAttrs.GetSize(); i++)
	{
		if (m_xmlAttrs[i]->m_namespaceURI == namespaceURI &&
			m_xmlAttrs[i]->m_attributeName == attrName)
		{
			m_xmlAttrs[i]->SetAttribute(element);
			break;
		}
	}
}

void Element::SetAllValues(Element* element)
{
	for (int i = 0; i < m_xmlAttrs.GetSize(); ++i)
	{
		m_xmlAttrs[i]->SetValues(element);
	}
}

NodeType Element::get_nodeType() const
{
	return NODE_ELEMENT;
}

bool Element::hasAttribute(StringIn name)
{
	Attr* attr = getAttributeNode(name);
	return attr != nullptr;
}

bool Element::hasAttributeNS(StringIn namespaceURI, StringIn localName)
{
	Attr* attr = getAttributeNodeNS(namespaceURI, localName);
	return attr != nullptr;
}

Attr* Element::getAttributeNode(StringIn name)
{
	return dynamic_cast<Attr*>(m_attributes->getNamedItem(name));
}

Attr* Element::getAttributeNodeNS(StringIn qualifiedName, StringIn localName)
{
	return dynamic_cast<Attr*>(m_attributes->getNamedItemNS(qualifiedName, localName));
}

String Element::getAttribute(StringIn name)
{
	Attr* attr = dynamic_cast<Attr*>(m_attributes->getNamedItem(name));
	if (attr)
	{
		return attr->get_value();
	}

	return nullptr;
}

String Element::getAttributeNS(StringIn namespaceURI, StringIn localName)
{
	Attr* attr = dynamic_cast<Attr*>(m_attributes->getNamedItemNS(namespaceURI, localName));
	if (attr)
	{
		return attr->get_value();
	}

	return nullptr;
}

/*
String Element::getAttribute(const WCHAR* name)
{
	Attr* attr = dynamic_cast<Attr*>(m_attributes->getNamedItem(name));
	if (attr)
	{
		return attr->get_value();
	}

	return NULL;
}

String Element::getAttributeNS(const WCHAR* namespaceURI, const WCHAR* localName)
{
	Attr* attr = dynamic_cast<Attr*>(m_attributes->getNamedItemNS(namespaceURI, localName));
	if (attr)
	{
		return attr->get_value();
	}

	return NULL;
}
*/

String Element::get_tagName()
{
	return get_nodeName();
}

void Element::set_ownerDocument(Document* newVal)
{
	m_ownerDocument = newVal;
}

void Element::removeAttribute(StringIn name)
{
	m_attributes->removeNamedItem(name);
}

void Element::removeAttributeNS(StringIn namespaceURI, StringIn localName)
{
	m_attributes->removeNamedItemNS(namespaceURI, localName);
}

NamedNodeMap* Element::get_attributes() const
{
	return m_attributes;
}

void Element::set_attributes(NamedNodeMap* newVal)
{
	ASSERT(newVal);

	///m_attributes->Unadvise(static_cast<IBase*>(this));
	m_attributes->m_pListener = nullptr;
	//m_attributes->Release();

	m_attributes = newVal;
	//m_attributes->AddRef();
	//DWORD cookie;
	//m_attributes->Advise(static_cast<IBase*>(this), &cookie);
	m_attributes->m_pListener = this;

	for (int i = 0; i < m_attributes->m_items.GetSize(); ++i)
	{
		Attr* attr = dynamic_cast<Attr*>(m_attributes->m_items[i]);
		attr->SetOwnerElement(this);
	//	attr->m_pListener = this;
	}
}

static ImmutableString<wchar_t> MutationEvent_str(L"MutationEvent");
static ImmutableString<wchar_t> DOMAttrModified_str(L"DOMAttrModified");

void Element::OnAddedNode(NamedNodeMap* nodemap, Node* node)
{
	Attr* attr = dynamic_cast<Attr*>(node);

	attr->SetOwnerElement(this);
//	attr->m_pListener = this;

	OnAttrValueChanged(nullptr, attr);

	String name = attr->get_nodeName();

	String value = attr->get_value();

	// Fire add attribute event
	{
		EventTarget* eventTarget = this;//dynamic_cast<EventTarget*>(this);//static_cast<T*>(this)->GetUnknown();
		ASSERT(eventTarget);

		DocumentEvent* ownerDocumentEvent = dynamic_cast<DocumentEvent*>(m_ownerDocument);
		if (ownerDocumentEvent)
		{
			MutationEvent* evt = static_cast<MutationEvent*>(ownerDocumentEvent->createEvent(&MutationEvent_str));

			//if (event)
			{
			// Create an attr addition event
				evt->initMutationEvent(&DOMAttrModified_str, true, false, attr, nullptr/*prevValue*/, value, name, CHANGE_ADDITION);
				bool doDefault = eventTarget->dispatchEvent(evt);
			}
		}
	}
}

void Element::OnRemoveNode(NamedNodeMap* nodemap, Node* node)
{
	Attr* attr = dynamic_cast<Attr*>(node);

	ASSERT(0);
#if 0

	OnAttrValueChanged(NULL, attr);

	sysstring name = attr->get_nodeName();

	sysstring prevValue = attr->get_value();

// Event
	CComQIPtr<ILDOMEventTarget, &IID_ILDOMEventTarget> eventTarget = static_cast<T*>(this)->GetUnknown();
	ASSERT(eventTarget);

	CComQIPtr<ILDOMDocumentEvent, &IID_ILDOMDocumentEvent> ownerDocumentEvent = m_ownerDocument;
	if (ownerDocumentEvent)
	{
		CComPtr<ILDOMMutationEvent> event;
		ownerDocumentEvent->createEvent(OLESTR("MutationEvent"), (ILDOMEvent**)&event);

		if (event)
		{
			event->initMutationEvent(OLESTR("DOMAttrModified"), VARIANT_TRUE, VARIANT_FALSE, attr, prevValue, NULL, name, CHANGE_REMOVAL);


			eventTarget->dispatchEvent(event);
		}
	}

	static_cast<Attr*>(attr.p)->m_pListener = NULL;
	attr->set_ownerElement(NULL);
#endif
}

#if 0
HRESULT Element::addBehavior(/*[in]*/ BSTR bstrUrl, /*[in]*/ VARIANT* pvarFactory, /*[out,retval]*/ long *pCookie)
{
	HRESULT hr = E_FAIL;	// Assume failure

	if (m_pBehaviorSite == NULL)
	{
		CComObject<CLElementBehaviorSite>::CreateInstance(&m_pBehaviorSite);
		m_pBehaviorSite->AddRef();
		m_pBehaviorSite->m_pElement = CComQIPtr<ILDOMElement, &IID_ILDOMElement>((IUnknown*)this);
	}

	if (pCookie) *pCookie = 0;

	CBehavior* pBehavior = new CBehavior;
	pBehavior->m_url = bstrUrl;
	pBehavior->m_cookie = ++m_nextCookie;
	pBehavior->m_factory = V_UNKNOWN(pvarFactory);
	m_behaviors.Add(pBehavior);

	CComQIPtr<ILElementBehavior, &IID_ILElementBehavior> behavior = (IUnknown*)pBehavior->m_factory;
	if (behavior)
	{
		behavior->Init(m_pBehaviorSite);
	}

	if (pCookie) *pCookie = pBehavior->m_cookie;

	return hr;
}
#endif

void Element::AddEventListener(Attr* attr, StringIn event)
{
	ASSERT(0);
#if 0
#if _WINDOWS
	CScriptSite* pScriptSite = CComQIPtr<CLDOMDocumentImplImpl>(m_ownerDocument)->m_pScriptSite;
	CComQIPtr<IActiveScriptParseProcedure> activeScriptParseProcedure = pScriptSite->m_activeScript;

	CComBSTR code;
	attr->get_value(&code);

	if (pScriptSite->m_debugDocumentHelper)
	{
		long charOffset = 0;	// TODO

		DWORD dwSourceContext;
		HRESULT hr = pScriptSite->m_debugDocumentHelper->DefineScriptBlock(charOffset, code.Length(), pScriptSite->m_activeScript, FALSE/*fScriptlet*/, &dwSourceContext);
#if 0
		CComQIPtr<Element>(element)->m_dwScriptCookie = dwSourceContext;
#endif
	}

	CComPtr<IDispatch> disp;

	HRESULT hr = activeScriptParseProcedure->ParseProcedureText(
		code,	// code
		OLESTR("evt"),//L"",	// formal params
		OLESTR("anonymous"),	// procedure name
		NULL,	// item name
		NULL,	// punkContext
		NULL,	// delimiter
		0,	// dwSourceContextCookie
		0,	// start line number
		SCRIPTPROC_IMPLICIT_THIS,//SCRIPTTEXT_ISVISIBLE,// | SCRIPTTEXT_ISPERSISTENT,	// flags
		&disp);

	if (SUCCEEDED(hr))
	{
		CComObject<CEventListener>* pListener;
		CComObject<CEventListener>::CreateInstance(&pListener);
		pListener->AddRef();
		pListener->m_listenerElement = element;
		pListener->m_handlerElement = NULL;//handlerElement;
		pListener->m_disp = disp;

		attr->m_pEventListener = pListener;

		EventTarget* eventTarget = dynamic_cast<EventTarget*>(element);
		if (eventTarget)
		{
			eventTarget->addEventListener(event, pListener, false/*useCapture*/);
		}
	}
#endif	// _WINDOWS
#endif
}

void Element::AddEventListeners()
{
//	CComQIPtr<IActiveScriptParseProcedure> activeScriptParseProcedure = pScriptSite->m_activeScript;

	int count = _countof(events);

	for (int n = 0; n < count; ++n)
	{
		String eventName = &events[n].eventName;

		Attr* attr = getAttributeNode(&events[n].attName);

		if (attr)
		{
			AddEventListener(attr, eventName);
		}
	}
}

void Element::UpdateAnimationElements(Element* domElement)
{
	domElement->SetAllValues(domElement);

#if 0
	CComQIPtr<ElementTimeImplImpl> elementTime = domElement;
	if (elementTime)
	{
		/*
		CComQIPtr<ILSMILSeqElement> seqElement = elementTime;
		if (seqElement)
		{
			MessageBeep(-1);
		}
		*/

		elementTime->Init();
	}
#endif

	ASSERT(0);
#if 0
	CComQIPtr<ILElementCSSInlineStyle, &IID_ILElementCSSInlineStyle> stylable = (IUnknown*)domElement;
	if (stylable)
	{
		if (CComQIPtr<Element>((IUnknown*)domElement)->m_bSetStyleAttribute == 0)
		{
			CComQIPtr<Element>((IUnknown*)domElement)->m_bSetStyleAttribute++;

			CComBSTR style;
			domElement->getAttribute(OLESTR("style"), &style);
			if (style.Length())
			{
				CComPtr<ILCSSStyleDeclaration> declaration;
				stylable->get_style(&declaration);

				declaration->set_cssText(style);
			}

			CComQIPtr<Element>((IUnknown*)domElement)->m_bSetStyleAttribute--;
		}
	}
#endif
///////////////////////////

	Node* child = domElement->get_firstChild();

	while (child != NULL)
	{
		NodeType nodeType = child->get_nodeType();

		if (nodeType == NODE_ELEMENT)
		{
			Element* element = dynamic_cast<Element*>(child);
			element->UpdateAnimationElements(element);	// Recurse
		}

		child = child->get_nextSibling();
	}
}

// virtual
void Element::OnAttrValueChanged(StringIn /*nodeName*/, Attr* attr)
{
	String nodeName = attr->get_localName();
	if (nodeName == nullptr)
	{
		nodeName = attr->get_nodeName();
	}

	String namespaceURI = attr->get_namespaceURI();
	//if ((BSTR)namespaceURI == NULL) namespaceURI = OLESTR("");

	SetValues(namespaceURI, nodeName, this);

#if 0	// TODO, had this
	CComQIPtr<ILAnimationElement, &IID_ILAnimationElement> animation = (IUnknown*)thisNode;
	if (animation)
	{
		CComQIPtr<CLAnimationElementImplImpl> pAnimation((IUnknown*)animation);

		pAnimation->SetValuesFromAttributes();
	}
#endif

	{
		size_t count = _countof(events);
		for (size_t n = 0; n < count; ++n)
		{
			if (nodeName == &events[n].attName)
			{
#if 0
			// TODO, remove if already existing
				ASSERT(attr->m_pEventListener == NULL);
#endif

				AddEventListener(attr, &events[n].eventName);
			}
		}
	}

#if 0	// TODO, had this
	// TODO
	if (!wcscmp(nodeName.c_str(), OLESTR("style")))
	{
		// Reparse style attribute
		CComQIPtr<ILElementCSSInlineStyle, &IID_ILElementCSSInlineStyle> stylable = (IUnknown*)thisNode;
		if (stylable)
		{
			if (m_bSetStyleAttribute == 0)
			{	
				m_bSetStyleAttribute++;

				CComBSTR value;
				attr->get_value(&value);
				//thisNode->getAttribute(L"style", &style);

				//if (value.Length())
				{
					CComPtr<ILCSSStyleDeclaration> declaration;
					stylable->get_style(&declaration);

					declaration->set_cssText(value);
				}

				m_bSetStyleAttribute--;
			}

			for (int i = 0; i < m_pNodes.GetSize(); i++)
			{
				((CPElement*)m_pNodes[i])->GetCSSPropertiesAndChildren();

#if 0	// I had this
				if (m_pNodes[i]->m_pView)	// TODO
				{
					m_pNodes[i]->m_pView->CalcDims((CPElement*)m_pNodes[i]);
				}
#endif
			}
		}
	}

// TODO
	CComQIPtr<CLElementTimeImplImpl> elementTimeImpl = (IUnknown*)thisNode;
	if (elementTimeImpl)
	{
		if (!wcscmp(nodeName, OLESTR("begin")) ||
			!wcscmp(nodeName, OLESTR("end")) ||
			!wcscmp(nodeName, OLESTR("dur")) ||
			!wcscmp(nodeName, OLESTR("speed")) ||
			!wcscmp(nodeName, OLESTR("accelerate")) ||
			!wcscmp(nodeName, OLESTR("decelerate")) ||
			!wcscmp(nodeName, OLESTR("autoReverse")) ||
			!wcscmp(nodeName, OLESTR("clipBegin")) ||
			!wcscmp(nodeName, OLESTR("clipEnd")))
		{
			if (m_parentNode)	// If inserted in document
			{
				if (elementTimeImpl->m_pCurrentInterval)
				{
					elementTimeImpl->m_pCurrentInterval->Release();
					elementTimeImpl->m_pCurrentInterval = NULL;
				}
				elementTimeImpl->m_instanceBeginList.m_items.RemoveAll();
				elementTimeImpl->m_instanceEndList.m_items.RemoveAll();

				//elementTimeImpl->Init();
				//elementTimeImpl->m_pCurrentInterval = elementTimeImpl->GetFirstInterval();

				elementTimeImpl->CalculateTimeBeforeParent();

			// Tell parent that a child has changed
				ILElementTimeContainer* parentTimeContainer;
				elementTimeImpl->get_parentTimeContainer(&parentTimeContainer);
				ASSERT(0);
#if 0
				CComQIPtr<CLElementTimeContainerImplImpl> parentTimeContainerImpl((IUnknown*)parentTimeContainer);
				if (parentTimeContainerImpl)
				{
					parentTimeContainerImpl->RecalculateTime();
				}
#endif

				elementTimeImpl->CalculateTimeAfterParent();
			}
		}
	}

	if (animation)
	{
		CComPtr<ILDOMElement> targetElement;
		animation->get_targetElement(&targetElement);

		CComQIPtr<ILSMILAnimationTarget, &IID_ILSMILAnimationTarget> animtarget = (IUnknown*)targetElement;
		CAnimationTarget* pAnimationTarget = static_cast<CAnimationTarget*>(animtarget.p);

		if (pAnimationTarget)
		{
			pAnimationTarget->DoAnimation();

			if (TRUE)
			{
				for (int i = 0; i < CComQIPtr<Element>((IUnknown*)targetElement)->m_pNodes.GetSize(); i++)
				{
					CPElement* pPElement = (CPElement*)CComQIPtr<Element>((IUnknown*)targetElement)->m_pNodes[i];

					pPElement->CalculateBoundsAndChildren();

					if (pPElement->m_parent)
						pPElement->m_parent->RecalculateParentBounds();
				}
			}
		}
	}
	else
	{
		CComQIPtr<ILSMILAnimationTarget, &IID_ILSMILAnimationTarget> animtarget = (IUnknown*)thisNode;
		CAnimationTarget* pAnimationTarget = static_cast<CAnimationTarget*>(animtarget.p);

		if (pAnimationTarget)
		{
			pAnimationTarget->DoAnimation();
		}
	}
#endif

		TRACE("TODO: OnAttrChanged(attr)\n");//ASSERT(0);
#if 0	// TODO
	for (int i = 0; i < m_pNodes.GetSize(); i++)
	{
		((CPElement*)m_pNodes[i])->OnAttrChanged(attr);
	}
#endif

#if 0	// removed this (use above instead)
	{	// Hack
		CComQIPtr<INotifySend> cp = this;
		cp->FireOnChanged((NotifyType)-1, this, DISPID_UNKNOWN);	// ???...
	}
#endif

}

Attr* Element::setAttributeNode(Attr* newAttr)
{
	return setAttributeNodeNS(newAttr);
}

Attr* Element::setAttributeNodeNS(Attr* newAttr)
{
	return (Attr*)m_attributes->setNamedItem(newAttr);
}

void Element::setAttribute(StringIn name, StringIn value)
{
// TODO: call setAttributeNS(NULL, ...)
	size_t length = m_attributes->m_items.GetSize();

	for (int i = 0; i < length; i++)
	{
		Attr* pAttr = dynamic_cast<Attr*>(m_attributes->m_items[i]);

		String attrname = pAttr->get_name();

		if (attrname == name)
		{
		// Set the new value
			pAttr->set_value(value);
			return;
		}
	}

// Create new attribute

	Attr* pAttr = m_ownerDocument->createAttribute(name);
	pAttr->set_value(value);

	m_attributes->setNamedItem(pAttr);
}

void Element::setAttributeNS(StringIn namespaceURI, StringIn qualifiedName, StringIn value)
{
	if (qualifiedName == nullptr)
	{
		raise(DOMException("Invalid argument"));
	}

// Extract localName from qualifiedName
	String localName;
	{
		size_t ncolon = qualifiedName.find(':');
		// This works since npos == -1
	//	if (ncolon != String::npos)
			localName = qualifiedName.RightOf(ncolon+1);
	//	else
		//	localName = qualifiedName;
	}

	uint length = m_attributes->m_items.GetSize();

	for (uint i = 0; i < length; ++i)
	{
		Attr* pAttr = dynamic_cast<Attr*>(m_attributes->m_items[i]);

		String attrname = pAttr->get_localName();
		if (attrname.GetLength() == 0)
		{
			attrname = pAttr->get_name();
		}

		String attrnamespaceURI = pAttr->get_namespaceURI();
	//	if ((BSTR)attrnamespaceURI == NULL) attrnamespaceURI = OLESTR("");

		if ((namespaceURI == attrnamespaceURI) && (attrname == localName))
		{
		// Set the new value
			pAttr->set_value(value);
			return;
		}
	}

// Create new attribute

	Attr* pAttr = m_ownerDocument->createAttributeNS(namespaceURI, qualifiedName);
	pAttr->set_value(value);

	m_attributes->setNamedItemNS(pAttr);
}

void Element::set_textContent(StringIn newVal)
{
// Optimize if there is one single textnode already there
#if 0
	CComQIPtr<ILDOMText, &IID_ILDOMText> textNode;
	if ((m_childNodes->m_items.size() == 1) && (textNode = m_childNodes->m_items[0]))
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

		if (newVal.GetLength() > 0)
		{
			Text* text = m_ownerDocument->createTextNode(newVal);
			if (text)
			{
				appendChild(text);
			}
		}
	}
}

Node* Element::cloneNodeExport(Document* ownerDocument, bool deep) const
{
	String tagName = get_localName();
	/*
	if (tagName == NULL)
	{
		tagName = m_nodeName;
	}
	*/

	String namespaceURI = get_namespaceURI();

	Element* newNode = ownerDocument->createElementNS(namespaceURI, tagName);
	if (newNode)
	{
		// Clone attributes
		{
			NamedNodeMap* attributes = m_attributes;

			NamedNodeMap* newAttributes = newNode->get_attributes();

			unsigned int nattrs = m_attributes->m_items.GetSize();

			for (unsigned int i = 0; i < nattrs; ++i)
			{
				Attr* attr = (Attr*)m_attributes->m_items[i];

				Node* newAttr = attr->cloneNodeExport(ownerDocument, true);

				newAttributes->setNamedItem(newAttr);
			}
		}

		// Clone childNodes
		if (deep)
		{
			NodeList* childNodes = get_childNodes();

			unsigned int nChildNodes = childNodes->get_length();

			for (unsigned int i = 0; i < nChildNodes; i++)
			{
				Node* child = childNodes->item(i);

				Node* newChild = child->cloneNodeExport(ownerDocument, true);

				newNode->appendChild(newChild);
			}
		}
	}

	return newNode;
}

// XDM::IData
XDM::IData* Element::getParent()
{
	return dynamic_cast<XDM::IData*>(m_parentNode);
}

unsigned int Element::getPosition()
{
	ASSERT(m_parentNode);

	if (m_parentNode->get_parentNode() == NULL)
		return 0;

	NodeList* nodes = m_parentNode->get_childNodes();
	unsigned int length = nodes->get_length();
	for (unsigned int i = 0; i < length; i++)
	{
		if (nodes->item(i) == this)
			return i;
	}
	ASSERT(0);
	return ~0;
}

/*
System::StringW* Element::getName()
{
	return get_localName();
}

System::StringW* Element::getNamespaceURI()
{
	return get_namespaceURI();
}
*/

XDM::IData* Element::getRoot()
{
	return m_ownerDocument;
}

unsigned int Element::getAttributeCount()
{
	return m_attributes->get_length();
}

Variant Element::getAttributeValue(unsigned int index)
{
	return Variant(((Attr*)m_attributes->item(index))->get_value());
}

String Element::getAttributeName(unsigned int index)
{
	return m_attributes->item(index)->get_localName();
}

String Element::getAttributeNamespaceURI(unsigned int index)
{
	return m_attributes->item(index)->get_namespaceURI();
}

System::Type* Element::getAttributeType(unsigned int index)
{
	return 0;
}

unsigned int Element::getChildCount()
{
	return m_childNodes->get_length();
}

bool Element::IsChildText(unsigned int index)
{
	return m_childNodes->item(index)->get_nodeType() == NODE_TEXT;
}

String Element::getChildName(unsigned int index)
{
	return m_childNodes->item(index)->get_localName();
}

String Element::getChildNamespaceURI(unsigned int index)
{
	return m_childNodes->item(index)->get_namespaceURI();
}

Type* Element::getChildType(unsigned int index)
{
	return 0;
}

XDM::IData* Element::getChildElement(unsigned int index)
{
	return dynamic_cast<XDM::IData*>(m_childNodes->item(index));
}

String Element::getChildText(unsigned int index)
{
	return m_childNodes->item(index)->get_textContent();
}

Object* Element::GetObject()
{
	return this;
}

}	// Web
}
