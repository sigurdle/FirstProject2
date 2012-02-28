#include "stdafx.h"
#include "HTML2.h"
#include "HTMLFrameElement.h"

#include "HTMLDocument.h"

namespace System
{
namespace Web
{

HTMLFrameElement::HTMLFrameElement(NamedNodeMap* attributes) : HTMLElement(new PHTMLFrameElement(this), attributes)
{
	m_src = NULL;
	m_name = NULL;

	m_pFrameContent = NULL;

	ASSERT(0);
//	AddXMLAttribute(NewNXMLAttr(&m_marginWidth, NULL, WSTR("marginwidth"), NULL));
//	AddXMLAttribute(NewNXMLAttr(&m_marginHeight, NULL, WSTR("marginheight"), NULL));

	SetAllValues(this);	// ???
}

HTMLFrameElement::~HTMLFrameElement()
{
//	m_contentDocument.Release();

	if (m_pFrameContent)
	{
		delete m_pFrameContent;
	}
}

bool HTMLFrameElement::dispatchEvent2(Event * evt, bool bCapture)
{
	String type = evt->get_type();

	if (type == L"activate")
	{
//		Fire_onactivate(evt);
	}
/*
	else if (!wcscmp(type, L"mouseup"))
	{
		Fire_onmouseup(evt);
	}
	else if (!wcscmp(type, L"mousemove"))
	{
		Fire_onmousemove(evt);
	}
	else if (!wcscmp(type, L"keydown"))
	{
		Fire_onkeydown(evt);
	}
*/
	return EventTarget::dispatchEvent2(evt, bCapture);
}

ErrorCode HTMLFrameElement::OnObjectAvailable(Object* object, StringIn url)
{
	ASSERT(0);
	m_pFrameContent = dynamic_cast<Gui::Control*>(object);

	ASSERT(0);
#if 0
	m_pElement->set_VisualTree(m_pFrameContent);
#endif

	return Success;
}

ErrorCode HTMLFrameElement::Load()
{
	ASSERT(m_pFrameContent == NULL);

	{
		String src = get_src();

		WCHAR result[2048];
		{
			String documentUrl = m_ownerDocument->get_url();

			ASSERT(0);
#if 0
			DWORD resultLenBytes = sizeof(result) - sizeof(result[0]);
			InternetCombineUrlW(CStringw(documentUrl).c_str(), CStringw(src).c_str(), result, &resultLenBytes, 0);
#endif
//			TCHAR dir[256];
//			TCHAR path[256];
//			_splitpath(W2A(documentUrl.c_str()), dir, path, NULL, NULL);

			/*
		_makepath(result, dir, path, W2A(src.c_str()), NULL);
			TCHAR result[2048];
			{
				BSTR bdocumentUrl;
				m_ownerDocument->get_url(&bdocumentUrl);
				_bstr_t documentUrl = _bstr_t(bdocumentUrl, false);

				_bstr_t baseUrl = documentUrl;

				DWORD resultLen = sizeof(result);
				InternetCombineUrl(baseUrl, src, result, &resultLen, 0);
			}
			*/

		}

		String url = string_copy(result);

		//CComQIPtr<CLDOMDocumentImplImpl> documentImpl(m_ownerDocument);

	//	LHTML::CLHTMLDocument* document = new LHTML::CLHTMLDocument;

		ASSERT(0);
#if 0
		DownloadDocument* binder = new DownloadDocument;
		binder->BindToObject(ConvertA2S(url), this);
#endif
	//	thread->pBrowser = new LXML::CHTMLWindow;


	//	thread->Run();

		return Success;
#if 0
		document->m_pWindow = pBrowser;
		document->load(url);


#if 0
		return m_pFrameContent->LoadSRC(CComQIPtr<IHlinkSite>(m_ownerDocument), url);
#endif
#endif
	}
	return Error;
}

#if 0
void HTMLFrameElement::OnDocumentReady(DownloadDocument* dd)
{
	/*
	if (dd->m_document->get_documentElement())
	{
		dd->pBrowser->m_htmTree = (LXML::CPElement*)dd->m_document->get_documentElement()->m_pNode;
		dd->pBrowser->m_htmTree->m_pWindow = dd->pBrowser;
//			pBrowser->m_htmTree->GetCSSPropertiesAndChildren();
//			pBrowser->m_htmTree->CalculateBoundsAndChildren();

		dd->pBrowser->m_htmTree->GetCSSPropertiesAndChildren();
		dd->pBrowser->m_htmTree->CalculateBoundsAndChildren();
	}
	m_pFrameContent = dd->pBrowser;

	((CPHTMLFrameElement*)m_pNode)->OnReady();
	*/
}
#endif

Document* HTMLFrameElement::get_contentDocument()
{
	if (m_pFrameContent)
	{
		ASSERT(0);
		return NULL;
#if 0
		return m_pFrameContent->m_contentDocument;
#endif
	}

	return NULL;

#if 0
	USES_CONVERSION;

	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	return S_OK;

	if (m_contentDocument == NULL)
	{
		CComBSTR src;
		get_src(&src);

		TCHAR result[2048];
		{
			CComBSTR documentUrl;
			m_ownerDocument->get_url(&documentUrl);

			DWORD resultLen = sizeof(result);
			InternetCombineUrl(W2A(documentUrl), W2A(src), result, &resultLen, 0);
		}

		CComBSTR url = A2W(result);
#if 0
		if (StgIsStorageFile(url) == S_OK)
		{
			MessageBeep(-1);
		}

		CComPtr<ILDOMImplementation> impl;
		impl.CoCreateInstance(CLSID_LDOMImplementation);

		CComPtr<ILDOMBuilder> builder;
		impl->createDOMBuilder(1, NULL, &builder);

		builder->parseURI(url, &m_contentDocument);

		if (m_contentDocument)
		{
		// Look for xsl-stylesheet
			CComPtr<ILDOMNode> child;
			m_contentDocument->get_firstChild(&child);
			while (child)
			{
				CComQIPtr<ILDOMProcessingInstruction> pi = child;
				if (pi)
				{
					CComBSTR target;
					pi->get_target(&target);

					if (!wcscmp(target, L"stylesheet"))
					{
						BSTR bdata;
						pi->get_data(&bdata);
						_bstr_t data = _bstr_t(bdata, false);

						CComObject<CLDOMNamedNodeMap>* attributes;
						CComObject<CLDOMNamedNodeMap>::CreateInstance(&attributes);
						if (attributes)
						{
							attributes->AddRef();

							CDOMParser parser;
							parser.m_textData = data;
							parser.m_textLen = data.length();
							parser.m_document = m_contentDocument;

							parser.ParseAttributes(NULL, attributes);

							CComPtr<ILDOMAttr> hrefNode;
							attributes->getNamedItem(L"href", (ILDOMNode**)&hrefNode);
							if (hrefNode)
							{
								BSTR bhref;
								hrefNode->get_value(&bhref);
								_bstr_t href = _bstr_t(bhref, false);

								if (href.length())
								{
									Document* xslDocument;
									bool bsuccess;

									ASSERT(0);
#if 0
								// TODO, some monikers, some services already defined for this ??
									CComQIPtr<IXMLDocumentInMemoryProvider> imp = m_pUI->m_document->m_spClientSite;
									if (imp)
									{
										imp->GetInMemoryDocument(href, &xslDocument);
										if (xslDocument)
											bsuccess = VARIANT_TRUE;
									}
#endif

									if (xslDocument == NULL)
									{
										xslDocument.CoCreateInstance(CLSID_LDOMDocument);
										xslDocument->load(href, &bsuccess);
									}

									if (bsuccess)
									{
										CComPtr<ILXSLTemplate> xslTemplate;
										xslTemplate.CoCreateInstance(CLSID_LXSLTemplate);
										if (xslTemplate)
										{
											xslTemplate->putref_stylesheet(xslDocument);

											CComPtr<ILXSLProcessor> xslProcessor;

											xslTemplate->createProcessor(&xslProcessor);

											CComPtr<ILDOMElement> documentElement;
											m_contentDocument->get_documentElement(&documentElement);

											xslProcessor->set_input(_variant_t((IUnknown*)m_contentDocument));
											bool done;
											xslProcessor->transform(&done);
											if (done)
											{
												_variant_t output;
												xslProcessor->get_output(&output);

												_bstr_t bstrOutput = output;

											//	::MessageBox(NULL, bstrOutput, "", MB_OK);
											//	bool bsuccess;
											//	m_document->loadXML(bstrOutput, &bsuccess);

												CComPtr<ITextData> textData;
												textData.CoCreateInstance(CLSID_TextData);
												textData->set_data(bstrOutput.copy());

												m_contentDocument.Release();
												builder->parseTextData(textData, &m_contentDocument);
											}
										}
									}
								}
							}

							attributes->Release();
						}
						break;
					}
				}

				CComPtr<ILDOMNode> nextSibling;
				child->get_nextSibling(&nextSibling);
				child = nextSibling;
			}
		}
		else
#endif

		// m_frameContent->LoadSRC(url);
	}

	*pVal = m_contentDocument;

	if (*pVal) (*pVal)->AddRef();
#endif

	return NULL;
}

IWindow* HTMLFrameElement::get_contentWindow()
{
	ASSERT(0);
	return NULL;
}

String HTMLFrameElement::get_frameBorder()
{
	return getAttribute(WSTR("frameborder"));
}

void HTMLFrameElement::set_frameBorder(StringIn newVal)
{
	setAttribute(WSTR("frameborder"), newVal);
}

String HTMLFrameElement::get_longDesc()
{
	return getAttribute(WSTR("longdesc"));
}

void HTMLFrameElement::set_longDesc(StringIn newVal)
{
	setAttribute(WSTR("longdesc"), newVal);
}

#if 0
STDMETHODIMP HTMLFrameElement::get_marginWidth(VARIANT *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	ASSERT(0);
#if 0
	if (m_marginWidth->m_specified)
		*pVal = _variant_t(m_marginWidth->m_value->m_value->m_value);
	else
		*pVal = _variant_t();
#endif
	/*
	CComBSTR border;
	getAttribute(L"marginwidth", &border);
	*pVal = _variant_t(border);
	*/

	return S_OK;
}

STDMETHODIMP HTMLFrameElement::put_marginWidth(VARIANT newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP HTMLFrameElement::get_marginHeight(VARIANT *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	ASSERT(0);
#if 0
	if (m_marginHeight->m_specified)
		*pVal = _variant_t(m_marginHeight->m_value->m_value->m_value);
	else
		*pVal = _variant_t();
#endif
	/*
	CComBSTR border;
	getAttribute(L"marginheight", &border);
	*pVal = _variant_t(border);
	*/

	return S_OK;
}

STDMETHODIMP HTMLFrameElement::put_marginHeight(VARIANT newVal)
{

	return S_OK;
}
#endif

String HTMLFrameElement::get_name()
{
	return getAttribute(WSTR("name"));
}

void HTMLFrameElement::set_name(StringIn newVal)
{
	setAttribute(WSTR("name"), newVal);
}

String HTMLFrameElement::get_src()
{
	return getAttribute(WSTR("src"));
}

void HTMLFrameElement::set_src(StringIn newVal)
{
	setAttribute(WSTR("src"), newVal);
}

bool HTMLFrameElement::get_noResize()
{
	ASSERT(0);

	return false;
}

void HTMLFrameElement::set_noResize(bool newVal)
{
	// TODO: Add your implementation code here
	ASSERT(0);

}

String HTMLFrameElement::get_scrolling()
{
	return getAttribute(WSTR("scrolling"));
}

void HTMLFrameElement::set_scrolling(StringIn newVal)
{
	setAttribute(WSTR("scrolling"), newVal);
}

/*
STDMETHODIMP HTMLFrameElement::get_border(VARIANT *pVal)
{
	ASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	sysstring border = getAttribute(L"border");
	ASSERT(0);
#if 0
	*pVal = _variant_t(border.c_str());
#endif
	return S_OK;
}

STDMETHODIMP HTMLFrameElement::put_border(VARIANT newVal)
{
	ASSERT(0);

	return S_OK;
}
*/

long HTMLFrameElement::get_frameSpacing()
{
	ASSERT(0);

	return 0;
}

void HTMLFrameElement::set_frameSpacing(long newVal)
{
	ASSERT(0);
}

void HTMLFrameElement::OnAttrValueChanged(StringIn /*nodeName*/, Attr* attr)
{
	String attrName = attr->get_name();

	if (attrName == L"src")
	{
	}
//
	HTMLElement::OnAttrValueChanged(NULL/*nodeName*/, attr);
}

}	// Web
}
