#ifndef w3c_Node_h
#define w3c_Node_h

namespace System
{
namespace Web
{

class WEBEXT Node : public Object
{
public:
	~Node();

	class UserData : public Object
	{
	public:
		String m_key;
		Object* m_data;
		IDOMUserDataHandler* m_handler;
	};

	virtual NodeType get_nodeType() const;

	virtual Node* insertNode(Node *newChild, Node* before);
	virtual Node* cloneNodeExport(Document* ownerDocument /*ownerDocument of cloned node*/, bool deep) const = 0;
	virtual Node* cloneNode(bool deep) const;
	virtual String get_textContent();
	virtual void set_textContent(StringIn newVal);
	ErrorCode setTextOffset(/*[in]*/ long which, long offset);	// TODO remove
	ErrorCode getTextOffset(/*[in]*/ long which, /*[out,retval]*/ long* offset);	// TODO remove
	virtual NodeList* get_childNodes() const;

	String get_localName() const;
	void set_localName(StringIn newVal);

	virtual String get_prefix() const;
	void set_prefix(StringIn newVal);

	virtual String get_namespaceURI() const;
	void set_namespaceURI(StringIn newVal);

	virtual String get_nodeName() const;
	void set_nodeName(StringIn newVal);

	virtual NamedNodeMap* get_attributes() const;
	virtual bool isSupported(StringIn feature, StringIn version);
	virtual bool hasAttributes() const;
	virtual bool hasChildNodes() const;
	virtual Node* replaceChild(Node* newChild, Node* oldChild);
	virtual Node* removeChild(Node* oldChild);
	virtual Node* insertBefore(Node* newChild, Node* refChild);
	virtual Node* appendChild(Node* newChild);
	virtual ChildNode* get_previousSibling() const = 0;
	virtual ChildNode* get_nextSibling() const = 0;
	virtual ChildNode* get_lastChild() const;
	virtual ChildNode* get_firstChild() const;
	virtual Node* get_parentNode() const = 0;

	virtual Document* get_ownerDocument() const;

protected:

	virtual void set_previousSibling(ChildNode *newVal) = 0;
	virtual void set_nextSibling(ChildNode *newVal) = 0;
	virtual void set_parentNode(Node* newVal) = 0;

public:

	Document* m_ownerDocument;

	ChildNode* m_firstChild;
	ChildNode* m_lastChild;

	// m_ppAttr points to this node, if we're being replaced in a NamedNodeMap, then we update this
	inner_ptr<Attr*> m_ppAttr;

	long m_textOffset[10];	// TODO remove

	int m_position;

	PNode* m_pNode;

protected:

	CTOR Node();

	friend class PElementBase;

	// TODO map<StringW*, UserData*>
	vector<UserData*> m_userdataList;

	NodeList* m_childNodes;
	String m_namespaceURI;
	String m_prefix;
	String m_localName;
	String m_nodeName;

	int m_xmlspace;	// 0=default, 1=preserve	// TODO, Attr don't have this
};

class WEBEXT ChildNode : public Node
{
public:

	virtual Node* get_parentNode() const;
	virtual ChildNode* get_previousSibling() const;
	virtual ChildNode* get_nextSibling() const;

	Node* m_parentNode;
	ChildNode* m_nextSibling;
	ChildNode* m_previousSibling;

	Node* m_ascendant_DOMAttrModifed;

protected:

	virtual void set_parentNode(Node* newVal);
	virtual void set_previousSibling(ChildNode *newVal);
	virtual void set_nextSibling(ChildNode *newVal);

	friend class Node;

protected:

	CTOR ChildNode();
	CTOR ChildNode(PNode* pNode);
};

}	// w3c
}

#endif // w3c_Node_h
