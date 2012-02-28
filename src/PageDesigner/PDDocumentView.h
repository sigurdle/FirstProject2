#include "PageDesignerCP.h"

#include "..\UIT\UIT.h"

class CPDObjectSelected;
class CPDObjectGroupSelected;
class CPDObjectFrameSelected;
class CPathSelection;

//HRESULT WINAPI myfunc(void* pv, REFIID riid, LPVOID* ppv, DWORD dw);
class CPDObjectSelection;

class ATL_NO_VTABLE CPDDocumentView : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CUIDialogImpl<CPDDocumentView, CWindowImpl<CPDDocumentView> >,
	public IPDDocumentView,
	public ProcessTargetCommands,

	public IDispEventImpl<1, CPDDocumentView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CPDDocumentView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<3, CPDDocumentView, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>,
	public CProxy_IPDDocumentViewEvents< CPDDocumentView >,
	public IConnectionPointContainerImpl<CPDDocumentView>,

	public CNotifyGetImpl<CPDDocumentView>,
	public IPDCustomRenderer,

	public IOleDocumentView,
	public IOleInPlaceObject, // IOleWindow
	public IOleInPlaceActiveObject, // IOleWindow

	public IPrint,
	public IOleCommandTarget
{
public:
	CPDDocumentView()
	{
		m_document = NULL;
		m_activeSpread = NULL;

		m_pBitmap = NULL;

		m_dragging = 0;
		m_startDragCursor = NULL;

		m_magnify = 1.0;

		m_bRulers = true;
		m_bViewTransparencyGrid = false;
		m_bAlt = false;

		m_rulerOffset.x = 0;
		m_rulerOffset.y = 0;

		m_pivotPt.x = 0;
		m_pivotPt.y = 0;

		m_activeLayer = NULL;
		m_activeLayerGroup = NULL;

		m_pActiveObject = NULL;
		m_pActivePath = NULL;

		m_activeTool = 0;

		m_hWndSizeGrip = NULL;

		m_bInvalid = true;

		m_bCurPosOnRulerVisible = false;
		m_bBrushSizeVisible = false;

		m_nIDTimer = 0;

	// Text Range selection
/*		m_curContainer = NULL;
		m_curOffset = 0;

		m_initContainer = NULL;
		m_initOffset = 0;
*/

		m_objectSelection = NULL;

	// IOleDocument
		m_fInPlaceActive = FALSE;
		m_fUIActive = FALSE;
		m_hOleMenu = NULL;
		m_hSharedMenu = NULL;
	}

	~CPDDocumentView()
	{
		DeselectAll();

		if (m_pBitmap)
		{
			delete m_pBitmap;
			m_pBitmap = NULL;
		}
	}

	int FinalConstruct();
	void FinalRelease();

	IPDDocument* m_document;
	IPDSpread* m_activeSpread;
	CComQIPtr<IPDSpreadMaster> m_activeMasterSpread;

	CComPtr<IPDObjectGroup> m_activeGroup;

//	CComPtr<IPDTextRange> m_range;
	CComPtr<IPDTextSelection> m_range;

	CComObject<CPDObjectSelection>* m_objectSelection;

	/*
	IDOMNode* m_curContainer;
	long m_curOffset;

	IDOMNode* m_initContainer;
	long m_initOffset;
	*/

	CDblPoint m_activeSpreadOffset;

	Gdiplus::RectF m_oldBounds;

	bool m_bCurPosOnRulerVisible;
	bool m_bBrushSizeVisible;

	int m_dragging;
	HCURSOR m_startDragCursor;

	bool m_bInvalid;

	int m_hit;
	CDblPoint m_dpt;
	CDblPoint m_dstartpt;
	CDblPoint m_doldpt;

	CPoint m_oldpt;
	CPoint m_startpt;

	CPoint m_point;
	CPoint m_oldpoint;
	CPoint m_startpoint;

	CPoint m_scrollpos;

	CDblPoint m_rulerOffset;

	CComQIPtr<IPDMatrix> m_matrix;

	long m_curveCp;
	long m_curveCtl;
	long m_curveDir;

	int m_spine;
	int m_maxPages;

	bool m_bRulers;
	bool m_bViewTransparencyGrid;

	CPDObjectSelected* m_pActiveObject;
	CArray<CPDObjectSelected*,CPDObjectSelected*> m_targetObjects;
	RectD	m_objectsBoundingBox;

	CComPtr<IPDGuide> m_newGuide;

	CComPtr<IPDLayer> m_activeLayer;
	IPDObjectGroup* m_activeLayerGroup;

	HWND m_hWndSizeGrip;

	CAxWindow m_axvert;
	CComQIPtr<IUIScrollBar> m_vert;

	CAxWindow m_axhorz;
	CComQIPtr<IUIScrollBar> m_horz;

	CRect m_areaRect;
	double m_magnify;

	CDblPoint m_brushSize;

	CDblPoint m_pivotPt;
	CRect m_zoomRect;
	CComPtr<IPDMatrix> m_freeTransformMatrix;
//	CComPtr<IPDMatrix> m_oldfreeTransformMatrix;

	int m_nIDTimer;

	Gdiplus::Bitmap*	m_pBitmap;

	class CHitData
	{
	public:
		int hit;
		long anchor;
		long segment;
		long ctl;
		double t;

		ILDOMNode* pNode;
		long offset;
//		CPathSelection* pPath;
		CComPtr<IPDPath> path;

		CHitData()
		{
			hit = 0;

			anchor = -1;
			segment = -1;
			ctl = 0;
			t = -1;

			pNode = NULL;
			offset = -1;
//			pPath = NULL;
		}
	};

	bool m_bAlt;

	long m_activeTool;

	PointD m_offsetPt;
	CPathSelection* m_pActivePath;

	CComPtr<IPDObject> m_objectToPlace;

	RectD m_newObjectBounds;

	void SetMatrix();
	void CalculateObjectsBoundingBox();
	void CalculateObjectsExpandedBoundingBox(RectD* objectsBoundingBox);

	RECT GetWindowRectFromSpreadRect(Gdiplus::RectF& spreadRect);

//	int FreeTransformHit(PointD dpt);

	//void RotateObject(IPDObject* object, PointD woldpt, PointD wpt, double cx, double cy);
	IPDMatrix* GetRotateObjectMatrix(PointD woldpt, PointD wpt, double cx, double cy);

	CPathSelection* GetPDPathSelected(IPDPath* pdpath);

	CPDObjectSelected* GetPDObjectSelected(IPDObjectUnknown* object);
	CPDObjectSelected* SelectPDObject(IPDObjectUnknown* object, UINT nFlags, BOOL bSelectPoints);
	void DeselectPDObject(IPDObjectUnknown* object);
	bool IsPDObjectSelected(IPDObjectUnknown* object);
	void DeselectAll();

	void DrawCurPosOnRuler(HDC hDC, CPoint point);
	void DrawBrushOutline(HDC hDC, CDblPoint point);
	void EraseBrushOutline();

	void DrawTextSelection(HDC hDC);

	HRESULT GetObjectUnderPoint(CDblPoint pt, int tool, CHitData* hit, IPDObject** pVal);
	HRESULT GetObjectUnderPoint(IPDObject* parent, IPDMatrix* pdmatrix, CDblPoint pt, int tool, CHitData* hit, IPDObject** pVal);

	IPDObject* FindPointUnderPoint(IPDObjectGroup* group, CDblPoint pt, long& curveCp, long& curveCtl);

	BOOL FindPointUnderPoint(IPDObjectFrame* frame, CDblPoint pt, long& curveCp, long& curveCtl);

	void SelectObjectsWithinRect(Gdiplus::RectF& rect, int tool, int& hit);
	void SelectObjectsWithinRect(IPDObject* object, IPDMatrix* matrix, Gdiplus::RectF& rect, int tool, int& hit);

	void OnSize();
	BOOL OnSetCursor();
	BOOL OnSetCursor(POINT point);
	void OnMouseMove();
	void OnMouseMove(UINT nFlags, POINT point);

	void ZoomToRect2(double left, double top, double right, double bottom);
	long GetPageIndexUnderPoint(CDblPoint pt);

//	BOOL MoveCursorLeft(IDOMNode* startContainer, long startOffset, IDOMNode* *container, long* offset);
//	BOOL MoveCursorRight(IDOMNode* startContainer, long startOffset, IDOMNode* *container, long* offset);

	void CopyTargetObjectsToClipboard(IDataObject* dataObject);
	void PasteObjectsFromClipboard();
	void PasteObjectsIntoFromClipboard();
	void ClearTargetObjects();
	IPDObjectGroup* GetObjectGroupFromClipboard();

	void SetTextWrapOnObjects(PDTextWrap textWrap);
	void OnTextWrapUpdate(PDTextWrap textWrap, IUICmdUpdate* pCmdUI);
	void SetParagraphAlign(int align);
	void UpdateParagraphAlign(long align, IUICmdUpdate* pCmdUI);

	IPDTextFont* GetActiveStoryRangeTextFont();
	IPDTextPara* GetActiveStoryRangeTextPara();

	bool IsGuideSelected(IPDGuide* guide);

	void CopySelectionToClipboard();
	void ClearSelection();

	void SetObjectSelection(IPDObjectSelection* selection);

	void RenderGuides(IPDRenderer* renderer, IPDSpread* spread, bool bDrawDeselected, bool bDrawSelected);

	IPDGuide* GetGuideUnderPoint(double x, double y);

	CArray<IPDPage*,IPDPage*> m_selectedPages;

	BOOL IsPageSelected(IPDPage* page)
	{
		for (int i = 0; i < m_selectedPages.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_selectedPages[i], page))
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	void SelectPage(IPDPage* page)
	{
		ATLASSERT(!IsPageSelected(page));

		m_selectedPages.Add(page);
	}

	void DeselectPage(IPDPage* page)
	{
		ATLASSERT(IsPageSelected(page));

		for (int i = 0; i < m_selectedPages.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_selectedPages[i], page))
			{
				m_selectedPages.RemoveAt(i);
				break;
			}
		}
	}

	void DefineSymbol(IPDSymbol* symbol);

