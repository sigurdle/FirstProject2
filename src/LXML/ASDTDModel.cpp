#include "stdafx.h"
#include "LXML2.h"

#include "ASDTDModel.h"

#include "DTDDocument.h"
#include "LDTDElement.h"
#include "DTDParser.h"

#include "ASDTDEntity.h"
#include "ASDTDElement.h"
#include "ASDTDAttribute.h"
#include "ASDTDContentModel.h"

namespace System
{
namespace Web
{

ASDTDModel::ASDTDModel()
{
	m_entityDeclarations = new CDTDASNamedObjectMap;
	m_elementDeclarations = new CDTDASNamedObjectMap;
	m_attributeDeclarations = new CDTDASNamedObjectMap;

//	m_errorHandler = this;
}

ASDTDModel::~ASDTDModel()
{
	/*
	if (m_entityDeclarations)
	{
		m_entityDeclarations->Release();
		m_entityDeclarations = NULL;
	}

	if (m_elementDeclarations)
	{
		m_elementDeclarations->Release();
		m_elementDeclarations = NULL;
	}

	if (m_attributeDeclarations)
	{
		m_attributeDeclarations->Release();
		m_attributeDeclarations = NULL;
	}
	*/
}

void ASDTDModel::BuildFromDTDDocument(DTDDocument* dtd)
{
	for (size_t i = 0; i < dtd->m_entityList.GetSize(); i++)
	{
		CEntity* pEntity = dtd->m_entityList[i];

		if (pEntity->m_c == 0)
		{
			ASSERT(0);
			CASDTDEntity* pASDTDEntity = NULL;//new CASDTDEntity;
		
			pASDTDEntity->m_name = pEntity->m_name;
			pASDTDEntity->m_value = pEntity->m_value;

			m_entityDeclarations->m_items.Add(pASDTDEntity);
		}
	}

	for (size_t i = 0; i < dtd->m_elementList.GetSize(); i++)
	{
		CLDTDElement* pElement = dtd->m_elementList[i];

		//ATLTRACE("<ELEMENT %S>\n", (BSTR)pElement->m_name);

		ASSERT(0);
		CASDTDElement* pASDTDElement = NULL;//new CASDTDElement;

#if 0
		pElement->m_pASElement = pASDTDElement;
#endif

		pASDTDElement->m_ownerASModel = this;
		//pASDTDElement->m_ownerDTDElement = pElement;

		pASDTDElement->m_name = pElement->m_name;
		pASDTDElement->m_ns = pElement->m_ns;
		pASDTDElement->m_contentType = pElement->m_contentType;
	//	pASDTDElement->m_isPCDataOnly = pElement->m_isPCDataOnly;

		m_elementDeclarations->m_items.Add(pASDTDElement);

		/*
		When more than one AttlistDecl is provided for a given element type,
		the contents of all those provided are merged. When more than one
		definition is provided for the same attribute of a given element type,
		the first declaration is binding and later declarations are ignored.
		For interoperability, writers of DTDs may choose to provide at most one
		attribute-list declaration for a given element type, at most one
		attribute definition for a given attribute name in an attribute-list
		declaration, and at least one attribute definition in each attribute-list
		declaration. For interoperability, an XML processor may at user option
		issue a warning when more than one attribute-list declaration is provided
		for a given element type, or more than one attribute definition is provided
		for a given attribute, but this is not an error.
		*/

		for (size_t j = 0; j < dtd->m_attlistList.GetSize(); j++)
		{
			CAttlist* pAttlist = dtd->m_attlistList[j];

			if (pElement->m_ns == pAttlist->m_ns && pElement->m_name == pAttlist->m_name)
			{
				for (size_t i = 0; i < pAttlist->m_attributes.GetSize(); i++)
				{
					CAttribute* pAtt = pAttlist->m_attributes[i];

					IASObject* object = pASDTDElement->m_attributeDecls->getNamedItem(pAtt->m_name);
					if (object == NULL)
					{
						ASSERT(0);
						CASDTDAttribute* pASDTDAttribute = NULL;//new CASDTDAttribute;

						pASDTDAttribute->m_name = pAtt->m_name;
						pASDTDAttribute->m_value = pAtt->m_value;
						pASDTDAttribute->m_defaultType = pAtt->m_defaultType;

						for (size_t en = 0; en < pAtt->m_enums.GetSize(); en++)
						{
							pASDTDAttribute->m_enums.Add(pAtt->m_enums[en]);
						}

						pASDTDElement->m_attributeDecls->m_items.Add(pASDTDAttribute);
					}
				}
			}
		}
	}

	for (size_t i = 0; i < dtd->m_elementList.GetSize(); i++)
	{
		CLDTDElement* pElement = dtd->m_elementList[i];

		CASDTDElement* pASDTDElement = (CASDTDElement*)m_elementDeclarations->m_items[i];

		if (pElement->m_pCPChoiceSeq)
		{
			pASDTDElement->m_asCM = BuildCM(pElement->m_pCPChoiceSeq);
			pASDTDElement->m_asCM->m_ownerElement = pASDTDElement;
			ASSERT(pASDTDElement->m_asCM != NULL);
		}
	}
}

#if 0
// IASModel
STDMETHODIMP ASDTDModel::createASContentModel(/*[in]*/ unsigned long minOccurs, /*[in]*/ unsigned long maxOccurs, /*[in]*/ ASContentModelTypeOp listOperator, /*[out,retval]*/ IASContentModel** pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CASDTDContentModel>* pContentModel;
	HRESULT hr = CComObject<CASDTDContentModel>::CreateInstance(&pContentModel);
	if (SUCCEEDED(hr))
	{
		pContentModel->AddRef();

		pContentModel->m_minOccurs = minOccurs;
		pContentModel->m_maxOccurs = maxOccurs;
		pContentModel->m_listOperator = listOperator;

		*pVal = pContentModel;
	}
	else
	{
		*pVal = NULL;
	}

	return S_OK;
}

STDMETHODIMP ASDTDModel::createASEntityDeclaration(/*[in]*/ BSTR name, /*[out,retval]*/ IASEntityDeclaration** pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CASDTDEntity>* pEntity;
	CComObject<CASDTDEntity>::CreateInstance(&pEntity);
	pEntity->AddRef();

	pEntity->m_name = name;

	*pVal = pEntity;

	return S_OK;
}

STDMETHODIMP ASDTDModel::createASNotationDeclaration(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[in]*/ BSTR systemId, /*[in]*/ BSTR publicId, /*[out,retval]*/ IASNotationDeclaration** pVal)
{
	return E_FAIL;
}

STDMETHODIMP ASDTDModel::createASAttributeDeclaration(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[out,retval]*/ IASAttributeDeclaration** pVal)
{
	return E_FAIL;
}

STDMETHODIMP ASDTDModel::createASElementDeclaration(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[out,retval]*/ IASElementDeclaration** pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CASDTDElement>* pElement;
	CComObject<CASDTDElement>::CreateInstance(&pElement);
	pElement->AddRef();

	pElement->m_pASModel = this;
	pElement->m_ns = namespaceURI;	// FIX
	pElement->m_name = name;

	*pVal = pElement;

	return S_OK;
}
#endif

IASNamedObjectMap* ASDTDModel::get_contentModelDeclarations()
{
	return NULL;
}

IASNamedObjectMap* ASDTDModel::get_entityDeclarations()
{
	return m_entityDeclarations;
}

IASNamedObjectMap* ASDTDModel::get_notationDeclarations()
{
	return NULL;
}

IASNamedObjectMap* ASDTDModel::get_attributeDeclarations()
{
	return m_attributeDeclarations;
}

IASNamedObjectMap* ASDTDModel::get_elementDeclarations()
{
	return m_elementDeclarations;
}

bool ASDTDModel::get_isNamespaceAware() const
{
	return false;
}

CASDTDContentModel* ASDTDModel::BuildCM(CCPChoiceSeq* cp)
{
	ASSERT(0);
	CASDTDContentModel* pCM = NULL;//new CASDTDContentModel;

	pCM->m_listOperator = cp->m_listOperator;
	pCM->m_minOccurs = cp->m_minOccurs;
	pCM->m_maxOccurs = cp->m_maxOccurs;

	CDTDASObjectList* pCMSubModels = pCM->m_subModels;
	ASSERT(pCMSubModels != NULL);

	for (size_t i = 0; i < cp->m_children.GetSize(); ++i)
	{
		CCP* pCP = cp->m_children[i];
		if (pCP->m_type == 1)
		{
			CCPElement* pCPElement = (CCPElement*)pCP;
			IASObject* pObject = m_elementDeclarations->getNamedItem(pCPElement->m_name);
			if (pObject)
			{
				pCMSubModels->m_items.Add(pObject);
			}
		}
		else if (pCP->m_type == 2)
		{
			CCPChoiceSeq* pCPChoiceSeq = (CCPChoiceSeq*)pCP;
			CASDTDContentModel* pCMSub = BuildCM(pCPChoiceSeq);	// Recurse

			pCMSubModels->m_items.Add(pCMSub);
		}
		else
			ASSERT(0);
	}

	return pCM;
}

#if 0
STDMETHODIMP ASDTDModel::load(BSTR pathName, bool *pSuccess)
{
	ASSERT(pSuccess != NULL);
	if (pSuccess == NULL) return E_POINTER;

	*pSuccess = VARIANT_FALSE;

	m_url = pathName;

//	m_textDoc.CoCreateInstance(CLSID_TextData);
	m_textDoc.CoCreateInstance(OLESTR("TextDataMod.TextData"));

	if (SUCCEEDED(m_textDoc->load(pathName)))
	{
		parse(pSuccess);
	}

	return S_OK;
}

STDMETHODIMP ASDTDModel::get_errorHandler(IUnknown **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_errorHandler;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP ASDTDModel::set_errorHandler(IUnknown *newVal)
{
	m_errorHandler = newVal;
	return S_OK;
}

STDMETHODIMP ASDTDModel::get_sourceTextDoc(IUnknown **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_textDoc;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP ASDTDModel::set_sourceTextDoc(IUnknown *newVal)
{
	m_textDoc = newVal;
	return S_OK;
}

STDMETHODIMP ASDTDModel::saveAsText(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComBSTR text = OLESTR("");

	for (int i = 0; i < m_elementDeclarations->m_items.GetSize(); i++)
	{
		CASDTDElement* pElement = (CASDTDElement*)m_elementDeclarations->m_items[i];

		text += pElement->GetAsText();

		if (pElement->m_attributeDecls->m_items.GetSize() > 0)
		{
			text += OLESTR("<!ATTLIST ");
			text += pElement->m_name;
			text += OLESTR(" ");

			for (int j = 0; j < pElement->m_attributeDecls->m_items.GetSize(); j++)
			{
				CASDTDAttribute* pAttribute = (CASDTDAttribute*)pElement->m_attributeDecls->m_items[j];

				text += pAttribute->m_name;
				text += OLESTR("\n");
			}

			text += OLESTR(">\n");
		}
	}

	*pVal = text.Detach();

	return S_OK;
}

STDMETHODIMP ASDTDModel::FireModelChanged()
{
#if 0
	Fire_ModelChanged();
#endif
	return S_OK;
}

STDMETHODIMP ASDTDModel::parse(bool *pSuccess)
{
	if (pSuccess == NULL) return E_POINTER;

	if (m_textDoc == NULL)
	{
		TRACE("\nASDTDModel::parse - m_textDoc == NULL\n\n");
		return E_FAIL;
	}

	*pSuccess = VARIANT_FALSE;

	{
		for (int i = 0; i < m_elementDeclarations->m_items.GetSize(); i++)
		{
			m_elementDeclarations->m_items[i]->Release();
		}
		m_elementDeclarations->m_items.RemoveAll();
	}

	ASSERT(0);
#if 0
	CComObject<CDTDParser>* parser;
	CComObject<CDTDParser>::CreateInstance(&parser);
	if (parser)
	{
		parser->AddRef();

		//parser->m_url = url;

		m_textDoc->get_data(&parser->m_textData);
		parser->m_errorHandler = m_errorHandler;

		try
		{
			parser->Parse();

			*pSuccess = VARIANT_TRUE;
		}
		catch(WCHAR* msg)
		{
			WCHAR emsg[1024];
			swprintf(emsg, L"%s\noffset: %d\nline: %d", msg, parser->m_fpos, parser->m_line+1);
			TRACE(L"DTD Error parsing: %s\n", emsg);
			::MessageBox(NULL, _bstr_t(emsg), "DTD", MB_OK);
		}

#if 0
		int i;

		for (i = 0; i < parser->m_elementList.GetSize(); i++)
		{
			CElement* pElement = parser->m_elementList[i];

			CComObject<CDTDElement>* pDTDElement;
			CComObject<CDTDElement>::CreateInstance(&pDTDElement);
			pDTDElement->AddRef();

			pDTDElement->m_name = pElement->m_name;
			pDTDElement->m_ns = pElement->m_ns;
			pDTDElement->m_contentType = pElement->m_contentType;
			pDTDElement->m_isPCDataOnly = pElement->m_isPCDataOnly;

			m_elementDeclarations->m_items.Add(pDTDElement);

			CAttlist* pAttlist = parser->GetAttlistByName(pElement->m_ns, pElement->m_name);
			if (pAttlist)
			{
				for (int i = 0; i < pAttlist->m_attributes.GetSize(); i++)
				{
					CAttribute* pAtt = pAttlist->m_attributes[i];

					CComObject<CDTDAttribute>* pDTDAttribute;
					CComObject<CDTDAttribute>::CreateInstance(&pDTDAttribute);
					pDTDAttribute->AddRef();

					pDTDAttribute->m_name = pAtt->m_name;
					for (int en = 0; en < pAtt->m_enums.GetSize(); en++)
					{
						pDTDAttribute->m_enums.Add(pAtt->m_enums[en]);
					}

					pDTDElement->m_attributeDecls->m_items.Add(pDTDAttribute);
				}
			}
		}

		for (i = 0; i < parser->m_elementList.GetSize(); i++)
		{
			CElement* pElement = parser->m_elementList[i];

			CComObject<CDTDElement>* pDTDElement = (CComObject<CDTDElement>*)m_elementDeclarations->m_items[i];

			if (pElement->m_pCPChoiceSeq)
			{
				pDTDElement->m_asCM = BuildCM(pElement->m_pCPChoiceSeq);
				ASSERT(pDTDElement->m_asCM != NULL);
			}
		}
#endif

		parser->Release();
	}
#endif

	return S_OK;
}

#endif

}	// Web
}
