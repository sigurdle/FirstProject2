#include "stdafx.h"
#include "PageDesigner.h"

#include "PDF.h"

/////////////////////
//

FILE* CPDFCosStream::OpenFStream(LPCTSTR mode)
{
	if (m_filename.GetLength() == 0)
	{
		TCHAR temppath[512];
		GetTempPath(sizeof(temppath), temppath);

		TCHAR filename[512];
		GetTempFileName(temppath, "pdf", 0, filename);

		m_filename = filename;
	}

	FILE* fp = fopen(m_filename, mode);
	if (fp)
	{
		m_fmode = mode;
		return fp;
	}

	return NULL;
}

void CPDFCosStream::CloseFStream(FILE* fp)
{
	if (strchr(m_fmode, 'w'))
	{
		fseek(fp, 0, SEEK_END);
		DWORD streamSize = ftell(fp);

	// Update (or set if this is the first time) the length attributes of the stream object
		CPDFCosInteger* pLength = (CPDFCosInteger*)m_attributesDict->CosDictGet("Length");
		if (pLength == NULL)
		{
			pLength = m_pCosDoc->CosNewInteger(false, streamSize);
			m_attributesDict->CosDictPut("Length", pLength);
		}
		else
			pLength->m_value = streamSize;
	}

	fclose(fp);
}


////////////////////////////////////
//

CPDFFont* CPDFDoc::GetOrCreateFont(PDEFontAttrs* fattrs)
{
	CPDFFont* pFont = NULL;

// Find if a font with same name etc already exist in document
	for (int i = 0; i < m_fonts.GetSize(); i++)
	{
		CPDFCosString* pBaseFont = (CPDFCosString*)m_fonts[i]->m_cos->CosDictGet("BaseFont");
		ATLASSERT(pBaseFont);

		if (!strnicmp(pBaseFont->m_str, fattrs->name, pBaseFont->m_nBytes))
		{
			pFont = m_fonts[i];
			break;
		}
	}

	if (pFont == NULL)	// Create font object directionary
	{
		pFont = new CPDFFont;
		pFont->m_cos = m_cos->CosNewDict(true);
		m_cos->m_cosObjects.Add(pFont->m_cos);

		CPDFCosName* pType = m_cos->CosNewName(false, "Font");
		pFont->m_cos->CosDictPut("Type", pType);

		CPDFCosName* pSubtype = m_cos->CosNewName(false, fattrs->type);
		pFont->m_cos->CosDictPut("Subtype", pSubtype);

		CPDFCosName* pBaseFont = m_cos->CosNewName(false, fattrs->name);
		pFont->m_cos->CosDictPut("BaseFont", pBaseFont);

		m_fonts.Add(pFont);
	}

	return pFont;
}

void CPDFEContent::UpdateFontNames(CPDFEElement* element)
{
	if (element->GetType() == 1)	// Text
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
	else if (element->GetType() == 3)	// Image
	{
		CPDFEImage* pImage = (CPDFEImage*)element;

		CPDFCosObject* pObject = pImage->m_cos;

	// Create /XObjects entry in Resource
		CPDFCosDict* pXObjectDict = (CPDFCosDict*)m_pPage->m_pCosResources->CosDictGet("XObject");
		if (!pXObjectDict)
		{
			pXObjectDict = m_pPage->m_pDoc->m_cos->CosNewDict(false);
			m_pPage->m_pCosResources->CosDictPut("XObject", pXObjectDict);
		}
		ATLASSERT(pXObjectDict);

		int nobject = FindDictObject(pXObjectDict, pObject);
		if (nobject == 0)
		{
			nobject = pXObjectDict->m_entries.GetSize()+1;

			CUString str;
			str.Format("Im%d", nobject);
			pXObjectDict->CosDictPut(str, pImage->m_cos);
		}

		pImage->m_nIndex = nobject;
	}

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
}

///////////////////////////////////////
// CPDFCosDoc

