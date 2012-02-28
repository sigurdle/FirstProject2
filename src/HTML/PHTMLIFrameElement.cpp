#include "stdafx.h"
#include "HTML2.h"

#if 0

#include "PHTMLIFrameElement.h"
#include "LHTMLIFrameElement.h"

#include "..\LXUI\LXUIFrameContent.h"
#include "..\LXUI\LXUIFrameContentView.h"

#include "PBlockBox.h"

/////////////////////////////////////////////////////////////////////////
// CPHTMLIFrameElement

CPHTMLIFrameElement::CPHTMLIFrameElement()
{
	m_pContainer = NULL;
}

CPHTMLIFrameElement::~CPHTMLIFrameElement()
{
}

void CPHTMLIFrameElement::PlaceControls(HWND hWndParent, CHTMFlowBlockContext* /*pC*/)
{
	ASSERT(0);
#if 0
	CLHTMLIFrameElement* pElement = static_cast<CLHTMLIFrameElement*>(m_pNode);

	if (m_pBox)
	{
		Gdiplus::RectF rcf = m_pBox->GetAbsInnerRect();

		CRect rc((int)rcf.X, (int)rcf.Y, (int)rcf.GetRight(), (int)rcf.GetBottom());

		if (pElement->m_pFrameContent == NULL)
		{
			CComObject<CLHTMLFrameContent>::CreateInstance(&pElement->m_pFrameContent);
			pElement->m_pFrameContent->AddRef();

			// TODO
			CPElement* pParent = this;
			while (pParent)
			{
				CComQIPtr<IOleInPlaceFrame> frame = static_cast<ILViewNode*>(pParent);
				if (frame)
				{
					pElement->m_pFrameContent->m_pInPlaceFrame = frame;
					break;
				}
				pParent = pParent->m_parent;
			}

			pElement->m_pFrameContent->m_hWnd = hWndParent;

			pElement->Load();
		}

		if (pElement->m_pFrameContent)
		{
			if (pElement->m_pFrameContent->m_spOleObject)
			{
				if (pElement->m_pFrameContent->m_pViewSite == NULL)
				{
#if 0
					pElement->m_pFrameContent->m_spOleObject->DoVerb(OLEIVERB_SHOW, NULL, pElement->m_pFrameContent, 0, hWndParent, &rc);
#endif
				}
				else
				{
					pElement->m_pFrameContent->m_pViewSite->SetRect(rc);
				}
			}
		}
	}

	if (pElement->m_pFrameContent)
	{
		if (pElement->m_pFrameContent->m_pViewSite)
		{
			ASSERT(pElement->m_pFrameContent->m_pViewSite->m_pIOleDocView);

			BOOL bShow = m_pBox != NULL;
			pElement->m_pFrameContent->m_pViewSite->m_pIOleDocView->Show(bShow);
		}
	}
#endif
}

#endif