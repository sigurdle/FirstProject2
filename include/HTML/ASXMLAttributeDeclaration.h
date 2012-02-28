#pragma once

class CASXMLAttributeDeclaration :
	public CComObjectRootEx<CComSingleThreadModel>,
//	public IASObject,
	public CSchemaNode<IASAttributeDeclaration>
{
public:
//	_bstr_t m_name;
	CArray<_bstr_t, _bstr_t> m_enums;

BEGIN_COM_MAP(CASXMLAttributeDeclaration)
	COM_INTERFACE_ENTRY(IASObject)
	COM_INTERFACE_ENTRY(IASAttributeDeclaration)
END_COM_MAP()

// IASObject
	STDMETHOD(get_asNodeType)(/*[out, retval]*/ ASObjectType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = AS_ATTRIBUTE_DECLARATION;
		return S_OK;
	}

	STDMETHOD(cloneASObject)(/*[in]*/ bool deep, /*[out,retval]*/ IASObject** pVal);

	STDMETHOD(get_localName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(set_localName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_prefix)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(set_prefix)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_nodeName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(set_nodeName)(/*[in]*/ BSTR newVal);

// IASAttributeDeclaration
	STDMETHOD(get_defaultType)(/*[out, retval]*/ ASValueConstraint *pVal);
	STDMETHOD(set_defaultType)(/*[in]*/ ASValueConstraint newVal);
	STDMETHOD(get_enumAttr)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(set_enumAttr)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_dataValue)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(set_dataValue)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_dataType)(/*[out, retval]*/ ASDataType *pVal);
	STDMETHOD(set_dataType)(/*[in]*/ ASDataType newVal);
};
