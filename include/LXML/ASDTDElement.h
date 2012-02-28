#ifndef __ASDTDELEMENT_H_
#define __ASDTDELEMENT_H_

#include "ASDTDObjectImpl.h"

namespace System
{
namespace Web
{

class CLDTDElement;

class ASDTDModel;
//class CDTDCPChoiceSeq;

class CASDTDContentModel;
class CDTDASNamedObjectMap;

class WEBEXT CASDTDElement :
	public CASDTDObject, public IASElementDeclaration
{
public:
	CASDTDElement();
	~CASDTDElement();

//	int FinalConstruct();
//	void FinalRelease();

//	CASDTDModel* m_pASModel;

	String m_ns;
	String m_name;

	ASContentModelType m_contentType;
//	bool m_isPCDataOnly;
	CASDTDContentModel* m_asCM;

	CDTDASNamedObjectMap* m_attributeDecls;

	CLDTDElement* m_ownerDTDElement;

	void BuildDefs()
	{
	}

//	void OnChanged(CASDTDContentModel* pCM);
//	CComBSTR GetAsText();

public:
	ASDataType get_elementType() const;
	void set_elementType(ASDataType newVal);
	ASContentModelType get_contentType();
	void set_contentType(/*[in]*/ ASContentModelType newVal);
	IASAttributeDeclaration* removeASAttributeDecl(/*[in]*/ IASAttributeDeclaration* attributeDecl);
	void addASAttributeDecl(/*[in]*/ IASAttributeDeclaration* attributeDecl);
	bool get_strictMixedContent() const;
	void set_strictMixedContent(bool newVal);
//	bool get_isPCDataOnly();
//	STDMETHOD(set_isPCDataOnly)(/*[in]*/ bool newVal);
	String get_systemId();
	void set_systemId(StringIn newVal);
	IASNamedObjectMap* get_ASAttributeDecls();
	IASContentModel* get_asCM();
	void set_asCM(IASContentModel* newVal);
	IASDataTypeDeclaration* get_elementDataType()
	{
		ASSERT(0);
		return NULL;
	}

	IASObjectList* get_attributesList()
	{
		return NULL;
	}

// IASObject
	void set_ownerASModel(IASModel* newVal)
	{
		VERIFY(0);
	}
	IASObject* cloneASObject(bool deep) const
	{
		ASSERT(0);
		return NULL;
	}

#if 0
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
#endif
	String get_nodeName()
	{
		return m_name;
	}

	void set_nodeName(StringIn newVal)
	{
		m_name = newVal;
	}

	ASObjectType get_asNodeType() const
	{
		return AS_ELEMENT_DECLARATION;
	}

#if 0
	STDMETHOD(GetDefType)(/*[out,retval]*/ BSTR* pVal)
	{
		return S_OK;
	}
#endif
};

}	// Web
}

#endif	// __ASDTDELEMENT_H_
