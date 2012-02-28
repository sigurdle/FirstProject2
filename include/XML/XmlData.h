#ifndef XmlData_h
#define XmlData_h

namespace System
{
namespace XmlData
{

enum NodeType
{
	NODE_COMMENT,
	NODE_CDATA_SECTION,
	NODE_TEXT,
	NODE_ELEMENT,
	NODE_DOCUMENT,
	NODE_DOCUMENT_TYPE,
	NODE_ENTITY_REFERENCE,
	NODE_PROCESSING_INSTRUCTION,
	NODE_ATTRIBUTE,
};

class Node;
class Document;

class XMLEXT NodeList : public Object
{
public:

	virtual unsigned int get_length() const;
	virtual Node* item(unsigned int index) const;

	vector<Node*> m_items;
};

class XMLEXT NamedNodeMap : public Object
{
public:

	virtual unsigned int get_length() const;
	virtual Node* item(unsigned int index) const;
	virtual Node* getNamedItemNS(StringIn namespaceURI, StringIn localName) const;

	vector<Node*> m_items;
	//map<System::StringW*, Node*, Ref_Less<System::StringW>, System::__gc_allocator> m_map;
};

class XMLEXT Node : public Object, public XDM::IData
{
public:

	virtual ~Node();

	void setUserData(StringIn key, Object* data);
	Object* getUserData(StringIn key) const;

	virtual String get_textContent();

	virtual long getTextOffset(long which) const;
	virtual void setTextOffset(long which, long offset);

	virtual Node* insertBefore(Node* child, Node* before);
	virtual Node* appendChild(Node* child);

	virtual Node* get_parentNode() const;
	virtual Node* get_firstChild() const;
	virtual Node* get_lastChild() const;
	virtual Node* get_nextSibling() const;
	virtual Node* get_previousSibling() const;

	virtual NodeList* get_childNodes();

	virtual NamedNodeMap* get_attributes();

	virtual NodeType get_nodeType() const = 0;
	virtual String get_nodeName() = 0;
	virtual String get_namespaceURI()
	{
		return nullptr;
	}

	virtual String get_localName()
	{
		return nullptr;
	}

	virtual String get_nodeValue()
	{
		return nullptr;
	}

	virtual Document* get_ownerDocument();

	void set_ownerDocument(Document* newVal);

	virtual String ToString() override
	{
		String str = get_nodeValue();
		if (str == nullptr) str = get_nodeName();
		return str;
	}

// XDM::IData

	virtual XDM::IData* getParent()
	{
		return get_parentNode();
	}
	virtual unsigned int getPosition();

//	virtual System::StringW* getName() = 0;
//	virtual System::StringW* getNamespaceURI() = 0;

	virtual XDM::IData* getRoot();

	virtual unsigned int getAttributeCount()
	{
		NamedNodeMap* attributes = get_attributes();
		if (attributes)
		{
			return attributes->get_length();
		}
		return 0;
	}
	virtual Variant getAttributeValue(unsigned int index);
	virtual String getAttributeName(unsigned int index);

	virtual String getAttributeNamespaceURI(unsigned int index);
	virtual System::Type* getAttributeType(unsigned int index);

	virtual unsigned int getChildCount();
	virtual bool IsChildText(unsigned int index);
	virtual String getChildName(unsigned int index);
	virtual String getChildNamespaceURI(unsigned int index);
	virtual System::Type* getChildType(unsigned int index);
	virtual XDM::IData* getChildElement(unsigned int index);
	virtual String getChildText(unsigned int index);

	virtual Object* GetObject()
	{
		return this;
	}

public:

	typedef map<String, Object*> tyuserdatamap;
	tyuserdatamap m_userdata;

protected:

	CTOR Node();

	NodeList* m_childNodes;
	Node* m_firstChild;
	Node* m_lastChild;
	Node* m_nextSibling;
	Node* m_previousSibling;
	Node* m_parentNode;
	Document* m_ownerDocument;
	int m_position;

