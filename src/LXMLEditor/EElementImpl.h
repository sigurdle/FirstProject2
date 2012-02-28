#pragma once

//#include "item.h"

//#include "EXMLDocument.h"
//#include "ESelectedElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CEXMLDocument;
//class CESelectedElementImpl;
class CLSVGBehavior;

class Node;

class LXMLEDITEXT NodeList : public System::Object
{
public:

	virtual unsigned int get_length() const;
	virtual Node* item(unsigned int index);

	Array<Node*> m_items;
};

class LXMLEDITEXT NamedNodeMap : public System::Object
{
public:

	virtual unsigned int get_length() const;
	virtual Node* item(unsigned int index);
	virtual Node* getNamedItemNS(System::StringW* namespaceURI, System::StringW* localName);

	Array<Node*> m_items;
};

class MutationEvent : public System::Event
{
public:
	Node* relatedNode;
	long m_offset;
	long m_len;
};

class LXMLEDITEXT Node :
	public System::EventTargetImpl
{
public:
	CTOR Node();
//	LXML::Node*	m_domElement; // Keep reference

	typedef map<System::StringW*, System::Object*> tyuserdatamap;
	tyuserdatamap m_userdata;

	void setUserData(System::StringW* key, System::Object* data)
	{
		m_userdata.insert(tyuserdatamap::value_type(key, data));
	}

	System::Object* getUserData(System::StringW* key)
	{
		tyuserdatamap::const_iterator it = m_userdata.find(key);
		if (it != m_userdata.end())
		{
			return (*it).second;
		}
		else
			return NULL;
	}

	System::StringW* m_localName;

	virtual System::StringW* get_textContent()
	{
		return NULL;
	}

	virtual long getTextOffset(long which) const;
	virtual void setTextOffset(long which, long offset);

	virtual Node* insertBefore(Node* child, Node* before);
	virtual Node* appendChild(Node* child);

	virtual Node* get_parentNode();
	virtual Node* get_firstChild();
	virtual Node* get_lastChild();
	virtual Node* get_nextSibling();
	virtual Node* get_previousSibling();

	virtual NodeList* get_childNodes();

	virtual NamedNodeMap* get_attributes();

	virtual Web::NodeType get_nodeType() const = 0;
	virtual System::StringW* get_nodeName() = 0;

	virtual CEXMLDocument* get_ownerDocument()
	{
		return m_ownerDocument;
	}

	void set_ownerDocument(CEXMLDocument* newVal)
	{
		m_ownerDocument = newVal;
	}

protected:

	NodeList* m_childNodes;
	Node* m_firstChild;
	Node* m_lastChild;
	Node* m_nextSibling;
	Node* m_previousSibling;
	Node* m_parentNode;
	CEXMLDocument* m_ownerDocument;	// Don't keep reference

	System::EventTargetImpl* GetParentEventTarget()
	{
		return dynamic_cast<System::EventTargetImpl*>(m_parentNode);
	}

private:
	long m_textOffset[10];

	Node* insertNode(Node *newChild, Node* pBefore);
};

class LXMLEDITEXT DocumentType : public Node
{
public:
	DocumentType()
	{
		m_name = NULL;
		m_publicId = NULL;
		m_systemId = NULL;
	}

	System::StringW* m_name;
	System::StringW* m_publicId;
	System::StringW* m_systemId;

	Web::NodeType get_nodeType() const
	{
		return Web::NODE_DOCUMENT_TYPE;
	}

	System::StringW* get_nodeName()
	{
		return WSTR("#");
	}
};

class LXMLEDITEXT ProcessingInstruction: public Node
{
public:
	ProcessingInstruction()
	{
	}

	Web::NodeType get_nodeType() const
	{
		return Web::NODE_PROCESSING_INSTRUCTION;
	}

	System::StringW* get_nodeName()
	{
		return WSTR("#");
	}
};

class LXMLEDITEXT EntityReference : public Node
{
public:
	EntityReference()
	{
	}

	Web::NodeType get_nodeType() const
	{
		return Web::NODE_ENTITY_REFERENCE;
	}

	System::StringW* get_nodeName()
	{
		return WSTR("#");
	}
};

class LXMLEDITEXT Attr : public Node
{
public:

	Attr();
	~Attr();

	Web::NodeType get_nodeType() const override
	{
		return Web::NODE_ATTRIBUTE;
	}

	virtual String get_prefix();
	virtual String get_localName();
	virtual String get_value();
	virtual void set_value(StringIn newVal);

	String get_nodeName() const override
	{
		return get_localName();
	}

