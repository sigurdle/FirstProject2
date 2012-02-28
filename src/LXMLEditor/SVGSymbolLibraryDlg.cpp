// SVGSymbolLibraryDlg.cpp : Implementation of CSVGSymbolLibraryDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "SVGSymbolLibraryDlg.h"

#if 0
#include "..\OleDataObject.h"

/////////////////////////////////////////////////////////////////////////////
// CSVGSymbolLibraryDlg

LRESULT CSVGSymbolLibraryDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;
	
	ButtonDown(nFlags, point);

	if (m_selectedItems.GetSize() > 0)
	{
		COleDataObject* pDataObject;
		CComObject<COleDataObject>::CreateInstance(&pDataObject);
		if (pDataObject)
		{
			pDataObject->AddRef();

			CMyDropSource*  pDropSource = new CMyDropSource;

			CComBSTR xmltext;
			
			xmltext = L"<svg>";

			for (int i = 0; i < m_selectedItems.GetSize(); i++)
			{
				CComPtr<ILSVGElement> element = m_selectedItems[i];

				CComBSTR xmltext2;
				m_xmlDocument->saveXML(element, &xmltext2);

				xmltext += xmltext2;
			}

			xmltext += L"</svg>";

			HGLOBAL hData = GlobalAlloc(GMEM_SHARE, (xmltext.Length()+1)*2);
			if (hData)
			{
				WCHAR* pData = (WCHAR*)GlobalLock(hData);
				if (pData)
				{
					CopyMemory(pData, (BSTR)xmltext, (xmltext.Length()+1)*2);

					GlobalUnlock(pData);

					STGMEDIUM stgm;
					stgm.tymed = TYMED_HGLOBAL;
					stgm.pUnkForRelease = NULL;
					stgm.hGlobal = hData;

					FORMATETC etc = { CF_UNICODETEXT, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
					pDataObject->SetData(&etc, &stgm, FALSE/*TRUE*/ /*fRelese*/);

					DWORD dropEffect = 0;
					if (::DoDragDrop(pDataObject, pDropSource, DROPEFFECT_COPY/* | DROPEFFECT_MOVE*/, &dropEffect) == DRAGDROP_S_DROP)
					{
					}
				}

				GlobalFree(hData);
			}

			pDataObject->Release();
		}
	}
#endif
	return 0;
}

STDMETHODIMP CSVGSymbolLibraryDlg::Load(BSTR pathName)
{
	if (SUCCEEDED(m_listView.m_xmlDocument.CoCreateInstance(CLSID_LSVGDocument)))
	{
		VARIANT_BOOL bsuccess;
		m_listView.m_xmlDocument->load(_variant_t(pathName), &bsuccess);

		if (bsuccess)
		{
			BuildItems();
		}

		if (m_hWnd)
		{
			Invalidate();
		}
	}

	return S_OK;
}

#endif