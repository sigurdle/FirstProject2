#pragma once

class CGlobalElementDefinition :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CDefinition<IASElementDeclaration>
{
public:
	CGlobalElementDefinition()
	{
		m_pParentModelGroup = NULL;
		m_pAnynomousTypeDef = NULL;
	}

//	CTypeDefinition* m_pAnynomousTypeDef;
	IASDataTypeDeclaration* m_pAnynomousTypeDef;
	CModelGroup* m_pParentModelGroup;

//	IASDataTypeDeclaration* GetTypeDefinition();
	_bstr_t GetElementName();

	STDMETHOD(get_elementDataType)(/*[out, retval]*/ IASDataTypeDeclaration* *pVal);

	STDMETHODIMP GetDefType(BSTR* pVal)
	{
		*pVal = SysAllocString(L"element");
		return S_OK;
	}

	STDMETHODIMP BuildDefs();

BEGIN_COM_MAP(CGlobalElementDefinition)
	COM_INTERFACE_ENTRY(IASObject)
	COM_INTERFACE_ENTRY(IASDeclaration)
	COM_INTERFACE_ENTRY(IASElementDeclaration)
END_COM_MAP()

// IASObject
	STDMETHOD(get_asNodeType)(/*[out, retval]*/ ASObjectType *pVal)
	{
		ATLASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;
		*pVal = AS_ELEMENT_DECLARATION;
		return E_FAIL;
	}

	STDMETHOD(get_nodeName)(/*[out, retval]*/ BSTR *pVal)
	{
		return m_element->getAttribute(L"name", pVal);
	}

//
	STDMETHOD(get_asCM)(/*[out, retval]*/ IASContentModel* *pVal);

// IASElementDeclaration
	STDMETHOD(get_ASAttributeDecls)(/*[out, retval]*/ IASNamedObjectMap* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;

		CComPtr<IASDataTypeDeclaration> dataType;
		get_elementDataType(&dataType);
		if (dataType)
		{
			CComQIPtr<IASComplexTypeDeclaration> complexType = dataType;
			if (complexType)
			{
				return complexType->get_ASAttributeDecls(pVal);
			}
		}

		return S_OK;
	}

	STDMETHOD(get_attributesList)(/*[out, retval]*/ IASObjectList* *pVal)
	{
		return S_OK;
	}

	STDMETHOD(get_elementType)(/*[out, retval]*/ ASDataType *pVal);
	STDMETHOD(set_elementType)(/*[in]*/ ASDataType newVal);

	STDMETHOD(get_contentType)(/*[out, retval]*/ ASContentModelType *pVal)
	{
		return S_OK;
	}
	STDMETHOD(set_contentType)(/*[in]*/ ASContentModelType newVal)
	{
		return S_OK;
	}
	STDMETHOD(removeASAttributeDecl)(/*[in]*/ IASAttributeDeclaration* attributeDecl, /*[out,retval]*/ IASAttributeDeclaration** pVal)
	{
		return S_OK;
	}
	STDMETHOD(addASAttributeDecl)(/*[in]*/ IASAttributeDeclaration* attributeDecl)
	{
		return S_OK;
	}
	STDMETHOD(get_strictMixedContent)(/*[out, retval]*/ bool *pVal)
	{
		return S_OK;
	}
	STDMETHOD(set_strictMixedContent)(/*[in]*/ bool newVal)
	{
		return S_OK;
	}
	STDMETHOD(get_isPCDataOnly)(/*[out, retval]*/ bool *pVal)
	{
		return S_OK;
	}
	STDMETHOD(set_isPCDataOnly)(/*[in]*/ bool newVal)
	{
		return S_OK;
	}
	STDMETHOD(get_systemId)(/*[out, retval]*/ BSTR *pVal)
	{
		return S_OK;
	}
	STDMETHOD(set_systemId)(/*[in]*/ BSTR newVal)
	{
		return S_OK;
	}
};