	String m_prefix;
};

class LXMLEDITEXT CharacterData : public Node
{
public:

	virtual unsigned int get_length() const;
	virtual System::StringW* get_data();
	virtual void set_data(System::StringW* data);
	//virtual System::StringW* get_dataref() const;
	virtual void deleteData(long offset, long count);
	virtual void insertData(long offset, System::StringW* arg);
	virtual System::StringW* substringData(unsigned int offset, unsigned int count) const;

public:
	System::StringW* m_data;
};

class LXMLEDITEXT Comment : public CharacterData
{
public:
	Comment()
	{
	}

	Web::NodeType get_nodeType() const
	{
		return Web::NODE_COMMENT;
	}

	System::StringW* get_nodeName()
	{
		return WSTR("#comment");
	}
};

class LXMLEDITEXT Text : public CharacterData
{
public:
	Text()
	{
	}

	Web::NodeType get_nodeType() const
	{
		return Web::NODE_TEXT;
	}

	System::StringW* get_nodeName()
	{
		return WSTR("#text");
	}
};

class LXMLEDITEXT CDATASection : public Text
{
public:
	CDATASection()
	{
	}

	Web::NodeType get_nodeType() const
	{
		return Web::NODE_CDATA_SECTION;
	}

	System::StringW* get_nodeName()
	{
		return WSTR("#cdata-section");
	}
};

class LXMLEDITEXT Element : public Node
{
public:
	Element();
	~Element();

	System::StringW* m_namespaceURI;
	System::StringW* m_localName;

	NamedNodeMap* m_attributes;

	Web::NodeType get_nodeType() const
	{
		return Web::NODE_ELEMENT;
	}

	System::StringW* get_nodeName()
	{
		return m_localName;
	}

	System::StringW* get_namespaceURI()
	{
		return m_namespaceURI;
	}

	virtual NamedNodeMap* get_attributes();

	void set_attributes(NamedNodeMap* attributes);

	System::StringW* getAttribute(System::StringW* name);

	/*
	ILSVGTransform* GetMatrixTransform()
	{
		CComQIPtr<ILSVGTransformable> transformable = m_domElement;

		if (transformable)
		{
			CComQIPtr<ILSVGAnimatedTransformList> animtransformlist;
			transformable->get_transform(&animtransformlist);

			CComQIPtr<ILSVGTransformList> basetransformlist;
			animtransformlist->get_baseVal(&basetransformlist);

			long numberOfItems;
			basetransformlist->get_numberOfItems(&numberOfItems);
			if (numberOfItems > 0)
			{
				for (int i = numberOfItems-1; i >= numberOfItems-1; i--)
				{
					CComQIPtr<ILSVGTransform> transform;
					basetransformlist->getItem(i, &transform);

					LSVGTransformType type;
					transform->get_type(&type);

					if (type == SVG_TRANSFORM_MATRIX)
					{
						return transform;
					}
				}
			}

		// Create new 'matrix' transform
			CComQIPtr<ILSVGMatrix> matrix;
			matrix.CoCreateInstance(CLSID_LSVGMatrix);
			
			CComQIPtr<ILSVGTransform> transform;
			basetransformlist->createSVGTransformFromMatrix(matrix, &transform);
			basetransformlist->appendItem(transform, NULL);

			return transform;
		}

		return NULL;
	}
	
	CComQIPtr<ILSVGMatrix> m_initialMatrix;
*/

	void DeselectAll();
	void DeleteSelected();

	Element* GetTargetElement()
	{
		return this;
	}

	// Have this on ESVGElement instead ??
	ErrorCode HitTest(ISVGView* view, Web::SVGSVGElement* svgsvgElement, Web::SVGMatrix* ctm, double ptx, double pty, _SVGHitData* hit)
	{
		ASSERT(0);
#if 0
		SVGMatrix mat(ctm);
		SVGPoint pt(ptx, pty);

		CComQIPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);

		gmMatrix3 imat = mat.inverse();
	//
		/*
		CComPtr<ILSVGMatrix> ictm;
		ctm->inverse(&ictm);

		CComPtr<ILSVGPoint> svgPoint;
		svgsvgElement->createSVGPoint(&svgPoint);
		svgPoint->put_x(pt.X);
		svgPoint->put_y(pt.Y);

		CComPtr<ILSVGPoint> xsvgPoint;
		svgPoint->matrixTransform(ictm, &xsvgPoint);
		*/

		SVGPoint xpt = pt.matrixTransform(imat);

