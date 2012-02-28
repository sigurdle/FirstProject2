// UIEdit.h : Declaration of the CUIEdit

#ifndef __UIEDIT_H_
#define __UIEDIT_H_

#include "resource.h"       // main symbols
#include "UICP.h"


#pragma pack(push, 1)

typedef BYTE	UBYTE;
typedef WORD	UWORD;
typedef void*	APTR;
typedef unsigned char* STRPTR;

#define FS_NORMAL			0
#define FSF_ITALIC		1
#define FSF_BOLD			2
#define FSF_UNDERLINE	4

struct SyntaxElement
{
	COLORREF  FgColor;
	COLORREF  BgColor;
//	UBYTE Style;   /* Bold/Italic/Underlined? */
	UBYTE Flags;
	ULONG	Reserved;
};

struct LineDef
{
	DWORD m_offset;
	DWORD m_ckOffset;
	DWORD	m_lineLength;
	DWORD	m_lineLengthR;
};

struct RLineDef
{
	DWORD m_offset;
	int m_nDispLines;
	DWORD	m_lineLength;
	DWORD	m_lineLengthR;
};

struct SyntaxChunk
{
	DWORD	Length;
	BYTE	Element;
	BYTE	Flags;
};	// 6 bytes

#if 0
//LONG InitCPPSyntax(struct SyntaxHandle *handle);

UWORD ParseCPPLines
(
	struct SyntaxHandle *handle, 
	LineDef** lines,
	BSTR textData,
	UWORD startoffset,
	UWORD maxlength,
	CArray <SyntaxChunk, SyntaxChunk>& SyntaxArr
);
#endif

#pragma pack(pop)

//#import "..\DOMCOREMOD\DOMCoreMod.tlb" no_function_mapping

//#include "..\UIT\UIT.h"

class CUIEdit;

class ATL_NO_VTABLE CEditUndoTyping : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IOleUndoUnit
{
public:
	CEditUndoTyping()
	{
		m_kind = 0;

		m_bRedo = false;
		m_pEdit = NULL;
		m_startCharPos = -1;
		m_len = 0;
		m_text = NULL;
	}

	~CEditUndoTyping()
	{
		if (m_text)
		{
			SysFreeString(m_text);
			m_text = NULL;
		}

		m_kind = 0;
	}

	bool m_bRedo;

public:
	long	m_kind;
	CUIEdit* m_pEdit;
	BSTR m_text;
	long m_startCharPos;
	long m_len;

DECLARE_REGISTRY_RESOURCEID(IDR_UIEDIT)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEditUndoTyping)
	COM_INTERFACE_ENTRY(IOleUndoUnit)
END_COM_MAP()

public:

// IOleUndoUnit
	STDMETHOD(Do)(/* [in] */ IOleUndoManager __RPC_FAR *pUndoManager);
	STDMETHOD(GetDescription)(/* [out] */ BSTR __RPC_FAR *pBstr);
	STDMETHOD(GetUnitType)(/* [out] */ CLSID __RPC_FAR *pClsid, /* [out] */ LONG __RPC_FAR *plID);
	STDMETHOD(OnNextAdd)(void);
};

class ATL_NO_VTABLE CEditUndoParent : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IOleParentUndoUnit // IOleUndoUnit
{
public:
	CEditUndoParent()
	{
		m_flags = UAS_NORMAL;
		m_state = 1;
	}

	void FinalRelease()
	{
		while (!m_undoList.IsEmpty())
		{
			IOleUndoUnit* pUU = (IOleUndoUnit*)m_undoList.RemoveTail();
			pUU->Release();
		}
	}

	UASFLAGS m_flags;

	int m_state;
	CUPtrList m_undoList;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEditUndoParent)
	COM_INTERFACE_ENTRY(IOleUndoUnit)
	COM_INTERFACE_ENTRY(IOleParentUndoUnit)
END_COM_MAP()

public:

