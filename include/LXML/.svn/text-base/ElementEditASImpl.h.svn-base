#ifndef __LELEMENTEDITASIMPL_H
#define __LELEMENTEDITASIMPL_H

namespace System
{
namespace w3c
{

template<class T> class CLElementEditASImpl/* :
	public ILElementEditAS*/
{
public:
#if 0
	STDMETHOD(getAttributeList)(IASNamedObjectMap** pVal)
	{
		if (pVal == NULL) return E_POINTER;

		*pVal = NULL;

		CComPtr<ILDOMDocument> ownerDocument;
		((ILDOMNode*)static_cast<T*>(this))->get_ownerDocument(&ownerDocument);
		if (ownerDocument)
		{
			CComQIPtr<ILDocumentAS, &IID_ILDocumentAS> documentAS((IUnknown*)ownerDocument);
			if (documentAS)
			{
				CComPtr<IASModel> asModel;
				documentAS->get_activeASModel(&asModel);
				if (asModel)
				{
					CComPtr<IASNamedObjectMap> elementDeclarations;
					asModel->get_elementDeclarations(&elementDeclarations);

					CComBSTR tagName;
					((ILDOMElement*)static_cast<T*>(this))->get_tagName(&tagName);

					CComPtr<IASElementDeclaration> elementDecl;

					elementDeclarations->getNamedItem(tagName, (IASObject**)&elementDecl);
					if (elementDecl)
					{
						elementDecl->get_ASAttributeDecls(pVal);
					}
				}
			}
		}

		return S_OK;
	}

#if 0
	STDMETHOD(getAllowedChildren)(/*[out,retval]*/ IASNamedObjectMap** pVal)
	{
		if (pVal == NULL) return E_POINTER;

		*pVal = NULL;

		CComPtr<ILDOMDocument> ownerDocument;
		static_cast<T*>(this)->get_ownerDocument(&ownerDocument);
		if (ownerDocument)
		{
			CComQIPtr<ILDocumentAS> documentAS = ownerDocument;
			if (documentAS)
			{
				CComQIPtr<IASModel> asModel;
				documentAS->get_activeASModel(&asModel);
				if (asModel)
				{
					CComQIPtr<IASNamedObjectMap> elementDeclarations;
					asModel->get_elementDeclarations(&elementDeclarations);

					CComBSTR tagName;
					static_cast<T*>(this)->get_tagName(&tagName);

					CComQIPtr<IASElementDeclaration> elementDecl;

					elementDeclarations->getNamedItem(tagName, (IASObject**)&elementDecl);
					if (elementDecl)
					{
						CComPtr<IASContentModel> asCM;
						elementDecl->get_asCM(&asCM);

						elementDecl->get_ASAttributeDecls(pVal);
					}
				}
			}
		}
	}
#endif
#endif
};

}	// w3c
}

#endif
