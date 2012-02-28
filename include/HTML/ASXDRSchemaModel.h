#ifndef __ASXDRSCHEMAMODEL_H_
#define __ASXDRSCHEMAMODEL_H_

//#include "resource.h"       // main symbols

class CASXDRSchemaModel : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CASXDRSchemaModel, &CLSID_ASXDRSchemaModel>,
	public IASXDRSchemaModel
{
public:
	CASXDRSchemaModel()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ASXDRSCHEMAMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CASXDRSchemaModel)
	COM_INTERFACE_ENTRY(IASModel)
	COM_INTERFACE_ENTRY(IASXDRSchemaModel)
END_COM_MAP()

// IASXDRSchemaModel
public:

// IASObject
	STDMETHOD(get_ownerASModel)(/*[out, retval]*/ IASModel* *pVal)
	{
		return E_FAIL;
	}

	STDMETHOD(set_ownerASModel)(/*[in]*/ IASModel* newVal)
	{
		return E_FAIL;
	}

	STDMETHOD(cloneASObject)(/*[in]*/ bool deep, /*[out,retval]*/ IASObject** pVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(get_localName)(/*[out, retval]*/ BSTR *pVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(set_localName)(/*[in]*/ BSTR newVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(get_prefix)(/*[out, retval]*/ BSTR *pVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(set_prefix)(/*[in]*/ BSTR newVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(get_nodeName)(/*[out, retval]*/ BSTR *pVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(put_nodeName)(/*[in]*/ BSTR newVal)
	{
		return E_FAIL;
	}

	STDMETHOD(get_asNodeType)(/*[out, retval]*/ ASObjectType *pVal)
	{
		*pVal = AS_MODEL;
		return S_OK;
	}

	STDMETHOD(setUserData)(/*[in]*/ BSTR key, /*[in]*/ IUnknown* data, /*[in]*/ IASUserDataHandler* handler, /*[out,retval]*/ IUnknown* *pVal)
	{
		return S_OK;
	}
	STDMETHOD(getUserData)(/*[in]*/ BSTR key, /*[out,retval]*/ IUnknown* *pVal)
	{
		return S_OK;
	}

// IASModel
	STDMETHOD(GetElement)(/*[out,retval]*/ ILDOMElement* *pVal)
	{
		return S_OK;
	}
	STDMETHOD(SetElement)(/*[in]*/ ILDOMElement* newVal)
	{
		return S_OK;
	}

	STDMETHOD(getASModels)(/*[out,retval]*/ IASObjectList* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;//m_asModels;
		//(*pVal)->AddRef();
		return S_OK;
	}

	STDMETHOD(FireModelChanged)()
	{
		return S_OK;
	}

	STDMETHOD(createASContentModel)(/*[in]*/ unsigned long minOccurs, /*[in]*/ unsigned long maxOccurs, /*[in]*/ ASContentModelTypeOp Operator, /*[out,retval]*/ IASContentModel** pVal)
	{
		return S_OK;
	}

	STDMETHOD(createASEntityDeclaration)(/*[in]*/ BSTR name, /*[out,retval]*/ IASEntityDeclaration** pVal)
	{
		return S_OK;
	}
	STDMETHOD(createASNotationDeclaration)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[in]*/ BSTR systemId, /*[in]*/ BSTR publicId, /*[out,retval]*/ IASNotationDeclaration** pVal)
	{
		return S_OK;
	}

	STDMETHOD(createASAttributeDeclaration)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[out,retval]*/ IASAttributeDeclaration** pVal)
	{
		return S_OK;
	}

	STDMETHOD(createASElementDeclaration)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[out,retval]*/ IASElementDeclaration** pVal)
	{
		return S_OK;
	}

	STDMETHOD(get_contentModelDeclarations)(/*[out, retval]*/ IASNamedObjectMap* *pVal)
	{
		return S_OK;
	}

	STDMETHOD(get_entityDeclarations)(/*[out, retval]*/ IASNamedObjectMap* *pVal)
	{
		return S_OK;
	}

	STDMETHOD(get_notationDeclarations)(/*[out, retval]*/ IASNamedObjectMap* *pVal)
	{
		return S_OK;
	}

	STDMETHOD(get_attributeDeclarations)(/*[out, retval]*/ IASNamedObjectMap* *pVal)
	{
		return S_OK;
	}

	STDMETHOD(get_elementDeclarations)(/*[out, retval]*/ IASNamedObjectMap* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
//		*pVal = m_globalElements;
//		(*pVal)->AddRef();
		return S_OK;
	}

	STDMETHOD(get_isNamespaceAware)(/*[out, retval]*/ bool *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = VARIANT_TRUE;
		return S_OK;
	}
};

#endif //__ASXDRSCHEMAMODEL_H_
