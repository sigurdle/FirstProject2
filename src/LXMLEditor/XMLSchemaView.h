// XMLSchemaView.h : Declaration of the CXMLSchemaView

#ifndef __XMLSCHEMAVIEW_H_
#define __XMLSCHEMAVIEW_H_

#include "resource.h"       // main symbols

#if 0

class CSchema;

class CXMLSchemaGlobalsCtl;
class CXMLSchemaDesignCtl;
class CXMLSchemaAttributesView;

/////////////////////////////////////////////////////////////////////////////
// CXMLSchemaView
class ATL_NO_VTABLE CXMLSchemaView : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CXMLSchemaView, &CLSID_XMLSchemaView>,
	public IConnectionPointContainerImpl<CXMLSchemaView>,

	public CUIDialogImpl<CXMLSchemaView, CWindowImpl<CXMLSchemaView> >,

	public IDispatchImpl<IXMLSchemaView, &IID_IXMLSchemaView, &LIBID_WEBEDITORLib>,
	public IDispEventImpl<1, CXMLSchemaView, &DIID__IXMLSchemaGlobalsCtlEvents, &LIBID_WEBEDITORLib, 1, 0>
{
public:
	DECLARE_WND_CLASS(NULL)

	CXMLSchemaView()
	{
		m_globalsCtl = NULL;
		m_designCtl = NULL;
		m_attributesCtl = NULL;

		m_pSchema = NULL;
	}

	int FinalConstruct();

	void FinalRelease()
	{
	}

	CComQIPtr<IESvgDocument> m_document;

	CComObject<CXMLSchemaGlobalsCtl>* m_globalsCtl;
	CComObject<CXMLSchemaDesignCtl>* m_designCtl;
	CComObject<CXMLSchemaAttributesView>* m_attributesCtl;
	
	CSchema* m_pSchema;

DECLARE_REGISTRY_RESOURCEID(IDR_XMLSCHEMAVIEW)
DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXMLSchemaView)
	COM_INTERFACE_ENTRY(IXMLSchemaView)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY2(IDispatch, IXMLSchemaView)

	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CXMLSchemaView)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CXMLSchemaView)
   SINK_ENTRY_EX(1, DIID__IXMLSchemaGlobalsCtlEvents, /*dispid*/1, OnDesignNode)
END_SINK_MAP()

	HRESULT __stdcall OnDesignNode(IDOMNode* node);

BEGIN_MSG_MAP(CXMLSchemaView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
/*
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk);
*/
END_MSG_MAP()

	long OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
/*
	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

// IXMLSchemaView
public:
	STDMETHOD(get_document)(/*[out, retval]*/ IESvgDocument* *pVal);
	STDMETHOD(put_document)(/*[in]*/ IESvgDocument* newVal);

// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Schema");
		return S_OK;
	}
};

#endif //__XMLSCHEMAVIEW_H_
#endif