#include "stdafx.h"
#include "LPDF.h"
#include "PDFPDPage.h"

#include "PDFPDDoc.h"
#include "PDFEContent.h"

#include "PDFCosDoc.h"
#include "PDFCosStream.h"	//TODO remove

namespace System
{
namespace PDF
{

/////////////////////////////////////////////////////////////////////////////
// CPDFPDPage

void CPDFPDPage::FinalRelease()
{
	if (m_pContent)
	{
	//	m_pContent->Release();
		m_pContent = NULL;
	}
}

CPDFEContent* CPDFPDPage::AcquirePDEContent()
{
	if (m_pContent == NULL)
	{
		m_pContent = new CPDFEContent;//::CreateInstance(&m_pContent);
		if (m_pContent)
		{
		//	m_pContent->AddRef();
			m_pContent->m_pPage = this;
		}
	}

	return m_pContent;
	//if (*pVal) (*pVal)->AddRef();
}

void CPDFPDPage::ReleasePDEContent()
{
	if (m_pContent == NULL) throw (Error);
	ASSERT(m_pContent);

	if (m_pContent)
	{
		// Create page's content stream if none exist
		if (m_pCosContents == NULL)
		{
			m_pCosContents = m_pDoc->m_cos->CosNewStream(true, NULL);
			m_cos->CosDictPut(ASTR("Contents"), m_pCosContents);

			/*
			TCHAR temppath[512];
			GetTempPath(sizeof(temppath), temppath);

			TCHAR filename[512];
			GetTempFileName(temppath, "pdf", 0, filename);

			m_pCosContents->m_filename = filename;
			*/
		}

		ASSERT(0);
#if 0
		FILE* fp = fopen(static_cast<CPDFCosStream*>(m_pCosContents)->m_filename.c_str(), "wb");
		if (fp)
		{
		// Update fonts/images used on page
			m_pContent->UpdateResources(m_pCosResources);

			// Write object hierarchy to the stream
			m_pContent->WriteToStream(fp);

			DWORD streamSize = ftell(fp);
			fclose(fp);

		// Update (or set if this is the first time) the length attribute of the stream object
			CPDFCosInteger* pLength;

			CPDFCosDict* attributesDict;
			m_pCosContents->CosStreamDict(&attributesDict);
			pLength = dynamic_cast<CPDFCosInteger*>(attributesDict->CosDictGet("Length"));
			if (pLength == NULL)
			{
				m_pDoc->m_cos->CosNewInteger(VARIANT_FALSE, streamSize, &pLength);
				attributesDict->CosDictPut("Length", pLength);
			}
			else
				pLength->SetValue(streamSize);

			m_pContent->Release();
			m_pContent = NULL;
		}
#endif
	}
}

CPDFPDDoc* CPDFPDPage::GetDoc()
{
	return m_pDoc;
}

}	// PDF
}