STDMETHODIMP CPDFCosDoc::Save(TCHAR* pathName)
{
	FILE* m_fp;

	m_fp = fopen(pathName, "wb");
	if (m_fp)
	{
		fprintf(m_fp, "%%PDF-1.4\r\n");

		for (int i = 0; i < m_cosObjects.GetSize(); i++)
		{
			if (m_cosObjects[i]->m_id)
			{
				m_cosObjects[i]->WriteToStream(m_fp);
			}
		}

		CPDFCosArray* pObject = new CPDFCosArray;
		m_cosObjects.Add(pObject);
		pObject->m_id = ++m_nextID;
		pObject->m_offset = ftell(m_fp);

		fprintf(m_fp,
			"%ld 0 obj\r\n"
			"[/PDF]\r\n"
			"endobj\r\n",
			pObject->m_id);

		long startxref = ftell(m_fp);

		fprintf(m_fp, "xref\r\n");
		fprintf(m_fp, "0 %d\r\n", m_cosObjects.GetSize()+1);
		fprintf(m_fp, "0000000000 65535 f\r\n");

		for (i = 0; i < m_cosObjects.GetSize(); i++)
		{
			fprintf(m_fp, "%10.10ld 00000 n\r\n", m_cosObjects[i]->m_offset);
		}

		CPDFCosDict* pTrailerDict = CosNewDict(false);
		if (pTrailerDict)
		{
			{// Size
				CPDFCosInteger* pSize = CosNewInteger(false, m_cosObjects.GetSize()+1);
				pTrailerDict->CosDictPut("Size", pSize);
			}

			if (m_pCatalog)
			{// Root
				pTrailerDict->CosDictPut("Root", m_pCatalog);
			}

			if (m_pInfo)
			{// Info
				pTrailerDict->CosDictPut("Info", m_pInfo);
			}

			fprintf(m_fp, "trailer\r\n");
			pTrailerDict->WriteToStream(m_fp);
			fprintf(m_fp, "\r\n");
		}

		fprintf(m_fp, "startxref\r\n%ld\r\n", startxref);

		fprintf(m_fp, "%%EOF");

		fclose(m_fp);
		m_fp = NULL;

		return S_OK;
	}

	return E_FAIL;
}

////////////////////////////////////////
// CPDFPage

STDMETHODIMP CPDFPage::GetCosResources(CPDFCosDict* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pCosResources;
	return S_OK;
}

STDMETHODIMP CPDFPage::AddCosResource(char* resType, char* resName, CPDFCosObject *resObj)
{
	ATLASSERT(m_pCosResources);

	if (!strcmp(resType, "Font"))
	{
		CPDFCosDict* pDict = (CPDFCosDict*)m_pCosResources->CosDictGet(resType);
		if (pDict == NULL)
		{
			pDict = m_pDoc->m_cos->CosNewDict(false);
			m_pCosResources->CosDictPut(resType, pDict);
		}

		pDict->CosDictPut(resName, resObj);
	}
	else
		return E_FAIL;

	return S_OK;
}

STDMETHODIMP CPDFPage::AcquirePDEContent(CPDFEContent* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_pContent == NULL)
	{
		m_pContent = new CPDFEContent;
		m_pContent->m_pPage = this;
	}

	*pVal = m_pContent;
	return S_OK;
}

STDMETHODIMP CPDFPage::ReleasePDEContent()
{
	ATLASSERT(m_pContent);

	if (m_pContent)
	{
		// Create page's content stream if none exist
		if (m_pCosContents == NULL)
		{
			m_pCosContents = m_pDoc->m_cos->CosNewStream(true, NULL);
			m_cos->CosDictPut("Contents", m_pCosContents);
			m_pDoc->m_cos->m_cosObjects.Add(m_pCosContents);

			TCHAR temppath[512];
			GetTempPath(sizeof(temppath), temppath);

			TCHAR filename[512];
			GetTempFileName(temppath, "pdf", 0, filename);

			m_pCosContents->m_filename = filename;
		}

		FILE* fp = fopen(m_pCosContents->m_filename, "wb");
		if (fp)
		{
		// Update fonts/images used on page
			m_pContent->UpdateFontNames();

#if 0
			if (m_pContent->m_fonts.GetSize() > 0)
			{
			// Create /Font entry in Resource
				CPDFCosDict* pFontDict = (CPDFCosDict*)m_pCosResources->CosDictGet("Font");
				if (!pFontDict)
				{
					pFontDict = m_pDoc->m_cos->CosNewDict(false);
					m_pCosResources->CosDictPut("Font", pFontDict);
				}
				ATLASSERT(pFontDict);

				for (int i = 0; i < m_pContent->m_fonts.GetSize(); i++)
				{
					CPDFFont* pFont = NULL;

				// Find if a font with same name etc already exist in document
					for (int j = 0; j < m_pDoc->m_fonts.GetSize(); j++)
					{
						CPDFCosString* pBaseFont = (CPDFCosString*)m_pDoc->m_fonts[j]->m_cos->CosDictGet("BaseFont");
						ATLASSERT(pBaseFont);
						
						if (!strnicmp(pBaseFont->m_str, m_pContent->m_fonts[i]->m_attrs.name, pBaseFont->m_nBytes))
						{
							pFont = m_pDoc->m_fonts[j];
							break;
						}
					}

					if (pFont == NULL)	// Create font object directionary
					{
						pFont = new CPDFFont;
						pFont->m_cos = m_pDoc->m_cos->CosNewDict(true);
						m_pDoc->m_cos->m_cosObjects.Add(pFont->m_cos);

						CPDFCosName* pType = m_pDoc->m_cos->CosNewName(false, "Font");
						pFont->m_cos->CosDictPut("Type", pType);

						CPDFCosName* pSubtype = m_pDoc->m_cos->CosNewName(false, m_pContent->m_fonts[i]->m_attrs.type);
						pFont->m_cos->CosDictPut("Subtype", pSubtype);

						CPDFCosName* pBaseFont = m_pDoc->m_cos->CosNewName(false, m_pContent->m_fonts[i]->m_attrs.name);
						pFont->m_cos->CosDictPut("BaseFont", pBaseFont);

						m_pDoc->m_fonts.Add(pFont);
					}

					pFontDict->CosDictPut(m_pContent->m_fonts[i]->m_name, pFont->m_cos);
				}
			}
#endif

			// Write object hierarchy to the stream
			m_pContent->WriteToStream(fp);

			DWORD streamSize = ftell(fp);
			fclose(fp);

		// Update (or set if this is the first time) the length attributes of the stream object
			CPDFCosInteger* pLength = (CPDFCosInteger*)m_pCosContents->m_attributesDict->CosDictGet("Length");
			if (pLength == NULL)
			{
				pLength = m_pDoc->m_cos->CosNewInteger(false, streamSize);
				m_pCosContents->m_attributesDict->CosDictPut("Length", pLength);
			}
			else
				pLength->m_value = streamSize;

			delete m_pContent;
			m_pContent = NULL;
		}
	}

	return S_OK;
}