// IOleDocumentView
	CRect m_rect;
	BOOL m_fInPlaceActive;
	BOOL m_fUIActive;

	CComPtr<IOleInPlaceSite>		m_spInPlaceSite;
	CComPtr<IOleInPlaceFrame>		m_spInPlaceFrame;
	CComPtr<IOleInPlaceUIWindow>	m_spInPlaceUIWindow;

	HMENU                      m_hSharedMenu;
	HOLEMENU                   m_hOleMenu;
	OLEMENUGROUPWIDTHS         m_mgw;

	OLEINPLACEFRAMEINFO        m_FrameInfo;

	HRESULT ActivateInPlace();
	HRESULT ActivateInPlace(HWND hParent);
	HRESULT DeactivateInPlace();
	HRESULT ActivateUI();
	HRESULT DeactivateUI();
	void MergeMenus();

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDDocumentView)
	COM_INTERFACE_ENTRY(IPDDocumentView)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(IPDCustomRenderer)

	COM_INTERFACE_ENTRY(IOleDocumentView)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IPrint)
	COM_INTERFACE_ENTRY(IOleCommandTarget)

//	COM_INTERFACE_ENTRY_FUNC(IID_IOleObject, 0, myfunc)
END_COM_MAP()

BEGIN_SINK_MAP(CPDDocumentView)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
   SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
