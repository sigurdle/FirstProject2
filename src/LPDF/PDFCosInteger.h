#pragma once

#include "PDFCosObj.h"

namespace System
{
namespace PDF
{

class PDFExt CPDFCosInteger : 
	public CPDFCosObj//Impl<IPDFCosInteger>
{
public:
	CPDFCosInteger()
	{
		m_value = 0;
	}

	CPDFCosInteger(long value)
	{
		m_value = value;
	}

	virtual void WriteToStream(std::FILE* fp);
	virtual void ReadFromStream(std::FILE* fp);

	void SetValue(long newVal);
	long GetValue() const;

protected:

	long m_value;
};

}
}