		VARIANT_BOOL bHit;
		ASSERT(0);
		return 0;
#if 0
		window->SVGHitTest(CComQIPtr<ILSVGElement>(m_domElement), 0, xpt.X, xpt.Y, &bHit);
#endif

		if (bHit)
			return S_OK;
		else
#endif
			return Success_False;
	}

	/////////

	//virtual
	ErrorCode CreateSelectedElement(CEXMLViewGroup* viewGroup, IESelectedElement* *pVal)
	{
		ASSERT(0);
#if 0
		CComObject<CESelectedElement>* pSelectedElement;
		CComObject<CESelectedElement>::CreateInstance(&pSelectedElement);
		pSelectedElement->AddRef();
		pSelectedElement->m_pElement = this;//SetElement(this);
		pSelectedElement->m_viewGroup = viewGroup;

		*pVal = pSelectedElement;
#endif
		return Success;
	}

//	virtual BOOL OnCmdMsg(UINT nID, CICmdUIUpdate* pCmdUI);

	Web::Node* get_domNode()
	{
		ASSERT(0);
		return NULL;//m_domElement;
	}

	Web::Element* get_domElement()
	{
		ASSERT(0);
		return NULL;//dynamic_cast<LXML::Element*>(m_domElement);
	}

	ErrorCode set_domElement(/*[in]*/ Web::Element* newVal)
	{
		ASSERT(0);
#if 0
		ASSERT(m_domElement == NULL);
		if (m_domElement != NULL) return E_FAIL;
		m_domElement = newVal;
#endif
		return Success;
	}

#if 0
	STDMETHOD(get_parentNode)(/*[out, retval]*/ IEElement* *pVal)
	{
		ASSERT(0);
		return 0;
#if 0
		ASSERT(pVal != NULL);
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
	STDMETHOD(put_parentNode)(/*[in]*/ IEElement* newVal)
	{
		//m_parentNode = newVal;
		return S_OK;
	}
#endif

	ErrorCode insertElement(/*[in]*/ Element* newChild, /*[in]*/ Element* pBefore)
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

		newChild->put_parentNode(this);

		CComPtr<IEElement> pAfter;

		if (pBefore)
			pBefore->get_previousElement(&pAfter);
		else
			pAfter = m_lastElement;

		newChild->put_nextElement(pBefore);
		newChild->put_previousElement(pAfter);

		if (pAfter == NULL)
			m_firstElement = newChild;
		else
			pAfter->put_nextElement (newChild);

		if (pBefore == NULL)
			m_lastElement = newChild;
		else
			pBefore->put_previousElement(newChild);

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
		return Success;
	}

	ErrorCode appendChild(Element* child)
	{
		return insertElement(child, NULL);
	}

	ErrorCode get_previousElement(/*[out, retval]*/ Element* *pVal)
	{
		ASSERT(0);
	/*
		if (pVal == NULL) return E_POINTER;
		*pVal = m_previousElement;
		if (*pVal) (*pVal)->AddRef();
		*/
		return Success;
	}
	ErrorCode set_previousElement(/*[in]*/ Element* newVal)
	{
		ASSERT(0);
	/*
		m_previousElement = newVal;
*/		return Success;
	}
	ErrorCode get_nextElement(/*[out, retval]*/ Element* *pVal)
	{
		ASSERT(0);
	/*
		if (pVal == NULL) return E_POINTER;
		*pVal = m_nextElement;
		if (*pVal) (*pVal)->AddRef();
*/		return Success;
	}
	ErrorCode set_nextElement(/*[in]*/ Element* newVal)
	{
		ASSERT(0);
	/*
		m_nextElement = newVal;
*/		return Success;
	}
	ErrorCode get_lastElement(/*[out, retval]*/ Element* *pVal)
	{
		ASSERT(0);
	/*
		if (pVal == NULL) return E_POINTER;
		*pVal = m_lastElement;
		if (*pVal) (*pVal)->AddRef();
*/		return Success;
	}

	ErrorCode get_firstElement(/*[out, retval]*/ Element* *pVal)
	{
		ASSERT(0);
	/*
		if (pVal == NULL) return E_POINTER;
		*pVal = m_firstElement;
		if (*pVal) (*pVal)->AddRef();
*/		return Success;
	}

	ErrorCode Move(ISVGView* view, double dx, double dy)
	{
		return Error_NotImplemented;
	}

	ErrorCode Resize(ISVGView* view, double x, double y, double width, double height)
	{
		return Error_NotImplemented;
	}

	long GetResizability()
	{
		return 0;	// Cannot resize
	}
};

}	// LXmlEdit
}
