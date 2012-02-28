#include "stdafx.h"
#include "LXML2.h"

#include "ASDTDModel.h"

#include "DOMParser.h"
#include "XMLParser.h"

#include <stdlib.h>

//#include "LDOMImplementation.h"

namespace System
{
namespace Web
{

Element* getElementById(Element* element, StringIn elementId);

Document::Document()
{
//	m_xpathEvaluator = NULL;

	m_errorHandler = nullptr;

	m_documentElement = nullptr;
	m_doctype = nullptr;

	m_standalone = false;
//	m_isXML = true;

	m_async = false;	// TODO, this should default to TRUE

	m_implementation = DOMImplementation::get_DOMImplementation();

	m_pWindow = nullptr;

#if _WINDOWS
	m_hThread = nullptr;
	m_threadID = 0L;
#endif

	MessageBeep(-1);
#if 0
	m_styleSheets = new Style::StyleSheetList;
#endif
}

Document::~Document()
{
}

NodeType Document::get_nodeType() const
{
	return NODE_DOCUMENT;
}

ImmutableString<WCHAR> documentName(L"#document");

IAbstractView* Document::get_defaultView()
{
	return m_pWindow;
}

String Document::get_nodeName() const
{
	return &documentName;
}

bool Document::get_async() const
{
	return m_async;
}

void Document::set_async(bool newVal)
{
	m_async = newVal;
}

DOMImplementation* Document::get_implementation()
{
	return m_implementation;
}

String Document::get_actualEncoding() const
{
	return nullptr;
}

void Document::set_actualEncoding(StringIn newVal)
{
	ASSERT(0);
}

String Document::get_xmlEncoding() const
{
	return m_encoding;
}

void Document::set_xmlEncoding(StringIn newVal)
{
	m_encoding = newVal;
}

bool Document::get_xmlStandalone() const
{
	return m_standalone;
}

void Document::set_xmlStandalone(bool newVal)
{
	m_standalone = newVal;
}

String Document::get_xmlVersion() const
{
	return m_version;
}

void Document::set_xmlVersion(StringIn newVal)
{
	m_version = newVal;
}

DocumentType* Document::get_doctype() const
{
	return m_doctype;
}

Node* Document::cloneNodeExport(Document* /*ownerDocument*/, bool deep) const
{
	ASSERT(0);
	return NULL;
}

// DOM Level 2
Node* Document::importNode(/*[in]*/ Node* importedNode, /*[in]*/ bool deep)
{
	ASSERT(importedNode != NULL);

	if (importedNode == NULL) THROW(-1);

//	CComQIPtr<CLDOMNodeImplImpl, &IID_IUnknown/*TODO*/> importedNodeImpl = importedNode;
//	if (importedNodeImpl == NULL) return E_FAIL;

	return importedNode->cloneNodeExport(this, deep);
}

// DOM Level 3
Node* Document::adoptNode(Node* sourceNode)
{
	ASSERT(sourceNode != NULL);
	if (sourceNode == NULL) THROW(new Exception(WSTR("null pointer")));

	NodeType nodeType = sourceNode->get_nodeType();

	if (nodeType == NODE_ATTRIBUTE)
	{
		Attr* attr = dynamic_cast<Attr*>(sourceNode);
		attr->SetOwnerElement(NULL);
		adoptNode(attr);
	}
	else
	{
		Node* parentNode = sourceNode->get_parentNode();
		if (parentNode)
		{
			parentNode->removeChild(sourceNode);
		}

		adoptNode(sourceNode);
	}

	return sourceNode;
}

Node* Document::renameNode(Node* n, StringIn namespaceURI, StringIn name)
{
	ASSERT(0);
	return NULL;
#if 0
	return CLDOMDocumentImplImpl::renameNode(this, n, namespaceURI, name);
#endif
#if 0
	ASSERT(n != NULL);
	ASSERT(pVal != NULL);
	if (n == NULL) return E_INVALIDARG;
	if (pVal == NULL) return E_POINTER;

	CComBSTR prevNamespaceURI;
	n->get_namespaceURI(&prevNamespaceURI);

	CComBSTR prevNodeName;
	n->get_nodeName(&prevNodeName);

// TODO, improve here
	if (FALSE)
	{
		n->set_namespaceURI(namespaceURI);
		n->set_nodeName(name);
	}
	else
	{
		CComPtr<ILDOMNode> parentNode;
		n->get_parentNode(&parentNode);

		CComPtr<ILDOMNode> nextSibling;
		n->get_nextSibling(&nextSibling);

		CComPtr<ILDOMElement> newElement;
		createElementNS(namespaceURI, name, &newElement);
		if (newElement)
		{
			parentNode->removeChild(n, NULL);

			CComPtr<ILDOMNamedNodeMap> attributes;
			n->get_attributes(&attributes);

			CComPtr<ILDOMNamedNodeMap> newAttributes;
			newElement->get_attributes(&newAttributes);

			long nattributes;
			attributes->get_length(&nattributes);
			for (int i = 0; i < nattributes; i++)
			{
				CComPtr<ILDOMNode> attr;
				attributes->item(i, &attr);

				newAttributes->setNamedItemNS(attr, NULL);
			}

			parentNode->insertBefore(newElement, nextSibling, NULL);

			*pVal = newElement;
			(*pVal)->AddRef();
		}
	}

////////////////////////////////
// create an event notification
#if 0
	CComQIPtr<ILDOMDocumentEvent> ownerDocumentEvent = this;//ownerDocument;
	ASSERT(ownerDocumentEvent != NULL);

	CComQIPtr<ILDOMMutationNameEvent> event;
	ownerDocumentEvent->createEvent(OLESTR("MutationNameEvent"), (ILDOMEvent**)&event);

	CComQIPtr<ILDOMEventTarget> eventTarget = n;

//
	event->initMutationNameEventNS(NULL, OLESTR("DOMElementNameChanged"), VARIANT_TRUE, VARIANT_FALSE, NULL, prevNamespaceURI, prevNodeName);
	bool doDefault;
	eventTarget->dispatchEvent(event, &doDefault);

//
	*pVal = n;
	(*pVal)->AddRef();
#endif

	return S_OK;
#endif
}

DocumentType* Document::createDocumentType(StringIn qualifiedName, StringIn publicId, StringIn systemId)
{
	DocumentType* pDocType = new DocumentType;

	pDocType->m_ownerDocument = this;
	pDocType->m_name = qualifiedName;
	pDocType->m_publicId = publicId;
	pDocType->m_systemId = systemId;

	return pDocType;
}

String Document::get_url() const
{
	return m_uri;
}

void Document::set_url(StringIn newVal)
{
	m_uri = newVal;
}

String Document::get_documentURI() const
{
	return m_uri;
}

void Document::set_documentURI(StringIn newVal)
{
// TODO
	m_uri = newVal;
}

Style::ICSSStyleDeclaration* Document::getOverrideStyle(Element* elt, StringIn pseudoElt)
{
	if (elt == NULL) throw new Exception(WSTR("null pointer"));

	// TODO pseudoElt

	ASSERT(0);
	return NULL;
	//return elt->m_overrideStyle;

#if 0
	CComQIPtr<ILSMILAnimationTarget> animtarget = elt;
	if (animtarget)
	{
		*pVal = static_cast<CAnimationTarget*>(animtarget.p)->m_overrideStyle;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return NULL;
#endif
}

Attr* Document::createAttribute(StringIn name)
{
	return createAttributeNS(nullptr, name);
}

Attr* Document::createAttributeNS(StringIn namespaceURI, StringIn qualifiedName)
{
	if (namespaceURI != nullptr)
	{
		if (!IsAttrNameValid(qualifiedName))
		{
	#if 0//_WINDOWS
			CComPtr<ICreateErrorInfo> cerrinfo;
			CreateErrorInfo(&cerrinfo);
			if (cerrinfo)
			{
				cerrinfo->SetGUID(IID_ILDOMDocument);
				cerrinfo->SetDescription(OLESTR("Invalid attribute name"));

				CComQIPtr<IErrorInfo> errinfo = cerrinfo;
				SetErrorInfo(0, errinfo);
			}
	#endif

			throw new Exception(WSTR("Attribute name invalid"));
			return NULL;
		}
	}

	Attr* attr = new Attr;
	attr->m_ownerDocument = this;

// TODO: Is this correct??

//	attr->set_nodeName(qualifiedName);

	if (qualifiedName != L"xmlns")
	{
		attr->set_nodeName(qualifiedName);
	}
	else	// Default namespace
	{
		attr->m_prefix = qualifiedName;	// ???
	//	attr->m_localName = qualifiedName;
		attr->m_nodeName = qualifiedName;	// ??
	}

	attr->set_namespaceURI(namespaceURI);

	return attr;
}

ProcessingInstruction* Document::createProcessingInstruction(StringIn target, StringIn data)
{
	if (target.GetLength() == 0) THROW(-1);

#if 0	// TODO
	if (target == OLESTR("xml-stylesheet"))
	{
		ProcessingInstructionStylesheet* pi = new
		CComObject<CLDOMProcessingInstructionStylesheet>::CreateInstance(&pi);
		if (pi)
		{
			pi->AddRef();

			pi->m_target = target;
			pi->set_data(data);

			pi->m_ownerDocument = static_cast<T*>(this);

			*pVal = pi;
		}
		else
			*pVal = NULL;
	}
	else
#endif
	{
		ProcessingInstruction* pi = new ProcessingInstruction(target);
		pi->set_data(data);
		pi->m_ownerDocument = this;
		return pi;
	}
}

DocumentFragment* Document::parseFragment(StringIn xml, Node* nsResolverParent)
{
	DocumentFragment* pFragment = new DocumentFragment;
	if (pFragment)
	{
		pFragment->m_ownerDocument = (this);

		ASSERT(0);
#if 0
		XMLParser parser;
		parser.m_uri = m_uri;
		parser.m_document = (this);
		parser.m_errorHandler = m_errorHandler;

		parser.m_fpos = 0;
		ASSERT(0);
#if 0
		parser.m_stream = new MemoryByteStream(xml.c_str(), xml.length());
#endif
	//	parser.m_textData = xml.c_str();
	//	parser.m_textLen = xml.length();

		try
		{
			bool ret = parser.ParseChildren(pFragment, nsResolverParent, false/*xmlSpacePreserve*/);

			return pFragment;
		}
		catch (Exception* e)
		{
			delete pFragment;
			throw e;
		}
#endif
	}

	raise(Exception(L"NULL"));
	return NULL;
}

Element* Document::createElementNS(StringIn namespaceURI, StringIn qualifiedName)
{
// Extract localName from qualifiedName
	String localName;
	{
		size_t ncolon = qualifiedName.find(':');
		if (ncolon != String::npos)
			localName = qualifiedName.RightOf(ncolon+1);
		else
			localName = qualifiedName;
	}

	Element* element = NULL;

	for (size_t i = 0; i < m_implementation->m_implList.GetSize(); ++i)
	{
		element = m_implementation->m_implList[i]->CreateElement(namespaceURI, localName, qualifiedName, NULL);
		if (element)
			break;
	}

	if (element == NULL)
	{
	// Generic DOM Element
		element = new GenericElement(namespaceURI, qualifiedName, localName);
	}

	if (element)
	{
		element->set_ownerDocument(this);
		element->set_namespaceURI(namespaceURI);
		element->set_nodeName(qualifiedName);
	}

	return element;

#if 0
	CComPtr<ILDOMElement> newElement;

	CLDOMDocumentImplImpl::createElementNS(namespaceURI, qualifiedName, &newElement);

	CComQIPtr<ILDOMDocument, &IID_ILDOMDocument> ownerDocument = static_cast<T*>(this);
	ASSERT(ownerDocument != NULL);
	CComQIPtr<CLDOMNodeImplImpl, &IID_IUnknown/*TODO*/>(newElement)->m_ownerDocument = ownerDocument;

	*ppElement = newElement.Detach();
#endif
	return NULL;
}

Element* Document::createElementNS(StringIn namespaceURI, StringIn qualifiedName, NamedNodeMap* attributes)
{
// Extract localName from qualifiedName
	String localName;
	{
		size_t ncolon = qualifiedName.find(':');
		if (ncolon != String::npos)
			localName = qualifiedName.RightOf(ncolon+1);
		else
			localName = qualifiedName;
	}

	Element* element = NULL;

	for (size_t i = 0; i < m_implementation->m_implList.GetSize(); ++i)
	{
		element = m_implementation->m_implList[i]->CreateElement(namespaceURI, localName, qualifiedName, attributes);
		if (element)
			break;
	}

	if (element == NULL)
	{
	// Generic DOM Element
		element = new GenericElement(namespaceURI, localName, qualifiedName, attributes);
	}

	if (element)
	{
		element->set_ownerDocument(this);
		element->set_namespaceURI(namespaceURI);
		element->set_nodeName(qualifiedName);
	}

	return element;
}

bool Document::load(IO::Stream* stream)
{
//	m_uri = xmlSource;

	XMLParser parser;
	parser.m_document = this;
	parser.m_errorHandler = m_errorHandler;
	return parser.load(stream);
/*
	if (m_documentElement)
	{
		BuildAnimationListForAllElements(m_documentElement, m_documentElement);
	}
*/
}

bool Document::load(StringIn xmlSource)
{
	m_uri = xmlSource;

	XMLParser parser;
	parser.m_document = this;
	parser.m_errorHandler = m_errorHandler;
	return parser.load(xmlSource);
/*
	if (m_documentElement)
	{
		BuildAnimationListForAllElements(m_documentElement, m_documentElement);
	}
*/
}

bool Document::loadXML(StringIn sourceText)
{
	XMLParser parser;
	// No uri: parser.m_uri
	parser.m_document = this;
	parser.m_errorHandler = m_errorHandler;
	return parser.loadXML(sourceText);
/*
	if (m_documentElement)
	{
		BuildAnimationListForAllElements(m_documentElement, m_documentElement);
	}
*/
}

Element* Document::getElementById(StringIn elementId)
{
	if (m_documentElement != NULL)
	{
		return Web::getElementById(m_documentElement, elementId);
	}
	else
		return NULL;
}

void Document::adoptNode2(Node* sourceNode)
{
	sourceNode->m_ownerDocument = this;

	NamedNodeMap* attributes = sourceNode->get_attributes();
	if (attributes)
	{
		long length = attributes->get_length();

		for (int i = 0; i < length; i++)
		{
			Node* attr = attributes->item(i);
			adoptNode(attr);
		}
	}

	NodeList* childNodes = sourceNode->get_childNodes();
	if (childNodes)
	{
		long length = childNodes->get_length();

		for (int i = 0; i < length; i++)
		{
			Node* node = childNodes->item(i);
			adoptNode(node);
		}
	}
}

Node* Document::insertNode(Node* newChild, Node* before)
{
	Element* element;
	DocumentType* doctype;

	if (element = dynamic_cast<Element*>(newChild))
	{
		if (m_documentElement != NULL) THROW(-1);
		m_documentElement = element;
	}
	else if (doctype = dynamic_cast<DocumentType*>(newChild))
	{
		if (m_doctype != NULL) THROW(-1);
		m_doctype = doctype;
	}

	return Node::insertNode(newChild, before);
}

Text* Document::createTextNode(StringIn data)
{
	Text* text = new Text;
	text->m_data = data;
	text->m_ownerDocument = this;
	return text;
}

CDATASection* Document::createCDATASection(StringIn data)
{
	CDATASection* cdata = new CDATASection;
	cdata->m_data = data;
	cdata->m_ownerDocument = this;
	return cdata;
}

Comment* Document::createComment(StringIn data)
{
	Comment* comment = new Comment;
	comment->m_data = data;
	comment->m_ownerDocument = this;
	return comment;
}

}	// Web
}

//#include "LHTMLWindow.h"
#if 0
#include "LBoxWindow.h"
#endif

#include "LXMLDocumentView.h"

#include "ScriptSite.h"

#include "Element.h"

#include "AnimationTarget.h"

#include "DTDDocument.h"
#include "ASDTDElement.h"
//#include "DTDContentModel.h"

#if 0
#include "LSMILElement.h"
#include "LSMILRootLayoutElement.h"
#include "LSMILRegionElement.h"
#include "LSMILSeqElement.h"
#include "LSMILParElement.h"
#include "LSMILSwitchElement.h"
#include "LSMILMediaElement.h"
#include "LSMILBrushElement.h"
#include "LSMILAnimateElement.h"
#include "LSMILAnimateColorElement.h"
#include "LSMILAnimateMotionElement.h"
#include "LSMILTransitionElement.h"
#include "LSMILTransitionFilterElement.h"
//#include "LSMILSetElement.h"
#endif

namespace System
{
namespace Web
{

// hm.. global function
WEBEXT bool DoAnimationsForAllElements(Element* element, /*double oldTime,*/ double currentTime)
{
	bool bAny = false;

	AnimationTarget* targetElement = dynamic_cast<AnimationTarget*>(element);
	if (targetElement)
	{
		bAny = targetElement->DoAnimation();
	}

	ASSERT(0);
#if 0
	CComPtr<ILDOMNode> child;
	element->get_firstChild(&child);
	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);

