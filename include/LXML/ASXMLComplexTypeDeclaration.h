#pragma once

namespace System
{
namespace Web
{

class CComplexTypeDefinition :
//	public CTypeDefinition,
	public ASObjectImpl, public IASDeclaration
{
public:
	CTOR CComplexTypeDefinition()
	{
		m_name = nullptr;
//		m_deepElement = NULL;
	}

//	ILDOMElement* m_deepElement;

	CASXMLNamedObjectMap* m_attributeDecls;

	String m_name;

	/*
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
	*/

	String GetDefType()
	{
		return WSTR("complexType");
	}

	ASObjectType get_asNodeType() const
	{
		return AS_COMPLEXTYPE_DECLARATION;
	}

	String get_nodeName()
	{
		return m_name;
	}

	void BuildDefs(Element* element);

	void BuildAttributes(Element* element);

// IASObject
	ASObjectType get_asNodeType()
	{
		return AS_COMPLEXTYPE_DECLARATION;
	}

#if 0
	STDMETHOD(get_nodeName)(/*[out, retval]*/ BSTR *pVal)
	{
		return m_element->getAttribute(L"name", pVal);
	}
#endif

//
	IASContentModel* get_asCM();
	void set_asCM(IASContentModel *newVal)
	{
		ASSERT(0);
	}

	IASNamedObjectMap* get_ASAttributeDecls()
	{
		return m_attributeDecls;
	}

	IASObjectList* get_attributesList()
	{
		return NULL;
	}

	void addASAttributeDecl(IASAttributeDeclaration* attributeDecl);
	IASAttributeDeclaration* removeASAttributeDecl(IASAttributeDeclaration* attributeDecl);
};

}	// Web
}
