#ifndef Web_Attr_h
#define Web_Attr_h

namespace System
{
namespace Web
{

interface IValueHandler
{
	virtual Object* Create() const = 0;
	virtual void ParseString(Object* value, StringIn str) const = 0;
	virtual void InterpolateValue(Object* dest, Object* a, Object* b, double t) = 0;
};

#if 0
typedef StringW* (Element::*GetBaseValString_t)();
typedef void (Element::*SetBaseValString_t)();
typedef Object* (Element::*GetBaseValObject_t)();
typedef void (Element::*SetAnimValObject_t)(Object* value);
//typedef IValueHandler* (Element::*GetValueHandler_t)();
typedef IValueHandler* (*GetValueHandler_t)();

struct attr_vtable
{
	StringW* (Element::*GetBaseValString)();
	void (Element::*SetBaseValString)();
	Object* (Element::*GetBaseValObject)();
	void (Element::*SetAnimValObject)(Object* value);
	GetValueHandler_t GetValueHandler;
	/*
	Object* (Element::CreateValue)(
	StringParser_t (Element::*GetParser)();
	*/
};
#endif

interface IAttrOwner
{
	virtual Element* GetElement() = 0;
	virtual String GetBaseValAsString() = 0;
	virtual void UpdateBaseValString() = 0;
	virtual Object* GetBaseValAsObject() = 0;
	virtual void SetAnimValAsObject(Object* value) = 0;
	virtual IValueHandler* GetValueHandler() = 0;
};

class WEBEXT Attr : public Node
{
public:
	CTOR Attr();
	~Attr();

	virtual Node* get_parentNode() const;
	virtual ChildNode* get_previousSibling() const;
	virtual ChildNode* get_nextSibling() const;

	virtual void set_parentNode(Node *newVal);
	virtual void set_previousSibling(ChildNode *newVal);
	virtual void set_nextSibling(ChildNode *newVal);

	virtual Element* get_ownerElement();
	virtual bool get_specified() const;
	virtual String get_value();
	virtual void set_value(StringIn newVal);
	virtual String get_name() const;

// Node
	virtual NodeType get_nodeType() const override;
	String get_nodeValue();
	void set_nodeValue(StringIn newVal);

	virtual Node* cloneNodeExport(Document* ownerDocument, bool deep) const;

protected:

	Element* GetOwnerElement();

private:

	friend class Element;
	friend class Document;

	void SetOwnerElement(Element* newVal);

	Element* m_ownerElement;	// Can I remove this?
	String m_textContent;	// Flattened
	bool m_specified;

public:	// TODO

	bool m_valueIsValid;
	short m_cssPropertyIndex;
	IAttrOwner* m_owner;

	list<ElementAnimation*> m_animations;
};

}	// Web
}	// System

#endif // Web_Attr_h
