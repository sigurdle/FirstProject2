#include "stdafx.h"
#include "LPDF.h"
#include "PDFCosInteger.h"

namespace System
{
namespace PDF
{

//virtual
void CPDFCosInteger::WriteToStream(std::FILE* fp)
{
	std::fprintf(fp, "%ld", m_value);
}

void CPDFCosInteger::ReadFromStream(std::FILE* fp)
{
	std::fscanf(fp, "%ld", &m_value);
}

long CPDFCosInteger::GetValue() const
{
	return m_value;
}

void CPDFCosInteger::SetValue(long newVal)
{
	m_value = newVal;
}

}
}
