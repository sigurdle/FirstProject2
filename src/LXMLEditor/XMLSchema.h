#pragma once

#if 0

class CSchema;
class CContentType;
class CDefinition;
class CElementDefinition;

class CSchemaNode
{
public:
	CSchemaNode()
	{
		m_pSchema = NULL;
		m_element = NULL;
	}

	CSchema* m_pSchema;
	ILDOMElement* m_element;

	virtual void BuildDefs()
	{
	}
};

class CDefList
{
public:
	CSchema* m_pSchema;
	CArray<CDefinition*,CDefinition*> m_defs;

	CElementDefinition* FindElementDefinition(ILDOMElement* element);
};

class CInclude : public CSchemaNode
{
public:
};

class CModelGroup : public CSchemaNode
{
public:
	_bstr_t GetType()
	{
		BSTR btagName;
		m_element->get_tagName(&btagName);
	// TODO, remove prefix if any
		return _bstr_t(btagName, false);
	};

	CDefList m_defs;

	virtual void BuildDefs();
};

class CDefinition : public CSchemaNode
{
public:
	CDefinition()
	{
	}

	virtual _bstr_t GetDefType() = 0;
};

class CTypeDefinition : public CDefinition
{
public:
	CTypeDefinition()
	{
		m_pContent = NULL;
	}

	CContentType* m_pContent;

	_bstr_t GetName()
	{
		if (m_element == NULL)
		{
			return m_name;
		}
		else
		{
			BSTR bname;
			m_element->getAttribute(L"name", &bname);
			_bstr_t name = _bstr_t(bname, false);
			return name;
		}
	}

	_bstr_t m_name;
};

class CSimpleTypeDefinition : public CTypeDefinition
{
public:
	CSimpleTypeDefinition()
	{
	}

	virtual _bstr_t GetDefType()
	{
		return L"simpleType";
	}
};

class CComplexTypeDefinition : public CTypeDefinition
{
public:
	CComplexTypeDefinition()
	{
	}

	virtual _bstr_t GetDefType()
	{
		return L"complexType";
	}

	virtual void BuildDefs();
};

class CGlobalElementDefinition : public CDefinition
{
public:
	CGlobalElementDefinition()
	{
		m_pParentModelGroup = NULL;
		m_pAnynomousTypeDef = NULL;
	}

	CTypeDefinition* m_pAnynomousTypeDef;
	CModelGroup* m_pParentModelGroup;

	CTypeDefinition* GetTypeDefinition();
	_bstr_t GetElementName();

	virtual _bstr_t GetDefType()
	{
		return L"element";
	}

	virtual void BuildDefs();
};

class CElementDefinition : public CDefinition
{
public:
	CElementDefinition()
	{
		m_pParentModelGroup = NULL;
		m_pAnynomousTypeDef = NULL;
	}

	CTypeDefinition* m_pAnynomousTypeDef;
	CModelGroup* m_pParentModelGroup;

	CTypeDefinition* GetTypeDefinition();
	_bstr_t GetElementName();
	bool IsRef();

	int GetMinOccurs();
	DWORD GetMaxOccurs();

	virtual _bstr_t GetDefType()
	{
		return L"element";
	}

	virtual void BuildDefs();
};

class CContentType : public CSchemaNode
{
public:
	_bstr_t m_derivationMethod;
	_bstr_t m_base;

	_bstr_t GetDerivationMethod()
	{
		return m_derivationMethod;
	}

	CTypeDefinition* m_pBaseType;

	CTypeDefinition* GetBaseTypeDef()
	{
		return m_pBaseType;
	}

	virtual void BuildDefs(ILDOMElement* parent) = 0;
};

class CSimpleContentType : public CContentType
{
public:

	virtual void BuildDefs(ILDOMElement* parent)
	{
	}
};

class CComplexContentType : public CContentType
{
public:
	CComplexContentType()
	{
		m_pModelGroup = NULL;
		m_pBaseType = NULL;
	}

	CModelGroup* m_pModelGroup;

	virtual void BuildDefs(ILDOMElement* parent);
};

class CSchema
{
public:
	CDefList m_globalDefs;
	CArray<CSchemaNode*,CSchemaNode*> m_globalElements;

	CArray<IXMLSchemaDocument*,IXMLSchemaDocument*> m_allDocuments;

	_bstr_t m_targetNamespace;
	_bstr_t m_elementFormDefault;
	_bstr_t m_attributeFormDefault;

	_bstr_t GetTargetNamespace()
	{
		return m_targetNamespace;
	/*
		BSTR btargetNamespace;
		m_schemaElement->getAttribute(L"targetNamespace", &btargetNamespace);
		if (btargetNamespace)
			return _bstr_t(btargetNamespace, false);
		else
			return _bstr_t(L"");
			*/
	}

	CTypeDefinition* FindTypeElementByName(ILDOMNode* parent, BSTR btypename);
	CGlobalElementDefinition* FindElementElementByName(ILDOMNode* parent, BSTR btypename);

	CDefinition* CreateDefinition(ILDOMElement* element);
	CDefinition* CreateGlobalDefinition(ILDOMElement* element);

	void AddDocument(IXMLSchemaDocument* document)
	{
		document->AddRef();
		m_allDocuments.Add(document);
	}

	void IncludeSchema(ILDOMElement* mergeDocumentElement);
};
#endif