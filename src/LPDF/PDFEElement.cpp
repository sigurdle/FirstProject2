#include "stdafx.h"
#include "LPDF.h"
#include "PDFEElement.h"

#include "PDFEMatrix.h"
#include "PDFEGraphicState.h"
#include "PDFEExtGState.h"

namespace System
{
namespace PDF
{

/////////////////////////////////////////////////////////////////////////////
// CPDFEElement

CPDFEElement::CPDFEElement()
{
	m_gstate = new CPDFEGraphicState;
	m_matrix = new CPDFEMatrix;
}

CPDFEElement::~CPDFEElement()
{
	if (m_gstate)
	{
	//	m_gstate->Release();
		m_gstate = NULL;
	}

	if (m_matrix)
	{
	//	m_matrix->Release();
		m_matrix = NULL;
	}
}

void CPDFEElement::SetMatrix(CPDFEMatrix* matrix)
{
	double a = matrix->get_a(); m_matrix->set_a(a);
	double b = matrix->get_b(); m_matrix->set_b(b);
	double c = matrix->get_c(); m_matrix->set_c(c);
	double d = matrix->get_d(); m_matrix->set_d(d);
	double e = matrix->get_e(); m_matrix->set_e(e);
	double f = matrix->get_f(); m_matrix->set_f(f);
}

void CPDFEElement::SetGState(/*[in]*/ CPDFEGraphicState* gstate)
{
	m_gstate->m_lineWidth = gstate->get_lineWidth();

//	m_gstate->m_extGState->Release();
	m_gstate->m_extGState = gstate->get_extGState();
}

CPDFEGraphicState* CPDFEElement::GetGState()
{
	CPDFEGraphicState* pGState = new CPDFEGraphicState;
	if (pGState)
	{
		pGState->m_lineWidth = m_gstate->m_lineWidth;
		pGState->m_extGState = m_gstate->m_extGState;

		return pGState;
	}

	return NULL;
}

}
}
