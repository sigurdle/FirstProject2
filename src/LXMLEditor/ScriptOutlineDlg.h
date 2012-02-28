#ifndef __SCRIPTOUTLINEDLG_H_
#define __SCRIPTOUTLINEDLG_H_

#include "resource.h"       // main symbols
//#import "C:\MMStudio\Extras\UI\UI.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

namespace System
{
namespace LXmlEdit
{

class CEXMLViewGroup;

class CScriptOutlineDlg : 
//	public IScriptOutlineDlg,

		public UI::Control,
//	public CUIDialogImpl<CScriptOutlineDlg, CWindowImpl<CScriptOutlineDlg> >,
//	public CUIEventHandlerImpl,
public UI::ProcessTargetCommands	// Web::EventListener

//	public IDispEventImpl<2, CScriptOutlineDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<4, CScriptOutlineDlg, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>,
//	public IUITreeControlSite
{
public:

	enum
	{
		SO_ELEMENT = 1,
		SO_SCRIPT = 2,
		SO_FUNCTION = 3,
		SO_EVENT = 4,
	};

	class CItem
	{
	public:
		CItem()
		{
			m_type = 0;
		}

		virtual ~CItem()
		{
		}

		int m_type;
		System::StringW* m_name;
		UI::TreeItem* m_TreeItem;	// TODO, keep ref?
	};

	class CItemElement : public CItem
	{
	public:
		CItemElement()
		{
			m_type = SO_ELEMENT;
			m_element = NULL;
		}

		Web::Element* m_element;
	};

	class CItemEvent : public CItem
	{
	public:
		CItemEvent()
		{
			m_type = SO_EVENT;
		}
	};

	class CItemScript : public CItem
	{
	public:
		CItemScript()
		{
			m_type = SO_SCRIPT;
			m_element = NULL;
		}

		Web::Element* m_element;
	};

	class CItemFunction : public CItem
	{
	public:
		CItemFunction()
		{
			m_type = SO_FUNCTION;

			m_node = NULL;
			m_startOffset = m_endOffset = -1;
		}

		Web::CharacterData* m_node;
		long m_startOffset;
		long m_endOffset;
	};

	CScriptOutlineDlg()
	{
		m_app = NULL;
//		m_hIcons = NULL;
	}

	ILXMLEditorApp* m_app;

	//CAxWindow m_axtreeCtl;
	UI::TreeControl* m_treeCtl;

#if 0
	HIMAGELIST m_hIcons;
#endif

	CEXMLViewGroup* m_viewGroup;

	void BuildTree(Web::Element* element, UI::TreeItem* *pVal);

	void BuildTree();
//	void AddObjects(DWORD parentItem, IDOMElement* pelement);
	//void AddClientScripts(IUITreeItem* parentItem, Web::Element* pelement);

	void AddJScriptFunctions(UI::TreeItem* parentItem, Web::CharacterData* chardataNode, const WCHAR * data, long len);
	void AddVBScriptFunctions(UI::TreeItem* parentItem, Web::CharacterData* chardataNode, const WCHAR * data, long len);

	/*
//DECLARE_REGISTRY_RESOURCEID(IDR_SCRIPTOUTLINEDLG)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CScriptOutlineDlg)
	COM_INTERFACE_ENTRY(IScriptOutlineDlg)
 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(Web::EventListener)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CScriptOutlineDlg)
END_CONNECTION_POINT_MAP()
*/
#if 0
BEGIN_SINK_MAP(CScriptOutlineDlg)
//   SINK_ENTRY_EX(2, DIID__IEXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
//   SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/1, OnItemClick)
  // SINK_ENTRY_EX(4, DIID__IUITreeControlEvents, /*dispid*/2, OnItemDblClick)
END_SINK_MAP()
#endif

	ErrorCode __stdcall OnDOMEvent(Web::Event* evt);

	void __stdcall OnItemClick(UI::TreeItem* item);
	void __stdcall OnItemDblClick(UI::TreeItem* item);

/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/

DECLARE_CMD_MAP(CScriptOutlineDlg)

	long OnScriptsNewScript(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

// IScriptOutlineDlg
public:
// IUIDlg
	/*
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Script Outline");
		return S_OK;
	}
	*/
// IUIEventHandler
//	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
// IUITreeControlSite
	ErrorCode GetItemText(ULONG itemdata, LONG column, System::StringW* * pVal);

};

}	// LXmlEdit
}

#endif //__SCRIPTOUTLINEDLG_H_
