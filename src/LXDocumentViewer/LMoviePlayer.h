// LMoviePlayer.h : Declaration of the CLMoviePlayer

#ifndef __LMOVIEPLAYER_H_
#define __LMOVIEPLAYER_H_

#include "resource.h"       // main symbols

class CLXDocumentViewerApp;

/////////////////////////////////////////////////////////////////////////////
// CLMoviePlayer
class ATL_NO_VTABLE CLMoviePlayer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLMoviePlayer, &CLSID_LMoviePlayer>,
	public IDispatchImpl<ILMoviePlayer, &IID_ILMoviePlayer, &LIBID_LXDOCUMENTVIEWERLib>,
	public ILElementBehaviorFactory,

	public CMessageMap
{
public:
	CLMoviePlayer() : m_cwnd("static", this, 1)
	{
	}

	int FinalConstruct()
	{
		m_cwnd.Create(NULL, CRect(0,0,0,0), NULL, WS_POPUP);
		return 0;
	}

	CLXDocumentViewerApp* m_app;

	CComPtr<ILGraphBuilder> m_filterGraph;

	CContainedWindow m_cwnd;

DECLARE_REGISTRY_RESOURCEID(IDR_LMOVIEPLAYER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLMoviePlayer)
	COM_INTERFACE_ENTRY(ILMoviePlayer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ILElementBehaviorFactory)
END_COM_MAP()

BEGIN_MSG_MAP(CLMoviePlayer)
	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
END_MSG_MAP()

	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ILMoviePlayer
public:
#if 0
	STDMETHOD(Show)(ILXFrameworkFrame* lxframe);
#endif

// ILElementBehaviorFactory
	STDMETHOD(FindBehavior)(BSTR bstrBehavior, BSTR bstrBehaviorUrl, ILElementBehaviorViewSite* pSite, ILElementBehaviorView** ppBehavior);
};

#endif //__LMOVIEPLAYER_H_
