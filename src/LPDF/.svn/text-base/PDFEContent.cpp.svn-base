#include "stdafx.h"
#include "LPDF.h"
#include "PDFEContent.h"

#include "PDFEElement.h"

#include "PDFEImage.h"

#include "PDFCosDict.h"

namespace System
{
namespace PDF
{

/////////////////////////////////////////////////////////////////////////////
// CPDFEContent

void CPDFEContent::WriteToStream(std::FILE* fp)
{
	for (int i = 0; i < m_elements.GetSize(); i++)
	{
		/*static_cast<CPDFEElement*>(static_cast<IPDFEElementImpl<IPDFEElement>*>*/(m_elements[i])->WriteToStream(fp);
	}
}

int CPDFEContent::FindDictObject(CPDFCosDict* pXObjectDict, CPDFCosObj* pObject)
{
	for (int i = 0; i < static_cast<CPDFCosDict*>(pXObjectDict)->m_entries.GetSize(); i++)
	{
		if (static_cast<CPDFCosDict*>(pXObjectDict)->m_entries[i]->m_value == pObject)
		{
			return i+1;
		}
	}

	return 0;
}

void CPDFEContent::UpdateResources(CPDFCosDict* pCosResources, CPDFEElement* element)
{
	PDFEType type = element->GetType();

#if 0
	if (type == kPDFEText)	// Text
	{
		CPDFEText* pText = (CPDFEText*)element;

	// Create /Fonts entry in Resource
		CPDFCosDict* pFontDict = (CPDFCosDict*)m_pPage->m_pCosResources->CosDictGet("Font");
		if (!pFontDict)
		{
			pFontDict = m_pPage->m_pDoc->m_cos->CosNewDict(false);
			m_pPage->m_pCosResources->CosDictPut("Font", pFontDict);
		}
		ATLASSERT(pFontDict);

		for (int i = 0; i < pText->m_textRuns.GetSize(); i++)
		{
			CPDFETextRun* pRun = pText->m_textRuns[i];

			if (pRun->m_pFont->m_nIndex == 0)
			{
				ATLASSERT(pRun->m_pFont->m_cos == NULL);

				CPDFFont* pFont = m_pPage->m_pDoc->GetOrCreateFont(&pRun->m_pFont->m_attrs);
				pRun->m_pFont->m_cos = pFont->m_cos;
				ATLASSERT(pRun->m_pFont->m_cos);

				int nobject = FindDictObject(pFontDict, pRun->m_pFont->m_cos);
				if (nobject == 0)
				{
					nobject = pFontDict->m_entries.GetSize()+1;

					CUString str;
					str.Format("F%d", nobject);
					pFontDict->CosDictPut(str, pRun->m_pFont->m_cos);
				}

				pRun->m_pFont->m_nIndex = nobject;
			}

			/*
			int nfont = FindFont(pRun->m_pFont);
			if (nfont == 0)
			{
				nfont = m_fonts.Add(pRun->m_pFont)+1;
				pRun->m_pFont->m_name.Format("F%d", nfont);
			}
			*/
		}
	}
	else
#endif
		if (type == kPDFEImage)	// Image
	{
		CPDFEImage* pImage = static_cast<CPDFEImage*>(element);

	// Create /XObjects entry in Resource
		CPDFCosDict* pXObjectDict = dynamic_cast<CPDFCosDict*>(pCosResources->CosDictGet(ASTR("XObject")));
		if (pXObjectDict == NULL)
		{
			CPDFCosDoc* cosdoc = pCosResources->GetDoc();

			pXObjectDict = cosdoc->CosNewDict(false);
			pCosResources->CosDictPut(ASTR("XObject"), pXObjectDict);
		}
		ASSERT(pXObjectDict);

		int nobject = FindDictObject(pXObjectDict, pImage->m_cos);
		if (nobject == 0)
		{
			nobject = pXObjectDict->m_entries.GetSize()+1;

			char str[32];
			std::sprintf(str, "Im%d", nobject);
			pXObjectDict->CosDictPut(ASTR(str), pImage->m_cos);
		}

		pImage->m_nIndex = nobject;
	}
#if 0
	if (element->m_gstate.extGState)
	{
		ATLASSERT(element->m_gstate.extGState->m_cos);

	// Create /ExtGState entry in Resource
		CPDFCosDict* pExtGStateDict = (CPDFCosDict*)m_pPage->m_pCosResources->CosDictGet("ExtGState");
		if (!pExtGStateDict)
		{
			pExtGStateDict = m_pPage->m_pDoc->m_cos->CosNewDict(false);
			m_pPage->m_pCosResources->CosDictPut("ExtGState", pExtGStateDict);
		}
		ATLASSERT(pExtGStateDict);

		int nobject = FindDictObject(pExtGStateDict, element->m_gstate.extGState->m_cos);
		if (nobject == 0)
		{
			nobject = pExtGStateDict->m_entries.GetSize()+1;

			CUString str;
			str.Format("GS%d", nobject);
			pExtGStateDict->CosDictPut(str, element->m_gstate.extGState->m_cos);

			element->m_gstate.extGState->m_nIndex = nobject;
		}
	}
#endif
}

uint CPDFEContent::GetNumElems()
{
	return m_elements.GetSize();
}

void CPDFEContent::AddElem(long addAfterIndex, CPDFEElement *pdeElement)
{
	if (pdeElement == NULL) throw(Error_InvalidArgument);
//	pdeElement->AddRef();

//	pdeElement->m_pPage = m_pPage;

	if (addAfterIndex > m_elements.GetSize())
		m_elements.Add(pdeElement);
	else
		m_elements.InsertAt(addAfterIndex+1, pdeElement);
}

}}
