#pragma once

#include "PDFCosObj.h"

namespace System
{
namespace PDF
{

class PDFExt CPDFCosName : 
	public CPDFCosObj//Impl<IPDFCosName>
{
public:
	CPDFCosName()
	{
	}

	System::StringA* GetValue()
	{
		return m_name;
	}

	virtual void WriteToStream(std::FILE* fp);
	virtual void ReadFromStream(std::FILE* fp);

	System::StringA* m_name;
};

}
}
