// ASGraphCtl.h : Declaration of the CASGraphCtl

#ifndef __ASGRAPHCTL_H_
#define __ASGRAPHCTL_H_

#include "resource.h"       // main symbols
//#include <atlctl.h>

#include "ASEditCtlsMod.h"

class CDTDDesignContentModel;
class CDTDDesignSchemaNode;
//class CDTDDesignElementDefinitionRoot;
class CDTDDesignDefinition;

//#include "ASEditCtlsModCP.h"

class ASGRAPHEXT CASGraphCtl : 
	public Control
//	public ProcessTargetCommands
{
public:
	CASGraphCtl()// : m_wndEdit(NULL, this, 1)
	{
	//	m_bWindowOnly = TRUE;
		m_pRoot = NULL;
		m_pActiveItem = NULL;
//		m_magnify = 1.0;

	//	m_hFont = NULL;

		m_pDef = NULL;
		m_pBeforeDef = NULL;
	}

#if 0
	int FinalConstruct()
	{
//		HRESULT hr;

		m_horz.CoCreateInstance(CLSID_UIScrollBar);
		m_horz->put_direction(0);

		m_vert.CoCreateInstance(CLSID_UIScrollBar);
		m_vert->put_direction(1);

		IDispEventImpl<1, CASGraphCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);
		IDispEventImpl<2, CASGraphCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

		GUID guid;
		CoCreateGuid(&guid);
		StringFromCLSID(guid, &m_key);

		return S_OK;
	}

	void FinalRelease()
	{
		CoTaskMemFree(m_key);

		IDispEventImpl<1, CASGraphCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
		IDispEventImpl<2, CASGraphCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);
	}
#endif

	sysstring m_key;

	/*
	CAxWindow m_axhorz;
	CAxWindow m_axvert;
	CComPtr<IUIScrollBar> m_horz;
	CComPtr<IUIScrollBar> m_vert;
	*/

//	CMenuWindow m_menuWnd;

//	HFONT m_hFont;

//	CRect m_areaRect;
//	double m_magnify;

//	CDTDDesignElementDefinitionRoot* m_pRoot;
	CDTDDesignContentModel* m_pRoot;
	CDTDDesignSchemaNode* m_pActiveItem;

//
	CDTDDesignDefinition* m_pDef;
	CDTDDesignDefinition* m_pBeforeDef;
	LDraw::Point m_oldpt;
//	void DrawInsertion(CDC& dc, IASDesignDefinition* pDef, CPoint pt);
	void DrawInsertion(LDraw::Graphics* dc, CDTDDesignDefinition* pDef, LDraw::Point pt);
//

	LXML::IASModel* m_asModel;
//	CComQIPtr<IASElementDeclaration> m_asElement;
	LXML::IASDeclaration* m_asDefinition;

	IUndoManager* m_undoManager;

//	CContainedWindow m_wndEdit;

	void OnSize();
	void OnButtonDown(WPARAM wParam, LPARAM lParam, int iButton, BOOL bDblClk);
	void UpdateView();

	/*
DECLARE_REGISTRY_RESOURCEID(IDR_ASGRAPHCTL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CASGraphCtl)
	COM_INTERFACE_ENTRY(IASGraphCtl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)

	COM_INTERFACE_ENTRY(IDropTarget)
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CASGraphCtl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
	PROP_ENTRY("ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage)
	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CASGraphCtl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IASGraphCtlEvents)
END_CONNECTION_POINT_MAP()
*/
#if 0
BEGIN_SINK_MAP(CASGraphCtl)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
   SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()

	void __stdcall OnHorzScroll(long code, long pos);
	void __stdcall OnVertScroll(long code, long pos);

BEGIN_MSG_MAP(CASGraphCtl)
	MESSAGE_HANDLER(WM_LBUTTONDOWN,, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK,, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_RBUTTONDOWN,, OnRButtonDown)
	MESSAGE_HANDLER(WM_CONTEXTMENU,, OnContextMenu)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

	COMMAND_HANDLER(1, EN_CHANGE, OnEditChange)

	CHAIN_MSG_MAP(CComControl<CASGraphCtl>)
	DEFAULT_REFLECTION_HANDLER()

	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_KEYDOWN, OnEditKeydown)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnEditKeydown)
END_MSG_MAP()
#endif
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnEditChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

#if 0
DECLARE_CMD_MAP(CASGraphCtl)
#endif

//	LRESULT OnViewZoomout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//	LRESULT OnViewZoomin(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnASGraphChangeModelSequence(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnASGraphChangeModelChoice(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnASGraphChangeModelAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	void OnASGraphChangeModelSequenceUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnASGraphChangeModelChoiceUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnASGraphChangeModelAllUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnASGraphUnbounded(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnASGraphUnboundedUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnASGraphOptional(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnASGraphOptionalUpdate(long iid, IUICmdUpdate* pCmdUI);

	STDMETHOD(get_ActiveItem)(/*[out, retval]*/ CDTDDesignSchemaNode* *pVal);
//	STDMETHOD(putref_ActiveItem)(/*[in]*/ IASDesignObject* newVal);
#if 0
	STDMETHOD(get_asRootObject)(/*[out, retval]*/ IUnknown* *pVal);
#endif
	void put_asRootObject(LXML::IASDeclaration* newVal);
	LXML::IASModel* get_asModel() const;
	void put_asModel(LXML::IASModel* newVal);

#if 0
// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);

#endif

	virtual void OnRender3(LDraw::Graphics* pGraphics);
	virtual void OnMeasure(LDraw::SizeD availSize);
	virtual void OnArrange(LDraw::SizeD finalSize);
	/*
	OLE_COLOR m_clrBackColor;
	BOOL m_bEnabled;
	CComPtr<IFontDisp> m_pFont;
	OLE_COLOR m_clrForeColor;
	*/
};

#endif //__ASGRAPHCTL_H_
