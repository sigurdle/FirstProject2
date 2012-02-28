// EPlayListDocument.cpp : Implementation of CEPlayListDocument
#include "stdafx.h"
#include "LXMedia.h"
#include "LXMedia2.h"
#include "EPlayListDocument.h"

#include "PlayListView.h"

//#include "LXFrameworkApp.h"
//#include "LXFrameworkFrame.h"
//extern CLXFrameworkApp* gApp;

/////////////////////////////////////////////////////////////////////////////
// CEPlayListDocument

// IEDocument

//	STDMETHOD(GetDocumentsClass)(/*[out,retval]*/ IDocumentsClass* *pVal);
//	STDMETHOD(get_undoManager)(/*[out, retval]*/ IOleUndoManager* *pVal);
//	STDMETHOD(LoadDocumentByteArray)(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success);

STDMETHODIMP CEPlayListDocument::Activate()
{
	return S_OK;
}

STDMETHODIMP CEPlayListDocument::NewDocument()
{
	return S_OK;
}

STDMETHODIMP CEPlayListDocument::CloseDocument()
{
	return S_OK;
}

STDMETHODIMP CEPlayListDocument::ShowViews(IEFrame* pFrame)
{
	ATLASSERT(0);
#if 0
	CComObject<CUIMDIChild>* child;
	CComObject<CUIMDIChild>::CreateInstance(&child);
	child->AddRef();
	child->m_spFrame = gApp->m_frame;//->GetUnknown();

	CComObject<CPlayListView>* pView;
	CComObject<CPlayListView>::CreateInstance(&pView);
	if (pView)
	{
		pView->m_pDocument = this;

		//gApp->m_frame->FindMenu(IDR_MEDIACLIPVIEW, &pClipView->m_menu);
		child->AddPage(pView, NULL);

		//m_pVideoClipView = pView;
	}

	ATLASSERT(0);
	//child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);
#endif

	return S_OK;
}

// IPersistFile
STDMETHODIMP CEPlayListDocument::Load(/* [in] */ LPCOLESTR pszFileName, /* [in] */ DWORD dwMode)
{
	USES_CONVERSION;

	FILE* fp = fopen(W2A(pszFileName), "r");
	if (fp)
	{
		char s[256];

		fgets(s, 256, fp);
		if (strncmp(s, "#EXTM3U\n", 8) == 0)
		{
			while (!feof(fp))
			{
				fgets(s, 8, fp);
				if (strncmp(s, "#EXTINF", 7) == 0)
				{
					int seconds;
					if (fscanf(fp, ":%d,", &seconds) == 1)
					{
						char title[512];
						if (fgets(title, sizeof(title), fp) == NULL)	// get to newline
						{
							break;
						}
						title[strlen(title)-1] = 0;	// replace \n with n

						char filename[512];
						if (fgets(filename, sizeof(filename), fp) == NULL)
						{
							break;
						}
						filename[strlen(filename)-1] = 0;	// replace \n with n

						CPlayListItem* pItem = new CPlayListItem;
						pItem->m_title = title;
						pItem->m_filename = filename;
						pItem->m_duration = seconds;

						m_items.AddTail(pItem);
					}
				}
				else
				{
					break;
				}

				char c;
				while (isspace(c = fgetc(fp)));
				ungetc(c, fp);
			}
		}

		fclose(fp);
	}

	return S_OK;//LoadFile(pszFileName);
}

BEGIN_CMD_MAP(CEPlayListDocument)
//	CMD_HANDLER(ID_EDIT_PLAY, OnPlay)
END_CMD_MAP()