		if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement, &IID_ILDOMElement> childelement = (IUnknown*)child;
			bool b = DoAnimationsForAllElements(childelement, /*oldTime,*/ currentTime);	// Recurse
			if (b)
				bAny = true;
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
#endif

	return bAny;
}

bool WEBEXT IsAttrNameValid(StringIn name)
{
	if (name.GetLength() == 0) return false;

	// TODO
	//ASSERT(0);
#if 0

	const WCHAR* p = name->c_str();

	if (!std::isalpha(p[0]) && p[0] != L'_') return false;

	p++;
	while (*p)
	{
		if (!std::isalnum(*p) && *p != '_' && *p != L'-' && *p != L':' && *p != L'.')
			return false;

		p++;
	}
#endif
	return true;
}

NodeList* Document::getElementsByTagNameNS(StringIn namespaceURI, StringIn localName) const
{
	ASSERT(localName != nullptr);
	if (localName == nullptr) throw new Exception(L"localName is null");

	NodeList* pNodeList = new NodeList;

	if (m_documentElement)
		ASSERT(0);//LXML::GetElementsByTagNameNSElement(m_documentElement, namespaceURI, localName, pNodeList);

	return pNodeList;
}

EntityReference* Document::createEntityReference(StringIn name)
{
	EntityReference* pNode = new EntityReference;

	pNode->m_ownerDocument = (this);

	DocumentType* doctype = get_doctype();

	if (doctype)
	{
		NamedNodeMap* entities = doctype->get_entities();

		Entity* entity = dynamic_cast<Entity*>(entities->getNamedItem(name));

		if (entity)
		{
			pNode->m_entity = entity;

			Node* node = entity->get_firstChild();

			while (node)
			{
				Node* clone = node->cloneNode(true);
				if (clone)
				{
					pNode->appendChild(clone);
				}

				node = node->get_nextSibling();
			}
		}
	}

	return pNode;
}

/////////////////////////////////////////////////////////////////////////////
// CLDOMDocumentImplImpl
#if 0

CLDOMDocumentImplImpl::CLDOMDocumentImplImpl()
{
#if 0
	m_acDocument = NULL;
#endif
	m_pScriptSite = NULL;
}

CLDOMDocumentImplImpl::~CLDOMDocumentImplImpl()
{
	ASSERT(m_pViews.GetSize() == 0);
}

#if 0
#include "LSVGExtensionDefsElement.h"
#endif

#include "LSVGShadowableImpl.h"

/*
ErrorCode CLDOMElementImplImpl::BindElement(ILDOMNodeList* extensionDefsElements)
{
	CComBSTR namespaceURI;
	get_namespaceURI(&namespaceURI);
}
*/

ErrorCode STDMETHODCALLTYPE CLDOMDocumentImplImpl::CreateMoniker( 
   /* [in] */ LPOLESTR szName,
   /* [in] */ IBindCtx *pBC,
   /* [out] */ IMoniker **ppmk,
   /* [in] */ DWORD dwReserved)
{
#if _WINDOWS
	return CreateURLMoniker(NULL/*TODO*/, szName, ppmk);
#else
	return E_FAIL;
#endif
}

ErrorCode BindExtension(ILDOMElement* componentElement, CLSVGShadowableImpl* shadowable);

ErrorCode CLDOMDocumentImplImpl::BindElements(ILDOMNodeList* extensionDefsElements, ILDOMElement* element)
{
	CComQIPtr<CLSVGShadowableImpl> shadowableImpl = element;

#if 0

	if (shadowableImpl)
	{
		CComBSTR namespaceURI;
		element->get_namespaceURI(&namespaceURI);

		CComBSTR name;
		element->get_localName(&name);
		if (name.Length() == 0)
		{
			name.Empty();
			element->get_tagName(&name);
		}

		long length;
		extensionDefsElements->get_length(&length);

		for (int i = 0; i < length; i++)
		{
			CComPtr<ILDOMNode> node;
			extensionDefsElements->item(i, &node);
			CComQIPtr<ILSVGExtensionDefsElement> extensionDefsElement = node;
			ASSERT(extensionDefsElement);

			CComPtr<ILSVGElementDefElement> elementDef;
			static_cast<CLSVGExtensionDefsElement*>(extensionDefsElement.p)->GetElementDef(namespaceURI, name, &elementDef);
			if (elementDef)
			{
				shadowableImpl->m_elementDef = elementDef;
				BindExtension(elementDef, shadowableImpl);
			}
		}
	}

// Recurse for children
	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			BindElements(extensionDefsElements, element);
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
#endif

	return S_OK;
}

int CLDOMDocumentImplImpl::ConstructScriptEngine()
{
	ErrorCode hr;

#if _WINDOWS
	hr = CComObject<CScriptSite>::CreateInstance(&m_pScriptSite);
	if (FAILED(hr)) return hr;
	m_pScriptSite->AddRef();
	m_pScriptSite->m_pDocument = this;
#endif

	return 0;
}

void CLDOMDocumentImplImpl::ReleaseScriptEngine()
{
#if _WINDOWS
	if (m_pScriptSite)
	{
		m_pScriptSite->Release();
		m_pScriptSite = NULL;
	}
#endif
}

ErrorCode CLDOMDocumentImplImpl::InitScripting()
{
#if _WINDOWS
	if (FALSE)	// Script debugging
	{
		m_pScriptSite->m_debugManager.CoCreateInstance(CLSID_ProcessDebugManager);

		m_pScriptSite->m_debugManager->GetDefaultApplication(&m_pScriptSite->m_debugApp);

		m_pScriptSite->m_debugApp->SetName(L"LXViewer");

		m_pScriptSite->m_debugManager->CreateDebugDocumentHelper(NULL/*punkOuter*/, &m_pScriptSite->m_debugDocumentHelper);

		m_pScriptSite->m_debugDocumentHelper->Init(m_pScriptSite->m_debugApp, m_uri/*m_friendlyName*/, m_uri/*m_friendlyName*/, 0/*TEXT_DOC_ATTR_READONLY*/);
		m_pScriptSite->m_debugDocumentHelper->Attach(NULL);
	}

	{
		CLSID clsid;
//		ErrorCode hr = CLSIDFromProgID(L"VBScript", &clsid);
		ErrorCode hr = CLSIDFromProgID(L"JScript", &clsid);
		ASSERT(SUCCEEDED(hr));

		m_pScriptSite->m_activeScript.CoCreateInstance(clsid);
		ASSERT(m_pScriptSite->m_activeScript != NULL);
	}

	{
		CComQIPtr<IActiveScriptParse> activeScriptParse = m_pScriptSite->m_activeScript;
		ErrorCode hr;
		
		hr = activeScriptParse->InitNew();
		ASSERT(hr == 0);

	//	CComQIPtr<IActiveScriptSite> site;
	//	m_scriptSite->QueryInterface(IID_IActiveScriptSite, (void**)&site);
		hr = m_pScriptSite->m_activeScript->SetScriptSite(m_pScriptSite);
		ASSERT(hr == 0);

		CComQIPtr<IDispatch> scriptdisp;
		hr = m_pScriptSite->m_activeScript->GetScriptDispatch(NULL, &scriptdisp);
		ASSERT(SUCCEEDED(hr));

		m_pScriptSite->m_pScriptDisp = scriptdisp;
		//scriptdisp->QueryInterface(IID_IDispatchEx, (void**)&m_pScriptDisp);
		ASSERT(m_pScriptSite->m_pScriptDisp != NULL);
	}
#endif

	return S_OK;
}

void CLDOMDocumentImplImpl::SetValuesOnAllAnimations(ILDOMElement* element)
{
#if 0
#if 0
	CComQIPtr<ILSMILAnimationTarget> targetElement = element;
	if (targetElement)
	{
		static_cast<CAnimationTarget*>(targetElement.p)->m_animationList.RemoveAll();
		BuildElementAnimationList(element, svgElement);
	}
#endif

	CComQIPtr<ILAnimationElement, &IID_ILAnimationElement> animation = element;
	if (animation)
	{
		CComQIPtr<CLAnimationElementImplImpl, &IID_IUnknown/*TODO*/> pAnimation(animation);

		/*
		CComQIPtr<ILDOMElement> target;
		pAnimation->get_targetElement(&target);
		*/

		/*
		if (target == targetElement2)
		*/
		{
			/*
			CComObject<CLCSSStyleDeclaration>* overrideStyle = static_cast<CAnimationTarget*>(targetElement.p)->m_overrideStyle;
			overrideStyle->Clear();
			*/

			pAnimation->SetValuesFromAttributes();
		}
	}

	CComPtr<ILDOMNode> child;
	element->get_firstChild(&child);
	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);

