#pragma once

#include "PDFCosObj.h"

namespace System
{
namespace PDF
{

class PDFExt CPDFCosArray : 
	public CPDFCosObj//Impl<IPDFCosArray>
{
public:
	CPDFCosArray()
	{
	}

	vector<CosObject> m_items;

	virtual void WriteToStream(std::FILE* fp);
	virtual void ReadFromStream(std::FILE* fp);

	long GetLength() const;
	CPDFCosObj* GetItem(int index);

	void CosArrayInsert(long pos, CPDFCosObj* obj);
};

}
}
