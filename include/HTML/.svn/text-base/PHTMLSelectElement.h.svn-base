class CHTMPSelect;

#if 0
#include "../LXUI/OleClientItem.h"

class ATL_NO_VTABLE CSelectObjectBase :
	public CComObjectRootEx<CComSingleThreadModel>,
	public COleClientItem
//	public IDispEventImpl<1, CSelectObjectBase, &DIID__IUIComboBoxEvents, &LIBID_UILib, 1, 0>
{
public:

	CHTMPSelect* m_pPElement;

	CTOR CSelectObjectBase()
	{
		m_pPElement = NULL;
	}

	~CSelectObjectBase()
	{
	}

	void FinalRelease()
	{
	}

BEGIN_COM_MAP(CSelectObjectBase)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IOleClientSite)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY2(IOleInPlaceSite, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY2(IOleInPlaceSiteEx, IOleInPlaceSiteWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceSiteWindowless)
END_COM_MAP()

BEGIN_SINK_MAP(CSelectObjectBase)
//   SINK_ENTRY_EX(1, DIID__IUIComboBoxEvents, /*dispid*/1, OnCurSelChange)
END_SINK_MAP()

	HRESULT __stdcall OnCurSelChange(long index);
};

class CSelectObject : public CComObject<CSelectObjectBase>
{
public:
};
#endif

#include "PHTMLElement.h"

namespace System
{
namespace Web
{

class HTMLEXT CHTMPSelect : public PHTMLElement
{
protected:

public:
#if 0
	CHTMPSelect();
	~CHTMPSelect();

	CArray<ILDOMElement*,ILDOMElement*> m_options;

	CSelectObject* m_pControl;

	void TraverseOPTIONEntries();

	long GetAttributeSize();
	BOOL GetAttributeMultiple();

	virtual void PlaceControls(HWND hWndParent, CHTMContext* pC);
	virtual void CalculateDimensions(CHTMCalcContext* pC);
	virtual void CreateControls(CHTMContext* pC);
	virtual BOOL HasDistributableChildren()
	{
		return FALSE;
	}
#endif
};

}	// Web
}
