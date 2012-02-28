#include "stdafx.h"
#include "HTML2.h"

#include "SMILDocument.h"

//#include "../LXML/LXMLDocumentView.h"
//#include "LHTMLDocumentView.h"

namespace System
{
namespace Web
{

SMILDocument::SMILDocument()
{
}

String SMILDocument::get_namespaceURI()
{
	return WSTR("http://www.w3.org/2001/SMIL20/Language");
}

void SMILDocument::seekElement(double seekTo)
{
	ASSERT(0);
#if 0
// TODO sequential

	/*
	m_activeChildren->m_items.RemoveAll();
	*/

//	m_activeTime = seekTo;

	if (m_documentElement)
	{
		Element* body = GetElementByTagName(m_documentElement, L"body", FALSE);

		if (body)
		{
			CComQIPtr<CLElementTimeImplImpl> bodyTime = body;
			bodyTime->Seek(seekTo/1000);

		//	double oldTime;	// TODO remove
		//	bodyTime->get_activeTime(&oldTime);// TODO remove

			DoAnimationsForAllElements(m_documentElement, /*oldTime,*/ seekTo/1000);
		}
		else
			ASSERT(0);	// TODO remove

		{
		// TODO, fix up here
			SMILDocument* pDocument = this;//((CLDOMDocument*)m_ownerDocument);

			for (int n = 0; n < pDocument->m_pViews.GetSize(); n++)
			{
#if 0
				pDocument->m_pElements[n]->Flow();
#endif

				ASSERT(0);
#if 0
				if (pDocument->m_pViews[n]->m_pUI)
				{
					pDocument->m_pViews[n]->m_pUI->InvalidateRect(
						&pDocument->m_pViews[n]->m_client, FALSE);
				}
#endif
			}
		}
	}
#endif
}

}	// Web
}
