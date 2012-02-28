// LMoviePlayer.cpp : Implementation of CLMoviePlayer
#include "stdafx.h"
#include "LXDocumentViewer.h"
#include "LXDocumentViewer2.h"
#include "LMoviePlayer.h"

#include "LVideoView.h"

/////////////////////////////////////////////////////////////////////////////
// CLMoviePlayer

#if 0
STDMETHODIMP CLMoviePlayer::Show(ILXFrameworkFrame* frame)
{
	CComPtr<ILXFrameworkApp> app;
	frame->GetApp(&app);

	CComPtr<ILXUIMDIFrameElement> frameelement;
	frame->get_Element(&frameelement);

	CComPtr<ILXUIDocument> appdocument;
	app->get_Document(&appdocument);

	CComPtr<ILXUIElement> mdiclient;
	frameelement->getMDIClient(&mdiclient);

	CComPtr<ILDOMDocument> doc;
	doc.CoCreateInstance(CLSID_LDOMDocument);

	VARIANT_BOOL success;
	doc->load(_variant_t(L"C:\\media_layout.xml"), &success);

	CComPtr<ILDOMElement> documentElement;
	doc->get_documentElement(&documentElement);

	CComPtr<ILDOMNode> layout;
	appdocument->importNode(documentElement, VARIANT_TRUE/*deep*/, &layout);

	CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
	LONGLONG duration;
	seeking->GetDuration(&duration);

// find the renderer filter
	CComPtr<ILBasicVideo> basicVideo;
	m_filterGraph->QueryFilterInterface(IID_ILBasicVideo, (IUnknown**)&basicVideo);

	/*
	if (basicVideo)
	{
		*/
		CComPtr<ILDOMElement> mdichild;
		appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"mdichild", &mdichild);
		if (mdichild)
		{
			CComPtr<ILXUIPageElement> page;
			appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"page", (ILDOMElement**)&page);
			if (page)
			{
				CComPtr<ILDOMElement> e;
				appdocument->createElementNS(L"http://www.lerstad.com/2004/lxui", L"content", &e);
				if (e)
				{
					e->appendChild(layout, NULL);

#if 0
					long cookie;
					e->addBehavior(L"#factory#videoview", &CComVariant(GetUnknown()), &cookie);
#endif

					page->appendChild(e, NULL);
				}
				mdichild->appendChild(page, NULL);
			}

			mdiclient->appendChild(mdichild, NULL);

			CComPtr<ILDOMElement> durationElement;
			appdocument->getElementById(L"media_duration", &durationElement);
			if (durationElement)
			{
				WCHAR str[64];
				swprintf(str, L"%g", (double)duration / LTIME_SCALE);
				durationElement->put_textContent(str);
			}

			CComPtr<ILDOMElement> videoElement;
			appdocument->getElementById(L"video", &videoElement);
			if (videoElement)
			{
				long cookie;
				videoElement->addBehavior(L"#factory#videoview", &CComVariant(GetUnknown()), &cookie);
			}

		}
	//}

	return S_OK;
}
#endif

#include "LXDocumentViewerApp.h"

LRESULT CLMoviePlayer::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	CComQIPtr<ILXFrameworkFrame> frame;
	m_app->m_spAddinSite->GetFrame(&frame);

	CComPtr<ILXFrameworkApp> app;
	frame->GetApp(&app);

//	CComPtr<ILXUIMDIFrameElement> frameelement;
//	frame->get_Element(&frameelement);

	CComPtr<ILXUIDocument> appdocument;
	app->get_Document(&appdocument);

	CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
	LONGLONG currentPos;
	seeking->GetCurrentPosition(&currentPos);

	CComPtr<ILDOMElement> element;
	appdocument->getElementById(L"media_current", &element);
	if (element)
	{
		WCHAR str[64];
		swprintf(str, L"%g", (double)currentPos / LTIME_SCALE);
		element->put_textContent(str);
	}
#endif

	return 0;
}

STDMETHODIMP CLMoviePlayer::FindBehavior(BSTR bstrBehavior, BSTR bstrBehaviorUrl, ILElementBehaviorViewSite* pSite, ILElementBehaviorView** ppBehavior)
{
	if (ppBehavior == NULL) return E_POINTER;
	*ppBehavior = NULL;

//	if (m_view)	// Only supports one view
//		return E_FAIL;

	if (!wcscmp(bstrBehavior, L"videoview"))
	{
#if 0
		CComObject<CLVideoView>* p;
		CComObject<CLVideoView>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			p->m_document = this;

//			m_view = p;

			*ppBehavior = p;
		}
#endif
	}
	else
		ATLASSERT(0);

	return S_OK;
}
