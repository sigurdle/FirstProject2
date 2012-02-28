#include "stdafx.h"
#include "LXML2.h"

#include "ElementEditVALImpl.h"

#include "DOMError.h"
#include "DOMLocator.h"

namespace System
{
namespace Web
{

DOMError* CreateDOMError(DOMErrorSeverity severity, System::StringW* message, IDOMLocator* location);

#if 0
HRESULT CreateDOMLocator(long offset, BSTR msg, ILDOMLocator* *pLocator)
{
	CComObject<CLDOMLocator>* locator;
	CComObject<CLDOMLocator>::CreateInstance(&locator);
	if (locator)
	{
		locator->m_offset = offset;
		//locator->m_lineNumber = 0;
		//locator->m_columnNumber = 0;

		(*pLocator = locator)->AddRef();
	}

	return S_OK;
}
#endif

#if 0
#include "DOMError.h"

HRESULT CreateDOMError(long offset, BSTR msg, ILDOMError* *pError)
{
	CComObject<CLDOMError>* error;
	CComObject<CLDOMError>::CreateInstance(&error);
	if (error)
	{
		
		locator->m_offset = offset;
		//locator->m_lineNumber = 0;
		//locator->m_columnNumber = 0;

		(*pLocator = locator)->AddRef();
	}

	return S_OK;
}
#endif

bool ElementEditVAL::isNodeValid(Element* element, bool deep, CheckTypeVAL wFValidityCheckLevel)
{
	Document* ownerDocument = element->get_ownerDocument();

	VERIFY(0);

#if 0
	CComPtr<ILDOMErrorHandler> errorHandler;
	ownerDocument->get_errorHandler(&errorHandler);

	CComQIPtr<ILDocumentAS> documentAS = ownerDocument;

	CComPtr<IASModel> asModel;
	documentAS->get_activeASModel(&asModel);

	if (asModel)
	{
		CComQIPtr<IASNamedObjectMap> elementDeclarations;
		asModel->get_elementDeclarations(&elementDeclarations);

		CComBSTR tagName;
		element->get_tagName(&tagName);

		CComQIPtr<IASElementDeclaration> elementDecl;

		elementDeclarations->getNamedItem(tagName, (IASObject**)&elementDecl);
		if (elementDecl)
		{
			CComPtr<IASNamedObjectMap> attributeDecls;
			elementDecl->get_ASAttributeDecls(&attributeDecls);

			NamedNodeMap* attributes = element->get_attributes();

			{
				long nattributes = attributes->get_length();
				for (int i = 0; i < nattributes; i++)
				{
					Attr* attr = dynamic_cast<Attr*>(attributes->item(i));

					CComBSTR name;
					attr->get_name(&name);

					CComPtr<IASAttributeDeclaration> attrDecl;

					attributeDecls->getNamedItem(name, (IASObject**)&attrDecl);

					if (attrDecl == NULL)
					{
						WCHAR msg[512];
						swprintf(msg, L"Undeclared Attribute %s", (BSTR)name);

						long offset;
						attr->getTextOffset(1, &offset);

						VARIANT_BOOL bContinue;
						errorHandler->handleError(
							CreateDOMError(LSEVERITY_ERROR, msg,
							ownerDocument->CreateDOMLocator(-1, -1, offset)), &bContinue);

						/*
						CComPtr<ILDOMLocator> locator;
						CreateDOMLocator(offset, msg, &locator);
						errorHandler->error(locator, NULL, msg);
						*/
					}
				}
			}

			{
				long nattrdecls;
				attributeDecls->get_length(&nattrdecls);

				for (int i = 0; i < nattrdecls; i++)
				{
					CComPtr<IASAttributeDeclaration> attrDecl;
					attributeDecls->item(i, (IASObject**)&attrDecl);

					ASValueConstraint defaultType;
					attrDecl->get_defaultType(&defaultType);

					CComBSTR name;
					attrDecl->get_nodeName(&name);

					if (defaultType == REQUIRED_VC)
					{
						CComPtr<ILDOMAttr> attr;
						attributes->getNamedItem(name, (ILDOMNode**)&attr);

						if (attr == NULL)
						{
							WCHAR msg[512];
							swprintf(msg, L"Missing required attribute '%s' on '%s' element", (BSTR)name, (BSTR)tagName);

							long offset;
							element->getTextOffset(3, &offset);

							VARIANT_BOOL bContinue;
							errorHandler->handleError(
								CreateDOMError(LSEVERITY_ERROR, msg,
								CComQIPtr<CLDOMDocumentImplImpl>(ownerDocument)->CreateDOMLocator(-1, -1, offset)), &bContinue);
						}
					}
				}
			}
		}
		else
		{
			WCHAR msg[512];
			swprintf(msg, L"Undeclared element '%s'", (BSTR)tagName);

			long offset;
			element->getTextOffset(1, &offset);

			VARIANT_BOOL bContinue;
			errorHandler->handleError(
				CreateDOMError(LSEVERITY_ERROR, msg,
				CComQIPtr<CLDOMDocumentImplImpl>(ownerDocument)->CreateDOMLocator(-1, -1, offset)), &bContinue);
		}
	}
#endif

	return false;
}

}	// Web
}
