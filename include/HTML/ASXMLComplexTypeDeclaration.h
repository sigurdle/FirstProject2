#pragma once

class CComplexTypeDefinition :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CTypeDefinition<IASComplexTypeDeclaration>
{
public:
	CComplexTypeDefinition()
	{
		m_deepElement = NULL;
	}

	ILDOMElement* m_deepElement;

	CComObject<CASXMLNamedObjectMap>* m_attributeDecls;

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CComObject<CASXMLNamedObjectMap>::CreateInstance(&m_attributeDecls);
		if (FAILED(hr)) return hr;
		m_attributeDecls->AddRef();

		return 0;
	}

	void FinalRelease()
	{
		if (m_attributeDecls)
		{
			m_attributeDecls->Release();
			m_attributeDecls = NULL;
		}
	}

	STDMETHODIMP GetDefType(BSTR* pVal)
	{
		*pVal = SysAllocString(L"complexType");
		return S_OK;
	}

	STDMETHODIMP BuildDefs();

	void BuildAttributes(ILDOMElement* element);

BEGIN_COM_MAP(CComplexTypeDefinition)
	COM_INTERFACE_ENTRY(IASObject)
	COM_INTERFACE_ENTRY(IASDeclaration)
	COM_INTERFACE_ENTRY(IASDataTypeDeclaration)
	COM_INTERFACE_ENTRY(IASComplexTypeDeclaration)
END_COM_MAP()

// IASObject
	STDMETHOD(get_asNodeType)(/*[out, retval]*/ ASObjectType *pVal)
	{
		ASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;
		*pVal = AS_COMPLEXTYPE_DECLARATION;
		return E_FAIL;
	}

	STDMETHOD(get_nodeName)(/*[out, retval]*/ BSTR *pVal)
	{
		return m_element->getAttribute(L"name", pVal);
	}

//
	STDMETHOD(get_asCM)(/*[out, retval]*/ IASContentModel* *pVal);

	STDMETHOD(get_ASAttributeDecls)(/*[out, retval]*/ IASNamedObjectMap* *pVal)
	{
		ASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;
		*pVal = m_attributeDecls;
		(*pVal)->AddRef();
		return S_OK;
	}

	STDMETHOD(get_attributesList)(/*[out, retval]*/ IASObjectList* *pVal)
	{
		return S_OK;
	}

	STDMETHOD(addASAttributeDecl)(/*[in]*/ IASAttributeDeclaration* attributeDecl);
	STDMETHOD(removeASAttributeDecl)(/*[in]*/ IASAttributeDeclaration* attributeDecl, /*[out,retval]*/ IASAttributeDeclaration** pVal);
};
