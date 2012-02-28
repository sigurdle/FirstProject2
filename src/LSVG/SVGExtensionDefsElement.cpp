#include "stdafx.h"
#include "LSVG2.h"
#include "SVGExtensionDefsElement.h"

namespace System
{
namespace Web
{

SVGElementDefElement* SVGExtensionDefsElement::GetElementDef(StringIn namespaceURI, StringIn name)
{
	ASSERT(0);
#if 0
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	CComBSTR namespaceAttr;
	getAttribute(L"namespace", &namespaceAttr);
	if (!cmpbstr(namespaceAttr, namespaceURI))
	{
		for (int i = 0; i < m_childNodes->m_items.GetSize(); i++)
		{
			CComQIPtr<ILSVGElementDefElement> elementDef = m_childNodes->m_items[i];
			if (elementDef)
			{
				CComBSTR nameAttr;
				elementDef->getAttribute(L"name", &nameAttr);

				if (!cmpbstr(nameAttr, name))
				{
					*pVal = elementDef;
					(*pVal)->AddRef();
					return S_OK;
				}
			}
		}
	}

#if 0
	{
		BSTR clsidstr;  getAttribute(L"classid", &clsidstr);
		if (!clsidstr) return;

	// TODO, allow white-space

		if (!wcsnicmp(clsidstr, L"clsid:", 6))
		{
			_bstr_t classid = _bstr_t(clsidstr + lstrlen("clsid:"));

			if (((BSTR)classid)[0] != L'{')	// }
			{
				classid = L"{" + classid + L"}";
			}

			CLSID	clsid;
			HRESULT hr = CLSIDFromString(classid, &clsid);

			m_factory.CoCreateInstance(clsid);
		}
	}
#endif

	CComBSTR href;
	getAttributeNS(L"http://www.w3.org/1999/xlink", L"href", &href);

	if (href.Length())
	{
		if (m_hrefDocument == NULL)	// Loading for first time
		{
			WCHAR url[4096];
			wcscpy(url, href);

			WCHAR* id = NULL;
			int i = href.Length()-1;
			while (i >= 0)
			{
				if (url[i] == L'#')
				{
					url[i] = 0;
					id = &url[i+1];
					break;
				}
				i--;
			}

			TCHAR result[2048];
			{
				CComBSTR documentUrl;
				m_ownerDocument->get_url(&documentUrl);

				DWORD resultLen = sizeof(result);
				InternetCombineUrl(_bstr_t(documentUrl), _bstr_t(url), result, &resultLen, 0);
			}

			m_hrefDocument.CoCreateInstance(CLSID_LDOMDocument);
			if (m_hrefDocument)
			{
				bool bsuccess;
				m_hrefDocument->load(_variant_t(result), &bsuccess);

				{
					CScriptSite* pScriptSite = CComQIPtr<CLDOMDocumentImplImpl>(m_hrefDocument)->m_pScriptSite;

					HRESULT hr;

					// Start running scripts
					hr = pScriptSite->m_activeScript->SetScriptState(SCRIPTSTATE_STARTED);
					ASSERT(SUCCEEDED(hr));

				// force the engine to connect any outbound interfaces to the 
				// host's objects
					hr = pScriptSite->m_activeScript->SetScriptState(SCRIPTSTATE_CONNECTED);
					ASSERT(SUCCEEDED(hr));
				}

				if (id)
				{
					CComPtr<ILDOMElement> element;
					m_hrefDocument->getElementById(id, &element);

					m_extensionDefsElement = CComQIPtr<ILSVGExtensionDefsElement>(element);
				}
			}
		}

		if (m_extensionDefsElement)
		{
			return static_cast<CLSVGExtensionDefsElement*>(m_extensionDefsElement.p)->GetElementDef(namespaceURI, name, pVal);
		}
	}
#endif
	return NULL;
}

}	// Web
}
