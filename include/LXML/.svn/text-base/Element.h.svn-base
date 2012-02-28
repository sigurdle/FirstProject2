#ifndef Web_Element_h
#define Web_Element_h

#include "DOMEventTargetImpl.h"
#include "ElementEditASImpl.h"

#include "XMLAttr.h"

namespace System
{
namespace Web
{

class WEBEXT AttrDef : public Object
{
public:

	CTOR AttrDef(const WCHAR* name) : m_name(name)
	{
	}

	ImmutableString<WCHAR> m_name;
};

class WEBEXT ElementType : public Object
{
public:
	CTOR ElementType(const Type_Info& typeinfo) : m_typeinfo(typeinfo)
	{
	}

	const Type_Info& m_typeinfo;
	AttrDef** m_unspecified;
	uint m_unspecifiedCount;
};

class WEBEXT AttributeContentListener : public Object, public IEventListener
{
public:

	CTOR AttributeContentListener(Element* element, StringIn content, bool preventDefaultOnReturnValue);

protected:

	virtual void handleEvent(Event* evt) override;

	Element* m_element;
	JSVM::ScriptFunction* m_pFun;
	bool m_preventDefaultOnReturnValue;
};

class WEBEXT Element :
	public ChildNode,
	public EventTarget,
	public XDM::IData,

	protected INamedNodeMapListener
	//protected IDOMAttrListener
{
public:
	~Element();

	virtual void OnAttrValueChanged(StringIn nodeName, Attr* attr);

	virtual void set_attributes(NamedNodeMap* newVal);

	void setAttribute(StringIn name, StringIn value);
	void setAttributeNS(StringIn namespaceURI, StringIn qualifiedName, StringIn value);
	Attr* setAttributeNode(Attr* newAttr);
	Attr* setAttributeNodeNS(Attr* newAttr);

	PElementBase* GetPElement() const
	{
		return static_cast<PElementBase*>(m_pNode);
	}

// Set baseVal/animVal from attributes and parse 'style' attributes
	void UpdateAnimationElements(Element* domElement);

	void AddEventListener(Attr* attr, StringIn eventType);
	void AddEventListeners();

	CATXMLAttr* GetXMLAttribute(StringIn attributeName);

	// TODO remove
	void SetValues(StringIn namespaceURI, StringIn attrName, Element* element);

	void SetAttribute(StringIn namespaceURI, StringIn attrName, Element* element);

	void SetAllValues(Element* element);
	virtual NodeType get_nodeType() const;

	virtual void set_textContent(StringIn newVal);

	bool hasAttribute(StringIn name);
	bool hasAttributeNS(StringIn namespaceURI, StringIn localName);
	Attr* getAttributeNode(StringIn name);
	Attr* getAttributeNodeNS(StringIn qualifiedName, StringIn localName);
	String getAttribute(StringIn name);
	String getAttributeNS(StringIn namespaceURI, StringIn localName) throw(DOMException);
	String get_tagName();
	virtual void set_ownerDocument(Document* newVal);
	virtual void removeAttribute(StringIn name);
	virtual void removeAttributeNS(StringIn namespaceURI, StringIn localName);
	virtual NamedNodeMap* get_attributes() const;

	virtual void OnAddedNode(NamedNodeMap* nodemap, Node* node);
	virtual void OnRemoveNode(NamedNodeMap* nodemap, Node* node);

	void AddXMLAttribute(CATXMLAttr* pAttr)
	{
		pAttr->m_animationTarget = this;

		m_xmlAttrs.Add(pAttr);
	}

	Node* cloneNodeExport(Document* ownerDocument, bool deep) const;

	TypeInfo* get_schemaTypeInfo();

	virtual ElementType* GetElementType()
	{
		return NULL;
	}

// XDM::IData
	virtual XDM::IData* getParent() override;
	virtual unsigned int getPosition() override;

	virtual XDM::IData* getRoot() override;

	virtual unsigned int getAttributeCount() override;
	virtual Variant getAttributeValue(unsigned int index) override;
	virtual String getAttributeName(unsigned int index) override;
	virtual String getAttributeNamespaceURI(unsigned int index) override;
	virtual Type* getAttributeType(unsigned int index) override;

	virtual unsigned int getChildCount() override;
	virtual bool IsChildText(unsigned int index) override;
	virtual String getChildName(unsigned int index) override;
	virtual String getChildNamespaceURI(unsigned int index) override;
	virtual Type* getChildType(unsigned int index) override;
	virtual XDM::IData* getChildElement(unsigned int index) override;
	virtual String getChildText(unsigned int index) override;

	virtual Object* GetObject() override;

public:

	void CreateAttributes()
	{
		m_attributes = new NamedNodeMap;
	}

	void UnspecifiedAttr(inner_ptr<Attr*> ppAttr, StringIn namespaceURI, StringIn localName);

	vector<CATXMLAttr*> m_xmlAttrs;	// List of xml attributes on element

	short m_bSetStyleAttribute;

	TypeInfo* m_schemaTypeInfo;

protected:

	CTOR Element(PElementBase* pPElement);
	CTOR Element(PElementBase* pPElement, NamedNodeMap* attributes);

	void AddAttributeContentEventHandler(StringIn type, StringIn attributeName, bool preventDefaultOnReturnValue);

	NamedNodeMap* m_attributes;
//	PElementBase* m_pElement;	// Same as m_pNode (TODO remove)

public:	// TODO

	CSSStyleDeclaration* m_styleDeclaration;	// style attribute
	CSSStyleDeclaration* m_presentationAttributes;	// (SVG) presentation attributes
	CSSStyleDeclaration* m_overrideStyle;	// Animations write into this
	vector<ElementAnimation*> m_animations;
};

}	// Web
}	// System

#endif // Web_Element_h
