// SmilRegionsView.h : Declaration of the CSmilRegionsView

#ifndef __SMILREGIONSVIEW_H_
#define __SMILREGIONSVIEW_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CSmilLayout;
class CSmilRegion;

class CSmilRegionsView : 
	public UI::Control
//	public CUIDialogImpl<CSmilRegionsView, CWindowImpl<CSmilRegionsView> >,
	
//	public IDispatchImpl<ISmilRegionsView, &IID_ISmilRegionsView, &LIBID_LXMLEDITORLib>
{
public:
	CSmilRegionsView()
	{
		m_dragging = 0;
		m_layout = NULL;
		m_pActiveRegion = NULL;
	}

	CEXMLViewGroup* m_viewGroup;
	CEXMLDocument* m_document;	// TODO remove

	Web::Element* m_layoutElement;

	CSmilLayout* m_layout;
	int m_dragging;
	LDraw::PointD m_oldpt;
	int m_sizeing;

	CSmilRegion* m_pActiveRegion;

	long OnPaint();
	long OnLButtonDown();
	long OnLButtonUp();
	long OnMouseMove();
	long OnCreate();
/*
	long OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

// ISmilRegionsView
public:
	ErrorCode get_document(/*[out, retval]*/ CEXMLDocument* *pVal);
	ErrorCode set_document(/*[in]*/ CEXMLDocument* newVal);

	/*
// IUIDlg
	ErrorCode(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"SMIL Regions");
		return S_OK;
	}
	*/
};

}	// LXmlEdit
}

#endif //__SMILREGIONSVIEW_H_
