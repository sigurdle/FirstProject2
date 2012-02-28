#ifndef __SVGSYMBOLLIBRARYDLG_H_
#define __SVGSYMBOLLIBRARYDLG_H_

#include "resource.h"       // main symbols

#include "SVGDefinitionsDlgT.h"

namespace System
{
namespace LXmlEdit
{

class CSVGSymbolLibraryDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSVGSymbolLibraryDlg, &CLSID_SVGSymbolLibraryDlg>,
//	public IDispatchImpl<ISVGSymbolLibraryDlg, &IID_ISVGSymbolLibraryDlg, &LIBID_LXMLEDITORLib>,

	public CSVGDefinitionsDlgT<CSVGSymbolLibraryDlg>
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CSVGSymbolLibraryDlg()
	{
		m_type = 2;
	}

	void BuildItems()
	{
		m_listView.RemoveItems();
		AddItems();
	}

	long OnLButtonDown();

	long OnFiltersSmallThumbnails(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(0);
		return 0;
	}

	long OnFiltersLargeThumbnails(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(1);
		return 0;
	}

	long OnFiltersSmallListView(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(2);
		return 0;
	}

	long OnFiltersLargeListView(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
	{
		m_listView.SetView(3);
		return 0;
	}

	void OnFiltersSmallThumbnailsUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 0);
	}

	void OnFiltersLargeThumbnailsUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 1);
	}

	void OnFiltersSmallListViewUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 2);
	}

	void OnFiltersLargeListViewUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
	{
		long view;
		m_listView.GetView(&view);

		pCmdUI->SetCheck(view == 3);
	}

// ISVGSymbolLibraryDlg
public:
	ErrorCode Load(System::StringW* pathName);
};

}	// LXmlEdit
}

#endif //__SVGSYMBOLLIBRARYDLG_H_
