#ifndef __DTDVIEWGROUP_H_
#define __DTDVIEWGROUP_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CEDTDDocument;

class CDTDViewGroup : 
//	public CComObjectRootEx<CComSingleThreadModel>,

//	public CUIMDIChildImpl<CDTDViewGroup>,
//	public IEViewGroup,
//	public IUIActivatable,
public UI::ProcessTargetCommands	// ILDOMEventListener
//	public ILDOMEventListener,

#if 0
	//public CProxy_IEXMLViewGroupEvents< CDTDViewGroup >,
	public IConnectionPointContainerImpl<CDTDViewGroup>
#endif
{
public:
	CDTDViewGroup()
	{
		m_pDocument = NULL;
	}

	~CDTDViewGroup()
	{
		TRACE("~CDTDViewGroup\n");
	}

	int FinalConstruct();
	void FinalRelease();

	CEDTDDocument* m_pDocument;

	Array<UI::Control*> m_views;

public:

protected:
public:

	void SetDocument(CEDTDDocument* pDocument);
	void UpdateFrameTitle();

	virtual void OnFinalMessage(UI::Control* /*hWnd*/);

//DECLARE_REGISTRY_RESOURCEID(IDR_WEBXMLVIEWGROUP)

#if 0
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDTDViewGroup)
//	COM_INTERFACE_ENTRY(IEViewGroup)
	/*
	COM_INTERFACE_ENTRY(IEXMLViewGroup)
	COM_INTERFACE_ENTRY(IUIActivatable)
	*/
//	COM_INTERFACE_ENTRY(IUIMDIChild)
//	COM_INTERFACE_ENTRY(IUIWnd)

	COM_INTERFACE_ENTRY(ILDOMEventListener)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDTDViewGroup)
//	CONNECTION_POINT_ENTRY(DIID__IEXMLViewGroupEvents)
END_CONNECTION_POINT_MAP()
#endif
/*
	typedef CUIMDIChildImpl<CDTDViewGroup> baseClass;

BEGIN_MSG_MAP(CDTDViewGroup)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	MESSAGE_HANDLER(WM_MDIACTIVATE, OnMDIActivate)
	CHAIN_MSG_MAP(baseClass)
END_MSG_MAP()

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnMDIActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

DECLARE_CMD_MAP(CDTDViewGroup)

//	LRESULT OnSelectBack(WORD wNotifyCode, WORD wID, UI::Control* hWndCtl, BOOL& bHandled);


// IWebXMLViewGroup
public:
	ErrorCode get_eDocument(/*[out,retval]*/ IEDocument* *pVal);

// IUIActivatable
//	ErrorCode(OnActivate)(IUIManager *uiManager);
//	ErrorCode(OnDeactivate)(IUIManager *uiManager);
// ICommandTarget
	ErrorCode OnCmdMsg(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, bool * bHandled);
};

}
}

#endif //__DTDVIEWGROUP_H_
