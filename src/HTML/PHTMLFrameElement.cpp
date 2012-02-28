#include "stdafx.h"
#include "HTML2.h"

#include "PHTMLFrameElement.h"

#include "HTMLFrameElement.h"

//#include "..\LXUI\LXUIFrameContent.h"
//#include "..\LXUI\LXUIFrameContentView.h"

namespace System
{
namespace Web
{

#if 0
void PHTMLFrameElement::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"Link")
		{
			evt->stopPropagation();

			LinkEvent* linkEvt = (LinkEvent*)evt;

			HTMLFrameElement* pElement = static_cast<HTMLFrameElement*>(m_pNode);

		//	delete pElement->m_pFrameContent;
			pElement->m_pFrameContent = NULL;

			pElement->set_src(linkEvt->m_href);

			if (pElement->m_pFrameContent == NULL)
			{
				pElement->Load();
				m_pControl->set_VisualTree(pElement->m_pFrameContent);
				m_pControl->InvalidateArrange();
				m_pControl->Invalidate();
			}
		}
	}
}
#endif

void PHTMLFrameElement::OnReady()
{
	ASSERT(0);
#if 0
	CLHTMLFrameElement* pElement = static_cast<CLHTMLFrameElement*>(m_pNode);

//	ASSERT(m_pBox);
//	LDraw::RectF rcf = m_pBox->GetAbsInnerRect();

	set_VisualTree/*pElement->m_ownerDocument->m_pWindow->AddRChild*/(pElement->m_pFrameContent);

	InvalidateArrange();
	Invalidate();

	MessageBeep(-1);
#endif

//dynamic_cast<CLXUIControl*>(m_pNode)->Invalidate();
}

void PHTMLFrameElement::Set()
{
	if (m_pBox)
	{
		gm::RectF rcf = m_pBox->GetAbsInnerRect();

	//	CRect rc((int)rcf.X, (int)rcf.Y, (int)rcf.GetRight(), (int)rcf.GetBottom());

		HTMLFrameElement* pElement = static_cast<HTMLFrameElement*>(m_pNode);

//		/*pElement->m_ownerDocument->*/ m_pWindow->AddRChild(this);//pElement->m_pFrameContent);
			ASSERT(0);
#if 0
		if (m_pControl->GetRParent() == NULL)
		{
			m_pWindow->AddRChild(m_pControl);//pElement->m_pFrameContent);
		}
/*pElement->m_pFrameContent->*/m_pControl->Measure(LDraw::SizeD(rcf.Width, rcf.Height));
/*pElement->m_pFrameContent->*/m_pControl->Arrange(LDraw::RectD(rcf.X, rcf.Y, rcf.Width, rcf.Height));
	//	/*pElement->m_pFrameContent->*/m_pControl->SetLayoutOffset(rcf.X, rcf.Y);
#endif

		if (!m_bTriedLoading)
		{
			m_bTriedLoading = true;
			pElement->Load();
		}


#if 0
			if (pElement->m_pFrameContent)
			{
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
			}
#endif

#if 0
		if (pElement->m_pFrameContent)
		{
			if (pElement->m_pFrameContent->m_pViewSite == NULL)
			{
				pElement->m_pFrameContent->m_hWnd = hWndParent;
				pElement->m_pFrameContent->m_spOleObject->DoVerb(OLEIVERB_SHOW, NULL, pElement->m_pFrameContent, 0, hWndParent, &rc);
			}
			else
			{
				pElement->m_pFrameContent->m_pViewSite->SetRect(rc);
			}
		}
#endif
	}
	else
		ASSERT(0);
}

}	// Web
}
