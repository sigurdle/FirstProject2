#include "stdafx.h"
#include "LPDF.h"
#include "PDFCosDict.h"

namespace System
{
namespace PDF
{
System::StringA* ReadNameFromStream(std::FILE* fp);

void CPDFCosDict::CosDictPut(System::StringA* name, CPDFCosObj *value)
{
	if (value == NULL) THROW(Error_InvalidArgument);

	CPDFCosDictEntry* pEntry = new CPDFCosDictEntry;
	pEntry->m_name = name;
	pEntry->m_value = value;
	
	m_entries.Add(pEntry);
}

CPDFCosObj* CPDFCosDict::CosDictGet(System::StringA* name)
{
	for (int i = 0; i < m_entries.GetSize(); i++)
	{
		if (*m_entries[i]->m_name == *name)
		{
			CPDFCosObj* obj = m_entries[i]->m_value;
		//	obj->AddRef();
			return obj;
		}
	}
	return NULL;
}

//virtual
void CPDFCosDict::WriteToStream(std::FILE* fp)
{
	if (m_id)
	{
		m_offset = std::ftell(fp);

		std::fprintf(fp, "%ld 0 obj\r\n", m_id);
	}

	std::fprintf(fp, "<<\r\n");

	for (int i = 0; i < m_entries.GetSize(); i++)
	{
		std::fprintf(fp, "/%s ", m_entries[i]->m_name->c_str());

		uint32 id = m_entries[i]->m_value.m_pObj->GetID();

		if (id)	// Write reference
		{
			std::fprintf(fp, "%ld 0 R", id);
		}
		else
		{
			m_entries[i]->m_value.m_pObj->WriteToStream(fp);
		}

		std::fprintf(fp, "\r\n");
	}

	std::fprintf(fp, ">>\r\n");

	if (m_id)
	{
		std::fprintf(fp, "endobj\r\n");
	}
}

void CPDFCosDict::ReadFromStream(std::FILE* fp)
{
	//fscanf(fp, "<<");
	if (std::fgetc(fp) != '<' || std::fgetc(fp) != '<')
		throw -1;

	std::fscanf(fp, "\r\n ");

	while (!feof(fp))
	{
		long pos = std::ftell(fp);

		if (std::fgetc(fp) == '>')
		{
			if (std::fgetc(fp) == '>')
			{
				break;
			}
		}

		std::fseek(fp, pos, SEEK_SET);

		// key must be a name
		System::StringA* name = ReadNameFromStream(fp);

		CosObject pObj = m_pCosDoc->ReadObject(fp);
		{
			CPDFCosDictEntry* pEntry = new CPDFCosDictEntry;
			pEntry->m_name = name;
			pEntry->m_value = pObj;
			m_entries.Add(pEntry);
		}

		std::fscanf(fp, "\r\n ");
	}
}

}
}
