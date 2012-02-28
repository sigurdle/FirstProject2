#ifndef __LIQUIFYTOOLPLUGIN_H_
#define __LIQUIFYTOOLPLUGIN_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CLiquifyToolPlugin;

class CLiquifyTool : 
	public ISVGTool
{
public:
	CLiquifyTool();
	~CLiquifyTool();

	class CTimerWnd : public MSWindows::WindowImpl//<CTimerWnd>
	{
	public:
		ISVGView* m_view;
		CLiquifyTool* m_lt;

		/*
	BEGIN_MSG_MAP(CTimerWnd)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
	END_MSG_MAP()
	*/

		MSWindows::LRESULT OnTimer(UINT uMsg, MSWindows::WPARAM wParam, MSWindows::LPARAM lParam, MSWindows::BOOL& bHandled);
	};

	class CElement
	{
	public:
		Element* m_eElement;

		Array<LDraw::PointD> m_points;
	};

	Array<CElement*> m_targetObjects;

	CLiquifyToolPlugin* m_pAddin;

	int m_nTool;
	int m_dragging;
	int m_hit;
	LDraw::PointD m_brushSize;

	LDraw::PointI m_startpt;
	LDraw::PointI m_oldpt;
	LDraw::PointD m_wstartpt;
	LDraw::PointD m_woldpt;

	CTimerWnd m_timerWnd;

	double m_twirlRate;

	bool m_bBrushSizeVisible;

	void AddTargetElement(CEXMLDocument* eDocument, Element* eElement);

	void DrawBrushOutline(ISVGView* view, MSWindows::HDC hDC, LDraw::PointD point);
	void EraseBrushOutline(ISVGView* view);

	void OnTimer(ISVGView* view);
	void Process(ISVGView* view, LDraw::PointD wpt);

//	ILSVGTransform* GetMatrixTransform(ILSVGSVGElement* svgsvgElement, ILSVGTransformable* transformable);


public:
	ErrorCode Options(UI::Control* hParent);
	ErrorCode OnDeactivate(ILXMLEditorApp* app);
	ErrorCode OnActivate(ILXMLEditorApp* app);
	ErrorCode Paint(/*[in]*/ ISVGView* view, /*[in]*/ long dragging, UI::Graphics* pGraphics);

	ErrorCode OnButtonDown(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse, /*[out,retval]*/ long* pdragging);
	ErrorCode OnButtonUp(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse);
	ErrorCode OnMouseMove(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse);
	ErrorCode OnSetCursor(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse);
};

/*template <class T>*/ class CPDBrushSettingsImpl
	//public IPDBrushSettings
{
public:
	CPDBrushSettingsImpl()
	{
		m_brushWidth = 60;
		m_brushHeight = 60;
		m_brushAngle = 0;
		m_showBrushSize = true;
		SetMatrix();
	}

	double m_brushWidth;
	double m_brushHeight;
	double m_brushAngle;
	bool m_showBrushSize;

	Web::SVGMatrix* m_matrix;

	ErrorCode SetMatrix()
	{
		ASSERT(0);
#if 0
		CComPtr<ILSVGMatrix> mat0;
		ErrorCode hr = mat0.CoCreateInstance(CLSID_LSVGMatrix);

		if (FAILED(hr)) return hr;

		CComPtr<ILSVGMatrix> mat1;
		mat0->scaleNonUniform(m_brushWidth/2, m_brushHeight/2, &mat1);

		CComPtr<ILSVGMatrix> mat2;
		mat1->rotate(m_brushAngle, &mat2);

		m_matrix.Release();
		m_matrix = mat2;
#endif
		return 0;
	}

public:
	double get_brushWidth() const
	{
		return m_brushWidth;
	}

	ErrorCode put_brushWidth(double newVal)
	{
		if (m_brushWidth != newVal)
		{
			m_brushWidth = newVal;
			SetMatrix();
		}
		return Success;
	}

	double get_brushHeight() const
	{
		return m_brushHeight;
	}

	void set_brushHeight(double newVal)
	{
		if (m_brushHeight != newVal)
		{
			m_brushHeight = newVal;
			SetMatrix();
		}
	}

	double get_brushAngle() const
	{
		return m_brushAngle;
	}

	void set_brushAngle(double newVal)
	{
		if (m_brushAngle != newVal)
		{
			m_brushAngle = newVal;
			SetMatrix();
		}
	}

	bool get_showBrushSize() const
	{
		return m_showBrushSize;
	}

	void put_showBrushSize(bool newVal)
	{
		m_showBrushSize = newVal;
	}

	Web::SVGMatrix* getBrushMatrix()
	{
		return m_matrix;
	}
};

class CLiquifyToolPlugin : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CLiquifyToolPlugin, &CLSID_LiquifyToolPlugin>,
//	public IDispatchImpl<ILiquifyToolPlugin, &IID_ILiquifyToolPlugin, &LIBID_LXMLEDITORLib>,

	public CPDBrushSettingsImpl,//<CLiquifyToolPlugin>,

	public ILXMLEditorPlugin,
	public ISVGToolFactory
{
public:
	CLiquifyToolPlugin()
	{
	}

	ILXMLEditorPluginClass * m_spAddinSite;

	/*
DECLARE_REGISTRY_RESOURCEID(IDR_LIQUIFYTOOLPLUGIN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLiquifyToolPlugin)
//	COM_INTERFACE_ENTRY(ILiquifyToolPlugin)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ILXMLEditorPlugin)
	COM_INTERFACE_ENTRY(IPDBrushSettings)
	COM_INTERFACE_ENTRY(ISVGToolFactory)
END_COM_MAP()
*/

// ILiquifyToolPlugin
public:
	ILXMLEditorPluginClass* GetSite()
	{
		return m_spAddinSite;
	}
	ErrorCode(SetSite)(ILXMLEditorPluginClass* pSite);

//	ErrorCode Startup(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app);
//	ErrorCode Shutdown(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app);
	ErrorCode FindTool(/*[in]*/ long id, System::Object* *pdlg, /*[out,retval]*/ ISVGTool** pVal);
};

}	// LXmlEdit
}

#endif //__LIQUIFYTOOLPLUGIN_H_
