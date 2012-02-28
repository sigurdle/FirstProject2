#ifndef __ASXMLSchemaModelGroup_h__
#define __ASXMLSchemaModelGroup_h__

namespace System
{
namespace Web
{

int GetElementAttributeInteger(Node* node, String name, int defVal);

class CModelGroup :
//	public CSchemaNode,
	public ASObjectImpl, public IASContentModel
{
public:
	CModelGroup()
	{
		m_minOccurs = 1;
		m_maxOccurs = 1;
		m_subModels = new CASXMLObjectList;
	}

#if 0
	_bstr_t GetType()
	{
		BSTR btagName;
		m_element->get_tagName(&btagName);
	// TODO, remove prefix if any
		return _bstr_t(btagName, false);
	}
#endif

	long m_minOccurs;
	long m_maxOccurs;

//	CDefList m_defs;
	CASXMLObjectList* m_subModels;	// TODO

	void BuildDefs(Element* element);

// IASObject
	ASObjectType get_asNodeType() const
	{
		return AS_CONTENTMODEL;
	}

	long get_minOccurs() const
	{
		return m_minOccurs;
	}

	long get_maxOccurs() const
	{
		return m_maxOccurs;
	}

	void set_minOccurs(long newVal)
	{
		ASSERT(0);
	}

	void set_maxOccurs(long newVal)
	{
		ASSERT(0);
	}

	ASContentModelTypeOp m_listOperator;

	ASContentModelTypeOp get_listOperator() const
	{
		return m_listOperator;
	}
	void set_listOperator(ASContentModelTypeOp newVal)
	{
		ASSERT(0);
	}

	String get_nodeName()
	{
		return nullptr;
	}

	IASObjectList* get_subModels()
	{
		return m_subModels;
	}

	virtual void replacesubModel( 
      /* [in] */ IASObject *oldNode,
      /* [in] */ IASObject *newNode)
	{
		ASSERT(0);
	}

#if 0
	STDMETHOD(cloneASObject)(/*[in]*/ bool deep, /*[out,retval]*/ IASObject** pVal);

// IASContentModel
	STDMETHOD(appendsubModel)(/*[in]*/ IASObject* newNode, /*[out,retval]*/ unsigned long* length);
	STDMETHOD(replacesubModel)(/*[in]*/ IASObject* oldNode, /*[in]*/ IASObject* newNode);
	STDMETHOD(insertBeforeSubModel)(/*[in]*/ IASObject* newObject, /*[in]*/ IASObject* refObject, /*[out,retval]*/ IASObject* *pVal);
	STDMETHOD(removeSubModel)(/*[in]*/ IASObject* oldObject);

//////

	STDMETHOD(UpdateElement)()
	{
		if (m_minOccurs == 1)
		{
			m_element->removeAttribute(L"minOccurs");
		}
		else
		{
			WCHAR str[32];
			swprintf(str, L"%d", m_minOccurs);
			m_element->setAttribute(L"minOccurs", str);
		}

		if (m_maxOccurs == 1)	// default, no need for attribute
		{
			m_element->removeAttribute(L"maxOccurs");
		}
		else if (m_maxOccurs == AS_UNBOUNDED)
		{
			m_element->setAttribute(L"maxOccurs", L"unbounded");
		}
		else
		{
			WCHAR str[32];
			swprintf(str, L"%d", m_maxOccurs);
			m_element->setAttribute(L"maxOccurs", str);
		}

		return S_OK;
	}

///////
	STDMETHOD(get_minOccurs)(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;

		if (m_element)
		{
			*pVal = GetElementAttributeInteger(m_element, L"minOccurs", 1);
		}
		else
			*pVal = m_minOccurs;

		return S_OK;
	}

	STDMETHOD(set_minOccurs)(long newVal)
	{
		m_minOccurs = newVal;

		if (m_element)
		{
			if (m_minOccurs == 1)
			{
				m_element->removeAttribute(L"minOccurs");
			}
			else
			{
				WCHAR str[32];
				swprintf(str, L"%d", m_minOccurs);
				m_element->setAttribute(L"minOccurs", str);
			}
		}

		return S_OK;
	}

	STDMETHOD(get_maxOccurs)(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;

		if (m_element)
		{
			CComBSTR val;
			m_element->getAttribute(L"maxOccurs", &val);
			if (val.Length() == 0)
			{
				*pVal = 1;	// default
			}
			else if (!wcscmp(val, L"unbounded"))
			{
				*pVal = AS_UNBOUNDED;
			}
			else
			{
				*pVal = str2int(val);
			}
		}
		else
		{
			*pVal = m_maxOccurs;
		}

		return S_OK;
	}

	STDMETHOD(set_maxOccurs)(long newVal)
	{
		m_maxOccurs = newVal;

		if (m_element)
		{
			if (m_maxOccurs == 1)	// default, no need for attribute
			{
				m_element->removeAttribute(L"maxOccurs");
			}
			else if (m_maxOccurs == AS_UNBOUNDED)
			{
				m_element->setAttribute(L"maxOccurs", L"unbounded");
			}
			else
			{
				WCHAR str[32];
				swprintf(str, L"%d", m_maxOccurs);
				m_element->setAttribute(L"maxOccurs", str);
			}
		}

		return S_OK;
	}

	STDMETHOD(get_listOperator)(ASContentModelTypeOp *pVal);
	STDMETHOD(set_listOperator)(ASContentModelTypeOp newVal);

	STDMETHOD(set_subModels)(IASObjectList* newVal)
	{
		return S_OK;
	}
#endif
};

}	// Web
}

#endif // __ASXMLSchemaModelGroup_h__
