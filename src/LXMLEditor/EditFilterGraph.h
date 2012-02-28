// EditFilterGraph.h : Declaration of the CEditFilterGraph

#ifndef __EDITFILTERGRAPH_H_
#define __EDITFILTERGRAPH_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{
//class CFilterPrimitiveElement;
class CESVGFilterElement;
class CFilterPrimitiveElement;

class CEditFilterGraph : 
public UI::Control
/*
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IEditFilterGraph, &IID_IEditFilterGraph, &LIBID_LXMLEDITORLib>,
	public CComControl<CEditFilterGraph>,
	public IPersistStreamInitImpl<CEditFilterGraph>,
	public IOleControlImpl<CEditFilterGraph>,
	public IOleObjectImpl<CEditFilterGraph>,
	public IOleInPlaceActiveObjectImpl<CEditFilterGraph>,
	public IViewObjectExImpl<CEditFilterGraph>,
	public IOleInPlaceObjectWindowlessImpl<CEditFilterGraph>,
	public IConnectionPointContainerImpl<CEditFilterGraph>,
	public CComCoClass<CEditFilterGraph, &CLSID_EditFilterGraph>,
	*/

#if 0
	public IDispEventImpl<2, CEditFilterGraph, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CEditFilterGraph, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>

	public IDispEventImpl<4, CEditFilterGraph, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
{
public:
	CEditFilterGraph()
	{
//		m_bWindowOnly = true;

		m_pLayer = NULL;
		m_pItemDrag = NULL;
		m_pNearItem = NULL;

		m_dragging = 0;
	}

#if 0
	int FinalConstruct()
	{
		m_horz.CoCreateInstance(CLSID_UIScrollBar);
		m_horz->put_direction(0);
//		IDispEventImpl<2, CEditFilterGraph, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);

		m_vert.CoCreateInstance(CLSID_UIScrollBar);
		m_vert->put_direction(1);
//		IDispEventImpl<3, CEditFilterGraph, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

		return S_OK;
	}
#endif

	void FinalRelease();

	int m_inpin;
	int m_dragging;

	CESVGFilterElement* m_pLayer;

	CFilterPrimitiveElement/*CFilterPrimitiveElement*/ * m_pItemDrag;
	CFilterPrimitiveElement/*CFilterPrimitiveElement*/ * m_pNearItem;
	LDraw::PointD m_oldpt;

//	CAxWindow m_axvert;
//	CAxWindow m_axhorz;
//	CComPtr<IUIScrollBar> m_vert;
//	CComPtr<IUIScrollBar> m_horz;

	LDraw::BBoxi m_areaRect;

	void OnSize();

	void __stdcall OnHorzScroll(long code, long pos);
	void __stdcall OnVertScroll(long code, long pos);

	ErrorCode __stdcall OnDOMEvent(Web::Event* evt);

// IEditFilterGraph
public:
	ErrorCode DeleteSelectedPrimitive();
	ErrorCode get_activeElement(/*[out, retval]*/ Element* *pVal);
	ErrorCode put_activeElement(/*[in]*/ Element* newVal);

//	ErrorCode OnDraw(ATL_DRAWINFO& di);
//	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
};

}	// LXmlEdit
}

#endif //__EDITFILTERGRAPH_H_
