// XMLSchemaGlobalsCtl.h : Declaration of the CXMLSchemaGlobalsCtl

#ifndef __XMLSCHEMAGLOBALSCTL_H_
#define __XMLSCHEMAGLOBALSCTL_H_

#include "resource.h"       // main symbols

namespace System
{

class CSchemaDiagramView;

/////////////////////////////////////////////////////////////////////////////
// CXMLSchemaGlobalsCtl
class CXMLSchemaGlobalsCtl : 
public UI::Control//CWindowImpl<CXMLSchemaGlobalsCtl>
//	public IDispEventImpl<2, CXMLSchemaGlobalsCtl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
{
public:
	CXMLSchemaGlobalsCtl()
	{
		m_pSchema = NULL;

		ASSERT(0);
#if 0
		m_schemaDesignBm = LoadBitmap(_Module.m_hInst, MAKEINTRESOURCE(IDB_SCHEMADESIGN));
#endif
	}

	~CXMLSchemaGlobalsCtl()
	{
	//	if (m_schemaDesignBm)
		{
	//		DeleteObject(m_schemaDesignBm);
	//		m_schemaDesignBm = NULL;
		}
	}

	CSchemaDiagramView* m_pSchema;

	LDraw::Bitmap* m_schemaDesignBm;

//	CAxWindow	m_axvert;
//	CComQIPtr<IUIScrollBar> m_vert;
	
	LDraw::BBoxi m_areaRect;

	void OnSize();

#if 0
BEGIN_SINK_MAP(CXMLSchemaGlobalsCtl)
//   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
  // SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()
#endif

//	HRESULT __stdcall OnHorzScroll(long code, long pos);
	void __stdcall OnVertScroll(long code, long pos);

/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
*/
public:
};

}

#endif //__XMLSCHEMAGLOBALSCTL_H_
