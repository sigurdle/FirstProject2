// PageDesignerApp.h : Declaration of the CPageDesignerApp

#ifndef __PageDesignerApp_H_
#define __PageDesignerApp_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"
#include "PDDocumentSettingsImpl.h"

class CPageDesignerFrame;
class CPDBrush;
class CPDSwatches;

template <class T> class ATL_NO_VTABLE CPDBrushSettingsImpl : 
	public IPDBrushSettings
{
public:
	CPDBrushSettingsImpl()
	{
		m_brushWidth = 60;
		m_brushHeight = 60;
		m_brushAngle = 0;
		m_showBrushSize = VARIANT_TRUE;

		SetMatrix();
	}

	double m_brushWidth;
	double m_brushHeight;
	double m_brushAngle;
	VARIANT_BOOL m_showBrushSize;

	CComPtr<IPDMatrix> m_matrix;

	void SetMatrix()
	{
		CComPtr<IPDMatrix> mat0;
		mat0.CoCreateInstance(CLSID_PDMatrix);

		//CComPtr<IPDMatrix> mat2;
		//mat->translate(m_brushWidth/2, m_brushHeight/2, &mat2);

		CComPtr<IPDMatrix> mat1;
		mat0->scaleNonUniform(m_brushWidth/2, m_brushHeight/2, &mat1);

		CComPtr<IPDMatrix> mat2;
		mat1->rotate(m_brushAngle, &mat2);

		m_matrix.Release();
		m_matrix = mat2;
	}

public:
	STDMETHODIMP get_brushWidth(double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_brushWidth;
		return S_OK;
	}

	STDMETHODIMP put_brushWidth(double newVal)
	{
		if (m_brushWidth != newVal)
		{
			m_brushWidth = newVal;
			SetMatrix();
		}
		return S_OK;
	}

	STDMETHODIMP get_brushHeight(double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_brushHeight;
		return S_OK;
	}

	STDMETHODIMP put_brushHeight(double newVal)
	{
		if (m_brushHeight != newVal)
		{
			m_brushHeight = newVal;
			SetMatrix();
		}
		return S_OK;
	}

	STDMETHODIMP get_brushAngle(double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_brushAngle;
		return S_OK;
	}

	STDMETHODIMP put_brushAngle(double newVal)
	{
		if (m_brushAngle != newVal)
		{
			m_brushAngle = newVal;
			SetMatrix();
		}
		return S_OK;
	}

	STDMETHODIMP get_showBrushSize(VARIANT_BOOL *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_showBrushSize;
		return S_OK;
	}

	STDMETHODIMP put_showBrushSize(VARIANT_BOOL newVal)
	{
		m_showBrushSize = newVal;
		return S_OK;
	}

	STDMETHODIMP getBrushMatrix(IPDMatrix **pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_matrix;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
};

class ATL_NO_VTABLE CPluginFilterClass : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPluginFilterClass
{
public:
	STDMETHOD(GetName)(/*[out,retval]*/ BSTR* pVal);
	_bstr_t m_name;
	CLSID	m_clsid;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPluginFilterClass)
	COM_INTERFACE_ENTRY(IPluginFilterClass)
END_COM_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CPageDesignerApp
class ATL_NO_VTABLE CPageDesignerApp : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CPageDesignerApp, &CLSID_PageDesignerApp>,
	public IConnectionPointContainerImpl<CPageDesignerApp>,
	public IDispatchImpl<IPageDesignerApp, &IID_IPageDesignerApp, &LIBID_PAGEDESIGNERLib>,

	public CPDDocumentSettingsImpl<CPageDesignerApp>,
	public CPDBrushSettingsImpl<CPageDesignerApp>,
	public IPDApplicationSettings,

	public ProcessTargetCommands,
	public CNotifySendImpl<CPageDesignerApp>
{
public:
	CPageDesignerApp()
	{
		m_frame = NULL;

		m_activeTool = ID_TOOL_SELECT;
		m_activeSelectionTool = ID_TOOL_SELECT;

		m_strokeOrFill = 0;	// Stroke
		m_newArtHasBasicAppearance = VARIANT_TRUE;

//		m_strokeBrush = NULL;
//		m_fillBrush = NULL;

		m_swatches = NULL;

		m_nextDocumentIndex = 0;

// ApplicationSettings
		m_clipboardSavePNG = VARIANT_TRUE;
		m_clipboardSaveJPEG = VARIANT_FALSE;
		m_clipboardSaveGIF = VARIANT_FALSE;
	}

	int FinalConstruct();
	void FinalRelease();

// ApplicationSettings

	VARIANT_BOOL m_clipboardSavePNG;
	VARIANT_BOOL m_clipboardSaveJPEG;
	VARIANT_BOOL m_clipboardSaveGIF;

//
	long m_activeTool;
	long m_activeSelectionTool;
	VARIANT_BOOL m_newArtHasBasicAppearance;
	int m_strokeOrFill;

	int m_nextDocumentIndex;

	CArray<CComObject<CPluginFilterClass>*,CComObject<CPluginFilterClass>*> m_pluginFilters;

	CComObject<CPageDesignerFrame>* m_frame;

//	CComObject<CPDBrush>* m_strokeBrush;
//	CComObject<CPDBrush>* m_fillBrush;

	CComObject<CPDSwatches>* m_swatches;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPageDesignerApp)
	COM_INTERFACE_ENTRY(IPageDesignerApp)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(IPDDocumentSettings)
	COM_INTERFACE_ENTRY(IPDBrushSettings)
	COM_INTERFACE_ENTRY(IPDApplicationSettings)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPageDesignerApp)
END_CONNECTION_POINT_MAP()

public:

	DECLARE_CMD_MAP(CPageDesignerApp)

	LRESULT OnEditPreferences(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnFileNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFileNewSite(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFileOpenSite(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnAppearanceNewArtHasBasicAppearance(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnAppearanceNewArtHasBasicAppearanceUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnSetTool(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnSetToolUpdate(long iid, IUICmdUpdate* pCmdUI);

	LRESULT OnHelp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCustomize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	void OnFontfaceUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnEditEmptyClipboard(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnEditEmptyClipboardUpdate(long iid, IUICmdUpdate* pCmdUI);

// IPageDesignerApp
public:
	STDMETHOD(get_strokeOrFill)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_strokeOrFill)(/*[in]*/ long newVal);
	STDMETHOD(get_newArtHasBasicAppearance)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_newArtHasBasicAppearance)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_clipboardSaveGIF)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_clipboardSaveGIF)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_clipboardSaveJPEG)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_clipboardSaveJPEG)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_clipboardSavePNG)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_clipboardSavePNG)(/*[in]*/ VARIANT_BOOL newVal);
#if 0
	STDMETHOD(get_fillBrush)(/*[out, retval]*/ IPDBrush* *pVal);
	STDMETHOD(get_strokeBrush)(/*[out, retval]*/ IPDBrush* *pVal);
#endif
	STDMETHOD(get_swatches)(/*[out, retval]*/ IPDSwatches* *pVal);
	STDMETHOD(OpenDocument)(/*[in]*/ BSTR pathName, /*[out,retval]*/ VARIANT_BOOL* success);
	STDMETHOD(get_uiManager)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(get_frame)(/*[out, retval]*/ IPageDesignerFrame* *pVal);
	STDMETHOD(Run)(/*[out,retval]*/ long* result);
};

#endif //__PageDesignerApp_H_
