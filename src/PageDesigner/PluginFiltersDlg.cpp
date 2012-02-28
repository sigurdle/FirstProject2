// PluginFiltersDlg.cpp : Implementation of CPluginFiltersDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "PluginFiltersDlg.h"

#include "PageDesignerApp.h"
extern CPageDesignerApp* gApp;

/////////////////////////////////////////////////////////////////////////////
// CPluginFiltersDlg

STDMETHODIMP CPluginFiltersDlg::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPluginFiltersDlg
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

LRESULT CPluginFiltersDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	int y = 0;

	for (int i = 0; i < gApp->m_pluginFilters.GetSize(); i++)
	{
		CPluginFilterClass* pPluginFilterClass = gApp->m_pluginFilters[i];
		dc.TextOut(0, y, pPluginFilterClass->m_name, pPluginFilterClass->m_name.length());

		y += 16;
	}

	return 0;
}

LRESULT CPluginFiltersDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	POINT pt = point;
	pt.y -= 0;//m_areaRect.top;
	pt.y += scrollposY;

	long neffects;
	neffects = gApp->m_pluginFilters.GetSize();//layers->get_length(&nlayers);

	int effectIndex = pt.y/16;

	if (effectIndex >= 0 && effectIndex < neffects)
	{
		CPluginFilterClass* pEffect = gApp->m_pluginFilters[effectIndex];

/*			if (AnySelectedObjectsOnLayer(layer))
			{
			// Start of dragging objects between layers

				m_insertObjectsFromLayerIndex = layerIndex;
				m_insertObjectsOnLayerIndex = layerIndex;

				DrawSelectedObjectsMarker(m_insertObjectsOnLayerIndex);

				m_dragging = 1;
				SetCapture();
			}
		}
		else
		{
			bool bSelected = IsLayerSelected(layer);

			if (nFlags & MK_CONTROL)	// Toggle selected
			{
				if (bSelected)
				{
					DeselectLayer(layer);
				}
				else
				{
					SelectLayer(layer);
					if (m_selectedLayerIndex == -1) m_selectedLayerIndex = layerIndex;

					m_view->m_activeLayer = layer;

					//Fire_ClickSwatch(swatch);
				}

				Invalidate();
			}
			else
			{
				long startSel, endSel;

				if (!(nFlags & MK_SHIFT) || (m_selectedLayerIndex == -1))
				{
					startSel = endSel = layerIndex;
				}
				else if (layerIndex > m_selectedLayerIndex)
				{
					startSel = m_selectedLayerIndex;
					endSel = layerIndex;
				}
				else
				{
					startSel = layerIndex;
					endSel = m_selectedLayerIndex;
				}

				DeselectAll();

				for (long i = startSel; i <= endSel; i++)
				{
					CComPtr<IPDLayer> layer;
					layers->item(i, (IUnknown**)&layer);

					SelectLayer(layer);
				}

				if (!(nFlags & MK_SHIFT) || (m_selectedLayerIndex == -1))
					m_selectedLayerIndex = layerIndex;

			//	Fire_ClickSwatch(swatch);
				m_view->m_activeLayer = layer;

				Invalidate();
				UpdateWindow();

				ATLASSERT(m_insertObjectsOnLayerIndex == -1);
*/
		CLSID guid;
		guid = pEffect->m_clsid;

		HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(CLSID));

		if (hData)
		{
			GUID* p = (GUID*)GlobalLock(hData);
			*p = guid;
			GlobalUnlock(hData);

			CMyDropSource*  dropSource = new CMyDropSource;
			CMyDataObject* dataObject = new CMyDataObject;

			STGMEDIUM	stg = {0};
			stg.tymed = TYMED_HGLOBAL;
			stg.hGlobal = hData;
			stg.pUnkForRelease = NULL;
			
			FORMATETC	etc = {0};
			etc.cfFormat = RegisterClipboardFormat(_T("PageDesigner-Effect-Guid"));
			etc.tymed = TYMED_HGLOBAL;
			etc.ptd = NULL;
			etc.dwAspect = DVASPECT_CONTENT;
			etc.lindex = -1;

			dataObject->SetData(&etc, &stg, TRUE);

			DWORD dropEffect = 0;
			HRESULT hr = ::DoDragDrop(dataObject, dropSource, DROPEFFECT_COPY, &dropEffect);

			if (hr == DRAGDROP_S_DROP)
			{
				if (dropEffect/* & DROPEFFECT_MOVE*/)
				{
				}
			}

			GlobalFree(hData);

		//	delete dataObject;
		//	delete dropSource;

		}
	}

	return 0;
}
