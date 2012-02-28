// PDFCosArray.cpp : Implementation of CPDFCosArray
#include "stdafx.h"
#include "LPDF.h"
#include "PDFCosArray.h"

namespace System
{
namespace PDF
{

/////////////////////////////////////////////////////////////////////////////
// CPDFCosArray

//virtual
void CPDFCosArray::WriteToStream(std::FILE* fp)
{
	std::fprintf(fp, "[\r\n");

	for (int i = 0; i < m_items.GetSize(); i++)
	{
		uint32 id = m_items[i].m_pObj->GetID();
		if (id)	// Write reference
		{
			std::fprintf(fp, "%ld 0 R", id);
		}
		else
		{
			m_items[i].m_pObj->WriteToStream(fp);
		}

		std::fprintf(fp, "\r\n");
	}

	std::fprintf(fp, "]");
}

void CPDFCosArray::ReadFromStream(std::FILE* fp)
{
	int c;

	c = std::fgetc(fp);
	ASSERT(c == '[');

	std::fscanf(fp, "\r\n ");

	while (!feof(fp))
	{
		c = std::fgetc(fp);
		if (c == ']')
			break;
		std::ungetc(c, fp);

		CosObject pObj = m_pCosDoc->ReadObject(fp);
	//	ASSERT(pObj);
	//	if (pObj)
		{
			m_items.Add(pObj);
		}

		std::fscanf(fp, "\r\n ");
	}

	ASSERT(c == ']');
}

void CPDFCosArray::CosArrayInsert(long pos, CPDFCosObj *obj)
{
//	obj->AddRef();
	if (pos < 0 || pos >= m_items.GetSize())
		m_items.Add(obj);
	else
		m_items.InsertAt(pos, obj);
}

long CPDFCosArray::GetLength() const
{
	return m_items.GetSize();
}

CPDFCosObj* CPDFCosArray::GetItem(int index)
{
	return m_items[index];
}

}
}
