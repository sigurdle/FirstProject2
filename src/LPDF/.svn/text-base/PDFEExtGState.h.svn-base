#ifndef __PDFEEXTGSTATE_H_
#define __PDFEEXTGSTATE_H_

class CPDFCosDict;

#include "PDFObject.h"

namespace System
{
namespace PDF
{

class CPDFEExtGState : 
	public CPDFObject //<IPDFEExtGState>
{
public:
	CTOR CPDFEExtGState()
	{
		m_cos = NULL;
		m_nIndex = 0;
	}

	/*
	void Create(CPDFCosDict* cosObj)
	{
		m_cos = cosObj;
		m_nIndex = 0;
	}
	*/

public:
	void SetOpacityStroke(double newVal);
	double GetOpacityStroke();
	void SetOpacityFill(double newVal);
	double GetOpacityFill();
	PDFEType GetType() const
	{
		return kPDFEExtGState;
	}

public:

	CPDFCosDict* m_cos;
	int m_nIndex;
};

}
}

#endif //__PDFEEXTGSTATE_H_
