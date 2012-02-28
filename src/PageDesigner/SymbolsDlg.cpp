// SymbolsDlg.cpp : Implementation of CSymbolsDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "SymbolsDlg.h"

#include "PDDocumentView.h"

/////////////////////////////////////////////////////////////////////////////
// CSymbolsDlg

int CSymbolsDlg::FinalConstruct()
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->FindMenu(IDR_SYMBOLS, &m_menu);

	return 0;
}

LRESULT CSymbolsDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	CRect client;
	GetClientRect(&client);

	if (m_view)
	{
		CComPtr<IObjectMap> symbols;
		m_view->m_document->get_symbols(&symbols);

		long nsymbols;
		symbols->get_length(&nsymbols);

		int ncolumns = client.Width()/32;

		for (int n = 0; n < nsymbols; n++)
		{
			int x = n%ncolumns*32;
			int y = n/ncolumns*32;

			CComPtr<IPDSymbol> symbol;
			symbols->item(n, (IUnknown**)&symbol);

			CComPtr<IPDObject> symbolObject;
			symbol->get_symbolObject(&symbolObject);

			CComQIPtr<IPDObjectTransformable> transformable = symbolObject;
			RectD bounds;
			transformable->get_bounds(&bounds);

			int width = 32;
			int height = bounds.Height * width/bounds.Width;

			if (height > 32)
			{
				height = 32;
				width = bounds.Width * height/bounds.Height;
			}

			double magnify = width/bounds.Width;

			int left = (32-width)/2;
			int top = (32-height)/2;

			if (IsSymbolSelected(symbol))
			{
				FillSolidRect(dc.m_hDC, x, y, 32, 32, GetSysColor(COLOR_HIGHLIGHT));
				FillSolidRect(dc.m_hDC, x+2, y+2, 32-4, 32-4, RGB(255, 255, 255));
			}
			else
			{
				dc.Rectangle(x, y, x+32, y+32);
			}

			CComPtr<IPDRenderer> renderer;
			renderer.CoCreateInstance(CLSID_PDRenderer);
			if (renderer)
			{
				Gdiplus::Graphics graphics(dc.m_hDC);

				graphics.TranslateTransform(x+left, y+top);
				graphics.ScaleTransform(magnify, magnify);

				renderer->put_targetHDC((HDC)&graphics);
				renderer->put_magnify(magnify);

				renderer->RenderObject(symbolObject);
			}
		}
	}

	return 0;
}

LRESULT CSymbolsDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	CRect client;
	GetClientRect(&client);

	if (m_view)
	{
		CComPtr<IObjectMap> symbols;
		m_view->m_document->get_symbols(&symbols);

		long nsymbols;
		symbols->get_length(&nsymbols);

		int ncolumns = client.Width()/32;

		int index = point.y/32*ncolumns + point.x/32;

		if (index >= 0 && index < nsymbols)
		{
			CComPtr<IPDSymbol> symbol;
			symbols->item(index, (IUnknown**)&symbol);

			bool bSelected = IsSymbolSelected(symbol);

			if (nFlags & MK_CONTROL)	// Toggle selected
			{
				if (bSelected)
				{
					DeselectSymbol(symbol);
				}
				else
				{
					SelectSymbol(symbol);
					if (m_selectedSymbolIndex == -1) m_selectedSymbolIndex = index;

				//	m_view->m_activeLayer = layer;

					//Fire_ClickSwatch(swatch);
				}

				Invalidate();
			}
			else
			{
				long startSel, endSel;

				if (!(nFlags & MK_SHIFT) || (m_selectedSymbolIndex == -1))
				{
					startSel = endSel = index;
				}
				else if (index > m_selectedSymbolIndex)
				{
					startSel = m_selectedSymbolIndex;
					endSel = index;
				}
				else
				{
					startSel = index;
					endSel = m_selectedSymbolIndex;
				}

				DeselectAll();

				for (long i = startSel; i <= endSel; i++)
				{
					CComPtr<IPDSymbol> symbol;
					symbols->item(i, (IUnknown**)&symbol);

					SelectSymbol(symbol);
				}

				if (!(nFlags & MK_SHIFT) || (m_selectedSymbolIndex == -1))
					m_selectedSymbolIndex = index;

			//	Fire_ClickSwatch(swatch);
				//m_view->m_activeLayer = layer;
			}
		}
		else
		{
			DeselectAll();
		}

		Invalidate();
	}

	return 0;
}

LRESULT CSymbolsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
/*	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);
	IDispEventImpl<1, CLayersDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);
*/
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	//RegisterDragDrop(m_hWnd, static_cast<IDropTarget*>(this));

	return 0;
}

