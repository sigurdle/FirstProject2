#ifndef w3c_DOMDocumentType_h
#define w3c_DOMDocumentType_h

#include "Node.h"
#include "DOMEventTargetImpl.h"

namespace System
{
namespace Web
{

class DocumentType;
class NamedNodeMap;
class DTDDocument;

class WEBEXT CLDOMInternalSubsetNode :
	public ChildNode,
	public EventTarget
{
public:
	CTOR CLDOMInternalSubsetNode();

	DocumentType* m_ownerDoctype;

	DocumentType* get_ownerDoctype() const
	{
		return m_ownerDoctype;
	}

	Node* cloneNodeExport(Document* ownerDocument, bool deep) const
	{
		ASSERT(0);
		return NULL;
	}
};

class CDTDDocument;

class WEBEXT DocumentType : 
	public ChildNode,
	public EventTarget,
	protected CNotifySendImpl<DocumentType>
{
public:
	CTOR DocumentType();
	~DocumentType();

	NamedNodeMap* get_notations();
	NamedNodeMap* get_entities();
	String get_internalSubset();
	void set_internalSubset(StringIn newVal);
	String get_systemId() const;
	void set_systemId(StringIn newVal);
	String get_publicId() const;
	void set_publicId(StringIn newVal);
	String get_name() const;
	void set_name(StringIn name);

// Node
	NodeType get_nodeType() const;
	Node* cloneNodeExport(Document* ownerDocument, bool deep) const;

// Extensions
#if 0
	STDMETHOD(get_internalDTD)(/*[out, retval]*/ ILDTDDocument* *pVal);
//	STDMETHOD(get_internalSubsetNodes)(/*[out, retval]*/ ILDOMNodeList* *pVal);
	STDMETHOD(get_internalSubsetNode)(/*[out, retval]*/ ILDOMInternalSubsetNode* *pVal);
#endif

public:

	CLDOMInternalSubsetNode* m_internalSubsetNode;

	String m_name;
	String m_publicId;
	String m_systemId;

	CDTDDocument* m_dtd;

protected:

	NamedNodeMap* m_entities;

// EventTarget
	virtual bool dispatchEvent2(Event* evt, bool bCapture);
};

}	// w3c
}

#endif // w3c_DOMDocumentType_h
