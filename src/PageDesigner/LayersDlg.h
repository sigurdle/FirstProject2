// LayersDlg.h : Declaration of the CLayersDlg

#ifndef __LAYERSDLG_H_
#define __LAYERSDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

class CPDDocumentView;

extern bool IsUnknownEqualUnknown(IUnknown* pThis, IUnknown* pOther);

/////////////////////////////////////////////////////////////////////////////
// CLayersDlg
class ATL_NO_VTABLE CLayersDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLayersDlg, &CLSID_LayersDlg>,
	public IConnectionPointContainerImpl<CLayersDlg>,
	public IDispatchImpl<ILayersDlg, &IID_ILayersDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CLayersDlg, CWindowImpl<CLayersDlg> >,
	public CNotifyGetImpl<CLayersDlg>,
	public CUIEventHandlerImpl,
	public IDropTarget,
	public ProcessTargetCommands,
	public IDispEventImpl<1, CLayersDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
//	public IDispEventImpl<3, CLayersDlg, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>
{
public:
	CLayersDlg()
	{
		m_view = NULL;

		m_selectedLayerIndex = -1;
		m_dragging = 0;

		m_insertObjectsOnLayerIndex = -1;
		m_insertObjectsFromLayerIndex = -1;
	}

	int FinalConstruct();

	CComObject<CPDDocumentView>* m_view;

	CRect m_areaRect;

	CAxWindow m_axvert;
	CComPtr<IUIScrollBar> m_vert;

	int m_dragging;

	int m_selectedLayerIndex;
	CArray<IPDLayer*,IPDLayer*> m_selectedLayers;
	
	long m_insertObjectsOnLayerIndex;
	long m_insertObjectsFromLayerIndex;

	void DrawSelectedObjectsMarker(long index);
	void DrawDragLayerMarker(long index);

	bool IsLayerSelected(IPDLayer* layer)
	{
		for (int i = 0; i < m_selectedLayers.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_selectedLayers[i], layer))
			{
				return true;
			}
		}

		return false;
	}

	void SelectLayer(IPDLayer* layer)
	{
		ATLASSERT(!IsLayerSelected(layer));
		m_selectedLayers.Add(layer);
	}

	void DeselectLayer(IPDLayer* layer)
	{
		for (int i = 0; i < m_selectedLayers.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_selectedLayers[i], layer))
			{
				m_selectedLayers.RemoveAt(i);
				return;
			}
		}
	}

	void DeselectAll()
	{
		m_selectedLayers.RemoveAll();
	}

	bool AnySelectedObjectsOnLayer(IPDLayer* layer);

	void OnSize();
	void ShowLayerOptions();

DECLARE_REGISTRY_RESOURCEID(IDR_LAYERSDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLayersDlg)
	COM_INTERFACE_ENTRY(ILayersDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(IDropTarget)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLayersDlg)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CLayersDlg)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
//   SINK_ENTRY_EX(3, DIID__IPDDocumentEvents, /*dispid*/3, OnLayerOptionsChanged)
END_SINK_MAP()

	HRESULT __stdcall OnVertScroll(long code, long pos);

//	void __stdcall OnLayerOptionsChanged(IPDLayer* layer);

BEGIN_MSG_MAP(CLayersDlg)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CLayersDlg)

	LRESULT OnLayerOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnLayerDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnLayerDeleteUpdate(long iid, IUICmdUpdate* pCmdUI);

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		CComQIPtr<IPDLayer> layer = targetObject;
		if (layer)
		{
			if (m_hWnd)
			{
				OnSize();
				Invalidate();
			}
		}

		return S_OK;
	}

public:
// ILayersDlg
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Layers");
		return S_OK;
	}
// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
// ICommandTarget
	STDMETHODIMP OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);
};

#endif //__LAYERSDLG_H_
