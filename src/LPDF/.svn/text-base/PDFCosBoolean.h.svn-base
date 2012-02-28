#pragma once

#include "PDFCosObj.h"

namespace System
{
namespace PDF
{

class PDFExt CPDFCosBoolean : 
	public CPDFCosObj//Impl<IPDFCosBoolean>
{
public:
	CPDFCosBoolean()
	{
		m_value = false;
	}

	bool m_value;

	virtual void WriteToStream(std::FILE* fp);
	virtual void ReadFromStream(std::FILE* fp);

};

}
}