		if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> childelement = child;
			SetValuesOnAllAnimations(childelement);	// Recurse
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}
#endif
}

#if 0	// Had this ??
ErrorCode CLDOMDocumentImplImpl::get_window(ILHTMLWindow* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	if (m_pViews.GetSize() > 0)
	{
		ASSERT(0);
#if 0
		*pVal = m_pViews[0];
		(*pVal)->AddRef();
#endif
	}

	return S_OK;
}
#endif

void CLDOMDocumentImplImpl::AddView(CXMLDocumentView* pView)
{
#ifdef _DEBUG
	for (int i = 0; i < m_pViews.GetSize(); i++)
	{
		if (m_pViews[i] == pView)
		{
			ASSERT(0);
		}
	}
#endif

	m_pViews.Add(pView);
}

void CLDOMDocumentImplImpl::RemoveView(CXMLDocumentView* pView)
{
	for (int i = 0; i < m_pViews.GetSize(); i++)
	{
		if (m_pViews[i] == pView)
		{
			m_pViews.RemoveAt(i);
			return;
		}
	}

	ASSERT(0);
}

ErrorCode CLDOMDocumentImplImpl::createElementNS(BSTR namespaceURI, BSTR qualifiedName, ILDOMElement **ppElement)
{
	CComPtr<ILDOMElement> newElement;

// Extract localName from qualifiedName
	OLECHAR* localName;
	{
		OLECHAR* colon;
		if (colon = wcschr(qualifiedName, L':'))
			localName = colon+1;
		else
			localName = qualifiedName;
	}

#if 0
// (X)HTML
	if (!cmpbstr(namespaceURI, L"http://www.w3.org/1999/xhtml"))
	{
		createHTMLElement(localName, &newElement);
	}
// SMIL
	else if (!cmpbstr(namespaceURI, L"http://www.w3.org/2001/SMIL20/Language") ||
			!cmpbstr(namespaceURI, L"http://www.w3.org/2000/SMIL20/CR/Language"))
	{
		if (!tcscmp(localName, L"root-layout"))
		{
			CComObject<CLSMILRootLayoutElement>* pElement;
			CComObject<CLSMILRootLayoutElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
		else if (!tcscmp(localName, L"region"))
		{
			CComObject<CLSMILRegionElement>* pElement;
			CComObject<CLSMILRegionElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
	//
		else if (
			!tcscmp(localName, L"ref") ||
			!tcscmp(localName, L"video") ||
			!tcscmp(localName, L"audio") ||
			!tcscmp(localName, L"animation") ||
			!tcscmp(localName, L"img"))
		{
			CComObject<CLSMILMediaElement>* pElement;
			CComObject<CLSMILMediaElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
		else if (!tcscmp(localName, L"brush"))
		{
			CComObject<CLSMILBrushElement>* pElement;
			CComObject<CLSMILBrushElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
		else if (!tcscmp(localName, L"seq") ||
					!tcscmp(localName, L"body"))
		{
			CComObject<CLSMILSeqElement>* pElement;
			CComObject<CLSMILSeqElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
		else if (!tcscmp(localName, L"par"))
		{
			CComObject<CLSMILParElement>* pElement;
			CComObject<CLSMILParElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
		else if (!tcscmp(localName, L"switch"))
		{
			CComObject<CLSMILSwitchElement>* pElement;
			CComObject<CLSMILSwitchElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
	//
		else if (!tcscmp(localName, L"animate"))
		{
			CComObject<CLSMILAnimateElement>* pElement;
			CComObject<CLSMILAnimateElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
		else if (!tcscmp(localName, L"animateColor"))
		{
			CComObject<CLSMILAnimateColorElement>* pElement;
			CComObject<CLSMILAnimateColorElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
		else if (!tcscmp(localName, L"animateMotion"))
		{
			CComObject<CLSMILAnimateMotionElement>* pElement;
			CComObject<CLSMILAnimateMotionElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
		else if (!tcscmp(localName, L"transitionFilter"))
		{
			CComObject<CLSMILTransitionFilterElement>* pElement;
			CComObject<CLSMILTransitionFilterElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
		else if (!tcscmp(localName, L"transition"))
		{
			CComObject<CLSMILTransitionElement>* pElement;
			CComObject<CLSMILTransitionElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
		else if (!tcscmp(localName, L"set"))
		{
			/*
			CComObject<CLSMILSetElement>* pElement;
			CComObject<CLSMILSetElement>::CreateInstance(&pElement);
			if (pElement)
			{
				pElement->AddRef();
				newElement = pElement;
			}
			*/
		}
		else
		{
			CComObject<CLSMILElement>* pElement;
			CComObject<CLSMILElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
	}
#if 0
// XML Schema
	else if (!tcscmp(namespaceURI, L"http://www.w3.org/2001/XMLSchema"))
	{
		newElement.CoCreateInstance(CLSID_DOMElement);
	}
// No Namespace
#endif
	else
#endif
	{
		for (int i = 0; i < m_implementation->m_implList.GetSize(); i++)
		{
			m_implementation->m_implList[i]->CreateElement(namespaceURI, localName, &newElement);
			if (newElement)
				break;
		}

	// Generic DOM Element
		if (newElement == NULL)
		{
			CComObject<CLDOMElement>* pElement;
			CComObject<CLDOMElement>::CreateInstance(&pElement);
			if (pElement)
			{
				newElement = pElement;
			}
		}
	}

	if (newElement)
	{
		CComQIPtr<CLDOMElementImplImpl>((IUnknown*)newElement)->set_nodeName(qualifiedName);
		CComQIPtr<CLDOMElementImplImpl>((IUnknown*)newElement)->set_namespaceURI(namespaceURI);
	}

	*ppElement = newElement;
	if (*ppElement) (*ppElement)->AddRef();

	return S_OK;
}
#endif

/*
template<class T> class FileBuffer : public BufferT<T>
{
public:
	CTOR FileBuffer(std::FILE* fp)
	{
		m_fp = fp;
	}

	std::FILE* m_fp;

	virtual void Write(const T* buf, int len)
	{
		std::fwrite(buf, len*sizeof(T), 1, m_fp);
	}
};
*/

bool Document::save(StringIn url)
{
	IO::FileStream fp(url, IO::FileMode_Create, IO::FileAccess_Write);
	if (!fp.IsHandleValid())
	{
		Std::Out << quote(url) << IO::FileStream::GetLastError();
		return false;
	}

//	if (fp)
	{
	//	FileBuffer<char> buffer(fp);
	//	StringBuilder<char> xml(&buffer);

		IO::StreamWriter writer(&fp);

		saveXML2(this, writer);

		//fwrite(buffer.m_str, buffer.m_len, 1, fp);

	//	std::fclose(fp);

		return true;
	}

	return false;
}

IO::TextWriter& WriteToStream(IO::TextWriter& xml, Node* node);

IO::TextWriter& WriteToStream(IO::TextWriter& stream, Attr* pAttr)
{
	stream << pAttr->get_name();
	stream << "=\"";
	stream << pAttr->get_value();
	stream << "\"";

	return stream;
}

IO::TextWriter& WriteToStream(IO::TextWriter& stream, Element* element)
{
	stream << "<";

	String tagName = element->get_tagName();
	stream << tagName;

// Attributes
	NamedNodeMap* attributes = element->get_attributes();
	uint length = attributes->get_length();

//#define foreach(i, l)	for (Attr* i = l
//	foreach(attr, attributes)

	for (uint i = 0; i < length; i++)
	{
		Attr* attr = (Attr*)attributes->item(i);

		stream << " ";
		stream << attr;
	}

	if (!element->hasChildNodes())
	{
		stream << " />";
	}
	else
	{
		stream << ">";

	// Children
		Node* child = element->get_firstChild();

		while (child != NULL)
		{
			stream << child;

			child = child->get_nextSibling();
		}

		stream << "</";
		stream << tagName;
		stream << ">";
	}

	return stream;
}

IO::TextWriter& WriteToStream(IO::TextWriter& xml, Node* node)
{
	NodeType nodeType = node->get_nodeType();

	if (nodeType == NODE_DOCUMENT)
	{
		Document* document = static_cast<Document*>(node);

		if (true)	// bHadXML
		{
			xml << "<?xml";

			if (true)
			{
				xml << " version=\"";
				//xml += m_version;
				xml << "1.0";
				xml << "\"";
			}

			if (true)
			{
				xml << " standalone=";
				xml << "\"";

				if (document->get_xmlStandalone())
					xml << "yes";
				else
					xml << "no";

				xml << "\"";
			}

			xml << "?>\n";
		}

		// Children
		Node* child = node->get_firstChild();

		while (child != NULL)
		{
			xml << child;

			child = child->get_nextSibling();
		}
	}
	else if (nodeType == NODE_DOCUMENT_TYPE)
	{
		/*
		CComQIPtr<ILDOMDocumentType, &IID_ILDOMDocumentType> doctype((IUnknown*)node);

		BSTR name; doctype->get_name(&name);
		BSTR publicId; doctype->get_publicId(&publicId);
		BSTR systemId; doctype->get_systemId(&systemId);

		xml += OLESTR("<!DOCTYPE ");
		xml += name;
		xml += OLESTR(" ");

		if (SysStringLen(publicId) > 0)
		{
			xml += OLESTR("PUBLIC ");
			xml += publicId;
			xml += OLESTR("\"");

			if (SysStringLen(systemId) > 0)
			{
				xml += OLESTR(" \"");
				xml += systemId;
				xml += OLESTR("\"");
			}
		}
		else
		{
			xml += OLESTR("SYSTEM \"");
			xml += systemId;
			xml += OLESTR("\"");
		}

		xml += OLESTR(">\n");

		SysFreeString(systemId);
		SysFreeString(publicId);
		SysFreeString(name);
		*/
	}
	else if (nodeType == NODE_PROCESSING_INSTRUCTION)
	{
		/*
		CComQIPtr<ILDOMProcessingInstruction, &IID_ILDOMProcessingInstruction> pi((IUnknown*)node);

		CComBSTR target;
		pi->get_target(&target);

		CComBSTR data;
		pi->get_data(&data);

		xml += OLESTR("<?");
		xml += target;
		xml += OLESTR(" ");
		xml += data;
		xml += OLESTR("?>\n");
		*/
	}
	else if (nodeType == NODE_ELEMENT)
	{
		Element* element = (Element*)node;

		xml << element;
	}
	else if (nodeType == NODE_DOCUMENT_FRAGMENT)
	{
		DocumentFragment* fragment = static_cast<DocumentFragment*>(node);

	// Children
		Node* child = node->get_firstChild();

		while (child != NULL)
		{
			//_bstr_t xml2 = saveXML2(child);
			/*xml +=*/ xml << child;

			child = child->get_nextSibling();
		}
	}
	else if (nodeType == NODE_ATTRIBUTE)
	{
		Attr* pAttr = static_cast<Attr*>(node);

		xml << pAttr;
	}
	else if (nodeType == NODE_TEXT)
	{
		Text* pText = static_cast<Text*>(node);

		xml << pText->get_data();
	}
	else if (nodeType == NODE_COMMENT)
	{
		ASSERT(0);	// TODO stream << 

		Comment* pComment = static_cast<Comment*>(node);

		xml << "<!--";

		xml << pComment->get_data();

		xml << "-->";
	}
	else if (nodeType == NODE_CDATA_SECTION)
	{
		ASSERT(0);	// TODO stream << 

		CDATASection* pCDATA = static_cast<CDATASection*>(node);

		xml << "<![CDATA[\n";

		xml << pCDATA->get_data();

		xml << "\n]]>";
	}
	/*
	else if (nodeType == LNODE_NOT_WELLFORMED)
	{
		NotWellformed* pText = static_cast<NotWellformed*>(node);

		xml << *pText->get_data()->ToStringA();
	}
	*/
#if 0
// DTD
	else if (nodeType == DTD_ELEMENT)
	{
		CLDTDElement* p = static_cast<CLDTDElement*>(node);

		xml += p->m_pASElement->GetAsText();
	}
#endif
	else
		ASSERT(0);

	return xml;
}

void Document::saveXML2(Node* node, IO::TextWriter& xml)
{
	WriteToStream(xml, node);
}

#if 0
void CLDOMDocumentImplImpl::MakeFormattedString2(ILDOMNode *node, CWCharString& xml)
{
	LDOMNodeType nodeType;
	node->get_nodeType(&nodeType);

	if (nodeType == LNODE_DOCUMENT)
	{
		CComQIPtr<ILDOMDocument, &IID_ILDOMDocument> document((IUnknown*)node);

		document->setTextOffset(0, xml.length());
		document->setTextOffset(1, xml.length());
		document->setTextOffset(2, xml.length());
		document->setTextOffset(3, xml.length());

		if (TRUE)	// bHadXML
		{
			xml += OLESTR("<?xml ");

			if (TRUE)
			{
				xml += OLESTR("version=\"");
				//xml += m_version;
				xml += OLESTR("1.0");
				xml += OLESTR("\" ");
			}

			if (TRUE)
			{
				xml += OLESTR("standalone=");
				xml += OLESTR("\"");

				if (m_standalone)
					xml += OLESTR("yes");
				else
					xml += OLESTR("no");

				xml += OLESTR("\"");
				xml += OLESTR(" ");
			}

			xml += OLESTR("?>\n");
		}

		// Children
		CComPtr<ILDOMNode> child;
		node->get_firstChild(&child);

		while (child != NULL)
		{
			MakeFormattedString2(child, xml);

			CComPtr<ILDOMNode> nextchild;
			child->get_nextSibling(&nextchild);
			child = nextchild;
		}

		document->setTextOffset(4, xml.length());
		document->setTextOffset(5, xml.length());
		document->setTextOffset(6, xml.length());
		document->setTextOffset(7, xml.length());
		document->setTextOffset(8, xml.length());
		document->setTextOffset(9, xml.length());
	}
	else if (nodeType == LNODE_DOCUMENT_TYPE)
	{
		CComQIPtr<ILDOMDocumentType, &IID_ILDOMDocumentType> doctype((IUnknown*)node);

		BSTR name; doctype->get_name(&name);
		BSTR publicId; doctype->get_publicId(&publicId);
		BSTR systemId; doctype->get_systemId(&systemId);

		doctype->setTextOffset(0, xml.length());

		xml += OLESTR("<!DOCTYPE ");

		doctype->setTextOffset(1, xml.length()-1);
		doctype->setTextOffset(2, xml.length());

		xml += name;
		xml += OLESTR(" ");

		if (SysStringLen(publicId) > 0)
		{
			xml += OLESTR("PUBLIC \"");
			xml += publicId;
			xml += OLESTR("\"");

			if (SysStringLen(systemId) > 0)
			{
				xml += OLESTR(" \"");
				xml += systemId;
				xml += OLESTR("\"");
			}
		}
		else
		{
			xml += OLESTR("SYSTEM \"");
			xml += systemId;
			xml += OLESTR("\"");
		}

		CComBSTR internalSubset;
		doctype->get_internalSubset(&internalSubset);
		if (internalSubset.Length())
		{
			xml += OLESTR("[");
			doctype->setTextOffset(6, xml.length());

			xml += internalSubset;

			doctype->setTextOffset(7, xml.length());
			xml += OLESTR("]");
		}

		xml += OLESTR(">\n");

		doctype->setTextOffset(8, xml.length());
		doctype->setTextOffset(9, xml.length());

		SysFreeString(systemId);
		SysFreeString(publicId);
		SysFreeString(name);
	}
	else if (nodeType == LNODE_PROCESSING_INSTRUCTION)
	{
		CComQIPtr<ILDOMProcessingInstruction, &IID_ILDOMProcessingInstruction> pi((IUnknown*)node);

		CComBSTR target;
		pi->get_target(&target);

		CComBSTR data;
		pi->get_data(&data);

		pi->setTextOffset(0, xml.length());
		xml += OLESTR("<?");
		pi->setTextOffset(1, xml.length());
		xml += target;
		pi->setTextOffset(2, xml.length());

		xml += OLESTR(" ");
		pi->setTextOffset(3, xml.length());
		pi->setTextOffset(4, xml.length());

		xml += data;
		pi->setTextOffset(5, xml.length());
		pi->setTextOffset(6, xml.length());

		pi->setTextOffset(7, xml.length());
		xml += OLESTR("?>");
		pi->setTextOffset(8, xml.length());

		xml += OLESTR("\n");
		pi->setTextOffset(9, xml.length());
	}
	else if (nodeType == LNODE_ELEMENT)
	{
		CComQIPtr<ILDOMElement, &IID_ILDOMElement> element((IUnknown*)node);

		element->setTextOffset(0, xml.length());

		xml += OLESTR("<");

		element->setTextOffset(1, xml.length());

		CComBSTR tagName;
		element->get_tagName(&tagName);
		xml += tagName;

		element->setTextOffset(2, xml.length());

	// Attributes
		CComPtr<ILDOMNamedNodeMap> attributes;
		element->get_attributes(&attributes);
		long length;
		attributes->get_length(&length);

		for (long i = 0; i < length; i++)
		{
			CComPtr<ILDOMAttr> attr;
			attributes->item(i, (ILDOMNode**)&attr);

			attr->setTextOffset(0, xml.length());	// ??

			xml += OLESTR(" ");
			MakeFormattedString2(attr, xml);
		}

		element->setTextOffset(3, xml.length());

		bool bHasChildren;
		element->hasChildNodes(&bHasChildren);

		if (!bHasChildren)
		{
			element->setTextOffset(4, xml.length());

			xml += OLESTR("/>");

			element->setTextOffset(5, xml.length());
			element->setTextOffset(6, xml.length());
			element->setTextOffset(7, xml.length());
			element->setTextOffset(8, xml.length());
		}
		else
		{
			xml += OLESTR(">");

			element->setTextOffset(4, xml.length());

		// Children
			CComPtr<ILDOMNode> child;
			node->get_firstChild(&child);

			while (child != NULL)
			{
				MakeFormattedString2(child, xml);

				CComPtr<ILDOMNode> nextchild;
				child->get_nextSibling(&nextchild);
				child = nextchild;
			}

			element->setTextOffset(5, xml.length());

			xml += OLESTR("</");
			element->setTextOffset(6, xml.length());
			xml += tagName;
			element->setTextOffset(7, xml.length());
			xml += OLESTR(">");
		}

		element->setTextOffset(8, xml.length());
		xml += OLESTR("\n");
		element->setTextOffset(9, xml.length());
	}
	else if (nodeType == LNODE_DOCUMENT_FRAGMENT)
	{
		CComQIPtr<ILDOMDocumentFragment, &IID_ILDOMDocumentFragment> fragment((IUnknown*)node);

	// Children
		CComPtr<ILDOMNode> child;
		node->get_firstChild(&child);

		while (child != NULL)
		{
			MakeFormattedString2(child, xml);

			CComPtr<ILDOMNode> nextchild;
			child->get_nextSibling(&nextchild);
			child = nextchild;
		}
	}
	else if (nodeType == LNODE_ATTRIBUTE)
	{
		CLDOMAttr* pAttr = static_cast<CLDOMAttr*>(node);

		CComBSTR name;
		pAttr->get_name(&name);

		pAttr->setTextOffset(1, xml.length());
		xml += name;

		pAttr->setTextOffset(2, xml.length());
		xml += OLESTR("=\"");

		pAttr->setTextOffset(3, xml.length());

		CComBSTR value;
		pAttr->get_value(&value);	// TODO

		xml += value;

		pAttr->setTextOffset(4, xml.length());
		xml += OLESTR("\"");

		pAttr->setTextOffset(5, xml.length());
		pAttr->setTextOffset(6, xml.length());
		pAttr->setTextOffset(7, xml.length());
		pAttr->setTextOffset(8, xml.length());
		pAttr->setTextOffset(9, xml.length());
	}
	else if (nodeType == LNODE_TEXT)
	{
		CLDOMText* pText = static_cast<CLDOMText*>(node);

		pText->setTextOffset(0, xml.length());
		pText->setTextOffset(1, xml.length());
		pText->setTextOffset(2, xml.length());

		xml += (BSTR)(pText->m_data);

		pText->setTextOffset(3, xml.length());
		pText->setTextOffset(4, xml.length());
		pText->setTextOffset(5, xml.length());
		pText->setTextOffset(6, xml.length());
		pText->setTextOffset(7, xml.length());
		pText->setTextOffset(8, xml.length());
		pText->setTextOffset(9, xml.length());
	}
	else if (nodeType == LNODE_COMMENT)
	{
		CLDOMComment* pComment = static_cast<CLDOMComment*>(node);

		pComment->setTextOffset(0, xml.length());

		xml += OLESTR("<!--");

		pComment->setTextOffset(1, xml.length());
		pComment->setTextOffset(2, xml.length());

		xml += (BSTR)(pComment->m_data);

		pComment->setTextOffset(3, xml.length());
		pComment->setTextOffset(4, xml.length());

		xml += OLESTR("-->");

		pComment->setTextOffset(5, xml.length());
		pComment->setTextOffset(6, xml.length());
		pComment->setTextOffset(7, xml.length());
		pComment->setTextOffset(8, xml.length());
		pComment->setTextOffset(9, xml.length());
	}
	else if (nodeType == LNODE_CDATA_SECTION)
	{
		CLDOMCDATASection* pCDATA = static_cast<CLDOMCDATASection*>(node);

		pCDATA->setTextOffset(0, xml.length());
		pCDATA->setTextOffset(1, xml.length());
		pCDATA->setTextOffset(2, xml.length());

		xml += OLESTR("<![CDATA[\n");

		pCDATA->setTextOffset(3, xml.length());
		pCDATA->setTextOffset(4, xml.length());

		xml += (BSTR)(pCDATA->m_data);

		pCDATA->setTextOffset(5, xml.length());
		pCDATA->setTextOffset(6, xml.length());

		xml += OLESTR("\n]]>");

		pCDATA->setTextOffset(7, xml.length());
		pCDATA->setTextOffset(8, xml.length());
		pCDATA->setTextOffset(9, xml.length());
	}
	else if (nodeType == LNODE_NOT_WELLFORMED)
	{
		CLDOMNotWellformed* pText = static_cast<CLDOMNotWellformed*>(node);

		pText->setTextOffset(0, xml.length());
		pText->setTextOffset(1, xml.length());
		pText->setTextOffset(2, xml.length());

		xml += (BSTR)(pText->m_data);

		pText->setTextOffset(3, xml.length());
		pText->setTextOffset(4, xml.length());
		pText->setTextOffset(5, xml.length());
		pText->setTextOffset(6, xml.length());
		pText->setTextOffset(7, xml.length());
		pText->setTextOffset(8, xml.length());
		pText->setTextOffset(9, xml.length());
	}
// DTD
	else if (nodeType == DTD_ELEMENT)
	{
		CLDTDElement* p = static_cast<CLDTDElement*>(node);

		p->setTextOffset(0, xml.length());
		p->setTextOffset(1, xml.length());
		p->setTextOffset(2, xml.length());

		xml += p->m_pASElement->GetAsText();

		p->setTextOffset(3, xml.length());
		p->setTextOffset(4, xml.length());
		p->setTextOffset(5, xml.length());
		p->setTextOffset(6, xml.length());
		p->setTextOffset(7, xml.length());
		p->setTextOffset(8, xml.length());
		p->setTextOffset(9, xml.length());
	}
	else
		ASSERT(0);
}
#endif

Element* getElementById(Element* element, StringIn elementId);

Element* getElementByIdChildren(Element* element, StringIn elementId)
{
	Node* node = element->get_firstChild();
	while (node)
	{
		Element* element = dynamic_cast<Element*>(node);
		if (element)
		{
			Element* p = getElementById(element, elementId);
			if (p)
				return p;
		}

		node = node->get_nextSibling();
	}

	return NULL;
}

Element* getElementById(Element* element, StringIn elementId)
{
	String id = element->getAttribute(WSTR("id"));
	if (id == elementId)
	{
		return element;
	}

	return getElementByIdChildren(element, elementId);
}

/*
Element* Document::getElementById(Element* element, const sysstring& elementId)
{
	sysstring id = element->getAttribute(OLESTR("id"));
	if (id.length() && !tcscmp(id.c_str(), elementId.c_str()))
	{
		return element;
	}

	Node* node = element->get_firstChild();
	while (node)
	{
		Element* element = dynamic_cast<Element*>(node);
		if (element)
		{
			Element* p = getElementById(element, elementId);
			if (p)
				return p;
		}

		node = node->get_nextSibling();
	}

	return NULL;
}
*/

#if 0

ErrorCode CLDOMDocumentImplImpl::renameNode(ILDOMDocument* thisNode, /*[in]*/ ILDOMNode* n, /*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[out,retval]*/ ILDOMNode* *pVal)
{
	ASSERT(n != NULL);
	ASSERT(pVal != NULL);
	if (n == NULL) return E_INVALIDARG;
	if (pVal == NULL) return E_POINTER;

	CComBSTR prevNamespaceURI;
	n->get_namespaceURI(&prevNamespaceURI);

	CComBSTR prevNodeName;
	n->get_nodeName(&prevNodeName);

// TODO, improve here
	if (FALSE)
	{
		CComQIPtr<CLDOMElementImplImpl>((IUnknown*)n)->put_namespaceURI(namespaceURI);
		CComQIPtr<CLDOMElementImplImpl>((IUnknown*)n)->put_nodeName(name);
	}
	else
	{
		CComPtr<ILDOMNode> parentNode;
		n->get_parentNode(&parentNode);

		CComPtr<ILDOMNode> nextSibling;
		n->get_nextSibling(&nextSibling);

		CComPtr<ILDOMElement> newElement;
		thisNode->createElementNS(namespaceURI, name, &newElement);
		if (newElement)
		{
			parentNode->removeChild(n, NULL);

			CComPtr<ILDOMNamedNodeMap> attributes;
			n->get_attributes(&attributes);

			CComPtr<ILDOMNamedNodeMap> newAttributes;
			newElement->get_attributes(&newAttributes);

			long nattributes;
			attributes->get_length(&nattributes);
			for (int i = 0; i < nattributes; i++)
			{
				CComPtr<ILDOMNode> attr;
				attributes->item(i, &attr);

				CComPtr<ILDOMNode> p;
				newAttributes->setNamedItemNS(attr, &p);
			}

			parentNode->insertBefore(newElement, CComVariant(nextSibling), NULL);

			*pVal = newElement;
			(*pVal)->AddRef();
		}
	}

////////////////////////////////
// create an event notification
#if 0
	CComQIPtr<ILDOMDocumentEvent> ownerDocumentEvent = this;//ownerDocument;
	ASSERT(ownerDocumentEvent != NULL);

	CComQIPtr<ILDOMMutationNameEvent> event;
	ownerDocumentEvent->createEvent(L"MutationNameEvent", (ILDOMEvent**)&event);

	CComQIPtr<ILDOMEventTarget> eventTarget = n;

//
	event->initMutationNameEventNS(NULL, L"DOMElementNameChanged", true, false, NULL, prevNamespaceURI, prevNodeName);
	bool doDefault;
	eventTarget->dispatchEvent(event, &doDefault);

//
	*pVal = n;
	(*pVal)->AddRef();
#endif

	return S_OK;
}

// Scripting

ErrorCode CLDOMDocumentImplImpl::AddEventListener(ILDOMElement* element)
{
	/*
The required event attribute specifies the event type for which the listener is being registered. As specified by [DOM2EVENTS], the value of the attribute should be an XML Name [XML]. 
*/

	CComBSTR event;
	element->getAttributeNS(OLESTR("http://www.w3.org/2001/xml-events"), OLESTR("event"), &event);
	if (event.Length() == 0)
	{
		return S_FALSE;	// This is required
	}

/*
The optional handler attribute specifies the URI-reference of an element
that defines the action that should be performed if the event reaches the
observer. (This specification does not mandate what form that element
should take: see further the section "Event Handlers"). If this attribute
is not present, the handler is the element that the event attribute is on
(see later under "Attaching Attributes Directly to the Handler Element"). 
*/
	CComPtr<ILDOMElement> handlerElement;

	CComBSTR handlerUri;
	element->getAttributeNS(OLESTR("http://www.w3.org/2001/xml-events"), OLESTR("handler"), &handlerUri);
	if ((BSTR)handlerUri != NULL)
	{
	// TODO uri reference
		BSTR ID = &((BSTR)handlerUri)[1];	// skip #
		getElementById(m_documentElement, ID, &handlerElement);
	}
	else
	{
		handlerElement = element;
	}

/*
The optional observer attribute specifies the id of the element with which the event listener
is to be registered. If this attribute is not present, the observer is the element
that the event attribute is on (see later under "Attaching Attributes Directly to the Observer Element"),
or the parent of that element (see later under "Attaching Attributes Directly to the Handler Element"). 
*/
	CComBSTR observerID;
	element->getAttributeNS(OLESTR("http://www.w3.org/2001/xml-events"), OLESTR("observer"), &observerID);

	CComPtr<ILDOMElement> targetElement;
	if (observerID.Length())
	{
		getElementById(m_documentElement, observerID, &targetElement);
	}
	else if (handlerUri.Length())		// observer is element
	{
		targetElement = element;
	}
	else	// observer is parent
	{
		CComPtr<ILDOMNode> parentNode;
		element->get_parentNode(&parentNode);

		targetElement = CComQIPtr<ILDOMElement, &IID_ILDOMElement>((IUnknown*)parentNode);
	}

	if (handlerElement && targetElement)
	{
		CComBSTR phase;
		element->getAttributeNS(OLESTR("http://www.w3.org/2001/xml-events"), OLESTR("phase"), &phase);
		bool useCapture = false;
		if (phase.Length())
		{
			if (!tcscmp(phase, OLESTR("capture")))
				useCapture = true;
		}

		CComBSTR textdata;

		long charOffset = 0;

	// TODO here
		CComPtr<ILDOMNode> node;
		handlerElement->get_firstChild(&node);
		while (node != NULL)
		{
			CComQIPtr<CLDOMCharacterDataImplImpl> textnode((IUnknown*)node);
			if (textnode)
			{
				charOffset = textnode->m_textOffset[4];

				textdata += textnode->m_data;
			}

			CComPtr<ILDOMNode> nextSibling;
			node->get_nextSibling(&nextSibling);
			node = nextSibling;
		}

		if (textdata.Length())
		{
#if _WINDOWS
			CComQIPtr<IActiveScriptParseProcedure> activeScriptParseProcedure = m_pScriptSite->m_activeScript;

			ErrorCode hr;

			if (m_pScriptSite->m_debugDocumentHelper)
			{
			//ErrorCode hr = m_pScriptSite->m_debugDocumentHelper->AddUnicodeText(textdata);
			//ASSERT(SUCCEEDED(hr));

				// TODO, have this, what was m_dwScriptCookie again?
#if 0
				DWORD dwSourceContext;
				hr = m_pScriptSite->m_debugDocumentHelper->DefineScriptBlock(charOffset, textdata.Length(), m_pScriptSite->m_activeScript, FALSE/*fScriptlet*/, &dwSourceContext);
				CComQIPtr<CLDOMElementImplImpl>(element)->m_dwScriptCookie = dwSourceContext;
#endif
			}

			CComPtr<IDispatch> disp;

			hr = activeScriptParseProcedure->ParseProcedureText(
				textdata,	// code
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
				pListener->m_listenerElement = targetElement;
				pListener->m_handlerElement = handlerElement;
				pListener->m_disp = disp;

				CComQIPtr<ILDOMEventTarget> eventTarget = targetElement;
				if (eventTarget)
				{
					eventTarget->addEventListener(event, pListener, useCapture);

					return S_OK;
				}
			}

			return hr;
#endif
		}
	}

	return E_FAIL;
}

/*
void CLDOMDocumentImplImpl::AddEventListeners(ILDOMNode* parent)
{
	ASSERT(0);

#if 0
	CComPtr<ILDOMNode> node;
	parent->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CComQIPtr<CLDOMElementImplImpl>(element)->AddEventListeners(element, m_pScriptSite);
#if 0
			//CComBSTR tagName;
			//element->get_tagName(&tagName);
			//if (!tcscmp(tagName, L"listener"))
			{
				AddEventListener(element);
			}
#endif

			AddEventListeners(element);	// Recurse
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
#endif
}
*/

void CLDOMDocumentImplImpl::AddScript(ILDOMElement* element)
{
#if _WINDOWS
	USES_CONVERSION;

// TODO: check type attribute

	CComQIPtr<IActiveScriptParse> activeScriptParse = m_pScriptSite->m_activeScript;
	CComQIPtr<IActiveScriptParseProcedure> activeScriptParseProcedure = m_pScriptSite->m_activeScript;

	CComBSTR href;
	element->getAttributeNS(OLESTR("http://www.w3.org/1999/xlink"), OLESTR("href"), &href);
	if (href.Length())
	{
		TCHAR absurl[2048];
		{
			//CComBSTR documentUrl ;
			//get_url(&documentUrl);

			DWORD resultLen = sizeof(absurl);	// Size, in bytes? or _countof(absurl);
			InternetCombineUrl(W2A(m_uri), W2A(href), absurl, &resultLen, 0);
		}

		CComPtr<ITextData> textfile;
		if (SUCCEEDED(textfile.CoCreateInstance(CLSID_TextData)))
		{
			if (SUCCEEDED(textfile->load(A2W(absurl))))
			{
				BSTR textdata;
				textfile->get_data(&textdata);

				/*
				if (m_pScriptSite->m_debugDocumentHelper)
				{
					BSTR textdata;
					textdata->get_data(&textdata);
					// Note, not freeing

					ErrorCode hr = m_pScriptSite->m_debugDocumentHelper->AddUnicodeText(textdata);
					ASSERT(SUCCEEDED(hr));
				}
				*/

				ErrorCode hr;

				EXCEPINFO excepinfo;

				hr = activeScriptParse->ParseScriptText(

					textdata,

					NULL,	// itemname
					NULL,
					NULL,
					0,
					0,	// start line number
					SCRIPTTEXT_ISVISIBLE,// | SCRIPTTEXT_ISPERSISTENT,	// flags
					NULL,
					&excepinfo);

				if (FAILED(hr))
				{
					//MessageBox(NULL, "Failed parsing script", "LHTML", MB_OK);
				}
			}
		}
	}
	else
	{
		CComBSTR textdata;

		long charOffset = 0;

	// TODO here
		CComQIPtr<ILDOMNode> node;
		element->get_firstChild(&node);
		while (node != NULL)
		{
			CComQIPtr<CLDOMCharacterDataImplImpl> textnode = node;
			if (textnode)
			{
				charOffset = textnode->m_textOffset[4];

				textdata += textnode->m_data;
			}

			CComPtr<ILDOMNode> nextSibling;
			node->get_nextSibling(&nextSibling);
			node = nextSibling;
		}

		if (textdata.Length())
		{
			ErrorCode hr;

			if (m_pScriptSite->m_debugDocumentHelper)
			{
			//ErrorCode hr = m_pScriptSite->m_debugDocumentHelper->AddUnicodeText(textdata);
			//ASSERT(SUCCEEDED(hr));

				DWORD dwSourceContext;
				hr = m_pScriptSite->m_debugDocumentHelper->DefineScriptBlock(charOffset, textdata.Length(), m_pScriptSite->m_activeScript, FALSE/*fScriptlet*/, &dwSourceContext);
				CComQIPtr<CLDOMElementImplImpl>(element)->m_dwScriptCookie = dwSourceContext;
			}

			EXCEPINFO excepinfo;

			hr = activeScriptParse->ParseScriptText(

				textdata,

				NULL,	// itemname
				NULL,	// punkContext
				NULL,
				CComQIPtr<CLDOMElementImplImpl>(element)->m_dwScriptCookie,//dwSourceContext,//m_pScriptSite->m_dwDocCookie,//dwSourceContext,//dwSourceContextCookie,
				0,	// start line number
				SCRIPTTEXT_ISVISIBLE,// | SCRIPTTEXT_ISPERSISTENT,	// flags
				NULL,
				&excepinfo);

			if (FAILED(hr))
			{
				//MessageBox(NULL, "Failed parsing script", "LHTML", MB_OK);
			}
		}
	}
#endif
}

void CLDOMDocumentImplImpl::AddScripts(ILDOMNode* parent)
{
#if _WINDOWS
	CComPtr<ILDOMNode> node;
	parent->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement, &IID_ILDOMElement> element = node;
		if (element)
		{
			// First try to add it as an xml-events element

			ErrorCode hr = AddEventListener(element);

			if (hr == S_FALSE)
			{
				// Then see if it's a normal script block
				CComBSTR tagName;
				element->get_tagName(&tagName);
				if (!tcscmp(tagName, L"script"))
				{
					AddScript(element);
				}
			}

			AddScripts(element);	// Recurse
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
#endif	// _WINDOWS
}

#if 0

//CComBSTR CLDOMDocumentImplImpl::saveXML2(ILDOMNode *node)
void CLDOMDocumentImplImpl::saveXML2(ILDOMNode *node, CWChar& xml)
{
	LDOMNodeType nodeType;
	node->get_nodeType(&nodeType);

//	CComBSTR xml;// = L"";

	if (nodeType == LNODE_DOCUMENT)
	{
		if (TRUE)	// bHadXML
		{
			xml += L"<?xml ";

			if (TRUE)
			{
				xml += L"version=\"";
				//xml += m_version;
				xml += L"1.0";
				xml += L"\" ";
			}

			if (TRUE)
			{
				xml += L"standalone=";
				xml += L"\"";

				if (m_standalone)
					xml += L"yes";
				else
					xml += L"no";

				xml += L"\"";
				xml += L" ";
			}

			xml += L"?>\n";
		}

		// Children
		CComQIPtr<ILDOMNode> child;
		node->get_firstChild(&child);

		while (child != NULL)
		{
			CComBSTR xml2 = saveXML2(child);
			xml += saveXML2(child);

			CComQIPtr<ILDOMNode> nextchild;
			child->get_nextSibling(&nextchild);
			child = nextchild;
		}
	}
	else if (nodeType == LNODE_DOCUMENT_TYPE)
	{
		CComQIPtr<ILDOMDocumentType> doctype = node;

		BSTR name; doctype->get_name(&name);
		BSTR publicId; doctype->get_publicId(&publicId);
		BSTR systemId; doctype->get_systemId(&systemId);

		xml += L"<!DOCTYPE ";
		xml += name;
		xml += L" ";

		if (SysStringLen(publicId) > 0)
		{
			xml += L"PUBLIC \"";
			xml += publicId;
			xml += L"\"";

			if (SysStringLen(systemId) > 0)
			{
				xml += L" \"";
				xml += systemId;
				xml += L"\"";
			}
		}
		else
		{
			xml += L"SYSTEM \"";
			xml += systemId;
			xml += L"\"";
		}

		xml += L">\n";

		SysFreeString(systemId);
		SysFreeString(publicId);
		SysFreeString(name);
	}
	else if (nodeType == LNODE_ELEMENT)
	{
		CComQIPtr<ILDOMElement> element = node;

		xml += L"<";

		BSTR ws0; element->getWhiteSpace(0, &ws0);
		xml += ws0;

		BSTR tagName;
		element->get_tagName(&tagName);
		xml += tagName;

		/*
		BSTR ws1; element->getWhiteSpace(1, &ws1);
		xml += ws1;
		*/

	// Attributes
		CComQIPtr<ILDOMNamedNodeMap> attributes;
		element->get_attributes(&attributes);
		unsigned long length;
		attributes->get_length(&length);

		for (unsigned long i = 0; i < length; i++)
		{
			CComQIPtr<ILDOMAttr> attr;
			attributes->item(i, (ILDOMNode**)&attr);

			//if (i > 0)
				xml += L" ";
			xml += saveXML2(attr);
		}

		BSTR ws2; element->getWhiteSpace(2, &ws2);
		xml += ws2;

		bool bHasChildren;
		element->hasChildNodes(&bHasChildren);

		if (!bHasChildren)
		{
			xml += L"/>";

			BSTR ws3; element->getWhiteSpace(3, &ws3);
			xml += ws3;
		}
		else
		{
			xml += L">";

			BSTR ws3; element->getWhiteSpace(3, &ws3);
			xml += ws3;

		// Children
			CComQIPtr<ILDOMNode> child;
			node->get_firstChild(&child);

			while (child != NULL)
			{
				_bstr_t xml2 = saveXML2(child);
				xml += saveXML2(child);

				CComQIPtr<ILDOMNode> nextchild;
				child->get_nextSibling(&nextchild);
				child = nextchild;
			}

			xml += L"</";
			xml += tagName;
			xml += L">";
		}

		BSTR ws4; element->getWhiteSpace(4, &ws4);
		xml += ws4;

		SysFreeString(tagName);
	}
	else if (nodeType == LNODE_DOCUMENT_FRAGMENT)
	{
		CComQIPtr<ILDOMDocumentFragment> fragment = node;

	// Children
		CComQIPtr<ILDOMNode> child;
		node->get_firstChild(&child);

		while (child != NULL)
		{
			_bstr_t xml2 = saveXML2(child);
			xml += saveXML2(child);

			CComQIPtr<ILDOMNode> nextchild;
			child->get_nextSibling(&nextchild);
			child = nextchild;
		}
	}
	else if (nodeType == LNODE_ATTRIBUTE)
	{
	//	CComQIPtr<ILDOMAttr> attr = node;
		CLDOMAttr* pAttr = static_cast<CLDOMAttr*>(node);

		BSTR name;
		pAttr->get_name(&name);

		//BSTR value;
		//attr->get_value(&value);

		xml += name;
		xml += L"=\"";
		//xml += value;
		xml += (BSTR)(pAttr->m_value);
		xml += L"\"";

		SysFreeString(name);
		//SysFreeString(value);
	}
	else if (nodeType == LNODE_TEXT)
	{
		CLDOMText* pText = static_cast<CLDOMText*>(node);

		xml += (BSTR)(pText->m_data);
		/*
		CComQIPtr<ILDOMText> text = node;

		BSTR s; text->get_data(&s);
		xml += s;
		SysFreeString(s);
		*/
	}
	else if (nodeType == LNODE_COMMENT)
	{
		CLDOMComment* pComment = static_cast<CLDOMComment*>(node);
	//	CComQIPtr<ILDOMComment> comment = node;

		xml += L"<!--";

		//BSTR s; comment->get_data(&s);
		//xml += s;
		//SysFreeString(s);
		xml += (BSTR)(pComment->m_data);

		xml += L"-->";
	}
	else if (nodeType == LNODE_CDATA_SECTION)
	{
		CLDOMCDATASection* pCDATA = static_cast<CLDOMCDATASection*>(node);
		//CComQIPtr<ILDOMCDATASection> cdata = node;

		xml += L"<![CDATA[\n";

		//BSTR s; cdata->get_data(&s);
		//xml += s;
		//SysFreeString(s);
		xml += (BSTR)(pCDATA->m_data);

		xml += L"\n]]>";
	}

//	return xml;//.Detach();
}
#endif

#endif

// XDM::IData
XDM::IData* Document::getParent()
{
	return NULL;
}

unsigned int Document::getPosition()
{
	ASSERT(0);
	return 0;
}

/*
System::StringW* Document::getName()
{
	ASSERT(0);
	return 0;
}

System::StringW* Document::getNamespaceURI()
{
	ASSERT(0);
	return 0;
}
*/

XDM::IData* Document::getRoot()
{
	return this;
}

unsigned int Document::getAttributeCount()
{
	return 0;
}

System::Variant Document::getAttributeValue(unsigned int index)
{
	ASSERT(0);
	THROW(-1);
	return System::Variant();
}

String Document::getAttributeName(unsigned int index)
{
	ASSERT(0);
	THROW(-1);
	return nullptr;
}

String Document::getAttributeNamespaceURI(unsigned int index)
{
	ASSERT(0);
	THROW(-1);
	return nullptr;
}

System::Type* Document::getAttributeType(unsigned int index)
{
	ASSERT(0);
	THROW(-1);
	return nullptr;
}

unsigned int Document::getChildCount()
{
	if (m_documentElement)
		return 1;
	else
		return 0;
}

bool Document::IsChildText(unsigned int index)
{
	if (m_documentElement == NULL)
	{
		ASSERT(0);
		THROW(-1);
	}

	if (index != 0)
	{
		ASSERT(0);
		THROW(-1);
	}

	return false;
}

String Document::getChildName(unsigned int index)
{
	if (index != 0)
	{
		ASSERT(0);
		THROW(-1);
	}

	return get_documentElement()->get_localName();
}

String Document::getChildNamespaceURI(unsigned int index)
{
	if (index != 0)
	{
		ASSERT(0);
		THROW(-1);
	}

	return m_documentElement->get_namespaceURI();
}

System::Type* Document::getChildType(unsigned int index)
{
	return 0;
}

XDM::IData* Document::getChildElement(unsigned int index)
{
	if (index != 0)
	{
		ASSERT(0);
		THROW(-1);
	}

	return m_documentElement;
}

String Document::getChildText(unsigned int index)
{
	return nullptr;
}

Object* Document::GetObject()
{
	return this;
}

void Document::loadDefaultStylesheet()
{
	ASSERT(0);
#if 0

//	LCSS::DocumentStyleImpl* documentStyle = dynamic_cast<LCSS::DocumentStyleImpl*>(m_document);
//	if (documentStyle)
	{
#if 0//WIN32
		TCHAR appdata[MAX_PATH];
		SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, appdata);
#else
		char appdata[MAX_PATH];
		strcpy_s(appdata, "C:\\Documents and Settings\\All Users\\Application Data");
#endif

		CSSStyleSheet* stylesheet = new CSSStyleSheet(NULL/*ownerNode*/, NULL/*ownerRule*/);
		if (stylesheet)
		{
#if WIN32
			char pathname[MAX_PATH];
			_makepath_s(pathname, NULL, appdata, "LXFramework", NULL);

			char filename[260];

			/*
			if (!wcscmp(taglocalName, OLESTR("nitf")))
			{
				_makepath(filename, NULL, pathname, "nitf.css", NULL);
			}
			else if (!wcscmp(taglocalName, OLESTR("article")))	// DocBook
			{
				_makepath(filename, NULL, pathname, "docbook.css", NULL);
			}
			else if (!wcscmp(taglocalName, OLESTR("stylesheet")))
			{
				_makepath(filename, NULL, pathname, "xslt.css", NULL);
			}
			else if (!wcscmp(taglocalName, OLESTR("html")) ||
				!wcscmp(taglocalName, OLESTR("svg")) ||
				!wcscmp(taglocalName, OLESTR("lxui")))
				*/
			{
				_makepath_s(filename, NULL, pathname, "html.css", NULL);
			}

			//MessageBox(NULL, filename, "", MB_OK);

			if (stylesheet->load(string_copy(filename))
#else
			if (stylesheet->load("WinHD_C:/Documents and Settings/All Users/Application Data/LXFramework/html.css"))
#endif
			{
				get_styleSheets()->append(stylesheet);
			}
		}
	}
#endif
}

}	// Web
}