// IOleUndoUnit
	STDMETHOD(Do)(/* [in] */ IOleUndoManager __RPC_FAR *pUndoManager);
	STDMETHOD(GetDescription)(/* [out] */ BSTR __RPC_FAR *pBstr);
	STDMETHOD(GetUnitType)(/* [out] */ CLSID __RPC_FAR *pClsid, /* [out] */ LONG __RPC_FAR *plID);
	STDMETHOD(OnNextAdd)(void);

// IOleParentUndoUnit
	STDMETHOD(Open)(/* [in] */ IOleParentUndoUnit __RPC_FAR *pPUU);
	STDMETHOD(Close)(/* [in] */ IOleParentUndoUnit __RPC_FAR *pPUU, /* [in] */ BOOL fCommit);
	STDMETHOD(Add)(/* [in] */ IOleUndoUnit __RPC_FAR *pUU);
	STDMETHOD(FindUnit)(/* [in] */ IOleUndoUnit __RPC_FAR *pUU);
	STDMETHOD(GetParentState)(/* [out] */ DWORD __RPC_FAR *pdwState);
};

class CAutoListMembersWindow;

/////////////////////////////////////////////////////////////////////////////
// CUIEdit
class ATL_NO_VTABLE CUIEdit : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComControl<CUIEdit>,
	public IConnectionPointContainerImpl<CUIEdit>,

	public IDispatchImpl<IUIEdit, &IID_IUIEdit, &LIBID_UILib>,

	public IPersistStreamInitImpl<CUIEdit>,
	public IOleControlImpl<CUIEdit>,
	public IOleObjectImpl<CUIEdit>,
	public IOleInPlaceActiveObjectImpl<CUIEdit>,
	public IViewObjectExImpl<CUIEdit>,
	public IOleInPlaceObjectWindowlessImpl<CUIEdit>,
	public ISupportErrorInfo,
	public IPersistStorageImpl<CUIEdit>,
	public ISpecifyPropertyPagesImpl<CUIEdit>,
	public IQuickActivateImpl<CUIEdit>,
	public IDataObjectImpl<CUIEdit>,
	public IProvideClassInfo2Impl<&CLSID_UIEdit, &DIID__IUIEditEvents, &LIBID_UILib>,
	public IPropertyNotifySinkCP<CUIEdit>,
	public CComCoClass<CUIEdit, &CLSID_UIEdit>,

	public CProxy_IUIEditEvents< CUIEdit >,
	public IDispEventImpl<1, CUIEdit, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CUIEdit, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CUIEdit, &DIID__ITextDataEvents2, &LIBID_UILib, 1, 0>
