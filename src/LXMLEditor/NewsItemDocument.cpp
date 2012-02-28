// NewsItemDocument.cpp : Implementation of CNewsItemDocument
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "NewsItemDocument.h"

#include "NewsItemView.h"

//#include "WebEditorApp.h"
//#include "WebEditorFrame.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CNewsItemDocument

void CNewsItemDocument::ShowView()
{
#if 0
	{
		CComObject<CUIMDIChild>* child;
		CComObject<CUIMDIChild>::CreateInstance(&child);
		child->AddRef();
		gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

		{
		// DTD
			CComObject<CNewsItemView>* view;
			CComObject<CNewsItemView>::CreateInstance(&view);
			if (view)
			{
			//	gApp->m_frame->FindMenu(IDR_SCHEMAVIEW, &view->m_menu);
				//dtdView->m_document = (CComObject<CDTDDocument>*)this;
				child->AddPage(view, NULL);
			}
		}

		child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);
	}
#endif
}

#endif