	/*
	CLXUIEventTargetImpl* GetParentEventTarget()
	{
		return dynamic_cast<CLXUIEventTargetImpl*>(m_parentNode);
	}
	*/

private:
	long m_textOffset[10];

	Node* insertNode(Node* newChild, Node* pBefore);
};

class XMLEXT DocumentType : public Node
{
public:
	CTOR DocumentType();

	virtual NodeType get_nodeType() const override;
	virtual String get_nodeName() override;
	virtual String get_name();

protected:

	friend class Document;
	friend class XMLParser;

	String m_name;
	String m_publicId;
	String m_systemId;
};

class XMLEXT ProcessingInstruction: public Node
{
public:
	CTOR ProcessingInstruction();

	virtual NodeType get_nodeType() const override;
	virtual String get_nodeName() override;
	virtual String get_nodeValue();

protected:

	friend class Document;

	CTOR ProcessingInstruction(Document* document, StringIn target, StringIn data)
	{
		m_ownerDocument = document;
		m_target = target;
		m_data = data;
	}

	String m_target;
	String m_data;
};

class XMLEXT EntityReference : public Node
{
public:
	CTOR EntityReference();
	NodeType get_nodeType() const;
	String get_nodeName();
};

class XMLEXT Attr : public Node
{
public:
	CTOR Attr();
	~Attr();

	virtual NodeType get_nodeType() const override;
	virtual String get_namespaceURI() override;
	virtual String get_nodeName() override;
	virtual String get_name();
	virtual String get_prefix() ;
	virtual String get_localName() override;
	virtual String get_nodeValue();
	virtual String get_value();
	virtual void set_value(StringIn newVal);

	virtual String ToString() override;

public:

	String m_namespaceURI;
	String m_nodeName;
	String m_prefix;
	String m_localName;
};

class XMLEXT CharacterData : public Node
{
public:
	virtual String get_nodeValue();
	virtual unsigned int get_length() const;
	virtual String get_data();
	virtual void set_data(StringIn data);
	virtual void deleteData(unsigned int offset, unsigned int count) throw (ArgumentOutOfRangeException*);
	virtual void insertData(unsigned int offset, StringIn arg) throw (ArgumentOutOfRangeException*);
	virtual String substringData(unsigned int offset, unsigned int count) const throw (ArgumentOutOfRangeException*);
	virtual String get_textContent();

	virtual String ToString() override
	{
		return get_data();
	}

public:

	String m_data;
};

class XMLEXT Comment : public CharacterData
{
public:
	CTOR Comment();

	virtual NodeType get_nodeType() const override;
	virtual String get_nodeName() override;

	virtual String ToString() override;

	static String s_nodeName;
};

class XMLEXT Text : public CharacterData
{
public:
	CTOR Text();

	virtual NodeType get_nodeType() const override;
	virtual String get_nodeName() override;

	static String s_nodeName;
};

class XMLEXT CDATASection : public Text
{
public:
	CTOR CDATASection();

	NodeType get_nodeType() const;
	String get_nodeName();

	virtual String ToString() override;

	static String s_nodeName;
};

class XMLEXT Element : public Node
{
public:
	CTOR Element();
	CTOR Element(NamedNodeMap* attributes);
	~Element();

	virtual NodeType get_nodeType() const override;
	virtual String get_tagName();
	virtual String get_nodeName() override;
	virtual String get_localName() override;
	virtual String get_namespaceURI() override;
	virtual NamedNodeMap* get_attributes() override;
	void set_attributes(NamedNodeMap* attributes);
	String getAttribute(StringIn name);
	String getAttributeNS(StringIn namespaceURI, StringIn localName);
	void setAttribute(StringIn name, StringIn value);

	Element* getElementByTagNameNS(StringIn namespaceURI, StringIn localName);

	virtual String ToString() override;

	void DeselectAll();
	void DeleteSelected();

