#include "stdafx.h"
#include "LPDF.h"
#include "PDFCosReal.h"

namespace System
{
namespace PDF
{

//virtual
void CPDFCosReal::WriteToStream(std::FILE* fp)
{
	std::fprintf(fp, "%g", m_value);
}

void CPDFCosReal::ReadFromStream(std::FILE* fp)
{
	std::fscanf(fp, "%lf", &m_value);
}

double CPDFCosReal::GetValue()
{
	return m_value;
}

void CPDFCosReal::SetValue(double newVal)
{
	m_value = newVal;
}

}	// PDF
}
