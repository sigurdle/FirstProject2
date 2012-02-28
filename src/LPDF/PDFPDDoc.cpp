#include "stdafx.h"
#include "LPDF.h"
#include "PDFPDDoc.h"

#include "PDFPDPage.h"

#include "PDFCosInteger.h"	// TODO remove

#include "PDFCosDoc.h"
#include "PDFCosDict.h"

#include "PDFEMatrix.h"

#include "PDFEImage.h"

#include "PDFEPath.h"

namespace System
{
namespace PDF
{

CPDFPDDoc::CPDFPDDoc()
{
	m_cos = NULL;
	m_cos = new CPDFCosDoc;
}

ErrorCode CPDFPDDoc::Create()
{
	m_cos->Create();
	return Success;
}

CPDFPDPage* CPDFPDDoc::CreatePage(long afterPageNum, double x1, double y1, double x2, double y2)
{
	CPDFCosDict* catalog = m_cos->GetRoot();

	CPDFCosDict* pPages = dynamic_cast<CPDFCosDict*>(catalog->CosDictGet(ASTR("Pages")));

	if (pPages)
	{
		CPDFCosArray* pKids = dynamic_cast<CPDFCosArray*>(pPages->CosDictGet(ASTR("Kids")));
		ASSERT(pKids);

		CPDFCosInteger* pCount = dynamic_cast<CPDFCosInteger*>(pPages->CosDictGet(ASTR("Count")));
		ASSERT(pCount);

		CPDFPDPage* pPage = new CPDFPDPage;
		if (pPage)
		{
		//	pPage->AddRef();

			pPage->m_pDoc = this;

			pPage->m_cos = m_cos->CosNewDict(true);

			{
				CPDFCosName* pType =	m_cos->CosNewName(false, ASTR("Page"));
				pPage->m_cos->CosDictPut(ASTR("Type"), pType);

				pPage->m_pCosResources = m_cos->CosNewDict(false);
				pPage->m_cos->CosDictPut(ASTR("Resources"), pPage->m_pCosResources);

				pPage->m_cos->CosDictPut(ASTR("Parent"), pPages);

				CPDFCosArray* pMediaBox = m_cos->CosNewArray(false);
				pPage->m_cos->CosDictPut(ASTR("MediaBox"), pMediaBox);
				{
					CPDFCosReal* pX =	m_cos->CosNewReal(false, x1);
					pMediaBox->CosArrayInsert(-1, pX);

					CPDFCosReal* pY =	m_cos->CosNewReal(false, y1);
					pMediaBox->CosArrayInsert(-1, pY);

					CPDFCosReal* pW =	m_cos->CosNewReal(false, x2);
					pMediaBox->CosArrayInsert(-1, pW);

					CPDFCosReal* pH =	m_cos->CosNewReal(false, y2);
					pMediaBox->CosArrayInsert(-1, pH);
				}

				/*
				CPDFCosStream* pContents = m_cos->CosNewStream(true, NULL);
				pPage->m_cos->CosDictPut("Contents", pContents);
				*/
			}

			pKids->CosArrayInsert(-1, pPage->m_cos);
			static_cast<CPDFCosInteger*>(pCount)->SetValue(static_cast<CPDFCosInteger*>(pCount)->GetValue() + 1);

			m_pages.InsertAt(afterPageNum+1, pPage);
		}

	//	pPage->AddRef();
		//if (*pVal) (*pVal)->AddRef();
		return pPage;
	}

	return NULL;
}

void CPDFPDDoc::SetInfo(StringA* binfoKey, StringA* bvalue)
{
/*
	if (m_cos->m_pInfo == NULL)
	{
		m_cos->m_pInfo = m_cos->CosNewDict(true);
		if (m_cos->m_pInfo)
		{
			m_cos->m_cosObjects.Add(m_cos->m_pInfo);
		}
	}

	if (m_cos->m_pInfo)
	{
		_bstr_t infoKey = _bstr_t(binfoKey);
		_bstr_t value = _bstr_t(bvalue);

		CPDFCosString* pString = m_cos->CosNewString(false, (char*)value, value.length());
		m_cos->m_pInfo->CosDictPut(infoKey, pString);
	}
*/
}

void CPDFPDDoc::Read(StringA* filename)
{
	m_cos->Read(filename);
}

void CPDFPDDoc::Save(StringA* pathName)
{
	m_cos->Save(pathName);
}

CPDFCosDoc* CPDFPDDoc::GetCosDoc()
{
	//m_cos->AddRef();
	return m_cos;
}

void CPDFPDDoc::SetCosDoc(CPDFCosDoc* cos)
{
	ASSERT(m_cos == NULL);
	m_cos = cos;
//	m_cos->AddRef();
}

CPDFEMatrix* CPDFPDDoc::CreateMatrix()
{
	CPDFEMatrix* pMatrix = new CPDFEMatrix;
	return pMatrix;
}

CPDFEImage* CPDFPDDoc::CreateImageFromCosObj(CPDFCosStream *imageObj, CPDFEMatrix *matrix)
{
	CPDFEImage* pImage = new CPDFEImage;
	if (pImage)
	{
		pImage->m_cos = imageObj;

		double a = matrix->get_a(); pImage->m_matrix->set_a(a);
		double b = matrix->get_b(); pImage->m_matrix->set_b(b);
		double c = matrix->get_c(); pImage->m_matrix->set_c(c);
		double d = matrix->get_d(); pImage->m_matrix->set_d(d);
		double e = matrix->get_e(); pImage->m_matrix->set_e(e);
		double f = matrix->get_f(); pImage->m_matrix->set_f(f);

		return pImage;//)->AddRef();
	}

	return NULL;
}

CPDFEPath* CPDFPDDoc::CreatePath()
{
	CPDFEPath* pPath = new CPDFEPath;
	if (pPath)
	{
		return pPath;//)->AddRef();
	}

	return NULL;
}

}	// PDF
}