	/*
	Element* GetTargetElement()
	{
		return this;
	}
  */


#if 0
	STDMETHOD(get_parentNode)(/*[out, retval]*/ IEElement* *pVal)
	{
		ASSERT(0);
		return 0;
#if 0
		ATLASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;

		*pVal = NULL;

		CComPtr<ILDOMNode> parentNode;
		m_domElement->get_parentNode(&parentNode);

		if (parentNode == NULL)
		{
			return S_OK;
		}

		CComQIPtr<remove> parentElement = parentNode;
		if (parentElement)
		{
			CComPtr<IEElement> eElement;
			m_pDocument->GetEElementFromDOMElement(parentElement, &eElement);

			*pVal = eElement;
			if (*pVal) (*pVal)->AddRef();
		}
#endif
		return S_OK;
	}
#endif

#if 0
	STDMETHOD(set_parentNode)(/*[in]*/ IEElement* newVal)
	{
		//m_parentNode = newVal;
		return S_OK;
	}
#endif

#if 0
	Element* insertElement)(/*[in]*/ Element* newChild, /*[in]*/ Element* pBefore)
	{
		ASSERT(0);
#if 0
#if 0
		IEElement* pPrevParent;
		newChild->get_parentNode(&pPrevParent);
		if (pPrevParent)
		{
			//pPrevParent->removeChild(newChild, &newChild);
			pPrevParent->Release();
		}

		newChild->AddRef();

		newChild->set_parentNode(this);

		CComPtr<IEElement> pAfter;

		if (pBefore)
			pBefore->get_previousElement(&pAfter);
		else
			pAfter = m_lastElement;

		newChild->set_nextElement(pBefore);
		newChild->set_previousElement(pAfter);

		if (pAfter == NULL)
			m_firstElement = newChild;
		else
			pAfter->set_nextElement (newChild);

		if (pBefore == NULL)
			m_lastElement = newChild;
		else
			pBefore->set_previousElement(newChild);

		if (pBefore)
		{
			for (int i = 0; i < m_children.GetSize(); i++)
			{
				if (m_children[i] == pBefore)
				{
					m_children.InsertAt(i, newChild);
					break;
				}
			}
		}
		else
		{
			m_children.Add(newChild);
		}
#endif

		// Insert into DOM tree
		{
			LXML::Node* domNode;
			newChild->get_domNode(&domNode);

			if (domNode)
			{
				LXML::Node* parentNode = domNode->get_parentNode();
				if (parentNode == NULL)	// Only if not already inserted
				{
					LXML::Node* domBefore;
					if (pBefore)
					{
						pBefore->get_domNode(&domBefore);
					}
					m_domElement->insertBefore(domNode, domBefore);
				}
			}
		}
#endif
		return NULL;
	}

	STDMETHODIMP appendChild(Element* child)
	{
		return insertElement(child, NULL);
	}
#endif

private:

	friend class Document;

	String m_namespaceURI;
	String m_nodeName;
	String m_prefix;
	String m_localName;
	NamedNodeMap* m_attributes;
};

class XMLEXT Document : public Node, public XPath::XPathEvaluator
{
public:

	CTOR Document();
	virtual ~Document();

	bool load(StringIn url);
	bool load(IO::Stream* stream);

	virtual NodeType get_nodeType() const override;
	virtual String get_nodeName() override;
	Element* get_documentElement();
	DocumentType* get_doctype();
	virtual Node* appendChild(Node* child) override;

	Comment* createComment(StringIn data);
	Text* createTextNode(StringIn data);
	CDATASection* createCDATASection(StringIn data);
	ProcessingInstruction* createProcessingInstruction(StringIn target, StringIn data);
	EntityReference* createEntityReference(StringIn name);
	Attr* createAttributeNS(StringIn namespaceURI, StringIn qualifiedName);
	Attr* createAttributeNS(StringIn namespaceURI, StringIn qualifiedName, StringIn localName);
	Element* createElementNS(StringIn namespaceURI, StringIn qualifiedName);
	Element* createElementNS(StringIn namespaceURI, StringIn qualifiedName, StringIn localName);

	virtual String ToString() override;

	static String s_nodeName;

private:

	Element* m_documentElement;
};

}	// XmlData
}	// System

#endif // XmlData_h
