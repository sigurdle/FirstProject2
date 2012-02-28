// SwatchesDlg.cpp : Implementation of CSwatchesDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "SwatchesDlg.h"

// TODO: remove this
#include "PageDesignerApp.h"
#include "PageDesignerFrame.h"
extern CPageDesignerApp* gApp;

/////////////////////////////////////////////////////////////////////////////
// CSwatchesDlg

int CSwatchesDlg::FinalConstruct()
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->FindMenu(IDR_SWATCHES, &m_menu);

	m_swatchesList.CoCreateInstance(CLSID_SwatchesList);
	m_swatchesList->put_multiSelect(VARIANT_TRUE);

	return S_OK;
}

LRESULT CSwatchesDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axswatchesList.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axswatchesList.AttachControl(m_swatchesList, &p);

	IDispEventImpl<1, CSwatchesDlg, &DIID__ISwatchesListEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventAdvise(m_swatchesList);

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	return 0;
}

LRESULT CSwatchesDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

	IDispEventImpl<1, CSwatchesDlg, &DIID__ISwatchesListEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventUnadvise(m_swatchesList);

	return 0;
}

LRESULT CSwatchesDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axswatchesList.MoveWindow(0, 0, client.right, client.bottom);

	return 0;
}

void __stdcall CSwatchesDlg::OnClickSwatch(IPDSwatch* swatch)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComPtr<IPDObjectWithBrush> object = m_targetObjects[i];

		CComPtr<IPDBrush> brush;
		object->get_brush(&brush);

		brush->put_swatch(swatch);

#if 0
		if (gApp->m_strokeOrFill == 0)
			frame->get_strokeBrush(&brush);
		else
			frame->get_fillBrush(&brush);

		brush->put_swatch(swatch);
#endif
	}
}

void CSwatchesDlg::UpdateSwatchesListCtl()
{
	CComPtr<IPDSwatch> swatch;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComPtr<IPDBrush> brush;
		m_targetObjects[i]->get_brush(&brush);

		CComPtr<IPDSwatch> swatch2;
		brush->get_swatch(&swatch2);

		if (i == 0)
		{
			swatch = swatch2;
		}
		else if (!IsUnknownEqualUnknown(swatch, swatch2))
		{
			swatch.Release();
			break;
		}
	}

	m_swatchesList->selectSwatch(swatch);
}

STDMETHODIMP CSwatchesDlg::OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
{
	//if (m_reentrance == 0)
	{
//		m_reentrance++;

		UpdateSwatchesListCtl();

//		m_reentrance--;
	}

	return S_OK;
}

STDMETHODIMP CSwatchesDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IPDDocument> document = object;
	if (document)
	{
		document->get_swatches(&m_swatches);
		m_swatchesList->put_swatches(m_swatches);

		*cookie = -1;
	}
	else
	{
		CComQIPtr<IPDObjectWithBrush> objectWithBrush = object;
		if (objectWithBrush)
		{
			{
				CComQIPtr<INotifySend> cp = objectWithBrush;
				DWORD cookie;
				cp->Advise(this, &cookie);
			}
			m_targetObjects.Add(objectWithBrush.Detach());

			*cookie = m_targetObjects.GetSize();

			UpdateSwatchesListCtl();
		}
	}

	return S_OK;
}

STDMETHODIMP CSwatchesDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	if (cookie > 0)
	{
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_targetObjects[i], object))
			{
				CComQIPtr<INotifySend> cp = object;
				cp->Unadvise(this);

				m_targetObjects[i]->Release();
				m_targetObjects.RemoveAt(i);

				UpdateSwatchesListCtl();

				break;
			}
		}
	}

	return S_OK;
}

// ICommandTarget
STDMETHODIMP CSwatchesDlg::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;
/*
// Try view
	CComQIPtr<ICommandTarget> view = m_view;
	if (view) view->OnCmdMsg(iid, pCmdUI, bHandled);
*/

	return S_OK;
}

BEGIN_CMD_MAP(CSwatchesDlg)
	CMD_HANDLER(ID_SWATCHES_NEWCOLORSWATCH, OnNewColorSwatch)
	CMD_HANDLER(ID_SWATCHES_NEWGRADIENTSWATCH, OnNewGradientSwatch)
	CMD_HANDLER(ID_SWATCHES_NEWTINTSWATCH, OnNewTintSwatch)
	CMD_HANDLER(ID_SWATCHES_DELETESWATCH, OnDeleteSwatch)
	CMD_UPDATE(ID_SWATCHES_DELETESWATCH, OnDeleteSwatchUpdate)
	CMD_HANDLER(ID_SWATCHES_SWATCHOPTIONS, OnSwatchOptions)
	CMD_UPDATE(ID_SWATCHES_SWATCHOPTIONS, OnSwatchOptionsUpdate)
END_CMD_MAP()

#include "ColorSwatchOptionsDlg.h"
#include "GradientSwatchOptionsDlg.h"
#include "PatternSwatchOptionsDlg.h"

LRESULT CSwatchesDlg::OnNewColorSwatch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_swatches)
	{
		CColorSwatchOptionsDlg dlg;

		CComPtr<IPDSwatchColor> swatch;
		m_swatches->createSwatchColor(&swatch);
		swatch->put_name(L"New Color Swatch");

		dlg.m_targetObjects.Add(swatch);

		if (dlg.DoModal(GetMainHwnd()) == IDOK)
		{
			m_swatches->appendSwatch(swatch);

			Invalidate();	// TODO remove
		}
	}

	return 0;
}

