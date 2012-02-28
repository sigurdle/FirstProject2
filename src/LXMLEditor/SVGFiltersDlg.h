// SVGFiltersDlg.h : Declaration of the CSVGFiltersDlg

#ifndef __SVGFILTERSDLG_H_
#define __SVGFILTERSDLG_H_

#include "resource.h"       // main symbols

#include "SVGDefinitionsDlgT.h"

class CView;

namespace System
{
namespace LXmlEdit
{
class CEXMLViewGroup;

class CSVGFiltersDlg : 
//	public CComCoClass<CSVGFiltersDlg, &CLSID_SVGFiltersDlg>,

	public CSVGDefinitionsDlgT<CSVGFiltersDlg>,
//	public CUIEventHandlerImpl,
public UI::ProcessTargetCommands	// Web::EventListener
#if 0
	public IDropTarget
#endif
//	public IDispEventImpl<1, CSVGFiltersDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CSVGFiltersDlg()
	{
		m_type = 1;
	}

	~CSVGFiltersDlg()
	{
		TRACE("~CSVGFiltersDlg()\n");
	}

	int FinalConstruct();

	//CComPtr<IWebXMLDocument> m_document;
	//CComPtr<IEXMLViewGroup> m_viewGroup;
	CView* m_view;
	CEXMLViewGroup* m_viewGroup;

	void BuildItems();
	void AddEventListeners();
	void RemoveEventListeners();

//DECLARE_REGISTRY_RESOURCEID(IDR_SVGFILTERSDLG)

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSVGFiltersDlg)
	COM_INTERFACE_ENTRY(ISVGFiltersDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(IDropTarget)
	COM_INTERFACE_ENTRY(Web::EventListener)
END_COM_MAP()
*/

#if 0
BEGIN_SINK_MAP(CSVGFiltersDlg)
	SINK_ENTRY_EX(1, DIID__IEXMLViewGroupEvents, /*dispid*/3, OnSelectionStyleChanged)
END_SINK_MAP()
#endif

	void __stdcall OnSelectionStyleChanged();

	long OnCreate();
	long OnDestroy();

	long OnClicked(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnDblClicked(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

DECLARE_CMD_MAP(CSVGFiltersDlg)

	long OnFiltersNewFilter(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnFiltersDeleteFilter(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnSelectAllUnused(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnFiltersSmallThumbnails(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(0);
		return 0;
	}

	long OnFiltersLargeThumbnails(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(1);
		return 0;
	}

	long OnFiltersSmallListView(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(2);
		return 0;
	}

	long OnFiltersLargeListView(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(3);
		return 0;
	}

	void OnFiltersSmallThumbnailsUpdate(long id, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 0);
	}

	void OnFiltersLargeThumbnailsUpdate(long id, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 1);
	}

	void OnFiltersSmallListViewUpdate(long id, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 2);
	}

	void OnFiltersLargeListViewUpdate(long id, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 3);
	}

// ISVGFiltersDlg
public:
#if 0
// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
#endif

// Web::EventListener
	void handleEvent(Web::Event* evt);

// IUIEventHandler
//	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

}	// LXmlEdit
}

#endif //__SVGFILTERSDLG_H_