//   SINK_ENTRY_EX(3, DIID__IPDDocumentEvents, /*dispid*/1, OnDocumentSetupChanged)
END_SINK_MAP()

	void __stdcall OnHorzScroll(long code, long pos);
	void __stdcall OnVertScroll(long code, long pos);

//	void __stdcall OnDocumentSetupChanged();

	typedef CUIDialogImpl<CPDDocumentView, CWindowImpl<CPDDocumentView> > baseClass;
	//typedef CUIMDIFrameImpl<CPageDesignerFrame, IUIFrame> baseClass;

BEGIN_MSG_MAP(CPDDocumentView)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
	MESSAGE_HANDLER(WM_SYSKEYDOWN, OnSysKeyDown)
	MESSAGE_HANDLER(WM_SYSKEYUP, OnSysKeyUp)
	MESSAGE_HANDLER(WM_CHAR, OnChar)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)

	MESSAGE_HANDLER(WM_SYSCHAR, OnSysChar)
	MESSAGE_HANDLER(WM_SYSDEADCHAR, OnSysDeadChar)
	CHAIN_MSG_MAP(baseClass)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSysDeadChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
//		MessageBeep(-1);
		return DefWindowProc(uMsg, wParam, lParam);
	}

	LRESULT OnSysChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
//		MessageBeep(-1);
		return DefWindowProc(uMsg, wParam, lParam);
	}

