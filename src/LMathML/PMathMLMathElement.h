#pragma once

#include "PMathMLElementImpl.h"

class CPMathMLMathElement :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPMathMLElementImpl
{
public:
	CPMathMLMathElement()
	{
	}

// CSS Box Model
	virtual void Draw(CHTMRenderContext* pC);
	virtual void CalculateDimensions(CHTMCalcContext* pC);	// ??
//	virtual void BuildChildren();
	virtual BOOL HasDistributableChildren();	// ??

BEGIN_COM_MAP(CPMathMLMathElement)
	COM_INTERFACE_ENTRY(ILViewNode)
END_COM_MAP()
};
