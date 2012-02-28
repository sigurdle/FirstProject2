#pragma once

#include "PDFCosObj.h"

namespace System
{
namespace PDF
{

class PDFExt CPDFCosString : 
	public CPDFCosObj//Impl<IPDFCosString>
{
public:
	CPDFCosString();

	virtual void WriteToStream(std::FILE* fp);
	virtual void ReadFromStream(std::FILE* fp);

	System::StringA* GetValue();

	System::StringA* m_value;
};

}
}
