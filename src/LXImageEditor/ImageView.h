#ifndef __IMAGEVIEW_H_
#define __IMAGEVIEW_H_

//#include "resource.h"       // main symbols

#include "ImageApp.h"

namespace System
{
namespace ImageEdit
{

class CImageView;

class CPImageLayerUnknown : public System::Object
{
public:
	CImageView* m_pView;
	ImageLayerUnknown* m_layerUnknown;
};

class CPImageLayerGroup : public CPImageLayerUnknown
{
public:
	vector<CPImageLayerUnknown*> m_subLayers;
};

class CPImageLayerBitmap : public CPImageLayerUnknown
{
public:
};

class CStrokeObject;
class CImageDocument;

/*
class ImageEditorExt PaintStroke : public Control
{
public:

};
*/

class ImageEditorExt CImageView : public UI::Control, public UI::IScrollContent, public UI::IStylusPlugin
{
public:
	CTOR CImageView();

	double m_pressure;

//	int FinalConstruct();
//	void FinalRelease();

	//CRect m_imageRect;
	double m_magnify;
	bool m_bRulers;

	int m_dragging;

	CImageDocument* m_document;
	CPImageLayerGroup* m_pImageLayerGroup;
	CPImageLayerUnknown* m_pActiveLayer;

	ImageLayerUnknown* m_activeLayer;

	CGroupImageObject* m_pActiveGroup;
	LDraw::Bitmap* m_pActiveBitmap;

//	IImageTool* m_pActiveTool;

	virtual void SetOwnerWindow(UI::VisualContentSource* pWindow);

/*	IEViewGroup* m_viewGroup;
	*/

	ImageLayerUnknown* GetActiveLayer()
	{
		return m_activeLayer;
	}

	void OnSize();

	virtual void OnPacket(UI::StylusPacket* packet);

#if 0
BEGIN_MSG_MAP(CImageView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
END_MSG_MAP()
#endif

//	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, WINBOOL& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, WINBOOL& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, WINBOOL& bHandled);
//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, WINBOOL& bHandled);
	void OnLButtonDown(LDraw::PointD point);
	void OnLButtonUp(LDraw::PointD point);
	void OnMouseMove(LDraw::PointD point);
	void OnTimer(UI::Graphics* pGraphics);

DECLARE_CMD_MAP(CImageView)

	void OnViewZoomIn(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	void OnViewZoomOut(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	long OnNewLayerViaCut(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	long OnNewLayerViaCopy(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	long OnNewAdjustmentLayerPosterize(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	long OnLayerMaskRevealAll(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	long OnLayerMaskHideAll(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	long OnLayerMaskEnable(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	long OnDepthAdd(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	long OnDepthClear(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	long OnLayerStyleDropShadow(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);

/*
	LRESULT OnEditCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, WINBOOL& bHandled);
	LRESULT OnEditPaste(WORD wNotifyCode, WORD wID, HWND hWndCtl, WINBOOL& bHandled);
	void OnEditPasteUpdate(long iid, IUICmdUpdate* pCmdUI);
*/
// IImageView
public:
	CImageDocument* GetDocument();

//	STDMETHOD(get_document)(/*[out, retval]*/ IDTDDocument* *pVal);
//	STDMETHOD(put_document)(/*[in]*/ IWebXMLDocument* newVal);
// IUIDlg
//	STDMETHOD(OnActivate)(WINBOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView);
// ILDOMEventListener
//	void handleEvent(System::Event* evt);

	void OnRender(UI::Graphics* pGraphics);
	LDraw::SizeD OnMeasure(LDraw::SizeD availSize);

	//IScrollContent
	LDraw::PointD OnSetPos(LDraw::PointD pos);
};

class MoveTool : public System::Object, public IImageTool
{
public:

	CTOR MoveTool();

	int m_hit;
	int m_dragging;

	long m_nTool;

	LDraw::matrix3f m_matrix;

	LDraw::PointD wstartpt;
	LDraw::PointD m_offsetPt;

#if 0
	void DrawRectangularMarquee(HDC hDC, CRect& rect)
	{
		Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
	}
#endif

	virtual ErrorCode OnLButtonDown(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags);
	virtual ErrorCode OnLButtonUp(CImageView* pView, LDraw::PointD point, UINT nFlags);
	virtual ErrorCode OnMouseMove(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags);
};

class SelectTool : public System::Object, public IImageTool
{
public:

	CTOR SelectTool()
	{
		m_dragging = 0;
	}

	int m_dragging;

	long m_nTool;
	LDraw::RectD m_rect;

	void DrawMarquee(MSWindows::HDC hDC, LDraw::RectI& rect);

	virtual ErrorCode OnLButtonDown(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags);

	virtual ErrorCode OnLButtonUp(CImageView* pView, LDraw::PointD point, UINT nFlags);

	virtual ErrorCode OnMouseMove(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags);
};

class MagicWandTool : public SelectTool
{
public:
	CTOR MagicWandTool();
};

class SelectEllipseTool : public SelectTool
{
public:
	CTOR SelectEllipseTool();
};

class SelectRectangleTool : public SelectTool
{
public:
	CTOR SelectRectangleTool();
};

class PaintbrushTool : public System::Object, public IImageTool
{
public:
	CTOR PaintbrushTool();

//	ILXImageApp* m_app;

	int m_dragging;
	CStrokeObject* m_pStroke;
	double m_oldpressure;

	virtual ErrorCode OnLButtonDown(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags);

	virtual ErrorCode OnLButtonUp(CImageView* pView, LDraw::PointD point, UINT nFlags);

	virtual ErrorCode OnMouseMove(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags);
};

}	// ImageEdit
}

#endif //__IMAGEVIEW_H_