//	public ProcessTargetCommands
{
public:
	CUIEdit();
	~CUIEdit();

	int FinalConstruct();
	void FinalRelease();

	int m_autoListStartOffset;
	int m_autoListEndOffset;

	CComObject<CAutoListMembersWindow>* m_pAutoListMembersWindow;

	ITextDataPtr m_tdp;

	CEditUndoTyping* m_pRecentUndoTyping;

	VARIANT_BOOL m_bMultiLine;
	BYTE m_bHorzSB;
	BYTE m_bVertSB;
	BYTE m_bLeftBar;
	int m_lborWidth;
	int m_case;

	int m_border;

	CComQIPtr<IOleUndoManager> m_undoManager;

	BSTR GetTextData()
	{
		ATLASSERT(m_tdp != NULL);

		BSTR data;
		m_tdp->get_data(&data);
		return data;
	}
	int GetTextLen()
	{
		ATLASSERT(m_tdp != NULL);

		long length;
		m_tdp->get_len(&length);
		return length;
	}

	void InsertText(int offset, BSTR data, int len);
	void DeleteText(int offset, int len);
	void ReplaceText(int offset, int deletelen, BSTR data);

// Cursor location
	int m_line;	// Current line
	int m_rline;
	int m_col;	// Actual column
	int m_rcol;
	int m_idealcolX;	// Desired column in pixels
	int m_offset;	// Offset into textData

	long m_tabSize;

	int m_selStart;
	int m_selEnd;
	int m_initSel;

	BOOL m_bShowCursor;

	CArray<RLineDef*, RLineDef*> m_rlinesArr;
	CArray<LineDef*, LineDef*> m_linesArr;

	CArray<SyntaxChunk,SyntaxChunk&> m_styleChunks;

	CArray<SyntaxElement,SyntaxElement&> m_styles;

	int m_spaceWidth;
//	int m_cw;
	int m_ch;

	int m_dragging;

	VARIANT_BOOL m_bShowTabs;
	VARIANT_BOOL m_bShowEOL;
	VARIANT_BOOL m_bShowSpace;
	VARIANT_BOOL m_bWordWrap;
	VARIANT_BOOL m_bLineNumbers;

	CAxWindow m_axvert;
	CAxWindow m_axhorz;
	CComQIPtr<IUIScrollBar>	m_vert;
	CComQIPtr<IUIScrollBar>	m_horz;
	CRect m_textArea;

	CComPtr<IFontDisp> m_pFont;

	void CreateSyntaxFonts();

	int GetMaxLineLength();

	void ClearSelectionAndInvalidate();
	void SetSelectionAndInvalidate(int start, int end);

	void BuildLineOffsets();
	void BuildRLineOffsets();

	void CalcLineCol(int offset);
	void CalcRLineCol(int offset);

//	void BuildLines();
//	int GetLineLength(int line);
	int CountLines();	// TODO remove

//	int Column2VColumn(int line, int col);	// Get the visual column of cursor, tab adjusted
//	int VColumn2Column(int line, int vcol);

	int ColumnFromPointX(int line, int x);
	int PointXFromColumn(int line, int col);

	void ShowCursor();
	void HideCursor();
	void ToggleCursor();
	void DrawCursor(HDC hDC);

	void ScrollIntoView(int line, int col);

//	void FormatRange(int start, int len, WORD style);
	//void ClearFormatting();

//	void Format(); // TODO, remove

	void MoveCursorLeft();
	void MoveCursorRight();
	void MoveCursorUp();
	void MoveCursorDown();
	void MoveCursorBegLine();
	void MoveCursorEndLine();
	void MoveCursorPageUp();
	void MoveCursorPageDown();

	void InvalidateLine(int line);
	void InvalidateRange(int startchar, int endchar);

	void InsertChar(WCHAR ch);
	void DeleteChar(int offset, int len);

	void Find(LPCTSTR findStr);

	void LocateCursor(int offset);
	void LocateCursor(int line, int col);

	void CopySelectionToClipboard();
	void PasteFromClipboard();
	void DeleteSelection();

	void ResetVScrollSize();
	void ResetHScrollSize();

//	IMETHOD void Update();
	void OnChange();

	void OnSize(BOOL bBuildLines);
//	BOOL OnSetCursor(UINT nHitTest, UINT message);
//	void OnMouseWheel(UINT nFlags, short zDelta);

// method
	long GetTextOffset()
	{
		return m_offset;
	}

	void OnMovedCursor();

	void OnEditFind();
	void OnFindMatchingBracket();

DECLARE_REGISTRY_RESOURCEID(IDR_UIEDIT)
//DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUIEdit)
	COM_INTERFACE_ENTRY(IUIEdit)
//	COM_INTERFACE_ENTRY(ICommandTarget)

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
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CUIEdit)
	CONNECTION_POINT_ENTRY(DIID__IUIEditEvents)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CUIEdit)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
   SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
   SINK_ENTRY_EX(3, DIID__ITextDataEvents2, /*dispid*/1, OnTextContentChanged)
   SINK_ENTRY_EX(3, DIID__ITextDataEvents2, /*dispid*/2, OnTextInsertText)
   SINK_ENTRY_EX(3, DIID__ITextDataEvents2, /*dispid*/3, OnTextDeletedText)
END_SINK_MAP()

	void __stdcall OnHorzScroll(long code, long pos);
	void __stdcall OnVertScroll(long code, long pos);

	void __stdcall OnTextContentChanged();
	void __stdcall OnTextInsertText(long offset, long len);
	void __stdcall OnTextDeletedText(long offset, long len);

