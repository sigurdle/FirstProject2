#pragma once

#if 0

class CHTMPInput;

#include "OleClientItem.h"

class ATL_NO_VTABLE CInputObjectBase :
	public CComObjectRootEx<CComSingleThreadModel>,
	public COleClientItem,
	public IDispEventImpl<1, CInputObjectBase, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>
//	public IDispEventImpl<2, CInputObjectBase, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>
{
public:

//	CComQIPtr<IUIEdit> m_edit;
//	COleClientItem* m_oleItem;

	CHTMPInput* m_pPElement;

	CTOR CInputObjectBase()
	{
		m_pPElement = NULL;
	}

	~CInputObjectBase()
	{
	}

BEGIN_COM_MAP(CInputObjectBase)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IOleClientSite)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY2(IOleInPlaceSite, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY2(IOleInPlaceSiteEx, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceSiteWindowless)
END_COM_MAP()

BEGIN_SINK_MAP(CInputObjectBase)
   SINK_ENTRY_EX(1, DIID__IUIEditEvents, /*dispid*/2, OnChange)
//   SINK_ENTRY_EX(2, DIID__IUIButtonEvents, /*dispid*/1, OnClick)
END_SINK_MAP()

	HRESULT __stdcall OnChange();
	HRESULT __stdcall OnClick();
};

class CInputObject : public CComObject<CInputObjectBase>
{
public:
};

#include "HTMPElement.h"

class CHTMPInput :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CHTMPElement
{
protected:

public:
	CHTMPInput();
	~CHTMPInput();

	int m_reentrance;

	CInputObject* m_pControl;

	_bstr_t GetAttributeType();
	_bstr_t GetAttributeValue();
	long GetAttributeSize();

	virtual void Draw(CHTMRenderContext* pC);
	virtual void CalculateDimensions(CHTMCalcContext* pC);
	virtual void CreateControls(CHTMContext* pC);
	virtual void PlaceControls(HWND hWndParent, CHTMContext* pC);
	virtual BOOL OnButtonDown(CComObject<CHTMLWindow>* pFrame, POINT point);

	virtual void OnSetAttribute(BSTR attrName);

BEGIN_COM_MAP(CHTMPInput)
	COM_INTERFACE_ENTRY(ILViewNode)
END_COM_MAP()
};

#endif