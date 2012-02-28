#include "stdafx.h"
#include "LXML2.h"

#include "ASDTDElement.h"
#include "ASDTDModel.h"
#include "ASDTDContentModel.h"

namespace System
{
namespace Web
{

	IASModel* CASDTDObject::get_ownerASModel()
{
	return m_ownerASModel;
}

	///

CASDTDElement::CASDTDElement()
{
//	m_ownerDTDElement = NULL;

	m_asCM = NULL;
	m_contentType = (ASContentModelType)0;	// Undefined
	m_attributeDecls = new CDTDASNamedObjectMap;
}

CASDTDElement::~CASDTDElement()
{
}

/*
int CASDTDElement::FinalConstruct()
{
	HRESULT hr;

	hr = CComObject<CDTDASNamedObjectMap>::CreateInstance(&m_attributeDecls);
	if (FAILED(hr)) return hr;
	m_attributeDecls->AddRef();

	return S_OK;
}

void CASDTDElement::FinalRelease()
{
	if (m_asCM)
	{
		m_asCM->Release();
		m_asCM = NULL;
	}

	if (m_attributeDecls)
	{
		m_attributeDecls->Release();
		m_attributeDecls = NULL;
	}
}
*/

IASContentModel* CASDTDElement::get_asCM()
{
	return m_asCM;
}

void CASDTDElement::set_asCM(IASContentModel *newVal)
{
	IASContentModel* asCM = m_asCM;
	if (asCM)
	{
	//	asCM->AddRef();
	//	m_asCM->Release();
	}

	m_asCM = (CASDTDContentModel*)newVal;
}

IASNamedObjectMap* CASDTDElement::get_ASAttributeDecls()
{
	return m_attributeDecls;
}

#if 0
STDMETHODIMP CASDTDElement::set_ASAttributeDecls(IASNamedObjectMap *newVal)
{
	IASNamedObjectMap* attributeDecls = m_attributeDecls;
	if (attributeDecls)
	{
		attributeDecls->AddRef();
		m_attributeDecls->Release();
	}

	m_attributeDecls = (CComObject<CDTDASNamedObjectMap>*)newVal;

	if (m_attributeDecls)
	{
		m_attributeDecls->AddRef();
	}

	return S_OK;
}
#endif

String CASDTDElement::get_systemId()
{
	return nullptr;//sysstring();
}

void CASDTDElement::set_systemId(StringIn newVal)
{
	ASSERT(0);
	//return S_OK;
}

/*
bool CASDTDElement::get_isPCDataOnly()
{
	return m_isPCDataOnly;
}

STDMETHODIMP CASDTDElement::set_isPCDataOnly(bool newVal)
{
	m_isPCDataOnly = newVal;
	return S_OK;
}
*/

bool CASDTDElement::get_strictMixedContent() const
{
	return false;	// This is constant for DTD
}

void CASDTDElement::set_strictMixedContent(bool newVal)
{
	VERIFY(0);
	//return E_FAIL;// ?? Should user be able to set this ??
}

void CASDTDElement::addASAttributeDecl(IASAttributeDeclaration *attributeDecl)
{
	VERIFY(0);
}

IASAttributeDeclaration* CASDTDElement::removeASAttributeDecl(IASAttributeDeclaration *attributeDecl)
{
	VERIFY(0);
	return NULL;
}

ASContentModelType CASDTDElement::get_contentType()
{
	return m_contentType;
}

void CASDTDElement::set_contentType(ASContentModelType newVal)
{
	m_contentType = newVal;
	//return S_OK;
}

ASDataType CASDTDElement::get_elementType() const
{
	// TODO: Add your implementation code here
	ASSERT(0);
	return COMPLEX_DATATYPE;
}

void CASDTDElement::set_elementType(ASDataType newVal)
{
	// TODO: Add your implementation code here

	ASSERT(0);

	//return S_OK;
}

#if 0
void CASDTDElement::OnChanged(CASDTDContentModel* pCM)
{
// TODO, other solution here?

// (this way forces a rebuild of the text in sourceview)

	m_ownerDTDElement->GetUnknown()->AddRef();	// Make sure we don't lose it

	CComPtr<ILDOMNode> parentNode;
	m_ownerDTDElement->get_parentNode(&parentNode);

	CComPtr<ILDOMNode> nextSibling;
	m_ownerDTDElement->get_nextSibling(&nextSibling);

// Remove it
	CComPtr<ILDOMNode> p;
	parentNode->removeChild(m_ownerDTDElement, &p);

// Reinsert it
	parentNode->insertBefore(m_ownerDTDElement, CComVariant(nextSibling), NULL);

	m_ownerDTDElement->GetUnknown()->Release();
}
#endif

#if 0
CComBSTR CASDTDElement::GetAsText()
{
	CComBSTR text = OLESTR("");

	text += OLESTR("<!ELEMENT ");
	if (m_name != NULL)
		text += m_name;
	text += OLESTR(" ");

	if (m_contentType == ELEMENT_CONTENTTYPE)
	{
		ASSERT(m_asCM);

		text += m_asCM->GetAsText();
	}
	else if (m_contentType == MIXED_CONTENTTYPE)
	{
		text += OLESTR("(");

		text += OLESTR("#PCDATA");

		text += OLESTR(")");
	}
	else if (m_contentType == EMPTY_CONTENTTYPE)
	{
		text += OLESTR("EMPTY");
	}
	else if (m_contentType == ANY_CONTENTTYPE)
	{
		text += OLESTR("ANY");
	}
	else
		ASSERT(0);

	text += OLESTR(">\n");

	return text;
}
#endif

}	// Web
}
