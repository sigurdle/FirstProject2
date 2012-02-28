#ifndef __SVGGRADIENTEDITCTL_H_
#define __SVGGRADIENTEDITCTL_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CSVGGradientEditCtl : 

	public Web::IEventListener
{
public:
	CSVGGradientEditCtl()
	{
		m_dragging = false;
		m_colorSpread = NULL;

		m_canEditStops = true;
	}

	Web::SVGElement* m_pElement;
	Web::SVGGradientElement* m_gradient;
	Web::SVGStopElement* m_activeStop;

	LDraw::PixelRGBA_32* m_colorSpread;
	int m_totalColors;
	LDraw::BBoxi m_previewRect;
	bool m_canEditStops;
	bool m_dragging;

	void InvalidateKnob(Web::SVGStopElement* stop);
	void InvalidatePreview();
	void InvalidateGradient();
	void InvalidateKnobs();
	void PrepareRange();
	void PaintGradient(MSWindows::HDC hDC);
	void NewColor(LDraw::Color newrgb);

	void OnButtonDown(UINT nFlags, LDraw::PointI point, int iButton, bool bDblClk);
	void OnMouseMove(UINT nFlags, LDraw::PointI point);
	void OnButtonUp(UINT nFlags, LDraw::PointI point, int iButton);

	/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
*/

// ISVGGradientEditCtl
public:
	ErrorCode get_canEditStops(/*[out, retval]*/ bool *pVal);
	ErrorCode put_canEditStops(/*[in]*/ bool newVal);
	ErrorCode SetSVGElement(/*[in]*/ System::Object* element);

//	HRESULT OnDraw(ATL_DRAWINFO& di);
//	OLE_COLOR m_clrBackColor;
	bool m_bEnabled;
//	CComPtr<IFontDisp> m_pFont;

// Web::EventListener
	void handleEvent(Web::Event* evt);
};

}	// LXmlEdit
}

#endif //__SVGGRADIENTEDITCTL_H_
