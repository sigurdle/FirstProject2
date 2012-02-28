#include "stdafx.h"
#include "LPDF.h"
#include "PDFEGraphicState.h"
#include "PDFEExtGState.h"

namespace System
{
namespace PDF
{

void CPDFEGraphicState::set_lineWidth(double newVal)
{
	m_lineWidth = newVal;
}

long CPDFEGraphicState::get_lineCap()
{
	// TODO: Add your implementation code here

	return 0;
}

void CPDFEGraphicState::set_lineCap(long newVal)
{
	// TODO: Add your implementation code here

}

long CPDFEGraphicState::get_lineJoin()
{
	// TODO: Add your implementation code here

	return 0;
}

void CPDFEGraphicState::set_lineJoin(long newVal)
{
	// TODO: Add your implementation code here

}

double CPDFEGraphicState::get_miterLimit()
{
	// TODO: Add your implementation code here

	return 0;
}

void CPDFEGraphicState::set_miterLimit(double newVal)
{
	// TODO: Add your implementation code here

}

CPDFEExtGState* CPDFEGraphicState::get_extGState()
{
	return m_extGState;
}

void CPDFEGraphicState::set_extGState(CPDFEExtGState *newVal)
{
	m_extGState = newVal;
}

}
}
