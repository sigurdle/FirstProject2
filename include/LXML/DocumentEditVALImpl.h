#ifndef __DOCUMENTEDITVALIMPL_H__
#define __DOCUMENTEDITVALIMPL_H__

#include "NodeEditVALImpl.h"

#include "NameList.h"

namespace System
{
namespace Web
{

template <class T> class DocumentEditVALImpl :
	public NodeEditVALImpl<T>
{
public:
	CTOR DocumentEditVALImpl()
	{
		m_continuousValidityChecking = false;
		m_definedElementTypes = NULL;
	}

	~DocumentEditVALImpl()
	{
		ASSERT(m_definedElementTypes == NULL);
	}

	/*
	int FinalConstruct()
	{
		return 0;
	}

	void FinalRelease()
	{
		if (m_definedElementTypes)
		{
		//	m_definedElementTypes->Release();
			m_definedElementTypes = NULL;
		}
	}
	*/

	bool get_continuousValidityChecking() const
	{
		return m_continuousValidityChecking;
	}

	void set_continuousValidityChecking(/*[in]*/ bool newVal)
	{
		// TODO
		m_continuousValidityChecking = newVal;
	}

	const NameList* getDefinedElementTypes()
	{
		ASSERT(0);
#if 0
		if (m_definedElementTypes == NULL)
		{
			CComObject<CLDOMNameList>::CreateInstance(&m_definedElementTypes);
			m_definedElementTypes->AddRef();

			CComQIPtr<ILDocumentAS, &IID_ILDocumentAS> documentAS(static_cast<T*>(this));

			CComPtr<IASModel> asModel;
			documentAS->get_activeASModel(&asModel);
			if (asModel)
			{
				CComPtr<IASNamedObjectMap> elementDeclarations;
				asModel->get_elementDeclarations(&elementDeclarations);

				long length;
				elementDeclarations->get_length(&length);

				for (int i = 0; i < length; i++)
				{
					CComPtr<IASElementDeclaration> elementDecl;
					elementDeclarations->item(i, (IASObject**)&elementDecl);

					CLDOMNameList::CNameItem item;
					elementDecl->get_nodeName(&item.m_name);

					m_definedElementTypes->m_items.Add(item);
				}
			}
		}
#endif

		return m_definedElementTypes;
	}

public:

	NameList* m_definedElementTypes;
	bool m_continuousValidityChecking;
};

}	// Web
}

#endif // __DOCUMENTEDITVALIMPL_H__
