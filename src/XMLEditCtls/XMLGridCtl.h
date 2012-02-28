#ifndef __XMLGRIDCTL_H_
#define __XMLGRIDCTL_H_

namespace System
{

class CGridItem;
class CGridNode;
class CGridElement;
class CGridContainer;
class CGridContainerNode;

#if 0
enum
{
	Font_ElementName = 0,
	Font_AttributeName,
	Font_Content
};

class CXMLGridCtl; //forward definition of parent class

class ATL_NO_VTABLE CFontNotifyImpl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPropertyNotifySink
{
public:
	CFontNotifyImpl(): m_pParent(NULL)
	{
	}

BEGIN_COM_MAP(CFontNotifyImpl)
	COM_INTERFACE_ENTRY(IPropertyNotifySink)
END_COM_MAP()

public:
	STDMETHOD(OnChanged)(DISPID dispid);
	STDMETHOD(OnRequestEdit)(DISPID dispid){return S_OK;}

	DWORD m_FontNotifyCookie;
	void SetParent(CXMLGridCtl *pParent)
	{
	  m_pParent = pParent;
	}
	CXMLGridCtl *m_pParent;
};
#endif

class XMLGRIDEXT CXMLGridCtl : 
	public UI::Control
//	public IDispEventImpl<1, CXMLGridCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<2, CXMLGridCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
//	public CProxy_IXMLGridCtlEvents< CXMLGridCtl >,
//	public IDropTarget,
//	public ILDOMEventListener
{
public:
	CXMLGridCtl();

	int FinalConstruct();
	void FinalRelease();

//	CComObject<CGridElement>* m_pTree;
	CGridContainerNode* m_pTree;

//	CContainedWindow m_wndEdit;
//	HWND m_hWndEdit;

	LXmlEdit::CEXMLDocument* m_document;
//	CComQIPtr<ILDTDDocument> m_dtdDocument;

	/*
	CAxWindow m_axvert;
	CAxWindow m_axhorz;
	CComQIPtr<IUIScrollBar>	m_horz;
	CComQIPtr<IUIScrollBar>	m_vert;
	*/

	int m_dragging;

	CGridElement* m_pElement;
	LDraw::BBoxi m_buttonRect;

	CGridItem* m_pActiveItem;
	CGridItem* m_pLastFocus;
	CGridContainer* m_commonAncestor;

	LDraw::BBoxi m_areaRect;

	System::StringW* m_userKey;

//	HFONT m_hFont[5];

	uint32 m_dwDragEffect;
	CGridNode* m_pDragParentItem;
	CGridNode* m_pDragBeforeItem;

	int m_bDragBottom;
	CGridItem* m_pDragOverItem;

	void Select(CGridItem* start, CGridItem* end);

	void Paste(Web::Node* parentNode, Web::Node* beforeNode, System::IO::ISequentialByteStream* stream);

	void DrawInsertionMarker(UI::Graphics * hDC);

	void DeleteSelected(CGridItem* pContainer);

	CGridNode* CreateGridNode(LXmlEdit::Node* node);

	void CreateFonts();

//	void OnSize();
	void InitTree();

#if 0
BEGIN_SINK_MAP(CXMLGridCtl)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
   SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()

	void __stdcall OnHorzScroll(long code, long pos);
	void __stdcall OnVertScroll(long code, long pos);
#endif

	/*
BEGIN_MSG_MAP(CXMLGridCtl)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)

	COMMAND_HANDLER(1, EN_CHANGE, OnEditChange)

	CHAIN_MSG_MAP(CComControl<CXMLGridCtl>)
	DEFAULT_REFLECTION_HANDLER()

	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_KEYDOWN, OnEditKeydown)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnEditKeydown)
END_MSG_MAP()
*/
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	LRESULT OnEditChange(int wNotifyCode, int wID, HWND hWndCtl, bool& bHandled);
	LRESULT OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/

#if 0
// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
#endif
	ErrorCode FireOnChanged(long dispID);

public:
#if 0
	STDMETHOD(GetXMLNodeFromDOMNode)(/*[in]*/ IUnknown* nodeUnk, /*[out, retval]*/ IXMLGridNode* *pVal);
	STDMETHOD(SelectItem)(/*[in]*/ IXMLGridItem* item);
	STDMETHOD(HasSelection)(VARIANT_BOOL* pVal);
	STDMETHOD(DeleteSelection)();
	STDMETHOD(get_ActiveNode)(/*[out, retval]*/ IXMLGridNode* *pVal);
	STDMETHOD(get_ActiveParentNode)(/*[out, retval]*/ IXMLGridNode* *pVal);
	STDMETHOD(get_ActiveItem)(/*[out, retval]*/ IXMLGridItem* *pVal);
	STDMETHOD(get_dtdDocument)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(put_dtdDocument)(/*[in]*/ IUnknown* newVal);
	STDMETHOD(CanPaste)(/*[out,retval]*/ VARIANT_BOOL* pVal);
	STDMETHOD(Paste)();
	STDMETHOD(CopyXML)();
	STDMETHOD(DisplayAsTable)();
	STDMETHOD(get_xmlDocument)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(put_xmlDocument)(/*[in]*/ IUnknown* newVal);

	ErrorCode OnDraw(ATL_DRAWINFO& di);
#endif
	virtual void OnRender(UI::Graphics* pGraphics);
	/*
	OLE_COLOR m_clrBackColor;
	BOOL m_bEnabled;
//	CComPtr<IFontDisp> m_pFont;
	OLE_COLOR m_clrForeColor;
	*/

#if 0
// ILDOMEventListener
	STDMETHOD(handleEvent)(ILDOMEvent* evt);
#endif
};

}

#endif //__XMLGRIDCTL_H_
