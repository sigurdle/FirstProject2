// StrokeDlg.cpp : Implementation of CStrokeDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "StrokeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CStrokeDlg

LRESULT CStrokeDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::SendMessage(GetDlgItem(IDC_STROKE_CAP0), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_STROKE_CAP0)));
	::SendMessage(GetDlgItem(IDC_STROKE_CAP1), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_STROKE_CAP1)));
	::SendMessage(GetDlgItem(IDC_STROKE_CAP2), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_STROKE_CAP2)));

	::SendMessage(GetDlgItem(IDC_STROKE_JOIN0), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_STROKE_JOIN0)));
	::SendMessage(GetDlgItem(IDC_STROKE_JOIN1), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_STROKE_JOIN1)));
	::SendMessage(GetDlgItem(IDC_STROKE_JOIN2), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_STROKE_JOIN2)));

//	GetDlgControl(IDC_STROKE_WEIGHT, IID_IUIEditUnitValue, (void**)&m_strokeWeightCtl);

//	IDispEventImpl<1, CStrokeDlg, &DIID__IUIEditUnitValueEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_strokeWeightCtl);

	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("0.5 pt"));
	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("1 pt"));
	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("2 pt"));
	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("3 pt"));
	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("4 pt"));
	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("5 pt"));
	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("6 pt"));
	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("7 pt"));
	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("8 pt"));
	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("9 pt"));
	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("10 pt"));
	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("12 pt"));
	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("15 pt"));
	::SendMessage(GetDlgItem(IDC_STROKE_WEIGHT), CB_ADDSTRING, 0, (LPARAM)_T("20 pt"));

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	return 0;
	return 1;  // Let the system set the focus
}

LRESULT CStrokeDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

//	IDispEventImpl<1, CStrokeDlg, &DIID__IUIEditUnitValueEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_strokeWeightCtl);

	return 0;
}

LRESULT CStrokeDlg::OnStrokeWeightChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	BOOL bTrans;

	double strokeWeight = GetDlgItemValue(m_hWnd, IDC_STROKE_WEIGHT, &bTrans);
	if (bTrans)
	{
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			m_targetObjects[i]->put_strokeWeight(strokeWeight);
		}
	}

	return 0;
}

LRESULT CStrokeDlg::OnStrokeCapChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		m_targetObjects[i]->put_strokeCap(wID-IDC_STROKE_CAP0);
	}

	return 0;
}

LRESULT CStrokeDlg::OnStrokeJoinChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		m_targetObjects[i]->put_strokeJoin(wID-IDC_STROKE_JOIN0);
	}

	return 0;
}

LRESULT CStrokeDlg::OnStrokeMiterLimitChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	TCHAR buf[64];
	GetDlgItemText(IDC_STROKE_MITERLIMIT, buf, sizeof(buf));

	int miterlimit = atof(buf);
	if (miterlimit < 1) miterlimit = 1;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		m_targetObjects[i]->put_strokeMiterLimit(miterlimit);
	}

	return 0;
}

LRESULT CStrokeDlg::OnStrokeDashChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	double dashArray[6];

	for (int n = 0; n < 6; n++)
	{
		BOOL bTrans;
		dashArray[n] = GetDlgItemValue(m_hWnd, IDC_STROKE_DASHED0+n, &bTrans);
		if (!bTrans)
		{
			dashArray[n] = -1;
			break;
		}
	}

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		for (int j = 0; j < n; j++)
		{
			m_targetObjects[i]->setDashedValue(j, dashArray[j]);
		}
	}

	return 0;
}

void CStrokeDlg::GetControlValues()
{
	ATLASSERT(0);
}

