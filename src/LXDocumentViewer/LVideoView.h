// LVIDEOVIEW.h : Declaration of the CLVideoView

#ifndef __LVideoView_H_
#define __LVideoView_H_

#include "resource.h"       // main symbols

#if 0
class CLMoviePlayer;

/////////////////////////////////////////////////////////////////////////////
// CLVideoView
class ATL_NO_VTABLE CLVideoView : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IConnectionPointContainerImpl<CLVideoView>,

	public CUIDialogImpl<CLVideoView, CWindowImpl<CLVideoView> >,
	public ILElementBehaviorView
{
public:
	CLVideoView()
	{
	}

	int FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	CLMoviePlayer* m_document;

	//

// ILElementBehavior
	CComPtr<ILElementBehaviorViewSite> m_behaviorSite;

	STDMETHODIMP Init(/*[in]*/ ILElementBehaviorViewSite* pBehaviorSite)
	{
		m_behaviorSite = pBehaviorSite;
		return S_OK;
	}
	STDMETHODIMP Detach()
	{
		m_behaviorSite.Release();
		return S_OK;
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLVideoView)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ILElementBehaviorView)


END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLVideoView)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CLVideoView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

//	DECLARE_CMD_MAP(CLVideoView)

public:
};

#endif //__LVIDEOVIEW_H_

#endif