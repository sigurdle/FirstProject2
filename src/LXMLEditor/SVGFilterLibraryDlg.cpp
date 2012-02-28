#include "stdafx.h"
#include "LXMLEditor2.h"
#include "SVGFilterLibraryDlg.h"

#include "EXMLDocument.h"	// TODO, remove

//#include "..\OleDataObject.h"

#if 0

HRESULT AddSVGElements(IEXMLDocument* m_document, HGLOBAL hData);
//HRESULT ApplyStyle(IWebXMLDocument* m_document);

/////////////////////////////////////////////////////////////////////////////
// CSVGFilterLibraryDlg

int CSVGFilterLibraryDlg::FinalConstruct()
{
//	CComQIPtr<IUIManager> uiManager = gIFrame;
//	uiManager->FindMenu(IDR_SVGFILTERLIBRARYDLG, &m_menu);

	return 0;
}

LRESULT CSVGFilterLibraryDlg::OnClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_listView.m_selectedItems.GetSize() > 0)
	{
		COleDataObject* pDataObject;
		CComObject<COleDataObject>::CreateInstance(&pDataObject);
		if (pDataObject)
		{
			pDataObject->AddRef();

			CMyDropSource*  pDropSource = new CMyDropSource;

			CComBSTR xmltext;
			
			xmltext = L"<svg>";

			for (int i = 0; i < m_listView.m_selectedItems.GetSize(); i++)
			{
				CSVGListViewItem* pItem = m_listView.m_selectedItems[i];
				CComPtr<ILDOMElement> element = (ILDOMElement*)pItem->m_element;
				if (element)
				{
					CComBSTR xmltext2;
					m_listView.m_xmlDocument->saveXML(_variant_t(element), &xmltext2);

					xmltext += xmltext2;
				}
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
						if (dropEffect == DROPEFFECT_NONE)
						{
							ATLASSERT(0);
#if 0
							CComPtr<IEDocument> webdocument;
							gIApp->get_ActiveDocument(&webdocument);

							CComQIPtr<IEXMLDocument> document = webdocument;
							if (document)
							{
								AddSVGElements(document, hData);

							// TODO have somewhere else
								ATLASSERT(0);
#if 0
								if (m_listView.m_selectedItemIndex >= 0 && m_listView.m_selectedItemIndex < m_listView.m_items.GetSize())
								{
									CComBSTR id;
									m_listView.m_items[m_listView.m_selectedItemIndex]->m_element->getAttribute(L"id", &id);

									_bstr_t filter = L"url(#" + _bstr_t(id) + L")";

									((CEXMLDocument*)document.p)->m_defaultStyle->setProperty(L"filter", filter, NULL);

									ApplyStyle(document);
								}
#endif
							}
#endif
						}
					}
					else
					{
						MessageBeep(-1);
					}
				}

				GlobalFree(hData);
			}

			pDataObject->Release();
		}
	}

	return 0;
}

STDMETHODIMP CSVGFilterLibraryDlg::Load(BSTR pathName)
{
	if (SUCCEEDED(m_listView.m_xmlDocument.CoCreateInstance(CLSID_LSVGDocument)))
	{
		VARIANT_BOOL bsuccess;
		m_listView.m_xmlDocument->load(_variant_t(pathName), &bsuccess);

		if (bsuccess)
		{
			BuildItems();
		}
	}

	return S_OK;
}

BEGIN_CMD_MAP(CSVGFilterLibraryDlg)
//	CMD_HANDLER(ID_FILTERS_NEWFILTER, OnFiltersNewFilter)

	CMD_HANDLER(ID_SVGLIST_SMALLTHUMBNAILS, OnFiltersSmallThumbnails)
	CMD_HANDLER(ID_SVGLIST_LARGETHUMBNAILS, OnFiltersLargeThumbnails)
	CMD_HANDLER(ID_SVGLIST_SMALLLISTVIEW, OnFiltersSmallListView)
	CMD_HANDLER(ID_SVGLIST_LARGELISTVIEW, OnFiltersLargeListView)
	CMD_UPDATE(ID_SVGLIST_SMALLTHUMBNAILS, OnFiltersSmallThumbnailsUpdate)
	CMD_UPDATE(ID_SVGLIST_LARGETHUMBNAILS, OnFiltersLargeThumbnailsUpdate)
	CMD_UPDATE(ID_SVGLIST_SMALLLISTVIEW, OnFiltersSmallListViewUpdate)
	CMD_UPDATE(ID_SVGLIST_LARGELISTVIEW, OnFiltersLargeListViewUpdate)
END_CMD_MAP()

#endif