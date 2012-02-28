#include "stdafx.h"
#include "LPDF.h"
#include "PDFCosDoc.h"

#include "PDFCosName.h"
#include "PDFCosDict.h"
#include "PDFCosArray.h"
#include "PDFCosInteger.h"
#include "PDFCosString.h"
#include "PDFCosReal.h"
#include "PDFCosStream.h"

#include "../LFC/ZLIBDecoder.h"

namespace System
{
using namespace IO;

namespace PDF
{

CosObject CPDFCosDoc::ReadObject2(std::FILE* fp)
{
	CPDFCosObj* obj = NULL;

	/*
	int c;
	while (isspace(c = fgetc(fp))) ;

	ungetc(c, fp);
	*/
	std::fscanf(fp, "\r\n ");

	long pos = std::ftell(fp);

	if (std::fgetc(fp) == '<' && std::fgetc(fp) == '<')
	{
		obj = new CPDFCosDict;
	}
	else
	{
		std::fseek(fp, pos, SEEK_SET);

		int c = std::fgetc(fp);

		if (c == '/')
		{
			obj = new CPDFCosName;
		}
		else if (c == '[')
		{
			std::fseek(fp, pos, SEEK_SET);

			obj = new CPDFCosArray;
		}
		else if (c == '(')
		{
			std::fseek(fp, pos, SEEK_SET);

			obj = new CPDFCosString;
		}
		else if (c == '<')	// hexadecimal string
		{
			std::fseek(fp, pos, SEEK_SET);

			obj = new CPDFCosString;
		}
		else if (c == 't' || c == 'f')
		{
			std::fseek(fp, pos, SEEK_SET);

			obj = new CPDFCosBoolean;
		}
		else
		{
			std::fseek(fp, pos, SEEK_SET);

			long number;
			int count = std::fscanf(fp, "%ld", &number);
			if (count == 1)
			{
				int c = std::fgetc(fp);
				if (c == '.')
				{
					obj = new CPDFCosReal;
				}
				else
				{
					obj = new CPDFCosInteger;
				}
			}
			else
			{
				std::fseek(fp, pos, SEEK_SET);

				int c = std::fgetc(fp);
				ASSERT(0);
			}
		}
	}

	std::fseek(fp, pos, SEEK_SET);

	if (obj == NULL)
		throw -1;

	if (obj)
	{
		obj->m_pCosDoc = this;
		obj->ReadFromStream(fp);

		CPDFCosDict* pDict = dynamic_cast<CPDFCosDict*>(obj);
		if (pDict)
		{
			long pos = std::ftell(fp);
			std::fscanf(fp, "\r\n ");
			char buf[9];
			std::fread(buf, 1, 6, fp);
			if (std::memcmp(buf, "stream", 6) == 0)
			{
				int c = std::fgetc(fp);

				if (c == '\r')
				{
					c = std::fgetc(fp);
				}
				
				ASSERT(c == '\n');
				if (c != '\n') throw -1;

				CPDFCosStream* pStream = new CPDFCosStream;
				pStream->m_pCosDoc = this;
				pStream->m_attributesDict = pDict;
				obj = pStream;

				CPDFCosInteger* pLength = dynamic_cast<CPDFCosInteger*>(pDict->CosDictGet(ASTR("Length")));

				if (false)
				{
					uint8* buf = new uint8[pLength->GetValue()];
					std::fread(buf, pLength->GetValue(), 1, fp);

					MemoryByteStream* pMem = new MemoryByteStream(buf, pLength->GetValue());

					ZLIBDecoder* pStream = new ZLIBDecoder(pMem);
				//	pStream->start();
				//	pStream->start_block();

					std::FILE* fp2 = std::fopen("c:/stream_temp", "wb");

					while (1)
					{
						uint8 c;
						ULONG nRead = pStream->Read(&c, 1);
						if (nRead == 0)
							break;

						std::fwrite(&c, 1, 1, fp2);
					}

					std::fclose(fp2);
				}
				else
				{
					pStream->m_start = std::ftell(fp);
					std::fseek(fp, pLength->GetValue(), System::IO::STREAM_SEEK_CUR);
				}

				c = std::fgetc(fp);
				if (c == '\r')
				{
					c = std::fgetc(fp);
					ASSERT(c == '\n');
				}
				else
				{
					if (c != '\n')
					{
						std::ungetc(c, fp);
					}
				}
			//	if (c != '\r' && c != '\n')
			//	{
			//		ungetc(c, fp);
			//	}

				std::fread(buf, 9, 1, fp);

				ASSERT(std::memcmp(buf, "endstream", 9) == 0);
			}
			else
			{
				std::fseek(fp, pos, SEEK_SET);
			}
		}
	}

	return obj;
}

CosObject::operator CPDFCosObj* ()
{
	if (m_pObj == NULL)
	{
		long oldpos = std::ftell(m_pCosDoc->m_fp);

		std::fseek(m_pCosDoc->m_fp, m_pCosDoc->m_objectsByIdOffset[m_R], SEEK_SET);
		m_pObj = m_pCosDoc->ReadObject(m_pCosDoc->m_fp);

		ASSERT(m_pObj->m_id == m_R);
		ASSERT(m_pObj->m_genNum == m_gen);

		if (m_pObj->m_id != m_R)
			throw -1;

		m_pCosDoc->m_objectsById[m_R] = m_pObj;

		std::fseek(m_pCosDoc->m_fp, oldpos, SEEK_SET);
	}

	return m_pObj;
}

CosObject CPDFCosDoc::ReadObject(std::FILE* fp)
{
	if (std::fgetc(fp) == '%')
	{
		char buf[512];
		std::fgets(buf, 512, fp);
		std::fscanf(fp, "\r\n ");
	}
	else
	{
		std::fseek(fp, -1, SEEK_CUR);
	}

	long pos = std::ftell(fp);

	// Check for indirect object

	long objectNumber;
	long objectGen;
	if (std::fscanf(fp, "%ld %ld", &objectNumber, &objectGen) == 2)
	{
	//	BufferImp<char> buffer;
	//	StringBuilderA s(&buffer);
		char s[16];
		int n = 0;

		//fscanf(fp, "%s", s);
		std::fscanf(fp, "\r\n ");
		int c;
		while (std::isalpha(c = std::fgetc(fp)))
		{
			if (n == 15) THROW(-1);

			s[n++] = (char)c;
		}
		s[n] = 0;
		std::ungetc(c, fp);

		if (!std::strcmp(s, "obj"))
		{
			CosObject object = ReadObject2(fp);

			object.m_pObj->m_id = objectNumber;
			object.m_pObj->m_genNum = objectGen;

			std::fscanf(fp, "\r\n endobj");

			return object;
		}
		else if (!std::strcmp(s, "R"))
		{
			/*
			CPDFCosRef* pObj = new CPDFCosRef;
			pObj->m_objId = objectNumber;
			*/
			/*
			CPDFCosObj* pObj = m_objectsById[objectNumber];
			if (pObj == NULL)
			{
				fseek(fp, m_objectsByIdOffset[objectNumber], SEEK_SET);
				pObj = ReadObject(fp);
				m_objectsById[objectNumber] = pObj;
			}
			return pObj;
			*/
			CosObject object;
			object.m_pCosDoc = this;
			object.m_R = objectNumber;
			object.m_gen = objectGen;
			return object;
		}
	}

	std::fseek(fp, pos, SEEK_SET);
	return ReadObject2(fp);
}

/////////////////////////////////////////////////////////////////////////////
// CPDFCosDoc

CPDFCosDoc::CPDFCosDoc()
{
	m_nextID = 0L;
	m_pCatalog = NULL;
	m_pInfo = NULL;
	m_pEncrypt = NULL;
	m_pID = NULL;
}

CPDFCosName* CPDFCosDoc::CosNewName(bool indirect, StringA* name)
{
	CPDFCosName* pCosName = new CPDFCosName;
	if (pCosName)
	{
		pCosName->m_pCosDoc = this;
		if (indirect) pCosName->m_id = ++m_nextID;
		pCosName->m_name = name;

		if (indirect)
		{
		//	pCosName->AddRef();
			m_cosObjects.Add(pCosName);
		}

		return pCosName;//->AddRef();
	}

	return NULL;
}

CPDFCosDict* CPDFCosDoc::CosNewDict(bool indirect)
{
	CPDFCosDict* pCosDict = new CPDFCosDict;
	if (pCosDict)
	{
		pCosDict->m_pCosDoc = this;
		if (indirect) pCosDict->m_id = ++m_nextID;

		if (indirect)
		{
			//pCosDict->AddRef();
			m_cosObjects.Add(pCosDict);
		}

		//pCosDict->AddRef();
		return (pCosDict);
	}

	return NULL;
}

CPDFCosArray* CPDFCosDoc::CosNewArray(bool indirect)
{
	CPDFCosArray* pCosArray = new CPDFCosArray;
	if (pCosArray)
	{
		pCosArray->m_pCosDoc = this;
		if (indirect) pCosArray->m_id = ++m_nextID;

		if (indirect)
		{
		//	pCosArray->AddRef();
			m_cosObjects.Add(pCosArray);
		}

		return pCosArray;//->AddRef();

	}

	return NULL;
}

CPDFCosInteger* CPDFCosDoc::CosNewInteger(bool indirect, long value)
{
	CPDFCosInteger* pCosInteger = new CPDFCosInteger;
	if (pCosInteger)
	{
		pCosInteger->m_pCosDoc = this;
		if (indirect) pCosInteger->m_id = ++m_nextID;

		pCosInteger->SetValue(value);

		if (indirect)
		{
			//pCosInteger->AddRef();
			m_cosObjects.Add(pCosInteger);
		}

		return pCosInteger;//->AddRef();

	}

	return NULL;
}

CPDFCosReal* CPDFCosDoc::CosNewReal(bool indirect, double value)
{
	CPDFCosReal* pCosReal = new CPDFCosReal;
	if (pCosReal)
	{
		pCosReal->m_pCosDoc = this;
		if (indirect) pCosReal->m_id = ++m_nextID;

		pCosReal->m_value = value;

		if (indirect)
		{
			//pCosReal->AddRef();
			m_cosObjects.Add(pCosReal);
		}

		return pCosReal;//->AddRef();
	}

	return NULL;
}

CPDFCosStream* CPDFCosDoc::CosNewStream(bool indirect, CPDFCosDict *attributesDict)
{
	if (!indirect)
		return NULL;	// must be true

	CPDFCosDict* rattributesDict;

	if (attributesDict == NULL)
	{
		rattributesDict = CosNewDict(false);
	}
	else
	{
		uint32 id = attributesDict->GetID();
		if (id)
			return NULL;	// must be direct

		rattributesDict = attributesDict;
	}

	CPDFCosStream* pCosStream = new CPDFCosStream;
	if (pCosStream)
	{
		pCosStream->m_pCosDoc = this;
		pCosStream->m_id = ++m_nextID;
		pCosStream->m_attributesDict = rattributesDict;

		if (indirect)
		{
		//	pCosStream->AddRef();
			m_cosObjects.Add(pCosStream);
		}

		return pCosStream;//->AddRef();
	}

	return NULL;
}

ErrorCode CPDFCosDoc::Create()
{
	{
		m_pCatalog = CosNewDict(true);
		if (m_pCatalog)
		{
			CPDFCosName* cosobj = CosNewName(false, ASTR("Catalog"));
			m_pCatalog->CosDictPut(ASTR("Type"), cosobj);
		}
	}

	{
		CPDFCosDict* pPages;
		pPages = CosNewDict(true);
		if (pPages)
		{
			CPDFCosName* pType = CosNewName(false, ASTR("Pages"));
			pPages->CosDictPut(ASTR("Type"), pType);

			CPDFCosArray* pKids = CosNewArray(false);
			pPages->CosDictPut(ASTR("Kids"), pKids);

			CPDFCosInteger* pCount = CosNewInteger(false, 0);
			pPages->CosDictPut(ASTR("Count"), pCount);
		}

		m_pCatalog->CosDictPut(ASTR("Pages"), pPages);	// Add pages to catalog
	}

	return Success;
}

CPDFCosDict* CPDFCosDoc::GetRoot()
{
	//m_pCatalog->AddRef();
	return m_pCatalog;
}

ErrorCode CPDFCosDoc::Read(StringA* pathName)
{
	m_fp = std::fopen(pathName->c_str(), "rb");

//ytestream stream(pStream);
//StringA header = ReadLine(stream);

	char buf[5];
	std::fread(buf, 1, 5, m_fp);

	if (std::memcmp(buf, "%PDF-", 5) != 0)
		return -1;

	char c;

	char version[8];
	while (1)
	{
		c = std::fgetc(m_fp);
		if (c == '\n' || c == '\r')
			break;
	}

	if (true)
	{
		char buf[33] = {0};
		std::fseek(m_fp, -32, SEEK_END);
		std::fread(buf, 1, 32, m_fp);
		char* p = std::strstr(buf, "startxref");
		p += 9;
		while (*p == '\r' || *p == '\n' || *p == ' ')
			p++;

		CPDFCosDict* pFirstDict = NULL;

		CPDFCosInteger* pPrev = NULL;
		long offset;
		std::sscanf(p, "%d", &offset);

		do
		{
			std::fseek(m_fp, offset, SEEK_SET);

			std::fscanf(m_fp, "\r\n%15s", buf);
			if (!std::strcmp(buf, "xref"))
			{
				std::fscanf(m_fp, "\r\n ");
				long start;
				long count;

				std::fscanf(m_fp, "%ld %ld", &start, &count);
				std::fscanf(m_fp, "\r\n ");

				for (int i = 0; i < count; i++)
				{
					long byteoffset;
					long gen;
					char c;
					std::fscanf(m_fp, "%d %d %c\r\n", &byteoffset, &gen, &c);

					m_objectsByIdOffset[start + i] = byteoffset;
				}
			}

			std::fscanf(m_fp, "\r\n%15s", buf);

			if (!std::strcmp(buf, "trailer"))
			{
				std::fscanf(m_fp, "\r\n ");

				CPDFCosDict* pDict = dynamic_cast<CPDFCosDict*>((CPDFCosObj*)ReadObject(m_fp));
				ASSERT(pDict);
				if (pFirstDict == NULL)
					pFirstDict = pDict;

				pPrev = dynamic_cast<CPDFCosInteger*>(pDict->CosDictGet(ASTR("Prev")));

				if (pPrev)
				{
					offset = pPrev->GetValue();
				}
			}
			else
				ASSERT(0);
		}
		while (pPrev);

		m_pCatalog = dynamic_cast<CPDFCosDict*>(pFirstDict->CosDictGet(ASTR("Root")));
		m_pEncrypt = dynamic_cast<CPDFCosDict*>(pFirstDict->CosDictGet(ASTR("Encrypt")));
		m_pID = dynamic_cast<CPDFCosArray*>(pFirstDict->CosDictGet(ASTR("ID")));

		return Success;
	}

#if 0
	while (!feof(m_fp))
	{
		long pos = ftell(m_fp);

		char buf[16];
		fscanf(m_fp, "\r\n%15s", buf);
		if (!strcmp(buf, "xref"))
		{
			fscanf(m_fp, "\r\n ");
			long start;
			long count;

			fscanf(m_fp, "%ld %ld", &start, &count);
			fscanf(m_fp, "\r\n ");

			for (int i = 0; i < count; i++)
			{
				long byteoffset;
				long gen;
				fscanf(m_fp, "%d %d n\r\n", &byteoffset, &gen);

				m_objectsByIdOffset[start + i] = byteoffset;
			}
		}
		else if (!strcmp(buf, "trailer"))
		{
			fscanf(m_fp, "\r\n ");

			CPDFCosDict* pDict = dynamic_cast<CPDFCosDict*>(ReadObject(m_fp));
			ASSERT(pDict);

			ASSERT(0);
#if 0
			CPDFCosRef* pRoot = dynamic_cast<CPDFCosRef*>(pDict->CosDictGet("Root"));

			fseek(m_fp, m_objectsById[pRoot->m_objId], SEEK_SET);

			m_pCatalog = dynamic_cast<CPDFCosDict*>(ReadObject(m_fp));
#endif
			break;
		}
		else
		{
			fseek(m_fp, pos, SEEK_SET);

			CPDFCosObj* pObj = ReadObject(m_fp);

			ASSERT(pObj);
			m_cosObjects.Add((pObj));
		}
	}
#endif

	return 0;
}

ErrorCode CPDFCosDoc::Save(StringA* pathName)
{
	std::FILE* m_fp;

	m_fp = std::fopen(pathName->c_str(), "wb");
	if (m_fp)
	{
		std::fprintf(m_fp, "%%PDF-1.4\r\n");

		for (int i = 0; i < m_cosObjects.GetSize(); i++)
		{
			uint32 id = m_cosObjects[i]->GetID();
			if (id)
			{
				m_cosObjects[i]->WriteToStream(m_fp);
			}
		}

		CPDFCosArray* pObject = new CPDFCosArray;
	//	pObject->AddRef();
		m_cosObjects.Add(pObject);
		pObject->m_id = ++m_nextID;
		pObject->m_offset = std::ftell(m_fp);

		std::fprintf(m_fp,
			"%ld 0 obj\r\n"
			"[/PDF]\r\n"
			"endobj\r\n",
			pObject->m_id);

		long startxref = std::ftell(m_fp);

		std::fprintf(m_fp, "xref\r\n");
		std::fprintf(m_fp, "0 %d\r\n", m_cosObjects.GetSize()+1);
		std::fprintf(m_fp, "0000000000 65535 f\r\n");

		for (int i = 0; i < m_cosObjects.GetSize(); i++)
		{
			std::fprintf(m_fp, "%10.10ld 00000 n\r\n", m_cosObjects[i]->m_offset);
		}

		CPDFCosDict* pTrailerDict;
		pTrailerDict = CosNewDict(false);
		if (pTrailerDict)
		{
			{// Size
				CPDFCosInteger* pSize = CosNewInteger(false, m_cosObjects.GetSize()+1);
				pTrailerDict->CosDictPut(ASTR("Size"), pSize);
			}

			if (m_pCatalog)
			{// Root
				pTrailerDict->CosDictPut(ASTR("Root"), m_pCatalog);
			}

			if (m_pInfo)
			{// Info
				pTrailerDict->CosDictPut(ASTR("Info"), m_pInfo);
			}

			std::fprintf(m_fp, "trailer\r\n");
			(pTrailerDict)->WriteToStream(m_fp);
			std::fprintf(m_fp, "\r\n");
		}

		std::fprintf(m_fp, "startxref\r\n%ld\r\n", startxref);

		std::fprintf(m_fp, "%%EOF");

		std::fclose(m_fp);
		m_fp = NULL;

		return Success;
	}

	return Error;
}

CPDFCosObj* CPDFCosDoc::GetObjByID(uint32 objNum)
{
	if (objNum == 0) return NULL;

	for (int i = 0; i < m_cosObjects.GetSize(); i++)
	{
		uint32 id = m_cosObjects[i]->GetID();
		if (id == objNum)
		{
			//dynamic_cast<Object*>(m_cosObjects[i])->AddRef();
			return m_cosObjects[i];
		}
	}

	return NULL;
}

}
}