LRESULT CSwatchesDlg::OnNewGradientSwatch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_swatches)
	{
		CGradientSwatchOptionsDlg dlg;

		CComPtr<IPDSwatchGradient> swatch;
		m_swatches->createSwatchGradient(&swatch);
		swatch->put_name(L"New Gradient Swatch");

		dlg.m_swatches = m_swatches;
		dlg.m_targetObjects.Add(swatch);

		if (dlg.DoModal(GetMainHwnd()) == IDOK)
		{
			m_swatches->appendSwatch(swatch);

			Invalidate();	// TODO remove
		}
	}

	return 0;
}

LRESULT CSwatchesDlg::OnNewTintSwatch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_swatches)
	{
	}

	return 0;
}

LRESULT CSwatchesDlg::OnDeleteSwatch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CArray<IPDSwatch*,IPDSwatch*> targetObjects;

	VARIANT_BOOL canDelete = VARIANT_TRUE;

	long index = 0;
	CComPtr<IPDSwatch> swatch;

	while (SUCCEEDED(m_swatchesList->getNextSelectedSwatch(index, &swatch)) && swatch)
	{
		VARIANT_BOOL canDelete2;
		swatch->get_canDelete(&canDelete2);
		if (!canDelete2)
		{
			canDelete = VARIANT_FALSE;
			break;
		}

		targetObjects.Add(swatch.Detach());

		index++;
	}

	if (canDelete)
	{
		for (int i = 0; i < targetObjects.GetSize(); i++)
		{
			m_swatches->removeSwatch(targetObjects[i]);
		}
	}

	for (int i = 0; i < targetObjects.GetSize(); i++)
	{
		targetObjects[i]->Release();
	}

	return 0;
}

void CSwatchesDlg::OnDeleteSwatchUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	VARIANT_BOOL canDelete = VARIANT_TRUE;

	long index = 0;
	CComPtr<IPDSwatch> swatch;

	while (SUCCEEDED(m_swatchesList->getNextSelectedSwatch(index, &swatch)) && swatch)
	{
		VARIANT_BOOL canDelete2;
		swatch->get_canDelete(&canDelete2);
		if (!canDelete2)
		{
			canDelete = VARIANT_FALSE;
			break;
		}

		swatch.Release();
		index++;
	}

	if (canDelete)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

LRESULT CSwatchesDlg::OnSwatchOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	long index = 0;
	CComPtr<IPDSwatch> swatch;

	PDSwatchType swatchType = (PDSwatchType)0;

	CArray<IPDSwatch*,IPDSwatch*> targetObjects;

	while (SUCCEEDED(m_swatchesList->getNextSelectedSwatch(index, &swatch)) && swatch)
	{
		PDSwatchType swatchType2;
		swatch->get_swatchType(&swatchType2);

		if (index == 0)
		{
			swatchType = swatchType2;
		}
		else if (swatchType != swatchType2)
		{
			swatchType = (PDSwatchType)0;
			break;
		}

		targetObjects.Add(swatch.Detach());

		index++;
	}
	
	if (swatchType)
	{
		if (swatchType == SWATCH_COLOR)
		{
			CColorSwatchOptionsDlg dlg;

			for (int i = 0; i < targetObjects.GetSize(); i++)
			{
				dlg.m_targetObjects.Add((IPDSwatchColor*)targetObjects[i]);
			}

			if (dlg.DoModal(GetMainHwnd()) == IDOK)
			{
			}
		}
		else if (swatchType == SWATCH_GRADIENT)
		{
			CGradientSwatchOptionsDlg dlg;

			dlg.m_swatches = m_swatches;

			for (int i = 0; i < targetObjects.GetSize(); i++)
			{
				dlg.m_targetObjects.Add((IPDSwatchGradient*)targetObjects[i]);
			}

			if (dlg.DoModal(GetMainHwnd()) == IDOK)
			{
			}
		}
		else if (swatchType == SWATCH_PATTERN)
		{
			CPatternSwatchOptionsDlg dlg;

			for (int i = 0; i < targetObjects.GetSize(); i++)
			{
				dlg.m_targetObjects.Add((IPDSwatchPattern*)targetObjects[i]);
			}

			if (dlg.DoModal(GetMainHwnd()) == IDOK)
			{
			}
		}
	}

	for (int i = 0; i < targetObjects.GetSize(); i++)
	{
		targetObjects[i]->Release();
	}

	return 0;
}

void CSwatchesDlg::OnSwatchOptionsUpdate(long iid, IUICmdUpdate* pCmdUI)
{
// Check that all selected swatches are of same type
	PDSwatchType swatchType = (PDSwatchType)0;

	long index = 0;
	CComPtr<IPDSwatch> swatch;

	while (SUCCEEDED(m_swatchesList->getNextSelectedSwatch(index, &swatch)) && swatch)
	{
		PDSwatchType swatchType2;
		swatch->get_swatchType(&swatchType2);

		if (index == 0)
		{
			swatchType = swatchType2;
		}
		else if (swatchType != swatchType2)
		{
			swatchType = (PDSwatchType)0;
			break;
		}

		swatch.Release();
		index++;
	}
	
	if (swatchType)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}
