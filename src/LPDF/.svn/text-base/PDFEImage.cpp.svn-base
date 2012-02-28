// PDFEImage.cpp : Implementation of CPDFEImage
#include "stdafx.h"
#include "LPDF.h"
#include "PDFEImage.h"

#include "PDFEMatrix.h"

namespace System
{
namespace PDF
{

/////////////////////////////////////////////////////////////////////////////
// CPDFEImage

//virtual
void CPDFEImage::WriteToStream(std::FILE* fp)
{
	std::fprintf(fp, "q\r\n"); // Save graphics state

	double a = m_matrix->get_a();
	double b = m_matrix->get_b();
	double c = m_matrix->get_c();
	double d = m_matrix->get_d();
	double e = m_matrix->get_e();
	double f = m_matrix->get_f();
	std::fprintf(fp, "%g %g %g %g %g %g cm\r\n", a, b, c, d, e, f);

	std::fprintf(fp, "/Im%d Do\r\n", m_nIndex);	// Paint image

	std::fprintf(fp, "Q\r\n");// Restore graphics state
}

}
}