LRESULT CSymbolsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

	/*
	IDispEventImpl<1, CLayersDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	RevokeDragDrop(m_hWnd);
  */

	return 0;
}

// ICommandTarget
STDMETHODIMP CSymbolsDlg::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try view
	CComQIPtr<ICommandTarget> view = m_view;
	if (view) view->OnCmdMsg(nID, nCode, pCmdUI, bHandled);

	return S_OK;
}

STDMETHODIMP CSymbolsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IPDDocumentView> view = object;
	if (view)
	{
		ATLASSERT(m_view == NULL);	// Assume only one active view at a time
		m_view = static_cast<CComObject<CPDDocumentView>*>(view.p);
		m_view->AddRef();
//		IDispEventImpl<3, CLayersDlg, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventAdvise(m_view->m_document);
/*
		if (!IsLayerSelected(m_view->m_activeLayer))
		{
			SelectLayer(m_view->m_activeLayer);
		}
*/
		{
			CComQIPtr<INotifySend> cp = m_view->m_document;
			DWORD cookie;
			cp->Advise(this, &cookie);
		}

		if (m_hWnd)
		{
//			OnSize();
			Invalidate();
		}

		*cookie = 1;
	}

	return S_OK;
}

STDMETHODIMP CSymbolsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	ATLASSERT(cookie == 1);
	ATLASSERT(m_view != NULL);

	//DeselectAll();

	CComQIPtr<INotifySend> cp = m_view->m_document;
	cp->Unadvise(this);

//	IDispEventImpl<3, CLayersDlg, &DIID__IPDDocumentEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventUnadvise(m_view->m_document);
	m_view->Release();
	m_view = NULL;

	if (m_hWnd)
	{
	//	OnSize();
		Invalidate();
	}

	return S_OK;
}

BEGIN_CMD_MAP(CSymbolsDlg)
	CMD_HANDLER(ID_SYMBOLS_REDEFINESYMBOL, OnSymbolsRedefineSymbol)
	CMD_HANDLER(ID_SYMBOLS_PLACESYMBOLINSTANCE, OnPlaceSymbolInstance)
	CMD_HANDLER(ID_SYMBOLS_SYMBOLOPTIONS, OnSymbolOptions)
	CMD_UPDATE(ID_SYMBOLS_SYMBOLOPTIONS, OnSymbolOptionsUpdate)
END_CMD_MAP()

LRESULT CSymbolsDlg::OnSymbolsRedefineSymbol(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_view)
	{
		CComPtr<IObjectMap> symbols;
		m_view->m_document->get_symbols(&symbols);

		long nsymbols;
		symbols->get_length(&nsymbols);

		if (m_selectedSymbolIndex >= 0 && m_selectedSymbolIndex < nsymbols)
		{
			CComPtr<IPDSymbol> symbol;
			symbols->item(m_selectedSymbolIndex, (IUnknown**)&symbol);

			m_view->DefineSymbol(symbol);
		}
	}

	return 0;
}

LRESULT CSymbolsDlg::OnPlaceSymbolInstance(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_view)
	{
		CComPtr<IObjectMap> symbols;
		m_view->m_document->get_symbols(&symbols);

		long nsymbols;
		symbols->get_length(&nsymbols);

		if (m_selectedSymbolIndex >= 0 && m_selectedSymbolIndex < nsymbols)
		{
			CComPtr<IPDSymbol> symbol;
			symbols->item(m_selectedSymbolIndex, (IUnknown**)&symbol);

			CComPtr<IPDObjectSymbolInstance> symbolInstance;
			symbolInstance.CoCreateInstance(CLSID_PDObjectSymbolInstance);
			if (symbolInstance)
			{
				symbolInstance->put_symbol(symbol);

				CComQIPtr<IPDObjectLayerGroup> activeLayerGroup;

				if (m_view->m_activeSpread)
					m_view->m_activeSpread->getLayerGroupFromLayer(m_view->m_activeLayer, &activeLayerGroup);

				activeLayerGroup->appendObject(symbolInstance);

				m_view->SelectPDObject(symbolInstance, 0, true);
			}
		}
	}

	return 0;
}

#include "SymbolOptionsDlg.h"

LRESULT CSymbolsDlg::OnSymbolOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_selectedSymbols.GetSize() == 1)
	{
		CSymbolOptionsDlg dlg;
		dlg.m_targetObjects.Add(m_selectedSymbols[0]);

		if (dlg.DoModal(GetMainHwnd()) == IDOK)
		{
		}
	}

	return 0;
}

void CSymbolsDlg::OnSymbolOptionsUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	pCmdUI->Enable(m_selectedSymbols.GetSize() == 1);
}
