#pragma once

#if 0
class CHTMPTextArea;

#include "OleClientItem.h"

class CTextAreaObjectBase :
	public CComObjectRootEx<CComSingleThreadModel>,
	public COleClientItem,
	public IDispEventImpl<1, CTextAreaObjectBase, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>
{
public:

//	CComQIPtr<IUIEdit> m_edit;
//	COleClientItem* m_oleItem;

	CHTMPTextArea* m_pPElement;

	CTextAreaObjectBase()
	{
		m_pPElement = NULL;
	}

	~CTextAreaObjectBase()
	{
	}

BEGIN_COM_MAP(CTextAreaObjectBase)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IOleClientSite)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY2(IOleInPlaceSite, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY2(IOleInPlaceSiteEx, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceSiteWindowless)
END_COM_MAP()

BEGIN_SINK_MAP(CTextAreaObjectBase)
   SINK_ENTRY_EX(1, DIID__IUIEditEvents, /*dispid*/2, OnChange)
END_SINK_MAP()

	HRESULT __stdcall OnChange();
};

class CTextAreaObject : public CComObject<CTextAreaObjectBase>
{
public:
};
#endif

#include "PHTMLElement.h"

namespace System
{
namespace Web
{

class HTMLEXT CHTMPTextArea : public PHTMLElement
{
protected:

public:
	CTOR CHTMPTextArea(HTMLElement* element);
	~CHTMPTextArea();

//	CTextAreaObject* m_pControl;

	long GetAttributeCols();
	long GetAttributeRows();

//	virtual void Draw(CHTMRenderContext* pC);
	virtual void CalculateDimensions(CHTMCalcContext* pC);
//	virtual void CreateControls(CHTMContext* pC);
//	virtual void PlaceControls(HWND hWndParent, CHTMContext* pC);
#if 0
	virtual BOOL OnButtonDown(POINT point, CPElement* *pVal);
#endif

	virtual void OnSetAttribute(System::StringW* attrName);
};

}	// Web
}
