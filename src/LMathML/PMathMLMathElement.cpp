#include "stdafx.h"
#include "LHTML.h"
#include "LHTML2.h"

#include "PMathMLMathElement.h"

//virtual
BOOL CPMathMLMathElement::HasDistributableChildren()
{
	return FALSE;
}

//virtual
void CPMathMLMathElement::CalculateDimensions(CHTMCalcContext* pC)
{
#if 0	// TODO, removed this, I don't think this should be here?
	GetCSSProperties(pC);
#endif

	m_specifiedWidth = 100;
	m_specifiedHeight = 100;
}

//virtual
void CPMathMLMathElement::Draw(CHTMRenderContext* pC)
{
}
