// ToolPresetsDlg.cpp : Implementation of CToolPresetsDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "ToolPresetsDlg.h"

#include "LXMLEditorApp.h"

#if 0

///////////////////////////////////////////////////////////////////////////
// CToolPresetsDlg

LRESULT CToolPresetsDlg::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;

	HDC hDC = lpdis->hDC;
	CRect& rc = *(CRect*)&lpdis->rcItem;
	CSVGListViewItem* pItem = (CSVGListViewItem*)lpdis->itemData;

	CToolPreset* pPreset = (CToolPreset*)pItem->m_element;
	CComQIPtr<IUICommand> command = pPreset->m_pTool->m_command;
	if (command != NULL)
	{
		HIMAGELIST hBitmap;
		command->get_bitmap((DWORD*)&hBitmap);

		long bitmapIndex;
		command->get_bitmapIndex(&bitmapIndex);
		//ImageList_GetIconSize(hBitmap, &cx, &cy);

		ImageList_Draw(hBitmap, bitmapIndex, hDC, rc.left, rc.top, ILD_TRANSPARENT);
	}

	return 0;
}

BEGIN_CMD_MAP(CToolPresetsDlg)

	CMD_HANDLER(ID_TOOLPRESETS_NEW, OnToolPresetsNew)

/*
	CMD_HANDLER(ID_SYMBOLS_DEFINESYMBOL, OnSymbolDefineSymbol)
	CMD_HANDLER(ID_SYMBOLS_NEWSYMBOL, OnSymbolsNewSymbol)
	CMD_HANDLER(ID_SYMBOLS_PLACESYMBOL, OnSymbolsPlaceSymbol)
	CMD_HANDLER(ID_SYMBOLS_BREAKLINKTOSYMBOL, OnBreakLinkToSymbol)
	CMD_UPDATE(ID_SYMBOLS_BREAKLINKTOSYMBOL, OnBreakLinkToSymbolUpdate)
	CMD_HANDLER(ID_SYMBOLS_SELECTALLUNUSED, OnSymbolSelectAllUnused)
*/
	CMD_HANDLER(ID_SVGLIST_SMALLTHUMBNAILS, OnListSmallThumbnails)
	CMD_HANDLER(ID_SVGLIST_LARGETHUMBNAILS, OnListLargeThumbnails)
	CMD_HANDLER(ID_SVGLIST_SMALLLISTVIEW, OnListSmallListView)
	CMD_HANDLER(ID_SVGLIST_LARGELISTVIEW, OnListLargeListView)
	CMD_UPDATE(ID_SVGLIST_SMALLTHUMBNAILS, OnListSmallThumbnailsUpdate)
	CMD_UPDATE(ID_SVGLIST_LARGETHUMBNAILS, OnListLargeThumbnailsUpdate)
	CMD_UPDATE(ID_SVGLIST_SMALLLISTVIEW, OnListSmallListViewUpdate)
	CMD_UPDATE(ID_SVGLIST_LARGELISTVIEW, OnListLargeListViewUpdate)
END_CMD_MAP()

#include "ToolPresetNameDlg.h"

LRESULT CToolPresetsDlg::OnToolPresetsNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CToolPresetNameDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		CToolPreset* pPreset = new CToolPreset;
		pPreset->m_name = dlg.m_name;
		pPreset->m_pTool = m_app->m_pActiveTool;

		m_listView.AddItem((DWORD)pPreset, _bstr_t(pPreset->m_name));

		m_app->m_toolPresets.Add(pPreset);
	}

	return 0;
}

#endif