void CStrokeDlg::SetControlValues()
{
	// Weight
	{
		double strokeWeight = tomUndefined;
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CComPtr<IPDStrokeSettings> stroke = m_targetObjects[i];

			double strokeWeight2;
			stroke->get_strokeWeight(&strokeWeight2);

			if (i == 0)
			{
				strokeWeight = strokeWeight2;
			}
			else if (strokeWeight != strokeWeight2)
			{
				strokeWeight = tomUndefined;
				break;
			}
		}

		if (strokeWeight != tomUndefined)
			SetDlgItemValue(m_hWnd, IDC_STROKE_WEIGHT, strokeWeight, UNIT_PT);
		else
			SetDlgItemText(IDC_STROKE_WEIGHT, "");
	}

	// Cap
	{
		long strokeCap = tomUndefined;
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CComPtr<IPDStrokeSettings> stroke = m_targetObjects[i];

			long strokeCap2;
			stroke->get_strokeCap(&strokeCap2);

			if (i == 0)
			{
				strokeCap = strokeCap2;
			}
			else if (strokeCap != strokeCap2)
			{
				strokeCap = tomUndefined;
				break;
			}
		}

		CheckRadioButton(IDC_STROKE_CAP0, IDC_STROKE_CAP2, IDC_STROKE_CAP0+strokeCap);
	}

	// Join
	{
		double strokeJoin = tomUndefined;
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CComPtr<IPDStrokeSettings> stroke = m_targetObjects[i];

			long strokeJoin2;
			stroke->get_strokeJoin(&strokeJoin2);

			if (i == 0)
			{
				strokeJoin = strokeJoin2;
			}
			else if (strokeJoin != strokeJoin2)
			{
				strokeJoin = tomUndefined;
				break;
			}
		}

		CheckRadioButton(IDC_STROKE_JOIN0, IDC_STROKE_JOIN2, IDC_STROKE_JOIN0+strokeJoin);
	}

	// MiterLimit
	{
		double miterLimit = tomUndefined;
		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CComPtr<IPDStrokeSettings> stroke = m_targetObjects[i];

			double miterLimit2;
			stroke->get_strokeMiterLimit(&miterLimit2);

			if (i == 0)
			{
				miterLimit = miterLimit2;
			}
			else if (miterLimit != miterLimit2)
			{
				miterLimit = tomUndefined;
				break;
			}
		}


		if (miterLimit != tomUndefined)
			SetDlgItemInt(IDC_STROKE_MITERLIMIT, miterLimit);
		else
			SetDlgItemText(IDC_STROKE_MITERLIMIT, "");
	}

// Dashes
	{
		double dashValues[6];
		long dashedCount = 0;

		for (int i = 0; i < m_targetObjects.GetSize(); i++)
		{
			CComPtr<IPDStrokeSettings> stroke = m_targetObjects[i];

			long dashedCount2;
			stroke->get_dashedCount(&dashedCount2);

			if (i == 0)
			{
				dashedCount = dashedCount2;
			}
			else if (dashedCount != dashedCount2)
			{
				dashedCount = 0;
				break;
			}

			for (int j = 0; j < dashedCount2; j++)
			{
				double value2;
				stroke->getDashedValue(j, &value2);
				if (i == 0)
				{
					dashValues[j] = value2;
				}
				else if (dashValues[j] != value2)
				{
					break;
				}
			}

			if (j < dashedCount2)
			{
				dashedCount = 0;
				break;
			}
		}

		for (i = 0; i < 6; i++)
		{
			if (i < dashedCount)
				SetDlgItemValue(m_hWnd, IDC_STROKE_DASHED0+i, dashValues[i], UNIT_PT);
			else
				SetDlgItemText(IDC_STROKE_DASHED0+i, "");
		}
	}
}

STDMETHODIMP CStrokeDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IPDStrokeSettings> stroke = object;
	if (stroke)
	{
		m_targetObjects.Add(stroke.Detach());

		*cookie = m_targetObjects.GetSize();

		SetControlValues();
	}

	return S_OK;
}

STDMETHODIMP CStrokeDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_targetObjects[i], object))
		{
			m_targetObjects[i]->Release();
			m_targetObjects.RemoveAt(i);
		}
	}

	SetControlValues();

	return S_OK;
}