BEGIN_PROP_MAP(CUIEdit)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_MSG_MAP(CUIEdit)
	CHAIN_MSG_MAP(CComControl<CUIEdit>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_NCDESTROY, OnNcDestroy)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_CHAR, OnChar)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IUIEdit,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

	HRESULT OnDraw(ATL_DRAWINFO& di);

	/*
DECLARE_CMD_MAP(CUIEdit)

	LRESULT OnEditCut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditPaste(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnEditCutCopyUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnEditPasteUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnEditDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnEditDeleteUpdate(long iid, IUICmdUpdate* pCmdUI);
	*/

// IUIEdit
public:
	STDMETHOD(get_line)(/*[out, retval]*/ long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_rline;
		return S_OK;
	}
	STDMETHOD(get_column)(/*[out, retval]*/ long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_rcol;
		return S_OK;
	}
	STDMETHOD(get_viewEOLs)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_viewEOLs)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_viewSpaces)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_viewSpaces)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_viewTabs)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_viewTabs)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_viewWhitespace)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_viewWhitespace)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_tabSize)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_tabSize)(/*[in]*/ long newVal);
	STDMETHOD(get_LineHeight)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_LineHeight)(/*[in]*/ long newVal);
	STDMETHOD(get_font)(/*[out, retval]*/ IFontDisp* *pVal);
	STDMETHOD(put_font)(/*[in]*/ IFontDisp* newVal);
	STDMETHOD(get_cursorBox)(/*[out, retval]*/ RECT *pVal);
	STDMETHOD(get_lineNumbers)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_lineNumbers)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_wordWrap)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_wordWrap)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_multiLine)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_multiLine)(/*[in]*/ VARIANT_BOOL newVal);

	STDMETHOD(ReplaceSelText)(/*[in]*/ BSTR data, /*[in]*/ long len);
	STDMETHOD(GetSelText)(/*[out,retval]*/ BSTR* pVal);
	STDMETHOD(GetSel)(/*[out]*/ long* start, /*[out]*/ long* end);
	STDMETHOD(SetSel)(/*[in]*/ long nStartChar, /*[in]*/ long nEndChar, /*[in]*/ VARIANT_BOOL bNoScroll);
	STDMETHOD(ReplaceText)(/*[in]*/ long offset, /*[in]*/ long len, /*[in]*/ BSTR data, /*[in]*/ long datalen);
	STDMETHOD(CanPaste)(/*[in]*/ unsigned long nFormat, /*[out,retval]*/ VARIANT_BOOL* pVal);
	STDMETHOD(Paste)();
	STDMETHOD(Copy)();
	STDMETHOD(Cut)();
	STDMETHOD(Clear)();
	STDMETHOD(NewStyle)(/*[out,retval]*/ long* index);
	STDMETHOD(SetStyle)(/*[in]*/ long index, /*[in]*/ DWORD fgColor, /*[in]*/ DWORD bgColor);
	STDMETHOD(ClearFormatting)();
	STDMETHOD(FormatRange)(/*[in]*/ long start, /*[in]*/ long len, /*[in]*/ long styleIndex, /*[in]*/ long* styleElementIndex);
	STDMETHOD(GetText)(/*[out,retval]*/ BSTR* text);
	STDMETHOD(SetText)(/*[in]*/ BSTR text);
	STDMETHOD(getCursorPosOffset)(/*[out,retval]*/ long* pVal);
	STDMETHOD(setCursorPosOffset)(/*[in]*/ long offset);
	STDMETHOD(get_undoManager)(/*[out, retval]*/ IOleUndoManager* *pVal);
	STDMETHOD(put_undoManager)(/*[in]*/ IOleUndoManager* newVal);
	STDMETHOD(get_horzScroll)(/*[out, retval]*/ DWORD *pVal);
	STDMETHOD(put_horzScroll)(/*[in]*/ DWORD newVal);
	STDMETHOD(get_vertScroll)(/*[out, retval]*/ DWORD *pVal);
	STDMETHOD(put_vertScroll)(/*[in]*/ DWORD newVal);
	STDMETHOD(get_textDocument)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(put_textDocument)(/*[in]*/ IDispatch* newVal);
	STDMETHOD(AutoListPopup)();
	STDMETHOD(AutoList)(/*[out,retval]*/ IUIAutoListWindow* *pVal);
};

#endif //__UIEDIT_H_
