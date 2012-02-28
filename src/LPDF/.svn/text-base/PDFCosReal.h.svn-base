#pragma once

#include "PDFCosObj.h"

namespace System
{
namespace PDF
{

class PDFExt CPDFCosReal : 
	public CPDFCosObj//Impl<IPDFCosReal>
{
public:
	CPDFCosReal()
	{
		m_value = 0.0;
	}

	virtual void WriteToStream(std::FILE* fp);
	virtual void ReadFromStream(std::FILE* fp);

	double GetValue();
	void SetValue(double newVal);

	double m_value;
};

}	// PDF
}
