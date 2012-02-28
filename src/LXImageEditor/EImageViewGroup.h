#ifndef __EIMAGEVIEWGROUP_H_
#define __EIMAGEVIEWGROUP_H_

//#include "resource.h"       // main symbols

namespace System
{

class CImageDocument;

class CEImageViewGroup 

//	public CUIMDIChildImpl<CEImageViewGroup>,
	//public IEViewGroup,
//	public IUIActivatable
//	public ProcessTargetCommands
//	public ILDOMEventListener,

//	public CProxy_IEXMLViewGroupEvents< CEImageViewGroup >,
//	public IConnectionPointContainerImpl<CEImageViewGroup>
{
public:
	CEImageViewGroup()
	{
		m_pDocument = NULL;
	}

	~CEImageViewGroup()
	{
		TRACE("~CEImageViewGroup\n");
	}

//	int FinalConstruct();
//	void FinalRelease();

	CImageDocument* m_pDocument;

//	CComPtr<IEViewGroupSite> m_spViewGroupSite;


/*
BEGIN_CONNECTION_POINT_MAP(CEImageViewGroup)
	CONNECTION_POINT_ENTRY(DIID__IEXMLViewGroupEvents)
END_CONNECTION_POINT_MAP()
*/

//	typedef CUIMDIChildImpl<CEImageViewGroup> baseClass;

/*
BEGIN_MSG_MAP(CEImageViewGroup)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
//	MESSAGE_HANDLER(WM_NCDESTROY, OnNcDestroy)
	MESSAGE_HANDLER(WM_MDIACTIVATE, OnMDIActivate)
	CHAIN_MSG_MAP(baseClass)
END_MSG_MAP()

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnNcDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnMDIActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

//DECLARE_CMD_MAP(CEImageViewGroup)

// IEImageViewGroup
public:
	//STDMETHOD(get_eDocument)(/*[out,retval]*/ IEDocument* *pVal);

// IEViewGroup
   ErrorCode OnActivate(bool bActive)
	{
		return Success;
	}

};

}

#endif //__EIMAGEVIEWGROUP_H_
