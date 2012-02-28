#ifndef __SVGTOOLSDLG_H_
#define __SVGTOOLSDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CLXMLEditorApp;

class CSVGToolsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSVGToolsDlg, &CLSID_NULL/*SVGToolsDlg*/>,

//	public ISVGToolsDlg,
	public UI::Control,
//	public CUIDialogImpl<CSVGToolsDlg, CWindowImpl<CSVGToolsDlg> >,
//	public ILElementBehavior,

	public Web::ICSSStyleDeclarationHandler
//	public CUIEventHandlerImpl
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS/* | CS_OWNDC*/ | CS_SAVEBITS, -1/*no brush*/)

	CSVGToolsDlg()
	{
		m_menuDlg = NULL;
	}

	CLXMLEditorApp* m_app;

//	CComQIPtr<ILHTMLActiveDocument> m_htmlActiveDoc;
//	CComQIPtr<ILHTMLActiveView> m_htmlView;

	CEXMLViewGroup* m_viewGroup;
//	CComPtr<IWebXMLDocument> m_document;

//	CComPtr<IUIMenuDlg> m_menuDlg;
	UI::Control* m_menuDlg;
//	CComObject<CUIMenuDlg>* m_menuDlg;

//	CComPtr<ILXMLEditorApp> m_app;

	LDraw::BBoxi m_strokerc;
	LDraw::BBoxi m_fillrc;
	LDraw::BBoxi m_drc[3];

	void DrawFillPaint(UI::Graphics * dc, LDraw::BBoxi rc, System::StringW* fillStr);
	void DrawStrokePaint(UI::Graphics * dc, LDraw::BBoxi rc, System::StringW* strokeStr);

// ILElementBehavior
//	CComPtr<ILElementBehaviorSite> m_behaviorSite;
#if 0
	STDMETHODIMP Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite)
	{
		m_behaviorSite = pBehaviorSite;
		return S_OK;
	}
	STDMETHODIMP Detach()
	{
		m_behaviorSite.Release();
		return S_OK;
	}
#endif
	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSVGToolsDlg)
	COM_INTERFACE_ENTRY(ISVGToolsDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(ILElementBehavior)
	COM_INTERFACE_ENTRY(ILCSSStyleDeclarationHandler)
END_COM_MAP()
*/
#if 0
BEGIN_MSG_MAP(CSVGToolsDlg)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
END_MSG_MAP()
#endif
	long OnPaint();
	long OnCreate();
	long OnDestroy();
	long OnSize();
	long OnLButtonDown();

// ISVGToolsDlg
public:
// IUIDlg
	/*
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Tools");
		return S_OK;
	}
	*/
	/*
	virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode)
	{
		CSize size;
		return CalcLayout(dwMode, nLength, &size);
	}
	*/

#if 0	// Had this
	STDMETHODIMP CalcLayout(DWORD dwMode, long nLength, SIZE* pVal)
	{
		CSize size(0,0);
		if (m_menuDlg)
			m_menuDlg->CalcLayout(dwMode, nLength, &size);

		pVal->cx = size.cx;
		pVal->cy = size.cy+64;

		return S_OK;
	}
#endif
// IUIEventHandler
//	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
// ILCSSStyleDeclarationHandler
	ErrorCode handleCSSEvent(/*[in]*/ long type, /*[in]*/ System::StringW* propertyName);
};

}	// LXmlEdit
}

#endif //__SVGTOOLSDLG_H_
