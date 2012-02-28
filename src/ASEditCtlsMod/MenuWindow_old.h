#if 0

class CMenuWindow : public CWindowImpl<CMenuWindow>
{
public:

	CMenuWindow()
	{
		m_items.Add(_T("Element"));
		m_items.Add(_T("Sequence"));
		m_items.Add(_T("Choice"));
		m_items.Add(_T("All"));
	}

	CComQIPtr<IASModel> m_asModel;
	CArray<CUString,CUString> m_items;

BEGIN_MSG_MAP(CMenuWindow)
	MESSAGE_HANDLER(WM_LBUTTONDOWN,, OnLButtonDown)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_MOVING, OnMoving)
//	MESSAGE_HANDLER(WM_CREATE, OnCreate)
//	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
END_MSG_MAP()

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnMoving(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::InvalidateRect(GetParent(), NULL, TRUE);

		//::SendMessage(::GetParent(GetParent()), WM_SIZE, 0, 0);

		return 0;
	}

};

/////////////////////////////////////////////
// CMenuWindow

LRESULT CMenuWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	int y = 0;
	for (int i = 0; i < m_items.GetSize(); i++)
	{
		dc.TextOut(0, y, m_items[i]);
		y += 16;

	}

	return 0;
}

LRESULT CMenuWindow::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	int index = point.y / 16;
	if (index >= 0 && index < m_items.GetSize())
	{
		if (index == 0)	// Element
		{
		}
		else
		{
			CComPtr<IASContentModel> cm;

			if (index == 1)	// Sequence
			{
				m_asModel->createASContentModel(1, 1, AS_SEQUENCE, &cm);
			}
			else if (index == 2)	// Choice
			{
				m_asModel->createASContentModel(1, 1, AS_CHOICE, &cm);
			}
			else if (index == 3)	// All
			{
				m_asModel->createASContentModel(1, 1, AS_ALL, &cm);
			}

			if (cm)
			{
				CComObject<COleDataObject>* dataObject;
				CComObject<COleDataObject>::CreateInstance(&dataObject);
				if (dataObject)
				{
					dataObject->AddRef();

					/*
					CComPtr<ILDOMDocument> document;
					document.CoCreateInstance(CLSID_LDOMDocument);
					VARIANT_BOOL bsuccess;
					document->loadXML(L"<as/>", &bsuccess);
					*/

					UINT nFormat = RegisterClipboardFormat("ASGraph-Item");

					/*
					int nCount = 0;
					for (int i = 0; i < ((CDTDDesignContentModel*)pNode->m_pParent)->m_defs.GetSize(); i++)
					{
						CDTDDesignContentModel* pItem = (CDTDDesignContentModel*)((CDTDDesignContentModel*)pNode->m_pParent)->m_defs[i];
						if (pItem->m_bSelected)
						{
							nCount++;
						}
					}
					*/

					HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(void*)+sizeof(int));
					if (hData)
					{
						void** p = (void**)GlobalLock(hData);

						p[0] = (void*)1;	// count
						p[1] = cm;

						GlobalUnlock(hData);

						CMyDropSource*  dropSource = new CMyDropSource;

						STGMEDIUM stgm;
						stgm.tymed = TYMED_HGLOBAL;
						stgm.pUnkForRelease = NULL;
						stgm.hGlobal = hData;

						FORMATETC etc = { nFormat, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
						dataObject->SetData(&etc, &stgm, FALSE/*TRUE*/);

						DWORD dropEffect = 0;
						HRESULT hr = ::DoDragDrop(dataObject, dropSource, DROPEFFECT_LINK | DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect);

						if (hr == DRAGDROP_S_DROP)
						{
							if (dropEffect/* & DROPEFFECT_MOVE*/)
							{
							}
						}

						GlobalFree(hData);
					}

					dataObject->Release();
				}
			}
		}
	}

	return 0;
}

#endif