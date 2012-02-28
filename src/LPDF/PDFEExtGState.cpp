#include "stdafx.h"
#include "LPDF.h"
#include "PDFEExtGState.h"

#include "PDFCosDict.h"
#include "PDFCosReal.h"

namespace System
{
namespace PDF
{

/////////////////////////////////////////////////////////////////////////////
// CPDFEExtGState

//	CPDFCosDict* m_cos;
//	int m_nIndex;

	/*
	void Create(CPDFCosDict* cosObj)
	{
		m_cos = cosObj;
		m_nIndex = 0;
	}
	*/

double CPDFEExtGState::GetOpacityFill()
{
	CPDFCosReal* pValue = dynamic_cast<CPDFCosReal*>(m_cos->CosDictGet(ASTR("ca")));
	if (pValue)
		return pValue->GetValue();
	else
		return 1.0;
}

void  CPDFEExtGState::SetOpacityFill(double opacity)
{
//	IPDFCosReal* pValue;
//	m_cos->CosDictGet("ca", (IPDFCosObj**)&pValue);
	CPDFCosReal* pValue = dynamic_cast<CPDFCosReal*>(m_cos->CosDictGet(ASTR("ca")));
	if (pValue == NULL)
	{
		pValue = m_cos->m_pCosDoc->CosNewReal(false, opacity);
		m_cos->CosDictPut(ASTR("ca"), pValue);
	}
	else
		pValue->SetValue(opacity);
}

double CPDFEExtGState::GetOpacityStroke()
{
//	IPDFCosReal* pValue;
//	m_cos->CosDictGet("CA", (IPDFCosObj**)&pValue);
	CPDFCosReal* pValue = dynamic_cast<CPDFCosReal*>(m_cos->CosDictGet(ASTR("CA")));
	if (pValue)
		return pValue->GetValue();
	else
		return 1.0;
}

void CPDFEExtGState::SetOpacityStroke(double opacity)
{
//	IPDFCosReal* pValue;
//	m_cos->CosDictGet("CA", (IPDFCosObj**)&pValue);
	CPDFCosReal* pValue = dynamic_cast<CPDFCosReal*>(m_cos->CosDictGet(ASTR("CA")));
	if (pValue == NULL)
	{
		pValue = m_cos->m_pCosDoc->CosNewReal(false, opacity);
		m_cos->CosDictPut(ASTR("CA"), pValue);
	}
	else
		pValue->SetValue(opacity);
}

}
}