////////////////////////////////////////
// CPDFDoc

STDMETHODIMP CPDFDoc::CreatePage(int afterPageNum, RectD mediaBox, CPDFPage* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = NULL;

	CPDFCosDict* pPages = (CPDFCosDict*)m_cos->m_pCatalog->CosDictGet("Pages");
	if (pPages)
	{
		CPDFCosArray* pKids = (CPDFCosArray*)pPages->CosDictGet("Kids");
		ATLASSERT(pKids);

		CPDFCosInteger* pCount = (CPDFCosInteger*)pPages->CosDictGet("Count");
		ATLASSERT(pCount);

		CPDFPage* pPage = new CPDFPage;
		pPage->m_pDoc = this;
		pPage->m_cos = m_cos->CosNewDict(true);
		m_cos->m_cosObjects.Add(pPage->m_cos);

		{
			CPDFCosName* pType = m_cos->CosNewName(false, "Page");
			pPage->m_cos->CosDictPut("Type", pType);

			pPage->m_pCosResources = m_cos->CosNewDict(false);
			//m_cos->m_cosObjects.Add(pPage->m_pCosResources);
			pPage->m_cos->CosDictPut("Resources", pPage->m_pCosResources);

			pPage->m_cos->CosDictPut("Parent", pPages);

			CPDFCosArray* pMediaBox = m_cos->CosNewArray(false);
			pPage->m_cos->CosDictPut("MediaBox", pMediaBox);
			{
				CPDFCosReal* pX = m_cos->CosNewReal(false, mediaBox.X);
				pMediaBox->m_items.Add(pX);

				CPDFCosReal* pY = m_cos->CosNewReal(false, mediaBox.Y);
				pMediaBox->m_items.Add(pY);

				CPDFCosReal* pW = m_cos->CosNewReal(false, mediaBox.Width);
				pMediaBox->m_items.Add(pW);

				CPDFCosReal* pH = m_cos->CosNewReal(false, mediaBox.Height);
				pMediaBox->m_items.Add(pH);
			}

			/*
			CPDFCosStream* pContents = m_cos->CosNewStream(true, NULL);
			pPage->m_cos->CosDictPut("Contents", pContents);
			*/
		}

		pKids->m_items.Add(pPage->m_cos);
		pCount->m_value++;

		m_pages.InsertAt(afterPageNum+1, pPage);

		*pVal = pPage;
	}

	return S_OK;
}

STDMETHODIMP CPDFDoc::SetInfo(BSTR binfoKey, BSTR bvalue)
{
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

	return S_OK;
}

STDMETHODIMP CPDFDoc::Create()
{
	{
		m_cos->m_pCatalog = m_cos->CosNewDict(true);
		if (m_cos->m_pCatalog)
		{
			m_cos->m_cosObjects.Add(m_cos->m_pCatalog);

			CPDFCosName* cosobj = m_cos->CosNewName(false, "Catalog");
			m_cos->m_pCatalog->CosDictPut("Type", cosobj);
		}
	}

	{
		CPDFCosDict* pPages = m_cos->CosNewDict(true);
		if (pPages)
		{
			m_cos->m_cosObjects.Add(pPages);

			CPDFCosName* pType = m_cos->CosNewName(false, "Pages");
			pPages->CosDictPut("Type", pType);

			CPDFCosArray* pKids = m_cos->CosNewArray(false);
			pPages->CosDictPut("Kids", pKids);

			CPDFCosInteger* pCount = m_cos->CosNewInteger(false, 0);
			pPages->CosDictPut("Count", pCount);
		}

		m_cos->m_pCatalog->CosDictPut("Pages", pPages);	// Add pages to catalog
	}

	return S_OK;
}

STDMETHODIMP CPDFDoc::Save(TCHAR* filename)
{
	return m_cos->Save(filename);
}