DECLARE_CMD_MAP(CPDDocumentView)

	LRESULT OnFilePlace(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnEditCut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditPaste(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditClear(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditPasteInto(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditPasteSpecial(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnEditPasteSpecialUpdate(long iid, IUICmdUpdate* pCmdUI);

	void OnEditCutCopyClearUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnEditPasteUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnEditPasteIntoUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnCharacterFontface(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnCharacterFontfaceUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnCharacterFontsize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnCharacterFontsizeUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnCharacterBold(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnCharacterLineheightUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnTextWrapNone(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnTextWrapBBox(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnTextWrapShape(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnTextWrapObject(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnTextWrapColumn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnTextWrapNoneUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnTextWrapBBoxUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnTextWrapShapeUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnTextWrapObjectUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnTextWrapColumnUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnTextWrapOffset(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnTextWrapOffsetUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnLayoutMarginsAndColumns(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnLayoutCreateGuides(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnTypeCreateOutlines(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnCharacter(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnParagraph(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnParagraphAlignLeft(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnParagraphAlignCenter(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnParagraphAlignRight(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnParagraphJustifyLeft(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnParagraphJustifyCenter(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnParagraphJustifyRight(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnParagraphJustifyAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	void OnParagraphAlignLeftUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnParagraphAlignCenterUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnParagraphAlignRightUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnParagraphJustifyLeftUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnParagraphJustifyCenterUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnParagraphJustifyRightUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnParagraphJustifyAllUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnObjectGroup(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnObjectGroupUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnObjectUngroup(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnObjectUngroupUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnObjectCompoundPathsMake(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnObjectCompoundPathsRelease(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnObjectReversePath(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnObjectPathAddAnchorPoints(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnObjectPathAddAnchorPointsUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnObjectFitContentToFrame(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnObjectFitFrameToContent(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCenterContent(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFitContentProportionally(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnObjectTextFrameOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnObjectTextFrameOptionsUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnObjectPathTypeOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnObjectPathTypeOptionsUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnObjectContentGraphic(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnObjectContentText(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnObjectContentUnassigned(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnObjectRasterize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnObjectRasterizeUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnTransparencyMakeOpacityMask(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnTransparencyReleaseOpacityMask(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnTransparencyReleaseOpacityMaskUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT CPDDocumentView::OnTransparencyEnableOpacityMask(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void CPDDocumentView::OnTransparencyEnableOpacityMaskUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT CPDDocumentView::OnTransparencyLinkOpacityMask(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void CPDDocumentView::OnTransparencyLinkOpacityMaskUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnSymbolsNewSymbol(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSymbolBreakLinktoSymbol(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnObjectArrangeBringToFront(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnObjectArrangeBringForward(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnObjectArrangeSendBackward(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnObjectArrangeSendToBack(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnObjectArrangeHigherUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnObjectArrangeLowerUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnViewZoomIn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewZoomOut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewActualSize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewRulers(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnViewActualSizeUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnViewRulersUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnViewTransparencyGrid(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnViewTransparencyGridUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnEditDefinePattern(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnEditDefinePatternUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnWindowNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// hm..
	LRESULT OnPagesCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// IPDDocumentView
public:
	STDMETHOD(getViewBox)(/*[out,retval]*/ RECT* pVal);
	STDMETHOD(get_rulers)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_rulers)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(setScrollPosXY)(/*[in]*/ long posx, /*[in]*/ long posy);
	STDMETHOD(get_activeSpread)(/*[out, retval]*/ IPDSpread* *pVal);
	STDMETHOD(put_activeSpread)(/*[in]*/ IPDSpread* newVal);

// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		return m_document->get_fileTitle(pVal);
	}

	STDMETHOD(OnActivate)(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView);

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID);

// IPDCustomRenderer
	STDMETHOD(RenderObject)(IPDRenderer* renderer, IPDObject* object);

// ICommandTarget
	STDMETHODIMP OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);

public :
	STDMETHOD(setRulerOrigin)(/*[in]*/ double x, /*[in]*/ double y);

// IOleDocumentView
	STDMETHOD(SetInPlaceSite)(IOleInPlaceSite __RPC_FAR *pIPSite);
	STDMETHOD(GetInPlaceSite)(IOleInPlaceSite __RPC_FAR *__RPC_FAR *ppIPSite);
	STDMETHOD(GetDocument)(IUnknown __RPC_FAR *__RPC_FAR *ppunk);
	STDMETHOD(SetRect)(LPRECT prcView);
	STDMETHOD(GetRect)(LPRECT prcView);
	STDMETHOD(SetRectComplex)(LPRECT prcView, LPRECT prcHScroll, LPRECT prcVScroll, LPRECT prcSizeBox);
	STDMETHOD(Show)(BOOL fShow);
	STDMETHOD(UIActivate)(BOOL fUIActivate);
	STDMETHOD(Open)(void);
	STDMETHOD(CloseView)(DWORD dwReserved);
	STDMETHOD(SaveViewState)(LPSTREAM pstm);
	STDMETHOD(ApplyViewState)(LPSTREAM pstm);
	STDMETHOD(Clone)(IOleInPlaceSite __RPC_FAR *pIPSiteNew, IOleDocumentView __RPC_FAR *__RPC_FAR *ppViewNew);

// IOleWindow
	STDMETHOD(GetWindow)(HWND __RPC_FAR *phwnd);
	STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode);

// IOleInPlaceObject
	STDMETHOD(InPlaceDeactivate)(void);
	STDMETHOD(UIDeactivate)(void);
	STDMETHOD(SetObjectRects)(LPCRECT lprcPosRect, LPCRECT lprcClipRect);
	STDMETHOD(ReactivateAndUndo)(void);

// IOleInPlaceActiveObject
	STDMETHODIMP TranslateAccelerator( 
            /* [in] */ LPMSG lpmsg);
	STDMETHODIMP OnFrameWindowActivate( 
            /* [in] */ BOOL fActivate);
	STDMETHODIMP OnDocWindowActivate( 
            /* [in] */ BOOL fActivate);
	STDMETHODIMP ResizeBorder( 
            /* [in] */ LPCRECT prcBorder,
            /* [unique][in] */ IOleInPlaceUIWindow *pUIWindow,
            /* [in] */ BOOL fFrameWindow);
	STDMETHODIMP EnableModeless(/* [in] */ BOOL fEnable);

// IPrint
	STDMETHOD(SetInitialPageNum)(LONG nFirstPage);
	STDMETHOD(GetPageInfo)(LONG __RPC_FAR *pnFirstPage, LONG __RPC_FAR *pcPages);
	STDMETHOD(Print)(DWORD grfFlags, DVTARGETDEVICE __RPC_FAR *__RPC_FAR *pptd, PAGESET __RPC_FAR *__RPC_FAR *ppPageSet, STGMEDIUM __RPC_FAR *pstgmOptions, IContinueCallback __RPC_FAR *pcallback, LONG nFirstPage, LONG __RPC_FAR *pcPagesPrinted, LONG __RPC_FAR *pnLastPage);

// IOleCommandTarget
	STDMETHOD(QueryStatus)(const GUID __RPC_FAR *pguidCmdGroup, ULONG cCmds, OLECMD __RPC_FAR prgCmds[  ], OLECMDTEXT __RPC_FAR *pCmdText);
	STDMETHOD(Exec)(const GUID __RPC_FAR *pguidCmdGroup, DWORD nCmdID, DWORD nCmdexecopt, VARIANT __RPC_FAR *pvaIn, VARIANT __RPC_FAR *pvaOut);

BEGIN_CONNECTION_POINT_MAP(CPDDocumentView)
	CONNECTION_POINT_ENTRY(DIID__IPDDocumentViewEvents)
END_CONNECTION_POINT_MAP()

};
