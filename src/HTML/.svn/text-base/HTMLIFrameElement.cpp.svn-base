#include "stdafx.h"
#include "HTML2.h"
#include "HTMLIFrameElement.h"

namespace System
{
namespace Web
{

HTMLIFrameElement::HTMLIFrameElement(NamedNodeMap* attributes) : HTMLElement(new PHTMLElement(this), attributes)
{
//		m_pFrameContent = NULL;
	m_srcAttr = NULL;
}

// virtual
void HTMLIFrameElement::OnAttrValueChanged(StringIn /*nodeName*/, Attr* attr)
{
	String attrName = attr->get_name();

	if (attrName == L"src")
	{
		ASSERT(0);
#if 0
		if (m_pFrameContent)
		{
			m_pFrameContent->Free();
			Load();
		}
#endif
	}
//
	HTMLElement::OnAttrValueChanged(NULL/*nodeName*/, attr);
}

ErrorCode HTMLIFrameElement::Load()
{
	ASSERT(0);
	return 0;
#if 0

	ASSERT(m_pFrameContent);

	sysstring src = get_src();

	if (src.Length())
	{
		TCHAR result[2048];
		{
			sysstring documentUrl = m_ownerDocument->get_url();

			DWORD resultLen = sizeof(result);
			InternetCombineUrl(W2A(documentUrl), W2A(src), result, &resultLen, 0);
		}

		CComBSTR url = A2W(result);

		return m_pFrameContent->LoadSRC(CComQIPtr<IHlinkSite>(m_ownerDocument), url);
	}
	else
		return S_FALSE;
#endif
}

Document* HTMLIFrameElement::get_contentDocument()
{
	ASSERT(0);
#if 0
	if (m_pFrameContent)
	{
		return m_pFrameContent->m_contentDocument;
	}
#endif
	return NULL;
}

IWindow* HTMLIFrameElement::get_contentWindow()
{
	ASSERT(0);
	return NULL;
}

String HTMLIFrameElement::get_src()
{
	return getAttribute(WSTR("src"));
}

void HTMLIFrameElement::set_src(StringIn newVal)
{
	setAttribute(WSTR("src"), newVal);
}

void HTMLIFrameElement::goBack()
{
	ASSERT(0);
#if 0
	if (m_pFrameContent)
	{
		CComPtr<IHlink> pHlink;
		m_pFrameContent->m_hlinkBrowseContext->GetHlink(HLID_PREVIOUS, &pHlink);
		if (pHlink)
		{
		//	CComPtr<IBindCtx> bctx;
		//	CreateBindCtx(0, &bctx);
			ErrorCode hr = HlinkNavigate(pHlink, static_cast<IHlinkFrame*>(m_pFrameContent/*->m_pViewSite*/), HLNF_NAVIGATINGBACK, NULL/*bctx*/, NULL, m_pFrameContent->m_hlinkBrowseContext);
		}
		//ErrorCode hr = ::HlinkGoBack(m_spUnknown);
	}
#endif
}

void HTMLIFrameElement::goForward()
{
#if 0
	if (m_pHBC)
	{
		CComPtr<IHlink> pHlink;
		m_pHBC->GetHlink(HLID_NEXT, &pHlink);
		if (pHlink)
		{
			CComPtr<IBindCtx> bctx;
			CreateBindCtx(0, &bctx);
			ErrorCode hr = HlinkNavigate(pHlink, m_view, HLNF_NAVIGATINGFORWARD, bctx, NULL, m_pHBC);
		}
//		ErrorCode hr = ::HlinkGoForward(m_spUnknown);
	}
#endif
}

}	// Web
}
